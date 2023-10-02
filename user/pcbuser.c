#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <stdlib.h>
#include <mpx/interrupts.h>
#include <../include/mpx/pcb.h>
// include whatever needed files.

struct pcb *pcb_create(char name[], int class, int priority)
{

    // pcb_setup() to create a pcb
    pcb *new_pcb = pcb_setup(name, class, priority);

    // insert into the appropriate queue with pcb_insert()
    pcb_insert(new_pcb);

    // ERROR HANDLING:
    // name must be unique and valid
    if (pcb_find(name) != NULL)
    {
        puts("PCB already exists.\n");
    }

    // class must be valid
    if ((class != 1) && (class != 0))
    {
        puts("Class not valid.\n");
    }

    // priority must be valid
    if ((priority < 0) || (priority > 9))
    {
        puts("Priority is invalid.\n");
    }

    return new_pcb;
}

// delete
void pcb_delete(char name[])
{

    // find process
    pcb *pcb = pcb_find(name);

    // remove from queue w/ pcb_remove()
    pcb_remove(pcb);

    // free all associated mem with pcb_free()
    pcb_free(pcb);

    // ERROR HANDLING:
    // valid name
    if (pcb_find(name) == NULL)
    {
        puts("Cannot remove, PCB does not exist.\n");
    }
    // cannot be a system process
    if (pcb->priority == 0)
    {
        puts("Cannot remove a system PCB.\n");
    }
}

// block
void pcb_block(char name[])
{
    pcb* pcb = pcb_find(name);

   if (pcb == NULL)
   {
    puts("PCB does not exist");
   }

   pcb_remove(pcb);
   pcb->execute = BLOCKED;
   pcb_insert(pcb);
}

// suspend
void pcb_suspend(char name[])
{
   pcb* pcb = pcb_find(name);

   if (pcb == NULL)
   {
    puts("PCB does not exist");
   }

   pcb_remove(pcb);
   pcb->dispatch = SUSPENDED;
   pcb_insert(pcb);

}

// unblock
void pcb_unblock(char name[])
{
    pcb* pcb = pcb_find(name);

   if (pcb == NULL)
   {
    puts("PCB does not exist");
   }

   pcb_remove(pcb);
   pcb->execute = READY;
   pcb_insert(pcb);
}

// resume
void pcb_resume(char name[])
{
    pcb* pcb = pcb_find(name);

   if (pcb == NULL)
   {
    puts("PCB does not exist");
   }

   pcb_remove(pcb);
   pcb->dispatch = NOT_SUSPENDED;
   pcb_insert(pcb);
}

//set priority
void set_priority(char* name, int new_priority){

    struct pcb* pcb = pcb_find(name);

    pcb_remove(pcb);
    pcb->priority = new_priority;
    pcb_insert(pcb);
}
// show PCB
void show_pcb(char *name)
{
    // not workin
    char temp = pcb_find(name);
    {
        if (temp == NULL)
        {
            // process not found
            puts("process not found");
        }
        else
        {
            char[] status[] = {pcb.name, pcb.class, pcb.priority};
        }
    }
}
void show_ready(char *name)
{
    // show_ready
    puts(name);
}

void show_blocked(void)
{
    puts("All PCBs in the Blocked State:")
}

void show_all(char *name)
{
    puts("this is show all");
    puts(name);
}
