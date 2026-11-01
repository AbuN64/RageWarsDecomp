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
/* AttackTrigger* are unresolved canonical player/actor/control/attack types. */







extern s32 Player_GetProfileAchievementFlag(void *, s16);
extern void Gsky_PostTargetedScreenMessage(void *, void *, s32, s32, f32);










typedef struct AttackTriggerPlayer AttackTriggerPlayer;
typedef struct AttackTriggerActor AttackTriggerActor;
typedef struct AttackTriggerControl AttackTriggerControl;
typedef struct AttackTriggerAction AttackTriggerAction;
struct AttackTriggerPlayer {
    char pad0[0x5D4];
    s32 playerIndex;
    char pad5D4[0x5DC - 0x5D4 - sizeof(s32)];
    void* camera;
    char pad5DC[0x62E - 0x5DC - sizeof(void*)];
    s16 weaponMode;
    char pad62E[0x6AC - 0x62E - sizeof(s16)];
    s32 inputFlags;
    char pad6AC[0x11D8 - 0x6AC - sizeof(s32)];
    f32 cooldown;
    char pad11D8[0x1450 - 0x11D8 - sizeof(f32)];
    s32 computerControlled;
    char pad1450[0x1454 - 0x1450 - sizeof(s32)];
    char* control;
};
struct AttackTriggerActor {
    char pad0[0x100];
    s32 flags;
    char pad100[0x1D8 - 0x100 - sizeof(s32)];
    char* player;
};
struct AttackTriggerControl {
    char pad0[0x23C];
    s32 fireRequested;
};
struct AttackTriggerAction {
    char pad0[0xCB];
    u8 triggerConsumed;
    char padCB[0x13C - 0xCB - sizeof(u8)];
    s32 fireMode;
};


static inline s32 can_fire(char *player) {
    s32 ammo;

    if (((AttackTriggerPlayer *)(player))->cooldown > 0.0f) {
        return 0;
    }
    if (((AttackTriggerPlayer *)(player))->computerControlled != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((AttackTriggerPlayer *)(player))->playerIndex], ((AttackTriggerPlayer *)(player))->weaponMode);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((AttackTriggerPlayer *)(player))->camera != 0) {
            Gsky_PostTargetedScreenMessage(&g_playerViewRenderContext.object, ((AttackTriggerPlayer *)(player))->camera, RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                          Player_GetPlayerIndex(&g_playerViewRenderContext, player), g_alternateFireMessageDuration);
        }
    }
    return ammo;
}

s32 Weaponai_TryRequestFiringState(void *actor, void *attack) {
    char *player;
    s32 trigger;
    char *control;

    player = ((AttackTriggerActor *)(actor))->player;
    if (((AttackTriggerPlayer *)(player))->cooldown > g_weaponTriggerCooldownLimit) {
        return 0;
    }
    if ((((AttackTriggerActor *)(actor))->flags & 0x300000) && ((AttackTriggerPlayer *)(player))->computerControlled != 0) {
        control = ((AttackTriggerPlayer *)(player))->control;
        trigger = ((AttackTriggerControl *)(control))->fireRequested;
        ((AttackTriggerControl *)(control))->fireRequested = 0;
    } else {
        trigger = ((AttackTriggerPlayer *)(player))->inputFlags & 0x2000;
    }
    if (trigger != 0 && Weaponai_CanStartFiring(actor, attack) != 0) {
        if (((AttackTriggerAction *)(attack))->fireMode == 2 && can_fire(player)) {
            Actor_RequestActorState(actor, attack, 8);
            return 2;
        }
        Actor_RequestActorState(actor, attack, 4);
        ((AttackTriggerAction *)(attack))->triggerConsumed = 0;
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
    Player *player = (Player *)((AttackTriggerActor *)actor)->player;
    s32 action = g_weaponActionRecords[player->pose * 12];
    AlternateModeInfo *info = (AlternateModeInfo *)g_weaponInfoByType[player->selectedAction];
    if (!Player_HasAmmoForMode(player, player->selectedAction)) {
        if (((AttackTriggerAction *)attack)->fireMode != 2) {
            player->weapon = Weaponai_FindNextUsableWeapon(player);
            return;
        }
        ((AttackTriggerAction *)attack)->fireMode = 1;
        if (info->flags & 0x20) player->state7E8 = 0;
        if (!Player_HasAmmoForMode(player, player->selectedAction)) {
            player->weapon = Weaponai_FindNextUsableWeapon(player);
            return;
        }
    }
    if ((player->actionFlags & 0x4000) && player->selectedAction < 18 && can_toggle_mode(player)) {
        if (((AttackTriggerAction *)attack)->fireMode == 1) {
            ((AttackTriggerAction *)attack)->fireMode = 2;
            if (!Player_HasAmmoForMode(player, player->selectedAction)) {
                SoundElement_PlayFlatSound(3405);
                if (player->camera) {
                    Gsky_PostTargetedScreenMessage(&g_playerViewRenderContext.object, player->camera,
                                                     RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_playerViewRenderContext.game.language),
                                                     Player_GetPlayerIndex(&g_playerViewRenderContext, player), 1.0f);
                }
                ((AttackTriggerAction *)attack)->fireMode = 1;
            } else if (info->flags & 0x20) {
                player->state7E8 = 1;
            }
        } else {
            ((AttackTriggerAction *)attack)->fireMode = 1;
            if (info->flags & 0x20) player->state7E8 = 0;
        }
    }
    if (Weaponai_TryRequestFiringState(actor, attack) == 0 && !(((AttackTriggerActor *)actor)->flags & 0x400)) {
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
extern s16 Weaponai_FindNextUsableWeapon(void *player);
extern s32 SoundElement_PlaySoundAtPosition(s16 track, CVector3 position, s32 emitterKey, s32 ownerId);












/* The PAL copy of Weapon_UpdateIdleWeaponSelection: the weapon switch and the idle request are two calls here. */
#endif
