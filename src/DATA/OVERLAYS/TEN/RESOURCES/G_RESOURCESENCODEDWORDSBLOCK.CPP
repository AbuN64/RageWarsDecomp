#include "DATA_OVERLAY_SN_RECORDS.H"

#include "include_asm.h"
#include "TYPES.H"

#if defined(VERSION_US)
struct {
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record0;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record3;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record6;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record7;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left; struct { u8 opcode; SnLe16 symbol; } right; } expression; } record9;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left; struct { u8 opcode; SnLe16 symbol; } right; } expression; } record10;
    u8 followingRecordFragment[1];
} g_resourcesEncodedWordsBlock __attribute__((aligned(4))) = {
    { 10, 98, SN_LE16(930), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(982), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1900) } } },
    { 10, 98, SN_LE16(986), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1900) } } },
    { 10, 92, SN_LE16(992), { 2, SN_LE16(439) } },
    { 52, SN_LE16(1000), 4 },
    { 10, 92, SN_LE16(1000), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(55948) } } },
    { 52, SN_LE16(1008), 4 },
    { 10, 96, SN_LE16(1050), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1054), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1102), { 44, { 0, SN_LE32(159121) }, { 2, SN_LE16(388) } } },
    { 10, 98, SN_LE16(1106), { 44, { 0, SN_LE32(159121) }, { 2, SN_LE16(388) } } },
    { 0x0A }
};
typedef char g_resourcesEncodedWordsBlockSizeCheck[(sizeof(g_resourcesEncodedWordsBlock) == 120) ? 1 : -1];
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    u8 alignmentFill[8];
} k_ResourcesEncodedWordsBlock8 __attribute__((aligned(4))) = {
    { 0x60, 0x62, 0x04, 0x02, 0xB3, 0x01, 0x0A, 0x62 }
};
#endif
#endif
