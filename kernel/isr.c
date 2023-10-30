#include <../include/mpx/pcb.h>
#include <../include/mpx/isr.h>
#include <../include/sys_req.h>
#include <../include/string.h>
#include <stddef.h>

// Global PCB pointer representing the currently executing process
pcb *current = NULL;

// The temporary next process pointer
pcb *next = NULL;

// Context from when sys_call is first called
context *first_context = NULL;

struct context *sys_call(struct context *cont)
{
    // Get the head of the ready queue
    pcb * ready = ready_head;

    // Handle system call based on the operation code

    // IDLE or EXIT
    if( cont->EAX == IDLE || cont->EAX == EXIT){
        //Save the first context
        if( first_context == NULL){
            first_context = cont;
        }

        //IDLE
        if (cont->EAX == IDLE) {
            //If the ready head is null, return context
            if (ready == NULL){
                return cont;
            }

            // Remove the ready head and set it to ready suspended
            next = ready;
            next->execute = 0;
            next->dispatch = 4;

            pcb_remove(ready);

            //If there is a currently executing process
            if(current != NULL){
                //Ready, Suspend and save the context
                current->execute = 0;
                current->dispatch = 4;
                current->stack_ptr = (char*) cont;
                pcb_insert(current);
            }

            current = next;
            return (context *)next->stack_ptr;
        }
        //EXIT
        else {
            pcb_free(current);

            if( ready == NULL){
                return first_context;
            }

            pcb_remove(current);

            next = ready;
            next->execute = 0;
            next->dispatch = 4;

            return (context *) next->stack_ptr;
        }
    }
    //Unrecognized op code
    else {
        cont->EAX = -1;
        return cont;
    }
}
