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
        
    }
}