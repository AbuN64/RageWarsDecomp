#include "include_asm.h"
#include "Common/gumtxl2f.h"
#include <platform_sdk.h>

/* aigetlen.CPP */
/** Read the hardware register at 0xA450000C. */
unsigned int osAiGetStatus(void) {
    return *(volatile unsigned int *)0xA450000C;
}
