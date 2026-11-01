#ifndef LIBGULTRA_INFERRED_LIBULTRA_EXCHANGEDEBUGLINKWORDS_H
#define LIBGULTRA_INFERRED_LIBULTRA_EXCHANGEDEBUGLINKWORDS_H
#include "COMMON/RESPONSE.H"
extern s32 Libultra_SendDebugLinkWord(u32 value);
extern s32 Libultra_ReceiveDebugLinkWord(s32 *wordOut);
extern void Libultra_EmptyDebugLinkHook(void);
extern s32 Libultra_SendDebugLinkHalfword(u32 value);
extern s32 Libultra_ReceiveDebugLinkString(u8 *textOut, s32 capacity);
extern s32 Libultra_ReceiveDebugLinkHalfword(u16 *halfwordOut);
extern void Libultra_SetDebugLinkCallback(int callbackAddress);
#endif
