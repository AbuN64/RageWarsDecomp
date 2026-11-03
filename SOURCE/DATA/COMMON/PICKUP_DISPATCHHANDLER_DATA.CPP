#include "DATA/COMMON/PICKUP_DISPATCHHANDLER_DATA.H"

#if defined(VERSION_US_REV1)
struct {
    unsigned int w0;
    unsigned short h1[6];
    unsigned int w2;
} g_pickupLifeDefinitionWords[2] = {
    { 0x00000000, { 0x06A9, 0x0001, 0x0000, 0x0000, 0x0001, 0x0000 }, (unsigned int)addrLow_Pickup_ApplyLifePoints },
    { 0x00000000, { 0x06AA, 0x0001, 0x0000, 0x0000, 0x000A, 0x0000 }, (unsigned int)addrLow_Pickup_ApplyLifePoints },
};
#endif
