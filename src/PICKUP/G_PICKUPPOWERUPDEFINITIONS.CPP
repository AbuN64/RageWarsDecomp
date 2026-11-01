#include "DATA/COMMON/G_PICKUPPOWERUPDEFINITIONS.H"

#if defined(VERSION_US_REV1)
struct {
    unsigned int w0;
    unsigned short h1[6];
    unsigned int w2[2];
} g_pickupPowerupDefinitions[4] = {
    { 0x800D7134, { 0x084B, 0x0E0C, 0xFFFF, 0x0000, 0x0012, 0x0003 }, { 0x00010000, (unsigned int)Pickup_HandlePowerWeaponPickup_Address } },
    { 0x800D7138, { 0x084C, 0x0E0C, 0xFFFF, 0x0000, 0x0013, 0x0004 }, { 0x00030000, (unsigned int)Pickup_HandlePowerWeaponPickup_Address } },
    { 0x800D713C, { 0x084D, 0x0E0C, 0xFFFF, 0x0000, 0x0014, 0x0006 }, { 0x00010000, (unsigned int)Pickup_HandlePowerWeaponPickup_Address } },
    { 0x800D7144, { 0x084F, 0x0E0C, 0xFFFF, 0x0000, 0x0015, 0x0005 }, { 0x00010000, (unsigned int)Pickup_HandlePowerWeaponPickup_Address } },
};
#endif
