#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#if defined(VERSION_EU)
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "OVLGAME/SHAREDRECAT224.H"
#endif
#if defined(VERSION_US_REV1)
/* Data separated from executable functions by the legacy split layout. */
unsigned int g_itemsHandlesessionoptionpageLinkGapWordsUsRev1[12] = { 0x00431023U, 0x3C01800EU, 0xC4202390U, 0x3C018014U, 0xE42068B0U, 0x8C84000CU, 0x3C03FBFFU, 0x8C820030U, 0x3463FFFFU, 0x00431024U, 0x03E00008U, 0xAC820030U };
#endif
#if defined(VERSION_US)
unsigned int g_itemsHandlesessionoptionpageLinkGapWords[12] = {
    0x41444745, 0x3C01800E, 0xC420D010, 0x3C018014, 0xE42007F0, 0x8C84000C, 0x3C03FBFF, 0x8C820030,
    0x3463FFFF, 0x00431024, 0x03E00008, 0xAC820030,
};
#endif
