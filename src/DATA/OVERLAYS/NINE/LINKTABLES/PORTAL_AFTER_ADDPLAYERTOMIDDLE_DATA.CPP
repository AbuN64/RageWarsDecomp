#include "DATA_OVERLAY_SN_RECORDS.H"

#include "TYPES.H"
#if defined(VERSION_US)
struct {
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record0;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record1;
    struct { u8 opcode; SnLe16 offset; } record2;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record6;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record7;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record9;
    struct { u8 opcode; SnLe16 offset; } record10;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record12;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record13;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record14;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record15;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record16;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record17;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record18;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record19;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record20;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record23;
    struct { u8 opcode; SnLe16 offset; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record25;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record26;
    struct { u8 opcode; SnLe16 offset; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record28;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record29;
    struct { u8 opcode; SnLe16 offset; } record30;
    struct { u8 opcode; SnLe16 offset; } record31;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record32;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record33;
    struct { u8 opcode; SnLe16 offset; } record34;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record35;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record36;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record37;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record38;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record39;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record40;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record41;
    struct { u8 opcode; SnLe16 offset; } record42;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record43;
    struct { u8 opcode; SnLe16 section; } record44;
    struct { u8 opcode; SnLe16 codeSize; u8 code[38]; } record45;
    struct { u8 opcode; SnLe16 section; } record46;
    struct { u8 opcode; SnLe16 codeSize; } record47;
} k_PortalAfterAddPlayerToMiddle __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 22 },
    { 52, SN_LE16(0), 0 },
    { 50, SN_LE16(24) },
    { 52, SN_LE16(24), 3 },
    { 10, 92, SN_LE16(52), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51024) } } },
    { 10, 96, SN_LE16(62), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(66), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(74), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(78), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(80), { 2, SN_LE16(376) } },
    { 50, SN_LE16(100) },
    { 10, 92, SN_LE16(128), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51100) } } },
    { 10, 96, SN_LE16(138), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(142), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(150), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1816) } } },
    { 10, 98, SN_LE16(154), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1816) } } },
    { 10, 92, SN_LE16(156), { 2, SN_LE16(376) } },
    { 52, SN_LE16(176), 2 },
    { 52, SN_LE16(180), 2 },
    { 10, 92, SN_LE16(180), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52620) } } },
    { 52, SN_LE16(192), 2 },
    { 52, SN_LE16(204), 2 },
    { 10, 96, SN_LE16(206), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(210), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(244) },
    { 10, 96, SN_LE16(246), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(250), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(284) },
    { 10, 96, SN_LE16(286), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(290), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(324) },
    { 50, SN_LE16(332) },
    { 10, 92, SN_LE16(332), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51308) } } },
    { 52, SN_LE16(340), 3 },
    { 50, SN_LE16(344) },
    { 10, 96, SN_LE16(346), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(350), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(358), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 98, SN_LE16(362), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 92, SN_LE16(364), { 2, SN_LE16(376) } },
    { 52, SN_LE16(384), 3 },
    { 10, 92, SN_LE16(392), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51324) } } },
    { 50, SN_LE16(400) },
    { 52, SN_LE16(424), 0 },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(38), { 0x00, 0x61, 0x6E, 0x4D, 0x69, 0x64, 0x64, 0x6C, 0x65, 0x53, 0x6C, 0x6F, 0x74, 0x20, 0x3E, 0x3D, 0x30, 0x20, 0x26, 0x26, 0x20, 0x61, 0x6E, 0x4D, 0x69, 0x64, 0x64, 0x6C, 0x65, 0x53, 0x6C, 0x6F, 0x74, 0x20, 0x3C, 0x20, 0x34, 0x00 } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(3132) }
};
typedef char k_PortalAfterAddPlayerToMiddleSizeCheck[(sizeof(k_PortalAfterAddPlayerToMiddle) == 434) ? 1 : -1];
#endif
