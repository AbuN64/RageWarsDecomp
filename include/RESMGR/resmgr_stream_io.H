#ifndef RESMGR_RESMGR_STREAM_IO_H
#define RESMGR_RESMGR_STREAM_IO_H
#include "COMMON/MEMORY_STREAM_BUFFER.H"

/* An open callback consumes the name and mode byte strings and returns a stream handle. */
typedef s32 (*ResourceOpenCallback)(const void *name, const void *mode);
extern s32 XStdio_OpenStream(const void *name, const void *mode);
extern void XStdio_InitializeStreams(void);
extern void XStdio_ShutdownStreams(void);
extern s32 XStdio_ReadStream(void *destination, s32 elementSize, s32 count, s32 handle);
typedef s32 (*ResourceReadCallback)(s32 handle, void *destination, s32 bytes);
#endif
