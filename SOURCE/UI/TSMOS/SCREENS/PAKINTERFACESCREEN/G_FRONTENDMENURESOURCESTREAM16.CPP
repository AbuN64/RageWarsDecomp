#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * Boundary gap at +0x6D8: code payload continues in following function. */
typedef struct MenuStreamRecord0 { u8 opcode; SnLe16 offset; SnLe32 line; SnLe16 file; } MenuStreamRecord0;
typedef struct MenuStreamRecord1 { u8 opcode; SnLe16 offset; u8 lineDelta; } MenuStreamRecord1;
typedef struct MenuStreamRecord2 { u8 opcode; SnLe16 offset; } MenuStreamRecord2;
typedef struct MenuStreamRecord3 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } MenuStreamRecord3;
typedef struct MenuStreamRecord4 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } MenuStreamRecord4;
typedef struct MenuStreamRecord5 { u8 opcode; SnLe16 offset; SnLe32 line; } MenuStreamRecord5;
typedef struct MenuStreamRecord6 { u8 opcode; SnLe16 section; } MenuStreamRecord6;
typedef struct MenuStreamRecord7 { u8 opcode; SnLe16 codeSize; u8 code[38]; } MenuStreamRecord7;
typedef struct MenuStreamRecord8 { u8 opcode; SnLe16 codeSize; } MenuStreamRecord8;
typedef struct MenuResourceStreamRecords {
    MenuStreamRecord0 record0;
    MenuStreamRecord1 record1;
    MenuStreamRecord2 record2;
    MenuStreamRecord1 record3;
    MenuStreamRecord3 record4;
    MenuStreamRecord3 record5;
    MenuStreamRecord3 record6;
    MenuStreamRecord3 record7;
    MenuStreamRecord3 record8;
    MenuStreamRecord3 record9;
    MenuStreamRecord4 record10;
    MenuStreamRecord1 record11;
    MenuStreamRecord3 record12;
    MenuStreamRecord3 record13;
    MenuStreamRecord4 record14;
    MenuStreamRecord3 record15;
    MenuStreamRecord3 record16;
    MenuStreamRecord2 record17;
    MenuStreamRecord3 record18;
    MenuStreamRecord3 record19;
    MenuStreamRecord3 record20;
    MenuStreamRecord3 record21;
    MenuStreamRecord3 record22;
    MenuStreamRecord3 record23;
    MenuStreamRecord4 record24;
    MenuStreamRecord1 record25;
    MenuStreamRecord3 record26;
    MenuStreamRecord3 record27;
    MenuStreamRecord1 record28;
    MenuStreamRecord3 record29;
    MenuStreamRecord3 record30;
    MenuStreamRecord4 record31;
    MenuStreamRecord1 record32;
    MenuStreamRecord4 record33;
    MenuStreamRecord3 record34;
    MenuStreamRecord3 record35;
    MenuStreamRecord1 record36;
    MenuStreamRecord4 record37;
    MenuStreamRecord2 record38;
    MenuStreamRecord4 record39;
    MenuStreamRecord2 record40;
    MenuStreamRecord4 record41;
    MenuStreamRecord2 record42;
    MenuStreamRecord4 record43;
    MenuStreamRecord1 record44;
    MenuStreamRecord3 record45;
    MenuStreamRecord2 record46;
    MenuStreamRecord3 record47;
    MenuStreamRecord3 record48;
    MenuStreamRecord5 record49;
    MenuStreamRecord3 record50;
    MenuStreamRecord1 record51;
    MenuStreamRecord3 record52;
    MenuStreamRecord3 record53;
    MenuStreamRecord2 record54;
    MenuStreamRecord3 record55;
    MenuStreamRecord3 record56;
    MenuStreamRecord2 record57;
    MenuStreamRecord4 record58;
    MenuStreamRecord3 record59;
    MenuStreamRecord3 record60;
    MenuStreamRecord1 record61;
    MenuStreamRecord3 record62;
    MenuStreamRecord3 record63;
    MenuStreamRecord3 record64;
    MenuStreamRecord3 record65;
    MenuStreamRecord3 record66;
    MenuStreamRecord3 record67;
    MenuStreamRecord2 record68;
    MenuStreamRecord3 record69;
    MenuStreamRecord3 record70;
    MenuStreamRecord3 record71;
    MenuStreamRecord3 record72;
    MenuStreamRecord2 record73;
    MenuStreamRecord3 record74;
    MenuStreamRecord3 record75;
    MenuStreamRecord3 record76;
    MenuStreamRecord3 record77;
    MenuStreamRecord2 record78;
    MenuStreamRecord3 record79;
    MenuStreamRecord3 record80;
    MenuStreamRecord3 record81;
    MenuStreamRecord3 record82;
    MenuStreamRecord1 record83;
    MenuStreamRecord4 record84;
    MenuStreamRecord3 record85;
    MenuStreamRecord3 record86;
    MenuStreamRecord2 record87;
    MenuStreamRecord3 record88;
    MenuStreamRecord3 record89;
    MenuStreamRecord3 record90;
    MenuStreamRecord3 record91;
    MenuStreamRecord3 record92;
    MenuStreamRecord3 record93;
    MenuStreamRecord2 record94;
    MenuStreamRecord3 record95;
    MenuStreamRecord3 record96;
    MenuStreamRecord3 record97;
    MenuStreamRecord3 record98;
    MenuStreamRecord2 record99;
    MenuStreamRecord3 record100;
    MenuStreamRecord3 record101;
    MenuStreamRecord3 record102;
    MenuStreamRecord3 record103;
    MenuStreamRecord2 record104;
    MenuStreamRecord3 record105;
    MenuStreamRecord3 record106;
    MenuStreamRecord3 record107;
    MenuStreamRecord3 record108;
    MenuStreamRecord1 record109;
    MenuStreamRecord4 record110;
    MenuStreamRecord2 record111;
    MenuStreamRecord1 record112;
    MenuStreamRecord4 record113;
    MenuStreamRecord3 record114;
    MenuStreamRecord3 record115;
    MenuStreamRecord1 record116;
    MenuStreamRecord4 record117;
    MenuStreamRecord3 record118;
    MenuStreamRecord3 record119;
    MenuStreamRecord2 record120;
    MenuStreamRecord3 record121;
    MenuStreamRecord3 record122;
    MenuStreamRecord4 record123;
    MenuStreamRecord1 record124;
    MenuStreamRecord4 record125;
    MenuStreamRecord3 record126;
    MenuStreamRecord3 record127;
    MenuStreamRecord2 record128;
    MenuStreamRecord4 record129;
    MenuStreamRecord3 record130;
    MenuStreamRecord3 record131;
    MenuStreamRecord2 record132;
    MenuStreamRecord4 record133;
    MenuStreamRecord3 record134;
    MenuStreamRecord3 record135;
    MenuStreamRecord2 record136;
    MenuStreamRecord4 record137;
    MenuStreamRecord3 record138;
    MenuStreamRecord3 record139;
    MenuStreamRecord1 record140;
    MenuStreamRecord3 record141;
    MenuStreamRecord3 record142;
    MenuStreamRecord3 record143;
    MenuStreamRecord3 record144;
    MenuStreamRecord1 record145;
    MenuStreamRecord3 record146;
    MenuStreamRecord1 record147;
    MenuStreamRecord3 record148;
    MenuStreamRecord3 record149;
    MenuStreamRecord2 record150;
    MenuStreamRecord3 record151;
    MenuStreamRecord3 record152;
    MenuStreamRecord2 record153;
    MenuStreamRecord3 record154;
    MenuStreamRecord3 record155;
    MenuStreamRecord5 record156;
    MenuStreamRecord3 record157;
    MenuStreamRecord1 record158;
    MenuStreamRecord3 record159;
    MenuStreamRecord3 record160;
    MenuStreamRecord3 record161;
    MenuStreamRecord3 record162;
    MenuStreamRecord6 record163;
    MenuStreamRecord7 record164;
    MenuStreamRecord3 record165;
    MenuStreamRecord3 record166;
    MenuStreamRecord3 record167;
    MenuStreamRecord3 record168;
    MenuStreamRecord3 record169;
    MenuStreamRecord3 record170;
    MenuStreamRecord3 record171;
    MenuStreamRecord3 record172;
    MenuStreamRecord6 record173;
    MenuStreamRecord8 record174;
} MenuResourceStreamRecords;
MenuResourceStreamRecords g_frontendMenuResourceStream16 __attribute__((aligned(1))) = {
    { 58, SN_LE16(0), SN_LE32(318), SN_LE16(317) },
    { 52, SN_LE16(0), 0 },
    { 50, SN_LE16(32) },
    { 52, SN_LE16(32), 8 },
    { 10, 96, SN_LE16(34), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(38), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(50), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(54), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(62), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(68) } } },
    { 10, 98, SN_LE16(66), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(68) } } },
    { 10, 92, SN_LE16(68), { 2, SN_LE16(376) } },
    { 52, SN_LE16(88), 2 },
    { 10, 96, SN_LE16(94), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(98), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 92, SN_LE16(104), { 2, SN_LE16(377) } },
    { 10, 96, SN_LE16(114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(118), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(120) },
    { 10, 96, SN_LE16(122), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(126), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(138), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(142), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(150), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(96) } } },
    { 10, 98, SN_LE16(154), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(96) } } },
    { 10, 92, SN_LE16(156), { 2, SN_LE16(376) } },
    { 52, SN_LE16(176), 2 },
    { 10, 96, SN_LE16(178), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(182), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(192), 2 },
    { 10, 96, SN_LE16(194), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(198), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(224), { 2, SN_LE16(378) } },
    { 52, SN_LE16(232), 4 },
    { 10, 92, SN_LE16(240), { 2, SN_LE16(379) } },
    { 10, 96, SN_LE16(250), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(254), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(260), 2 },
    { 10, 92, SN_LE16(272), { 2, SN_LE16(380) } },
    { 50, SN_LE16(280) },
    { 10, 92, SN_LE16(292), { 2, SN_LE16(380) } },
    { 50, SN_LE16(300) },
    { 10, 92, SN_LE16(312), { 2, SN_LE16(380) } },
    { 50, SN_LE16(320) },
    { 10, 92, SN_LE16(332), { 2, SN_LE16(380) } },
    { 52, SN_LE16(340), 3 },
    { 10, 92, SN_LE16(360), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(416) } } },
    { 50, SN_LE16(368) },
    { 10, 96, SN_LE16(370), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(374), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 56, SN_LE16(396), SN_LE32(346) },
    { 10, 92, SN_LE16(408), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(344) } } },
    { 52, SN_LE16(416), 4 },
    { 10, 96, SN_LE16(418), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(422), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(432) },
    { 10, 96, SN_LE16(434), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(438), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(448) },
    { 10, 92, SN_LE16(456), { 2, SN_LE16(381) } },
    { 10, 96, SN_LE16(466), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(470), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(476), 2 },
    { 10, 96, SN_LE16(478), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(482), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(490), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(494), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(502), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(506), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(528) },
    { 10, 96, SN_LE16(530), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(534), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(538), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(542), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(584) },
    { 10, 96, SN_LE16(586), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(590), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(602), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(606), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(628) },
    { 10, 96, SN_LE16(630), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(634), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(642), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(646), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(668), 2 },
    { 10, 92, SN_LE16(676), { 2, SN_LE16(381) } },
    { 10, 96, SN_LE16(686), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(690), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(696) },
    { 10, 96, SN_LE16(698), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(702), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(710), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(714), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(722), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(726), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(748) },
    { 10, 96, SN_LE16(750), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(754), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(758), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(762), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(804) },
    { 10, 96, SN_LE16(806), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(810), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(822), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(826), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(848) },
    { 10, 96, SN_LE16(850), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(854), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(862), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(866), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(888), 4 },
    { 10, 92, SN_LE16(896), { 2, SN_LE16(381) } },
    { 50, SN_LE16(908) },
    { 52, SN_LE16(920), 2 },
    { 10, 92, SN_LE16(928), { 2, SN_LE16(382) } },
    { 10, 96, SN_LE16(938), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(942), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(948), 2 },
    { 10, 92, SN_LE16(956), { 2, SN_LE16(381) } },
    { 10, 96, SN_LE16(966), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(970), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(976) },
    { 10, 96, SN_LE16(978), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(982), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(992), { 2, SN_LE16(383) } },
    { 52, SN_LE16(1000), 3 },
    { 10, 92, SN_LE16(1008), { 2, SN_LE16(381) } },
    { 10, 96, SN_LE16(1018), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1022), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1028) },
    { 10, 92, SN_LE16(1036), { 2, SN_LE16(381) } },
    { 10, 96, SN_LE16(1046), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1050), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1056) },
    { 10, 92, SN_LE16(1064), { 2, SN_LE16(381) } },
    { 10, 96, SN_LE16(1074), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1078), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1084) },
    { 10, 92, SN_LE16(1092), { 2, SN_LE16(381) } },
    { 10, 96, SN_LE16(1102), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1106), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1112), 2 },
    { 10, 96, SN_LE16(1114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1118), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1122), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(1126), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(0) } } },
    { 52, SN_LE16(1132), 2 },
    { 10, 92, SN_LE16(1152), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(1296) } } },
    { 52, SN_LE16(1160), 2 },
    { 10, 96, SN_LE16(1162), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1166), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1200) },
    { 10, 96, SN_LE16(1202), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1206), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1236) },
    { 10, 96, SN_LE16(1238), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1242), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 56, SN_LE16(1276), SN_LE32(383) },
    { 10, 92, SN_LE16(1288), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(1136) } } },
    { 52, SN_LE16(1296), 9 },
    { 10, 96, SN_LE16(1298), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1302), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1334), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(136) } } },
    { 10, 98, SN_LE16(1338), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(136) } } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(38), { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 10, 8, SN_LE16(6), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(1524) } } },
    { 10, 8, SN_LE16(10), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(1644) } } },
    { 10, 8, SN_LE16(14), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2108) } } },
    { 10, 8, SN_LE16(18), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(1580) } } },
    { 10, 8, SN_LE16(22), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(1468) } } },
    { 10, 8, SN_LE16(26), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(1356) } } },
    { 10, 8, SN_LE16(30), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(1412) } } },
    { 10, 8, SN_LE16(34), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(1636) } } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(4760) },
};
typedef char MenuResourceStreamSize[(sizeof(MenuResourceStreamRecords) == 1752) ? 1 : -1];
#endif
