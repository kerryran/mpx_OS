bits 32

global sys_call_isr

section .text
extern sys_call   ; Allows assembly to call the C function

sys_call_isr:
    ; Push segment registers (DS, ES, FS, GS) in the reverse order
    push gs
    push fs
    push es
    push ds

    ; Push general-purpose registers in the reverse order
    pushad

    ; Push the current ESP value
    push esp

    ; Call your C function
    call sys_call_isr

    ; Set ESP based on the return value of your function (EAX)
    pop eax
    mov esp, [eax]

    ; Pop the general-purpose registers in the correct order
    popad

    ; Pop the segment registers in the correct order
    pop ds
    pop es
    pop fs
    pop gs

    ; Return from ISR
    iret

; bits 32

; global sys_call_isr

; ;;; System call interrupt handler. To be implemented in Module R3.
; extern sys_call			; allows asm to view the c function
; sys_call_isr:
; mov eax, -1	
; 	; pusha ;this pushes all, CHANGE THIS to push in opposte order of struct once struct is made
; 	; push ESP
;     ; call sys_call_isr
; 	; mov ESP, [EAX] ;set ESP to the value that EAX points to, or remove the [   ] if sys_call_isr returns a value not a pointer idk yet
;     ; popa ;this pops all CHANGE THIS to pop in order of struct once struct is made
; 	iret
	
