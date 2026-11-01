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
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record10;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record12;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record13;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record14;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record15;
    struct { u8 opcode; SnLe16 section; } record16;
    struct { u8 opcode; SnLe16 codeSize; u8 code[29]; } record17;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record18;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record23;
    struct { u8 opcode; SnLe16 section; } record24;
    struct { u8 opcode; SnLe16 codeSize; } record25;
} k_PortalAfterCheckPAK __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 3 },
    { 52, SN_LE16(0), 0 },
    { 50, SN_LE16(20) },
    { 52, SN_LE16(20), 5 },
    { 10, 92, SN_LE16(48), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(45556) } } },
    { 10, 96, SN_LE16(58), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(62), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(70), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(74), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(76), { 2, SN_LE16(376) } },
    { 52, SN_LE16(96), 2 },
    { 52, SN_LE16(104), 2 },
    { 10, 92, SN_LE16(108), { 2, SN_LE16(391) } },
    { 52, SN_LE16(120), 4 },
    { 10, 96, SN_LE16(146), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1352) } } },
    { 10, 98, SN_LE16(150), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1352) } } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(29), { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 10, 8, SN_LE16(5), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(45628) } } },
    { 10, 8, SN_LE16(9), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(45692) } } },
    { 10, 8, SN_LE16(13), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(45692) } } },
    { 10, 8, SN_LE16(17), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(45628) } } },
    { 10, 8, SN_LE16(21), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(45692) } } },
    { 10, 8, SN_LE16(25), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(45756) } } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(1220) }
};
typedef char k_PortalAfterCheckPAKSizeCheck[(sizeof(k_PortalAfterCheckPAK) == 251) ? 1 : -1];
#endif
