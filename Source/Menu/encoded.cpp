#include "include_asm.h"
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Common/effectrender.h"
#include "Menu/levelselect_types.h"
#if ((defined(VERSION_DE))) || ((!(defined(VERSION_DE))))
#include "Menu/handle_unlocked_level_selection_body.h"
#endif
#include "../../sdk/include/LIBC.H"
#include "Common/weapon_screen_message_operations.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/cheatcode.h"
#include "Common/vector4f.h"
#include "Common/font_style_and_glyph_operations.h"
#include "Common/menu_ui_providers.h"
#include "Menu/menu_drawanimatedmenusprite.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Menu/Encoded/encoded_drawtextentrycursor_symbols.h"
#include "Menu/built_menu.h"
#include "Common/runtime_declarations.h"
#include "Menu/Encoded/encoded_findunlockedlevel_symbols.h"
#include "Common/world.h"
#if ((!(defined(VERSION_DE))))
#include "Common/shared_menuselection.h"
#endif
#if ((!(defined(VERSION_DE))))
#include "Common/game_session.h"
#endif
#if ((!(defined(VERSION_DE))))
#include "Ovlgame/confirming_controller.h"
#endif
#include "Menu/encoded_resettextentryresult.h"
#include "Menu/Encoded/encoded_resettextentryresult_symbols.h"
#include "Render/soundelement_playflatsound.h"
#include "Menu/Encoded/encoded_applycheatcode_symbols.h"
#include "Menu/menu_item_views.h"
#include "Menu/Pak/pak_menu_entries.h"

#if defined(VERSION_DE)
extern char g_encodedCheatTextWords[180];
#endif

/* Minimal callback views established by Encoded_UpdateLevelSelectionAvailability_MenuHandleunlockedlevelselection..C85C: the owner at+12
   supplies the descriptor whose option flags are at+728. */

static inline s32 levelBit_menuHandleunlockedlevelselection(s32 level) {
    s32 bit;

    switch (level) {
    default:
    case 0:
        bit = 0x10000;
        break;
    case 1:
        bit = 0x20000;
        break;
    case 2:
        bit = 0x40000;
        break;
    case 3:
        bit = 0x80000;
        break;
    case 4:
        bit = 0x100000;
        break;
    case 5:
        bit = 0x200000;
        break;
    case 6:
        bit = 0x800000;
        break;
    case 7:
        bit = 0x400000;
        break;
    case 8:
        bit = 0x1000000;
        break;
    case 9:
        bit = 0x2000000;
        break;
    case 10:
        bit = 0x4000000;
        break;
    }
    return bit;
}

/* Choose the first unlocked level, then enable the corresponding widget flags. */
static inline s32 firstUnlocked_menuHandleunlockedlevelselection(void) {
    s32 level = 0;
    s32 i;
    for (i = 0; i < 11; i++) {
        if (g_gameSettings.unlockedLevels & levelBit_menuHandleunlockedlevelselection(level)) {
            return level;
        }
        level++;
        if (level >= 11) {
            level = 0;
        } else if (level < 0) {
            level = 10;
        }
    }
    return -1;
}

void Encoded_UpdateLevelSelectionAvailability(LevelSelectOwner *owner) {
    s32 level = firstUnlocked_menuHandleunlockedlevelselection();
    g_encodedSelectedLevelIndex = level;
    if (level != -1) {
        owner->descriptor->flags |= 0x01800000;
    } else {
        owner->descriptor->flags &= 0xFE7FFFFF;
    }
    if (g_gameSettings.local) {
        owner->descriptor->flags &= 0xFE7FFFFF;
    }
}
#if defined(VERSION_DE)
#endif

/* Draws the g_encodedTextEntryState spinner: during the first part of its blink period it fills a two-pixel white bar below the item under the digit its value selects, placed from the item's x by the character width Menu_GetWidgetStyle_EncodedDrawtextentrycursor reports scaled to the screen, with the style's alpha, through OnScreen_SetupFillMode and OnScreen_DrawBevelBox; then draws the item through Menu_DrawLocalizedMenuItemText. */
void Encoded_DrawTextEntryCursor(void *menu, MenuLocalizedTextItemView *item, void *third, MenuStyle *style) {
    f32 width;
    f32 alpha;
    s32 x;
    unsigned int bits;

    if (g_encodedTextEntryState.timer <= (6.0f)) {
        width = ((struct PaddedFloatView *)Menu_GetWidgetStyle((struct MenuItemFlagsView *)menu))->value * (f32)g_hudReferenceViewportWidth * (0.0035211266949772835f);
        x = (f32)item->x + (f32)g_encodedTextEntryState.value * width;
        g_multiplayerItemRenderState = -1;
        alpha = style->alpha * (style->fade * (128.0f));
        OnScreen_SetupFillMode();
        OnScreen_DrawBevelBox(x, item->y, (f32)x + width, item->y + 2, 0, 0, 0xFF, 0xFF, 0xFF,
                      (u8)(bits = !((2147483648.0f) <= alpha) ? (s32)alpha : (bits = (s32)(alpha - (2147483648.0f))) | 0x80000000U));
    }
    Menu_DrawLocalizedMenuItemText(menu, item, third, style);
}

s32 Encoded_UpdateTextEntryCursor(void *entry, CheatMenuInputView *menu) {
    f32 t;

    t = g_encodedTextEntryState.timer + g_frameElapsedTime;
    g_encodedTextEntryState.timer = t;
    if (t >= g_encodedTextCursorTiming[1]) {
        g_encodedTextEntryState.timer = t - g_encodedTextCursorTiming[1];
    }
    if (menu->state == 2) {
        if (((s32 (*)(s32))Control_IsLeftPressed)(menu->input) != 0 && g_encodedTextEntryState.value > 0) {
            g_encodedTextEntryState.value--;
            g_encodedTextEntryState.timer = 0.0f;
        } else if (((s32 (*)(s32))Control_IsRightPressed)(menu->input) != 0) {
            if (g_encodedTextEntryState.value < g_encodedTextEntryState.count) {
                g_encodedTextEntryState.value++;
                g_encodedTextEntryState.timer = 0.0f;
            }
        }
    }
    return 0;
}

/* Does nothing and returns 0. */
s32 Encoded_TextEntryReturnZero(void) {
    return 0;
}

s32 Encoded_InsertTextEntryCharacter(TextEntryBufferView *textEntry) {
    s32 index;
    s32 count;

    g_encodedCheatCharacterIndex = -1;
    g_encodedTextEntryState.timer = 0;
    if (g_encodedTextEntryState.count == 22) {
        return 0;
    }
    index = 22;
    if (g_encodedTextEntryState.value < 22) {
        do {
            g_encodedTextEntryState.text[index] = g_encodedTextEntryState.text[index - 1];
            index--;
        } while (g_encodedTextEntryState.value < index);
    }
    g_encodedTextEntryState.text[g_encodedTextEntryState.value] =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        *textEntry->textBuffer[g_languageIndex];
#else
        **textEntry->textBuffer;
#endif
    count = g_encodedTextEntryState.count + 1;
    g_encodedTextEntryState.value++;
    g_encodedTextEntryState.count = count;
    g_encodedTextEntryState.text[count] = 0;
    return 0;
}

s32 Encoded_DeletePreviousTextEntryCharacter(void) {
    s32 index;
    s32 next;

    g_encodedCheatCharacterIndex = -1;
    g_encodedTextEntryState.timer = 0;
    if (g_encodedTextEntryState.count == 0) {
        return 0;
    }
    if (g_encodedTextEntryState.value == 0) {
        return 0;
    }
    index = g_encodedTextEntryState.value - 1;
    if (index < 23) {
        do {
            next = index + 1;
            g_encodedTextEntryState.text[index] = g_encodedTextEntryState.text[next];
            index = next;
        } while (index < 23);
    }
    g_encodedTextEntryState.value--;
    g_encodedTextEntryState.count--;
    return 0;
}

s32 Encoded_CheckEncodedText(u8 *input) {
    s32 index = 0;

    if ((s32)Libc_StringLength((const char *)input) != (s32)Libc_StringLength((const char *)g_encodedCheatCode)) {
        return 0;
    }
    for (; index < (s32)Libc_StringLength((const char *)input); index++) {
        if ((input[index] ^ index) != g_encodedCheatCode[index]) {
            return 0;
        }
    }
    return 1;
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const float g_Encoded_UpdateTextEntryCursorConstantWords[1] = {
    15.0f,
};
#endif

/* Points labelItem's label field at the entry of g_encodedCheatLabelTable_EncodedFindunlockedlevel that g_encodedCheatCharacterIndex selects when it is below 12, else at g_unlockedLevelResultLabel, and returns 0. */





extern u32 g_encodedCheatCharacterIndex;
extern MenuPointerEntry g_encodedCheatLabelTable[];


s32 Encoded_SetTextEntryResultLabel(MenuBuildEntry *labelItem) {
    if (g_encodedCheatCharacterIndex < 12) {
        labelItem->resource = (s32)(g_encodedCheatLabelTable[g_encodedCheatCharacterIndex].ptr);
    } else {
        labelItem->resource = (s32)(&g_unlockedLevelResultLabel);
    }
    return 0;
}

/* Steps index through the eleven entries (wrapping 10 to 0 and below 0 to 10), before the test when mode is 0 and after it otherwise, until one whose flag bit is set in g_menuOptionAvailabilityFlags; returns that index, or -1 after eleven tries. */
s32 Encoded_FindUnlockedLevel(s32 index, s32 step, s32 mode) {
    s32 i;
    s32 mask;
    s32 *flags;

    for (i = 0; i < 11; i++) {
        if (mode == 0) {
            index += step;
            if (index >= 11) {
                index = 0;
            } else if (index < 0) {
                index = 10;
            }
        }
        switch (index) {
        case 0:
        default:
            mask = 0x10000;
            break;
        case 1:
            mask = 0x20000;
            break;
        case 2:
            mask = 0x40000;
            break;
        case 3:
            mask = 0x80000;
            break;
        case 4:
            mask = 0x100000;
            break;
        case 5:
            mask = 0x200000;
            break;
        case 6:
            mask = 0x800000;
            break;
        case 7:
            mask = 0x400000;
            break;
        case 8:
            mask = 0x1000000;
            break;
        case 9:
            mask = 0x2000000;
            break;
        case 10:
            mask = 0x4000000;
            break;
        }
        flags = &g_gameSettings.unlockedLevels;
        if (*flags & mask) {
            return index;
        }
        if (mode != 0) {
            index += step;
            if (index >= 11) {
                index = 0;
            } else if (index < 0) {
                index = 10;
            }
        }
    }
    return -1;
}

#if defined(VERSION_US_REV1)
const float k_LevelGetselectedresourceidgermanEncodedWords[1] = {
    15.0f,
};
#endif

#if !(defined(VERSION_US_REV1))
/* Maps the state number g_encodedSelectedLevelIndex (0 to 10) to a fixed value through a jump table; anything else gives 1000. */
s32 Level_GetSelectedResourceIdGerman(void) {
    switch (g_encodedSelectedLevelIndex) {
    case 0:
    default:
        return 1000;
    case 1:
        return 2000;
    case 2:
        return 3000;
    case 3:
        return 4000;
    case 4:
        return 5000;
    case 5:
        return 6000;
    case 6:
        return 7401;
    case 7:
        return 7501;
    case 8:
        return 7601;
    case 9:
        return 7602;
    case 10:
        return 8000;
    }
}
#endif

#if defined(VERSION_EU)
extern unsigned int g_encodedLevelHandlersAndCheatTextEu[1];
#endif

#if defined(VERSION_US)
extern unsigned int g_encodedLevelHandlersAndCheatTextUs[1];
#endif

#if defined(VERSION_EU_X)
struct {
    unsigned int w0[3];
    unsigned char b1[168];
} g_encodedCheatTextAndHeaderEuX = {
    {
        0x00000000, 0x0000001E, 0x00000001,
    },
    {
        0x4A, 0x40, 0x4C, 0x46, 0x57, 0x52, 0x49, 0x49, 0x4C, 0x4C, 0x58, 0x4D, 0x59, 0x41, 0x59, 0x40,
        0x42, 0x5D, 0x56, 0x00, 0x42, 0x44, 0x55, 0x42, 0x56, 0x40, 0x49, 0x45, 0x44, 0x40, 0x5C, 0x42,
        0x43, 0x43, 0x47, 0x5C, 0x51, 0x45, 0x5A, 0x52, 0x5A, 0x51, 0x00, 0x00, 0x46, 0x53, 0x4D, 0x4C,
        0x50, 0x56, 0x52, 0x55, 0x41, 0x59, 0x4F, 0x00, 0x4C, 0x48, 0x45, 0x4B, 0x50, 0x56, 0x49, 0x52,
        0x5C, 0x00, 0x00, 0x00, 0x41, 0x40, 0x4A, 0x44, 0x4B, 0x4A, 0x00, 0x00, 0x48, 0x44, 0x47, 0x46,
        0x56, 0x40, 0x55, 0x4D, 0x5D, 0x48, 0x44, 0x00, 0x57, 0x49, 0x43, 0x57, 0x57, 0x44, 0x52, 0x42,
        0x50, 0x5D, 0x5F, 0x59, 0x49, 0x40, 0x4F, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x49, 0x46, 0x4D, 0x57,
        0x45, 0x47, 0x40, 0x46, 0x00, 0x00, 0x00, 0x00, 0x50, 0x48, 0x52, 0x50, 0x55, 0x50, 0x43, 0x46,
        0x43, 0x00, 0x00, 0x00, 0x53, 0x55, 0x4D, 0x4E, 0x54, 0x40, 0x4B, 0x00, 0x48, 0x4E, 0x4E, 0x42,
        0x57, 0x51, 0x4F, 0x44, 0x43, 0x4B, 0x45, 0x52, 0x00, 0x00, 0x00, 0x00, 0x55, 0x43, 0x47, 0x51,
        0x4A, 0x4A, 0x49, 0x43, 0x44, 0x4C, 0x00, 0x00,
    },
};
#endif

#if defined(VERSION_EU)
struct EncodedCheatText g_encodedCheatTextAndHeaderEu = {
    { 0xE9F63878, 0xE9F61471, 0xE9E30A66 },
    {
        0x4A, 0x40, 0x4C, 0x46, 0x57, 0x52, 0x49, 0x49, 0x4C, 0x4C, 0x58, 0x4D, 0x59, 0x41, 0x59, 0x40,
        0x42, 0x5D, 0x56, 0x00, 0x42, 0x44, 0x55, 0x42, 0x56, 0x40, 0x49, 0x45, 0x44, 0x40, 0x5C, 0x42,
        0x43, 0x43, 0x47, 0x5C, 0x51, 0x45, 0x5A, 0x52, 0x5A, 0x51, 0x00, 0x00, 0x46, 0x53, 0x4D, 0x4C,
        0x50, 0x56, 0x52, 0x55, 0x41, 0x59, 0x4F, 0x00, 0x4C, 0x48, 0x45, 0x4B, 0x50, 0x56, 0x49, 0x52,
        0x5C, 0x00, 0x00, 0x00, 0x41, 0x40, 0x4A, 0x44, 0x4B, 0x4A, 0x00, 0x00, 0x48, 0x44, 0x47, 0x46,
        0x56, 0x40, 0x55, 0x4D, 0x5D, 0x48, 0x44, 0x00, 0x57, 0x49, 0x43, 0x57, 0x57, 0x44, 0x52, 0x42,
        0x50, 0x5D, 0x5F, 0x59, 0x49, 0x40, 0x4F, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x49, 0x46, 0x4D, 0x57,
        0x45, 0x47, 0x40, 0x46, 0x00, 0x00, 0x00, 0x00, 0x50, 0x48, 0x52, 0x50, 0x55, 0x50, 0x43, 0x46,
        0x43, 0x00, 0x00, 0x00, 0x53, 0x55, 0x4D, 0x4E, 0x54, 0x40, 0x4B, 0x00, 0x48, 0x4E, 0x4E, 0x42,
        0x57, 0x51, 0x4F, 0x44, 0x43, 0x4B, 0x45, 0x52, 0x00, 0x00, 0x00, 0x00, 0x55, 0x43, 0x47, 0x51,
        0x4A, 0x4A, 0x49, 0x43, 0x44, 0x4C, 0x00, 0x00
    },
};
#endif

#if defined(VERSION_US)
struct EncodedCheatText g_encodedCheatTextAndHeaderUs = {
    {
        0x585F5649, 0x43544F52, 0x595F4755,
    },
    {
        0x4A, 0x40, 0x4C, 0x46, 0x57, 0x52, 0x49, 0x49, 0x4C, 0x4C, 0x58, 0x4D, 0x59, 0x41, 0x59, 0x40,
        0x42, 0x5D, 0x56, 0x00, 0x42, 0x44, 0x55, 0x42, 0x56, 0x40, 0x49, 0x45, 0x44, 0x40, 0x5C, 0x42,
        0x43, 0x43, 0x47, 0x5C, 0x51, 0x45, 0x5A, 0x52, 0x5A, 0x51, 0x00, 0x00, 0x46, 0x53, 0x4D, 0x4C,
        0x50, 0x56, 0x52, 0x55, 0x41, 0x59, 0x4F, 0x00, 0x4C, 0x48, 0x45, 0x4B, 0x50, 0x56, 0x49, 0x52,
        0x5C, 0x00, 0x00, 0x00, 0x41, 0x40, 0x4A, 0x44, 0x4B, 0x4A, 0x00, 0x00, 0x48, 0x44, 0x47, 0x46,
        0x56, 0x40, 0x55, 0x4D, 0x5D, 0x48, 0x44, 0x00, 0x57, 0x49, 0x43, 0x57, 0x57, 0x44, 0x52, 0x42,
        0x50, 0x5D, 0x5F, 0x59, 0x49, 0x40, 0x4F, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x49, 0x46, 0x4D, 0x57,
        0x45, 0x47, 0x40, 0x46, 0x00, 0x00, 0x00, 0x00, 0x50, 0x48, 0x52, 0x50, 0x55, 0x50, 0x43, 0x46,
        0x43, 0x00, 0x00, 0x00, 0x53, 0x55, 0x4D, 0x4E, 0x54, 0x40, 0x4B, 0x00, 0x48, 0x4E, 0x4E, 0x42,
        0x57, 0x51, 0x4F, 0x44, 0x43, 0x4B, 0x45, 0x52, 0x00, 0x00, 0x00, 0x00, 0x55, 0x43, 0x47, 0x51,
        0x4A, 0x4A, 0x49, 0x43, 0x44, 0x4C, 0x00, 0x00,
    },
};
#endif

#if !(defined(VERSION_DE))




static inline s32 levelBit_encodedHandleunlockedlevelselection(s32 level) {
    s32 bit;

    switch (level) {
    default:
    case 0:
        bit = 0x10000;
        break;
    case 1:
        bit = 0x20000;
        break;
    case 2:
        bit = 0x40000;
        break;
    case 3:
        bit = 0x80000;
        break;
    case 4:
        bit = 0x100000;
        break;
    case 5:
        bit = 0x200000;
        break;
    case 6:
        bit = 0x800000;
        break;
    case 7:
        bit = 0x400000;
        break;
    case 8:
        bit = 0x1000000;
        break;
    case 9:
        bit = 0x2000000;
        break;
    case 10:
        bit = 0x4000000;
        break;
    }
    return bit;
}


#endif

/* Resets g_encodedCheatCharacterIndex to -1. */
void Encoded_ResetTextEntryResult(void) {
    g_encodedCheatCharacterIndex = -1;
}

/* Checks the entered code g_encodedCheatCode against the twelve cheat codes of g_encodedCheatDefinitions (each stored with
   every character xored with its index): for each one that matches, ors its flags into the cheat word of g_gameSettings,
   copies them to g_persistedOptionUnlockFlags, records its index in g_encodedCheatCharacterIndex (-1 when none) and plays its sound. */
s32 Encoded_ApplyCheatCode(void)
{
    u32 i;
    s32 j;
    s32 match;
    s32 hasSound; /* the code's sound is read before the match index is stored */
    Shared_Game *settings;
    u8 *code;

    g_encodedCheatCharacterIndex = -1;
    for (i = 0; i < 12; i++) {
        code = g_encodedCheatDefinitions[i].code;
        j = 0;
        if ((s32)Libc_StringLength((const char *)code) != (s32)Libc_StringLength((const char *)g_encodedCheatCode)) {
            match = 0;
        } else {
            for (;;) {
                if (j < (s32)Libc_StringLength((const char *)code)) {
                    if ((code[j] ^ j) != g_encodedCheatCode[j]) {
                        match = 0;
                        break;
                    }
                    j++;
                } else {
                    match = 1;
                    break;
                }
            }
        }
        if (match) {
            g_gameSettings.unlockedLevels |= g_encodedCheatDefinitions[i].flags;
            settings = &g_gameSettings;
            do {
                g_persistedOptionUnlockFlags = settings->unlockedLevels;
            } while (0);
            hasSound = g_encodedCheatDefinitions[i].sound != 0;
            g_encodedCheatCharacterIndex = i;
            if (hasSound) {
                SoundElement_PlayFlatSound((s16)g_encodedCheatDefinitions[i].sound);
            }
        }
    }
    return 0;
}

/* Retained data for this translation unit. */
#if defined(VERSION_DE)
char g_encodedCheatTextWords[180] = "WRIILLXMYAY@J@LFWRIILLXMYAY@B]V\000BDUBV@IED@\\BCCG\\QEZRZQ\000\000FSMLPVRUAYO\000LHEKPVIR\\\000\000\000A@JDKJ\000\000HDGFV@UM]HD\000WICWWDRBP]_YI@O_\000\000\000\000IFMWEG@F\000\000\000\000PHRPUPCFC\000\000\000SUMNT@K\000HNNBWQODCKER\000\000\000\000UCGQJJICDL";
#endif
#if defined(VERSION_EU)
unsigned int g_encodedLevelHandlersAndCheatTextEu[1] = {
    0x4A0A6F4D,
};
#endif
#if defined(VERSION_US)
unsigned int g_encodedLevelHandlersAndCheatTextUs[1] = {
    0x00004B01,
};
#endif
