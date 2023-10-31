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
//#include <pcb.h>
#include <pcbuser.h>

typedef struct alarm{
    char* time;
    char* message;
}alarm;


void alarm(char* time, char* message){

    alarm *new_alarm = sys_alloc_mem(sizeof(*new_alarm));

    //Initialize time input
    int seconds = 0;
    int minutes = 0;
    int hours = 0;

    //Gather time input from user
    

}


