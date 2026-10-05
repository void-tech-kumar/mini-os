#include "scheduler.h"
#include "../process/process.h"

void scheduler_init(void)
{
    /* Scheduler initialization */
}

int scheduler_next(void)
{
    int next_pid = process_get_next_ready();

    if (next_pid > 0)
    {
        process_set_running(next_pid);
    }

    return next_pid;
}
