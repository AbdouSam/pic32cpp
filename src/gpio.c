#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "helpers.h"

#include "pic32_config.h"
#include "error.h"

#ifndef TEST
#include <xc.h>
#else
#include <stddef.h>
#include "xc_stub.h"
#endif

#include "gpio.h"


#if (PIC32_PIN_COUNT == 64)
# define PIC32_PORT_COUNT   6
#elif (PIC32_PIN_COUNT == 100)
# define PIC32_PORT_COUNT   7
#elif (PIC32_PIN_COUNT == 124)
# define PIC32_PORT_COUNT   9
#elif (PIC32_PIN_COUNT == 144)
# define PIC32_PORT_COUNT   10
#else
  #error "Pin Count Inavailable in this series"
#endif

#define is_regindex_valid(x)  if ((unsigned)x > GPIO_MAP_REG_MAX)return (ERRMAX)

uint32_t volatile *gpio_tris[] =
{
#if (PIC32_PIN_COUNT != 64)
  &TRISA,
#endif
  &TRISB,
  &TRISC,
  &TRISD,
  &TRISE,
  &TRISF,
  &TRISG,
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
  &TRISH,
  &TRISJ,
#endif
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100) && \
  (PIC32_PIN_COUNT != 124))
  &TRISK,
#endif
};

uint32_t volatile *gpio_lat[] =
{
#if (PIC32_PIN_COUNT != 64)
  &LATA,
#endif
  &LATB,
  &LATC,
  &LATD,
  &LATE,
  &LATF,
  &LATG,
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
  &LATH,
  &LATJ,
#endif
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100) && \
  (PIC32_PIN_COUNT != 124))
  &LATK,
#endif
};

uint32_t volatile *gpio_port[] =
{
#if (PIC32_PIN_COUNT != 64)
  &PORTA,
#endif
  &PORTB,
  &PORTC,
  &PORTD,
  &PORTE,
  &PORTF,
  &PORTG,
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
  &PORTH,
  &PORTJ,
#endif
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100) && \
  (PIC32_PIN_COUNT != 124))
  &PORTK,
#endif
};


uint32_t volatile *gpio_odc[] =
{
#if (PIC32_PIN_COUNT != 64)
  &ODCA,
#endif
  &ODCB,
  &ODCC,
  &ODCD,
  &ODCE,
  &ODCF,
  &ODCG,
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
  &ODCH,
  &ODCJ,
#endif
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100) && \
  (PIC32_PIN_COUNT != 124))
  &ODCK,
#endif
};



static uint32_t volatile  * const   output_map_register[] = {
  &RPD2R,
  &RPG8R,
  &RPF4R,
  &RPD10R,
  &RPF1R,
  &RPB9R,
  &RPB10R,
  &RPC14R,
  &RPB5R,
  NULL,
#if (PIC32_PIN_COUNT != 64)
  &RPC1R,
  &RPD14R,
  &RPG1R,
  &RPA14R,
#else
  NULL,
  NULL,
  NULL,
  NULL,
#endif
#if ((PIC32_PIN_COUNT != 100) && (PIC32_PIN_COUNT != 64))
  &RPD6R,
#else
  NULL,
#endif
  NULL,

  &RPD3R,
  &RPG7R,
  &RPF5R,
  &RPD11R,
  &RPF0R,
  &RPB1R,
  &RPE5R,
  &RPC13R,
  &RPB3R,
  NULL,
#if (PIC32_PIN_COUNT != 64)
  &RPC4R,
  &RPD15R,
  &RPG0R,
  &RPA15R,
#else
  NULL,
  NULL,
  NULL,
  NULL,
#endif
#if ((PIC32_PIN_COUNT != 100) && (PIC32_PIN_COUNT != 64))
  &RPD7R,
#else
  NULL,
#endif
  NULL,

  &RPD9R,
  &RPG6R,
  &RPB8R,
  &RPB15R,
  &RPD4R,
  &RPB0R,
  &RPE3R,
  &RPB7R,
  NULL,
#if (PIC32_PIN_COUNT != 64)
  &RPF12R,
  &RPD12R,
  &RPF8R,
  &RPC3R,
  &RPE9R,
#else
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,

#endif
  NULL,
  NULL,

  &RPD1R,
  &RPG9R,
  &RPB14R,
  &RPD0R,
  NULL,
  &RPB6R,
  &RPD5R,
  &RPB2R,
  &RPF3R,
#if (PIC32_PIN_COUNT != 64)
  &RPF13R,
  NULL,
  &RPF2R,
  &RPC2R,
  &RPE8R,
#else
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
#endif
  NULL,
  NULL,
};

int gpio_outfunc_map_set(int func_index, int value)
{
  is_regindex_valid(func_index);
  *output_map_register[func_index] = value;
  return OK;
}

void gpio_output_set(uint8_t port, uint16_t pin)
{
  BIT_CLR(gpio_tris[port], pin);
}

void gpio_input_set(uint8_t port, uint16_t pin)
{

  BIT_SET(gpio_tris[port], pin);
}

/* Pin acts as an open drain output */
void gpio_open_drain_set(uint8_t port, uint16_t pin)
{
  /* check if pin is output */

  BIT_SET(gpio_odc[port], pin);
}

/* Pin acts as normal digital output */
void gpio_open_drain_clear(uint8_t port, uint16_t pin)
{

  BIT_CLR(gpio_odc[port], pin);
}

void gpio_state_write(uint8_t port, uint16_t pin, bool state)
{
  if (state)
    {
      BIT_SET(gpio_lat[port], pin);
    }
  else
    {
      BIT_CLR(gpio_lat[port], pin);
    }
}

void gpio_state_set(uint8_t port, uint16_t pin)
{

  BIT_SET(gpio_lat[port], pin);
}

void gpio_state_clear(uint8_t port, uint16_t pin)
{

  BIT_CLR(gpio_lat[port], pin);
}

void gpio_state_toggle(uint8_t port, uint16_t pin)
{

  BIT_INV(gpio_lat[port], pin);
}

bool gpio_state_get(uint8_t port, uint16_t pin)
{

  return !((*gpio_port[port] & (1 << pin)) == 0);
}

bool gpio_isinput(uint8_t port, uint16_t pin)
{
  return !((*gpio_tris[port] & (1 << pin)) == 0);
}

bool gpio_isoutput(uint8_t port, uint16_t pin)
{
  return !gpio_isinput(port, pin);
}

void gpio_init(void)
{
#if (PIC32_PIN_COUNT != 64)
  ANSELA = 0;
#endif

  ANSELB = 0;

#if (PIC32_PIN_COUNT != 64)
  ANSELC = 0;
#endif

#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
  ANSELD = 0;
#endif

  ANSELE = 0;
#if (PIC32_PIN_COUNT != 64)
  ANSELF = 0;
#endif

  ANSELG = 0;

#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
  ANSELH    = 0;
  ANSELJ    = 0;
#endif

}
