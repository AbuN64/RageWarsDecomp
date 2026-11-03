#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * Boundary gap at +0x6C6: code payload continues in following function. */
typedef struct MenuStreamRecord0 { u8 opcode; SnLe16 offset; u8 lineDelta; } MenuStreamRecord0;
typedef struct MenuStreamRecord1 { u8 opcode; SnLe16 offset; } MenuStreamRecord1;
typedef struct MenuStreamRecord2 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } MenuStreamRecord2;
typedef struct MenuStreamRecord3 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } MenuStreamRecord3;
typedef struct MenuStreamRecord4 { u8 opcode; SnLe16 section; } MenuStreamRecord4;
typedef struct MenuStreamRecord5 { u8 opcode; SnLe16 codeSize; u8 code[96]; } MenuStreamRecord5;
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
    MenuStreamRecord1 record11;
    MenuStreamRecord2 record12;
    MenuStreamRecord2 record13;
    MenuStreamRecord2 record14;
    MenuStreamRecord0 record15;
    MenuStreamRecord2 record16;
    MenuStreamRecord2 record17;
    MenuStreamRecord3 record18;
    MenuStreamRecord1 record19;
    MenuStreamRecord2 record20;
    MenuStreamRecord2 record21;
    MenuStreamRecord2 record22;
    MenuStreamRecord2 record23;
    MenuStreamRecord3 record24;
    MenuStreamRecord0 record25;
    MenuStreamRecord2 record26;
    MenuStreamRecord2 record27;
    MenuStreamRecord1 record28;
    MenuStreamRecord2 record29;
    MenuStreamRecord2 record30;
    MenuStreamRecord0 record31;
    MenuStreamRecord0 record32;
    MenuStreamRecord2 record33;
    MenuStreamRecord1 record34;
    MenuStreamRecord2 record35;
    MenuStreamRecord0 record36;
    MenuStreamRecord2 record37;
    MenuStreamRecord2 record38;
    MenuStreamRecord1 record39;
    MenuStreamRecord2 record40;
    MenuStreamRecord2 record41;
    MenuStreamRecord2 record42;
    MenuStreamRecord2 record43;
    MenuStreamRecord0 record44;
    MenuStreamRecord2 record45;
    MenuStreamRecord2 record46;
    MenuStreamRecord2 record47;
    MenuStreamRecord2 record48;
    MenuStreamRecord1 record49;
    MenuStreamRecord2 record50;
    MenuStreamRecord2 record51;
    MenuStreamRecord2 record52;
    MenuStreamRecord2 record53;
    MenuStreamRecord0 record54;
    MenuStreamRecord1 record55;
    MenuStreamRecord3 record56;
    MenuStreamRecord0 record57;
    MenuStreamRecord2 record58;
    MenuStreamRecord0 record59;
    MenuStreamRecord2 record60;
    MenuStreamRecord1 record61;
    MenuStreamRecord0 record62;
    MenuStreamRecord0 record63;
    MenuStreamRecord0 record64;
    MenuStreamRecord1 record65;
    MenuStreamRecord0 record66;
    MenuStreamRecord1 record67;
    MenuStreamRecord2 record68;
    MenuStreamRecord2 record69;
    MenuStreamRecord2 record70;
    MenuStreamRecord2 record71;
    MenuStreamRecord2 record72;
    MenuStreamRecord3 record73;
    MenuStreamRecord1 record74;
    MenuStreamRecord2 record75;
    MenuStreamRecord2 record76;
    MenuStreamRecord2 record77;
    MenuStreamRecord2 record78;
    MenuStreamRecord0 record79;
    MenuStreamRecord1 record80;
    MenuStreamRecord2 record81;
    MenuStreamRecord0 record82;
    MenuStreamRecord2 record83;
    MenuStreamRecord2 record84;
    MenuStreamRecord3 record85;
    MenuStreamRecord1 record86;
    MenuStreamRecord2 record87;
    MenuStreamRecord2 record88;
    MenuStreamRecord2 record89;
    MenuStreamRecord2 record90;
    MenuStreamRecord3 record91;
    MenuStreamRecord0 record92;
    MenuStreamRecord2 record93;
    MenuStreamRecord2 record94;
    MenuStreamRecord1 record95;
    MenuStreamRecord2 record96;
    MenuStreamRecord2 record97;
    MenuStreamRecord0 record98;
    MenuStreamRecord2 record99;
    MenuStreamRecord2 record100;
    MenuStreamRecord1 record101;
    MenuStreamRecord2 record102;
    MenuStreamRecord2 record103;
    MenuStreamRecord2 record104;
    MenuStreamRecord2 record105;
    MenuStreamRecord0 record106;
    MenuStreamRecord2 record107;
    MenuStreamRecord2 record108;
    MenuStreamRecord2 record109;
    MenuStreamRecord2 record110;
    MenuStreamRecord1 record111;
    MenuStreamRecord2 record112;
    MenuStreamRecord2 record113;
    MenuStreamRecord2 record114;
    MenuStreamRecord2 record115;
    MenuStreamRecord0 record116;
    MenuStreamRecord1 record117;
    MenuStreamRecord3 record118;
    MenuStreamRecord1 record119;
    MenuStreamRecord2 record120;
    MenuStreamRecord0 record121;
    MenuStreamRecord2 record122;
    MenuStreamRecord0 record123;
    MenuStreamRecord2 record124;
    MenuStreamRecord1 record125;
    MenuStreamRecord0 record126;
    MenuStreamRecord0 record127;
    MenuStreamRecord0 record128;
    MenuStreamRecord1 record129;
    MenuStreamRecord0 record130;
    MenuStreamRecord1 record131;
    MenuStreamRecord2 record132;
    MenuStreamRecord2 record133;
    MenuStreamRecord2 record134;
    MenuStreamRecord2 record135;
    MenuStreamRecord2 record136;
    MenuStreamRecord3 record137;
    MenuStreamRecord0 record138;
    MenuStreamRecord2 record139;
    MenuStreamRecord2 record140;
    MenuStreamRecord2 record141;
    MenuStreamRecord2 record142;
    MenuStreamRecord4 record143;
    MenuStreamRecord5 record144;
    MenuStreamRecord2 record145;
    MenuStreamRecord2 record146;
    MenuStreamRecord2 record147;
    MenuStreamRecord2 record148;
    MenuStreamRecord2 record149;
    MenuStreamRecord2 record150;
    MenuStreamRecord2 record151;
    MenuStreamRecord2 record152;
    MenuStreamRecord2 record153;
    MenuStreamRecord2 record154;
    MenuStreamRecord2 record155;
    MenuStreamRecord2 record156;
    MenuStreamRecord2 record157;
    MenuStreamRecord2 record158;
    MenuStreamRecord2 record159;
    MenuStreamRecord2 record160;
    MenuStreamRecord2 record161;
    MenuStreamRecord2 record162;
    MenuStreamRecord2 record163;
    MenuStreamRecord2 record164;
    MenuStreamRecord2 record165;
    MenuStreamRecord2 record166;
    MenuStreamRecord2 record167;
    MenuStreamRecord2 record168;
    MenuStreamRecord4 record169;
    MenuStreamRecord6 record170;
} MenuResourceStreamRecords;
MenuResourceStreamRecords g_frontendMenuResourceStream3 __attribute__((aligned(1))) = {
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
typedef char MenuResourceStreamSize[(sizeof(MenuResourceStreamRecords) == 1734) ? 1 : -1];
#endif
