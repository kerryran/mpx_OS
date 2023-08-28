#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <mpx/interrupts.h>

// helper function to READ a byte from RTC
void rtc_read(uint8_t reg)
{

    outb(0x74, reg);

    inb(0x74);
}

// helper function to WRITE a byte to RTC
void rtc_write(uint8_t reg, uint8_t value)
{
    cli(); // disable interrupts

    outb(0x70, reg);
    outb(0x71, value);

    sti(); // enable interrupts
}

void get_time()
{
    rtc_read(0x00);
    rtc_read(0x02);
    rtc_read(0x04);
}

void get_date()
{
    rtc_read(0x07);
    rtc_read(0x08);
    rtc_read(0x09);
}

void set_time(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    rtc_write(0x04, hours);
    rtc_write(0x02, minutes);
    rtc_write(0x00, seconds);
}

void set_date(uint8_t day, uint8_t month, uint8_t year)
{
    rtc_write(0x07, day);
    rtc_write(0x08, month);
    rtc_write(0x09, year);
}
