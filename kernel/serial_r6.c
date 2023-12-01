#include <../include/mpx/serial_r6.h>

dcb *serialPort;

int serial_open(device dev, int speed){
// Initialize the serial port associated with the dev parameter
// Initialize the associated DCB
// Install the appropriate ISR
// Set the port speed to the speed parameter
// Set other line characteristics (8 data bits, no parity, 1 stop bit)
// Enable all necessary interrupts
// Return an integer indicating success or failure
}

int serial_close(device dev){
// End a serial port session
// Clear open indicator of associated DCB
// Disable associated interrupt in PIC mask
// Return an integer indicating success or failure
}
int serial_read(device dev, char *buf, size_t len){
// Begin reading input from the serial device dev
// Reads data into the buffer at buf
// Reads no more than len bytes
// If there are characters in the ring buffer, read until buf is full or no more
// characters in the ring buffer
// If buf is full, return
// Otherwise, change device states to reading and notify ISR to place
// characters in the the associated buffer instead of the ring buffer
}

int serial_write(device dev, char *buf, size_t len){
//  Begins writing data to the serial port dev
//  Write the first character from buf to the output register
//  Enable write interrupts
//  Let the ISR do the rest

}
void serial_interrupt(void){
// • Disable interrupts
// • Obtain the correct DCB
// • Read the Interrupt ID Register to determine the exact type of interrupt
// • Based on the type (input, output), pass the handling to a second function
// • Issue EOI to the PIC
// • Reenable interrupt
}

void serial_input_interrupt(struct dcb *dcb){
// Read the character from the device
// • If the DCB state is reading, store the character in the appropriate IOCB
// buffer
// • If the buffer is now full, or input was new-line, signal completion
// • Otherwise, attempt to store the character in the ring buffe
}
// 
void serial_output_interrupt(struct dcb *dcb){
// • If the DCB state is writing, check for additional characters in the
// appropriate IOCB buffer
// • If there is additional data, write the next character to the device
// • If you have just written the last character from the IOCB, disable write
// interrupts and signal completion
}
