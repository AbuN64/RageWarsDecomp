#ifndef GAME_GAME_H
#define GAME_GAME_H
s32 Frontend_SelectNextLanguage(void *window, s32 b, s32 c, s32 press);
s32 Frontend_SelectPreviousLanguage(void *window, s32 b, s32 c, s32 press);
struct Shared_PlayerSettingsRecord;
void Items_CopyDefaultLocalizedPlayerName(struct Shared_PlayerSettingsRecord *record);
void Items_SetDefaultPlayerName(u8 *record);
#endif
