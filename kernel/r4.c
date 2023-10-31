#include <memory.h>
#include <string.h>
#include <../include/mpx/pcb.h>
#include <../include/mpx/isr.h>
#include <../include/processes.h>
#include <../include/comhand.h>
#include <../include/mpx/r4.h>


void command_handler()
{
	pcb * pcb = pcb_setup("comhand", 0, 9);
	context *contexto = (context *) pcb->stack_ptr;
	memset(contexto, 0, sizeof(context));

	//Segments
    contexto->CS = (unsigned int)0x08;
    contexto->DS = (unsigned int)0x10;   
    contexto->ES = (unsigned int)0x10;   
    contexto->FS = (unsigned int)0x10;   
    contexto->GS = (unsigned int)0x10;   
    contexto->SS = (unsigned int)0x10;  
    //Registers
    contexto->EBP = (unsigned int) pcb->stack;
    contexto->EAX = (unsigned int) 0x00; 
    contexto->EBX = (unsigned int) 0x00; 
    contexto->ECX = (unsigned int) 0x00; 
    contexto->EDX = (unsigned int) 0x00; 
    contexto->EBP = (unsigned int) 0x00; 
    contexto->ESI = (unsigned int) 0x00; 
    contexto->EDI = (unsigned int) 0x00; 
    //Flags
    contexto->EIP = (unsigned int) comhand;  
    contexto->EFLAGS =(unsigned int)0x0202;

	pcb_insert(pcb);
}

void sys_idle()
{
    pcb * pcb = pcb_setup("idle", 0, 0);
	context *contexto = (context *) pcb->stack_ptr;
	memset(contexto, 0, sizeof(context));

	//Segments
    contexto->CS = (unsigned int)0x08;
    contexto->DS = (unsigned int)0x10;   
    contexto->ES = (unsigned int)0x10;   
    contexto->FS = (unsigned int)0x10;   
    contexto->GS = (unsigned int)0x10;   
    contexto->SS = (unsigned int)0x10;  
    //Registers
    contexto->EBP = (unsigned int) pcb->stack;
    contexto->EAX = (unsigned int) 0x00; 
    contexto->EBX = (unsigned int) 0x00; 
    contexto->ECX = (unsigned int) 0x00; 
    contexto->EDX = (unsigned int) 0x00; 
    contexto->EBP = (unsigned int) 0x00; 
    contexto->ESI = (unsigned int) 0x00; 
    contexto->EDI = (unsigned int) 0x00; 
    //Flags
    contexto->EIP = (unsigned int) sys_idle_process;  
    contexto->EFLAGS =(unsigned int)0x0202;

	pcb_insert(pcb);
}
