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
    puts("\nI am before disabling interrupts\n");
    // cli(); // disable interrupts

    // Convert integer to binary
    int binary[8];
    int i = 0;

    puts("\nI am before the while loop\n");
    while (value > 0)
    {
        // Problem... what if user types in number like 05? How does atoi handle that? Does it even matter?
        // 24 HR TIME
        binary[i] = value % 2;
        // Trying to print value fails
        puts("\nI am before printing the value\n");
        value /= 2;
        i++;
    }

    puts("\n I am before outb to reg");
    outb(0x71, reg);
    puts("\nI am before outb to valuee");
    outb(0x70, value);

    // sti(); // enable interrupts
}

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

char *get_date()
{
    outb(0x70, 0x07);
    unsigned char day = inb(0x71);
    // convert the shift
    int ones_day = day & 0x0F;
    // tens place
    int tens_day = day / 16;
    // tens_day = (tens_day & 00001111);
    //  actual day
    int day_fr = (tens_day * 10) + ones_day;
    // delete later
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
