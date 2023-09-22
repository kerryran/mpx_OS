// idk what this is but we need it
extern struct pcb *queue_head;

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
