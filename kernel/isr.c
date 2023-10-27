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

struct context *sys_call(struct context *context)
{
    // Get the operation code from EAX
    op_code operation_code = (op_code)context->EAX;

    // Get the head of the ready queue
    current = ready_head;

    // Handle system call based on the operation code
    switch (operation_code)
    {
    // If operation code is EXIT, terminate the process
    case EXIT:
        // Check if this is the first time sys_call has been called
        if (first_context == NULL)
        {
            // Save the context
            first_context = context;
        }

        // If there are no ready, unsuspended processes, return the original context
        if (ready_head == NULL)
        {
            first_context->EAX = 0;
            return first_context;
        }

        // Free the currently running process
        pcb_free(current);

        // Remove the current process from the ready queue
        pcb_remove(current);

        // If the ready_head is not NULL, load the first (in the queue?) as implemented in IDLE

        // Remove the first process from the ready queue and store it in a tmp var as the next process
        pcb_remove(current);
        next = current;

        // Save the content of the current process by updating its stack pointer
        // Question: What is the stack pointer? How is that implemented? What are we updating about it?

        // Add the current process back to the queue
        pcb_insert(current);

        // Return a pointer to the context of the next process
        next->pcb_context->EAX = 0;
        return next->pcb_context;

    // If operation code is IDLE, perform a context switch
    case IDLE:
        // Check if this is the first time sys_call has been called
        if (first_context == NULL)
        {
            // Save the context
            first_context = context;
        }

        // If the ready, non-suspended queue is empty continue with the current process
        if (ready_head == NULL)
        {
            context->EAX = 0;
            return context;
        }

        // Remove the first process from the ready queue and store it in a tmp var as the next process
        pcb_remove(current);
        next = current;

        // Save the content of the current process by updating its stack pointer
        // Question: What is the stack pointer? How is that implemented? What are we updating about it?

        // Add the current process back to the queue
        pcb_insert(current);

        // Return the context of the next process
        next->pcb_context->EAX = 0;
        return next->pcb_context;

    // If the operation code is anything else
    default:
        // Set the return value to -1
        context->EAX = -1;
        
        return context;
    }
}

