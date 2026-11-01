#include "COMMON/STATEPAIR.H"
#include "COMMON/GAME_SESSION.H"
#include "UI/TSMOS/TSMOS.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/RECORD.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"
#include "RESMGR/TSMOS_SETIDLETIMER.H"

/** Return the global word at g_frontendActiveState. */




/** Store a scalar and clear its associated global state word. */
void Tsmos_SetIdleTimer(f32 value) {
    g_frontendTimerState.value = value;
    g_gameSession.transitionTime = 0;
}
