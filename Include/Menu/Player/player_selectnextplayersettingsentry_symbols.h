#ifndef MENU_PLAYER_PLAYER_SELECTNEXTPLAYERSETTINGSENTRY_SYMBOLS_H
#define MENU_PLAYER_PLAYER_SELECTNEXTPLAYERSETTINGSENTRY_SYMBOLS_H
#include "Menu/Player/player_initplayersettingsscreen_symbols.h"
#include "types.h"
typedef s32 (*PlayerSettingsEventHandler)(void *, s32, s32, s32, s32);
extern PlayerSettingsEventHandler g_playerSettingsEventHandlers;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern s32 g_playerSettingsSlotNumberTranslations[];
#else
#endif
#endif
