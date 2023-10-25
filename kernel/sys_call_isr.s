global sys_call_isr
extern sys_call

sys_call_isr:
    ; Push segment registers (DS, ES, FS, GS) in the reverse order
    push gs
    push fs
    push es
    push ds

    ; Push general-purpose registers in the reverse order
    push edi
    push esi
    push ebp
    push edx
    push ecx
    push ebx
    push eax

    ; Push the current ESP value
    push esp

    ; Doesn't sys_call need a parameter?
    call sys_call

    mov esp, [eax]

    ; Pop the current ESP value
    pop esp
    pop eax
    pop ebx
    pop ecx
    pop edx
    pop ebp
    pop esi
    pop edi

    ; Pop the segment registers in the correct order
    pop ds
    pop es
    pop fs
    pop gs

    ; Return from ISR
    iret
