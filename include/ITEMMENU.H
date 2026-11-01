#ifndef ITEMMENU_H
#define ITEMMENU_H
#include "COMMON/OBJRECAT18V6.H"
#include "SYSTEM/TIMED_EFFECT_AND_ITEM_MENU_VIEWS.H"
extern void ItemMenu_ResetEntries(CItemMenu *rec);
extern s32 ItemMenu_SetEntry(char *, s32, s32, s32, s32, f32, s32, s32, s32);
extern s32 ItemMenu_IsSelectedEntryActive(void *);
extern s32 ItemMenu_AdvanceSelection(ItemMenuCursorState *menu, s32 backward);
extern void ItemMenu_ClearEntry(CItem *);
extern void ItemMenu_ToggleEntry(void *, void *);
extern s32 ItemMenu_RestoreBootMemory(void);
extern void ItemMenu_RestoreBootMemoryNoOp(void);
extern s32 ItemMenu_IsRestorableAddress(u32 address);
extern void ItemMenu_IsRestorableAddressNoOp(void);
#endif
