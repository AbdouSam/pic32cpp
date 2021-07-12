#ifndef INCLUDED_PIC32_TIMER_H
#define INCLUDED_PIC32_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "interrupt.h"

void timer_1_init(void);

int timer_init(int timer_id,
               int_callback_ft intcb);

int timer_start(int timer_id);
int timer_start_oneshot(int timer_id);
int timer_stop(int timer_id);
int timer_setperiod_ms(int timer_id, uint32_t prd_ms);


#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_PIC32_TIMER_H */
