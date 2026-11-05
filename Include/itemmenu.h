#ifndef ITEMMENU_H
#define ITEMMENU_H
#include "Common/hud_effects.h"
#include "System/timed_effect_and_item_menu_views.h"
struct CItem;
extern void ItemMenu_ResetEntries(CItemMenu *rec);

extern s32 ItemMenu_IsSelectedEntryActive(void *);
extern s32 ItemMenu_AdvanceSelection(CItemMenu *menu, s32 backward);
extern void ItemMenu_ClearEntry(struct CItem *);
extern void ItemMenu_ToggleEntry(void *, void *);
extern s32 ItemMenu_RestoreBootMemory(void);
extern void ItemMenu_RestoreBootMemoryNoOp(void);
extern s32 ItemMenu_IsRestorableAddress(u32 address);
extern void ItemMenu_IsRestorableAddressNoOp(void);
struct ToggleMenu;
struct ToggleMenuPlayerInputView;
struct CItemMenu_t;
struct Player;
void ItemMenu_DrawEntries(struct CItemMenu_t *panel, struct Player *player);
s32 ItemMenu_SetEntry(char *menu, s32 entryValue, s32 entryKey, s32 imageResource, s32 imageFrame, f32 restoreValue, s32 restoreExtra, s32 selectCallbackAddress, s32 updateCallbackAddress);
struct CItemMenu_t;
struct Player;
void ItemMenu_UpdateToggleMenu(struct CItemMenu_t *menu, struct Player *input);
#endif
