#include "DATA/REST_SOURCE_RECORDS.H"
extern s32 g_weaponChargeSpinTarget;
extern char g_weaponFireStateCallbackTable[];
#include "DATA/OVL1_F/WEAPON_CHARGE_CALLBACK_ADDRESS.H"
#include "DATA/WEAPON_EVENT_CALLBACKS/WEAPONAI_TRYENTERALTERNATEAMMOMODE.H"
#include "DATA/WEAPON_EVENT_CALLBACKS/WEAPON_REQUEST_RELEASE_ON_ENABLED_EVENT_ADDRESS.H"
#include "DATA/WEAPON_EVENT_CALLBACKS/RESOURCE_CALLBACK_LABELS.H"
#include "DATA/WEAPON_EVENT_CALLBACKS/OVERLAY_SIX_EFFECT_CALLBACK_ROM_ENTRY.H"
#include "DATA/WEAPON_EVENT_CALLBACKS/WEAPONAI_TRYENTERCHARGEDALTERNATEMODE.H"
#include "DATA/WEAPON_EVENT_CALLBACKS/WEAPON_EVENT_CALLBACK_ADDRESS.H"
#include "DATA/WEAPON_EVENT_CALLBACKS/WEAPON_FORCE_MARKER_ADDRESS.H"
#include "include_asm.h"
#include "DATA/WEAPON_EVENT_CALLBACKS/WEAPON_INITIALIZEFIRESTATECALLBACKS_LABEL.H"

/* 800CF8C4.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4 */
void * g_Ovltab6EncodedWordsBlock6[15] = {
    0, 0, 0, 0, 0, 0,
    0, (void *)&g_weaponFireStateCallbackTable, 0, 0, 0, 0,
    0, 0, 0,
};

/* ROM-grounded data: src/rw_weapon_state_entry_D0500_us_rev1.c */
RestWeaponStateEntryD0500UsRev1Record885 g_WeaponStateEntryD0500UsRev1 = {
    2,
    (unsigned int)addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant2,
};
#endif

/* 800CF908.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508 */
RestOvltab6EncodedWordsBlock13Record886 g_Ovltab6EncodedWordsBlock13 = {
    (unsigned int)addrLow_Weaponai_TryEnterAlternateAmmoMode,
    0x00000000,
};
#endif

/* 800CF908_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_resource_animation_D0510_us_rev1.c */
RestWeaponStateResourceAnimationD0510UsRev1Record887 g_WeaponStateResourceAnimationD0510UsRev1 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* 800CF920.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D0520_us_rev1.c */
RestWeaponStateEntryD0520UsRev1Record888 g_WeaponStateEntryD0520UsRev1 = {
    3,
    0x00000000,
};
#endif

/* 800CF928.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528 */
RestOvltab6EncodedWordsBlock8Record889 g_Ovltab6EncodedWordsBlock8 = {
    (unsigned int)addrLow_Weaponai_TryEnterAlternateAmmoMode,
    0x00000000,
};

RestOvltab6EncodedWordsBlock16Record890 g_Ovltab6EncodedWordsBlock16 = {
    20110,
    1.0f,
    0,
    0,
};
#endif

/* 800CF940.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D0540_us_rev1.c */
RestWeaponStateEntryD0540UsRev1Record891 g_WeaponStateEntryD0540UsRev1 = {
    5,
    0x00000000,
};
#endif

/* 800CF948.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548 */
RestOvltab6EncodedWordsBlock11Record892 g_Ovltab6EncodedWordsBlock11 = {
    (unsigned int)addrLow_Weapon_RequestReleaseOnEnabledEvent,
    0x00000000,
};
#endif

/* 800CF948_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_resource_animation_D0550_us_rev1.c */
RestWeaponStateResourceAnimationD0550UsRev1Record893 g_WeaponStateResourceAnimationD0550UsRev1 = {
    20200,
    1.0f,
    3,
    0,
};
#endif

/* 800CF960.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D0560_us_rev1.c */
RestWeaponStateEndD0560UsRev1Record894 g_WeaponStateEndD0560UsRev1 = {
    -1,
};
#endif

/* 800CF964.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548_unclaimed_D0560_unclaimed_D0564 */
void * g_Ovltab6EncodedWordsBlock7[15] = {
    0, 0, 0, 0, 0, 0,
    0, (void *)((char *)&g_weaponChargeSpinTarget + 804), 0, 0, 0, 0,
    0, 0, 0,
};

/* ROM-grounded data: src/rw_weapon_state_entry_D05A0_us_rev1.c */
RestWeaponStateEntryD05A0UsRev1Record896 g_WeaponStateEntryD05A0UsRev1 = {
    5,
    (unsigned int)addrLow_Weapon_PlayStartupCue80C,
};
#endif

/* 800CF9A8.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548_unclaimed_D0560_unclaimed_D0564_unclaimed_D05A8 */
RestOvltab6EncodedWordsBlock5Record897 g_Ovltab6EncodedWordsBlock5 = {
    (unsigned int)addrLow_Weapon_UpdateAlternateTriggerCompletion,
    0x00000000,
};

RestOvltab6EncodedWordsBlock18Record898 g_Ovltab6EncodedWordsBlock18 = {
    20200,
    1.0f,
    3,
    0,
};
#endif

/* 800CF9C0.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D05C0_us_rev1.c */
RestWeaponStateEndD05C0UsRev1Record899 g_WeaponStateEndD05C0UsRev1 = {
    -1,
};
#endif

/* 800CF9C4.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548_unclaimed_D0560_unclaimed_D0564_unclaimed_D05A8_unclaimed_D05C0_unclaimed_D05C4 */
RestOvltab6EncodedWordsBlock1Layout900 g_Ovltab6EncodedWordsBlock1 = {
    { 0, 0, 0, 0, 0, 0, 0 },
    3e+01f,
    { (void *)&g_weaponFireStateCallbackTable, 0, 0, 0, 0, 0, 0, 0 },
};

/* ROM-grounded data: src/rw_weapon_state_entry_D0604_us_rev1.c */
RestWeaponStateEntryD0604UsRev1Record901 g_WeaponStateEntryD0604UsRev1 = {
    2,
    0x00000000,
};
#endif

/* 800CFA0C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548_unclaimed_D0560_unclaimed_D0564_unclaimed_D05A8_unclaimed_D05C0_unclaimed_D05C4_unclaimed_D060C */
RestOvltab6EncodedWordsBlock4Record902 g_Ovltab6EncodedWordsBlock4 = {
    (unsigned int)addrLow_Weaponai_TryEnterChargedAlternateMode,
    0x00000000,
};

RestOvltab6EncodedWordsBlock15Record903 g_Ovltab6EncodedWordsBlock15 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* 800CFA24.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D0624_us_rev1.c */
RestWeaponStateEntryD0624UsRev1Record904 g_WeaponStateEntryD0624UsRev1 = {
    3,
    0x00000000,
};
#endif

/* 800CFA2C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548_unclaimed_D0560_unclaimed_D0564_unclaimed_D05A8_unclaimed_D05C0_unclaimed_D05C4_unclaimed_D060C_unclaimed_D0624_unclaimed_D062C */
RestOvltab6EncodedWordsRecord905 g_Ovltab6EncodedWords = {
    (unsigned int)addrLow_Weaponai_TryEnterChargedAlternateMode,
    0x00000000,
};

RestOvltab6EncodedWordsBlock14Record906 g_Ovltab6EncodedWordsBlock14 = {
    20110,
    1.0f,
    0,
    0,
};
#endif

/* 800CFA44.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D0644_us_rev1.c */
RestWeaponStateEntryD0644UsRev1Record907 g_WeaponStateEntryD0644UsRev1 = {
    5,
    0x00000000,
};
#endif

/* 800CFA4C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548_unclaimed_D0560_unclaimed_D0564_unclaimed_D05A8_unclaimed_D05C0_unclaimed_D05C4_unclaimed_D060C_unclaimed_D0624_unclaimed_D062C_unclaimed_D0644_unclaimed_D064C */
RestOvltab6EncodedWordsBlock10Record908 g_Ovltab6EncodedWordsBlock10 = {
    (unsigned int)addrLow_Weapon_ApproachSpinPhaseAndRelease,
    0x00000000,
};

RestOvltab6EncodedWordsBlock17Record909 g_Ovltab6EncodedWordsBlock17 = {
    20100,
    1.0f,
    3,
    0,
};
#endif

/* 800CFA64.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D0664_us_rev1.c */
RestWeaponStateEndD0664UsRev1Record910 g_WeaponStateEndD0664UsRev1 = {
    -1,
};
#endif

/* 800CFA68.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548_unclaimed_D0560_unclaimed_D0564_unclaimed_D05A8_unclaimed_D05C0_unclaimed_D05C4_unclaimed_D060C_unclaimed_D0624_unclaimed_D062C_unclaimed_D0644_unclaimed_D064C_unclaimed_D0664_unclaimed_D0668 */
void * g_Ovltab6EncodedWordsBlock3[15] = {
    0, 0, 0, 0, 0, 0,
    0, (void *)&g_weaponFireStateCallbackTable, 0, 0, 0, 0,
    0, 0, 0,
};

/* ROM-grounded data: src/rw_weapon_state_entry_D06A4_us_rev1.c */
RestWeaponStateEntryD06A4UsRev1Record912 g_WeaponStateEntryD06A4UsRev1 = {
    2,
    0x00000000,
};
#endif

/* 800CFAAC.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548_unclaimed_D0560_unclaimed_D0564_unclaimed_D05A8_unclaimed_D05C0_unclaimed_D05C4_unclaimed_D060C_unclaimed_D0624_unclaimed_D062C_unclaimed_D0644_unclaimed_D064C_unclaimed_D0664_unclaimed_D0668_unclaimed_D06AC */
RestOvltab6EncodedWordsBlock9Record913 g_Ovltab6EncodedWordsBlock9 = {
    (unsigned int)addrLow_Weaponai_UpdateForceMarkerTrigger,
    0x00000000,
};

RestOvltab6EncodedWordsBlock19Record914 g_Ovltab6EncodedWordsBlock19 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

/* 800CFAC4.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_entry_D06C4_us_rev1.c */
RestWeaponStateEntryD06C4UsRev1Record915 g_WeaponStateEntryD06C4UsRev1 = {
    3,
    0x00000000,
};
#endif

/* 800CFACC.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548_unclaimed_D0560_unclaimed_D0564_unclaimed_D05A8_unclaimed_D05C0_unclaimed_D05C4_unclaimed_D060C_unclaimed_D0624_unclaimed_D062C_unclaimed_D0644_unclaimed_D064C_unclaimed_D0664_unclaimed_D0668_unclaimed_D06AC_unclaimed_D06C4_unclaimed_D06CC */
RestOvltab6EncodedWordsBlock2Record916 g_Ovltab6EncodedWordsBlock2 = {
    (unsigned int)addrLow_Weaponai_UpdateForceMarkerTrigger,
    0x00000000,
};
#endif

/* 800CFACC_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_resource_animation_D06D4_us_rev1.c */
RestWeaponStateResourceAnimationD06D4UsRev1Record917 g_WeaponStateResourceAnimationD06D4UsRev1 = {
    20110,
    1.0f,
    0,
    0,
};
#endif

/* 800CFAE4.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_weapon_state_end_D06E4_us_rev1.c */
RestWeaponStateEndD06E4UsRev1Record918 g_WeaponStateEndD06E4UsRev1 = {
    -1,
};
#endif

/* 800CFAE8.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CF5C0_unclaimed_D01E8_unclaimed_D0200_unclaimed_D0208_unclaimed_D0220_unclaimed_D0228_unclaimed_D0240_unclaimed_D0244_unclaimed_D0288_unclaimed_D02A0_unclaimed_D02A8_unclaimed_D02C0_unclaimed_D02C4_unclaimed_D0308_unclaimed_D0320_unclaimed_D0324_unclaimed_D0368_unclaimed_D0380_unclaimed_D0388_unclaimed_D03A0_unclaimed_D03A8_unclaimed_D03C0_unclaimed_D03C4_unclaimed_D0408_unclaimed_D0420_unclaimed_D0428_unclaimed_D0440_unclaimed_D0444_unclaimed_D0488_unclaimed_D04A0_unclaimed_D04A8_unclaimed_D04C0_unclaimed_D04C4_unclaimed_D0508_unclaimed_D0520_unclaimed_D0528_unclaimed_D0540_unclaimed_D0548_unclaimed_D0560_unclaimed_D0564_unclaimed_D05A8_unclaimed_D05C0_unclaimed_D05C4_unclaimed_D060C_unclaimed_D0624_unclaimed_D062C_unclaimed_D0644_unclaimed_D064C_unclaimed_D0664_unclaimed_D0668_unclaimed_D06AC_unclaimed_D06C4_unclaimed_D06CC_unclaimed_D06E4_unclaimed_D06E8 */
void * g_Ovltab6EncodedWordsBlock12[9] = {
    0, 0, 0, 0, 0, 0,
    0, (void *)&addrLow_Weapon_InitializeFireStateCallbacks, 0,
};
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity0[2] = { 0x0001, 0x0064 };
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoResourceCost0[2] = { 0x0414, 0x000A };
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity1[2] = { 0x0001, 0x0064 };
#endif

/* 800CFB18.CPP */
#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_requirement_item_id_D0714_us_rev1.c */
unsigned short g_WeaponRequirementItemIdD0714UsRev1[] = {
    0x042D,
#if defined(VERSION_US_REV1)
    0x0014,
#endif
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity2[2] = { 0x0001, 0x0064 };
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoResourceCost2[2] = { 0x03E8, 0x000A };
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity3[2] = { 0x0001, 0x0064 };
#endif

/* 800CFB28.CPP */
#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_requirement_item_id_D0724_us_rev1.c */
unsigned short g_WeaponRequirementItemIdD0724UsRev1[] = {
    0x03EB,
#if defined(VERSION_US_REV1)
    0x0019,
#endif
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity4[2] = { 0x0000, 0x00C8 };
#endif

/* 800CFB30.CPP */
#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_requirement_item_id_D072C_us_rev1.c */
unsigned short g_WeaponRequirementItemIdD072CUsRev1[] = {
    0x03F1,
#if defined(VERSION_US_REV1)
    0x0001,
#endif
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity5[2] = { 0x0000, 0x00C8 };
#endif

/* 800CFB38.CPP */
#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_requirement_item_id_D0734_us_rev1.c */
unsigned short g_WeaponRequirementItemIdD0734UsRev1[] = {
    0x0431,
#if defined(VERSION_US_REV1)
    0x0019,
#endif
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity6[2] = { 0x0000, 0x00C8 };
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoResourceCost6[2] = { 0x0007, 0x0001 };
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity7[2] = { 0x0000, 0x00C8 };
#endif

/* 800CFB48.CPP */
#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_requirement_item_id_D0744_us_rev1.c */
unsigned short g_WeaponRequirementItemIdD0744UsRev1[] = {
    0x0439,
#if defined(VERSION_US_REV1)
    0x000C,
#endif
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity8[2] = { 0x0000, 0x00C8 };
#endif

/* 800CFB50.CPP */
#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_requirement_item_id_D074C_us_rev1.c */
unsigned short g_WeaponRequirementItemIdD074CUsRev1[] = {
    0x0433,
#if defined(VERSION_US_REV1)
    0x0001,
#endif
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity9[2] = { 0x0000, 0x00C8 };
#endif

/* 800CFB58.CPP */
#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_requirement_item_id_D0754_us_rev1.c */
unsigned short g_WeaponRequirementItemIdD0754UsRev1[] = {
    0x0437,
#if defined(VERSION_US_REV1)
    0x0001,
#endif
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity10[2] = { 0x0000, 0x00C8 };
#endif

/* 800CFB60.CPP */
#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_requirement_item_id_D075C_us_rev1.c */
unsigned short g_WeaponRequirementItemIdD075CUsRev1[] = {
    0x03F9,
#if defined(VERSION_US_REV1)
    0x0002,
#endif
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity11[2] = { 0x0001, 0x0064 };
#endif

/* 800CFB68.CPP */
#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_requirement_item_id_D0764_us_rev1.c */
unsigned short g_WeaponRequirementItemIdD0764UsRev1[] = {
    0x03F5,
#if defined(VERSION_US_REV1)
    0x000A,
#endif
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity12[2] = { 0x0001, 0x0064 };
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoResourceCost12[2] = { 0x0416, 0x0005 };
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity13[2] = { 0x0001, 0x0064 };
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoResourceCost13[2] = { 0x0405, 0x0003 };
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponAmmoSlotCapacity14[2] = { 0x0001, 0x0064 };
#endif
