#include <stdint.h>

//helper function to read a byte from RTC
uint8_t rtc_read(uint8_t reg){
    outb(0x70, reg);
    return inb(0x71);
}

//helper function to write a byte to RTC
void rtc_write(uint8_t reg, uint8_t value){
    cli(); //disable interrupts

    outb(0x70, reg);
    outb(0x71, value);

    sti(); //enable interrupts
}

void get_time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds){
    *seconds = rtc_read(0x00);
    *minutes = rtc_read(0x02);
    *hours = rtc_read(0x04);
}

void get_date(uint8_t *day, uint8_t *month, uint8_t *year){
    *day = rtc_read(0x07);
    *month = rtc_read(0x08);
    *year = rtc_read(0x09);
}

void set_time(uint8_t hours, uint8_t minutes, uint8_t seconds){
    rtc_write(0x04, hours);
    rtc_write(0x02, minutes);
    rtc_write(0x00, seconds);
}

void set_time(uint8_t day, uint8_t month, uint8_t year){
    rtc_write(0x07, day);
    rtc_write(0x08, month);
    rtc_write(0x09, year);
}