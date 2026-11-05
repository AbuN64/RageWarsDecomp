#ifndef MENU_MENU_ADVANCEFADEMETER_H
#define MENU_MENU_ADVANCEFADEMETER_H
#include "Common/numberpadscreen.h"
#include "Common/struct_fade_meter_record.h"
extern s32 Menu_GetFadeMeterDone(struct Meter *record);
extern s32 Menu_AdvanceFadeMeter(struct Meter *meter, s32 step);
extern s32 Menu_DispatchPakActionEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount);
extern void Menu_SetFadeMeterDirection(struct Meter *timer, s32 mode);
extern void Menu_InitializeFadeMeter(struct FadeMeterRecord *record, s32 value);
extern s32 SmpSlider_GetTransitionMode(s32);
struct ObjMenuUpdatePakActionMenu {
    char pad[0x44];
    struct MenuWidget *transitionCell;
};
typedef struct ChoiceMenuState {
    struct ObjMenuUpdatePakActionMenu *slider;
    s32 labelFlicker;
    struct MenuWidget *transitionCell;
    s32 transitionTimer;
    s32 nextScreen;
} ChoiceMenuState;

#endif
