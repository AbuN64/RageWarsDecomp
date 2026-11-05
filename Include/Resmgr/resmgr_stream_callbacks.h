#ifndef RESMGR_RESMGR_STREAM_CALLBACKS_H
#define RESMGR_RESMGR_STREAM_CALLBACKS_H
#include "Common/memory_stream_buffer.h"
#include "Resmgr/resmgr_stream_io.h"

/* Stream seek callbacks preserve the handle, byte offset and origin, and return status. */
typedef s32 (*ResourceSeekCallback)(s32 handle, s32 offset, s32 origin);
extern s32 XStdio_SeekStream(s32 handle, s32 offset, s32 origin);
extern void XStdio_CloseMemoryStream(void);
extern s32 XStdio_ReadCharacter(s32 streamId);
extern s32 XStdio_OpenMemoryStream(const void *name, const void *mode);
extern void XStdio_LoadMemoryStream(void);
extern void XStdio_SetStreamCallbacks(ResourceOpenCallback openCallback, s32 openContext, ResourceReadCallback readCallback, s32 readContext, ResourceSeekCallback seekCallback, void (*closeCallback)(void), void (*writeCallback)(void));
extern void XStdio_QueryStreamPosition(void);
extern void XStdio_FreeMemoryStream(void);
extern void XStdio_QueryStreamEnd(void);
#endif
