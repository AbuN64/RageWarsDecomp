#ifndef MENU_PAK_NOTE_NOTE_CREATEANDWRITENOTE_SYMBOLS_H
#define MENU_PAK_NOTE_NOTE_CREATEANDWRITENOTE_SYMBOLS_H
#include "types.h"
struct PakRecord;
extern OSPfs g_controllerPakFileSystems[];
extern u8 g_controllerPakFrontendState;
extern struct PakRecord g_controllerPakChannelRecords[];
extern s32 Pfs_ReadWriteFile(OSPfs* pfs, s32 file_no, u8 flag, int offset, int size_in_bytes, u8* data_buffer);
#endif
