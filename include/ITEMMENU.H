#ifndef ITEMMENU_H
#define ITEMMENU_H
#include "COMMON/OBJRECAT18V6.H"
#include "SYSTEM/TIMED_EFFECT_AND_ITEM_MENU_VIEWS.H"
extern void ItemMenu_ResetEntries(CItemMenu *rec);

extern s32 ItemMenu_IsSelectedEntryActive(void *);
extern s32 ItemMenu_AdvanceSelection(ItemMenuCursorState *menu, s32 backward);
extern void ItemMenu_ClearEntry(CItem *);
extern void ItemMenu_ToggleEntry(void *, void *);
extern s32 ItemMenu_RestoreBootMemory(void);
extern void ItemMenu_RestoreBootMemoryNoOp(void);
extern s32 ItemMenu_IsRestorableAddress(u32 address);
extern void ItemMenu_IsRestorableAddressNoOp(void);
struct ToggleMenu;
struct ToggleMenuPlayerInputView;
void ItemMenu_DrawEntries(struct ToggleMenu *panel, struct ToggleMenuPlayerInputView *player);
s32 ItemMenu_SetEntry(char *menu, s32 entryValue, s32 entryKey, s32 imageResource, s32 imageFrame, f32 restoreValue, s32 restoreExtra, s32 selectCallbackAddress, s32 updateCallbackAddress);
void ItemMenu_UpdateToggleMenu(struct ToggleMenu *menu, struct ToggleMenuPlayerInputView *input);
#endif
