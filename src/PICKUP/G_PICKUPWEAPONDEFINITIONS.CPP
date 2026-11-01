#include "DATA/COMMON/G_PICKUPWEAPONDEFINITIONS.H"

#if defined(VERSION_US_REV1)
struct {
    unsigned int w0;
    unsigned short h1[6];
    unsigned int w2;
} g_pickupWeaponDefinitions[6] = {
    { 0x800D71F0, { 0x0BC4, 0x0DB6, 0x0000, 0x0000, 0x0001, 0x0064 }, (unsigned int)addrLow_Pickup_ApplyAmmoEntryVariant4 },
    { 0x800D71F4, { 0x0BC5, 0x0DB6, 0x0000, 0x0000, 0x0001, 0x0064 }, (unsigned int)addrLow_Pickup_ApplyAmmoEntryVariant4 },
    { 0x800D71F8, { 0x0BC6, 0x0DAC, 0x0000, 0x0000, 0x0000, 0x0032 }, (unsigned int)addrLow_Pickup_ApplyAmmoEntryVariant4 },
    { 0x800D71FC, { 0x0BC7, 0x0DAC, 0x0000, 0x0000, 0x0000, 0x0032 }, (unsigned int)addrLow_Pickup_ApplyAmmoEntryVariant4 },
    { 0x800D7200, { 0x0BC8, 0x0DC0, 0x0000, 0x0000, 0x0002, 0x0005 }, (unsigned int)addrLow_Pickup_ApplyAmmoEntryVariant4 },
    { 0x800D7204, { 0x0BC9, 0x0DC0, 0x0000, 0x0000, 0x0002, 0x0005 }, (unsigned int)addrLow_Pickup_ApplyAmmoEntryVariant4 },
};
#endif
