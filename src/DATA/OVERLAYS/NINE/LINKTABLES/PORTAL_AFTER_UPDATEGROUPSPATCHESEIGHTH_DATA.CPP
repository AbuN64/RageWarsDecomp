#include "DATA_OVERLAY_SN_RECORDS.H"

#include "TYPES.H"
#if defined(VERSION_US)
struct {
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record0;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; SnLe16 section; } record2;
    struct { u8 opcode; SnLe16 codeSize; u8 code[4]; } record3;
    struct { u8 opcode; SnLe16 section; } record4;
    struct { u8 opcode; SnLe16 codeSize; } record5;
} k_PortalAfterUpdateGroupsPatchesEighth __attribute__((aligned(1))) = {
    { 10, 96, SN_LE16(2), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1256) } } },
    { 10, 98, SN_LE16(6), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1256) } } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(4), { 0x4F, 0x00, 0x00, 0x00 } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(324) }
};
typedef char k_PortalAfterUpdateGroupsPatchesEighthSizeCheck[(sizeof(k_PortalAfterUpdateGroupsPatchesEighth) == 42) ? 1 : -1];
#endif
