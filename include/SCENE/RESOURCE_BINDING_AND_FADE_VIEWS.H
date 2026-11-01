#ifndef SCENE_RESOURCE_BINDING_AND_FADE_VIEWS_H
#define SCENE_RESOURCE_BINDING_AND_FADE_VIEWS_H
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "COMMON/MANAGER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct Manager {
    OSMesgQueue requests;
    OSMesg requestMessages[64];
    u8 requestStorage[2348 - sizeof(OSMesgQueue) - 64 * sizeof(OSMesg)];
    IntrusiveList pending;
    IntrusiveList active;
    char padActive[0x20 - sizeof(IntrusiveList)];
    char lock[24];
    char reservedBytes[0x24];
    s32 mask;
};
struct GeometryVariantByteView {
    unsigned char padding_0[18];
    signed char propModelIndex;
};
struct OwnerStaticInstanceDrawGeometryVariant {
    char pad0[0x20];
    s32 resourceDescriptor;
    char pad24[4];
    char transform[168];
    s32 flagsD0;
    char padD4[6];
    u8 colorFrame;
};
struct ActorResourceStatusView {
    char pad0[0x18];
    char * geometryVariant;
    char pad18[0xD8 - 0x18 - sizeof(char*)];
    unsigned short statusFlags;
};
struct CacheAllocationNodeView {
    int payload;
    int reservedWord;
    int reservedWord1;
    int reservedWord2;
};
/* Shared object layout established by resource-binding consumers. */
struct ResourceBinding {
    u8 padding000[1];
    s8 variant; /* 0x01 */
    u8 padding002[0x1E];
    s32 *resource; /* 0x20: loaded resource descriptor */
    u8 padding024[4];
    u8 transform[140]; /* 0x28 */
    void *loadedResource; /* 0xB4 */
    u8 runtimeState[24]; /* 0xB8 */
    s32 registrationFlags; /* 0xD0 */
    u8 padding0D4[4];
    u16 status; /* 0xD8 */
    u8 colorFrame; /* 0xDA */
};
/* Actor resource fade selects the near/far value using its frame threshold. */
struct ResourceFadeDefinition {
    u8 reserved0[0xE];
    s8 nearValue; /* 0xE */
    s8 farValue; /* 0xF */
    u8 reserved10[0x14];
    u32 threshold; /* 0x24 */
};
struct ResourceNodePair {
    CacheResourceNode *first;
    CacheResourceNode *second;
};
/* Resource manager slot and its wait queue (g_resourceSlotLockState / g_resourceHeapLockQueue). */
typedef struct ResourceLockState {
    s32 slot;
    u8 reserved4[0xB98 - 4];
    OSMesgQueue waitQueue;
} ResourceLockState;
extern int Statinst_SelectDistanceVariant(void *object);
extern void Statinst_RefreshResourceUsage(void *resourceBinding);
extern s8 Statinst_SelectGameModeVariant(struct LevelActor *actor);
extern void Statinst_DrawForGameMode(void *);
extern CachedResource *Cache_RequestPairedResource(s32 unused, s32 key, CachedResource *first, CachedResource *second, s32 mode, void *owner, void *tag, void *spare, s32 async);
#endif
