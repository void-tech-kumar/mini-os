#include <stdint.h>

void kernel_main(void)
{
    volatile uint16_t *video_memory = (uint16_t *)0xB8000;

    const char *message = "MiniOS Kernel Started!";

    for (int i = 0; message[i] != '\0'; i++)
    {
        video_memory[i] = (uint16_t)message[i] | (uint16_t)0x0F00;
    }

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
