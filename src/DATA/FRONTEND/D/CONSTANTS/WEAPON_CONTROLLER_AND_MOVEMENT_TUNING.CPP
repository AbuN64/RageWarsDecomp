#include "DATA/REST_SOURCE_RECORDS.H"
#include "DATA/OVL1_D/WEAPON_CHARGE_FIVE_CALLBACK_ADDRESS.H"

#if defined(VERSION_US_REV1)
RestweaponControllerAndMovementTuningUsRev1Layout404 g_weaponControllerAndMovementTuningUsRev1 = {
    { 0, 8 },
    (void *)&addrLow_Weapon_InitializeChargeForWeaponFive,
    { 65536, 327680, 262144, 786432, 524288, 655360, 131072, 196608 },
    { 3e+01f, 48.0f, 1.3e+02f },
};
#endif
