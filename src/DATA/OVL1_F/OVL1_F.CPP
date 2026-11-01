#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_playerReactionReserveApproachRate[];
extern char g_weaponFireStateCallbackTable[];
#include "DATA/OVL1_F/WEAPON_CHARGE_CALLBACK_ADDRESS.H"
#include "DATA/OVL1_F/g_overlayOneFLinkRecordConstantWords_Ovl1F.H"
#include "DATA/OVL1_F/g_overlayOneFLinkRecordLinkWordsBlock3_Ovl1F.H"
#include "DATA/OVL1_F/g_overlayOneFLinkRecordLinkWordsBlock4_Ovl1F.H"
#include "DATA/OVL1_F/g_overlayOneFLinkRecordLinkWordsBlock5_Ovl1F.H"
#include "DATA/OVL1_F/g_overlayOneFLinkRecordLinkWordsBlock7_Ovl1F.H"
#include "DATA/OVL1_F/WEAPON_UPDATE_HELD_FIRE_CALLBACK_ADDRESS.H"
#include "DATA/OVL1_F/g_overlayOneFLinkRecordConstantWordsBlock10_Ovl1F.H"
#include "DATA/OVL1_F/g_overlayOneFLinkRecordLinkWordsBlock11_Ovl1F.H"
#include "DATA/OVL1_F/g_overlayOneFLinkRecordConstantWordsBlock13_Ovl1F.H"
#include "DATA/OVL1_F/g_overlayOneFLinkRecordLinkWordsBlock13_Ovl1F.H"
#include "DATA/OVL1_F/g_overlayOneFLinkRecordConstantWordsBlock19_Ovl1F.H"

/* g_overlayOneFLinkRecordAddressWords_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
extern char g_weaponFireStateCallbackTable[];
void * g_overlayOneFLinkRecordAddressWords[8] = {
    (void *)&g_weaponFireStateCallbackTable, 0, 0, 0,
    0, 0, 0, 0,
};
#endif

/* WEAPON_CHARGE_CALLBACK_ADDRESS.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D01E0_us_rev1.c */
RestoverlayOneFLinkRecordLinkWordsRecord708 g_overlayOneFLinkRecordLinkWords = {
    2,
    (unsigned int)addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant2,
};
#endif

/* g_overlayOneFLinkRecordConstantWords_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8 */
RestoverlayOneFLinkRecordLinkWordsBlock1Record709 g_overlayOneFLinkRecordLinkWordsBlock1 = {
    (unsigned int)addrLow_Weaponai_ToggleFiringModeWithAmmoCheck,
    0x00000000,
};

RestoverlayOneFLinkRecordConstantWordsRecord710 g_overlayOneFLinkRecordConstantWords = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock1_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D0200_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock1Record711 g_overlayOneFLinkRecordConstantWordsBlock1 = {
    3,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordLinkWordsBlock2_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208 */
RestoverlayOneFLinkRecordLinkWordsBlock2Record712 g_overlayOneFLinkRecordLinkWordsBlock2 = {
    (unsigned int)addrLow_Weaponai_ToggleFiringModeWithAmmoCheck,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock2_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_resource_animation_D0210_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock2Record713 g_overlayOneFLinkRecordConstantWordsBlock2 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordLinkWordsBlock3_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D0220_us_rev1.c */
RestoverlayOneFLinkRecordLinkWordsBlock3Record714 g_overlayOneFLinkRecordLinkWordsBlock3 = {
    4,
    (unsigned int)addrLow_Weapon_EnterChargeStateWithCues,
};
#endif

/* g_overlayOneFLinkRecordLinkWordsBlock4_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228 */
RestoverlayOneFLinkRecordLinkWordsBlock4Record715 g_overlayOneFLinkRecordLinkWordsBlock4 = {
    (unsigned int)addrLow_Weaponai_UpdateSpinAndRepeatCue,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock3_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_resource_animation_D0230_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock3Record716 g_overlayOneFLinkRecordConstantWordsBlock3 = {
    20200,
    1.0f,
    3,
    0,
};
#endif

/* g_overlayOneFLinkRecordSentinelWords_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D0240_us_rev1.c */
RestoverlayOneFLinkRecordSentinelWordsRecord717 g_overlayOneFLinkRecordSentinelWords = {
    -1,
};
#endif

/* g_overlayOneFLinkRecordAddressWordsBlock1_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
extern char g_weaponFireStateCallbackTable[];
void * g_overlayOneFLinkRecordAddressWordsBlock1[15] = {
    0, 0, 0, 0,
    0, 0, 0, (void *)&g_weaponFireStateCallbackTable,
    0, 0, 0, 0,
    0, 0, 0,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock4_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D0280_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock4Record718 g_overlayOneFLinkRecordConstantWordsBlock4 = {
    2,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordLinkWordsBlock5_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288 */
RestoverlayOneFLinkRecordLinkWordsBlock5Record719 g_overlayOneFLinkRecordLinkWordsBlock5 = {
    (unsigned int)addrLow_Weaponai_UpdateAnimatedFiringMode,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock5_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_resource_animation_D0290_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock5Record720 g_overlayOneFLinkRecordConstantWordsBlock5 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock6_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D02A0_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock6Record721 g_overlayOneFLinkRecordConstantWordsBlock6 = {
    3,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordLinkWordsBlock6_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8 */
RestoverlayOneFLinkRecordLinkWordsBlock6Record722 g_overlayOneFLinkRecordLinkWordsBlock6 = {
    (unsigned int)addrLow_Weaponai_UpdateAnimatedFiringMode,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock7_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_resource_animation_D02B0_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock7Record723 g_overlayOneFLinkRecordConstantWordsBlock7 = {
    20110,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordSentinelWordsBlock1_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D02C0_us_rev1.c */
RestoverlayOneFLinkRecordSentinelWordsBlock1Record724 g_overlayOneFLinkRecordSentinelWordsBlock1 = {
    -1,
};
#endif

/* g_overlayOneFLinkRecordAddressWordsBlock2_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
extern char g_weaponFireStateCallbackTable[];
void * g_overlayOneFLinkRecordAddressWordsBlock2[15] = {
    0, 0, 0, 0,
    0, 0, 0, (void *)&g_weaponFireStateCallbackTable,
    0, 0, 0, 0,
    0, 0, 0,
};
#endif

/* g_overlayOneFLinkRecordLinkWordsBlock7_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D0300_us_rev1.c */
RestoverlayOneFLinkRecordLinkWordsBlock7Record725 g_overlayOneFLinkRecordLinkWordsBlock7 = {
    8,
    (unsigned int)addrLow_Weapon_SetDelayAndRequestStateEight,
};
#endif

/* WEAPON_UPDATE_HELD_FIRE_CALLBACK_ADDRESS.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308 */
void * g_overlayOneFLinkRecordLinkWordsBlock8[3] = {
    (void *)&addrLow_Weaponai_UpdateHeldFire, 0, (void *)((char *)&g_playerReactionReserveApproachRate + 36),
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock8_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_animation_D0314_us_rev1.c */
RestLinkerAlignmentFill12 g_overlayOneFLinkRecordConstantBlock8LinkerAlignmentFill727 = {
    { 63, 128, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0 },
};
#endif

/* g_overlayOneFLinkRecordSentinelWordsBlock2_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D0320_us_rev1.c */
RestoverlayOneFLinkRecordSentinelWordsBlock2Record728 g_overlayOneFLinkRecordSentinelWordsBlock2 = {
    -1,
};
#endif

/* g_overlayOneFLinkRecordAddressWordsBlock3_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324 */
extern char g_weaponFireStateCallbackTable[];
void * g_overlayOneFLinkRecordAddressWordsBlock3[15] = {
    0, 0, 0, 0,
    0, 0, 0, (void *)&g_weaponFireStateCallbackTable,
    0, 0, 0, 0,
    0, 0, 0,
};

/* ROM-grounded data: src/rw_weapon_state_entry_D0360_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock9Record729 g_overlayOneFLinkRecordConstantWordsBlock9 = {
    2,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock10_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368 */
RestoverlayOneFLinkRecordLinkWordsBlock9Record730 g_overlayOneFLinkRecordLinkWordsBlock9 = {
    (unsigned int)addrLow_Weaponai_TryEnterAmmoCostState,
    0x00000000,
};

RestoverlayOneFLinkRecordConstantWordsBlock10Record731 g_overlayOneFLinkRecordConstantWordsBlock10 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock11_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D0380_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock11Record732 g_overlayOneFLinkRecordConstantWordsBlock11 = {
    3,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock12_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388 */
RestoverlayOneFLinkRecordLinkWordsBlock10Record733 g_overlayOneFLinkRecordLinkWordsBlock10 = {
    (unsigned int)addrLow_Weaponai_TryEnterAmmoCostState,
    0x00000000,
};

RestoverlayOneFLinkRecordConstantWordsBlock12Record734 g_overlayOneFLinkRecordConstantWordsBlock12 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordLinkWordsBlock11_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D03A0_us_rev1.c */
RestoverlayOneFLinkRecordLinkWordsBlock11Record735 g_overlayOneFLinkRecordLinkWordsBlock11 = {
    11,
    (unsigned int)addrLow_Weapon_EmptyAlternateFireHook,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock13_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8 */
RestoverlayOneFLinkRecordLinkWordsBlock12Record736 g_overlayOneFLinkRecordLinkWordsBlock12 = {
    (unsigned int)addrLow_Weapon_UpdateHeldAlternateFire_Ovl1F,
    0x00000000,
};

RestoverlayOneFLinkRecordConstantWordsBlock13Record737 g_overlayOneFLinkRecordConstantWordsBlock13 = {
    20200,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordSentinelWordsBlock3_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D03C0_us_rev1.c */
RestoverlayOneFLinkRecordSentinelWordsBlock3Record738 g_overlayOneFLinkRecordSentinelWordsBlock3 = {
    -1,
};
#endif

/* g_overlayOneFLinkRecordAddressWordsBlock4_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4 */
void * g_overlayOneFLinkRecordAddressWordsBlock4[15] = {
    0, 0, 0, 0, 0, 0,
    0, (void *)&g_weaponFireStateCallbackTable, 0, 0, 0, 0,
    0, 0, 0,
};

/* ROM-grounded data: src/rw_weapon_state_entry_D0400_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock14Record740 g_overlayOneFLinkRecordConstantWordsBlock14 = {
    2,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordLinkWordsBlock13_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408 */
RestoverlayOneFLinkRecordLinkWordsBlock13Record741 g_overlayOneFLinkRecordLinkWordsBlock13 = {
    (unsigned int)addrLow_Weaponai_TryEnterAlternateStateEight,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock15_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_resource_animation_D0410_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock15Record742 g_overlayOneFLinkRecordConstantWordsBlock15 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock16_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D0420_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock16Record743 g_overlayOneFLinkRecordConstantWordsBlock16 = {
    3,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock17_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428 */
RestoverlayOneFLinkRecordLinkWordsBlock14Record744 g_overlayOneFLinkRecordLinkWordsBlock14 = {
    (unsigned int)addrLow_Weaponai_TryEnterAlternateStateEight,
    0x00000000,
};

RestoverlayOneFLinkRecordConstantWordsBlock17Record745 g_overlayOneFLinkRecordConstantWordsBlock17 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordSentinelWordsBlock4_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D0440_us_rev1.c */
RestoverlayOneFLinkRecordSentinelWordsBlock4Record746 g_overlayOneFLinkRecordSentinelWordsBlock4 = {
    -1,
};
#endif

/* g_overlayOneFLinkRecordAddressWordsBlock5_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444 */
void * g_overlayOneFLinkRecordAddressWordsBlock5[15] = {
    0, 0, 0, 0, 0, 0,
    0, (void *)&g_weaponFireStateCallbackTable, 0, 0, 0, 0,
    0, 0, 0,
};

/* ROM-grounded data: src/rw_weapon_state_entry_D0480_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock18Record748 g_overlayOneFLinkRecordConstantWordsBlock18 = {
    2,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock19_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488 */
RestoverlayOneFLinkRecordLinkWordsBlock15Record749 g_overlayOneFLinkRecordLinkWordsBlock15 = {
    (unsigned int)addrLow_Weapon_UpdateSpecialFireAndAmmo,
    0x00000000,
};

RestoverlayOneFLinkRecordConstantWordsBlock19Record750 g_overlayOneFLinkRecordConstantWordsBlock19 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock20_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D04A0_us_rev1.c */
RestoverlayOneFLinkRecordConstantWordsBlock20Record751 g_overlayOneFLinkRecordConstantWordsBlock20 = {
    3,
    0x00000000,
};
#endif

/* g_overlayOneFLinkRecordConstantWordsBlock21_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8 */
RestoverlayOneFLinkRecordLinkWordsBlock16Record752 g_overlayOneFLinkRecordLinkWordsBlock16 = {
    (unsigned int)addrLow_Weapon_UpdateSpecialFireAndAmmo,
    0x00000000,
};

RestoverlayOneFLinkRecordConstantWordsBlock21Record753 g_overlayOneFLinkRecordConstantWordsBlock21 = {
    20110,
    1.0f,
    0,
    0,
};
#endif

/* g_overlayOneFLinkRecordSentinelWordsBlock5_Ovl1F.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D04C0_us_rev1.c */
RestoverlayOneFLinkRecordSentinelWordsBlock5Record754 g_overlayOneFLinkRecordSentinelWordsBlock5 = {
    -1,
};
#endif
