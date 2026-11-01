#include "DATA/OVL1_J/MENU_SELECTEUROPEANPAKACTIONLABEL.H"
#include "DATA/UI/EVENT_HANDLER_RECORD.H"
#if defined(VERSION_US)
/* 80408CB0_11.CPP */
/* g_equipmentAndPlayerSettingsMenuDataEuX_MenuSelecteuropeanpakactionlabel.CPP */
extern char addrLow_Player_CreateFourPlayerResults[];
extern char addrLow_Player_StartFourPlayerResults[];
extern char addrLow_Player_UpdateFourPlayerResults[];
extern char addrLow_Player_DrawFourPlayerResults[];
extern char addrLow_Frontend_ConfirmEquipmentSelection[];
extern char addrLow_Frontend_FreeEquipmentScreen[];
extern char addrLow_Frontend_RestoreEquipmentSelections[];
extern char addrLow_Frontend_SelectPreviousEquipmentColumn[];
extern char addrLow_Frontend_SelectNextEquipmentColumn[];
extern char addrLow_Frontend_SelectPreviousEquipmentChoice[];
extern char addrLow_Frontend_SelectNextEquipmentChoice[];
extern char addrLow_Frontend_CancelEquipmentSelection[];
unsigned int g_equipmentAndPlayerSettingsMenuDataEuX[174] = {
    0x00000132, 0x000000EA, 0x000000EB, 0x000000EC, 0x000000ED, 0x000000EE, 0x000000EF, 0x00000122,
    0x00000121, 0x00000120, 0x0000011F, 0x0000011E, 0x000000DE, 0x000000E0, 0x000000E2, 0x000000E4,
    0x000000E6, 0x000000E8, 0x000000F7, 0x00000133, 0x00000111, 0x00000112, 0x00000113, 0x00000114,
    0x00000115, 0x00000116, 0x00000128, 0x00000129, 0x0000012A, 0x0000012B, 0x0000012C, 0x000000FB,
    0x000000FD, 0x000000FF, 0x00000101, 0x00000103, 0x00000105, 0x000000CF, 0x00000134, 0x000000F0,
    0x000000F1, 0x000000F2, 0x000000F3, 0x000000F4, 0x000000F5, 0x00000131, 0x00000130, 0x0000012F,
    0x0000012E, 0x0000012D, 0x000000D3, 0x000000D5, 0x000000D7, 0x000000D9, 0x000000DB, 0x000000DD,
    0x000000F9, 0x00000135, 0x00000117, 0x00000118, 0x00000119, 0x0000011A, 0x0000011B, 0x0000011C,
    0x00000123, 0x00000124, 0x00000125, 0x00000126, 0x00000127, 0x00000106, 0x00000108, 0x0000010A,
    0x0000010C, 0x0000010E, 0x00000110, 0x00000098, 0x00001397, 0x0000000A, 0x800D1D9C, 0x000000AD,
    0x00001396, 0x0000000C, 0x800D1DA4, 0x000000AF, 0x000013AD, 0x0000000B, 0x800D1DA0, 0x000000B3,
    0x000013A9, 0x00000001, 0x800D1D78, 0x000000A2, 0x0000139B, 0x0000000F, 0x800D1DB0, 0x0000009A,
    0x000013A1, 0x0000000D, 0x800D1DA8, 0x0000009B, 0x000013A2, 0x00000009, 0x800D1D98, 0x00000099,
    0x0000139A, 0x00000008, 0x800D1D94, 0x000000AA, 0x0000138D, 0x0000000E, 0x800D1DAC, 0x000000AE,
    0x0000138F, 0x00000007, 0x800D1D90, 0x000000B0, 0x0000138C, 0x00000002, 0x800D1D7C, 0x000000A9,
    0x000013A7, 0x00000005, 0x800D1D88, 0x000000AB, 0x0000139E, 0x00000003, 0x800D1D80, 0x000000AC,
    0x00001393, 0x00000006, 0x800D1D8C, 0x000000B1, 0x0000138B, 0x00000004, 0x800D1D84, 0x00000E07,
    0x00000008, (unsigned int)addrLow_Player_StartFourPlayerResults, 0x00000E08, 0x00000008, (unsigned int)addrLow_Player_UpdateFourPlayerResults, 0x00000E0A, 0x00000008, (unsigned int)addrLow_Player_DrawFourPlayerResults,
    0x00000E06, 0x00000008, (unsigned int)addrLow_Player_CreateFourPlayerResults, 0x00000E03, 0x00000008, (unsigned int)addrLow_Frontend_FreeEquipmentScreen, 0x0000000A, 0x00000008,
    (unsigned int)addrLow_Frontend_RestoreEquipmentSelections, 0x00000002, 0x00000008, (unsigned int)addrLow_Frontend_CancelEquipmentSelection, 0x00000001, 0x00000008, (unsigned int)addrLow_Frontend_ConfirmEquipmentSelection, 0x00000007,
    0x00007530, (unsigned int)addrLow_Frontend_SelectPreviousEquipmentChoice, 0x00000005, 0x00007530, (unsigned int)addrLow_Frontend_SelectPreviousEquipmentColumn, 0x00000008, 0x00007530, (unsigned int)addrLow_Frontend_SelectNextEquipmentChoice,
    0x00000006, 0x00007530, (unsigned int)addrLow_Frontend_SelectNextEquipmentColumn, 0x00000000, 0x00000000, 0x00000000,
};
#endif
#if defined(VERSION_US_REV1)
/* g_titleButtonEventHandlerRecordsUsRev1_MenuSelecteuropeanpakactionlabel.CPP */
EventHandlerRecord g_titleButtonEventHandlerRecordsUsRev1[7] = {
    { 3592, 30, g_Menu_UpdateTitleButtonScreenAddress },
    { 3590, 30, g_Menu_CreateTitleButtonScreenAddress },
    { 3591, 30, g_Menu_WrapTitleButtonScreenNodesAddress },
    { 3587, 30, g_Menu_FreeTitleButtonScreenAddress },
    { 1, 30, g_Menu_HandleTitleButtonChoiceAddress },
    { 2, 30, g_Menu_CancelTitleButtonScreenAddress },
    { 0, 0, 0 },
};
#endif
