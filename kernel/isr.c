#include <../include/mpx/pcb.h>
#include <../include/mpx/isr.h>
#include <../include/sys_req.h>
#include <stddef.h>

pcb *pcb_exec = NULL;
context *first_cont = NULL;

pcb *next = NULL;

struct context *sys_call(struct context *cont)
{
    // Get the operation code from EAX
    op_code operation_code = (op_code)cont->EAX;

    // Declare a context pointer to be returned
    pcb *next = NULL;
    pcb *ready = ready_head

    // Handle system call based on the operation code
    switch (operation_code)
    {
        case EXIT:
           if (first_cont == NULL)
    {
        first_cont = cont;
    }
            if (next_context == NULL) {
                next_context = first_cont;
            }

            pcb_free(ready);
            
            cont->EAX = 0;
            break;

        case IDLE:
           if (first_cont == NULL)
             {
             first_cont = cont;
             }
            // Handle IDLE case
            if (ready == NULL){
                return cont;
            }

            next = ready;
            next->execute = 0;
            next->dispatch = 4;
            pcb_remove(ready);

            if (ready != NULL) {
                ready->execute = 0;
                ready->dispatch = 4;
                //ready-.stackptr = cont;
                pcb_insert(ready)
            }
            ready = next;
            //return next->stackpr;



            cont->EAX = 0;
            break;

        default:
            // Set the return value to -1 for unknown operation codes
            cont->EAX = -1;
            return cont;
    }

    // Return context pointer
    return next_context;
}
