#ifndef INCLUDED_PIC32_GPIO_H
#define INCLUDED_PIC32_GPIO_H

#include <stdint.h>
#include <stdbool.h>

#define PIC32_MAX_PORT_PIN  (16U)
#define GPIO_MAP_REG_MAX    (PIC32_MAX_PORT_PIN * 4U)
#define INPUT_PIN_NC        (0xFFU)

enum
{
#if (PIC32_PIN_COUNT != 64)
  PIC32_PORTA,
#endif
  PIC32_PORTB,
  PIC32_PORTC,
  PIC32_PORTD,
  PIC32_PORTE,
  PIC32_PORTF,
  PIC32_PORTG,
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
  PIC32_PORTH,
  PIC32_PORTJ,
#endif
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100) && \
  (PIC32_PIN_COUNT != 124))
  PIC32_PORTK,
#endif
  PIC32_PORT_MAX,
};

enum
{
#if (PIC32_PIN_COUNT != 64)
  PIC32_BASE_PORTA  = PIC32_PORTA * PIC32_MAX_PORT_PIN,
#endif
  PIC32_BASE_PORTB  = PIC32_PORTB * PIC32_MAX_PORT_PIN,
  PIC32_BASE_PORTC  = PIC32_PORTC * PIC32_MAX_PORT_PIN,
  PIC32_BASE_PORTD  = PIC32_PORTD * PIC32_MAX_PORT_PIN,
  PIC32_BASE_PORTE  = PIC32_PORTE * PIC32_MAX_PORT_PIN,
  PIC32_BASE_PORTF  = PIC32_PORTF * PIC32_MAX_PORT_PIN,
  PIC32_BASE_PORTG  = PIC32_PORTG * PIC32_MAX_PORT_PIN,
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
  PIC32_BASE_PORTH  = PIC32_PORTH * PIC32_MAX_PORT_PIN,
  PIC32_BASE_PORTJ  = PIC32_PORTJ * PIC32_MAX_PORT_PIN,
#endif
#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100) && \
  (PIC32_PIN_COUNT != 124))
  PIC32_BASE_PORTK = PIC32_PORTK * PIC32_MAX_PORT_PIN,
#endif
};


#ifdef __cplusplus
extern "C" {
#endif

void gpio_init(void);

bool gpio_state_get(uint8_t port, uint16_t nbr);

void gpio_state_write(uint8_t port, uint16_t nbr, bool state);

void gpio_state_set(uint8_t port, uint16_t nbr);

void gpio_state_clear(uint8_t port, uint16_t nbr);

void gpio_state_toggle(uint8_t port, uint16_t nbr);

void gpio_input_set(uint8_t port, uint16_t nbr);

void gpio_output_set(uint8_t port, uint16_t nbr);

void gpio_open_drain_set(uint8_t port, uint16_t pin);

void gpio_open_drain_clear(uint8_t port, uint16_t pin);

bool gpio_isinput(uint8_t port, uint16_t pin);

bool gpio_isoutput(uint8_t port, uint16_t pin);

int gpio_outfunc_map_set(int func_index, int value);





#ifdef __cplusplus
}
#endif


#endif /* INCLUDED_PIC32_GPIO_H */