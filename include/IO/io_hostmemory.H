#ifndef IO_IO_HOSTMEMORY_H
#define IO_IO_HOSTMEMORY_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
extern void Libsn_FillPortBytes(s32 address, s32 value, u32 count);
extern void Libsn_CopyPortBytes(s32 address, s32 port, s32 count);
extern void Libsn_TransferHostMemoryRanges(u32 mode);
extern void Libsn_CopyHostBlockToCart(void);
extern void Libsn_WriteTransferPortByte(s32, unsigned char);
extern void Libsn_WritePortBuffer(s32 address, const u8 *source, u32 length);
extern void Libsn_WritePortBufferWithDma(u32 address, u8 *source, u32 remaining);
extern void Libsn_InitializeHostMemoryAccess(void);
extern void Libsn_ServiceHostCommands(void);
extern s32 Libsn_MeasureTerminatedString(u8 *);
extern void Libsn_InitializeHostRequestThread(s32 threadPriority);
extern s32 Libsn_SendHostCommand(s32, s32, s32, s32);
extern void Libsn_RunHostRequestThread(void);
extern s32 Libsn_InitializePollingHost(void);
extern void *Libsn_InitializeQueuedHost(void);
extern u32 Libsn_SendHostStringRequest(u8 *buffer, s32 argument);
extern s32 Libsn_SendHostNameFlags(u8 *name, u32 flags);
extern s32 Libsn_SendHostScalarRequest(s32);
extern s32 Libsn_ReadHostChannel(s32 channel, u8 *destination, u32 remaining);
extern s32 Libsn_WriteHostChannel(s32 channel, u8 *source, u32 remaining);
extern s32 Libsn_SendHostTripleRequest(s32, u32, s32);
#endif
