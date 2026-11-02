#include "COMMON/STATEPAIR.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/RECORD.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"
#include "UI/TSMOS/TSMOS.H"

/** Set g_frontendShutdownState to one. */


s32 GetMenuScreenOwner(void);


void Tsmos_RequestFrontendShutdown(void) {
    extern int g_frontendShutdownState;
    g_frontendShutdownState = 1;
}

void Tsmos_ScaleCurrentScreen(void) {
    if (g_frontendCurrentVideoModeIndex == 1) {
        Tsmos_ScaleWidgetTree(Node_GetScreenData(GetMenuScreenOwner()), 0);
    }
}
