#ifndef LIBULTRA_IO_EPIRAWREAD_H
#define LIBULTRA_IO_EPIRAWREAD_H
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OSPIHANDLE_S.H"
extern s32 osEPiRawReadIo(struct OSPiHandle_s *handle, u32 address, u32 *value);
#endif
