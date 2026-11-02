#include "../../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "COMMON/PAKQUEUESTATE.H"
#include "RENDER/RESIDENT_TEXTURE_MENU_VIEWS.H"
#include "ENGINE/TENGINE.H"

#if defined(VERSION_US_REV1)
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENTSTATE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WORLD.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "../../../sdk/include/AUDIO/sprintf.H"
#include "TYPES.H"
#include <ultra64.h>
u32 SetN64_LocatePackSection(s32, s32, s32, u32 *);

/* Separate-object views of the menu state words (each access has its own lui; DATA-FRAME-O1 F2b). */
extern struct CacheResourceNode *g_artsendSelectedTextureResource;
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

    if (g_artsendSelectedTextureResource != NULL) {
        Cache_UnlockResource(NULL, g_artsendSelectedTextureResource);
    }
    g_artsendSelectedTextureResource = NULL;
    g_artsendTextureResetWordOne = 0;
    g_artsendTextureResetWordTwo = 0;
    g_artsendActionMappingSelection = 0;
    key = SetN64_LocatePackSection(world->textureDirectory, world->textureBank, g_artsendTextureViewer.selectionIndex, &size);
    resource = Cache_RequestResource(0, key - 1, key, size, 9, -1, &g_artsendTextureResourceCallbackUsRev1, "Artsend Texture", 1);
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
#include "COMMON/RESIDENTSTATE.H"
#include "TYPES.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "COMMON/TEXTURE_REQUEST.H"
#include "ENGINE/AUDIO/CHANNEL.H"

struct ArtsendTextureSelection;



void Tengine_UpdateArtsendTexturePreview(void) {
    f32 scale;
    s32 wrappedSelection;
    s32 regpart_temp_a0;
    s32 count_0;
    s32 count_1;
    s32 count_2;
    s32 count_3;
    s32 count_4;
    s32 count_5;
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
                count_0 = g_artsendPreviousFrameHoldCount;
                previousFrameHold = count_0;
                count_0 += 1;
                g_artsendPreviousFrameHoldCount = count_0;
                if (previousFrameHold >= 3) {
                    g_artsendTextureSelectionChanged = 1;
                    g_artsendPreviousFrameHoldCount = 0;
                    g_artsendTextureFrameSelection -= 1;
                }
            }
            if (g_controllerProfiles[0].buttons & 0x100) {
                count_1 = g_artsendNextFrameHoldCount;
                nextFrameHold = count_1;
                count_1 += 1;
                g_artsendNextFrameHoldCount = count_1;
                if (nextFrameHold >= 3) {
                    g_artsendTextureSelectionChanged = 1;
                    g_artsendNextFrameHoldCount = 0;
                    g_artsendTextureFrameSelection += 1;
                }
            }
        } else {
            if (g_controllerProfiles[0].buttons & 0x200) {
                count_2 = g_artsendPreviousTextureHoldCount;
                previousTextureHold = count_2;
                count_2 += 1;
                g_artsendPreviousTextureHoldCount = count_2;
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
                count_3 = g_artsendNextTextureHoldCount;
                nextTextureHold = count_3;
                count_3 += 1;
                g_artsendNextTextureHoldCount = count_3;
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
                count_4 = g_artsendPreviousPageHoldCount;
                previousPageHold = count_4;
                count_4 += 1;
                g_artsendPreviousPageHoldCount = count_4;
                if (previousPageHold >= 3) {
                    regpart_temp_a0 = g_artsendTextureSelectionIndex - 5;
                    previousPageWrappedInput = regpart_temp_a0 + g_artsendTextureSelection.count;
                    previousPageIndex = previousPageWrappedInput % g_artsendTextureSelection.count;
                    g_artsendTextureViewer.selectionIndex = regpart_temp_a0;
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
                count_5 = g_artsendNextPageHoldCount;
                nextPageHold = count_5;
                count_5 += 1;
                g_artsendNextPageHoldCount = count_5;
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
        Onscrn_DrawText((char *)&g_artsendTextureViewer.displayData, 16, g_hudReferenceViewportHeight - 48, 0xFF, 0, 0, scale, scale);
    }
}
#endif
