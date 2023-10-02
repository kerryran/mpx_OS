#include <../include/sys_req.h>
#include <../include/string.h>
#include <stdbool.h>
#include <mpx/serial.h>
#include <../include/dateAndTime.h>
#include <stdlib.h>
#include <../include/pcbuser.h>
#include <../include/mpx/pcb.h>
void comhand(void)
{
        // Welcome/Start-Up Message
        puts("\nWelcome to\n");
        puts("   _____                               ___  ____   \n");
        puts("  |  ___| __ ___   __ _  __ _ _   _   / _ \\/ ___|  \n");
        puts("  | |_ | '__/ _ \\ / _` |/ _` | | | | | | | \\___ \\  \n");
        puts("  |  _|| | | (_) | (_| | (_| | |_| | | |_| |___) | \n");
        puts("  |_|  |_|  \\___/ \\__, |\\__, |\\__, |  \\___/|____/  \n");
        puts("                  |___/ |___/ |___/                \n");
        puts("      _    _          _    _          _    _\n");
        puts("     (o)--(o)        (o)--(o)        (o)--(o)\n");
        puts("    /.______.\\      /.______.\\      /.______.\\\n");
        puts("    \\________/      \\________/      \\________/\n");
        puts("   ./        \\.    ./        \\.    ./        \\.\n");
        puts("  ( .        , )  ( .        , )  ( .        , )\n");
        puts("   \\ \\_\\\\//_/ /    \\ \\_\\\\//_/ /    \\ \\_\\\\//_/ /\n");

        puts("\n                  Developed by\n");
        puts("   _____                ____                        _  \n");
        puts("  |  ___| __ ___   __ _/ ___|  __ _ _   _  __ _  __| | \n");
        puts("  | |_ | '__/ _ \\ / _` \\___ \\ / _` | | | |/ _` |/ _` | \n");
        puts("  |  _|| | | (_) | (_| |___) | (_| | |_| | (_| | (_| | \n");
        puts("  |_|  |_|  \\___/ \\__, |____/ \\__, |\\__,_|\\__,_|\\__,_| \n");
        puts("                  |___/          |_|                   ");

        while (true)
        {
                // Main Menu Prompt
                puts("\nMain Menu:\n");
                puts("1) Help\n2) Version\n3) Date & Time\n4) Process\n5) Quit\n");
                puts("Enter a number to select:\n");
                puts(">");

                // Input buffer
                char buffer[4] = {0};
                // Read from the buffer
                sys_req(READ, COM1, buffer, 4);

                // Print out help menu
                if (strcmp(buffer, "1") == 0)
                {
                        puts("\nCommands:\ni. Help - describes all the available commands.\n");
                        puts("i. Version - describes the operating system version.\n");
                        puts("i. Date & Time - Opens the date & time menu.\n");
                        puts("ii. Get Date - Displays the current date.\n");
                        puts("ii. Set Date - Allows user to set the date MM/DD/YY.\n");
                        puts("ii. Get Time - Displays the current time.\n");
                        puts("ii. Set Time - Allows user to set the time.\n");
                        puts("i. Process - Opens the process menu.\n");
                        puts("ii. Manage - Opens the Manage PCB Menu.\n");
                        puts("iii. Create PCB - Allows user to create a new process by entering a name followed by a \nclass (0 for system-level 1 for user-level) followed by a priority (highest 0-9 lowest).\n");
                        puts("iii. Delete PCB - Takes name input from user and deletes that process.\n");
                        puts("iii. Block PCB - Takes name input from the user and blocks that process.\n");
                        puts("iii. UnBlock PCB - Takes name input from the user and unblocks that process.\n");
                        puts("iii. Suspend PCB - Takes name input from the user and suspends that process.\n");
                        puts("iii. Resume PCB - Takes name input from the user and resumes that process.\n");
                        puts("iii. Set PCB Priority - Takes name input from the user and then an integer input \n(highest 0 to 9 lowest) to set process priority.\n");
                        puts("ii. View - Opens the View PCB Menu.\n");
                        puts("iii. Show PCB - Allows user to enter a name to search for a pcb and displays its information.\n");
                        puts("iii. Show Ready - Displays ready PCBs.\n");
                        puts("iii. Show Blocked - Displays blocked PCBs.\n");
                        puts("iii. Show All - Displays information about all PCBs.\n");
                        puts("i. Quit - Logs the user out.\n");
                }
                // Print out version number
                else if (strcmp(buffer, "2") == 0)
                {
                        puts("\nVersion: 2.1 (now with frogs!)\n");
                }
                // Print out Date and Time Menu
                else if (strcmp(buffer, "3") == 0)
                {
                        puts("\nDate & Time Menu:");
                        puts("\n1) Get Date\n2) Set Date\n3) Get Time\n4) Set Time\n5) Back\n");
                        puts(">");
                        // Choice buffer
                        char choice[5] = {0};
                        // Read from the buffer
                        sys_req(READ, COM1, choice, 5);
                        // Print out: Get Date
                        if (strcmp(choice, "1") == 0)
                        {
                                puts("The date is: ");
                                get_date();
                        }
                        // Allow user to set the date
                        else if (strcmp(choice, "2") == 0)
                        {
                                // Allow user to enter the year
                                puts("\nEnter The Year:\n");
                                puts(">");
                                // Year buffer
                                char year[3] = {0};
                                // Read year from user
                                sys_req(READ, COM1, year, 3);
                                // Validate year from user
                                int year_valid = isNum(year);
                                if (year_valid == 0)
                                {
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                }
                                // Convert year to an integer
                                int y = atoi(year);
                                // Check if year is a leap year
                                if ((y % 4) == 0 && (y % 100) != 0)
                                {
                                        // Allow user to enter month
                                        puts("\nEnter The Month:\n");
                                        puts(">");
                                        // Month buffer
                                        char month[3] = {0};
                                        // Read in month from the user
                                        sys_req(READ, COM1, month, 3);
                                        // Validate month
                                        int month_valid = isNum(month);
                                        if (month_valid == 0)
                                        {
                                                puts("\nInvalid date, Please select a new option");
                                                continue;
                                        }
                                        // Convert month to int
                                        int m = atoi(month);
                                        // Check if month is February
                                        if (m == 2)
                                        {
                                                // Allow user to enter the day
                                                puts("\nEnter The Day:\n");
                                                puts(">");
                                                // Day buffer
                                                char day[3] = {0};
                                                // Read in the day
                                                sys_req(READ, COM1, day, 3);
                                                // Validate day
                                                int day_valid = isNum(day);
                                                if (day_valid == 0)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Cnvert day to int
                                                int d = atoi(day);
                                                // Check if February has more than 29 days (Leap year)
                                                if (d > 29)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Set date with valid inputs
                                                set_date(d, m, y);
                                        }
                                        // Validate month is not larger than 12
                                        else if (m > 12)
                                        {
                                                puts("\nInvalid date, Please select a new option");
                                                continue;
                                        }
                                        // Check if month entered has 31 days
                                        else if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
                                        {
                                                // Allow user to enter the day
                                                puts("\nEnter The Day:\n");
                                                puts(">");
                                                // Day buffer
                                                char day[3] = {0};
                                                // Read in day
                                                sys_req(READ, COM1, day, 3);
                                                // Validate day
                                                int day_valid = isNum(day);
                                                if (day_valid == 0)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Convert day to int
                                                int d = atoi(day);
                                                // Make sure day is greater than 31
                                                if (d > 31)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Set date with valid inputs
                                                set_date(d, m, y);
                                        }
                                        else
                                        {
                                                // If here, the month must contain only 30 days
                                                // Allow user to enter day
                                                puts("\nEnter The Day:\n");
                                                puts(">");
                                                // Day buffer
                                                char day[3] = {0};
                                                // Read in day
                                                sys_req(READ, COM1, day, 3);
                                                // Validate day
                                                int day_valid = isNum(day);
                                                if (day_valid == 0)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Convert day to int
                                                int d = atoi(day);
                                                // Check if day is greater than 30
                                                if (d > 30)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Set date with valid inputs
                                                set_date(d, m, y);
                                        }
                                }
                                else
                                {
                                        // If here, the year is not a Leap Year
                                        // Allow user to enter the month
                                        puts("\nEnter The Month:\n");
                                        puts(">");
                                        // Month buffer
                                        char month[3] = {0};
                                        // Read in month
                                        sys_req(READ, COM1, month, 3);
                                        // Validate month
                                        int month_valid = isNum(month);
                                        if (month_valid == 0)
                                        {
                                                puts("\nInvalid date, Please select a new option");
                                                continue;
                                        }
                                        // Convert month to int
                                        int m = atoi(month);
                                        // Check if month is February
                                        if (m == 2)
                                        {
                                                // Allow user to enter the day
                                                puts("\nEnter The Day:\n");
                                                puts(">");
                                                // Day buffer
                                                char day[3] = {0};
                                                // Read in day
                                                sys_req(READ, COM1, day, 3);
                                                // Validate day
                                                int day_valid = isNum(day);
                                                if (day_valid == 0)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Convert day to int
                                                int d = atoi(day);
                                                // Check if day is greater than 28
                                                if (d > 28)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Set date with valid inputs
                                                set_date(d, m, y);
                                        }
                                        // Check if month is greater than 12
                                        else if (m > 12)
                                        {
                                                puts("\nInvalid date, Please select a new option");
                                                continue;
                                        }
                                        // Check if month has 31 days
                                        else if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
                                        {
                                                // Allow user to enter the day
                                                puts("\nEnter The Day:\n");
                                                puts(">");
                                                // Day buffer
                                                char day[3] = {0};
                                                // Read in day
                                                sys_req(READ, COM1, day, 3);
                                                // Validate day
                                                int day_valid = isNum(day);
                                                if (day_valid == 0)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Convert day to int
                                                int d = atoi(day);
                                                // Check if day is greater than 31
                                                if (d > 31)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Set date with valid inputs
                                                set_date(d, m, y);
                                        }
                                        else
                                        {
                                                // If here, month must have 30 days
                                                // Allow user to enter day
                                                puts("\nEnter The Day:\n");
                                                puts(">");
                                                // Day buffer
                                                char day[3] = {0};
                                                // Read in day
                                                sys_req(READ, COM1, day, 3);
                                                // Validate day
                                                int day_valid = isNum(day);
                                                if (day_valid == 0)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Convert day to int
                                                int d = atoi(day);
                                                // Check if day is greater than 30
                                                if (d > 30)
                                                {
                                                        puts("\nInvalid date, Please select a new option");
                                                        continue;
                                                }
                                                // Set date with valid inputs
                                                set_date(d, m, y);
                                        }
                                }
                        }
                        // Print out: Get Time
                        else if (strcmp(choice, "3") == 0)
                        {
                                // Display time in UTC time zone
                                puts("The time in UTC is: ");
                                get_time();
                        }
                        // Allow user to set the time
                        else if (strcmp(choice, "4") == 0)
                        {
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
                                        continue;
                                }
                                // Convert the hour to int
                                int hr = atoi(hour);
                                // Check if hour is greater than 24
                                if (hr > 24)
                                {
                                        puts("\nInvalid time, Please select a new option");
                                        continue;
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
                                        continue;
                                }
                                // Convert minute to int
                                int min = atoi(minute);
                                if (min > 59)
                                {
                                        puts("\nInvalid time, Please select a new option");
                                        continue;
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
                                        continue;
                                }
                                // Convert second to int
                                int sec = atoi(second);
                                if (sec > 59)
                                {
                                        puts("\n Invalid time, Please select a new option");
                                        continue;
                                }
                                // Set time with valid inputs
                                set_time(hr, min, sec);
                        }
                        // Go Back
                        else if (strcmp(choice, "5") == 0)
                        {
                                continue;
                        }
                        else
                        {
                                puts("\nUnrecognized command.\n");
                        }
                }
                // PCB Menu

                else if (strcmp(buffer, "4") == 0)
                {
                        puts("\nPCB Menu");
                        puts("\n1) Manage\n2) View\n3) Back\n");
                        puts(">");
                        char choice[5] = {0};
                        // Read from the buffer
                        sys_req(READ, COM1, choice, 5);

                        if (strcmp(choice, "1") == 0)
                        {
                                puts("\nManage PCB Menu:");
                                puts("\n1) Create PCB\n2) Delete PCB\n3) Block PCB\n4) Unblock PCB\n5) Suspend PCB\n6) Resume PCB\n7) Set PCB Priority\n8) Back\n");

                                puts(">");
                                char choice[5] = {0};
                                // Read from the buffer
                                sys_req(READ, COM1, choice, 5);

                                if (strcmp(choice, "1") == 0)
                                {
                                        // Show Pcb Menu
                                        puts("\nType PCB Name:");
                                        // required for UI
                                        puts(">");
                                        // init choice buffer
                                        char choice[5] = {0};
                                        // Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        puts("\nType PCB Class:");
                                        // required for UI
                                        puts(">");
                                        // init class buffer
                                        char class[5] = {0};
                                        int class_valid = isNum(class);
                                        if (class_valid == 0)
                                        {
                                                puts("\nInvalid");
                                                continue;
                                        }
                                        // Convert class to an integer
                                        sys_req(READ, COM1, class, 5);
                                        int classInt = atoi(class);
                                        // Read from the buffer

                                        puts("\nType PCB Priority:");
                                        // required for UI
                                        puts(">");
                                        // init priority buffer
                                        char priority[5] = {0};
                                        int priority_valid = isNum(priority);
                                        if (priority_valid == 0)
                                        {
                                                puts("\nInvalid");
                                                continue;
                                        }
                                        // Convert class to an integer
                                        sys_req(READ, COM1, priority, 5);
                                        int priorityInt = atoi(priority);
                                        // Read from the buffer
                                        //Read from the buffer
                                        //has errors, checking for 

                                        //goes here if its a valid entry
                                        
                                        if (((strcmp(class,"0") == 0) || (strcmp(class,"1")==0)) && ((strcmp(choice,"")!=0))){

                                        
                                         if(strcmp(class,"0") == 0 ){
                                                //goes here if class is 0 (system process)
                                                 puts("You are about to create a system process. This action cannot be undone without restarting the system.");
                                                 puts("\nConfirm:");
                                                 puts("\n1) Yes");
                                                 puts("\nAny) Cancel");
                                                 puts("\n>");
                                                 char confirm[5] = {0};
                                                 // Read from the buffer
                                                 sys_req(READ, COM1, confirm, 5);

                                                 if (strcmp(confirm, "1") == 0)
                                                 {
                                                         pcb_create(choice, classInt, priorityInt);
                                                 }
                                                 else{
                                                         puts("Action canceled");
                                                         continue;
                                                 }
                                         }
                                         else{
                                                pcb_create(choice, classInt, priorityInt);
                                         }
                                         
                                         
                                        }
                                        //invalid entry
                                        else{
                                                puts("Action canceled");
                                        }
                                        
                                                
                                }
                                else if (strcmp(choice, "2") == 0)
                                {
                                        // Delete Pcb Menu
                                        puts("\nEnter PCB Name:");
                                        // required for UI
                                        puts(">");
                                        // init choice buffer
                                        char choice[5] = {0};
                                        // Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        // PCB 1
                                        pcb_delete(choice);
                                }
                                else if (strcmp(choice, "3") == 0)
                                {
                                        // Block Pcb Menu
                                        puts("\nEnter PCB to Block:");
                                        // required for UI
                                        puts(">");
                                        // init choice buffer
                                        char choice[5] = {0};
                                        // Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        pcb_block(choice);
                                }
                                else if (strcmp(choice, "4") == 0)
                                {
                                        // Block Pcb Menu
                                        puts("\nEnter PCB to UnBlock:");
                                        // required for UI
                                        puts(">");
                                        // init choice buffer
                                        char choice[5] = {0};
                                        // Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        // PCB 1
                                        pcb_unblock(choice);
                                }
                                else if (strcmp(choice, "5") == 0)
                                {
                                        // Suspend Pcb Menu
                                        puts("\nType PCB to Suspend:");
                                        // required for UI
                                        puts(">");
                                        // init choice buffer
                                        char choice[5] = {0};
                                        // Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        // PCB 1
                                        pcb_suspend(choice);
                                }
                                else if (strcmp(choice, "6") == 0)
                                {
                                        // Resume Pcb Menu
                                        puts("\nType PCB to Resume:");
                                        // required for UI
                                        puts(">");
                                        // init choice buffer
                                        char choice[5] = {0};
                                        // Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        // PCB 1
                                        pcb_resume(choice);
                                }
                                else if (strcmp(choice, "7") == 0)
                                {
                                        // Change Pcb Priority Menu
                                        puts("\nChoose PCB to Change Priority:");
                                        // Choices Go Here
                                        puts("\nType PCB Name:");
                                        // required for UI
                                        puts(">");
                                        // init choice buffer
                                        char choice[5] = {0};
                                        // Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        struct pcb *pcb = pcb_find(choice);
                                        if (pcb == NULL)
                                        {
                                                puts("PCB does not exist.\n");
                                                continue;
                                        }
                                        puts("\nType PCB Priority:");
                                        // init choice buffer
                                        puts(">");
                                        // Read from the buffer

                                        char priority[5] = {0};
                                        sys_req(READ, COM1, priority, 5);
                                        int priority_valid = isNum(priority);
                                        if (priority_valid == 0)
                                        {
                                                puts("\nInvalid");
                                                continue;
                                        }

                                        // Convert priority to an integer
                                        int priorityInt = atoi(priority);

                                        if ((priorityInt < 0) || (priorityInt > 9))
                                        {
                                                puts("Invalid Priority");
                                                continue;
                                        }
                                        // uncomment when made
                                        set_priority(choice, priorityInt);
                                }
                        }
                        else if (strcmp(choice, "2") == 0)
                        {
                                puts("\nView PCB Menu:");
                                puts("\n1) Show PCB\n2) Show Ready\n3) Show Blocked\n4) Show All\n5) Back\n");
                                puts(">");
                                char choice[5] = {0};
                                // Read from the buffer
                                sys_req(READ, COM1, choice, 5);

                                if (strcmp(choice, "1") == 0)
                                {
                                        // Show Pcb Menu
                                        puts("\n Enter PCB to Show:");
                                        // required for UI
                                        puts(">");
                                        // init choice buffer
                                        char choice[5] = {0};
                                        // Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        // PCB 1
                                        show_pcb(choice);
                                }
                                else if (strcmp(choice, "2") == 0)
                                {
                                        show_ready();
                                }
                                else if (strcmp(choice, "3") == 0)
                                {
                                        show_blocked();
                                }
                                else if (strcmp(choice, "4") == 0)
                                {
                                        show_all();
                                }
                                else if (strcmp(choice, "5") == 0)
                                {
                                        continue;
                                }
                                else
                                {
                                        puts("\nUnrecognized command.\n");
                                }
                        }
                        else if (strcmp(choice, "3") == 0)
                        {
                                continue;
                        }
                        else
                        {
                                puts("\nUnrecognized command.\n");
                        }
                }

                // Shutdown
                else if (strcmp(buffer, "5") == 0)
                {
                        puts("\nAre you sure you want to shutdown?\n");
                        puts("1) Confirm\nAny-Key) Cancel\n");
                        puts(">");
                        // Confirm buffer
                        char confirm[5] = {0};
                        // Read in confirm
                        sys_req(READ, COM1, confirm, 5);
                        if (strcmp(confirm, "1") == 0)
                        {
                                puts("\nShutting Down...\n");
                                return;
                        }
                        else
                        {
                                puts("\nCanceled Shutdown...\n");
                                continue;
                        }
                }
                else
                {
                        puts("\nUnrecognized command.\n");
                }
        }
}
