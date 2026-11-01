#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/VECTOR4F.H"
#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/SOUNDINFO.H"
#include "TYPES.H"
#include "WORLD/PLAYERAI_RESPAWNFRAGTAGPLAYER.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/PLAYER_SPAWN_PLACEMENT.H"

extern f32 Graphu64_GetTrianglePlaneHeight(void *node, f32 x, f32 z);

extern f32 Region_GetPolygonHeight(s32, f32, f32);

extern char g_actorParticleEffectSystem;

extern s32 Particle_CountOwnerListOneEffects(void *, s32);

extern s32 InstHdr_GetActorMotionState(void *levelActor);




extern PlayerRespawnHealthView *g_playerSequenceActor;

extern void Player_UpdateRunEndPlayer(void *);


extern s32 g_playerSpecialAnimationTable;

extern void Cache_DrainAndCompactResources(s32 a);



extern s32 SoundElement_PlaySoundAtPosition(s16 track, CVector3 soundPosition, s32 positionAddress, s32 ownerId);

extern void TeamSelect_EmptyWeaponWheelHook(void *weaponWheelState);



extern void Playerai_InitializePlayerHealth(void *player);

void Playerai_ToggleActionFlagMode(Player *player) {
    u8 *ptr;

    ptr = &g_frontendScreenStatus.settings.local;
    if (*ptr != 0) {
        return;
    }
    if (((MenuMatchGlobals *)(ptr - ((char *)&((MenuMatchGlobals *)0)->settings.local - (char *)0)))->suppressFlaggedActions != 0) {
        if (player->inputFlags & 0x20) {
            return;
        }
    }
    if (!(player->actionFlags & 0x800)) {
        return;
    }
    if (player->toggle != 0) {
        player->toggle = 0;
        return;
    }
    player->toggle = 1;
}

void Playerai_SelectAlternateWeapon(Player *player) {
    u8 *ptr;
    WeaponInfo *weaponDefinition;
    s16 alternate;
    u16 alternateWeaponBits;

    ptr = &g_frontendScreenStatus.settings.local;
    if (*ptr != 0) {
        return;
    }
    if (player->weaponLocked != 0) {
        if (player->weaponBusy != 0) {
            return;
        }
    }
    if (((MenuMatchGlobals *)(ptr - ((char *)&((MenuMatchGlobals *)0)->settings.local - (char *)0)))->suppressFlaggedActions != 0) {
        if (player->inputFlags & 0x20) {
            return;
        }
    }
    if (!(player->actionFlags & 0x200)) {
        return;
    }
    weaponDefinition = g_weaponInfoByType[player->weapon];
    alternate = weaponDefinition->alternate;
    alternateWeaponBits = (u16)weaponDefinition->alternate;
    if (alternate == -1) {
        return;
    }
    if (player->actions[alternate][0] != 0) {
        player->weapon = (s16)alternateWeaponBits;
    }
}

void Playerai_UpdateSurfaceHeightEffect(void *surface, CVector3 *position) {
    f32 first;
    f32 amount;

    if (surface != 0 && position != 0 &&
        (((Shared_CollisionSurface *)surface)->flags & 0x40)) {
        first = Graphu64_GetTrianglePlaneHeight(surface,
            position->x, position->z);
        amount = (f32)(s32)(first - Region_GetPolygonHeight(surface,
            position->x, position->z));
        if (amount < g_playerSurfaceAudioHeightThreshold) {
            SoundElement_SetClampedAudioLevel(g_playerSurfaceAudioBaseLevel - (amount * g_playerSurfaceAudioHeightScale));
            return;
        }
    }
    SoundElement_SetClampedAudioLevel(0.0f);
}

/** Perform no work for callers at VRAM 0x8022EAF4. */
void Playerai_EmptySurfaceHeightEffectHook(void) {
}

/** Test whether an actor satisfies the condition selected by an entry type. */
s32 Playerai_PlayerHasAmmoForWeapon(void *player, s32 requestedWeaponType) {
    void *entry;
    s16 *condition;
    char *indexed;
    s32 offset;

    entry = g_weaponInfoByType[requestedWeaponType];
    {
        s32 sw_arg1_value = requestedWeaponType;
        if ((unsigned int)sw_arg1_value > 21) {
            goto sw_arg1_default;
        }
        switch (sw_arg1_value) {
        case 0: goto sw_arg1_0;
        case 1: goto sw_arg1_1;
        case 2: goto sw_arg1_1;
        case 3: goto sw_arg1_3;
        case 4: goto sw_arg1_4;
        case 5: goto sw_arg1_1;
        case 6: goto sw_arg1_1;
        case 7: goto sw_arg1_1;
        case 8: goto sw_arg1_1;
        case 9: goto sw_arg1_1;
        case 10: goto sw_arg1_1;
        case 11: goto sw_arg1_1;
        case 12: goto sw_arg1_12;
        case 13: goto sw_arg1_1;
        case 14: goto sw_arg1_1;
        case 15: goto sw_arg1_1;
        case 16: goto sw_arg1_default;
        case 17: goto sw_arg1_default;
        case 18: goto sw_arg1_0;
        case 19: goto sw_arg1_0;
        case 20: goto sw_arg1_0;
        case 21: goto sw_arg1_0;
        }
    }
    do {
    sw_arg1_1:
    sw_arg1_2:
    sw_arg1_5:
    sw_arg1_6:
    sw_arg1_7:
    sw_arg1_8:
    sw_arg1_9:
    sw_arg1_10:
    sw_arg1_11:
    sw_arg1_13:
    sw_arg1_14:
    sw_arg1_15:
        condition = ((WeaponInfo *)(entry))->weaponClass;
        offset = condition[0] * 2;
        indexed = player;
        indexed += offset;
        return ((Shared_ActorView *)player)->ammo[condition[0]] >= condition[3];
    sw_arg1_3:
        return ((Shared_ActorView *)player)->ammo[0] >= 3;
    sw_arg1_4:
        return ((Shared_ActorView *)player)->ammo[0] >= 5;
    sw_arg1_12:
        if (((Shared_ActorView *)player)->ammo[2] == 0) {
            goto check_external;
        }
    sw_arg1_0:
    sw_arg1_18:
    sw_arg1_19:
    sw_arg1_20:
    sw_arg1_21:
        return 1;
    check_external:
        return Particle_CountOwnerListOneEffects(&g_actorParticleEffectSystem, (s32)player);
    sw_arg1_default:
        return 0;

    } while (0);
}

int Playerai_ReturnZero(void) {
    char pad[0x10];
    return 0;
}

s32 Playerai_TryEnterLandedState(void *player, LevelActor *actor) {
    if (actor->position1.y <= 0.0f && InstHdr_GetActorMotionState(actor) != 0) {
        Player_SetPlayerState(player, actor, 2);
        return 1;
    }
    return 0;
}

/** Update the object's state code from identity, mode, and height bounds. */







void Playerai_SelectMovementAnimation(FragTagRespawnActorView *object) {
    int suppress = 0;
    float value;

    if (object->unk_0x086C == 4420) {
        suppress = object->unk_0x010E == 0;
    }
    if (object->ownerId == g_fragTagModelId) {
        object->unk_0x086C = 2210;
        return;
    }
    if (!suppress) {
        value = object->unk_0x06C0;
        if (g_playerMovementForwardAnimationThreshold <= value) {
            object->unk_0x086C = 2210;
            return;
        }
        if (value <= g_playerMovementReverseAnimationThreshold) {
            object->unk_0x086C = 2215;
            return;
        }
        object->unk_0x086C = 20;
    }
}

/** Empty adjacent entry point included in Playerai_SelectMovementAnimation's Splat span. */
void Playerai_EmptyMovementAnimationHook(void) {
}

void Playerai_AdvanceCurrentRunEndState(void) {
    if (g_playerSequenceActor->health == 1) {
        Player_UpdateRunEndPlayer((s32)g_playerSequenceActor);
    } else {
        Player_SetPlayerState(g_playerSequenceActor, g_playerSequenceActor, 34);
    }
    g_playerSequenceWindowEnabled = 1;
    g_playerSequenceCompletionPending = 0;
}

void Playerai_UpdateStoredRunEndPlayer(void) {
    Player_UpdateRunEndPlayer(g_playerTrackFiftyRequest);
}

void Playerai_ResetMotionAndSelectIdleAnimation(FragTagRespawnActorView *player)
{
  s32 clearedActorFlags;
  clearedActorFlags = player->flags & 0xFF7FFFFF;
  player->flags = clearedActorFlags;
  player->unk_0x001C = 0;
  player->unk_0x0020 = 0;
  player->unk_0x0024 = 0;
  player->unk_0x11D8 = 0.0f;
  player->flags = clearedActorFlags | 0x01000000;
  player->unk_0x11FC = 0;
  player->flags = clearedActorFlags | 0x01000000;
  if (player->unk_0x13B4 == (&g_playerSpecialAnimationTable))
  {
    player->unk_0x086C = 24100;
    return;
  }
  player->unk_0x086C = 1;
}

void Playerai_ReleasePlayerResource(ResourceLoadState *resourceLoadState) {
    s32 handle;

    Control_SetControllerMode(0);
    Cache_DrainAndCompactResources(0);
    handle = resourceLoadState->handle;
    if (handle != 0) {
        Cache_ReleaseResource(0, handle);
        resourceLoadState->handle = 0;
        resourceLoadState->state4 = 0;
        resourceLoadState->state8 = 0;
    }
}

/** Preserve the empty hook at VRAM 0x8022EDE4. */
void Playerai_EmptyPlayerResourceHook(void) {
}

void Playerai_RespawnFragTagPlayer(void *player) {
    s32 mode;

    ((Shared_ActorView *)player)->controls->transientFlag = 1;
    mode = g_gameSettings.counters.m_nFragTagSkin;
    switch (mode) {
    case 0:
        SoundElement_PlaySoundAtPosition(6305,
                      ((Shared_ActorView *)player)->position.vector,
                      (s32)((char *)player + 8), -1);
        break;
    case 1:
        SoundElement_PlaySoundAtPosition(6505,
                      ((Shared_ActorView *)player)->position.vector,
                      (s32)((char *)player + 8), -1);
        break;
    case 2:
        SoundElement_PlaySoundAtPosition(6405,
                      ((Shared_ActorView *)player)->position.vector,
                      (s32)((char *)player + 8), -1);
        break;
    }
    TeamSelect_EmptyWeaponWheelHook((char *)&((SharedPlayer *)player)->views5E8.view938_128.strokes);
    ((FragTagRespawnActorView *)player)->unk_0x11B4 = 0;
    Actor_RequestActorState(&((Shared_ActorView *)player)->weapon, &((Shared_ActorView *)player)->weapon.behaviorFlags, 1);
    Player_PlacePlayerAtSpawnPoint(player, ((Shared_ActorView *)player)->spawn, 0, 1);
    Playerai_InitializePlayerHealth(player);
}

s32 Playerai_CountTrailingSpaces(s32 textAddress, s32 length) {
    s32 characterIndex;
    s32 result;
    s32 space;

    result = 0;
    space = 32;
    characterIndex = length;
loop_1:
    characterIndex -= 1;
    if (*((u8 *)textAddress + characterIndex) == space) {
        result += 1;
        if (characterIndex > 0) {
            goto loop_1;
        }
    }
    return result;
}

