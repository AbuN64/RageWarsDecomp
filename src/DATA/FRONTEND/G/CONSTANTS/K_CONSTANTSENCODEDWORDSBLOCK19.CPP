#include "DATA/REST_SOURCE_RECORDS.H"
extern s32 g_weaponChargeSpinTarget;
#include "DATA/OVL1_G/WEAPON_UPDATE_CALLBACK_ADDRESSES.H"

#if defined(VERSION_US_REV1)
RestConstantsEncodedWordsBlock19Layout409 k_ConstantsEncodedWordsBlock19 = {
    { 0, 0 },
    { 1.0f, 1.0f },
    { (void *)((char *)&g_weaponChargeSpinTarget + 4), (void *)&g_weapon_ApplySideDependentYawEntry, (void *)&g_weaponai_SettleSpinToThirdTurnEntry },
};
#endif
