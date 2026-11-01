#include "DATA_OVERLAY_SN_RECORDS.H"

#include "TYPES.H"
#if defined(VERSION_US)
struct {
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record0;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record2;
    struct { u8 opcode; SnLe16 section; } record3;
    struct { u8 opcode; SnLe16 codeSize; u8 code[4]; } record4;
    struct { u8 opcode; SnLe16 section; } record5;
    struct { u8 opcode; SnLe16 codeSize; } record6;
} k_PortalAfterUpdateGroupsPatchesSixth __attribute__((aligned(1))) = {
    { 10, 96, SN_LE16(2), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1248) } } },
    { 10, 98, SN_LE16(6), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1248) } } },
    { 10, 92, SN_LE16(20), { 2, SN_LE16(431) } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(4), { 0x42, 0xC8, 0x00, 0x00 } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(12) }
};
typedef char k_PortalAfterUpdateGroupsPatchesSixthSizeCheck[(sizeof(k_PortalAfterUpdateGroupsPatchesSixth) == 49) ? 1 : -1];
#endif
