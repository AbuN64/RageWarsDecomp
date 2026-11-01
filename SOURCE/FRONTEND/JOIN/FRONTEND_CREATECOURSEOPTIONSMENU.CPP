#include "include_asm.h"
#if defined(VERSION_US_REV1)
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/REQUESTRECAT10.H"
#include "TYPES.H"
#include "COMMON/SHARED_MENUREPLY.H"
/* 8040B45C_24.CPP */
/* 8041DF04_4.CPP */
/* Creates the three-row request screen and shows its selected row. */
extern struct CourseOptionsScreen *g_courseOptionsScreen;
s32 Frontend_CreateCourseOptionsMenu(void *root) {
    SlotSelectionWidget *item;
    s32 row;

    { void *memory = Cache_AllocateMemory(32); g_courseOptionsScreen = memory; }
    g_courseOptionsScreen->handle = root;
    g_courseOptionsScreen->mode = SmpOverlay_CreateOverlayNode((s32) root, 4);
    SmpOverlay_ShowSlotById((s32) root, 0, 905);
    SmpOverlay_ShowSlotById((s32) root, 1, 905);
    SmpOverlay_ShowSlotById((s32) root, 2, 905);
    SmpOverlay_ShowSlotById((s32) root, 3, 905);

    item = Node_FindWidgetByResourceId(root, 907);
    item->alpha = 140;
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        Widget_SetWidgetFlag08(item, 0);
    }

    g_courseOptionsScreen->timer = 0;
    g_courseOptionsScreen->selection = 0;
    item = Node_FindWidgetByResourceId(root, 908);
    g_courseOptionsScreen->rows[0] = item;
    item = Node_FindWidgetByResourceId(root, 917);
    g_courseOptionsScreen->rows[1] = item;
    item = Node_FindWidgetByResourceId(root, 918);
    g_courseOptionsScreen->rows[2] = item;
    g_courseOptionsScreen->step = Join_CountUsedSlots();

    for (row = 0; row < 3; row++) {
        Join_UpdateJoinRequestDisplay(row);
        item = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[row], 914);
        Widget_SetWidgetFlag08(item, 0);
    }

    Tsmos_ActivateControllerState();

    item = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], 914);
    Widget_SetWidgetFlag08(item, 1);
    return 0;
}
#endif
#if defined(VERSION_EU_X)
#include "TYPES.H"
/* 80406A88_14.CPP */
typedef struct { void *list; s32 resourceWidget; void *item; s32 scrollDelay; s32 reservedWord10; char text14[12]; s32 playerCount; } SliderPopupEu;
typedef struct { u8 pad0[0x10]; u8 alpha; u8 pad11[0x27]; void *text; } SliderItemEu;
extern void *Cache_AllocateMemory(s32);
extern void Tsmos_ActivateControllerState(void);
extern void *Node_FindWidgetByResourceId(void *, s32);
#endif
