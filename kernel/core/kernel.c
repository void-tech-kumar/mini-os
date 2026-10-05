#include <stdint.h>
#include "../process/process.h"

static volatile uint16_t *video_memory = (uint16_t *)0xB8000;

static void print_string(const char *str, int row)
{
    int i = 0;

    while (str[i] != '\0')
    {
        video_memory[row * 80 + i] =
            (uint16_t)str[i] | 0x0F00;
        i++;
    }
}

void kernel_main(void) __attribute__((section(".text.start")));

void kernel_main(void)
{
    process_init();

    int pid = process_create(1);

    print_string("MiniOS Kernel Started!", 0);
    print_string("Process Management Started", 2);

    if (pid > 0)
    {
        print_string("Process Created: PID 1", 4);
        print_string("Process State: READY", 5);
    }

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
