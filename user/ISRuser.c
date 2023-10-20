#include <stdio.h>
#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <stdlib.h>
#include <mpx/interrupts.h>
#include <../include/mpx/ISRuser.h>
#include <../include/mpx/pcb.h>
#include <include/processes.h>
#include <include/pcbuser.h>

void yield(void){
    sys_req(IDLE);
}
 
void load_r3(void){

    //Load the R3 test processes from <processes.h>
    //Each process (one per function) is loaded
    //and queued in a non-suspended ready state,
    // with a name and priority of your choosing
    proc1();
    pcb* process1 = pcb_setup("proc1", 0, 1);
    process1->dispatch = 3;
    process1->execute = 0;

    proc2();
    pcb* process2 = pcb_setup("proc2", 0, 2);
    process1->dispatch = 3;
    process1->execute = 0;

    proc3();
    pcb* process3 = pcb_setup("proc3", 0, 3);
    process1->dispatch = 3;
    process1->execute = 0;
    
    proc4();
    pcb* process4 = pcb_setup("proc4", 0, 4);
    process1->dispatch = 3;
    process1->execute = 0;
    
    proc5();
    pcb* process5 = pcb_setup("proc5", 0, 5);
    process1->dispatch = 3;
    process1->execute = 0;
    
    sys_idle_process();
    pcb* process_sys_idle = pcb_setup("proc_idle", 0, 6);
    process_sys_idle->dispatch = 3;
    process_sys_idle->execute = 0;
    
    //initialze and save the context for each process at the top of the PCB stack:
    //CS must be 0x08 while other segments are 0x10
    //EBP must be the bottom of the PCB Stack
    //ESP must be the top of the PCB stack
    //EIP must be a pointer to the function (the name of the function, without parentesis, is a point to that function)
    //EFLAGS must be 0x0202
    //All other registers should be 0
}