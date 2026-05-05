/* AT91SAM3X8E linker script */

ENTRY(reset_handler)

/* flash starts at 0x80000; boot ROM occupies 0x00000000-0x0007FFFF */
MEMORY
{
    flash  (rx)  : ORIGIN = 0x00080000, LENGTH = 512K
    sram0  (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
    sram1  (rwx) : ORIGIN = 0x20080000, LENGTH = 32K
}

SECTIONS
{
    .text :
    {
        KEEP(*(.vectors))   /* vector table first -- CPU reads it on reset */
        *(.text*)
        *(.rodata*)
    } > flash

    .data :
    {
        _data_start = .;
        *(.data*)
        _data_end = .;
    } > sram0 AT > flash    /* VMA in SRAM, LMA in flash; reset_handler copies it */

    __data_load = LOADADDR(.data);

    .bss :
    {
        _bss_start = .;
        *(.bss*)
        *(COMMON)
        _bss_end = .;
    } > sram0

    /* stack at top of SRAM0, grows downward */
    _stack_top = ORIGIN(sram0) + LENGTH(sram0);
}
