#include "CppUTestExt/MockSupport.h"
#include "gpio.h"

bool gpio_state_get(uint8_t port, uint16_t pin)
{
  return mock("gpio")
          .actualCall("gpio_state_get")
          .withParameter("port", (int)port)
          .withParameter("pin", (int)pin)
          .returnIntValue();
}

void gpio_state_write(uint8_t port, uint16_t pin, bool state)
{
  mock("gpio")
    .actualCall("gpio_state_write")
    .withParameter("port", (int)port)
    .withParameter("pin", (int)pin);
}

void gpio_state_set(uint8_t port, uint16_t pin)
{
  mock("gpio")
    .actualCall("gpio_state_set")
    .withParameter("port", (int)port)
    .withParameter("pin", (int)pin);
}

void gpio_state_clear(uint8_t port, uint16_t pin)
{
  mock("gpio")
    .actualCall("gpio_state_clear")
    .withParameter("port", (int)port)
    .withParameter("pin", (int)pin);
}

void gpio_state_toggle(uint8_t port, uint16_t pin)
{
  mock("gpio")
    .actualCall("gpio_state_toggle")
    .withParameter("port", (int)port)
    .withParameter("pin", (int)pin);
}

void gpio_input_set(uint8_t port, uint16_t pin)
{
  mock("gpio")
    .actualCall("gpio_input_set")
    .withParameter("port", (int)port)
    .withParameter("pin", (int)pin);
}

void gpio_output_set(uint8_t port, uint16_t pin)
{
  mock("gpio")
    .actualCall("gpio_output_set")
    .withParameter("port", (int)port)
    .withParameter("pin", (int)pin);
}

void gpio_open_drain_set(uint8_t port, uint16_t pin)
{
  mock("gpio")
    .actualCall("gpio_open_drain_set")
    .withParameter("port", (int)port)
    .withParameter("pin", (int)pin);
}

void gpio_open_drain_clear(uint8_t port, uint16_t pin)
{
  mock("gpio")
    .actualCall("gpio_open_drain_clear")
    .withParameter("port", (int)port)
    .withParameter("pin", (int)pin);
}