#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/SESSIONHANDLERROW.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern s32 Playerai_GetFirstPlayer(void *);

void CCredits_UpdateScroll(void *object) {
    f32 time;
    f32 height;
    s32 line;
    if (g_creditsSkipRequested != 0) {
        time = g_creditsLineTimer - g_frameElapsedTime;
        g_creditsLineTimer = time;
        if (time <= 0.0f) {
            Playerai_GetFirstPlayer(&g_playerViewRenderContext);
            if (g_creditsSelectSpawnOnExit != 0) {
                if (g_creditsReturnToFrontend == 0) {
                    SetN64_SelectSpawnAfterCredits(object, 1999);
                    return;
                }
                goto advance;
            }
            if (g_creditsReturnToFrontend != 0) {
advance:
                SetN64_SetTransitionTarget(object, 1);
                g_gameSettings.counters.m_bCreditsSeenOnce = 1;
            }
        }
    } else {
        if (g_hudReferenceViewportHeight >= 223) {
            g_creditsScrollPosition -= g_creditsNormalScrollStep;
        } else {
            g_creditsScrollPosition -= g_creditsFastScrollStep;
        }
        height = (f32)g_hudReferenceViewportHeight * g_creditsViewportHeightScale;
        if (g_creditsScrollPosition <= -height) {
            line = g_creditsCurrentLine + 1;
            g_creditsCurrentLine = line;
            g_creditsScrollPosition += height;
            if (g_creditsLocalizedLines[g_languageIndex][line] == 0) {
                g_creditsSkipRequested = 1;
                g_creditsLineTimer = g_creditsNextLineDelayEu;
            }
        }
    }
}
#endif
