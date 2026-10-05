#include <stdint.h>
#include "../process/process.h"
#include "../scheduler/scheduler.h"

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
    scheduler_init();

    int pid1 = process_create(1);
    int pid2 = process_create(2);

    int selected_pid = scheduler_next();

    print_string("MiniOS Kernel Started!", 0);
    print_string("Process Management Started", 2);

    if (pid1 > 0)
    {
        print_string("Process Created: PID 1", 4);
    }

    if (pid2 > 0)
    {
        print_string("Process Created: PID 2", 5);
    }

    if (selected_pid == pid2)
    {
        print_string("Scheduler Selected: PID 2", 7);
        print_string("Process State: RUNNING", 8);
    }

    while (1)
    {
        __asm__ volatile ("hlt");
    }
}
