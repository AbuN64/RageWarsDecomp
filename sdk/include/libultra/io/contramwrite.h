#ifndef LIBULTRA_IO_CONTRAMWRITE_H
#define LIBULTRA_IO_CONTRAMWRITE_H
u32 __osContRamWrite(s32 completionQueue, s32 channel, u16 blockAddress, u8 *inputData, s32 forceWrite);
#endif
