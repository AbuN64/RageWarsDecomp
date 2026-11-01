#include "COMMON/OBJRECAT3CV2.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/RECORD.H"
#include "COMMON/STATEPAIR.H"
#include "UI/TSMOS/TSMOS.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"

/** Store the active value and reset its timer to sixty. */
void Tsmos_SetTimerState(int timerState) {
    g_frontendTimerState.state = timerState;
    g_frontendTransitionCountdown = 60;
}
