#include "syscall.h"
#include "lib/stdio.h"
#include <stdint.h>

extern void syscall_entry();

void init_syscall() {
    uint16_t* ivt = (uint16_t *)0;
    ivt[0x80 * 2] = (uint16_t)syscall_entry;
    ivt[0x80 * 2 + 1] = 0x0000;
}

uint16_t __attribute__((cdecl)) syscall_handler(uint16_t ax, uint16_t bx, uint16_t cx, uint16_t dx, uint16_t si, uint16_t di) {
    uint16_t count = 0;

    switch (ax) {
        case SYS_EXIT:
            return bx; // Exit code
            break;

        case SYS_READ:
            for (count = 0; count < cx; count++) {
                ((char*)bx)[count] = getchar();
                if (((char*)bx)[count] == '\r') break;
            }
            return count; // Return number of chars read
            break;

        case SYS_WRITE:
            for (count = 0; count < cx; count++) {
                putchar(((char*)bx)[count]);
            }
            return count; // Return number of chars written
            break;

        case SYS_GETCHAR:
            return (uint16_t)getchar();
            break;

        case SYS_PRINT:
            puts((char*)bx);
            return 0;
            break;

        default:
            return 0xFFFF; // Error
            break;
    }
}
