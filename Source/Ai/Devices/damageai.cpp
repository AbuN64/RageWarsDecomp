#include "Common/game_session.h"
#include "include_asm.h"
#include "Weapons/actor_requestactorstate.h"
#include "Common/animationtriggerdefinition.h"
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/funcptr.h"
#include "Common/shared_voidcallback.h"
#include "Common/world.h"
#include "Common/breakable_hits.h"
#include "Engine/rumble_setactorstatebit.h"
#if !(defined(VERSION_DE) || defined(VERSION_EU))
#include "Cbarrel/barrel_spawnflaggedeffects.h"
#endif
#if !(defined(VERSION_DE) || defined(VERSION_EU))
#include "Link/link_dispatchmatchingtriggers.h"
#endif

#if !(defined(VERSION_DE) || defined(VERSION_EU))
/* Applies a hit to a damageable object: when its descriptor takes the hit (flag 1 for hits
   without bit 0x200, flag 2 for hits with it) it lowers the health by the damage, not below
   zero, turns the remaining percentage into the damage stage with the lowest threshold above it to set
   the model and time and the stage byte, and runs Actor_RequestActorState_Damageai (kind 2 when the
   descriptor has flag 0x40, else 1) once the health reaches zero. */


void DamageAI_ApplyHitEuropeanExtended(Damageable *damageable, Health *health, Hit *hit)
{
    s32 canHit = 0;
    s32 flags;
    s32 remaining;
    u8 percent;
    u8 best;
    s32 bestIndex;
    s32 i;
    s32 kind;
    Damage *damage;

    flags = damageable->desc->damage.flags;
    damage = &damageable->desc->damage;
    bestIndex = canHit;
    if (flags & 1) {
        canHit = ((hit->flags >> 9) ^ 1) & 1;
    }
    if ((flags & 2) && (hit->flags & 0x200)) {
        canHit = 1;
    }
    if (canHit) {
        remaining = health->health - hit->damage;
        if (remaining < 0) {
            remaining = 0;
        }
        best = 100;
        health->health = remaining;
        percent = ((f32)remaining / (f32)health->maxHealth) * 100.0f;
        for (i = 0; i < 4; i++) {
            if (damage->threshold[i] < best && damage->threshold[i] != 0 &&
                percent < damage->threshold[i]) {
                best = damage->threshold[i];
                bestIndex = i;
            }
        }
        health->model = damage->model[bestIndex];
        health->time = damage->time[bestIndex];
        damageable->stage = damage->model[bestIndex];
        if (health->health == 0) {
            kind = 1;
            if (damageable->desc->damage.flags & 0x40) {
                kind = 2;
            }
            Actor_RequestActorState(damageable, health, kind);
        }
    }
}
#endif

#if defined(VERSION_EU_X)
unsigned int k_damageaiFragment[2] = {
    0x43C00000, 0x3FC90FDC,
};
#endif

#if defined(VERSION_EU)
/* Applies a hit to a damageable object: when its descriptor takes the hit (flag 1 for hits
   without bit 0x200, flag 2 for hits with it) it lowers the health by the damage, not below
   zero, turns the remaining percentage into the damage stage with the lowest threshold above it to set
   the model and time and the stage byte, and runs Actor_RequestActorState_Damageai (kind 2 when the
   descriptor has flag 0x40, else 1) once the health reaches zero. */


void DamageAI_ApplyHitEuropean(Damageable *damageable, Health *health, Hit *hit)
{
    s32 canHit = 0;
    s32 flags;
    s32 remaining;
    u8 percent;
    u8 best;
    s32 bestIndex;
    s32 i;
    s32 kind;
    Damage *damage;

    flags = damageable->desc->damage.flags;
    damage = &damageable->desc->damage;
    bestIndex = canHit;
    if (flags & 1) {
        canHit = ((hit->flags >> 9) ^ 1) & 1;
    }
    if ((flags & 2) && (hit->flags & 0x200)) {
        canHit = 1;
    }
    if (canHit) {
        remaining = health->health - hit->damage;
        if (remaining < 0) {
            remaining = 0;
        }
        best = 100;
        health->health = remaining;
        percent = ((f32)remaining / (f32)health->maxHealth) * 100.0f;
        for (i = 0; i < 4; i++) {
            if (damage->threshold[i] < best && damage->threshold[i] != 0 &&
                percent < damage->threshold[i]) {
                best = damage->threshold[i];
                bestIndex = i;
            }
        }
        health->model = damage->model[bestIndex];
        health->time = damage->time[bestIndex];
        damageable->stage = damage->model[bestIndex];
        if (health->health == 0) {
            kind = 1;
            if (damageable->desc->damage.flags & 0x40) {
                kind = 2;
            }
            Actor_RequestActorState(damageable, health, kind);
        }
    }
}
#endif

#if defined(VERSION_DE)
void DamageAI_ApplyHitGerman(Damageable *damageable, Health *health, Hit *hit)
{
    s32 canHit = 0;
    s32 flags;
    s32 remaining;
    u8 percent;
    u8 best;
    s32 bestIndex;
    s32 i;
    s32 kind;
    Damage *damage;

    flags = damageable->desc->damage.flags;
    damage = &damageable->desc->damage;
    bestIndex = canHit;
    if (flags & 1) {
        canHit = ((hit->flags >> 9) ^ 1) & 1;
    }
    if ((flags & 2) && (hit->flags & 0x200)) {
        canHit = 1;
    }
    if (canHit) {
        remaining = health->health - hit->damage;
        if (remaining < 0) {
            remaining = 0;
        }
        best = 100;
        health->health = remaining;
        percent = ((f32)remaining / (f32)health->maxHealth) * 100.0f;
        for (i = 0; i < 4; i++) {
            if (damage->threshold[i] < best && damage->threshold[i] != 0 &&
                percent < damage->threshold[i]) {
                best = damage->threshold[i];
                bestIndex = i;
            }
        }
        health->model = damage->model[bestIndex];
        health->time = damage->time[bestIndex];
        damageable->stage = damage->model[bestIndex];
        if (health->health == 0) {
            kind = 1;
            if (damageable->desc->damage.flags & 0x40) {
                kind = 2;
            }
            Actor_RequestActorState(damageable, health, kind);
        }
    }
}
#endif

#if defined(VERSION_DE)
void *k_DamageaiData[2] = {
    (void *)g_deviceDrawRomDamageEntry, (void *)g_deviceDrawRomDamageEntry,
};
#endif


struct Owner;

/** Initialize the dest record's vtable-like fields from source's flag byte. */
void DamageAI_InitializeDispatch(LevelActor *source, void *dest) {
    ((SpawnDispatchOwner *)dest)->callbacks = &g_damageDispatchTable;
    ((SpawnDispatchOwner *)dest)->update = &g_damageUpdateRomEntry;
    ((SpawnDispatchOwner *)dest)->draw = &g_deviceDrawRomEntry;
    ((SpawnDispatchOwner *)dest)->hit = &g_damageHitRomEntry;
    ((SpawnDispatchOwner *)dest)->spawn = 0;
    ((SpawnDispatchOwner *)dest)->remaining = source->renderPass;
}

void DamageAI_RequestCurrentActorState(LevelActor *actor, void *requestContext) {
    if (Rumble_TestActorStateBit(&g_world, actor) == 1) {
        Actor_RequestActorState(actor, requestContext, 1);
    } else {
        Actor_RequestActorState(actor, requestContext, 0);
        actor->flags |= 0x10000;
    }
}

void DamageAI_InvokeOwnerCallback(void *callbackContext, Shared_CallbackOwner *callbackOwner) {
    void *callbackHook = callbackOwner->hook;
    if (callbackHook != 0) {
        FuncPtr fn = ((Shared_CallbackHook *)(callbackHook))->callback;
        if (fn != 0) {
            ((void (*)(void *, Shared_CallbackOwner *))fn)(callbackContext, callbackOwner);
        }
    }
}

/** Return the nested record's field, or a fallback constant when zero. */
int DamageAI_GetActivationSound(void *owner) {
    int activationSound = ((Hold5324 *)((struct Owner *)owner)->track)->r.sound;
    if (activationSound != 0) {
        return activationSound;
    }
    return 21300;
}

int DamageAI_GetActivationMode(void *actor) {
    return ((Obj5324 *)actor)->holder->r.activationMode;
}

void DamageAI_ActivateActor(Obj5324 *actor, s32 *activationContext) {
    s32 mode;
    Rec5324 *activationRecord;
    Shared_World *pFlag;

    activationRecord = &actor->holder->r;
    pFlag = &g_world;
    Rumble_SetActorStateBit(pFlag, actor, 1);
    Link_DispatchActorLinks(actor, 0x40000, actor);
    if (activationContext[1] == 0) {
        actor->flags = actor->flags & 0xFFFEFFFF;
    }
    if (activationRecord->activationMode == 0) {
        actor->flags &= ~0x2000;
        actor->flags &= ~0x100;
    }
    mode = pFlag->mode;
    if (mode == 4) {
        if (activationRecord->soundIdWord.whole != -1) {
            SoundElement_PlaySoundAtPosition(activationRecord->soundIdWord.half.id, actor->pos.v, 0, -1);
        }
        if (activationRecord->spawnEffectKind != -1) {
            Barrel_SpawnActorEffect(actor, activationRecord->spawnEffectKind, actor->pos.t, 0);
        }
        Barrel_SpawnFlaggedEffects(actor, activationContext, 4, activationRecord->primaryEffectMask, activationRecord->secondaryEffectMask);
        /* Fx_RecycleOwnerParticles unlinks the walker by the object's 32-bit identity;
         * the registry holds those identities as s32. */
        Fx_RecycleOwnerParticles(&g_gameSession.hud.actors, (s32)actor);
        if (pFlag->mode != mode) {
            goto block_10;
        }
    } else {
block_10:
        actor->flags = (actor->flags & ~0x100) | 0x08000000;
    }
}

/** Clear two flags when the controlling byte and nested flag are set. */
void DamageAI_ClearCollisionFlagsOnHit(BreakableHitContext *breakableHitContext, BreakableHitStateView *hitState) {
    char *nested = breakableHitContext->descriptor;
    if (hitState->active != 0 &&
        (((struct Descriptor *)nested)->damage.flags & 0x4) != 0) {
        unsigned int flags = breakableHitContext->flags;
        flags &= ~0x2000;
        flags &= ~0x100;
        breakableHitContext->flags = flags;
    }
}

/** Return the word through the pointer stored. */
int DamageAI_GetDefinitionValue(void *object) {
    return ((struct Access_s32_40 *) ((struct Owner *) object)->track)->field;
}
