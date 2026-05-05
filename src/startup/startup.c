#include <stdint.h>

extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _stack_top;
extern uint32_t __data_load;

void reset_handler(void);
int  main(void);

static void default_handler(void) { for (;;) {} }

/* vector table -- placed first in flash at 0x00080000 */
__attribute__((section(".vectors"), used))
static void (*const vector_table[])(void) = {
    /* [0]  initial SP      */ (void (*)(void))&_stack_top,
    /* [1]  reset           */ reset_handler,
    /* [2]  NMI             */ default_handler,
    /* [3]  HardFault       */ default_handler,
    /* [4]  MemManage       */ default_handler,
    /* [5]  BusFault        */ default_handler,
    /* [6]  UsageFault      */ default_handler,
    /* [7..10] reserved     */ 0, 0, 0, 0,
    /* [11] SVCall          */ default_handler,
    /* [12] DebugMonitor    */ default_handler,
    /* [13] reserved        */ 0,
    /* [14] PendSV          */ default_handler,
    /* [15] SysTick         */ default_handler,
    /* [16+] peripheral IRQs */
};

void reset_handler(void)
{
    uint32_t *src;
    uint32_t *dst;

    /* copy .data from flash to SRAM */
    src = &__data_load;
    dst = &_data_start;
    while (dst < &_data_end) {
        *dst++ = *src++;
    }

    /* zero .bss */
    dst = &_bss_start;
    while (dst < &_bss_end) {
        *dst++ = 0;
    }

    main();

    for (;;) {}
}
