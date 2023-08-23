#include <../include/sys_req.h>
#include <../include/string.h>
#include <stdbool.h>
#include <mpx/serial.h>

void comhand(void) {
        //Menu Prompt
       // puts("Hello I am a Menu");
       char* string = "I am a menu";
       sys_req(WRITE, COM1, &string, strlen(string));
   
}
