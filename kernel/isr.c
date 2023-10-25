#include <../include/mpx/pcb.h>
#include <../include/mpx/isr.h>
#include <../include/sys_req.h>
#include <stddef.h>

pcb *pcb_exec = NULL;
pcb *next = NULL;
context *first_cont = NULL;

struct context *sys_call(struct context *cont)
{
    // Get the operation code from EAX
    op_code operation_code = (op_code)cont->EAX;

    // Declare a context pointer to be returned
    pcb *next = NULL;
    pcb *ready = ready_head;

    // Handle system call based on the operation code
    switch (operation_code)
    {
        // If context is EXIT
    case EXIT:
        // Check if this is the first time sys_call has been called
        if (first_cont == NULL)
        {
            // Save the context
            first_cont = cont;
        }

        pcb_free(ready);

        if (ready == NULL)
        {
            return cont;
        }

        pcb_remove(ready);
        next = ready;
        next->execute = 0;  // Ready
        next->dispatch = 4; // Suspended

        // return (context) stackptr;

        cont->EAX = 0;
        break; // Remove this when the return is implemented
    // If context is IDLE
    case IDLE:
        // Check if this is the first time sys_call has been called
        if (first_cont == NULL)
        {
            // Save the context
            first_cont = cont;
        }
        // Handle IDLE case
        if (ready == NULL)
        {
            return cont;
        }

        next = ready;
        next->execute = 0;  // Ready
        next->dispatch = 4; // Suspended
        pcb_remove(ready);

        if (ready != NULL)
        {
            ready->execute = 0;
            ready->dispatch = 4;
            // ready-.stackptr = cont;
            pcb_insert(ready);
        }
        ready = next;
        // return next->stackpr;
        break; // remove this when the return is implemented

    default:
        // Set the return value to -1 for unknown operation codes
        cont->EAX = -1;
        return cont;
    }
}
