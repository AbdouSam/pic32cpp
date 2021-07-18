#include "board.h"
#include "gpio_cpp.h"
#include "wdt.h"
#include "delay.h"
#include "timer_cpp.h"
using namespace pic32plus;

namespace
{
  bool wdt_flag = false;
}

Gpio red_led(GPIO::LED_RED, GPIO::OUTPUT);
Gpio orange_led(GPIO::LED_ORANGE, GPIO::OUTPUT);
Gpio yellow_led(GPIO::LED_YELLOW, GPIO::OUTPUT);

TimerHW<void(*)()> blinktimer(TIMER::TIMER_2, 
  [](){
        yellow_led.toggle();
        red_led.toggle();
      });

TimerHW<void(*)()> orangetimer(TIMER::TIMER_3, 
  [](){
        orange_led.toggle();
      });


TimerHW<void(*)()> wdttimer(TIMER::TIMER_4, 
  [](){
        ::wdt_flag = true;
      });

void app_init()
{
  red_led.clear();
  yellow_led.clear();
  orange_led.set();
  
  blinktimer.start(500);
  wdttimer.start(500);
  orangetimer.start_oneshot(500);
}

void app_task()
{
  if (::wdt_flag)
  {
    ::wdt_flag = false;
    wdt_clear();
  }
}