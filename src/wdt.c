
#ifndef TEST
#include <xc.h>
#else
#include "xc_stub.h"
#endif

#include <stdint.h>

void wdt_clear(void)
{
  volatile uint16_t * wdtclrkey;
  asm volatile("di");
  /* get address of upper 16-bit word of the WDTCON SFR */
  wdtclrkey     = ( (volatile uint16_t *)&WDTCON ) + 1;
  *wdtclrkey    = 0x5743;
  asm volatile("ei");
}
