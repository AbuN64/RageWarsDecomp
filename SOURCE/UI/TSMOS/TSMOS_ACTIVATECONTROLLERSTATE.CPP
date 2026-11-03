#include "COMMON/OBJRECAT3CV2.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/RECORD.H"
#include "COMMON/STATEPAIR.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"

/** Set g_frontendShutdownState to one. */


extern void Controller_ClearControllerFlags(s32 *controller);

/** Return the global word at g_frontendActiveState. */




void Tsmos_ActivateControllerState(void) {
    s32 *p;

    p = &g_frontendControllerState;
    if (*p != 1) {
        *p = 1;
        Controller_ClearControllerFlags(p);
    }
}

void Tsmos_DeactivateControllerState(void) {
    g_frontendControllerState = 0;
}

int Tsmos_IsControllerStateActive(void) {
    return g_frontendControllerState;
}

s32 Tsmos_IsFrontendActive(void) {
    return g_frontendActiveState;
}

void Tsmos_SetModeOneFlag(s32 mode) {
    if (mode == 1) {
        g_frontendModeOneState = mode;
        return;
    }
    g_frontendModeOneState = 0;
}

int Tsmos_GetModeOneFlag(void) {
    return g_frontendModeOneState;
}
