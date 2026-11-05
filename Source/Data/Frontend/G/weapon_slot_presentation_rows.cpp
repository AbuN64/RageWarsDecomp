#include "Ammo/ammo.h"
#include "Weapon_state_tables/weapon_state_tables.h"
#include "Data/rest_source_records.h"
#include "Common/runtime_declarations.h"
#include "include_asm.h"
#include "Common/Lone/weapon_locked_notice_text.h"
#include "Frontend/frontend_data_address_symbols.h"
#include "Data/Ovl1_g/weapon_update_callback_addresses.h"
#include "Data/Ovl1_g/weapon_spin_feedback_callback_address.h"

#if defined(VERSION_US_REV1)
struct WeaponSlotPresentationRow g_weaponSlotPresentationRows[8] __attribute__((aligned(8))) = {
    /* slots 11-12 */
    {
        { 0, g_weaponAmmoRequirementPairs[22], g_weaponAmmoRequirementPairs[24], 0, g_weaponAmmoRequirementPairs[80], g_weaponAmmoRequirementPairs[82], 0 },
        { 6.0f, 7.0f, 10.0f },
        { { 0, 0 }, { 1.0f, 1.0f }, { (void *)&g_weaponFireStateCallbackTable, 0, 0 } },
        { ((unsigned int)&g_weaponLockedNoticeText[11]), { 0x04CB, 0x0BC0 } },
        { 0x0000, 0xFFFF },
        { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
        0x00000000,
    },
    /* slots 13-14 */
    {
        { 0, g_weaponAmmoRequirementPairs[26], g_weaponAmmoRequirementPairs[28], 0, g_weaponAmmoRequirementPairs[84], g_weaponAmmoRequirementPairs[86], 0 },
        { 6.0f, 7.0f, 10.0f },
        { { 0, 0 }, { 1.0f, 1.0f }, { (void *)&g_weaponFireStateCallbackTable, 0, 0 } },
        { ((unsigned int)&g_weaponLockedNoticeText[12]), { 0x04CC, 0x0BC1 } },
        { 0x0000, 0xFFFF },
        { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
        0x00000000,
    },
    /* slots 15-16 */
    {
        { 0, g_weaponAmmoRequirementPairs[30], g_weaponAmmoRequirementPairs[32], 0, g_weaponAmmoRequirementPairs[88], g_weaponAmmoRequirementPairs[90], 0 },
        { 6.0f, 7.0f, 10.0f },
        { { 0, 0 }, { 1.0f, 1.0f }, { (void *)(&g_weaponChargeSpinTarget + 73), 0, 0 } },
        { ((unsigned int)&g_weaponLockedNoticeText[13]), { 0x04CD, 0x0BC2 } },
        { 0x0000, 0xFFFF },
        { { 0xFFFF, 0xFFFF, 0xFFFF, 0x0000 }, 0x00000003 },
        0x00000000,
    },
    /* slots 17-18 */
    {
        { 0, g_weaponAmmoRequirementPairs[34], g_weaponAmmoRequirementPairs[36], 0, g_weaponAmmoRequirementPairs[92], g_weaponAmmoRequirementPairs[94], 0 },
        { 6.0f, 7.0f, 10.0f },
        { { 0, 0 }, { 1.0f, 1.0f }, { (void *)(&g_weaponChargeSpinTarget + 137), 0, 0 } },
        { ((unsigned int)&g_weaponLockedNoticeText[14]), { 0x04CE, 0x0BC3 } },
        { 0x0000, 0xFFFF },
        { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000007 },
        0x00000000,
    },
    /* slot 19 */
    {
        { 0, g_weaponAmmoRequirementPairs[38], 0, 0, g_weaponAmmoRequirementPairs[96], 0, 0 },
        { 6.0f, 7.0f, 10.0f },
        { { 0, 0 }, { 1.0f, 1.0f }, { (void *)&g_weaponStateScripts.forceMarkerFireState[7], 0, 0 } },
        { ((unsigned int)&g_weaponLockedNoticeText[15]), { 0x04CF, 0x0BC4 } },
        { 0x0000, 0xFFFF },
        { { 0xFFFF, 0xFFFF, 0xFFFF, 0x0000 }, 0x00000003 },
        0x00000000,
    },
    /* slot 20 */
    {
        { 0, g_weaponAmmoRequirementPairs[40], 0, 0, g_weaponAmmoRequirementPairs[98], 0, 0 },
        { 6.0f, 7.0f, 10.0f },
        { { 0, 0 }, { 1.0f, 1.0f }, { (void *)(&g_weaponChargeSpinTarget + 169), 0, 0 } },
        { ((unsigned int)&g_weaponLockedNoticeText[16]), { 0x04D0, 0x0BC5 } },
        { 0x0000, 0xFFFF },
        { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
        0x00000000,
    },
    /* slots 21-22 */
    {
        { 0, g_weaponAmmoRequirementPairs[42], g_weaponAmmoRequirementPairs[44], 0, g_weaponAmmoRequirementPairs[100], g_weaponAmmoRequirementPairs[102], 0 },
        { 6.0f, 7.0f, 10.0f },
        { { 0, 0 }, { 1.0f, 1.0f }, { (void *)(&g_weaponChargeSpinTarget + 1), (void *)&g_weapon_ApplySideDependentYawEntry, (void *)&g_weaponSettleSpinToAnimationSectorEntry } },
        { ((unsigned int)&g_weaponLockedNoticeText[17]), { 0x04D1, 0x0BC6 } },
        { 0x0000, 0xFFFF },
        { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
        0x00000000,
    },
    /* slots 23-24 */
    {
        { 0, g_weaponAmmoRequirementPairs[46], g_weaponAmmoRequirementPairs[48], 0, g_weaponAmmoRequirementPairs[104], g_weaponAmmoRequirementPairs[106], 0 },
        { 6.0f, 7.0f, 10.0f },
        { { 0, 0 }, { 1.0f, 1.0f }, { (void *)&g_weaponSpinFireStateTable, 0, (void *)&g_weapon_EaseSpinAndUpdateFeedbackEntry } },
        { ((unsigned int)&g_weaponLockedNoticeText[18]), { 0x04D2, 0x0BC7 } },
        { 0x0000, 0xFFFF },
        { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 },
        0x00000000,
    },
};
#endif
