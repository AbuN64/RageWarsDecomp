#include "include_asm.h"
#include "COMMON/GUMTXL2F.H"
#include <ultra64.h>

/* aigetlen.CPP */
/** Read the hardware register at 0xA450000C. */
unsigned int osAiGetStatus(void) {
    return *(volatile unsigned int *)0xA450000C;
}
