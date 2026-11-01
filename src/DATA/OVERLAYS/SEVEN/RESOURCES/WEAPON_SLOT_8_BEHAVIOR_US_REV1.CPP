#include "TYPES.H"

extern char k_ResourcesEncodedWordsBlock3[];

#include "DATA/WEAPON_SPIN_CALLBACKS/WEAPON_SPIN_AND_SIDE_YAW_CALLBACK_ADDRESSES.H"

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    void * reserved0;
    void * reserved1;
    f32 scale;
    f32 speed;
    void * states;
    void * enter;
    void * update;
} g_weaponSlot8BehaviorUsRev1 __attribute__((aligned(4))) = {
    0,
    0,
    1.0f,
    1.0f,
    (void *)&k_ResourcesEncodedWordsBlock3,
    (void *)&g_Weapon_ApplyScaledSideYawAddress,
    (void *)&g_Weaponai_DecaySpinAndActivateEffectAddress
};
typedef char g_weaponSlot8BehaviorUsRev1SizeCheck[(sizeof(g_weaponSlot8BehaviorUsRev1) == 28) ? 1 : -1];
#endif
#endif
