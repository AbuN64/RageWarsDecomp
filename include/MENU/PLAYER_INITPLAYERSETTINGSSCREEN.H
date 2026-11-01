#ifndef MENU_PLAYER_INITPLAYERSETTINGSSCREEN_H
#define MENU_PLAYER_INITPLAYERSETTINGSSCREEN_H
#include "COMMON/MENULISTSCREEN.H"
extern void Player_StorePlayerSettingsEntry(s32);
extern u8 g_profileSlotSettingsByte7D[];
extern u8 g_profileSlotSettingsByte79[];
extern u8 g_profileSlotSettingsByte7A[];
extern u8 g_profileSlotSettingsByte82[];
void Player_SelectPlayerSettingsEntry(s32);
#endif
