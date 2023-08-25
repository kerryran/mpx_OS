#include <../include/sys_req.h>
#include <../include/string.h>
#include <stdbool.h>
#include <mpx/serial.h>
#include <../include/dateAndTime.h>

void comhand(void)
{
        // Menu Prompt
        puts("FroggyOS\n");
        puts("1) Help\n2) Version\n3) Quit\n");
        puts("Enter a number to select:\n");

        while (true)
        {
                puts(">");
                // int nread = sys_req(READ, COM1, buf, 5);
                // sys_req(WRITE, COM1, buf, 5);
                char buffer[5] = {0};
                // char* selection;
                sys_req(READ, COM1, buffer, 5);
                // break;
                if (buffer[0] == 0)
                {
                        puts("buffer is empty");
                }
                // puts(buffer);
                else
                {
                        if (strcmp(buffer, "1") == 0)
                        {
                                puts("\nyou pressed 1\n");
                        }
                        else if (strcmp(buffer, "2") == 0)
                        {
                                puts("\nVersion: 1.0\n");
                        }
                        else if (strcmp(buffer, "3") == 0)
                        {
                                puts("\nAre you sure you want to shutdown?\n");
                                sys_req(READ, COM1, buffer, 5);
                                char *confirm;
                                if (strcmp(confirm, "1") == 0)
                                {
                                        puts("Shutting Down");
                                        return;
                                }
                                else
                                {
                                        break;
                                }
                        }
                }
        }
}
