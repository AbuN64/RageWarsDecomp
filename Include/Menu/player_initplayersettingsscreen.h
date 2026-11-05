#ifndef MENU_PLAYER_INITPLAYERSETTINGSSCREEN_H
#define MENU_PLAYER_INITPLAYERSETTINGSSCREEN_H
#include "Common/menulistscreen.h"
extern void Player_StorePlayerSettingsEntry(s32);
extern u8 g_profileSlotSettingsSecondaryListSelection[];
extern u8 g_profileSlotSettingsPrimarySliderItem[];
extern u8 g_profileSlotSettingsSecondarySliderItem[];
extern u8 g_profileSlotSettingsExtraListSelection[];
void Player_SelectPlayerSettingsEntry(s32);
#endif
