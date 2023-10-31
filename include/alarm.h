#include <../include/mpx/pcb.h>

typedef struct alarm{
    int hour;
    int min;
    int sec;
    char name_arr[10];
    char message[100];
    state dispatch;
    state execute;
    struct alarm *next;
}alarm;

void create_alarm(void);
void insert_alarm(alarm *alarm);
void remove_alarm(alarm *old_alarm);
void check_alarm(struct alarm *alarm);

extern struct alarm *alarm_head;
