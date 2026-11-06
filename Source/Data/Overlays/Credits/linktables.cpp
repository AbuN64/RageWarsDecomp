#include "Weapon_state_tables/weapon_state_tables.h"
#include "Ai/Weapon/weapon.h"
#include "Engine/Audio/channel.h"
#include "Weapons/pitch_translation_and_spin_actions.h"
#include "Data/Ovl1_f/ovl1_f.h"
#include "Ai/ai_functions.h"
#include "types.h"
#include "include_asm.h"
#include "Data/Overlays/encoded_callback.h"
#include "Data/Overlays/Credits/linktables_addresses.h"
#include "Ai/weaponai.h"
#include "Weapons/charge_and_linked_actor_handles.h"
#include "Common/runtime_declarations.h"
/* G_WEAPONSTATECALLBACKRECORDWORDS_EU.CPP */
#if defined(VERSION_EU)
#include "Data/Ovl1_g/weapon_update_callback_addresses.h"
#include "Data/Ovl1_g/weapon_spin_feedback_callback_address.h"
struct {
    u32 words0[1021];
    char textSCHAEFGEN[12];
    u32 words2[2];
} g_weaponStateCallbackRecordWords_eu = {
    {
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000002, (unsigned int)Weapon_ReleaseLinkedActorHandles,
        (unsigned int)g_weaponai_ToggleFiringModeWithAmmoCheckEntry, 0x00000000, 0x00004E84, 0x3F800000, 0x00000000,
        0x00000000,
        0x00000003, 0x00000000, (unsigned int)g_weaponai_ToggleFiringModeWithAmmoCheckEntry, 0x00000000, 0x00004E84,
        0x3F800000, 0x00000000, 0x00000000,
        0x00000004, (unsigned int)g_weapon_EnterChargeStateWithCuesEntry,
        (unsigned int)g_weaponai_UpdateSpinAndRepeatCueEntry, 0x00000000, 0x00004EE8, 0x3F800000, 0x00000003,
        0x00000000,
        0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000002, 0x00000000, (unsigned int)g_weaponai_UpdateAnimatedFiringModeEntry, 0x00000000, 0x00004E84,
        0x3F800000, 0x00000000, 0x00000000,
        0x00000003, 0x00000000, (unsigned int)g_weaponai_UpdateAnimatedFiringModeEntry, 0x00000000, 0x00004E8E,
        0x3F800000, 0x00000000, 0x00000000,
        0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000008, ENCODED_CALLBACK_ADDRESS(Weapon_SetDelayAndRequestAlternateFireState), ENCODED_CALLBACK_ADDRESS(Weaponai_UpdateHeldFire),
        0x00000000, 0x800CABF8, 0x3F800000, 0x00000003, 0x00000000,
        0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000002, 0x00000000, (unsigned int)g_weaponai_TryEnterAmmoCostStateEntry, 0x00000000, 0x00004E84, 0x3F800000,
        0x00000000, 0x00000000,
        0x00000003, 0x00000000, (unsigned int)g_weaponai_TryEnterAmmoCostStateEntry, 0x00000000, 0x00004E84, 0x3F800000,
        0x00000000, 0x00000000,
        0x0000000B, ENCODED_CALLBACK_ADDRESS(Weapon_EmptyAlternateFireHook), ENCODED_CALLBACK_ADDRESS(Weapon_UpdateHeldAlternateFire),
        0x00000000, 0x00004EE8, 0x3F800000, 0x00000000, 0x00000000,
        0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000002, 0x00000000, (unsigned int)g_weaponTryRequestAlternateFireEntry, 0x00000000, 0x00004E84,
        0x3F800000, 0x00000000, 0x00000000,
        0x00000003, 0x00000000, (unsigned int)g_weaponTryRequestAlternateFireEntry, 0x00000000, 0x00004E84,
        0x3F800000, 0x00000000, 0x00000000,
        0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000002, 0x00000000, (unsigned int)g_weapon_UpdateSpecialFireAndAmmoEntry, 0x00000000, 0x00004E84,
        0x3F800000, 0x00000000, 0x00000000,
        0x00000003, 0x00000000, (unsigned int)g_weapon_UpdateSpecialFireAndAmmoEntry, 0x00000000, 0x00004E8E,
        0x3F800000, 0x00000000, 0x00000000,
        0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000002, (unsigned int)Weapon_ReleaseLinkedActorHandles,
        (unsigned int)g_weaponai_TryEnterAlternateAmmoModeEntry, 0x00000000, 0x00004E84, 0x3F800000, 0x00000000,
        0x00000000,
        0x00000003, 0x00000000, (unsigned int)g_weaponai_TryEnterAlternateAmmoModeEntry, 0x00000000, 0x00004E8E,
        0x3F800000, 0x00000000, 0x00000000,
        0x00000005, 0x00000000, (unsigned int)g_weapon_RequestReleaseOnEnabledEventEntry, 0x00000000, 0x00004EE8,
        0x3F800000, 0x00000003, 0x00000000,
        0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[200], 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,
        0x00000005, (unsigned int)g_weapon_PlayAlternateTriggerStartupCueEntry,
        (unsigned int)g_weapon_UpdateAlternateTriggerCompletionEntry, 0x00000000, 0x00004EE8, 0x3F800000, 0x00000003,
        0x00000000,
        0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x41F00000, (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000000, 0x00000002, 0x00000000, (unsigned int)g_weaponai_TryEnterChargedAlternateModeEntry, 0x00000000,
        0x00004E84, 0x3F800000, 0x00000000,
        0x00000000, 0x00000003, 0x00000000, (unsigned int)g_weaponai_TryEnterChargedAlternateModeEntry, 0x00000000,
        0x00004E8E, 0x3F800000, 0x00000000,
        0x00000000, 0x00000005, 0x00000000, (unsigned int)g_weapon_ApproachSpinPhaseAndReleaseEntry, 0x00000000,
        0x00004E84, 0x3F800000, 0x00000003,
        0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000000, 0x00000002, 0x00000000, (unsigned int)g_weaponai_UpdateForceMarkerTriggerEntry, 0x00000000,
        0x00004E84, 0x3F800000, 0x00000000,
        0x00000000, 0x00000003, 0x00000000, (unsigned int)g_weaponai_UpdateForceMarkerTriggerEntry, 0x00000000,
        0x00004E8E, 0x3F800000, 0x00000000,
        0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, ENCODED_CALLBACK_ADDRESS(Weapon_InitializeFireStateCallbacks), 0x00000000, 0x00010064, 0x0414000A,
        0x00010064, 0x042D0014, 0x00010064,
        0x03E8000A, 0x00010064, 0x03EB0019, 0x000000C8, 0x03F10001, 0x000000C8, 0x04310019, 0x000000C8,
        0x00070001, 0x000000C8, 0x0439000C, 0x000000C8, 0x04330001, 0x000000C8, 0x04370001, 0x000000C8,
        0x03F90002, 0x00010064, 0x03F5000A, 0x00010064, 0x04160005, 0x00010064, 0x04050003, 0x00010064,
        0x041B0032, 0x00010064, 0x0401000A, 0x00010064, 0x04030032, 0x0002004B, 0x03F70001, 0x0002004B,
        0x04250001, 0x0002004B, 0x03EC0001, 0x0002004B, 0x03EF0001, 0x00010064, 0x03FB000A, 0x00010064,
        0x03FE0064, 0x00010064, 0x0408000A, 0x00010064, 0x04320032, 0x00010064, 0x03FF0005, 0x00010064,
        0x04190032, 0x00030014, 0x01290001, 0x00040014, 0x040A0001, 0x00050001, 0x040C0001, 0x00060014,
        0x040E0001, 0x00010064, 0x04B0000A, 0x00010064, 0x04B10019, 0x000000C8, 0x04BB0001, 0x000000C8,
        0x04BC0019, 0x000000C8, 0x00070001, 0x000000C8, 0x04C4000C, 0x000000C8, 0x04C10001, 0x000000C8,
        0x04C20001, 0x000000C8, 0x04CB0002, 0x00010064, 0x04C5000A, 0x00010064, 0x04160005, 0x00010064,
        0x04DA0003, 0x00010064, 0x04DD0032, 0x00010064, 0x0401000A, 0x00010064, 0x04030032, 0x0002004B,
        0x04C90001, 0x0002004B, 0x04CA0001, 0x0002004B, 0x04B40001, 0x0002004B, 0x03EF0001, 0x00010064,
        0x04CD000A, 0x00010064, 0x04D00064, 0x00010064, 0x04E0000A, 0x00010064, 0x04E30032, 0x00010064,
        0x04D10005, 0x00010064, 0x04D30032, 0x00030014, 0x01290001, 0x00040014, 0x040A0001, 0x00050001,
        0x040C0001, 0x00060014, 0x040E0001, (unsigned int)&g_weaponLockedNoticeTextEu[4], 0x04C30BB8, 0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
        0x00000003, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[240], 0x00000000,
        (unsigned int)g_weapon_EaseSpinAndUpdateFeedbackEntry, (unsigned int)&g_weaponLockedNoticeTextEu[8], 0x04D3FFFF, 0x0000FFFF, 0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[12], 0x04D4FFFF, 0x0000FFFF,
        0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[16], 0x04C40BB9, 0x0000FFFF,
        0xFFFF02F8, 0x02F90000,
        0x00000003, 0x00000000, 0x3F5F66F4, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[339],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[341], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[339],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[341],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[40], 0x00000000,
        ENCODED_CALLBACK_ADDRESS(Weapon_EmptyChargeStateHook), (unsigned int)&g_weaponLockedNoticeTextEu[20], 0x04C50BBA, 0x0C83FFFF, 0xFFFF02DA, 0x02DA0000,
        0x00000023, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[343],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[345], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[401],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[403],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[24], 0x04C60BBB, 0x0000FFFF,
        0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x3F860A93, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[347],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[349], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[405],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[407],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[96], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[28], 0x04C70BBC,
        0x0000FFFF, 0xFFFF02DA, 0x02DA0000,
        0x00000007, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[351],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[353], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[409],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[411],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[200], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[32], 0x04C80BBD,
        0x0000FFFF, 0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[355],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[357], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[413],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[415],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[36], 0x04C90BBE, 0x0000FFFF,
        0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[359], 0x00000000,
        0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[417], 0x00000000,
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)k_weaponFireStateTable, (unsigned int)g_weapon_ApplyScaledSideYawEntry,
        (unsigned int)Weaponai_DecaySpinAndActivateEffect, (unsigned int)&g_weaponLockedNoticeTextEu[40], 0x04CA0BBF, 0x0C83FFFF, 0xFFFF02DA, 0x02DA0000,
        0x00000027, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[361],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[363], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[419],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[421],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[44], 0x04CB0BC0, 0x0000FFFF,
        0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[365],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[367], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[423],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[425],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[48], 0x04CC0BC1, 0x0000FFFF,
        0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[369],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[371], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[427],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[429],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[72], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[52], 0x04CD0BC2,
        0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[373],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[375], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[431],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[433],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[136], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[56], 0x04CE0BC3,
        0x0000FFFF, 0xFFFF02DA, 0x02DA0000,
        0x00000007, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[377], 0x00000000,
        0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[435], 0x00000000,
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[305], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[60], 0x04CF0BC4,
        0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[379], 0x00000000,
        0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[437], 0x00000000,
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[168], 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[64], 0x04D00BC5,
        0x0000FFFF, 0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[381],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[383], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[439],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[441],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu, (unsigned int)g_weapon_ApplySideDependentYawEntry,
        (unsigned int)g_weaponSettleSpinToAnimationSectorEntry, (unsigned int)&g_weaponLockedNoticeTextEu[68], 0x04D10BC6, 0x0000FFFF, 0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[385],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[387], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[443],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[445],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable.entries[8], 0x00000000, (unsigned int)g_weapon_EaseSpinAndUpdateFeedbackEntry, (unsigned int)&g_weaponLockedNoticeTextEu[72], 0x04D20BC7, 0x0000FFFF,
        0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[389],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[391], 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[447],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[449],
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[265],
        (unsigned int)g_weaponTranslatePitchEffectEventEntry, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[76], 0x04D50BC8, 0x0000FFFF,
        0xFFFF02C6, 0x02C70000,
        0x00000003, 0x40800000, 0x3F490FDC, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[393], 0x00000000,
        0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[451], 0x00000000,
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[80], 0x04D60BC9, 0x0000FFFF,
        0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[453], 0x00000000,
        0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[395], 0x00000000,
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[84], 0x04D70BCA, 0x0000FFFF,
        0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[399], 0x00000000,
        0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[457], 0x00000000,
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)&g_weaponLockedNoticeTextEu[92], 0x04D90BCC, 0x0000FFFF,
        0xFFFF02DA, 0x02DA0000,
        0x00000003, 0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[397], 0x00000000,
        0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[455], 0x00000000,
        0x00000000, 0x40C00000, 0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
        (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000,
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[459],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[531],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[555],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[579],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[603],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[627],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[651],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[675],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[699],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[723],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[747],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[771],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[795],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[819],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[843],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[867],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[483],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[507],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[891],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[915],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[939],
        (unsigned int)&g_weaponStateCallbackRecordWords_eu.words0[963], 0x00000000, 0x0BEA0BEB, 0x0BECFFFF, 0x0BED0BEE,
        0x0BEF0BF0, (unsigned int)&g_playerSourceEffectFinalMessageEuropean[32], (unsigned int)&g_playerSourceEffectFinalMessageEuropean[36],
        (unsigned int)&g_playerSourceEffectFinalMessageEuropean[40], (unsigned int)&g_playerSourceEffectFinalMessageEuropean[44], (unsigned int)&g_playerSourceEffectFinalMessageEuropean[48], (unsigned int)&g_playerSourceEffectFinalMessageEuropean[52], (unsigned int)&g_playerSourceEffectFinalMessageEuropean[56], 0x20534348, 0x41454647, 0x454E202D,
    },
    " SCHAEFGEN -",
    {
        0x00000000, (unsigned int)g_linktablesTrailingTargetAddress,
    },
};
#endif

/* PLAYERAI_INITIALIZEPLAYERHEALTH_DATA.CPP */
#if defined(VERSION_EU_X)
extern struct {
    f32 targetFacingEaseRate;
    f32 reactionReserveApproachRate;
    s16 disabledAimAnimation[4];
    f32 aimScale;
    s16 weaponAnimationDurationPairs[30];
    s32 handMirrorAxesAndFlags[5];
    f32 weaponRestOffset;
    void * nextTable;
    u32 stateTableHeaderReserved[7];
    s32 state0Id;
    void * state0Enter;
    void * state0Update;
    u32 state0Reserved;
    s32 state0Animation;
    f32 state0Rate;
    s32 state0Threshold;
    u32 state0Flags;
    s32 state1Id;
    void * state1Enter;
    void * state1Update;
    u32 state1Reserved;
    s32 state1Animation;
    f32 state1Rate;
    s32 state1Threshold;
    u32 state1Flags;
    s32 state2Id;
    void * state2Enter;
    void * state2Update;
    u32 state2Reserved;
    s32 state2Animation;
    f32 state2Rate;
    s32 state2Threshold;
    u32 state2Flags;
    s32 state3Id;
    void * state3Enter;
    void * state3Update;
    u32 state3Reserved;
    s32 state3Animation;
    f32 state3Rate;
    s32 state3Threshold;
    u32 state3Flags;
    s32 state4Id;
    void * state4Enter;
    void * state4Update;
    u32 state4Reserved;
    void * state4AnimationList;
    f32 state4Rate;
    s32 state4Threshold;
    u32 state4Flags;
    s32 state5Id;
    void * state5Enter;
    void * state5Update;
    u32 state5Reserved;
    void * state5AnimationList;
    f32 state5Rate;
    s32 state5Threshold;
    u32 state5Flags;
    s32 state6Id;
    void * state6Enter;
    void * state6Update;
    u32 state6Reserved;
    s32 state6Animation;
    f32 state6Rate;
    s32 state6Threshold;
    u32 state6Flags;
    s32 state7Id;
    void * state7Enter;
    void * state7Update;
    u32 state7Reserved;
    s32 state7Animation;
    f32 state7Rate;
    s32 state7Threshold;
    u32 state7Flags;
    void * table8Next;
    u32 table8HeaderReserved[7];
    s32 state9Id;
    void * state9Enter;
    void * state9Update;
    u32 state9Reserved;
    s32 state9Animation;
    f32 state9Rate;
    s32 state9Threshold;
    u32 state9Flags;
    s32 state10Id;
    void * state10Enter;
    void * state10Update;
    u32 state10Reserved;
    s32 state10Animation;
    f32 state10Rate;
    s32 state10Threshold;
    u32 state10Flags;
    s32 state11Id;
    void * state11Enter;
    void * state11Update;
    u32 state11Reserved;
    s32 state11Animation;
    f32 state11Rate;
    s32 state11Threshold;
    u32 state11Flags;
    s32 state12Id;
    void * state12Enter;
    void * state12Update;
    u32 state12Reserved;
    s32 state12Animation;
    f32 state12Rate;
    s32 state12Threshold;
    u32 state12Flags;
    void * table13Next;
    u32 table13HeaderReserved[7];
    s32 state14Id;
    void * state14Enter;
    void * state14Update;
    u32 state14Reserved;
    s32 state14Animation;
    f32 state14Rate;
    s32 state14Threshold;
    u32 state14Flags;
    s32 state15Id;
    void * state15Enter;
    void * state15Update;
    u32 state15Reserved;
    s32 state15Animation;
    f32 state15Rate;
    s32 state15Threshold;
    u32 state15Flags;
    s32 state16Id;
    void * state16Enter;
    void * state16Update;
    u32 state16Reserved;
    s32 state16Animation;
    f32 state16Rate;
    s32 state16Threshold;
    u32 state16Flags;
    s32 state17Id;
    void * state17Enter;
    void * state17Update;
    u32 state17Reserved;
    s32 state17Animation;
    f32 state17Rate;
    s32 state17Threshold;
    u32 state17Flags;
    s32 state18Id;
    void * state18Enter;
    void * state18Update;
    u32 state18Reserved;
    s32 state18Animation;
    f32 state18Rate;
    s32 state18Threshold;
    u32 state18Flags;
} k_playeraiHealthStateRecords __attribute__((aligned(4)));
typedef char k_playeraiHealthStateRecordsSizeCheck[
    (sizeof(k_playeraiHealthStateRecords) == 744) ? 1 : -1];
#endif

/* G_WEAPONSTATECALLBACKRECORDWORDS_EU_X.CPP */
#if defined(VERSION_EU_X)
#include "Data/Ovl1_g/weapon_update_callback_addresses.h"
#include "Data/Ovl1_g/weapon_spin_feedback_callback_address.h"
u32 g_weaponStateCallbackRecordWords_eu_x[1026] = {
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000002, ENCODED_CALLBACK_ADDRESS(Weapon_ReleaseLinkedActorHandles),
    (unsigned int)g_weaponai_ToggleFiringModeWithAmmoCheckEntry, 0x00000000,
    0x00004E84, 0x3F800000, 0x00000000, 0x00000000, 0x00000003, 0x00000000,
    (unsigned int)g_weaponai_ToggleFiringModeWithAmmoCheckEntry, 0x00000000, 0x00004E84, 0x3F800000, 0x00000000,
    0x00000000,
    0x00000004, (unsigned int)g_weapon_EnterChargeStateWithCuesEntry,
    (unsigned int)g_weaponai_UpdateSpinAndRepeatCueEntry, 0x00000000, 0x00004EE8, 0x3F800000,
    0x00000003, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000002, 0x00000000, (unsigned int)g_weaponai_UpdateAnimatedFiringModeEntry, 0x00000000, 0x00004E84, 0x3F800000,
    0x00000000, 0x00000000, 0x00000003, 0x00000000, (unsigned int)g_weaponai_UpdateAnimatedFiringModeEntry, 0x00000000,
    0x00004E8E, 0x3F800000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000008, ENCODED_CALLBACK_ADDRESS(Weapon_SetDelayAndRequestAlternateFireState),
    (unsigned int)g_weaponai_UpdateHeldFireEntry, 0x00000000,
    0x800CB5C8, 0x3F800000, 0x00000003, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000002, 0x00000000, (unsigned int)g_weaponai_TryEnterAmmoCostStateEntry, 0x00000000,
    0x00004E84, 0x3F800000, 0x00000000, 0x00000000, 0x00000003, 0x00000000,
    (unsigned int)g_weaponai_TryEnterAmmoCostStateEntry, 0x00000000, 0x00004E84, 0x3F800000, 0x00000000, 0x00000000,
    0x0000000B, ENCODED_CALLBACK_ADDRESS(Weapon_EmptyAlternateFireHook),
    (unsigned int)g_weapon_UpdateHeldAlternateFireEntry, 0x00000000, 0x00004EE8, 0x3F800000,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000002, 0x00000000, (unsigned int)g_weaponTryRequestAlternateFireEntry, 0x00000000, 0x00004E84,
    0x3F800000,
    0x00000000, 0x00000000, 0x00000003, 0x00000000, (unsigned int)g_weaponTryRequestAlternateFireEntry,
    0x00000000,
    0x00004E84, 0x3F800000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000002, 0x00000000, (unsigned int)g_weapon_UpdateSpecialFireAndAmmoEntry, 0x00000000,
    0x00004E84, 0x3F800000, 0x00000000, 0x00000000, 0x00000003, 0x00000000,
    (unsigned int)g_weapon_UpdateSpecialFireAndAmmoEntry, 0x00000000, 0x00004E8E, 0x3F800000, 0x00000000, 0x00000000,
    0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002,
    ENCODED_CALLBACK_ADDRESS(Weapon_ReleaseLinkedActorHandles),
    (unsigned int)g_weaponai_TryEnterAlternateAmmoModeEntry, 0x00000000, 0x00004E84, 0x3F800000, 0x00000000, 0x00000000,
    0x00000003, 0x00000000, (unsigned int)g_weaponai_TryEnterAlternateAmmoModeEntry, 0x00000000, 0x00004E8E, 0x3F800000,
    0x00000000, 0x00000000, 0x00000005, 0x00000000, (unsigned int)g_weapon_RequestReleaseOnEnabledEventEntry,
    0x00000000,
    0x00004EE8, 0x3F800000, 0x00000003, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[200], 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000,
    0x00000000, 0x00000000, 0x00000005, (unsigned int)g_weapon_PlayAlternateTriggerStartupCueEntry,
    (unsigned int)g_weapon_UpdateAlternateTriggerCompletionEntry, 0x00000000,
    0x00004EE8, 0x3F800000, 0x00000003, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x41F00000, (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x00000000,
    (unsigned int)g_weaponai_TryEnterChargedAlternateModeEntry,
    0x00000000, 0x00004E84, 0x3F800000, 0x00000000, 0x00000000, 0x00000003,
    0x00000000, (unsigned int)g_weaponai_TryEnterChargedAlternateModeEntry, 0x00000000, 0x00004E8E, 0x3F800000,
    0x00000000,
    0x00000000, 0x00000005, 0x00000000, (unsigned int)g_weapon_ApproachSpinPhaseAndReleaseEntry, 0x00000000, 0x00004E84,
    0x3F800000, 0x00000003, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)&g_weaponFireStateCallbackTable,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000002, 0x00000000, (unsigned int)g_weaponai_UpdateForceMarkerTriggerEntry, 0x00000000, 0x00004E84,
    0x3F800000, 0x00000000, 0x00000000, 0x00000003, 0x00000000, (unsigned int)g_weaponai_UpdateForceMarkerTriggerEntry,
    0x00000000, 0x00004E8E, 0x3F800000, 0x00000000, 0x00000000, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, (unsigned int)g_weapon_InitializeFireStateCallbacksEntry, 0x00000000, 0x00010064, 0x0414000A,
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
    0x040C0001, 0x00060014, 0x040E0001, (unsigned int)g_weaponLockedNoticeTextEuX + 0xC, 0x04C30BB8, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFF0000, 0x00000003, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[240], 0x00000000,
    (unsigned int)g_weapon_EaseSpinAndUpdateFeedbackEntry, (unsigned int)g_weaponLockedNoticeTextEuX + 0x18, 0x04D3FFFF, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0x24, 0x04D4FFFF, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0x30, 0x04C40BB9, 0x0000FFFF,
    0xFFFF02F8, 0x02F90000, 0x00000003, 0x00000000, 0x3F5F66F4,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[339],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[341], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[339],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[341], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[40], 0x00000000, ENCODED_CALLBACK_ADDRESS(Weapon_EmptyChargeStateHook),
    (unsigned int)g_weaponLockedNoticeTextEuX + 0x3C, 0x04C50BBA, 0x0C83FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000023, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[343],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[345], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[401],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[403], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0x48, 0x04C60BBB, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x3F860A93,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[347],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[349], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[405],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[407], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[96], 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0x54, 0x04C70BBC,
    0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000007, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[351],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[353], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[409],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[411], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[200], 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0x60, 0x04C80BBD,
    0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[355],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[357], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[413],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[415], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0x6C, 0x04C90BBE, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[359],
    0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[417], 0x00000000, 0x00000000,
    0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)k_weaponFireStateTable, (unsigned int)g_weapon_ApplyScaledSideYawEntry,
    (unsigned int)g_weaponai_DecaySpinAndActivateEffectEntry, (unsigned int)g_weaponLockedNoticeTextEuX + 0x78, 0x04CA0BBF, 0x0C83FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000027, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[361],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[363], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[419],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[421], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0x84, 0x04CB0BC0, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[365],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[367], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[423],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[425], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0x90, 0x04CC0BC1, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[369],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[371], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[427],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[429], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[72], 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0x9C, 0x04CD0BC2,
    0x0000FFFF,
    0xFFFFFFFF, 0xFFFF0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[373],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[375], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[431],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[433], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[136], 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0xA8, 0x04CE0BC3,
    0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000007, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[377],
    0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[435], 0x00000000, 0x00000000,
    0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[305], 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0xB4,
    0x04CF0BC4, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFF0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[379],
    0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[437], 0x00000000, 0x00000000,
    0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[168], 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0xC0, 0x04D00BC5,
    0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[381],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[383], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[439],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[441], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)g_weaponStateCallbackRecordWords_eu_x, (unsigned int)g_weapon_ApplySideDependentYawEntry,
    (unsigned int)g_weaponSettleSpinToAnimationSectorEntry, (unsigned int)g_weaponLockedNoticeTextEuX + 0xCC, 0x04D10BC6, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[385],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[387], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[443],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[445], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable.entries[8], 0x00000000, (unsigned int)g_weapon_EaseSpinAndUpdateFeedbackEntry, (unsigned int)g_weaponLockedNoticeTextEuX + 0xD8, 0x04D20BC7, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[389],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[391], 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[447],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[449], 0x00000000, 0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[265], (unsigned int)g_weaponTranslatePitchEffectEventEntry,
    0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0xE4, 0x04D50BC8, 0x0000FFFF,
    0xFFFF02C6, 0x02C70000, 0x00000003, 0x40800000, 0x3F490FDC,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[393],
    0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[451], 0x00000000, 0x00000000,
    0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0xF0, 0x04D60BC9, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[453],
    0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[395], 0x00000000, 0x00000000,
    0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0xFC, 0x04D70BCA, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[399],
    0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[457], 0x00000000, 0x00000000,
    0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000, (unsigned int)g_weaponLockedNoticeTextEuX + 0x114, 0x04D90BCC, 0x0000FFFF,
    0xFFFF02DA, 0x02DA0000, 0x00000003, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[397],
    0x00000000, 0x00000000, (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[455], 0x00000000, 0x00000000,
    0x40C00000,
    0x40E00000, 0x41200000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000,
    (unsigned int)&g_weaponFireStateCallbackTable, 0x00000000, 0x00000000,
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[459],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[531],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[555],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[579],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[603],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[627],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[651],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[675],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[699],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[723],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[747],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[771],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[795],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[819],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[843],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[867],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[483],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[507],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[891],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[915],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[939],
    (unsigned int)&g_weaponStateCallbackRecordWords_eu_x[963], 0x00000000, 0x0BEA0BEB, 0x0BECFFFF, 0x0BED0BEE,
    0x0BEF0BF0,
    (unsigned int)&g_playerSourceEffectFinalMessageEuropean[24], (unsigned int)&g_playerSourceEffectFinalMessageEuropean[27], (unsigned int)&g_playerSourceEffectFinalMessageEuropean[30], (unsigned int)&g_playerSourceEffectFinalMessageEuropean[33], (unsigned int)&g_playerSourceEffectFinalMessageEuropean[36], (unsigned int)&g_playerSourceEffectFinalMessageEuropean[39],
    (unsigned int)&g_playerSourceEffectFinalMessageEuropean[42], 0x00000001, 0x00000001, 0x00000001, 0x00000000,
    ENCODED_CALLBACK_ADDRESS(Gsky_FloorSurfaceNoOp),
};
#endif

/* S_JUSTINTEXT.CPP */
#if defined(VERSION_US_REV1)
extern char s_justinText[8];
#endif

/* S_COONERTEXT.CPP */
#if defined(VERSION_US_REV1)
char s_coonerText[8] = "E COONER";
#endif

/* LIBULTRA_SENDDEBUGLINKIDENTIFICATION_DATA.CPP */
#if defined(VERSION_US_REV1)
/* "N64 V1.00" and its terminator: text, so bytes. */
const char g_debugLinkIdentificationText[10] =
    "N64 V1.00";
#endif

/* G_TECHNICIANSCREDITSTEXT.CPP */
#if defined(VERSION_US_REV1)
char g_techniciansCreditsText[12] = "TECHNICIANS";
#endif

/* G_TURNOVERCREDITSTEXTPOOL.CPP */
#if defined(VERSION_US_REV1)
char g_turnoverCreditsTextPool[576] = "ANTHONY GENTILE\000TURNOVER TECHNICIAN\000CHRIS MAHER\000TURNOVER COORDINATOR\000\000\000\000MAX IMAS\000\000\000\000LLOYD THOMPSON\000\000MARK BERKOWITZ\000\000JAY CAPOZELLO\000\000\000DJ PELUSO\000\000\000PAUL JOHNSON\000\000\000\000JOE CARBONE\000MAURICE PHILIPS\000SCOTT SNOPOWSKI\000LUC ANGRAND II\000\000BRHETT HOHWALD\000\000DAN BADILLA\000JOSHUA ROGERS\000\000\000PAUL DICARLO\000\000\000\000JON NICOLAI\000CHRIS RAPPO\000PROJECT LEADS\000\000\000MATT CANONICO\000\000\000MARK GARONE\000LEAD ANALYSTS\000\000\000MIKE PATTERSON\000\000BRIAN REGAN\000SENIOR LEAD ANALYST\000JEFF ROSA\000\000\000DALE TAYLOR\000QA SUPERVISOR\000\000\000CAROL CARACCIOLO\000\000\000\000BILL DICKSON\000\000\000\000MANUAL SUPPORT MANAGER\000\000NICOLE RUISI\000\000\000\000KATHLEEN BYRNE\000\000PROJECT TRACKING\000\000\000\000JAMES DALY";
#endif

/* S_PRODUCERTEXT.CPP */
#if defined(VERSION_US_REV1)
char s_producerText[12] __attribute__((aligned(1))) = "PRODUCER\000\000\000\000";
#endif

/* PUBLISHER_AND_VOICE_CREDITS_TEXT.CPP */
#if defined(VERSION_US_REV1)
char g_productDevelopmentCreditsTextPool[1052] = "                  NY PRODUCT DEVELOPMENT\000\000\000\000                ACCLAIM ENTERTAINMENT INC.\000\000                           PUBLISHER CREDITS\000\000\000\000DARREN STUBBINGTON\000\000EXECUTIVE VP OF ACCLAIM STUDIOS\000CRAIG GALLEY\000\000\000\000VP OF TECHNOLOGY\000\000\000\000CYRUS LUM\000\000\000VP OF DIGITAL PRODUCTIONS\000\000\000NIGEL COOK\000\000VP OF PRODUCT DEVELOPMENT AND DESIGN\000\000\000\000                       GLOBAL DIRECTORS\000ALAN JOHNSON\000\000\000\000DIRECTOR OF DIGITAL PRODUCTIONS\000AUDIO MANAGER\000\000\000CREATIVE DIRECTOR\000\000\000MALCOLM CRUMMACK\000\000\000\000DIRECTOR OF PRODUCT DEVELOPMENT\000STEVEN BROUMLEY\000TECHNICAL DIRECTOR\000\000RUSSELL BYRD\000\000\000\000GM OF ACCLAIM STUDIOS AUSTIN\000\000\000\000        ACCLAIM STUDIOS AUSTIN DIRECTORS\000\000\000\000MARC SCHAEFGEN - LORD OF THE DEAD\000\000\000TITOS MENCHACA - TAL SET\000\000\000\000DOUG FORREST - BASTILLE\000JOSE BROWN - OBLIVION / GUARDIAN\000\000\000\000DAVID DIENSTBIER - CAMPAIGNER\000\000\000DAVID KRAUSE - FIREBORN / DINOSOIDS\000JESSICA ROBERTSON - SYRA\000\000\000\000TODD LOWE - PURLIN\000\000BERNADETTE NASON - ADON\000TRAVIS DAVIS - TUROK\000\000\000\000                       CHARACTER VOICES\000JUSTIN WITHERS\000\000SHANE TATE\000\000JIM STRONG\000\000BRANDON ROWLETT\000MARK RICHARDS\000\000\000CHRIS KENDALL\000\000\000JERREMY ARNSTON";
#endif
