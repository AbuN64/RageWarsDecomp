#include "include_asm.h"
#include "Frontend/smp_overlay.h"
#include "Join/join_cyclejoinrequestrank.h"
#include "Common/player_join_requests.h"
#include "Common/selectionscreenstate.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/shared_menureply.h"

#if defined(VERSION_DE)
typedef struct { s32 owner; void *list; void *w8[3]; void *w14; s32 sel; s32 joinedSlotCount; } CourseSelectionState;

/* Opens the 0x20-byte screen state g_courseOptionsScreen for owner owner: a four-row list, the widgets 0x385, 0x386, 0x38F, 0x390 and three 0x38C rows (shown one by one through Join_UpdateJoinRequestDisplay); returns zero. */
s32 Menu_CreateGermanCourseOptions(s32 owner) {
    u8 *widget;
    s32 i;
    g_courseOptionsScreen = (CourseSelectionState *)Cache_AllocateMemory(32);
    g_courseOptionsScreen->handle = owner;
    g_courseOptionsScreen->mode = SmpOverlay_CreateOverlayNode(owner, 4);
    SmpOverlay_ShowSlotById(owner, 0, 899);
    SmpOverlay_ShowSlotById(owner, 1, 899);
    SmpOverlay_ShowSlotById(owner, 2, 899);
    SmpOverlay_ShowSlotById(owner, 3, 899);
    widget = Node_FindWidgetByResourceId(owner, 901);
    widget[16] = 140;
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        Widget_SetWidgetFlag08(widget, 0);
    }
    g_courseOptionsScreen->timer = 0;
    g_courseOptionsScreen->selection = 0;
    g_courseOptionsScreen->rows[0] = Node_FindWidgetByResourceId(owner, 902);
    g_courseOptionsScreen->rows[1] = Node_FindWidgetByResourceId(owner, 911);
    g_courseOptionsScreen->rows[2] = Node_FindWidgetByResourceId(owner, 912);
    g_courseOptionsScreen->step = (s32)Join_CountUsedSlots();
    for (i = 0; i < 3; ) {
        Join_UpdateJoinRequestDisplay(i);
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId((s32)g_courseOptionsScreen->rows[i], 908), 0);
        i++;
    }
    Tsmos_ActivateControllerState();
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId((s32)g_courseOptionsScreen->rows[(s32)g_courseOptionsScreen->selection], 908), 1);
    return 0;
}
#endif
