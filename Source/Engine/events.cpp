#include "Common/output.h"
#include "Common/vector4f.h"
#include "include_asm.h"
#include "types.h"
#include "Common/box_contact.h"
#include "Common/world.h"
#include "Common/level_actor.h"
#include "System/contact_effect.h"
#include "Engine/particle.h"
#include "Engine/events.h"
#include "Common/shared_particleinstance.h"
#include "Common/game_session.h"
#include "Common/shared_gameslot.h"
#include "Common/sharedplayer.h"
#include "Common/gameplay_transition.h"
#include "Common/model_tree_region_operations.h"
#include "Common/animationtriggerdefinition.h"
#include "Fx/normalize_vector.h"
#include "Cbarrel/barrel_spawnflaggedeffects.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
#include "Render/playerai_toggleforcemarker.h"
#include "Common/approachlocation.h"
#include "Common/ballisticparams.h"
#include "Common/multiplayeroptions.h"
#include "Common/triple.h"
#include "Particle/particle_spawneffectgroup.h"
#include <platform_sdk.h>
#include "Common/gameplay_reactions.h"
#include "Engine/graphics_math.h"
#include "Engine/Instance/gobjinst.h"
#include "Ai/cbarrel.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Common/aiprofile.h"
#include "Engine/scene.h"
#include "Common/gameplay_camera.h"
#include "Common/viewflags.h"
#include "Common/runtime_declarations.h"
#include "Gsky/gsky_containsvisiblepoint.h"
#include "Common/menu_match_globals.h"
#include "Camera/gsky.h"
#include "Common/gameplay_sound_table.h"
#include "Engine/Audio/channel.h"
#include "Render/rangenode.h"
#include "Common/Lone/controller_rumble_pool.h"
#include "Common/resident_event_handler.h"
#include "Common/animation_pool.h"
#include "Engine/Audio/T2SoundElement.h"
#include "Animpool/animpool_spawndescribedsceneeffect.h"
#include "Engine/session.h"
#include "Engine/Instance/insthdr.h"
#include "Data/rest_source_records.h"
#include "Ai/Nav/Patrol/patrol.h"

/* EVENTS_DELIVERCONTACTEFFECT.CPP */

typedef struct ContactNode ContactNode;
struct ContactNode {
    u8 pad0[0x16E0];
    ContactNode *next;
};
static inline void dispatchEffect(void *object, void *source, s32 effect, CVector3 position, ContactEffectStyle style) {
    if (g_effectCallbackFlags[effect].handler != 0) {
        g_effectCallbackFlags[effect].handler(object, source, effect, position, style);
    }
}
/* Delivers a contact effect to objects: when the scene is in mode 4 or the effect's flags allow it, the effect's
 * handler (g_effectCallbackFlags table, flags in the second word: 2 = broadcast, 8 = scene object array) is called either
 * on the target alone or on every other object -- the scene's object array or its registered list
 * and then the scene's chained player list -- skipping the target.
 * */
void Events_DeliverContactEffect(void *target, void *source, s32 effect, s32 contactArg, CVector3 position, ContactEffectStyle style) {
    s32 i;
    s32 count;
    LevelActor *actor;
    LevelActor *objects;
    void *other;
    ContactNode *node;
    Shared_World *world = &g_world;
    if (world->mode != 4 && (g_effectCallbackFlags[effect].flags & 0x10) == 0) {
        return;
    }
    if ((g_effectCallbackFlags[effect].flags & 2) == 0) {
        dispatchEffect(target, source, effect, position, style);
        return;
    }
    if ((g_effectCallbackFlags[effect].flags & 8) != 0) {
        count = world->actorCapacity;
        objects = world->actors;
        for (i = 0; i < count; i++) {
            other = &objects[i];
            if (other != target) {
                dispatchEffect(other, source, effect, position, style);
            }
        }
        for (node = g_transientPlayerList.actorList; node != 0; node = node->next) {
            if ((void *)node != target && (void *)&((SharedPlayer *)node)->views1C.view2E8_27.weapon != target) {
                dispatchEffect(node, source, effect, position, style);
            }
        }
    } else {
        count = world->registeredCount;
        for (i = 0; i < count; i++) {
            other = world->registered[i];
            if (other != target) {
                dispatchEffect(other, source, effect, position, style);
            }
        }
        node = g_transientPlayerList.actorList;
        while (node != 0) {
            if ((void *)node != target && (void *)&((SharedPlayer *)node)->views1C.view2E8_27.weapon != target) {
                dispatchEffect(node, source, effect, position, style);
            }
            node = node->next;
        }
    }
}

/* EVENTS_APPLYDAMAGEEVENT.CPP */

typedef struct DamageDefinition { s32 kind; } DamageDefinition;
typedef struct DamageActor {
    u8 category; char pad01[3]; u16 kind; char pad06[0x12];
    DamageDefinition *definition;
    char pad1C[0xC8]; u16 team; char padE6[0x1A]; u32 flags;
    char pad104[0x14]; u32 *properties;
    char pad11C[0x10]; struct DamageActor *owner;
    char pad130[0xA8]; struct ReactionPlayer *player;
} DamageActor;


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
    u8 effectKind; /* impact response variant (4 or 5) */
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
        InstHdr_CopyActorPositionAndModel((LevelActor *)target, position,
                         &effectPosition, hit, 0, 1);
        effectPosition = position;
        effectPosition.y += k_damageEffectHeightOffset;
        zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f;
        Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem,
                         target, target,
                         0, 0, 233, zero, rotation, effectPosition, 0, -1,
                         effectKind == 5 ? 3 : 1);
        effectPosition.x = 0.0f; effectPosition.y = 0.0f; effectPosition.z = 0.0f;
        CScene_StartEventClips(&g_world, player->sound + 320, 3, *(Triple *)&effectPosition, k_damageEffectClipScale[0], k_damageEffectClipScale[1]);
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
                Gsky_StartScaledShake((struct ShakeEmitterChannelView *)source->player->display, k_damagePrimaryShakeLevel,
                                 100.0f, k_damagePrimaryShakeLevel, k_damagePrimaryShakeScale, 1, position);
            } else if (target->effectFlags & 0x2000) {
                Gsky_StartScaledShake((struct ShakeEmitterChannelView *)source->player->display, k_damageSecondaryShakeLevel,
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
            angle = Barrel_GetSignedAngleToPoint((LevelActor *)source, target->position);
            source->turn += angle * k_damageTurnScale;
        }
    }
}

/* Published contiguous pool of damage scaling constants, read by index. */
/* Forwards the actor, event value and three-component input with a zero final flag. */
extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);
extern f32 Gobjinst_GetRootMeanSquareScale(void *);
struct CVector3_t; struct Box70; extern s32 Gobjinst_FindNearestBoneBounds(char *obj, struct CVector3_t point, struct Box70 *out);
extern f32 Graphu64_GetPointDistance(f32 *a, f32 *b);
extern f32 Events_GetActorSizeScale(u8 *);

extern s32 Player_GetMaxHealth(void *);
struct ActorDamageHookView;




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
    CDamageInfo *damageInfo = &event;
    buildDamage(damageInfo, target, damage * 2.0f, radius, flags, shield);
    if (damage * k_damageEventScaleConstants[9] > 0.0f) Barrel_RunDamageHook(player, &player->damageState, damageInfo);
}
static inline void reflectedActor(Shared_ReactionPlayer *player, Shared_ReactionActor *target, f32 damage, f32 radius, s32 flags, Shield **shield) {
    CDamageInfo event;
    CDamageInfo *damageInfo = &event;
    f32 value = damage * k_damageEventScaleConstants[13];
    buildDamage(damageInfo, target, value, radius, flags, shield);
    if (value > 0.0f) Barrel_RunDamageHook(player, &player->damageState, damageInfo);
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
        if (target->category == 2 && g_currentActorInstance.instance0 == (void *)self && g_damageShieldSelection != -1 && !special) {
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
                                if ((attacker != NULL) && (attacker->reactionFlags & 0x1000) && (Particle_HasKindOneEntry((Shared_ParticleInstance *)projectile) != 0)) {
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
                        if ((attacker->reactionFlags & 0x800) && ((Particle_HasKindZeroEntry((Shared_ParticleInstance *)projectile) != 0) || (Particle_HasKindTwoEntry((Shared_ParticleInstance *)projectile) != 0))) {
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

/* Forwards the actor, event value and three-component input with a zero final flag. */

/* Decides whether one actor may affect another: always when the override g_motionVisibilitySettings is set; never for actors of the same kind or a target lacking flags 0x310000, nor, while visibilityEnabled_AnimpoolSpawnsceneeffect is set, when neither actor carries 0x300000; otherwise only when the target is in state 1, 4, 7 or 11. */

void Events_DispatchCallback(void *sourceActor, void *targetActor, s32 eventKind, CVector3 eventPosition, ResourceManagerState eventParams) {
    if (g_effectCallbackFlags[eventKind].handler != 0) {
        g_effectCallbackFlags[eventKind].handler(sourceActor, targetActor, eventKind, eventPosition, *(ContactEffectStyle *)&eventParams);
    }
}

void Events_ForwardCallback(void *sourceActor, void *targetActor, s32 eventKind, CVector3 eventPosition, ResourceManagerState eventParams) {
    if (g_effectCallbackFlags[eventKind].handler != 0) {
        g_effectCallbackFlags[eventKind].handler(sourceActor, targetActor, eventKind, eventPosition, *(ContactEffectStyle *)&eventParams);
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
                    scale = k_clipEventHighFlagScale;
                } else if (global[-371] & 0x20) {
                    scale = k_clipEventLowFlagScale;
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

void Events_StopClipEvent(s32 source, s32 target, s32 kind, s32 eventPositionWord, s32 positionYWord, s32 positionZWord, s32 eventParams) {
    s32 *eventWords = &eventPositionWord;
    SoundElement_PlayDialogGroup(eventWords[3]);
}

void Events_SpawnActorEffect(void *actor,int target,int kind,Triple input,int event) {
 Barrel_SpawnActorEffect(actor,event,input,0);
}

s32 Events_AdjustWeaponHitPosition(LevelActor *levelActor, CVector3 *hitPosition) {
    CVector3 first;
    CVector3 second;
    LevelActor *object = levelActor;
    Player *actor;
    s16 state;
    s32 result;

    result = 0;
    if ((object->kind == 1) &&
        ((object->flags & 0x300000) != 0)) {
        actor = object->controller;
        if (levelActor == &actor->actorParts[1]) {
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

s32 Events_CanAffectActor(LevelActor *actor, LevelActor *target)
{
    LevelActor *source = actor;
    LevelActor *destination = target;
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

typedef struct PushStrength { u16 value; u16 pad; } PushStrength;
typedef struct PushScale { s8 value; u8 pad[3]; } PushScale;
void Events_ComputeRadialImpulse(struct Player *actor, Player *other, PushStrength strength, PushScale scale, CVector3 *out) {
    char frame[16];
    CVector3 offset;
    char scratch[80];
    f32 radius;
    f32 distance;
    radius = (f32)strength.value * k_damageRadiusScale;
    radius *= Events_GetActorSizeScale(other);
    out->x = out->y = out->z = 0.0f;
#ifdef VERSION_DE
    if (((LevelActor *)actor)->active != 0 && other->kind == 2) {
#else
    if (other->kind == 2) {
#endif
        Graphu64_SubtractVectors(&offset, &actor->pos, &(other)->pos);
        distance = Gu_Sqrtf(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
        Graphu64_NormalizeVec3(&offset.x);
        if (!(radius <= distance)) {
            Graphu64_ScaleVector(out, &offset, (f32)scale.value * (((radius - distance) / radius) * k_damageEuropeanFalloffScale));
        }
    }
}

/* EVENTS_COMPUTEDAMAGESCALE.CPP */

/* Returns how strongly a blast at a position with a radius affects an actor: finds the shield covering the position (the held carrier shield g_currentActorInstance of the actor for an object target other than the two 0x402/0x404 types, otherwise Gobjinst_FindNearestBoneBounds's shield in g_damageBoneBoundsShield), reports it, scales by the shield factor unless friendly fire is off for team damage, and when falloff is asked returns zero for an invulnerable player's untouched full hit, zero beyond the radius plus the actor's width, or the scale times one minus the distance to the actor's body over that reach. */


/* Spawns a hit effect when the target has a rider: turns the negated hit direction into the victim's frame through Player_TransformPointByViewOrOwnerMatrix, makes it relative to the victim rider's centre and converts it to a rotation, resolves the hit position on the attacker through InstHdr_CopyActorPositionAndModel, spawns effect 0xE9 there raised by k_playerEventClipHeightAndAngle (size 3 for kind 5, otherwise 1), and starts effect 3 on the victim's emitter. */


/* Forwards a position and extent to Events_ApplyDamageEvent with zero flags and priority 0x80, but only when
   the first byte of the given object is 1. */

f32 Events_ComputeDamageScale(ActorEventsComputeDamageScale *self, Target *target, CVector3 position, f32 radius, s32 falloff, s32 flags, Shield **found) {
    PlayerDamageFlagsView *player;
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
    scale = *(&k_damageEuropeanFalloffScale + 1);
    scaled = 1;
    if (self->flags & 0x300000) {
        player = self->player;
    }
    if (g_gameSettings.local != 0 && (flags & 0x200)) {
        shielded = 0;
    }
    if (target->kind == 2) {
        if (target->type == 1028 || target->type == 1026) {
            special = 1;
        }
        if (target->kind == 2 && g_currentActorInstance.instance0 == self && g_currentActorInstance.value != -1 && !special) {
            shield = (Shield *)&g_currentActorInstance.block18;
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
        if (player != 0 && (player->flags & 2) && scale == k_damageSpecialScale && (flags & 0x200)) {
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
                scale *= (1.0f) - distance / reach;
            }
        }
    }
    return scale;
}

void Events_SpawnRiderImpactEffect(SharedPlayer *target, ActorEventsSpawnRiderImpactEffect *actor, Triple position, CVector3 direction, s32 kind) {
    SharedPlayer *player;
    CVector3 v;
    Triple point;
    Triple zero;
    CQuatern rotation;
    s32 roomIndex;

    if (target->views5DC.view5DC_5.rider == 0) {
        return;
    }
    player = actor->player;
    v.x = -direction.x;
    v.y = direction.y;
    v.z = direction.z;
    Player_TransformPointByViewOrOwnerMatrix(player, &v);
    v.x -= player->views5DC.view5DC_5.rider->position.x;
    v.y -= player->views5DC.view5DC_5.rider->position.y;
    v.z -= player->views5DC.view5DC_5.rider->position.z;
    rotation = Graphu64_BuildDirectionQuaternion(&v);
    InstHdr_CopyActorPositionAndModel(actor, *(CVector3 *)&position, &point, &roomIndex, 0, 1);
    point = position;
    ((CVector3 *)&point)->y += k_playerEventClipHeightAndAngle;
    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor, 0, 0, 233, *(CVector3 *)&zero, rotation, *(CVector3 *)&point, 0, -1, kind == 5 ? 3 : 1);
    point.x = 0;
    point.y = 0;
    point.z = 0;
    CScene_StartEventClips(&g_world, &((ControllerProfile *)player->views5E8.view698_37.emitter)->effectPool, 3, *(Triple *)&point, *(&k_playerEventClipHeightAndAngle + 1), k_playerEventClipScale[0]);;
}

void Events_ApplyDirectDamage(unsigned char *source, s32 target, s32 kind, Triple position, struct IntPair params) {
    if (*source == 1) {
        Events_ApplyDamageEvent(source, target, kind, *(CVector3 *)&(position), *(Shared_DamageParameters *)&(params), 0, 0, 128);
    }
}

void Events_ApplyRadialDamage(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent((void *)source, target, kind, *(CVector3 *)&position, *(Shared_DamageParameters *)&params, 1, 0, 128);
}

void Events_ApplyRadialDamageWithKnockback(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent((void *)source, target, kind, *(CVector3 *)&position, *(Shared_DamageParameters *)&params, 1, 1, 128);
}

void Events_PreserveEventArgument(int source, int target, int kind, int eventArgument) {
    int *p = &eventArgument;
    *p = eventArgument;
}

void Events_RunActorNodeOperation(s32 actor, s32 unusedTarget, s32 unusedKind, CVector3 position)
{
  Events_UpdateNodeAtPosition((void *)actor, position, 1);
}

void Events_RunSecondNodeOperation(s32 actor, s32 unusedTarget, s32 unusedKind, CVector3 position)
{
  Events_UpdateNodeAtPosition((void *)actor, position, 0);
}

void Events_StartCameraFadeAtPoint(s32 source, s32 target, s32 kind, Triple testPoint, CEventValueFormat7a fadeParams) {
    NodeEventsStartCameraFadeAtPoint *node;

    node = g_gameplayCameraList.camera;
    while (node != 0) {
        if (Gsky_ContainsVisiblePoint(node, testPoint) != 0) {
            Gsky_StartFade(node, fadeParams.a, fadeParams.b, fadeParams.c, fadeParams.m_FadeStep,
                          fadeParams.m_FadeRed, fadeParams.f, fadeParams.m_FadeBlue);
        }
        node = node->next;
    }
}

void Events_ConsumeEventArgument(int source, int target, int kind, int eventArgument) {
    int *p = &eventArgument;
    *p = eventArgument;
}

/* Moves the target actor's linked player to the requested position, then raises the event on the actor. */
void Events_RequestActorPosition(s32 source, void *target, s32 kind, CVector3 position, struct IntPair positionParams) {
    s32 mode = positionParams.first;
    LevelActor *actor = target;
    ((Player *)actor->controller)->requestedPosition = position;
    Weapon_SpawnTargetPlayerFireEffect(actor, (intptr_t) &actor->behaviorFlags, mode);
}

/* EVENTS_POSTGAMEPLAYMESSAGE.CPP */

void Events_StartEnabledCameraEmitter(s32 sourceActor, s32 targetActor, s32 eventKind, Triple t, Vec4s v) {
    Gsky_StartEmitter(&g_frontendScreenStatus, (f32) v.x, (f32) v.y, (f32) v.z, (f32) v.w * k_playerEventClipScale[1], 1, *(CVector3 *)&t);
}

void Events_StartDisabledCameraEmitter(s32 sourceActor, s32 targetActor, s32 eventKind, Triple t, Vec4s v) {
    Gsky_StartEmitter(&g_frontendScreenStatus, (f32) v.x, (f32) v.y, (f32) v.z, (f32) v.w * k_eventEmitterAngleConstants, 0, *(CVector3 *)&t);
}


void Events_PostGameplayMessage(void *owner, LevelActor *actor, s32 event, Triple position, ResourceManagerState params) {
    if (actor->kind == 1 && (actor->flags & 0x300000)) {
        Player *player = actor->controller;
        void *parent = player->camera;
        if (parent != 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
            Camera_PostScreenMessage(&g_frontendScreenStatus, parent, g_gameplayEventMessageTable[params.active].sound[g_frontendScreenStatus.settings.language]);
#else
            Camera_PostScreenMessage(&g_frontendScreenStatus, parent, gameplaySoundValue(params.active));
#endif
        }
    } else {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        Camera_PostScreenMessage(&g_frontendScreenStatus, &g_frontendScreenStatus.fallbackCamera, g_gameplayEventMessageTable[params.active].sound[g_frontendScreenStatus.settings.language]);
#else
        Camera_PostScreenMessage(&g_frontendScreenStatus, &g_frontendScreenStatus.fallbackCamera, gameplaySoundValue(params.active));
#endif
    }
    if (gameplaySoundHook(params.active) != 0) {
        SoundElement_PlayDialogGroup(gameplaySoundHook(params.active));
    }
}

/* EVENTS_APPLYFLAG100RADIALDAMAGE.CPP */

void Events_ApplyFlag100RadialDamage(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent(source, target, kind, *(CVector3 *)&(position), *(Shared_DamageParameters *)&(params), 1, 0, 0x100);
}

void Events_ApplyFlag100RadialKnockback(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent(source, target, kind, *(CVector3 *)&(position), *(Shared_DamageParameters *)&(params), 1, 1, 0x100);
}

void Events_ApplyFlag200RadialDamage(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent(source, target, kind, *(CVector3 *)&(position), *(Shared_DamageParameters *)&(params), 1, 0, 0x200);
}

void Events_ApplyFlag200RadialKnockback(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent(source, target, kind, *(CVector3 *)&(position), *(Shared_DamageParameters *)&(params), 1, 1, 0x200);
}

void Events_ApplyFlag400RadialDamage(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent(source, target, kind, *(CVector3 *)&(position), *(Shared_DamageParameters *)&(params), 1, 0, 0x400);
}

/* EVENTS_PLAYTEAMCLIP.CPP */

/* Plays an effect at a position through SoundElement_PlayPositionedSoundWithScale unless the global g_simpleObjectPauseState is set, selecting the target from the given object's type and team masks and choosing the scale from the global option flags. */

/* Effect callback that fires only near an object's height: when the event's height lies within k_eventUpperHeightRange below or k_eventLowerHeightRange above the object's y at 0xC, it forwards the event to Events_ApplyDamageEvent with mode 1 and flags 0x200. */

static inline void fire(char *sourceActor, s32 target, s32 kind, Triple position, struct IntPair params)
{
    Events_ApplyDamageEvent((void *)sourceActor, target, kind, *(CVector3 *)&position, *(Shared_DamageParameters *)&params, 1, 0, 0x200);
}

void Events_ApplyFlag400RadialKnockback(s32 source, s32 target, s32 kind, Triple position, struct IntPair params) {
    Events_ApplyDamageEvent((void *)source, target, kind, *(CVector3 *)&position, *(Shared_DamageParameters *)&params, 1, 1, 0x400);
}

void Events_StartActorEmitter(ActorEmitterSource *sourceActor, ContextEventsStartActorEmitter *targetContext, s32 eventKind, Triple emitterPosition, ParamsEventsStartActorEmitter emitterParams) {
    void *resource;

    if ((sourceActor->actorKind == 1) && (sourceActor->flags & 0x300000)) {
        resource = &((ControllerProfile *)targetContext->inner->resource)->effectPool;
        emitterPosition.x = 0;
        emitterPosition.y = 0;
        emitterPosition.z = 0;
    } else {
        resource = &g_controllerRumblePool;
    }

    CScene_StartEventClips(&g_world, resource, emitterParams.value, emitterPosition, emitterParams.angle * *(&k_eventEmitterAngleConstants + 1), emitterParams.scale * k_eventEmitterAndClipScaleConstants);;
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
                scale = k_teamClipPrimaryFlagScale;
            } else if (global[-371] & 0x20) {
                scale = k_teamClipSecondaryFlagScale;
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
    switch (filter->type) {
    case 0:
        if (((EffectSpawnModeView *)actor)->team != effectParams.second) {
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

void Events_FireWithinHeightRange(LevelActor *sourceActor, s32 target, s32 kind, struct TripleEventsFireWithinHeightRange eventPosition, struct IntPair params)
{
    LevelActor *actor = sourceActor;
    f32 d = actor->position0.y - eventPosition.y;

    if (d < 0.0f ? -d <= k_eventLowerHeightRange : d <= k_eventUpperHeightRange) {
        fire(sourceActor, target, kind, *(Triple *)&eventPosition, params);
    }
}

void Events_SetActorEventBit(void *sourceActor, s32 targetActor, s32 eventKind, s32 eventPositionBase, s32 eventPositionY, s32 eventPositionZ, s32 eventParams) {
    u8 actorKind = ((LevelActor *)sourceActor)->kind;
    if (actorKind == 1) {
        s32 *p = &eventPositionBase;
        ((struct ActorEventBitWord *)sourceActor)->value = ((struct ActorEventBitWord *)sourceActor)->value | (actorKind << p[3]);
    }
}

void Events_ClearActorEventBit(void *actor, s32 targetActor, s32 eventKind, s32 eventPositionWord, s32 eventPositionY, s32 eventPositionZ, s32 eventParams) {
    u8 actorKind = ((LevelActor *)actor)->kind;
    if (actorKind == 1) {
        s32 *p = &eventPositionWord;
        ((struct ActorEventBitWord *)actor)->value = ((struct ActorEventBitWord *)actor)->value & ~(actorKind << p[3]);
    }
}

/* EVENTS_SPAWNATTACHEDEFFECT.CPP */

/* Spawns an effect of the given kind for an object through Animpool_SpawnAnimationObject at the object's position with its velocity (none when the object is inactive) and a uniform scale; kind 0x40C instead starts at the camera with no velocity and, once spawned, follows the camera's target through Particle_GetEffectResource, and kinds 0x474 to 0x477 attach to the host's partner effect for active flagged hosts, otherwise the effect is started through Animpool_ReleaseSceneEffect. */

/* Forwards a position read from an object to SetN64_SpawnModelEffect on the global g_modelEffectPool with a zero offset and a zero trailing weight, returning its result. */

void Events_SpawnAttachedEffect(EffectSpawnSourceView *source, void *hostObject, s32 eventKind, Spawn spawn) {
    LevelActor *host = (LevelActor *)hostObject;
    Vec3f scale;
    Vec3f velocity;
    EffectEventsSpawnAttachedEffect *effect;
    void *storage;
    EffectEventsSpawnAttachedEffect *partner;

#if defined(VERSION_DE)
    if (spawn.kind == 801) {
        return;
    }
#endif
    if (source->active == 0) {
        velocity.x = 0;
        velocity.y = 0;
        velocity.z = 0;
    } else {
        velocity = source->velocity;
    }
    spawn.position = source->position;
    scale.x = spawn.size;
    scale.y = spawn.size;
    scale.z = spawn.size;
    if (spawn.kind == 1036) {
        spawn.position = *(CVector3 *)&g_collisionCurrentActor->vecE4;
        velocity.x = 0;
        velocity.y = 0;
        velocity.z = 0;
    }
    storage = Animpool_SpawnAnimationObject(&g_sceneEffectPool, spawn.kind, source->id, spawn.position, 0.0f, velocity, scale, 0);
    effect = storage;
    if (effect == 0) {
        return;
    }
    if (spawn.kind == 1036) {
        effect->target = Particle_GetEffectResource(host);
        effect->offset.x = ((CVector3 *)&g_collisionCurrentActor->vecF0)->x;
        effect->offset.y = ((CVector3 *)&g_collisionCurrentActor->vecF0)->y;
        effect->offset.z = ((CVector3 *)&g_collisionCurrentActor->vecF0)->z;
    } else if ((unsigned)(spawn.kind - 1140) < 4) {
        if (host->kind == 1 && (host->flags & 0x300000)) {
            partner = ((Player *)host->controller);
            if (partner != 0) {
                partner->child = effect;
                effect->scale = partner->scale;
            }
        } else {
            Animpool_ReleaseSceneEffect(effect);
        }
    }
}

s32 Events_SpawnPositionedEffect(s32 sourceActor, LevelActor *targetActor, s32 eventKind, Triple eventPosition, Extra effectParams) {
    CVector3 scale;
    Triple zero;

    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    scale.x = effectParams.scale;
    scale.y = effectParams.scale;
    scale.z = effectParams.scale;
    return SetN64_SpawnModelEffect((intptr_t)&g_modelEffectPool, 0, effectParams.id, *(CVector3 *)&zero, targetActor->position0, 0, 0.0f);
}

typedef struct SoundDefinition { s32 kind; } SoundDefinition;
typedef struct SoundActor {
    char pad0[0x18];
    SoundDefinition *definition;
} SoundActor;
typedef struct SoundSource {
    u8 kind;
    char pad1[0xCF];
    s32 owner;
} SoundSource;

void Events_PlayTeamEffect(SoundActor *actor, SoundSource *source, s32 eventKind,
                     CVector3 position, EventCounterParameters params) {
    f32 gain = k_positionedSoundDefaultGain;
    s32 owner = -1;
    u8 kind;
    if (g_frontendScreenStatus.status[7] == 0 && InstHdr_GetActorMotionIndex(actor) == params.team) {
        kind = source->kind;
        switch (kind) {
        case 0:
            owner = source->owner;
            break;
        case 1:
            if (actor->definition->kind == kind) {
                if (g_frontendScreenStatus.settings.flags & 0x40) {
                    gain = k_positionedSoundAlternateGain;
                }
                if (g_frontendScreenStatus.settings.flags & 0x20) {
                    gain = k_nearbyPlayerBlastConstants[0];
                }
            }
            break;
        }
        SoundElement_PlayPositionedSoundWithScale(params.value, position, 0, owner, gain);
    }
}

/* EVENTS_INCREMENTNEARBYPLAYERCOUNTER.CPP */

/* Calls Barrel_SetLoopingSound_EventsIncrementnearbyplayercounter on an object, its block and a stack argument when the pause word is clear, the object exists and its first byte is one. */

void Events_SetActorLoopingSound(void *sourceActor, LevelActor *object, s32 third, struct IntPair pair, s32 fifth, s32 sixth) {
    if (g_gameSession.clockPaused == 0 && object != 0 && object->kind == 1) {
        do {
            Barrel_SetLoopingSound(object, &(object)->behaviorFlags, sixth);
        } while (0);
    }
}

/* Calls Barrel_StopActorLoopingSound on an object and its block when the object exists and its
   first byte is one. The fourth argument is a record passed by value whose first word lands in
   its home slot. */

void Events_StopActorLoopingSound(void *sourceActor, LevelActor *object, s32 third, struct IntPair pair) {
    if (object != 0 && object->kind == 1) {
        Barrel_StopActorLoopingSound(object, &(object)->behaviorFlags);
    }
}

/* Damages the owner of a live actor (kind 1 with either blast bit of 0x300000 set) that is inside
   the blast: the radius is blastRadius scaled by k_nearbyPlayerBlastConstants[1], and when the squared radius still covers
   the squared distance from the owner's position at 8 to player's position at 8, the remaining
   fraction of the squared radius times blastDamage is applied through Playerai_AddCappedEventCounter. */

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

/* Calls Barrel_StopActorLoopingSound on an object and its sound state block, sets bit 0x20 in that block's first word, clears flags 0x10000, 0x2000 and 0x100, and calls Animpool_ReleaseSceneEffect when flag 0x80000 remains set. */

void Events_DeactivateActor(LevelActor *object, s32 second, s32 third, struct IntPair pair) {
    Barrel_StopActorLoopingSound(object, &(object)->behaviorFlags);
    (object)->behaviorFlags |= 0x20;
    (object)->flags &= 0xFFFEFFFF;
    (object)->flags &= ~0x2000;
    (object)->flags &= ~0x100;
    if ((object)->flags & 0x80000) {
        Animpool_ReleaseSceneEffect(object);
    }
}

/* EVENTS_APPLYDAMAGEREACTION_DATA.CPP */



/* EVENTS_ADJUSTWEAPONHITPOSITION_DATA.CPP */





/* EVENTS_FLOAT_CONSTANT_WORDS_800_C443_C.CPP */



/* EVENTS.CPP */



/* EVENTS_FIREWITHINHEIGHTRANGE_DATA.CPP */



/* EVENTS_PLAYTEAMEFFECT_DATA.CPP */



/* SCENE_EFFECT_TUNING_CONSTANTS.CPP */

/* Retained data for this translation unit. */

const float k_eventsApplydamagereactionDataFloatConstants[8] = {
    1.0f, 2.0e+01f, 1.0f, 1.0e+01f, 12.0f, 10.24f,
    1.0f, 0.5f,
};

const float g_weaponHitPositionHalf[1] = {
    0.5f,
};

const float k_eventsAdjustweaponhitpositionDataFloatConstants[2] = {
    0.04f, 102.399994f,
};

const float k_eventsFloatConstants[2] = {
    1.0f, 1.0f,
};

const float k_eventsTrailingFloatConstants[7] = {
    12.0f, 10.24f, 1.0f, 10.24f, 10.24f, 10.24f,
    0.003921569f,
};

const float k_eventsFirewithinheightrangeDataFloatConstants[5] = {
    1.0f, 2.5f, 0.35f, 76.799995f, 76.799995f,
};

const float k_eventsPlayteameffectDataFloatConstants[3] = {
    1.0f, 2.5f, 0.35f,
};

const float g_Events_IncrementNearbyPlayerCounterConstants[1] = {
    10.24f,
};
