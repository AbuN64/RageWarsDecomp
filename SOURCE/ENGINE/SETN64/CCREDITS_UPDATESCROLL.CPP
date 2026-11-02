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

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
extern int Playerai_GetFirstPlayer(void *world);


void CCredits_UpdateScroll(void *session) {
    f32 remainingTime;
    f32 scrollBoundary;
    s32 nextLine;

    if (g_creditsSkipRequested != 0) {
        remainingTime = g_creditsLineTimer - g_frameElapsedTime;
        g_creditsLineTimer = remainingTime;
        if (remainingTime <= 0.0f) {
            Playerai_GetFirstPlayer(&g_playerViewRenderContext);
            if (g_creditsSelectSpawnOnExit != 0) {
                if (g_creditsReturnToFrontend == 0) {
                    SetN64_SelectSpawnAfterCredits(session, 1999);
                    return;
                }
                goto block_6;
            }
            if (g_creditsReturnToFrontend != 0) {
block_6:
                SetN64_SetTransitionTarget(session, 1);
                g_gameSettings.counters.m_bCreditsSeenOnce = 1;
            }
        }
    } else {
        if (g_hudReferenceViewportHeight >= 223) {
            g_creditsScrollPosition -= g_creditsNormalScrollStep;
        } else {
            g_creditsScrollPosition -= g_creditsFastScrollStep;
        }
        scrollBoundary = (f32)g_hudReferenceViewportHeight * g_creditsViewportHeightScale;
        if (g_creditsScrollPosition <= -scrollBoundary) {
            nextLine = g_creditsCurrentLine + 1;
            g_creditsCurrentLine = nextLine;
            g_creditsScrollPosition += scrollBoundary;
            if (g_creditsLocalizedLines[0][nextLine] == 0) {
                g_creditsSkipRequested = 1;
                g_creditsLineTimer = g_creditsNextLineDelay;
            }
        }
    }
}
#endif
