#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "include_asm.h"

#if defined(VERSION_DE)
extern struct PlayerCountScreenState *g_playerCountScreen;
extern char s_playerCountFormat[];
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Tsmos_ActivateControllerState(void);
extern void *SmpFade_CreateFadeWidget(s32 a, s32 b);
extern void SmpSlider_EnableTransition(struct Access_s32_5C *object);
extern void SmpButton_WrapButtonWidget(s32 a);
extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);
extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);
/* Builds the 0x24-byte state g_playerCountScreen from the resources 0x392 to 0x397, hooks its list at 0x14 into the part Node_FindWidgetByResourceId returns for 0x397 and registers it with XStdio_FormatBuffer; returns zero. */
s32 Frontend_CreatePlayerCountScreenDe(s32 root) {
    MenuWidget *part;
    g_playerCountScreen = (struct PlayerCountScreenState *)Cache_AllocateMemory(36);
    Tsmos_ActivateControllerState();
    g_playerCountScreen->menu = SmpFade_CreateFadeWidget(914, 915);
    SmpSlider_EnableTransition(g_playerCountScreen->menu);
    SmpButton_WrapButtonWidget(918);
    part = (MenuWidget *)Node_FindWidgetByResourceId(root, 916);
    g_playerCountScreen->window = part;
    part->alpha = 0xF;
    g_playerCountScreen->button = SmpFlicker_CreateFlickerWidget(917, 110);
    g_playerCountScreen->delay = 3;
    part = (MenuWidget *)Node_FindWidgetByResourceId(root, 919);
    part->text = g_playerCountScreen->text;
    g_playerCountScreen->value = 1;
    XStdio_FormatBuffer(g_playerCountScreen->text, s_playerCountFormat, 1);
    return 0;
}
#endif
