#include "DATA/REST_SOURCE_RECORDS.H"


/* g_slotSelectionMenuEventHandlerRecordsUsRev1_GRewarditemtiers.CPP */
#if defined(VERSION_US_REV1)
extern char g_Frontend_CreateSlotSelectionMenuAddress[];
extern char g_Frontend_AnimateSlotSelectionMenuAddress[];
extern char g_Focus_FreeMenuBlockAddress[];
extern char g_Menu_PositionSelectionMenuModelAddress[];
extern char g_Menu_DrawMenuBlockModelAddress[];
extern char g_Menu_HandleNextProfileEventAddress[];
extern char g_Menu_BeginSelectionMenuExitAddress[];
extern char g_Menu_ConsumeSelectionMenuEventAddress[];
RestslotSelectionMenuEventHandlerRecordsUsRev1Record438 g_slotSelectionMenuEventHandlerRecordsUsRev1 = {
    3592,
    16,
    (unsigned int)g_Frontend_AnimateSlotSelectionMenuAddress,
    3591,
    16,
    (unsigned int)g_Menu_PositionSelectionMenuModelAddress,
    10,
    16,
    (unsigned int)g_Menu_HandleNextProfileEventAddress,
    3594,
    16,
    (unsigned int)g_Menu_DrawMenuBlockModelAddress,
    3590,
    16,
    (unsigned int)g_Frontend_CreateSlotSelectionMenuAddress,
    3587,
    16,
    (unsigned int)g_Focus_FreeMenuBlockAddress,
    2,
    16,
    (unsigned int)g_Menu_BeginSelectionMenuExitAddress,
    1,
    16,
    (unsigned int)g_Menu_ConsumeSelectionMenuEventAddress,
    { 0x00000000, 0x00000000, 0x00000000 },
};
#endif

/* g_rewardScoreBudgets_GRewarditemtiers.CPP */
#if defined(VERSION_US_REV1)
RestrewardItemTierPairsUsRev1Layout439 g_rewardItemTierPairsUsRev1 = {
    99,
    46,
    98,
    47,
    97,
    41,
    95,
    42,
    96,
    48,
};

s32 g_rewardScoreBudgets[25] = {
    5, 10, 15, 20, 25, 5,
    15, 20, 30, 35, 10, 20,
    30, 40, 50, 10, 30, 45,
    60, 75, 20, 40, 60, 80,
    100,
};
#endif

/* g_rewardItemTiers_GRewarditemtiers.CPP */
#if defined(VERSION_US_REV1)
extern char g_slotSelectionTextReferenceShared1[];
extern char g_slotSelectionTextReferenceShared3[];
unsigned int g_rewardItemTiers[102] = {
    0, (unsigned int)(g_slotSelectionTextReferenceShared1 + 8), 1, (unsigned int)(g_slotSelectionTextReferenceShared1 + 80),
    2, (unsigned int)(g_slotSelectionTextReferenceShared1 + 32), 3, (unsigned int)(g_slotSelectionTextReferenceShared1 + 44),
    4, (unsigned int)(g_slotSelectionTextReferenceShared1 + 92), 5, (unsigned int)(g_slotSelectionTextReferenceShared1 + 20),
    6, (unsigned int)(g_slotSelectionTextReferenceShared3 + 16), 7, (unsigned int)(g_slotSelectionTextReferenceShared3 + 28),
    8, (unsigned int)(g_slotSelectionTextReferenceShared3 + 4), 9, (unsigned int)(g_slotSelectionTextReferenceShared1 + 68),
    10, (unsigned int)(g_slotSelectionTextReferenceShared3 + 40), -1, (unsigned int)(g_slotSelectionTextReferenceShared1 + 104),
    -1, (unsigned int)(g_slotSelectionTextReferenceShared1 + 112), -1, (unsigned int)g_slotSelectionTextReferenceShared3,
    -1, (unsigned int)(g_slotSelectionTextReferenceShared1 + 108), 17, (unsigned int)(g_slotSelectionTextReferenceShared3 + 52),
    18, (unsigned int)(g_slotSelectionTextReferenceShared1 + 56), 0, (unsigned int)(g_slotSelectionTextReferenceShared1 + 12),
    1, (unsigned int)(g_slotSelectionTextReferenceShared1 + 84), 2, (unsigned int)(g_slotSelectionTextReferenceShared1 + 36),
    3, (unsigned int)(g_slotSelectionTextReferenceShared1 + 48), 4, (unsigned int)(g_slotSelectionTextReferenceShared1 + 96),
    5, (unsigned int)(g_slotSelectionTextReferenceShared1 + 24), 6, (unsigned int)(g_slotSelectionTextReferenceShared3 + 20),
    7, (unsigned int)(g_slotSelectionTextReferenceShared3 + 32), 8, (unsigned int)(g_slotSelectionTextReferenceShared3 + 8),
    9, (unsigned int)(g_slotSelectionTextReferenceShared1 + 72), 10, (unsigned int)(g_slotSelectionTextReferenceShared3 + 44),
    -1, (unsigned int)(g_slotSelectionTextReferenceShared1 + 104), -1, (unsigned int)(g_slotSelectionTextReferenceShared1 + 112),
    -1, (unsigned int)g_slotSelectionTextReferenceShared3, -1, (unsigned int)(g_slotSelectionTextReferenceShared1 + 108),
    17, (unsigned int)(g_slotSelectionTextReferenceShared3 + 56), 18, (unsigned int)(g_slotSelectionTextReferenceShared1 + 60),
    0, (unsigned int)(g_slotSelectionTextReferenceShared1 + 16), 1, (unsigned int)(g_slotSelectionTextReferenceShared1 + 88),
    2, (unsigned int)(g_slotSelectionTextReferenceShared1 + 40), 3, (unsigned int)(g_slotSelectionTextReferenceShared1 + 52),
    4, (unsigned int)(g_slotSelectionTextReferenceShared1 + 100), 5, (unsigned int)(g_slotSelectionTextReferenceShared1 + 28),
    6, (unsigned int)(g_slotSelectionTextReferenceShared3 + 24), 7, (unsigned int)(g_slotSelectionTextReferenceShared3 + 36),
    8, (unsigned int)(g_slotSelectionTextReferenceShared3 + 12), 9, (unsigned int)(g_slotSelectionTextReferenceShared1 + 76),
    10, (unsigned int)(g_slotSelectionTextReferenceShared3 + 48), 11, (unsigned int)(g_slotSelectionTextReferenceShared1 + 104),
    12, (unsigned int)(g_slotSelectionTextReferenceShared1 + 112), 13, (unsigned int)g_slotSelectionTextReferenceShared3,
    14, (unsigned int)(g_slotSelectionTextReferenceShared1 + 108), 17, (unsigned int)(g_slotSelectionTextReferenceShared3 + 60),
    18, (unsigned int)(g_slotSelectionTextReferenceShared1 + 64),
};
#endif

/* g_rewardItemLabelPointerTailUsRev1_GRewarditemtiers.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E3594_unclaimed_E4390_unclaimed_E441C_unclaimed_E45B4 */
extern char g_slotSelectionTextReferenceShared4[];
void *g_rewardItemLabelPointerTailUsRev1[3] = {
    (void *)(g_slotSelectionTextReferenceShared4 + 204), (void *)(g_slotSelectionTextReferenceShared4 + 208), (void *)(g_slotSelectionTextReferenceShared4 + 212),
};
#endif
