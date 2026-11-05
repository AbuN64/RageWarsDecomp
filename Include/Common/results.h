#ifndef COMMON_RESULTS_H
#define COMMON_RESULTS_H
#include "Common/effect_slot_pool.h"
#include "types.h"
#include "Common/level_actor.h"
extern float g_effectDefaultUpperBound;



struct SceneEffect;
typedef struct SceneEffect SceneEffect;








struct SceneEffect;
struct ActorDefinitionHeader;
/* CAnimPool allocates 32 full actors, each with its own list links and counted owner. */
struct SceneEffect {
    LevelActor actor; /* +0x0, extent 0x2E8 */
    struct SceneEffect *previous; /* +0x2E8 */
    struct SceneEffect *next; /* +0x2EC */
    s32 *ref; /* +0x2F0 */
    u8 unknown2F4[4];
};

/* Shared object layout established by effect-pool consumers. */
struct CAnimPool {
    SceneEffect DynAnims[32]; /* 0x0000 */
    IntrusiveList FreeList; /* 0x5F00 */
    IntrusiveList UsedList; /* 0x5F14 */
};
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"



struct SceneEffect;
struct EffectSlotPool;





















/* Resident resource chunks have two count/stride words followed by byte payload. */
typedef struct ResidentDataChunk {
    s32 width;
    s32 count;
    u8 data[1];
} ResidentDataChunk;
#endif
