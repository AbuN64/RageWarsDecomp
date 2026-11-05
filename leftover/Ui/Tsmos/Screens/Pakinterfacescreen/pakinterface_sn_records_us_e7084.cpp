#include "data_overlay_sn_records.h"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * The code payload continues in the following function. */
typedef struct SnLineDeltaRecord { u8 opcode; SnLe16 offset; u8 lineDelta; } SnLineDeltaRecord;
typedef struct SnOffsetMarkRecord { u8 opcode; SnLe16 offset; } SnOffsetMarkRecord;
typedef struct SnPatchReferencePlusConstantRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } SnPatchReferencePlusConstantRecord;
typedef struct SnPatchRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } SnPatchRecord;
typedef struct SnSectionSwitchRecord { u8 opcode; SnLe16 section; } SnSectionSwitchRecord;
typedef struct SnCodeBlock38Record { u8 opcode; SnLe16 codeSize; u8 code[38]; } SnCodeBlock38Record;
typedef struct SnCodeSizeRecord { u8 opcode; SnLe16 codeSize; } SnCodeSizeRecord;
typedef struct SnObjectRecords {
    SnLineDeltaRecord record0;
    SnLineDeltaRecord record1;
    SnOffsetMarkRecord record2;
    SnLineDeltaRecord record3;
    SnOffsetMarkRecord record4;
    SnPatchReferencePlusConstantRecord record5;
    SnPatchReferencePlusConstantRecord record6;
    SnPatchReferencePlusConstantRecord record7;
    SnPatchReferencePlusConstantRecord record8;
    SnPatchReferencePlusConstantRecord record9;
    SnPatchRecord record10;
    SnLineDeltaRecord record11;
    SnLineDeltaRecord record12;
    SnPatchReferencePlusConstantRecord record13;
    SnPatchReferencePlusConstantRecord record14;
    SnPatchReferencePlusConstantRecord record15;
    SnPatchReferencePlusConstantRecord record16;
    SnSectionSwitchRecord record17;
    SnCodeBlock38Record record18;
    SnPatchReferencePlusConstantRecord record19;
    SnPatchReferencePlusConstantRecord record20;
    SnPatchReferencePlusConstantRecord record21;
    SnPatchReferencePlusConstantRecord record22;
    SnPatchReferencePlusConstantRecord record23;
    SnPatchReferencePlusConstantRecord record24;
    SnPatchReferencePlusConstantRecord record25;
    SnPatchReferencePlusConstantRecord record26;
    SnSectionSwitchRecord record27;
    SnCodeSizeRecord record28;
} SnObjectRecords;
SnObjectRecords g_pakInterfaceSnRecords_us_E7084 __attribute__((aligned(1))) = {
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
typedef char MenuResourceStreamSize[(sizeof(SnObjectRecords) == 304) ? 1 : -1];
#endif
