#ifndef MENU_PAK_PROFILE_SAVE_BLOCKS_H
#define MENU_PAK_PROFILE_SAVE_BLOCKS_H
#include "COMMON/MENURECAT24.H"
extern void Timer_ReleaseSaveBlocks(void);
extern void Timer_SetSaveTrailerValue(s32 offset, s32 value);
extern void Timer_AllocateSaveBlock(void ***handle, void **data, s32 units);
extern char *Timer_GetSaveBlockByteCount(s32 block);
extern s32 Timer_GetSaveTrailerValue(s32 *block);
extern void Timer_CapturePlayerProfile(struct PlayerSavedProfileOwner *owner);
#endif
