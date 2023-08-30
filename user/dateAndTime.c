#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <stdlib.h>
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
    //ones place
    int ones_sec = (seconds & 00001111);
    //tens place
    int tens_sec = seconds >> 4;
    tens_sec = (tens_sec & 00001111);
    //actual seconds
    int seconds_fr = (tens_sec * 10) + ones_sec;
    //convert to string
    char secs[3];
    itoa(seconds_fr,secs, 10);

    outb(0x70, 0x02);
    unsigned char minutes = inb(0x02);
    //ones place
    int ones_min = (minutes & 00001111);
    //tens place
    int tens_min = minutes >> 4;
    tens_min = (tens_min & 00001111);
    //actual minutes
    int minutes_fr = (tens_min * 10) + ones_min;
    //convert to string
    char mins[3]; 
    itoa(minutes_fr, mins, 10);

    outb(0x70,0x04);
    unsigned char hours = inb(0x04);
    //ones place
    int ones_hr = (hours & 00001111);
    //tens place
    int tens_hr = hours >> 4;
    tens_hr = (tens_hr & 00001111);
    //actual hours
    int hours_fr = (tens_hr * 10) + ones_hr;
    //convert to string
    char hrs[3];
    itoa(hours_fr, hrs, 10);

    char* final_time = strcat(hrs, ":");
    final_time = strcat(final_time, mins);
    final_time = strcat(final_time, ":");
    final_time = strcat(final_time, secs);
    return final_time;
    
}

char* get_date()
{
    outb(0x70, 0x07);
    unsigned char day = inb(0x07);
    //ones place
    int ones_day = (day & 00001111);
    //tens place
    int tens_day = day >> 4;
    tens_day = (tens_day & 00001111);
    //actual day
    int day_fr = (tens_day * 10) + ones_day;
    //delete later
    puts((char*)day_fr);

    outb(0x70,0x08);
    unsigned char month = inb(0x08);
    //ones place
    int ones_month = (month & 00001111);
    //tens place
    int tens_month = month >> 4;
    tens_month = (tens_month & 00001111);
    //actual month
    int month_fr=(tens_month * 10) + ones_month;
    //delete later
    puts((char*)month_fr);

    outb(0x70,0x09);
    unsigned char year = inb(0x09);
    //ones place
    int ones_year = (year & 00001111);
    //tens place
    int tens_year = year >> 4;
    tens_year = (tens_year & 00001111);
    //actual year
    int year_fr = (tens_year * 10) + ones_year;
    //delete later
    puts((char*)year_fr);

    //delete later
    char* date = "date";
    return date;
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
