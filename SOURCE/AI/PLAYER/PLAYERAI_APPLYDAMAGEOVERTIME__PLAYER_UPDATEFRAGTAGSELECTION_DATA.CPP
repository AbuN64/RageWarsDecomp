#include "include_asm.h"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/PLAYER_RECORD_AND_FRAGTAG_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAMEPLAY_ROUND_RULES.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/ACTORRESOURCEHEADER.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "GFX/TEXT/PLAYERAI_APPLYDAMAGEOVERTIME_DATA.H"


extern void *Scene_FindActorDefinition(Shared_World *world, s32 selection, s32 modelKind);


extern s32 g_playerWeaponClassMode;







extern void GameObject_DrawBlobShadow(void *actor, CVector3 *offset, s32 raised);



extern void Playerai_ApplyPeriodicHazardDamage(void *player, void *unused);

/** Report whether the nested pointer's word at 0x564 is nonzero. */
int Playerai_HasActiveView(void *object) {
    LinkedActorOwnerView *object_record = object;
    View *nested = object_record->owner;
    if (nested != 0) {
        return nested->shieldActive != 0;
    }
    return 0;
}

/** Report whether the global state word is nonzero. */
int Player_IsClockPaused(void) {
    return g_gameSession.clockPaused != 0;
}

void Playerai_LoadActorModel(void *actor) {
    s32 modelKind;
    void *result;

    modelKind = ((Shared_ActorView *)actor)->state;
    if (g_gameSettings.counters.m_bFragTagOn != 0 && ((Shared_ActorView *)actor)->controls->transientFlag == 1) {
        modelKind = 19;
    }
    result = Scene_FindActorDefinition(&g_world, 11, modelKind);
    if (result != 0) {
        ((Shared_ActorView *)actor)->model = result;
    } else {
        result = Scene_FindActorDefinition(&g_world, 11, -1);
        if (result != 0) {
            ((Shared_ActorView *)actor)->model = result;
        } else {
            result = Scene_FindActorDefinition(&g_world, -1, -1);
            ((Shared_ActorView *)actor)->model = result;
        }
    }
    ((LevelActor *)actor)->scale.x = ((PlayerSequenceResourceView *)result)->scaleX;
    ((LevelActor *)actor)->scale.y = ((PlayerSequenceResourceView *)result)->scaleY;
    ((LevelActor *)actor)->scale.z = ((PlayerSequenceResourceView *)result)->scaleZ;
}

void Playerai_UpdateCharacterModel(void *actor) {
    s32 modelKind;
    Shared_Game *base;

    base = &g_gameSettings;
    if (base->local == 0) {
        modelKind = 102;
    } else if (base->fragTagEnabled != 0 && ((Shared_ActorView *)actor)->controls->transientFlag != 0) {
        modelKind = g_fragTagModelId;
    } else {
        modelKind = g_characterModelIds[((LevelActor *)actor)->definition->character];
        ((Shared_ActorView *)actor)->id = ((Shared_ActorView *)actor)->controls->playerId;
    }
    ((void (*)(void *, void *, s32, s32))Scene_ChangeInstanceModel)(&g_world, actor, modelKind, ((Shared_ActorView *)actor)->effectId);
}

void Playerai_UpdateHeldWeaponModel(Player *actor) {
    s32 modelOffset;

    if (actor->computer != 0) {
        if (g_gameSettings.counters.transitionActive == 0) {
            modelOffset = 23;
            goto after;
        }
    }
    modelOffset = (g_playerWeaponClassMode == 1) ? 0 : 23;
after:
    ((void (*)(void *, void *, s32, s32))Scene_ChangeInstanceModel)(&g_world, &actor->weaponModel,
        ((WeaponInfo *)g_weaponInfoByType[actor->selectedAction])->model + modelOffset,
        actor->weaponAnimationTable->defaultAnimation);
}

void Playerai_DrawCachedModelAndShadow(void *actorIn, s32 shadowMode) {
    CVector3 viewOffset;
    void *animationResource;
    Shared_ActorView *actor;
    PlayerCameraTargetView *message;
    ActorAnimationResourceView *object = actorIn;

    if (object->flags & 0x40000) {
        animationResource = Cache_RequestResource(0, object->resource, object->resource, object->resourceFlags, 4, 0, 0, g_playerModelResourceTag, 1);
        if (animationResource != 0) {
            actor = object->owner;
            Gobjinst_UpdateModelBounds(actorIn, (s32)SetN64_GetPackSection(*(void **)animationResource, 0));
            if (shadowMode != 0) {
                message = actor->message;
                if (message != 0) {
                    viewOffset.x = message->position.x - object->position.x;
                    viewOffset.y = 0.0f;
                    viewOffset.z = ((PlayerCameraTargetView *)actor->message)->position.z - object->position.z;
                    GameObject_DrawBlobShadow(actorIn, &viewOffset, shadowMode);
                }
            }
            Cache_UnlockResource(0, animationResource);
        }
    }
}

void Playerai_SetInheritedMotionFlags(void *player, void *source, s32 enabled) {
    PlayerDamageOverTimeView *object = player;
    ActorFlagsWordView *argument = source;
    s32 flags;
    s32 flag_1000;
    s32 flag_8000;
    s32 flag_10000;

    if (enabled != 0) {
        flags = argument->flags;
        flag_1000 = flags & 0x1000;
        flag_8000 = flags & 0x8000;
        flag_10000 = flags & 0x10000;
        if (flag_1000 == 0) {
            object->effectTimer = 0;
        } else {
            Playerai_ApplyDamageOverTime(player, source);
        }
        if (flag_8000) {
            Playerai_NoopDamageSourceCallback_de(player, source);
        }
        if (flag_10000) {
            Playerai_ApplyPeriodicHazardDamage(player, source);
        }
    }
}

extern void Player_ApplyPlayerDamage(void *player, void *attacker, s32 amount, s32 damageFlags, s32 kind);
/* Damage over time while the source's effect flag 0x1000 is set (Playerai_SetInheritedMotionFlags): advances the player's
 * effect timer by the frame step; past 300 it marks the player and deals max(1, (150 - health / 256) / 15)
 * points (8.8 fixed) of kind 0x1F, then winds the timer back by 22.5 so the next tick follows sooner.
 * HONEST-FORM-OPEN: the step check stores the same value in both arms. jump2 cross-jumps the arms and
 * deletes the test, but its reads of `previous` and `step` keep both live past the sum, which puts the
 * sum in $f2 as in the ROM (REV1-ONE-65B RESULT.md). */
void Playerai_ApplyDamageOverTime(Shared_ActorView *player, void *source) {
    s32 missing;
    s32 amount;
    f32 elapsed;
    f32 previous;
    f32 step;
    previous = player->recoveryTime;
    step = g_frameElapsedTime;
    elapsed = previous + step;
    if (elapsed - previous != step) {
        player->recoveryTime = elapsed;
    } else {
        player->recoveryTime = elapsed;
    }
    if (300.0f < elapsed) {
        missing = 150 - (player->health >> 8);
        amount = 1;
        if (missing > 0) {
            missing /= 15;
            if (missing > 0) {
                amount = missing;
            }
        }
        player->collisionState = 1;
        Player_ApplyPlayerDamage(player, source, amount << 8, 0, 31);
        player->recoveryTime -= 22.5f;
    }
}
