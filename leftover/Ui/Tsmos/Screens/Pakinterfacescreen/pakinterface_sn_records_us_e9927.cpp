#include "data_overlay_sn_records.h"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * The code payload continues in the following function. */
typedef struct SnLineDeltaRecord { u8 opcode; SnLe16 offset; u8 lineDelta; } SnLineDeltaRecord;
typedef struct SnPatchRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } SnPatchRecord;
typedef struct SnPatchReferencePlusConstantRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } SnPatchReferencePlusConstantRecord;
typedef struct SnOffsetMarkRecord { u8 opcode; SnLe16 offset; } SnOffsetMarkRecord;
typedef struct SnSectionSwitchRecord { u8 opcode; SnLe16 section; } SnSectionSwitchRecord;
typedef struct SnCodeBlock96Record { u8 opcode; SnLe16 codeSize; u8 code[96]; } SnCodeBlock96Record;
typedef struct SnCodeSizeRecord { u8 opcode; SnLe16 codeSize; } SnCodeSizeRecord;
typedef struct SnObjectRecords {
    SnLineDeltaRecord record0;
    SnPatchRecord record1;
    SnPatchRecord record2;
    SnLineDeltaRecord record3;
    SnPatchReferencePlusConstantRecord record4;
    SnPatchReferencePlusConstantRecord record5;
    SnOffsetMarkRecord record6;
    SnPatchReferencePlusConstantRecord record7;
    SnPatchReferencePlusConstantRecord record8;
    SnLineDeltaRecord record9;
    SnOffsetMarkRecord record10;
    SnPatchReferencePlusConstantRecord record11;
    SnLineDeltaRecord record12;
    SnPatchRecord record13;
    SnLineDeltaRecord record14;
    SnPatchReferencePlusConstantRecord record15;
    SnLineDeltaRecord record16;
    SnPatchReferencePlusConstantRecord record17;
    SnPatchReferencePlusConstantRecord record18;
    SnOffsetMarkRecord record19;
    SnPatchRecord record20;
    SnOffsetMarkRecord record21;
    SnPatchReferencePlusConstantRecord record22;
    SnLineDeltaRecord record23;
    SnOffsetMarkRecord record24;
    SnPatchReferencePlusConstantRecord record25;
    SnLineDeltaRecord record26;
    SnPatchRecord record27;
    SnOffsetMarkRecord record28;
    SnPatchReferencePlusConstantRecord record29;
    SnLineDeltaRecord record30;
    SnPatchReferencePlusConstantRecord record31;
    SnPatchReferencePlusConstantRecord record32;
    SnOffsetMarkRecord record33;
    SnPatchRecord record34;
    SnOffsetMarkRecord record35;
    SnPatchReferencePlusConstantRecord record36;
    SnLineDeltaRecord record37;
    SnPatchReferencePlusConstantRecord record38;
    SnPatchReferencePlusConstantRecord record39;
    SnPatchReferencePlusConstantRecord record40;
    SnLineDeltaRecord record41;
    SnOffsetMarkRecord record42;
    SnPatchReferencePlusConstantRecord record43;
    SnOffsetMarkRecord record44;
    SnPatchRecord record45;
    SnLineDeltaRecord record46;
    SnPatchReferencePlusConstantRecord record47;
    SnPatchReferencePlusConstantRecord record48;
    SnPatchRecord record49;
    SnOffsetMarkRecord record50;
    SnPatchReferencePlusConstantRecord record51;
    SnPatchReferencePlusConstantRecord record52;
    SnPatchReferencePlusConstantRecord record53;
    SnPatchReferencePlusConstantRecord record54;
    SnPatchRecord record55;
    SnLineDeltaRecord record56;
    SnLineDeltaRecord record57;
    SnOffsetMarkRecord record58;
    SnPatchRecord record59;
    SnPatchReferencePlusConstantRecord record60;
    SnLineDeltaRecord record61;
    SnLineDeltaRecord record62;
    SnOffsetMarkRecord record63;
    SnPatchReferencePlusConstantRecord record64;
    SnOffsetMarkRecord record65;
    SnPatchReferencePlusConstantRecord record66;
    SnPatchReferencePlusConstantRecord record67;
    SnPatchRecord record68;
    SnOffsetMarkRecord record69;
    SnPatchRecord record70;
    SnOffsetMarkRecord record71;
    SnPatchReferencePlusConstantRecord record72;
    SnLineDeltaRecord record73;
    SnPatchReferencePlusConstantRecord record74;
    SnLineDeltaRecord record75;
    SnLineDeltaRecord record76;
    SnPatchReferencePlusConstantRecord record77;
    SnPatchReferencePlusConstantRecord record78;
    SnPatchRecord record79;
    SnOffsetMarkRecord record80;
    SnPatchReferencePlusConstantRecord record81;
    SnPatchReferencePlusConstantRecord record82;
    SnPatchReferencePlusConstantRecord record83;
    SnPatchReferencePlusConstantRecord record84;
    SnPatchRecord record85;
    SnLineDeltaRecord record86;
    SnLineDeltaRecord record87;
    SnOffsetMarkRecord record88;
    SnPatchRecord record89;
    SnPatchReferencePlusConstantRecord record90;
    SnLineDeltaRecord record91;
    SnLineDeltaRecord record92;
    SnOffsetMarkRecord record93;
    SnPatchReferencePlusConstantRecord record94;
    SnOffsetMarkRecord record95;
    SnPatchReferencePlusConstantRecord record96;
    SnPatchReferencePlusConstantRecord record97;
    SnPatchRecord record98;
    SnOffsetMarkRecord record99;
    SnPatchReferencePlusConstantRecord record100;
    SnOffsetMarkRecord record101;
    SnPatchRecord record102;
    SnOffsetMarkRecord record103;
    SnPatchReferencePlusConstantRecord record104;
    SnLineDeltaRecord record105;
    SnPatchRecord record106;
    SnOffsetMarkRecord record107;
    SnPatchReferencePlusConstantRecord record108;
    SnLineDeltaRecord record109;
    SnLineDeltaRecord record110;
    SnPatchReferencePlusConstantRecord record111;
    SnPatchReferencePlusConstantRecord record112;
    SnPatchRecord record113;
    SnOffsetMarkRecord record114;
    SnPatchReferencePlusConstantRecord record115;
    SnPatchReferencePlusConstantRecord record116;
    SnPatchReferencePlusConstantRecord record117;
    SnPatchReferencePlusConstantRecord record118;
    SnPatchRecord record119;
    SnLineDeltaRecord record120;
    SnLineDeltaRecord record121;
    SnOffsetMarkRecord record122;
    SnPatchRecord record123;
    SnPatchReferencePlusConstantRecord record124;
    SnLineDeltaRecord record125;
    SnLineDeltaRecord record126;
    SnOffsetMarkRecord record127;
    SnPatchReferencePlusConstantRecord record128;
    SnOffsetMarkRecord record129;
    SnPatchReferencePlusConstantRecord record130;
    SnPatchReferencePlusConstantRecord record131;
    SnPatchRecord record132;
    SnOffsetMarkRecord record133;
    SnPatchReferencePlusConstantRecord record134;
    SnOffsetMarkRecord record135;
    SnPatchRecord record136;
    SnOffsetMarkRecord record137;
    SnPatchReferencePlusConstantRecord record138;
    SnLineDeltaRecord record139;
    SnPatchRecord record140;
    SnOffsetMarkRecord record141;
    SnPatchReferencePlusConstantRecord record142;
    SnLineDeltaRecord record143;
    SnPatchReferencePlusConstantRecord record144;
    SnLineDeltaRecord record145;
    SnPatchReferencePlusConstantRecord record146;
    SnOffsetMarkRecord record147;
    SnLineDeltaRecord record148;
    SnLineDeltaRecord record149;
    SnLineDeltaRecord record150;
    SnOffsetMarkRecord record151;
    SnLineDeltaRecord record152;
    SnOffsetMarkRecord record153;
    SnPatchReferencePlusConstantRecord record154;
    SnPatchReferencePlusConstantRecord record155;
    SnPatchReferencePlusConstantRecord record156;
    SnPatchReferencePlusConstantRecord record157;
    SnPatchReferencePlusConstantRecord record158;
    SnPatchRecord record159;
    SnLineDeltaRecord record160;
    SnPatchReferencePlusConstantRecord record161;
    SnPatchReferencePlusConstantRecord record162;
    SnPatchReferencePlusConstantRecord record163;
    SnPatchReferencePlusConstantRecord record164;
    SnSectionSwitchRecord record165;
    SnCodeBlock96Record record166;
    SnPatchReferencePlusConstantRecord record167;
    SnPatchReferencePlusConstantRecord record168;
    SnPatchReferencePlusConstantRecord record169;
    SnPatchReferencePlusConstantRecord record170;
    SnPatchReferencePlusConstantRecord record171;
    SnPatchReferencePlusConstantRecord record172;
    SnPatchReferencePlusConstantRecord record173;
    SnPatchReferencePlusConstantRecord record174;
    SnPatchReferencePlusConstantRecord record175;
    SnPatchReferencePlusConstantRecord record176;
    SnPatchReferencePlusConstantRecord record177;
    SnPatchReferencePlusConstantRecord record178;
    SnPatchReferencePlusConstantRecord record179;
    SnPatchReferencePlusConstantRecord record180;
    SnPatchReferencePlusConstantRecord record181;
    SnPatchReferencePlusConstantRecord record182;
    SnPatchReferencePlusConstantRecord record183;
    SnPatchReferencePlusConstantRecord record184;
    SnPatchReferencePlusConstantRecord record185;
    SnPatchReferencePlusConstantRecord record186;
    SnPatchReferencePlusConstantRecord record187;
    SnPatchReferencePlusConstantRecord record188;
    SnPatchReferencePlusConstantRecord record189;
    SnPatchReferencePlusConstantRecord record190;
    SnSectionSwitchRecord record191;
    SnCodeSizeRecord record192;
} SnObjectRecords;
SnObjectRecords g_pakInterfaceSnRecords_us_E9927 __attribute__((aligned(1))) = {
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
typedef char MenuResourceStreamSize[(sizeof(SnObjectRecords) == 1723) ? 1 : -1];
#endif
