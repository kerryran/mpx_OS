#include <../include/sys_req.h>
#include <../include/string.h>
#include <stdbool.h>
#include <mpx/serial.h>

void comhand(void) {

        //Menu Prompt
       puts("FroggyOS\n");
       puts("1) Help\n2) Version\n");
       puts("Enter a number to select\n");
       puts(">");
       
       while(true){
        char* buf[5] = {0};
        sys_req(READ, COM1, buf, 5);
        }

}
