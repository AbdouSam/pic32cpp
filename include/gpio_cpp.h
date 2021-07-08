#ifndef GPIO_CPP_H
#define GPIO_CPP_H

#include "gpio.h"

namespace pic32plus
{
  namespace GPIO
  {
    enum pin_t
    {
    #if (PIC32_PIN_COUNT != 64)
      pinA0     = PIC32_BASE_PORTA + 0,
      pinA1     = PIC32_BASE_PORTA + 1,
      pinA2     = PIC32_BASE_PORTA + 2,
      pinA3     = PIC32_BASE_PORTA + 3,
      pinA4     = PIC32_BASE_PORTA + 4,
      pinA5     = PIC32_BASE_PORTA + 5,
      pinA6     = PIC32_BASE_PORTA + 6,
      pinA7     = PIC32_BASE_PORTA + 7,
      pinA9     = PIC32_BASE_PORTA + 9,
      pinA10    = PIC32_BASE_PORTA + 10,
      pinA14    = PIC32_BASE_PORTA + 14,
      pinA15    = PIC32_BASE_PORTA + 15,
    #endif

      pinB0     = PIC32_BASE_PORTB + 0,
      pinB1     = PIC32_BASE_PORTB + 1,
      pinB2     = PIC32_BASE_PORTB + 2,
      pinB3     = PIC32_BASE_PORTB + 3,
      pinB4     = PIC32_BASE_PORTB + 4,
      pinB5     = PIC32_BASE_PORTB + 5,
      pinB6     = PIC32_BASE_PORTB + 6,
      pinB7     = PIC32_BASE_PORTB + 7,
      pinB8     = PIC32_BASE_PORTB + 8,
      pinB9     = PIC32_BASE_PORTB + 9,
      pinB10    = PIC32_BASE_PORTB + 10,
      pinB11    = PIC32_BASE_PORTB + 11,
      pinB12    = PIC32_BASE_PORTB + 12,
      pinB13    = PIC32_BASE_PORTB + 13,
      pinB14    = PIC32_BASE_PORTB + 14,
      pinB15    = PIC32_BASE_PORTB + 15,

    #if (PIC32_PIN_COUNT != 64)
      pinC1     = PIC32_BASE_PORTC + 1,
      pinC2     = PIC32_BASE_PORTC + 2,
      pinC3     = PIC32_BASE_PORTC + 3,
      pinC4     = PIC32_BASE_PORTC + 4,
    #endif
      pinC12    = PIC32_BASE_PORTC + 12,
      pinC13    = PIC32_BASE_PORTC + 13,
      pinC14    = PIC32_BASE_PORTC + 14,
      pinC15    = PIC32_BASE_PORTC + 15,

      pinD0     = PIC32_BASE_PORTD + 0,
      pinD1     = PIC32_BASE_PORTD + 1,
      pinD2     = PIC32_BASE_PORTD + 2,
      pinD3     = PIC32_BASE_PORTD + 3,
      pinD4     = PIC32_BASE_PORTD + 4,
      pinD5     = PIC32_BASE_PORTD + 5,
    #if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
      pinD6     = PIC32_BASE_PORTD + 6,
      pinD7     = PIC32_BASE_PORTD + 7,
    #endif
      pinD9     = PIC32_BASE_PORTD + 9,
      pinD10    = PIC32_BASE_PORTD + 10,
      pinD11    = PIC32_BASE_PORTD + 11,
    #if (PIC32_PIN_COUNT != 64)
      pinD12    = PIC32_BASE_PORTD + 12,
      pinD13    = PIC32_BASE_PORTD + 13,
      pinD14    = PIC32_BASE_PORTD + 14,
      pinD15    = PIC32_BASE_PORTD + 15,
    #endif

      pinE0 = PIC32_BASE_PORTE + 0,
      pinE1 = PIC32_BASE_PORTE + 1,
      pinE2 = PIC32_BASE_PORTE + 2,
      pinE3 = PIC32_BASE_PORTE + 3,
      pinE4 = PIC32_BASE_PORTE + 4,
      pinE5 = PIC32_BASE_PORTE + 5,
      pinE6 = PIC32_BASE_PORTE + 6,
      pinE7 = PIC32_BASE_PORTE + 7,
    #if (PIC32_PIN_COUNT != 64)
      pinE8 = PIC32_BASE_PORTE + 8,
      pinE9 = PIC32_BASE_PORTE + 9,
    #endif

      pinF0     = PIC32_BASE_PORTF + 0,
      pinF1     = PIC32_BASE_PORTF + 1,
    #if (PIC32_PIN_COUNT != 64)
      pinF2     = PIC32_BASE_PORTF + 2,
    #endif
      pinF3     = PIC32_BASE_PORTF + 3,
      pinF4     = PIC32_BASE_PORTF + 4,
      pinF5     = PIC32_BASE_PORTF + 5,
      pinF8     = PIC32_BASE_PORTF + 8,
    #if (PIC32_PIN_COUNT != 64)
      pinF12    = PIC32_BASE_PORTF + 12,
      pinF13    = PIC32_BASE_PORTF + 13,
    #endif

    #if (PIC32_PIN_COUNT != 64)
      pinG0     = PIC32_BASE_PORTG + 0,
      pinG1     = PIC32_BASE_PORTG + 1,
    #endif
      pinG6     = PIC32_BASE_PORTG + 6,
      pinG7     = PIC32_BASE_PORTG + 7,
      pinG8     = PIC32_BASE_PORTG + 8,
      pinG9     = PIC32_BASE_PORTG + 9,
    #if (PIC32_PIN_COUNT != 64)
      pinG12    = PIC32_BASE_PORTG + 12,
      pinG13    = PIC32_BASE_PORTG + 13,
      pinG14    = PIC32_BASE_PORTG + 14,
      pinG15    = PIC32_BASE_PORTG + 15,
    #endif

    #if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
      pinH0     = PIC32_BASE_PORTH + 0,
      pinH1     = PIC32_BASE_PORTH + 1,
    #if (PIC32_PIN_COUNT != 124)
      pinH2     = PIC32_BASE_PORTH + 2,
      pinH3     = PIC32_BASE_PORTH + 3,
    #endif
      pinH4     = PIC32_BASE_PORTH + 4,
      pinH5     = PIC32_BASE_PORTH + 5,
      pinH6     = PIC32_BASE_PORTH + 6,
    #if (PIC32_PIN_COUNT != 124)
      pinH7     = PIC32_BASE_PORTH + 7,
    #endif
      pinH8     = PIC32_BASE_PORTH + 8,
      pinH9     = PIC32_BASE_PORTH + 9,
      pinH10    = PIC32_BASE_PORTH + 10,
    #if (PIC32_PIN_COUNT != 124)
      pinH11    = PIC32_BASE_PORTH + 11,
    #endif
      pinH12    = PIC32_BASE_PORTH + 12,
      pinH13    = PIC32_BASE_PORTH + 13,
    #if (PIC32_PIN_COUNT != 124)
      pinH14    = PIC32_BASE_PORTH + 14,
      pinH15    = PIC32_BASE_PORTH + 15,
    #endif

      pinJ0     = PIC32_BASE_PORTJ + 0,
      pinJ1     = PIC32_BASE_PORTJ + 1,
      pinJ2     = PIC32_BASE_PORTJ + 2,
    #if (PIC32_PIN_COUNT != 124)
      pinJ3     = PIC32_BASE_PORTJ + 3,
    #endif
      pinJ4     = PIC32_BASE_PORTJ + 4,
    #if (PIC32_PIN_COUNT != 124)
      pinJ5     = PIC32_BASE_PORTJ + 5,
      pinJ6     = PIC32_BASE_PORTJ + 6,
      pinJ7     = PIC32_BASE_PORTJ + 7,
    #endif
      pinJ8     = PIC32_BASE_PORTJ + 8,
      pinJ9     = PIC32_BASE_PORTJ + 9,
    #if (PIC32_PIN_COUNT != 124)
      pinJ10    = PIC32_BASE_PORTJ + 10,
    #endif
      pinJ11    = PIC32_BASE_PORTJ + 11,
    #if (PIC32_PIN_COUNT != 124)
      pinJ12    = PIC32_BASE_PORTJ + 12,
      pinJ13    = PIC32_BASE_PORTJ + 13,
      pinJ14    = PIC32_BASE_PORTJ + 14,
      pinJ15    = PIC32_BASE_PORTJ + 15,
    #endif
    #if (PIC32_PIN_COUNT != 124)
      pinK0 = PIC32_BASE_PORTK + 0,
      pinK1 = PIC32_BASE_PORTK + 1,
      pinK2 = PIC32_BASE_PORTK + 2,
      pinK3 = PIC32_BASE_PORTK + 3,
      pinK4 = PIC32_BASE_PORTK + 4,
      pinK5 = PIC32_BASE_PORTK + 5,
      pinK6 = PIC32_BASE_PORTK + 6,
      pinK7 = PIC32_BASE_PORTK + 7,
    #endif  /* 124 */
    #endif  /* 64 && 100 */
    };

    static const uint8_t pps_pin_map[] = {
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

    enum port_t
    {
    #if (PIC32_PIN_COUNT != 64)
      PORTA,
    #endif
      PORTB,
      PORTC,
      PORTD,
      PORTE,
      PORTF,
      PORTG,
    #if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))
      PORTH,
      PORTJ,
    #endif
    #if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100) && \
      (PIC32_PIN_COUNT != 124))
      PORTK,
    #endif
      PORT_MAX,
    };
    
    enum pmode_t
    {
      OUTPUT,
      OD_OUTPUT,
      INPUT,
      ANALOG,
    };
  }
}
namespace pic32plus
{
  class Gpio
  {
  public:

    Gpio();
    Gpio(GPIO::pin_t pin, GPIO::pmode_t pmode);
    ~Gpio();

    void set();
    void clear();
    bool read();

    inline static int gpio_map_getindex(GPIO::pin_t pin)
    {
      for (int i = 0; i < (int)GPIO_MAP_REG_MAX; i++)
        {
          if (pin == GPIO::pps_pin_map[i])
            {
              return i;
            }
        }
      return INPUT_PIN_NC;
    }
  private:
    uint8_t d_pin;
    GPIO::port_t d_port;
    GPIO::pmode_t d_pmode;    
    bool d_state;

  private:
    inline void get_port_pin(GPIO::port_t& port, GPIO::pin_t& pin)
    {
      port = (GPIO::port_t)(pin / (unsigned)PIC32_MAX_PORT_PIN);

      //assert(port < GPIO::PORT_MAX);

      pin = (GPIO::pin_t)((unsigned)pin - (port * (unsigned)PIC32_MAX_PORT_PIN));
     
      //assert(pin < (unsigned)PIC32_MAX_PORT_PIN);
    }

  };
}

#endif /* GPIO_CPP_H */