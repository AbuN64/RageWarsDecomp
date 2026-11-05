#ifndef LIBULTRA_IO_EPIRAWREAD_H
#define LIBULTRA_IO_EPIRAWREAD_H
#include "types.h"
#include "Common/vector4f.h"
#include "Common/resident_event_handler.h"
#include "Common/ospihandle_s.h"
extern s32 osEPiRawReadIo(struct OSPiHandle_s *handle, u32 address, u32 *value);
#endif
