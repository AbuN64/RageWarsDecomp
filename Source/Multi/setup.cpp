#include "Ui/ui_address_symbols.h"
#include "include_asm.h"
#include "Ovlgame/ovlgame_address_symbols.h"
#include "Common/shared_gameslot.h"
#include "Common/pak_enter_player_options.h"
#include "types.h"
#include "Common/weapon_screen_message_operations.h"
#include "Multi/setup_setupnamespinner.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Multi/multi_address_symbols.h"
#include "Setup/setup_name_cursor_constant_words.h"
#include <platform_sdk.h>
#include "Multi/setup_comparebytesequence.h"
#include "Common/vector4f.h"
#include "Common/font_style_and_glyph_operations.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Pak/menu_createmenufromparameters.h"
#include "Pak/menu_drawanimatedmenusprite.h"
#include "Common/shared_optionsscreen.h"
#include "Common/gameplay_settings.h"
#include "Common/aiprofile.h"
#include "Common/rendercounters.h"
#include "Multi/setup_hasactivegamecounters.h"
#include "Game/game.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "data_overlay_sn_records.h"
#include "Common/packed_callback.h"
#include "Data/Ovltbl/items_copylocalizedplayernamesuffix.h"

#if defined(VERSION_DE)

/* Highlights the name slot Player_GetPlayerIndexDe finds for the menu (display flags 0x1800000 on its model part,
   cleared on the other three), resets that spinner's timer and copies the slot's name (trailing blanks
   dropped, none when it starts like the default name) into the spinner; value and max = its length. */
void Setup_LoadNameEditBuffer(NameSpinnerMenu *menu) {
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
    index = Player_GetPlayerIndex(&g_playerViewRenderContext, menu->id);
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
    destination = g_multiplayerNameEntryStates[index].text;
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
    defaultName = g_defaultPlayerNames[0];
    remaining = 6;
    do {
        nameChar = *name++;
        defaultChar = *defaultName++;
        remaining--;
        if ((u8)nameChar != defaultChar || (u8)nameChar == 0) {
            break;
        }
    } while (remaining == 0);
    /* The loop runs only while the count is zero, so it compares the first character. */
    if (nameChar == defaultChar) {
        trailing = 8;
    }
    for (i = 0; i < 8 - trailing; i++) {
        *destination++ = *source++;
    }
    *destination = 0;
    g_multiplayerNameEntryStates[index].value = 8 - trailing;
    g_multiplayerNameEntryStates[index].count = 8 - trailing;
}
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_EU_X)

#include "Common/Lone/g_languageindex.h"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Common/effectrender.h"
#include "Multi/multi_address_symbols.h"
#include "Menu/menu_item_views.h"
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
    index = Player_GetPlayerIndex(&g_playerViewRenderContext, menu->id);
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
    destination = g_multiplayerNameEntryStates[index].text;
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
    defaultName = g_defaultPlayerNames[0];
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
    /* The loop runs only while the count is zero, so it compares the first character. */
    if (nameChar == defaultChar) {
        trailing = 8;
    }
    for (i = 0; i < 8 - trailing; i++) {
        *destination++ = *source++;
    }
    *destination = 0;
    g_multiplayerNameEntryStates[index].value = 8 - trailing;
    g_multiplayerNameEntryStates[index].count = 8 - trailing;
}
#endif
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
/* Steps a menu spinner for the entry Player_GetPlayerIndexDe finds in g_playerViewRenderContext: advances its repeat timer by g_frameElapsedTime, wrapping at g_multiplayerNameEntryTimingLimits, and while the menu is active (state 1) decrements its value above zero when Control_IsLeftPressed reports the decrease input, or else increments it below its maximum when Control_IsRightPressed reports the increase input, restarting the timer on a change. Returns zero. */

s32 Setup_UpdateNameCursor(void *owner, NameSpinnerMenu *menu) {
    s32 i;
    f32 t;

    i = Player_GetPlayerIndex(&g_playerViewRenderContext, menu->id);
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
            if (g_multiplayerNameEntryStates[i].value < g_multiplayerNameEntryStates[i].count) {
                g_multiplayerNameEntryStates[i].value++;
                g_multiplayerNameEntryStates[i].timer = 0.0f;
            }
        }
    }
    return 0;
}
#endif
#if defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Setup_UpdateNameCursor(void *owner, NameSpinnerMenu *menu) {
    s32 i;
    f32 t;

    i = Player_GetPlayerIndex(&g_playerViewRenderContext, menu->id);
    t = g_multiplayerNameEntryStates[i].timer + g_frameElapsedTime;
    g_multiplayerNameEntryStates[i].timer = t;
    if (t >= (*(float *)&g_multiplayerNameEntryTimingLimits)) {
        g_multiplayerNameEntryStates[i].timer = t - (*(float *)&g_multiplayerNameEntryTimingLimits);
    }
    if (menu->state == 1) {
        if (((s32 (*)(s32))Control_IsLeftPressed)(menu->input) != 0 && g_multiplayerNameEntryStates[i].value > 0) {
            g_multiplayerNameEntryStates[i].value--;
            g_multiplayerNameEntryStates[i].timer = 0;
        } else if (((s32 (*)(s32))Control_IsRightPressed)(menu->input) != 0) {
            if (g_multiplayerNameEntryStates[i].value < g_multiplayerNameEntryStates[i].count) {
                g_multiplayerNameEntryStates[i].value++;
                g_multiplayerNameEntryStates[i].timer = 0;
            }
        }
    }
    return 0;
}
#endif

/* Append one selected character to an eight-character entry buffer. */
s32 Setup_AppendNameCharacter(TextEntryBufferView *textEntry, MenuRules *menuRules) {
 s32 value; s32 count; s32 index=Player_GetPlayerIndex(&g_playerViewRenderContext,menuRules->locked);
 g_multiplayerNameEntryStates[index].timer=0;
 if(g_multiplayerNameEntryStates[index].count == 8) return 0;
 {
 g_multiplayerNameEntryStates[index].text[g_multiplayerNameEntryStates[index].value]=
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
     **textEntry->textBuffer;
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
     *textEntry->textBuffer[g_playerViewRenderContext.object.language];
#endif
 value=g_multiplayerNameEntryStates[index].value+1;
 count=g_multiplayerNameEntryStates[index].count+1;
 g_multiplayerNameEntryStates[index].value=value;
 g_multiplayerNameEntryStates[index].count=count;
 g_multiplayerNameEntryStates[index].text[count]=0;
 }
 return 0;
}

/* Compares two strings byte by byte and returns whether the last pair compared is equal. It stops
   at the first difference or terminator, and keeps going only while the count, decremented once
   per byte, is exactly zero, so a count of one compares a single byte. */
s32 Setup_CompareByteSequence(u8 *a, u8 *b, s32 count) {
    u8 c;
    u8 d;

    do {
        c = *a++;
        d = *b++;
        count--;
    } while (c == d && c != 0 && count == 0);
    return c == d;
}

/* Draws a menu spinner: during the first half of its blink period (the timer of its g_multiplayerNameEntryStates entry up to the float after g_multiplayerNameEntryTimingLimits) it fills a two-pixel white bar under the digit its value selects, placed from the item's x at 0x14 by the character width Menu_GetWidgetStyle_EncodedDrawtextentrycursor reports scaled to the screen, with the style's alpha at 0x30 and 0x34, through OnScreen_SetupFillMode and OnScreen_DrawBevelBox; then draws the item through Menu_DrawLocalizedMenuItemText. */


void Setup_DrawNameCursor(void *menu, MenuLocalizedTextItemView *item, void *third, StyleMultiDrawNameCursor *style) {
    s32 i;
    f32 width;
    f32 alpha;
    s32 x;
    unsigned int bits;

    i = Player_GetPlayerIndex(&g_playerViewRenderContext, style->id);
    if (g_multiplayerNameEntryStates[i].timer <= *(&(*(float *)&g_multiplayerNameEntryTimingLimits) + 1)) {
        width = ((struct PaddedFloatView *)Menu_GetWidgetStyle((struct MenuItemFlagsView *)menu))->value * (f32)g_hudReferenceViewportWidth * g_multiplayerNameCursorWidthScale;
        x = (f32)item->x + (f32)g_multiplayerNameEntryStates[i].value * width;
        g_multiplayerItemRenderState = -1;
        alpha = style->alpha * (style->fade * (64.0f));
        OnScreen_SetupFillMode();
        OnScreen_DrawBevelBox(x, item->y - 2, (f32)x + width, item->y, 0, 0, 0xFF, 0xFF, 0xFF,
                      (u8)(bits = !((2147483648.0f) <= alpha) ? (s32)alpha : (bits = (s32)(alpha - (2147483648.0f))) | 0x80000000U));
    }
    Menu_DrawLocalizedMenuItemText(menu, item, third, style);
}

/* Deletes the final character of the selected player's text entry: resets its cursor and, when the entry holds characters, decrements the count and length and clears the character at the new end. */


/* Copies a player label with spaces for empty characters and refreshes the entry. */

/* Returns 1 when any of the words at 0x28, 0x1C or 0x20 of g_matchRoundCounters is nonzero, else 0. */
s32 Setup_DeleteNameCharacter(s32 owner, NameEditMenuContext *menuEntry) {
    s32 i;
    s32 count;

    i = Player_GetPlayerIndex(&g_playerViewRenderContext, menuEntry->profileOwner);
    count = g_multiplayerNameEntryStates[i].count;
    g_multiplayerNameEntryStates[i].timer = 0;
    if (count == 0) {
        return 0;
    }
    g_multiplayerNameEntryStates[i].count = count - 1;
    g_multiplayerNameEntryStates[i].value--;
    g_multiplayerNameEntryStates[i].text[g_multiplayerNameEntryStates[i].value] = 0;
    return 0;
}

s32 Setup_CommitPlayerName(s32 first, NameEditMenuContext *second, s32 third) {
    s32 playerIndexResult;
    s32 characterIndex;
    s32 nonemptyCharacters;
    u8 *sourceName;
    u8 *destinationName;
    u8 character;
    Player *player;

    player = second->profileOwner;
    playerIndexResult = Player_GetPlayerIndex(&g_playerViewRenderContext, player);
    sourceName = (playerIndexResult * sizeof(SavedPlayerName)) + g_multiplayerSavedPlayerNames;
    destinationName = (u8 *)((Shared_MenuData *)&g_playerViewRenderContext)->game.playerSettings[playerIndexResult].name;
    nonemptyCharacters = 0;
    characterIndex = 0;
    do {
        character = *sourceName;
        sourceName += 1;
        if (character == 0) {
            character = 32;
        } else {
            nonemptyCharacters += 1;
        }
        *destinationName = character;
        characterIndex += 1;
        destinationName += 1;
    } while (characterIndex < 8);
    *destinationName = 0;
    if (nonemptyCharacters == 0) {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
Items_CopyDefaultLocalizedPlayerName
#else
Items_SetDefaultPlayerName
#endif
(player->profile);
    }
    Menu_TryCreateMenu(first, second, third);
    return 1;
}

s32 Setup_HasActiveGameCounters(void) {
    CGameStatus *s = &g_gameSettings.counters;
    s32 ret;

    ret = 0;
    if (s->round != 0 || s->elapsed != 0 || s->state != 0) {
        ret = 1;
    }
    return ret;
}

#if defined(VERSION_US) || defined(VERSION_US_REV1)
const float g_multiplayerNameEntryTimingLimits = 15.0f;
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
const float g_multiplayerNameCursorTuning[2] = {
    6.0f, 0.0035211267f,
};
#endif

#if defined(VERSION_DE) || defined(VERSION_US)
#ifdef VERSION_DE
extern unsigned int k_LibsnEnumeratememoryrangesEncodedWords[1055];
#endif
#if defined(VERSION_DE)
extern unsigned int g_libsnHostMemoryRanges_LibsnEnumeratememoryrangesData[3];
#endif
#endif

#if defined(VERSION_DE) || defined(VERSION_US)
#ifdef VERSION_DE
unsigned int k_itemsCopylocalizedplayernamesuffixFragment[8] = {
    0x00435988, 0x00000E0A, 0x00000013, 0x0042F768, 0x00000E08, 0x00000013, 0x0042F8DC, 0x00000E06,
};
unsigned int k_ItemsCopylocalizedplayernamesuffixEncodedWords[124] = {
    0x00000013, 0x0042EF10, 0x00000E03, 0x00000013, 0x00435990, 0x00000002, 0x00000013, 0x00432118,
    0x00000001, 0x00000013, 0x00430698, 0x0000000A, 0x00000013, 0x0042FB08, 0x0000000B, 0x00000013,
    (unsigned int)Frontend_DestroyPakProfileScreen_Address, 0x00000005, 0x00000013, 0x004303B8, 0x00000006, 0x00000013, 0x004300D8, 0x00000008,
    0x00000013, 0x0042FF00, 0x00000007, 0x00000013, 0x0042FFE8, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000E07, 0x00000001, (unsigned int)Frontend_DestroyPauseMenu_Address, 0x00000E08, 0x00000001,
    0x00435C28, 0x00000E0A, 0x00000001, 0x00435C20, 0x00000E06, 0x00000001, 0x00435AF4, 0x00000E03,
    0x00000001, 0x00435BC0, 0x00000001, 0x00000001, 0x00435C98, 0x00000002, 0x00000001, 0x00435C78,
    0x0000000A, 0x00000001, 0x00435C30, 0x00000000, 0x00000000, 0x00000000, 0x00000E07, 0x0000001F,
    0x00435EB4, 0x00000E08, 0x0000001F, 0x00435FDC, 0x00000E0A, 0x0000001F, 0x00435ED4, 0x00000E06,
    0x0000001F, 0x00435DE0, 0x00000E03, 0x0000001F, 0x00435E7C, 0x00000001, 0x0000001F, 0x00436004,
    0x00000002, 0x0000001F, 0x00435FE4, 0x00000000, 0x00000000, 0x00000000, 0x00000E07, 0x00000020,
    0x00436248, 0x00000E08, 0x00000020, 0x00436354, 0x00000E0A, 0x00000020, 0x00436268, 0x00000E06,
    0x00000020, 0x0043617C, 0x00000E03, 0x00000020, 0x00436210, 0x00000001, 0x00000020, 0x0043637C,
    0x00000002, 0x00000020, 0x0043635C, 0x00000000, 0x00000000, 0x00000000, 0xB25DCFB1, 0xB34020C4,
    0x00000000, 0x00000000, 0x00000E07, 0x00000005, 0x00436B28, 0x00000E08, 0x00000005, 0x00436B30,
    0x00000E06, 0x00000005, 0x004364B0, 0x00000E03,
};
#endif
#endif
#if defined(VERSION_DE)
struct {
    u32 words0[386];
    char text1[20];
    u32 words2[1];
    char text3[24];
    u32 words4[6];
} g_itemsCopylocalizedplayernamesuffixWritableWordsDe = {
    {
        0x00000005, 0x00436AF8, 0x0000000A, 0x00000005, 0x00436BAC, 0x00000002, 0x00000005, 0x00436C18,
        0x00000001, 0x00000005, 0x00436BB4, 0x00000008, 0x0000005C, 0x00436C54, 0x00000007, 0x0000005C,
        0x00436D0C, 0x00000000, 0x00000000, 0x00000000, 0x00000E07, 0x0000000C, 0x0043700C, 0x00000E08,
        0x0000000C, 0x00437014, 0x00000E06, 0x0000000C, 0x00436E54, 0x00000E03, 0x0000000C, 0x00436FDC,
        0x00000002, 0x0000000C, 0x0043708C, 0x00000001, 0x0000000C, (unsigned int)Player_FreeAlternatePlayerSettingsScreen_Address, 0x00000008, 0x000001C2,
        0x004370D4, 0x00000007, 0x000001C2, 0x00437184, 0x00000000, 0x00000000, 0x00000000, 0xE559E3A1,
        0x00000000, 0x00000000, 0x00000E08, 0x00000009, 0x00437404, 0x00000E06, 0x00000009, 0x004372D0,
        0x00000E07, 0x00000009, 0x004373D4, 0x00000E03, 0x00000009, 0x004373A4, 0x00000001, 0x00000009,
        0x00437570, 0x00000002, 0x00000009, 0x00437534, 0x00000000, 0x00000000, 0x00000000, 0x00000E08,
        0x0000001E, 0x004377D0, 0x00000E06, 0x0000001E, 0x004376D8, 0x00000E07, 0x0000001E, 0x004377A8,
        0x00000E03, 0x0000001E, 0x00437778, 0x00000001, 0x0000001E, 0x004378F0, 0x00000002, 0x0000001E,
        0x004378B4, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000E08, 0x00000012, 0x00438C44,
        0x00000E07, 0x00000012, 0x00438A94, 0x00000E06, 0x00000012, 0x00437A10, 0x00000E03, 0x00000012,
        0x00438A64, 0x00000002, 0x00000012, 0x00438E1C, 0x00000001, 0x00000012, 0x00438D54, 0x00000E0A,
        0x00000012, 0x00438A9C, 0x00000000, 0x00000000, 0x00000000, 0xED1BA083, 0x1472E040, 0x9ACE57A0,
        0x00000000, 0x00000000, 0x00000E07, 0x00000006, 0x00438FD0, 0x00000E08, 0x00000006, 0x00438FD8,
        0x00000E06, 0x00000006, 0x00438ED0, 0x00000E03, 0x00000006, 0x00438FA0, 0x00000002, 0x00000006,
        0x00439134, 0x00000001, 0x00000006, 0x004390E8, 0x00000000, 0x00000000, 0x00000000, 0x00000E07,
        0x0000000D, 0x004392C0, 0x00000E08, 0x0000000D, 0x004392C8, 0x00000E06, 0x0000000D, 0x00439200,
        0x00000E03, 0x0000000D, 0x00439290, 0x00000002, 0x0000000D, 0x004393C4, 0x00000001, 0x0000000D,
        0x00439368, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000E08, 0x00000018, 0x004395E8,
        0x00000E06, 0x00000018, 0x004394A0, 0x00000E03, 0x00000018, 0x004395B8, 0x00000001, 0x00000018,
        0x00439710, 0x00000002, 0x00000018, (unsigned int)Frontend_HandleProfileResetConfirm_Address, 0x0000000A, 0x00000018, 0x004396B0, 0x00000000,
        0x00000000, 0x00000000, 0x030F775D, 0x30B05309, 0x00000E06, 0x00000021, 0x00439CF0, 0x00000002,
        0x00000021, 0x00439DC4, 0x00000001, 0x00000021, 0x00439D18, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x000000CF, 0x00000130, 0x000000E8, 0x000000E9, 0x000000EA, 0x000000EB, 0x000000EC,
        0x000000ED, 0x00000120, 0x0000011F, 0x0000011E, 0x0000011D, 0x0000011C, 0x000000DC, 0x000000DE,
        0x000000E0, 0x000000E2, 0x000000E4, 0x000000E6, 0x000000F5, 0x00000131, 0x0000010F, 0x00000110,
        0x00000111, 0x00000112, 0x00000113, 0x00000114, 0x00000126, 0x00000127, 0x00000128, 0x00000129,
        0x0000012A, 0x000000F9, 0x000000FB, 0x000000FD, 0x000000FF, 0x00000101, 0x00000103, 0x000000CD,
        0x00000132, 0x000000EE, 0x000000EF, 0x000000F0, 0x000000F1, 0x000000F2, 0x000000F3, 0x0000012F,
        0x0000012E, 0x0000012D, 0x0000012C, 0x0000012B, 0x000000D1, 0x000000D3, 0x000000D5, 0x000000D7,
        0x000000D9, 0x000000DB, 0x000000F7, 0x00000133, 0x00000115, 0x00000116, 0x00000117, 0x00000118,
        0x00000119, 0x0000011A, 0x00000121, 0x00000122, 0x00000123, 0x00000124, 0x00000125, 0x00000104,
        0x00000106, 0x00000108, 0x0000010A, 0x0000010C, 0x0000010E, 0x00000098, 0x00001397, 0x0000000A,
        (unsigned int)g_weaponLockedNoticeText + 0x28, 0x000000AD, 0x00001396, 0x0000000C, (unsigned int)g_weaponLockedNoticeText + 0x30, 0x000000AF, 0x000013AD, 0x0000000B,
        (unsigned int)g_weaponLockedNoticeText + 0x2C, 0x000000B3, 0x000013A9, 0x00000001, (unsigned int)g_weaponLockedNoticeText + 0x4, 0x000000A2, 0x0000139B, 0x0000000F,
        (unsigned int)g_weaponLockedNoticeText + 0x3C, 0x0000009A, 0x000013A1, 0x0000000D, (unsigned int)g_weaponLockedNoticeText + 0x34, 0x0000009B, 0x000013A2, 0x00000009,
        (unsigned int)g_weaponLockedNoticeText + 0x24, 0x00000099, 0x0000139A, 0x00000008, (unsigned int)g_weaponLockedNoticeText + 0x20, 0x000000AA, 0x0000138D, 0x0000000E,
        (unsigned int)g_weaponLockedNoticeText + 0x38, 0x000000AE, 0x0000138F, 0x00000007, (unsigned int)g_weaponLockedNoticeText + 0x1C, 0x000000B0, 0x0000138C, 0x00000002,
        (unsigned int)g_weaponLockedNoticeText + 0x8, 0x000000A9, 0x000013A7, 0x00000005, (unsigned int)g_weaponLockedNoticeText + 0x14, 0x000000AB, 0x0000139E, 0x00000003,
        (unsigned int)g_weaponLockedNoticeText + 0xC, 0x000000AC, 0x00001393, 0x00000006, (unsigned int)g_weaponLockedNoticeText + 0x18, 0x000000B1, 0x0000138B, 0x00000004,
        (unsigned int)g_weaponLockedNoticeText + 0x10, 0x00000E07, 0x00000008, 0x0043A2F0, 0x00000E08, 0x00000008, 0x0043A5B8, 0x00000E0A,
        0x00000008, 0x0043A850, 0x00000E06, 0x00000008, 0x00439E90, 0x00000E03, 0x00000008, 0x0043BB30,
        0x0000000A, 0x00000008, (unsigned int)addrLow_Frontend_FreeEquipmentScreen, 0x00000002, 0x00000008, 0x0043BEE8, 0x00000001, 0x00000008,
        0x0043AB00, 0x00000007, 0x00007530, 0x0043BDB0, 0x00000005, 0x00007530, 0x0043BC80, 0x00000008,
        0x00007530, 0x0043BE4C, 0x00000006, 0x00007530, 0x0043BD18, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, (unsigned int)&g_equipmentEventHandlers + 0x90, 0x62696720, 0x63686561, 0x74206163, 0x74697661, 0x74656400, (unsigned int)&g_encodedCheatCode[0xC],
    },
    "big cheat activated\000",
    {
        (unsigned int)&g_encodedCheatCode[0xC], 0x6A616E65, 0x73206368, 0x65617420, 0x61637469, 0x76617465, 0x64000000, (unsigned int)&g_encodedCheatCode[0x24],
    },
    "janes cheat activated\000\000\000",
    {
        (unsigned int)&g_encodedCheatCode[0x24], 0xD0543EBB, (unsigned int)g_playerViewRenderContextPlayerNames_de, (unsigned int)&g_profileAchievementProgressRows[0x89], (unsigned int)&g_profileAchievementProgressRows[0x11F], (unsigned int)&g_profileAchievementProgressRows[0x1B5],
    },
};
#endif

#if defined(VERSION_DE)
u32 k_VhandlerInitializepagereuroextendedEncodedBlockDe[30] = {
    0x3DD1A331, 0x0FE1150F, 0x3161E6A1, 0x6F6137EF, 0x2612912E, 0xA1F34005,
    0x0228B2E2, 0x13A1B410, 0xF0F15124, 0x0E2FA16C, 0x29CD8A02, 0x34ED5CB3,
    0xC2E2200F, 0x20EEE1A2, 0xB3BFE01D, 0x22FEE3EF, 0x10B12F30, 0xF01F0F5F,
    0x1106B110, 0x32317C11, 0x11331FB1, 0x312D3200, 0x060E4321, 0xB115B031,
    0x0223FE40, 0xFFB10D0D, 0x19E1FEFF, 0x2EE0C1F0, 0xB0FFF1FF, 0x0EFD1EB3,
};
#if defined(VERSION_DE)
struct {
    u8 retainedRecordWords[8];
} k_VhandlerInitializepagereuroextendedEncodedWords __attribute__((aligned(4))) = {
    { 0xB2, 0xE0, 0x1E, 0xF1, 0xE1, 0xCD, 0xFF, 0xF3 }
};
#endif
#endif
#if defined(VERSION_DE)
struct {
    u32 reserved[3];
} k_resourcePagerReservedRecord = {
    { 0xB1B31D31, 0xFFDEDA0B, 0x2EA1EC3D }
};
#endif

#if defined(VERSION_DE) || defined(VERSION_US)
#ifdef VERSION_DE
struct {
    unsigned int words0[188];
    float floats1[1];
    unsigned int words2[16];
    float floats3[1];
    unsigned int words4[211];
    float floats5[1];
    unsigned int words6[157];
} k_VhandlerHandleresourcepagerequestEncodedWords = {
    {
        0xA131C611, 0x0B18060E, 0x50B13131, 0x5027B5F2, 0xC012B102, 0x2415E12E, 0x1A5E41A1, 0xD54E9F4B,
        0x4895E2F6, 0xA1E2092D, 0x3E6F20BF, 0x78B134B5, 0xF4DB1EC0, 0xCA2DA1B5, 0xAE6B4BF2, 0xB87DD3B1,
        0x110A5DE3, 0x0EF1BEDD, 0xA1A3E1F0, 0xF038661D, 0x63B12D02, 0xB2002A36, 0xF035B33F, 0x15D30E45,
        0x03B41EB3, 0x1410016C, 0x13D1F21D, 0xB1FF4FFF, 0x1EF0EE0E, 0xEFB1EEF0, 0x0FE942CE, 0x0FB4B13B,
        0x0FAD20BD, 0x3DFB50B1, 0x01E5EFDF, 0xD113F30B, 0xB10F2C10, 0x5F30DF23, 0xEEA23C11, 0xFC50BD71,
        0x4BCFB3FE, 0xDFF3F1FB, 0xE40A32B1, 0x0B1EA1BF, 0xE1EDB013, 0xB1E14FC2, 0xEA2D1E2F, 0xF0B1FF03,
        0x450047A0, 0x06F2B33F, 0xD1011050, 0x301D03B1, 0x23E12F7C, 0x52D5124F, 0xB33F12E6, 0xE1407A40,
        0x33B1F204, 0xB17042D2, 0xC11EB00F, 0x21311B1F, 0x13E00EA2, 0x41CD2D17, 0xDAAEDFD9, 0xB22FCC40,
        0xC1FB3FE0, 0xECB11DD1, 0x03D04FCF, 0xEF12B1EE, 0x0DEDA000, 0x0F2180B3, 0xEF2DA02F, 0xF1B0FF3D,
        0xB12AD3C4, 0xFAD0CFC0, 0xFDB1C231, 0x2C2FE3A1, 0x1A30B101, 0xDFD11C32, 0xEE5006B1, 0xFD2F5315,
        0xD05103EF, 0xB121F4E0, 0x34313D01, 0x00A37E0D, 0x35F0E2F4, 0x0FDCB151, 0x5E233003, 0x4F4015B1,
        0x4F211502, 0x407F0E20, 0xA375D7BE, 0x4532D450, 0x5FB1E225, 0xFF12FDFE, 0x1D0FB1C6, 0xCAEF1D0C,
        0xFBC0E0C3, 0xF00B30FE, 0xF1E1E0FE, 0xB3293C4E, 0xF1E1BF2D, 0x02B1A3E0, 0x0BFFE01D, 0xD4C2B2F2,
        0x23F251F0, 0x2A0FF2B2, 0x3FF0F312, 0x032D0FEB, 0xB10F0103, 0x06014002, 0xFEA26311, 0x5793014E,
        0x2143B120, 0xD2E11F41, 0xE12320A3, 0x7F614C03, 0x1385064F, 0xB325C231, 0xFD1E313C, 0x04B3EE3E,
        0x1C000EB0, 0xEB3FB1DD, 0x1BFFE1DE, 0x2DED1EB3, 0xC010C2EF, 0x22B110DD, 0xB1F0D0F3, 0x1EF3D40D,
        0xF3B30032, 0xE0F16100, 0x1122B1FE, 0x1D04302F, 0x110E21B1, 0xC14214D2, 0x51F23F1C, 0xA23FE134,
        0xD1EC522E, 0xF1A14D15, 0x11300FEE, 0x9215A1FF, 0x1FF0F0C1, 0xCE0018A3, 0xF10D08E1, 0x1A4A1FB1,
        0xB1EC3DF0, 0xCED0FD2F, 0xFFA0ADED, 0xEEA022DE, 0x2F42B320, 0x3FF50F01, 0x2C20E0B1, 0x204022D5,
        0x3031E212, 0xB1F01EF3, 0xFF4F3100, 0xC0A3EF3D, 0xD1F0E41E, 0xFEB3A300, 0xEB01F0FE, 0xF3E301A3,
        0xE00C2C00, 0xF5FCC11C, 0xA23E231F, 0xFFCE2FDA, 0x2CB125F2, 0x102110E1, 0x321DB101, 0x1F4F12F4,
        0x114F23B1, 0x0103251E, 0x41FF6011, 0xA2FFEFA2, 0x621D1B2F, 0x17A1BCFB, 0xE3AE0F10, 0x3CD1A3E5,
        0xEC1FE0FE, 0xCBC1A2A3, 0x0FDB2EA5, 0xD83A04C0, 0xA1DD3FC3, 0x0DEED6EB, 0xB3A1F11B, 0x3F107E5D,
        0x6511A3C5, 0x40D00514, 0x4313C7A3, 0x7E60E2D1, 0x3E523F5B, 0xA1C56332, 0xB401D73D, 0x3CA20EE2,
    },
    { 0.2053198f },
    {
        0xA1C56332, 0xB401D73D, 0x3CA20EE2, 0xEE23DD08, 0xE1EEB3EF, 0xC02B04FE, 0xFFFBE2A1, 0x921DFAE0,
        0xDF0A3EA3, 0xB1E0004D, 0xE0B01021, 0xDFA114F1, 0x7D16F22E, 0xF437A34D, 0x1381E022, 0x5C1FC2A2,
    },
    { 3.7003502e-09f },
    {
        0xF11E065C, 0xA1048031, 0x30E4B222, 0x1EA106B0, 0x3D3406EE, 0x5811A1B5, 0xE22912E5, 0x4C3E31A1,
        0xA00C5A06, 0xC22F5FFD, 0xA3AD4070, 0x14C48B6F, 0x44B3F21E, 0xDF01E140, 0xE000A093, 0x3E40E3BD,
        0xE9D314B1, 0x041D32F0, 0x1E3033A3, 0xA1685633, 0x211F2867, 0x26A1CCD0, 0xB2023E70, 0xDF95B2F1,
        0x5F13DCF2, 0xF22302B1, 0xDDFBE3FC, 0x40F11ED1, 0xA14AFD31, 0xEC6DDEDF, 0x2FA3F073, 0xB0FD1CC4,
        0x2E22A2F2, 0xCED4D97D, 0x40CFDDA2, 0xB2F1F332, 0x1C203EFA, 0xB33CEE00, 0xFF14E1FF, 0x0DA2AD30,
        0xC52C908F, 0x3F72A150, 0xA8FECD21, 0xA61B19A1, 0xE0D6E5C1, 0x6DC2E04F, 0xA33246B4, 0x2E1D0F1E,
        0x41B140E0, 0xEFFD1E24, 0x1F2DA3BF, 0xD4306413, 0x92DDF5B3, 0x3133EFFF, 0xED1F5104, 0xB3FE0DF2,
        0xF05013FD, 0x0EB30141, 0x05FE1C1F, 0xF213A16F, 0x2CB19C40, 0x44A50CA1, 0x1F5B0205, 0x211204D1,
        0xA130401E, 0xDD0F3B10, 0x01A2DFFB, 0xED01C271, 0x2FBFB1D2, 0xF2303F11, 0xAC2025A1, 0xC211FBED,
        0xF42F6CF4, 0xA1842EF2, 0x236D11FD, 0xACB101F1, 0x2FE1FB2D, 0x03D1A338, 0x20BDE2F1, 0x3D4EABB3,
        0xD1FF04E1, 0xF0FCFD20, 0xB3052F1D, 0xF0D0005E, 0x32A1EFDC, 0xDC14F62E, 0x6EFCA1A2, 0xFEF3C446,
        0xF03D00A1, 0xD2044226, 0xED3FDF2C, 0xA1610510, 0x4DDC033E, 0x15A14A14, 0x170E353D, 0x531DA125,
        0xCE433501, 0x1BF01FA1, 0x12240CE1, 0xB1D01F22, 0xA30BFEDE, 0xE201060E, 0xB9A33EFF, 0x51032ECD,
        0xC221A351, 0x73EE11DB, 0x4E27F6A3, 0xF0D02DA1, 0x12E17E01, 0xA3EEBCF2, 0x22E3E42E, 0xECA3D0EC,
        0x50E2FFF3, 0x90FEA3DE, 0x24013C0B, 0x1FDF11A2, 0x300EF3F1, 0x12EA0AF0, 0xA232F1FE, 0xF3BD0EC1,
        0x40A305D0, 0xEEECF1F2, 0x7D11A11E, 0xF1EF1F52, 0xE40D2CA1, 0x4DB34306, 0x102DC0FD, 0xA2104F04,
        0x4101CEFE, 0xE4A2013C, 0x02800E2F, 0xD3139130, 0x7E2879D6, 0x2444A7B2, 0x1210000D, 0x1F10F400,
        0xA100CF02, 0xFD3341E0, 0x01A1FF2E, 0xE7616F20, 0x21C2A310, 0x4FFF32D2, 0xDD1E10A1, 0x10F1301D,
        0xB2F401F0, 0x90CECCE7, 0xD9310FBD, 0xB1A12E81, 0x0B41D22B, 0xFD1EB1F0, 0xDF011D12, 0xDF0BF0A1,
        0xEF1F05E0, 0xE101DD3E, 0x92B43D40, 0x579F9CF7, 0x0BA33004, 0x20DE2B1F, 0x0522915A, 0x3780C03C,
        0x74636E93, 0x6CA47DB7, 0x51460A0A, 0xA1F0E404, 0x10E2023D, 0xF3A04040, 0xFFDD0304, 0xB342A123,
        0xC90F1EF0, 0x03D230A1, 0xDD029D3D, 0x200C4E90, 0xA1FEC141, 0xF00112DF, 0x5DA3B20D, 0x2D403E0F,
        0x3FEFA2DE, 0xBDEC100D, 0x61BE2092, 0xBEB15F01, 0x4C4855E1, 0x9371DD33, 0x3AD1564B, 0x24A11010,
        0x14D2022F, 0x330C9154, 0x576F678F, 0x832FF1A0, 0x1F210511, 0x3421C22E, 0xA122C01F, 0xD20E2F98,
        0x02A1EF0E, 0xF111D3FB, 0x1100A0F1, 0x0EFBC001, 0xF01D23A2, 0xB1CF100E, 0x22F21EFB, 0x93F4BF32,
        0x1AF910DB, 0x3FA2EE1E, 0x12BF0F0E, 0x3030A1F2, 0x20F023E4, 0x212E0293, 0x4EF34081, 0x20C7F351,
        0xA1EF5F0E, 0x1F00F24F, 0x15A130F5, 0x4D2F3030, 0xF5309334, 0xEC262CDC, 0xCE50E5A1, 0x11DF1D0B,
    },
    { 1.8369818e+08f },
    {
        0xF5309334, 0xEC262CDC, 0xCE50E5A1, 0x11DF1D0B, 0xE0E0B12C, 0x9202B49D, 0x5ADC4B5D, 0xD190F225,
        0xE4923CCE, 0x0D69A152, 0xE100F1EC, 0xFFF22CA1, 0x1F2DE5DD, 0xFEB32D00, 0x9228A51E, 0x0EE38FE7,
        0x3CA1041C, 0x130F4044, 0xD1139000, 0xF81A0D70, 0x64210692, 0x1AD6E200, 0x2D012720, 0xA2350F11,
        0x2020D1D3, 0x20A20031, 0xEE3E01EF, 0xCDFE92E2, 0x829987EA, 0x5943CCA1, 0xEDFDF3E0, 0x2404DD1C,
        0xA2CA2FEE, 0x3E1F011E, 0xD2913FC4, 0x8AE0248C, 0x9642A241, 0x0B00D030, 0x0FEFF190, 0x1333CF72,
        0x730412F0, 0xA24FFF00, 0xF43121F0, 0xFEA2DDF1, 0xF2E04FE2, 0xF0DFA12E, 0xE212F324, 0x3C031FA3,
        0x30E321C1, 0x3F23D15F, 0x922173F4, 0x01B62569, 0x6FA05101, 0x1011E011, 0x20FF90E0, 0x6C51EDBD,
        0xBEE002A2, 0xEC2DB0FE, 0xE010D2CE, 0x90CBC0EC, 0xCE1E347D, 0xFDA2DEFD, 0xF19D1002, 0x4D03A1ED,
        0x0E1E10B1, 0x4E01E1A1, 0x04E04E03, 0x0F0CE011, 0xA22312F1, 0xFE000F1E, 0x1490F30E, 0xBCC6100D,
        0x73FBA01E, 0xFF0F3342, 0x2FF05391, 0xC7F0D09E, 0x24936D04, 0x90B4FFC8, 0xEDAF11E1, 0x9192E9F1,
        0x3C1E1CE0, 0x255DA231, 0x2010E014, 0xD22FF4A3, 0xED111FF0, 0x0F1CD2FE, 0x920C8E0B, 0x01611D1D,
        0x2393C2FE, 0x262EE06B, 0x3556A1FE, 0x31B04531, 0x3F01E1A1, 0x4326E1F1, 0x0E3EE241, 0x93E10F3F,
        0xB071AEBD, 0x3F91400E, 0xC0F1B3D0, 0xC8F393F0, 0x3A3FE415, 0xCB92B2A2, 0x1D7F1EF0, 0xFF10F01B,
        0x92CEDEA4, 0x4254D3F9, 0x1191C371, 0x7DE40B31, 0x00E4913F, 0x7114C00B, 0x16530C91, 0x4C842001,
        0x43AFCC1A, 0x92D40F60, 0xE0B3DD1C, 0x0193E1ED, 0xEEB61B31, 0x81C2922F, 0x2F379E4E, 0xB4327DA1,
        0x010F0421, 0x11D05F10, 0x92210E80, 0x8E01D072, 0xC093213D, 0x638A3DDD, 0x271D937A, 0xBCD43B52,
        0xE32CCDA3, 0x12B221F2, 0xF0CD0FF4, 0x93402DD6, 0x9EE0F770, 0xA1A31FB0, 0xC4204F1E, 0x0CFFA1F3,
        0xD1214D2F, 0xC0DD0493, 0xFE6D0A1E, 0x0717D122, 0x93B9F330, 0x0313F2B1, 0xDFA32F02, 0x210EFF40,
        0x013091A1, 0x01FA3D27, 0x6220FFA1, 0xE1E0510F, 0x112EF0CE, 0x934F5D12, 0xECC2BE1F, 0x1E92E41E,
        0xDFBDE100, 0x4D0391D0, 0xF2F2E0A0, 0x1D013F93, 0x392D31C5,
    },
};
#endif
#if defined(VERSION_DE)
unsigned int g_VhandlerHandleresourcepagerequestEncodedWordSingle[1] = {
    0x3E300DCC,
};
#endif
#ifdef VERSION_DE
unsigned int g_VhandlerHandleresourcepagerequestEncodedWords[179] = {
    0x93F0D7E7, 0x709FF00E, 0x61931143, 0x0FDE1D15, 0x452D91CF, 0x0E1E71E7, 0x34FD29A3, 0x01021F41,
    0xE1E21D00, 0x93230208, 0x0DD1E525, 0xBE93DDBD, 0xDC31027B, 0xD09E938D, 0x6A33F2D2, 0xBBC1B091,
    0xC37EF3C2, 0xCFCA12F1, 0x90126F02, 0xF0EE0DFF, 0xEE911F03, 0xD5EC4C0E, 0x4743A1F2, 0x01E10041,
    0x0222FE93, 0xF120F523, 0x3E141DE2, 0x93D0E360, 0x261C04FA, 0x2493F113, 0x132F2801, 0xB1039352,
    0x0EDD2C22, 0xB1FC7291, 0xF44EB0EF, 0xFE412D05, 0x8087ED0F, 0xEFCEAF0A, 0xCB93EFED, 0x59ECE21E,
    0xD31D93C9, 0x32D4B25D, 0x01BC0191, 0x2D5235EC, 0x3FB10104, 0x9312211C, 0xB4FE1114, 0x51926002,
    0x0ECDFF45, 0xF12B93B4, 0x1D0330F2, 0x13EAEF81, 0x9773450F, 0xE1FC7D0C, 0xA30410F0, 0x2F0F0021,
    0x0283F3EE, 0x1D4E1E65, 0xB147931F, 0x0FF20C20, 0x26C11483, 0xCC3ACD2B, 0x0A7FDBED, 0x93D0C0FD,
    0x03A11B1A, 0x0F938001, 0x2CCD1FDC, 0x0F2C8298, 0x05E0E1FB, 0xD00B7093, 0x0143DE54, 0xB430006F,
    0x93214FD0, 0x10512BD7, 0x3E910323, 0xA50371FD, 0x361F9131, 0x5141E4F3, 0x0FEE1E93, 0x36FE3112,
    0xFD2FF101, 0x931600FB, 0x04DFE13E, 0x049302CF, 0x002ACD03, 0xF13F93B0, 0xFF00FC12, 0xFD2E3F91,
    0xBE1FD322, 0xE0D40BEC, 0x91E23C5D, 0xDE4E00EE, 0xB2911416, 0x00F5200E, 0x4E0F9362, 0x21DB20F3,
    0x1022F291, 0x21F1F4BD, 0xFF222E00, 0x910F2ADF, 0x0020E0E2, 0x0B93FFBF, 0x1FF40EEF, 0xD2CC91EE,
    0x3DE4FE01, 0x0EDDE081, 0x20EE4CE4, 0xD25E3ED6, 0x82451FE3, 0x50004C0F, 0x1292FFE2, 0x242F3F03,
    0x2FFD8133, 0x244D2021, 0xD11F4683, 0xE144C061, 0xFF61CFF0, 0x82167EF6, 0x6FF22221, 0x528267C0,
    0x7F15FE88, 0x102F920B, 0x0FC120EC, 0xC1131293, 0xEF240FFD, 0xF002EE1E, 0x83E2322E, 0xFED22E2D,
    0x9082D32E, 0x21F083F4, 0x1EED82ED, 0xF30EFCE1, 0xF1DE2583, 0x4C23E1BE, 0x53DF31E3, 0x91FB2F0F,
    0xE5F0221D, 0x0F82EBA1, 0x9F6DE63D, 0x99B2832E, 0x1D4301DD, 0xFB474F92, 0x00F01111, 0x1FF14600,
    0x82DD5FF2, 0xED0F525F, 0xC282F4E0, 0x1EFFFE44, 0x200283F0, 0xF2DEF100, 0x5F0EFC83, 0x34EF0DCF,
    0x01BEC10F, 0x831E128C, 0x5FFBC61F, 0x4F83A1DC, 0x43D0DF3F, 0xEFD183F2, 0xF63FD024, 0x3EEF1083,
    0x1350D924, 0xF0F2CC01, 0x8360ABD3, 0x115F9C2F, 0x1493FD0E, 0x40E0EFFF, 0x043D73B8, 0x7204E014,
    0x42F3C393, 0x11031010, 0x02021E04, 0x83053F20, 0x01250E10, 0x1F8350D1, 0x0E63EE1A, 0xE40E8303,
    0x0C3FD11B, 0xEFF1E493, 0xFBF1EE11,
};
#endif
#if defined(VERSION_DE)
unsigned int g_VhandlerHandleresourcepagerequestEncodedWordsTriple[3] = {
    0x2EDF001D, 0x83F4FCA0, 0x0302D211,
};
#endif
#endif
#if defined(VERSION_DE)
extern unsigned int g_resourcePageRequestEncodedData[93];
#endif

/* Retained data for this translation unit. */
#if defined(VERSION_DE)
unsigned int g_resourcePageRequestEncodedData[93] = {
    0xF283FA02, 0x0304FF41, 0x0FBD8334, 0x1F160F0E, 0x1C232382, 0x2FEEFF01, 0xE02D2732, 0x725D1113,
    0x7AF9A760, 0x6482F204, 0x3EFFDF53, 0x2FB08150, 0x0422F1E0, 0x4CE0DE83, 0x10FCC205, 0x2F0AFFE0,
    0x8100F2F2, 0x1FFB1D2F, 0xE3832FED, 0xEFB2712F, 0xB61E83DF, 0xEC0252F4, 0xED20E272, 0x11FDF023,
    0x1B78B311, 0x8331CEC0, 0x273D12BF, 0x538332C1, 0x411054E1, 0x010F730F, 0x735113F0, 0x5B3F1F82,
    0x43EE4EEE, 0x2FF1FCEC, 0x83CD2101, 0xFFBF1B14, 0xCF83FFF1, 0x3DCBF105, 0x0DE072A2, 0x3CB9CD41,
    0x02F2F082, 0xEB01112F, 0x2DCF02BE, 0x82F1F441, 0x2ED222F0, 0x0082C323, 0x3E0110E0, 0xF0358251,
    0x10C31F31, 0xD1220272, 0x6D24DFDC, 0x903F31ED, 0x8312C144, 0x0FF0F210, 0x21820DFF, 0x1502E0DF,
    0xE25183C1, 0xF901300D, 0xD2300173, 0xC0BA25F2, 0x5C2ED912, 0x73DF5AB2, 0xFF3D37FA, 0xDD713E54,
    0xB23E1FD1, 0x152F824E, 0x0F011F33, 0xFFE01082, 0x21FF116F, 0xE32220FF, 0x733234FC, 0x423F0308,
    0x757203CD, 0xF0D0F511, 0x1AEE7373, 0x0112F40C, 0x6E11CD73, 0xF1E32E8A, 0x45EFE1E8, 0x73DCFC54,
    0xEFA9EE24, 0xD373F2DB, 0x1D12F36A, 0xD9B183D3, 0x411C1FF1, 0xF0004283, 0x0CCE5001, 0x1FE232F0,
    0x73DE4FA0, 0x3CD431ED, 0xAE731A23, 0xEB742ADE, 0x91BE8322,
};
#endif
