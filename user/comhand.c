#include <../include/sys_req.h>
#include <stdbool.h>
#include <mpx/serial.h>

void comhand(void) {
    while (true){
        char buf[100] = { 0 };
        int buf_size = sizeof(buf);

        serial_out(COM1, "whaty\0", 5);
        //Menu Prompt
        sys_req(WRITE, COM1, "buf", "hello I'm a menu");

        int nread = sys_req(READ, COM1, buf, buf_size);
        //Echo the input to terminal
        sys_req(WRITE, COM1, buf, nread);
        //Command handling
        
    }
}
