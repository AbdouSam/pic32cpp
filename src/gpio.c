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

static const uint8_t                pin_map[] = {
  pinD2,
  pinG8,
  pinF4,
  pinD10,
  pinF1,
  pinB9,
  pinB10,
  pinC14,
  pinB5,
  INPUT_PIN_NC,
#if (PIC32_PIN_COUNT != 64)
  pinC1,
  pinD14,
  pinG1,
  pinA14,
#else
  INPUT_PIN_NC,
  INPUT_PIN_NC,
  INPUT_PIN_NC,
  INPUT_PIN_NC,
#endif
#if ((PIC32_PIN_COUNT != 100) && (PIC32_PIN_COUNT != 64))
  pinD6,
#else
  INPUT_PIN_NC,
#endif
  INPUT_PIN_NC,

  pinD3,
  pinG7,
  pinF5,
  pinD11,
  pinF0,
  pinB1,
  pinE5,
  pinC13,
  pinB3,
  INPUT_PIN_NC,
#if (PIC32_PIN_COUNT != 64)
  pinC4,
  pinD15,
  pinG0,
  pinA15,
#else
  INPUT_PIN_NC,
  INPUT_PIN_NC,
  INPUT_PIN_NC,
  INPUT_PIN_NC,
#endif
#if ((PIC32_PIN_COUNT != 100) && (PIC32_PIN_COUNT != 64))
  pinD7,
#else
  INPUT_PIN_NC,
#endif
  INPUT_PIN_NC,

  pinD9,
  pinG6,
  pinB8,
  pinB15,
  pinD4,
  pinB0,
  pinE3,
  pinB7,
  INPUT_PIN_NC,
#if (PIC32_PIN_COUNT != 64)
  pinF12,
  pinD12,
  pinF8,
  pinC3,
  pinE9,
#else
  INPUT_PIN_NC,
  INPUT_PIN_NC,
  INPUT_PIN_NC,
  INPUT_PIN_NC,
  INPUT_PIN_NC,

#endif
  INPUT_PIN_NC,
  INPUT_PIN_NC,

  pinD1,
  pinG9,
  pinB14,
  pinD0,
  INPUT_PIN_NC,
  pinB6,
  pinD5,
  pinB2,
  pinF3,
#if (PIC32_PIN_COUNT != 64)
  pinF13,
  INPUT_PIN_NC,
  pinF2,
  pinC2,
  pinE8,
#else
  INPUT_PIN_NC,
  INPUT_PIN_NC,
  INPUT_PIN_NC,
  INPUT_PIN_NC,
  INPUT_PIN_NC,
#endif
  INPUT_PIN_NC,
  INPUT_PIN_NC,
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

static inline pic32_gpio_port_t getportnumber(pic32_pin_t pin)
{
  pic32_gpio_port_t port = (pic32_gpio_port_t)(pin / (uint32_t)PIC32_MAX_PORT_PIN);

  assert(port < PIC32_PORT_MAX);

  return port;
}

static inline pic32_pin_t getpinnumber(pic32_pin_t pin, pic32_gpio_port_t port)
{
   pin = (pic32_pin_t)((uint32_t)pin - (port * (uint32_t)PIC32_MAX_PORT_PIN));
   
   assert(pin < PIC32_MAX_PORT_PIN);

   return pin;
}
int gpio_outfunc_map_set(int func_index, int value)
{
  is_regindex_valid(func_index);
  *output_map_register[func_index] = value;
  return OK;
}

void gpio_output_set(pic32_pin_t pin)
{
  pic32_gpio_port_t port = getportnumber(pin);

  pin = getpinnumber(pin, port);

  BIT_CLR(gpio_tris[port], pin);
}

void gpio_input_set(pic32_pin_t pin)
{
  pic32_gpio_port_t port = getportnumber(pin);

  pin = getpinnumber(pin, port);

  BIT_SET(gpio_tris[port], pin);
}

void gpio_state_write(pic32_pin_t pin, bool state)
{
  pic32_gpio_port_t port = getportnumber(pin);

  pin = getpinnumber(pin, port);

  if (state)
    {
      BIT_SET(gpio_lat[port], pin);
    }
  else
    {
      BIT_CLR(gpio_lat[port], pin);
    }
}

void gpio_state_set(pic32_pin_t pin)
{
  pic32_gpio_port_t port = getportnumber(pin);

  pin = getpinnumber(pin, port);

  BIT_SET(gpio_lat[port], pin);
}

void gpio_state_clear(pic32_pin_t pin)
{
  pic32_gpio_port_t port = getportnumber(pin);

  pin = getpinnumber(pin, port);

  BIT_CLR(gpio_lat[port], pin);
}

void gpio_state_toggle(pic32_pin_t pin)
{
  pic32_gpio_port_t port = getportnumber(pin);

  pin = getpinnumber(pin, port);

  BIT_INV(gpio_lat[port], pin);
}

bool gpio_state_get(pic32_pin_t pin)
{
  pic32_gpio_port_t port = getportnumber(pin);

  pin = getpinnumber(pin, port);

  return !((*gpio_port[port] & (1 << pin)) == 0);
}

bool gpio_isinput(pic32_pin_t pin)
{
  pic32_gpio_port_t port = getportnumber(pin);

  pin = getpinnumber(pin, port);

  return !((*gpio_tris[port] & (1 << pin)) == 0);
}

bool gpio_isoutput(pic32_pin_t pin)
{
  return !gpio_isinput(pin);
}

int gpio_map_getindex(pic32_pin_t pin)
{
  int i;

  for (i = 0; i < (int)GPIO_MAP_REG_MAX; i++)
    {
      if (pin == pin_map[i])
        {
          return i;
        }

    }
  return INPUT_PIN_NC;
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
