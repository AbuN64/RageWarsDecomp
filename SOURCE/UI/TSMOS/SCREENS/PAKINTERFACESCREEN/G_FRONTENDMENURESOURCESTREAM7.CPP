#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * Boundary gap at +0x6BB: code payload continues in following function. */
typedef struct MenuStreamRecord0 { u8 opcode; SnLe16 offset; u8 lineDelta; } MenuStreamRecord0;
typedef struct MenuStreamRecord1 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } MenuStreamRecord1;
typedef struct MenuStreamRecord2 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } MenuStreamRecord2;
typedef struct MenuStreamRecord3 { u8 opcode; SnLe16 offset; } MenuStreamRecord3;
typedef struct MenuStreamRecord4 { u8 opcode; SnLe16 section; } MenuStreamRecord4;
typedef struct MenuStreamRecord5 { u8 opcode; SnLe16 codeSize; u8 code[96]; } MenuStreamRecord5;
typedef struct MenuStreamRecord6 { u8 opcode; SnLe16 codeSize; } MenuStreamRecord6;
typedef struct MenuResourceStreamRecords {
    MenuStreamRecord0 record0;
    MenuStreamRecord1 record1;
    MenuStreamRecord1 record2;
    MenuStreamRecord0 record3;
    MenuStreamRecord2 record4;
    MenuStreamRecord2 record5;
    MenuStreamRecord3 record6;
    MenuStreamRecord2 record7;
    MenuStreamRecord2 record8;
    MenuStreamRecord0 record9;
    MenuStreamRecord3 record10;
    MenuStreamRecord2 record11;
    MenuStreamRecord0 record12;
    MenuStreamRecord1 record13;
    MenuStreamRecord0 record14;
    MenuStreamRecord2 record15;
    MenuStreamRecord0 record16;
    MenuStreamRecord2 record17;
    MenuStreamRecord2 record18;
    MenuStreamRecord3 record19;
    MenuStreamRecord1 record20;
    MenuStreamRecord3 record21;
    MenuStreamRecord2 record22;
    MenuStreamRecord0 record23;
    MenuStreamRecord3 record24;
    MenuStreamRecord2 record25;
    MenuStreamRecord0 record26;
    MenuStreamRecord1 record27;
    MenuStreamRecord3 record28;
    MenuStreamRecord2 record29;
    MenuStreamRecord0 record30;
    MenuStreamRecord2 record31;
    MenuStreamRecord2 record32;
    MenuStreamRecord3 record33;
    MenuStreamRecord1 record34;
    MenuStreamRecord3 record35;
    MenuStreamRecord2 record36;
    MenuStreamRecord0 record37;
    MenuStreamRecord2 record38;
    MenuStreamRecord2 record39;
    MenuStreamRecord2 record40;
    MenuStreamRecord0 record41;
    MenuStreamRecord3 record42;
    MenuStreamRecord2 record43;
    MenuStreamRecord3 record44;
    MenuStreamRecord1 record45;
    MenuStreamRecord0 record46;
    MenuStreamRecord2 record47;
    MenuStreamRecord2 record48;
    MenuStreamRecord1 record49;
    MenuStreamRecord3 record50;
    MenuStreamRecord2 record51;
    MenuStreamRecord2 record52;
    MenuStreamRecord2 record53;
    MenuStreamRecord2 record54;
    MenuStreamRecord1 record55;
    MenuStreamRecord0 record56;
    MenuStreamRecord0 record57;
    MenuStreamRecord3 record58;
    MenuStreamRecord1 record59;
    MenuStreamRecord2 record60;
    MenuStreamRecord0 record61;
    MenuStreamRecord0 record62;
    MenuStreamRecord3 record63;
    MenuStreamRecord2 record64;
    MenuStreamRecord3 record65;
    MenuStreamRecord2 record66;
    MenuStreamRecord2 record67;
    MenuStreamRecord1 record68;
    MenuStreamRecord3 record69;
    MenuStreamRecord1 record70;
    MenuStreamRecord3 record71;
    MenuStreamRecord2 record72;
    MenuStreamRecord0 record73;
    MenuStreamRecord2 record74;
    MenuStreamRecord0 record75;
    MenuStreamRecord0 record76;
    MenuStreamRecord2 record77;
    MenuStreamRecord2 record78;
    MenuStreamRecord1 record79;
    MenuStreamRecord3 record80;
    MenuStreamRecord2 record81;
    MenuStreamRecord2 record82;
    MenuStreamRecord2 record83;
    MenuStreamRecord2 record84;
    MenuStreamRecord1 record85;
    MenuStreamRecord0 record86;
    MenuStreamRecord0 record87;
    MenuStreamRecord3 record88;
    MenuStreamRecord1 record89;
    MenuStreamRecord2 record90;
    MenuStreamRecord0 record91;
    MenuStreamRecord0 record92;
    MenuStreamRecord3 record93;
    MenuStreamRecord2 record94;
    MenuStreamRecord3 record95;
    MenuStreamRecord2 record96;
    MenuStreamRecord2 record97;
    MenuStreamRecord1 record98;
    MenuStreamRecord3 record99;
    MenuStreamRecord2 record100;
    MenuStreamRecord3 record101;
    MenuStreamRecord1 record102;
    MenuStreamRecord3 record103;
    MenuStreamRecord2 record104;
    MenuStreamRecord0 record105;
    MenuStreamRecord1 record106;
    MenuStreamRecord3 record107;
    MenuStreamRecord2 record108;
    MenuStreamRecord0 record109;
    MenuStreamRecord0 record110;
    MenuStreamRecord2 record111;
    MenuStreamRecord2 record112;
    MenuStreamRecord1 record113;
    MenuStreamRecord3 record114;
    MenuStreamRecord2 record115;
    MenuStreamRecord2 record116;
    MenuStreamRecord2 record117;
    MenuStreamRecord2 record118;
    MenuStreamRecord1 record119;
    MenuStreamRecord0 record120;
    MenuStreamRecord0 record121;
    MenuStreamRecord3 record122;
    MenuStreamRecord1 record123;
    MenuStreamRecord2 record124;
    MenuStreamRecord0 record125;
    MenuStreamRecord0 record126;
    MenuStreamRecord3 record127;
    MenuStreamRecord2 record128;
    MenuStreamRecord3 record129;
    MenuStreamRecord2 record130;
    MenuStreamRecord2 record131;
    MenuStreamRecord1 record132;
    MenuStreamRecord3 record133;
    MenuStreamRecord2 record134;
    MenuStreamRecord3 record135;
    MenuStreamRecord1 record136;
    MenuStreamRecord3 record137;
    MenuStreamRecord2 record138;
    MenuStreamRecord0 record139;
    MenuStreamRecord1 record140;
    MenuStreamRecord3 record141;
    MenuStreamRecord2 record142;
    MenuStreamRecord0 record143;
    MenuStreamRecord2 record144;
    MenuStreamRecord0 record145;
    MenuStreamRecord2 record146;
    MenuStreamRecord3 record147;
    MenuStreamRecord0 record148;
    MenuStreamRecord0 record149;
    MenuStreamRecord0 record150;
    MenuStreamRecord3 record151;
    MenuStreamRecord0 record152;
    MenuStreamRecord3 record153;
    MenuStreamRecord2 record154;
    MenuStreamRecord2 record155;
    MenuStreamRecord2 record156;
    MenuStreamRecord2 record157;
    MenuStreamRecord2 record158;
    MenuStreamRecord1 record159;
    MenuStreamRecord0 record160;
    MenuStreamRecord2 record161;
    MenuStreamRecord2 record162;
    MenuStreamRecord2 record163;
    MenuStreamRecord2 record164;
    MenuStreamRecord4 record165;
    MenuStreamRecord5 record166;
    MenuStreamRecord2 record167;
    MenuStreamRecord2 record168;
    MenuStreamRecord2 record169;
    MenuStreamRecord2 record170;
    MenuStreamRecord2 record171;
    MenuStreamRecord2 record172;
    MenuStreamRecord2 record173;
    MenuStreamRecord2 record174;
    MenuStreamRecord2 record175;
    MenuStreamRecord2 record176;
    MenuStreamRecord2 record177;
    MenuStreamRecord2 record178;
    MenuStreamRecord2 record179;
    MenuStreamRecord2 record180;
    MenuStreamRecord2 record181;
    MenuStreamRecord2 record182;
    MenuStreamRecord2 record183;
    MenuStreamRecord2 record184;
    MenuStreamRecord2 record185;
    MenuStreamRecord2 record186;
    MenuStreamRecord2 record187;
    MenuStreamRecord2 record188;
    MenuStreamRecord2 record189;
    MenuStreamRecord2 record190;
    MenuStreamRecord4 record191;
    MenuStreamRecord6 record192;
} MenuResourceStreamRecords;
MenuResourceStreamRecords g_frontendMenuResourceStream7 __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 3 },
    { 10, 92, SN_LE16(4), { 2, SN_LE16(412) } },
    { 10, 92, SN_LE16(16), { 2, SN_LE16(413) } },
    { 52, SN_LE16(36), 2 },
    { 10, 96, SN_LE16(38), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(42), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(88) },
    { 10, 96, SN_LE16(90), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(94), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(144), 4 },
    { 50, SN_LE16(160) },
    { 10, 92, SN_LE16(164), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13628) } } },
    { 52, SN_LE16(172), 3 },
    { 10, 92, SN_LE16(172), { 2, SN_LE16(402) } },
    { 52, SN_LE16(180), 3 },
    { 10, 92, SN_LE16(184), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(68848) } } },
    { 52, SN_LE16(192), 2 },
    { 10, 96, SN_LE16(194), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(198), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(244) },
    { 10, 92, SN_LE16(248), { 2, SN_LE16(396) } },
    { 50, SN_LE16(256) },
    { 10, 92, SN_LE16(256), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13616) } } },
    { 52, SN_LE16(264), 4 },
    { 50, SN_LE16(280) },
    { 10, 92, SN_LE16(284), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13628) } } },
    { 52, SN_LE16(292), 2 },
    { 10, 92, SN_LE16(292), { 2, SN_LE16(402) } },
    { 50, SN_LE16(300) },
    { 10, 92, SN_LE16(308), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(57944) } } },
    { 52, SN_LE16(316), 2 },
    { 10, 96, SN_LE16(318), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(322), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(344) },
    { 10, 92, SN_LE16(348), { 2, SN_LE16(396) } },
    { 50, SN_LE16(356) },
    { 10, 92, SN_LE16(356), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13616) } } },
    { 52, SN_LE16(364), 3 },
    { 10, 96, SN_LE16(366), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(370), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(428), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13112) } } },
    { 52, SN_LE16(436), 5 },
    { 50, SN_LE16(452) },
    { 10, 92, SN_LE16(456), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13628) } } },
    { 50, SN_LE16(464) },
    { 10, 92, SN_LE16(464), { 2, SN_LE16(402) } },
    { 52, SN_LE16(472), 3 },
    { 10, 96, SN_LE16(474), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(478), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(488), { 2, SN_LE16(411) } },
    { 50, SN_LE16(500) },
    { 10, 96, SN_LE16(514), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(518), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(526), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 98, SN_LE16(530), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 92, SN_LE16(532), { 2, SN_LE16(376) } },
    { 52, SN_LE16(552), 4 },
    { 52, SN_LE16(560), 2 },
    { 50, SN_LE16(572) },
    { 10, 92, SN_LE16(576), { 2, SN_LE16(414) } },
    { 10, 92, SN_LE16(592), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13064) } } },
    { 52, SN_LE16(600), 2 },
    { 52, SN_LE16(608), 2 },
    { 50, SN_LE16(620) },
    { 10, 92, SN_LE16(620), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13008) } } },
    { 50, SN_LE16(628) },
    { 10, 96, SN_LE16(630), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(634), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(648), { 2, SN_LE16(415) } },
    { 50, SN_LE16(656) },
    { 10, 92, SN_LE16(660), { 2, SN_LE16(396) } },
    { 50, SN_LE16(668) },
    { 10, 92, SN_LE16(668), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13112) } } },
    { 52, SN_LE16(676), 2 },
    { 10, 92, SN_LE16(676), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13616) } } },
    { 52, SN_LE16(684), 87 },
    { 52, SN_LE16(700), 3 },
    { 10, 96, SN_LE16(702), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(706), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(716), { 2, SN_LE16(411) } },
    { 50, SN_LE16(728) },
    { 10, 96, SN_LE16(742), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(746), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(754), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 98, SN_LE16(758), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 92, SN_LE16(760), { 2, SN_LE16(376) } },
    { 52, SN_LE16(780), 4 },
    { 52, SN_LE16(788), 2 },
    { 50, SN_LE16(800) },
    { 10, 92, SN_LE16(804), { 2, SN_LE16(414) } },
    { 10, 92, SN_LE16(820), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13292) } } },
    { 52, SN_LE16(828), 2 },
    { 52, SN_LE16(836), 2 },
    { 50, SN_LE16(848) },
    { 10, 92, SN_LE16(848), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13236) } } },
    { 50, SN_LE16(856) },
    { 10, 96, SN_LE16(858), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(862), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(876), { 2, SN_LE16(415) } },
    { 50, SN_LE16(884) },
    { 10, 92, SN_LE16(888), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52984) } } },
    { 50, SN_LE16(896) },
    { 10, 92, SN_LE16(896), { 2, SN_LE16(402) } },
    { 50, SN_LE16(904) },
    { 10, 92, SN_LE16(904), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13356) } } },
    { 52, SN_LE16(912), 2 },
    { 10, 92, SN_LE16(912), { 2, SN_LE16(402) } },
    { 50, SN_LE16(920) },
    { 10, 92, SN_LE16(920), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13616) } } },
    { 52, SN_LE16(928), 3 },
    { 52, SN_LE16(944), 3 },
    { 10, 96, SN_LE16(946), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(950), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(960), { 2, SN_LE16(411) } },
    { 50, SN_LE16(972) },
    { 10, 96, SN_LE16(986), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(990), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(998), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 98, SN_LE16(1002), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 92, SN_LE16(1004), { 2, SN_LE16(376) } },
    { 52, SN_LE16(1024), 4 },
    { 52, SN_LE16(1032), 2 },
    { 50, SN_LE16(1044) },
    { 10, 92, SN_LE16(1048), { 2, SN_LE16(414) } },
    { 10, 92, SN_LE16(1064), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13536) } } },
    { 52, SN_LE16(1072), 2 },
    { 52, SN_LE16(1080), 2 },
    { 50, SN_LE16(1092) },
    { 10, 92, SN_LE16(1092), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13480) } } },
    { 50, SN_LE16(1100) },
    { 10, 96, SN_LE16(1102), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1106), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1120), { 2, SN_LE16(415) } },
    { 50, SN_LE16(1128) },
    { 10, 92, SN_LE16(1132), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53760) } } },
    { 50, SN_LE16(1140) },
    { 10, 92, SN_LE16(1140), { 2, SN_LE16(402) } },
    { 50, SN_LE16(1148) },
    { 10, 92, SN_LE16(1148), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13600) } } },
    { 52, SN_LE16(1156), 2 },
    { 10, 92, SN_LE16(1156), { 2, SN_LE16(402) } },
    { 50, SN_LE16(1164) },
    { 10, 92, SN_LE16(1164), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13616) } } },
    { 52, SN_LE16(1172), 10 },
    { 10, 92, SN_LE16(1172), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13616) } } },
    { 52, SN_LE16(1180), 2 },
    { 10, 92, SN_LE16(1184), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13628) } } },
    { 50, SN_LE16(1192) },
    { 52, SN_LE16(1220), 0 },
    { 52, SN_LE16(1220), 4 },
    { 52, SN_LE16(1220), 0 },
    { 50, SN_LE16(1256) },
    { 52, SN_LE16(1256), 10 },
    { 50, SN_LE16(1268) },
    { 10, 92, SN_LE16(1296), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13780) } } },
    { 10, 96, SN_LE16(1306), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(1310), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(1318), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 98, SN_LE16(1322), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(212) } } },
    { 10, 92, SN_LE16(1324), { 2, SN_LE16(376) } },
    { 52, SN_LE16(1344), 4 },
    { 10, 96, SN_LE16(1346), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1350), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1418), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(408) } } },
    { 10, 98, SN_LE16(1422), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(408) } } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(96), { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 10, 8, SN_LE16(0), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(14144) } } },
    { 10, 8, SN_LE16(4), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(8), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(12), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(16), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(20), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(24), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(28), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(32), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(13876) } } },
    { 10, 8, SN_LE16(36), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(14244) } } },
    { 10, 8, SN_LE16(40), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(44), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(48), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(52), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(56), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(60), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(64), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(68), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(72), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(14564) } } },
    { 10, 8, SN_LE16(76), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(80), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(84), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(88), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(15052) } } },
    { 10, 8, SN_LE16(92), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(14808) } } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(1224) },
};
typedef char MenuResourceStreamSize[(sizeof(MenuResourceStreamRecords) == 1723) ? 1 : -1];
#endif
