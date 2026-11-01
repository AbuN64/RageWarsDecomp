#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#if defined(VERSION_US_REV1)
/* g_enemyMixWordsAndLights_PakAdjustownernotificationoptionData.CPP */
/* Nine words, then the ambient light, the diffuse light and its direction as bytes (read bytewise by the RSP). */
struct {
    unsigned int words[9];
    unsigned char lights[20];
} g_enemyMixWordsAndLights = {
    { 0x00000001, 0x3F800000, 0x3F8067C9, 0x3F8041C9, 0x3F801BC1, 0x00000000, 0x3F7F9F36, 0x3F7F52FA,
      0x3F7F06B0 },
    { 0x38, 0x38, 0x38, 0x00, 0x38, 0x38, 0x38, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
      0xD6, 0x1E, 0xDC, 0x00 },
};
/* ROM-grounded data: rodata/unresolved/800D0EF4 */
s32 g_pakAdjustownernotificationoptionDataZeroWords[1] = {
    0,
};
#endif
