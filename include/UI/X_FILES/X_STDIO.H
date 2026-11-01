#ifndef UI_X_FILES_X_STDIO_H
#define UI_X_FILES_X_STDIO_H
#include "TYPES.H"
extern s32 g_stdioFormatBuffer;

extern s32 XStdio_PrintStream(void *stream, const char *format, ...);
extern void XStdio_InitializeStreams(void);
extern void XStdio_ShutdownStreams(void);
extern s32 XStdio_OpenStream(const void *name, const void *mode);
extern s32 XStdio_ReadStream(void *destination, s32 elementSize, s32 count, s32 handle);
extern s32 XStdio_WriteStreamNoop(const unsigned char *data, s32 size, s32 count, void *stream);
extern int XStdio_ReadUnavailable(void);
extern s32 XStdio_SeekStream(s32 handle, s32 offset, s32 origin);
extern void XStdio_QueryStreamPosition(void);
extern void XStdio_QueryStreamEnd(void);
extern s32 XStdio_ReadCharacter(s32);
extern int XStdio_WriteUnavailable(void);
extern s32 *XStdio_FormatScratchArgumentList(s32, s32);
extern void XStdio_LoadMemoryStream(void);
extern void XStdio_FreeMemoryStream(void);
extern s32 XStdio_OpenMemoryStream(const void *name, const void *mode);
extern void XStdio_CloseMemoryStream(void);
extern s32 XStdio_ReadMemoryStream(s32 handle, void *destination, s32 bytes);
extern int XStdio_WriteMemoryStreamNoop(void);
extern s32 XStdio_SeekMemoryStream(s32 handle, s32 offset, s32 origin);
extern unsigned int XStdio_TellMemoryStream(void);
extern int XStdio_IsMemoryStreamAtEnd(void);
extern void XStdio_SetTextOutputCallbacks(int first, int second);
#endif
