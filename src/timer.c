#include <stdint.h>
#include <xc.h>

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

#define MAX_TMR_PR_VALUE (65535U)

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

int timer_init(pic32_timer_t timer_id,
               uint32_t freq,
               uint8_t subp,
               int_callback_ft intcb)
{
  uint32_t tmr_clk;
  uint32_t tmr_preload;
  int prs_idx;

  if (timer_id < PIC32_TIMER_2 || timer_id > PIC32_TIMER_9)
  {
    return -1;
  }

  *tmr_con[timer_id] = 0x0;
  *tmr_tmr[timer_id] = 0x0;

  tmr_clk = sysclk_timerfreq_get();

  /* check if a prescaler is required */
  for (prs_idx = 0; prs_idx < TMR_PRESCALE_MAX_INDX; prs_idx++)
  {
    tmr_preload = tmr_clk / freq / tmrs_prescale_value[prs_idx];

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


  BIT_CLR(timer_intreg[timer_id].enable, timer_intreg[timer_id].ibit);
  
  BIT_CLR(timer_intreg[timer_id].flag, timer_intreg[timer_id].ibit);

  BIT_WRITE(timer_intreg[timer_id].prio, INT_PRIO_BITLEN, 
            timer_intreg[timer_id].prioshift,
            timer_intreg[timer_id].defprio);

  BIT_WRITE(timer_intreg[timer_id].prio, INT_SUBP_BITLEN,
            timer_intreg[timer_id].subpshift,
            subp);

  BIT_SET(timer_intreg[timer_id].enable, timer_intreg[timer_id].ibit);

  if (intcb != NULL)
    timer_int_cb[timer_id] = intcb;

  BIT_SET(tmr_con[timer_id], TMR_ON_BIT);

  return 0;
}

int timer_stop(pic32_timer_t timer_id)
{
   if (timer_id < PIC32_TIMER_2 || timer_id > PIC32_TIMER_9)
  {
    return -1;
  }

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
}
#endif

#if (TIMER_3_ENABLED == 1)
void timer_3_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_3] != NULL)
    timer_int_cb[PIC32_TIMER_3]();
}
#endif

#if (TIMER_4_ENABLED == 1)
void timer_4_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_4] != NULL)
    timer_int_cb[PIC32_TIMER_4]();
}
#endif

#if (TIMER_5_ENABLED == 1)
void timer_5_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_5] != NULL)
    timer_int_cb[PIC32_TIMER_5]();
}
#endif

#if (TIMER_6_ENABLED == 1)
void timer_6_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_6] != NULL)
    timer_int_cb[PIC32_TIMER_6]();
}
#endif

#if (TIMER_7_ENABLED == 1)
void timer_7_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_7] != NULL)
    timer_int_cb[PIC32_TIMER_7]();
}
#endif

#if (TIMER_8_ENABLED == 1)
void timer_8_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_8] != NULL)
    timer_int_cb[PIC32_TIMER_8]();
}
#endif

#if (TIMER_9_ENABLED == 1)
void timer_9_callback(void)
{
  if (timer_int_cb[PIC32_TIMER_9] != NULL)
    timer_int_cb[PIC32_TIMER_9]();
}
#endif

#ifdef __cplusplus
}
#endif
