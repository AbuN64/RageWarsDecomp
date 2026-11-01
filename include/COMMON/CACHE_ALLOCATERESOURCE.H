#ifndef COMMON_CACHE_ALLOCATERESOURCE_H
#define COMMON_CACHE_ALLOCATERESOURCE_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

void **Cache_AllocateResource(s32, s32, s32, char *);
extern const char g_pakPakStateNoteName[16];

extern struct PakDirectory *g_controllerPakNoteLists;
#endif
