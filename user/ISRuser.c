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
    pcb *pcb = proc1;
    //and queued in a non-suspended ready state,
    pcb->dispatch =3;
    pcb->execute =0;
    //with a name and priority of your choosing
    pcb->name_arr = "proc1";
    pcb->priority = 1;
    //initialze and save the context for each process at the top of the PCB stack:
    
    //CS must be 0x08 while other segments are 0x10
    //EBP must be the bottom of the PCB Stack
    //ESP must be the top of the PCB stack
    //EIP must be a pointer to the function (the name of the function, without parentesis, is a point to that function)
    //EFLAGS must be 0x0202
    //All other registers should be 0


    //make process
    //assign a context (stack ptr)
    //fill out stack with register values
}