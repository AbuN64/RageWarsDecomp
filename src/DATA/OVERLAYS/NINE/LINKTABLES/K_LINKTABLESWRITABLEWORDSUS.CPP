#include "DATA_OVERLAY_SN_RECORDS.H"

#include "TYPES.H"
#if defined(VERSION_US)
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
    struct { u8 opcode; SnLe16 codeSize; u8 code[364]; } record15;
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
    struct { u8 opcode; SnLe16 codeSize; u8 code[132]; } record38;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record39;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record40;
    struct { u8 opcode; SnLe16 offset; } record41;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record42;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record43;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record44;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record45;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record46;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record47;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record48;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record49;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record50;
    struct { u8 opcode; SnLe16 offset; } record51;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record52;
    struct { u8 opcode; SnLe16 section; } record53;
    struct { u8 opcode; SnLe16 codeSize; u8 code[138]; } record54;
    struct { u8 opcode; SnLe16 section; } record55;
} k_LinktablesWritableWordsUs __attribute__((aligned(4))) = {
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
    { 2, SN_LE16(364), { 0x27, 0xBD, 0xFF, 0xD8, 0xAF, 0xBF, 0x00, 0x24, 0xAF, 0xBE, 0x00, 0x20, 0x03, 0xA0, 0xF0, 0x21, 0xAF, 0xC4, 0x00, 0x28, 0xAF, 0xC5, 0x00, 0x2C, 0xAF, 0xC6, 0x00, 0x30, 0xAF, 0xC7, 0x00, 0x34, 0xAF, 0xC0, 0x00, 0x18, 0x8F, 0xC2, 0x00, 0x18, 0x00, 0x40, 0x20, 0x21, 0x00, 0x04, 0x18, 0x40, 0x00, 0x62, 0x18, 0x21, 0x00, 0x03, 0x10, 0x80, 0x3C, 0x01, 0x00, 0x00, 0x00, 0x22, 0x08, 0x21, 0x8C, 0x23, 0x00, 0x00, 0x14, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x00, 0x40, 0x20, 0x21, 0x00, 0x04, 0x18, 0x40, 0x00, 0x62, 0x18, 0x21, 0x00, 0x03, 0x10, 0x80, 0x3C, 0x01, 0x00, 0x00, 0x00, 0x22, 0x08, 0x21, 0x8C, 0x23, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x2C, 0x14, 0x62, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x00, 0x40, 0x20, 0x21, 0x00, 0x04, 0x18, 0x40, 0x00, 0x62, 0x18, 0x21, 0x00, 0x03, 0x10, 0x80, 0x8F, 0xC3, 0x00, 0x28, 0x84, 0x64, 0x00, 0x0C, 0x3C, 0x01, 0x00, 0x00, 0x00, 0x22, 0x08, 0x21, 0x8C, 0x22, 0x00, 0x00, 0x10, 0x44, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x00, 0x40, 0x20, 0x21, 0x00, 0x04, 0x18, 0x40, 0x00, 0x62, 0x18, 0x21, 0x00, 0x03, 0x10, 0x80, 0x3C, 0x01, 0x00, 0x00, 0x00, 0x22, 0x08, 0x21, 0x8C, 0x23, 0x00, 0x00, 0x24, 0x02, 0x75, 0x30, 0x10, 0x62, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x00, 0x40, 0x20, 0x21, 0x00, 0x04, 0x18, 0x40, 0x00, 0x62, 0x18, 0x21, 0x00, 0x03, 0x10, 0x80, 0x8F, 0xC3, 0x00, 0x38, 0xAF, 0xA3, 0x00, 0x10, 0x3C, 0x01, 0x00, 0x00, 0x00, 0x22, 0x08, 0x21, 0x8C, 0x22, 0x00, 0x00, 0x8F, 0xC4, 0x00, 0x28, 0x8F, 0xC5, 0x00, 0x2C, 0x8F, 0xC6, 0x00, 0x30, 0x8F, 0xC7, 0x00, 0x34, 0x00, 0x40, 0xF8, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x18, 0x21, 0x00, 0x60, 0x10, 0x21, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x24, 0x43, 0x00, 0x01, 0xAF, 0xC3, 0x00, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x21, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0xE8, 0x21, 0x8F, 0xBF, 0x00, 0x24, 0x8F, 0xBE, 0x00, 0x20, 0x27, 0xBD, 0x00, 0x28, 0x03, 0xE0, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 } },
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
    { 2, SN_LE16(132), { 0x27, 0xBD, 0xFF, 0xE8, 0xAF, 0xBF, 0x00, 0x14, 0xAF, 0xBE, 0x00, 0x10, 0x03, 0xA0, 0xF0, 0x21, 0xAF, 0xC4, 0x00, 0x18, 0x8F, 0xC2, 0x00, 0x18, 0x04, 0x40, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x28, 0x43, 0x00, 0x08, 0x10, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x04, 0x00, 0x00, 0x24, 0x84, 0x00, 0x00, 0x24, 0x05, 0x0D, 0xD6, 0x3C, 0x06, 0x00, 0x00, 0x24, 0xC6, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x3C, 0x01, 0x00, 0x00, 0xAC, 0x22, 0x00, 0x00, 0x03, 0xC0, 0xE8, 0x21, 0x8F, 0xBF, 0x00, 0x14, 0x8F, 0xBE, 0x00, 0x10, 0x27, 0xBD, 0x00, 0x18, 0x03, 0xE0, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 } },
    { 52, SN_LE16(0), 6 },
    { 52, SN_LE16(0), 0 },
    { 50, SN_LE16(20) },
    { 10, 92, SN_LE16(48), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32668) } } },
    { 10, 96, SN_LE16(58), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(62), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(70), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(856) } } },
    { 10, 98, SN_LE16(74), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(856) } } },
    { 10, 92, SN_LE16(76), { 2, SN_LE16(376) } },
    { 52, SN_LE16(96), 2 },
    { 10, 96, SN_LE16(102), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(106), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(0) } } },
    { 50, SN_LE16(108) },
    { 52, SN_LE16(132), 0 },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(138), { 0x00, 0x00, 0x00, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x20, 0x3E, 0x3D, 0x30, 0x20, 0x26, 0x26, 0x20, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x20, 0x3C, 0x20, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x5F, 0x4D, 0x41, 0x58, 0x5F, 0x55, 0x53, 0x45, 0x52, 0x53, 0x00, 0x00, 0x00, 0x70, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x00, 0x70, 0x54, 0x65, 0x78, 0x74, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x70, 0x54, 0x65, 0x78, 0x74, 0x53, 0x74, 0x72, 0x69, 0x6E, 0x67, 0x00, 0x5B, 0x4D, 0x4F, 0x44, 0x45, 0x5D, 0x00, 0x00, 0x70, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x2D, 0x3E, 0x70, 0x43, 0x68, 0x69, 0x6C, 0x64, 0x72, 0x65, 0x6E, 0x2D, 0x3E, 0x54, 0x79, 0x70, 0x65, 0x20, 0x3D, 0x3D, 0x20, 0x53, 0x4D, 0x5F, 0x4F, 0x54, 0x5F, 0x54, 0x45, 0x58, 0x54, 0x00 } },
    { 6, SN_LE16(2) }
};
typedef char k_LinktablesWritableWordsUsSizeCheck[(sizeof(k_LinktablesWritableWordsUs) == 1252) ? 1 : -1];
struct {
    struct { u8 opcode; SnLe16 codeSize; } record0;
} k_LinktablesWritableWordsUsTail __attribute__((aligned(1))) = {
    { 2, SN_LE16(452) }
};
typedef char k_LinktablesWritableWordsUsTailSizeCheck[(sizeof(k_LinktablesWritableWordsUsTail) == 3) ? 1 : -1];
#endif
