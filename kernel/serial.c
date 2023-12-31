#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>

enum uart_registers
{
	RBR = 0, // Receive Buffer
	THR = 0, // Transmitter Holding
	DLL = 0, // Divisor Latch LSB
	IER = 1, // Interrupt Enable
	DLM = 1, // Divisor Latch MSB
	IIR = 2, // Interrupt Identification
	FCR = 2, // FIFO Control
	LCR = 3, // Line Control
	MCR = 4, // Modem Control
	LSR = 5, // Line Status
	MSR = 6, // Modem Status
	SCR = 7, // Scratch
};

static int initialized[4] = {0};

static int serial_devno(device dev)
{
	switch (dev)
	{
	case COM1:
		return 0;
	case COM2:
		return 1;
	case COM3:
		return 2;
	case COM4:
		return 3;
	}
	return -1;
}

int serial_init(device dev)
{
	int dno = serial_devno(dev);
	if (dno == -1)
	{
		return -1;
	}
	outb(dev + IER, 0x00);			// disable interrupts
	outb(dev + LCR, 0x80);			// set line control register
	outb(dev + DLL, 115200 / 9600); // set bsd least sig bit
	outb(dev + DLM, 0x00);			// brd most significant bit
	outb(dev + LCR, 0x03);			// lock divisor; 8bits, no parity, one stop
	outb(dev + FCR, 0xC7);			// enable fifo, clear, 14byte threshold
	outb(dev + MCR, 0x0B);			// enable interrupts, rts/dsr set
	(void)inb(dev);					// read bit to reset port
	initialized[dno] = 1;
	return 0;
}

int serial_out(device dev, const char *buffer, size_t len)
{
	int dno = serial_devno(dev);
	if (dno == -1 || initialized[dno] == 0)
	{
		return -1;
	}
	for (size_t i = 0; i < len; i++)
	{
		outb(dev, buffer[i]);
	}
	return (int)len;
}

int serial_poll(device dev, char *buffer, size_t len)
{
	// insert your code to gather keyboard input via the technique of polling.
	// You must validate each key and handle special keys such as delete, back space, and
	// arrow keys

	// initialize counter
	////int char_count = 0;

	// initialize buffer counter
	int buffer_count = 0;
	int cursor_location = 0;

	// while buffer is not full
	while (buffer_count < (int)len - 1)
	{

		// inb the status register

		// check if the line register contents and 1 are true
		if ((inb(COM1 + LSR)) & 1)
		{
			// then this means we have a character in com1
			// increment char counter

			// inb com1 to read the character
			char c = inb(COM1);

			// if it is a new line then you are done
			if (c == '\r')
			{
				// moves to next line
				outb(dev, '\r');
				outb(dev, '\n');
				break;
			}
			//backspace
			else if (c == '\x7F')
			{
			
				if (cursor_location > 0)
				{
					// Remove last character from the buffer
					// Output backspace and a space to clear the previous character
					
					buffer_count--;
					outb(dev, '\b');
					outb(dev, ' ');
					outb(dev, '\b');
					cursor_location--;
					buffer[buffer_count] = 0;
				}
				else
				{

				}
			
			}
				else if (c == '\x5B') {

					char c = inb(COM1);
					//up arrow 
					if(c == 'A'){
					}
					else if(c == 'B'){
					//down arrow
					}
					//right arrow
					else if(c == 'C'){
						if(cursor_location<3){
							outb(dev, ' ');
							cursor_location++;
							
						}
						else{

						}

					}
					//left arrow
					else if(c == 'D'){
						if (cursor_location > 0)
						{
							cursor_location--;
							
							
							outb(dev, '\b');

							buffer[buffer_count] = 0;
						}
						else{
							
						}
					}
					else if(c == '3'){
						char c = inb(COM1);
						if(c=='~'){
							outb(dev, ' ');
							outb(dev, '\b');
							
							buffer_count--;
							buffer[cursor_location] = 0;
							
						}
					}
					else{
						
					}
			}
			else if(c == ' ')
			{
				// handles space bar
				cursor_location++;
				outb(dev, ' ');

				// increment buffer count
				buffer_count++;
			}
			
			else if((c <= 'Z' && c >= '0') || (c <= 'z' && c >= 'a'))
			{
				// if regular character then outb it so the user can see and add to the buffer
				buffer[cursor_location] = c;
				cursor_location++;
				outb(dev, c);

				// increment buffer count
				buffer_count++;
			}
			else{
				
				 
			}
		}
	}

	// returns number of characters added to the buffer
	cursor_location = 0;
	return buffer_count;
}
