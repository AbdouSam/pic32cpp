#include "sysclk.h"

uint32_t sysclk_sysfreq_get(void)
{
  return SYS_FREQ;
}

uint32_t sysclk_timerfreq_get(void)
{
  return SYS_FREQ / (PERPHERAL3_CLK_DIV + 1);
}

uint32_t sysclk_uartfreq_get(void)
{
  return SYS_FREQ / (PERPHERAL2_CLK_DIV + 1);
}

void sysclk_init(void)
{
}