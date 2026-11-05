#ifndef MENU_PLAYER_PLAYER_SELECTNEXTALTERNATEPLAYERSETTINGSENTRY_SYMBOLS_H
#define MENU_PLAYER_PLAYER_SELECTNEXTALTERNATEPLAYERSETTINGSENTRY_SYMBOLS_H
#include "Menu/Player/player_storealternateplayersettingsentry_symbols.h"
#include "types.h"
struct StyleNextState;
typedef s32 (*AlternatePlayerSettingsEventHandler)(void *, s32, s32, s32, s32);
extern AlternatePlayerSettingsEventHandler g_alternatePlayerSettingsEventHandlers;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern s32 g_playerSettingsSlotNumberTranslations[];
#else
#endif
#endif
