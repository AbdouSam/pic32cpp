/*
 * @Author AbdouSam
 * @brief, simplest code to test-run a PIC32MZ without any use of libraries
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "pic32_config.h"

#include "uart.h"
#include "interrupt.h"
#include "timer.h"
#include "gpio.h"
#include "delay.h"
#include "debug.h"
#include "wdt.h"
#include "app.h"

static char          c_tmp;
static char          rx_tmp[10];
static int           rx_index = 0;

static unsigned int  millis = 0;
static bool          wdt_clear_flag = true;

static void timer_wdt_callback(void)
{
  gpio_state_toggle(LED_RED);
  gpio_state_toggle(LED_GREEN);
  wdt_clear_flag = true;
}

static char read_char(void)
{
  if (uart_rx_any(PIC32_UART_4)) /* Data ready */
    {
      return uart_rx_char(PIC32_UART_4);
    }
  return 0;
}

static void uart_callback(void)
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

int app_init(void)
{
  /* Initial IO as it is set in pic32_config.h */
  gpio_init();

  gpio_output_set(LED_ORANGE);
  gpio_output_set(LED_RED);
  gpio_output_set(LED_GREEN);

  gpio_state_clear(LED_ORANGE);
  gpio_state_clear(LED_RED);
  gpio_state_clear(LED_GREEN);

  uart_rxi_set(PIC32_UART_4, 3, IF_RBUF_NOT_EMPTY, uart_callback);
  
  debug_init();

  delay_ms(100);

  debug_print("Hello World\n");

  timer_1_init();

  if (timer_init(PIC32_TIMER_2, 2 /* Hz */, 0, timer_wdt_callback) < 0)
  {
    debug_print("Timer 2 failed to init\n");
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

  if (wdt_clear_flag)
  {
    wdt_clear_flag = false;
    wdt_clear();
  }

}