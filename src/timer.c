#ifdef TEST
#include "xc_stub.h"
#else
#include <xc.h>
#endif

#include <stdint.h>
#include <stdbool.h>

#include "pic32_config.h"
#include "sysclk.h"
#include "interrupt.h"
#include "helpers.h"
#include "timer.h"

#define TMR_TCKPS_BIT_1 (4)
#define TMR_TCKPS_BIT_2 (5)
#define TMR_TCKPS_BIT_3 (6)
#define TMR_ON_BIT      (15)

#define TMR1_TCKPS_MASK ((1 << TMR_TCKPS_BIT_1) | (1 << TMR_TCKPS_BIT_2))

#define TMR_TCKPS_MASK  ((1 << TMR_TCKPS_BIT_1) | \
                        (1 << TMR_TCKPS_BIT_2) | \
                        (1 << TMR_TCKPS_BIT_3))

#define TCON(x)             T ## x ## CON
#define TCONbits_TCKPS(x)   T ## x ## CONbits.TCKPS
#define TCONbits_ON(x)      T ## x ## CONbits.ON
#define IECbits_TIE(x, y)   IEC ## y ## bits.T ## x ## IE
#define IFSbits_TIF(x, y)   IFS ## y ## bits.T ## x ## IF
#define IPCbits_TIP(x, y)   IPC ## y ## bits.T ## x ## IP
#define IPCbits_TIS(x, y)   IPC ## y ## bits.T ## x ## IS
#define PR(x)               PR ## x
#define TMR(x)              TMR ## x

#define is_idvalid(x) if ((x) < PIC32_TIMER_2 || (x) > PIC32_TIMER_9) return (-1);

#define MAX_TMR_PR_VALUE (65535U)
#define DEFAULT_SUB_PRIO 1

enum
{
  PIC32_TIMER_1 = 0,
  PIC32_TIMER_2,
  PIC32_TIMER_3,
  PIC32_TIMER_4,
  PIC32_TIMER_5,
  PIC32_TIMER_6,
  PIC32_TIMER_7,
  PIC32_TIMER_8,
  PIC32_TIMER_9,
  PIC32_TIMER_MAX,
};

enum
{
  TMR1_PRESCALE_1   = 0b00,
  TMR1_PRESCALE_8   = 0b01,
  TMR1_PRESCALE_64  = 0b10,
  TMR1_PRESCALE_256 = 0b11,
};

/* timers from 2 to 9. */

enum
{
  TMR_PRESCALE_1    = 0b000,
  TMR_PRESCALE_2    = 0b001,
  TMR_PRESCALE_4    = 0b010,
  TMR_PRESCALE_8    = 0b011,
  TMR_PRESCALE_16   = 0b100,
  TMR_PRESCALE_32   = 0b101,
  TMR_PRESCALE_64   = 0b110,
  TMR_PRESCALE_256  = 0b111,
  TMR_PRESCALE_MAX_INDX  = 8,
};

static uint16_t tmr1_prescale_value[] = {
  1, 8, 64, 256
};
static uint16_t tmrs_prescale_value[] = {
  1, 2, 4, 8, 16, 32, 64, 256
};

static uint32_t volatile * const tmr_con[PIC32_TIMER_MAX] =
{
  &T1CON,
  &T2CON,
  &T3CON,
  &T4CON,
  &T5CON,
  &T6CON,
  &T7CON,
  &T8CON,
  &T9CON,
};

static uint32_t volatile * const tmr_loadval[PIC32_TIMER_MAX] =
{
  &PR1,
  &PR2,
  &PR3,
  &PR4,
  &PR5,
  &PR6,
  &PR7,
  &PR8,
  &PR9,
};

static uint32_t volatile * const tmr_tmr[PIC32_TIMER_MAX] =
{
  &TMR1,
  &TMR2,
  &TMR3,
  &TMR4,
  &TMR5,
  &TMR6,
  &TMR7,
  &TMR8,
  &TMR9,
};

static bool timer_int_oneshot[PIC32_TIMER_MAX];

static intr_regs_t const timer_intreg[PIC32_TIMER_MAX] =
{
  {
    .flag      = &IFS0,
    .enable    = &IEC0,
    .prio      = &IPC1,
    .prioshift = IPC_PRIO_SHIFT_0,
    .subpshift = IPC_SUBP_SHIFT_0,
    .defprio   = TIMER1_INT_PRIO,
    .ibit      = 4,
  },
  {
    .flag      = &IFS0,
    .enable    = &IEC0,
    .prio      = &IPC2,
    .prioshift = IPC_PRIO_SHIFT_8,
    .subpshift = IPC_SUBP_SHIFT_8,
    .defprio   = TIMER2_INT_PRIO,
    .ibit      = 9,
  },
  {
    .flag      = &IFS0,
    .enable    = &IEC0,
    .prio      = &IPC3,
    .prioshift = IPC_PRIO_SHIFT_16,
    .subpshift = IPC_SUBP_SHIFT_16,
    .defprio   = TIMER3_INT_PRIO,
    .ibit      = 14,
  },
  {
    .flag      = &IFS0,
    .enable    = &IEC0,
    .prio      = &IPC4,
    .prioshift = IPC_PRIO_SHIFT_24,
    .subpshift = IPC_SUBP_SHIFT_24,
    .defprio   = TIMER4_INT_PRIO,
    .ibit      = 19,
  },
  {
    .flag      = &IFS0,
    .enable    = &IEC0,
    .prio      = &IPC6,
    .prioshift = IPC_PRIO_SHIFT_0,
    .subpshift = IPC_SUBP_SHIFT_0,
    .defprio   = TIMER5_INT_PRIO,
    .ibit      = 24,
  },
  {
    .flag      = &IFS0,
    .enable    = &IEC0,
    .prio      = &IPC7,
    .prioshift = IPC_PRIO_SHIFT_0,
    .subpshift = IPC_SUBP_SHIFT_0,
    .defprio   = TIMER6_INT_PRIO,
    .ibit      = 28,
  },
  {
    .flag      = &IFS1,
    .enable    = &IEC1,
    .prio      = &IPC8,
    .prioshift = IPC_PRIO_SHIFT_0,
    .subpshift = IPC_SUBP_SHIFT_0,
    .defprio   = TIMER7_INT_PRIO,
    .ibit      = 0,
  },
  {
    .flag      = &IFS1,
    .enable    = &IEC1,
    .prio      = &IPC9,
    .prioshift = IPC_PRIO_SHIFT_0,
    .subpshift = IPC_SUBP_SHIFT_0,
    .defprio   = TIMER8_INT_PRIO,
    .ibit      = 4,
  },
  {
    .flag      = &IFS1,
    .enable    = &IEC1,
    .prio      = &IPC10,
    .prioshift = IPC_PRIO_SHIFT_0,
    .subpshift = IPC_SUBP_SHIFT_0,
    .defprio   = TIMER9_INT_PRIO,
    .ibit      = 8,
  },

};

static int_callback_ft timer_int_cb[PIC32_TIMER_MAX];

void timer_1_init(void)
{
  uint32_t tmr_clk = sysclk_timerfreq_get();

  *tmr_con[PIC32_TIMER_1] = 0x0;
  *tmr_tmr[PIC32_TIMER_1] = 0x0;
  
  *tmr_loadval[PIC32_TIMER_1] = tmr_clk / TIMER_1_FREQ / tmr1_prescale_value[TMR_PRESCALE_1];
  BIT_MASK(tmr_con[PIC32_TIMER_1], TMR1_TCKPS_MASK, (TMR_PRESCALE_1 << TMR_TCKPS_BIT_1));

  BIT_CLR(timer_intreg[PIC32_TIMER_1].enable, timer_intreg[PIC32_TIMER_1].ibit);
  
  BIT_CLR(timer_intreg[PIC32_TIMER_1].flag, timer_intreg[PIC32_TIMER_1].ibit);

  BIT_WRITE(timer_intreg[PIC32_TIMER_1].prio, INT_PRIO_BITLEN, 
            timer_intreg[PIC32_TIMER_1].prioshift,
            timer_intreg[PIC32_TIMER_1].defprio);

  BIT_WRITE(timer_intreg[PIC32_TIMER_1].prio, INT_SUBP_BITLEN,
            timer_intreg[PIC32_TIMER_1].subpshift,
            0);

  BIT_SET(timer_intreg[PIC32_TIMER_1].enable, timer_intreg[PIC32_TIMER_1].ibit);

  BIT_SET(tmr_con[PIC32_TIMER_1], TMR_ON_BIT);
}

int timer_setperiod_ms(int timer_id, uint32_t prd_ms)
{
  int prs_idx;
  uint32_t tmr_clk;
  uint32_t tmr_preload;
  double freq;

  is_idvalid(timer_id);

  if (prd_ms < 1)
    return -1; /* minimum of period 1 ms */

  freq = (1.0 / (double)prd_ms) * 1000.0;
  
  tmr_clk = sysclk_timerfreq_get();

  /* check if a prescaler is required */
  for (prs_idx = 0; prs_idx < TMR_PRESCALE_MAX_INDX; prs_idx++)
  {
    tmr_preload = tmr_clk / (uint32_t)freq / tmrs_prescale_value[prs_idx];

    if (tmr_preload <= MAX_TMR_PR_VALUE && tmr_preload > 0)
      break;
  }

  if (prs_idx == TMR_PRESCALE_MAX_INDX)
  {
    /* preload value failed */
    return -1;
  }

  *tmr_loadval[timer_id] = tmr_clk / freq / tmrs_prescale_value[prs_idx];
  BIT_MASK(tmr_con[timer_id], TMR_TCKPS_MASK, (prs_idx << TMR_TCKPS_BIT_1));

  return 0;
}

int timer_start(int timer_id)
{
  is_idvalid(timer_id);

  BIT_SET(tmr_con[timer_id], TMR_ON_BIT);

  timer_int_oneshot[timer_id] = false;

  return 0;
}

int timer_start_oneshot(int timer_id)
{
  is_idvalid(timer_id);

  BIT_SET(tmr_con[timer_id], TMR_ON_BIT);

  timer_int_oneshot[timer_id] = true;
  
  return 0;
}

int timer_init(int timer_id,
               int_callback_ft intcb)
{
  is_idvalid(timer_id);

  *tmr_con[timer_id] = 0x0;
  *tmr_tmr[timer_id] = 0x0;


  BIT_CLR(timer_intreg[timer_id].enable, timer_intreg[timer_id].ibit);
  
  BIT_CLR(timer_intreg[timer_id].flag, timer_intreg[timer_id].ibit);

  BIT_WRITE(timer_intreg[timer_id].prio, INT_PRIO_BITLEN, 
            timer_intreg[timer_id].prioshift,
            timer_intreg[timer_id].defprio);

  BIT_WRITE(timer_intreg[timer_id].prio, INT_SUBP_BITLEN,
            timer_intreg[timer_id].subpshift,
            DEFAULT_SUB_PRIO);

  if (intcb != NULL)
  {
    timer_int_cb[timer_id] = intcb;
    BIT_SET(timer_intreg[timer_id].enable, timer_intreg[timer_id].ibit);
  }

  return 0;
}

int timer_stop(int timer_id)
{
  is_idvalid(timer_id);

  BIT_CLR(tmr_con[timer_id], TMR_ON_BIT);

  return 0;
}

#ifdef __cplusplus
extern "C" {
#endif

#if (TIMER_2_ENABLED == 1)
void timer_2_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_2] != NULL)
    timer_int_cb[PIC32_TIMER_2]();

  if (timer_int_oneshot[PIC32_TIMER_2] == true)
    BIT_CLR(tmr_con[PIC32_TIMER_2], TMR_ON_BIT);
}
#endif

#if (TIMER_3_ENABLED == 1)
void timer_3_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_3] != NULL)
    timer_int_cb[PIC32_TIMER_3]();

  if (timer_int_oneshot[PIC32_TIMER_3] == true)
    BIT_CLR(tmr_con[PIC32_TIMER_3], TMR_ON_BIT);
}
#endif

#if (TIMER_4_ENABLED == 1)
void timer_4_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_4] != NULL)
    timer_int_cb[PIC32_TIMER_4]();

  if (timer_int_oneshot[PIC32_TIMER_4] == true)
    BIT_CLR(tmr_con[PIC32_TIMER_4], TMR_ON_BIT);
}
#endif

#if (TIMER_5_ENABLED == 1)
void timer_5_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_5] != NULL)
    timer_int_cb[PIC32_TIMER_5]();

  if (timer_int_oneshot[PIC32_TIMER_5] == true)
    BIT_CLR(tmr_con[PIC32_TIMER_5], TMR_ON_BIT);
}
#endif

#if (TIMER_6_ENABLED == 1)
void timer_6_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_6] != NULL)
    timer_int_cb[PIC32_TIMER_6]();

  if (timer_int_oneshot[PIC32_TIMER_6] == true)
    BIT_CLR(tmr_con[PIC32_TIMER_6], TMR_ON_BIT);
}
#endif

#if (TIMER_7_ENABLED == 1)
void timer_7_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_7] != NULL)
    timer_int_cb[PIC32_TIMER_7]();

  if (timer_int_oneshot[PIC32_TIMER_7] == true)
    BIT_CLR(tmr_con[PIC32_TIMER_7], TMR_ON_BIT);
}
#endif

#if (TIMER_8_ENABLED == 1)
void timer_8_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_8] != NULL)
    timer_int_cb[PIC32_TIMER_8]();

  if (timer_int_oneshot[PIC32_TIMER_8] == true)
    BIT_CLR(tmr_con[PIC32_TIMER_8], TMR_ON_BIT);
}
#endif

#if (TIMER_9_ENABLED == 1)
void timer_9_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_9] != NULL)
    timer_int_cb[PIC32_TIMER_9]();

  if (timer_int_oneshot[PIC32_TIMER_9] == true)
    BIT_CLR(tmr_con[PIC32_TIMER_9], TMR_ON_BIT);
}
#endif

#ifdef __cplusplus
}
#endif
