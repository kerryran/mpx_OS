#include <../include/mpx/pcb.h>
#include <../include/mpx/isr.h>
#include <../include/sys_req.h>
#include <../include/string.h>
#include <stddef.h>

// Global PCB pointer representing the currently executing process
pcb *current = NULL;

// The temporary next process pointer

// Context from when sys_call is first called
context *first_context = NULL;

struct context *sys_call(struct context *cont)
{
    // Get the head of the ready queue
    pcb * ready = ready_head;
    //Need to get the first object in the ready_head linked list, not the whole list?

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
                cont->EAX = 0;
                return cont;
            }

            //If there is a currently executing process
            if(current != NULL){
                //Ready, NONSuspend and save the context
                current->execute = 0;
                current->dispatch = 3;
                current->stack_ptr = (char*) cont;
                pcb_insert(current);
            }

            current = ready_head;
            ready_head = ready_head->next;
            cont = (context *) current->stack_ptr;
            cont->EAX = 0;

            return cont;
        }
        //EXIT
        else {
            
            pcb_free(current);

            if( ready == NULL){
                first_context->EAX = 0;
                return first_context;
            }

            pcb_remove(ready);

            current = ready;
            current->execute = 0;
            current->dispatch = 3;

            ((context *)current->stack_ptr)->EAX = 0;
            return (context *) current->stack_ptr;
        }
    }
    //Unrecognized op code
    else {
        cont->EAX = -1;
        return cont;
    }
} 
