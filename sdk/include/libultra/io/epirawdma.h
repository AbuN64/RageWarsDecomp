#ifndef LIBULTRA_IO_EPIRAWDMA_H
#define LIBULTRA_IO_EPIRAWDMA_H
struct OSPiHandle_s;
s32 __osEPiRawStartDma(struct OSPiHandle_s *pihandle, s32 direction, u32 devAddr, void *dramAddr, u32 size);
#endif
