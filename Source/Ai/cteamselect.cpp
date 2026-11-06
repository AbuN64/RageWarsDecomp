#include "Common/gameplay_camera.h"
#include "Common/gameplay_transition.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "include_asm.h"
#include "Menu/teammenu.h"
#include "Common/sharedplayer.h"
#include "Common/math_helpers.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Common/aiprofile.h"
#include "Common/viewflags.h"
#include "Common/shared_gameslot.h"
#include <PR/gbi.h>
#include "Common/vector4f.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/player_record_and_fragtag_views.h"
#include "Common/resourceloadstate.h"
#include "Render/soundelement_playflatsound.h"
#include <platform_sdk.h>
#include <PR/abi.h>
#include "Ai/cteamselect.h"
#include "Common/sessionhandlerrow.h"
#include "Common/triple.h"
#include "Engine/rumble.h"
#include "Game/builddirectionmatrix.h"
#include "Weaponai/weaponai_drawredmarkerquad__weaponai.h"
#include "Graphu64/graphu64_buildlookatmatrix.h"
#include "World/playerai_respawnfragtagplayer.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "onscrn.h"
#include "Cteamselect/cteamselect_drawteamicons.h"
#include "Cteamselect/s_selectteamtext.h"
#include "Onscrn/onscreen_drawscaledmaskedimage.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/menu_match_globals.h"
#include "Engine/Audio/channel.h"
#include "Cteamselect/cteamselect_updateteamchoiceinput.h"
#include "Cteamselect/cteamselect_updateteamwheel.h"
#include "Cteamselect/player_resetplayerforround_data.h"
#include "Ai/Cteamselect/cteamselect_initteamchoices.h"
#include "Cteamselect/cteamselect_drawteamwheel.h"
#include "Data/rest_source_records.h"
#include "Data/Ovl1_d/nav_initvisiblepursuit.h"
#include "Data/Ovl1_d/addrlow_nav_updatevisiblepursuit.h"
#include "Ai/Weapon/weapon.h"
#include "Common/navigation_actor_search_views.h"

void TeamSelect_DrawWeaponIcons(CBarrel *menu, Item *items, s32 count, Player *player) {
    s32 width;
    s32 height;
    f32 fade;
    s32 level;
    f32 scaleX;
    f32 scaleY;
    f32 x;
    f32 y;
    f32 alpha;
    s32 red;
    s16 green;
    s32 blue;
    GameplayCamera *view;
    f32 *viewport;
    Item *item;

    level = g_gameSettings.hudFade + 64;
    fade = menu->m_Alpha * (level < 256 ? level : 255.0f);
    item = items;
    while (--count != -1) {
        view = player->camera;
        scaleX = view->viewWidth * (1.0f / 320.0f);
        scaleY = view->viewHeight * (1.0f / 240.0f);
        viewport = &view->viewWidth;
        x = viewport[2] + viewport[0] * 0.5f + item->position.x * 0.5f * viewport[0];
        y = viewport[3] + viewport[1] * 0.5f + item->position.y * 0.5f * viewport[1];
        alpha = item->width;
        if (item->icon != 0) {
            OnScreen_GetImageDimensions(item->icon, 0, &width, &height);
            if (menu->m_Selected == item->slot) {
                blue = red = Math_Cosf(menu->m_Glow) * 63.0f + 192.0f;
                alpha = 1.0f;
                green = red;
            } else {
                red = Playerai_PlayerHasAmmoForWeapon(player, item->weapon);
                red = red == 0 ? 100 : 200;
                green = red;
                blue = red;
            }
            gDPSetEnvColor(g_displayListCursor++, red, green, blue, (u32)(alpha * fade));
            OnScreen_DrawSpriteResource(item->icon, 0, x - width * item->height * scaleX * 0.5f,
                             y - height * item->height * scaleY * 0.5f,
                             scaleX * item->height, scaleY * item->height, 1);
        }
        item++;
    }
}

/* Lays out a player's weapon menu when it is active: for each of the eight slots holding a
   weapon it eases the slot's scale toward its target (1.3 times larger under the cursor),
   turns an offset raised by the menu's opening by the slot's angle to place it, and lists it with its
   weapon's icon from g_weaponInfoByType (no icon for weapons outside 0 to 21), then passes the list to
   TeamSelect_DrawWeaponIcons. */


void TeamSelect_DrawWeaponWheel(CBarrel *menu, s32 unusedView, s32 viewPlayer) {
    Matrix matrix;
    CVector3 position;
    Item items[36];
    CVector3 offset;
    s32 count;
    s32 i;
    CBarrelWeapon *slot;
    Item *item;
    f32 target;
    f32 size;
    s32 weapon;

    if (menu->m_Mode != 0) {
        offset.x = 0.0f;
        item = items;
        count = 0;
        offset.y = -0.6f - (0.4f - menu->m_Alpha * 0.4f);
        offset.z = 0.0f;
        for (i = 0; i < 8; i++) {
            slot = &menu->m_WeaponList[i];
            if (menu->m_WeaponList[i].m_Weapon != -1) {
                if (i == menu->m_Selected) {
                    target = *(&g_weaponWheelScalePoolPrefix + 1) * 1.3f;
                } else {
                    target = *(&g_weaponWheelScalePoolPrefix + 1);
                }
                size = 1.0f;
                slot->m_Scale = Graphu64_ApproachValue(slot->m_Scale, target, *(&g_weaponWheelScalePoolPrefix + 1) * 0.1f);
                Graphu64_IdentityMatrix(&matrix);
                RollMatrix(&matrix, slot->m_Rot);
                Graphu64_TransformPoint(&matrix, &offset, &position);
                weapon = menu->m_WeaponList[i].m_Weapon;
                if (weapon < 0) {
                    goto no_icon;
                }
                if (weapon >= 22) {
                no_icon:
                    item->icon = item->width = 0;
                    item->slot = i;
                    item->weapon = menu->m_WeaponList[i].m_Weapon;
                    item->position = position;
                } else {
                    item->slot = i;
                    item->weapon = menu->m_WeaponList[i].m_Weapon;
                    item->position = position;
                    item->icon = ((WeaponInfo *)g_weaponInfoByType[weapon])->icon;
                    item->width = size;
                    item->height = size;
                }
                item++;
                count++;
            } else {
                item->icon = item->width = 0;
            }
        }
        TeamSelect_DrawWeaponIcons(menu, items, count, (Player *)viewPlayer);
    }
}

/* Returns which of eight menu directions a player's stick points in: -1 inside a dead zone of radius
   60, a diagonal (1, 3, 5 or 7) when both axes are non-zero and their magnitudes differ by less than 46,
   otherwise 2 or 6 when the horizontal axis dominates and 0 or 4 when the vertical one does, reading
   the stick bytes of the controller. */
s32 TeamSelect_GetEightWayStickSlot(TeamMenuPlayerControllerView *player) {
    ControllerAxesView *controller;
    s8 x;
    s8 y;
    controller = player->controller;
    x = controller->x;
    y = controller->y;
    if (x * x + y * y < 3600) {
        return -1;
    }
    if (RW_ABS(RW_ABS(x) - RW_ABS(y)) < 46 && x != 0 && y != 0) {
        if (x * y > 0) {
            if (x > 0) {
                return 1;
            }
            if (controller->x != 0) {
                return 5;
            }
            return 5;
        }
        return y > 0 ? 7 : 3;
    }
    if (RW_ABS(x) > RW_ABS(y)) {
        return x <= 0 ? 6 : 2;
    }
    if (y > 0) {
        return 0;
    }
    return 4;
}

/* Runs a player's weapon menu each frame: the menu button (0x8000 of the controller) counts
   only while Playerai_IsRoundEndState allows and the controller is not paused through g_resultExitPending, which instead
   closes the menu (state 3), as does holding the button while the value is positive; from a
   closed state holding it clears the pending weapon, rebuilds the menu through TeamSelect_InitWeaponChoices
   and opens it, while releasing it with a weapon pending outside category 8 rebuilds it and marks it
   open; with no category the slot under the cursor from TeamSelect_GetEightWayStickSlot, when it changes, plays sound
   0xD4D for an unowned weapon, forgets an empty slot, moves the cursor and requests the
   slot's weapon unless it is current, switching the slot to the weapon's alternate of
   its g_weaponInfoByType record when the player holds that one and input bit 0x1000 is clear. */

void TeamSelect_UpdateWeaponWheelInput(CBarrel *menu, void *player, s32 selectionContext) {
    s32 held;
    s32 slot;
    s32 category;
    s16 weapon;
    s16 alternate;

    held = ((struct ControllerButtonFlagsView *) ((TeamWeaponSelectionPlayerView *) player)->controller)->buttons & 0x8000;
    if (Playerai_IsRoundEndState(player) != 0) {
        held = 0;
    }
    if (g_gameSettings.counters.m_bFragTagOn != 0
            && ((struct FragTagProfileFlagView *) ((TeamWeaponSelectionPlayerView *) player)->options)->fragTagEnabled == 1) {
        held = 0;
        menu->m_Mode = 3;
    }
    if (held && menu->m_Time > 0.0f) {
        menu->m_Mode = 3;
    }
    if (menu->m_Mode == 0 || menu->m_Mode == 3) {
        if (!held) {
            if (((TeamWeaponSelectionPlayerView *)(player))->pendingWeapon != -1 && menu->m_DisplaySlot != 8) {
                TeamSelect_InitWeaponChoices(menu, 0, player);
                menu->m_Mode = 1;
            }
            return;
        }
        ((TeamWeaponSelectionPlayerView *)(player))->pendingWeapon = -1;
        TeamSelect_InitWeaponChoices(menu, held, player);
        ((TeamWeaponSelectionPlayerView *)(player))->locked = 1;
        menu->m_Mode = 1;
    }
    category = menu->m_DisplaySlot;
    if (category != -1) {
        return;
    }
    slot = TeamSelect_GetEightWayStickSlot(player);
    if (slot == menu->m_WheelIndexLastFrame) {
        return;
    }
    if (slot != category) {
        weapon = menu->m_WeaponList[slot].m_Weapon;
        if (menu->m_WeaponList[slot].m_bEnabled == 0) {
            SoundElement_PlayFlatSound(3405);
            return;
        }
        if (weapon < 0) {
            menu->m_WheelIndexLastFrame = category;
            return;
        }
        if (slot != menu->m_Selected) {
            menu->m_Selected = slot;
        }
        if (weapon == ((TeamWeaponSelectionPlayerView *)(player))->selectedWeapon) {
            menu->m_WheelIndexLastFrame = slot;
            return;
        }
        ((TeamWeaponSelectionPlayerView *)(player))->requestedWeapon = weapon;
        if (!(((TeamWeaponSelectionPlayerView *)(player))->flags & 0x1000)) {
            alternate = ((WeaponInfo *)(g_weaponInfoByType[weapon]))->alternate;
            if (alternate != category && ((Player *)player)->weaponSlots[alternate].owned != 0) {
                menu->m_WeaponList[slot].m_Weapon = alternate;
            }
        }
    }
    menu->m_WheelIndexLastFrame = slot;
}


/* Advances a player's weapon wheel one frame: reads the wheel input unless the player is in a locked state,
   opens it (mode 1) while its progress rises to 1, keeps it open (mode 2) until TeamSelect_TryCloseWeaponWheel allows
   closing, and fades it out (mode 3), spinning the wheel while it is shown. */
void TeamSelect_UpdateDraftPanel(CBarrel *wheel, Player *player, s32 selectionContext)
{
    if ((u32)(player->state - 17) < 2) return;
    if (((SharedPlayer *)player)->views5E8.viewCCC_164.teamWheel) return;
    if (player->cooldown > 0.0f) return;
    if (Cinema_IsSequenceActive()) return;
    wheel->m_QuickSelect = player->profile->weaponWheelMode == 1;
    if (player->state == 14) {
        if (!player->actorParts[1].animationMarker) return;
        if (((struct ControllerProfile *)player->weaponAnimation)->buttons & 0x8000) player->weapon = Weapon_PickRandomArmedWeapon(player);
    } else if ((((struct ControllerProfile *)player->weaponAnimation)->history[0] & 0x8000) && player->profile->weaponWheelMode) {
        player->weapon = Weaponai_NextAvailableWeapon(player);
    } else if (player->profile->weaponWheelMode != 1 || (player->pendingWeapon != -1 && wheel->m_DisplaySlot != 8)) {
        TeamSelect_UpdateWeaponWheelInput(wheel, player, selectionContext);
    }
    if (player->weapon != player->selectedAction) {
        if (player->deathCount) {
            Rumble_SetEffectOwnerSlot((s32)player->deathCount, 0);
            player->deathCount = 0;
        }
        player->weaponDraftHold = 0; player->fireFrame = -1;
    }
    switch (wheel->m_Mode) {
    case 1:
        wheel->m_Alpha += g_frameElapsedTime * 1.25f;
        if (wheel->m_DisplaySlot != -1) wheel->m_Time = 16.0f;
        else wheel->m_Time = 0.0f;
        if (wheel->m_Alpha >= 1.0f) {
            wheel->m_Mode = 2; wheel->m_Alpha = 1.0f;
            if (wheel->m_DisplaySlot != -1) wheel->m_DisplaySlot = 8;
        }
        break;
    case 2:
        if (!TeamSelect_TryCloseWeaponWheel(wheel, player)) break;
        wheel->m_DisplaySlot = -1; player->locked = 0; wheel->m_Mode = 3;
    case 3:
        wheel->m_Alpha -= g_frameElapsedTime * 0.25f;
        if (wheel->m_Alpha <= 0.0f) { wheel->m_Alpha = 0.0f; wheel->m_Mode = 0; }
        break;
    }
    if (wheel->m_Mode) wheel->m_Glow += g_frameElapsedTime * (RW_PI_F6 / 6);
    else player->locked = 0;
}

/* CPlayer_t as the weapon barrel reads it (debug catalog): m_Data (CPlayerLoadSaveData_t at 0x5E0) holds per weapon
   index whether the player holds it and its barrel slot (m_WeaponList, CWeapon_t at 0x602), then m_CurrentWeapon. */
typedef struct CWeapon_t {
    s8 m_bHolding;
    s8 m_nWeaponSlot;
} CWeapon;
struct TeamWeaponPlayer {
    u8 pad0[((char *)&((Player *)0)->weaponSlots - (char *)0)];
    CWeapon m_WeaponList[22];
    s16 m_CurrentWeapon;
};
extern f32 g_weaponWheelInitialSlotScale;
/* Fills the first eight weapons of the barrel: a slot shows the weapon the player put in it when m_DisplaySlot
   allows that slot (-1 every slot, 3, 7 or 4 only that slot, else that slot and the next), with its g_weaponInfoByType
   record, whether the player has ammo for it and a rotation of 45 degrees per slot, and m_Selected lands on the
   current weapon; any other slot is empty (-1). */
void TeamSelect_InitWeaponChoices(CBarrel *barrel, s32 buttonAWheel, Player *player) {
    s32 choice;
    s32 weapon;
    s32 displaySlot;
    s32 accepted;
    barrel->m_UnderwaterWhenSetup = 0;
    barrel->m_ButtonAWheel = buttonAWheel;
    barrel->m_Selected = -1;
    choice = 0;
    do {
        for (weapon = 0; weapon < 22; weapon++) {
            if (choice == player->weaponSlots[weapon].action) break;
        }
        if (weapon >= 22) {
            barrel->m_WeaponList[choice].m_Weapon = -1;
            barrel->m_WeaponList[choice].m_bEnabled = 0;
        } else {
            displaySlot = barrel->m_DisplaySlot;
            if (displaySlot == -1) accepted = 1;
            else if (displaySlot == 3 || displaySlot == 7) accepted = choice == displaySlot;
            else if (displaySlot == 4) accepted = choice == 4;
            else {
                accepted = 0;
                if (choice == displaySlot || choice == displaySlot + 1) accepted = 1;
            }
            if (!accepted) {
                barrel->m_WeaponList[choice].m_Weapon = -1;
                barrel->m_WeaponList[choice].m_bEnabled = 0;
            } else {
                barrel->m_WeaponList[choice].m_Weapon = weapon;
                if (player->selectedAction == weapon) barrel->m_Selected = choice;
                barrel->m_WeaponList[choice].m_pInfo = g_weaponInfoByType[weapon];
                if (Playerai_PlayerHasAmmoForWeapon(player, weapon) != 0) barrel->m_WeaponList[choice].m_bEnabled = 1;
                else barrel->m_WeaponList[choice].m_bEnabled = 0;
                barrel->m_WeaponList[choice].m_Spin = 0.0f;
                barrel->m_WeaponList[choice].m_Scale = g_weaponWheelInitialSlotScale;
                barrel->m_WeaponList[choice].m_Rot = (f32)choice * 0.785398245f;
            }
        }
        choice++;
    } while (choice < 8);
    barrel->m_QuickSelect = 1;
}

/** Reset the weapon menu: closed, no cursor or hover, and its thirty-six slots fanned 30 degrees apart. */
void TeamSelect_ResetWeaponWheel(CBarrel *menu) {
    s32 i;

    menu->m_Mode = 0;
    menu->m_Time = 0;
    menu->m_Alpha = 0;
    menu->m_Rot = 0;
    menu->m_Glow = 0;
    menu->m_Selected = -1;
    menu->m_QuickSelect = 1;
    menu->m_DisplaySlot = -1;
    menu->CurrentWeaponListSize = 0;
    menu->m_UnderwaterWhenSetup = 0;
    menu->m_WheelIndexLastFrame = -1;
    for (i = 0; i < 36; i++) {
        menu->m_WeaponList[i].m_Rot = -(i * g_weaponWheelResetAngleStep);
        menu->m_WeaponList[i].m_Spin = 0;
        menu->m_WeaponList[i].m_Scale = g_weaponWheelInitialSlotScale;
    }
}

void TeamSelect_DrawWeaponWheelSprites(s32 menu, s32 unusedView, s32 player) {
    Gfx *cmd;

    Onscrn_SetupSpriteMode(0xFF);
    gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
    TeamSelect_DrawWeaponWheel((CBarrel *)menu, unusedView, player);
}

/** Preserve the empty hook. */
void TeamSelect_EmptyWeaponWheelHook(void *weaponWheelState) {
}

/* Counts the wheel's close delay down; once it has elapsed and the wheel button is released, clears the
   closed index and reports that the wheel may close. */
s32 TeamSelect_TryCloseWeaponWheel(CBarrel *wheel, Player *player) {
    f32 closeDelay;

    closeDelay = ((ResetTimerStorage *)(wheel))->closeDelay;
    if (closeDelay > 0.0f) {
        ((ResetTimerStorage *)(wheel))->closeDelay = closeDelay - g_frameElapsedTime;
        return 0;
    }
    if (((ResetFlagsStorage *)((((ResetOwnerStorage *)(player))->controller)))->buttons & 0x8000) {
        return 0;
    }
    ((ResetTimerStorage *)(wheel))->selectedIndex = -1;
    return 1;
}

f32 CTeamSelect_ComputeDirectedAngleStep(f32 currentAngle, f32 targetAngle, s32 turnDirection, f32 approachRate) {
    f32 angleStep;
    f32 stepMagnitude;
    f32 angleDifference;

    Graphu64_WrapPeriodicValue(&currentAngle);
    Graphu64_WrapPeriodicValue(&targetAngle);
    if (turnDirection > 0) {
        if (targetAngle < currentAngle) {
            targetAngle += g_weaponWheelPositiveAnglePeriod;
        }
    } else if (targetAngle > currentAngle) {
        targetAngle -= g_weaponWheelNegativeAnglePeriod;
    }
    angleDifference = targetAngle - currentAngle;
    angleStep = angleDifference * approachRate * g_frameElapsedTime;
    stepMagnitude = angleStep;
    if (angleStep < 0.0f) {
        stepMagnitude = -angleStep;
    }
    if (angleDifference < 0.0f) {
        if (-angleDifference < stepMagnitude) {
            goto clamp;
        }
    } else if (angleDifference < stepMagnitude) {
clamp:
        angleStep = angleDifference;
    }
    return angleStep;
}






#if defined(VERSION_EU_X)
extern unsigned int k_cteamselectFragment[2];
#endif

#if defined(VERSION_EU)
extern unsigned int k_cteamselectFragment[2];
#endif

#if defined(VERSION_DE)
unsigned int k_CteamselectData[2] = {
    0x65616D00, 0x437F0000,
};
#endif

 /* "Select Team" */


void Cteamselect_DrawTeamIcons(struct TeamMenu *menu, TeamMenuIconView *items, s32 count, SharedPlayer *player) {
    s32 width;
    s32 height;
    f32 fade;
    s32 level;
    f32 scaleX;
    f32 scaleY;
    f32 x;
    f32 y;
    f32 alpha;
    s32 red;
    s32 green;
    s32 blue;
    GameplayCamera *view;
    GameplayCamera *titleView;
    f32 *viewport;
    TeamMenuIconView *item;

    titleView = (GameplayCamera *)player->views5DC.view5DC_1.view;
    level = g_gameSettings.hudFade + 64;
    fade = menu->open * (level < 256 ? level : 255.0f);
    item = items;
    while (--count != -1) {
        view = (GameplayCamera *)player->views5DC.view5DC_1.view;
        scaleX = view->viewWidth * (1.0f / 320.0f);
        scaleY = view->viewHeight * (1.0f / 240.0f);
        viewport = &view->viewWidth;
        x = viewport[2] + viewport[0] * 0.5f + item->position.x * 0.5f * viewport[0];
        y = viewport[3] + viewport[1] * 0.5f + item->position.y * 0.5f * viewport[1];
        alpha = item->width;
        if (item->icon != 0) {
            OnScreen_GetImageDimensions(item->icon, 0, &width, &height);
            if (menu->cursor == item->slot) {
                red = Math_Cosf(menu->spin) * 63.0f + 192.0f;
                alpha = 1.0f;
                green = red;
                blue = red;
            } else {
                red = 150;
                green = red;
                blue = red;
                alpha *= 0.75f;
            }
            gDPSetEnvColor(g_displayListCursor++, red, green, blue, alpha * fade);
            OnScreen_DrawSpriteResource(item->icon, 0, x - width * item->height * scaleX * 0.5f,
                          y - height * item->height * scaleY * 0.5f,
                          scaleX * item->height, scaleY * item->height, 1);
        }
        item++;
    }
    scaleY = titleView->viewHeight / g_hudReferenceViewportHeight;
    scaleX = titleView->viewWidth / g_hudReferenceViewportWidth;
    OnScreen_SetupTextRendering();
    OnScreen_SetTextScale(0.6f, 0.6f);
    OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
    x = viewport[2] + viewport[0] * 0.5f;
    y = viewport[3] + viewport[1] * 0.5f;
    Onscrn_DrawText(s_selectTeamText, x, y, 200, 1, 1, scaleX, scaleY);
}

/* Returns the cardinal team-menu slot, or -1 inside the deadzone/diagonals. */
s32 Cteamselect_GetFourWayStickSlot(void *object) {
    StickPlayer *player = object;
    StickInput *input = player->input;
    s8 x = input->x;
    s8 y = input->y;
    if (x*x + y*y < 3600) return -1;
    if (((f32)(((f32)x < 0.0f ? -x : x) - ((f32)y < 0.0f ? -y : y)) < 0.0f ? -(((f32)x < 0.0f ? -x : x) - ((f32)y < 0.0f ? -y : y))
        : (((f32)x < 0.0f ? -x : x) - ((f32)y < 0.0f ? -y : y))) < 46
            && x && y) goto diagonal;

    if (((f32)x < 0.0f ? -x : x) > ((f32)y < 0.0f ? -y : y)) { s32 r = 1; if (x <= 0) r = 3; return r; }
    return (y <= 0) << 1;

diagonal:
    return -1;
}

/* Runs a player's team selection menu each frame unless a menu is paused (Cinema_IsSequenceActive): while the
   game is ending (g_matchEndingTeamWheelClose) an open menu is closed through TeamSelect_CloseTeamWheel; a closed menu opens through
   Cteamselect_InitTeamChoices when team selection g_teamScoringEnabled is on and the player has no team yet (0xFF of its
   controls); while it is open the player is held (0x11B4, 0x11B8) and shielded for 2, and the team slot
   under the stick (Cteamselect_GetFourWayStickSlot) becomes the hovered entry, moving the cursor and
   choosing the entry's team for the player unless the entry is disabled or flagged 0x8000; the menu
   then slides open at 0.25 per frame, and once Cteamselect_TryConfirmTeamChoice confirms a choice it releases the player,
   announces the chosen team with its message and sound, and slides closed, the menu's spin
   turning while it is shown. */




void Cteamselect_UpdateTeamWheel(TeamMenu *menu, SharedPlayer *player, void *selectionContext) {
    s32 held;
    s32 slot;
    Entry *entry;
    u16 team;

    if (Cinema_IsSequenceActive() != 0) {
        return;
    }
    if (g_matchEndingTeamWheelClose.head != 0 && menu->state != 0) {
        TeamSelect_CloseTeamWheel(menu);
        return;
    }
    held = player->views5E8.view698_35.controller->rawButtons & 0x8000;
    if (menu->state == 0 || menu->state == 3) {
        if (g_gameSettings.counters.teams == 0 || player->views5D8.view5D8_1.record->team != 0xFF) {
            goto run;
        }
        Cteamselect_InitTeamChoices((Shared_MenuItemList *)menu, held, player);
        menu->state = 1;
    }
    player->views5E8.view11B4_136.locked = 1;
    player->views5E8.view11B8_138.frozen = 1;
    player->views5E8.view670_31.shield = 2.0f;
    slot = Cteamselect_GetFourWayStickSlot(player);
    if (slot != menu->hover) {
        if (slot != -1) {
            entry = (Entry *) ((char *) menu + slot * sizeof(TeamMenuSlotView));
            team = entry->team;
            if (entry->enabled == 0) {
                goto run;
            }
            if ((s16) team < 0) {
                menu->hover = -1;
                goto run;
            }
            if (slot != menu->cursor) {
                menu->cursor = slot;
            }
            player->views5D8.view5D8_1.record->team = team;
        }
        menu->hover = slot;
    }
run:
    switch (menu->state) {
    case 1:
        menu->open += g_frameElapsedTime * 0.25f;
        if (1.0f <= menu->open) {
            menu->open = 1.0f;
            menu->state = 2;
        }
        break;
    case 2:
        if (Cteamselect_TryConfirmTeamChoice(menu, player) == 0) {
            break;
        }
        menu->state = 3;
        player->views5E8.view11B4_136.locked = 0;
        player->views5E8.view11B8_138.frozen = 0;
        switch (player->views5D8.view5D8_1.record->team) {
        case 0:
#ifdef VERSION_EU
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view,
                g_teamSelectedNoticesEu[0][g_frontendScreenStatus.settings.language]);
#elif defined(VERSION_EU_X)
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view,
                g_teamSelectedNoticesEuX[0][g_frontendScreenStatus.settings.language]);
#else
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_teamSelectedNotice[0]);
#endif
            SoundElement_PlayFlatSound(742);
            break;
        case 1:
#ifdef VERSION_EU
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view,
                g_teamSelectedNoticesEu[1][g_frontendScreenStatus.settings.language]);
#elif defined(VERSION_EU_X)
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view,
                g_teamSelectedNoticesEuX[1][g_frontendScreenStatus.settings.language]);
#else
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_teamSelectedNotice[1]);
#endif
            SoundElement_PlayFlatSound(740);
            break;
        case 2:
#ifdef VERSION_EU
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view,
                g_teamSelectedNoticesEu[2][g_frontendScreenStatus.settings.language]);
#elif defined(VERSION_EU_X)
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view,
                g_teamSelectedNoticesEuX[2][g_frontendScreenStatus.settings.language]);
#else
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_teamSelectedNotice[2]);
#endif
            SoundElement_PlayFlatSound(744);
            break;
        case 3:
#ifdef VERSION_EU
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view,
                g_teamSelectedNoticesEu[3][g_frontendScreenStatus.settings.language]);
#elif defined(VERSION_EU_X)
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view,
                g_teamSelectedNoticesEuX[3][g_frontendScreenStatus.settings.language]);
#else
            Camera_PostScreenMessage(&g_frontendScreenStatus, player->views5DC.view5DC_1.view, g_teamSelectedNotice[3]);
#endif
            SoundElement_PlayFlatSound(748);
            break;
        }
        /* fall through */
    case 3:
        menu->open -= g_frameElapsedTime * 0.25f;
        if (menu->open <= 0.0f) {
            menu->open = 0.0f;
            menu->state = 0;
        }
        break;
    }
    if (menu->state != 0) {
        menu->spin += g_frameElapsedTime * 0.52359885f;
    }
}

/** Reset the team menu: closed, no cursor or hover, and its four team slots fanned 30 degrees apart. */
void TeamSelect_ResetTeamWheel(TeamMenu *menu) {
    s32 i;

    menu->state = 0;
    menu->subState = 0;
    menu->open = 0;
    menu->reset = 0;
    menu->spin = 0;
    menu->cursor = -1;
    menu->count = 4;
    menu->hover = -1;
    for (i = 0; i < 4; i++) {
        menu->slots[i].angle = -(i * g_teamWheelResetAngleStep);
        menu->slots[i].angleVelocity = 0;
        menu->slots[i].scale = g_teamWheelInitialSlotScale;
    }
}


void TeamSelect_DrawTeamWheelSprites(s32 menu, s32 viewContext, s32 player) {
    Gfx *cmd;

    Onscrn_SetupSpriteMode(0xFF);
    gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
    Cteamselect_DrawTeamWheel(menu, viewContext, player);
}

/** Reset a record and mark its word as invalid. */
void TeamSelect_CloseTeamWheel(void *record) {
    TeamMenu *menu = record;
    menu->state = 0;
    menu->subState = 0;
    menu->cursor = -1;
    menu->open = 0;
}

/* Lays out the four team choices around the open menu and draws their icons. */


void Cteamselect_DrawTeamWheel(MenuCteamselectDrawTeamWheel *menu, s32 viewContext, void *player) {
    Matrix matrix;
    CVector3 position;
    TeamMenuIconView items[4];
    CVector3 offset;
    s32 i;
    TeamMenuSlotView *slot;
    TeamMenuIconView *item;
    f32 target;

    if (menu->active != 0) {
        offset.x = 0.0f;
        item = items;
        offset.y = -0.6f - (0.4f - menu->open * 0.4f);
        offset.z = 0.0f;
        for (i = 0; i < 4; i++) {
            slot = &menu->slots[i];
            if (i == menu->cursor) {
                target = *(&g_teamWheelScalePoolPrefix + 1) * 1.3f;
            } else {
                target = *(&g_teamWheelScalePoolPrefix + 1);
            }
            slot->scale = Graphu64_ApproachValue(slot->scale, target, *(&g_teamWheelScalePoolPrefix + 1) * 0.1f);
            Graphu64_IdentityMatrix(&matrix);
            RollMatrix(&matrix, slot->angle);
            Graphu64_TransformPoint(&matrix, &offset, &position);
            item->slot = i;
            item->position = position;
            item->icon = i + 3100;
            item->width = 1.0f;
            item->height = 1.0f;
            item++;
        }
        Cteamselect_DrawTeamIcons(menu, items, 4, player);
    }
}

void Cteamselect_InitTeamChoices(Shared_MenuItemList *list, s32 heldButtons, void *player) {
    s32 i;
    f32 scale = g_teamWheelChoiceScale;
    f32 value = g_teamWheelInitialSlotScale;

    list->selection = -1;
    for (i = 0; i < 4; i++) {
        list->records[i].index = i;
        list->records[i].enabled = 1;
        list->records[i].image = 0;
        list->records[i].value = value;
        list->records[i].angle = i * scale;
    }
}

s32 Cteamselect_TryConfirmTeamChoice(void *menu, void *player) {
    if (((((struct ControllerButtonFlagsView *) (((struct TeamMenuPlayerLinksView *) player)->controller))->buttons) & 0x8000)
            && ((((struct Record *) (((struct TeamMenuPlayerLinksView *) player)->options))->team) != 0xFF)) {
        (((struct Object6C *) menu)->value) = -1;
        return 1;
    }
    return 0;
}
void Cteamselect_UpdateTeamChoiceInput(char *menu, void *player) {
    s32 flags;
    s32 state;
    s32 result;
    s32 value;
    char *entry;
    flags = ((struct ControllerButtonFlagsView *) ((TeamWeaponRuntimePlayerView *) player)->controller)->buttons & 0x8000;
    state = *(s32 *)menu;
    if ((state == 0) || (state == 3)) {
        if ((g_gameSettings.counters.teams != 0) &&
            (((struct Record *) ((TeamWeaponRuntimePlayerView *) player)->options)->team == 0xFF)) {
            Cteamselect_InitTeamChoices((void *)menu, flags, player);
            *(s32 *)menu = 1;
        } else {
            return;
        }
    }
    ((TeamWeaponRuntimePlayerView *)(player))->shieldDuration = g_teamWheelPlayerShieldDuration;
    ((TeamWeaponRuntimePlayerView *)(player))->locked = 1;
    ((TeamWeaponRuntimePlayerView *)(player))->lockState = 1;
    result = Cteamselect_GetFourWayStickSlot(player);
    if (result != ((TeamMenuSelectionPairView *)(menu))->hover) {
        if (result != -1) {
            entry = (char *)menu + result * sizeof(TeamMenuSlotView);
            value = ((Entry *)(entry))->team;
            if (((Entry *)(entry))->enabled != 0) {
                if ((s16)value < 0) {
                    ((TeamMenuSelectionPairView *)(menu))->hover = -1;
                    return;
                }
                if (result != ((TeamMenuSelectionPairView *)(menu))->cursor) {
                    ((TeamMenuSelectionPairView *)(menu))->cursor = result;
                }
                ((struct Record *) ((TeamWeaponRuntimePlayerView *) player)->options)->team = value;
            } else {
                return;
            }
        }
        ((TeamMenuSelectionPairView *)(menu))->hover = result;
    }
}

extern const char s_selectTeamText[12];







#if defined(VERSION_EU_X)

#endif

#if defined(VERSION_EU)

#endif

#if defined(VERSION_DE)

#endif

#if defined(VERSION_EU)
extern DecodeEncodedWordsBlock1Layout k_decodeFragment;
#endif

#if defined(VERSION_EU)
float g_sceneEffectTuningEu[4] = {
    0.09f, 0.05f, 0.5f, 64.0f,
};
#endif

#if defined(VERSION_EU_X)
extern float k_SceneLoadlevelresourcesFractions[4];
#endif

#if defined(VERSION_US)
PlayerControllerStateAndTuningWordsUsLayout g_playerControllerStateAndTuningWordsUs = {
    { 0, 0, 1, 2200, 0, 0 },
    "quR\000",
    { 15073792, 65536, 327680, 262144, 786432, 524288, 655360, 131072, 196608 },
    { 3e+01f, 48.0f, 1.3e+02f }
};
#endif



#if defined(VERSION_US)

#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
f32 g_teamSelectFloatLimits[2] = {
    1.0f, 2.14748365e+09f
};
#endif
#endif

/* Retained data for this translation unit. */

const float g_weaponWheelResetAngleStepBits[1] = {
    0.17453295f,
};

const float g_weaponWheelAnglePeriodBits[2] = {
    6.283186f, 6.283186f,
};

const float g_teamWheelResetAngleStep_StorageWords[1] = {
    1.5707965f,
};

const float g_teamWheelChoiceScale_StorageWords[1] = {
    1.5707965f,
};

const float g_teamWheelPlayerShieldDuration_StorageWords[1] = {
    2.0f,
};
#if defined(VERSION_EU_X)
const unsigned int k_CteamselectUpdateteamchoiceinputQuarterWords[1] = {
    0x3E800000,
};
#endif
#if defined(VERSION_EU)
const unsigned int k_cteamselectUpdateteamchoiceinputFragment[1] = {
    0x2529FFF0,
};
#endif
#if defined(VERSION_DE)
const unsigned int k_CteamselectUpdateteamchoiceinputData[1] = {
    0xBF350481,
};
#endif

const char s_selectTeamText[12] = "Select Team";
