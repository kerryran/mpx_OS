// all registers for the context
typedef struct context
{
    int CS;
    int DS;
    int ES;
    int FS;
    int GS;
    int SS;
    int EI;
    int EFLAGS;
    int EAX;
    int EBX;
    int ECX;
    int EDX;
    int ESI;
    int EDI;
    int EBP;
    int ESP;
} context;
