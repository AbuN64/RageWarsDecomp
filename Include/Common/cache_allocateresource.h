#ifndef COMMON_CACHE_ALLOCATERESOURCE_H
#define COMMON_CACHE_ALLOCATERESOURCE_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"

void **Cache_AllocateResource(s32, s32, s32, char *);
extern const char g_pakPakStateNoteName[16];

extern struct PakDirectory *g_controllerPakNoteLists;
#endif
