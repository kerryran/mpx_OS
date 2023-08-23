#include <../include/sys_req.h>
#include <../include/string.h>
#include <stdbool.h>
#include <mpx/serial.h>

void comhand(void)
{
        // Menu Prompt
        puts("FroggyOS\n");
        puts("1) Help\n2) Version\n");
        puts("Enter a number to select:\n");
        puts(">");

        while (true)
        {
                char buf[5] = {0};
                int nread = sys_req(READ, COM1, buf, 5);
                sys_req(WRITE, COM1, buf, nread);

                char selection;

                if (selection == "1")
                {
                        puts("HELP ME FOR thE LOVE OF GOD\n");
                }
                else if (selection == "2")
                {
                        puts("Version: 1.0\n");
                }
                else if (selection == "3")
                {
                        puts("Are you sure you want to shutdown?");
                        sys_req(READ, COM1, buf, 5);
                        char confirm;
                        if (confirm == "1")
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
