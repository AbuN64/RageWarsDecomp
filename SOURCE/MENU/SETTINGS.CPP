#include "include_asm.h"
#include "MENU/LOCALIZED_GAME_OPTION_CHOICES.H"
#include "COMMON/FRONTEND_RESOURCE_LOAD_STATE.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"

/* MENU_CREATELOCALIZEDSETTINGSPAGE.CPP */
#if defined(VERSION_EU_X)
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/SCROLL.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
extern struct Record *Cache_AllocateMemory(s32 size);
extern MenuWidget *Node_FindWidgetByResourceId(void *, s32);
#endif
#if defined(VERSION_DE)
/* 80408AC4_12.CPP */
extern char s_nodeDefaultFieldText[];
extern char s_nodeAlternateFieldText[];
typedef struct { char pad0[0x14]; char *text; } PakOperationLabelItem;
s32 Menu_SelectPakOperationActionLabel(PakOperationLabelItem *labelItem) {
    switch (g_frontendResourceLoadStage) {
    case 0:
    default:
        labelItem->text = s_nodeDefaultFieldText;
        break;
    case 3:
        labelItem->text = s_nodeDefaultFieldText;
        break;
    case 4:
        labelItem->text = s_nodeDefaultFieldText;
        break;
    case 1:
    case 2:
        labelItem->text = s_nodeAlternateFieldText;
        break;
    }
    return 0;
}
#endif
#if defined(VERSION_EU)
#include "COMMON/REQUESTRECAT10.H"
#include "FRONTEND/SMP_OVERLAY.H"
#include "JOIN/JOIN_CYCLEJOINREQUESTRANK.H"
/* 80408CB0_24.CPP */
extern struct CourseOptionsScreen *g_courseOptionsScreen;
extern struct Record *Cache_AllocateMemory(s32 size);


extern void Widget_SetWidgetFlag08(void *object, int enabled);
extern void Tsmos_ActivateControllerState(void);
s32 Menu_CreateEuJoinOptions(void *handle) {
    MenuWidget *widget;
    s32 i;
    g_courseOptionsScreen = Cache_AllocateMemory(32);
    g_courseOptionsScreen->handle = handle;
    g_courseOptionsScreen->mode = SmpOverlay_CreateOverlayNode(handle, 4);
    SmpOverlay_ShowSlotById(handle, 0, 905);
    SmpOverlay_ShowSlotById(handle, 1, 905);
    SmpOverlay_ShowSlotById(handle, 2, 905);
    SmpOverlay_ShowSlotById(handle, 3, 905);
    widget = Node_FindWidgetByResourceId(handle, 907);
    widget->alpha = 140;
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        Widget_SetWidgetFlag08(widget, 0);
    }
    g_courseOptionsScreen->timer = 0;
    g_courseOptionsScreen->selection = 0;
    g_courseOptionsScreen->rows[0] = Node_FindWidgetByResourceId(handle, 908);
    g_courseOptionsScreen->rows[1] = Node_FindWidgetByResourceId(handle, 917);
    g_courseOptionsScreen->rows[2] = Node_FindWidgetByResourceId(handle, 918);
    g_courseOptionsScreen->step = Join_CountUsedSlots();
    for (i = 0; i < 3; i++) {
        Join_UpdateJoinRequestDisplay(i);
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[i], 914), 0);
    }
    Tsmos_ActivateControllerState();
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], 914), 1);
    return 0;
}
#endif

/* K_WIDGETCONSTANTWORDSBLOCK1.CPP */
#if defined(VERSION_DE)
const unsigned int k_widgetConstantWordsBlock1[1] = {
    0x0040DBA0,
};
#endif
