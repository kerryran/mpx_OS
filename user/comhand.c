#include <../include/sys_req.h>
#include <../include/string.h>
#include <stdbool.h>
#include <mpx/serial.h>

void comhand(void)
{
        // Menu Prompt
        puts("FroggyOS\n");
        puts("1) Help\n2) Version\n3) Quit\n");
        puts("Enter a number to select:\n");
        puts(">");

        while (true)
        {
                char buf[5] = {0};
                //int nread = sys_req(READ, COM1, buf, 5);
                //sys_req(WRITE, COM1, buf, 5);

                //char* selection;
                sys_req(READ,COM1,buf,5);
                //break;
                puts(buf);

                if (strcmp(buf,"1") == 0)
                {
                        puts("you pressed 1\n");
                }
                else if (strcmp(buf,"2") == 0)
                {
                        puts("Version: 1.0\n");
                }
                else if (strcmp(buf,"3") == 0)
                {
                        puts("Are you sure you want to shutdown?");
                        sys_req(READ, COM1, buf, 5);
                        char* confirm;
                        if (strcmp(confirm,"1") == 0)
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
