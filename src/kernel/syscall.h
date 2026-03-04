#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

#define SYS_EXIT 1
#define SYS_READ 2
#define SYS_WRITE 3
#define SYS_GETCHAR 4
#define SYS_PRINT 5

void init_syscall();

// Force cdecl calling convention (stack-based)
void __attribute__((cdecl)) syscall_handler(uint16_t ax, uint16_t bx,
                                            uint16_t cx, uint16_t dx,
                                            uint16_t si, uint16_t di);

#endif
