#ifndef AUDIO_HASHTABLE_H
#define AUDIO_HASHTABLE_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LISTNODE.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/VECTOR4F.H"

extern void HashTable_InitializeResourceTable(s32 capacity);

extern void HashTable_RemoveResourceByKey(s32 resourceKey);
extern s32 HashTable_RoundCapacityToPowerOfTwo(s32 mask);
#endif
