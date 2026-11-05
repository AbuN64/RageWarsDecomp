#include "Common/rotation_extraction.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/menu_screen_elements.h"
#include "Common/record.h"
#include "Common/statepair.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Ui/math_controller_events.h"

/** Marks the controller state active and clears the controller flags when it was not active yet. */
void Tsmos_ActivateControllerState(void) {
    s32 *controllerState;

    controllerState = &g_frontendControllerState;
    if (*controllerState != 1) {
        *controllerState = 1;
        Controller_ClearControllerFlags(controllerState);
    }
}

/** Marks the controller state inactive. */
void Tsmos_DeactivateControllerState(void) {
    g_frontendControllerState = 0;
}

/** Returns the controller state word: nonzero while the controller state is active. */
int Tsmos_IsControllerStateActive(void) {
    return g_frontendControllerState;
}

/** Reports the frontend as never active through this entry. */
s32 Tsmos_IsFrontendActive(void) {
    return g_frontendActiveState;
}

void Tsmos_SetMenuModelFlag(s32 mode) {
    if (mode == 1) {
        g_frontendMenuModelFlag = mode;
        return;
    }
    g_frontendMenuModelFlag = 0;
}

int Tsmos_GetMenuModelFlag(void) {
    return g_frontendMenuModelFlag;
}
