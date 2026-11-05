#ifndef MENU_PAK_ALLOCATERENDERBUFFERS_H
#define MENU_PAK_ALLOCATERENDERBUFFERS_H
#include "types.h"
extern s32 Note_NeedsIdRepair(s32 ch);
extern s32 Note_ContainsInvalidNameByte(u8 *name, s32 size);
extern u32 Note_BytesToPakPages(u32);
extern u32 Note_Crc32(const void *data, u32 byteCount, u32 initialCrc);
#endif
