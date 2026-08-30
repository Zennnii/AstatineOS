global isr_common_stub
extern interrupt_handler

; isr macro (for isr's that have an error code)
%macro ISR_ERROR_CODE 1
global isr %+ %1
isr %+ %1:
    cli
    ; no need to push an error code since the CPU already did
    push dword %1 ; interrupt vector

    jmp isr_common_stub
%endmacro

; isr macro (for isr's that dont have an error code)
%macro ISR_NO_ERROR_CODE 1
global isr %+ %1
isr %+ %1:
    cli
    push dword 0 ; dummy error code
    push dword %1 ; interrupt vector

    jmp isr_common_stub
%endmacro

%assign i 0

; loop to set all isr's
%rep 32
    %if i = 8 || i = 10 || i = 11 || i = 12 || i = 13 || i = 14 || i = 17 || i = 21
        ISR_ERROR_CODE i
    %else
        ISR_NO_ERROR_CODE i
    %endif

    %assign i i + 1
%endrep

isr_common_stub:
    ; Save GPRs
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    ; Save current frame pointer
    mov rbx, rsp

    ; Align stack for C ABI
    and rsp, -16

    ; interrupt_handler(frame)
    mov rdi, rbx
    call interrupt_handler

    ; Restore original stack position
    mov rsp, rbx

    ; Restore GPRs
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ; Remove vector + error code
    add rsp, 16

    iretq