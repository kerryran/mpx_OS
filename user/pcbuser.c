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
    // Unique name
    if (pcb_find(name) != NULL)
    {
        puts("\nPCB already exists.\n");
        return NULL;
    }

    // Valid name
    if (strcmp(name, "") == 0)
    {
        puts("\nInvalid name.\n");
    }

    if (class != 0 && class != 1)
    {
        puts("\nClass is invalid.\n");
        return NULL;
    }

    // priority must be valid
    if ((priority < 0) || (priority > 9))
    {
        puts("\nPriority is invalid.\n");
        return NULL;
    }
    pcb *new_pcb = pcb_setup(name, class, priority);
    pcb_insert(new_pcb);

    return new_pcb;
}

// delete
void pcb_delete(char name[])
{

    // find process
    pcb *pcb = pcb_find(name);

    if (pcb_find(name) == NULL)
    {
        puts("\nCannot remove, PCB does not exist.\n");
    }
    // cannot be a system process
    else if (pcb->class == 0)
    {
        puts("\nCannot remove a system PCB.\n");
    }
    else
    {
        // remove from queue w/ pcb_remove()
        pcb_remove(pcb);

        // free all associated mem with pcb_free()
        pcb_free(pcb);
    }
}

// block
void pcb_block(char name[])
{
    pcb *pcb = pcb_find(name);

    if (pcb == NULL)
    {
        puts("\nPCB does not exist\n");
    }
    else
    {

        pcb_remove(pcb);
        pcb->execute = BLOCKED;
        pcb->next = NULL;
        pcb_insert(pcb);
    }

    // suspend
    void pcb_suspend(char name[])
    {
        pcb *pcb = pcb_find(name);

        if (pcb == NULL)
        {
            puts("\nPCB does not exist");
        }
        // cannot be a system process
        else if (pcb->class == 0)
        {
            puts("\nCannot suspend a system PCB.\n");
        }
        else
        {
            pcb_remove(pcb);
            pcb->dispatch = SUSPENDED;
            pcb->next = NULL;
            pcb_insert(pcb);
        }
    }

    // unblock
    void pcb_unblock(char name[])
    {
        pcb *pcb = pcb_find(name);

        if (pcb == NULL)
        {
            puts("\nPCB does not exist");
        }
        else
        {
            pcb_remove(pcb);
            pcb->execute = READY;
            pcb->next = NULL;
            pcb_insert(pcb);
        }
    }

    // resume
    void pcb_resume(char name[])
    {
        pcb *pcb = pcb_find(name);

        if (pcb == NULL)
        {
            puts("\nPCB does not exist");
        }

        pcb_remove(pcb);
        pcb->dispatch = NOT_SUSPENDED;
        pcb_insert(pcb);
    }

    // set priority
    void set_priority(char name[], int new_priority)
    {

        pcb *pcb = pcb_find(name);

        if (pcb == NULL)
        {
            puts("\nPCB does not exist");
        }

        if ((new_priority < 0) || (new_priority > 9))
        {
            puts("Invalid Priority");
        }
        else
        {
            pcb_remove(pcb);
            pcb->priority = new_priority;
            pcb->next = NULL;
            pcb_insert(pcb);
        }
    }
    // show PCB
    void show_pcb(char *name)
    {
        struct pcb *found_pcb = pcb_find(name);

        // Check if the PCB with the given name exists
        if (found_pcb != NULL)
        {
            puts("\n\nProcess Information:");
            puts("\nName: ");
            puts(found_pcb->name_arr);
            puts("\nClass: ");
            char class_str[10];
            itoa(found_pcb->class, class_str, 10);
            puts(class_str);
            puts("\nState: ");
            char execute_str[10];
            itoa(found_pcb->execute, execute_str, 10);
            puts(execute_str);
            puts("\nSuspended Status: ");
            char dispatch_str[10];
            itoa(found_pcb->dispatch, dispatch_str, 10);
            puts(dispatch_str);
            puts("\nPriority: ");
            char priority_str[10];
            itoa(found_pcb->priority, priority_str, 10);
            puts(priority_str);
            puts("\n");
        }
        else
        {
            puts("\nProcess not found.");
        }
    }
    void show_ready(void)
    {
        // check through the ready queue
        struct pcb *current_ready = ready_head;
        char num[10];

        puts("\nReady Queue:\n");
        if (current_ready == NULL)
        {
            puts("\nReady Queue is Empty\n");
        }
        else
        {
            puts("Format: Name, Class, State, Status, Priority \n");
            while (current_ready != NULL)
            {
                puts(current_ready->name_arr);
                puts(", ");
                itoa(current_ready->class, num, 10);
                puts(num);
                puts(", ");
                itoa(current_ready->execute, num, 10);
                puts(num);
                puts(", ");
                itoa(current_ready->dispatch, num, 10);
                puts(num);
                puts(", ");
                itoa(current_ready->priority, num, 10);
                puts(num);
                puts("\n");

                current_ready = current_ready->next;
            }
        }
        // check through the suspended ready queue
        current_ready = suspended_ready_head;

        puts("\nSuspended Ready Queue:\n");
        if (current_ready == NULL)
        {
            puts("\nSuspended Ready Queue is Empty\n");
        }
        else
        {
            puts("Format: Name, Class, State, Status, Priority \n");
            while (current_ready != NULL)
            {
                puts(current_ready->name_arr);
                puts(", ");
                itoa(current_ready->class, num, 10);
                puts(num);
                puts(", ");
                itoa(current_ready->execute, num, 10);
                puts(num);
                puts(", ");
                itoa(current_ready->dispatch, num, 10);
                puts(num);
                puts(", ");
                itoa(current_ready->priority, num, 10);
                puts(num);
                puts("\n");

                current_ready = current_ready->next;
            }
        }
    }
    void show_blocked(void)
    {
        // check through the blocked queue
        struct pcb *current_blocked = blocked_head;
        char num[10];

        puts("\nBlocked Queue:\n");
        if (current_blocked == NULL)
        {
            puts("\nBlocked Queue is Empty\n");
        }
        else
        {
            puts("Format: Name, Class, State, Status, Priority \n");
            while (current_blocked != NULL)
            {
                puts(current_blocked->name_arr);
                puts(", ");
                itoa(current_blocked->class, num, 10);
                puts(num);
                puts(", ");
                itoa(current_blocked->execute, num, 10);
                puts(num);
                puts(", ");
                itoa(current_blocked->dispatch, num, 10);
                puts(num);
                puts(", ");
                itoa(current_blocked->priority, num, 10);
                puts(num);
                puts("\n");

                current_blocked = current_blocked->next;
            }
        }
        // check through the suspended blocked queue
        current_blocked = suspended_blocked_head;

        puts("\nSuspended Blocked Queue:\n");
        if (current_blocked == NULL)
        {
            puts("\nSuspended Blocked Queue is Empty\n");
        }
        else
        {
            puts("Format: Name, Class, State, Status, Priority \n");
            while (current_blocked != NULL)
            {
                puts(current_blocked->name_arr);
                puts(", ");
                itoa(current_blocked->class, num, 10);
                puts(num);
                puts(", ");
                itoa(current_blocked->execute, num, 10);
                puts(num);
                puts(", ");
                itoa(current_blocked->dispatch, num, 10);
                puts(num);
                puts(", ");
                itoa(current_blocked->priority, num, 10);
                puts(num);
                puts("\n");

                current_blocked = current_blocked->next;
            }
        }
    }

    void show_all(void)
    {
        show_ready();
        show_blocked();
    }
