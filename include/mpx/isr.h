// all registers for the context
typedef struct context
{
    //Segments
    unsigned int CS;
    unsigned int DS;
    unsigned int ES;
    unsigned int FS;
    unsigned int GS;
    unsigned int SS;
    //registers
    unsigned int EAX;
    unsigned int EBX;
    unsigned int ECX;
    unsigned int EDX;
    unsigned int ESI;
    unsigned int EDI;
    unsigned int EBP; 
    //flags
    unsigned int EIP;
    unsigned int EFLAGS;
} context;

struct context *sys_call(struct context *context);
