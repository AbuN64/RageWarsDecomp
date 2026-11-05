#include "Ai/player_reaction_rate_data.h"
#include "Weapons/pitch_translation_and_spin_actions.h"
#include "Data/rest_source_records.h"
#include "Data/Ovl1_f/weapon_charge_callback_address.h"
#include "Data/Ovl1_f/g_overlayoneflinkrecordconstantwords_ovl1f.h"
#include "Data/Ovl1_f/g_overlayoneflinkrecordlinkwordsblock3_ovl1f.h"
#include "Data/Ovl1_f/g_overlayoneflinkrecordlinkwordsblock4_ovl1f.h"
#include "Data/Ovl1_f/g_overlayoneflinkrecordlinkwordsblock5_ovl1f.h"
#include "Data/Ovl1_f/g_overlayoneflinkrecordlinkwordsblock7_ovl1f.h"
#include "Data/Ovl1_f/weapon_update_held_fire_callback_address.h"
#include "Data/Ovl1_f/g_overlayoneflinkrecordconstantwordsblock10_ovl1f.h"
#include "Data/Ovl1_f/g_overlayoneflinkrecordlinkwordsblock11_ovl1f.h"
#include "Data/Ovl1_f/g_overlayoneflinkrecordconstantwordsblock13_ovl1f.h"
#include "Data/Ovl1_f/g_overlayoneflinkrecordlinkwordsblock13_ovl1f.h"
#include "Data/Ovl1_f/g_overlayoneflinkrecordconstantwordsblock19_ovl1f.h"
#include "Data/Ovl1_f/ovl1_f.h"
#include "Common/runtime_declarations.h"

#if defined(VERSION_US_REV1)
void * g_overlayOneFLinkRecordAddress[8] = {
    (void *)&g_weaponFireStateCallbackTable, 0, 0, 0,
    0, 0, 0, 0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsRecord g_overlayOneFLinkRecordLink_usrev1_D01E0 = {
    2,
    (unsigned int)addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant2,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock1Record g_overlayOneFToggleFiringModeWithAmmoCheckLinkPrimary_usrev1_D01E8 = {
    (unsigned int)Weaponai_ToggleFiringModeWithAmmoCheck,
    0x00000000,
};

OverlayOneFLinkRecordConstantWordsRecord g_overlayOneFLinkRecordConstant_usrev1_D01F0 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock1Record g_overlayOneFToggleFiringModeWithAmmoCheckModeAlternate_usrev1_D0200 = {
    3,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock2Record g_overlayOneFToggleFiringModeWithAmmoCheckLinkAlternate_usrev1_D0208 = {
    (unsigned int)Weaponai_ToggleFiringModeWithAmmoCheck,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock2Record g_overlayOneFToggleFiringModeWithAmmoCheckParametersAlternate_usrev1_D0210 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock3Record g_overlayOneFEnterChargeStateWithCuesLinkPrimary_usrev1_D0220 = {
    4,
    (unsigned int)Weapon_EnterChargeStateWithCues,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock4Record g_overlayOneFUpdateSpinAndRepeatCueLinkPrimary_usrev1_D0228 = {
    (unsigned int)Weaponai_UpdateSpinAndRepeatCue,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock3Record g_overlayOneFUpdateSpinAndRepeatCueParametersPrimary_usrev1_D0230 = {
    20200,
    1.0f,
    3,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordSentinelWordsRecord g_overlayOneFLinkRecordSentinel_usrev1_D0240 = {
    -1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_weaponSlotUpdateSpinAndRepeatCueFireStateSlots[15] = {
    0, 0, 0, 0,
    0, 0, 0, (void *)&g_weaponFireStateCallbackTable,
    0, 0, 0, 0,
    0, 0, 0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock4Record g_overlayOneFUpdateAnimatedFiringModeModePrimary_usrev1_D0280 = {
    2,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock5Record g_overlayOneFUpdateAnimatedFiringModeLinkPrimary_usrev1_D0288 = {
    (unsigned int)Weaponai_UpdateAnimatedFiringMode,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock5Record g_overlayOneFUpdateAnimatedFiringModeParametersPrimary_usrev1_D0290 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock6Record g_overlayOneFUpdateAnimatedFiringModeModeAlternate_usrev1_D02A0 = {
    3,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock6Record g_overlayOneFUpdateAnimatedFiringModeLinkAlternate_usrev1_D02A8 = {
    (unsigned int)Weaponai_UpdateAnimatedFiringMode,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock7Record g_overlayOneFUpdateAnimatedFiringModeParametersAlternate_usrev1_D02B0 = {
    20110,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordSentinelWordsBlock1Record g_overlayOneFUpdateAnimatedFiringModeSentinel_usrev1_D02C0 = {
    -1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_overlayOneFUpdateAnimatedFiringModeFireStateSlots[15] = {
    0, 0, 0, 0,
    0, 0, 0, (void *)&g_weaponFireStateCallbackTable,
    0, 0, 0, 0,
    0, 0, 0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock7Record g_overlayOneFSetDelayAndRequestAlternateFireStateLinkPrimary_usrev1_D0300 = {
    8,
    (unsigned int)Weapon_SetDelayAndRequestAlternateFireState,
};
#endif

#if defined(VERSION_US_REV1)
void * g_overlayOneFUpdateHeldFireAnimationChoices[3] = {
    (void *)&Weaponai_UpdateHeldFire, 0, (void *)&g_weaponAnimationChoicesB,
};
#endif

#if defined(VERSION_US_REV1)
ByteBlock12 g_overlayOneFSetDelayAndRequestAlternateFireStateParametersPrimary_usrev1_D0314 = {
    { 63, 128, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordSentinelWordsBlock2Record g_overlayOneFSetDelayAndRequestAlternateFireStateSentinel_usrev1_D0320 = {
    -1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_weaponDelayedFireStateSlots[15] = {
    0, 0, 0, 0,
    0, 0, 0, (void *)&g_weaponFireStateCallbackTable,
    0, 0, 0, 0,
    0, 0, 0,
};

OverlayOneFLinkRecordConstantWordsBlock9Record g_overlayOneFTryEnterAmmoCostStateModePrimary_usrev1_D0360 = {
    2,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock9Record g_overlayOneFTryEnterAmmoCostStateLinkPrimary_usrev1_D0368 = {
    (unsigned int)Weaponai_TryEnterAmmoCostState,
    0x00000000,
};

OverlayOneFLinkRecordConstantWordsBlock10Record g_overlayOneFTryEnterAmmoCostStateParametersPrimary_usrev1_D0370 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock11Record g_overlayOneFTryEnterAmmoCostStateModeAlternate_usrev1_D0380 = {
    3,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock10Record g_overlayOneFTryEnterAmmoCostStateLinkAlternate_usrev1_D0388 = {
    (unsigned int)Weaponai_TryEnterAmmoCostState,
    0x00000000,
};

OverlayOneFLinkRecordConstantWordsBlock12Record g_overlayOneFTryEnterAmmoCostStateParametersAlternate_usrev1_D0390 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock11Record g_overlayOneFEmptyAlternateFireHookLinkPrimary_usrev1_D03A0 = {
    11,
    (unsigned int)Weapon_EmptyAlternateFireHook,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock12Record g_overlayOneFUpdateHeldAlternateFireLinkPrimary_usrev1_D03A8 = {
    (unsigned int)addrLow_Weapon_UpdateHeldAlternateFire_Ovl1F,
    0x00000000,
};

OverlayOneFLinkRecordConstantWordsBlock13Record g_overlayOneFUpdateHeldAlternateFireParametersPrimary_usrev1_D03B0 = {
    20200,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordSentinelWordsBlock3Record g_overlayOneFUpdateHeldAlternateFireSentinel_usrev1_D03C0 = {
    -1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_overlayOneFUpdateHeldAlternateFireFireStateSlots[15] = {
    0, 0, 0, 0, 0, 0,
    0, (void *)&g_weaponFireStateCallbackTable, 0, 0, 0, 0,
    0, 0, 0,
};

OverlayOneFLinkRecordConstantWordsBlock14Record g_overlayOneFTryEnterAlternateFireStateModePrimary_usrev1_D0400 = {
    2,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock13Record g_overlayOneFTryEnterAlternateFireStateLinkPrimary_usrev1_D0408 = {
    (unsigned int)Weaponai_TryEnterAlternateFireState,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock15Record g_overlayOneFTryEnterAlternateFireStateParametersPrimary_usrev1_D0410 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock16Record g_overlayOneFTryEnterAlternateFireStateModeAlternate_usrev1_D0420 = {
    3,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock14Record g_overlayOneFTryEnterAlternateFireStateLinkAlternate_usrev1_D0428 = {
    (unsigned int)Weaponai_TryEnterAlternateFireState,
    0x00000000,
};

OverlayOneFLinkRecordConstantWordsBlock17Record g_overlayOneFTryEnterAlternateFireStateParametersAlternate_usrev1_D0430 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordSentinelWordsBlock4Record g_overlayOneFTryEnterAlternateFireStateSentinel_usrev1_D0440 = {
    -1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_overlayOneFTryEnterAlternateFireStateFireStateSlots[15] = {
    0, 0, 0, 0, 0, 0,
    0, (void *)&g_weaponFireStateCallbackTable, 0, 0, 0, 0,
    0, 0, 0,
};

OverlayOneFLinkRecordConstantWordsBlock18Record g_overlayOneFUpdateSpecialFireAndAmmoModePrimary_usrev1_D0480 = {
    2,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock15Record g_overlayOneFUpdateSpecialFireAndAmmoLinkPrimary_usrev1_D0488 = {
    (unsigned int)Weapon_UpdateSpecialFireAndAmmo,
    0x00000000,
};

OverlayOneFLinkRecordConstantWordsBlock19Record g_overlayOneFUpdateSpecialFireAndAmmoParametersPrimary_usrev1_D0490 = {
    20100,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordConstantWordsBlock20Record g_overlayOneFUpdateSpecialFireAndAmmoModeAlternate_usrev1_D04A0 = {
    3,
    0x00000000,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordLinkWordsBlock16Record g_overlayOneFUpdateSpecialFireAndAmmoLinkAlternate_usrev1_D04A8 = {
    (unsigned int)Weapon_UpdateSpecialFireAndAmmo,
    0x00000000,
};

OverlayOneFLinkRecordConstantWordsBlock21Record g_overlayOneFUpdateSpecialFireAndAmmoParametersAlternate_usrev1_D04B0 = {
    20110,
    1.0f,
    0,
    0,
};
#endif

#if defined(VERSION_US_REV1)
OverlayOneFLinkRecordSentinelWordsBlock5Record g_overlayOneFUpdateSpecialFireAndAmmoSentinel_usrev1_D04C0 = {
    -1,
};
#endif
