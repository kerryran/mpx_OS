#ifndef PCB_H
#define PCB_H

typedef enum classes
{
    SYSTEM = 0,
    USER = 1
} classes;

typedef enum state
{
    // Execute
    READY = 0,
    BLOCKED = 1,
    RUNNING = 2,
    // Dispatch
    NOT_SUSPENDED = 3,
    SUSPENDED = 4
} state;

// The struct we need
typedef struct pcb
{
    const char *name_ptr;
    char name_arr[8];
    enum classes class;
    state dispatch;
    state execute;
    int priority; // 0 = highest, 9 = lowest
    char stack[1024];
    struct pcb *next;

} pcb;

struct pcb *get_ready(void);

struct pcb *get_sus_ready(void);

struct pcb *get_blocked(void);

struct pcb *get_sus_blocked(void);

// Allocate memory for a new PCB, including the stack and in
// and basic initialization
struct pcb *pcb_allocate(void);

// Free all memory associated with a PCB, including the stack
int pcb_free(struct pcb *pcb);

// Allocate (via allocate_pcb()) a new PCB and initialize it with data provided, sets the state to Ready, Not-suspeneded
struct pcb *pcb_setup(const char *name, int class, int priority);

// Search all process queues for a process with the provided name
struct pcb *pcb_find(const char *name);

// Insert a PCB into the appropriate queue based on state and priority
void pcb_insert(struct pcb *pcb);

// Remove a PCB from its current queue but do not free any assocaited memoery or data structures
int pcb_remove(struct pcb *pcb);

#endif
