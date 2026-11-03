#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/VIDEO_DIMENSIONS.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "FRONTEND/RESULTS_REFRESHTRIALCATALOGUEWIDGETS.H"
#include "FRONTEND/RESULTS_LOADTRIALCOMPLETIONFLAGS.H"
#include "FRONTEND/RESULTS.H"
#include "RESULTS/RESULTS_RENDERRESULTSOPTIONSPREVIEW.H"
extern ResultsOptionsScreen *g_trialCatalogueScreen;

/* Draw callback of the results screen g_trialCatalogueScreen: on draw event 1 in states 3, 8 or 9 it resets
   the fill colour g_menuModelFillEnabled to opaque white, and for each of the one or two viewports clips the
   display list to its rectangle in g_menuPlayerScissorRects (0, then 2 for the lower view), draws the player's panel through Preview_DrawModelPreview and restores the
   full-screen clip. Outside two-player mode (and unless GetMenuScreenOwner reports 0x19) it plays sound
   0x259 past the base at 0xA44 on the twentieth frame, raises the banner blink after six more
   frames, and fades the two banner sprites out by 30 per frame before hiding them. Returns zero. */












extern struct MenuPlayerScissorRect g_menuPlayerScissorRects[];

extern s32 g_hudReferenceViewportWidth;



extern void Preview_DrawModelPreview(struct ModelPreview *self);

extern void Widget_SetWidgetFlag08(void *object, int enabled);

/* Loads the stage list of the results screen g_trialCatalogueScreen: clears its two 36-bit sets at 0xA74 and
   0xA79, copies into the first the 36 cleared-stage bits that the player record g_localPlayerProfiles[index at
   0xA5C] keeps for the current mode g_gameControllerMode (at 0x7E, 0x83, 0x88 or 0x8D for modes 1 to 4), and
   refreshes the list through Results_RefreshTrialCatalogueWidgets. */







extern struct ResultsPreviewProfile g_localPlayerProfiles[];

extern void Defs_SetBitValue(u8 *, s32, s32);

extern s32 Defs_TestBit(void *bitArray, s32 index);

s32 Results_RenderResultsOptionsPreview(void *unused0, void *unused1, s32 event) {
    s32 views;
    s32 i;
    s32 alpha;
    s32 k;

    if (event == 1 && (g_trialCatalogueScreen->state == 3 || g_trialCatalogueScreen->state == 8 || g_trialCatalogueScreen->state == 9)) {
        g_menuModelFillEnabled = 0;
        g_menuModelFillColor[0] = 255.0f;
        g_menuModelFillColor[1] = 255.0f;
        g_menuModelFillColor[2] = 255.0f;
        g_menuModelFillColor[3] = 255.0f;
        views = 1;
        if (g_gameSettings.controllerMode == 2) {
            views = 2;
        }
        for (i = 0, k = 0; i < views; i++, k = 2) {
            gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, g_menuPlayerScissorRects[k].left, g_menuPlayerScissorRects[k].top, g_menuPlayerScissorRects[k].right, g_menuPlayerScissorRects[k].bottom);
            Preview_DrawModelPreview(g_trialCatalogueScreen->panels[i]);
            gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
        }
        if (g_gameSettings.controllerMode != 2 && GetMenuScreenOwner() != 25) {
            if (g_trialCatalogueScreen->frames < 20) {
                if (++g_trialCatalogueScreen->frames == 20) {
                    k = g_trialCatalogueScreen->selection;
                    Menu_SetOptionsSceneSelection(k + 601);
                    g_trialCatalogueScreen->blinkDelay = 0;
                }
            }
            if (g_trialCatalogueScreen->blinkDelay != -1) {
                if (++g_trialCatalogueScreen->blinkDelay >= 6) {
                    g_trialCatalogueScreen->blinking = 1;
                    g_trialCatalogueScreen->blinkDelay = -1;
                }
            }
            if (g_trialCatalogueScreen->blinking == 1) {
                alpha = g_trialCatalogueScreen->banner->alpha;
                alpha -= 30;
                if (alpha <= 0) {
                    g_trialCatalogueScreen->blinking = 0;
                    Widget_SetWidgetFlag08(g_trialCatalogueScreen->bannerShadow, 0);
                    Widget_SetWidgetFlag08(g_trialCatalogueScreen->banner, 0);
                    alpha = 0xFF;
                }
                g_trialCatalogueScreen->banner->alpha = alpha;
                g_trialCatalogueScreen->bannerShadow->alpha = alpha;
            }
        }
    }
    return 0;
}

void Results_LoadTrialCompletionFlags(void) {
    s32 i;

    i = 0;
    do {
        Defs_SetBitValue(g_trialCatalogueScreen->owned, i, 0);
        Defs_SetBitValue(g_trialCatalogueScreen->pending, i, 0);
        i++;
    } while (i < 36);
    switch (g_gameSettings.controllerMode) {
    case 1:
        i = 0;
        do {
            Defs_SetBitValue(g_trialCatalogueScreen->owned, i, Defs_TestBit(g_localPlayerProfiles[g_trialCatalogueScreen->player].single, i));
            i++;
        } while (i < 36);
        break;
    case 2:
        i = 0;
        do {
            Defs_SetBitValue(g_trialCatalogueScreen->owned, i, Defs_TestBit(g_localPlayerProfiles[g_trialCatalogueScreen->player].versus, i));
            i++;
        } while (i < 36);
        break;
    case 3:
        i = 0;
        do {
            Defs_SetBitValue(g_trialCatalogueScreen->owned, i, Defs_TestBit(g_localPlayerProfiles[g_trialCatalogueScreen->player].three, i));
            i++;
        } while (i < 36);
        break;
    case 4:
        i = 0;
        do {
            Defs_SetBitValue(g_trialCatalogueScreen->owned, i, Defs_TestBit(g_localPlayerProfiles[g_trialCatalogueScreen->player].four, i));
            i++;
        } while (i < 36);
        break;
    }
    Results_RefreshTrialCatalogueWidgets();
}

extern struct ProfileWeaponRowEntry g_trialCatalogueStages[];

/* Backtracking search over the 36 unlock nodes of g_trialCatalogueStages: while any node is still set in the
   remaining bit set, appends to the -1-terminated path the first remaining node linked to the
   path's last node, clears its bit and recurses, undoing the step when the recursion fails. Every
   exit returns one, so the first linked choice at each depth is always kept. */
s32 Results_FindUnlockPath(u8 *remaining, s32 *path) {
    s32 anyLeft;
    s32 node;
    s32 last;
    s32 linked;

    anyLeft = 0;
    node = 0;
    do {
        if (Defs_TestBit(remaining, node) == 1) {
            anyLeft = 1;
        }
        node++;
    } while (node < 36 && anyLeft == 0);
    if (anyLeft != 0) {
        last = 0;
        while (path[last] != -1) {
            last++;
        }
        last--;
        node = 0;
        while (node < 36) {
            if (Defs_TestBit(remaining, node) == 0) {
                node++;
            } else {
                linked = Results_IsUnlockLinked(g_trialCatalogueStages[path[last]].value, g_trialCatalogueStages[node].value);
                if (linked == 1) {
                    last++;
                    path[last] = node;
                    path[last + 1] = -1;
                    Defs_SetBitValue(remaining, node, 0);
                    if (Results_FindUnlockPath(remaining, path) == linked) {
                        return 1;
                    }
                    Defs_SetBitValue(remaining, node, 1);
                    path[last] = -1;
                    last--;
                }
                node++;
            }
        }
    }
    return 1;
}
