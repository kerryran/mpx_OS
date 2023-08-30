#include <stdint.h>
void rtc_write(uint8_t reg, uint8_t value);
char* get_time();
char* get_date();
void set_time(uint8_t hours, uint8_t minutes, uint8_t seconds);
void set_date(uint8_t day, uint8_t month, uint8_t year);
