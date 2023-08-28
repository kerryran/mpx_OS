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
                char string[4] = "abc";
                char *strong = substring(string, 0, 1);
                puts(strong);
                // Main Menu Prompt
                puts("\nMain Menu:\n");
                puts("1) Help\n2) Version\n3) Date & Time\n4) Quit\n");
                puts("Enter a number to select:\n");
                puts(">");

                char buffer[5] = {0};

                sys_req(READ, COM1, buffer, 5);

                // Working as intended
                if (strcmp(buffer, "1") == 0)
                {
                        puts("\nCommands:\n1) Help - describes all the available commands.\n2) Version - describes the operating system version.\n3) Get Date -returns the system date.\n");
                        puts("4) Set Date - allows user to update the system date, format as YYYY/MM/DD.\n5) Get Time - returns the system time.\n6) Set Time - allows user to update the system time, format as HH:MM:SS\n");
                        puts("7) Quit - Logs user out of the machine.\n");
                }
                // Working as intended
                else if (strcmp(buffer, "2") == 0)
                {
                        puts("\nVersion: 1.0\n");
                }
                else if (strcmp(buffer, "3") == 0)
                {
                        puts("\n1) Get Date\n2) Set Date\n3) Get Time\n4) Set Time\n5) Back\n");
                        puts(">");
                        char choice[5] = {0};
                        sys_req(READ, COM1, choice, 5);
                        if (strcmp(choice, "1") == 0)
                        {
                                // Doesn't work, crashes
                                get_date(0, 0, 0);
                        }
                        else if (strcmp(choice, "2") == 0)
                        {
                                // Needs error checking
                                puts("\nEnter Date:\n");
                                puts(">");
                                char date[12] = {0};
                                sys_req(READ, COM1, date, 12);
                                char *year = substring(date, 0, 4);
                                char *month = substring(date, 5, 2);
                                char *day = substring(date, 8, 2);
                                puts(year);
                                puts(month);
                                puts(day);

                                set_date(atoi(day), atoi(month), atoi(year));
                        }
                        else if (strcmp(choice, "3") == 0)
                        {
                                // Doesn't work, crashes
                                get_time(0, 0, 0);
                        }
                        else if (strcmp(choice, "4") == 0)
                        {
                                // Needs error checking
                                puts("\nEnter Time:\n");
                                puts(">");
                                char time[12] = {0};
                                sys_req(READ, COM1, time, 12);
                                char *hours = substring(time, 0, 2);
                                char *minutes = substring(time, 3, 2);
                                char *seconds = substring(time, 6, 2); // This makes no sense for a user to enter.
                                puts(hours);
                                puts(minutes);
                                puts(seconds);
                                set_time(atoi(hours), atoi(minutes), atoi(seconds));
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
