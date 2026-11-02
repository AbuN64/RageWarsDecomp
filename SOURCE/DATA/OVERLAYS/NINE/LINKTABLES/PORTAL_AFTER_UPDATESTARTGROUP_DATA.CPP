#include "DATA_OVERLAY_SN_RECORDS.H"

#include "TYPES.H"
#if defined(VERSION_US)
struct {
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record0;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record5;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record6;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record7;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record9;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record10;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record11;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record12;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record13;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record14;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record15;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record16;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record17;
    struct { u8 opcode; SnLe16 offset; } record18;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record23;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record25;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record28;
    struct { u8 opcode; SnLe16 section; } record29;
    struct { u8 opcode; SnLe16 codeSize; u8 code[4]; } record30;
    struct { u8 opcode; SnLe16 section; } record31;
    u8 followingRecordFragment[1];
} k_PortalAfterUpdateStartGroup __attribute__((aligned(4))) = {
    { 10, 96, SN_LE16(2), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1260) } } },
    { 10, 98, SN_LE16(6), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1260) } } },
    { 10, 92, SN_LE16(32), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(44608) } } },
    { 52, SN_LE16(64), 2 },
    { 10, 92, SN_LE16(64), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(44628) } } },
    { 52, SN_LE16(72), 6 },
    { 10, 92, SN_LE16(72), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(44628) } } },
    { 52, SN_LE16(80), 2 },
    { 10, 96, SN_LE16(82), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(86), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(106), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 56, SN_LE16(144), SN_LE32(4190) },
    { 10, 92, SN_LE16(156), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(43176) } } },
    { 52, SN_LE16(164), 80 },
    { 52, SN_LE16(188), 0 },
    { 52, SN_LE16(188), 4 },
    { 52, SN_LE16(188), 0 },
    { 50, SN_LE16(208) },
    { 52, SN_LE16(208), 3 },
    { 10, 92, SN_LE16(236), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(44832) } } },
    { 10, 96, SN_LE16(246), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(250), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(258), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(262), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(264), { 2, SN_LE16(376) } },
    { 52, SN_LE16(284), 4 },
    { 10, 96, SN_LE16(294), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(298), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(4), { 0x43, 0x96, 0x00, 0x00 } },
    { 6, SN_LE16(2) },
    { 0x02 }
};
typedef char k_PortalAfterUpdateStartGroupSizeCheck[(sizeof(k_PortalAfterUpdateStartGroup) == 288) ? 1 : -1];
struct { SnLe16 codeSize; } k_PortalAfterUpdateStartGroupTail = { SN_LE16(28) };
#endif
