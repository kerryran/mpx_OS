#include <../include/mpx/pcb.h>
#include <../include/mpx/isr.h>

// all registers for the context
typedef struct context
{
    int CS;
    int DS;
    int ES;
    int FS;
    int GS;
    int SS;
    int EI;
    int EFLAGS;
    int EAX;
    int EBX;
    int ECX;
    int EDX;
    int ESI;
    int EDI;
    int EBP;
    int ESP;
    // struct context *next;
    // How to add the context to the PCB stack space?
    // And where is this done? System call?

} context;

// Global PCB pointer for currently executing process
pcb *pcb_exec = NULL;

// Context pointer from first sys_call()
static context *first_cont = NULL;

struct context *sys_call(context *cont)
{
    if (first_cont == NULL)
    {
        first_cont = cont;
    }
}
