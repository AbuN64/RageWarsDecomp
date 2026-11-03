#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * Boundary gap at +0x795: code payload continues in following function. */
typedef struct MenuStreamRecord0 { u8 opcode; SnLe16 offset; u8 lineDelta; } MenuStreamRecord0;
typedef struct MenuStreamRecord1 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } MenuStreamRecord1;
typedef struct MenuStreamRecord2 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } MenuStreamRecord2;
typedef struct MenuStreamRecord3 { u8 opcode; SnLe16 offset; } MenuStreamRecord3;
typedef struct MenuStreamRecord4 { u8 opcode; SnLe16 section; } MenuStreamRecord4;
typedef struct MenuStreamRecord5 { u8 opcode; SnLe16 codeSize; u8 code[16]; } MenuStreamRecord5;
typedef struct MenuStreamRecord6 { u8 opcode; SnLe16 codeSize; } MenuStreamRecord6;
typedef struct MenuResourceStreamRecords {
    MenuStreamRecord0 record0;
    MenuStreamRecord1 record1;
    MenuStreamRecord0 record2;
    MenuStreamRecord1 record3;
    MenuStreamRecord0 record4;
    MenuStreamRecord1 record5;
    MenuStreamRecord1 record6;
    MenuStreamRecord0 record7;
    MenuStreamRecord2 record8;
    MenuStreamRecord3 record9;
    MenuStreamRecord1 record10;
    MenuStreamRecord1 record11;
    MenuStreamRecord3 record12;
    MenuStreamRecord1 record13;
    MenuStreamRecord1 record14;
    MenuStreamRecord3 record15;
    MenuStreamRecord1 record16;
    MenuStreamRecord1 record17;
    MenuStreamRecord0 record18;
    MenuStreamRecord1 record19;
    MenuStreamRecord0 record20;
    MenuStreamRecord1 record21;
    MenuStreamRecord0 record22;
    MenuStreamRecord1 record23;
    MenuStreamRecord0 record24;
    MenuStreamRecord1 record25;
    MenuStreamRecord1 record26;
    MenuStreamRecord0 record27;
    MenuStreamRecord1 record28;
    MenuStreamRecord1 record29;
    MenuStreamRecord0 record30;
    MenuStreamRecord2 record31;
    MenuStreamRecord3 record32;
    MenuStreamRecord1 record33;
    MenuStreamRecord1 record34;
    MenuStreamRecord3 record35;
    MenuStreamRecord1 record36;
    MenuStreamRecord1 record37;
    MenuStreamRecord3 record38;
    MenuStreamRecord1 record39;
    MenuStreamRecord1 record40;
    MenuStreamRecord0 record41;
    MenuStreamRecord1 record42;
    MenuStreamRecord0 record43;
    MenuStreamRecord1 record44;
    MenuStreamRecord0 record45;
    MenuStreamRecord1 record46;
    MenuStreamRecord1 record47;
    MenuStreamRecord0 record48;
    MenuStreamRecord2 record49;
    MenuStreamRecord3 record50;
    MenuStreamRecord1 record51;
    MenuStreamRecord1 record52;
    MenuStreamRecord3 record53;
    MenuStreamRecord1 record54;
    MenuStreamRecord1 record55;
    MenuStreamRecord3 record56;
    MenuStreamRecord1 record57;
    MenuStreamRecord1 record58;
    MenuStreamRecord0 record59;
    MenuStreamRecord1 record60;
    MenuStreamRecord0 record61;
    MenuStreamRecord1 record62;
    MenuStreamRecord0 record63;
    MenuStreamRecord1 record64;
    MenuStreamRecord0 record65;
    MenuStreamRecord1 record66;
    MenuStreamRecord0 record67;
    MenuStreamRecord1 record68;
    MenuStreamRecord1 record69;
    MenuStreamRecord0 record70;
    MenuStreamRecord2 record71;
    MenuStreamRecord3 record72;
    MenuStreamRecord1 record73;
    MenuStreamRecord1 record74;
    MenuStreamRecord3 record75;
    MenuStreamRecord1 record76;
    MenuStreamRecord1 record77;
    MenuStreamRecord3 record78;
    MenuStreamRecord1 record79;
    MenuStreamRecord1 record80;
    MenuStreamRecord0 record81;
    MenuStreamRecord1 record82;
    MenuStreamRecord0 record83;
    MenuStreamRecord1 record84;
    MenuStreamRecord0 record85;
    MenuStreamRecord1 record86;
    MenuStreamRecord0 record87;
    MenuStreamRecord1 record88;
    MenuStreamRecord0 record89;
    MenuStreamRecord1 record90;
    MenuStreamRecord1 record91;
    MenuStreamRecord0 record92;
    MenuStreamRecord2 record93;
    MenuStreamRecord3 record94;
    MenuStreamRecord1 record95;
    MenuStreamRecord1 record96;
    MenuStreamRecord3 record97;
    MenuStreamRecord1 record98;
    MenuStreamRecord1 record99;
    MenuStreamRecord3 record100;
    MenuStreamRecord1 record101;
    MenuStreamRecord1 record102;
    MenuStreamRecord3 record103;
    MenuStreamRecord1 record104;
    MenuStreamRecord1 record105;
    MenuStreamRecord0 record106;
    MenuStreamRecord1 record107;
    MenuStreamRecord0 record108;
    MenuStreamRecord1 record109;
    MenuStreamRecord0 record110;
    MenuStreamRecord1 record111;
    MenuStreamRecord0 record112;
    MenuStreamRecord1 record113;
    MenuStreamRecord0 record114;
    MenuStreamRecord1 record115;
    MenuStreamRecord1 record116;
    MenuStreamRecord0 record117;
    MenuStreamRecord2 record118;
    MenuStreamRecord3 record119;
    MenuStreamRecord1 record120;
    MenuStreamRecord1 record121;
    MenuStreamRecord3 record122;
    MenuStreamRecord1 record123;
    MenuStreamRecord3 record124;
    MenuStreamRecord0 record125;
    MenuStreamRecord1 record126;
    MenuStreamRecord1 record127;
    MenuStreamRecord3 record128;
    MenuStreamRecord1 record129;
    MenuStreamRecord1 record130;
    MenuStreamRecord3 record131;
    MenuStreamRecord1 record132;
    MenuStreamRecord1 record133;
    MenuStreamRecord3 record134;
    MenuStreamRecord1 record135;
    MenuStreamRecord1 record136;
    MenuStreamRecord0 record137;
    MenuStreamRecord1 record138;
    MenuStreamRecord0 record139;
    MenuStreamRecord1 record140;
    MenuStreamRecord0 record141;
    MenuStreamRecord1 record142;
    MenuStreamRecord0 record143;
    MenuStreamRecord1 record144;
    MenuStreamRecord0 record145;
    MenuStreamRecord1 record146;
    MenuStreamRecord1 record147;
    MenuStreamRecord0 record148;
    MenuStreamRecord2 record149;
    MenuStreamRecord3 record150;
    MenuStreamRecord1 record151;
    MenuStreamRecord1 record152;
    MenuStreamRecord3 record153;
    MenuStreamRecord1 record154;
    MenuStreamRecord3 record155;
    MenuStreamRecord0 record156;
    MenuStreamRecord1 record157;
    MenuStreamRecord1 record158;
    MenuStreamRecord3 record159;
    MenuStreamRecord1 record160;
    MenuStreamRecord1 record161;
    MenuStreamRecord3 record162;
    MenuStreamRecord1 record163;
    MenuStreamRecord1 record164;
    MenuStreamRecord3 record165;
    MenuStreamRecord1 record166;
    MenuStreamRecord1 record167;
    MenuStreamRecord0 record168;
    MenuStreamRecord1 record169;
    MenuStreamRecord0 record170;
    MenuStreamRecord1 record171;
    MenuStreamRecord0 record172;
    MenuStreamRecord1 record173;
    MenuStreamRecord0 record174;
    MenuStreamRecord1 record175;
    MenuStreamRecord0 record176;
    MenuStreamRecord1 record177;
    MenuStreamRecord1 record178;
    MenuStreamRecord1 record179;
    MenuStreamRecord1 record180;
    MenuStreamRecord2 record181;
    MenuStreamRecord3 record182;
    MenuStreamRecord1 record183;
    MenuStreamRecord0 record184;
    MenuStreamRecord1 record185;
    MenuStreamRecord3 record186;
    MenuStreamRecord0 record187;
    MenuStreamRecord0 record188;
    MenuStreamRecord0 record189;
    MenuStreamRecord3 record190;
    MenuStreamRecord0 record191;
    MenuStreamRecord3 record192;
    MenuStreamRecord1 record193;
    MenuStreamRecord1 record194;
    MenuStreamRecord1 record195;
    MenuStreamRecord1 record196;
    MenuStreamRecord1 record197;
    MenuStreamRecord2 record198;
    MenuStreamRecord0 record199;
    MenuStreamRecord1 record200;
    MenuStreamRecord1 record201;
    MenuStreamRecord0 record202;
    MenuStreamRecord0 record203;
    MenuStreamRecord1 record204;
    MenuStreamRecord0 record205;
    MenuStreamRecord1 record206;
    MenuStreamRecord1 record207;
    MenuStreamRecord3 record208;
    MenuStreamRecord1 record209;
    MenuStreamRecord1 record210;
    MenuStreamRecord3 record211;
    MenuStreamRecord1 record212;
    MenuStreamRecord0 record213;
    MenuStreamRecord1 record214;
    MenuStreamRecord3 record215;
    MenuStreamRecord0 record216;
    MenuStreamRecord4 record217;
    MenuStreamRecord5 record218;
    MenuStreamRecord4 record219;
    MenuStreamRecord6 record220;
} MenuResourceStreamRecords;
MenuResourceStreamRecords g_frontendMenuResourceStream2 __attribute__((aligned(1))) = {
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
typedef char MenuResourceStreamSize[(sizeof(MenuResourceStreamRecords) == 1941) ? 1 : -1];
#endif
