#include "COMMON/RESOURCELOADSTATE.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "AI/WEAPONAI.H"
#include "COMMON/LONE/WEAPON_LOCKED_NOTICE_TEXT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIPLE.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "COMMON/PLAYERPROFILES.H"
#include "COMMON/SHAREDCALLBACK5.H"

/* Handles a player's attack trigger: nothing while cooling down past g_weaponTriggerCooldownLimit; the trigger is the
 * controller latch at 0x23C (cleared when read) for a flagged controlled player, else flag 0x2000; when it
 * fires and Weaponai_CanStartFiring accepts the attack, a ranged attack (type 2) that may fire takes action 8 and
 * returns 2, otherwise action 4 starts with the combo byte cleared and returns 1. Adapted from
 * Weaponai_TryEnterAlternateStateEight with the fire check as the same static helper. */
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PLAYER_GETPLAYERINDEX.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "AI/PLAYER/PLAYER_GETAMMOCAPACITY.H"
#include "GSKY/SKY_POSTTARGETEDSCREENMESSAGE.H"
#include "WEAPONAI/WEAPONAI_DRAWREDMARKERQUAD__WEAPONAI.H"
#include "WORLD/PLAYERPROFILE.H"
/* The weapon actor links to its Player and AiController; attack is its WeaponFireState. */





















static inline s32 can_fire(char *player) {
    s32 ammo;

    if (((Player *)(player))->cooldown > 0.0f) {
        return 0;
    }
    if (((Player *)(player))->computer != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((Player *)(player))->slot], ((Player *)(player))->selectedAction);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((Player *)(player))->camera != 0) {
            Gsky_PostTargetedScreenMessage(&g_playerViewRenderContext.object, ((Player *)(player))->camera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                          Player_GetPlayerIndex(&g_playerViewRenderContext, player), g_alternateFireMessageDuration);
        }
    }
    return ammo;
}

s32 Weaponai_TryRequestFiringState(void *actor, void *attack) {
    char *player;
    s32 trigger;
    char *control;

    player = ((LevelActor *)(actor))->controller;
    if (((Player *)(player))->cooldown > g_weaponTriggerCooldownLimit) {
        return 0;
    }
    if ((((LevelActor *)(actor))->flags & 0x300000) && ((Player *)(player))->computer != 0) {
        control = ((Player *)(player))->controller;
        trigger = ((AiController *)(control))->fireRequested;
        ((AiController *)(control))->fireRequested = 0;
    } else {
        trigger = ((Player *)(player))->inputFlags & 0x2000;
    }
    if (trigger != 0 && Weaponai_CanStartFiring(actor, attack) != 0) {
        if (((WeaponFireState *)(attack))->mode == 2 && can_fire(player)) {
            Actor_RequestActorState(actor, attack, 8);
            return 2;
        }
        Actor_RequestActorState(actor, attack, 4);
        ((WeaponFireState *)(attack))->triggerMode = 0;
        return 1;
    }
    return 0;
}

extern s16 g_weaponActionRecords[];
/* Updates alternate fire, falling back to another weapon when neither mode has
 * ammunition. Reports unavailable modes, preserves the selected action captured
 * on entry, then processes the attack trigger. */
#include "COMMON/AIPROFILE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
typedef struct AlternateModeInfo { u8 pad0[0x14]; u32 flags; } AlternateModeInfo;
/* The adjacent exact can_fire supplies the same readiness check; this call site
 * owns its distinct message-duration literal and localized European strings. */
static inline s32 can_toggle_mode(Player *player) {
    s32 allowed;
    if (player->cooldown > 0.0f) return 0;
    if (player->computer != 0) return 1;
    if (g_gameSettings.controllerMode != 1) return 1;
    allowed = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[player->slot], player->selectedAction);
    if (allowed == 0) {
        SoundElement_PlayFlatSound(3405);
        if (player->camera) {
            Gsky_PostTargetedScreenMessage(&g_playerViewRenderContext.object, player->camera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                                             Player_GetPlayerIndex(&g_playerViewRenderContext, player), 1.0f);
        }
    }
    return allowed;
}
void Weaponai_UpdateAlternateFire(void *actor, void *attack) {
    Player *player = (Player *)((LevelActor *)actor)->controller;
    s32 action = g_weaponActionRecords[player->pose * 12];
    AlternateModeInfo *info = (AlternateModeInfo *)g_weaponInfoByType[player->selectedAction];
    if (!Player_HasAmmoForMode(player, player->selectedAction)) {
        if (((WeaponFireState *)attack)->mode != 2) {
            player->weapon = Weaponai_FindNextUsableWeapon(player);
            return;
        }
        ((WeaponFireState *)attack)->mode = 1;
        if (info->flags & 0x20) player->state7E8 = 0;
        if (!Player_HasAmmoForMode(player, player->selectedAction)) {
            player->weapon = Weaponai_FindNextUsableWeapon(player);
            return;
        }
    }
    if ((player->actionFlags & 0x4000) && player->selectedAction < 18 && can_toggle_mode(player)) {
        if (((WeaponFireState *)attack)->mode == 1) {
            ((WeaponFireState *)attack)->mode = 2;
            if (!Player_HasAmmoForMode(player, player->selectedAction)) {
                SoundElement_PlayFlatSound(3405);
                if (player->camera) {
                    Gsky_PostTargetedScreenMessage(&g_playerViewRenderContext.object, player->camera,
                                                     RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_playerViewRenderContext.game.language),
                                                     Player_GetPlayerIndex(&g_playerViewRenderContext, player), 1.0f);
                }
                ((WeaponFireState *)attack)->mode = 1;
            } else if (info->flags & 0x20) {
                player->state7E8 = 1;
            }
        } else {
            ((WeaponFireState *)attack)->mode = 1;
            if (info->flags & 0x20) player->state7E8 = 0;
        }
    }
    if (Weaponai_TryRequestFiringState(actor, attack) == 0 && !(((AiTarget *)actor)->flags & 0x400)) {
        Actor_RequestActorState(actor, attack, action);
    }
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "WEAPONS/PLAYERRECAT1450V1.H"


extern s16 g_weaponActionRecords[];

extern s32 SoundElement_PlaySoundAtPosition(s16 track, CVector3 position, s32 emitterKey, s32 ownerId);












/* The PAL copy of Weapon_UpdateIdleWeaponSelection: the weapon switch and the idle request are two calls here. */
#endif
