#ifndef IO_LIBSN_DISABLEINTERRUPTS_H
#define IO_LIBSN_DISABLEINTERRUPTS_H
#include "TYPES.H"
extern void Libsn_RestoreInterruptEnable(s32 saved);
extern int Libsn_DisableInterrupts();
extern void Libsn_WritePortWord(s32 address, s32 value);
#endif
