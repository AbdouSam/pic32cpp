#include "gpio_cpp.h"
#include "wdt.h"
#include "delay.h"
#include "board.h"

using namespace pic32plus;

Gpio red_led(GPIO::LED_RED, GPIO::OUTPUT);
Gpio green_led(GPIO::LED_GREEN, GPIO::OUTPUT);

void app_init()
{
  red_led.clear();
  green_led.clear();
}

void app_task()
{
  red_led.toggle();

  delay_ms(1000);

  green_led.toggle();

  wdt_clear();
}