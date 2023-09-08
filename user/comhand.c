#include <../include/sys_req.h>
#include <../include/string.h>
#include <stdbool.h>
#include <mpx/serial.h>
#include <../include/dateAndTime.h>
#include <stdlib.h>

void comhand(void)
{
        // Welcome/Start-Up Message
        puts("\nWelcome to FroggyOS\n");

        while (true)
        {
                // Main Menu Prompt
                puts("\nMain Menu:\n");
                puts("1) Help\n2) Version\n3) Date & Time\n4) Quit\n");
                puts("Enter a number to select:\n");
                puts(">");

                char buffer[4] = {0};

                sys_req(READ, COM1, buffer, 4);

                // Working as intended
                if (strcmp(buffer, "1") == 0)
                {
                        puts("\nCommands:\n1) Help - describes all the available commands.\n2) Version - describes the operating system version.\n3) Get Date -returns the system date.\n");
                        puts("4) Set Date - allows user to update the system date, format as MM/DD/YY.\n5) Get Time - returns the system time.\n6) Set Time - allows user to update the system time, format as HH:MM:SS\n");
                        puts("7) Quit - Logs user out of the machine.\n");
                }
                // Working as intended
                else if (strcmp(buffer, "2") == 0)
                {
                        puts("\nVersion: 1.0\n");
                }
                else if (strcmp(buffer, "3") == 0)
                {
                        puts("\nDate & Time Menu:");
                        puts("\n1) Get Date\n2) Set Date\n3) Get Time\n4) Set Time\n5) Back\n");
                        puts(">");
                        char choice[5] = {0};
                        sys_req(READ, COM1, choice, 5);
                        if (strcmp(choice, "1") == 0)
                        {
                                puts("The date is: ");
                                get_date();
                        }
                        else if (strcmp(choice, "2") == 0)
                        {
                                
                                puts("\nEnter The Year:\n");
                                puts(">");
                                char year[3] = {0};
                                sys_req(READ, COM1, year, 3);

                                //validate year
                                int year_valid = isNum(year);
                                if(year_valid == 0){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                }

                                int y = atoi(year);

                                if((y%4)==0 && (y%100)!=0){
                                //this is a leap year, check february
                                puts("\nEnter The Month:\n");
                                puts(">");
                                char month[3] = {0};
                                sys_req(READ, COM1, month, 3);
                                
                                //validate month
                                int month_valid = isNum(month);
                                if(month_valid == 0){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                }

                                int m = atoi(month);
                                if(m == 2){
                                //february     
                                puts("\nEnter The Day:\n");
                                puts(">");
                                char day[3] = {0};
                                sys_req(READ, COM1, day, 3); 
                                
                                //validate day
                                int day_valid = isNum(day);
                                if(day_valid == 0){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                }

                                int d = atoi(day);

                                if(d > 29){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                } 
                                 set_date(d, m, y);
                                }
                                else if(m > 12){
                                       puts("\nInvalid date, Please select a new option");
                                        continue; 
                                }
                                else if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) ||(m == 12) ){
                                      //months have 31 days
                                         puts("\nEnter The Day:\n");
                                         puts(">");
                                         char day[3] = {0};
                                         sys_req(READ, COM1, day, 3); 
                                        
                                        //validate day
                                        int day_valid = isNum(day);
                                        if(day_valid == 0){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                         }
                                        int d = atoi(day);

                                        if(d > 31){
                                               puts("\nInvalid date, Please select a new option");
                                                continue;  
                                        }

                                        set_date(d, m, y);
                                }
                                else{
                                        //month must have 30 days
                                        puts("\nEnter The Day:\n");
                                         puts(">");
                                         char day[3] = {0};
                                         sys_req(READ, COM1, day, 3); 
                                       
                                        //validate day
                                        int day_valid = isNum(day);
                                        if(day_valid == 0){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                        }

                                        int d = atoi(day);

                                        if(d > 30){
                                               puts("\nInvalid date, Please select a new option");
                                                continue;  
                                        }
                                        
                                        set_date(d, m, y);
                                }
                                
                                }
                                else{
                                //not a leap year!
                                puts("\nEnter The Month:\n");
                                puts(">");
                                char month[3] = {0};
                                sys_req(READ, COM1, month, 3);

                                //validate month
                                int month_valid = isNum(month);
                                if(month_valid == 0){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                }

                                int m = atoi(month);
                                if(m == 2){
                                //february     
                                puts("\nEnter The Day:\n");
                                puts(">");
                                char day[3] = {0};
                                sys_req(READ, COM1, day, 3); 
                                
                                //validate day
                                int day_valid = isNum(day);
                                if(day_valid == 0){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                }

                                int d = atoi(day);

                                if(d > 28){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                } 
                                 set_date(d, m, y);
                                }
                                else if(m > 12){
                                       puts("\nInvalid date, Please select a new option");
                                        continue; 
                                }
                                else if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) ||(m == 12) ){
                                      //months have 31 days
                                         puts("\nEnter The Day:\n");
                                         puts(">");
                                         char day[3] = {0};
                                         sys_req(READ, COM1, day, 3); 

                                        //validate day
                                         int day_valid = isNum(day);
                                         if(day_valid == 0){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                         }

                                        int d = atoi(day);

                                        if(d > 31){
                                               puts("\nInvalid date, Please select a new option");
                                                continue;  
                                        }

                                        set_date(d, m, y);
                                }
                                else{
                                        //month must have 30 days
                                        puts("\nEnter The Day:\n");
                                         puts(">");
                                         char day[3] = {0};
                                         sys_req(READ, COM1, day, 3); 

                                        //validate day
                                        int day_valid = isNum(day);
                                        if(day_valid == 0){
                                        puts("\nInvalid date, Please select a new option");
                                        continue;
                                         }

                                        int d = atoi(day);

                                        if(d > 30){
                                               puts("\nInvalid date, Please select a new option");
                                                continue;  
                                        }
                                        
                                        set_date(d, m, y);
                                }   
                                }
                        }
                        else if (strcmp(choice, "3") == 0)
                        {
                                puts("The time in UTC is: ");
                                get_time();
                        }
                        else if (strcmp(choice, "4") == 0)
                        {
                                // Needs error checking
                                puts("\nUse 24 hr formating for the following entries:\n");
                                puts("\nEnter The Hours:\n");
                                puts(">");
                                char hour[3] = {0};
                                sys_req(READ, COM1, hour, 3);
                                
                                //validate hour
                                int hour_valid = isNum(hour);
                                if(hour_valid == 0){
                                        puts("\nInvalid time, Please select a new option");
                                        continue;
                                }

                                int hr = atoi(hour);
                                        if(hr > 24){
                                                puts("\nInvalid time, Please select a new option");
                                                continue;
                                        }

                                puts("\nEnter The Minutes:\n");
                                puts(">");
                                char minute[3] = {0};
                                sys_req(READ, COM1, minute, 3);
                                
                                //validate minute
                                int minute_valid = isNum(minute);
                                if(minute_valid == 0){
                                        puts("\nInvalid time, Please select a new option");
                                        continue;
                                }

                                int min = atoi(minute);
                                        if(min > 59){
                                               puts("\nInvalid time, Please select a new option");
                                                continue; 
                                        }
                                puts("\nEnter The Seconds:\n");
                                puts(">");
                                char second[3] = {0};
                                sys_req(READ, COM1, second, 3);

                                //validate second
                                int second_valid = isNum(second);
                                if(second_valid == 0){
                                        puts("\nInvalid time, Please select a new option");
                                        continue;
                                }
                                int sec = atoi(second);
                                        if(sec > 59){
                                                puts("\n Invalid time, Please select a new option");
                                                continue;
                                        }
                                set_time(hr, min, sec);
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
                // Working as intended
                else if (strcmp(buffer, "4") == 0)
                {
                        puts("\nAre you sure you want to shutdown?\n");
                        puts("1) Confirm\nAny-Key) Cancel\n");
                        puts(">");
                        char confirm[5] = {0};

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

