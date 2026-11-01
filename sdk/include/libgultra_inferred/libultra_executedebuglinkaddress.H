#ifndef LIBGULTRA_INFERRED_LIBULTRA_EXECUTEDEBUGLINKADDRESS_H
#define LIBGULTRA_INFERRED_LIBULTRA_EXECUTEDEBUGLINKADDRESS_H
#include "../PERIPHERAL_PORT_BYTE_VIEWS.H"
extern s32 Libultra_WaitDebugLinkReceiveReady(u32 attemptLimit);
extern s32 Libultra_WaitDebugLinkAcknowledgement(u32 attemptLimit);
extern void Libultra_SetDebugLinkMode(s32 mode);
extern void Libultra_SetDebugLinkByteRequest(s32 requested);
extern void Libultra_SetDebugLinkReceiveEnable(s32 enabled);
extern void Libultra_WritePortByteValue(s16 *port, s32 value);
extern s32 Libultra_WaitDebugLinkTransmitReady(u32 attemptLimit);
extern s32 Libultra_ReadDebugLinkMemoryByte(void);
extern void Libultra_SetDebugLinkHandshakeBit(s32 enabled);
extern s32 Libultra_WriteDebugLinkMemoryByte(void);
extern s32 Libultra_WaitDebugLinkRequestAcknowledgement(u32 attemptLimit);
extern void Libultra_SetDebugLinkBlockTransfer(s32 enabled);
extern void Libultra_SetDebugLinkTransmitStrobe(s32 strobe);
extern s32 Libultra_WaitPortStatus(u8 *status, u8 mask, u32 attemptLimit, s32 reload);
extern s32 Libultra_HandshakeDebugLink(void);
extern s32 Libultra_ExecuteDebugLinkAddress(void);
extern int Libultra_DebugLinkAlwaysReady(void);
extern s32 Libultra_GetDebugLinkRequestAcknowledgement(void);
extern u8 Libultra_ReadPortStatusByte(void *port);
extern void Libultra_SetDebugLinkHostRequest(s32 requested);
extern s32 Libultra_CheckDebugLinkAcknowledgement(u32 attemptLimit);
extern void Libultra_SetDebugLinkEnable(s32 enabled);
#endif
