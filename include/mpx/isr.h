
extern struct pcb *current;
// all registers for the context
typedef struct context
{
    //Segments
    int DS;
    int ES;
    int FS;
    int GS;
    int SS;
    //registers
    int ESP;
    int EAX;
    int EBX;
    int ECX;
    int EDX;
    int ESI;
    int EDI;
    int EBP; 
    //flags
    int EIP;
    int CS;
    int EFLAGS;
} context;

struct context *sys_call(struct context *context);
