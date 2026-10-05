#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESSES 16

typedef enum {
    PROCESS_NEW,
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_WAITING,
    PROCESS_TERMINATED
} process_state_t;

typedef struct {
    int pid;
    process_state_t state;

    unsigned int program_counter;
    unsigned int stack_pointer;

    unsigned int registers[8];

    int priority;
} PCB;

void process_init(void);
int process_create(int priority);
void process_terminate(int pid);

int process_get_next_ready(void);
void process_set_running(int pid);
process_state_t process_get_state(int pid);

#endif
