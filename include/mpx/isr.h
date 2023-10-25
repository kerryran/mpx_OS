// all registers for the context
typedef struct context
{
    unsigned int CS;
    unsigned int DS;
    unsigned int ES;
    unsigned int FS;
    unsigned int GS;
    unsigned int SS;
    unsigned int EIP;
    unsigned int EFLAGS;
    unsigned int EAX;
    unsigned int EBX;
    unsigned int ECX;
    unsigned int EDX;
    unsigned int ESI;
    unsigned int EDI;
    unsigned int EBP;
    unsigned int ESP;
} context;

struct context *sys_call(struct context *context);
