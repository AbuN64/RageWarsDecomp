#include "include_asm.h"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/FUNCPTR.H"
#include "COMMON/SHARED_VOIDCALLBACK.H"
#include "COMMON/WORLD.H"
#include "COMMON/OBJRECAT30.H"

#if !(defined(VERSION_DE) || defined(VERSION_EU))
/* Applies a hit to a damageable object: when its descriptor at 0x18 takes the hit (flag 1 for hits
   without bit 0x200, flag 2 for hits with it) it lowers the health at 0x4 by the damage, not below
   zero, turns the remaining percentage into the damage stage with the lowest threshold above it to set
   the model and time at 0x124 and 0x128 and the stage byte, and runs Actor_RequestActorState_Damageai (kind 2 when the
   descriptor has flag 0x40, else 1) once the health reaches zero. */
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"







void DamageAI_ApplyHitEuropeanExtended(Damageable *obj, Health *health, Hit *hit)
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

    flags = obj->desc->damage.flags;
    damage = &obj->desc->damage;
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
        obj->stage = damage->model[bestIndex];
        if (health->health == 0) {
            kind = 1;
            if (obj->desc->damage.flags & 0x40) {
                kind = 2;
            }
            Actor_RequestActorState(obj, health, kind);
        }
    }
}
#endif

#if defined(VERSION_EU_X)
unsigned int k_DamageaiEncodedWordsBlock1[2] = {
    0x43C00000, 0x3FC90FDC,
};
#endif

#if defined(VERSION_EU)
/* Applies a hit to a damageable object: when its descriptor at 0x18 takes the hit (flag 1 for hits
   without bit 0x200, flag 2 for hits with it) it lowers the health at 0x4 by the damage, not below
   zero, turns the remaining percentage into the damage stage with the lowest threshold above it to set
   the model and time at 0x124 and 0x128 and the stage byte, and runs Actor_RequestActorState_Damageai (kind 2 when the
   descriptor has flag 0x40, else 1) once the health reaches zero. */












void DamageAI_ApplyHitEuropean(Damageable *obj, Health *health, Hit *hit)
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

    flags = obj->desc->damage.flags;
    damage = &obj->desc->damage;
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
        obj->stage = damage->model[bestIndex];
        if (health->health == 0) {
            kind = 1;
            if (obj->desc->damage.flags & 0x40) {
                kind = 2;
            }
            Actor_RequestActorState(obj, health, kind);
        }
    }
}
#endif

#if defined(VERSION_DE)
void DamageAI_ApplyHitGerman(Damageable *obj, Health *health, Hit *hit)
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

    flags = obj->desc->damage.flags;
    damage = &obj->desc->damage;
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
        obj->stage = damage->model[bestIndex];
        if (health->health == 0) {
            kind = 1;
            if (obj->desc->damage.flags & 0x40) {
                kind = 2;
            }
            Actor_RequestActorState(obj, health, kind);
        }
    }
}
#endif

#if defined(VERSION_DE)
void *k_DamageaiEncodedWords[2] = {
    (void *)((char *)&g_deviceDrawRomEntry + 792), (void *)((char *)&g_deviceDrawRomEntry + 792),
};
#endif

extern s32 Rumble_TestActorStateBit(void *, void *);


typedef struct Owner Owner;

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
    void *obj = callbackOwner->hook;
    if (obj != 0) {
        FuncPtr fn = ((Shared_CallbackHook *)(obj))->callback;
        if (fn != 0) {
            ((void (*)(void *, Shared_CallbackOwner *))fn)(callbackContext, callbackOwner);
        }
    }
}

/** Return the nested record's field, or a fallback constant when zero. */
int DamageAI_GetActivationSound(void *owner) {
    int activationSound = ((Hold5324 *)((Owner *)owner)->track)->r.sound;
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
    Rec5324 *rec;
    Shared_World *pFlag;

    rec = &actor->holder->r;
    pFlag = &g_world;
    Rumble_SetActorStateBit(pFlag, actor, 1);
    Link_DispatchActorLinks(actor, 0x40000, actor);
    if (activationContext[1] == 0) {
        actor->flags = actor->flags & 0xFFFEFFFF;
    }
    if (rec->activationMode == 0) {
        actor->flags &= ~0x2000;
        actor->flags &= ~0x100;
    }
    mode = pFlag->mode;
    if (mode == 4) {
        if (rec->soundIdWord.whole != -1) {
            SoundElement_PlaySoundAtPosition(rec->soundIdWord.half.id, actor->pos.v, 0, -1);
        }
        if (rec->spawnEffectKind != -1) {
            Barrel_SpawnActorEffect(actor, rec->spawnEffectKind, actor->pos.t, 0);
        }
        Barrel_SpawnFlaggedEffects(actor, activationContext, 4, rec->primaryEffectMask, rec->secondaryEffectMask);
        /* Fx_RecycleOwnerParticles unlinks the walker by the object's 32-bit identity;
         * the registry holds those identities as s32. */
        Fx_RecycleOwnerParticles(&g_actorParticleScene, (s32)actor);
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

/** Return the word at offset 0x40 through the pointer stored at offset 0x18. */
int DamageAI_GetDefinitionValue(void *object) {
    return ((struct Access_s32_40 *) ((Owner *) object)->track)->field;
}
