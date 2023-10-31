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
#include <alarm.h>
#include <../include/mpx/ISRuser.h>

alarm *alarm_head = NULL;
//pcb *ready_head = NULL;

struct alarm *create_alarm(){

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
    yield();
    sys_req(READ, COM1, hour, 3);
    // Validate hour
    int hour_valid = isNum(hour);
    if (hour_valid == 0)
    {
            puts("\nInvalid time, Please select a new option");
            return NULL;
    }
    // Convert the hour to int
    int hr = atoi(hour);
    // Check if hour is greater than 24
    if (hr > 24)
    {
            puts("\nInvalid time, Please select a new option");
            return NULL;
    }
    // Allow user to enter the minutes
    puts("\nEnter The Minutes:\n");
    puts(">");
    // Minute buffer
    char minute[3] = {0};
    // Read in the minute
    yield();
    sys_req(READ, COM1, minute, 3);
    // Validate minute
    int minute_valid = isNum(minute);
    if (minute_valid == 0)
    {
            puts("\nInvalid time, Please select a new option");
            return NULL;
    }
    // Convert minute to int
    int min = atoi(minute);
    if (min > 59)
    {
            puts("\nInvalid time, Please select a new option");
            return NULL;
    }
    // Allow user to enter the seconds
    puts("\nEnter The Seconds:\n");
    puts(">");
    // Second buffer
    char second[3] = {0};
    // Read in the second
    yield();
    sys_req(READ, COM1, second, 3);
    // Validate second
    int second_valid = isNum(second);
    if (second_valid == 0)
    {
            puts("\nInvalid time, Please select a new option");
            return NULL;
    }
    // Convert second to int
    int sec = atoi(second);
    if (sec > 59)
    {
            puts("\n Invalid time, Please select a new option");
            return NULL;
    }

    //After validating, set the time to the alarm
    new_alarm->hour = hr;
    new_alarm->min = min;
    new_alarm->sec = sec;

    //Need alarm name
    puts("\n Please input a name for your alarm\n");
    puts(">");
    char name[10]= {0};
    yield();
    sys_req(READ, COM1, name, 10);

    
    for (int i = 0; i < 8 && name[i] != '\0'; i++)
    {
        new_alarm->name_arr[i] = name[i];
    }

    //Need alarm message
    puts("\n Please input the message you would like to display with your alarm\n");
    puts(">");
    char message[100] = {0};
    yield();
    sys_req(READ, COM1, message, 100);

    
    for (int j = 0; j < 98 && message[j] != '\0'; j++)
    {
        new_alarm->message[j] = message[j];
    }

    //Add alarm to queue
    insert_alarm(new_alarm);

    pcb *test = pcb_find(new_alarm->name_arr);
    if (test == NULL){
        puts("failure");
    }else{
        puts("pcb was created");
    }

    return new_alarm;
}
void insert_alarm(alarm *alarm){
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
    else{
        puts("Could not insert alarm.");
        return;
    }
}

void remove_alarm(alarm *old_alarm){

     if (old_alarm->dispatch == 3 && old_alarm->execute == 0)
    {
        // Case 1: Head is NULL
        if (alarm_head == NULL)
        {
            // There is nothing in the list, how did we get here?
            puts("There are no alarms currently in the queue");
        }
        // Case 2: Head is not NULL
        else
        {
            // Traverse the list to find the alarm and it's previous node
            struct alarm *current = alarm_head;
            struct alarm *prev = NULL;

            while (current != NULL && strcmp(current->name_arr, alarm_head->name_arr))
            {
                prev = current;
                current = current->next;
            }

            // If we found the alarm to remove
            if (current != NULL)
            {
                if (prev != NULL)
                {
                    // The alarm is not the head
                    prev->next = current->next;
                    return;
                }
                else
                {
                    // The alarm is the head
                    alarm_head = current->next;
                    return;
                }
            }
        }
    }
}
void check_alarm(alarm *alarm){
    //get actual time from registers

     // read from register
    outb(0x70, 0x00);
    unsigned char seconds = inb(0x71);
    // get ones place of seconds
    int ones_sec = (seconds & 0x0F);
    // get tens place of seconds
    int tens_sec = seconds / 16;
    // combine
    int seconds_fr = (tens_sec * 10) + ones_sec;
    // convert to string
    char secs[3];
    itoa(seconds_fr, secs, 10);

    // read from register
    outb(0x70, 0x02);
    unsigned char minutes = inb(0x71);
    // get ones place of minutes
    int ones_min = (minutes & 0x0F);
    // get tens place of minutes
    int tens_min = minutes / 16;
    // combine
    int minutes_fr = (tens_min * 10) + ones_min;
    // convert to string
    char mins[3];
    itoa(minutes_fr, mins, 10);

    // read from register
    outb(0x70, 0x04);
    unsigned char hours = inb(0x71);
    // get ones place of hours
    int ones_hr = (hours & 0x0F);
    // get tens place of hours
    int tens_hr = hours / 16;
    // combine
    int hours_fr = (tens_hr * 10) + ones_hr;
    // convert to string
    char hrs[3];
    itoa(hours_fr, hrs, 10);

    while(alarm != NULL){
    //Check is actual time is the time of the alarm
    if(alarm->hour < hours_fr || (alarm->hour == hours_fr && alarm->min < minutes_fr) || (alarm->hour == hours_fr && alarm->min == minutes_fr && alarm->sec <= seconds_fr)){
        //Need to display the message 
        puts("\n");
        puts(alarm->message);
        puts("\n");
        //remove alarm from the queue
        remove_alarm(alarm);
        //Exit process
        sys_req(EXIT, COM1, NULL, NULL);
        }

        //Move to next alarm
        alarm = alarm->next;
    }
    
    //Remains idle
      sys_req(IDLE,COM1,NULL,NULL);
}

void alarm_process(){

        //Create alarm process
        alarm *new_alarm = create_alarm();
    
        context *context1 = (context *) new_alarm->stack_ptr;
        memset(context1, 0, sizeof(context));

        //Segments
        context1->CS = (unsigned int)0x08;
        context1->DS = (unsigned int)0x10;   
        context1->ES = (unsigned int)0x10;   
        context1->FS = (unsigned int)0x10;   
        context1->GS = (unsigned int)0x10;   
        context1->SS = (unsigned int)0x10;  
        //Registers
        context1->EBP = (unsigned int) new_alarm->stack;
        context1->EAX = (unsigned int) 0x00; 
        context1->EBX = (unsigned int) 0x00; 
        context1->ECX = (unsigned int) 0x00; 
        context1->EDX = (unsigned int) 0x00; 
        context1->EBP = (unsigned int) 0x00; 
        context1->ESI = (unsigned int) 0x00; 
        context1->EDI = (unsigned int) 0x00; 
        //Flags
        context1->EIP = (unsigned int) proc1;  
        context1->EFLAGS =(unsigned int)0x0202;

        //insert alarm into alarm queue
        insert_alarm(new_alarm);
        check_alarm(new_alarm);
}
void show_alarms(void)
{
    // check through the blocked queue
    struct alarm *current_alarm = alarm_head;
    char num[10];

    puts("\nAlarm Queue:\n");
    if (current_alarm == NULL)
    {
        puts("\nAlarm Queue is Empty\n");
    }
    else
    {
        puts("Format: Name, State, Status, Time Set, Message \n");
        while (current_alarm != NULL)
        {
            puts(current_alarm->name_arr);
            puts(", ");
            itoa(current_alarm->execute, num, 10);
            puts(num);
            puts(", ");
            itoa(current_alarm->dispatch, num, 10);
            puts(num);
            puts(", ");
            itoa(current_alarm->hour, num, 10);
            puts(num);
            puts(":");
            itoa(current_alarm->min, num, 10);
            puts(num);
            puts(":");
            itoa(current_alarm->sec, num, 10);
            puts(num);
            puts(", ");
            puts(current_alarm->message);
            puts("\n");

            current_alarm = current_alarm->next;
        }
    }
    
    
}
