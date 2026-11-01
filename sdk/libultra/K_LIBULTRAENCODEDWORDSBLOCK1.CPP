#include "../include/libultra/TURRET_STATE_CALLBACK_ADDRESSES.h"

#if defined(VERSION_US_REV1)
unsigned int k_LibultraEncodedWordsBlock1[15] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)Turret_Construct_Address,
    (unsigned int)Turret_Setup_Address, 0x00000000, 0x00000000, (unsigned int)Turret_LinkEffect_Activate_Address, 0x00000000, (unsigned int)Turret_LinkEffect_MakeVisible_Address, 0x00000000,
};
#endif
