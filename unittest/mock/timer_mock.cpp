#include "CppUTestExt/MockSupport.h"
#include "timer.h"

void timer_1_init(void)
{
  mock("timer").actualCall("timer_1_init");
}

int timer_init(int timer_id,
               int_callback_ft intcb)
{
  return mock("timer")
          .actualCall("timer_init")
          .withParameter("timer_id", (int)timer_id)
          .withParameter("intcb", (void(*)())intcb)
          .returnIntValue();
}



int timer_start(int timer_id)
{
  return mock("timer")
        .actualCall("timer_start")
        .withParameter("timer_id", (int)timer_id)
        .returnIntValue();
}

int timer_start_oneshot(int timer_id)
{
  return mock("timer")
        .actualCall("timer_start_oneshot")
        .withParameter("timer_id", (int)timer_id)
        .returnIntValue();
}

int timer_stop(int timer_id)
{
  return mock("timer")
        .actualCall("timer_stop")
        .withParameter("timer_id", (int)timer_id)
        .returnIntValue();
}

int timer_setperiod_ms(int timer_id, uint32_t prd_ms)
{
  return mock("timer")
        .actualCall("timer_setperiod_ms")
        .withParameter("timer_id", (int)timer_id)
        .withParameter("prd_ms", (int)prd_ms)
        .returnIntValue();
}
