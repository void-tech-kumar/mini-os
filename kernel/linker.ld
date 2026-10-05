ENTRY(kernel_main)

SECTIONS
{
    . = 0x1000;

    .text.start :
    {
        *(.text.start)
    }

    .text :
    {
        *(.text)
    }

    .rodata :
    {
        *(.rodata)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
}
