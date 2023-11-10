#include <../include/mpx/pcb.h>
#include <../include/mpx/isr.h>
#include <../include/sys_req.h>
#include <../include/string.h>
#include <../include/pcbuser.h>
#include <stddef.h>

// Global PCB pointer representing the currently executing process
pcb *current = NULL;

// The temporary next process pointer

// Context from when sys_call is first called
context *first_context = NULL;

struct context *sys_call(struct context *cont)
{
    // Get the head of the ready queue
    //pcb * readyP = ready_head;
    //Need to get the first object in the ready_head linked list, not the whole list?

    // Handle system call based on the operation code

    // IDLE or EXIT
    if( cont->EAX == IDLE || cont->EAX == EXIT){


        //IDLE
        if (cont->EAX == IDLE) {
                    //Save the first context
        if( first_context == NULL){
            first_context = cont;
        }

            //If there is a currently executing process
            if(current != NULL){
                //Ready, NONSuspend and save the context
                current->execute = 0;
                current->dispatch = 3;
                current->stack_ptr = (char*) cont;
                pcb_insert(current);
             //   show_ready();
              //  cont->EAX = 0;
            }


        }
        //EXIT
        else {
            // delete the pcb
            pcb_free(current);

        }
    }
    //Unrecognized op code
    else {
        cont->EAX = -1;
        return cont;
    }
    // check next process
    if (ready_head != NULL){    
                current = ready_head;
                pcb_remove(current);
           // ready_head = ready_head->next;
            //set state to running
            return (context *) current->stack_ptr;
            //cont->EAX = 0; _
    }
    else{
        context* temp = first_context;
    first_context = NULL;
    current = NULL;
            return temp;
    }
} 
