#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "include_asm.h"
#if defined(VERSION_US_REV1)
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/REQUESTRECAT10.H"
#include "TYPES.H"
#include "COMMON/SHARED_MENUREPLY.H"
#endif
#if defined(VERSION_EU_X)
#include "TYPES.H"
#include "PLAYERCOUNT/FRONTEND_CREATECOURSEOPTIONSMENU.H"
#include "UI/TSMOS/SMP/SMP_FADE.H"
/* 80406A88_14.CPP */
extern struct PlayerCountScreenState *g_playerCountScreen;
extern char s_playerCountFormat[];
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Tsmos_ActivateControllerState(void);

extern void SmpSlider_EnableTransition(struct Access_s32_5C *object);
extern void SmpButton_WrapButtonWidget(s32);
extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);
extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);
/* Builds a three-row slider popup in its 0x24-byte state g_playerCountScreen: title/list from the ids at 0x39C, the numeric
   readout item at 0x39D showing the text at +0x14 formatted with s_playerCountFormat. Returns 0. */
s32 Frontend_CreatePlayerCountScreenEux(void *window) {
    MenuWidget *item;
    void *title;

    g_playerCountScreen = Cache_AllocateMemory(36);
    Tsmos_ActivateControllerState();
    title = SmpFade_CreateFadeWidget(924, 925);
    g_playerCountScreen->menu = title;
    SmpSlider_EnableTransition(title);
    SmpButton_WrapButtonWidget(928);
    item = Node_FindWidgetByResourceId(window, 926);
    g_playerCountScreen->window = item;
    item->alpha = 15;
    g_playerCountScreen->button = SmpFlicker_CreateFlickerWidget(927, 110);
    g_playerCountScreen->delay = 3;
    item = Node_FindWidgetByResourceId(window, 929);
    item->text = g_playerCountScreen->text;
    g_playerCountScreen->value = 1;
    XStdio_FormatBuffer(g_playerCountScreen->text, s_playerCountFormat, 1);
    return 0;
}
#endif
