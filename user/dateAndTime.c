#include <../include/dateAndTime.h>
#include <mpx/io.h>
#include <mpx/serial.h>
#include <sys_req.h>
#include <string.h>
#include <stdlib.h>
#include <mpx/interrupts.h>

char *get_time()
{
    outb(0x70, 0x00);
    unsigned char seconds = inb(0x71);
    // ones place
    int ones_sec = (seconds & 0x0F);
    // tens place
    int tens_sec = seconds / 16;
    // tens_sec = (tens_sec & 0x0F);
    //  actual seconds
    int seconds_fr = (tens_sec * 10) + ones_sec;
    // convert to string
    char secs[3];
    itoa(seconds_fr, secs, 10);

    // mod 16 to get low
    // deivde by 16 to get high
    // multiply by 16 to reverse for set
    outb(0x70, 0x02);
    unsigned char minutes = inb(0x71);
    // ones place
    int ones_min = (minutes & 0x0F);
    // tens place
    int tens_min = minutes / 16;
    // tens_min = (tens_min & 0x0F);
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
    // tens_hr = (tens_hr & 00001111);
    //  actual hours
    int hours_fr = (tens_hr * 10) + ones_hr;
    // convert to string
    char hrs[3];
    itoa(hours_fr, hrs, 10);

    char *final_time = strcat(hrs, ":");
    // puts("\n");
    // puts(final_time);
    // puts("\n");
    final_time = strcat(final_time, mins);
    final_time = strcat(final_time, ":");
    final_time = strcat(final_time, secs);
    puts(final_time);
    return "done";
}

void set_time(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    // we have int of the user input

    // get tens place of day
    int tens_seconds = seconds * 16;
    // get ones place of day
    int ones_seconds = seconds & 0x0F;
    // make char of day
    unsigned char day_pc = (unsigned char)(tens_seconds * 10) + ones_seconds;
    // write to register
    outb(0x71, day_pc);

    // get tens place of day
    int tens_month = minutes * 16;
    // get ones place of day
    int ones_month = minutes & 0x0F;
    // make char of day
    unsigned char month_pc = (unsigned char)(tens_month * 10) + ones_month;
    // write to register
    outb(0x71, month_pc);

    // get tens place of day
    int tens_year = hours * 16;
    // get ones place of day
    int ones_year = hours & 0x0F;
    // make char of day
    unsigned char year_pc = (unsigned char)(tens_year * 10) + ones_year;
    // write to register
    outb(0x71, year_pc);
}

void set_date(uint8_t day, uint8_t month, uint8_t year)
{
    cli(); // Disable Interupts
    // we have int of the user input

    // get tens place of day
    int tens_day = ((day / 10) & 15) << 4;
    // get ones place of day
    int ones_day = (day % 10) & 15;
    // make char of day
    int day_pc = (tens_day + ones_day);
    // write to register
    outb(0x70, 0x07);
    outb(0x71, day_pc);

    // // get tens place of day
    int tens_month = ((month / 10) & 15) << 4;
    // // get ones place of day
    int ones_month = (month % 10) & 15;
    // // make char of day
    int month_pc = tens_month + ones_month;
    // // write to register
    outb(0x70, 0x08);
    outb(0x71, month_pc);

    // // get tens place of day
    int tens_year = ((year / 10) & 15) << 4;
    // // get ones place of day
    int ones_year = (year % 10) & 15;
    // // make char of day
    int year_pc = tens_year + ones_year;
    // // write to register
    outb(0x70, 0x09);
    outb(0x71, year_pc);

    sti(); // Enable Interrupts
}

char *get_date()
{
    outb(0x70, 0x07);
    unsigned char day = inb(0x71);
    // convert the shift
    int ones_day = day & 0x0F;
    // tens place
    int tens_day = day / 16;
    //  actual day
    int day_fr = (tens_day * 10) + ones_day;
    // Convert to string
    char days[3];
    itoa(day_fr, days, 10);

    outb(0x70, 0x08);
    unsigned char month = inb(0x71);
    // convert the shift
    int ones_month = month & 0x0F;
    // tens place
    int tens_month = month / 16;
    // tens_month = (tens_month & 00001111);
    //  actual month
    int month_fr = (tens_month * 10) + ones_month;
    // delete later
    char months[3];
    itoa(month_fr, months, 10);

    outb(0x70, 0x09);
    unsigned char year = inb(0x71);
    // convert the shift
    int ones_year = year & 0x0F;

    int tens_year = year / 16;

    int year_fr = (tens_year * 10) + ones_year;

    char years[3];
    itoa(year_fr, years, 10);

    char *final_date = strcat(months, ":");
    final_date = strcat(final_date, days);
    final_date = strcat(final_date, ":");
    final_date = strcat(final_date, years);
    puts(final_date);
    return "done";
}
