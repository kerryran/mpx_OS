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
#include <../include/mpx/pcb.h>
#include <pcbuser.h>
#include <memory.h>

typedef struct alarm{
    int hour;
    int min;
    int sec;
    char name_arr[10];
    char message[100];
    state dispatch;
    state execute;
    struct alarm *next;
}alarm;



struct alarm *alarm_head;

void create_alarm(){

    alarm *new_alarm = sys_alloc_mem(sizeof(*new_alarm));

    //set alarm to non-suspended and ready
    new_alarm->dispatch = 3;
    new_alarm->execute = 0;

    //Gather time input from user
     // 24-hour time
    puts("\nUse 24 hr formating for the following entries:\n");
    // Allow user to enter the hour
    puts("\nEnter The Hours:\n");
    puts(">");
    // Hour buffer
    char hour[3] = {0};
    // Read in the hour
    sys_req(READ, COM1, hour, 3);
    // Validate hour
    int hour_valid = isNum(hour);
    if (hour_valid == 0)
    {
            puts("\nInvalid time, Please select a new option");
            return;
    }
    // Convert the hour to int
    int hr = atoi(hour);
    // Check if hour is greater than 24
    if (hr > 24)
    {
            puts("\nInvalid time, Please select a new option");
            return;
    }
    // Allow user to enter the minutes
    puts("\nEnter The Minutes:\n");
    puts(">");
    // Minute buffer
    char minute[3] = {0};
    // Read in the minute
    sys_req(READ, COM1, minute, 3);
    // Validate minute
    int minute_valid = isNum(minute);
    if (minute_valid == 0)
    {
            puts("\nInvalid time, Please select a new option");
            return;
    }
    // Convert minute to int
    int min = atoi(minute);
    if (min > 59)
    {
            puts("\nInvalid time, Please select a new option");
            return;
    }
    // Allow user to enter the seconds
    puts("\nEnter The Seconds:\n");
    puts(">");
    // Second buffer
    char second[3] = {0};
    // Read in the second
    sys_req(READ, COM1, second, 3);
    // Validate second
    int second_valid = isNum(second);
    if (second_valid == 0)
    {
            puts("\nInvalid time, Please select a new option");
            return;
    }
    // Convert second to int
    int sec = atoi(second);
    if (sec > 59)
    {
            puts("\n Invalid time, Please select a new option");
            return;
    }

    //After validating, set the time to the alarm
    new_alarm->hour = hr;
    new_alarm->min = min;
    new_alarm->sec = sec;

    //Need alarm name
    puts("\n Please input a name for your alarm\n");
    puts(">");
    char name[10]= {0};
    sys_req(READ, COM1, name, 10);

    
    for (int i = 0; i < 8 && name[i] != '\0'; i++)
    {
        new_alarm->name_arr[i] = name[i];
    }

    //Need alarm message
    puts("\n Please input the message you would like to display with your alarm\n");
    puts(">");
    char message[100] = {0};
    sys_req(READ, COM1, message, 100);

    
    for (int j = 0; j < 98 && message[j] != '\0'; j++)
    {
        new_alarm->message[j] = message[j];
    }

    //Add alarm to queue

}
void insert_alarm(struct alarm *alarm){
    if (alarm->dispatch == 3 && alarm->execute == 0)
    {
        // Case 1: Head is NULL 
        if (alarm_head == NULL)
        {
            // Insert at beginning
            alarm->next = alarm_head;
            alarm_head = alarm;
        }
        // Case 2:alarms are in the queue
        else
        {
            // Traverse the list to find the proper position
            struct alarm *current = alarm_head;

            while (current->next != NULL)
            {
                current = current->next;
            }
            // Insert after current
            alarm->next = current->next;
            current->next = alarm;
        }
    }
}

