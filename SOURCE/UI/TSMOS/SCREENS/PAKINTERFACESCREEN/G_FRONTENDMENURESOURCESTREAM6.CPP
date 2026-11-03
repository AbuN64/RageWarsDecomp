#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * Boundary gap at +0x130: code payload continues in following function. */
typedef struct MenuStreamRecord0 { u8 opcode; SnLe16 offset; u8 lineDelta; } MenuStreamRecord0;
typedef struct MenuStreamRecord1 { u8 opcode; SnLe16 offset; } MenuStreamRecord1;
typedef struct MenuStreamRecord2 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } MenuStreamRecord2;
typedef struct MenuStreamRecord3 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } MenuStreamRecord3;
typedef struct MenuStreamRecord4 { u8 opcode; SnLe16 section; } MenuStreamRecord4;
typedef struct MenuStreamRecord5 { u8 opcode; SnLe16 codeSize; u8 code[38]; } MenuStreamRecord5;
typedef struct MenuStreamRecord6 { u8 opcode; SnLe16 codeSize; } MenuStreamRecord6;
typedef struct MenuResourceStreamRecords {
    MenuStreamRecord0 record0;
    MenuStreamRecord0 record1;
    MenuStreamRecord1 record2;
    MenuStreamRecord0 record3;
    MenuStreamRecord1 record4;
    MenuStreamRecord2 record5;
    MenuStreamRecord2 record6;
    MenuStreamRecord2 record7;
    MenuStreamRecord2 record8;
    MenuStreamRecord2 record9;
    MenuStreamRecord3 record10;
    MenuStreamRecord0 record11;
    MenuStreamRecord0 record12;
    MenuStreamRecord2 record13;
    MenuStreamRecord2 record14;
    MenuStreamRecord2 record15;
    MenuStreamRecord2 record16;
    MenuStreamRecord4 record17;
    MenuStreamRecord5 record18;
    MenuStreamRecord2 record19;
    MenuStreamRecord2 record20;
    MenuStreamRecord2 record21;
    MenuStreamRecord2 record22;
    MenuStreamRecord2 record23;
    MenuStreamRecord2 record24;
    MenuStreamRecord2 record25;
    MenuStreamRecord2 record26;
    MenuStreamRecord4 record27;
    MenuStreamRecord6 record28;
} MenuResourceStreamRecords;
MenuResourceStreamRecords g_frontendMenuResourceStream6 __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 4 },
    { 52, SN_LE16(0), 0 },
    { 50, SN_LE16(32) },
    { 52, SN_LE16(32), 9 },
    { 50, SN_LE16(44) },
    { 10, 92, SN_LE16(72), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7368) } } },
    { 10, 96, SN_LE16(82), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(86), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(94), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 98, SN_LE16(98), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 92, SN_LE16(100), { 2, SN_LE16(376) } },
    { 52, SN_LE16(120), 4 },
    { 52, SN_LE16(144), 2 },
    { 10, 96, SN_LE16(146), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(150), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(182), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(264) } } },
    { 10, 98, SN_LE16(186), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(264) } } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(38), { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 10, 8, SN_LE16(6), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(8344) } } },
    { 10, 8, SN_LE16(10), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9000) } } },
    { 10, 8, SN_LE16(14), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9436) } } },
    { 10, 8, SN_LE16(18), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(8644) } } },
    { 10, 8, SN_LE16(22), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7752) } } },
    { 10, 8, SN_LE16(26), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7452) } } },
    { 10, 8, SN_LE16(30), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7460) } } },
    { 10, 8, SN_LE16(34), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9872) } } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(2908) },
};
typedef char MenuResourceStreamSize[(sizeof(MenuResourceStreamRecords) == 304) ? 1 : -1];
#endif
