#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <iostream>

#include "timer.h"
#include "timer_cpp.h"

using namespace pic32plus;

TimerHW<void(*)()> *t;
bool timer_flag;

namespace
{
  void timer_cb(void)
  {
    timer_flag = true;
  }
}

TEST_GROUP(timer_test)
{
  void setup()
  {   
      timer_flag = false;

      mock("timer")
        .expectOneCall("timer_init")
        .withParameter("timer_id", TIMER::TIMER_2)
        .withParameter("intcb", ::timer_cb);

      t = new TimerHW<void(*)()>(TIMER::TIMER_2, ::timer_cb);
  }

  void teardown()
  {
      mock("timer").checkExpectations();
      mock().clear();
      delete t;
  }
};


TEST(timer_test, start_timer)
{
  mock("timer")
    .expectOneCall("timer_setperiod_ms")
    .withParameter("timer_id", TIMER::TIMER_2)
    .withParameter("prd_ms", 1);

  mock("timer")
    .expectOneCall("timer_start")
    .withParameter("timer_id", TIMER::TIMER_2);

  int ret = t->start(1/* 1/ms */);
  CHECK_EQUAL(0, ret);

  /* mock interrupt */
  ::timer_cb();
  
  CHECK_EQUAL(true, timer_flag);
}

TEST(timer_test, start_timer_oneshot)
{
  mock("timer")
    .expectOneCall("timer_setperiod_ms")
    .withParameter("timer_id", TIMER::TIMER_2)
    .withParameter("prd_ms", 1);

  mock("timer")
    .expectOneCall("timer_start_oneshot")
    .withParameter("timer_id", TIMER::TIMER_2);

  int ret = t->start_oneshot(1/* 1/ms */);
  CHECK_EQUAL(0, ret);

  /* mock interrupt */
  ::timer_cb();
  
  CHECK_EQUAL(true, timer_flag);
}