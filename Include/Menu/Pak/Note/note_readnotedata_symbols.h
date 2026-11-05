#ifndef MENU_PAK_NOTE_NOTE_READNOTEDATA_SYMBOLS_H
#define MENU_PAK_NOTE_NOTE_READNOTEDATA_SYMBOLS_H
#include "types.h"
extern u8 g_controllerPakFrontendState;
extern s32 Pfs_ReadWriteFile(OSPfs* pfs, s32 file_no, u8 flag, int offset, int size_in_bytes, u8* data_buffer);
extern OSPfs g_controllerPakFileSystems[];
#endif
