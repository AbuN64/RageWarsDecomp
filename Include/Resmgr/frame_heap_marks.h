#ifndef RESMGR_FRAME_HEAP_MARKS_H
#define RESMGR_FRAME_HEAP_MARKS_H
#include "Common/record.h"
extern void ESmem_PushFrameHeapMark(void);
extern void ESmem_ResetFrameHeapUsageRanges(void);
extern void ESmem_SwapFrameHeap(void);
#endif
