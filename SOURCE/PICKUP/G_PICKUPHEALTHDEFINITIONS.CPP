#include "DATA/COMMON/G_PICKUPHEALTHDEFINITIONS.H"

#if defined(VERSION_US_REV1)
struct {
    unsigned int w0;
    unsigned short h1[4];
    unsigned int w2[3];
} g_pickupHealthDefinitions[8] = {
    { 0x800D7070, { 0x06A5, 0x0001, 0x0000, 0x0000 }, { 0x00000002, 0x000000C8, (unsigned int)g_Pickup_ApplyHealthAddress } },
    { 0x800D7074, { 0x06A6, 0x0001, 0x0000, 0x0000 }, { 0x0000000A, 0x00000064, (unsigned int)g_Pickup_ApplyHealthAddress } },
    { 0x800D7084, { 0x06A7, 0x0001, 0x012B, 0x0000 }, { 0x00000064, 0x00000064, (unsigned int)g_Pickup_ApplyHealthAddress } },
    { 0x800D7088, { 0x06A8, 0x0001, 0x012B, 0x0000 }, { 0x00000064, 0x000000C8, (unsigned int)g_Pickup_ApplyHealthAddress } },
    { 0x800D7074, { 0x06B8, 0x0001, 0x0000, 0x0000 }, { 0x0000000A, 0x00000064, (unsigned int)g_Pickup_ApplyHealthAddress } },
    { 0x800D7078, { 0x06B9, 0x0DE8, 0x0000, 0x0000 }, { 0x0000000F, 0x00000064, (unsigned int)g_Pickup_ApplyHealthAddress } },
    { 0x800D707C, { 0x06BA, 0x0DE8, 0x0000, 0x0000 }, { 0x00000019, 0x00000064, (unsigned int)g_Pickup_ApplyHealthAddress } },
    { 0x800D7080, { 0x06BB, 0x0DF2, 0x0000, 0x0000 }, { 0x00000032, 0x00000064, (unsigned int)g_Pickup_ApplyHealthAddress } },
};
#endif
