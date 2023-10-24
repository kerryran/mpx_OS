#include <../include/mpx/pcb.h>
#include <../include/mpx/isr.h>
#include <../include/sys_req.h>
#include<stddef.h>

pcb *pcb_exec = NULL;

static context *first_cont = NULL;

struct context *sys_call(context *cont)
{
    // Get the operation code from EAX
    op_code operation_code = (op_code)cont->EAX;

    if (first_cont == NULL)
    {
        first_cont = cont;
    }

    // Declare a context pointer to be returned
    context *next_context = NULL;

    // Handle system call based on the operation code
    switch (operation_code)
    {
        case EXIT:
            
            if (next_context == NULL) {
                next_context = first_cont;
            }
            break;

        case IDLE:
    
            break;

        

        default:
           
            break;
    }

    // Return context pointer
    return next_context;
}

