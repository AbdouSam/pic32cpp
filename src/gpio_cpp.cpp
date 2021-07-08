#include "gpio_cpp.h"
#include "gpio.h"

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

  bool Gpio::read()
  {
    gpio_state_get(d_port, d_pin);
    return d_state;
  }

} /* namespace pic32plus */