void comhand(void) {
    while (true){
        char buf[100] = { 0 };
        int nread = sys_req(READ, COM1, buf, sizeof(buf));
        //Echo the input to terminal
        sys_req(WRITE, COM1, buf, nread);
        //Command handling
    }
}