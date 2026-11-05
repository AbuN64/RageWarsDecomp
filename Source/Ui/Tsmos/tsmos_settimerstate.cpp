#include "Common/rotation_extraction.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/menu_screen_elements.h"
#include "Common/record.h"
#include "Common/statepair.h"
#include "Ui/Tsmos/TSMOS.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"

/** Store the active value and reset its timer to sixty. */
void Tsmos_SetTimerState(int timerState) {
    g_frontendTimerState.state = timerState;
    g_frontendTransitionCountdown = 60;
}
