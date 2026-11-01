#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/OBJRECAT30.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/LISTHEADER.H"
#include "TYPES.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"

extern void Geometry_QueueModelInstance(void **, void *, s32, void *, void *, s32);




extern void Scene_SetLevelActorStateBit(void *a, unsigned short b, unsigned short c, int d);

void Device_RespondToActivation(Obj54E0 *actor, void *responseContext) {
    Rec54E0 *rec;

    rec = &actor->holder->r;
    actor->flags = actor->flags & 0xFFFEFFFF;
    Link_DispatchActorLinks(actor, 0x40000, actor);
    if (rec->activationMode == 0) {
        actor->flags &= ~0x2000;
        actor->flags &= ~0x100;
    }
    if (g_world.mode == 4) {
        if (rec->soundIdWord.whole != -1) {
            SoundElement_PlaySoundAtPosition(rec->soundIdWord.half.id, actor->pos.v, 0, -1);
        }
        if (rec->spawnEffectKind != -1) {
            Barrel_SpawnActorEffect(actor, rec->spawnEffectKind, actor->pos.t, 0);
        }
        Barrel_SpawnFlaggedEffects(actor, responseContext, 8, rec->primaryEffectMask, rec->secondaryEffectMask);
    }
}

/** Clear two flags when the controlling byte and nested flag are set. */
void Device_ClearCollisionFlagsOnHit(void *levelActor, void *hitState) {
    LevelActor *object = levelActor;
    BreakableDefinition *nested = (void *)object->definition;
    BreakableHitStateView *state = hitState;
    if (state->active != 0 &&
        (nested->flags & 0x20) != 0) {
        unsigned int flags = object->flags;
        flags &= ~0x2000;
        flags &= ~0x100;
        object->flags = flags;
    }
}

/* Draw callback installed by DamageAI_InitializeDispatch; the animation lookup is
 * the same third callback argument consumed by Gobjinst_DrawActorModelWithViewEffects. */
void Device_DrawSpawnedModel(void *levelActor, void *spawnDispatchOwner, void *modelLookup) {
    LevelActor *actor = levelActor;
    SpawnDispatchOwner *owner = spawnDispatchOwner;
    Lookup *lookup = modelLookup;

    actor->mask = 1 << owner->spawn;
    if (lookup->drawModel != 0) {
        Geometry_QueueModelInstance(lookup->value, actor->animationMatrices, 1,
                        &actor->lighting[g_lightingBufferIndex], 0, owner->remaining);
    }
}

void Device_RequestAndSetActiveState(void *actor, void *requestContext) {
    Actor_RequestActorState(actor, requestContext, 1);
    Rumble_SetActorStateBit(&g_world, actor, 1);
}

void Device_EnableTriggerActor(Trigger *trigger) {
    Scene_SetLevelActorStateBit(&g_world, trigger->owner, trigger->actor, 1);
}

/** Return the object's 0x200 status bit. */
unsigned int Device_GetHitStateBit(void *object) {
    struct Hit *hit = object;
    return hit->flags & 0x200;
}

int Device_IsHitStateBitClear(Hit *hitRecord) {
    return ((hitRecord->flags >> 9) ^ 1) & 1;
}
