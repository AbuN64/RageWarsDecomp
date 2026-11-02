#include "DATA/COMMON/G_PICKUPSPECIALDEFINITIONS.H"

#if defined(VERSION_US_REV1)
struct {
    unsigned int w0;
    unsigned short h1[4];
    unsigned int w2;
} g_pickupSpecialDefinitions[3] = {
    { 0x800D70D4, { 0x0BD6, 0x0E0E, 0x0000, 0x0000 }, (unsigned int)addrLow_Pickup_ApplySpecialPickupEntryVariant4 },
    { 0x800D70D8, { 0x0BD7, 0x02C6, 0x0000, 0x0000 }, (unsigned int)addrLow_Pickup_ApplySpecialPickupEntryVariant4 },
    { 0x800D70E4, { 0x0BD8, 0x0DCA, 0x0000, 0x0000 }, (unsigned int)addrLow_Pickup_ApplySpecialPickupEntryVariant4 },
};
#endif
