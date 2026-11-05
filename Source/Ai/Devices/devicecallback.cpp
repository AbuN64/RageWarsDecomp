#include "Common/animationtriggerdefinition.h"
#include "Common/audio_callbacks.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/ballisticparams.h"
#include "Common/shared_gameslot.h"
#include "Common/level_actor.h"
#include "Common/world.h"
#include "Common/breakable_hits.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/animation_pool.h"
#include "Common/listheader.h"
#include "types.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Weapons/actor_requestactorstate.h"
#include "Cbarrel/barrel_spawnflaggedeffects.h"
#include "Gobjinst/player_drawtintedplayer_data.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Geometry/geometry_drawblendparts.h"

void Device_RespondToActivation(Obj54E0 *actor, void *responseContext) {
    Rec54E0 *activationRecord;

    activationRecord = &actor->holder->r;
    actor->flags = actor->flags & 0xFFFEFFFF;
    Link_DispatchActorLinks(actor, 0x40000, actor);
    if (activationRecord->activationMode == 0) {
        actor->flags &= ~0x2000;
        actor->flags &= ~0x100;
    }
    if (g_world.mode == 4) {
        if (activationRecord->soundIdWord.whole != -1) {
            SoundElement_PlaySoundAtPosition(activationRecord->soundIdWord.half.id, actor->pos.v, 0, -1);
        }
        if (activationRecord->spawnEffectKind != -1) {
            Barrel_SpawnActorEffect(actor, activationRecord->spawnEffectKind, actor->pos.t, 0);
        }
        Barrel_SpawnFlaggedEffects(actor, responseContext, 8, activationRecord->primaryEffectMask, activationRecord->secondaryEffectMask);
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

/** Return the object's status bit that marks it active. */
unsigned int Device_GetHitStateBit(void *object) {
    struct Hit *hit = object;
    return hit->flags & 0x200;
}

int Device_IsHitStateBitClear(Hit *hitRecord) {
    return ((hitRecord->flags >> 9) ^ 1) & 1;
}
