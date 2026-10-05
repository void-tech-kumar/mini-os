#include "process.h"

static PCB process_table[MAX_PROCESSES];
static int next_pid = 1;

void process_init(void)
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        process_table[i].pid = -1;
        process_table[i].state = PROCESS_TERMINATED;
        process_table[i].priority = 0;
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

int process_get_next_ready(void)
{
    int selected_pid = -1;
    int highest_priority = -1;

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (process_table[i].pid != -1 &&
            process_table[i].state == PROCESS_READY)
        {
            if (process_table[i].priority > highest_priority)
            {
                highest_priority = process_table[i].priority;
                selected_pid = process_table[i].pid;
            }
        }
    }

    return selected_pid;
}

void process_set_running(int pid)
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (process_table[i].pid == pid)
        {
            process_table[i].state = PROCESS_RUNNING;
            return;
        }
    }
}

process_state_t process_get_state(int pid)
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (process_table[i].pid == pid)
        {
  
          return process_table[i].state;
        }
    }

    return PROCESS_TERMINATED;
}
