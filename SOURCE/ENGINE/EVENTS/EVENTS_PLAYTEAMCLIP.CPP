#include "COMMON/GAMEPLAY_CAMERA.H"
#include "RENDER/RANGENODE.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/LONE/CONTROLLER_RUMBLE_POOL.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "ENGINE/EVENTS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/WORLD.H"
#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
extern f32 k_eventEmitterAndClipScaleConstants;
extern void Events_ApplyDamageEvent(void *, s32, s32, Triple, struct IntPair, s32, s32, s32);


extern void CScene_StartEventClips(void *, void *, s32, Triple, f32, f32);

/* Plays an effect at a position through SoundElement_PlayPositionedSoundWithScale unless the global g_simpleObjectPauseState is set, selecting the target from the given object's type and team masks and choosing the scale from the global option flags. Adapted from Events_PlayClipEvent with the null object test and case 2 removed, a team test for case 0, a mask test for case 1, and the scale constants changed. */













/* Effect callback that fires only near an object's height: when the event's height lies within k_eventUpperHeightRange below or k_eventLowerHeightRange above the object's y at 0xC, it forwards the event to Events_ApplyDamageEvent with mode 1 and flags 0x200. */









static inline void fire(char *sourceActor, s32 target, s32 kind, Triple position, struct IntPair params)
{
    Events_ApplyDamageEvent((void *)sourceActor, target, kind, position, params, 1, 0, 0x200);
}

void Events_ApplyFlag400RadialKnockback(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent((void *)source, target, kind, position, params, 1, 1, 0x400);
}

void Events_StartActorEmitter(ActorEmitterSource *sourceActor, ContextEventsStartActorEmitter *targetContext, s32 unused2, Triple emitterPosition, ParamsEventsStartActorEmitter emitterParams) {
    void *resource;

    if ((sourceActor->actorKind == 1) && (sourceActor->flags & 0x300000)) {
        resource = &((ControllerProfile *)targetContext->inner->resource)->effectPool;
        emitterPosition.x = 0;
        emitterPosition.y = 0;
        emitterPosition.z = 0;
    } else {
        resource = &g_controllerRumblePool;
    }

    CScene_StartEventClips(&g_world, resource, emitterParams.value, emitterPosition,
                  emitterParams.angle * *(&k_eventEmitterAngleConstants + 1), emitterParams.scale * k_eventEmitterAndClipScaleConstants);
}

void Events_IgnoreEvent(int unusedSource, int unusedTarget, int unusedKind, int unusedPosition, ...)
{
  int constantTrue;
  float constantTrueFloat;
  constantTrue = 1;
  constantTrueFloat = (float) constantTrue;
  if (constantTrueFloat)
  {
  }
}

void Events_PlayTeamClip(EventMaskActorView *sourceActor, EventMaskActorView *targetActor, s32 unusedEventKind, CVector3 soundPosition,
                   EventCounterParameters clipParams) {
    s32 *global = &g_gameSession.clockPaused;
    s32 selected;
    f32 scale;

    scale = (&k_eventEmitterAndClipScaleConstants)[1];
    selected = -1;
    if (global[0] != 0) {
        return;
    }

    switch (targetActor->type) {
    case 0:
        if (sourceActor->kind->team != clipParams.team) {
            return;
        }
        selected = targetActor->value;
        break;
    case 1:
        if (targetActor->kind->value == targetActor->type) {
            if (global[-371] & 0x40) {
                scale = k_teamClipFlagFortyScale;
            } else if (global[-371] & 0x20) {
                scale = k_teamClipFlagTwentyScale;
            }
        }
        if ((targetActor->mask & (1 << clipParams.team)) == 0) {
            return;
        }
        break;
    }

    SoundElement_PlayPositionedSoundWithScale(clipParams.value, soundPosition, 0, selected, scale);
}

void Events_SpawnFilteredActorEffect(void *actor, Filter *filter, s32 unusedEventKind, Triple position, struct IntPair effectParams) {
    EffectSpawnModeView *object = actor;
    switch (filter->type) {
    case 0:
        if (object->team != effectParams.second) {
            return;
        }
        break;
    case 1:
        if (!(filter->mask & (filter->type << effectParams.second))) {
            return;
        }
        break;
    }
    Barrel_SpawnActorEffect(actor, effectParams.first, position, 0);
}

void Events_FireWithinHeightRange(char *sourceActor, s32 target, s32 kind, TripleEventsFireWithinHeightRange eventPosition, struct IntPair params)
{
    LevelActor *actor = (LevelActor *)sourceActor;
    f32 d = actor->position0.y - eventPosition.y;

    if (d < 0.0f ? -d <= k_eventLowerHeightRange : d <= k_eventUpperHeightRange) {
        fire(sourceActor, target, kind, *(Triple *)&eventPosition, params);
    }
}

void Events_SetActorEventBit(void *sourceActor, s32 unused1, s32 unused2, s32 eventPositionBase, s32 unused4, s32 unused5, s32 unused6) {
    u8 actorKind = *(u8 *)sourceActor;
    if (actorKind == 1) {
        s32 *p = &eventPositionBase;
        ((Field_s32_2E0 *)(sourceActor))->value = ((Field_s32_2E0 *)(sourceActor))->value | (actorKind << p[3]);
    }
}

void Events_ClearActorEventBit(void *actor, s32 unused1, s32 unused2, s32 eventPositionWord, s32 unused4, s32 unused5, s32 unused6) {
    u8 actorKind = *(u8 *)actor;
    if (actorKind == 1) {
        s32 *p = &eventPositionWord;
        ((Field_s32_2E0 *)(actor))->value = ((Field_s32_2E0 *)(actor))->value & ~(actorKind << p[3]);
    }
}
