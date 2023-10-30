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

    //Error checking pcb
    pcb * exists = pcb_find("proc1");

    // Process 1
    if (exists != NULL) {
        puts("ERROR proc1 exists already");
    }
    else {

        pcb *pcb1 = pcb_setup("proc1", 1, 2);

        //Initialize the context with the appropriate values
        context * context1 = (context *) pcb1->stack_ptr;
        memset(context1, 0, sizeof(context));

        //Segments
        context1->CS = (unsigned int)0x08;
        context1->DS = (unsigned int)0x10;   
        context1->ES = (unsigned int)0x10;   
        context1->FS = (unsigned int)0x10;   
        context1->GS = (unsigned int)0x10;   
        context1->SS = (unsigned int)0x10;  
        //Registers
        context1->EBP = (unsigned int) pcb1->stack;
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


    //Process 2
    exists = pcb_find("proc2");
    if (exists != NULL) {
        puts("ERROR proc2 exists already");
    }
    else {

        pcb *pcb = pcb_setup("proc2", 1, 2);

        //Initialize the context with the appropriate values
        context * context2 = (context *) pcb->stack_ptr;
        memset(context2, 0, sizeof(context));

        //Segments
        context2->CS = (unsigned int)0x08;
        context2->DS = (unsigned int)0x10;   
        context2->ES = (unsigned int)0x10;   
        context2->FS = (unsigned int)0x10;   
        context2->GS = (unsigned int)0x10;   
        context2->SS = (unsigned int)0x10;  
        //Registers
        context2->EBP = (unsigned int) pcb->stack;
        context2->EAX = (unsigned int) 0x00; 
        context2->EBX = (unsigned int) 0x00; 
        context2->ECX = (unsigned int) 0x00; 
        context2->EDX = (unsigned int) 0x00; 
        context2->EBP = (unsigned int) 0x00; 
        context2->ESI = (unsigned int) 0x00; 
        context2->EDI = (unsigned int) 0x00; 
        //Flags
        context2->EIP = (unsigned int) proc1;  
        context2->EFLAGS =(unsigned int)0x0202;
        //Add the process to the queue
        pcb_insert(pcb);
        puts("Created proc2");
    }

    //Process 3
    exists = pcb_find("proc3");
    if (exists != NULL) {
        puts("ERROR proc3 exists already");
    }
    else {

        pcb *pcb = pcb_setup("proc3", 1, 2);

        //Initialize the context with the appropriate values
        context * context2 = (context *) pcb->stack_ptr;
        memset(context2, 0, sizeof(context));

        //Segments
        context2->CS = (unsigned int)0x08;
        context2->DS = (unsigned int)0x10;   
        context2->ES = (unsigned int)0x10;   
        context2->FS = (unsigned int)0x10;   
        context2->GS = (unsigned int)0x10;   
        context2->SS = (unsigned int)0x10;  
        //Registers
        context2->EBP = (unsigned int) pcb->stack;
        context2->EAX = (unsigned int) 0x00; 
        context2->EBX = (unsigned int) 0x00; 
        context2->ECX = (unsigned int) 0x00; 
        context2->EDX = (unsigned int) 0x00; 
        context2->EBP = (unsigned int) 0x00; 
        context2->ESI = (unsigned int) 0x00; 
        context2->EDI = (unsigned int) 0x00; 
        //Flags
        context2->EIP = (unsigned int) proc1;  
        context2->EFLAGS =(unsigned int)0x0202;
        //Add the process to the queue
        pcb_insert(pcb);
        puts("Created proc3");
    }

    //Process 4
    exists = pcb_find("proc4");
    if (exists != NULL) {
        puts("ERROR proc4 exists already");
    }
    else {

        pcb *pcb = pcb_setup("proc4", 1, 2);

        //Initialize the context with the appropriate values
        context * context2 = (context *) pcb->stack_ptr;
        memset(context2, 0, sizeof(context));

        //Segments
        context2->CS = (unsigned int)0x08;
        context2->DS = (unsigned int)0x10;   
        context2->ES = (unsigned int)0x10;   
        context2->FS = (unsigned int)0x10;   
        context2->GS = (unsigned int)0x10;   
        context2->SS = (unsigned int)0x10;  
        //Registers
        context2->EBP = (unsigned int) pcb->stack;
        context2->EAX = (unsigned int) 0x00; 
        context2->EBX = (unsigned int) 0x00; 
        context2->ECX = (unsigned int) 0x00; 
        context2->EDX = (unsigned int) 0x00; 
        context2->EBP = (unsigned int) 0x00; 
        context2->ESI = (unsigned int) 0x00; 
        context2->EDI = (unsigned int) 0x00; 
        //Flags
        context2->EIP = (unsigned int) proc1;  
        context2->EFLAGS =(unsigned int)0x0202;
        //Add the process to the queue
        pcb_insert(pcb);
        puts("Created proc4");
    }

    //Process 5
    exists = pcb_find("proc5");
    if (exists != NULL) {
        puts("ERROR proc5 exists already");
    }
    else {

        pcb *pcb = pcb_setup("proc5", 1, 2);

        //Initialize the context with the appropriate values
        context * context2 = (context *) pcb->stack_ptr;
        memset(context2, 0, sizeof(context));

        //Segments
        context2->CS = (unsigned int)0x08;
        context2->DS = (unsigned int)0x10;   
        context2->ES = (unsigned int)0x10;   
        context2->FS = (unsigned int)0x10;   
        context2->GS = (unsigned int)0x10;   
        context2->SS = (unsigned int)0x10;  
        //Registers
        context2->EBP = (unsigned int) pcb->stack;
        context2->EAX = (unsigned int) 0x00; 
        context2->EBX = (unsigned int) 0x00; 
        context2->ECX = (unsigned int) 0x00; 
        context2->EDX = (unsigned int) 0x00; 
        context2->EBP = (unsigned int) 0x00; 
        context2->ESI = (unsigned int) 0x00; 
        context2->EDI = (unsigned int) 0x00; 
        //Flags
        context2->EIP = (unsigned int) proc1;  
        context2->EFLAGS =(unsigned int)0x0202;
        //Add the process to the queue
        pcb_insert(pcb);
        puts("Created proc5");
    }
}
