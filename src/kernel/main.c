#include <stdint.h>
#include "sam3x8e.h"

void SystemInit(void) {}

uint32_t SystemCoreClock = 4000000UL;   /* 4 MHz RC oscillator at power-on */

int main(void)
{
    /* TODO: clock setup -- switch from 4 MHz RC to 84 MHz PLLA */

    /* TODO: peripheral init */

    /* TODO: interrupt setup */

    for (;;) {}

    return 0;
}
