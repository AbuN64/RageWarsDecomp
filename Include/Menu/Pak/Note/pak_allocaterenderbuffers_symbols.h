#ifndef MENU_PAK_NOTE_PAK_ALLOCATERENDERBUFFERS_SYMBOLS_H
#define MENU_PAK_NOTE_PAK_ALLOCATERENDERBUFFERS_SYMBOLS_H
#include "types.h"
struct PakRecord;
extern struct PakRecord g_controllerPakChannelRecords[];
extern const char s_bufferText[9];  /* "Z-Buffer" */
extern char s_displayBufferText[15];    /* "Display Buffer" */
extern char s_colorFramesAndZBufferText[31];    /* "color frame buffers + z buffer" */
extern char s_displayListsText[14];    /* "display lists" */
extern const char s_fifoText[5];     /* "fifo" */
extern char s_audioHeapText[11];    /* "audio heap" */
#endif
