#include "Weapon_state_tables/weapon_state_tables.h"
#include "Data/Ovl1_f/ovl1_f.h"
#include "Weapons/charge_and_linked_actor_handles.h"
#include "include_asm.h"
#include "types.h"
#include "Data/Overlays/encoded_callback.h"
#include "Data/Overlays/Credits/constants_addresses.h"
#include "Ai/weaponai.h"
#include "Engine/Audio/channel.h"
#include "Weapons/pitch_translation_and_spin_actions.h"
#include "Weapons/startup_cues_and_side_yaw.h"
#include "Ai/Weapon/weapon.h"
#include "Common/runtime_declarations.h"
#include "Common/Lone/weapon_locked_notice_text.h"

/* OVLSCENE_LOADSCENERESOURCES_DATA.CPP */
#if !(defined(VERSION_US_REV1))
const char g_objectTypesText[13] =
    "object types\000";
#endif

#if defined(VERSION_US_REV1)
const char k_OvlsceneLoadsceneresourcesEncodedBytes[13] =
    "object types";
#endif

/* INTELLIGENCE_TEXT.CPP */
#if !(defined(VERSION_US_REV1))
const char s_intelligenceText[13] =
    "intelligence\000";
#endif

#if defined(VERSION_US_REV1)
const char g_intelligenceText[13] =
    "intelligence";
#endif

/* BINARIES_INDEX_TEXT.CPP */
#if !(defined(VERSION_US_REV1))
const char g_binariesIndexText[15] =
    "binaries index\000";
#endif

#if defined(VERSION_US_REV1)
const char g_binariesIndexText[15] =
    "binaries index";
#endif

/* DYNAMIC_LIGHTS_TEXT.CPP */
#if !(defined(VERSION_US_REV1))
const char s_dynamicLightsText[15] =
    "dynamic lights\000";
#endif

#if defined(VERSION_US_REV1)
const char g_dynamicLightsText[15] =
    "dynamic lights";
#endif

/* CINEMAS_INDEX_TEXT.CPP */
#if !(defined(VERSION_US_REV1))
const char g_cinemasIndexText[14] =
    "Cinemas index\000";
#endif

#if defined(VERSION_US_REV1)
const char g_cinemasIndexText[14] = "Cinemas index";
#endif

/* WEAPON_ACTION_STATE_TABLE_DE.CPP */
#if defined(VERSION_DE)
u32 g_weaponActionStateTable_de[1026] = {
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000002, ENCODED_CALLBACK_ADDRESS(Weapon_ReleaseLinkedActorHandles),
    ENCODED_CALLBACK_ADDRESS(Weaponai_ToggleFiringModeWithAmmoCheck), 0x00000000,
    0x00004E84, 0x3F800000, 0x00000000, 0x00000000, 0x00000003, 0x00000000,
    ENCODED_CALLBACK_ADDRESS(Weaponai_ToggleFiringModeWithAmmoCheck), 0x00000000, 0x00004E84, 0x3F800000, 0x00000000,
    0x00000000,
    0x00000004, ENCODED_CALLBACK_ADDRESS(Weapon_EnterChargeStateWithCues),
    ENCODED_CALLBACK_ADDRESS(Weaponai_UpdateSpinAndRepeatCue), 0x00000000, 0x00004EE8, 0x3F800000,
    0x00000003, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000002, 0x00000000, ENCODED_CALLBACK_ADDRESS(Weaponai_UpdateAnimatedFiringMode), 0x00000000, 0x00004E84,
    0x3F800000,
    0x00000000, 0x00000000, 0x00000003, 0x00000000, ENCODED_CALLBACK_ADDRESS(Weaponai_UpdateAnimatedFiringMode),
    0x00000000,
    0x00004E8E, 0x3F800000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000008, ENCODED_CALLBACK_ADDRESS(Weapon_SetDelayAndRequestAlternateFireState),
    ENCODED_CALLBACK_ADDRESS(Weaponai_UpdateHeldFire), 0x00000000,
    0x800CA018, 0x3F800000, 0x00000003, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000002, 0x00000000, ENCODED_CALLBACK_ADDRESS(Weaponai_TryEnterAmmoCostState), 0x00000000,
    0x00004E84, 0x3F800000, 0x00000000, 0x00000000, 0x00000003, 0x00000000,
    ENCODED_CALLBACK_ADDRESS(Weaponai_TryEnterAmmoCostState), 0x00000000, 0x00004E84, 0x3F800000, 0x00000000, 0x00000000,
    0x0000000B, ENCODED_CALLBACK_ADDRESS(Weapon_EmptyAlternateFireHook),
    (unsigned int)Weapon_UpdateHeldAlternateFire, 0x00000000, 0x00004EE8, 0x3F800000,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000002, 0x00000000, ENCODED_CALLBACK_ADDRESS(Weaponai_TryEnterAlternateFireState), 0x00000000, 0x00004E84,
    0x3F800000,
    0x00000000, 0x00000000, 0x00000003, 0x00000000, ENCODED_CALLBACK_ADDRESS(Weaponai_TryEnterAlternateFireState),
    0x00000000,
    0x00004E84, 0x3F800000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000002, 0x00000000, ENCODED_CALLBACK_ADDRESS(Weapon_UpdateSpecialFireAndAmmo),
    0x00000000,
    0x00004E84, 0x3F800000, 0x00000000, 0x00000000, 0x00000003, 0x00000000,
    ENCODED_CALLBACK_ADDRESS(Weapon_UpdateSpecialFireAndAmmo), 0x00000000, 0x00004E8E, 0x3F800000, 0x00000000,
    0x00000000,
    0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002,
    ENCODED_CALLBACK_ADDRESS(Weapon_ReleaseLinkedActorHandles),
    ENCODED_CALLBACK_ADDRESS(Weaponai_TryEnterAlternateAmmoMode), 0x00000000, 0x00004E84, 0x3F800000, 0x00000000,
    0x00000000,
    0x00000003, 0x00000000, ENCODED_CALLBACK_ADDRESS(Weaponai_TryEnterAlternateAmmoMode), 0x00000000, 0x00004E8E,
    0x3F800000,
    0x00000000, 0x00000000, 0x00000005, 0x00000000, ENCODED_CALLBACK_ADDRESS(Weapon_RequestReleaseOnEnabledEvent),
    0x00000000,
    0x00004EE8, 0x3F800000, 0x00000003, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponActionStateTable_de[200], 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000005, (unsigned int)Weapon_PlayStartupCue80C,
    ENCODED_CALLBACK_ADDRESS(Weapon_UpdateAlternateTriggerCompletion), 0x00000000,
    0x00004EE8, 0x3F800000, 0x00000003, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x41F00000, (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x00000000,
    ENCODED_CALLBACK_ADDRESS(Weaponai_TryEnterChargedAlternateMode),
    0x00000000, 0x00004E84, 0x3F800000, 0x00000000, 0x00000000, 0x00000003,
    0x00000000, ENCODED_CALLBACK_ADDRESS(Weaponai_TryEnterChargedAlternateMode), 0x00000000, 0x00004E8E, 0x3F800000,
    0x00000000,
    0x00000000, 0x00000005, 0x00000000, ENCODED_CALLBACK_ADDRESS(Weapon_ApproachSpinPhaseAndRelease), 0x00000000,
    0x00004E84,
    0x3F800000, 0x00000003, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)&g_weaponFireStateCallbackTable,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000002, 0x00000000, ENCODED_CALLBACK_ADDRESS(Weaponai_UpdateForceMarkerTrigger), 0x00000000,
    0x00004E84,
    0x3F800000, 0x00000000, 0x00000000, 0x00000003, 0x00000000,
    ENCODED_CALLBACK_ADDRESS(Weaponai_UpdateForceMarkerTrigger),
    0x00000000, 0x00004E8E, 0x3F800000, 0x00000000, 0x00000000, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, ENCODED_CALLBACK_ADDRESS(Weapon_InitializeFireStateCallbacks), 0x00000000, 0x00010064, 0x0414000A,
    0x00010064,
    0x042D0014, 0x00010064, 0x03E8000A, 0x00010064, 0x03EB0019, 0x000000C8,
    0x03F10001, 0x000000C8, 0x04310019, 0x000000C8, 0x00070001, 0x000000C8,
    0x0439000C, 0x000000C8, 0x04330001, 0x000000C8, 0x04370001, 0x000000C8,
    0x03F90002, 0x00010064, 0x03F5000A, 0x00010064, 0x04160005, 0x00010064,
    0x04050003, 0x00010064, 0x041B0032, 0x00010064, 0x0401000A, 0x00010064,
    0x04030032, 0x0002004B, 0x03F70001, 0x0002004B, 0x04250001, 0x0002004B,
    0x03EC0001, 0x0002004B, 0x03EF0001, 0x00010064, 0x03FB000A, 0x00010064,
    0x03FE0064, 0x00010064, 0x0408000A, 0x00010064, 0x04320032, 0x00010064,
    0x03FF0005, 0x00010064, 0x04190032, 0x00030014, 0x01290001, 0x00040014,
    0x040A0001, 0x00050001, 0x040C0001, 0x00060014, 0x040E0001, 0x00010064,
    0x04B0000A, 0x00010064, 0x04B10019, 0x000000C8, 0x04BB0001, 0x000000C8,
    0x04BC0019, 0x000000C8, 0x00070001, 0x000000C8, 0x04C4000C, 0x000000C8,
    0x04C10001, 0x000000C8, 0x04C20001, 0x000000C8, 0x04CB0002, 0x00010064,
    0x04C5000A, 0x00010064, 0x04160005, 0x00010064, 0x04DA0003, 0x00010064,
    0x04DD0032, 0x00010064, 0x0401000A, 0x00010064, 0x04030032, 0x0002004B,
    0x04C90001, 0x0002004B, 0x04CA0001, 0x0002004B, 0x04B40001, 0x0002004B,
    0x03EF0001, 0x00010064, 0x04CD000A, 0x00010064, 0x04D00064, 0x00010064,
    0x04E0000A, 0x00010064, 0x04E30032, 0x00010064, 0x04D10005, 0x00010064,
    0x04D30032, 0x00030014, 0x01290001, 0x00040014, 0x040A0001, 0x00050001,
    0x040C0001, 0x00060014, 0x040E0001, (unsigned int)&g_weaponLockedNoticeText[1], 0x04C30BB8, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFF0000, 0x00000003, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponActionStateTable_de[240], 0x00000000, (unsigned int)Weapon_EaseSpinAndUpdateFeedback, (unsigned int)&g_weaponLockedNoticeText[2],
    0x04D3FFFF, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[3], 0x04D4FFFF, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[4], 0x04C40BB9, 0x0000FFFF,
    0xFFFF02F8, 0x02F90000, 0x00000003, 0x00000000, 0x3F5F66F4, (unsigned int)&g_weaponActionStateTable_de[339],
    (unsigned int)&g_weaponActionStateTable_de[341], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[339],
    (unsigned int)&g_weaponActionStateTable_de[341], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponActionStateTable_de[40], 0x00000000,
    ENCODED_CALLBACK_ADDRESS(Weapon_EmptyChargeStateHook), (unsigned int)&g_weaponLockedNoticeText[5], 0x04C50BBA, 0x0C83FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000023, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[343],
    (unsigned int)&g_weaponActionStateTable_de[345], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[401],
    (unsigned int)&g_weaponActionStateTable_de[403], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[6], 0x04C60BBB, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x3F860A93, (unsigned int)&g_weaponActionStateTable_de[347],
    (unsigned int)&g_weaponActionStateTable_de[349], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[405],
    (unsigned int)&g_weaponActionStateTable_de[407], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponActionStateTable_de[96], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[7], 0x04C70BBC, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000007, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[351],
    (unsigned int)&g_weaponActionStateTable_de[353], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[409],
    (unsigned int)&g_weaponActionStateTable_de[411], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponActionStateTable_de[200], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[8], 0x04C80BBD, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[355],
    (unsigned int)&g_weaponActionStateTable_de[357], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[413],
    (unsigned int)&g_weaponActionStateTable_de[415], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[9], 0x04C90BBE, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[359],
    0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[417], 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)k_weaponFireStateTable, (unsigned int)Weapon_ApplyScaledSideYaw,
    (unsigned int)Weaponai_DecaySpinAndActivateEffect, (unsigned int)&g_weaponLockedNoticeText[10], 0x04CA0BBF, 0x0C83FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000027, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[361],
    (unsigned int)&g_weaponActionStateTable_de[363], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[419],
    (unsigned int)&g_weaponActionStateTable_de[421], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[11], 0x04CB0BC0, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[365],
    (unsigned int)&g_weaponActionStateTable_de[367], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[423],
    (unsigned int)&g_weaponActionStateTable_de[425], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[12], 0x04CC0BC1, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[369],
    (unsigned int)&g_weaponActionStateTable_de[371], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[427],
    (unsigned int)&g_weaponActionStateTable_de[429], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponActionStateTable_de[72], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[13], 0x04CD0BC2, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFF0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[373],
    (unsigned int)&g_weaponActionStateTable_de[375], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[431],
    (unsigned int)&g_weaponActionStateTable_de[433], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponActionStateTable_de[136], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[14], 0x04CE0BC3, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000007, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[377],
    0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[435], 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponActionStateTable_de[305], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[15], 0x04CF0BC4, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFF0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[379],
    0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[437], 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponActionStateTable_de[168], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[16], 0x04D00BC5, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[381],
    (unsigned int)&g_weaponActionStateTable_de[383], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[439],
    (unsigned int)&g_weaponActionStateTable_de[441], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)g_weaponActionStateTable_de, (unsigned int)Weapon_ApplySideDependentYaw,
    ENCODED_CALLBACK_ADDRESS(Weaponai_SettleSpinToThirdTurn), (unsigned int)&g_weaponLockedNoticeText[17], 0x04D10BC6, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[385],
    (unsigned int)&g_weaponActionStateTable_de[387], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[443],
    (unsigned int)&g_weaponActionStateTable_de[445], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable.entries[8], 0x00000000, (unsigned int)Weapon_EaseSpinAndUpdateFeedback, (unsigned int)&g_weaponLockedNoticeText[18], 0x04D20BC7, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[389],
    (unsigned int)&g_weaponActionStateTable_de[391], 0x00000000, (unsigned int)&g_weaponActionStateTable_de[447],
    (unsigned int)&g_weaponActionStateTable_de[449], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponActionStateTable_de[265], (unsigned int)Weapon_TranslateEventSixByPitch, 0x00000000,
    (unsigned int)&g_weaponLockedNoticeText[19], 0x04D50BC8, 0x0000FFFF,
    0xFFFF02C6, 0x02C70000, 0x00000003, 0x40800000, 0x3F490FDC, (unsigned int)&g_weaponActionStateTable_de[393],
    0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[451], 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[20], 0x04D60BC9, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[453],
    0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[395], 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[21], 0x04D70BCA, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[399],
    0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[457], 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeText[23], 0x04D90BCC, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[397],
    0x00000000, 0x00000000, (unsigned int)&g_weaponActionStateTable_de[455], 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponActionStateTable_de[459], (unsigned int)&g_weaponActionStateTable_de[531],
    (unsigned int)&g_weaponActionStateTable_de[555],
    (unsigned int)&g_weaponActionStateTable_de[579], (unsigned int)&g_weaponActionStateTable_de[603],
    (unsigned int)&g_weaponActionStateTable_de[627], (unsigned int)&g_weaponActionStateTable_de[651],
    (unsigned int)&g_weaponActionStateTable_de[675], (unsigned int)&g_weaponActionStateTable_de[699],
    (unsigned int)&g_weaponActionStateTable_de[723], (unsigned int)&g_weaponActionStateTable_de[747],
    (unsigned int)&g_weaponActionStateTable_de[771], (unsigned int)&g_weaponActionStateTable_de[795],
    (unsigned int)&g_weaponActionStateTable_de[819], (unsigned int)&g_weaponActionStateTable_de[843],
    (unsigned int)&g_weaponActionStateTable_de[867], (unsigned int)&g_weaponActionStateTable_de[483],
    (unsigned int)&g_weaponActionStateTable_de[507], (unsigned int)&g_weaponActionStateTable_de[891],
    (unsigned int)&g_weaponActionStateTable_de[915], (unsigned int)&g_weaponActionStateTable_de[939],
    (unsigned int)&g_weaponActionStateTable_de[963], 0x00000000, 0x0BEA0BEB, 0x0BECFFFF, 0x0BED0BEE, 0x0BEF0BF0,
    (unsigned int)&g_playerSourceEffectFinalMessage[8], (unsigned int)&g_playerSourceEffectFinalMessage[9], (unsigned int)&g_playerSourceEffectFinalMessage[10], (unsigned int)&g_playerSourceEffectFinalMessage[11], (unsigned int)&g_playerSourceEffectFinalMessage[12], (unsigned int)&g_playerSourceEffectFinalMessage[13],
    (unsigned int)&g_playerSourceEffectFinalMessage[14], (unsigned int)Gsky_FloorSurfaceNoOp, 0x40400000, 0x00000000, 0x00000000,
    (unsigned int)Gsky_FloorSurfaceNoOp,
};
#endif

/* S_STUDIOSAUSTTEXT.CPP */
#if defined(VERSION_US_REV1)
char s_studiosAustText[24] = "    ACCL\r\000M STUDIOS AUST";
#endif
