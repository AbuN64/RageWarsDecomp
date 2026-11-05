#ifndef AI_CBARREL_H
#define AI_CBARREL_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/route_chase_records.h"
/* Tracker offsets retained from the folded AI record. Plan describes the aim
 * operation's fields in this same storage, rather than a route-chase bot. */
typedef struct Tracker {
    s32 flags;
    s32 active;
    u8 pad8[0x2C];
    s8 mode;
    u8 pad35[2];
    s8 targetingDisabled;
    u8 pad38[0x30];
    struct LevelActor *self;
    CVector3 offset;
    struct LevelActor *lockedTarget;
    f32 targetTimer;
    struct LevelActor *anchor;
    u8 pad84[4];
    struct LevelActor *target;
    f32 angle;
    f32 height;
    s8 slot;
    u8 pad95[7];
    f32 homeYaw;
    u8 padA0[0x10];
    CVector3 homePos;
    s32 homeRoom;
    u8 padC0[0xE];
    s8 team;
} Tracker;

typedef struct BarrelTargetInfo {
    s32 kind;
    struct LevelActor *target;
    f32 m_DeltaAngle;
    CVector3 m_vTargetPos;
    CVector3 m_vDeltaTargetPos;
    f32 m_DistFrom;
    CVector3 m_vXZTargetPos;
    CVector3 m_vXZDeltaTargetPos;
    f32 m_XZDistFrom;
} BarrelTargetInfo;
extern float g_barrelClearAimClearance;
extern float g_barrelFlaggedAimProbeScale;
extern float k_barrelPrimarySoundRandomMaximum;
extern float k_barrelSecondarySoundRandomMaximum;
struct LevelActor;
struct LevelActor;
#include "Menu/teammenu.h"
#include "Common/runtime_declarations.h"
#include "Cbarrel/cbarrel_resolvetrackgoal_data.h"

extern void Barrel_ClearTargetInfo(struct LevelActor *actorView, void *trackerState, struct BarrelTargetInfo *targetInfo);

extern void Barrel_AddActorYaw(struct LevelActor *actor, f32 yawDelta);

extern void Barrel_FillWordPair(int *value, int word);

extern const f32 g_barrelFlaggedEffectRandomRanges[];

extern s32 Cbarrel_ClassifyTrackTarget(struct LevelActor *actor, struct RouteChaseBot *routeChaseBot, struct LevelActor *targetActor);

extern void Cbarrel_LockTrackerTarget(void *ownerActor, void *trackerState, struct LevelActor *target, float lockDuration);




extern const float g_goalBesideActorClearance;
extern void Barrel_FillDamagePacket(void *packet, s32 damageSource, s32 damage, f32 radius, s32 damageFlags, s32 shield);
#endif
