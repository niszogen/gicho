#include "syscall.h"
#include "lib/stdio.h"
#include <stdint.h>

extern void syscall_entry();

void init_syscall() {
  uint16_t *ivt = (uint16_t *)0;
  ivt[0x80 * 2] = (uint16_t)syscall_entry;
  ivt[0x80 * 2 + 1] = 0x0000;
}

// Handler using cdecl (stack-based arguments)
void __attribute__((cdecl)) syscall_handler(uint16_t ax, uint16_t bx,
                                            uint16_t cx, uint16_t dx,
                                            uint16_t si, uint16_t di) {
  switch (ax) {
  case SYS_EXIT:
    return;
    break;

  case SYS_READ:
    for (uint16_t i = 0; i < cx; i++) {
      ((char *)bx)[i] = getchar();
      if (((char *)bx)[i] == '\r')
        break;
    }
    break;

  case SYS_WRITE:
    for (uint16_t i = 0; i < cx; i++) {
      putchar(((char *)bx)[i]);
    }
    break;

  case SYS_GETCHAR:
    getchar();
    break;

  case SYS_PRINT:
    puts((char *)bx);
    break;

  default:
    break;
  }
}
