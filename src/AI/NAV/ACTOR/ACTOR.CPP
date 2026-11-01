#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "AI/SOURCE.H"
#include "AI/ACTOR_SETUP_VERSIONS.H"
#include "TYPES.H"
#include <ultra64.h>
#include "UI/X_FILES/X_PLUS.H"

/* 80212C90_18.CPP */
/* Seeds an actor record from its definition: clears the sound handle, pending flag and channel, copies the
   definition's first, second and send bytes into the source object, and takes the health from the
   definition (unsigned for kinds 1 and 4, with kind 1's two levels; signed short for kind 7). For kinds 1
   and 4 the scene mask scales it: 8 by g_actorSceneMaskEightHealthLimits with a floor and no second level, 0x20 by
   g_actorSceneMaskTwentyHealthScale with second level g_actorSceneMaskTwentySecondaryLevel. The health is kept as 24.8 fixed point. */
void Actor_ApplyActorDefinition(Dest *actor, void *def, CVector3 position, Source *source) {
    s32 send;
    s32 first;
    s32 second;
    f32 pitch;
    f32 level;
    f32 level2;
    f64 wide;
    f32 scaled;
    s32 raw;

    send = 0;
    level = g_actorDefaultLevelPair;
    level2 = (&g_actorDefaultLevelPair)[1];
    first = 0;
    second = 0;
    actor->handle = -1;
    actor->pending = 0;
    actor->channel = -1;
    pitch = level;
    if (def != 0) {
        send = ((ActorDefinitionHeader *)def)->send;
        first = ((ActorDefinitionHeader *)def)->first;
        second = ((ActorDefinitionHeader *)def)->second;
        switch (((ActorDefinitionHeader *)def)->kind) {
        case 1:
            raw = ((ActorHealthDefinition *)def)->health;
            wide = raw;
            if (raw < 0) {
                wide += g_actorKindOneUnsignedHealthBias;
            }
            level = ((MovementDescriptor *)def)->level;
            level2 = ((MovementDescriptor *)def)->secondaryLevel;
            pitch = wide;
            break;
        case 4:
            raw = ((ActorHealthDefinition *)def)->health;
            wide = raw;
            if (raw < 0) {
                wide += g_actorKindFourUnsignedHealthBias;
            }
            pitch = wide;
            break;
        case 7:
            pitch = ((PickupHealthDefinition *)def)->health;
            break;
        }
        if (((ActorDefinitionHeader *)def)->kind == 1 || ((ActorDefinitionHeader *)def)->kind == 4) {
            switch (g_gameSettings.sceneMask) {
            case 8:
                scaled = pitch * g_actorSceneMaskEightHealthLimits;
                level2 = 0.0f;
                if (scaled < (&g_actorSceneMaskEightHealthLimits)[1]) {
                    scaled = (&g_actorSceneMaskEightHealthLimits)[1];
                }
                pitch = scaled;
                break;
            case 32:
                level2 = g_actorSceneMaskTwentySecondaryLevel;
                pitch *= g_actorSceneMaskTwentyHealthScale;
                break;
            }
        }
    }
    source->send = send;
    source->first = first;
    source->second = second;
    actor->health = pitch;
    actor->level = (s32) level;
    actor->secondaryLevel = (s32) level2;
    actor->health <<= 8;
    actor->maxHealth = actor->health;
}

/* Builds an actor record from its source object: clears the record (keeping animation), applies the
 * definition, installs this version's two behaviour tables, seeds the position, height and scale copies,
 * the sentinel indices (-1) and the unit scales, clears the attach count and its flag bit, runs the
 * optional spawn callback, and sets the attach count when the source has bit 27 of its flags. */
typedef struct ActorSpawnCallbacks {
    void (*onSpawn)(Source *, Dest *);
} ActorSpawnCallbacks;
extern char ACTOR_TABLE_A;
extern char ACTOR_TABLE_B;
extern f32 Region_GetPolygonHeight(void *, f32, f32);
void Actor_InitSpawnedActor(Source *source, Dest *actor, ActorSpawnCallbacks *callbacks) {
    void *saved;
    void *surface;
    f32 scale;
    s32 value;
    u32 bits;

    saved = actor->animation;
    XPlus_FillMemory(actor, 0, sizeof(Dest));
    actor->flags = 0x40;
    actor->animation = saved;
    Actor_ApplyActorDefinition(actor, source->definition, source->position, source);
    actor->callback11C = &ACTOR_TABLE_A;
    actor->draw = &ACTOR_TABLE_B;
    actor->state = -1;
    actor->old_state = -1;
    actor->entry = NULL;
    actor->initialPosition = source->position;
    actor->previousPosition = source->position;
    actor->animationCount[0] = 0;
    actor->animationCount[1] = 0;
    actor->animationCount[2] = 0;
    actor->initialHeight = source->height;
    actor->cueTimer = 0;
    actor->reserved78[0] = 0;
    actor->reserved78[1] = 0;
    actor->reserved78[2] = 0;
    actor->reserved78[3] = 0;
    actor->reserved78[4] = 0;
    actor->height8C = source->height;
    actor->height90 = source->position.y;
    actor->height9C = source->height;
    actor->positionA0 = source->position;
    actor->surfaceAC = source->surface;
    actor->positionB0 = source->position;
    surface = source->surface;
    actor->surfaceBC = surface;
    if ((source->definition->gate & 4) && surface != NULL) {
        actor->positionB0.y = Region_GetPolygonHeight(surface, actor->positionB0.x, actor->positionB0.z);
    }
    scale = 1.0f;
    value = -1;
    actor->state_result = value;
    value = 20;
    actor->state13 = value;
    value = 0xFF;
    actor->state95 = value;
    bits = -1;
    actor->result = bits;
    actor->old_state = bits;
    actor->state14[0] = bits;
    actor->state14[1] = bits;
    actor->state14[2] = bits;
    actor->state14[3] = bits;
    actor->channel = bits;
    actor->state96 = bits;
    actor->count = 0;
    actor->reservedD0 = 0;
    actor->reservedWordBeforeTail = 0;
    actor->reserved44 = 0;
    actor->state12 = 0;
    actor->reserved1C[0] = 0;
    actor->reserved1C[1] = 0;
    actor->reserved1C[2] = 0;
    actor->reserved1C[3] = 0;
    actor->pending = 0;
    actor->state94 = 0;
    actor->sound = NULL;
    actor->scale = scale;
    actor->entry_scale = scale;
    actor->flags &= ~1;
    actor->initialScale = scale;
    if (callbacks != NULL && callbacks->onSpawn != NULL) {
        callbacks->onSpawn(source, actor);
    }
    bits = 0x8000000;
    if (source->flags & bits) {
        actor->count = 1;
    }
}

/* 800C6E84_10.CPP */

