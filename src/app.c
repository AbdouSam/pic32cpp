/*
 * @Author AbdouSam
 * @brief, simplest code to test-run a PIC32MZ without any use of libraries
 *
 */

#include <xc.h>


#include <string.h>
#include <stdbool.h>

#include "pic32_config.h"

/*
#include "debug.h"
#include "uart.h"
*/
#include "interrupt.h"
#include "timer.h"
#include "sysclk.h"
#include "gpio.h"
#include "delay.h"
#include "app.h"

/* This define is to set the  µC to run on internal clock
 * config is set to run CPU at 200 Mhz,
 * with internal or 24Mhz external clock
 */

/*#define CONFIG_CPU_USE_FRC */

/*** DEVCFG0 ***/
#pragma config DEBUG =      OFF
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx1
#pragma config TRCEN =      OFF
#pragma config BOOTISA =    MIPS32
#pragma config FECCCON =    OFF_UNLOCKED
#pragma config FSLEEP =     OFF
#pragma config DBGPER =     PG_ALL
#pragma config SMCLR =      MCLR_NORM
#pragma config SOSCGAIN =   GAIN_2X
#pragma config SOSCBOOST =  ON
#pragma config POSCGAIN =   GAIN_0_5X
#pragma config POSCBOOST =  ON
#pragma config EJTAGBEN =   NORMAL
#pragma config CP =         OFF /* code protect */

/*** DEVCFG1 ***/

#pragma config FNOSC =      SPLL
#pragma config DMTINTV =    WIN_127_128
#pragma config FSOSCEN =    OFF
#pragma config IESO =       OFF

#ifdef CONFIG_CPU_USE_FRC
#pragma config POSCMOD =    OFF
#else
#pragma config POSCMOD =    HS
#endif

#pragma config OSCIOFNC =   OFF
#pragma config FCKSM =      CSECME
#pragma config WDTPS =      PS1048576
#pragma config WDTSPGM =    STOP
#pragma config FWDTEN =     OFF /* WatchDog timer */
#pragma config WINDIS =     NORMAL
#pragma config FWDTWINSZ =  WINSZ_25
#pragma config DMTCNT =     DMT31
#pragma config FDMTEN =     OFF /* Deadman timer */

/*** DEVCFG2 ***/

#ifdef CONFIG_CPU_USE_FRC
#pragma config FPLLIDIV =   DIV_1
#else
#pragma config FPLLIDIV =   DIV_3
#endif

#pragma config FPLLRNG =    RANGE_5_10_MHZ

#ifdef CONFIG_CPU_USE_FRC
#pragma config FPLLICLK =   PLL_FRC
#else
#pragma config FPLLICLK =   PLL_POSC
#endif

#pragma config FPLLMULT =   MUL_50
#pragma config FPLLODIV =   DIV_2
#pragma config UPLLFSEL =   FREQ_24MHZ

/*** DEVCFG3 ***/

#pragma config USERID =     0xffff
#pragma config FMIIEN =     OFF
#pragma config FETHIO =     ON
#pragma config PGL1WAY =    ON
#pragma config PMDL1WAY =   ON
#pragma config IOL1WAY =    ON
#pragma config FUSBIDIO =   OFF

/*** BF1SEQ0 ***/

#pragma config TSEQ =       0x0000
#pragma config CSEQ =       0xffff

#if 0
static char          c_tmp;
static char          rx_tmp[10];
static int           rx_index = 0;
#endif

static unsigned int  millis = 0;
static bool          wdt_clear_flag = true;

static void wdt_clear(void)
{
  volatile uint16_t * wdtclrkey;
  asm volatile("di");
  /* get address of upper 16-bit word of the WDTCON SFR */
  wdtclrkey     = ( (volatile uint16_t *)&WDTCON ) + 1;
  *wdtclrkey    = 0x5743;
  asm volatile("ei");
}

/**
 * override weak def in interrupt.c 
 */
void timer_2_callback(void)
{
  gpio_state_toggle(LED_RED);
  gpio_state_toggle(LED_GREEN);
  wdt_clear_flag = true;
}

#if 0
static char read_char(void)
{
  if (uart_rx_any(PIC32_UART_4)) /* Data ready */
    {
      return uart_rx_char(PIC32_UART_4);
    }
  return 0;
}

void uart_callback(void)
{

  gpio_state_toggle(pinE9);
  c_tmp = read_char();
  if (c_tmp != '\n')
    rx_tmp[rx_index] = c_tmp;

  rx_index++;
  if (rx_index > 9)
  {
    rx_index = 0;
  }
}

#endif

int app_init(void)
{
  sysclk_init();

  /* Initial IO as it is set in pic32_config.h */
  gpio_init();

  gpio_state_clear(LED_ORANGE);
  gpio_state_clear(LED_RED);
  gpio_state_clear(LED_GREEN);

  //uart_rxi_set(PIC32_UART_4, 3, IF_RBUF_NOT_EMPTY, uart_callback);
  
  //debug_init();

  delay_ms(100);

  //debug_print("Hello World\n");

  timer_1_init();

  if (timer_init(PIC32_TIMER_2, 2 /* Hz */, 0) < 0)
  {
    //debug_print("Timer 2 failed to init\n");
  } 

  interrupt_init();
  return 0;
}

void app_task(void)
{
  if (interrupt_tick_get() - millis >= 1000)
    {
      /* test timer/interrupt/gpio */
      gpio_state_toggle(LED_ORANGE);

      millis = interrupt_tick_get();

    }

  #if 0
  int c_local;

  if ((c_tmp >= 'a') && (c_tmp <= 'z'))
    {
      uart_tx_char(PIC32_UART_4, c_tmp);
      uart_tx_char(PIC32_UART_4, '\n');
      c_tmp = 0;
    }

  if (c_tmp == '\n')
    {
      debug_print("Word: ");

      for (c_local = 0; c_local<10; c_local++)
        debug_putc(rx_tmp[c_local]);

      debug_putc('\n');
      c_tmp = 0;
    }

#endif
  if (wdt_clear_flag)
  {
    wdt_clear_flag = false;
    wdt_clear();
  }

}