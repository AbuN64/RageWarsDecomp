#include "include_asm.h"
#if defined(VERSION_US_REV1)
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/REQUESTRECAT10.H"
#include "TYPES.H"
#include "COMMON/SHARED_MENUREPLY.H"
#endif
#if defined(VERSION_EU_X)
#include "TYPES.H"
/* 80406A88_14.CPP */
typedef struct { void *list; s32 resourceWidget; void *item; s32 scrollDelay; s32 reservedWord10; char text14[12]; s32 playerCount; } SliderPopupEu;
typedef struct { u8 pad0[0x10]; u8 alpha; u8 pad11[0x27]; void *text; } SliderItemEu;
extern SliderPopupEu *g_playerCountScreen;
extern char s_playerCountFormat[];
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Tsmos_ActivateControllerState(void);
extern void *SmpFade_CreateFadeWidget(s32, s32);
extern void SmpSlider_EnableTransition(struct Access_s32_5C *object);
extern void SmpButton_WrapButtonWidget(s32);
extern void *Node_FindWidgetByResourceId(void *, s32);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);
extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);
/* Builds a three-row slider popup in its 0x24-byte state g_playerCountScreen: title/list from the ids at 0x39C, the numeric
   readout item at 0x39D showing the text at +0x14 formatted with s_playerCountFormat. Returns 0. */
s32 Frontend_CreatePlayerCountScreenEux(void *window) {
    SliderItemEu *item;
    void *title;

    g_playerCountScreen = Cache_AllocateMemory(36);
    Tsmos_ActivateControllerState();
    title = SmpFade_CreateFadeWidget(924, 925);
    g_playerCountScreen->list = title;
    SmpSlider_EnableTransition(title);
    SmpButton_WrapButtonWidget(928);
    item = Node_FindWidgetByResourceId(window, 926);
    g_playerCountScreen->item = item;
    item->alpha = 15;
    g_playerCountScreen->resourceWidget = SmpFlicker_CreateFlickerWidget(927, 110);
    g_playerCountScreen->scrollDelay = 3;
    item = Node_FindWidgetByResourceId(window, 929);
    item->text = g_playerCountScreen->text14;
    g_playerCountScreen->playerCount = 1;
    XStdio_FormatBuffer(g_playerCountScreen->text14, s_playerCountFormat, 1);
    return 0;
}
#endif
