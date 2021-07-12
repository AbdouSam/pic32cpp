#ifndef TIMER_CPP_H
#define TIMER_CPP_H

#include "timer.h"

namespace pic32plus
{
  namespace TIMER
  {
    enum timer_t
    {
      TIMER_1 = 0,
      TIMER_2,
      TIMER_3,
      TIMER_4,
      TIMER_5,
      TIMER_6,
      TIMER_7,
      TIMER_8,
      TIMER_9,
    };
  }

}

namespace pic32plus
{
  template<typename T>
  class TimerHW
  {
  public:
    using  timer_cb_t = void (*)();
    inline TimerHW(TIMER::timer_t id, T cb)
    :t_id(id)
    {
      t_cb = (timer_cb_t)cb;
      timer_init((int)id, t_cb);
    }

    ~TimerHW()
    {

    }

    inline int start(uint32_t prd_ms)
    {
      if (timer_setperiod_ms(t_id, prd_ms) != 0)
        return -1;

      if (timer_start(t_id) != 0)
        return -1;

      return 0;
    }

    inline int start_oneshot(uint32_t prd_ms)
    {
      if (timer_setperiod_ms(t_id, prd_ms) != 0)
        return -1;

      if (timer_start_oneshot(t_id) != 0)
        return -1;

      return 0;
    }

    inline int stop()
    {
      return timer_stop(t_id);
    }

  private:
    TIMER::timer_t t_id;
    timer_cb_t t_cb;
  };
}
#endif /* TIMER_CPP_H */