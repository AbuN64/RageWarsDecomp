#include "COMMON/OBJRECAT18V6.H"
#include "SYSTEM/TIMED_EFFECT_AND_ITEM_MENU_VIEWS.H"
#include "COMMON/SHAREDPLAYER.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/MATH_HELPERS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/ALFXPARAM.H"
#include <PR/os_internal_si.h>
#include "RENDER/SETN64_STARTSESSIONTHREADS.H"
#include "ITEMMENU.H"
#include "UI/X_FILES/X_PLUS.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "include_asm.h"

/* ITEMMENU.CPP */
/* 802A6AC0_4.CPP */
/* Steps a four-item toggle menu: counts frames, and once ItemMenu_IsSelectedEntryActive allows input opens the menu on button 0x20 or, on release, closes it after running the selected item's select callback (toggling it when that reports 1, or directly when it has none); each frame it settles every item's bounce animation toward zero, toggles the selected item off when an enabled item's update callback fails, advances the blink counter twice, and then either finishes opening, finishes closing, or moves the selection through ItemMenu_AdvanceSelection on buttons 0x100 and 0x200. Toggling an item starts its bounce at +5 with the current frame and its restore values, or at -5 when switching off. */

static inline void toggle(ToggleMenu *menu, MenuItem *item) {
    if ((item->on = !item->on) != 0) {
        item->bounce = 5;
        item->startFrame = menu->frame;
        item->value = item->restoreValue;
        item->extra = item->restoreExtra;
    } else {
        item->bounce = -5;
    }
}

void ItemMenu_UpdateToggleMenu(ToggleMenu *menu, ToggleMenuPlayerInputView *input) {
    s16 bounce;
    s32 i;
    menu->frame++;
    if (ItemMenu_IsSelectedEntryActive(menu) == 0) {
        return;
    }
    if (menu->state < 2) {
        if ((input->held & 0x20) && menu->state != 1) {
            menu->state = 1;
        }
    } else if (!(input->held & 0x20) && menu->state != 3) {
        menu->state = 3;
        if (menu->items[menu->selected].active != 0) {
            if (menu->items[menu->selected].select != 0) {
                if (menu->items[menu->selected].select(input, &menu->items[menu->selected]) == 1) {
                    toggle(menu, &menu->items[menu->selected]);
                }
            } else {
                toggle(menu, &menu->items[menu->selected]);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        bounce = RW_ABS(menu->items[i].bounce);
        if (bounce != 0) {
            if (bounce == menu->items[i].bounce) {
                menu->items[i].bounce--;
            } else {
                menu->items[i].bounce++;
            }
        }
        if (menu->items[i].active != 0 && menu->items[i].on != 0 && menu->items[i].update != 0 &&
            menu->items[i].update(input, &menu->items[i]) == 0) {
            toggle(menu, &menu->items[menu->selected]);
        }
    }
    if (++menu->blink >= 5) {
        menu->blink = -5;
    }
    if (++menu->blink >= 5) {
        menu->blink = -5;
    }
    if (menu->state == 1) {
        if (++menu->timer >= 5) {
            menu->state = 2;
        }
    } else if (menu->state == 3) {
        if (--menu->timer == 0) {
            menu->state = 0;
        }
    } else if (input->pressed & 0x100) {
        ItemMenu_AdvanceSelection((ItemMenuCursorState *)menu, 0);
    } else if (input->pressed & 0x200) {
        ItemMenu_AdvanceSelection((ItemMenuCursorState *)menu, 1);
    }
}

/* 802A6AC0_7.CPP */

/* Clears a record: its four 0x38-byte entries through an inline per-entry clear, its two leading
   flag bytes and trailing words, and sets the word at 0xE6 to -5. */
static inline void clear_entry(CItem *e) {
    e->state = 0;
    e->active = 0;
    e->generation = 0;
    e->transitionStep = 0;
    e->transitionFrame = 0;
}

/* Soft-resets the game: checks the "systembootdone" marker (copied from s_systembootdoneText and zero-padded with the memset XPlus_FillMemory) through SetN64_CompareByteStrings (recording the result in g_systemBootMarkerComparison and re-arming it through SetN64_CopyString_Itemmenu), and on a cold boot copies the resident code and data back from the cartridge word by word after each PI idle wait, then clears the BSS from g_graphicsTaskYieldBuffer to g_runtimeHeapStart, in both passes skipping the marker, its flag and, when not cold booting, the preserved save, settings and pad regions; finally reinitialises through osInitialize and SetN64_StartSessionThreads. */

extern char g_sceneCollisionStorage;

extern s32 g_graphicsTaskYieldBuffer;

extern s32 g_runtimeHeapStart;

extern void SetN64_CopyString(char *marker, char *name);

static inline s32 is_restorable(u32 address) {
    if (address >= (uintptr_t)&g_systemBootMarker && address < (uintptr_t)&g_systemBootMarker + 16) {
        return 0;
    }
    if (address == (uintptr_t)&g_systemBootMarkerComparison) {
        return 0;
    }
    if (g_systemBootMarkerComparison != 0) {
        return 1;
    }
    if (address >= (uintptr_t)&g_controllerActorSnapshot && address < (uintptr_t)&g_controllerActorSnapshot + 1072) {
        return 0;
    }
    if (address >= (uintptr_t)&g_gameSettings && address < (uintptr_t)&g_gameSettings + 1412) {
        return 0;
    }
    if (address >= (uintptr_t)&g_worldSnapshotNoteData && address < (uintptr_t)&g_worldSnapshotNoteData + 22528) {
        return 0;
    }
    if (address >= (uintptr_t)&g_sceneCollisionStorage && address < (uintptr_t)&g_sceneCollisionStorage + 0x5000) {
        return 0;
    }
    if (address >= (uintptr_t)&g_gameSettings + 1496 && address <= (uintptr_t)&g_gameSettings + 1672) {
        return 0;
    }
    return 1;
}

/* Draw active toggle-menu items in activation order, then draw the open menu
* with a pulsing highlight on its selected item. */
void ItemMenu_DrawEntries(ToggleMenu *panel, ToggleMenuPlayerInputView *player) {
    MenuItem *sorted[4];
    s32 width;
    s32 height;
    MenuItem *slot;
    MenuItem *first;
    MenuItem *second;
    f32 *view;
    s32 i;
    s32 swapped;
    s32 n;
    s16 magnitude;
    s32 pulse;
    s16 r, g, b;
    f32 spacing;
    f32 opacity;
    f32 sx, sy;
    f32 x, y;
    f32 unit;
    f32 colorScale;
    f32 fadeStep;
    f32 grid;
    f32 origin;
    s32 row;
    f32 factor;

    spacing = 0.0f;
    for (i = 0; i < 4; i++) {
        sorted[i] = &panel->items[i];
    }
    do {
        swapped = 0;
        for (i = 0; i < 3; i++) {
            first = sorted[i];
            second = sorted[i + 1];
            if ((u32)first->startFrame > (u32)second->startFrame) {
                swapped = 1;
                sorted[i] = second;
                sorted[i+1] = first;
            }
        }
    } while (swapped);
    r = g = b = 255;
    i = 0;
    n = i;
    colorScale = 255.0f;
    fadeStep = 0.1f;
    grid = 0.25f;
    origin = 0.75f;
    unit = 0.5f;

    view = player->view->viewport;
    sx = view[0] * 0.0015625f;
    sy = view[1] * 0.0020833334f;
    for (i = 0; i < 4; i++) {
        slot = sorted[i];
        magnitude = slot->bounce;
        if ((f32)magnitude < 0.0f) {
            magnitude = -magnitude;
        }
        if (slot->active && (slot->on || magnitude != 0)) {
            OnScreen_GetImageDimensions(slot->image, slot->imageFrame, &width, &height);
            if (width != 0) {
                opacity = (magnitude != slot->bounce ? (f32)magnitude : (f32)(5-magnitude)) * fadeStep;
                row = n;
                if (n < 0) {
                    row = n + 3;
                }
                row >>= 2;
                x = view[2] + view[0]*unit + ((origin - (f32)(n-row*4)*grid)+spacing)*unit*view[0];
                y = view[3] + view[1]*unit + (origin - (f32)(row))*unit*view[1];
                gDPSetEnvColor(g_displayListCursor++, r, g, b, opacity*colorScale);
                OnScreen_DrawSpriteResource(slot->image, slot->imageFrame,
                (s16)(s32)(x-(f32)width*sx*unit),
                (s16)(s32)(y-(f32)height*sy*unit), sx, sy, 1);
                if (magnitude != slot->bounce && opacity < grid) {
                    spacing += grid - opacity;
                }
                n++;
            }
        }
    }
    if (panel->state) {
        i = 0;
        n = i;
        unit = 0.5f;

        sx = view[0]*0.003125f;
        colorScale = (f32)(panel->timer*51);
        sy = view[1]*0.004166667f;
        for (i = 0; i < 4; i++) {
            slot = &panel->items[i];
            if (slot->active) {
                OnScreen_GetImageDimensions(slot->image, slot->imageFrame, &width, &height);
                if (width != 0) {
                    row = n;
                    if (n < 0) {
                        row = n + 3;
                    }
                    row >>= 2;
                    x = view[2]+view[0]*unit+((2.0f*(f32)(n-row*4)*0.25f)+-0.75f)*unit*view[0];
                    y = view[3]+view[1]*unit+((2.0f*(f32)(row))+-0.5f)*unit*view[1];
                    if (i == panel->selected) {
                        pulse = panel->blink;
                        factor = (f32)((((f32)pulse < 0.0f ? -pulse : pulse) * 191) / 5 + 64);
                        opacity = factor * 0.00390625f;
                        r = 255;
                        g = 255;
                        b = 255;
                    } else {
                        r = 128;
                        g = 128;
                        b = 128;
                        opacity = unit;
                    }
                    gDPSetEnvColor(g_displayListCursor++, r, g, b, opacity*colorScale);
                    n++;
                    OnScreen_DrawSpriteResource(slot->image, slot->imageFrame,
                    (s16)(s32)(x-(f32)width*sx*unit),
                    (s16)(s32)(y-(f32)height*sy*unit), sx, sy, 1);
                }
            }
        }
    }
}

void ItemMenu_ResetEntries(CItemMenu *rec) {
    int i;
    for (i = 0; i < 4; i++) {
        clear_entry(&rec->entries[i]);
    }
    rec->active = 0;
    rec->m_ModePos = 0;
    rec->m_LastItemPos = 0;
    rec->m_ItemAlphaFade = -5;
    rec->m_FrameCount = 0;
}

/* Finds or allocates one of four records and updates its parameters. */
s32 ItemMenu_SetEntry(char *menu, s32 entryValue, s32 entryKey, s32 imageResource, s32 imageFrame, f32 restoreValue, s32 restoreExtra, s32 selectCallbackAddress, s32 updateCallbackAddress) {
    s32 entryIndex;
    u32 key;
    char *entryStorage;
    CItem *unusedPointer;
    CItem *unusedPointer1;
    entryIndex = 0;
    key = entryKey & 0xFFFF;
    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
        if (((CItemMenu *)menu)->entries[entryIndex].active != 0 &&
            ((CItemMenu *)menu)->entries[entryIndex].key == key) {
            break;
        }
    }
    if (entryIndex == 4) {
        for (entryIndex = 0; entryIndex < 4; entryIndex++) {
            if (((CItemMenu *)menu)->entries[entryIndex].active == 0) {
                break;
            }
        }
        if (entryIndex == 4) {
            return 0;
        }
    }
    entryStorage = (char *)&((CItemMenu *)menu)->entries[entryIndex];
    ((CItemMenu *)menu)->m_LastItemPos = entryIndex;
    ((CItem *)(entryStorage))->active = 1;
    ((CItem *)(entryStorage))->resource = entryValue;
    ((CItem *)(entryStorage))->key = entryKey;
    ((CItem *)(entryStorage))->imageResource = imageResource;
    ((CItem *)(entryStorage))->imageFrameOrTextureHandle = imageFrame;
    ((CItem *)(entryStorage))->restoreValue = restoreValue;
    ((CItem *)(entryStorage))->restoreExtra = restoreExtra;
    ((CItem *)(entryStorage))->selectCallbackAddress = selectCallbackAddress;
    ((CItem *)(entryStorage))->generation = (u8) (((CItem *)(entryStorage))->generation + 1);
    ((CItem *)(entryStorage))->updateCallbackOrTextureId = updateCallbackAddress;
    return 1;
}

s32 ItemMenu_IsSelectedEntryActive(void *menu)
{
  s32 remainingEntries;
  s32 activeEntryCount;
  s8 *selectedEntry;
  activeEntryCount = 0;
  remainingEntries = 3;
  do
  {
    selectedEntry = ((s8 *)(menu + (((struct ItemMenuSelectionView *)menu)->id * sizeof(CItem)))) + ((char *)&((CItemMenu *)0)->entries - (char *)0);
    if ((*((s32 *) selectedEntry)) != 0)
    {
      activeEntryCount += 1;
    }
    remainingEntries -= 1;
  }
  while (remainingEntries >= 0);
  return activeEntryCount != 0;
}

/* Moves a menu's cursor at 0xE4 over its four 0x38-byte entries, forward when backward is zero and backward otherwise, wrapping around and skipping entries whose word at 0x4 is zero; returns the entry landed on. */
s32 ItemMenu_AdvanceSelection(ItemMenuCursorState *menu, s32 backward) {
    u16 cursor;
    if (backward == 0) {
        do {
            menu->cursor++;
            menu->cursor %= 4;
        } while (menu->entries[menu->cursor].active == 0);
        return menu->cursor;
    }
    do {
        cursor = --menu->cursor;
        if (cursor >= 4) {
            cursor = 3;
        }
        menu->cursor = cursor;
    } while (menu->entries[cursor].active == 0);
    return cursor;
}

void ItemMenu_ClearEntry(CItem *entry) {
    entry->state = 0;
    entry->active = 0;
    entry->generation = 0;
    entry->transitionStep = 0;
    entry->transitionFrame = 0;
}

void ItemMenu_ToggleEntry(void *entry, void *menu) {
    s32 enabled;
    enabled = (((struct ItemMenuToggleStateView *) ((s8 *) entry))->state) == 0;
    (((struct ItemMenuToggleStateView *) ((s8 *) entry))->state) = enabled;
    if (enabled != 0) {
        (((struct ItemMenuToggleStateView *) ((s8 *) entry))->transitionStep) = 5;
        (((struct ItemMenuToggleStateView *) ((s8 *) entry))->transitionFrame) = (s32) (((struct StateFrontendScrollResultsBackward *) ((s8 *) menu))->count);
        (((struct ItemMenuToggleStateView *) ((s8 *) entry))->value) = (f32) (((struct ItemMenuToggleStateView *) ((s8 *) entry))->restoreValue);
        (((struct ItemMenuToggleStateView *) ((s8 *) entry))->extra) = (s32) (((struct ItemMenuToggleStateView *) ((s8 *) entry))->restoreExtra);
        return;
    }
    (((struct ItemMenuToggleStateView *) ((s8 *) entry))->transitionStep) = -5;
}

s32 ItemMenu_RestoreBootMemory(void) {
    u32 *src;
    u32 *dst;
    s32 count;
    u32 status;
    u32 *piStatus;
    char name[16];
    *(MarkerItemMenuRestoreBootMemory *)name = s_systembootdoneText;
    XPlus_FillMemory(&name[15], 0, 1);
    if (((s32 (*)(char *, char *))SetN64_CompareByteStrings)(&g_systemBootMarker, name) == 0) {
        g_systemBootMarkerComparison = 0;
    } else {
        g_systemBootMarkerComparison = 1;
        SetN64_CopyString(&g_systemBootMarker, name);
    }
    if (g_systemBootMarkerComparison == 0) {
        src = (u32 *)0xB0001000;
        dst = (u32 *)0x80000400;
        piStatus = (u32 *)0xA4600010;
        count = 262143;
        do {
            status = *piStatus & 3;
            while (status != 0) {
            }
            if (is_restorable((u32)dst | 0x80000000)) {
                *dst = *src;
            }
            dst++;
            src++;
        } while (count-- != 0);
    }
    for (dst = (u32 *)&g_graphicsTaskYieldBuffer; (u32)dst < (uintptr_t)&g_runtimeHeapStart; dst++) {
        if (is_restorable((u32)dst | 0x80000000)) {
            *dst = 0;
        }
    }
    osInitialize();
    SetN64_StartSessionThreads();
    return 0;
}

void ItemMenu_RestoreBootMemoryNoOp(void) {
}

s32 ItemMenu_IsRestorableAddress(u32 address) {
    address |= 0x80000000;
    if (((address) >= (u32)&(g_systemBootMarker) && (address) < (u32)&(g_systemBootMarker) + (16)) || address == (uintptr_t)&g_systemBootMarkerComparison) {
        return 0;
    }
    if (g_systemBootMarkerComparison != 0) {
        return 1;
    }
    if (((address) >= (u32)&(g_controllerActorSnapshot) && (address) < (u32)&(g_controllerActorSnapshot) + (1072))) {
        return 0;
    }
    if (((address) >= (u32)&(g_gameSettings) && (address) < (u32)&(g_gameSettings) + (1412))) {
        return 0;
    }
    if (((address) >= (u32)&(g_worldSnapshotNoteData) && (address) < (u32)&(g_worldSnapshotNoteData) + (22528))) {
        return 0;
    }
    if (((address) >= (u32)&(g_sceneCollisionStorage) && (address) < (u32)&(g_sceneCollisionStorage) + (0x5000))) {
        return 0;
    }
    if (address >= (uintptr_t)&g_gameSettings.counters && address <= (uintptr_t)&g_gameSettings.counters + 176) {
        return 0;
    }
    return 1;
}

void ItemMenu_IsRestorableAddressNoOp(void) {
}

/* 800CB0A0.CPP */

/* G_SYSTEMBOOTDONETEXT.CPP */
#if !(defined(VERSION_US_REV1))
const char g_systembootdoneText[15] =
    "systembootdone\000";
#endif

#if defined(VERSION_EU_X)
unsigned char k_GSystembootdonetextEncodedBytesBlock1[1] = {
    0x20,
};
#endif

#if defined(VERSION_EU)
unsigned char k_GSystembootdonetextEncodedBytes[1] = {
    0xFF,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_systembootdoneText_GSystembootdonetext.c */
MarkerItemMenuRestoreBootMemory s_systembootdoneText = {
    "systembootdone",
};
#endif
