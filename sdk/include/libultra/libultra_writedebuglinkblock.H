#ifndef LIBULTRA_LIBULTRA_WRITEDEBUGLINKBLOCK_H
#define LIBULTRA_LIBULTRA_WRITEDEBUGLINKBLOCK_H
s32 Libultra_ReadDebugLinkBlock(u8 *dst, s32 count, u32 *checksum);
s32 Libultra_WriteDebugLinkBlock(u8 *stream, s32 count);
#endif
