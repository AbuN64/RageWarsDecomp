#ifndef FRONTEND_SYMBOLS_H
#define FRONTEND_SYMBOLS_H
#include "Engine/lighting.h"
#include "Engine/Unicol/unicol.h"
#include "Ai/nav_symbols.h"
#include "Ai/ai_shared_symbols.h"
#include "Engine/Instance/gobjinst.h"
#include "Ai/player_symbols.h"
#include "types.h"
#include "Common/ccollisioninfo2_t.h"
struct CollisionInfoSlot;
/* One 32-byte collision slot: the 28-byte collision response followed by 4 bytes the setup table never reads. */
typedef struct CollisionInfoSlot {
    CCollisionInfo2_t info;
    u8 reserved[4];
} CollisionInfoSlot;
extern struct CollisionInfoSlot g_particleCollisionProbeResult[17];
#if (defined(VERSION_US))
extern struct CollisionInfoSlot g_collisionInfoSlotsB[17];
extern s32 g_globalGameplayFlags[];
#endif
#endif
extern char g_ResourcesEncodedWords[];
