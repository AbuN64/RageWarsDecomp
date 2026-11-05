#include "Common/statepair.h"
#include "types.h"
#include "Ui/g_frontendshutdownstate.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/menu_screen_elements.h"
#include "Common/record.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Ui/Tsmos/TSMOS.h"

/** Set g_frontendShutdownState to one. */


s32 GetMenuScreenOwner(void);


void Tsmos_RequestFrontendShutdown(void) {
    g_frontendShutdownState.x = 1;
}

void Tsmos_ScaleCurrentScreen(void) {
    if (g_frontendCurrentVideoModeIndex == 1) {
        Tsmos_ScaleWidgetTree(Node_GetScreenData(GetMenuScreenOwner()), 0);
    }
}
