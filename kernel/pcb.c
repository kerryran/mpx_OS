#include <memory.h>
#include <string.h>
#include <../include/mpx/isr.h>
#include <../include/mpx/pcb.h>

// HEADS
pcb *ready_head = NULL;
pcb *suspended_ready_head = NULL;
pcb *blocked_head = NULL;
pcb *suspended_blocked_head = NULL;

// Allocate memory for a new PCB, including the stack and in
// and basic initialization
struct pcb *pcb_allocate(void)
{
    // need to check if this acctually allocates, if not return NULL
    pcb *some_pcb = sys_alloc_mem(sizeof(*some_pcb));

    if (some_pcb == NULL)
    {
        puts("Unable to allocate memory");
        return NULL;
    }

    return some_pcb;
}

// Free all memory associated with a PCB, including the stack
int pcb_free(struct pcb *pcb)
{

    int free_pcb = sys_free_mem(pcb);

    if (free_pcb == 0)
    {
        // successful free
        return 0;
    }
    else
    {
        // unsuccessful free
        return -1;
    }
}

// Allocate (via allocate_pcb()) a new PCB and initialize it with data provided, sets the state to Ready, Not-suspeneded
struct pcb *pcb_setup(const char *name, int class, int priority)
{
    pcb *new_pcb = pcb_allocate();

    int i;
    for (i = 0; i < 8 && name[i] != '\0'; i++)
    {
        new_pcb->name_arr[i] = name[i];
    }

    new_pcb->class = class;
    new_pcb->priority = priority;
    new_pcb->next = NULL;

    // Set states to READY and NOT_SUSPENDED
    new_pcb->execute = READY;
    new_pcb->dispatch = NOT_SUSPENDED;

    // Initialize context with appropriate values
    new_pcb->stack_ptr = (char *)(new_pcb->stack +1022) - sizeof(context);

    return new_pcb;
}


// Search all process queues for a process with the provided name (processes will not have the same name)
struct pcb *pcb_find(const char *name)
{
    struct pcb *current = NULL;

    // NOTSUSPENDED READY
    current = ready_head;
    while (current != NULL)
    {
        if (strcmp(current->name_arr, name) == 0)
        {
            // Found a pcb with the name
            return current;
        }
        current = current->next;
    }
    // SUSPENDED READY
    current = suspended_ready_head;
    while (current != NULL)
    {
        if (strcmp(current->name_arr, name) == 0)
        {
            // Found a pcb with the name
            return current;
        }
        current = current->next;
    }
    // NOTSUSPENDED BLOCKED
    current = blocked_head;
    while (current != NULL)
    {
        if (strcmp(current->name_arr, name) == 0)
        {
            // Found a pcb with the name
            return current;
        }
        current = current->next;
    }
    // SUSPENDED BLOCKED
    current = suspended_blocked_head;
    while (current != NULL)
    {
        if (strcmp(current->name_arr, name) == 0)
        {
            // Found a pcb with the name
            return current;
        }
        current = current->next;
    }

    // NAME WAS NOT FOUND
    return NULL;
}

// Insert a PCB into the appropriate queue based on state and priority
// Ready queues are sorted by priority (low to high), then FIFO
// Blocked queues are sorted by FIFO only
void pcb_insert(struct pcb *pcb)
{
    // Check execute and dispatch states to determine list to choose

    // NOTSUSPENDED READY
    if (pcb->dispatch == 3 && pcb->execute == 0)
    {
        // Case 1: Head is NULL and Case 2: pcb priority is lower than head
        if (ready_head == NULL || pcb->priority < ready_head->priority)
        {
            // Insert at beginning
            pcb->next = ready_head;
            ready_head = pcb;
        }
        // Case 3: pcb priority is higher than head
        else
        {
            // Traverse the list to find the proper position
            struct pcb *current = ready_head;

            while (current->next != NULL && current->next->priority <= pcb->priority)
            {
                current = current->next;
            }
            // Insert after current
            pcb->next = current->next;
            current->next = pcb;
        }
    }
    // SUSPENDED READY
    else if (pcb->dispatch == 4 && pcb->execute == 0)
    {
        // Case 1: Head is NULL and Case 2: pcb priority is lower than head
        if (suspended_ready_head == NULL || pcb->priority < suspended_ready_head->priority)
        {
            // Insert at beginning
            pcb->next = suspended_ready_head;
            suspended_ready_head = pcb;
        }
        // Case 3: pcb priority is higher than head
        else
        {
            // Traverse the list to find the proper position
            struct pcb *current = suspended_ready_head;

            while (current->next != NULL && current->next->priority <= pcb->priority)
            {
                current = current->next;
            }
            // Insert after current
            pcb->next = current->next;
            current->next = pcb;
        }
    }
    // NOTSUSPENDED BLOCKED
    else if (pcb->dispatch == 3 && pcb->execute == 1)
    {
        // Case 1: Head is NULL and Case 2: pcb priority is lower than head
        if (blocked_head == NULL || pcb->priority < blocked_head->priority)
        {
            // Case 1: Head is NULL
            if (blocked_head == NULL || pcb->priority < blocked_head->priority)
            {
                // The list is empty and this pcb is the head
                blocked_head = pcb;
            }
            // Case 2: Head is not NULL
            else
            {
                // Traverse to the end of the list
                struct pcb *current = blocked_head;
                while (current->next != NULL && current->next->priority <= pcb->priority && current->next->priority <= pcb->priority)
                {
                    current = current->next;
                }
                // Insert after current
                current->next = pcb;
            }
        }
    }
    // SUSPENDED BLOCKED
    else if (pcb->dispatch == 4 && pcb->execute == 1)
    {
        // Case 1: Head is NULL
        if (suspended_blocked_head == NULL || pcb->priority < suspended_blocked_head->priority || pcb->priority < suspended_blocked_head->priority)
        {
            // The list is empty and this pcb is the head
            suspended_blocked_head = pcb;
        }
        // Case 2: Head is not NULL
        else
        {
            // Traverse to the end of the list
            struct pcb *current = suspended_blocked_head;
            while (current->next != NULL && current->next->priority <= pcb->priority && current->next->priority <= pcb->priority)
            {
                current = current->next;
            }
            // Insert after current
            current->next = pcb;
        }
    }
}

// Remove a PCB from its current queue
// SUCCESS = 0
// NOT FOUND = 1
// EMPTY LIST = 2
int pcb_remove(struct pcb *pcb)
{
    // Check execute and dispatch states to determine list to choose

    // NOTSUSPENDED READY
    if (pcb->dispatch == 3 && pcb->execute == 0)
    {
        // Case 1: Head is NULL
        if (ready_head == NULL)
        {
            // There is nothing in the list, how did we get here?
            return 2;
        }
        // Case 2: Head is not NULL
        else
        {
            // Traverse the list to find the PCB and it's previous node
            struct pcb *current = ready_head;
            struct pcb *prev = NULL;

            while (current != NULL && strcmp(current->name_arr, pcb->name_arr)!= 0)
            {
                prev = current;
                current = current->next;
            }

            // If we found the PCB to remove
            if (current != NULL)
            {
                if (prev != NULL)
                {
                    // The PCB is not the head
                    prev->next = current->next;
                    return 0;
                }
                else
                {
                    // The PCB is the head
                    ready_head = current->next;
                    return 0;
                }
            }
        }
    }
    // SUSPENDED READY
    else if (pcb->dispatch == 4 && pcb->execute == 0)
    {
        // Case 1: Head is NULL
        if (suspended_ready_head == NULL)
        {
            // There is nothing in the list, how did we get here?
            return 2;
        }
        // Case 2: Head is not NULL
        else
        {
            // Traverse the list to find the PCB and it's previous node
            struct pcb *current = suspended_ready_head;
            struct pcb *prev = NULL;

            while (current != NULL && strcmp(current->name_arr, pcb->name_arr))
            {
                prev = current;
                current = current->next;
            }

            // If we found the PCB to remove
            if (current != NULL)
            {
                if (prev != NULL)
                {
                    // The PCB is not the head
                    prev->next = current->next;
                    return 0;
                }
                else
                {
                    // The PCB is the head
                    suspended_ready_head = current->next;
                    return 0;
                }
            }
        }
    }
    // NOTSUSPENDED BLOCKED
    else if (pcb->dispatch == 3 && pcb->execute == 1)
    {
        // Case 1: Head is NULL
        if (blocked_head == NULL)
        {
            // There is nothing in the list, how did we get here?
            return 2;
        }
        // Case 2: Head is not NULL
        else
        {
            // Traverse the list to find the PCB and it's previous node
            struct pcb *current = blocked_head;
            struct pcb *prev = NULL;

            while (current != NULL && strcmp(current->name_arr, pcb->name_arr))
            {
                prev = current;
                current = current->next;
            }

            // If we found the PCB to remove
            if (current != NULL)
            {
                if (prev != NULL)
                {
                    // The PCB is not the head
                    prev->next = current->next;
                    return 0;
                }
                else
                {
                    // The PCB is the head
                    blocked_head = current->next;
                    return 0;
                }
            }
        }
    }
    // SUSPENDED BLOCKED
    else if (pcb->dispatch == 4 && pcb->execute == 1)
    {
        // Case 1: Head is NULL
        if (suspended_blocked_head == NULL)
        {
            // There is nothing in the list, how did we get here?
            return 2;
        }
        // Case 2: Head is not NULL
        else
        {
            // Traverse the list to find the PCB and it's previous node
            struct pcb *current = suspended_blocked_head;
            struct pcb *prev = NULL;

            while (current != NULL && strcmp(current->name_arr, pcb->name_arr))
            {
                prev = current;
                current = current->next;
            }

            // If we found the PCB to remove
            if (current != NULL)
            {
                if (prev != NULL)
                {
                    // The PCB is not the head
                    prev->next = current->next;
                    return 0;
                }
                else
                {
                    // The PCB is the head
                    suspended_blocked_head = current->next;
                    return 0;
                }
                pcb->next = NULL;
            }
        }
    }
    // NOT FOUND
    return 1;
}
