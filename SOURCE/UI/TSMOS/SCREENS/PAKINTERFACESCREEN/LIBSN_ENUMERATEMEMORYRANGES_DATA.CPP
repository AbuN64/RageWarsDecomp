#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
/* Typed Psy-Q records surrounding OnAccept pieces eight and nine. */
struct {
    u8 precedingRecordFragment[10];
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; SnLe16 section; } record5;
    struct { u8 opcode; SnLe16 codeSize; } record6;
} k_LibsnEnumeratememoryrangesEncodedWords __attribute__((aligned(1))) = {
    { 0x00, 0x2C, 0x04, 0x02, 0x00, 0x00, 0x44, 0x70, 0x00, 0x00 },
    { 10, 8, SN_LE16(16), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 10, 8, SN_LE16(20), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28756) } } },
    { 10, 8, SN_LE16(24), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 10, 8, SN_LE16(28), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28772) } } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(2164) },
};
#endif
