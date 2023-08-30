#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <mpx/interrupts.h>

// helper function to WRITE a byte to RTC
void rtc_write(uint8_t reg, uint8_t value)
{
    cli(); // disable interrupts

    outb(0x70, reg);
    outb(0x71, value);

    sti(); // enable interrupts
}

char* get_time()
{
   

    outb(0x70, 0x00);
    unsigned char seconds = inb(0x00);
    //convert the shift??
    int ones_sec = (seconds & 00001111);

    outb(0x70, 0x02);
    unsigned char minutes = inb(0x02);
    //convert the shift??
    int ones_min = (minutes & 00001111);

    outb(0x70,0x04);
    unsigned char hours = inb(0x04);
    //convert the shift??
    int ones_hr = (hours & 00001111);

    //delete the following later
    puts((char*)ones_sec);
    puts((char*)ones_min);
    puts((char*)ones_hr);
    char* time = "time";
    return time;
    
}

void get_date()
{
    outb(0x70, 0x07);
    unsigned char day = inb(0x07);
    //convert the shift
    int ones_day = (day & 00001111);

    outb(0x70,0x08);
    unsigned char month = inb(0x08);
    //convert the shift
    int ones_month = (month & 00001111);

    outb(0x70,0x09);
    unsigned char year = inb(0x09);
    //convert the shift
    int ones_year = (year & 00001111);

    //delete the following later
    puts((char*)ones_day);
    puts((char*)ones_month);
    puts((char*)ones_year);
    
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
