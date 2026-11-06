#include "Ai/Weapon/weapon.h"
#include "Ai/weaponai.h"
#include "include_asm.h"
#include "Weapons/charge_and_linked_actor_handles.h"
#include "Ai/ai_address_labels.h"
#include "Ai/weapon_fire_state_table_row.h"
#include "Common/runtime_declarations.h"
#include "Weapons/startup_cues_and_side_yaw.h"

#if defined(VERSION_US)
WeaponFireStateTableRow k_weaponFireStateTable[5] = {
    { (u32)&g_weaponFireStateCallbackTable, 0, 0, 0, 0, 0.0f, 0, 0 },
    { 2, (void *)Weapon_ReleaseLinkedActorHandles, (void *)Weapon_UpdateNormalFireAction, 0, 0x4E84, 1.0f, 0, 0 },
    { 3, 0, (void *)Weapon_UpdateNormalFireAction, 0, 0x4E84, 1.0f, 0, 0 },
    { 4, (void *)Weapon_InitializeChargeAndStartupCues, (void *)Weaponai_UpdateChargeAndRepeatCue, 0, 0x4EE8, 1.0f, 3, 0 },
    { 0xFFFFFFFF, 0, 0, 0, 0, 0.0f, 0, 0 },
};
#endif

#if defined(VERSION_EU)
WeaponFireStateTableRow k_weaponFireStateTable[5] = {
    { (u32)&g_weaponFireStateCallbackTable, 0, 0, 0, 0, 0.0f, 0, 0 },
    { 2, (void *)Weapon_ReleaseLinkedActorHandles, (void *)Weapon_UpdateNormalFireAction, 0, 0x4E84, 1.0f, 0, 0 },
    { 3, 0, (void *)Weapon_UpdateNormalFireAction, 0, 0x4E84, 1.0f, 0, 0 },
    { 4, (void *)Weapon_InitializeChargeAndStartupCues, (void *)Weaponai_UpdateChargeAndRepeatCue, 0, 0x4EE8, 1.0f, 3, 0 },
    { 0xFFFFFFFF, 0, 0, 0, 0, 0.0f, 0, 0 },
};
#endif

#if defined(VERSION_EU_X)
WeaponFireStateTableRow k_weaponFireStateTable[5] = {
    { (u32)&g_weaponFireStateCallbackTable, 0, 0, 0, 0, 0.0f, 0, 0 },
    { 2, (void *)Weapon_ReleaseLinkedActorHandles, (void *)Weapon_UpdateNormalFireAction, 0, 0x4E84, 1.0f, 0, 0 },
    { 3, 0, (void *)Weapon_UpdateNormalFireAction, 0, 0x4E84, 1.0f, 0, 0 },
    { 4, (void *)Weapon_InitializeChargeAndStartupCues, (void *)Weaponai_UpdateChargeAndRepeatCue, 0, 0x4EE8, 1.0f, 3, 0 },
    { 0xFFFFFFFF, 0, 0, 0, 0, 0.0f, 0, 0 },
};
#endif

#if defined(VERSION_DE)
WeaponFireStateTableRow k_weaponFireStateTable[5] = {
    { (u32)&g_weaponFireStateCallbackTable, 0, 0, 0, 0, 0.0f, 0, 0 },
    { 2, (void *)Weapon_ReleaseLinkedActorHandles, (void *)Weapon_UpdateNormalFireAction, 0, 0x4E84, 1.0f, 0, 0 },
    { 3, 0, (void *)Weapon_UpdateNormalFireAction, 0, 0x4E84, 1.0f, 0, 0 },
    { 4, (void *)Weapon_InitializeChargeAndStartupCues, (void *)Weaponai_UpdateChargeAndRepeatCue, 0, 0x4EE8, 1.0f, 3, 0 },
    { 0xFFFFFFFF, 0, 0, 0, 0, 0.0f, 0, 0 },
};
#endif
