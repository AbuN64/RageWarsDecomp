#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_WeaponStateEndCFF98UsRev1[];
#include "DATA/OVL1_G/WEAPON_ACTION_FIVE_SPIN_ADDRESS.H"

#if defined(VERSION_US_REV1)
RestConstantsEncodedWordsBlock21Layout410 k_ConstantsEncodedWordsBlock21 = {
    { 0, 0 },
    { 1.0f, 1.0f },
    { (void *)((char *)&g_WeaponStateEndCFF98UsRev1 + 32), 0, (void *)&g_weapon_EaseSpinForActionFiveEntry },
};
#endif
