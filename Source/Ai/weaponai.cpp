#include "Ai/Weapon/weapon.h"
#include "include_asm.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include <PR/gbi.h>
#include <platform_sdk.h>
#include "Common/gameplay_transition.h"
#include "Common/player_record_and_fragtag_views.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/sessionhandlerrow.h"
#include "types.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/shared_menureply.h"
#include "Common/resourceloadstate.h"
#include "Weapons/weaponai_drawredmarkerquad.h"
#include "Weapons/actor_requestactorstate.h"
#include "Render/soundelement_playflatsound.h"
#include "Ai/ai_shared_symbols.h"
#include "Common/world.h"
#include "Weapons/weapon_switch_actions.h"
#include "Common/menu_match_globals.h"
#include "Engine/Audio/channel.h"
#include "Weaponai/weaponai_drawredmarkerquad__weaponai.h"
#include "World/playerai_respawnfragtagplayer.h"
#include "Common/shared_gameslot.h"
#include "Weapons/player_inventory.h"
#include "Particle/particle_releaseownerlistoneeffects.h"
#include "Ai/weaponai.h"
#include "Common/Lone/weapon_locked_notice_text.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/runtime_declarations.h"
#include "Common/triple.h"
#include "Common/playerprofiles.h"
#include "Common/ai_behaviour_types.h"
#include "Common/player_getplayerindex.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Gsky/sky_posttargetedscreenmessage.h"
#include "World/playerprofile.h"
#include "Common/aiprofile.h"
#include "Common/shared_optionsscreen.h"
#include "Common/player_sequence_state.h"
#include "Common/rendercounters.h"
#include "Engine/Audio/T2SoundElement.h"
#include "Common/menu_text.h"
#include "Common/gameplay_round_rules.h"
#include "Render/weapon_initializechargeandstartupcues_data.h"
#include "Ai/weapon_updatealternatefire__weaponai.h"
#include "Menu/pak_load.h"
#include "Common/resultsoptionsscreen.h"
#include "Common/animationtriggerdefinition.h"
#include "Common/name.h"
#include "Common/gameplay_camera.h"
#include "Render/playerai_toggleforcemarker.h"
#include "Ai/player_alternate_fire.h"
#include "Weapons/player_updatefragtagselection.h"

void Weaponai_DrawRedMarkerQuad(void *object, void *drawContext) {
    MarkerActor *actor = object;
    MarkerNode *node;
    s32 red, alpha;
    node = actor->node;
    if (node->active) {
        gSPMatrix(g_displayListCursor++, (uintptr_t)&node->matrices[g_lightingBufferIndex], G_MTX_LOAD);
        gDPPipeSync(g_displayListCursor++);
        Geometry_InvalidateMaterialKeys();
        Geometry_SetModePreset(14);
        Geometry_SetCombineMode(28);
        red = 200; alpha = 150;
        gSPGeometryMode(g_displayListCursor++, G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | 0x80, 0);
        gSPGeometryMode(g_displayListCursor++, 0, G_SHADE | G_SHADING_SMOOTH);
        g_weaponRedMarkerVertices[0].x = 1;
        g_weaponRedMarkerVertices[0].y = 1;
        g_weaponRedMarkerVertices[0].z = 0;
        g_weaponRedMarkerVertices[0].flag = 0;
        g_weaponRedMarkerVertices[0].s = 0;
        g_weaponRedMarkerVertices[0].t = 0;
        g_weaponRedMarkerVertices[0].r = red;
        g_weaponRedMarkerVertices[0].g = 0;
        g_weaponRedMarkerVertices[0].b = 0;
        g_weaponRedMarkerVertices[0].a = red;
        g_weaponRedMarkerVertices[1].x = -1;
        g_weaponRedMarkerVertices[1].y = 1;
        g_weaponRedMarkerVertices[1].z = 0;
        g_weaponRedMarkerVertices[1].flag = 0;
        g_weaponRedMarkerVertices[1].s = 0;
        g_weaponRedMarkerVertices[1].t = 0;
        g_weaponRedMarkerVertices[1].r = red;
        g_weaponRedMarkerVertices[1].g = 0;
        g_weaponRedMarkerVertices[1].b = 0;
        g_weaponRedMarkerVertices[1].a = red;
        g_weaponRedMarkerVertices[2].x = 15;
        g_weaponRedMarkerVertices[2].y = 1;
        g_weaponRedMarkerVertices[2].z = -1;
        g_weaponRedMarkerVertices[2].flag = 0;
        g_weaponRedMarkerVertices[2].s = 0;
        g_weaponRedMarkerVertices[2].t = 0;
        g_weaponRedMarkerVertices[2].r = red;
        g_weaponRedMarkerVertices[2].g = 0;
        g_weaponRedMarkerVertices[2].b = 0;
        g_weaponRedMarkerVertices[2].a = alpha;
        g_weaponRedMarkerVertices[3].x = -15;
        g_weaponRedMarkerVertices[3].y = 1;
        g_weaponRedMarkerVertices[3].z = -1;
        g_weaponRedMarkerVertices[3].flag = 0;
        g_weaponRedMarkerVertices[3].s = 0;
        g_weaponRedMarkerVertices[3].t = 0;
        g_weaponRedMarkerVertices[3].r = red;
        g_weaponRedMarkerVertices[3].g = 0;
        g_weaponRedMarkerVertices[3].b = 0;
        g_weaponRedMarkerVertices[3].a = alpha;
        gSPVertex(g_displayListCursor++, (u32)g_weaponRedMarkerVertices, 4, 0);
        gSP1Triangle(g_displayListCursor++, 0, 1, 2, 0);
        gSP1Triangle(g_displayListCursor++, 1, 2, 3, 0);
        if (node->extra) Fx_DrawRedParticleQuad((uintptr_t)&node->extraMatrices[g_lightingBufferIndex]);
    }
}

s32 Weaponai_FindNextUsableWeapon(void *player)
{
    s32 slot;
    s32 category;
    s32 special;
    Player *actor;
    char *indexed;
    char *scan;

    actor = player;
    category = actor->weaponSlots[actor->selectedAction].action;
    if (category < 0) {
        category = 0;
    }
    if (category >= 8) {
        category = 0;
    }

    category++;
    if (category < 8) {
        special = 6;
        do {
            for (slot = 0; slot < 22; slot++) {
                if (category == actor->weaponSlots[slot].action) {
                    break;
                }
            }
            if ((slot < 22) && Playerai_PlayerHasAmmoForWeapon(actor, slot)) {
                if ((slot != special) || (actor->ammo[0] >= 11)) {
                    if ((actor->computer == 0) || (slot < 18)) {
                        return slot;
                    }
                }
            }
            category++;
            slot = 0;
        } while (category < 8);
    }

    category = actor->weaponSlots[actor->selectedAction].action;
    if (category < 0) {
        category = 0;
    }
    if (category >= 8) {
        category = 0;
    }

    category--;
    if (category > 0) {
        special = 6;
        do {
            for (slot = 0; slot < 22; slot++) {
                if (category == actor->weaponSlots[slot].action) {
                    break;
                }
            }
            if ((slot < 22) && Playerai_PlayerHasAmmoForWeapon(actor, slot)) {
                if ((slot != special) || (actor->ammo[0] >= 11)) {
                    return slot;
                }
            }
            category--;
            slot = 0;
        } while (category > 0);
    }
    return 0;
}

s32 Weaponai_NextAvailableWeapon(ObjectWeaponsNextAvailableWeapon *player) {
    s32 value;
    s32 number;
    s32 index;
    s32 result;

    value = player->values[player->selected * 2];
    if (value < 0) {
        value = 0;
    }
    if (value >= 8) {
        value = 0;
    }
    value++;
    while (value < 8) {
        number = 0;
        while ((number < 22) && (value != player->values[number * 2])) {
            number++;
        }
        if ((number < 22) && (Playerai_PlayerHasAmmoForWeapon(player, number) != 0)) {
            return number;
        }
        value++;
    }
    value = player->values[player->selected * 2];
    number = 1;
    while (number < value) {
        index = 0;
        while ((index < 22) && (number != player->values[index * 2])) {
            index++;
        }
        if ((index < 22) && (Playerai_PlayerHasAmmoForWeapon(player, index) != 0)) {
            return index;
        }
        number++;
    }
    SoundElement_PlayFlatSound(3405);
    result = player->selected;
    return result;
}

void Weaponai_UpdateCallbacksAndTimers(void *actorStorage, void *stateController) {
    void *actor;
    s16 index;
    s32 value;
    f32 old_delta;
    f32 scaled_delta;
    f32 zero;
    f32 timer;
    void *callback_owner;
    void (*callback)(void *, void *);

    actor = ((WeaponMarkerActorContext *)(actorStorage))->owner;
    index = ((WeaponMarkerActorView *)(actor))->pose;
    value = g_weaponActionRecords[index].action;

    if (0.0f < ((WeaponMarkerActorView *)(actor))->cooldown) {
        return;
    }

    old_delta = g_frameElapsedTime;
    scaled_delta = old_delta * g_weaponMarkerDeltaScale;
    if (actor != 0 && (((WeaponMarkerActorView *)(actor))->reactionFlags & 0x2000)) {
        g_frameElapsedTime = scaled_delta;
    } else {
        g_frameElapsedTime = old_delta;
    }

    timer = ((WeaponMarkerControllerView *)(stateController))->timeRemainingA;
    zero = 0.0f;
    if (zero < timer) {
        ((WeaponMarkerControllerView *)(stateController))->timeRemainingA = timer - g_frameElapsedTime;
        ((WeaponMarkerActorContext *)(actorStorage))->stateFlag = 0;
    } else {
        ((WeaponMarkerActorContext *)(actorStorage))->stateFlag = 0;
    }

    if (zero < ((WeaponMarkerControllerView *)(stateController))->timeRemainingB) {
        ((WeaponMarkerControllerView *)(stateController))->timeRemainingB -= g_frameElapsedTime;
    }

    if (value == 1) {
        Actor_RequestActorState(actorStorage, stateController, 1);
    }
    if (((WeaponMarkerActorView *)(actor))->weapon != ((WeaponMarkerActorView *)(actor))->selectedAction) {
        ((WeaponMarkerActorView *)(actor))->recenterSuppressed = 0;
        Actor_RequestActorState(actorStorage, stateController, 1);
    }

    callback_owner = ((WeaponMarkerControllerView *)(stateController))->callback_owner;
    if (callback_owner != 0) {
        callback = ((struct Hook *) callback_owner)->fn;
        if (callback != 0) {
            callback(actorStorage, stateController);
        }
    }

    callback = ((struct WeaponMarkerCallbackView *) ((char *) g_weaponInfoByType[((WeaponMarkerActorView *) actor)->selectedAction]))->callback;
    if (callback != 0) {
        callback(actorStorage, stateController);
    }
    Playerai_UpdateHeldWeaponModel(actor);
    g_frameElapsedTime = old_delta;
}

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))


void Weaponai_InitializeSwitchAndRequestIdle(void *actor, void *weaponFireState) {
    s16 index;
    u16 unsigned_index;
    void *owner;
    void *state;

    state = ((LevelActor *)actor)->controller;
    index = ((Player *)state)->weapon;
    unsigned_index = (u16)((Player *)state)->weapon;
    if ((((Player *)state)->selectedAction != index) || (g_world.mode != 4)) {
        if (Weapon_IsPrimarySwitchGroup(index) != 0) {
            ((Player *)state)->weaponChanged = 1;
        } else if (Weapon_IsSecondarySwitchGroup(index) != 0) {
            ((Player *)state)->secondaryChanged = 1;
        } else if (Weapon_IsSpecialSwitchGroup(index) != 0) {
            ((Player *)state)->specialChanged = 1;
        }
        ((Player *)state)->selectedAction = unsigned_index;
        ((WeaponFireState *)weaponFireState)->animation = ((WeaponInfo *)g_weaponInfoByType[(s16)unsigned_index])->animation;
        ((WeaponFireState *)weaponFireState)->animationCount = ((WeaponInfo *)(g_weaponInfoByType[((Player *)state)->selectedAction]))->animationCount;
        owner = ((Player *)state)->camera;
        if ((owner != 0) && ((u32)g_gameLoopFrameCount >= 5U)) {
            Camera_PostScreenMessage(&g_frontendScreenStatus, owner,
                *(void **)*(void **)g_weaponInfoByType[((Player *)state)->selectedAction]);
        }
        ((WeaponFireState *)weaponFireState)->spinStep = 0;
        ((WeaponFireState *)weaponFireState)->spin = 0;
        ((Shared_Actor *)actor)->color = 0;
        ((WeaponFireState *)weaponFireState)->charge = 0;
    }
    Actor_RequestActorState(actor, weaponFireState, 0);
}

void Weaponai_InitializeSwitchForSingleRound(void *actor, WeaponFireState *fireState) {
    s16 nextWeapon;
    u16 nextWeaponUnsigned;
    void *messageOwner;
    char *player;

    player = ((LevelActor *)actor)->controller;
    nextWeapon = ((Player *)player)->weapon;
    nextWeaponUnsigned = (u16)((Player *)player)->weapon;
    if ((((Player *)player)->selectedAction != nextWeapon) || (g_world.mode != 4)) {
        if (Weapon_IsPrimarySwitchGroup(nextWeapon) != 0) {
            ((Player *)player)->weaponChanged = 1;
        } else if (Weapon_IsSecondarySwitchGroup(nextWeapon) != 0) {
            ((Player *)player)->secondaryChanged = 1;
        } else if (Weapon_IsSpecialSwitchGroup(nextWeapon) != 0) {
            ((Player *)player)->specialChanged = 1;
        }
        ((Player *)player)->selectedAction = nextWeaponUnsigned;
        fireState->animation = ((WeaponInfo *)(g_weaponInfoByType[(s16)nextWeaponUnsigned]))->animation;
        fireState->animationCount = ((WeaponInfo *)(g_weaponInfoByType[((Player *)player)->selectedAction]))->animationCount;
        messageOwner = ((Player *)player)->camera;
        if ((messageOwner != 0) && ((u32)g_gameLoopFrameCount >= 5U)) {
            Camera_PostScreenMessage(&g_frontendScreenStatus, messageOwner,
                          **(void ***)g_weaponInfoByType[((Player *)player)->selectedAction]);
        }
        fireState->spinStep = 0;
        fireState->spin = 0;
        ((Shared_Actor *)actor)->color = 0;
        fireState->charge = 0;
    }
    fireState->mode = 1;
    fireState->rounds = 1;
}
#endif


#if defined(VERSION_EU)
const unsigned int k_weaponIdleSelectionPad[1] = { 0x00000000 };
#endif
s32 Weaponai_CanStartFiring(void *owner, void *slot) {
    WeaponFireState *weaponSlot = (WeaponFireState *)slot;
    WeaponPlayer *player = (WeaponPlayer *)((Player *)owner)->actorParts[0].controller;
    if (weaponSlot->charge > 0.0f || !Player_HasAmmoForMode(player, player->mode)) return 0;
    if ((player->status->flag8F == 1 && g_gameSettings.counters.m_bFragTagOn != 0) || player->recoil > 0.0f || player->busy != 0) return 0;
    switch ((s16)(player->mode - 1)) {
    case 10:
        if (player->flags6AC & 0x4000) return 0;
        break;
    case 17:
        if (player->state788 != 2) return 0;
        break;
    case 8:
        if (weaponSlot->cooldown > 0.0f && weaponSlot->mode == 2) return 0;
        if (player->ammo < 50 && weaponSlot->mode == 2) return 0;
        if (player->ammo < 10) {
            if (weaponSlot->mode == 1) return 0;
        }
        break;
    case 11:
        if (Particle_CountOwnerListOneEffects(&g_actorParticleEffectSystem, player) >= 3) return 0;
        break;
    case 0:
        if (weaponSlot->rounds == 0) return 0;
        break;
    }
    return 1;
}

/* Handles a player's attack trigger: nothing while cooling down past g_weaponTriggerCooldownLimit; the trigger is the
 * controller latch (cleared when read) for a flagged controlled player, else flag 0x2000; when it
 * fires and Weaponai_CanStartFiring accepts the attack, a ranged attack (type 2) that may fire takes action 8 and
 * returns 2, otherwise action 4 starts with the combo byte cleared and returns 1. Adapted from
 * Weaponai_TryEnterAlternateFireState with the fire check as the same static helper. */
/* The weapon actor links to its Player and AiController; attack is its WeaponFireState. */


static inline s32 can_fire_Weaponai_TryRequestFiringState(char *player) {
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
            Gsky_PostTargetedScreenMessage(&g_playerViewRenderContext.object, ((Player *)(player))->camera,
                RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
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
        if (((WeaponFireState *)(attack))->mode == 2 && can_fire_Weaponai_TryRequestFiringState(player)) {
            Actor_RequestActorState(actor, attack, 8);
            return 2;
        }
        Actor_RequestActorState(actor, attack, 4);
        ((WeaponFireState *)(attack))->triggerMode = 0;
        return 1;
    }
    return 0;
}

/* Updates alternate fire, falling back to another weapon when neither mode has
 * ammunition. Reports unavailable modes, preserves the selected action captured
 * on entry, then processes the attack trigger. */
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
            Gsky_PostTargetedScreenMessage(&g_playerViewRenderContext.object, player->camera,
                RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                                             Player_GetPlayerIndex(&g_playerViewRenderContext, player), 1.0f);
        }
    }
    return allowed;
}
void Weaponai_UpdateAlternateFire(void *actor, void *attack) {
    Player *player = (Player *)((LevelActor *)actor)->controller;
    s32 action = g_weaponActionRecords[player->pose].action;
    WeaponInfo *info = (WeaponInfo *)g_weaponInfoByType[player->selectedAction];
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
                                                     RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu,
                                                         g_weaponLockedNoticeTextEuX, g_playerViewRenderContext.game.language),
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


/* The PAL copy of Weapon_UpdateIdleWeaponSelection: the weapon switch and the idle request are two calls here. */
#endif


#if !(defined(VERSION_EU) || defined(VERSION_EU_X))


void Weapon_UpdateIdleWeaponSelection(LevelActor *levelActor, void *weaponFireState) {
    s32 state;
    void *actor;
    CGameStatus *audio;
    s32 mode;

    actor = levelActor->controller;
    state = g_weaponActionRecords[((Player *)actor)->pose].action;
    if ((s8)((Dest *)weaponFireState)->count != 0) {
        if (Player_HasAmmoForMode(actor, ((Player *)actor)->selectedAction) == 0) {
            if (((Dest *)weaponFireState)->fireMode == 2) {
                ((Dest *)weaponFireState)->fireMode = 1;
                if (Player_HasAmmoForMode(actor, ((Player *)actor)->selectedAction) == 0) {
                    ((Player *)actor)->weapon = Weaponai_FindNextUsableWeapon(actor);
                }
            }
        }
    }
    Playerai_EndHeldAlternateFire(actor);
    ((Player *)actor)->idleAnimationState = 0;
    ((WeaponAnimationState *)((Player *)actor)->weaponAnimation)->speed = 0;
    ((Dest *)weaponFireState)->fireCounter = 0;

    audio = &g_gameSettings.counters;
    if ((audio->m_bFragTagOn != 0) &&
        (((Player *)actor)->profile->bonus != 0)) {
        if (((Player *)actor)->actionFlags & 0x2000) {
            mode = audio->m_nFragTagSkin;
            switch (mode) {
            case 0:
                SoundElement_PlaySoundAtPosition(6305,
                              ((Player *)actor)->pos,
                              (s32)&((Player *)actor)->pos, -1);
                break;
            case 1:
                SoundElement_PlaySoundAtPosition(6505,
                              ((Player *)actor)->pos,
                              (s32)&((Player *)actor)->pos, -1);
                break;
            case 2:
                SoundElement_PlaySoundAtPosition(6405,
                              ((Player *)actor)->pos,
                              (s32)&((Player *)actor)->pos, -1);
                break;
            }
        }
    } else if ((state != 1) && (state != 7) &&
               ((s8)((Dest *)weaponFireState)->count != 0)) {
        Weaponai_InitializeSwitchAndRequestIdle(levelActor, weaponFireState);
    }
}
#endif

/* Runs a charge weapon's fire for its holder: picks the holder's next weapon through
   Weaponai_FindNextUsableWeapon when the current one cannot be used; while the fire input 0x4000 is held on a weapon
   that can fire (not stunned, with ammunition, clicking and showing the empty message otherwise) in
   ready state 1, a full charge of at least 50 fires action 5 and enters state 2,
   while a partial charge clicks and shows the not-ready message; otherwise it fires the state's action
   from g_weaponActionRecords unless Weaponai_TryRequestFiringState handles the weapon or the actor has flag 0x400, and when
   Weaponai_TryRequestFiringState handles it the barrel spin grows, drives the model's animation speed
   (capped at 1), returns the weapon to state 1 and sets the spin step. */





static inline s32 can_fire_Weaponai_UpdateSpinAndAlternateFire(char *player) {
    s32 ammo;
    if (((SharedPlayer *)(player))->views5E8.view11D8_147.jumpCooldown > 0.0f) {
        return 0;
    }
    if (((SharedPlayer *)(player))->views1450.view1450_0.computerControlled != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((SharedPlayer *)(player))->views1C.view5D4_45.playerIndex],
        ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                Player_GetPlayerIndex(&g_playerViewRenderContext, player),
                          1.0f);
        }
    }
    return ammo;
}


/* Advances a player's second charging action: when the trigger is released (as in Weaponai_UpdateSpinAndRepeatCue) or the
 * cooldown is past g_weaponAlternateStunLimit, it switches to action 2, runs Playerai_StopPrimaryAttachedSound and
 * Playerai_StopSecondaryAttachedSound, plays sound
 * 0x794 at the player's target or position and pushes the charge by the release amount; otherwise
 * it grows the charge by the charge rate and each time the cue timer runs out adds the cue period
 * back and plays the charge cue (0x3F9 in a multiplayer match without controller, 0x4CB otherwise).
 * Adapted from Weaponai_UpdateSpinAndRepeatCue. */


static inline s32 released_Weaponai_UpdateSpinAndAlternateFire(void *actor, char *player) {
    char *control;
    s32 latch;

    if (((Player *)player)->cooldown > g_weaponAlternateStunLimit) {
        return 1;
    }
    if ((((LevelActor *)actor)->flags & 0x300000) && ((Player *)player)->computer != 0) {
        control = ((Player *)player)->controller;
        latch = ((AiController *)control)->fireRequested;
        ((AiController *)control)->fireRequested = 0;
        return latch == 0;
    }
    if (!(((Player *)player)->inputFlags & 0x2000)) {
        return 1;
    }
    if (((Player *)player)->locked != 0) {
        return 1;
    }
    return Player_HasAmmoForMode(player, ((Player *)player)->selectedAction) == 0;
}

void Weaponai_UpdateSpinAndAlternateFire(Shared_Actor *actor, WeaponFireState *fire) {
    char *player;
    s32 action;
    char *model;
    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
    }
    if ((((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) && can_fire_Weaponai_UpdateSpinAndAlternateFire(player) && fire->mode == 1) {
        if (((SharedPlayer *)(player))->views5E8.chargeView.charge >= 50) {
            Actor_RequestActorState(actor, fire, 5);
            fire->mode = 2;
        } else {
            SoundElement_PlayFlatSound(3405);
            if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
                Gsky_PostTargetedScreenMessage((&((Shared_MenuData *)&g_playerViewRenderContext)->object),
                    ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                    RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX,
                        g_playerViewRenderContext.object.language),
                              Player_GetPlayerIndex(&g_playerViewRenderContext, player), 1.0f);
            }
            fire->mode = 1;
        }
        return;
    }
    if (Weaponai_TryRequestFiringState(actor, fire) == 0) {
        if (!(actor->weaponFlags & 0x400)) {
            Actor_RequestActorState(actor, fire, action);
        }
    } else {
        fire->spin += fire->spin * g_frameElapsedTime * 2.0f;
        model = ((SharedPlayer *)(player))->views5E8.view698_37.emitter;
        if (!(fire->spin < 0.0f ? 1.0f < -fire->spin * 1.7904929f
                                                     : 1.0f < fire->spin * 1.7904929f)) {
            if (fire->spin < 0.0f) {
                ((WeaponAnimationState *)(model))->speed = -fire->spin * 1.7904929f;
            } else {
                ((WeaponAnimationState *)(model))->speed = fire->spin * 1.7904929f;
            }
        } else {
            ((WeaponAnimationState *)(model))->speed = 1.0f;
        }
        fire->spinStep = fire->spin * g_frameElapsedTime * 2.0f;
        fire->mode = 1;
    }
}

void Weaponai_SelectReleasedFireState(struct WeaponActorStateView *actor, void *stateController) {
    s16 weaponMode;
    s32 fireMode;
    void *value;

    value = actor->value;
    if (!(((struct WeaponAlternateFireFlagsView *)(value))->value & 0x2000)) {
        weaponMode = ((struct PlayerWeaponClassView *)(value))->value;
        if (weaponMode != 0) {
            if (weaponMode == 2) {
                fireMode = ((struct WeaponAttackPhaseView *)(stateController))->value;
                if (fireMode == 1) {
                    Actor_RequestActorState(actor, stateController, 5);
                } else if (fireMode == weaponMode) {
                    Actor_RequestActorState(actor, stateController, 9);
                } else {
                    goto check_height;
                }
            } else {
                goto check_state;
            }
        } else {
check_height:
            if (!(((struct WeaponReleasedFireLevelView *)(stateController))->value > g_weaponAlternateFireDelayLimit)) {
                Actor_RequestActorState(actor, stateController, 9);
            } else {
                Actor_RequestActorState(actor, stateController, 5);
            }
        }
        goto done;
check_state:
        if (Playerai_GetWeaponAmmo(value, (s16) weaponMode) == 1) {
            Actor_RequestActorState(actor, stateController, 7);
        } else {
            Actor_RequestActorState(actor, stateController, 5);
        }
done:
        ;
    }
}

void Weaponai_UpdateChargeAndRepeatCue(LevelActor *actor, Dest *attack) {
    char *player;
    CVector3 *position;
    char *target;

    player = actor->controller;
    target = ((Player *)player)->camera;
    if (target != 0) {
        position = &((PlayerCameraTargetView *)target)->position;
    } else {
        position = &((Player *)player)->pos;
    }
    if (released_Weaponai_UpdateSpinAndAlternateFire(actor, player)) {
        Actor_RequestActorState(actor, attack, 2);
        Playerai_StopPrimaryAttachedSound(player);
        Playerai_StopSecondaryAttachedSound(player);
        SoundElement_PlaySoundAtPosition(1940, *position, position, -1);
        Graphu64_EaseValueToward(&attack->charge, (f32)g_weaponEasedSpinSpinTarget * g_weaponAlternateChargeScales[0], 0.4f);
        return;
    }
    Graphu64_EaseValueToward(&attack->charge, (f32)g_weaponEasedSpinSpinTarget * g_weaponAlternateChargeScales[1], 0.4f);
    attack->cueTimer -= g_frameElapsedTime;
    if (attack->cueTimer <= 0.0f) {
        attack->cueTimer += g_weaponAlternateChargeCueInterval;
        if (((Player *)player)->computer == 0 && g_playerWeaponClassMode == 1) {
            Playerai_DispatchWeaponFireEffect(actor->controller, 1017);
        } else {
            Playerai_DispatchWeaponFireEffect(actor->controller, 1227);
        }
    }
}

/* Runs a spinning weapon's barrel for its holder: unless the weapon is in state 4 the spin
   speed decays, the spin angle advances by twice the speed per frame, and the
   holder's model animation speed follows the spin speed, capped at 1; while the fire input
   0x4000 is held and the holder is not stunned, a single player game (g_gameControllerMode) without infinite
   ammunition checks the ammunition through Player_GetProfileAchievementFlag and, when it is empty, clicks
   (sound 0xD4D) and shows the empty message on the holder's view; with ammunition and a loaded
   weapon it plays the wind-up sound 0x7BC unless already firing, sets the firing flags
   0x18400 and restarts the firing timer at 25. Written with the fire check as the static
   helper shared with Weaponai_TryEnterAlternateFireState. */


static inline s32 can_fire_Weaponai_DecaySpinAndActivateEffect(char *player) {
    s32 ammo;
    if (((SharedPlayer *)(player))->views5E8.view11D8_147.jumpCooldown > 0.0f) {
        return 0;
    }
    if (((SharedPlayer *)(player))->views1450.view1450_0.computerControlled != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((SharedPlayer *)(player))->views1C.view5D4_45.playerIndex],
        ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                Player_GetPlayerIndex(&g_playerViewRenderContext, player),
                          1.0f);
        }
    }
    return ammo;
}
void Weaponai_DecaySpinAndActivateEffect(Shared_Actor *actor, WeaponFireState *weapon) {
    char *player;
    char *model;
    player = actor->entity;
    if (weapon->variant != 4) {
        weapon->spin = Graphu64_DecayToZero(weapon->spin, 0.013613569f);
    }
    weapon->spinStep += weapon->spin * g_frameElapsedTime * 2.0f;
    model = ((SharedPlayer *)(player))->views5E8.view698_37.emitter;
    if (!(weapon->spin < 0.0f ? 1.0f < -weapon->spin * 1.7904929f
                                                   : 1.0f < weapon->spin * 1.7904929f)) {
        if (weapon->spin < 0.0f) {
            ((WeaponAnimationState *)(model))->speed = -weapon->spin * 1.7904929f;
        } else {
            ((WeaponAnimationState *)(model))->speed = weapon->spin * 1.7904929f;
        }
    } else {
        ((WeaponAnimationState *)(model))->speed = 1.0f;
    }
    if ((((SharedPlayer *)(player))->views5E8.view6AC_45.inputFlags & 0x4000) && can_fire_Weaponai_DecaySpinAndActivateEffect(player)
            && ((SharedPlayer *)(player))->views5E8.chargeView.charge > 0) {
        if (!(((SharedPlayer *)(player))->views122C.view122C_2.options & 0x18400)) {
            SoundElement_PlayFlatSound(1980);
        }
        ((SharedPlayer *)(player))->views122C.view122C_2.options |= 0x18400;
        ((SharedPlayer *)(player))->fxTime = 25.0f;
    }
}

/* Runs a weapon's two-shot alternate fire for its holder: when the holder cannot use the
   alternate mode of its weapon (Player_HasAmmoForMode) a pending switch is cancelled and, if still
   unusable, the holder picks its next weapon through Weaponai_FindNextUsableWeapon; otherwise, while the
   alternate input 0x4000 is held and the weapon can fire (not stunned, and with ammunition in a single
   player game, clicking and showing the empty message when out), mode 1 with a second shot available
   arms mode 2, clicking and showing the unavailable message and falling back to mode 1 when mode 2
   cannot be used, and any other state resets to mode 1; finally, unless Weaponai_TryRequestFiringState handled the
   weapon or the actor has flag 0x400, it fires through Actor_RequestActorState_Damageai with the holder's state's fire
   mode from g_weaponActionRecords. */


static inline s32 can_fire_Weaponai_ToggleFiringModeWithAmmoCheck(char *player) {
    s32 ammo;
    if (((SharedPlayer *)(player))->views5E8.view11D8_147.jumpCooldown > 0.0f) {
        return 0;
    }
    if (((SharedPlayer *)(player))->views1450.view1450_0.computerControlled != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((SharedPlayer *)(player))->views1C.view5D4_45.playerIndex],
        ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                Player_GetPlayerIndex(&g_playerViewRenderContext, player),
                          1.0f);
        }
    }
    return ammo;
}
void Weaponai_ToggleFiringModeWithAmmoCheck(Shared_Actor *actor, WeaponFireState *fireState) {
    char *player;
    s32 action;
    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        if (fireState->mode != 2) {
            ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
            return;
        }
        fireState->mode = 1;
        if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
            ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
            return;
        }
    }
    if ((((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) && can_fire_Weaponai_ToggleFiringModeWithAmmoCheck(player)) {
        if (fireState->mode == 1 && can_fire_Weaponai_ToggleFiringModeWithAmmoCheck(player)) {
            fireState->mode = 2;
            if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
                SoundElement_PlayFlatSound(3405);
                if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
                    Gsky_PostTargetedScreenMessage((&((Shared_MenuData *)&g_playerViewRenderContext)->object),
                        ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                        RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX,
                            g_playerViewRenderContext.object.language),
                                  Player_GetPlayerIndex(&g_playerViewRenderContext, player), 1.0f);
                }
                fireState->mode = 1;
            }
        } else {
            fireState->mode = 1;
        }
    }
    if (Weaponai_TryRequestFiringState(actor, fireState) == 0 && !(actor->weaponFlags & 0x400)) {
        Actor_RequestActorState(actor, fireState, action);
    }
}

/* Advances a player's charging action: when the trigger is released (controller latch for a controlled
 * player, otherwise flag 0x2000 with no hold and a disallowed action) or the cooldown is past g_weaponChargeCooldownLimit, it
 * switches to action 2, runs Playerai_StopPrimaryAttachedSound and Playerai_StopSecondaryAttachedSound and plays sound 0x978 at the player's target or
 * position; otherwise it grows the charge by the charge rate and, each time the cue timer
 * runs out, restarts it and plays the charge cue (0x3FB in a multiplayer match without controller, 0x4CD
 * otherwise). */




static inline s32 released_Weaponai_UpdateSpinAndRepeatCue(void *actor, Player *player) {
    AiController *control;
    s32 latch;

    if (player->cooldown > g_weaponChargeCooldownLimit) {
        return 1;
    }
    if ((((Shared_Actor *)actor)->weaponFlags & 0x300000) && player->computer != 0) {
        control = player->controller;
        latch = control->fireRequested;
        control->fireRequested = 0;
        return latch == 0;
    }
    if (!(player->inputFlags & 0x2000)) {
        return 1;
    }
    if (player->locked != 0) {
        return 1;
    }
    return Player_HasAmmoForMode(player, player->selectedAction) == 0;
}

void Weaponai_UpdateSpinAndRepeatCue(Shared_Actor *actor, WeaponFireState *attack) {
    Player *player;
    CVector3 *position;
    PlayerCameraTargetView *target;

    player = actor->entity;
    target = player->camera;
    if (target != 0) {
        position = &target->position;
    } else {
        position = &player->pos;
    }
    if (released_Weaponai_UpdateSpinAndRepeatCue(actor, player)) {
        Actor_RequestActorState(actor, attack, 2);
        Playerai_StopPrimaryAttachedSound(player);
        Playerai_StopSecondaryAttachedSound(player);
        SoundElement_PlaySoundAtPosition(2424, *position, (s32)position, -1);
        return;
    }
    Graphu64_EaseValueToward(&attack->spin, (f32)g_weaponChargeSpinTarget * g_weaponChargeSpinScale, 0.4f);
    attack->cueTimer -= g_frameElapsedTime;
    if (attack->cueTimer <= 0.0f) {
        attack->cueTimer = g_weaponChargeCueInterval;
        if (player->computer == 0 && g_playerWeaponClassMode == 1) {
            Playerai_DispatchWeaponFireEffect(actor->entity, 1019);
        } else {
            Playerai_DispatchWeaponFireEffect(actor->entity, 1229);
        }
    }
}


void Weaponai_SettleSpinToThirdTurn(Shared_Actor *actor, WeaponFireState *fireState) {
    f32 spin;
    f32 remainingSpin;
    f32 animationSpin;
    Player *entity;
    void *weaponAnimation;

    entity = (Player *)actor->entity;
    if (fireState->variant != 4) {
        spin = fireState->spin;
        if (spin > 0.0f) {
            fireState->spin = Graphu64_DecayToZero(spin, g_weaponAnimatedFiringSpinDecay);
        } else {
            f32 value = fireState->spinStep;
            f32 period = g_weaponAnimatedFiringSpinPeriod;
            fireState->spin = 0.0f;
            if (period <= value) {
                do {
                    value -= period;
                    fireState->spinStep = value;
                } while (period <= value);
            }
            period = fireState->spinStep;
            if (period < g_weaponSpinEaseToZeroLimit) {
                Graphu64_EaseValueToward(&fireState->spinStep, 0.0f, 0.125f);
            } else if (period < g_weaponSpinEaseToMiddleSectorLimit) {
                Graphu64_EaseValueToward(&fireState->spinStep, 2.0943952f, 0.125f);
            } else if (period < g_weaponSpinEaseToLastSectorLimit) {
                Graphu64_EaseValueToward(&fireState->spinStep, 4.1887903f, 0.125f);
            } else {
                Graphu64_EaseValueToward(&fireState->spinStep, 6.2831855f, 0.125f);
            }
        }
    }
    fireState->spinStep += (fireState->spin * g_frameElapsedTime) * 2.0f;
    remainingSpin = fireState->spin;
    weaponAnimation = entity->weaponAnimation;
    if (!(remainingSpin < 0.0f
              ? g_weaponNegativeSpinSpeedLimit < (-remainingSpin * g_weaponNegativeSpinSpeedScale)
              : g_weaponPositiveSpinSpeedLimit < (remainingSpin * g_weaponPositiveSpinSpeedScale))) {
        animationSpin = fireState->spin;
        if (animationSpin < 0.0f) {
            ((WeaponAnimationState *)weaponAnimation)->speed = (f32) (-animationSpin * g_weaponReverseAnimationSpinScale);
            return;
        }
        ((WeaponAnimationState *)weaponAnimation)->speed = (f32) (animationSpin * g_weaponForwardAnimationSpinScale);
        return;
    }
    ((WeaponAnimationState *)weaponAnimation)->speed = (f32) g_weaponStoppedAnimationSpeed;
}

/* Runs a player's rapid-fire action: when the current action is not allowed a type 2 request drops to type 1
 * and retries once before the idle state is refreshed; a player flagged 0x4000 that may fire with rounds at
 * 0x144 turns a type 1 request into type 2 (reporting the empty weapon and staying type 1 when firing is
 * not allowed) or any other request into type 1, and holds one round; the barrel spin then winds
 * down by 0.5 to 1 while type 1 or up by 0.05 to 2 while type 2 and turns the barrel frame (of
 * 8); finally the default action for the player's state starts unless Weaponai_TryRequestFiringState handled the request
 * or the actor is flagged 0x400. Adapted from Weaponai_TryEnterAlternateFireState with the same static fire check. */


static inline s32 can_fire_Weaponai_UpdateSpinAndRepeatCue(Player *player) {
    s32 ammo;
    if (player->cooldown > 0.0f) {
        return 0;
    }
    if (player->computer != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[player->slot], player->selectedAction);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (player->camera != 0) {
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, player->camera,
                RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                Player_GetPlayerIndex(&g_playerViewRenderContext, player),
                          1.0f);
        }
    }
    return ammo;
}
void Weaponai_UpdateAnimatedFiringMode(Shared_Actor *actor, WeaponFireState *fireState) {
    Player *player;
    s32 action;
    s32 single;
    player = actor->entity;
    action = g_weaponActionRecords[player->pose].action;
    if (Player_HasAmmoForMode(player, player->selectedAction) == 0) {
        if (fireState->mode != 2) {
            goto idle;
        }
        fireState->mode = 1;
        if (Player_HasAmmoForMode(player, player->selectedAction) == 0) {
        idle:
            player->weapon = Weaponai_FindNextUsableWeapon(player);
            return;
        }
    }
    if ((player->actionFlags & 0x4000) && can_fire_Weaponai_UpdateSpinAndRepeatCue(player) && fireState->rounds > 0) {
        single = 1;
        if (fireState->mode == single) {
            fireState->mode = 2;
            if (Player_HasAmmoForMode(player, player->selectedAction) == 0) {
                SoundElement_PlayFlatSound(3405);
                if (player->camera != 0) {
                    Gsky_PostTargetedScreenMessage(&g_playerViewRenderContext.object, player->camera,
                        RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX,
                            g_playerViewRenderContext.object.language),
                                  Player_GetPlayerIndex(&g_playerViewRenderContext, player), 1.0f);
                }
                fireState->mode = single;
                goto spin;
            }
        } else {
            fireState->mode = single;
        }
        fireState->rounds = single;
    }
spin:
    if (fireState->mode == 1) {
        if (player->fireSpin > 1.0f) {
            player->fireSpin -= 0.5f;
        }
        if (player->fireSpin < 1.0f) {
            player->fireSpin = 1.0f;
        }
    } else if (fireState->mode == 2) {
        if (player->fireSpin < 2.0f) {
            player->fireSpin += 0.05f;
        }
        if (player->fireSpin > 2.0f) {
            player->fireSpin = 2.0f;
        }
    }
    player->fireFrame = (player->fireFrame + (s32)player->fireSpin) % 8;
    if (Weaponai_TryRequestFiringState(actor, fireState) == 0 && !(actor->weaponFlags & 0x400)) {
        Actor_RequestActorState(actor, fireState, action);
    }
}

/* Starts a player's secondary action: sets the request type to 1, refreshes the idle state when the current
 * action is not allowed, and when the player is flagged 0x4000, may fire and holds a charge either releases
 * a charged shot (sound 0x42E at the player, action 0xB) once charged past 24 or reports the empty weapon;
 * otherwise the default action for the player's state is started unless Weaponai_TryRequestFiringState handled the request
 * or the actor is flagged 0x400. Adapted from Weaponai_TryEnterAlternateFireState with the same static fire check. */





static inline s32 can_fire_Weaponai_TryEnterAmmoCostState(char *player) {
    s32 ammo;

    if (((SharedPlayer *)(player))->views5E8.view11D8_147.jumpCooldown > 0.0f) {
        return 0;
    }
    if (((SharedPlayer *)(player))->views1450.view1450_0.computerControlled != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((SharedPlayer *)(player))->views1C.view5D4_45.playerIndex],
        ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                Player_GetPlayerIndex(&g_playerViewRenderContext, player),
                          g_ammoCostScreenMessageDuration);
        }
    }
    return ammo;
}

void Weaponai_TryEnterAmmoCostState(Shared_Actor *actor, WeaponFireState *fireState) {
    char *player;
    s32 action;

    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    fireState->mode = 1;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
        return;
    }
    if ((((SharedPlayer *)(player))->views5E8.view6AC_45.inputFlags & 0x4000) && can_fire_Weaponai_TryEnterAmmoCostState(player)
            && ((SharedPlayer *)(player))->views5E4.view5E4_0.health != 0) {
        if (((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[0] >= 25) {
            SoundElement_PlaySoundAtPosition(1070, ((Player *)player)->pos,
                (s32)&((Player *)player)->pos, -1);
            Actor_RequestActorState(actor, fireState, 11);
        } else if (((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) {
            SoundElement_PlayFlatSound(3405);
            if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
                Gsky_PostTargetedScreenMessage(&((Shared_MenuData *)&g_playerViewRenderContext)->object,
                    ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                    RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX,
                        g_playerViewRenderContext.object.language),
                              Player_GetPlayerIndex(&g_playerViewRenderContext, player), g_ammoCostPlayerViewMessageDuration);
            }
        }
        return;
    }
    if (Weaponai_TryRequestFiringState(actor, fireState) == 0 && !(actor->weaponFlags & 0x400)) {
        Actor_RequestActorState(actor, fireState, action);
    }
}

/* Starts a player's action: when the current action is not allowed the idle state is refreshed; a player
 * flagged 0x4000 with no cooldown, no lock and the ammo option enabled checks its weapon's ammo, playing sound
 * 0xD4D and reporting the empty weapon when it is out, and takes action 8 when it may fire; otherwise the
 * default action for the player's state is started unless Weaponai_TryRequestFiringState handled the request or the actor is
 * flagged 0x400. */




static inline s32 can_fire_Weaponai_TryEnterAlternateFireState(char *player) {
    s32 ammo;

    if (((SharedPlayer *)(player))->views5E8.view11D8_147.jumpCooldown > 0.0f) {
        return 0;
    }
    if (((SharedPlayer *)(player))->views1450.view1450_0.computerControlled != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((SharedPlayer *)(player))->views1C.view5D4_45.playerIndex],
        ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
#if defined(VERSION_EU)
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                ((g_weaponLockedNoticeTextEu)[g_languageIndex]), Player_GetPlayerIndex(&g_playerViewRenderContext, player),
#elif defined(VERSION_EU_X)
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                ((g_weaponLockedNoticeTextEuX)[g_languageIndex]), Player_GetPlayerIndex(&g_playerViewRenderContext, player),
#else
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                (g_weaponLockedNoticeText[0]), Player_GetPlayerIndex(&g_playerViewRenderContext, player),
#endif
                          g_alternateFireLockedNoticeDuration);
        }
    }
    return ammo;
}

void Weaponai_TryEnterAlternateFireState(Shared_Actor *actor, void *attack) {
    char *player;
    s32 action;

    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
        return;
    }
    if ((((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) && can_fire_Weaponai_TryEnterAlternateFireState(player)) {
        Actor_RequestActorState(actor, attack, 8);
        return;
    }
    if (Weaponai_TryRequestFiringState(actor, attack) == 0 && !(actor->weaponFlags & 0x400)) {
        Actor_RequestActorState(actor, attack, action);
    }
}

/* Continues a player's secondary action: refreshes the idle state when the current action is not allowed;
 * a player flagged 0x4000 that may fire with a type 1 request takes action 5 and marks the request type 2,
 * unless it is in state 4 with a charge under 48, which reports the empty weapon; otherwise a request
 * Weaponai_TryRequestFiringState handles is marked type 1 and the default action for the player's state is started unless
 * the actor is flagged 0x400. Adapted from Weaponai_TryEnterAlternateFireState with the same static fire check. */





static inline s32 can_fire_Weaponai_TryEnterAlternateAmmoMode(char *player) {
    s32 ammo;

    if (((SharedPlayer *)(player))->views5E8.view11D8_147.jumpCooldown > 0.0f) {
        return 0;
    }
    if (((SharedPlayer *)(player))->views1450.view1450_0.computerControlled != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((SharedPlayer *)(player))->views1C.view5D4_45.playerIndex],
        ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                Player_GetPlayerIndex(&g_playerViewRenderContext, player),
                          g_alternateAmmoScreenMessageDuration);
        }
    }
    return ammo;
}

void Weaponai_TryEnterAlternateAmmoMode(Shared_Actor *actor, WeaponFireState *fireState) {
    char *player;
    s32 action;

    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
    }
    if ((((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) && can_fire_Weaponai_TryEnterAlternateAmmoMode(player) && fireState->mode == 1) {
        if (((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[0] >= 48 || ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon != 4) {
            Actor_RequestActorState(actor, fireState, 5);
            fireState->mode = 2;
            return;
        } else {
            SoundElement_PlayFlatSound(3405);
            if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
                Gsky_PostTargetedScreenMessage(&((Shared_MenuData *)&g_playerViewRenderContext)->object,
                    ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                    RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX,
                        g_playerViewRenderContext.object.language),
                              Player_GetPlayerIndex(&g_playerViewRenderContext, player), g_alternateAmmoPlayerViewMessageDuration);
            }
        }
        return;
    }
    if (Weaponai_TryRequestFiringState(actor, fireState) == 0) {
        if (!(actor->weaponFlags & 0x400)) {
            Actor_RequestActorState(actor, fireState, action);
        }
        return;
    }
    fireState->mode = 1;
}

/* Handles a player's charged secondary action: refreshes the idle state when the action is not allowed and
 * picks the effect position (the weapon's, else the player's); a player flagged 0x4000 that may
 * fire with a type 1 request marks it type 2 and, once charged to 50, plays sound 0xB23 at that position and
 * takes action 5, otherwise reports the empty weapon and restores type 1; any other request Weaponai_TryRequestFiringState
 * handles becomes type 1 with 0x124 cleared, else the state's default action starts unless the actor is
 * flagged 0x400. Adapted from Weaponai_TryEnterAlternateFireState with the same static fire check. */





static inline s32 can_fire_Weaponai_TryEnterChargedAlternateMode(char *player) {
    s32 ammo;

    if (((SharedPlayer *)(player))->views5E8.view11D8_147.jumpCooldown > 0.0f) {
        return 0;
    }
    if (((SharedPlayer *)(player))->views1450.view1450_0.computerControlled != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((SharedPlayer *)(player))->views1C.view5D4_45.playerIndex],
        ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX, g_languageIndex),
                Player_GetPlayerIndex(&g_playerViewRenderContext, player),
                          g_chargedAlternateScreenMessageDuration);
        }
    }
    return ammo;
}

void Weaponai_TryEnterChargedAlternateMode(Shared_Actor *actor, WeaponFireState *fireState) {
    char *player;
    s32 action;
    s32 *pos;
    s32 type;

    player = actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
    }
    if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
        pos = (s32 *)((char *)&((GameplayCamera *)((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera)->position);
    } else {
        pos = (s32 *)&((SharedPlayer *)(player))->views0.view8_2.position;
    }
    if ((((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x4000) && can_fire_Weaponai_TryEnterChargedAlternateMode(player) && (type = fireState->mode) == 1) {
        fireState->mode = 2;
        if (((SharedPlayer *)(player))->views5E8.chargeView.charge >= 50) {
            SoundElement_PlaySoundAtPosition(2851, *(CVector3 *)pos, (s32)pos, (s32)player);
            Actor_RequestActorState(actor, fireState, 5);
        } else {
            SoundElement_PlayFlatSound(3405);
            if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
                Gsky_PostTargetedScreenMessage(&((Shared_MenuData *)&g_playerViewRenderContext)->object,
                    ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                    RW_LOCALIZED_TEXT(g_weaponLockedNoticeText[0], g_weaponLockedNoticeTextEu, g_weaponLockedNoticeTextEuX,
                        g_playerViewRenderContext.object.language),
                              Player_GetPlayerIndex(&g_playerViewRenderContext, player), g_chargedAlternatePlayerViewMessageDuration);
            }
            fireState->mode = type;
        }
        return;
    }
    if (Weaponai_TryRequestFiringState(actor, fireState) == 0) {
        if (!(actor->weaponFlags & 0x400)) {
            Actor_RequestActorState(actor, fireState, action);
        }
        return;
    }
    fireState->mode = 1;
    fireState->spinStep = 0.0f;
}

/* Runs a player's aiming action: refreshes the idle state when the action is not allowed; while the aim
 * flag 0x4000 is held and the weapon may fire (as in Weaponai_TryEnterAlternateFireState) the attack enters aiming and, for scoped
 * weapons, zooms in through Playerai_ToggleForceMarker_WeaponaiUpdateheldfire; when aiming stops it zooms back out unless the zoom was already
 * cancelled; then the default action for the player's state starts unless Weaponai_TryRequestFiringState handled the
 * request or the actor is flagged 0x400. Adapted from Weaponai_TryEnterAlternateFireState with the aiming state.
 */




static inline s32 can_fire_Weaponai_UpdateForceMarkerTrigger(char *player, f32 *scale) {
    s32 ammo;

    if (((SharedPlayer *)(player))->views5E8.view11D8_147.jumpCooldown > 0.0f) {
        return 0;
    }
    if (((SharedPlayer *)(player))->views1450.view1450_0.computerControlled != 0) {
        return 1;
    }
    if (g_gameSettings.controllerMode != 1) {
        return 1;
    }
    ammo = Player_GetProfileAchievementFlag(&g_localPlayerProfiles[((SharedPlayer *)(player))->views1C.view5D4_45.playerIndex],
        ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon);
    if (ammo == 0) {
        SoundElement_PlayFlatSound(3405);
        if (((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera != 0) {
#if defined(VERSION_EU)
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                ((g_weaponLockedNoticeTextEu)[g_languageIndex]), Player_GetPlayerIndex(&g_playerViewRenderContext, player),
#elif defined(VERSION_EU_X)
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                ((g_weaponLockedNoticeTextEuX)[g_languageIndex]), Player_GetPlayerIndex(&g_playerViewRenderContext, player),
#else
            Gsky_PostTargetedScreenMessage(&g_frontendScreenStatus, ((SharedPlayer *)(player))->views5DC.view5DC_0.messageCamera,
                g_weaponLockedNoticeText[0], Player_GetPlayerIndex(&g_playerViewRenderContext, player),
#endif
                          *scale);
        }
    }
    return ammo;
}

void Weaponai_UpdateForceMarkerTrigger(Shared_Actor *actor, WeaponFireState *attack) {
    char *player;
    s32 action;

    player = (char *)actor->entity;
    action = g_weaponActionRecords[((SharedPlayer *)(player))->views5E8.view650_15.actionState].action;
    if (Player_HasAmmoForMode(player, ((SharedPlayer *)(player))->views5E8.view62E_13.selectedWeapon) == 0) {
        ((SharedPlayer *)(player))->views5E8.view770_91.requestedWeapon = Weaponai_FindNextUsableWeapon(player);
    }
    if ((((SharedPlayer *)(player))->views5E8.view6AC_45.inputFlags & 0x4000) && can_fire_Weaponai_UpdateForceMarkerTrigger(player, &k_forceMarkerLockedNoticeScale)) {
        attack->triggered = 1;
        if (((SharedPlayer *)(player))->views5E8.view6B0_46.actionFlags & 0x2000) {

#if defined(VERSION_EU_X)
            Playerai_ToggleForceMarkerEuropean(player, 0);
#else
            Playerai_ToggleForceMarker(player, 0);
#endif

            attack->alternate = 1;
        }
    } else if (attack->triggered != 0) {
        if (attack->alternate == 0) {

#if defined(VERSION_EU_X)
            Playerai_ToggleForceMarkerEuropean(player, 1);
#else
            Playerai_ToggleForceMarker(player, 1);
#endif

        } else {
            attack->alternate = 0;
        }
        attack->triggered = 0;
    }
    if (Weaponai_TryRequestFiringState(actor, attack) == 0 && !(actor->weaponFlags & 0x400)) {
        Actor_RequestActorState(actor, attack, action);
    }
}
/* k_forceMarkerLockedNoticeScale and k_heldFireLockedNoticeScale are the two message-duration floats of this unit's literal pool. */
void Weaponai_UpdateHeldFire(Shared_Actor *actor, WeaponFireState *attack) {
    Player *state;
    s32 finished;
    state = (Player *)actor->entity;
    if (attack->triggerMode != 0) {
        if (state->selectedAction == 4 || state->selectedAction == 14 || state->selectedAction == 15) {
            goto no;
        }
        if (state->selectedAction == 10) {
            if (!(state->inputFlags & 0x4000)) goto no;
            if (state->ammo[2] == 0) goto no;
            goto yes;
        } else if (state->selectedAction == 3) {
            if ((state->inputFlags & 0x6000) != 0x6000) goto no;
            if (state->ammo[0] == 0) goto no;
            if (state->ammo[1] != 0) goto yes;
        no:
            finished = 0;
            goto done;
        yes:
            finished = 1;
        done:;
        } else {
            finished = Weaponai_TryRequestFiringState(actor, attack);
        }
        if (finished != 0) {
            attack->triggerMode = 0;
            attack->queuedAction = -1;
        } else {
            if (state->selectedAction == 5) {
                Playerai_StopSecondaryAttachedSound(state);
                SoundElement_PlaySoundAtPosition(1120, state->pos, &state->pos, -1);
            }
            if (state->selectedAction == 3 && can_fire_Weaponai_UpdateForceMarkerTrigger((char *)state, &k_heldFireLockedNoticeScale) != 0 && state->gear == 2) {
                Actor_RequestActorState(actor, attack, 11);
                Playerai_BeginHeldAlternateFire(state);
            } else {
                Actor_RequestActorState(actor, attack, 2);
            }
        }
        state->controllerMode = 1;
        state->controllerTimer = 0.0f;
    }
}

/** Thin wrapper around Actor_RequestActorState_Damageai. */
void Weaponai_ForwardActorStateRequest(void *actor, void *stateController, s32 action) {
    Actor_RequestActorState(actor, stateController, action);
}

void Weaponai_ApplyWeaponSwitch(void *part, void *body) {
    s16 index;
    u16 unsigned_index;
    void *owner;
    void *state;

    state = ((LevelActor *)part)->controller;
    index = ((Player *)state)->weapon;
    unsigned_index = (u16)((Player *)state)->weapon;
    if ((((Player *)state)->selectedAction != index) || (g_world.mode != 4)) {
        if (Weapon_IsPrimarySwitchGroup(index) != 0) {
            ((Player *)state)->weaponChanged = 1;
        } else if (Weapon_IsSecondarySwitchGroup(index) != 0) {
            ((Player *)state)->secondaryChanged = 1;
        } else if (Weapon_IsSpecialSwitchGroup(index) != 0) {
            ((Player *)state)->specialChanged = 1;
        }
        ((Player *)state)->selectedAction = unsigned_index;
        ((WeaponFireState *)body)->animation = ((WeaponInfo *)g_weaponInfoByType[(s16)unsigned_index])->animation;
        ((WeaponFireState *)body)->animationCount = ((WeaponInfo *)(g_weaponInfoByType[((Player *)state)->selectedAction]))->animationCount;
        owner = ((Player *)state)->camera;
        if ((owner != 0) && ((u32)g_gameLoopFrameCount >= 5U)) {
            Camera_PostScreenMessage(&g_frontendScreenStatus, owner,
                #if defined(VERSION_EU) || defined(VERSION_EU_X)
                (*(void ***)g_weaponInfoByType[((Player *)state)->selectedAction])[g_frontendScreenStatus.settings.language]);
#else
                *(void **)*(void **)g_weaponInfoByType[((Player *)state)->selectedAction]);
#endif
        }
        ((WeaponFireState *)body)->spinStep = 0;
        ((WeaponFireState *)body)->spin = 0;
        ((Shared_Actor *)part)->color = 0;
        ((WeaponFireState *)body)->charge = 0;
    }
}

/* Handles a player's attack trigger: nothing while cooling down past g_weaponTriggerCooldownLimit; the trigger is the
 * controller latch (cleared when read) for a flagged controlled player, else flag 0x2000; when it
 * fires and Weaponai_CanStartFiring accepts the attack, a ranged attack (type 2) that may fire takes action 8 and
 * returns 2, otherwise action 4 starts with the combo byte cleared and returns 1. Adapted from
 * Weaponai_TryEnterAlternateFireState with the fire check as the same static helper. */


/* Updates alternate fire, falling back to another weapon when neither mode has
 * ammunition. Reports unavailable modes, preserves the selected action captured
 * on entry, then processes the attack trigger. */
/* The adjacent exact can_fire supplies the same readiness check; this call site
 * owns its distinct message-duration literal and localized European strings. */

#if defined(VERSION_EU) || defined(VERSION_EU_X)


/* The PAL copy of Weapon_UpdateIdleWeaponSelection: the weapon switch and the idle request are two calls here. */
void Weaponai_UpdateAfterAmmoModeChange(LevelActor *levelActor, void *weaponSlot) {
    s32 state;
    void *actor;
    CGameStatus *audio;
    s32 mode;

    actor = levelActor->controller;
    state = *(s16 *)((char *)g_weaponActionRecords +
                     (((Player *)actor)->pose * sizeof(struct WeaponActionRecord)));
    if ((s8)((Dest *)weaponSlot)->count != 0) {
        if (Player_HasAmmoForMode(actor, ((Player *)actor)->selectedAction) == 0) {
            if (((Dest *)weaponSlot)->fireMode == 2) {
                ((Dest *)weaponSlot)->fireMode = 1;
                if (Player_HasAmmoForMode(actor, ((Player *)actor)->selectedAction) == 0) {
                    ((Player *)actor)->weapon = Weaponai_FindNextUsableWeapon(actor);
                }
            }
        }
    }
    Playerai_EndHeldAlternateFire(actor);
    ((Player *)actor)->idleAnimationState = 0;
    ((WeaponAnimationState *)((Player *)actor)->weaponAnimation)->speed = 0;
    ((Dest *)weaponSlot)->fireCounter = 0;

    audio = &g_gameSettings.counters;
    if ((audio->m_bFragTagOn != 0) &&
        (((Player *)actor)->profile->bonus != 0)) {
        if (((Player *)actor)->actionFlags & 0x2000) {
            mode = audio->m_nFragTagSkin;
            switch (mode) {
            case 0:
                SoundElement_PlaySoundAtPosition(6305,
                              ((Player *)actor)->pos,
                              (s32)&((Player *)actor)->pos, -1);
                break;
            case 1:
                SoundElement_PlaySoundAtPosition(6505,
                              ((Player *)actor)->pos,
                              (s32)&((Player *)actor)->pos, -1);
                break;
            case 2:
                SoundElement_PlaySoundAtPosition(6405,
                              ((Player *)actor)->pos,
                              (s32)&((Player *)actor)->pos, -1);
                break;
            }
        }
    } else if ((state != 1) && (state != 7) &&
               ((s8)((Dest *)weaponSlot)->count != 0)) {
        Weaponai_ApplyWeaponSwitch(levelActor, weaponSlot);
        Actor_RequestActorState(levelActor, weaponSlot, 0);
    }
}
#endif















const s32 g_weaponEasedSpinSpinTarget = 20;

/* Retained data for this translation unit. */

const float g_Weaponai_UpdateCallbacksAndTimersConstantWords[1] = {
    0.25f,
};

const float g_Weaponai_SelectReleasedFireStateConstantWords[1] = {
    3e+01f,
};

const float g_Weaponai_UpdateChargeAndRepeatCueConstantWords[4] = {
    0.1f, 0.017453294f, 0.017453294f, 1.125f,
};

const float g_Weaponai_TryEnterChargedAlternateModeConstantWords[2] = {
    1.0f, 1.0f,
};

const float g_Weaponai_UpdateForceMarkerTriggerConstantWords[1] = {
    1.0f,
};

const float g_Weaponai_UpdateHeldFireConstantWords[1] = {
    1.0f,
};

#if defined(VERSION_DE)
float g_weaponTriggerCooldownLimit = 0.100000001f;
float g_alternateFireMessageDuration = 1.0f;
#endif
