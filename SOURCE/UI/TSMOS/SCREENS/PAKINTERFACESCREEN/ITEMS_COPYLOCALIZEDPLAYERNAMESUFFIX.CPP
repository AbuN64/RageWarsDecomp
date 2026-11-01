#include "DATA_OVERLAY_SN_RECORDS.H"
#include "DATA/OVLTBL/ITEMS_COPYLOCALIZEDPLAYERNAMESUFFIX.H"
#include "TYPES.H"
#if defined(VERSION_DE) || defined(VERSION_US)
#ifdef VERSION_US
struct {
    u8 precedingRecordFragment[5];
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record3;
    u8 followingRecordFragment[6];
} k_ItemsCopylocalizedplayernamesuffixEncodedWordsBlock1 __attribute__((aligned(4))) = {
    { 0x00, 0xAC, 0x7D, 0x00, 0x00 },
    { 52, SN_LE16(896), 42 },
    { 10, 92, SN_LE16(896), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(63148) } } },
    { 52, SN_LE16(912), 2 },
    { 0x0A, 0x5C, 0x90, 0x03, 0x02, 0x92 }
};
typedef char k_ItemsCopylocalizedplayernamesuffixEncodedWordsBlock1SizeCheck[(sizeof(k_ItemsCopylocalizedplayernamesuffixEncodedWordsBlock1) == 32) ? 1 : -1];
#if defined(VERSION_US)
struct {
    u8 precedingRecordFragment[1];
    struct { u8 opcode; SnLe16 offset; } record0;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; SnLe16 offset; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record3;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record6;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record7;
    struct { u8 opcode; SnLe16 offset; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record9;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record10;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record12;
    struct { u8 opcode; SnLe16 offset; } record13;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record14;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record15;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record16;
    struct { u8 opcode; SnLe16 offset; } record17;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record18;
    struct { u8 opcode; SnLe16 offset; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record21;
    struct { u8 opcode; SnLe16 offset; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record23;
    struct { u8 opcode; SnLe16 offset; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record25;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record27;
    struct { u8 opcode; SnLe16 offset; } record28;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record29;
    struct { u8 opcode; SnLe16 offset; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record32;
    struct { u8 opcode; SnLe16 offset; } record33;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record34;
    struct { u8 opcode; SnLe16 offset; } record35;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record36;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record37;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record38;
    struct { u8 opcode; SnLe16 offset; } record39;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record40;
    struct { u8 opcode; SnLe16 section; } record41;
    struct { u8 opcode; SnLe16 codeSize; u8 codeFragment[158]; } record42;
} k_ItemsCopylocalizedplayernamesuffixEncodedWords __attribute__((aligned(4))) = {
    { 0x01 },
    { 50, SN_LE16(920) },
    { 10, 92, SN_LE16(924), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(64660) } } },
    { 50, SN_LE16(932) },
    { 10, 92, SN_LE16(936), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32184) } } },
    { 52, SN_LE16(944), 3 },
    { 10, 92, SN_LE16(944), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32172) } } },
    { 52, SN_LE16(952), 5 },
    { 10, 92, SN_LE16(952), { 2, SN_LE16(402) } },
    { 50, SN_LE16(960) },
    { 10, 96, SN_LE16(962), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(966), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(970), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(974), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1080) },
    { 10, 92, SN_LE16(1080), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32172) } } },
    { 52, SN_LE16(1088), 4 },
    { 10, 92, SN_LE16(1088), { 2, SN_LE16(402) } },
    { 50, SN_LE16(1096) },
    { 10, 92, SN_LE16(1100), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52984) } } },
    { 50, SN_LE16(1108) },
    { 10, 96, SN_LE16(1110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1164) },
    { 10, 92, SN_LE16(1168), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1176) },
    { 10, 92, SN_LE16(1176), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32172) } } },
    { 52, SN_LE16(1184), 3 },
    { 10, 92, SN_LE16(1184), { 2, SN_LE16(402) } },
    { 50, SN_LE16(1192) },
    { 10, 92, SN_LE16(1196), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53760) } } },
    { 50, SN_LE16(1204) },
    { 10, 96, SN_LE16(1206), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1210), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1260) },
    { 10, 92, SN_LE16(1264), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1272) },
    { 10, 92, SN_LE16(1272), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32172) } } },
    { 52, SN_LE16(1280), 35 },
    { 10, 92, SN_LE16(1284), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32184) } } },
    { 50, SN_LE16(1292) },
    { 52, SN_LE16(1316), 0 },
    { 6, SN_LE16(3) },
    { 2, SN_LE16(168), { 0x00, 0x00, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0A, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x08, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x06, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x03, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }
};
typedef char k_ItemsCopylocalizedplayernamesuffixEncodedWordsSizeCheck[(sizeof(k_ItemsCopylocalizedplayernamesuffixEncodedWords) == 496) ? 1 : -1];
#endif
#endif
#endif
