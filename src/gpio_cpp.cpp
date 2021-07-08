#include "gpio_cpp.h"
#include "gpio.h"

namespace pic32plus
{
  namespace GPIO
  {
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
  }
}

namespace pic32plus
{
  Gpio::Gpio(GPIO::pin_t pin, GPIO::pmode_t pmode)
  :d_pmode(pmode), d_state(false)
  {
    GPIO::port_t port;
    get_port_pin(port, pin);
   
    d_port = port;
    d_pin = (uint8_t)pin;

    switch (pmode)
    {
      case GPIO::OUTPUT:
      {
        gpio_output_set(port, pin);
        gpio_open_drain_clear(port, pin);
        break;
      }
      case GPIO::OD_OUTPUT:
      {
        gpio_output_set(port, pin);
        gpio_open_drain_set(port, pin);
        break;
      }
      case GPIO::INPUT:
      {
        gpio_input_set(port, pin);
        break;
      }
      case GPIO::ANALOG:
      {
        break;
      }
      default:
      {
        // Error
      }
    }
  }

  Gpio::~Gpio()
  {
  }

  void Gpio::set()
  {
    gpio_state_set(d_port, d_pin);
    d_state = true;
  }

  void Gpio::clear()
  {
    gpio_state_clear(d_port, d_pin);
    d_state = false;
  }

  void Gpio::toggle()
  {
    gpio_state_toggle(d_port, d_pin);
    d_state = !false;
  }

  bool Gpio::read()
  {
    gpio_state_get(d_port, d_pin);
    return d_state;
  }

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


} /* namespace pic32plus */