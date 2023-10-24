#include <../include/mpx/pcb.h>
#include <../include/mpx/isr.h>
#include <../include/sys_req.h>
#include<stddef.h>

// Global PCB pointer for currently executing process
pcb *pcb_exec = NULL;

// Context pointer from the first sys_call()
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
            // Implement EXIT operation
            // Delete the currently running PCB
            // Load the next process context (if any) or the original context
            // Ensure that the return value is 0
            // Example:
            // delete_current_pcb();
            // next_context = get_next_process_context();
            if (next_context == NULL) {
                next_context = first_cont;
            }
            break;

        case IDLE:
            // Implement IDLE operation
            // Retrieve the context of the next process (if any)
            // and store it in 'next_context'
            // Ensure that the return value is 0
            // Example:
            // next_context = get_next_process_context();
            break;

        case READ:
            // Implement READ operation
            // Extract required arguments for READ operation
            // Perform READ operation logic
            // Example:
            // result = read_from_device();
            break;

        case WRITE:
            // Implement WRITE operation
            // Extract required arguments for WRITE operation
            // Perform WRITE operation logic
            // Example:
            // result = write_to_device();
            break;

        default:
            // Handle other system call operations
            // Set the return value to -1 if needed
            // Example:
            // Handle other operations or set the return value to -1
            // return_value = handle_other_operations();
            // next_context = get_next_process_context();
            break;
    }

    // Return the appropriate context pointer
    return next_context;
}

