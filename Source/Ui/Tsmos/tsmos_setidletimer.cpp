#include "Common/statepair.h"
#include "Common/game_session.h"
#include "Ui/Tsmos/TSMOS.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/menu_screen_elements.h"
#include "Common/record.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Resmgr/tsmos_setidletimer.h"

/** Return the global word at g_frontendActiveState. */




/** Store a scalar and clear its associated global state word. */
void Tsmos_SetIdleTimer(f32 value) {
    g_frontendTimerState.value = value;
    g_gameSession.transitionTime = 0;
}
