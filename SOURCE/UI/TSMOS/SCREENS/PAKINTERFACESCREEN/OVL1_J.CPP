#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_weaponLockedNoticeText[];
#if defined(VERSION_US_REV1)
/* 80408CB0_16.CPP */
/* g_frontendLoadoutResourceHalfwords_Ovl1J.CPP */
/* Resource IDs are read with lhu at +2 within each four-byte slot.
 * Keep the intervening halfwords: native u32 storage moves IDs to +0.
 * Player_CreateFourPlayerResults: 8043A198..8043A1E8, stride 0x4C. */
s32 g_frontendLoadoutResourceHalfwords[75] = {
    306, 234, 235, 236, 237, 238,
    239, 290, 289, 288, 287, 286,
    222, 224, 226, 228, 230, 232,
    247, 307, 273, 274, 275, 276,
    277, 278, 296, 297, 298, 299,
    300, 251, 253, 255, 257, 259,
    261, 207, 308, 240, 241, 242,
    243, 244, 245, 305, 304, 303,
    302, 301, 211, 213, 215, 217,
    219, 221, 249, 309, 279, 280,
    281, 282, 283, 284, 291, 292,
    293, 294, 295, 262, 264, 266,
    268, 270, 272,
};
/* g_LoadoutEquipmentItemsUsRev1_Ovl1J.CPP */
RestLoadoutEquipmentItemsUsRev1Layout775 g_LoadoutEquipmentItemsUsRev1 = {
    { 152, 5015, 10 },
    (void *)((char *)&g_weaponLockedNoticeText + 52),
    { 173, 5014, 12 },
    (void *)((char *)&g_weaponLockedNoticeText + 60),
    { 175, 5037, 11 },
    (void *)((char *)&g_weaponLockedNoticeText + 56),
};
/* g_loadoutWeaponItems_Ovl1J.CPP */
RestloadoutWeaponItemsLayout776 g_loadoutWeaponItems = {
    { 179, 5033, 1 },
    (void *)((char *)&g_weaponLockedNoticeText + 16),
    { 162, 5019, 15 },
    (void *)((char *)&g_weaponLockedNoticeText + 72),
    { 154, 5025, 13 },
    (void *)((char *)&g_weaponLockedNoticeText + 64),
    { 155, 5026, 9 },
    (void *)((char *)&g_weaponLockedNoticeText + 48),
    { 153, 5018, 8 },
    (void *)((char *)&g_weaponLockedNoticeText + 44),
    { 170, 5005, 14 },
    (void *)((char *)&g_weaponLockedNoticeText + 68),
    { 174, 5007, 7 },
    (void *)((char *)&g_weaponLockedNoticeText + 40),
    { 176, 5004, 2 },
    (void *)((char *)&g_weaponLockedNoticeText + 20),
};
/* g_LoadoutAbilitiesItemsUsRev1_Ovl1J.CPP */
RestLoadoutAbilitiesItemsUsRev1Layout777 g_LoadoutAbilitiesItemsUsRev1 = {
    { 169, 5031, 5 },
    (void *)((char *)&g_weaponLockedNoticeText + 32),
    { 171, 5022, 3 },
    (void *)((char *)&g_weaponLockedNoticeText + 24),
    { 172, 5011, 6 },
    (void *)((char *)&g_weaponLockedNoticeText + 36),
    { 177, 5003, 4 },
    (void *)((char *)&g_weaponLockedNoticeText + 28),
};
/* g_MenuEventHandlersE6804UsRev1_Ovl1J.CPP */
extern char addrLow_Player_StartFourPlayerResults[];
extern char addrLow_Player_UpdateFourPlayerResults[];
extern char addrLow_Player_DrawFourPlayerResults[];
RestMenuEventHandlersE6804UsRev1Record778 g_MenuEventHandlersE6804UsRev1 = {
    3591,
    8,
    (unsigned int)addrLow_Player_StartFourPlayerResults,
    3592,
    8,
    (unsigned int)addrLow_Player_UpdateFourPlayerResults,
    3594,
    8,
    (unsigned int)addrLow_Player_DrawFourPlayerResults,
};
/* g_MenuEventHandlersE6834UsRev1_Ovl1J.CPP */
/* ROM-grounded data: rodata/unresolved/800E59E6_unclaimed_E6828 */
extern char addrLow_Player_CreateFourPlayerResults[];
RestOvl1JEncodedWordsRecord779 g_Ovl1JEncodedWords = {
    3590,
    8,
    (unsigned int)addrLow_Player_CreateFourPlayerResults,
};
extern char addrLow_Frontend_ConfirmEquipmentSelection[];
extern char addrLow_Frontend_FreeEquipmentScreen[];
extern char addrLow_Frontend_RestoreEquipmentSelections[];
extern char addrLow_Frontend_SelectPreviousEquipmentColumn[];
extern char addrLow_Frontend_SelectNextEquipmentColumn[];
extern char addrLow_Frontend_SelectPreviousEquipmentChoice[];
extern char addrLow_Frontend_SelectNextEquipmentChoice[];
extern char addrLow_Frontend_CancelEquipmentSelection[];
RestMenuEventHandlersE6834UsRev1Record780 g_MenuEventHandlersE6834UsRev1 = {
    3587,
    8,
    (unsigned int)addrLow_Frontend_FreeEquipmentScreen,
    10,
    8,
    (unsigned int)addrLow_Frontend_RestoreEquipmentSelections,
    2,
    8,
    (unsigned int)addrLow_Frontend_CancelEquipmentSelection,
    1,
    8,
    (unsigned int)addrLow_Frontend_ConfirmEquipmentSelection,
    7,
    30000,
    (unsigned int)addrLow_Frontend_SelectPreviousEquipmentChoice,
    5,
    30000,
    (unsigned int)addrLow_Frontend_SelectPreviousEquipmentColumn,
    8,
    30000,
    (unsigned int)addrLow_Frontend_SelectNextEquipmentChoice,
    6,
    30000,
    (unsigned int)addrLow_Frontend_SelectNextEquipmentColumn,
    { 0x00000000, 0x00000000, 0x00000000 },
};
#endif
