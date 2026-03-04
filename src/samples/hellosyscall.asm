[bits 16]
[org 0x7E00]

    ; Ensure DS is 0 for our string pointer (kernel uses DS=0 too)
    xor ax, ax
    mov ds, ax

    mov ax, 5           ; SYS_PRINT = 5
    mov bx, HELLO_WORLD ; pointer to string
    int 0x80            ; call kernel

    mov ax, 1           ; SYS_EXIT = 1
    xor bx, bx          ; exit code 0
    int 0x80

    ; Return from program to kernel shell
    ; We must use retf because kernel's 'run' command used retf to call us.
    ret

HELLO_WORLD db "Hello from syscall!", 0x0d, 0x0a, 0
