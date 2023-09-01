#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <stdlib.h>
#include <mpx/interrupts.h>

void rtc_write(uint8_t reg, uint8_t value){
    cli();
   outb(0x70,reg);
   outb(0x71,value);

   sti();
}
char *get_time()
{
    outb(0x70, 0x00);
    unsigned char seconds = inb(0x71);
    // ones place
    int ones_sec = (seconds & 0x0F);
    // tens place
    int tens_sec = seconds / 16;
    //  actual seconds
    int seconds_fr = (tens_sec * 10) + ones_sec;
    // convert to string
    char secs[3];
    itoa(seconds_fr, secs, 10);

    outb(0x70, 0x02);
    unsigned char minutes = inb(0x71);
    // ones place
    int ones_min = (minutes & 0x0F);
    // tens place
    int tens_min = minutes / 16;
    //  actual minutes
    int minutes_fr = (tens_min * 10) + ones_min;
    // convert to string
    char mins[3];
    itoa(minutes_fr, mins, 10);

    outb(0x70, 0x04);
    unsigned char hours = inb(0x71);
    // ones place
    int ones_hr = (hours & 0x0F);
    // tens place
    int tens_hr = hours / 16;
    //  actual hours
    int hours_fr = (tens_hr * 10) + ones_hr;
    // convert to string
    char hrs[3];
    itoa(hours_fr, hrs, 10);

    char *final_time = strcat(hrs, ":");
    final_time = strcat(final_time, mins);
    final_time = strcat(final_time, ":");
    final_time = strcat(final_time, secs);
    puts(final_time);
    return "done";
}

char *get_date()
{
    outb(0x70, 0x07);
    unsigned char day = inb(0x71);
    // ones place
    int ones_day = day & 0x0F;
    // tens place
    int tens_day = day / 16;
    //  actual day
    int day_fr = (tens_day * 10) + ones_day;
    // convert to string
    char days[3];
    itoa(day_fr, days, 10);

    outb(0x70, 0x08);
    unsigned char month = inb(0x71);
    // ones place
    int ones_month = month & 0x0F;
    // tens place
    int tens_month = month / 16;
    //  actual month
    int month_fr = (tens_month * 10) + ones_month;
    //convert to string
    char months[3];
    itoa(month_fr, months, 10);

    outb(0x70, 0x09);
    unsigned char year = inb(0x71);
    // ones place
    int ones_year = year & 0x0F;
    // tens place
    int tens_year = year / 16;
    // actual year
    int year_fr = (tens_year * 10) + ones_year;
    // convert to string
    char years[3];
    itoa(year_fr, years, 10);

    char *final_date = strcat(months, "/");
    final_date = strcat(final_date, days);
    final_date = strcat(final_date, "/");
    final_date = strcat(final_date, years);
    puts(final_date);
    return "done";
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
