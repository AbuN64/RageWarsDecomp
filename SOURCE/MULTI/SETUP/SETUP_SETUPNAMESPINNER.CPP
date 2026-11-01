#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MENURECAT20V1.H"
#include "TYPES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "MULTI/SETUP_SETUPNAMESPINNER.H"
#if defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_EU_X)
extern char g_playerViewRenderContext[];
extern Spinner g_multiplayerNameEntryStates[];
extern s32 Player_GetPlayerIndex(char *, s32);
#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
extern u8 *g_defaultPlayerNameOne;
#endif
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/EFFECTRENDER.H"
#endif
/* Highlights the name slot Player_GetPlayerIndexDe finds for the menu (display flags 0x1800000 on its model part,
   cleared on the other three), resets that spinner's timer and copies the slot's name (trailing blanks
   dropped, none when it starts like the default name) into the spinner; value and max = its length. */
void Setup_SetupNameSpinner(NameSpinnerMenu *menu) {
    s32 index;
    s32 trailing;
    s32 i;
    u8 *source;
    u8 *defaultName;
    u8 *name;
    char *destination;
    u8 defaultChar;
    s32 remaining;
    s32 nameChar;
    index = Player_GetPlayerIndex(g_playerViewRenderContext, menu->id);
    switch (index) {
        default:
        case 0:
            menu->model->part[0].flags |= 0x1800000;
            menu->model->part[1].flags &= ~0x1800000;
            menu->model->part[2].flags &= ~0x1800000;
            menu->model->part[3].flags &= ~0x1800000;
            break;
        case 1:
            menu->model->part[1].flags |= 0x1800000;
            menu->model->part[0].flags &= ~0x1800000;
            menu->model->part[2].flags &= ~0x1800000;
            menu->model->part[3].flags &= ~0x1800000;
            break;
        case 2:
            menu->model->part[2].flags |= 0x1800000;
            menu->model->part[0].flags &= ~0x1800000;
            menu->model->part[1].flags &= ~0x1800000;
            menu->model->part[3].flags &= ~0x1800000;
            break;
        case 3:
            menu->model->part[3].flags |= 0x1800000;
            menu->model->part[0].flags &= ~0x1800000;
            menu->model->part[1].flags &= ~0x1800000;
            menu->model->part[2].flags &= ~0x1800000;
            break;
    }
    g_multiplayerNameEntryStates[index].timer = 0;
    destination = g_multiplayerNameEntryStates[index].name;
    source = g_gameSettings.playerSettings[index].name;
    i = 8;
    trailing = 0;
    while (i > 0) {
        i--;
        if (source[i] != ' ') {
            break;
        }
        trailing++;
    }
    name = source;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    defaultName = g_playerPartnerSuffixByLanguage[g_languageIndex];
#else
    defaultName = g_defaultPlayerNameOne;
#endif
    remaining = 6;
    do {
        nameChar = *name++;
        defaultChar = *defaultName++;
        remaining--;
        if ((u8)nameChar != defaultChar || (u8)nameChar == 0) {
            break;
        }
    } while (remaining == 0);
    /* The ROM loops only while the count is 0, so this compares the first character. */
    if (nameChar == defaultChar) {
        trailing = 8;
    }
    for (i = 0; i < 8 - trailing; i++) {
        *destination++ = *source++;
    }
    *destination = 0;
    g_multiplayerNameEntryStates[index].value = 8 - trailing;
    g_multiplayerNameEntryStates[index].max = 8 - trailing;
}
#endif
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
/* Steps a menu spinner for the entry Player_GetPlayerIndexDe finds in g_playerViewRenderContext: advances its repeat timer by g_frameElapsedTime, wrapping at g_multiplayerNameEntryTimingLimits, and while the menu is active (state 1) decrements its value above zero when Control_IsLeftPressed reports the decrease input, or else increments it below its maximum when Control_IsRightPressed reports the increase input, restarting the timer on a change. Returns zero. */
extern char g_playerViewRenderContext[];
extern Spinner g_multiplayerNameEntryStates[];
extern s32 Player_GetPlayerIndex(char *, s32);
s32 Setup_UpdateNameCursor(void *unused, NameSpinnerMenu *menu) {
    s32 i;
    f32 t;

    i = Player_GetPlayerIndex(g_playerViewRenderContext, menu->id);
    t = g_multiplayerNameEntryStates[i].timer + g_frameElapsedTime;
    g_multiplayerNameEntryStates[i].timer = t;
    if (t >= (15.0f)) {
        g_multiplayerNameEntryStates[i].timer = t - (15.0f);
    }
    if (menu->state == 1) {
        if (((s32 (*)(s32))Control_IsLeftPressed)(menu->input) != 0 && g_multiplayerNameEntryStates[i].value > 0) {
            g_multiplayerNameEntryStates[i].value--;
            g_multiplayerNameEntryStates[i].timer = 0.0f;
        } else if (((s32 (*)(s32))Control_IsRightPressed)(menu->input) != 0) {
            if (g_multiplayerNameEntryStates[i].value < g_multiplayerNameEntryStates[i].max) {
                g_multiplayerNameEntryStates[i].value++;
                g_multiplayerNameEntryStates[i].timer = 0.0f;
            }
        }
    }
    return 0;
}
#endif
#if defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Setup_UpdateNameCursor(void *unused, NameSpinnerMenu *menu) {
    s32 i;
    f32 t;

    i = Player_GetPlayerIndex(g_playerViewRenderContext, menu->id);
    t = g_multiplayerNameEntryStates[i].timer + g_frameElapsedTime;
    g_multiplayerNameEntryStates[i].timer = t;
    if (t >= g_multiplayerNameEntryTimingLimits) {
        g_multiplayerNameEntryStates[i].timer = t - g_multiplayerNameEntryTimingLimits;
    }
    if (menu->state == 1) {
        if (((s32 (*)(s32))Control_IsLeftPressed)(menu->input) != 0 && g_multiplayerNameEntryStates[i].value > 0) {
            g_multiplayerNameEntryStates[i].value--;
            g_multiplayerNameEntryStates[i].timer = 0;
        } else if (((s32 (*)(s32))Control_IsRightPressed)(menu->input) != 0) {
            if (g_multiplayerNameEntryStates[i].value < g_multiplayerNameEntryStates[i].max) {
                g_multiplayerNameEntryStates[i].value++;
                g_multiplayerNameEntryStates[i].timer = 0;
            }
        }
    }
    return 0;
}
#endif
