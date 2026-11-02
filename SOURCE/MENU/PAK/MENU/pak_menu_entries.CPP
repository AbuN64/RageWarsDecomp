#include "include_asm.h"
#include "MENU/PAK/pak_menu_entries.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "MENU/pak_menu_entries.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MENU/OPTION_AND_TEXT_LAYER_VIEWS.H"
#include "COMMON/MENU_UI_PROVIDERS.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

/* Moves a menu cursor through its entry table in one direction (16 to 19, reading the step byte at that offset of the current entry), wrapping at either end, recording the reverse step on the new entry when its flag allows, until it reaches an entry flagged 0x1800000 whose descriptor word at 0x1C is set. */






void Menu_MoveMenuCursor(struct MenuCursorNavigationView *menu, u8 dir) {
    struct PakMenuChoiceEntry *entry;
    s32 old;

    entry = &menu->entries[menu->cursor];
    do {
        old = menu->cursor;
        menu->cursor += ((s8 *)entry)[dir];
        if (menu->cursor < 0) {
            menu->cursor = menu->count - 1;
        } else if (menu->cursor >= menu->count) {
            menu->cursor = 0;
        }
        entry = &menu->entries[menu->cursor];
        old -= menu->cursor;
        switch (dir) {
        case 16:
            if (entry->flags & 0x80000) {
                entry->back[1] = old;
            }
            break;
        case 17:
            if (entry->flags & 0x40000) {
                entry->back[0] = old;
            }
            break;
        case 18:
            if (entry->flags & 0x200000) {
                entry->back[3] = old;
            }
            break;
        case 19:
            if (entry->flags & 0x100000) {
                entry->back[2] = old;
            }
            break;
        }
    } while ((entry->flags & 0x1800000) != 0x1800000 || entry->target->locked == 0);
}

/* Update entry callbacks, animate opening/closing, and handle the selected entry. */
extern f32 literals_Scene_GetPlatformRoutePoint;
extern const f32 g_pakMenuAnimationLimits[4];
extern f32 g_menuPanelOpenRate, g_menuPanelOpenLimit, g_menuPanelCloseRate;
typedef struct PakMenu PakMenu;
typedef struct PakEntry PakEntry;
typedef s32 (*PakEntryCallback)();
typedef struct PakEntryClass {
    u8 pad0[0x18];
    PakEntryCallback update; /* 0x18 */
    PakEntryCallback confirm; /* 0x1C */
} PakEntryClass;
struct PakEntry {
    u8 pad0[4];
    s16 type; /* 4 */
    u8 pad6[2];
    s32 flags; /* 8 */
    u8 padC[0xC];
    PakEntryClass *cls; /* 0x18 */
    s32 value; /* 0x1C */
    u8 pad20[8];
};
typedef struct PakMenuClass {
    u8 pad0[0x14];
    PakEntryCallback hold; /* 0x14 */
} PakMenuClass;
typedef struct PakInput {
    u8 pad0[0xB0];
    s32 buttons; /* 0xB0 */
} PakInput;
struct PakMenu {
    s16 selected; /* 0 */
    u8 pad2[10];
    PakEntry *entries; /* 0xC */
    s32 count; /* 0x10 */
    PakMenuClass *cls; /* 0x14 */
    u8 pad18[8];
    PakInput *input; /* 0x20 */
    u8 pad24[4];
    s16 state; /* 0x28 */
    u8 pad2A[2];
    f32 fade; /* 0x2C */
    f32 openA; /* 0x30 */
    f32 openB; /* 0x34 */
};
s32 Menu_UpdateMenuEntries(PakMenu *menu, void *context) {
    s32 closeRequested = 0;
    PakEntry *entry;
    s32 i;
    s32 selectionFlags;
    s32 allowRepeat;
    s32 buttons;
    s32 state;
    PakEntryCallback callback;
    callback = menu->cls->hold;
    if (callback != 0) {
        closeRequested = callback(menu, context);
    }
    i = menu->count;
    entry = menu->entries;
    while (--i != -1) {
        callback = entry->cls->update;
        if (callback != 0) {
            callback(entry, menu, context);
        }
        entry++;
    }
    entry = menu->entries + menu->selected;
    menu->fade += literals_Scene_GetPlatformRoutePoint;
    selectionFlags = entry->flags & 0x400000;
    Menu_StepSpriteFrame(menu);
    switch (menu->state) {
    case 0:
        menu->openA += literals_Scene_GetPlatformRoutePoint;
        if (menu->openA >= g_pakMenuAnimationLimits[0]) {
            menu->openA = g_pakMenuAnimationLimits[0];
            menu->state = 1;
        }
        break;
    case 1:
        menu->openB += literals_Scene_GetPlatformRoutePoint * g_menuPanelOpenRate;
        if (menu->openB >= g_menuPanelOpenLimit) {
            menu->openB = g_menuPanelOpenLimit;
            menu->state = 2;
        }
        break;
    case 3:
        menu->openB -= literals_Scene_GetPlatformRoutePoint * g_menuPanelCloseRate;
        if (menu->openB <= 0.0f) {
            menu->openB = 0.0f;
            menu->state = 4;
        }
        break;
    case 4:
        menu->openA -= literals_Scene_GetPlatformRoutePoint;
        if (menu->openA <= 0.0f) {
            menu->openA = 0.0f;
            return 1;
        }
        break;
    }
    state = menu->state;
    if (state >= 3) {
        return 0;
    }
    if (state < 0) {
        return 0;
    }
    if (closeRequested != 0) {
        menu->state = 4;
    }
    if (entry->flags & 8) {
        return 0;
    }
    allowRepeat = 1;
    if (entry->type == 2) {
        buttons = menu->input->buttons;
        if (buttons & 0x20202) {
            allowRepeat = 0;
            entry->value -= 2;
            if (entry->value < 0) {
                entry->value = 0;
            }
        } else if (buttons & 0x40101) {
            entry->value += 2;
            allowRepeat = 0;
            if (entry->value >= 256) {
                entry->value = 0xFF;
            }
        }
    }
    if (selectionFlags == 0) {
        if (Control_IsLeftPressed(menu->input) != 0) {
            Menu_MoveMenuCursor(menu, 16);
        }
        if (Control_IsRightPressed(menu->input) != 0) {
            Menu_MoveMenuCursor(menu, 17);
        }
    } else if (menu->input->buttons & 0x60303) {
        allowRepeat = 0;
    }
    if (allowRepeat != 0) {
        if (Control_IsNavUp(menu->input) != 0) {
            Menu_MoveMenuCursor(menu, 18);
        }
        if (Control_IsNavDown(menu->input) != 0) {
            Menu_MoveMenuCursor(menu, 19);
        }
    }
    if (menu->state != 2) {
        return 0;
    }
    if (Control_IsAButtonPressed(menu->input) != 0 ||
        (Control_IsLeftPressed(menu->input) != 0 && selectionFlags != 0) ||
        (Control_IsRightPressed(menu->input) != 0 && selectionFlags != 0)) {
        callback = entry->cls->confirm;
        if (callback != 0 && callback(entry, menu, context) == 0) {
            return 0;
        }
        menu->state = 3;
    }
    return 0;
}


extern void *Menu_GetListContext(s8 *);
extern void Menu_MeasureMenuText(TextBoundsText *, CItemInfo *);
extern u32 g_gameLoopFrameCount;

/* Lay out visible menu entries and draw their callbacks with a pulsing selection highlight. */
void Menu_DrawMenuEntries(struct MenuStyle *menu, s8 *member) {
    CItemInfo bounds, metrics, placed;
    TextBoundsData *data;
    TextBoundsText *entry;
    s32 i;
    f32 centerX, centerY, top, bottom, alpha;

    data = Menu_GetListContext(member);
    bounds.left = 1024;
    bounds.right = -1024;
    bounds.m_Top = 1024;
    bounds.m_Bottom = -1024;
    metrics.width = 0;
    metrics.height = 0;
    metrics.left = 0;
    metrics.right = 0;
    metrics.m_Top = 0;
    metrics.m_Bottom = 0;
    for (i = 0; i < menu->count; i++) {
        entry = &menu->entries[i];
        if (entry->flags & 0x800000) {
            if (entry->flags & 0x20000000) {
                metrics.left = 1024;
                metrics.right = -1024;
                metrics.m_Top = 1024;
                metrics.m_Bottom = -1024;
                metrics.width = 0;
                metrics.height = 0;
            } else {
                Menu_MeasureMenuText(entry, &metrics);
            }
            bounds.left = bounds.left < metrics.left ? bounds.left : metrics.left;
            bounds.right = bounds.right > metrics.right ? bounds.right : metrics.right;
            bounds.m_Top = bounds.m_Top < metrics.m_Top ? bounds.m_Top : metrics.m_Top;
            bounds.m_Bottom = bounds.m_Bottom > metrics.m_Bottom ? bounds.m_Bottom : metrics.m_Bottom;
        }
    }
    bounds.width = bounds.right - bounds.left;
    bounds.height = bounds.m_Bottom - bounds.m_Top;
    if (bounds.width < 0 || bounds.height < 0) {
        return;
    }
    centerX = data->x + data->width * 0.5f + menu->x;
    centerY = data->y + data->height * 0.5f + menu->y;
    bounds.left = centerX - bounds.width / 2;
    bounds.right = centerX + bounds.width / 2;
    bounds.m_Top = centerY - bounds.height / 2;
    bounds.m_Bottom = centerY + bounds.height / 2;
    metrics.width = 0;
    metrics.height = 0;
    metrics.left = 0;
    metrics.right = 0;
    metrics.m_Top = 0;
    metrics.m_Bottom = 0;
    g_multiplayerItemRenderState = -1;
    for (i = 0; i < menu->count; i++) {
        entry = &menu->entries[i];
        if (entry->flags & 0x800000) {
            metrics.entryIndex = i;
            if (entry->flags & 0x20000000) {
                Menu_MeasureMenuText(entry, &metrics);
                metrics.width = 0;
                metrics.height = 0;
                metrics.left = data->x;
                metrics.right = 0;
                metrics.m_Top = data->y;
                metrics.m_Bottom = 0;
            } else {
                Menu_MeasureMenuText(entry, &metrics);
            }
            placed = metrics;
            if (!(entry->flags & 0x20000000)) {
                placed.left += bounds.left;
                placed.right += bounds.left;
                placed.m_Top += bounds.m_Top;
                placed.m_Bottom += bounds.m_Top;
            }
            if (entry->flags & 1) {
                placed.left = centerX - metrics.width / 2;
                placed.right = placed.left + metrics.width;
            }
            if (entry->flags & 2) {
                placed.left = bounds.left;
                placed.right = placed.left + metrics.width;
            }
            if (entry->flags & 4) {
                placed.right = bounds.right;
                placed.left = placed.right - metrics.width;
            }
            if (entry->flags & 0x800000) {
                if (menu->state == i && entry->mode != 3 && !(entry->flags & 8)) {
                    top = placed.m_Top;
                    bottom = placed.m_Bottom;
                    /* Preserve the highlight extent calculation and its float rounding. */
                    bottom = top + (bottom - top);
                    OnScreen_SetupFillMode();
                    alpha = menu->alpha * menu->fade *
                        ((Gu_Sinf((f32)(g_gameLoopFrameCount * 10) * 0.017453294f) + 1.0f) * 50.0f + 50.0f);
                    if (entry->flags & 0x10) {
                        OnScreen_DrawBevelBox(placed.left - 4, top, placed.right + 4, bottom, 0, 0, 255, 0, 10, (u8)alpha);
                    } else {
                        OnScreen_DrawBevelBox(placed.left - 4, top, placed.right + 4, bottom, 0, 0, 255, 0, 10, (u8)alpha);
                    }
                    g_multiplayerItemRenderState = -1;
                }
                entry->handlers->draw(entry, &placed, &bounds, menu);
            }
        }
    }
}


#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/VIDEO_DIMENSIONS.H"
extern s32 g_hudReferenceViewportWidth;
extern TextBoundsFont g_menuFontStyles[];
/* The font a text entry's style bits select (the switch of Menu_DrawStyledMenuText). */
static __inline__ TextBoundsFont *textBoundsFont(TextBoundsText *text) {
    s32 style = 0;
    switch ((u32)text->flags & 0x3FE0) {
    case 32: style = 0; break;
    case 64: style = 1; break;
    case 128: style = 2; break;
    case 0x100: style = 3; break;
    case 0x200: style = 4; break;
    case 0x400: style = 5; break;
    case 0x800: style = 6; break;
    case 0x1000: style = 7; break;
    case 0x2000: style = 8; break;
    default: style = 0; break;
    }
    return &g_menuFontStyles[style];
}
/* Draws the dark backing panel behind a menu: as wide as the screen, centred on the menu's anchor, and as
 * tall as a fraction of the screen height less a margin. The relative pass places it above the anchor, the
 * other below. Measures every entry first and draws nothing when the menu has no extent. */
void Menu_DrawMenuPanel(StyledMenuTextPanel *menu, TextBoundsText *text, s32 relative) {
    TextBoundsData *data = menu->data;
    TextBoundsFont *font = textBoundsFont(text);
    CItemInfo panel;
    CItemInfo bounds;
    s32 i;
    f32 centerX;
    f32 height;
    s32 top;
    panel.left = 1024;
    panel.right = -1024;
    panel.m_Top = 1024;
    panel.m_Bottom = -1024;
    bounds.width = 0;
    bounds.height = 0;
    bounds.left = 0;
    bounds.right = 0;
    bounds.m_Top = 0;
    bounds.m_Bottom = 0;
    for (i = 0; i < menu->count; i++) {
        Menu_MeasureMenuText(&menu->entries[i], &bounds);
        panel.left = panel.left < bounds.left ? panel.left : bounds.left;
        panel.right = panel.right > bounds.right ? panel.right : bounds.right;
        panel.m_Top = panel.m_Top < bounds.m_Top ? panel.m_Top : bounds.m_Top;
        panel.m_Bottom = panel.m_Bottom > bounds.m_Bottom ? panel.m_Bottom : bounds.m_Bottom;
    }
    panel.width = panel.right - panel.left;
    panel.height = panel.m_Bottom - panel.m_Top;
    if (panel.width < 0 || panel.height < 0) {
        return;
    }
    centerX = data->x + data->width * 0.5f + menu->x;
    panel.width = SCREEN_WD;
    panel.left = centerX - panel.width / 2;
    panel.right = centerX + panel.width / 2;
    height = SCREEN_HT * 0.21621622f;
    if (SCREEN_HT >= 223) {
        height -= 13.0f;
    } else {
        height -= 9.0f;
    }
    if (relative != 0) {
        top = data->y + (f32)SCREEN_HT + menu->y - height;
    } else {
        top = data->y + menu->y;
    }
    panel.m_Top = top;
    panel.m_Bottom = top + height;
    panel.height = panel.m_Bottom - panel.m_Top;
    OnScreen_SetupFillMode();
    OnScreen_DrawBevelBox(panel.left, panel.m_Top, panel.right, panel.m_Bottom, 1, 0, 0, 0, 0, (u8)(u32)(menu->alpha * 192.0f));
}
