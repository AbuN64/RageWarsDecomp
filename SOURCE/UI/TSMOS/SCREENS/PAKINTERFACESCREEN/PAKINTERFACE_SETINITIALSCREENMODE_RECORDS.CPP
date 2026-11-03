#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
struct {
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
} g_pakInterfaceInitialModeRecords __attribute__((aligned(1))) = {
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


struct {
    struct { u8 opcode; SnLe16 codeSize; } record0;
} k_LinktablesWritableWordsUsTail __attribute__((aligned(1))) = {
    { 2, SN_LE16(452) }
};
typedef char k_LinktablesWritableWordsUsTailSizeCheck[(sizeof(k_LinktablesWritableWordsUsTail) == 3) ? 1 : -1];
#endif
