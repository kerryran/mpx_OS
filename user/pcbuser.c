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

    // pcb_setup() to create a pcb
    pcb *new_pcb = pcb_setup(name, class, priority);

    // insert into the appropriate queue with pcb_insert()
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
        puts("Cannot remove, PCB does not exist.\n");
    }
    // cannot be a system process
    else if(pcb->priority == 0)
    {
        puts("Cannot remove a system PCB.\n");
    }
    else{
         // remove from queue w/ pcb_remove()
        pcb_remove(pcb);

        // free all associated mem with pcb_free()
        pcb_free(pcb);

        
    };

   
    // ERROR HANDLING:
    // valid name
   
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
void set_priority(char name[], int new_priority){
    pcb* pcb = pcb_find(name);
    pcb_remove(pcb);
    pcb->priority = new_priority;
    pcb_insert(pcb);
}
// show PCB
void show_pcb(char *name)
{
    struct pcb *found_pcb = pcb_find(name);

    // Check if the PCB with the given name exists
     if (found_pcb != NULL) {
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
    } else {
        puts("\nProcess not found.");
    }
}
void show_ready(void) {
    // check through the ready queue
    struct pcb *current_ready = ready_head;
    puts("\n\nReady Queue:");
    if(current_ready == NULL){
        puts("\nReady Queue is Empty");
    }
    while (current_ready != NULL) {
        puts(current_ready->name_arr);
        current_ready = current_ready->next;
    }
}
void show_blocked(void) {
    // check through the blocked queue
    struct pcb *current_blocked = blocked_head;
    puts("\n\nBlocked Queue:");
    if(current_blocked == NULL){
        puts("\nBlocked Queue is Empty");
    }
    while (current_blocked != NULL) {
        puts(current_blocked->name_arr);
        current_blocked = current_blocked->next;
    }
}
void show_all(void) {
    // check through the ready queue
    struct pcb *current_ready = ready_head;
    puts("\n\nReady Queue:");
    if(current_ready == NULL){
        puts("\nReady Queue is Empty");
    }
    while (current_ready != NULL) {
        show_pcb(current_ready->name_arr); // Display information for the PCB
        current_ready = current_ready->next;
    }

    // check suspended ready queue
    struct pcb *current_suspended_ready = suspended_ready_head;
    puts("\n\nSuspended Ready Queue:");\
    if(current_suspended_ready == NULL){
        puts("\nSuspended Ready Queue is Empty");
    }
    while (current_suspended_ready != NULL) {
        show_pcb(current_suspended_ready->name_arr); // Display information for the PCB
        current_suspended_ready = current_suspended_ready->next;
    }

    // check the blocked queue
    struct pcb *current_blocked = blocked_head;
    puts("\n\nBlocked Queue:");
    if(current_blocked == NULL){
        puts("\nBlocked Queue is Empty");
    }
    while (current_blocked != NULL) {
        show_pcb(current_blocked->name_arr); // Display information for the PCB
        current_blocked = current_blocked->next;
    }

    // check the suspended blocked queue
    struct pcb *current_suspended_blocked = suspended_blocked_head;
    puts("\n\nSuspended Blocked Queue:");
    if(current_suspended_blocked == NULL){
        puts("\nSuspended Blocked Queue is Empty");
    }
    while (current_suspended_blocked != NULL) {
        show_pcb(current_suspended_blocked->name_arr); // Display information for the PCB
        current_suspended_blocked = current_suspended_blocked->next;
    }
}
