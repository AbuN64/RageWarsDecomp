#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"

/* g_joinOptionsInitialWord_MenuRandomizecharacterpreviewData.CPP */
/* ROM-grounded data: rodata/writable/800E39C0 */
s32 g_joinOptionsInitialWord[1] = {
    0,
};

/* g_joinOptionsEventHandlerRecords_MenuRandomizecharacterpreviewData.CPP */
/* Menu event handler registry: eleven 12-byte records of {event id, sub id 0x17, handler address
   in the Join_CreateUsJoinOptionsMenu_MenuRandomizecharacterpreviewData-family menu code}, followed by a three-word tail. The handler addresses sit
   in each cartridge's own menu code, so only the tail words are cartridge-stable in some pairs;
   the tail differs per cartridge and the records keep the ids common to all of them. */
#if defined(VERSION_DE)
extern char g_Menu_CreateGermanCourseOptionsAddress[];
extern char g_Frontend_SelectPreviousJoinModelAddress[];
extern char g_Frontend_SelectNextJoinModelAddress[];
extern char g_Join_DestroyJoinOptionsMenuAddress[];
extern char g_Join_PulseJoinSelectionHighlightAddress[];
extern char g_Join_RequestJoinOptionsExitAddress[];
extern char g_Join_RequestJoinOptionsExitAlternateAddress[];
extern char g_Join_SelectPreviousJoinRowAddress[];
extern char g_Join_SelectNextJoinRowAddress[];
extern char g_Join_CycleJoinRequestRankAddress[];
RestjoinOptionsEventHandlerRecordsRecord442 g_joinOptionsEventHandlerRecords = {
    3590,
    23,
    (unsigned int)g_Menu_CreateGermanCourseOptionsAddress,
    3587,
    23,
    (unsigned int)g_Join_DestroyJoinOptionsMenuAddress,
    3592,
    23,
    (unsigned int)g_Join_PulseJoinSelectionHighlightAddress,
    2,
    23,
    (unsigned int)g_Join_RequestJoinOptionsExitAlternateAddress,
    1,
    23,
    (unsigned int)g_Join_RequestJoinOptionsExitAddress,
    7,
    23,
    (unsigned int)g_Frontend_SelectPreviousJoinModelAddress,
    8,
    23,
    (unsigned int)g_Frontend_SelectNextJoinModelAddress,
    5,
    23,
    (unsigned int)g_Join_SelectPreviousJoinRowAddress,
    6,
    23,
    (unsigned int)g_Join_SelectNextJoinRowAddress,
    10,
    23,
    (unsigned int)g_Join_CycleJoinRequestRankAddress,
    { 0x00000000, 0x00000000, 0x00000000, 0x00000023, 0x3E0F5C29 },
};
#elif defined(VERSION_EU)
extern char g_Menu_CreateEuJoinOptionsCallbackAddressEu[];
extern char g_Frontend_SelectPreviousJoinModelAddressVariant2[];
extern char g_Frontend_SelectNextJoinModelAddressVariant2[];
extern char g_Join_DestroyJoinOptionsMenuAddressVariant3[];
extern char g_Join_PulseJoinSelectionHighlightAddressVariant3[];
extern char g_Join_RequestJoinOptionsExitAddressVariant3[];
extern char g_Join_RequestJoinOptionsExitAlternateAddressVariant3[];
extern char g_Join_SelectPreviousJoinRowAddressVariant3[];
extern char g_Join_SelectNextJoinRowAddressVariant3[];
extern char g_Join_CycleJoinRequestRankAddressVariant3[];
RestjoinOptionsEventHandlerRecordsRecord443 g_joinOptionsEventHandlerRecords = {
    3590,
    23,
    (unsigned int)g_Menu_CreateEuJoinOptionsCallbackAddressEu,
    3587,
    23,
    (unsigned int)g_Join_DestroyJoinOptionsMenuAddressVariant3,
    3592,
    23,
    (unsigned int)g_Join_PulseJoinSelectionHighlightAddressVariant3,
    2,
    23,
    (unsigned int)g_Join_RequestJoinOptionsExitAlternateAddressVariant3,
    1,
    23,
    (unsigned int)g_Join_RequestJoinOptionsExitAddressVariant3,
    7,
    23,
    (unsigned int)g_Frontend_SelectPreviousJoinModelAddressVariant2,
    8,
    23,
    (unsigned int)g_Frontend_SelectNextJoinModelAddressVariant2,
    5,
    23,
    (unsigned int)g_Join_SelectPreviousJoinRowAddressVariant3,
    6,
    23,
    (unsigned int)g_Join_SelectNextJoinRowAddressVariant3,
    10,
    23,
    (unsigned int)g_Join_CycleJoinRequestRankAddressVariant3,
    { 0x00000000, 0x00000000, 0x00000000, 0x1D800013, 0x4B132F10 },
};
#elif defined(VERSION_EU_X)
extern char g_Menu_CreateEuJoinOptionsCallbackAddressEu[];
extern char g_Frontend_SelectPreviousJoinModelAddressVariant2[];
extern char g_Frontend_SelectNextJoinModelAddressVariant2[];
extern char g_Join_DestroyJoinOptionsMenuAddressVariant3[];
extern char g_Join_PulseJoinSelectionHighlightAddressVariant3[];
extern char g_Join_RequestJoinOptionsExitAddressVariant3[];
extern char g_Join_RequestJoinOptionsExitAlternateAddressVariant3[];
extern char g_Join_SelectPreviousJoinRowAddressVariant3[];
extern char g_Join_SelectNextJoinRowAddressVariant3[];
extern char g_Join_CycleJoinRequestRankAddressVariant3[];
RestjoinOptionsEventHandlerRecordsRecord444 g_joinOptionsEventHandlerRecords = {
    3590,
    23,
    (unsigned int)g_Menu_CreateEuJoinOptionsCallbackAddressEu,
    3587,
    23,
    (unsigned int)g_Join_DestroyJoinOptionsMenuAddressVariant3,
    3592,
    23,
    (unsigned int)g_Join_PulseJoinSelectionHighlightAddressVariant3,
    2,
    23,
    (unsigned int)g_Join_RequestJoinOptionsExitAlternateAddressVariant3,
    1,
    23,
    (unsigned int)g_Join_RequestJoinOptionsExitAddressVariant3,
    7,
    23,
    (unsigned int)g_Frontend_SelectPreviousJoinModelAddressVariant2,
    8,
    23,
    (unsigned int)g_Frontend_SelectNextJoinModelAddressVariant2,
    5,
    23,
    (unsigned int)g_Join_SelectPreviousJoinRowAddressVariant3,
    6,
    23,
    (unsigned int)g_Join_SelectNextJoinRowAddressVariant3,
    10,
    23,
    (unsigned int)g_Join_CycleJoinRequestRankAddressVariant3,
    { 0x00000000, 0x00000000, 0x00000000, 0x00000021, 0x0000001F },
};
#elif defined(VERSION_US)
extern char g_Join_CreateUsJoinOptionsMenuCallbackAddressUs[];
extern char g_Join_SelectPreviousUsJoinModelCallbackAddressUs[];
extern char g_CJoinCharacter_CycleModelSelectionCallbackAddressUs[];
extern char g_Join_DestroyJoinOptionsMenuAddressVariant2[];
extern char g_Join_PulseJoinSelectionHighlightAddressVariant2[];
extern char g_Join_RequestJoinOptionsExitAddressVariant2[];
extern char g_Join_RequestJoinOptionsExitAlternateAddressVariant2[];
extern char g_Join_SelectPreviousJoinRowAddressVariant2[];
extern char g_Join_SelectNextJoinRowAddressVariant2[];
extern char g_Join_CycleJoinRequestRankAddressVariant2[];
RestjoinOptionsEventHandlerRecordsRecord445 g_joinOptionsEventHandlerRecords = {
    3590,
    23,
    (unsigned int)g_Join_CreateUsJoinOptionsMenuCallbackAddressUs,
    3587,
    23,
    (unsigned int)g_Join_DestroyJoinOptionsMenuAddressVariant2,
    3592,
    23,
    (unsigned int)g_Join_PulseJoinSelectionHighlightAddressVariant2,
    2,
    23,
    (unsigned int)g_Join_RequestJoinOptionsExitAlternateAddressVariant2,
    1,
    23,
    (unsigned int)g_Join_RequestJoinOptionsExitAddressVariant2,
    7,
    23,
    (unsigned int)g_Join_SelectPreviousUsJoinModelCallbackAddressUs,
    8,
    23,
    (unsigned int)g_CJoinCharacter_CycleModelSelectionCallbackAddressUs,
    5,
    23,
    (unsigned int)g_Join_SelectPreviousJoinRowAddressVariant2,
    6,
    23,
    (unsigned int)g_Join_SelectNextJoinRowAddressVariant2,
    10,
    23,
    (unsigned int)g_Join_CycleJoinRequestRankAddressVariant2,
    { 0x00000000, 0x00000000, 0x00000000, 0x54000004, 0x00000066 },
};
#elif defined(VERSION_US_REV1)
extern char g_Join_CreateUsJoinOptionsMenuCallbackAddressUs[];
extern char g_Join_SelectPreviousUsJoinModelCallbackAddressUs[];
extern char g_CJoinCharacter_CycleModelSelectionCallbackAddressUs[];
extern char g_Join_DestroyJoinOptionsMenuAddressVariant2[];
extern char g_Join_PulseJoinSelectionHighlightAddressVariant2[];
extern char g_Join_RequestJoinOptionsExitAddressVariant2[];
extern char g_Join_RequestJoinOptionsExitAlternateAddressVariant2[];
extern char g_Join_SelectPreviousJoinRowAddressVariant2[];
extern char g_Join_SelectNextJoinRowAddressVariant2[];
extern char g_Join_CycleJoinRequestRankAddressVariant2[];
RestjoinOptionsEventHandlerRecordsRecord446 g_joinOptionsEventHandlerRecords = {
    3590,
    23,
    (unsigned int)g_Join_CreateUsJoinOptionsMenuCallbackAddressUs,
    3587,
    23,
    (unsigned int)g_Join_DestroyJoinOptionsMenuAddressVariant2,
    3592,
    23,
    (unsigned int)g_Join_PulseJoinSelectionHighlightAddressVariant2,
    2,
    23,
    (unsigned int)g_Join_RequestJoinOptionsExitAlternateAddressVariant2,
    1,
    23,
    (unsigned int)g_Join_RequestJoinOptionsExitAddressVariant2,
    7,
    23,
    (unsigned int)g_Join_SelectPreviousUsJoinModelCallbackAddressUs,
    8,
    23,
    (unsigned int)g_CJoinCharacter_CycleModelSelectionCallbackAddressUs,
    5,
    23,
    (unsigned int)g_Join_SelectPreviousJoinRowAddressVariant2,
    6,
    23,
    (unsigned int)g_Join_SelectNextJoinRowAddressVariant2,
    10,
    23,
    (unsigned int)g_Join_CycleJoinRequestRankAddressVariant2,
    { 0x00000000, 0x00000000, 0x00000000, 0x00000020, 0x00000193 },
};
#endif

#if defined(VERSION_EU) || defined(VERSION_US)
RestjoinOptionsTrailingWordsLayout447 g_joinOptionsTrailingWords = {
    { 146, 0, 35 },
    { 0.14f, 0.14f, 0.14f, 0.14f },
};
#endif

#if defined(VERSION_EU_X)
RestjoinOptionsTrailingWords_eu_xLayout448 g_joinOptionsTrailingWords_eu_x = {
    { 150, 0, 35 },
    { 0.14f, 0.14f, 0.14f, 0.14f },
};
#endif

#if defined(VERSION_DE)
RestjoinOptionsTrailingWords_deLayout449 g_joinOptionsTrailingWords_de = {
    { 144, 0, 35 },
    { 0.14f, 0.14f, 0.14f, 0.14f },
};
#endif
