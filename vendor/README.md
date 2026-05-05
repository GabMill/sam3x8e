# sam3x8e/vendor — Third-party headers

This directory contains vendor-supplied headers that provide C-language access to the
AT91SAM3X8E's registers without hand-writing raw address constants.

## Layout

```
vendor/
├── cmsis/
│   └── include/          # ARM CMSIS core headers (architecture, not chip-specific)
│       ├── core_cm3.h    # Cortex-M3 core peripherals: SysTick, NVIC, SCB, ITM, DWT
│       ├── core_cmFunc.h # CMSIS intrinsic helper functions (__enable_irq, __WFI, etc.)
│       └── core_cmInstr.h# CMSIS Cortex-M instruction wrappers (CLZ, REV, RBIT, etc.)
└── sam/
    └── include/          # Atmel/Microchip SAM3X8E CMSIS device headers
        ├── sam3x8e.h     # Top-level chip header — #include this in your source
        ├── sam3xa.h      # SAM3X/3A family selector (chooses device variant)
        ├── system_sam3xa.h # SystemInit() and SystemCoreClock declarations
        ├── component/    # Peripheral register struct definitions (one per peripheral)
        ├── instance/     # Per-instance base addresses and IRQ numbers
        └── pio/          # GPIO pin name macros for each SAM3X/3A variant
```

## How to use

In any C source file, include the top-level device header:

```c
#include "sam3x8e.h"
```

The compiler is told to look here via the Makefile flags:

```makefile
-Ivendor/sam/include    # for "sam3x8e.h" and relatives
-Ivendor/cmsis/include  # for <core_cm3.h> (angle-bracket include)
-D__SAM3X8E__           # select the SAM3X8E device variant
```

After including it, every peripheral is accessible via struct pointers, e.g.:

```c
PMC->PMC_PCER0 = (1u << ID_PIOB);   // enable PIOB peripheral clock
PIOB->PIO_PER  = PIO_PB27;          // PIO enable on PB27
PIOB->PIO_OER  = PIO_PB27;          // set PB27 as output
PIOB->PIO_SODR = PIO_PB27;          // drive PB27 high (Arduino Due LED on)
```

## Source and licence

Headers sourced from the **ArduinoCore-sam** project:  
<https://github.com/arduino/ArduinoCore-sam>

- `cmsis/` headers: © ARM Limited, Apache License 2.0  
- `sam/` headers: © Atmel Corporation (now Microchip), BSD-style licence  
  (see the licence header at the top of each file)

These headers are redistributed as-is, unmodified.
