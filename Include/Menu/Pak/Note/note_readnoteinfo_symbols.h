#ifndef MENU_PAK_NOTE_NOTE_READNOTEINFO_SYMBOLS_H
#define MENU_PAK_NOTE_NOTE_READNOTEINFO_SYMBOLS_H
#include "types.h"
extern OSPfs g_controllerPakFileSystems[];
extern u8 g_controllerPakFrontendState;
extern s32 Pfs_ReadWriteFile(OSPfs* pfs, s32 file_no, u8 flag, int offset, int size_in_bytes, u8* data_buffer);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern u8 *g_pakCompanyCodes[], *g_pakCompanyCodes[];
#endif
#endif
