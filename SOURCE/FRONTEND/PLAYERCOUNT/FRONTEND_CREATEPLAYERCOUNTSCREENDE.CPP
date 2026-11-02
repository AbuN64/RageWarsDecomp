#include "include_asm.h"

#if defined(VERSION_DE)
typedef struct PlayerCountScreenStateDe {
    void *list;
    void *resourceWidget;
    void *item;
    s32 playerCount;
    char pad10[4];
    char text14[12];
    s32 selectionChanged;
} PlayerCountScreenStateDe;
typedef struct { char pad0[0x10]; u8 flags; char pad11[0x27]; void *text; } PlayerCountScreenPartView;
extern PlayerCountScreenStateDe *g_playerCountScreen;
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
    PlayerCountScreenPartView *part;
    g_playerCountScreen = (PlayerCountScreenStateDe *)Cache_AllocateMemory(36);
    Tsmos_ActivateControllerState();
    g_playerCountScreen->list = SmpFade_CreateFadeWidget(914, 915);
    SmpSlider_EnableTransition(g_playerCountScreen->list);
    SmpButton_WrapButtonWidget(918);
    part = (PlayerCountScreenPartView *)Node_FindWidgetByResourceId(root, 916);
    g_playerCountScreen->item = part;
    part->flags = 0xF;
    g_playerCountScreen->resourceWidget = SmpFlicker_CreateFlickerWidget(917, 110);
    g_playerCountScreen->playerCount = 3;
    part = (PlayerCountScreenPartView *)Node_FindWidgetByResourceId(root, 919);
    part->text = g_playerCountScreen->text14;
    g_playerCountScreen->selectionChanged = 1;
    XStdio_FormatBuffer(g_playerCountScreen->text14, s_playerCountFormat, 1);
    return 0;
}
#endif
