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
typedef struct SnCodeBlock96Record { u8 opcode; SnLe16 codeSize; u8 code[96]; } SnCodeBlock96Record;
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
    SnOffsetMarkRecord record11;
    SnPatchReferencePlusConstantRecord record12;
    SnPatchReferencePlusConstantRecord record13;
    SnPatchReferencePlusConstantRecord record14;
    SnLineDeltaRecord record15;
    SnPatchReferencePlusConstantRecord record16;
    SnPatchReferencePlusConstantRecord record17;
    SnPatchRecord record18;
    SnOffsetMarkRecord record19;
    SnPatchReferencePlusConstantRecord record20;
    SnPatchReferencePlusConstantRecord record21;
    SnPatchReferencePlusConstantRecord record22;
    SnPatchReferencePlusConstantRecord record23;
    SnPatchRecord record24;
    SnLineDeltaRecord record25;
    SnPatchReferencePlusConstantRecord record26;
    SnPatchReferencePlusConstantRecord record27;
    SnOffsetMarkRecord record28;
    SnPatchReferencePlusConstantRecord record29;
    SnPatchReferencePlusConstantRecord record30;
    SnLineDeltaRecord record31;
    SnLineDeltaRecord record32;
    SnPatchReferencePlusConstantRecord record33;
    SnOffsetMarkRecord record34;
    SnPatchReferencePlusConstantRecord record35;
    SnLineDeltaRecord record36;
    SnPatchReferencePlusConstantRecord record37;
    SnPatchReferencePlusConstantRecord record38;
    SnOffsetMarkRecord record39;
    SnPatchReferencePlusConstantRecord record40;
    SnPatchReferencePlusConstantRecord record41;
    SnPatchReferencePlusConstantRecord record42;
    SnPatchReferencePlusConstantRecord record43;
    SnLineDeltaRecord record44;
    SnPatchReferencePlusConstantRecord record45;
    SnPatchReferencePlusConstantRecord record46;
    SnPatchReferencePlusConstantRecord record47;
    SnPatchReferencePlusConstantRecord record48;
    SnOffsetMarkRecord record49;
    SnPatchReferencePlusConstantRecord record50;
    SnPatchReferencePlusConstantRecord record51;
    SnPatchReferencePlusConstantRecord record52;
    SnPatchReferencePlusConstantRecord record53;
    SnLineDeltaRecord record54;
    SnOffsetMarkRecord record55;
    SnPatchRecord record56;
    SnLineDeltaRecord record57;
    SnPatchReferencePlusConstantRecord record58;
    SnLineDeltaRecord record59;
    SnPatchReferencePlusConstantRecord record60;
    SnOffsetMarkRecord record61;
    SnLineDeltaRecord record62;
    SnLineDeltaRecord record63;
    SnLineDeltaRecord record64;
    SnOffsetMarkRecord record65;
    SnLineDeltaRecord record66;
    SnOffsetMarkRecord record67;
    SnPatchReferencePlusConstantRecord record68;
    SnPatchReferencePlusConstantRecord record69;
    SnPatchReferencePlusConstantRecord record70;
    SnPatchReferencePlusConstantRecord record71;
    SnPatchReferencePlusConstantRecord record72;
    SnPatchRecord record73;
    SnOffsetMarkRecord record74;
    SnPatchReferencePlusConstantRecord record75;
    SnPatchReferencePlusConstantRecord record76;
    SnPatchReferencePlusConstantRecord record77;
    SnPatchReferencePlusConstantRecord record78;
    SnLineDeltaRecord record79;
    SnOffsetMarkRecord record80;
    SnPatchReferencePlusConstantRecord record81;
    SnLineDeltaRecord record82;
    SnPatchReferencePlusConstantRecord record83;
    SnPatchReferencePlusConstantRecord record84;
    SnPatchRecord record85;
    SnOffsetMarkRecord record86;
    SnPatchReferencePlusConstantRecord record87;
    SnPatchReferencePlusConstantRecord record88;
    SnPatchReferencePlusConstantRecord record89;
    SnPatchReferencePlusConstantRecord record90;
    SnPatchRecord record91;
    SnLineDeltaRecord record92;
    SnPatchReferencePlusConstantRecord record93;
    SnPatchReferencePlusConstantRecord record94;
    SnOffsetMarkRecord record95;
    SnPatchReferencePlusConstantRecord record96;
    SnPatchReferencePlusConstantRecord record97;
    SnLineDeltaRecord record98;
    SnPatchReferencePlusConstantRecord record99;
    SnPatchReferencePlusConstantRecord record100;
    SnOffsetMarkRecord record101;
    SnPatchReferencePlusConstantRecord record102;
    SnPatchReferencePlusConstantRecord record103;
    SnPatchReferencePlusConstantRecord record104;
    SnPatchReferencePlusConstantRecord record105;
    SnLineDeltaRecord record106;
    SnPatchReferencePlusConstantRecord record107;
    SnPatchReferencePlusConstantRecord record108;
    SnPatchReferencePlusConstantRecord record109;
    SnPatchReferencePlusConstantRecord record110;
    SnOffsetMarkRecord record111;
    SnPatchReferencePlusConstantRecord record112;
    SnPatchReferencePlusConstantRecord record113;
    SnPatchReferencePlusConstantRecord record114;
    SnPatchReferencePlusConstantRecord record115;
    SnLineDeltaRecord record116;
    SnOffsetMarkRecord record117;
    SnPatchRecord record118;
    SnOffsetMarkRecord record119;
    SnPatchReferencePlusConstantRecord record120;
    SnLineDeltaRecord record121;
    SnPatchReferencePlusConstantRecord record122;
    SnLineDeltaRecord record123;
    SnPatchReferencePlusConstantRecord record124;
    SnOffsetMarkRecord record125;
    SnLineDeltaRecord record126;
    SnLineDeltaRecord record127;
    SnLineDeltaRecord record128;
    SnOffsetMarkRecord record129;
    SnLineDeltaRecord record130;
    SnOffsetMarkRecord record131;
    SnPatchReferencePlusConstantRecord record132;
    SnPatchReferencePlusConstantRecord record133;
    SnPatchReferencePlusConstantRecord record134;
    SnPatchReferencePlusConstantRecord record135;
    SnPatchReferencePlusConstantRecord record136;
    SnPatchRecord record137;
    SnLineDeltaRecord record138;
    SnPatchReferencePlusConstantRecord record139;
    SnPatchReferencePlusConstantRecord record140;
    SnPatchReferencePlusConstantRecord record141;
    SnPatchReferencePlusConstantRecord record142;
    SnSectionSwitchRecord record143;
    SnCodeBlock96Record record144;
    SnPatchReferencePlusConstantRecord record145;
    SnPatchReferencePlusConstantRecord record146;
    SnPatchReferencePlusConstantRecord record147;
    SnPatchReferencePlusConstantRecord record148;
    SnPatchReferencePlusConstantRecord record149;
    SnPatchReferencePlusConstantRecord record150;
    SnPatchReferencePlusConstantRecord record151;
    SnPatchReferencePlusConstantRecord record152;
    SnPatchReferencePlusConstantRecord record153;
    SnPatchReferencePlusConstantRecord record154;
    SnPatchReferencePlusConstantRecord record155;
    SnPatchReferencePlusConstantRecord record156;
    SnPatchReferencePlusConstantRecord record157;
    SnPatchReferencePlusConstantRecord record158;
    SnPatchReferencePlusConstantRecord record159;
    SnPatchReferencePlusConstantRecord record160;
    SnPatchReferencePlusConstantRecord record161;
    SnPatchReferencePlusConstantRecord record162;
    SnPatchReferencePlusConstantRecord record163;
    SnPatchReferencePlusConstantRecord record164;
    SnPatchReferencePlusConstantRecord record165;
    SnPatchReferencePlusConstantRecord record166;
    SnPatchReferencePlusConstantRecord record167;
    SnPatchReferencePlusConstantRecord record168;
    SnSectionSwitchRecord record169;
    SnCodeSizeRecord record170;
} SnObjectRecords;
SnObjectRecords g_pakInterfaceSnRecords_us_E8CC1 __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 3 },
    { 52, SN_LE16(0), 0 },
    { 50, SN_LE16(32) },
    { 52, SN_LE16(32), 6 },
    { 50, SN_LE16(44) },
    { 10, 92, SN_LE16(72), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(10480) } } },
    { 10, 96, SN_LE16(82), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(86), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(94), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 98, SN_LE16(98), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 92, SN_LE16(100), { 2, SN_LE16(376) } },
    { 50, SN_LE16(120) },
    { 10, 96, SN_LE16(122), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(126), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(184), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(11228) } } },
    { 52, SN_LE16(192), 4 },
    { 10, 96, SN_LE16(194), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(198), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(208), { 2, SN_LE16(411) } },
    { 50, SN_LE16(220) },
    { 10, 96, SN_LE16(234), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(238), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(246), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 98, SN_LE16(250), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 92, SN_LE16(252), { 2, SN_LE16(376) } },
    { 52, SN_LE16(272), 2 },
    { 10, 96, SN_LE16(274), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(278), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(324) },
    { 10, 96, SN_LE16(326), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(330), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(380), 3 },
    { 52, SN_LE16(396), 5 },
    { 10, 92, SN_LE16(400), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(11240) } } },
    { 50, SN_LE16(408) },
    { 10, 92, SN_LE16(408), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(11220) } } },
    { 52, SN_LE16(416), 3 },
    { 10, 96, SN_LE16(418), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(422), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(484) },
    { 10, 96, SN_LE16(486), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(490), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(534), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(538), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(592), 3 },
    { 10, 96, SN_LE16(594), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(598), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(602), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(606), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(716) },
    { 10, 96, SN_LE16(718), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(722), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(726), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(730), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(836), 2 },
    { 50, SN_LE16(848) },
    { 10, 92, SN_LE16(852), { 2, SN_LE16(396) } },
    { 52, SN_LE16(860), 3 },
    { 10, 92, SN_LE16(860), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(11228) } } },
    { 52, SN_LE16(868), 43 },
    { 10, 92, SN_LE16(872), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(11240) } } },
    { 50, SN_LE16(880) },
    { 52, SN_LE16(904), 0 },
    { 52, SN_LE16(904), 3 },
    { 52, SN_LE16(904), 0 },
    { 50, SN_LE16(936) },
    { 52, SN_LE16(936), 6 },
    { 50, SN_LE16(948) },
    { 10, 92, SN_LE16(976), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(11384) } } },
    { 10, 96, SN_LE16(986), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(990), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(998), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 98, SN_LE16(1002), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 92, SN_LE16(1004), { 2, SN_LE16(376) } },
    { 50, SN_LE16(1024) },
    { 10, 96, SN_LE16(1026), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1030), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1112), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12180) } } },
    { 10, 92, SN_LE16(1144), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12172) } } },
    { 52, SN_LE16(1152), 4 },
    { 50, SN_LE16(1168) },
    { 10, 92, SN_LE16(1172), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12192) } } },
    { 52, SN_LE16(1180), 3 },
    { 10, 96, SN_LE16(1182), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1186), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1196), { 2, SN_LE16(411) } },
    { 50, SN_LE16(1208) },
    { 10, 96, SN_LE16(1222), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(1226), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(1234), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 98, SN_LE16(1238), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 92, SN_LE16(1240), { 2, SN_LE16(376) } },
    { 52, SN_LE16(1260), 2 },
    { 10, 96, SN_LE16(1262), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1266), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1312) },
    { 10, 96, SN_LE16(1314), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1318), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1368), 2 },
    { 10, 96, SN_LE16(1370), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1374), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1428) },
    { 10, 96, SN_LE16(1430), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1434), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1478), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1482), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1536), 2 },
    { 10, 96, SN_LE16(1538), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1542), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1546), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1550), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1660) },
    { 10, 96, SN_LE16(1662), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1666), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1670), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1674), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1780), 2 },
    { 50, SN_LE16(1792) },
    { 10, 92, SN_LE16(1796), { 2, SN_LE16(396) } },
    { 50, SN_LE16(1804) },
    { 10, 92, SN_LE16(1804), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12180) } } },
    { 52, SN_LE16(1812), 45 },
    { 10, 92, SN_LE16(1812), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12180) } } },
    { 52, SN_LE16(1820), 3 },
    { 10, 92, SN_LE16(1824), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12192) } } },
    { 50, SN_LE16(1832) },
    { 52, SN_LE16(1856), 0 },
    { 52, SN_LE16(1856), 2 },
    { 52, SN_LE16(1856), 0 },
    { 50, SN_LE16(1892) },
    { 52, SN_LE16(1892), 9 },
    { 50, SN_LE16(1904) },
    { 10, 92, SN_LE16(1932), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12340) } } },
    { 10, 96, SN_LE16(1942), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(1946), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(1954), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 98, SN_LE16(1958), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 92, SN_LE16(1960), { 2, SN_LE16(376) } },
    { 52, SN_LE16(1980), 3 },
    { 10, 96, SN_LE16(1982), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1986), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(2054), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(312) } } },
    { 10, 98, SN_LE16(2058), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(312) } } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(96), { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 10, 8, SN_LE16(0), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12700) } } },
    { 10, 8, SN_LE16(4), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(8), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(12), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(16), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(20), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(24), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(28), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(32), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12436) } } },
    { 10, 8, SN_LE16(36), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(12800) } } },
    { 10, 8, SN_LE16(40), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(44), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(48), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(52), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(56), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(60), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(64), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(68), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(72), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13120) } } },
    { 10, 8, SN_LE16(76), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(80), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(84), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(88), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13608) } } },
    { 10, 8, SN_LE16(92), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13364) } } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(1440) },
};
typedef char MenuResourceStreamSize[(sizeof(SnObjectRecords) == 1734) ? 1 : -1];
#endif
