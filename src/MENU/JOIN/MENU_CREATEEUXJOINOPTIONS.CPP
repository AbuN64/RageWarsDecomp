#include "include_asm.h"

#if defined(VERSION_EU_X)
#include "TYPES.H"
typedef struct EuxDrawScreen { void *window; s32 overlayNodeId; void *roots[3]; s32 selection; s32 reservedWord; s32 count; } EuxDrawScreen;
typedef struct { u8 pad0[0x10]; u8 alpha; } EuxDrawItem;
extern EuxDrawScreen *g_courseOptionsScreen;
extern struct Record *Cache_AllocateMemory(s32 size);
extern s32 SmpOverlay_CreateOverlayNode(void *, s32);
extern void SmpOverlay_ShowSlotById(void *, s32, s32);
extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);
extern void Widget_SetWidgetFlag08(void *, s32);
extern s32 Menu_GetPreviousScreenOwner(s32);
extern s32 Join_CountUsedSlots(void);
extern void Join_UpdateJoinRequestDisplay(s32);
extern void Tsmos_ActivateControllerState(void);
/* Builds the pak-draw selection screen: allocates its 0x20-byte state, creates the four rows, hides the pointer item
   when the pad answer is 0x16, collects the three root items and hides their cursors, then shows the cursor of the
   current root. Returns 0. */
s32 Menu_CreateEuxJoinOptions(void *window) {
    EuxDrawScreen *screen;
    EuxDrawItem *item;
    s32 i;

    screen = Cache_AllocateMemory(32);
    g_courseOptionsScreen = screen;
    screen->window = window;
    g_courseOptionsScreen->overlayNodeId = SmpOverlay_CreateOverlayNode(window, 4);
    SmpOverlay_ShowSlotById(window, 0, 909);
    SmpOverlay_ShowSlotById(window, 1, 909);
    SmpOverlay_ShowSlotById(window, 2, 909);
    SmpOverlay_ShowSlotById(window, 3, 909);
    item = Node_FindWidgetByResourceId(window, 911);
    item->alpha = 140;
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        Widget_SetWidgetFlag08(item, 0);
    }
    g_courseOptionsScreen->reservedWord = 0;
    g_courseOptionsScreen->selection = 0;
    g_courseOptionsScreen->roots[0] = Node_FindWidgetByResourceId(window, 912);
    g_courseOptionsScreen->roots[1] = Node_FindWidgetByResourceId(window, 921);
    g_courseOptionsScreen->roots[2] = Node_FindWidgetByResourceId(window, 922);
    g_courseOptionsScreen->count = Join_CountUsedSlots();
    for (i = 0; i < 3; i++) {
        Join_UpdateJoinRequestDisplay(i);
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_courseOptionsScreen->roots[i], 918), 0);
    }
    Tsmos_ActivateControllerState();
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_courseOptionsScreen->roots[g_courseOptionsScreen->selection], 918), 1);
    return 0;
}
#endif
