#include "DATA/REST_SOURCE_RECORDS.H"


/* 800E4F60.CPP */
#if !(defined(VERSION_DE))
/* ROM-grounded data: rodata/writable/800E4F60 */
#ifdef VERSION_EU
u16 k_OvldatZeroWords[4] = {
    0, 0, 0, 813,
};
#endif
#ifdef VERSION_EU_X
u16 k_OvldatZeroWords[4] = {
    0, 0, 0, 817,
};
#endif
#ifdef VERSION_US
u16 k_OvldatZeroWords[4] = {
    0, 0, 0, 813,
};
#endif
#ifdef VERSION_US_REV1
s32 k_OvldatZeroWords[1] = {
    0,
};
#endif
#endif

/* 800E4F64.CPP */
#if defined(VERSION_US_REV1)
RestArenaCatalogueRecord g_catalogueArenaRecordWords[40] = {
    { 813, 815, 2, 0 },
    { 786, 816, 2, 1 },
    { 785, 860, 2, 2 },
    { 787, 835, 2, 3 },
    { 799, 801, 2, 4 },
    { 804, 788, 2, 5 },
    { 844, 841, 1, 6 },
    { 853, 858, 0, 7 },
    { 824, 827, 3, 8 },
    { 800, 817, 2, 9 },
    { 831, 829, 3, 10 },
    { 803, 859, 2, 11 },
    { 793, 798, 2, 12 },
    { 820, 834, 3, 13 },
    { 802, 805, 2, 14 },
    { 843, 846, 1, 15 },
    { 852, 855, 0, 16 },
    { 794, 796, 2, 17 },
    { 809, 806, 2, 18 },
    { 808, 811, 2, 19 },
    { 830, 832, 3, 20 },
    { 836, 839, 1, 21 },
    { 795, 797, 2, 22 },
    { 851, 854, 0, 23 },
    { 807, 810, 2, 24 },
    { 819, 822, 3, 25 },
    { 837, 840, 1, 26 },
    { 814, 812, 2, 27 },
    { 818, 821, 3, 28 },
    { 842, 845, 1, 29 },
    { 848, 833, 3, 30 },
    { 847, 849, 3, 31 },
    { 826, 823, 3, 32 },
    { 857, 856, 0, 33 },
    { 838, 850, 1, 34 },
    { 825, 828, 3, 35 },
    { 790, -1, 2, 0 },
    { 792, -1, 3, 0 },
    { 791, -1, 1, 0 },
    { 789, -1, 0, 0 },
};
#endif

/* 800E51E4.CPP */
#if defined(VERSION_US_REV1)
s32 g_cupCategoryZeroArenaControls[5] = {
    789, 853, 852, 851, 857,
};
#endif

/* 800E51F8.CPP */
#if defined(VERSION_US_REV1)
s32 g_cupCategoryOneArenaControls[7] = {
    791, 838, 837, 836, 844, 843,
    842,
};
#endif

/* 800E5214.CPP */
#if defined(VERSION_US_REV1)
s32 g_cupCategoryThreeArenaControls[11] = {
    792, 820, 819, 818, 826, 825,
    824, 831, 830, 848, 847,
};
#endif

/* 800E5240.CPP */
#if defined(VERSION_US_REV1)
s32 g_cupCategoryTwoArenaControls[17] = {
    790, 787, 804, 803, 802, 809,
    808, 807, 814, 813, 786, 785,
    799, 800, 793, 794, 795,
};
#endif

/* 800E5284.CPP */
#if defined(VERSION_US_REV1)
extern char addrLow_CScenarioSetup_OpenScenarioSetupScreen[];
extern char g_frontend_DrawSetupResultPanelsEntry[];
extern char addrLow_ScenarioSetup_UpdateSetupTransition[];
extern char addrLow_ScenarioSetup_CloseSetupScreen[];
extern char addrLow_ScenarioSetup_ReturnSetupEventZeroAlt[];
extern char addrLow_ScenarioSetup_BeginSetupConfirmation[];
extern char addrLow_ScenarioSetup_SelectPreviousCatalogueItem[];
extern char addrLow_ScenarioSetup_SelectNextSetupItem[];
extern char addrLow_ScenarioSetup_SelectPreviousCatalogueCategory[];
extern char addrLow_ScenarioSetup_SelectNextCatalogueCategory[];
extern char addrLow_ScenarioSetup_EndSetupInput[];
extern char addrLow_ScenarioSetup_RefreshSetupScreen[];
RestscenarioSetupMenuEventHandlerWordsRecord35 g_scenarioSetupMenuEventHandlerWords = {
    3592,
    20,
    (unsigned int)addrLow_ScenarioSetup_UpdateSetupTransition,
    3591,
    20,
    (unsigned int)addrLow_ScenarioSetup_ReturnSetupEventZeroAlt,
    10,
    20,
    (unsigned int)addrLow_ScenarioSetup_BeginSetupConfirmation,
    3590,
    20,
    (unsigned int)addrLow_CScenarioSetup_OpenScenarioSetupScreen,
    3587,
    20,
    (unsigned int)addrLow_ScenarioSetup_CloseSetupScreen,
    3594,
    20,
    (unsigned int)g_frontend_DrawSetupResultPanelsEntry,
    2,
    20,
    (unsigned int)addrLow_ScenarioSetup_EndSetupInput,
    1,
    20,
    (unsigned int)addrLow_ScenarioSetup_RefreshSetupScreen,
    5,
    20,
    (unsigned int)addrLow_ScenarioSetup_SelectPreviousCatalogueItem,
    6,
    20,
    (unsigned int)addrLow_ScenarioSetup_SelectNextSetupItem,
    8,
    20,
    (unsigned int)addrLow_ScenarioSetup_SelectNextCatalogueCategory,
    7,
    20,
    (unsigned int)addrLow_ScenarioSetup_SelectPreviousCatalogueCategory,
    { 0x00000000, 0x00000000, 0x00000000 },
};
#endif

/* 800E5320.CPP */
#if defined(VERSION_US_REV1)
s32 k_Ovldat9EncodedWords[40] = {
    574, 610, 577, 582, 586, 590,
    594, 598, 602, 603, 575, 611,
    579, 583, 587, 591, 595, 599,
    604, 605, 576, 612, 580, 584,
    588, 592, 596, 600, 606, 607,
    578, 613, 581, 585, 589, 593,
    597, 601, 608, 609,
};
#endif
