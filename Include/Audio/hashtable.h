#ifndef AUDIO_HASHTABLE_H
#define AUDIO_HASHTABLE_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/sharedplayer.h"
#include "Common/listnode.h"
#include "Common/resident_event_handler.h"
#include "Common/vector4f.h"

extern void HashTable_InitializeResourceTable(s32 capacity);

extern void HashTable_RemoveResourceByKey(s32 resourceKey);
extern s32 HashTable_RoundCapacityToPowerOfTwo(s32 mask);
struct ResourceLoadRequest;
void HashTable_SetResourceByKey(u32 key, struct ResourceLoadRequest *value);
extern s32 g_resourceHashEvenIndexMask;
#endif
