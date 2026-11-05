#include "data_overlay_sn_records.h"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * The code payload continues in the following function. */
typedef struct SnLineDeltaRecord { u8 opcode; SnLe16 offset; u8 lineDelta; } SnLineDeltaRecord;
typedef struct SnPatchReferencePlusConstantRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } SnPatchReferencePlusConstantRecord;
typedef struct SnPatchRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } SnPatchRecord;
typedef struct SnOffsetMarkRecord { u8 opcode; SnLe16 offset; } SnOffsetMarkRecord;
typedef struct SnSectionSwitchRecord { u8 opcode; SnLe16 section; } SnSectionSwitchRecord;
typedef struct SnCodeBlock16Record { u8 opcode; SnLe16 codeSize; u8 code[16]; } SnCodeBlock16Record;
typedef struct SnCodeSizeRecord { u8 opcode; SnLe16 codeSize; } SnCodeSizeRecord;
typedef struct SnObjectRecords {
    SnLineDeltaRecord record0;
    SnPatchReferencePlusConstantRecord record1;
    SnLineDeltaRecord record2;
    SnPatchReferencePlusConstantRecord record3;
    SnLineDeltaRecord record4;
    SnPatchReferencePlusConstantRecord record5;
    SnPatchReferencePlusConstantRecord record6;
    SnLineDeltaRecord record7;
    SnPatchRecord record8;
    SnOffsetMarkRecord record9;
    SnPatchReferencePlusConstantRecord record10;
    SnPatchReferencePlusConstantRecord record11;
    SnOffsetMarkRecord record12;
    SnPatchReferencePlusConstantRecord record13;
    SnPatchReferencePlusConstantRecord record14;
    SnOffsetMarkRecord record15;
    SnPatchReferencePlusConstantRecord record16;
    SnPatchReferencePlusConstantRecord record17;
    SnLineDeltaRecord record18;
    SnPatchReferencePlusConstantRecord record19;
    SnLineDeltaRecord record20;
    SnPatchReferencePlusConstantRecord record21;
    SnLineDeltaRecord record22;
    SnPatchReferencePlusConstantRecord record23;
    SnLineDeltaRecord record24;
    SnPatchReferencePlusConstantRecord record25;
    SnPatchReferencePlusConstantRecord record26;
    SnLineDeltaRecord record27;
    SnPatchReferencePlusConstantRecord record28;
    SnPatchReferencePlusConstantRecord record29;
    SnLineDeltaRecord record30;
    SnPatchRecord record31;
    SnOffsetMarkRecord record32;
    SnPatchReferencePlusConstantRecord record33;
    SnPatchReferencePlusConstantRecord record34;
    SnOffsetMarkRecord record35;
    SnPatchReferencePlusConstantRecord record36;
    SnPatchReferencePlusConstantRecord record37;
    SnOffsetMarkRecord record38;
    SnPatchReferencePlusConstantRecord record39;
    SnPatchReferencePlusConstantRecord record40;
    SnLineDeltaRecord record41;
    SnPatchReferencePlusConstantRecord record42;
    SnLineDeltaRecord record43;
    SnPatchReferencePlusConstantRecord record44;
    SnLineDeltaRecord record45;
    SnPatchReferencePlusConstantRecord record46;
    SnPatchReferencePlusConstantRecord record47;
    SnLineDeltaRecord record48;
    SnPatchRecord record49;
    SnOffsetMarkRecord record50;
    SnPatchReferencePlusConstantRecord record51;
    SnPatchReferencePlusConstantRecord record52;
    SnOffsetMarkRecord record53;
    SnPatchReferencePlusConstantRecord record54;
    SnPatchReferencePlusConstantRecord record55;
    SnOffsetMarkRecord record56;
    SnPatchReferencePlusConstantRecord record57;
    SnPatchReferencePlusConstantRecord record58;
    SnLineDeltaRecord record59;
    SnPatchReferencePlusConstantRecord record60;
    SnLineDeltaRecord record61;
    SnPatchReferencePlusConstantRecord record62;
    SnLineDeltaRecord record63;
    SnPatchReferencePlusConstantRecord record64;
    SnLineDeltaRecord record65;
    SnPatchReferencePlusConstantRecord record66;
    SnLineDeltaRecord record67;
    SnPatchReferencePlusConstantRecord record68;
    SnPatchReferencePlusConstantRecord record69;
    SnLineDeltaRecord record70;
    SnPatchRecord record71;
    SnOffsetMarkRecord record72;
    SnPatchReferencePlusConstantRecord record73;
    SnPatchReferencePlusConstantRecord record74;
    SnOffsetMarkRecord record75;
    SnPatchReferencePlusConstantRecord record76;
    SnPatchReferencePlusConstantRecord record77;
    SnOffsetMarkRecord record78;
    SnPatchReferencePlusConstantRecord record79;
    SnPatchReferencePlusConstantRecord record80;
    SnLineDeltaRecord record81;
    SnPatchReferencePlusConstantRecord record82;
    SnLineDeltaRecord record83;
    SnPatchReferencePlusConstantRecord record84;
    SnLineDeltaRecord record85;
    SnPatchReferencePlusConstantRecord record86;
    SnLineDeltaRecord record87;
    SnPatchReferencePlusConstantRecord record88;
    SnLineDeltaRecord record89;
    SnPatchReferencePlusConstantRecord record90;
    SnPatchReferencePlusConstantRecord record91;
    SnLineDeltaRecord record92;
    SnPatchRecord record93;
    SnOffsetMarkRecord record94;
    SnPatchReferencePlusConstantRecord record95;
    SnPatchReferencePlusConstantRecord record96;
    SnOffsetMarkRecord record97;
    SnPatchReferencePlusConstantRecord record98;
    SnPatchReferencePlusConstantRecord record99;
    SnOffsetMarkRecord record100;
    SnPatchReferencePlusConstantRecord record101;
    SnPatchReferencePlusConstantRecord record102;
    SnOffsetMarkRecord record103;
    SnPatchReferencePlusConstantRecord record104;
    SnPatchReferencePlusConstantRecord record105;
    SnLineDeltaRecord record106;
    SnPatchReferencePlusConstantRecord record107;
    SnLineDeltaRecord record108;
    SnPatchReferencePlusConstantRecord record109;
    SnLineDeltaRecord record110;
    SnPatchReferencePlusConstantRecord record111;
    SnLineDeltaRecord record112;
    SnPatchReferencePlusConstantRecord record113;
    SnLineDeltaRecord record114;
    SnPatchReferencePlusConstantRecord record115;
    SnPatchReferencePlusConstantRecord record116;
    SnLineDeltaRecord record117;
    SnPatchRecord record118;
    SnOffsetMarkRecord record119;
    SnPatchReferencePlusConstantRecord record120;
    SnPatchReferencePlusConstantRecord record121;
    SnOffsetMarkRecord record122;
    SnPatchReferencePlusConstantRecord record123;
    SnOffsetMarkRecord record124;
    SnLineDeltaRecord record125;
    SnPatchReferencePlusConstantRecord record126;
    SnPatchReferencePlusConstantRecord record127;
    SnOffsetMarkRecord record128;
    SnPatchReferencePlusConstantRecord record129;
    SnPatchReferencePlusConstantRecord record130;
    SnOffsetMarkRecord record131;
    SnPatchReferencePlusConstantRecord record132;
    SnPatchReferencePlusConstantRecord record133;
    SnOffsetMarkRecord record134;
    SnPatchReferencePlusConstantRecord record135;
    SnPatchReferencePlusConstantRecord record136;
    SnLineDeltaRecord record137;
    SnPatchReferencePlusConstantRecord record138;
    SnLineDeltaRecord record139;
    SnPatchReferencePlusConstantRecord record140;
    SnLineDeltaRecord record141;
    SnPatchReferencePlusConstantRecord record142;
    SnLineDeltaRecord record143;
    SnPatchReferencePlusConstantRecord record144;
    SnLineDeltaRecord record145;
    SnPatchReferencePlusConstantRecord record146;
    SnPatchReferencePlusConstantRecord record147;
    SnLineDeltaRecord record148;
    SnPatchRecord record149;
    SnOffsetMarkRecord record150;
    SnPatchReferencePlusConstantRecord record151;
    SnPatchReferencePlusConstantRecord record152;
    SnOffsetMarkRecord record153;
    SnPatchReferencePlusConstantRecord record154;
    SnOffsetMarkRecord record155;
    SnLineDeltaRecord record156;
    SnPatchReferencePlusConstantRecord record157;
    SnPatchReferencePlusConstantRecord record158;
    SnOffsetMarkRecord record159;
    SnPatchReferencePlusConstantRecord record160;
    SnPatchReferencePlusConstantRecord record161;
    SnOffsetMarkRecord record162;
    SnPatchReferencePlusConstantRecord record163;
    SnPatchReferencePlusConstantRecord record164;
    SnOffsetMarkRecord record165;
    SnPatchReferencePlusConstantRecord record166;
    SnPatchReferencePlusConstantRecord record167;
    SnLineDeltaRecord record168;
    SnPatchReferencePlusConstantRecord record169;
    SnLineDeltaRecord record170;
    SnPatchReferencePlusConstantRecord record171;
    SnLineDeltaRecord record172;
    SnPatchReferencePlusConstantRecord record173;
    SnLineDeltaRecord record174;
    SnPatchReferencePlusConstantRecord record175;
    SnLineDeltaRecord record176;
    SnPatchReferencePlusConstantRecord record177;
    SnPatchReferencePlusConstantRecord record178;
    SnPatchReferencePlusConstantRecord record179;
    SnPatchReferencePlusConstantRecord record180;
    SnPatchRecord record181;
    SnOffsetMarkRecord record182;
    SnPatchReferencePlusConstantRecord record183;
    SnLineDeltaRecord record184;
    SnPatchReferencePlusConstantRecord record185;
    SnOffsetMarkRecord record186;
    SnLineDeltaRecord record187;
    SnLineDeltaRecord record188;
    SnLineDeltaRecord record189;
    SnOffsetMarkRecord record190;
    SnLineDeltaRecord record191;
    SnOffsetMarkRecord record192;
    SnPatchReferencePlusConstantRecord record193;
    SnPatchReferencePlusConstantRecord record194;
    SnPatchReferencePlusConstantRecord record195;
    SnPatchReferencePlusConstantRecord record196;
    SnPatchReferencePlusConstantRecord record197;
    SnPatchRecord record198;
    SnLineDeltaRecord record199;
    SnPatchReferencePlusConstantRecord record200;
    SnPatchReferencePlusConstantRecord record201;
    SnLineDeltaRecord record202;
    SnLineDeltaRecord record203;
    SnPatchReferencePlusConstantRecord record204;
    SnLineDeltaRecord record205;
    SnPatchReferencePlusConstantRecord record206;
    SnPatchReferencePlusConstantRecord record207;
    SnOffsetMarkRecord record208;
    SnPatchReferencePlusConstantRecord record209;
    SnPatchReferencePlusConstantRecord record210;
    SnOffsetMarkRecord record211;
    SnPatchReferencePlusConstantRecord record212;
    SnLineDeltaRecord record213;
    SnPatchReferencePlusConstantRecord record214;
    SnOffsetMarkRecord record215;
    SnLineDeltaRecord record216;
    SnSectionSwitchRecord record217;
    SnCodeBlock16Record record218;
    SnSectionSwitchRecord record219;
    SnCodeSizeRecord record220;
} SnObjectRecords;
SnObjectRecords g_pakInterfaceSnRecords_us_E7D10 __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 130 },
    { 10, 92, SN_LE16(0), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9928) } } },
    { 52, SN_LE16(8), 3 },
    { 10, 92, SN_LE16(24), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7744) } } },
    { 52, SN_LE16(32), 3 },
    { 10, 96, SN_LE16(34), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(38), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(96), 2 },
    { 10, 92, SN_LE16(96), { 2, SN_LE16(402) } },
    { 50, SN_LE16(104) },
    { 10, 96, SN_LE16(106), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(160) },
    { 10, 96, SN_LE16(162), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(166), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(216) },
    { 10, 96, SN_LE16(218), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(222), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(272), 2 },
    { 10, 92, SN_LE16(276), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(284), 2 },
    { 10, 92, SN_LE16(284), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7744) } } },
    { 52, SN_LE16(292), 2 },
    { 10, 92, SN_LE16(292), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9928) } } },
    { 52, SN_LE16(300), 3 },
    { 10, 92, SN_LE16(340), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(8336) } } },
    { 10, 92, SN_LE16(360), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(8336) } } },
    { 52, SN_LE16(368), 4 },
    { 10, 96, SN_LE16(370), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(374), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(428), 2 },
    { 10, 92, SN_LE16(428), { 2, SN_LE16(402) } },
    { 50, SN_LE16(436) },
    { 10, 96, SN_LE16(438), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(442), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(492) },
    { 10, 96, SN_LE16(494), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(498), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(548) },
    { 10, 96, SN_LE16(550), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(554), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(604), 2 },
    { 10, 92, SN_LE16(608), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(616), 2 },
    { 10, 92, SN_LE16(616), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(8336) } } },
    { 52, SN_LE16(624), 3 },
    { 10, 96, SN_LE16(626), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(630), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(688), 2 },
    { 10, 92, SN_LE16(688), { 2, SN_LE16(402) } },
    { 50, SN_LE16(696) },
    { 10, 96, SN_LE16(698), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(702), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(752) },
    { 10, 96, SN_LE16(754), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(758), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(808) },
    { 10, 96, SN_LE16(810), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(814), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(864), 2 },
    { 10, 92, SN_LE16(868), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(876), 2 },
    { 10, 92, SN_LE16(876), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(8336) } } },
    { 52, SN_LE16(884), 2 },
    { 10, 92, SN_LE16(884), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9928) } } },
    { 52, SN_LE16(892), 3 },
    { 10, 92, SN_LE16(920), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(8636) } } },
    { 52, SN_LE16(928), 4 },
    { 10, 96, SN_LE16(930), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(934), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(988), 2 },
    { 10, 92, SN_LE16(988), { 2, SN_LE16(402) } },
    { 50, SN_LE16(996) },
    { 10, 96, SN_LE16(998), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1002), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1052) },
    { 10, 96, SN_LE16(1054), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1058), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1108) },
    { 10, 96, SN_LE16(1110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1164), 2 },
    { 10, 92, SN_LE16(1168), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(1176), 2 },
    { 10, 92, SN_LE16(1176), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(8636) } } },
    { 52, SN_LE16(1184), 2 },
    { 10, 92, SN_LE16(1184), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9928) } } },
    { 52, SN_LE16(1192), 3 },
    { 10, 92, SN_LE16(1220), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(8992) } } },
    { 52, SN_LE16(1228), 4 },
    { 10, 96, SN_LE16(1230), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1234), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1288), 2 },
    { 10, 92, SN_LE16(1288), { 2, SN_LE16(402) } },
    { 50, SN_LE16(1296) },
    { 10, 96, SN_LE16(1298), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1302), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1352) },
    { 10, 96, SN_LE16(1354), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1358), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1408) },
    { 10, 96, SN_LE16(1410), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1414), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1464) },
    { 10, 96, SN_LE16(1466), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1470), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1520), 2 },
    { 10, 92, SN_LE16(1524), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(1532), 2 },
    { 10, 92, SN_LE16(1532), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(8992) } } },
    { 52, SN_LE16(1540), 2 },
    { 10, 92, SN_LE16(1540), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9928) } } },
    { 52, SN_LE16(1548), 3 },
    { 10, 92, SN_LE16(1576), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9428) } } },
    { 52, SN_LE16(1584), 4 },
    { 10, 96, SN_LE16(1586), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1590), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1644), 2 },
    { 10, 92, SN_LE16(1644), { 2, SN_LE16(402) } },
    { 50, SN_LE16(1652) },
    { 10, 96, SN_LE16(1654), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1658), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1708) },
    { 10, 92, SN_LE16(1708), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(63320) } } },
    { 50, SN_LE16(1720) },
    { 52, SN_LE16(1732), 2 },
    { 10, 96, SN_LE16(1734), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1738), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1788) },
    { 10, 96, SN_LE16(1790), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1794), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1844) },
    { 10, 96, SN_LE16(1846), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1850), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1900) },
    { 10, 96, SN_LE16(1902), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1906), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1956), 3 },
    { 10, 92, SN_LE16(1960), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(1968), 2 },
    { 10, 92, SN_LE16(1968), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9428) } } },
    { 52, SN_LE16(1976), 2 },
    { 10, 92, SN_LE16(1976), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9928) } } },
    { 52, SN_LE16(1984), 3 },
    { 10, 92, SN_LE16(2012), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9864) } } },
    { 52, SN_LE16(2020), 4 },
    { 10, 96, SN_LE16(2022), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2026), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2080), 2 },
    { 10, 92, SN_LE16(2080), { 2, SN_LE16(402) } },
    { 50, SN_LE16(2088) },
    { 10, 96, SN_LE16(2090), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2094), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2144) },
    { 10, 92, SN_LE16(2144), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(63320) } } },
    { 50, SN_LE16(2156) },
    { 52, SN_LE16(2168), 2 },
    { 10, 96, SN_LE16(2170), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2174), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2224) },
    { 10, 96, SN_LE16(2226), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2230), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2280) },
    { 10, 96, SN_LE16(2282), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2286), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2336) },
    { 10, 96, SN_LE16(2338), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2342), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2392), 3 },
    { 10, 92, SN_LE16(2396), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(2404), 2 },
    { 10, 92, SN_LE16(2404), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9864) } } },
    { 52, SN_LE16(2412), 2 },
    { 10, 92, SN_LE16(2412), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9928) } } },
    { 52, SN_LE16(2420), 3 },
    { 10, 92, SN_LE16(2420), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9928) } } },
    { 52, SN_LE16(2428), 3 },
    { 10, 96, SN_LE16(2430), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(2434), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(2442), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 98, SN_LE16(2446), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 92, SN_LE16(2448), { 2, SN_LE16(376) } },
    { 50, SN_LE16(2468) },
    { 10, 92, SN_LE16(2468), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9928) } } },
    { 52, SN_LE16(2476), 4 },
    { 10, 92, SN_LE16(2480), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(9940) } } },
    { 50, SN_LE16(2488) },
    { 52, SN_LE16(2512), 0 },
    { 52, SN_LE16(2512), 3 },
    { 52, SN_LE16(2512), 0 },
    { 50, SN_LE16(2544) },
    { 52, SN_LE16(2544), 3 },
    { 50, SN_LE16(2556) },
    { 10, 92, SN_LE16(2584), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(10084) } } },
    { 10, 96, SN_LE16(2594), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(2598), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(2606), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 98, SN_LE16(2610), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 92, SN_LE16(2612), { 2, SN_LE16(376) } },
    { 52, SN_LE16(2632), 2 },
    { 10, 96, SN_LE16(2634), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2638), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2696), 2 },
    { 52, SN_LE16(2720), 2 },
    { 10, 92, SN_LE16(2748), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(10208) } } },
    { 52, SN_LE16(2756), 4 },
    { 10, 96, SN_LE16(2758), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2762), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2808) },
    { 10, 96, SN_LE16(2810), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2814), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2864) },
    { 10, 92, SN_LE16(2864), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(10324) } } },
    { 52, SN_LE16(2872), 5 },
    { 10, 92, SN_LE16(2876), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(10336) } } },
    { 50, SN_LE16(2884) },
    { 52, SN_LE16(2908), 0 },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(16), { 0x70, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00 } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(2076) },
};
typedef char MenuResourceStreamSize[(sizeof(SnObjectRecords) == 1941) ? 1 : -1];
#endif
