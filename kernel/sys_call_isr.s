bits 32

global sys_call_isr

;;; System call interrupt handler. To be implemented in Module R3.
extern sys_call			; allows asm to view the c function
sys_call_isr:
mov eax, -1	
	; pusha ;this pushes all, CHANGE THIS to push in opposte order of struct once struct is made
	; push ESP
    ; call sys_call_isr
	; mov ESP, [EAX] ;set ESP to the value that EAX points to, or remove the [   ] if sys_call_isr returns a value not a pointer idk yet
    ; popa ;this pops all CHANGE THIS to pop in order of struct once struct is made
	iret
	
