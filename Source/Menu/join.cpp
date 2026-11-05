#include "include_asm.h"
#if ((defined(VERSION_EU_X)))
#include "types.h"
#endif
#if ((defined(VERSION_EU_X)))
#include "Frontend/smp_overlay.h"
#endif
#if ((defined(VERSION_EU_X)))
#include "Join/join_cyclejoinrequestrank.h"
#endif
#if ((defined(VERSION_EU_X)))
#include "Common/player_join_requests.h"
#endif
#if ((defined(VERSION_EU_X)))
#include "Common/selectionscreenstate.h"
#endif
#if ((defined(VERSION_EU_X)))
#include "Frontend/node_findwidgetbyresourceid.h"
#endif
#if ((defined(VERSION_EU_X)))
#include "Common/shared_menureply.h"
#endif

#if defined(VERSION_EU_X)
typedef struct { u8 pad0[0x10]; u8 alpha; } EuxDrawItem;

/* Builds the pak-draw selection screen: allocates its 0x20-byte state, creates the four rows, hides the pointer item
   when the pad answer is 0x16, collects the three root items and hides their cursors, then shows the cursor of the
   current root. Returns 0. */
s32 Menu_CreateEuxJoinOptions(void *window) {
    struct CourseOptionsScreen *screen;
    EuxDrawItem *item;
    s32 i;

    screen = Cache_AllocateMemory(32);
    g_courseOptionsScreen = screen;
    screen->handle = window;
    g_courseOptionsScreen->mode = SmpOverlay_CreateOverlayNode(window, 4);
    SmpOverlay_ShowSlotById(window, 0, 909);
    SmpOverlay_ShowSlotById(window, 1, 909);
    SmpOverlay_ShowSlotById(window, 2, 909);
    SmpOverlay_ShowSlotById(window, 3, 909);
    item = Node_FindWidgetByResourceId(window, 911);
    item->alpha = 140;
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        Widget_SetWidgetFlag08(item, 0);
    }
    g_courseOptionsScreen->timer = 0;
    g_courseOptionsScreen->selection = 0;
    g_courseOptionsScreen->rows[0] = Node_FindWidgetByResourceId(window, 912);
    g_courseOptionsScreen->rows[1] = Node_FindWidgetByResourceId(window, 921);
    g_courseOptionsScreen->rows[2] = Node_FindWidgetByResourceId(window, 922);
    g_courseOptionsScreen->step = Join_CountUsedSlots();
    for (i = 0; i < 3; i++) {
        Join_UpdateJoinRequestDisplay(i);
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[i], 918), 0);
    }
    Tsmos_ActivateControllerState();
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], 918), 1);
    return 0;
}
#endif
