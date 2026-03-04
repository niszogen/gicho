[bits 16]
[extern syscall_handler]

global syscall_entry
syscall_entry:
    pusha           ; Save AX, CX, DX, BX, SP, BP, SI, DI
    push ds         ; Save segment registers
    push es

    ; Set DS/ES to kernel data (0x0000)
    xor ax, ax
    mov ds, ax
    mov es, ax

    mov bp, sp
    
    ; Push arguments for cdecl (right to left)
    push word [bp+4]  ; DI
    push word [bp+6]  ; SI
    push word [bp+14] ; DX
    push word [bp+16] ; CX
    push word [bp+12] ; BX
    push word [bp+18] ; AX
    
    call syscall_handler
    
    ; The C return value is in AX. 
    ; We want the caller's AX (saved at [bp+18]) to be this value after popa.
    mov [bp+18], ax

    add sp, 12      ; Clean up arguments

    pop es
    pop ds
    popa
    iret
