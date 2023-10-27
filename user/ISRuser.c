#include <stdio.h>
#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <stdlib.h>
#include <mpx/interrupts.h>
#include <../include/mpx/isr.h>
#include <../include/mpx/pcb.h>
#include <include/processes.h>
#include <include/pcbuser.h>

void yield(void){
    sys_req(IDLE);
}
 
void load_r3(void){
    //Load the R3 test processes from <processes.h>
    //Each process (one per function) is loaded
    pcb *pcb1 = pcb_setup("proc1", 0, 5);  // call setup pcb
    //and queued in a non-suspended ready state,
    pcb1->dispatch =3;
    pcb1->execute =0;
    //with a name and priority of your choosing
    pcb1->priority = 1;
    // HERE create an initial context
    pcb_insert(pcb1);
    

    //initialze and save the context for each process at the top of the PCB stack:
    (context *)cp = (context *)pcb->stack_top
    cp->cs = 0x08;
    cp->eip = proc1
    //CS must be 0x08 while other segments are 0x10
    //EBP must be the bottom of the PCB Stack
    //ESP must be the top of the PCB stack
    //EIP must be a pointer to the function (the name of the function, without parentesis, is a point to that function)
    //EFLAGS must be 0x0202
    //All other registers should be 0
    context->ESP =
    context->EAX =
    context->EBX =
    context->ECX =
    context->EDX =
    context->EDP =
    context->ESI =
    context->EDI =
    context->DS =    
    context->ES =    
    context->FS =    
    context->GS =    
    context->SS =    
    context->EIP =
    context->CS =    
    context->EFLAGS =

    //make process
    //assign a context (stack ptr)
    //fill out stack with register values
}