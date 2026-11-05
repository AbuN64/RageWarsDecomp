#include <platform_sdk.h>
#include "Io/externs.h"
#include "Common/obj.h"
#include "types.h"
#include "include_asm.h"

s32 Libsn_ReadPortWord(s32 portAddress) {
    if (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
        do {
        } while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY));
    }
    return *(vu32 *)portAddress;
}

extern volatile s32 g_libsnDelayIteration;

void Libsn_SpinDelay(s32 iterationCount) {
    for (g_libsnDelayIteration = 0; g_libsnDelayIteration < iterationCount; g_libsnDelayIteration++) {
    }
}
