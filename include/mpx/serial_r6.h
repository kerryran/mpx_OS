#ifndef MPX_SERIAL_R6_H
#define MPX_SERIAL_R6_H

#include <stddef.h>
#include <mpx/device.h>

int serial_open(device dev, int speed);
int serial_close(device dev);
int serial_read(device dev, char *buf, size_t len);
int serial_write(device dev, char *buf, size_t len);
void serial_interrupt(void);
void serial_input_interrupt(struct dcb *dcb);
void serial_output_interrupt(struct dcb *dcb);

#define RING_BUFFER_SIZE 50

typedef struct dcb
{
    int flag; // A flag indicating whether the port is open;
    int *event_flag; //The event flag – Set to 0 at the beginning of an operation, and set to 1 to indicate when the operation is complete
	int status;//IDLE or READING or WRITING
    int *address_in;//Addresses and counters associated with the current input buffer
    int *count_in;//Addresses and counters associated with the current input buffer
    int placed_in;
    char *address_out;//Addresses and counters associated with the current output buffe
    int count_out;//Addresses and counters associated with the current output buffe
    int placed_out;//Addresses and counters associated with the current output buffe
    char ring_buffer[RING_BUFFER_SIZE];//An array to be used as the input ring buffer, with associated input index, output index, and counte
    int ring_buffer_in;//An array to be used as the input ring buffer, with associated input index, output index, and counte
    int ring_buffer_count;//An array to be used as the input ring buffer, with associated input index, output index, and counte
    int ring_buffer_out;//An array to be used as the input ring buffer, with associated input index, output index, and counte
} dcb;

#define calcBaudRate(x) (115200 / (long) x)
#define OPEN_INV_E_FLAG_POINTER -101
#define OPEN_INV_B_RATE_DIVISOR -102
#define OPEN_PORT_OPEN -103

#define CLOSE_SERIAL_PORT_NOT_OPEN -201

#define READ_PORT_NOT_OPEN -301
#define READ_INVALID_BUFFER_ADDRESS -302
#define READ_INVALID_COUNT_ADDRESS -303
#define READ_DEVICE_BUSY -304

#define WRITE_SERIAL_PORT_NOT_OPEN -401
#define WRITE_INVALID_BUFFER_ADDRESS -402
#define WRITE_INVALID_COUNT_ADDRESS -403
#define WRITE_DEVICE_BUSY -404 

#define COM1_INT_ID 0x0c
#define COM1_BASE 0x3F8
#define COM1_INT_EN COM1_BASE+1
//Baud rate divisor
#define COM1_BAUDRD_LSB COM1_BASE
#define COM1_BAUDRD_MSB COM1_BASE+1
#define COM1_INTERRUPT_ID COM1_BASE+2
#define COM1_LINECONTROL COM1_BASE+3
#define COM1_MODEM_CONTROL COM1_BASE+4
#define COM1_LINE_STATUS COM1_BASE+5
#define COM1_MODEM_STATUS COM1_BASE+6
#define PIC_MASK 0x21
#define PIC_CMD 0x20
//end of interupt
#define EOI 0x20
#define LINE_CONTROL 0x80
#define LINE_CONTROL2 0x03
#define PIC_MASK 0x21
#define INT_OVERALL_SERIAL 0x08
#define INT_INPUT_READY 0x01
#define IE_BIT_ONE 0x02
//DCB STATUS
#define OPENED -9999
#define CLOSED -9998

#define IDLING -9997
#define READING -9996
#define WRITING -9995
#endif

