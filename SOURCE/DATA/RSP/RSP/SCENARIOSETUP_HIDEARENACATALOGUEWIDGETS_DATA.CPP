#include "DATA/REST_SOURCE_RECORDS.H"
extern char ScenarioSetup_CloseSetupScreen_Address[];
extern char addrLow_CScenarioSetup_OpenScenarioSetupScreen[];
extern char addrLow_Frontend_DrawSetupResultPanelsEntryVariant1[];
extern char addrLow_Frontend_DrawSetupResultPanelsEntryVariant2[];
extern char addrLow_ScenarioSetup_BeginSetupConfirmation[];
extern char addrLow_ScenarioSetup_CloseSetupScreen[];
extern char addrLow_ScenarioSetup_EndSetupInput[];
extern char addrLow_ScenarioSetup_RefreshSetupScreen[];
extern char addrLow_ScenarioSetup_ReturnSetupEventZeroAlt[];
extern char addrLow_ScenarioSetup_SelectNextCatalogueCategory[];
extern char addrLow_ScenarioSetup_SelectNextSetupItem[];
extern char addrLow_ScenarioSetup_SelectPreviousCatalogueCategory[];
extern char addrLow_ScenarioSetup_SelectPreviousCatalogueItem[];
extern char addrLow_ScenarioSetup_UpdateSetupTransition[];
extern char g_CScenarioSetup_OpenScenarioSetupScreenEncodedCallbackEntryVariant1[];
extern char g_CScenarioSetup_OpenScenarioSetupScreenEncodedCallbackEntryVariant2[];
extern char g_CScenarioSetup_OpenScenarioSetupScreenPackedAddress24[];
extern char g_Frontend_DrawSetupResultPanelsPackedAddress24[];
extern char g_Frontend_MatchOptionsEvent0E03ScenarioSetupEvent0E08HandlerPackedAddress24[];
extern char g_ScenarioSetup_BeginSetupConfirmationEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_BeginSetupConfirmationEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_BeginSetupConfirmationPackedAddress24[];
extern char g_ScenarioSetup_CloseSetupScreenEncodedCallback[];
extern char g_ScenarioSetup_CloseSetupScreenPackedAddress24[];
extern char g_ScenarioSetup_EndSetupInputEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_EndSetupInputEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_RefreshSetupScreenEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_RefreshSetupScreenEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_RefreshSetupScreenPackedAddress24[];
extern char g_ScenarioSetup_ReturnSetupEventZeroAltEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_ReturnSetupEventZeroAltEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_ReturnSetupEventZeroAltPackedAddress24[];
extern char g_ScenarioSetup_SelectNextCatalogueCategoryEncodedCallback[];
extern char g_ScenarioSetup_SelectNextCatalogueCategoryPackedAddress24[];
extern char g_ScenarioSetup_SelectNextSetupItemEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_SelectNextSetupItemEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_SelectNextSetupItemPackedAddress24[];
extern char g_ScenarioSetup_SelectPreviousCatalogueCategoryEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_SelectPreviousCatalogueCategoryEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_SelectPreviousCatalogueCategoryPackedAddress24[];
extern char g_ScenarioSetup_SelectPreviousCatalogueItemEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_SelectPreviousCatalogueItemEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_SelectPreviousCatalogueItemPackedAddress24[];
extern char g_ScenarioSetup_SetupScreenEvent02Event08HandlerPackedAddress24[];
extern char g_ScenarioSetup_UpdateSetupTransitionEncodedCallback[];
extern char g_ScenarioSetup_UpdateSetupTransitionPackedAddress24[];
extern char g_frontend_DrawSetupResultPanelsEntry[];

#if !(defined(VERSION_US_REV1))
#ifdef VERSION_DE
extern char g_CScenarioSetup_OpenScenarioSetupScreenEncodedCallbackEntryVariant1[];
extern char addrLow_Frontend_DrawSetupResultPanelsEntryVariant1[];
extern char g_Frontend_MatchOptionsEvent0E03ScenarioSetupEvent0E08HandlerPackedAddress24[];
extern char ScenarioSetup_CloseSetupScreen_Address[];
extern char g_ScenarioSetup_ReturnSetupEventZeroAltEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_BeginSetupConfirmationEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_SelectPreviousCatalogueItemEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_SelectNextSetupItemEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_SelectPreviousCatalogueCategoryEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_SelectNextCatalogueCategoryEncodedCallback[];
extern char g_ScenarioSetup_EndSetupInputEncodedCallbackEntryVariant1[];
extern char g_ScenarioSetup_RefreshSetupScreenEncodedCallbackEntryVariant1[];
RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout866 g_ScenariosetupHidearenacataloguewidgetsEncodedWords = {
    { 811, 2, 0, 782, 812, 2, 1, 781, 856, 2, 2, 783, 831, 2, 3, 795, 797, 2, 4, 800, 784, 2, 5, 840, 837, 1, 6, 849, 854, 0, 7, 820, 823, 3, 8, 796, 813, 2, 9, 827, 825, 3, 10, 799, 855, 2, 11, 789, 794, 2, 12, 816, 830, 3, 13, 798, 801, 2, 14, 839, 842, 1, 15, 848, 851, 0, 16, 790, 792, 2, 17, 805, 802, 2, 18, 804, 807, 2, 19, 826, 828, 3, 20, 832, 835, 1, 21, 791, 793, 2, 22, 847, 850, 0, 23, 803, 806, 2, 24, 815, 818, 3, 25, 833, 836, 1, 26, 810, 808, 2, 27, 814, 817, 3, 28, 838, 841, 1, 29, 844, 829, 3, 30, 843, 845, 3, 31, 822, 819, 3, 32, 853, 852, 0, 33, 834, 846, 1, 34, 821, 824, 3, 35, 786, -1, 2, 0, 788, -1, 3, 0, 787, -1, 1, 0, 785, -1, 0, 0, 785, 849, 848, 847, 853, 787, 834, 833, 832, 840, 839, 838, 788, 816, 815, 814, 822, 821, 820, 827, 826, 844, 843, 786, 783, 800, 799, 798, 805, 804, 803, 810, 809, 782, 781, 795, 796, 789, 790, 791, 3592, 20 },
    (void *)&g_Frontend_MatchOptionsEvent0E03ScenarioSetupEvent0E08HandlerPackedAddress24,
    { 3591, 20 },
    (void *)&g_ScenarioSetup_ReturnSetupEventZeroAltEncodedCallbackEntryVariant1,
    { 10, 20 },
    (void *)&g_ScenarioSetup_BeginSetupConfirmationEncodedCallbackEntryVariant1,
    { 3590, 20 },
    (void *)&g_CScenarioSetup_OpenScenarioSetupScreenEncodedCallbackEntryVariant1,
    { 3587, 20 },
    (void *)&ScenarioSetup_CloseSetupScreen_Address,
    { 3594, 20 },
    (void *)&addrLow_Frontend_DrawSetupResultPanelsEntryVariant1,
    { 2, 20 },
    (void *)&g_ScenarioSetup_EndSetupInputEncodedCallbackEntryVariant1,
    { 1, 20 },
    (void *)&g_ScenarioSetup_RefreshSetupScreenEncodedCallbackEntryVariant1,
    { 5, 20 },
    (void *)&g_ScenarioSetup_SelectPreviousCatalogueItemEncodedCallbackEntryVariant1,
    { 6, 20 },
    (void *)&g_ScenarioSetup_SelectNextSetupItemEncodedCallbackEntryVariant1,
    { 8, 20 },
    (void *)&g_ScenarioSetup_SelectNextCatalogueCategoryEncodedCallback,
    { 7, 20 },
    { (void *)&g_ScenarioSetup_SelectPreviousCatalogueCategoryEncodedCallbackEntryVariant1, 0, 0, 0 },
    { 570, 606, 573, 578, 582, 586, 590, 594, 598, 599, 571, 607, 575, 579, 583, 587, 591, 595, 600, 601, 572, 608, 576, 580, 584, 588, 592, 596, 602, 603, 574, 609, 577, 581, 585, 589, 593, 597, 604, 605 },
};
#endif
#ifdef VERSION_EU_X
extern char g_CScenarioSetup_OpenScenarioSetupScreenEncodedCallbackEntryVariant2[];
extern char addrLow_Frontend_DrawSetupResultPanelsEntryVariant2[];
extern char g_ScenarioSetup_UpdateSetupTransitionEncodedCallback[];
extern char g_ScenarioSetup_CloseSetupScreenEncodedCallback[];
extern char g_ScenarioSetup_ReturnSetupEventZeroAltEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_BeginSetupConfirmationEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_SelectPreviousCatalogueItemEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_SelectNextSetupItemEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_SelectPreviousCatalogueCategoryEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_SetupScreenEvent02Event08HandlerPackedAddress24[];
extern char g_ScenarioSetup_EndSetupInputEncodedCallbackEntryVariant2[];
extern char g_ScenarioSetup_RefreshSetupScreenEncodedCallbackEntryVariant2[];
RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout867 g_ScenariosetupHidearenacataloguewidgetsEncodedWords = {
    { 819, 2, 0, 790, 820, 2, 1, 789, 864, 2, 2, 791, 839, 2, 3, 803, 805, 2, 4, 808, 792, 2, 5, 848, 845, 1, 6, 857, 862, 0, 7, 828, 831, 3, 8, 804, 821, 2, 9, 835, 833, 3, 10, 807, 863, 2, 11, 797, 802, 2, 12, 824, 838, 3, 13, 806, 809, 2, 14, 847, 850, 1, 15, 856, 859, 0, 16, 798, 800, 2, 17, 813, 810, 2, 18, 812, 815, 2, 19, 834, 836, 3, 20, 840, 843, 1, 21, 799, 801, 2, 22, 855, 858, 0, 23, 811, 814, 2, 24, 823, 826, 3, 25, 841, 844, 1, 26, 818, 816, 2, 27, 822, 825, 3, 28, 846, 849, 1, 29, 852, 837, 3, 30, 851, 853, 3, 31, 830, 827, 3, 32, 861, 860, 0, 33, 842, 854, 1, 34, 829, 832, 3, 35, 794, -1, 2, 0, 796, -1, 3, 0, 795, -1, 1, 0, 793, -1, 0, 0, 793, 857, 856, 855, 861, 795, 842, 841, 840, 848, 847, 846, 796, 824, 823, 822, 830, 829, 828, 835, 834, 852, 851, 794, 791, 808, 807, 806, 813, 812, 811, 818, 817, 790, 789, 803, 804, 797, 798, 799, 3592, 20 },
    (void *)&g_ScenarioSetup_UpdateSetupTransitionEncodedCallback,
    { 3591, 20 },
    (void *)&g_ScenarioSetup_ReturnSetupEventZeroAltEncodedCallbackEntryVariant2,
    { 10, 20 },
    (void *)&g_ScenarioSetup_BeginSetupConfirmationEncodedCallbackEntryVariant2,
    { 3590, 20 },
    (void *)&g_CScenarioSetup_OpenScenarioSetupScreenEncodedCallbackEntryVariant2,
    { 3587, 20 },
    (void *)&g_ScenarioSetup_CloseSetupScreenEncodedCallback,
    { 3594, 20 },
    (void *)&addrLow_Frontend_DrawSetupResultPanelsEntryVariant2,
    { 2, 20 },
    (void *)&g_ScenarioSetup_EndSetupInputEncodedCallbackEntryVariant2,
    { 1, 20 },
    (void *)&g_ScenarioSetup_RefreshSetupScreenEncodedCallbackEntryVariant2,
    { 5, 20 },
    (void *)&g_ScenarioSetup_SelectPreviousCatalogueItemEncodedCallbackEntryVariant2,
    { 6, 20 },
    (void *)&g_ScenarioSetup_SelectNextSetupItemEncodedCallbackEntryVariant2,
    { 8, 20 },
    (void *)&g_ScenarioSetup_SetupScreenEvent02Event08HandlerPackedAddress24,
    { 7, 20 },
    { (void *)&g_ScenarioSetup_SelectPreviousCatalogueCategoryEncodedCallbackEntryVariant2, 0, 0, 0 },
    { 579, 615, 582, 587, 591, 595, 599, 603, 607, 608, 580, 616, 584, 588, 592, 596, 600, 604, 609, 610, 581, 617, 585, 589, 593, 597, 601, 605, 611, 612, 583, 618, 586, 590, 594, 598, 602, 606, 613, 614 },
};
#endif
#ifdef VERSION_EU
extern char g_CScenarioSetup_OpenScenarioSetupScreenPackedAddress24[];
extern char g_Frontend_DrawSetupResultPanelsPackedAddress24[];
extern char g_ScenarioSetup_UpdateSetupTransitionPackedAddress24[];
extern char g_ScenarioSetup_CloseSetupScreenPackedAddress24[];
extern char g_ScenarioSetup_ReturnSetupEventZeroAltPackedAddress24[];
extern char g_ScenarioSetup_BeginSetupConfirmationPackedAddress24[];
extern char g_ScenarioSetup_SelectPreviousCatalogueItemPackedAddress24[];
extern char g_ScenarioSetup_SelectNextSetupItemPackedAddress24[];
extern char g_ScenarioSetup_SelectPreviousCatalogueCategoryPackedAddress24[];
extern char g_ScenarioSetup_SelectNextCatalogueCategoryPackedAddress24[];
extern char g_ScenarioSetup_SetupScreenEvent02Event08HandlerPackedAddress24[];
extern char g_ScenarioSetup_RefreshSetupScreenPackedAddress24[];
RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout868 g_ScenariosetupHidearenacataloguewidgetsEncodedWords = {
    { 815, 2, 0, 786, 816, 2, 1, 785, 860, 2, 2, 787, 835, 2, 3, 799, 801, 2, 4, 804, 788, 2, 5, 844, 841, 1, 6, 853, 858, 0, 7, 824, 827, 3, 8, 800, 817, 2, 9, 831, 829, 3, 10, 803, 859, 2, 11, 793, 798, 2, 12, 820, 834, 3, 13, 802, 805, 2, 14, 843, 846, 1, 15, 852, 855, 0, 16, 794, 796, 2, 17, 809, 806, 2, 18, 808, 811, 2, 19, 830, 832, 3, 20, 836, 839, 1, 21, 795, 797, 2, 22, 851, 854, 0, 23, 807, 810, 2, 24, 819, 822, 3, 25, 837, 840, 1, 26, 814, 812, 2, 27, 818, 821, 3, 28, 842, 845, 1, 29, 848, 833, 3, 30, 847, 849, 3, 31, 826, 823, 3, 32, 857, 856, 0, 33, 838, 850, 1, 34, 825, 828, 3, 35, 790, -1, 2, 0, 792, -1, 3, 0, 791, -1, 1, 0, 789, -1, 0, 0, 789, 853, 852, 851, 857, 791, 838, 837, 836, 844, 843, 842, 792, 820, 819, 818, 826, 825, 824, 831, 830, 848, 847, 790, 787, 804, 803, 802, 809, 808, 807, 814, 813, 786, 785, 799, 800, 793, 794, 795, 3592, 20 },
    (void *)&g_ScenarioSetup_UpdateSetupTransitionPackedAddress24,
    { 3591, 20 },
    (void *)&g_ScenarioSetup_ReturnSetupEventZeroAltPackedAddress24,
    { 10, 20 },
    (void *)&g_ScenarioSetup_BeginSetupConfirmationPackedAddress24,
    { 3590, 20 },
    (void *)&g_CScenarioSetup_OpenScenarioSetupScreenPackedAddress24,
    { 3587, 20 },
    (void *)&g_ScenarioSetup_CloseSetupScreenPackedAddress24,
    { 3594, 20 },
    (void *)&g_Frontend_DrawSetupResultPanelsPackedAddress24,
    { 2, 20 },
    (void *)&g_ScenarioSetup_SetupScreenEvent02Event08HandlerPackedAddress24,
    { 1, 20 },
    (void *)&g_ScenarioSetup_RefreshSetupScreenPackedAddress24,
    { 5, 20 },
    (void *)&g_ScenarioSetup_SelectPreviousCatalogueItemPackedAddress24,
    { 6, 20 },
    (void *)&g_ScenarioSetup_SelectNextSetupItemPackedAddress24,
    { 8, 20 },
    (void *)&g_ScenarioSetup_SelectNextCatalogueCategoryPackedAddress24,
    { 7, 20 },
    { (void *)&g_ScenarioSetup_SelectPreviousCatalogueCategoryPackedAddress24, 0, 0, 0 },
    { 574, 610, 577, 582, 586, 590, 594, 598, 602, 603, 575, 611, 579, 583, 587, 591, 595, 599, 604, 605, 576, 612, 580, 584, 588, 592, 596, 600, 606, 607, 578, 613, 581, 585, 589, 593, 597, 601, 608, 609 },
};
#endif
#ifdef VERSION_US
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
RestScenariosetupHidearenacataloguewidgetsEncodedWordsLayout869 g_ScenariosetupHidearenacataloguewidgetsEncodedWords = {
    { 815, 2, 0, 786, 816, 2, 1, 785, 860, 2, 2, 787, 835, 2, 3, 799, 801, 2, 4, 804, 788, 2, 5, 844, 841, 1, 6, 853, 858, 0, 7, 824, 827, 3, 8, 800, 817, 2, 9, 831, 829, 3, 10, 803, 859, 2, 11, 793, 798, 2, 12, 820, 834, 3, 13, 802, 805, 2, 14, 843, 846, 1, 15, 852, 855, 0, 16, 794, 796, 2, 17, 809, 806, 2, 18, 808, 811, 2, 19, 830, 832, 3, 20, 836, 839, 1, 21, 795, 797, 2, 22, 851, 854, 0, 23, 807, 810, 2, 24, 819, 822, 3, 25, 837, 840, 1, 26, 814, 812, 2, 27, 818, 821, 3, 28, 842, 845, 1, 29, 848, 833, 3, 30, 847, 849, 3, 31, 826, 823, 3, 32, 857, 856, 0, 33, 838, 850, 1, 34, 825, 828, 3, 35, 790, -1, 2, 0, 792, -1, 3, 0, 791, -1, 1, 0, 789, -1, 0, 0, 789, 853, 852, 851, 857, 791, 838, 837, 836, 844, 843, 842, 792, 820, 819, 818, 826, 825, 824, 831, 830, 848, 847, 790, 787, 804, 803, 802, 809, 808, 807, 814, 813, 786, 785, 799, 800, 793, 794, 795, 3592, 20 },
    (void *)&addrLow_ScenarioSetup_UpdateSetupTransition,
    { 3591, 20 },
    (void *)&addrLow_ScenarioSetup_ReturnSetupEventZeroAlt,
    { 10, 20 },
    (void *)&addrLow_ScenarioSetup_BeginSetupConfirmation,
    { 3590, 20 },
    (void *)&addrLow_CScenarioSetup_OpenScenarioSetupScreen,
    { 3587, 20 },
    (void *)&addrLow_ScenarioSetup_CloseSetupScreen,
    { 3594, 20 },
    (void *)&g_frontend_DrawSetupResultPanelsEntry,
    { 2, 20 },
    (void *)&addrLow_ScenarioSetup_EndSetupInput,
    { 1, 20 },
    (void *)&addrLow_ScenarioSetup_RefreshSetupScreen,
    { 5, 20 },
    (void *)&addrLow_ScenarioSetup_SelectPreviousCatalogueItem,
    { 6, 20 },
    (void *)&addrLow_ScenarioSetup_SelectNextSetupItem,
    { 8, 20 },
    (void *)&addrLow_ScenarioSetup_SelectNextCatalogueCategory,
    { 7, 20 },
    { (void *)&addrLow_ScenarioSetup_SelectPreviousCatalogueCategory, 0, 0, 0 },
    { 574, 610, 577, 582, 586, 590, 594, 598, 602, 603, 575, 611, 579, 583, 587, 591, 595, 599, 604, 605, 576, 612, 580, 584, 588, 592, 596, 600, 606, 607, 578, 613, 581, 585, 589, 593, 597, 601, 608, 609 },
};
#endif
#endif
