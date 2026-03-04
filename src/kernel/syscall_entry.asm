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

    ; After pusha, push ds, push es:
    ; [sp+0]  = ES
    ; [sp+2]  = DS
    ; [sp+4]  = DI
    ; [sp+6]  = SI
    ; [sp+8]  = BP
    ; [sp+10] = SP
    ; [sp+12] = BX
    ; [sp+14] = DX
    ; [sp+16] = CX
    ; [sp+18] = AX (Syscall Number)

    mov bp, sp
    
    ; Push arguments for cdecl (right to left):
    ; void syscall_handler(ax, bx, cx, dx, si, di)
    push word [bp+4]  ; DI
    push word [bp+6]  ; SI
    push word [bp+14] ; DX
    push word [bp+16] ; CX
    push word [bp+12] ; BX
    push word [bp+18] ; AX
    
    call syscall_handler
    
    ; Clean up stack (6 words * 2 bytes = 12)
    add sp, 12

    pop es
    pop ds
    popa
    iret
