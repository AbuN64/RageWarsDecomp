#include "Gfxdata/audio_decodeframe_data.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "include_asm.h"
#include "Data/Gfxdata/audio_decodeframe_data.h"
#include "Weapon_state_tables/weapon_state_tables.h"
#include "Data/Ovl1_f/ovl1_f.h"
#include "Data/Weapon_spin_callbacks/weapon_no_operation_callback_address.h"
#include "Ammo/ammo.h"
#include "Resources/weapon_slot_behavior_words.h"
#include "Data/Weapon_spin_callbacks/weapon_spin_and_side_yaw_callback_addresses.h"
#include "Data/Overlays/Weaponslot/weapon_slot_block.h"

#if defined(VERSION_US_REV1)
WeaponSlotRecordTable g_weaponSlotRecords __attribute__((aligned(4))) = {
    /* slot 1 */
    {
        { { 0, 0 }, { 1.0f, 1.0f }, (void *)&g_weaponFireStateCallbackTable, 0, 0 },
        { (unsigned int)&g_backdropTextLines[140], { 0x04D4, 0xFFFF } },
        { 0, -1 },
        { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
    },
    {
        /* slot 2 */
        {
            {
                { { 0, 0 }, { 1.0f, 1.0f }, (void *)&g_weaponFireStateCallbackTable, 0, 0 },
                { (unsigned int)&g_backdropTextLines[144], { 0x04C4, 0x0BB9 } },
                { 0, -1 },
                { { 0xFFFF, 0x02F8, 0x02F9, 0x0000 }, 0x00000003 },
            },
            { 0.87266469f, (void *)&g_weaponAmmoRequirementPairs[0], (void *)&g_weaponAmmoRequirementPairs[2], 0, (void *)&g_weaponAmmoRequirementPairs[0], (void *)&g_weaponAmmoRequirementPairs[2], 0 },
        },
        /* slot 3 */
        {
            {
                { { 0, 0 }, { 1.0f, 1.0f }, &g_weaponSlotUpdateSpinAndRepeatCueFireStateSlots[7], 0, (void *)&g_weaponNoOperationCallbackAddress },
                { (unsigned int)&g_backdropTextLines[148], { 0x04C5, 0x0BBA } },
                { 3203, -1 },
                { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000023 },
            },
            { 0.0f, (void *)&g_weaponAmmoRequirementPairs[4], (void *)&g_weaponAmmoRequirementPairs[6], 0, (void *)&g_weaponAmmoRequirementPairs[62], (void *)&g_weaponAmmoRequirementPairs[64], 0 },
        },
        /* slot 4 */
        {
            {
                { { 0, 0 }, { 1.0f, 1.0f }, (void *)&g_weaponFireStateCallbackTable, 0, 0 },
                { (unsigned int)&g_backdropTextLines[152], { 0x04C6, 0x0BBB } },
                { 0, -1 },
                { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
            },
            { 1.0471977f, (void *)&g_weaponAmmoRequirementPairs[8], (void *)&g_weaponAmmoRequirementPairs[10], 0, (void *)&g_weaponAmmoRequirementPairs[66], (void *)&g_weaponAmmoRequirementPairs[68], 0 },
        },
        /* slot 5 */
        {
            {
                { { 0, 0 }, { 1.0f, 1.0f }, &g_weaponDelayedFireStateSlots[7], 0, 0 },
                { (unsigned int)&g_backdropTextLines[156], { 0x04C7, 0x0BBC } },
                { 0, -1 },
                { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000007 },
            },
            { 0.0f, (void *)&g_weaponAmmoRequirementPairs[12], (void *)&g_weaponAmmoRequirementPairs[14], 0, (void *)&g_weaponAmmoRequirementPairs[70], (void *)&g_weaponAmmoRequirementPairs[72], 0 },
        },
        /* slot 6 */
        {
            {
                { { 0, 0 }, { 1.0f, 1.0f }, &g_weaponStateScripts.alternateAmmoFireState[7], 0, 0 },
                { (unsigned int)&g_backdropTextLines[160], { 0x04C8, 0x0BBD } },
                { 0, -1 },
                { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
            },
            { 0.0f, (void *)&g_weaponAmmoRequirementPairs[16], (void *)&g_weaponAmmoRequirementPairs[18], 0, (void *)&g_weaponAmmoRequirementPairs[74], (void *)&g_weaponAmmoRequirementPairs[76], 0 },
        },
        /* slot 7 */
        {
            {
                { { 0, 0 }, { 1.0f, 1.0f }, (void *)&g_weaponFireStateCallbackTable, 0, 0 },
                { (unsigned int)&g_backdropTextLines[164], { 0x04C9, 0x0BBE } },
                { 0, -1 },
                { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
            },
            { 0.0f, (void *)&g_weaponAmmoRequirementPairs[20], 0, 0, (void *)&g_weaponAmmoRequirementPairs[78], 0, 0 },
        },
    },
    /* slot 8 */
    {
        { { 0, 0 }, { 1.0f, 1.0f }, (void *)&k_weaponResourceBehaviorPointers, (void *)&g_Weapon_ApplyScaledSideYawAddress, (void *)&g_Weaponai_DecaySpinAndActivateEffectAddress },
        { (unsigned int)&g_backdropTextLines[168], { 0x04CA, 0x0BBF } },
        { 3203, -1 },
        { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000027 },
    },
};
#endif
