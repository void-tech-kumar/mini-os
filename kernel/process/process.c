#include "process.h"

static PCB process_table[MAX_PROCESSES];
static int next_pid = 1;

void process_init(void)
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        process_table[i].pid = -1;
        process_table[i].state = PROCESS_TERMINATED;
    }
}

int process_create(int priority)
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (process_table[i].pid == -1)
        {
            process_table[i].pid = next_pid++;
            process_table[i].state = PROCESS_READY;
            process_table[i].program_counter = 0;
            process_table[i].stack_pointer = 0;
            process_table[i].priority = priority;

            return process_table[i].pid;
        }
    }

    return -1;
}

void process_terminate(int pid)
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (process_table[i].pid == pid)
        {
            process_table[i].state = PROCESS_TERMINATED;
            process_table[i].pid = -1;
            return;
        }
    }
}
