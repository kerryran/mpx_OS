#include <stdint.h>

struct pcb *pcb_create(char name[], int class, int priority);
void pcb_delete(char name[]);
void pcb_block(char name[]);
void pcb_unblock(char name[]);
void pcb_suspend(char name[]);
void pcb_resume(char name[]);
void show_pcb(char *name);
void show_ready(char *name);
void show_blocked(char *name);
void show_all(char *name);
