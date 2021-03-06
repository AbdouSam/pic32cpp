#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "pic32_config.h"

#include "gpio.h"
#include "uart.h"
#include "debug.h"

#define STR_SIZE 256

typedef struct
{
  pic32_uart_t id;
  uint16_t rs485pin;
}dbg_port_t;

static dbg_port_t dbg_port;

static void dbg_puts(pic32_uart_t id, char *s)
{
  unsigned int i;

  for (i = 0; i < strlen(s); i++)
    {
      uart_tx_char(id, s[i]);
    }
}

void debug_init(void)
{
  dbg_port.id = UART_ATTACHED_TO_DBG;

  uart_init(dbg_port.id, 
            NO_PARITY_8_BIT_DATA,
            ONE_STOP_BIT, 
            UART_DEBUG_BAUDRATE);

  #ifdef CONFIG_DEBUG_RS485_PIN
  dbg_port.rs485pin = CONFIG_DEBUG_RS485_PIN;
  gpio_output_set(0, dbg_port.rs485pin); // for later fix
  #endif
}

int debug_print(const char * format, ...)
{
  int ret;
  va_list args;
  char  str[STR_SIZE];

  va_start(args, format);

  vsprintf(str, format, args);

#ifdef CONFIG_DEBUG_RS485_PIN
  gpio_state_set(dbg_port.rs485pin);
#endif

  dbg_puts(dbg_port.id, str);

#ifdef CONFIG_DEBUG_RS485_PIN
  gpio_state_clear(dbg_port.rs485pin);
#endif


  va_end(args);

  /* ret is supposed to have the number of charachters written.
   * dbg_puts doesn't implement this. Come back to this later.
   */

  ret = 0;

  return ret;
}

void debug_putc(char c)
{

#ifdef CONFIG_DEBUG_RS485_PIN
  gpio_state_set(dbg_port.rs485pin);
#endif
  uart_tx_char(dbg_port.id, c);
#ifdef CONFIG_DEBUG_RS485_PIN
  gpio_state_clear(dbg_port.rs485pin);
#endif

}
