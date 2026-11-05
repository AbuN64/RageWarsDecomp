#ifndef MENU_PLAYER_PLAYER_INITPLAYERSETTINGSSCREEN_SYMBOLS_H
#define MENU_PLAYER_PLAYER_INITPLAYERSETTINGSSCREEN_SYMBOLS_H
#include "types.h"
struct StateMenuSelectPlayerSettingsEntry;
extern struct StateMenuSelectPlayerSettingsEntry *g_playerSettingsScreen;
#if (!(defined(VERSION_EU) || defined(VERSION_EU_X)))
#endif
#if !((!(defined(VERSION_EU) || defined(VERSION_EU_X))))
extern char *g_matchOptionsCursorNormalLabelByLanguage[];
extern char *g_alternateSettingsModeLabels[];
extern u8 *g_optionsOffLabels[];
extern char *g_alternateSettingsControlLabels[];
extern char *g_alternateSettingsHandLabels[];
extern char *g_alternateSettingsFinalChoiceLabelsEu[];
extern char *g_alternateSettingsFinalChoiceLabelsEuX[];
#endif
#endif
