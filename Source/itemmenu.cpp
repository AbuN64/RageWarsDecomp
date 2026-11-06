#include "Common/hud_effects.h"
#include "System/timed_effect_and_item_menu_views.h"
#include "Common/sharedplayer.h"
#include <PR/gbi.h>
#include <platform_sdk.h>
#include "Common/math_helpers.h"
#include "Common/sessionhandlerrow.h"
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Common/runtime_declarations.h"
#include "Common/vector4f.h"
#include "Common/aiprofile.h"
#include "Common/gameplay_camera.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/alfxparam.h"
#include <PR/os_internal_si.h>
#include "Render/setn64_startsessionthreads.h"
#include "itemmenu.h"
#include "Ui/X_files/x_plus.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Common/snapshot_actor.h"
#include "include_asm.h"
#include "Constants/setup_updatenamecursor_data.h"
#include "Data/initialized_runtime_buffers.h"
#include "Render/setn64_updatefadetransition.h"
#include "itemmenu_symbols.h"

/* Steps a four-item toggle menu: counts frames, and once ItemMenu_IsSelectedEntryActive allows input opens the menu on button 0x20 or, on release, closes it after running the selected item's select callback (toggling it when that reports 1, or directly when it has none); each frame it settles every item's bounce animation toward zero, toggles the selected item off when an enabled item's update callback fails, advances the blink counter twice, and then either finishes opening, finishes closing, or moves the selection through ItemMenu_AdvanceSelection on buttons 0x100 and 0x200. Toggling an item starts its bounce at +5 with the current frame and its restore values, or at -5 when switching off. */

static inline void toggle(CItemMenu *menu, CItem *item) {
    if ((item->state = !item->state) != 0) {
        item->transitionStep = 5;
        item->transitionFrame = menu->m_FrameCount;
        item->value = item->restoreValue;
        item->extra = item->restoreExtra;
    } else {
        item->transitionStep = -5;
    }
}

void ItemMenu_UpdateToggleMenu(CItemMenu *menu, Player *input) {
    s16 bounce;
    s32 i;
    menu->m_FrameCount++;
    if (ItemMenu_IsSelectedEntryActive(menu) == 0) {
        return;
    }
    if (menu->active < 2) {
        if ((input->inputFlags & 0x20) && menu->active != 1) {
            menu->active = 1;
        }
    } else if (!(input->inputFlags & 0x20) && menu->active != 3) {
        menu->active = 3;
        if (menu->entries[menu->m_LastItemPos].active != 0) {
            if (menu->entries[menu->m_LastItemPos].selectCallbackAddress != 0) {
                if (((s32 (*)(void *, CItem *))menu->entries[menu->m_LastItemPos].selectCallbackAddress)(input, &menu->entries[menu->m_LastItemPos]) == 1) {
                    toggle(menu, &menu->entries[menu->m_LastItemPos]);
                }
            } else {
                toggle(menu, &menu->entries[menu->m_LastItemPos]);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        bounce = RW_ABS(menu->entries[i].transitionStep);
        if (bounce != 0) {
            if (bounce == menu->entries[i].transitionStep) {
                menu->entries[i].transitionStep--;
            } else {
                menu->entries[i].transitionStep++;
            }
        }
        if (menu->entries[i].active != 0 && menu->entries[i].state != 0 && menu->entries[i].updateCallbackOrTextureId != 0 &&
            ((s32 (*)(void *, CItem *))menu->entries[i].updateCallbackOrTextureId)(input, &menu->entries[i]) == 0) {
            toggle(menu, &menu->entries[menu->m_LastItemPos]);
        }
    }
    if (++menu->m_ItemAlphaFade >= 5) {
        menu->m_ItemAlphaFade = -5;
    }
    if (++menu->m_ItemAlphaFade >= 5) {
        menu->m_ItemAlphaFade = -5;
    }
    if (menu->active == 1) {
        if (++menu->m_ModePos >= 5) {
            menu->active = 2;
        }
    } else if (menu->active == 3) {
        if (--menu->m_ModePos == 0) {
            menu->active = 0;
        }
    } else if (input->actionFlags & 0x100) {
        ItemMenu_AdvanceSelection(menu, 0);
    } else if (input->actionFlags & 0x200) {
        ItemMenu_AdvanceSelection(menu, 1);
    }
}

/* Clears a record: its four 0x38-byte entries through an inline per-entry clear, its two leading
   flag bytes and trailing words, and sets the word at 0xE6 to -5. */
static inline void clearEntry(CItem *e) {
    e->state = 0;
    e->active = 0;
    e->generation = 0;
    e->transitionStep = 0;
    e->transitionFrame = 0;
}

/* Soft-resets the game: checks the "systembootdone" marker (copied from s_systembootdoneText and zero-padded with the memset XPlus_FillMemory) through SetN64_CompareByteStrings (recording the result in g_systemBootMarkerComparison and re-arming it through SetN64_CopyString_Itemmenu), and on a cold boot copies the resident code and data back from the cartridge word by word after each PI idle wait, then clears the BSS from g_graphicsTaskYieldBuffer to g_runtimeHeapStart, in both passes skipping the marker, its flag and, when not cold booting, the preserved save, settings and pad regions; finally reinitialises through osInitialize and SetN64_StartSessionThreads. */
static inline s32 isRestorable(u32 address) {
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
void ItemMenu_DrawEntries(CItemMenu *panel, Player *player) {
    CItem *sorted[4];
    s32 width;
    s32 height;
    CItem *slot;
    CItem *first;
    CItem *second;
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
        sorted[i] = &panel->entries[i];
    }
    do {
        swapped = 0;
        for (i = 0; i < 3; i++) {
            first = sorted[i];
            second = sorted[i + 1];
            if ((u32)first->transitionFrame > (u32)second->transitionFrame) {
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

    view = &player->camera->viewWidth;
    sx = view[0] * 0.0015625f;
    sy = view[1] * 0.0020833334f;
    for (i = 0; i < 4; i++) {
        slot = sorted[i];
        magnitude = slot->transitionStep;
        if ((f32)magnitude < 0.0f) {
            magnitude = -magnitude;
        }
        if (slot->active && (slot->state || magnitude != 0)) {
            OnScreen_GetImageDimensions(slot->imageResource, slot->imageFrameOrTextureHandle, &width, &height);
            if (width != 0) {
                opacity = (magnitude != slot->transitionStep ? (f32)magnitude : (f32)(5-magnitude)) * fadeStep;
                row = n;
                if (n < 0) {
                    row = n + 3;
                }
                row >>= 2;
                x = view[2] + view[0]*unit + ((origin - (f32)(n-row*4)*grid)+spacing)*unit*view[0];
                y = view[3] + view[1]*unit + (origin - (f32)(row))*unit*view[1];
                gDPSetEnvColor(g_displayListCursor++, r, g, b, opacity*colorScale);
                OnScreen_DrawSpriteResource(slot->imageResource, slot->imageFrameOrTextureHandle,
                (s16)(s32)(x-(f32)width*sx*unit),
                (s16)(s32)(y-(f32)height*sy*unit), sx, sy, 1);
                if (magnitude != slot->transitionStep && opacity < grid) {
                    spacing += grid - opacity;
                }
                n++;
            }
        }
    }
    if (panel->active) {
        i = 0;
        n = i;
        unit = 0.5f;

        sx = view[0]*0.003125f;
        colorScale = (f32)(panel->m_ModePos*51);
        sy = view[1]*0.004166667f;
        for (i = 0; i < 4; i++) {
            slot = &panel->entries[i];
            if (slot->active) {
                OnScreen_GetImageDimensions(slot->imageResource, slot->imageFrameOrTextureHandle, &width, &height);
                if (width != 0) {
                    row = n;
                    if (n < 0) {
                        row = n + 3;
                    }
                    row >>= 2;
                    x = view[2]+view[0]*unit+((2.0f*(f32)(n-row*4)*0.25f)+-0.75f)*unit*view[0];
                    y = view[3]+view[1]*unit+((2.0f*(f32)(row))+-0.5f)*unit*view[1];
                    if (i == panel->m_LastItemPos) {
                        pulse = panel->m_ItemAlphaFade;
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
                    OnScreen_DrawSpriteResource(slot->imageResource, slot->imageFrameOrTextureHandle,
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
        clearEntry(&rec->entries[i]);
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
    CItem *entry;
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
    entry = &((CItemMenu *)menu)->entries[entryIndex];
    ((CItemMenu *)menu)->m_LastItemPos = entryIndex;
    entry->active = 1;
    entry->resource = entryValue;
    entry->key = entryKey;
    entry->imageResource = imageResource;
    entry->imageFrameOrTextureHandle = imageFrame;
    entry->restoreValue = restoreValue;
    entry->restoreExtra = restoreExtra;
    entry->selectCallbackAddress = selectCallbackAddress;
    entry->generation = (u8) (entry->generation + 1);
    entry->updateCallbackOrTextureId = updateCallbackAddress;
    return 1;
}

s32 ItemMenu_IsSelectedEntryActive(void *menu)
{
  s32 remainingEntries;
  s32 activeEntryCount;
  CItem *selectedEntry;
  activeEntryCount = 0;
  remainingEntries = 3;
  do
  {
    selectedEntry = ((s8 *)(menu + (((CItemMenu *)menu)->m_LastItemPos * sizeof(CItem)))) + ((char *)&((CItemMenu *)0)->entries - (char *)0);
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
s32 ItemMenu_AdvanceSelection(CItemMenu *menu, s32 backward) {
    u16 cursor;
    if (backward == 0) {
        do {
            menu->m_LastItemPos++;
            menu->m_LastItemPos %= 4;
        } while (menu->entries[menu->m_LastItemPos].active == 0);
        return menu->m_LastItemPos;
    }
    do {
        cursor = --menu->m_LastItemPos;
        if (cursor >= 4) {
            cursor = 3;
        }
        menu->m_LastItemPos = cursor;
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

/* Flips an entry between enabled and disabled. Enabling starts a fade-in from the menu's current
   count and restores the saved value and extra; disabling starts the fade-out. */
void ItemMenu_ToggleEntry(void *entryAddress, void *menuAddress) {
    struct ItemMenuToggleStateView *entry = (struct ItemMenuToggleStateView *)entryAddress;
    struct StateFrontendScrollResultsBackward *menu = (struct StateFrontendScrollResultsBackward *)menuAddress;
    s32 enabled;
    enabled = (((CItem *) ((s8 *) entry))->state) == 0;
    (((CItem *) ((s8 *) entry))->state) = enabled;
    if (enabled != 0) {
        (((CItem *) ((s8 *) entry))->transitionStep) = 5;
        (((CItem *) ((s8 *) entry))->transitionFrame) = (s32) (((CItemMenu *) ((s8 *) menu))->m_FrameCount);
        (((CItem *) ((s8 *) entry))->value) = (f32) (((CItem *) ((s8 *) entry))->restoreValue);
        (((CItem *) ((s8 *) entry))->extra) = (s32) (((CItem *) ((s8 *) entry))->restoreExtra);
        return;
    }
    (((CItem *) ((s8 *) entry))->transitionStep) = -5;
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
    if (((s32 (*)(char *, char *))SetN64_CompareByteStrings)(g_systemBootMarker, name) == 0) {
        g_systemBootMarkerComparison = 0;
    } else {
        g_systemBootMarkerComparison = 1;
        SetN64_CopyString(g_systemBootMarker, name);
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
            if (isRestorable((u32)dst | 0x80000000)) {
                *dst = *src;
            }
            dst++;
            src++;
        } while (count-- != 0);
    }
    for (dst = (u32 *)&g_graphicsTaskYieldBuffer; (u32)dst < (uintptr_t)&g_runtimeHeapStart; dst++) {
        if (isRestorable((u32)dst | 0x80000000)) {
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

#if !(defined(VERSION_US_REV1))
const char g_systembootdoneText[15] =
    "systembootdone\000";
#endif

#if defined(VERSION_EU_X)
extern unsigned char k_gSystembootdonetextFragment[1];
#endif

#if defined(VERSION_EU)
extern unsigned char k_GSystembootdonetextEncodedBytes[1];
#endif

#if defined(VERSION_US_REV1)
MarkerItemMenuRestoreBootMemory s_systembootdoneText = {
    "systembootdone",
};
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* String and constant data used by the itemmenu module. */
extern float g_itemmenuFloatPair[2];
extern char g_itemmenuTextLayecProjectsDmN64Source[44];
extern char g_itemmenuTextPthisNull[16];
extern char g_itemmenuTextPplayerNull[16];
extern char g_itemmenuTextCitemmenuCheckforuseditemslotsPthisTrue[48];
extern char g_itemmenuTextDirectionCitemmenuDirectionPrev[40];
extern char g_itemmenuTextPthis[8];
extern char g_itemmenuTextPplayer[8];
extern char g_itemmenuTextPcamera[8];
#endif
