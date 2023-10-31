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
#include <float.h>
#include <pcb.h>
#include <pcbuser.h>

char* alarm(char* time, char* message){
        pcb* pcb = pcb_setup("alarm", 1, 1);
        (context*) pcb->stack_ptr = sys_call(IDLE);
        char* current_time = get_time();
        if(strcmp(current_time, time)==0){
                puts(message);
                return message;
                (context*) pcb->stack_ptr = sys_call(EXIT);
        }
        return "no alarm";
}

alarm_val *alarms;
int exit;

void add_alarm(alarm *alarm_to_add){
    if (alarms == NULL){
        alarms = ((sys_alloc_men(sizeof(*alarms))));
        alarms->head = NULL;
        alarms->tail = NULL;
    }

    alarm_val *temp = alarms;

    if(alarm_to_add == NULL){
        puts("The queue is empty")
        return;
    }

    if(temp->tail != NULL){
        temp->tail->next = alarm_to_add;
        alarm_to_add->prev = temp->tail;
        temp->tail = alarm_to_add;
    }else{
        temp->head = alarm_to_add;
        temp->tail = alarm_to_add;
    }
}
void remove_alarm(alarm *alarm_to_remove){
    alarm_val *temp = alarms;

    if(temp->head == NULL || alarm_to_remove == NULL){
        puts("Error, nothing to remove");
        return;
    }

    if(temp->head == alarm_to_remove){
        temp->head = alarm_to_remove
    }
}