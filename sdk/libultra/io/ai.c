#include "../../include/libgultra.h"
#include "COMMON/GUMTXL2F.H"
#include "TYPES.H"
#include "../../include/libgultra/ai.h"

/* Returns whether the audio interface status register at 0xA450000C has its top bit (FIFO full)
   set. */
s32 __osAiDeviceBusy(void) {
    return *(volatile s32 *) 0xA450000C >> 31 != 0;
}
