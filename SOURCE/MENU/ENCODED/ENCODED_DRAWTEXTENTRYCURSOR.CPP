#include "../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/CHEATCODE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "TYPES.H"
#include "COMMON/MENU_UI_PROVIDERS.H"
extern Shared_Entry g_encodedTextEntryState;
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

extern PaddedFloatView *Menu_GetWidgetStyle(void *, s32);

extern void Menu_DrawLocalizedMenuItemText(struct Field *object, s32 second, s32 third, s32 fourth);

/* Steps the menu spinner in g_encodedTextEntryState: advances its repeat timer by g_frameElapsedTime, wrapping at the second entry of g_encodedTextCursorTiming, and while the menu is active (state 2) decrements its value above zero when Control_IsLeftPressed reports the decrease input, or else increments it below its maximum when Control_IsRightPressed reports the increase input, restarting the timer on a change. Returns zero. */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif

/* Shifts the input history, appends the current byte, and advances the history counters. */

extern u32 g_encodedCheatCharacterIndex;

/* Checks whether the input matches the indexed, XOR-masked reference string. */



extern u8 g_encodedCheatCode[100];

/* Draws the g_encodedTextEntryState spinner: during the first part of its blink period it fills a two-pixel white bar below the item under the digit its value selects, placed from the item's x by the character width Menu_GetWidgetStyle_EncodedDrawtextentrycursor reports scaled to the screen, with the style's alpha, through OnScreen_SetupFillMode and OnScreen_DrawBevelBox; then draws the item through Menu_DrawLocalizedMenuItemText. */
void Encoded_DrawTextEntryCursor(void *menu, MenuLocalizedTextItemView *item, void *third, MenuStyle *style) {
    f32 width;
    f32 alpha;
    s32 x;
    unsigned int bits;

    if (g_encodedTextEntryState.timer <= (6.0f)) {
        width = Menu_GetWidgetStyle(menu, 0)->value * (f32)g_hudReferenceViewportWidth * (0.0035211266949772835f);
        x = (f32)item->x + (f32)g_encodedTextEntryState.value * width;
        g_multiplayerItemRenderState = -1;
        alpha = style->alpha * (style->fade * (128.0f));
        OnScreen_SetupFillMode();
        OnScreen_DrawBevelBox(x, item->y, (f32)x + width, item->y + 2, 0, 0, 0xFF, 0xFF, 0xFF,
                      (u8)(bits = !((2147483648.0f) <= alpha) ? (s32)alpha : (bits = (s32)(alpha - (2147483648.0f))) | 0x80000000));
    }
    Menu_DrawLocalizedMenuItemText(menu, item, third, style);
}

s32 Encoded_UpdateTextEntryCursor(void *unused, CheatMenuInputView *menu) {
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
