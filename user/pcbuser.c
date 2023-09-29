#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <stdlib.h>
#include <mpx/interrupts.h>

//include whatever needed files.
#include "pcb.h"
#include <stdio.h>

struct pcb* pcb_create(char name[], enum class class, int priority){

    //pcb_setup() to create a pcb
    struct pcb* new_pcb =pcb_setup(name, class, priority);

    //insert into the appropriate queue with pcb_insert()
    pcb_insert(new_pcb);

    //ERROR HANDLING:
    //name must be unique and valid
    if (pcb_find(name) != NULL){
        puts("PCB already exists.\n");
    }

    //class must be valid
    if((class != 1) || (class!=0)){
        puts("Class not valid.\n");
    }
    
    //priority must be valid
    if((priority<0) || (priority > 9)){
        puts("Prority is invalid.\n");
    }

    return new_pcb;
}

//delete
void pcb_delete(char name[]){

    //find process
    struct pcb* pcb = pcb_find(name);

    //remove from queue w/ pcb_remove()
    pcb_remove(pcb);

    //free all associated mem with pcb_free()
    pcb_free(pcb);

    //ERROR HANDLING:
    //valid name
    if(pcb_find(name) == NULL){
        puts("Cannot remove, PCB does not exist.\n");
    }

    //cannot be a system process
    if(pcb->prority == 0){
        puts("Cannot remove a system PCB.\n");
    }

    return 0;
}

//block
void pcb_block(char name[]){

    struct pcb* pcb = pcb_find(name);

    if(pcb == NULL){
        puts("PCB does not exist.\n");
        return 0;
    }
    
    //move to appropriate queue
    pcb_remove(pcb);
    //puts process in blocked state
    pcb->execute= 1;
    pcb_insert(pcb);

    //ERROR HANDLING:
    //must be valid name
    
    
    return 0;
}

//unblock
void pcb_unblock(char name[]){

    struct pcb* pcb = pcb_find(name);

    if(pcb == NULL){
        puts("PCB does not exist.\n");
        return 0;
    }
    ///move to appropriate queue
    pcb_remove(pcb);
    //puts process in unblocked (ready) state
    pcb->execute= 0;
    pcb_insert(pcb);

    return 0;
}

//suspend
void pcb_suspend(char name[]){
    struct pcb* pcb = pcb_find(name);

    if(pcb == NULL){
        puts("PCB does not exist.\n");
        return 0;
    }
    //move to appropriate queue
    pcb_remove(pcb);
    //puts process in suspended state
    pcb->dispatch= 4;
    pcb_insert(pcb);

    //ERROR HANDLING:
    //name must be valid
    if(pcb_find(name) == NULL){
        puts("Cannot remove, PCB does not exist.\n");
    }
    //cannot be a system process
    if(pcb->prority == 0){
        puts("Cannot suspend a system PCB.\n");
    }
    
    return 0;
}
//resume
void pcb_resume(char name[]){
    struct pcb* pcb = pcb_find(name);

    if(pcb == NULL){
        puts("PCB does not exist.\n");
        return 0;
    }
    ///move to appropriate queue
    pcb_remove(pcb);
    //puts process in resumed (not suspended) state
    pcb->dispatch= 3;
    pcb_insert(pcb);

    //ERROR HANDLING:
    //name must be valid

    return 0;
}

//set priority

//show PCB
void show_pcb(char* name){
    //not workin
    char temp = pcb_find(name){
        if(temp == NULL){
            //process not found
            puts("process not found");
        }
        else{
            char[] status[] = {pcb.name, pcb.class, pcb.priority};
        }
    }
}
void show_ready(char* name){
    //show_ready
}

void show_blocked(char* name){
   //show blocked
}

void show_all(char* name){
   puts("this is show all");
}