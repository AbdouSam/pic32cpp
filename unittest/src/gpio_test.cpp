#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTestExt/MockSupport.h"

#include "gpio.h"
#include "gpio_cpp.h"

TEST_GROUP(gpio_test)
{
  void setup()
  {
  }

  void teardown()
  {
      mock("IO").checkExpectations();
      mock().clear();
  }
};

TEST(gpio_test, set_pinA0_then_read)
{
  using namespace pic32plus;

  mock("gpio")
    .expectOneCall("gpio_output_set")
    .withParameter("port",(int)GPIO::PORTA)
    .withParameter("pin", 0);

  mock("gpio")
    .expectOneCall("gpio_open_drain_clear")
    .withParameter("port",(int)GPIO::PORTA)
    .withParameter("pin", 0);

  Gpio pin(GPIO::pinA0, GPIO::OUTPUT);

  mock("gpio")
    .expectOneCall("gpio_state_set")
    .withParameter("port",(int)GPIO::PORTA)
    .withParameter("pin", 0);

  pin.set();

  mock("gpio")
    .expectOneCall("gpio_state_get")
    .withParameter("port",(int)GPIO::PORTA)
    .withParameter("pin", 0);

  CHECK_EQUAL(true, pin.read());
}

TEST(gpio_test, clear_pinA0_then_read)
{
  using namespace pic32plus;

  mock("gpio")
    .expectOneCall("gpio_output_set")
    .withParameter("port",(int)GPIO::PORTD)
    .withParameter("pin", 1);

  mock("gpio")
    .expectOneCall("gpio_open_drain_clear")
    .withParameter("port",(int)GPIO::PORTD)
    .withParameter("pin", 1);

  Gpio pin(GPIO::pinD1, GPIO::OUTPUT);

  mock("gpio")
    .expectOneCall("gpio_state_clear")
    .withParameter("port",(int)GPIO::PORTD)
    .withParameter("pin", 1);

  pin.clear();

  mock("gpio")
    .expectOneCall("gpio_state_get")
    .withParameter("port",(int)GPIO::PORTD)
    .withParameter("pin", 1);

  CHECK_EQUAL(false, pin.read());
}