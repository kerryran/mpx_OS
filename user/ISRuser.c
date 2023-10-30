#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <stdlib.h>
#include <mpx/interrupts.h>
#include <../include/mpx/isr.h>
#include <../include/mpx/pcb.h>
#include <../include/processes.h>
#include <../include/pcbuser.h>

void yield(){
    sys_req(IDLE, 0, NULL, NULL);
}
 
void load_r3(){
    //Load the R3 test processes from <processes.h>
    //Each process (one per function) is loaded
    // Create a process in the ready, non-suspended state with any priority and name

    exists = pcb_find("proc1");
    if (exists != NULL) {
        puts("ERROR proc1 exists already");
    }
    else {

        pcb *pcb1 = pcb_setup("proc1", 1, 2);

        //Initialize the context with the appropriate values
        context * context1 = (context *) pcb1->stack_ptr;
        memset(context1, 0, sizeof(content));

        //Segments
        context1->CS = (unsigned int)0x08;
        context1->DS = (unsigned int)0x10;   
        context1->ES = (unsigned int)0x10;   
        context1->FS = (unsigned int)0x10;   
        context1->GS = (unsigned int)0x10;   
        context1->SS = (unsigned int)0x10;  
        //Registers
        context1->EBP = (unsigned int) pcb1->stack_ptr;
        context1->EAX = (unsigned int) 0x00; 
        context1->EBX = (unsigned int) 0x00; 
        context1->ECX = (unsigned int) 0x00; 
        context1->EDX = (unsigned int) 0x00; 
        context1->EBP = (unsigned int) 0x00; 
        context1->ESI = (unsigned int) 0x00; 
        context1->EDI = (unsigned int) 0x00; 
        //Flags
        context1->EIP = (unsigned int) proc1;  
        context1->EFLAGS =(unsigned int)0x0202;
        //Add the process to the queue
        pcb_insert(pcb1);
        puts("Created proc1");
    }

    //proc2 steps
    pcb * pcb2 = pcb_setup("proc2", 1, 2);
    
    context * context2 = (context *) pcb2->stack_ptr;
    context1->ESP = (unsigned int)0x00; 
    context2->EAX =(unsigned int)0x00; 
    context2->EBX =(unsigned int)0x00; 
    context2->ECX =(unsigned int)0x00; 
    context2->EDX =(unsigned int)0x00; 
    context2->EBP =(unsigned int)0x00; 
    context2->ESI = (unsigned int)0x00; 
    context2->EDI =  (unsigned int)0x00; 
    context2->DS = (unsigned int)0x10;   
    context2->ES = (unsigned int)0x10;   
    context2->FS = (unsigned int)0x10;   
    context2->GS = (unsigned int)0x10;   
    context2->SS =  (unsigned int)0x10;  
    context2->EIP = (unsigned int)proc2; 
    context2->CS = (unsigned int)0x08;
    context2->EFLAGS =(unsigned int)0x0202;
    pcb_insert(pcb2);

    //proc3 steps
    pcb *pcb3 = pcb_setup("proc3", 1, 2);
    context * context3 = (context *) pcb3->stack_ptr;
    // HERE create an initial context
    context3->EAX =(unsigned int)0x00; 
    context3->EBX =(unsigned int)0x00; 
    context3->ECX =(unsigned int)0x00; 
    context3->EDX =(unsigned int)0x00; 
    context3->EBP =(unsigned int)0x00; 
    context3->ESI = (unsigned int)0x00; 
    context3->EDI =  (unsigned int)0x00; 
    context3->DS = (unsigned int)0x10;   
    context3->ES = (unsigned int)0x10;   
    context3->FS = (unsigned int)0x10;   
    context3->GS = (unsigned int)0x10;   
    context3->SS =  (unsigned int)0x10;  
    context3->EIP = (unsigned int)proc3;  
    context3->CS = (unsigned int)0x08;
    context3->EFLAGS =(unsigned int)0x0202;
    pcb_insert(pcb3);

    //proc4 steps
    pcb *pcb4 = pcb_setup("proc4", 1, 2);
    context * context4 = (context *)pcb4->stack_ptr;
    // HERE create an initial context
    context1->ESP = (unsigned int)0x00; 
    context4->EAX =(unsigned int)0x00; 
    context4->EBX =(unsigned int)0x00; 
    context4->ECX =(unsigned int)0x00; 
    context4->EDX =(unsigned int)0x00; 
    context4->EBP =(unsigned int)0x00; 
    context4->ESI = (unsigned int)0x00; 
    context4->EDI =  (unsigned int)0x00; 
    context4->DS = (unsigned int)0x10;   
    context4->ES = (unsigned int)0x10;   
    context4->FS = (unsigned int)0x10;   
    context4->GS = (unsigned int)0x10;   
    context4->SS =  (unsigned int)0x10;  
    context4->EIP = (unsigned int) proc4; 
    context4->CS = (unsigned int)0x08;
    context4->EFLAGS =(unsigned int)0x0202;
    pcb_insert(pcb4);

    //proc5 steps
    pcb *pcb5 = pcb_setup("proc5", 1, 2);
    context * context5 = (context *) pcb5->stack_ptr;
    // HERE create an initial context
    context1->ESP = (unsigned int)0x00; 
    context5->EAX =(unsigned int)0x00; 
    context5->EBX =(unsigned int)0x00; 
    context5->ECX =(unsigned int)0x00; 
    context5->EDX =(unsigned int)0x00; 
    context5->EBP =(unsigned int)0x00; 
    context5->ESI = (unsigned int)0x00; 
    context5->EDI =  (unsigned int)0x00; 
    context5->DS = (unsigned int)0x10;   
    context5->ES = (unsigned int)0x10;   
    context5->FS = (unsigned int)0x10;   
    context5->GS = (unsigned int)0x10;   
    context5->SS =  (unsigned int)0x10;  
    context5->EIP = (unsigned int)proc5; 
    context5->CS = (unsigned int)0x08;
    context5->EFLAGS =(unsigned int)0x0202;
    pcb_insert(pcb5);


    //initialze and save the context for each process at the top of the PCB stack:
    
    //CS must be 0x08 while other segments are 0x10
    //EBP must be the bottom of the PCB Stack
    //ESP must be the top of the PCB stack
    //EIP must be a pointer to the function (the name of the function, without parentesis, is a point to that function)
    //EFLAGS must be 0x0202
    //All other registers should be 0
}
