#include "include_asm.h"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/WORLD.H"
#include "ENGINE/EVENTS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/MODEL_TREE_REGION_OPERATIONS.H"
#include "TYPES.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"

typedef struct DamageDefinition { s32 kind; } DamageDefinition;
typedef struct DamageActor {
    u8 category; char pad01[3]; u16 kind; char pad06[0x12];
    DamageDefinition *definition;
    char pad1C[0xC8]; u16 team; char padE6[0x1A]; u32 flags;
    char pad104[0x14]; u32 *properties;
    char pad11C[0x10]; struct DamageActor *owner;
    char pad130[0xA8]; struct ReactionPlayer *player;
} DamageActor;

#include "TYPES.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"


extern s32 InstHdr_CanActorReceiveInteraction(void *);

/* Whether source may hurt target: never itself, nor when source is a player whose hit InstHdr_CanActorReceiveInteraction refuses;
 * a stand-in (category 2) is safe when its owner is a player canDamage protects, when source owns it and it has
 * property 0x40, or for source kind 1 on team 0xCA against kind 0x14; players (category 1) go through canDamage. */
static inline s32 canDamage(DamageActor *source, DamageActor *actor) {
    if (g_gameSettings.local) {
        return 1;
    }
    if (actor->team == source->team) {
        return 0;
    }
    if (!(source->flags & 0x310000)) {
        return 0;
    }
    if (g_world.visibilityEnabled && !(actor->flags & 0x300000) && !(source->flags & 0x300000)) {
        return 0;
    }
    switch (source->definition->kind) {
    case 1:
    case 4:
    case 7:
    case 11:
        return 1;
    }
    return 0;
}
s32 Events_CanDamageActor(DamageActor *source, DamageActor *target) {
    DamageActor *owner;
    DamageActor *standIn;
    if (source == target) {
        return 0;
    }
    if ((source->flags & 0x300000) && !InstHdr_CanActorReceiveInteraction(source)) {
        return 0;
    }
    if (target->category != 1) {
        if (target->category == 2) {
            standIn = target;
            owner = standIn->owner;
            if (owner) {
                if (owner->category == 1 && !canDamage(source, owner)) {
                    return 0;
                }
                if (source == standIn->owner && (*standIn->properties & 0x40)) {
                    return 0;
                }
            }
            if (standIn->kind == 20 && source->definition->kind == 1 && source->team == 202) {
                return 0;
            }
        }
    } else if (!canDamage(source, target)) {
        return 0;
    }
    return 1;
}

#include "TYPES.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/WORLD.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
extern float k_damagePrimaryShakeScale;
extern float k_damagePrimaryShakeLevel;
extern float k_damageSecondaryShakeScale;
extern float k_damageSecondaryShakeLevel;
extern float k_damageEffectHeightOffset;
extern float k_damageEffectFirstScale;
extern float k_damageTurnScale;

void Player_TransformPointByViewOrOwnerMatrix(s32, f32 *);
void CScene_StartEventClips(Shared_World *, s32, s32, CVector3, f32, f32);
extern s32 g_actorParticleEffectSystem;
extern float k_damageEffectSecondScale;

#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"
typedef struct ReactionDisplay {
    char pad000[0x128];
    CVector3 origin;
} ReactionDisplay;
typedef struct ReactionPlayer {
    char pad000[0x5DC];
    ReactionDisplay *display;
    char pad5E0[0xB8];
    s32 sound;
} ReactionPlayer;
typedef struct ReactionActor {
    u8 category; char pad01[7];
    CVector3 position;
    char pad14[4];
    DamageDefinition *definition;
    CVector3 velocity;
    char pad28[0x44];
    f32 turn;
    char pad70[0x90];
    u32 flags;
    char pad104[0x6C];
    u32 eventFlags;
    char pad174[0x38];
    u32 effectFlags;
    char pad1B0[0x28];
    ReactionPlayer *player;
} ReactionActor;

typedef struct ReactionShield {
    char pad00[0x66];
    u8 effectKind; /* 0x66: impact response variant (4 or 5) */
} ReactionShield;

static inline s32 isReflectShield(ReactionShield *shield) {
    if (shield->effectKind == 4 || shield->effectKind == 5) {
        return 1;
    }
    return 0;
}
static inline void applyShieldReaction(ReactionActor *target, ReactionPlayer *player, CVector3 position, CVector3 impulse, s32 effectKind) {
    CVector3 localImpulse;
    CVector3 effectPosition;
    CVector3 zero;
    CQuatern rotation;
    s32 hit[2];
    if (player->display) {
        player = target->player;
        localImpulse.x = -impulse.x;
        localImpulse.y = impulse.y;
        localImpulse.z = impulse.z;
        Player_TransformPointByViewOrOwnerMatrix((s32)player, &localImpulse.x);
        localImpulse.x -= player->display->origin.x;
        localImpulse.y -= player->display->origin.y;
        localImpulse.z -= player->display->origin.z;
        rotation = Graphu64_BuildDirectionQuaternion(&localImpulse.x);
        InstHdr_CopyActorPositionAndModel((TrackerAimActorView *)target, position,
                         &effectPosition, hit, 0, 1);
        effectPosition = position;
        effectPosition.y += k_damageEffectHeightOffset;
        zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f;
        Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem,
                         (struct EffectActor *)target, (struct EffectActor *)target,
                         0, 0, 233, zero, rotation, effectPosition, 0, -1,
                         effectKind == 5 ? 3 : 1);
        effectPosition.x = 0.0f; effectPosition.y = 0.0f; effectPosition.z = 0.0f;
        CScene_StartEventClips(&g_world, player->sound + 320, 3,
                         effectPosition, k_damageEffectFirstScale, k_damageEffectSecondScale);
    }
}

/* Applies a hit's reaction: a player victim gets its hit flag, the attacker's screen shake, and (when the hit is
 * absorbed) a reflect-shield spark plus sound with the impulse cancelled; walking/flying attackers then take the
 * impulse and optionally turn toward the target. */
void Events_ApplyDamageReaction(void *sourceObject, char *targetObject, s32 absorbImpulse, CVector3 position, CVector3 impulse,
                      s32 applyTurn, ReactionShield *shield, u32 hitFlags) {
    ReactionActor *source = (ReactionActor *)sourceObject;
    ReactionActor *target = (ReactionActor *)targetObject;
    s32 absorb = absorbImpulse;
    f32 angle;
    if (target->category == 1) {
        DamageActor *victim = (DamageActor *)target;
        target->eventFlags |= 0x8000;
        if ((source->flags & 0x300000) && source->player->display) {
            if (target->effectFlags & 0x4000) {
                Gsky_StartScaledShake((char *)source->player->display, k_damagePrimaryShakeLevel,
                                 100.0f, k_damagePrimaryShakeLevel, k_damagePrimaryShakeScale, 1, position);
            } else if (target->effectFlags & 0x2000) {
                Gsky_StartScaledShake((char *)source->player->display, k_damageSecondaryShakeLevel,
                                 50.0f, k_damageSecondaryShakeLevel, k_damageSecondaryShakeScale, 1, position);
            }
        }
        if (absorb) {
            if (shield && (victim->flags & 0x300000) &&
                isReflectShield(shield)) {
                applyShieldReaction(target, victim->player, position, impulse, shield->effectKind);
            }
            impulse.x = 0.0f; impulse.y = 0.0f; impulse.z = 0.0f;
        }
        if ((victim->flags & 0x300000) && (hitFlags & 0x200)) {
            Link_DispatchActorLinks((struct Shared_Actor *)source, 16, victim);
        }
    }
    if (source->definition->kind == 1 || source->definition->kind == 11) {
        Graphu64_AddVec3(&source->velocity, &source->velocity, &impulse);
        if (applyTurn) {
            angle = Barrel_GetSignedAngleToPoint((TrackerAimActorView *)source, target->position);
            source->turn += angle * k_damageTurnScale;
        }
    }
}

#include <ultra64.h>
#include "COMMON/GAMEPLAY_REACTIONS.H"
/* Published contiguous pool of damage scaling constants, read by index. */
extern const f32 k_damageEventScaleConstants[16];
/* Forwards the actor, event value and three-component input with a zero final flag. */
extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);
extern f32 Gobjinst_GetRootMeanSquareScale(void *);
extern s32 Gobjinst_FindNearestBoneBounds(void *, CVector3, Shield *);
extern f32 Graphu64_GetPointDistance(CVector3 *, CVector3 *);
extern f32 Events_GetActorSizeScale(u8 *);
extern void Barrel_FillDamagePacket(CDamageInfo *, void *, s32, f32, s32, Shield *);
extern s32 Player_GetMaxHealth(void *);
struct ActorDamageHookView;
extern void Barrel_RunDamageHook(void *, struct ActorDamageHookView *, CDamageInfo *);
extern s32 Particle_HasKindOneEntry(Shared_ReactionObjectKind *);
extern s32 Particle_HasKindZeroEntry(Shared_ReactionObjectKind *);
extern s32 Particle_HasKindTwoEntry(Shared_ReactionObjectKind *);
extern void *g_currentActorInstance;
extern s32 g_damageShieldSelection;
extern Shield g_damageFallbackShield;
static inline void storeActorHealth(Shared_ReactionActor *actor, s32 value) { actor->health = value; }
static inline void storePlayerHealth(Shared_ReactionPlayer *player, s32 value) {
    player->health = value;
    player->actorHealth = player->health;
    storeActorHealth(&player->actor2E8, player->health);
}
static inline void buildDamage(CDamageInfo *event, Shared_ReactionActor *target, f32 damage, f32 radius, s32 flags, Shield **shield) {
    Barrel_FillDamagePacket(event, target, (s32)damage, radius, flags, *shield);
}
static inline void reflectedProjectile(Shared_ReactionPlayer *player, Shared_ReactionActor *target, f32 damage, f32 radius, s32 flags, Shield **shield) {
    CDamageInfo event;
    CDamageInfo *p = &event;
    buildDamage(p, target, damage * 2.0f, radius, flags, shield);
    if (damage * k_damageEventScaleConstants[9] > 0.0f) Barrel_RunDamageHook(player, &player->damageState, p);
}
static inline void reflectedActor(Shared_ReactionPlayer *player, Shared_ReactionActor *target, f32 damage, f32 radius, s32 flags, Shield **shield) {
    CDamageInfo event;
    CDamageInfo *p = &event;
    f32 value = damage * k_damageEventScaleConstants[13];
    buildDamage(p, target, value, radius, flags, shield);
    if (value > 0.0f) Barrel_RunDamageHook(player, &player->damageState, p);
}
static inline s32 adjustHit(Shared_ReactionActor *target, CVector3 *position) {
    s32 adjusted;
    s16 ownerState;
    Shared_ReactionPlayer *owner;
    CVector3 body, origin;
        adjusted = 0;
        if ((target->category == 1) && (target->flags & 0x300000)) {
            owner = target->player;
            if (((void *)target == (void *)&owner->actor2E8) && ((ownerState = owner->weaponIndex, (ownerState == 0)) || (ownerState == 17) || (ownerState == 16))) {
                body = (*position);
                origin = owner->position;
                Graphu64_InterpolateVector(&(*position), 0.75f, &body, &origin);
                (*position).y += Gobjinst_GetActorHeight(owner) * k_damageEventScaleConstants[0];
                adjusted = 1;
            }
        }
        return adjusted;
}
static inline f32 hitSize(Shared_ReactionActor *target) {
    if (target->category == 1) return Gobjinst_GetRootMeanSquareScale(target);
    else return k_damageEventScaleConstants[2];
}
static inline void hitImpulse(Shared_ReactionActor *source, Shared_ReactionActor *target, Shared_DamageParameters copied, CVector3 *out) {
    CVector3 delta;
    CVector3 direction;
    CVector3 push;
    f32 orientation[4][4];
    f32 radius, distance;
    radius = (f32)copied.radius * k_damageEventScaleConstants[6];
    radius *= Events_GetActorSizeScale(&target->category);
    out->z = 0.0f;
    out->y = 0.0f;
    out->x = 0.0f;
    /* The de release skips the push when the source has no health left. */
    if (
#ifdef VERSION_DE
        source->health != 0 &&
#endif
        target->category == 2) {
        Graphu64_SubtractVectors(&direction, &source->position, &target->position);
        distance = Gu_Sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
        Graphu64_NormalizeVec3(&direction);
        if (!(radius <= distance)) {
            Graphu64_ScaleVector(out, &direction, (f32)copied.impulse * (((radius - distance) / radius) * k_damageEventScaleConstants[7]));
        }
    }
}
static inline f32 scaleHit(Shared_ReactionActor *self, Shared_ReactionActor *target, CVector3 position, f32 radius, s32 falloff, s32 flags, Shield **found) {
    Shared_ReactionPlayer *player;
    s32 shielded;
    s32 scaled;
    s32 special;
    Shield *shield;
    f32 scale;
    f32 bottom;
    f32 top;
    f32 reach;
    f32 distance;
    CVector3 body;

    special = 0;
    shielded = 1;
    player = 0;
    scale = k_damageEventScaleConstants[3];
    scaled = 1;
    if (self->flags & 0x300000) {
        player = self->player;
    }
    if (g_gameSettings.local != 0 && (flags & 0x200)) {
        shielded = 0;
    }
    if (target->category == 2) {
        if (target->type == 1028 || target->type == 1026) {
            special = 1;
        }
        if (target->category == 2 && g_currentActorInstance == (void *)self && g_damageShieldSelection != -1 && !special) {
            shield = &g_damageFallbackShield;
            falloff = 0;
            goto have;
        }
    }
    shield = Gobjinst_FindNearestBoneBounds(self, position, &g_damageBoneBoundsShield) ? &g_damageBoneBoundsShield : 0;
have:
    *found = shield;
    if (shielded && shield != 0) {
        scale *= shield->factor;
    }
    if (falloff != 0) {
        if (player != 0 && (player->reactionFlags & 2) && scale == k_damageEventScaleConstants[4] && (flags & 0x200)) {
            scale = 0.0f;
        } else {
            body = self->position;
            bottom = self->position.y + self->height;
            top = bottom + Gobjinst_GetActorHeight(self);
            if (top < position.y) {
                body.y = top;
            } else if (position.y < bottom) {
                body.y = bottom;
            } else {
                body.y = position.y;
            }
            reach = radius + Gobjinst_GetActorRadius(self);
            distance = Graphu64_GetPointDistance(&position, &body);
            if (reach < distance) {
                return 0.0f;
            }
            if (scaled) {
                scale *= k_damageEventScaleConstants[5] - distance / reach;
            }
        }
    }
    return scale;
}

void Events_ApplyDamageEvent(Shared_ReactionActor *source, Shared_ReactionActor *target, s32 kind, CVector3 position, Shared_DamageParameters params, s32 falloff, s32 knockback, s32 flags) {
    s32 restored2;
    s32 restored;
    f32 damage;
    CVector3 impulse;
    s32 adjusted;
    Shared_ReactionActor *owner;
    Shared_ReactionPlayer *ownerPlayer;
    s32 restored3;
    Shared_ReactionPlayer *carrier;
    s32 maximum;
    s32 maximum2;
    u8 category;
    Shield *shield;
    Shared_ReactionObjectKind *projectile;
    CDamageInfo hit;
    CDamageInfo *event;
    f32 radius;
    s32 maximum3;
    Shared_ReactionPlayer *attacker;
    Shared_ReactionPlayer *victim;

    attacker = NULL;
    if (source->flags & 0x300000) {
        attacker = source->player;
    }
    if (Events_CanDamageActor(source, target) != 0) {
        adjusted = adjustHit(target, &position);
        radius = (f32) params.radius * k_damageEventScaleConstants[1];
        radius *= hitSize(target);
        damage = (f32)params.damage;
        damage *= scaleHit(source, target, position, radius, falloff, flags, &shield);
        if (!(damage <= 0.0f)) {
            hitImpulse(source, target, params, &impulse);
            event = &hit;
            Barrel_FillDamagePacket(event, target, (s32)damage, radius, flags, shield);
            category = target->category;
            if (category == 2) {
                projectile = &target->objectKind;
                owner = target->owner;
                if ((owner != NULL) && (owner->category == 1)) {
                    if (owner->flags & 0x300000) {
                        ownerPlayer = owner->player;
                        if (attacker != NULL) {
                            if (ownerPlayer->reactionFlags & 0x40) {
                                restored = ownerPlayer->health + (s32) (damage * k_damageEventScaleConstants[8]);
                                maximum = Player_GetMaxHealth(ownerPlayer);
                                if (restored < maximum) {
                                    maximum = restored;
                                }
                                storePlayerHealth(ownerPlayer, maximum);
                            }
                        }
                        if (attacker != NULL) {
                            {
                                if (attacker->reactionFlags & 0x10) {
                                    reflectedProjectile(ownerPlayer, target, damage, radius, flags, &shield);
                                }
                                if ((attacker != NULL) && (attacker->reactionFlags & 0x1000) && (Particle_HasKindOneEntry(projectile) != 0)) {
                                    restored2 = attacker->health + (s32) damage;
                                    maximum2 = Player_GetMaxHealth(ownerPlayer);
                                    if (restored2 < maximum2) {
                                        maximum2 = restored2;
                                    }
                                    damage = 0.0f;
                                    storePlayerHealth(attacker, maximum2);
                                }
                            }
                        }
                        if ((damage > 0.0f) && (attacker != NULL) && (ownerPlayer->reactionFlags & 8) && (ownerPlayer != attacker)) {
                            attacker->reactionFlags = (s32) (attacker->reactionFlags | 0x4000);
                            attacker->reactionTimer = (f32) k_damageEventScaleConstants[10];
                        }
                        if (ownerPlayer->reactionFlags & 0x200) {
                            damage *= k_damageEventScaleConstants[11];
                            Barrel_FillDamagePacket(&hit, target, (s32)damage, radius, flags, shield);
                        }
                    } else if (target->type == 1063) {
                        carrier = NULL;
                        if (owner->team == 1036) {
                            carrier = owner->player;
                        }
                        if ((carrier != NULL) && (carrier->reactionFlags & 0x200)) {
                            damage *= k_damageEventScaleConstants[11];
                            Barrel_FillDamagePacket(event, target, (s32)damage, radius, flags, shield);
                        }
                    }
                    if (attacker != NULL) {
                        if ((attacker->reactionFlags & 0x800) && ((Particle_HasKindZeroEntry(projectile) != 0) || (Particle_HasKindTwoEntry(projectile) != 0))) {
                            damage = 0.0f;
                        }
                        if ((attacker != NULL) && (attacker->reactionFlags & 0x400)) {
                            damage = 0.0f;
                        }
                    }
                }
            } else if (category == 1) {
                if (target->flags & 0x300000) {
                    victim = target->player;
                    if (attacker != NULL) {
                        if (victim->reactionFlags & 0x40) {
                            restored3 = victim->health + (s32) (damage * k_damageEventScaleConstants[12]);
                            maximum3 = Player_GetMaxHealth(victim);
                            if (restored3 < maximum3) {
                                maximum3 = restored3;
                            }
                            storePlayerHealth(victim, maximum3);
                        }
                    }
                    if (attacker != NULL) {
                        {
                            if (attacker->reactionFlags & 0x10) {
                                reflectedActor(victim, target, damage, radius, flags, &shield);
                            }
                        }
                    }
                    if ((damage > 0.0f) && (attacker != NULL) && (attacker != victim) && (victim->reactionFlags & 8)) {
                        attacker->reactionFlags = (s32) (attacker->reactionFlags | 0x4000);
                        attacker->reactionTimer = (f32) k_damageEventScaleConstants[14];
                    }
                    if (victim->reactionFlags & 0x200) {
                        damage *= k_damageEventScaleConstants[15];
                        Barrel_FillDamagePacket(&hit, target, (s32)damage, radius, flags, shield);
                    }
                }
                if ((attacker != NULL) && (attacker->reactionFlags & 0x400)) {
                    damage = 0.0f;
                }
                if ((damage > 0.0f) && (attacker != NULL)) {
                    attacker->damageToggle = (s32) (attacker->damageToggle == 0);
                }
            }
            if (damage != 0.0f) {
                Barrel_RunDamageHook(source, &source->damageState, &hit);
                Events_ApplyDamageReaction(source, target, adjusted, position, impulse, knockback, shield, flags);
            }
        }
    }
}


extern f32 Gobjinst_GetRootMeanSquareScale(void *target);



/* Forwards the actor, event value and three-component input with a zero final flag. */




/* Decides whether one actor may affect another: always when the override g_motionVisibilitySettings is set; never for actors of the same kind or a target lacking flags 0x310000, nor, while visibilityEnabled_AnimpoolSpawnsceneeffect is set, when neither actor carries 0x300000; otherwise only when the target is in state 1, 4, 7 or 11. */



extern EventCallbackEntry g_effectCallbackFlags[];
void Events_DispatchCallback(void *sourceActor, void *targetActor, s32 eventKind, CVector3 eventPosition, ResourceManagerState eventParams) {
    if (g_effectCallbackFlags[eventKind].callback != 0) {
        g_effectCallbackFlags[eventKind].callback(sourceActor, targetActor, eventKind, eventPosition, eventParams);
    }
}

void Events_ForwardCallback(void *sourceActor, void *targetActor, s32 eventKind, CVector3 eventPosition, ResourceManagerState eventParams) {
    if (g_effectCallbackFlags[eventKind].callback != 0) {
        g_effectCallbackFlags[eventKind].callback(sourceActor, targetActor, eventKind, eventPosition, eventParams);
    }
}

void Events_UpdateNodeAtPosition(void *actor, CVector3 input, s32 enableNodeFlag) {
    CVector3 output;
    s32 value;

    InstHdr_CopyActorPositionAndModel(actor, input, &output, &value, 0, 0);
    if (enableNodeFlag != 0) {
        Region_SetNodeGroupFlag((void *)value);
    } else {
        Region_ClearNodeGroupFlag((void *)value);
    }
}

f32 Events_GetActorSizeScale(u8 *other) {
    if (*other == 1) {
        return Gobjinst_GetRootMeanSquareScale(other);
    } else {
        return k_damageDefaultScale;
    }
}

void Events_PlayClipEvent(s32 unusedSource, ClipEventTargetView *targetActor, s32 unusedEventKind, CVector3 soundPosition,
                   Clip clipParams) {
    s32 *global = &g_gameSession.clockPaused;
    s32 selected;
    f32 scale;

    scale = k_clipEventDefaultScale;
    selected = -1;
    if (global[0] != 0) {
        return;
    }

    if (targetActor != 0) {
        switch (targetActor->type) {
        case 1:
            if (*targetActor->kind == targetActor->type) {
                if (global[-371] & 0x40) {
                    scale = k_clipEventFlagFortyScale;
                } else if (global[-371] & 0x20) {
                    scale = k_clipEventFlagTwentyScale;
                }
            }
            selected = (s32)targetActor;
            break;
        case 0:
            selected = targetActor->value;
            break;
        case 2:
            selected = (s32)targetActor;
            break;
        }
    }

    SoundElement_PlayPositionedSoundWithScale(clipParams.frames, soundPosition, 0, selected, scale);
}

void Events_StopClipEvent(s32 unused0, s32 unused1, s32 unused2, s32 eventPositionWord, s32 unused4, s32 unused5, s32 unused6) {
    s32 *p = &eventPositionWord;
    SoundElement_PlayDialogGroup(p[3]);
}

void Events_SpawnActorEffect(void *actor,int unused1,int unused2,Triple input,int event) {
 Barrel_SpawnActorEffect(actor,event,input,0);
}

s32 Events_AdjustWeaponHitPosition(void *levelActor, CVector3 *hitPosition) {
    CVector3 first;
    CVector3 second;
    LevelActor *object = levelActor;
    Shared_ActorView *actor;
    s16 state;
    s32 result;

    result = 0;
    if ((object->kind == 1) &&
        ((object->flags & 0x300000) != 0)) {
        actor = object->controller;
        if (levelActor == &actor->weapon) {
            state = actor->selectedAction;
            if ((state == 0) || (state == 17) || (state == 16)) {
                first = *hitPosition;
                second = ((LevelActor *)actor)->position0;
                Graphu64_InterpolateVector(hitPosition, 0.75f, &first, &second);
                hitPosition->y += Gobjinst_GetActorHeight(actor) * k_weaponHitHeightScale;
                result = 1;
            }
        }
    }
    return result;
}

s32 Events_CanAffectActor(char *actor, char *target)
{
    LevelActor *source = (LevelActor *)actor;
    LevelActor *destination = (LevelActor *)target;
    s32 flags;

    if (g_gameSettings.local != 0) {
        return 1;
    }
    if (source->type == destination->type) {
        return 0;
    }
    flags = destination->flags;
    if (!(flags & 0x310000)) {
        return 0;
    }
    if (g_world.visibilityEnabled != 0 && !(source->flags & 0x300000) && !(flags & 0x300000)) {
        return 0;
    }
    switch (destination->definition->kind) {
    case 1:
    case 4:
    case 7:
    case 11:
        return 1;
    }
    return 0;
}

#include "TYPES.H"
#include "COMMON/AIPROFILE.H"
typedef struct PushStrength { u16 value; u16 pad; } PushStrength;
typedef struct PushScale { s8 value; u8 pad[3]; } PushScale;
extern f32 k_damageRadiusScale;
void Events_ComputeRadialImpulse(struct Player *actor, u8 *other, PushStrength strength, PushScale scale, CVector3 *out) {
    char frame[16];
    CVector3 offset;
    char scratch[80];
    f32 radius;
    f32 distance;
    radius = (f32)strength.value * k_damageRadiusScale;
    radius *= Events_GetActorSizeScale(other);
    out->x = out->y = out->z = 0.0f;
#ifdef VERSION_DE
    if (((LevelActor *)actor)->active != 0 && *other == 2) {
#else
    if (*other == 2) {
#endif
        Graphu64_SubtractVectors(&offset, &actor->pos, &((struct Player *)other)->pos);
        distance = Gu_Sqrtf(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
        Graphu64_NormalizeVec3(&offset.x);
        if (!(radius <= distance)) {
            Graphu64_ScaleVector(out, &offset, (f32)scale.value * (((radius - distance) / radius) * k_damageEuropeanFalloffScale));
        }
    }
}
