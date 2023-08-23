#include <../include/sys_req.h>
#include <../include/string.h>
#include <stdbool.h>
#include <mpx/serial.h>

void comhand(void) {

        //Menu Prompt
       puts("FroggyOS\n");

       char[5] buf = {0};
       sys_req(READ, COM1, buf, strlen(buf));

}
