#include <float.h>
#include <iso646.h>
#include <limits.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdnoreturn.h>
#include <sys_req.h>
#include <string.h>
#include <version.h>
#include <stdlib.h>
#include <shutdown.h>
#include <get_date.h>
#include <get_time.h>
#include <set_date.h>
#include <itoa.h>
#include <set_time.h>
#include <isdigit.h>
#include <help.h>
#include <mpx/io.h>
#include <memory.h>
#include <mpx/interrupts.h>
#include <mpx/serial.h>
#include <PCBcommands.h>
#include <PCB.h>
#include <r4.h>
#include <mpx/registers.h>

#define BLK "\033[0;30m"
#define RED "\033[0;31m" // errors and Y on shutdown
#define GRN "\033[0;32m" // N on shutdown
#define YEL "\033[0;33m" // version
#define BLU "\033[0;34m" // get date or time
#define MAG "\033[0;35m" // ascii art
#define CYN "\033[0;36m" // set date or time
#define WHT "\033[0;37m"

// alarm queue- add in alarm here after time and message are given by user, global variable
alarmQ *alarms;
int exit;

void add_to_queue(alarm *insert)
{

    if (alarms == NULL)
    {
        alarms = ((sys_alloc_mem(sizeof(*alarms))));
        alarms->front = NULL;
        alarms->rear = NULL;
    }

    alarmQ *temporary = alarms;

    if (insert == NULL)
    {
        put("Queue is empty\n");
        return;
    }

    if (temporary->rear != NULL)
    {
        temporary->rear->next = insert;
        insert->prev = temporary->rear;
        temporary->rear = insert;
    }
    else
    {
        temporary->front = insert;
        temporary->rear = insert;
    }
}

void remove_from_queue(alarm *remove)
{

    alarmQ *temporary = alarms;

    // if nothing on the queue
    if (temporary->front == NULL || remove == NULL)
    {
        // error
        return;
    }

    // removing from head
    if (temporary->front == remove)
    {
        temporary->front = remove->next;
    }

    // removing from tail
    if (temporary->rear == remove)
    {
        temporary->rear = remove->prev;
    }

    // removing from middle
    // check
    if (remove->next != NULL)
    {
        // move
        remove->next->prev = remove->prev;
    }

    if (remove->prev != NULL)
    {
        remove->prev->next = remove->next;
    }

    remove->prev = NULL;
    remove->next = NULL;
}

void create_alarm()
{

    // • Command (which must spawn a separate ready, non-suspended process!) to display a message at a certain time with two parameters
    // • Time – When to display the message • Message – The message to display
    // • Process should be idle before the specified time
    // • If the current time matches the requested time or later, display the message
    // and exit the process – it is OK for alarms to trigger late, but never early
    // • It should be possible to have multiple Alarm processes running concurrently

    alarm *new_alarm = ((sys_alloc_mem(sizeof(*new_alarm))));

    // SET TIME CODE
    int minute_int = 0;
    int second_int = 0;
    int hour_int = 0;

    char *error_message1 = "\nInvalid input, please enter DIGITS only! Or type Ctrl-c to exit.\n";
    char *error_message2 = "\nInvalid input, please enter two digit values within the range only! Or type Ctrl-c to exit.\n";

    char *hour_prompt = "\nEnter the current hour for the alarm to go off (0 to 23):\n";
    char hour_buff[4];
    put(hour_prompt);
    sys_req(READ, COM1, hour_buff, sizeof(hour_buff)); // reads user input

    hour_int = atoi(hour_buff);
    while (1)
    {
        if (hour_int > 23 || hour_int < 0 || isdigit(hour_buff) == 0 || strlen(hour_buff) >= 3)
        {

            put(RED); // Changes text color to red

            if (isdigit(hour_buff) == 0)
            {
                put(error_message1);
            }

            if (hour_int > 23 || hour_int < 0 || strlen(hour_buff) >= 3)
            {

                put(error_message2);
            }

            put(WHT); // Changes text color to white

            put("\n");
            memset(hour_buff, '\0', sizeof(hour_buff));        // clears buffer
            exit = sys_req(READ, COM1, hour_buff, sizeof(hour_buff)); // reads user input
            if(exit == -1){
                return;
            }

            hour_int = atoi(hour_buff);
        }
        else
        {
            break;
        }
    }

    new_alarm->hour = hour_int;

    char *minute_prompt = "\nEnter the current minute (0 to 59) for the alarm to go off:\n";
    char minute_buff[4];
    put(minute_prompt);
    sys_req(READ, COM1, minute_buff, sizeof(minute_buff));

    minute_int = atoi(minute_buff);

    while (1)
    {
        if (minute_int >= 60 || minute_int < 0 || isdigit(minute_buff) == 0 || strlen(minute_buff) >= 3)
        {

            put(RED);

            if (isdigit(minute_buff) == 0)
            {
                put(error_message1);
            }

            if (minute_int >= 60 || minute_int < 0 || strlen(minute_buff) >= 3)
            {
                put(error_message2);
            }

            put(WHT);

            put("\n");
            memset(minute_buff, '\0', sizeof(minute_buff));
             exit = sys_req(READ, COM1, minute_buff, sizeof(minute_buff));
            if(exit == -1){
                return;
            }
            minute_int = atoi(minute_buff);
        }
        else
        {
            break;
        }
    }

    new_alarm->minute = minute_int;

    char *second_prompt = "\nEnter the current second (0 to 59) for the alarm to go off:\n";
    char second_buff[4];
    put(second_prompt);
    sys_req(READ, COM1, second_buff, sizeof(second_buff));

    second_int = atoi(second_buff);

    while (1)
    {
        if (second_int >= 60 || second_int < 0 || isdigit(second_buff) == 0 || strlen(second_buff) >= 3)
        {

            put(RED);

            if (isdigit(second_buff) == 0)
            {
                put(error_message1);#include <../include/dateAndTime.h>
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
#include <../include/mpx/r4.h>
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
    command_handler();
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

            }

            if (second_int >= 60 || second_int < 0 || strlen(second_buff) >= 3)
            {

                put(error_message2);
            }

            put(WHT);

            put("\n");
            memset(second_buff, '\0', sizeof(second_buff));
            exit = sys_req(READ, COM1, second_buff, sizeof(second_buff));
            if(exit == -1){
                return;
            }
            second_int = atoi(second_buff);
        }
        else
        {
            break;
        }
    }
    put("\n");
    put("The alarm time set is given in Military Time (UTC)\n");
    put(CYN);
    // if hour_buff size is 1 prefix hour with 0
    if (strlen(hour_buff) == 1)
    {
        put("0");
    }

    put(hour_buff);

    put(":");

    if (strlen(minute_buff) == 1)
    {
        put("0");
    }

    put(minute_buff);

    put(":");

    if (strlen(second_buff) == 1)
    {
        put("0");
    }

    put(second_buff);
    put("\n");
    put(WHT);

    new_alarm->second = second_int;

    // ends set time code

    // Prompt user to enter alarm name
    // char *name_prompt = "\n Enter a name for the alarm: \n";
    // char name_buff[50];
    // put("\n");
    // put(name_prompt);
    // sys_req(READ, COM1, name_buff, sizeof(name_buff)); // reads user input

    // Prompt user to enter message
    char *message_prompt = "\nEnter the message to be printed when the alarm goes off: \n";
    char message_buff[100];
    put(message_prompt);
    sys_req(READ, COM1, message_buff, sizeof(message_buff)); // reads user input

    strcpy(message_buff, new_alarm->message);

    // add in alarm to alarm queue- global- need one process to handle alarms
    // can do priority based

    add_to_queue(new_alarm);

    alarmProc();
}

void alarm_process()
{

    // process runs infinite loop -each time it checks for any alarms that need to br peinted, print them, remove from queue, then idle
    //   add in process to ready queue using same way as r3 with creating processes
    //  process- process i create that handles alarms- only do this once- the first time you run alarm
    //  if I have already created process, that one runs. If not, make the process

    // create my own process function that checks time, prints message, and deletes from queue, then calls sys call idle
    // does all this in infinite loop
    while (1)
    {
        alarmQ *temporary = alarms;
        alarm *new_alarm = temporary->front;

        // GET TIME CODE- goes in process

        // read seconds
        outb(0x70, 0x00);        // Writes to the RTC index register for seconds
        int bcd_sec = inb(0x71); // reads bcd seconds value from RTC data register

        // read minutes
        outb(0x70, 0x02);
        int bcd_min = inb(0x71);

        // read hours
        outb(0x70, 0x04);
        int bcd_hour = inb(0x71);

        // convert all to decimal
        int dec_sec = bcd_to_dec(bcd_sec);

        int dec_min = bcd_to_dec(bcd_min);

        int dec_hour = bcd_to_dec(bcd_hour);

        while (new_alarm != NULL)
        {

            int entered_hour = new_alarm->hour;
            int entered_min = new_alarm->minute;
            int entered_sec = new_alarm->second;

            // • If the current time matches the requested time or later, display the message
            // and exit the process – it is OK for alarms to trigger late, but never early
            if (entered_hour < dec_hour || (entered_hour == dec_hour && entered_min < dec_min) || (entered_hour == dec_hour && entered_min == dec_min && entered_sec <= dec_sec))
            {
                // once you hit the time, write message and remove
                put("\n");
                put(new_alarm->message);
                put("\n");
                remove_from_queue(new_alarm);
                sys_req(EXIT, COM1, NULL, NULL);
            }
            // while it is less than specified time - use get time- continue to idle
            new_alarm = new_alarm->next;
        }
        sys_req(IDLE, COM1, NULL, NULL);
    }
}

void alarmProc()
{
    // create process just like I did for r3 processes

    char *name = "alarm1";
    char *pcbName = "alarm1";

    for (int cat = 1; pcb_find(name) != NULL; cat++)
    {
        int i;
        for (i = 0; name[i] != '\0'; i++)
        {
            pcbName[i] = name[i];
        }
        pcbName[i-1] = *itoa(cat);
        pcbName[i + 1] = '\0';
    }

    pcb *newPcb = pcb_setup(pcbName, 0, 9);
    newPcb->state = 0;
    newPcb->sus_state = 0;
    // commented because defined it in pcb setup
    // newPcb->topofstack = (newPcb->stack) + 1024 - sizeof(reg);
    reg *context = (reg *)newPcb->topofstack;
    memset(context, 0, sizeof(reg));

    // segments
    context->CS = 0x08;
    context->FS = 0x10;
    context->GS = 0x10;
    context->DS = 0x10;
    context->ES = 0x10;
    context->SS = 0x10;

    // general
    context->EBP = (uint32_t)newPcb->stack;
    context->EAX = 0;
    context->EBX = 0;
    context->ECX = 0;
    context->EDX = 0;
    context->ESI = 0;
    context->EDI = 0;

    // status
    context->EFLAGS = 0x0202;
    context->EIP = (uint32_t)alarm_process;

    pcb_insert(newPcb);
}

// somewhere we need to call alarm proc, in kmain or commhand, in commhand

// i