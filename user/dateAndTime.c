#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <stdlib.h>
#include <mpx/interrupts.h>

char *get_time()
{
    // read from register
    outb(0x70, 0x00);
    unsigned char seconds = inb(0x71);
    // get ones place of seconds
    int ones_sec = (seconds & 0x0F);
    // get tens place of seconds
    int tens_sec = seconds / 16;
    // combine
    int seconds_fr = (tens_sec * 10) + ones_sec;
    // convert to string
    char secs[3];
    itoa(seconds_fr, secs, 10);

    // read from register
    outb(0x70, 0x02);
    unsigned char minutes = inb(0x71);
    // get ones place of minutes
    int ones_min = (minutes & 0x0F);
    // get tens place of minutes
    int tens_min = minutes / 16;
    // combine
    int minutes_fr = (tens_min * 10) + ones_min;
    // convert to string
    char mins[3];
    itoa(minutes_fr, mins, 10);

    // read from register
    outb(0x70, 0x04);
    unsigned char hours = inb(0x71);
    // get ones place of hours
    int ones_hr = (hours & 0x0F);
    // get tens place of hours
    int tens_hr = hours / 16;
    // combine
    int hours_fr = (tens_hr * 10) + ones_hr;
    // convert to string
    char hrs[3];
    itoa(hours_fr, hrs, 10);

    // combine hours, minutes and seconds into one string
    char *final_time = strcat(hrs, ":");
    final_time = strcat(final_time, mins);
    final_time = strcat(final_time, ":");
    final_time = strcat(final_time, secs);
    // print time to console
    puts(final_time);

    // return success statement
    return "get time complete";
}

void set_time(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    cli(); // Disable Interupts

    // get tens place of seconds
    int tens_seconds = ((seconds / 10) & 15) << 4;
    // get ones place of seconds
    int ones_seconds = (seconds % 10) & 15;
    // make char of seconds
    int seconds_pc = (tens_seconds + ones_seconds);
    // write to register
    outb(0x70, 0x00);
    outb(0x71, seconds_pc);

    // get tens place of minutes
    int tens_minutes = ((minutes / 10) & 15) << 4;
    // get ones place of minutes
    int ones_minutes = (minutes % 10) & 15;
    // make char of minutes
    int minutes_pc = tens_minutes + ones_minutes;
    // write to register
    outb(0x70, 0x02);
    outb(0x71, minutes_pc);

    // get tens place of hours
    int tens_hours = ((hours / 10) & 15) << 4;
    // get ones place of hours
    int ones_hours = (hours % 10) & 15;
    // make char of hours
    int hours_pc = tens_hours + ones_hours;
    // write to register
    outb(0x70, 0x04);
    outb(0x71, hours_pc);

    sti(); // Enable Interrupts
}

char *get_date()
{
    // read from register
    outb(0x70, 0x07);
    unsigned char day = inb(0x71);
    // get ones place of day
    int ones_day = day & 0x0F;
    // get tens place of day
    int tens_day = day / 16;
    // combine
    int day_fr = (tens_day * 10) + ones_day;
    // convert to string
    char days[3];
    itoa(day_fr, days, 10);

    // read from register
    outb(0x70, 0x08);
    unsigned char month = inb(0x71);
    // get ones place of month
    int ones_month = month & 0x0F;
    // get tens place of month
    int tens_month = month / 16;
    // combine
    int month_fr = (tens_month * 10) + ones_month;
    // convert to string
    char months[3];
    itoa(month_fr, months, 10);

    // read from register
    outb(0x70, 0x09);
    unsigned char year = inb(0x71);
    // get ones place of year
    int ones_year = year & 0x0F;
    // get tens place of year
    int tens_year = year / 16;
    // combine
    int year_fr = (tens_year * 10) + ones_year;
    // convert to string
    char years[3];
    itoa(year_fr, years, 10);

    // combine month, day, year into one string
    char *final_date = strcat(months, "/");
    final_date = strcat(final_date, days);
    final_date = strcat(final_date, "/");
    final_date = strcat(final_date, years);
    // print date to console
    puts(final_date);

    // return success statement
    return "get date complete";
}

void set_date(uint8_t day, uint8_t month, uint8_t year)
{
    cli(); // Disable Interupts

    // get tens place of day
    int tens_day = ((day / 10) & 15) << 4;
    // get ones place of day
    int ones_day = (day % 10) & 15;
    // make char of day
    int day_pc = (tens_day + ones_day);
    // write to register
    outb(0x70, 0x07);
    outb(0x71, day_pc);

    // // get tens place of month
    int tens_month = ((month / 10) & 15) << 4;
    // // get ones place of month
    int ones_month = (month % 10) & 15;
    // // make char of month
    int month_pc = tens_month + ones_month;
    // // write to register
    outb(0x70, 0x08);
    outb(0x71, month_pc);

    // // get tens place of year
    int tens_year = ((year / 10) & 15) << 4;
    // // get ones place of year
    int ones_year = (year % 10) & 15;
    // // make char of year
    int year_pc = tens_year + ones_year;
    // // write to register
    outb(0x70, 0x09);
    outb(0x71, year_pc);

    sti(); // Enable Interrupts
}
