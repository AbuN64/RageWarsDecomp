#include "LIBC.H"
#include "include_asm.h"
#include "Common/pakqueuestate.h"
#include "Render/resident_texture_menu_views.h"
#include "Engine/tengine.h"
#include "Engine/cache.h"
#if defined(VERSION_US_REV1)
#endif
#if defined(VERSION_US_REV1)
#include "Common/residentstate.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/runtime_declarations.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/world.h"
#endif
#if defined(VERSION_US_REV1)
#include "Render/setn64_getpacksection.h"
#endif
#if defined(VERSION_US_REV1)
#include "Scene/cache_requestresource.h"
#endif
#if defined(VERSION_US_REV1)
#include "Scene/cache_allocateresourceat.h"
#endif
#if defined(VERSION_US_REV1)
#include "AUDIO/sprintf.H"
#endif
#if defined(VERSION_US_REV1)
#include "types.h"
#include "Engine/cache.h"
#endif
#if defined(VERSION_US_REV1)
#include <platform_sdk.h>
#endif
#if defined(VERSION_US_REV1)
#include "Engine/session.h"
#endif
#if defined(VERSION_US_REV1)
#include "Tengine/s_artsendactivatedtext.h"
#endif
#if defined(VERSION_US_REV1)
#include "Tengine/s_artsenddeactivatedtext.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/effectrender.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/aiprofile.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/resident_event_handler.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/sharedtrackobjectprefix.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/scene_frame_and_effect_updates.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/font_style_and_glyph_operations.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/texture_request.h"
#endif
#if defined(VERSION_US_REV1)
#include "Engine/Audio/channel.h"
#endif
#include "Common/residentstate.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/texture_request.h"
#include "Tengine/s_artsendactivatedtext.h"
#include "Common/rotation_extraction.h"
#include "Tengine/s_artsenddeactivatedtext.h"

/* TENGINE.CPP */

#if defined(VERSION_US_REV1)

/* Separate-object views of the menu state words. */
/* Releases the previous texture viewer entry, loads entry g_artsendTextureViewer.selectionIndex from the resident pack,
   wraps the frame selection into its texture/palette tables and prints the "tex N frm F of C" title. */
void Tengine_LoadSelectedTexture(void) {
    u32 size;
    u32 key;
    struct CacheResourceNode *resource;
    s32 *entries;
    s32 *textures;
    s32 *palettes;
    s32 texture;
    s32 palette;
    s32 frame;
    u8 *name;
    s32 i;
    Shared_World *world = &g_world;

    if (g_artsendTextureViewer.resource != 0) {
        Cache_UnlockResource(NULL, g_artsendTextureViewer.resource);
    }
    g_artsendTextureViewer.resource = 0;
    g_artsendTextureResetWordA = 0;
    g_artsendTextureResetWordB = 0;
    g_artsendActionMappingSelection = 0;
    key = SetN64_LocatePackSection(world->textureDirectory, world->textureBank, g_artsendTextureViewer.selectionIndex, &size);
    resource = Cache_RequestResource(0, key - 1, key, size, 9, -1, &g_artsendTextureResourceCallback, "Artsend Texture", 1);
    entries = (s32 *)resource->data;
    textures = SetN64_GetPackSection(entries, 1);
    palettes = SetN64_GetPackSection(entries, 2);
    while (g_artsendTextureViewer.selectionValue < 0) {
        g_artsendTextureViewer.selectionValue += *textures;
    }
    texture = g_artsendTextureViewer.selectionValue % *textures;
    palette = g_artsendTextureViewer.selectionValue % *palettes;
    g_artsendTextureViewer.resource = resource;
    g_artsendTextureViewer.textureOverride = SetN64_GetPackSection(textures, texture);
    g_artsendTextureViewer.paletteOverride = SetN64_GetPackSection(palettes, palette);
    g_artsendTextureViewer.selector = SetN64_GetPackSection(entries, 0);
    g_artsendTextureViewer.overridesOff = 0;
    g_artsendTextureViewer.entryTable = entries;
    g_artsendTextureViewer.textureTable = textures;
    g_artsendTextureViewer.paletteTable = palettes;
    frame = texture;
    if (*entries == 4) {
        name = SetN64_GetPackSection(entries, 3);
        for (i = 0; i < (s32)Libc_StringLength((const char *)name); i++) {
            if (name[i] == '.') {
                name[i] = '\0';
                break;
            }
        }
        Libc_FormatString(g_artsendTextureViewer.displayData, "tex %d frm %d of %d, %s", g_artsendTextureViewer.selectionIndex, frame,
                         *textures, name);
    } else {
        Libc_FormatString(g_artsendTextureViewer.displayData, "tex %d frm %d of %d", g_artsendTextureViewer.selectionIndex, texture,
                         *textures);
    }
    g_artsendTextureViewer.frameCount = 0;
}
#endif

#if defined(VERSION_US_REV1)
/* Handles repeated menu navigation inputs and draws the current menu display.
 * The index/value/changed words form the contiguous selection record; named globals
 * and owner fields provide views of that same menu state. */

struct ArtsendTextureSelection;

void Tengine_UpdateArtsendTexturePreview(void) {
    f32 scale;
    s32 wrappedSelection;
    s32 regpartTempA0;
    s32 count0;
    s32 count1;
    s32 count2;
    s32 count3;
    s32 count4;
    s32 count5;
    s32 unusedSelectionValue;
    s32 previousTextureWrappedInput;
    s32 previousPageWrappedInput;
    s32 previousFrameHold;
    s32 unusedPageIndex;
    s32 nextFrameHold;
    s32 previousTextureHold;
    s32 nextTextureHold;
    s32 nextTextureIndex;
    s32 unusedTextureIndex;
    s32 previousPageHold;
    s32 nextPageHold;
    s32 nextPageIndex;
    s32 previousTextureIndex;
    s32 previousPageIndex;
    s32 minusOne;
    struct ArtsendTextureSelection *selection;

    if (g_textureVariationBypassEnabled != 0) {
        if (g_controllerProfiles[0].buttons & 0x10) {
            if (g_artsendToggleButtonHeld == 0) {
                if (g_artsendTextureViewer.alternateTitle == 0) {
                    Camera_PostScreenMessage(&g_frontendScreenStatus, &g_frontendScreenStatus.fallbackCamera, s_artsendActivatedText);
                    g_artsendTextureViewer.titleWasShown = 1;
                } else {
                    Camera_PostScreenMessage(&g_frontendScreenStatus, &g_frontendScreenStatus.fallbackCamera, s_artsendDeactivatedText);
                }
                g_artsendToggleButtonHeld = 1;
                g_artsendTextureViewer.alternateTitle = (u8) ((u8) g_artsendTextureViewer.alternateTitle < 1U);
            }
        } else {
            g_artsendToggleButtonHeld = 0;
        }
        if (g_controllerProfiles[0].buttons & 0x2000) {
            if (g_controllerProfiles[0].buttons & 0x200) {
                count0 = g_artsendPreviousFrameHoldCount;
                previousFrameHold = count0;
                count0 += 1;
                g_artsendPreviousFrameHoldCount = count0;
                if (previousFrameHold >= 3) {
                    g_artsendTextureSelectionChanged = 1;
                    g_artsendPreviousFrameHoldCount = 0;
                    g_artsendTextureFrameSelection -= 1;
                }
            }
            if (g_controllerProfiles[0].buttons & 0x100) {
                count1 = g_artsendNextFrameHoldCount;
                nextFrameHold = count1;
                count1 += 1;
                g_artsendNextFrameHoldCount = count1;
                if (nextFrameHold >= 3) {
                    g_artsendTextureSelectionChanged = 1;
                    g_artsendNextFrameHoldCount = 0;
                    g_artsendTextureFrameSelection += 1;
                }
            }
        } else {
            if (g_controllerProfiles[0].buttons & 0x200) {
                count2 = g_artsendPreviousTextureHoldCount;
                previousTextureHold = count2;
                count2 += 1;
                g_artsendPreviousTextureHoldCount = count2;
                if (previousTextureHold >= 3) {
                    minusOne = g_artsendTextureSelectionIndex;
                    minusOne -= 1;
                    previousTextureWrappedInput = minusOne + g_artsendTextureSelection.count;
                    previousTextureIndex = previousTextureWrappedInput % g_artsendTextureSelection.count;
                    g_artsendTextureViewer.titleWasShown = 1;
                    ((struct ArtsendTextureSelection *)&g_artsendTextureSelectionIndex)->index = minusOne;
                    g_artsendTextureSelectionIndex = previousTextureIndex;
                    if ((f32) previousTextureIndex < 0.0f) {
                        previousTextureIndex = -previousTextureIndex;
                    }
                    g_artsendTextureViewer.selectionIndex = previousTextureIndex;
                    g_artsendPreviousTextureHoldCount = 0;
                }
            }
            if (g_controllerProfiles[0].buttons & 0x100) {
                count3 = g_artsendNextTextureHoldCount;
                nextTextureHold = count3;
                count3 += 1;
                g_artsendNextTextureHoldCount = count3;
                if (nextTextureHold >= 3) {
                    nextTextureIndex = g_artsendTextureSelectionIndex + 1;
                    wrappedSelection = nextTextureIndex % g_artsendTextureSelection.count;
                    g_artsendNextTextureHoldCount = 0;
                    g_artsendTextureSelectionChanged = 1;
                    g_artsendTextureViewer.selectionIndex = nextTextureIndex;
                    g_artsendTextureSelectionIndex = wrappedSelection;
                }
            }
            if (g_controllerProfiles[0].buttons & 0x400) {
                count4 = g_artsendPreviousPageHoldCount;
                previousPageHold = count4;
                count4 += 1;
                g_artsendPreviousPageHoldCount = count4;
                if (previousPageHold >= 3) {
                    regpartTempA0 = g_artsendTextureSelectionIndex - 5;
                    previousPageWrappedInput = regpartTempA0 + g_artsendTextureSelection.count;
                    previousPageIndex = previousPageWrappedInput % g_artsendTextureSelection.count;
                    g_artsendTextureViewer.selectionIndex = regpartTempA0;
                    selection = (struct ArtsendTextureSelection *)&g_artsendTextureSelectionIndex;
                    g_artsendTextureSelectionIndex = previousPageIndex;
                    if ((f32) previousPageIndex < 0.0f) {
                        previousPageIndex = -previousPageIndex;
                    }
                    selection->index = previousPageIndex;
                    selection->changed = 1;
                    g_artsendPreviousPageHoldCount = 0;
                }
            }
            if (g_controllerProfiles[0].buttons & 0x800) {
                count5 = g_artsendNextPageHoldCount;
                nextPageHold = count5;
                count5 += 1;
                g_artsendNextPageHoldCount = count5;
                if (nextPageHold >= 3) {
                    nextPageIndex = g_artsendTextureSelectionIndex + 5;
                    wrappedSelection = nextPageIndex % g_artsendTextureSelection.count;
                    g_artsendNextPageHoldCount = 0;
                    g_artsendTextureSelectionChanged = 1;
                    g_artsendTextureViewer.selectionIndex = nextPageIndex;
                    g_artsendTextureSelectionIndex = wrappedSelection;
                }
            }
        }
        g_artsendTextureViewer.frameCount += 1;
        if (g_artsendTextureViewer.titleWasShown != 0) {
            Tengine_LoadSelectedTexture();
            g_artsendTextureViewer.titleWasShown = 0;
        }
        OnScreen_SetupTextRendering();
        scale = g_artsendTextureTitleScale;
        OnScreen_LoadTextTileModeOne();
        OnScreen_SetTextScale(scale, scale);
        OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
        Onscrn_DrawText(g_artsendTextureViewer.displayData, 16, g_hudReferenceViewportHeight - 48, 0xFF, 0, 0, scale, scale);
    }
}
#endif

/* TENGINE_QUERYARTSENDOVERRIDE.CPP */

#if defined(VERSION_US_REV1)





/** Decode a frontend input selector into its current button mask. */
s32 Tengine_QueryArtsendOverride(s32 overrideSelector) {
    if (g_textureVariationBypassEnabled == 0) {
        goto zero;
    }

    {
        s32 swOuterValue = overrideSelector;
        swOuterValue -= (257);
        if ((unsigned int)swOuterValue > 5) {
            goto sw_outer_default;
        }
        switch (swOuterValue) {
        case 0: goto sw_outer_0x101;
        case 1: goto sw_outer_0x102;
        case 2: goto sw_outer_0x103;
        case 3: goto sw_outer_0x104;
        case 4: goto sw_outer_0x105;
        case 5: goto sw_outer_0x106;
        }
    }
    do {
    sw_outer_0x101:
        return (s32)g_artsendTextureViewer.textureOverride;
    sw_outer_0x102:
        return (s32)g_artsendTextureViewer.paletteOverride;
    sw_outer_0x103:
        return 1 << g_artsendTextureViewer.selector->primaryButton;
    sw_outer_0x104:
        return 1 << g_artsendTextureViewer.selector->secondaryButton;
    sw_outer_0x105:
        {
        s32 swInnerValue = g_artsendTextureViewer.selector->mode;
        if ((unsigned int)swInnerValue > 5) {
            goto zero;
        }
        switch (swInnerValue) {
        case 0: goto sw_inner_0;
        case 1: goto sw_inner_1;
        case 2: goto sw_inner_2;
        case 3: goto sw_inner_1;
        case 4: goto sw_inner_4;
        case 5: goto sw_inner_1;
        }
    }
    do {
        sw_inner_0:
            return 8;
        sw_inner_1:
        sw_inner_3:
        sw_inner_5:
            return 4;
        sw_inner_2:
            return 32;
        sw_inner_4:
            return 16;
    } while (0);
    sw_outer_0x106:
        g_artsendTextureViewer.overridesOff = 1;
zero:
        return 0;
    sw_outer_default:
        return 0;
    } while (0);
}
#endif

/* S_ARTSENDACTIVATEDTEXT.CPP */

#if defined(VERSION_US_REV1)
extern const char s_artsendActivatedText[18];
#endif

/* S_ARTSENDDEACTIVATEDTEXT.CPP */

#if defined(VERSION_US_REV1)
extern const char s_artsendDeactivatedText[20];
#endif

/* TENGINE_UPDATEARTSENDTEXTUREPREVIEW_DATA.CPP */

#if defined(VERSION_US_REV1)

#endif

/* Retained data for this translation unit. */
#if defined(VERSION_US_REV1)
const float g_artsendTexturePreviewUnitScale[1] = {
    1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const char s_artsendActivatedText[18] = "Artsend Activated";
#endif
#if defined(VERSION_US_REV1)
const char s_artsendDeactivatedText[20] = "Artsend Deactivated";
#endif
