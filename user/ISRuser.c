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

void yield(void){
    sys_req(IDLE);
}
 
void load_r3(void){
    //Load the R3 test processes from <processes.h>
    //Each process (one per function) is loaded
    pcb *pcb1 = pcb_setup("proc1", 1, 2);  // call setup pcb
    context *context1 = (context *)pcb1->stack_ptr;
    //and queued in a non-suspended ready state,
    pcb1->dispatch =3;
    pcb1->execute =0;
    //with a name and priority of your choosing
    pcb1->priority = 1;
    pcb1->context->ESP =(unsigned int)0x00; 
    pcb1->context->EAX =(unsigned int)0x00; 
    pcb1->context->EBX =(unsigned int)0x00; 
    pcb1->context->ECX =(unsigned int)0x00; 
    pcb1->context->EDX =(unsigned int)0x00; 
    pcb1->context->EDP =(unsigned int)0x00; 
    pcb1->context->ESI = (unsigned int)0x00; 
    pcb1->context->EDI =  (unsigned int)0x00; 
    pcb1->context->DS = (unsigned int)0x10;   
    pcb1->context->ES = (unsigned int)0x10;   
    pcb1->context->FS = (unsigned int)0x10;   
    pcb1->context->GS = (unsigned int)0x10;   
    pcb1->context->SS =  (unsigned int)0x10;  
    pcb1->context->EIP = (unsigned int)0x10;  
    pcb1->context->CS = (unsigned int)0x08;
    pcb1->context->EFLAGS =(unsigned int)0x0202;
    // HERE create an initial context
    pcb_insert(pcb1);

    //proc2 steps
    pcb *pbc2 = pcb_setup("proc2", 1, 2);
    (context *)context = (context *)pcb->stack_ptr;
    pcb2->dispatch =3;
    pcb2->execute =0;
    pcb2->priority = 1;
    pcb2->context->ESP =(unsigned int)0x00; 
    pcb2->context->EAX =(unsigned int)0x00; 
    pcb2->context->EBX =(unsigned int)0x00; 
    pcb2->context->ECX =(unsigned int)0x00; 
    pcb2->context->EDX =(unsigned int)0x00; 
    pcb2->context->EDP =(unsigned int)0x00; 
    pcb2->context->ESI = (unsigned int)0x00; 
    pcb2->context->EDI =  (unsigned int)0x00; 
    pcb2->context->DS = (unsigned int)0x10;   
    pcb2->context->ES = (unsigned int)0x10;   
    pcb2->context->FS = (unsigned int)0x10;   
    pcb2->context->GS = (unsigned int)0x10;   
    pcb2->context->SS =  (unsigned int)0x10;  
    pcb2->context->EIP = (unsigned int)0x10;  
    pcb2->context->CS = (unsigned int)0x08;
    pcb2->context->EFLAGS =(unsigned int)0x0202;
    // HERE create an initial context
    pcb_insert(pcb2);

    //proc3 steps
    pcb *pbc3 = pcb_setup("proc3", 1, 2);
    (context *)context = (context *)pcb->stack_ptr;
    pcb3->dispatch =3;
    pcb3->execute =0;
    pcb3->priority = 1;
    // HERE create an initial context
    pcb3->context->ESP =(unsigned int)0x00; 
    pcb3->context->EAX =(unsigned int)0x00; 
    pcb3->context->EBX =(unsigned int)0x00; 
    pcb3->context->ECX =(unsigned int)0x00; 
    pcb3->context->EDX =(unsigned int)0x00; 
    pcb3->context->EDP =(unsigned int)0x00; 
    pcb3->context->ESI = (unsigned int)0x00; 
    pcb3->context->EDI =  (unsigned int)0x00; 
    pcb3->context->DS = (unsigned int)0x10;   
    pcb3->context->ES = (unsigned int)0x10;   
    pcb3->context->FS = (unsigned int)0x10;   
    pcb3->context->GS = (unsigned int)0x10;   
    pcb3->context->SS =  (unsigned int)0x10;  
    pcb3->context->EIP = (unsigned int)0x10;  
    pcb3->context->CS = (unsigned int)0x08;
    pcb3->context->EFLAGS =(unsigned int)0x0202;
    pcb_insert(pcb3);

    //proc4 steps
    pcb *pbc4 = pcb_setup("proc4", 1, 2);
    (context *)context = (context *)pcb->stack_ptr;
    pcb4->dispatch =3;
    pcb4->execute =0;
    pcb4->priority = 1;
    // HERE create an initial context
    pcb4->context->ESP =(unsigned int)0x00; 
    pcb4->context->EAX =(unsigned int)0x00; 
    pcb4->context->EBX =(unsigned int)0x00; 
    pcb4->context->ECX =(unsigned int)0x00; 
    pcb4->context->EDX =(unsigned int)0x00; 
    pcb4->context->EDP =(unsigned int)0x00; 
    pcb4->context->ESI = (unsigned int)0x00; 
    pcb4->context->EDI =  (unsigned int)0x00; 
    pcb4->context->DS = (unsigned int)0x10;   
    pcb4->context->ES = (unsigned int)0x10;   
    pcb4->context->FS = (unsigned int)0x10;   
    pcb4->context->GS = (unsigned int)0x10;   
    pcb4->context->SS =  (unsigned int)0x10;  
    pcb4->context->EIP = (unsigned int)0x10;  
    pcb4->context->CS = (unsigned int)0x08;
    pcb4->context->EFLAGS =(unsigned int)0x0202;
    pcb_insert(pcb4);

    //proc5 steps
    pcb *pbc5 = pcb_setup("proc5", 1, 2);
    (context *)context = (context *)pcb->stack_ptr;
    pcb5->dispatch =3;
    pcb5->execute =0;
    pcb5->priority = 1;
    // HERE create an initial context
    pcb5->context->ESP =(unsigned int)0x00; 
    pcb5->context->EAX =(unsigned int)0x00; 
    pcb5->context->EBX =(unsigned int)0x00; 
    pcb5->context->ECX =(unsigned int)0x00; 
    pcb5->context->EDX =(unsigned int)0x00; 
    pcb5->context->EDP =(unsigned int)0x00; 
    pcb5->context->ESI = (unsigned int)0x00; 
    pcb5->context->EDI =  (unsigned int)0x00; 
    pcb5->context->DS = (unsigned int)0x10;   
    pcb5->context->ES = (unsigned int)0x10;   
    pcb5->context->FS = (unsigned int)0x10;   
    pcb5->context->GS = (unsigned int)0x10;   
    pcb5->context->SS =  (unsigned int)0x10;  
    pcb5->context->EIP = (unsigned int)0x10;  
    pcb5->context->CS = (unsigned int)0x08;
    pcb5->context->EFLAGS =(unsigned int)0x0202;
    pcb_insert(pcb5);


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