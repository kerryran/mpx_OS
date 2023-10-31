#include <../include/mpx/pcb.h>

typedef struct alarm{
    int hour;
    int min;
    int sec;
    char name_arr[10];
    char message[100];
    state dispatch;
    state execute;
    char stack[1024];
    char *stack_ptr;
    struct alarm *next;
}alarm;

struct alarm *create_alarm(void);
void insert_alarm(alarm *alarm);
void remove_alarm(alarm *old_alarm);
void check_alarm(alarm *alarm);
void show_alarms(void);

extern struct alarm *alarm_head;
