#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "include_asm.h"

#if defined(VERSION_EU)
#include "TYPES.H"
extern struct PlayerCountScreenState *g_playerCountScreen;
extern char s_playerCountFormat[];
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Tsmos_ActivateControllerState(void);
extern void *SmpFade_CreateFadeWidget(s32, s32);
extern void SmpSlider_EnableTransition(struct Access_s32_5C *object);
extern void SmpButton_WrapButtonWidget(s32);
extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);
extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);
/* Builds a three-row slider popup in its 0x24-byte state g_playerCountScreen: title/list from the ids at 0x398, the numeric
   readout item at 0x39D showing the text at +0x14 formatted with s_playerCountFormat. Returns 0. */
s32 Frontend_CreatePlayerCountScreenEu(void *window) {
    MenuWidget *item;
    void *title;

    g_playerCountScreen = Cache_AllocateMemory(36);
    Tsmos_ActivateControllerState();
    title = SmpFade_CreateFadeWidget(920, 921);
    g_playerCountScreen->menu = title;
    SmpSlider_EnableTransition(title);
    SmpButton_WrapButtonWidget(924);
    item = Node_FindWidgetByResourceId(window, 922);
    g_playerCountScreen->window = item;
    item->alpha = 15;
    g_playerCountScreen->button = SmpFlicker_CreateFlickerWidget(923, 110);
    g_playerCountScreen->delay = 3;
    item = Node_FindWidgetByResourceId(window, 925);
    item->text = g_playerCountScreen->text;
    g_playerCountScreen->value = 1;
    XStdio_FormatBuffer(g_playerCountScreen->text, s_playerCountFormat, 1);
    return 0;
}
#endif
