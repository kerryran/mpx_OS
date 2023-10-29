#include <../include/mpx/pcb.h>
#include <../include/mpx/isr.h>
#include <../include/sys_req.h>
#include <stddef.h>

// Global PCB pointer representing the currently executing process
pcb *current = NULL;

// The temporary next process pointer
pcb *next = NULL;

// Context from when sys_call is first called
context *first_context = NULL;

struct context *sys_call(struct context *cont)
{
    // Get the operation code from EAX
    op_code operation_code = (op_code)cont->EAX;

    // Get the head of the ready queue as the next process
    next = ready_head;

    // Handle system call based on the operation code
    switch (operation_code)
    {
    // If operation code is EXIT, terminate the process
    case EXIT:
        // Check if this is the first time sys_call has been called
        if (first_context == NULL)
        {
            // Save the context
            first_context = cont;
        }

        // If there are no ready, unsuspended processes, return the original context
        if (ready_head == NULL)
        {
            first_context->EAX = 0;
            return first_context;
        }

        // Remove the next process from the ready queue
        pcb_remove(next);
        // Free the currently running process
        pcb_free(current);

        current = next;

        // Return a pointer to the context of the next process
        ((context *)next->stack_ptr)->EAX = 0;
        return (context *) next->stack_ptr;

    // If operation code is IDLE, perform a context switch
    case IDLE:
        // Check if this is the first time sys_call has been called
        if (first_context == NULL)
        {
            // Save the context
            first_context = cont;
        }

        // If the ready, non-suspended queue is empty continue with the current process
        if (ready_head == NULL)
        {
            cont->EAX = 0;
            return cont;
        }
        // If the there is a currently executing process
        if(current != NULL){
            current->stack_ptr = (char *) cont;
            current->execute = 0;
            current->dispatch = 4;
            pcb_insert(current);
            cont->EAX = 0;
        }
        current = ready_head;
        cont = (context *) current->stack_ptr;
        cont->EAX = 0;

        // Return the context of the next process
        return cont;

    // If the operation code is anything else
    default:
        // Set the return value to -1
        cont->EAX = -1;
        return cont;
    }
}
