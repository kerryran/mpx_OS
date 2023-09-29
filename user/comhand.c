#include <../include/sys_req.h>
#include <../include/string.h>
#include <stdbool.h>
#include <mpx/serial.h>
#include <../include/dateAndTime.h>
#include <stdlib.h>
#include <../include/pcbuser.h>
void comhand(void)
{
        // Welcome/Start-Up Message
        puts("\nWelcome to\n");
        puts(" _____                               ___  ____   \n");
        puts("|  ___| __ ___   __ _  __ _ _   _   / _ \\/ ___|  \n");
        puts("| |_ | '__/ _ \\ / _` |/ _` | | | | | | | \\___ \\  \n");
        puts("|  _|| | | (_) | (_| | (_| | |_| | | |_| |___) | \n");
        puts("|_|  |_|  \\___/ \\__, |\\__, |\\__, |  \\___/|____/  \n");
        puts("                |___/ |___/ |___/                \n");
        puts("\nDeveloped by\n");
        puts(" _____                ____                        _  \n");
        puts("|  ___| __ ___   __ _/ ___|  __ _ _   _  __ _  __| | \n");
        puts("| |_ | '__/ _ \\ / _` \\___ \\ / _` | | | |/ _` |/ _` | \n");
        puts("|  _|| | | (_) | (_| |___) | (_| | |_| | (_| | (_| | \n");
        puts("|_|  |_|  \\___/ \\__, |____/ \\__, |\\__,_|\\__,_|\\__,_| \n");
        puts("                |___/          |_|                   \n");

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
                        puts("\nCommands:\n1) Help - describes all the available commands.\n2) Version - describes the operating system version.\n3) Get Date -returns the system date.\n");
                        puts("4) Set Date - allows user to update the system date, format as MM/DD/YY.\n5) Get Time - returns the system time.\n6) Set Time - allows user to update the system time, format as HH:MM:SS\n");
                        puts("7) Quit - Logs user out of the machine.\n");
                }
                // Print out version number
                else if (strcmp(buffer, "2") == 0)
                {
                        puts("\nVersion: 2.0\n");
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
                                        //Show Pcb Menu
<<<<<<< HEAD
                                        puts("\nChoose PCB to Create:");
                                        //Choices Go Here
                                        puts("\n1) PCB 1 1\n2) PCB 2\n3) Back\n");
=======
                                        puts("\nType PCB Name:");
>>>>>>> main
                                        //required for UI
                                        puts(">");
                                        //init choice buffer
                                        char choice[5] = {0};
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
<<<<<<< HEAD
                                        //PCB 1
                                        if (strcmp(choice, "1") == 0)
                                        {
                                                pcb_create("pcb1", "pcb1Class", "pcb1Priority");
                                        }
                                        else if (strcmp(choice, "2") == 0)
                                        {
                                                pcb_create("pcb2", "pcb2Class", "pcb2Priority");
                                        }
                                        //keep, this is the back option for the inital menu, make 3 higher if you add more menus
                                        else if (strcmp(choice, "3") == 0)
                                        {
                                                continue;
                                        }
                                        else
                                        {
                                                puts("\nUnrecognized command.\n");
                                        }
=======
                                        puts("\nType PCB Class:");
                                        //required for UI
                                        puts(">");
                                        //init choice buffer
                                        char class[5] = {0};
                                        int class_valid = isNum(class);
                                        if (class_valid == 0)
                                        {
                                                puts("\nInvalid");
                                                continue;
                                        }
                                        // Convert year to an integer
                                        int classInt = atoi(class);
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        puts("\nType PCB Priority:");
                                        //required for UI
                                        puts(">");
                                        //init choice buffer
                                        char priority[5] = {0};
                                        int priority_valid = isNum(priority);
                                        if (priority_valid == 0)
                                        {
                                                puts("\nInvalid");
                                                continue;
                                        }
                                        // Convert year to an integer
                                        int priorityInt = atoi(priority);
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        pcb_create(choice, classInt, priorityInt);
                                        
>>>>>>> main
                                }
                                else if (strcmp(choice, "2") == 0)
                                {
                                        //Delete Pcb Menu
<<<<<<< HEAD
                                        puts("\nChoose PCB to Delete:");
                                        //Choices Go Here
                                        puts("\n1) PCB 1 1\n2) PCB 2\n3) Back\n");
=======
                                        puts("\nEnter PCB Name:");
>>>>>>> main
                                        //required for UI
                                        puts(">");
                                        //init choice buffer
                                        char choice[5] = {0};
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        //PCB 1
<<<<<<< HEAD
                                        if (strcmp(choice, "1") == 0)
                                        {
                                                pcb_delete("pcb1");
                                        }
                                        else if (strcmp(choice, "2") == 0)
                                        {
                                                pcb_delete("pcb2");
                                        }
                                        //keep, this is the back option for the inital menu, make 3 higher if you add more menus
                                        else if (strcmp(choice, "3") == 0)
                                        {
                                                continue;
                                        }
                                        else
                                        {
                                                puts("\nUnrecognized command.\n");
                                        }
=======
                                        pcb_delete(choice);
>>>>>>> main
                                }
                                else if (strcmp(choice, "3") == 0)
                                {
                                        //Block Pcb Menu
<<<<<<< HEAD
                                        puts("\nChoose PCB to Block:");
                                        //Choices Go Here
                                        puts("\n1) PCB 1 1\n2) PCB 2\n3) Back\n");
=======
                                        puts("\nEnter PCB to Block:");
>>>>>>> main
                                        //required for UI
                                        puts(">");
                                        //init choice buffer
                                        char choice[5] = {0};
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
<<<<<<< HEAD
                                        //PCB 1
                                        if (strcmp(choice, "1") == 0)
                                        {
                                                pcb_block("pcb1");
                                        }
                                        else if (strcmp(choice, "2") == 0)
                                        {
                                                pcb_block("pcb2");
                                        }
                                        //keep, this is the back option for the inital menu, make 3 higher if you add more menus
                                        else if (strcmp(choice, "3") == 0)
                                        {
                                                continue;
                                        }
                                        else
                                        {
                                                puts("\nUnrecognized command.\n");
                                        }
=======
                                        pcb_block(choice);
>>>>>>> main
                                }
                                else if (strcmp(choice, "4") == 0)
                                {
                                        //Block Pcb Menu
<<<<<<< HEAD
                                        puts("\nChoose PCB to UnBlock:");
                                        //Choices Go Here
                                        puts("\n1) PCB 1 1\n2) PCB 2\n3) Back\n");
=======
                                        puts("\nEnter PCB to UnBlock:");
>>>>>>> main
                                        //required for UI
                                        puts(">");
                                        //init choice buffer
                                        char choice[5] = {0};
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        //PCB 1
<<<<<<< HEAD
                                        if (strcmp(choice, "1") == 0)
                                        {
                                                pcb_unblock("pcb1");
                                        }
                                        else if (strcmp(choice, "2") == 0)
                                        {
                                                pcb_unblock("pcb2");
                                        }
                                        //keep, this is the back option for the inital menu, make 3 higher if you add more menus
                                        else if (strcmp(choice, "3") == 0)
                                        {
                                                continue;
                                        }
                                        else
                                        {
                                                puts("\nUnrecognized command.\n");
                                        }
=======
                                        pcb_unblock(choice);
>>>>>>> main
                                }
                                else if (strcmp(choice, "5") == 0)
                                {
                                        //Suspend Pcb Menu
<<<<<<< HEAD
                                        puts("\nChoose PCB to Suspend:");
                                        //Choices Go Here
                                        puts("\n1) PCB 1 1\n2) PCB 2\n3) Back\n");
=======
                                        puts("\nType PCB to Suspend:");
>>>>>>> main
                                        //required for UI
                                        puts(">");
                                        //init choice buffer
                                        char choice[5] = {0};
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        //PCB 1
<<<<<<< HEAD
                                        if (strcmp(choice, "1") == 0)
                                        {
                                                pcb_suspend("pcb1");
                                        }
                                        else if (strcmp(choice, "2") == 0)
                                        {
                                                pcb_suspend("pcb2");
                                        }
                                        //keep, this is the back option for the inital menu, make 3 higher if you add more menus
                                        else if (strcmp(choice, "3") == 0)
                                        {
                                                continue;
                                        }
                                        else
                                        {
                                                puts("\nUnrecognized command.\n");
                                        }
=======
                                        pcb_suspend(choice);
>>>>>>> main
                                }
                                else if (strcmp(choice, "6") == 0)
                                {
                                        //Resume Pcb Menu
<<<<<<< HEAD
                                        puts("\nChoose PCB to Resume:");
                                        //Choices Go Here
                                        puts("\n1) PCB 1 1\n2) PCB 2\n3) Back\n");
=======
                                        puts("\nType PCB to Resume:");
>>>>>>> main
                                        //required for UI
                                        puts(">");
                                        //init choice buffer
                                        char choice[5] = {0};
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        //PCB 1
<<<<<<< HEAD
                                        if (strcmp(choice, "1") == 0)
                                        {
                                                pcb_resume("pcb1");
                                        }
                                        else if (strcmp(choice, "2") == 0)
                                        {
                                                pcb_resume("pcb2");
                                        }
                                        //keep, this is the back option for the inital menu, make 3 higher if you add more menus
                                        else if (strcmp(choice, "3") == 0)
                                        {
                                                continue;
                                        }
                                        else
                                        {
                                                puts("\nUnrecognized command.\n");
                                        }
=======
                                        pcb_resume(choice);
>>>>>>> main
                                }
                                else if (strcmp(choice, "7") == 0)
                                {
                                        //Change Pcb Priority Menu
                                        puts("\nChoose PCB to Change Priority:");
                                        //Choices Go Here
<<<<<<< HEAD
                                        puts("\n1) PCB 1 1\n2) PCB 2\n3) Back\n");
=======
                                        puts("\nType PCB Name:");
>>>>>>> main
                                        //required for UI
                                        puts(">");
                                        //init choice buffer
                                        char choice[5] = {0};
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
<<<<<<< HEAD
                                        //PCB 1
                                        if (strcmp(choice, "1") == 0)
                                        {
                                                //Change Pcb Priority Menu
                                                puts("\nChoose Priority:");
                                                //Choices Go Here
                                                puts("\n1) Priority 1\n2) Priority 2\n3) Back\n");
                                                //required for UI
                                                puts(">");
                                                //init choice buffer
                                                char choice[5] = {0};
                                                //Read from the buffer
                                                sys_req(READ, COM1, choice, 5);
                                                //Priority 1
                                                if (strcmp(choice, "1") == 0)
                                                {
                                                        pcb_setpriority("pcb1","1");
                                                }
                                                else if (strcmp(choice, "2") == 0)
                                                {
                                                        pcb_block("pcb1", "2");
                                                }
                                                //keep, this is the back option for the inital menu, make 3 higher if you add more menus
                                                else if (strcmp(choice, "3") == 0)
                                                {
                                                        continue;
                                                }
                                                else
                                                {
                                                puts("\nUnrecognized command.\n");
                                                }
                                        }
                                        else if (strcmp(choice, "2") == 0)
                                        {
                                               //Change Pcb Priority Menu
                                                puts("\nChoose Priority:");
                                                //Choices Go Here
                                                puts("\n1) Priority 1\n2) Priority 2\n3) Back\n");
                                                //required for UI
                                                puts(">");
                                                //init choice buffer
                                                char choice[5] = {0};
                                                //Read from the buffer
                                                sys_req(READ, COM1, choice, 5);
                                                //Priority 1
                                                if (strcmp(choice, "1") == 0)
                                                {
                                                        pcb_setpriority("pcb2","1");
                                                }
                                                else if (strcmp(choice, "2") == 0)
                                                {
                                                        pcb_block("pcb2", "2");
                                                }
                                                //keep, this is the back option for the inital menu, make 3 higher if you add more menus
                                                else if (strcmp(choice, "3") == 0)
                                                {
                                                        continue;
                                                }
                                                else
                                                {
                                                puts("\nUnrecognized command.\n");
                                                }
                                        }
                                        //keep, this is the back option for the inital menu, make 3 higher if you add more menus
                                        else if (strcmp(choice, "3") == 0)
                                        {
                                                continue;
                                        }
                                        else
                                        {
                                                puts("\nUnrecognized command.\n");
                                        }
                                }
                                else if (strcmp(choice, "8") == 0)
                                {
                                        continue;
                                }
                                else
                                {
                                        puts("\nUnrecognized command.\n");
=======
                                        puts("\nType PCB Priority:");
                                        //init choice buffer
                                        char priority[5] = {0};
                                        int priority_valid = isNum(priority);
                                        if (priority_valid == 0)
                                        {
                                                puts("\nInvalid");
                                                continue;
                                        }
                                        // Convert year to an integer
                                        //int priorityInt = atoi(priority);
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        //uncomment when made
                                        //pcb_setpriority(name, priority);
                                        
>>>>>>> main
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
                                
                                if (strcmp(choice, "1") == 0){
                                        //Show Pcb Menu
<<<<<<< HEAD
                                        puts("\nChoose PCB to Show:");
                                        //Choices Go Here
                                        puts("\n1) PCB 1 1\n2) PCB 2\n3) Back\n");
=======
                                        puts("\n Enter PCB to Show:");
>>>>>>> main
                                        //required for UI
                                        puts(">");
                                        //init choice buffer
                                        char choice[5] = {0};
                                        //Read from the buffer
                                        sys_req(READ, COM1, choice, 5);
                                        //PCB 1
<<<<<<< HEAD
                                        if (strcmp(choice, "1") == 0)
                                        {
                                                show_pcb("pcb1");
                                        }
                                        else if (strcmp(choice, "2") == 0)
                                        {
                                                show_pcb("pcb2");
                                        }
                                        //keep, this is the back option for the inital menu, make 3 higher if you add more menus
                                        else if (strcmp(choice, "3") == 0)
                                        {
                                                continue;
                                        }
                                        else
                                        {
                                                puts("\nUnrecognized command.\n");
                                        }
                                        
                                }
                                else if (strcmp(choice, "2") == 0){
                                        show_ready();
                                }
                                else if (strcmp(choice, "3") == 0){
                                        show_blocked();
                                }
                                else if (strcmp(choice, "4") == 0){
                                        show_all();
=======
                                        show_pcb(choice);
                                        
                                }
                                else if (strcmp(choice, "2") == 0){
                                        //show_ready();
                                        //show_ready();
                                }
                                else if (strcmp(choice, "3") == 0){
                                        //show_blocked();
                                        //show_blocked();
                                }
                                else if (strcmp(choice, "4") == 0){
                                        //show_all();
                                        //show_all();
>>>>>>> main
                                }
                                else if (strcmp(choice, "5") == 0){
                                        continue;
                                }
                                else{
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
}
