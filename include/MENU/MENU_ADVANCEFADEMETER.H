#ifndef MENU_MENU_ADVANCEFADEMETER_H
#define MENU_MENU_ADVANCEFADEMETER_H
#include "COMMON/NUMBERPADSCREEN.H"
extern s32 Menu_GetFadeMeterDone(s32 *record);
extern s32 Menu_AdvanceFadeMeter(struct Meter *meter, s32 step);
extern s32 Menu_DispatchSixChoiceEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount);
extern void Menu_SetFadeMeterDirection(struct Triple *timer, s32 mode);
extern void Menu_InitializeFadeMeter(struct RecGobjinstSampleBoneTranslation *record, s32 value);
#endif
