#ifndef LIBULTRA_LIBULTRA_RECEIVEDEBUGLINKIMAGE_H
#define LIBULTRA_LIBULTRA_RECEIVEDEBUGLINKIMAGE_H
s32 Libultra_DispatchDebugLinkCallback(void);
s32 Libultra_ReadDebugLinkHalfword(void);
s32 Libultra_ReadDebugLinkWord(void);
s32 Libultra_ReceiveDebugLinkImage(void);
s32 Libultra_WriteDebugLinkHalfword(void);
s32 Libultra_WriteDebugLinkWord(void);
#endif
