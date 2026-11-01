#ifndef RDP_DMA_IO_H
#define RDP_DMA_IO_H
#include "TYPES.H"
#include <ultra64.h>

/* Uncached RDP DMA registers; every access retains the shared volatile word type. */
#define RDP_DMA_START_REG 0xA4100000U
#define RDP_DMA_END_REG 0xA4100004U
#define RDP_DMA_STATUS_REG 0xA410000CU
#endif
