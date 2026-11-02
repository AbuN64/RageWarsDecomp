#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "RENDER/RANGENODE.H"
#include "TYPES.H"

/* Calls Barrel_SetLoopingSound_EventsIncrementnearbyplayercounter on an object, its block at offset 0x170 and a stack argument when the pause word is clear, the object exists and its first byte is one. Adapted from Events_StopActorLoopingSound with the pause-word test, the callee and the extra stack argument changed, and the call wrapped in do-while(0) so the stack argument loads at entry. */


extern void Barrel_SetLoopingSound(u8 *, u8 *, s32);

void Events_SetActorLoopingSound(void *unused, u8 *object, s32 third, struct IntPair pair, s32 fifth, s32 sixth) {
    if (g_gameSession.clockPaused == 0 && object != 0 && object[0] == 1) {
        do {
            Barrel_SetLoopingSound(object, &((LevelActor *)object)->behaviorFlags, sixth);
        } while (0);
    }
}

/* Calls Barrel_StopActorLoopingSound on an object and its block at offset 0x170 when the object exists and its
   first byte is one. The fourth argument is a record passed by value whose first word lands in
   its home slot. */


extern void Barrel_StopActorLoopingSound(u8 *, u8 *);

void Events_StopActorLoopingSound(void *unused, u8 *object, s32 third, struct IntPair pair) {
    if (object != 0 && object[0] == 1) {
        Barrel_StopActorLoopingSound(object, &((LevelActor *)object)->behaviorFlags);
    }
}

/* Damages the owner of a live actor (kind 1 with either blast bit of 0x300000 set) that is inside
   the blast: the radius is blastRadius scaled by k_nearbyPlayerBlastConstants[1], and when the squared radius still covers
   the squared distance from the owner's position at 8 to player's position at 8, the remaining
   fraction of the squared radius times blastDamage is applied through Playerai_AddCappedEventCounter. */











extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
extern void Playerai_AddCappedEventCounter(EventCounterPlayerView *, s32);

void Events_IncrementNearbyPlayerCounter(EventCounterActorView *sourceActor, Player *player, s32 unusedKind, Blast blast) {
    CVector3 delta;
    EventCounterPlayerView *owner;
    f32 range;
    f32 dist;

    if (sourceActor->kind == 1 && (sourceActor->flags & 0x300000) != 0) {
        owner = sourceActor->owner;
        if (owner->alive != 0) {
            range = (f32)blast.radius * k_nearbyPlayerBlastConstants[1];
            Graphu64_SubtractVectors(&delta, &owner->pos, &player->pos);
            dist = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
            range = range * range;
            if (range < dist) {
                return;
            }
            Playerai_AddCappedEventCounter(owner, (s32)(((range - dist) / range) * (f32)blast.damage) & 0xFFFF);
        }
    }
}

void Events_SetActorEffectMode(LevelActor *actor, int unusedTarget, int unusedKind, Blast blast) {
    actor->effectMode = (u8)blast.radius;
}

/* Calls Barrel_StopActorLoopingSound on an object and its block at 0x170, sets bit 0x20 in that block's first word, clears flags 0x10000, 0x2000 and 0x100 at offset 0x100, and calls Animpool_ReleaseSceneEffect when flag 0x80000 remains set. Adapted from Link_DeactivateActorState with the block taken at offset 0x170 of the object, a by-value record added as the fourth argument, and each flag update written as a compound assignment to memory. */


extern void Animpool_ReleaseSceneEffect(void *node);




void Events_DeactivateActor(u8 *object, s32 second, s32 third, struct IntPair pair) {
    Barrel_StopActorLoopingSound(object, &((LevelActor *)object)->behaviorFlags);
    ((LevelActor *)object)->behaviorFlags |= 0x20;
    ((LevelActor *)object)->flags &= 0xFFFEFFFF;
    ((LevelActor *)object)->flags &= ~0x2000;
    ((LevelActor *)object)->flags &= ~0x100;
    if (((LevelActor *)object)->flags & 0x80000) {
        Animpool_ReleaseSceneEffect(object);
    }
}
