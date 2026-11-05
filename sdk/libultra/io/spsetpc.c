#include "include_asm.h"
#include <platform_sdk.h>
#include "types.h"



/* Sets the RSP program counter: returns -1 unless the RSP status register shows the processor
   halted, otherwise writes the address to the program counter register and returns zero. */
s32 __osSpSetPc(u32 pc) {
    u32 status = *(volatile u32 *) 0xA4040010;

    if (!(status & 1)) {
        return -1;
    }
    *(volatile u32 *) 0xA4080000 = pc;
    return 0;
}

