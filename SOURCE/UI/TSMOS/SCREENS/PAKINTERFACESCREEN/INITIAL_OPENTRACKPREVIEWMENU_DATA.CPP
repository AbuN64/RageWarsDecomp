#include "include_asm.h"
#include "DATA/UI/EVENT_HANDLER_RECORD.H"
#if defined(VERSION_US)
unsigned int g_InitialOpentrackpreviewmenuTrailingWordUs[1] = {
    0x000A080C,
};
#endif
#if defined(VERSION_US_REV1)
/* 80408AC4_18.CPP */
/* g_playerSettingsCreateEventRecordUsRev1_InitialOpentrackpreviewmenuData.CPP */
/* ROM-grounded data: rodata/unresolved/800E5698_unclaimed_E62B0 */
extern char g_Player_InitPlayerSettingsScreenAddress[];
EventHandlerRecord g_playerSettingsCreateEventRecordUsRev1[1] = {
    { 3590, 5, g_Player_InitPlayerSettingsScreenAddress },
};
extern char g_Player_FreePlayerSettingsScreenAddress[];
extern char g_playerSettingsUnhandledEventCallbackAddressUsRev1[];
extern char g_Player_ConfirmPlayerSettingsEntryAddress[];
extern char g_Player_CancelPlayerSettingsEntryAddress[];
extern char g_Player_SelectNextPlayerSettingsEntryAddress[];
extern char g_Player_SelectPreviousPlayerSettingsEntryAddress[];
EventHandlerRecord g_playerSettingsEventHandlerRecordsUsRev1[7] = {
    { 3587, 5, g_Player_FreePlayerSettingsScreenAddress },
    { 10, 5, g_playerSettingsUnhandledEventCallbackAddressUsRev1 },
    { 2, 5, g_Player_CancelPlayerSettingsEntryAddress },
    { 1, 5, g_Player_ConfirmPlayerSettingsEntryAddress },
    { 8, 94, g_Player_SelectNextPlayerSettingsEntryAddress },
    { 7, 94, g_Player_SelectPreviousPlayerSettingsEntryAddress },
    { 0, 0, 0 },
};
/* g_alternatePlayerSettingsEventHandlerRecordsUsRev1_InitialOpentrackpreviewmenuData.CPP */
extern char g_Player_BuildItemLabelListAddress[];
extern char g_Player_FreeAlternatePlayerSettingsScreenAddress[];
extern char g_alternatePlayerSettingsUnhandledEventCallbackAddressUsRev1[];
extern char g_alternatePlayerSettingsUnhandledEventCallbackAddressUsRev1Alternate[];
extern char g_Player_ConfirmAlternatePlayerSettingsEntryAddress[];
extern char g_Player_CancelAlternatePlayerSettingsEntryAddress[];
extern char g_Player_SelectNextAlternatePlayerSettingsEntryAddress[];
extern char g_Player_SelectPreviousAlternatePlayerSettingsEntryAddress[];
EventHandlerRecord g_alternatePlayerSettingsEventHandlerRecordsUsRev1[9] = {
    { 3591, 12, g_alternatePlayerSettingsUnhandledEventCallbackAddressUsRev1 },
    { 3592, 12, g_alternatePlayerSettingsUnhandledEventCallbackAddressUsRev1Alternate },
    { 3590, 12, g_Player_BuildItemLabelListAddress },
    { 3587, 12, g_Player_FreeAlternatePlayerSettingsScreenAddress },
    { 2, 12, g_Player_CancelAlternatePlayerSettingsEntryAddress },
    { 1, 12, g_Player_ConfirmAlternatePlayerSettingsEntryAddress },
    { 8, 454, g_Player_SelectNextAlternatePlayerSettingsEntryAddress },
    { 7, 454, g_Player_SelectPreviousAlternatePlayerSettingsEntryAddress },
    { 0, 0, 0 },
};
/* g_playerSettingsPackedTextFragmentUsRev1_InitialOpentrackpreviewmenuData.CPP */
/* ROM-grounded data: rodata/unresolved/800E5698_unclaimed_E62B0_unclaimed_E6310_unclaimed_E637C */
char g_playerSettingsPackedTextFragmentUsRev1[4] =
    "LL_S";
#endif
#if defined(VERSION_EU_X)
/* g_equipmentAndPlayerSettingsMenuDataEu_InitialOpentrackpreviewmenuData.CPP */
extern char g_Player_CreateFourPlayerResultsAddress[];
extern char g_Player_StartFourPlayerResultsAddress[];
extern char g_Player_UpdateFourPlayerResultsAddress[];
extern char g_Player_DrawFourPlayerResultsAddress[];
extern char g_Frontend_ConfirmEquipmentSelectionAddress[];
extern char g_Frontend_FreeEquipmentScreenAddress[];
extern char g_Frontend_RestoreEquipmentSelectionsAddress[];
extern char g_Frontend_SelectPreviousEquipmentChoicePackedAddress242[];
extern char g_Frontend_SelectNextEquipmentColumnAddress[];
extern char g_Frontend_SelectPreviousEquipmentChoiceAddress[];
extern char g_Frontend_SelectNextEquipmentChoiceAddress[];
extern char g_Frontend_CancelEquipmentSelectionAddress[];
unsigned int g_equipmentAndPlayerSettingsMenuDataEu[174] = {
    0x00000136, 0x000000EE, 0x000000EF, 0x000000F0, 0x000000F1, 0x000000F2, 0x000000F3, 0x00000126,
    0x00000125, 0x00000124, 0x00000123, 0x00000122, 0x000000E2, 0x000000E4, 0x000000E6, 0x000000E8,
    0x000000EA, 0x000000EC, 0x000000FB, 0x00000137, 0x00000115, 0x00000116, 0x00000117, 0x00000118,
    0x00000119, 0x0000011A, 0x0000012C, 0x0000012D, 0x0000012E, 0x0000012F, 0x00000130, 0x000000FF,
    0x00000101, 0x00000103, 0x00000105, 0x00000107, 0x00000109, 0x000000D3, 0x00000138, 0x000000F4,
    0x000000F5, 0x000000F6, 0x000000F7, 0x000000F8, 0x000000F9, 0x00000135, 0x00000134, 0x00000133,
    0x00000132, 0x00000131, 0x000000D7, 0x000000D9, 0x000000DB, 0x000000DD, 0x000000DF, 0x000000E1,
    0x000000FD, 0x00000139, 0x0000011B, 0x0000011C, 0x0000011D, 0x0000011E, 0x0000011F, 0x00000120,
    0x00000127, 0x00000128, 0x00000129, 0x0000012A, 0x0000012B, 0x0000010A, 0x0000010C, 0x0000010E,
    0x00000110, 0x00000112, 0x00000114, 0x00000098, 0x00001397, 0x0000000A, 0x800DCD04, 0x000000AD,
    0x00001396, 0x0000000C, 0x800DCD1C, 0x000000AF, 0x000013AD, 0x0000000B, 0x800DCD10, 0x000000B3,
    0x000013A9, 0x00000001, 0x800DCC98, 0x000000A2, 0x0000139B, 0x0000000F, 0x800DCD40, 0x0000009A,
    0x000013A1, 0x0000000D, 0x800DCD28, 0x0000009B, 0x000013A2, 0x00000009, 0x800DCCF8, 0x00000099,
    0x0000139A, 0x00000008, 0x800DCCEC, 0x000000AA, 0x0000138D, 0x0000000E, 0x800DCD34, 0x000000AE,
    0x0000138F, 0x00000007, 0x800DCCE0, 0x000000B0, 0x0000138C, 0x00000002, 0x800DCCA4, 0x000000A9,
    0x000013A7, 0x00000005, 0x800DCCC8, 0x000000AB, 0x0000139E, 0x00000003, 0x800DCCB0, 0x000000AC,
    0x00001393, 0x00000006, 0x800DCCD4, 0x000000B1, 0x0000138B, 0x00000004, 0x800DCCBC, 0x00000E07,
    0x00000008, (unsigned int)g_Player_StartFourPlayerResultsAddress, 0x00000E08, 0x00000008, (unsigned int)g_Player_UpdateFourPlayerResultsAddress, 0x00000E0A, 0x00000008, (unsigned int)g_Player_DrawFourPlayerResultsAddress,
    0x00000E06, 0x00000008, (unsigned int)g_Player_CreateFourPlayerResultsAddress, 0x00000E03, 0x00000008, (unsigned int)g_Frontend_FreeEquipmentScreenAddress, 0x0000000A, 0x00000008,
    (unsigned int)g_Frontend_RestoreEquipmentSelectionsAddress, 0x00000002, 0x00000008, (unsigned int)g_Frontend_CancelEquipmentSelectionAddress, 0x00000001, 0x00000008, (unsigned int)g_Frontend_ConfirmEquipmentSelectionAddress, 0x00000007,
    0x00007530, (unsigned int)g_Frontend_SelectPreviousEquipmentChoiceAddress, 0x00000005, 0x00007530, (unsigned int)g_Frontend_SelectPreviousEquipmentChoicePackedAddress242, 0x00000008, 0x00007530, (unsigned int)g_Frontend_SelectNextEquipmentChoiceAddress,
    0x00000006, 0x00007530, (unsigned int)g_Frontend_SelectNextEquipmentColumnAddress, 0x00000000, 0x00000000, 0x00000000,
};
#endif
