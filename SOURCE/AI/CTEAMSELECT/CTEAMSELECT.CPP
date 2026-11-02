#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "include_asm.h"
#include "MENU/TEAMMENU.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MATH_HELPERS.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include <PR/gbi.h>
#include "COMMON/VECTOR4F.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/PLAYER_RECORD_AND_FRAGTAG_VIEWS.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include <ultra64.h>
#include <PR/abi.h>
#include "AI/CTEAMSELECT.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/TRIPLE.H"

extern s32 Playerai_PlayerHasAmmoForWeapon(void *, s32);

/* 80217388_4.CPP */
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
    RacerViewport *view;
    f32 *viewport;
    Item *item;

    level = g_gameSettings.hudFade + 64;
    fade = menu->m_Alpha * (level < 256 ? level : 255.0f);
    item = items;
    while (--count != -1) {
        view = player->camera;
        scaleX = view->viewportWidth * (1.0f / 320.0f);
        scaleY = view->viewportHeight * (1.0f / 240.0f);
        viewport = &view->viewportWidth;
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

/* Lays out a player's weapon menu when it is active: for each of the eight slots at 0x1C holding a
   weapon it eases the slot's scale toward its target (1.3 times larger under the cursor at 0x37C),
   turns an offset raised by the menu's opening by the slot's angle to place it, and lists it with its
   weapon's icon from g_weaponInfoByType (no icon for weapons outside 0 to 21), then passes the list to
   TeamSelect_DrawWeaponIcons. */

extern f32 Graphu64_ApproachValue(f32, f32, f32);

extern void Graphu64_IdentityMatrix(Matrix *);

extern void RollMatrix(Matrix *, f32);

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
                    item->icon = ((ResourceShortIdView *)g_weaponInfoByType[weapon])->resourceId;
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
   the stick bytes at 0xC6 and 0xC7 of the controller at 0x698. */
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

/* 80217388_6.CPP */
/* Runs a player's weapon menu each frame: the menu button (0x8000 of the controller at 0x698) counts
   only while Playerai_IsRoundEndState allows and the controller is not paused through g_resultExitPending, which instead
   closes the menu (state 3), as does holding the button while the value at 0x4 is positive; from a
   closed state holding it clears the pending weapon at 0xCC0, rebuilds the menu through TeamSelect_InitWeaponChoices
   and opens it, while releasing it with a weapon pending outside category 8 rebuilds it and marks it
   open; with no category the slot under the cursor from TeamSelect_GetEightWayStickSlot, when it changes, plays sound
   0xD4D for an unowned weapon, forgets an empty slot, moves the cursor at 0x37C and requests the
   slot's weapon at 0x770 unless it is current, switching the slot to the weapon's alternate at 0xC of
   its g_weaponInfoByType record when the player holds that one and input bit 0x1000 is clear. */

void TeamSelect_UpdateWeaponWheelInput(s32 *menu, void *player, s32 unused2) {
    s32 held;
    s32 slot;
    s32 category;
    Entry34 *entry;
    s16 weapon;
    s16 alternate;
    char *ammo;

    held = ((struct ControllerButtonFlagsView *) ((TeamWeaponSelectionPlayerView *) player)->controller)->buttons & 0x8000;
    if (Playerai_IsRoundEndState(player) != 0) {
        held = 0;
    }
    if (g_gameSettings.counters.m_bFragTagOn != 0 && ((struct FragTagProfileFlagView *) ((TeamWeaponSelectionPlayerView *) player)->options)->fragTagEnabled == 1) {
        held = 0;
        menu[0] = 3;
    }
    if (held && ((struct PaddedFloatView *) menu)->value > 0.0f) {
        menu[0] = 3;
    }
    if (menu[0] == 0 || menu[0] == 3) {
        if (!held) {
            if (((TeamWeaponSelectionPlayerView *)(player))->pendingWeapon != -1 && ((CBarrel *)menu)->m_DisplaySlot != 8) {
                TeamSelect_InitWeaponChoices((CBarrel *)menu, 0, player);
                menu[0] = 1;
            }
            return;
        }
        ((TeamWeaponSelectionPlayerView *)(player))->pendingWeapon = -1;
        TeamSelect_InitWeaponChoices((CBarrel *)menu, held, player);
        ((TeamWeaponSelectionPlayerView *)(player))->locked = 1;
        menu[0] = 1;
    }
    category = ((CBarrel *)menu)->m_DisplaySlot;
    if (category != -1) {
        return;
    }
    slot = TeamSelect_GetEightWayStickSlot(player);
    if (slot == ((CBarrel *)menu)->m_WheelIndexLastFrame) {
        return;
    }
    if (slot != category) {
        entry = (Entry34 *)&((Block24 *)menu)[slot];
        weapon = entry->weapon;
        if (entry->owned == 0) {
            SoundElement_PlayFlatSound(3405);
            return;
        }
        if (weapon < 0) {
            ((CBarrel *)menu)->m_WheelIndexLastFrame = category;
            return;
        }
        if (slot != ((CBarrel *)menu)->m_Selected) {
            ((CBarrel *)menu)->m_Selected = slot;
        }
        if (weapon == ((TeamWeaponSelectionPlayerView *)(player))->selectedWeapon) {
            ((CBarrel *)menu)->m_WheelIndexLastFrame = slot;
            return;
        }
        ((TeamWeaponSelectionPlayerView *)(player))->requestedWeapon = weapon;
        if (!(((TeamWeaponSelectionPlayerView *)(player))->flags & 0x1000)) {
            alternate = ((WeaponInfo *)(g_weaponInfoByType[weapon]))->alternate;
            if (alternate != category && (ammo = (char *) player + alternate * 2)[((char *)&((Shared_ActorView *)0)->actions - (char *)0)] != 0) {
                entry->weapon = alternate;
            }
        }
    }
    ((CBarrel *)menu)->m_WheelIndexLastFrame = slot;
}

typedef struct DraftConfig17F4C { u8 pad[0x82]; u8 mode; } DraftConfig17F4C;
typedef struct DraftInput17F4C { u8 pad[0xB0]; u32 pressed; u8 padB4[4]; u32 held; } DraftInput17F4C;
typedef struct DraftPlayer17F4C {
    u8 pad[0x48C]; s8 enabled; u8 pad48D[0x5D8 - 0x48D];
    DraftConfig17F4C *config; void *ui; s32 type;
    u8 pad5E4[0x62E - 0x5E4]; s16 oldChoice; u8 pad630[0x698 - 0x630];
    DraftInput17F4C *input; u8 pad69C[0x770 - 0x69C]; s16 choice;
    u8 pad772[0xCC0 - 0x772]; s32 selection; u8 padCC4[8]; s32 blocked;
    u8 padCD0[0x11B0 - 0xCD0]; void *effect; s32 active;
    u8 pad11B8[0x20]; f32 delay; u8 pad11DC[0x14]; s32 word11F0;
    u8 pad11F4[4]; s32 word11F8;
} DraftPlayer17F4C;
typedef struct WeaponWheelDraftState {
    s32 state; f32 value, timer; u8 padC[8]; f32 angle;
    u8 pad18[0x380 - 0x18]; s32 mode; u8 pad384[4]; s32 selection;
} WeaponWheelDraftState;

s16 Weaponai_NextAvailableWeapon(void *);
s32 Rumble_SetEffectOwnerSlot(s32, s32);
void TeamSelect_UpdateDraftPanel(WeaponWheelDraftState *state, DraftPlayer17F4C *player, s32 unused2)
{
    if ((u32)(player->type - 17) < 2) return;
    if (player->blocked) return;
    if (player->delay > 0.0f) return;
    if (Cinema_IsSequenceActive()) return;
    state->mode = player->config->mode == 1;
    if (player->type == 14) {
        if (!player->enabled) return;
        if (player->input->pressed & 0x8000) player->choice = Weapon_PickRandomArmedWeapon(player);
    } else if ((player->input->held & 0x8000) && player->config->mode) {
        player->choice = Weaponai_NextAvailableWeapon(player);
    } else if (player->config->mode != 1 || (player->selection != -1 && state->selection != 8)) {
        TeamSelect_UpdateWeaponWheelInput(&state->state, player, unused2);
    }
    if (player->choice != player->oldChoice) {
        if (player->effect) {
            Rumble_SetEffectOwnerSlot((s32)player->effect, 0);
            player->effect = 0;
        }
        player->word11F0 = 0; player->word11F8 = -1;
    }
    switch (state->state) {
    case 1:
        state->timer += g_frameElapsedTime * 1.25f;
        if (state->selection != -1) state->value = 16.0f;
        else state->value = 0.0f;
        if (state->timer >= 1.0f) {
            state->state = 2; state->timer = 1.0f;
            if (state->selection != -1) state->selection = 8;
        }
        break;
    case 2:
        if (!TeamSelect_TryCloseWeaponWheel(state, player)) break;
        state->selection = -1; player->active = 0; state->state = 3;
    case 3:
        state->timer -= g_frameElapsedTime * 0.25f;
        if (state->timer <= 0.0f) { state->timer = 0.0f; state->state = 0; }
        break;
    }
    if (state->state) state->angle += g_frameElapsedTime * (RW_PI_F6 / 6);
    else player->active = 0;
}

/* CPlayer_t as the weapon barrel reads it (debug catalog): m_Data (CPlayerLoadSaveData_t at 0x5E0) holds per weapon
   index whether the player holds it and its barrel slot (m_WeaponList, CWeapon_t at 0x602), then m_CurrentWeapon. */
typedef struct CWeapon_t {
    s8 m_bHolding;
    s8 m_nWeaponSlot;
} CWeapon;
struct TeamWeaponPlayer {
    u8 pad0[((char *)&((Shared_ActorView *)0)->actions - (char *)0)];
    CWeapon m_WeaponList[22];
    s16 m_CurrentWeapon;
};
extern f32 g_weaponWheelInitialSlotScale;
/* Fills the first eight weapons of the barrel: a slot shows the weapon the player put in it when m_DisplaySlot
   allows that slot (-1 every slot, 3, 7 or 4 only that slot, else that slot and the next), with its g_weaponInfoByType
   record, whether the player has ammo for it and a rotation of 45 degrees per slot, and m_Selected lands on the
   current weapon; any other slot is empty (-1). */
void TeamSelect_InitWeaponChoices(CBarrel *barrel, s32 buttonAWheel, TeamWeaponPlayer *player) {
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
            if (choice == player->m_WeaponList[weapon].m_nWeaponSlot) break;
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
                if (player->m_CurrentWeapon == weapon) barrel->m_Selected = choice;
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

/* 80217388_7.CPP */
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

/** Preserve the empty hook at VRAM 0x80218464. */
void TeamSelect_EmptyWeaponWheelHook(void) {
}

s32 TeamSelect_TryCloseWeaponWheel(void *resetTimerStorage, void *resetOwnerStorage) {
    f32 closeDelay;

    closeDelay = ((ResetTimerStorage *)(resetTimerStorage))->closeDelay;
    if (closeDelay > 0.0f) {
        ((ResetTimerStorage *)(resetTimerStorage))->closeDelay = closeDelay - g_frameElapsedTime;
        return 0;
    }
    if (((ResetFlagsStorage *)((((ResetOwnerStorage *)(resetOwnerStorage))->controller)))->buttons & 0x8000) {
        return 0;
    }
    ((ResetTimerStorage *)(resetTimerStorage))->selectedIndex = -1;
    return 1;
}

f32 CTeamSelect_ComputeDirectedAngleStep(f32 currentAngle, f32 targetAngle, s32 turnDirection, f32 approachRate) {
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;

    Graphu64_WrapPeriodicValue(&currentAngle);
    Graphu64_WrapPeriodicValue(&targetAngle);
    if (turnDirection > 0) {
        if (targetAngle < currentAngle) {
            targetAngle += g_weaponWheelPositiveAnglePeriod;
        }
    } else if (targetAngle > currentAngle) {
        targetAngle -= g_weaponWheelNegativeAnglePeriod;
    }
    f3 = targetAngle - currentAngle;
    f1 = f3 * approachRate * g_frameElapsedTime;
    f2 = f1;
    if (f1 < 0.0f) {
        f2 = -f1;
    }
    if (f3 < 0.0f) {
        if (-f3 < f2) {
            goto clamp;
        }
    } else if (f3 < f2) {
clamp:
        f1 = f3;
    }
    return f1;
}

/* 800C7338.CPP */

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_CteamselectEmptyPoolBlock.c */
#endif

/* 800C733C.CPP */
/* ROM-grounded data: src/g_weaponWheelResetAngleStepBits_Cteamselect.c */
const float g_weaponWheelResetAngleStepBits[1] = {
    0.17453295f,
};

/* 800C7340.CPP */
/* ROM-grounded data: src/g_weaponWheelAnglePeriodBits_Cteamselect.c */
const float g_weaponWheelAnglePeriodBits[2] = {
    6.283186f, 6.283186f,
};

#if defined(VERSION_EU_X)
unsigned int k_CteamselectEncodedWordsBlock2[2] = {
    0x3D0EFA36, 0x3F800000,
};
#endif

#if defined(VERSION_EU)
unsigned int k_CteamselectEncodedWordsBlock1[2] = {
    0x00000000, 0x2129FFFF,
};
#endif

#if defined(VERSION_DE)
unsigned int k_CteamselectEncodedWords[2] = {
    0x65616D00, 0x437F0000,
};
#endif
