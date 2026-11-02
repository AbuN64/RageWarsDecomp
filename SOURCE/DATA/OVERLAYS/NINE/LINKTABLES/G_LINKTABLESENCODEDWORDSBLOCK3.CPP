#include "DATA_OVERLAY_SN_RECORDS.H"

#include "include_asm.h"

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US)
struct {
    u8 precedingRecordFragment[2];
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; SnLe16 offset; } record6;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record7;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record8;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record9;
    struct { u8 opcode; SnLe16 offset; } record10;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record12;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record13;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record14;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record15;
    struct { u8 opcode; SnLe16 offset; } record16;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record17;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record18;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record21;
    struct { u8 opcode; SnLe16 offset; } record22;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record23;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record25;
    struct { u8 opcode; SnLe16 offset; } record26;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record28;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record29;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record32;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record33;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record34;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record35;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record36;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record37;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record38;
    struct { u8 opcode; SnLe16 offset; } record39;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record40;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record41;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record42;
    struct { u8 opcode; SnLe16 offset; } record43;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record44;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record45;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record46;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record47;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record48;
    struct { u8 opcode; SnLe16 offset; } record49;
    struct { u8 opcode; SnLe16 codeSize; } record50;
} g_LinktablesEncodedWordsBlock3 __attribute__((aligned(4))) = {
    { 0xA5, 0x01 },
    { 52, SN_LE16(6112), 3 },
    { 10, 96, SN_LE16(6114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(6118), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(6162), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(6166), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(6176) },
    { 52, SN_LE16(6200), 0 },
    { 52, SN_LE16(6200), 3 },
    { 52, SN_LE16(6200), 0 },
    { 50, SN_LE16(6216) },
    { 52, SN_LE16(6216), 7 },
    { 10, 92, SN_LE16(6240), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(61040) } } },
    { 52, SN_LE16(6248), 2 },
    { 10, 96, SN_LE16(6250), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(6254), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(6288) },
    { 10, 96, SN_LE16(6290), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(6294), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(6328), 2 },
    { 10, 96, SN_LE16(6358), { 2, SN_LE16(384) } },
    { 10, 98, SN_LE16(6362), { 2, SN_LE16(384) } },
    { 50, SN_LE16(6372) },
    { 52, SN_LE16(6388), 2 },
    { 10, 96, SN_LE16(6430), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(6434), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(6480) },
    { 52, SN_LE16(6488), 2 },
    { 10, 92, SN_LE16(6500), { 2, SN_LE16(421) } },
    { 52, SN_LE16(6508), 2 },
    { 52, SN_LE16(6520), 3 },
    { 10, 92, SN_LE16(6520), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(61020) } } },
    { 52, SN_LE16(6528), 2 },
    { 56, SN_LE16(6540), SN_LE32(5263) },
    { 10, 92, SN_LE16(6552), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(60704) } } },
    { 52, SN_LE16(6560), 20 },
    { 52, SN_LE16(6584), 0 },
    { 52, SN_LE16(6584), 3 },
    { 52, SN_LE16(6584), 0 },
    { 50, SN_LE16(6604) },
    { 52, SN_LE16(6604), 6 },
    { 10, 96, SN_LE16(6606), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(6610), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(6644) },
    { 10, 96, SN_LE16(6646), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(6650), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(6684), 2 },
    { 10, 96, SN_LE16(6714), { 2, SN_LE16(384) } },
    { 10, 98, SN_LE16(6718), { 2, SN_LE16(384) } },
    { 50, SN_LE16(6728) },
    { 2, SN_LE16(3584) }
};
typedef char g_LinktablesEncodedWordsBlock3SizeCheck[(sizeof(g_LinktablesEncodedWordsBlock3) == 364) ? 1 : -1];
#endif
