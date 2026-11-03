#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/OBJ.H"
#include "COMMON/REC.H"
#include "TYPES.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "ANIMPOOL/ANIMPOOL_SPAWNDESCRIBEDSCENEEFFECT.H"
#include "CBARREL/BARREL_SPAWNFLAGGEDEFFECTS.H"
#include "LINK/LINK_DISPATCHMATCHINGTRIGGERS.H"
#include "TURRETAI/TURRET_TRACKTARGET.H"






extern void Rumble_SetActorStateBit(Shared_World *, void *, s32);





extern s32 Rumble_TestActorStateBit(void *, void *);

void Turret_Code_IDLE(void *actor, void *state) {
    if (Turret_TrackTarget(actor, state) != 0) {
        Actor_RequestActorState(actor, state, 63);
    }
}

void Turret_Code_FIRE(void *actor, void *state) {
    if (Turret_TrackTarget(actor, state) == 0) {
        Actor_RequestActorState(actor, state, 62);
    }
}

void Turret_Setup_DEATH(void *actor, void *state) {
    LevelActor *actorView = actor;
    ActorMotionState *stateView = state;
    ActorMotionDefinition *motion;
    s32 clearedFlags;
    Shared_World *world;

    motion = &((ActorMotionResource *)actorView->definition)->motion;
    Barrel_SpawnFlaggedEffects(actor, state, 4, motion->eventMask, motion->secondaryEventMask);
    world = &g_world;
    stateView->event = 0;
    Rumble_SetActorStateBit(world, actor, 1);
    Link_DispatchActorLinks(actor, 1, actor);
    clearedFlags = actorView->flags & 0xFFFEFFFF;
    actorView->flags = clearedFlags;
    if (world->mode != 4) {
        actorView->flags = clearedFlags | 0x08000000;
    }
}

void Turret_Code_DEATH(LevelActor *actor, ActorMotionState *state) {
    if ((state->actionPending != 0) && (actor->flags & 0x80000)) {
        Animpool_ReleaseSceneEffect(actor);
    }
}

void Turret_LinkEffect_MakeVisible(Shared_Actor *actor) {
    if (Rumble_TestActorStateBit(&g_world, actor) == 0) {
        actor->weaponFlags |= 0x2100;
    }
}
