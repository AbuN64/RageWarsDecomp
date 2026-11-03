#ifndef UI_TSMOS_SMP_SMP_BUTTON_H
#define UI_TSMOS_SMP_SMP_BUTTON_H
struct MenuListWidget *SmpButton_CreateListWidget(s32 listWidgetId, s32 itemWidgetId);
struct MenuListWidget;
void SmpButton_SelectListEntry(struct MenuListWidget *menu, s32 index);
#endif
