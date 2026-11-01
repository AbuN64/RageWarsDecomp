#include "COMMON/CONTREADFORMAT.H"

/* Points the RDP command DMA at a new display-list buffer, returning -1 if the RDP is busy, otherwise clearing the XBUS flag, waiting for it to drop and writing the physical start and end addresses (libultra osDpSetNextBuffer). */
#include "../../include/RDP_DMA_IO.H"
#include "TYPES.H"
#include "COMMON/OSTHREAD_S.H"
#include "../../include/libgultra.h"
#include <ultra64.h>



s32 osDpSetNextBuffer(void *bufPtr, u64 size) {
    if (__osDpDeviceBusy()) {
        return -1;
    }
    IO_WRITE(RDP_DMA_STATUS_REG, 1);
    do {
    } while (IO_READ(RDP_DMA_STATUS_REG) & 1);
    IO_WRITE(RDP_DMA_START_REG, osVirtualToPhysical(bufPtr));
    IO_WRITE(RDP_DMA_END_REG, osVirtualToPhysical(bufPtr) + size);
    return 0;
}
