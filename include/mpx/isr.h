// all registers for the context
typedef struct context
{
    unsigned int ESP;
    unsigned int EAX;
    unsigned int EBX;
    unsigned int ECX;
    unsigned int EDX;
    unsigned int EDP;
    unsigned int ESI;
    unsigned int EDI;
    unsigned int DS;
    unsigned int ES;
    unsigned int FS;
    unsigned int GS;
    unsigned int SS;
    unsigned int EIP;
    unsigned int CS;
    unsigned int EFLAGS;
} context;

struct context *sys_call(struct context *context);
