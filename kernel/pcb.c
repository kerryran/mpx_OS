#include <memory.h>
#include <stdio.h>

// Number of characters a pcb name can be
int MAX_NAME_LEN = 8;

typedef enum class{
    SYSTEM = 0,
    USER = 1
}class;

typedef enum state{
    READY = 0,
    BLOCKED = 1,
    SUSPENDED_READY = 2,
    SUSPENDED_BLOCKED = 3
}state;

// The struct we need
typedef struct pcb
{
    char *name_ptr;
    char name_arr[MAX_NAME_LEN];
    int class;    // 0 for system, 1 for user
    int priority; // 0 = highest, 9 = lowest
    char stack[1024];
}pcb;

// idk what this is but we need it
pcb *queue_head;

// Allocate memory for a new PCB, including the stack and in
// and basic initialization
pcb *pcb_allocate(void)
{
    //need to check if this acctually allocates, if not return NULL
    struct pcb *some_pcb = sys_alloc_mem(sizeof(*some_pcb));

   some_pcb->name_ptr = sys_alloc_mem(some_pcb->name_ptr);

    if(some_pcb == NULL || some_pcb->name_ptr == NULL){
        puts("Unable to allocate memory");
        return NULL;
    }

    return *some_pcb;

}

// Free all memory associated with a PCB, including the stack
int pcb_free(struct pcb *pcb)
{
    int free =  sys_free_mem(pcb->name_ptr);

    int free_pcb = sys_free_mem(pcb);

    if(free == 0 && free_pcb == 0){
        //successful free
        return 0;
    }
    else{
        //unsuccessful free
        return -1;
    }
}

// Allocate (via allocate_pcb()) a new PCB and initialize it with data provided, sets the state to Ready, Not-suspeneded
struct pcb *pcb_setup(const char *name, int class, int priority)
{
    
    struct pcb *new_pcb = allocate_pcb();

    new_pcb->name_ptr = name;

    new_pcb->class = class;

    new_pcb->priority = priority; 

    //somehow set the state
    state = 0;
}

// Search all process queues for a process with the provided name
struct pcb *pcb_find(const char *name)
{
}

// Insert a PCB into the appropriate queue based on state and priority
void pcb_insert(struct pcb *pcb)
{
}

// Remove a PCB from its current queue but do not free any assocaited memoery or data structures
int pcb_remove(struct pcb *pcb)
{
}
