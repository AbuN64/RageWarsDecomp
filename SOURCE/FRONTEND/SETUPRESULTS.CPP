#include "include_asm.h"
#include "COMMON/SHARED_MENUREPLY.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/CHEATCODE.H"
#include "ENGINE/CONTROL.H"
#include "TYPES.H"
#include "FRONTEND/SCENARIO_RESULT_ROWS.H"
#include "UI/TSMOS/SCREENS/SCENARIOSETUPSCREEN.H"

/* SETUPRESULTS.CPP */
/* Draw callback of the versus results screen g_setupScreen: on draw event 1 in states 3, 8 or 9 it
   sets the fill g_menuModelFillEnabled to blended white, restores the full-screen clip, and at alpha 210 draws
   the four player panels (on screen 0x14 with no pending pause) and the tie panel at 0x308 unless a
   winner is set, then resets the fill. On update event 0 (unless GetMenuScreenOwner reports 0x19) it
   plays the winner's voice on the twentieth frame, raises the banner blink six frames later, and
   fades the two banner sprites out by 30 per frame before hiding them. Returns zero. */

extern struct VersusResultsScreen *g_setupScreen;

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
extern void Preview_DrawMenuModelItem(struct MenuModelItem *item);
#else
#endif

#if defined(VERSION_DE)
extern void Preview_DrawMenuModelItem(struct MenuModelItem *item);
#else
#endif

extern void Widget_SetWidgetFlag08(void *object, int enabled);

s32 Frontend_DrawSetupResultPanels(void *unused0, void *unused1, s32 event) {
    s32 i;
    s32 alpha;

    if (event == 1 && (g_setupScreen->state == 3 || g_setupScreen->state == 8 || g_setupScreen->state == 9)) {
        /* MIXED: the ROM keeps both stores, so the first is an in-struct store of the same word (data typing open). */
        ((struct MenuRenderFill *)&g_menuModelFillEnabled)->mode = 0;
        g_menuModelFillEnabled = 1;
        g_menuModelFillColor[0] = 255.0f;
        g_menuModelFillColor[1] = 255.0f;
        g_menuModelFillColor[2] = 255.0f;
        g_menuModelFillColor[3] = 255.0f;
        gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, g_hudReferenceViewportWidth - 1, g_hudReferenceViewportHeight - 1);
        g_menuModelFillColor[3] = 210.0f;
        if (GetMenuScreenOwner() == 20 && g_selectionMessageReply.ready == 0) {
            for (i = 0; i < 4; i++) {
#if defined(VERSION_DE)

#if defined(VERSION_DE)
Preview_DrawMenuModelItem
#else
Frontend_DrawResultModelPreviewDe
#endif
(g_setupScreen->panels[i]);
#else

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Preview_DrawMenuModelItem
#else
Preview_DrawMenuModelItem_Setupresults
#endif
(g_setupScreen->panels[i]);
#endif
            }
        }
        if (g_setupScreen->winner == 0) {
#if defined(VERSION_DE)

#if defined(VERSION_DE)
Preview_DrawMenuModelItem
#else
Frontend_DrawResultModelPreviewDe
#endif
(g_setupScreen->tie);
#else

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Preview_DrawMenuModelItem
#else
Preview_DrawMenuModelItem_Setupresults
#endif
(g_setupScreen->tie);
#endif
        }
        g_menuModelFillEnabled = 0;
        g_menuModelFillColor[3] = 255.0f;
    }
    if (event == 0 && GetMenuScreenOwner() != 25) {
        if (g_setupScreen->frames < 20) {
            if (++g_setupScreen->frames == 20 && g_setupScreen->winner > 0) {
                Menu_SetOptionsSceneSelection(ScenarioSetup_ResolveArenaFromSelection(ScenarioSetup_CategoryToList(g_setupScreen->winnerSlot), g_setupScreen->winner) + 601);
                g_setupScreen->blinkDelay = 0;
            }
        }
        if (g_setupScreen->blinkDelay != -1) {
            if (++g_setupScreen->blinkDelay >= 6) {
                g_setupScreen->blinking = 1;
                g_setupScreen->blinkDelay = -1;
            }
        }
        if (g_setupScreen->blinking == 1) {
            alpha = g_setupScreen->banner->value;
            alpha -= 30;
            if (alpha <= 0) {
                g_setupScreen->blinking = 0;
                Widget_SetWidgetFlag08(g_setupScreen->bannerShadow, 0);
                Widget_SetWidgetFlag08(g_setupScreen->banner, 0);
                alpha = 0xFF;
            }
            g_setupScreen->banner->value = alpha;
            g_setupScreen->bannerShadow->value = alpha;
        }
    }
    return 0;
}
