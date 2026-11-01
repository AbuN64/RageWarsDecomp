#include "TYPES.H"

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* (flag mask, sound id) pairs walked by Barrel_SpawnFlaggedEffects for the primary effect mask: bits 0-5 play sounds 1701-1706, every other bit sound 2200;
   the {0, 0} terminator is the first pair of the following table's data */
s32 g_barrelPrimaryFlagSoundTable[64] = {
    0x00000001, 1701,
    0x00000002, 1702,
    0x00000004, 1703,
    0x00000008, 1704,
    0x00000010, 1705,
    0x00000020, 1706,
    0x00000040, 2200,
    0x00000080, 2200,
    0x00000100, 2200,
    0x00000200, 2200,
    0x00000400, 2200,
    0x00000800, 2200,
    0x00001000, 2200,
    0x00002000, 2200,
    0x00004000, 2200,
    0x00008000, 2200,
    0x00010000, 2200,
    0x00020000, 2200,
    0x00040000, 2200,
    0x00080000, 2200,
    0x00100000, 2200,
    0x00200000, 2200,
    0x00400000, 2200,
    0x00800000, 2200,
    0x01000000, 2200,
    0x02000000, 2200,
    0x04000000, 2200,
    0x08000000, 2200,
    0x10000000, 2200,
    0x20000000, 2200,
    0x40000000, 2200,
    0x80000000, 2200,
};
#endif
