#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
struct {
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record16;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record17;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record18;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record23;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record25;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record28;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record29;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record32;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record33;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record34;
    struct { u8 opcode; SnLe16 section; } record35;
    struct { u8 opcode; SnLe16 codeSize; u8 code[81]; } record36;
    struct { u8 opcode; SnLe16 section; } record37;
    struct { u8 opcode; SnLe16 codeSize; } record38;
} g_pakInterfaceProcRecords __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 5 },
    { 52, SN_LE16(0), 0 },
    { 52, SN_LE16(32), 14 },
    { 10, 96, SN_LE16(58), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(16) } } },
    { 10, 98, SN_LE16(66), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(16) } } },
    { 10, 92, SN_LE16(76), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32536) } } },
    { 10, 96, SN_LE16(106), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(8) } } },
    { 10, 98, SN_LE16(114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(8) } } },
    { 10, 96, SN_LE16(158), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(12) } } },
    { 10, 98, SN_LE16(166), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(12) } } },
    { 10, 96, SN_LE16(198), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(12) } } },
    { 10, 98, SN_LE16(206), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(12) } } },
    { 10, 92, SN_LE16(220), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32516) } } },
    { 10, 96, SN_LE16(258), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(16) } } },
    { 10, 98, SN_LE16(266), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(16) } } },
    { 10, 92, SN_LE16(300), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32548) } } },
    { 10, 92, SN_LE16(320), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32244) } } },
    { 10, 92, SN_LE16(332), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32548) } } },
    { 52, SN_LE16(364), 0 },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(81), { 0x61, 0x6E, 0x4D, 0x6F, 0x64, 0x65, 0x20, 0x3E, 0x3D, 0x20, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x5F, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x4D, 0x4F, 0x44, 0x45, 0x5F, 0x43, 0x52, 0x45, 0x41, 0x54, 0x45, 0x20, 0x26, 0x26, 0x20, 0x61, 0x6E, 0x4D, 0x6F, 0x64, 0x65, 0x20, 0x3C, 0x20, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x5F, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x4D, 0x4F, 0x44, 0x45, 0x5F, 0x45, 0x4E, 0x44, 0x00 } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(132) },
};
#endif
