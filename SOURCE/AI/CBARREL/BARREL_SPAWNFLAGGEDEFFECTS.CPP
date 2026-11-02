#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/FIELD_VEC_B0.H"
#include "TYPES.H"
#include "AI/CBARREL.H"
#include "COMMON/PROBE.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "ENGINE/INSTANCE/INSTHDR.H"
#include "COMMON/FUNCPTR.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "WEAPONS/BARREL_GETEYEDISTANCESQUARED.H"
#include "include_asm.h"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "MENU/TEAMMENU.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"

/* 80213ED4_19.CPP */
void Barrel_AddActorYaw(ActorYawView *actor, f32 yawDelta) {
    actor->yaw = (f32) (actor->yaw + yawDelta);
    ((s32 (*)(void *))Graphu64_WrapPeriodicValue)(&actor->yaw);
}

/* 80213ED4_20.CPP */
void Barrel_SpawnFlaggedEffects(Player *actor, s32 *emittedFlags, s32 emissionFlag, s32 primaryEffectMask, s32 secondaryEffectMask) {
    s32 *entry;

    if ((emittedFlags[0] & emissionFlag) != 0) {
        return;
    }

    emittedFlags[0] |= emissionFlag;
    entry = g_barrelPrimaryFlagSoundTable;
    if (entry[0] != 0) {
        do {
            if ((primaryEffectMask & entry[0]) != 0) {
                Insthdr_PlayActorGraphSound(actor,
                              actor->pos,
                              entry[1],
                              Graphu64_RandomBetween(g_barrelFlaggedEffectRandomRanges, k_barrelPrimarySoundRandomMaximum));
            }
            entry += 2;
        } while (entry[0] != 0);
    }

    entry = g_barrelSecondaryFlagSoundTable;
    if (entry[0] != 0) {
        do {
            if ((secondaryEffectMask & entry[0]) != 0) {
                Insthdr_PlayActorGraphSound(actor,
                              actor->pos,
                              entry[1],
                              Graphu64_RandomBetween(k_barrelSecondarySoundRandomMinimum, k_barrelSecondarySoundRandomMaximum));
            }
            entry += 2;
        } while (entry[0] != 0);
    }
}

/* 80213ED4_21.CPP */
/** Store one word into both elements of a two-word value. */
void Barrel_FillWordPair(int *value, int word) {
    value[0] = word;
    value[1] = word;
}

/* 80213ED4_22.CPP */
/** Read the next u16 from the cursor stream, wrapping back to base on the -1 sentinel. */
s16 Barrel_ReadLoopingSequenceValue(BarrelSequenceCursor *sequence) {
    u16 *cur;
    u16 value;

    cur = sequence->cur;
    value = *cur;
    cur += 1;
    sequence->cur = cur;
    if (*(s16 *) cur == -1) {
        sequence->cur = sequence->base;
    }
    return (s16) value;
}

/* Runs the hook with the arguments this function was called with: its callers pass the actor, its hook state
 * and the damage record, and the hook reads them from the same argument registers. */
void Barrel_RunDamageHook(void *actor, struct ActorDamageHookView *callbackState, void *damage) {
    FuncPtr fn = callbackState->callback;
    if (fn != 0) {
        ((void (*)(void *, void *, void *))fn)(actor, callbackState, damage);
    }
}

extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);

/** Subtract obj->y from vectorY in-place via Graphu64_SubtractVectors, then return the squared length of (vectorX, vectorY', vectorZ). */
f32 Barrel_GetEyeDistanceSquared(void *candidate, CVector3 v) {
    f32 eyeDeltaY;

    Graphu64_SubtractVectors(&v, &v, &((ActorBarrelIsTargetInViewCone *)(candidate))->position);
    eyeDeltaY = v.y - ((ActorBarrelIsTargetInViewCone *)(candidate))->eye;
    v.y = eyeDeltaY;
    return (v.x * v.x) + (eyeDeltaY * eyeDeltaY) + (v.z * v.z);
}

/* Squared XZ distance to a point using the existing by-value vector ABI. */
f32 Barrel_GetFlatDistanceSquared(LevelActor *actor, CVector3 point)
{
    f32 dx = point.x - actor->position0.x;
    f32 dz = point.z - actor->position0.z;
    return dx * dx + dz * dz;
}

void Barrel_IgnoreEffectCallback(void *unused0, void *unused1, BarrelWordPair unused2) {
}

extern void *SoundVoicePool_GetGlobalState(void);
extern s32 SoundVoicePool_StopNode(void *, void *);

void Barrel_SetLoopingSound(void *actor, void *stateController, s32 sixth) {
    CLoopingSoundData *node;
    void *fallback;
    s32 kind;

    node = ((Dest *)stateController)->sound;
    fallback = (void *)-1;
    if (node != 0) {
        if (node->state == sixth) {
            return;
        }
        SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), ((Dest *)stateController)->sound);
    }

    kind = *(u8 *)actor;
    if (kind != 0) {
        if (kind >= 0) {
            if (kind < 3) {
                fallback = actor;
            }
        }
    } else {
        fallback = (void *)((LevelActor *)actor)->resourceFlags;
    }

    ((Dest *)stateController)->sound =
        SoundVoicePool_PlaySpatialSound(SoundVoicePool_GetGlobalState(), sixth, &((LevelActor *)actor)->position0,
                      &((LevelActor *)actor)->position0, (s32)fallback);
}

/* 80217388.CPP */
void Barrel_StopActorLoopingSound(void *actor, void *soundState) {
    void *owner = 0;
    u8 type = *(u8 *)actor;

    switch (type) {
    case 1:
    case 2:
        owner = actor;
        break;
    case 0:
        owner = (void *)((LevelActor *)actor)->resourceFlags;
        break;
    }

    if (((Dest *)soundState)->sound != 0) {
        SoundElement_StopAudioBySecondaryValue(owner);
        if (((Dest *)soundState)->sound != 0) {
            SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), ((Dest *)soundState)->sound);
            ((Dest *)soundState)->sound = 0;
        }
    }
}

extern f32 Gobjinst_GetActorRadius(void *actor);
extern void Graphu64_ScaleVector(struct CVector3_t *,struct CVector3_t *,f32);
extern void Graphu64_AddVec3(CVector3 *result, CVector3 *left, CVector3 *right);
extern void InstHdr_CopyActorPositionAndModel(void *levelActor, CVector3 value, void *positionOut, s32 *modelFlagsOut,
                          s32 unused6, s32 unused7);

void Barrel_FindOffsetApproachPosition(void *actor, s32 unused, void *target, Player *player,
                   void *positionOut, s32 *modelFlagsOut) {
    CVector3 offset;
    CVector3 position;
    f32 distance;

    if (player != 0) {
        Graphu64_SubtractVectors(&offset, &((Player *)(target))->pos,
                       &player->pos);
        offset.y = 0.0f;
        Graphu64_NormalizeVec3(&offset.x);
    } else {
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = 0.0f;
    }

    distance = Gobjinst_GetActorRadius(target) + Gobjinst_GetActorRadius(actor) + g_barrelApproachClearance;
    Graphu64_ScaleVector(&offset, &offset, distance);
    Graphu64_AddVec3(&position, &((Player *)(target))->pos, &offset);
    InstHdr_CopyActorPositionAndModel(target, position, positionOut, modelFlagsOut, 0, 0);
}

void Barrel_ClearTargetInfo(Shared_ActorView *actorView, void *unused1, BarrelTargetInfo *targetInfo) {
    Triple local1;
    Triple local2;

    local1 = actorView->position.words;
    local2.x = 0;
    local2.y = 0;
    local2.z = 0;
    targetInfo->type = 3;
    targetInfo->reservedWordA = 0;
    targetInfo->reservedWordB = 0;
    targetInfo->first = local1;
    targetInfo->second = local2;
    targetInfo->reservedWordC = 0;
    local2.y = 0;
    local1.y = 0;
    targetInfo->third = local1;
    targetInfo->fourth = local2;
    targetInfo->reservedWordD = 0;
}

void Barrel_SpawnEffectsFromMask(Player *actor, s32 unused1, s32 effectMask, s32 *entry) {
    if (entry[0] != 0) {
        do {
            if ((effectMask & entry[0]) != 0) {
                Insthdr_PlayActorGraphSound(actor,
                              actor->pos,
                              entry[1],
                              Graphu64_RandomBetween(g_barrelEffectSoundMinimumPitch, g_barrelEffectSoundMaximumPitch));
            }
            entry += 2;
        } while (entry[0] != 0);
    }
}

