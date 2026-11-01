#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"

/* g_EquipActivateequipmentpanelHalfwordsLabel.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
s16 g_EquipActivateequipmentpanelHalfwords1[1] = {
    209,
};
#endif

/* g_EquipActivateequipmentpanelPointerWordsLabel.CPP */
#if defined(VERSION_EU)
extern char g_Player_CreateFourPlayerResultsPackedAddress242[];
extern char g_Player_StartFourPlayerResultsPackedAddress242[];
extern char g_Player_UpdateFourPlayerResultsPackedAddress242[];
extern char g_Player_DrawFourPlayerResultsPackedAddress242[];
extern char g_Frontend_ConfirmEquipmentSelectionPackedAddress242[];
extern char g_Frontend_FreeEquipmentScreenPackedAddress242[];
extern char g_Frontend_RestoreEquipmentSelectionsPackedAddress242[];
extern char g_Frontend_SelectPreviousEquipmentColumnPackedAddress242[];
extern char g_Frontend_SelectNextEquipmentColumnPackedAddress242[];
extern char g_Frontend_SelectPreviousEquipmentChoicePackedAddress242[];
extern char g_Frontend_SelectNextEquipmentChoicePackedAddress242[];
extern char g_Frontend_CancelEquipmentSelectionPackedAddress242[];
s32 g_EquipActivateequipmentpanelPointerWords1[174] = {
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
    268, 270, 272, 152, 5015, 10,
    -2146562540, 173, 5014, 12, -2146562508, 175,
    5037, 11, -2146562524, 179, 5033, 1,
    -2146562684, 162, 5019, 15, -2146562460, 154,
    5025, 13, -2146562492, 155, 5026, 9,
    -2146562556, 153, 5018, 8, -2146562572, 170,
    5005, 14, -2146562476, 174, 5007, 7,
    -2146562588, 176, 5004, 2, -2146562668, 169,
    5031, 5, -2146562620, 171, 5022, 3,
    -2146562652, 172, 5011, 6, -2146562604, 177,
    5003, 4, -2146562636, 3591, 8, (unsigned int)g_Player_StartFourPlayerResultsPackedAddress242,
    3592, 8, (unsigned int)g_Player_UpdateFourPlayerResultsPackedAddress242, 3594, 8, (unsigned int)g_Player_DrawFourPlayerResultsPackedAddress242,
    3590, 8, (unsigned int)g_Player_CreateFourPlayerResultsPackedAddress242, 3587, 8, (unsigned int)g_Frontend_FreeEquipmentScreenPackedAddress242,
    10, 8, (unsigned int)g_Frontend_RestoreEquipmentSelectionsPackedAddress242, 2, 8, (unsigned int)g_Frontend_CancelEquipmentSelectionPackedAddress242,
    1, 8, (unsigned int)g_Frontend_ConfirmEquipmentSelectionPackedAddress242, 7, 30000, (unsigned int)g_Frontend_SelectPreviousEquipmentChoicePackedAddress242,
    5, 30000, (unsigned int)g_Frontend_SelectPreviousEquipmentColumnPackedAddress242, 8, 30000, (unsigned int)g_Frontend_SelectNextEquipmentChoicePackedAddress242,
    6, 30000, (unsigned int)g_Frontend_SelectNextEquipmentColumnPackedAddress242, 0, 0, 0,
};
#endif
