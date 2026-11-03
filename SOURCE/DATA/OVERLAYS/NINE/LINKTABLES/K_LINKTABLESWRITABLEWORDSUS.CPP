#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
struct {
    u8 precedingRecordFragment[10];
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record6;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record7;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record9;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record10;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record12;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record13;
    struct { u8 opcode; SnLe16 section; } record14;
    struct { u8 opcode; SnLe16 codeSize; } record15;
} k_LinktablesWritableWordsUs __attribute__((aligned(1))) = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 10, 8, SN_LE16(8), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5300) } } },
    { 10, 8, SN_LE16(20), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5472) } } },
    { 10, 8, SN_LE16(32), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(6260) } } },
    { 10, 8, SN_LE16(44), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(0) } } },
    { 10, 8, SN_LE16(56), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5360) } } },
    { 10, 8, SN_LE16(68), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31488) } } },
    { 10, 8, SN_LE16(80), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15100) } } },
    { 10, 8, SN_LE16(92), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7248) } } },
    { 10, 8, SN_LE16(104), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9964) } } },
    { 10, 8, SN_LE16(116), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13656) } } },
    { 10, 8, SN_LE16(128), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12216) } } },
    { 10, 8, SN_LE16(140), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(10360) } } },
    { 10, 8, SN_LE16(152), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(11264) } } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(364) },
};
#endif
