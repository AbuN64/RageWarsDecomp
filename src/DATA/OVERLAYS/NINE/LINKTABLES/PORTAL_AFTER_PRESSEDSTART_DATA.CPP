#include "DATA_OVERLAY_SN_RECORDS.H"

#include "TYPES.H"
#if defined(VERSION_US)
struct {
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record0;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; SnLe16 offset; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record6;
    struct { u8 opcode; SnLe16 offset; } record7;
    struct { u8 opcode; SnLe16 offset; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record9;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record10;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record11;
    struct { u8 opcode; SnLe16 offset; } record12;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record13;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record14;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record15;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record16;
    struct { u8 opcode; SnLe16 offset; } record17;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record18;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record23;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record24;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record25;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left; struct { u8 opcode; SnLe16 symbol; } right; } expression; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left; struct { u8 opcode; SnLe16 symbol; } right; } expression; } record27;
    struct { u8 opcode; SnLe16 offset; } record28;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record29;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; SnLe16 offset; } record32;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record33;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record34;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record35;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record36;
    struct { u8 opcode; SnLe16 section; } record37;
    struct { u8 opcode; SnLe16 codeSize; u8 code[67]; } record38;
    struct { u8 opcode; SnLe16 section; } record39;
    struct { u8 opcode; SnLe16 codeSize; } record40;
} k_PortalAfterPressedStart __attribute__((aligned(1))) = {
    { 10, 96, SN_LE16(2), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1276) } } },
    { 10, 98, SN_LE16(6), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1276) } } },
    { 10, 92, SN_LE16(32), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(44984) } } },
    { 50, SN_LE16(64) },
    { 10, 96, SN_LE16(66), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(70), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(120), { 2, SN_LE16(381) } },
    { 50, SN_LE16(132) },
    { 50, SN_LE16(144) },
    { 10, 96, SN_LE16(146), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(150), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(200), { 2, SN_LE16(381) } },
    { 50, SN_LE16(212) },
    { 52, SN_LE16(224), 2 },
    { 52, SN_LE16(248), 0 },
    { 52, SN_LE16(248), 5 },
    { 52, SN_LE16(248), 0 },
    { 50, SN_LE16(268) },
    { 52, SN_LE16(268), 2 },
    { 10, 92, SN_LE16(296), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(45268) } } },
    { 10, 96, SN_LE16(306), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(310), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(318), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(322), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(324), { 2, SN_LE16(376) } },
    { 52, SN_LE16(344), 2 },
    { 10, 96, SN_LE16(374), { 44, { 0, SN_LE32(157920) }, { 2, SN_LE16(388) } } },
    { 10, 98, SN_LE16(378), { 44, { 0, SN_LE32(157920) }, { 2, SN_LE16(388) } } },
    { 50, SN_LE16(388) },
    { 52, SN_LE16(400), 2 },
    { 10, 96, SN_LE16(402), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(406), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(456) },
    { 10, 96, SN_LE16(458), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(462), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(512), 5 },
    { 52, SN_LE16(536), 0 },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(67), { 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x2D, 0x3E, 0x6D, 0x5F, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x5B, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x5D, 0x2E, 0x6D, 0x5F, 0x6E, 0x4E, 0x65, 0x78, 0x74, 0x4D, 0x6F, 0x64, 0x65, 0x20, 0x21, 0x3D, 0x20, 0x2D, 0x31, 0x00 } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(168) }
};
typedef char k_PortalAfterPressedStartSizeCheck[(sizeof(k_PortalAfterPressedStart) == 391) ? 1 : -1];
#endif
