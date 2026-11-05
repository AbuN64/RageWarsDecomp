#include "data_overlay_sn_records.h"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * The code payload continues in the following function. */
typedef struct SnLineFileRecord { u8 opcode; SnLe16 offset; SnLe32 line; SnLe16 file; } SnLineFileRecord;
typedef struct SnLineDeltaRecord { u8 opcode; SnLe16 offset; u8 lineDelta; } SnLineDeltaRecord;
typedef struct SnOffsetMarkRecord { u8 opcode; SnLe16 offset; } SnOffsetMarkRecord;
typedef struct SnPatchReferencePlusConstantRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } SnPatchReferencePlusConstantRecord;
typedef struct SnPatchRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } SnPatchRecord;
typedef struct SnLineNumberRecord { u8 opcode; SnLe16 offset; SnLe32 line; } SnLineNumberRecord;
typedef struct SnSectionSwitchRecord { u8 opcode; SnLe16 section; } SnSectionSwitchRecord;
typedef struct SnCodeBlock38Record { u8 opcode; SnLe16 codeSize; u8 code[38]; } SnCodeBlock38Record;
typedef struct SnCodeSizeRecord { u8 opcode; SnLe16 codeSize; } SnCodeSizeRecord;
typedef struct SnObjectRecords {
    SnLineFileRecord record0;
    SnLineDeltaRecord record1;
    SnOffsetMarkRecord record2;
    SnLineDeltaRecord record3;
    SnPatchReferencePlusConstantRecord record4;
    SnPatchReferencePlusConstantRecord record5;
    SnPatchReferencePlusConstantRecord record6;
    SnPatchReferencePlusConstantRecord record7;
    SnPatchReferencePlusConstantRecord record8;
    SnPatchReferencePlusConstantRecord record9;
    SnPatchRecord record10;
    SnLineDeltaRecord record11;
    SnPatchReferencePlusConstantRecord record12;
    SnPatchReferencePlusConstantRecord record13;
    SnPatchRecord record14;
    SnPatchReferencePlusConstantRecord record15;
    SnPatchReferencePlusConstantRecord record16;
    SnOffsetMarkRecord record17;
    SnPatchReferencePlusConstantRecord record18;
    SnPatchReferencePlusConstantRecord record19;
    SnPatchReferencePlusConstantRecord record20;
    SnPatchReferencePlusConstantRecord record21;
    SnPatchReferencePlusConstantRecord record22;
    SnPatchReferencePlusConstantRecord record23;
    SnPatchRecord record24;
    SnLineDeltaRecord record25;
    SnPatchReferencePlusConstantRecord record26;
    SnPatchReferencePlusConstantRecord record27;
    SnLineDeltaRecord record28;
    SnPatchReferencePlusConstantRecord record29;
    SnPatchReferencePlusConstantRecord record30;
    SnPatchRecord record31;
    SnLineDeltaRecord record32;
    SnPatchRecord record33;
    SnPatchReferencePlusConstantRecord record34;
    SnPatchReferencePlusConstantRecord record35;
    SnLineDeltaRecord record36;
    SnPatchRecord record37;
    SnOffsetMarkRecord record38;
    SnPatchRecord record39;
    SnOffsetMarkRecord record40;
    SnPatchRecord record41;
    SnOffsetMarkRecord record42;
    SnPatchRecord record43;
    SnLineDeltaRecord record44;
    SnPatchReferencePlusConstantRecord record45;
    SnOffsetMarkRecord record46;
    SnPatchReferencePlusConstantRecord record47;
    SnPatchReferencePlusConstantRecord record48;
    SnLineNumberRecord record49;
    SnPatchReferencePlusConstantRecord record50;
    SnLineDeltaRecord record51;
    SnPatchReferencePlusConstantRecord record52;
    SnPatchReferencePlusConstantRecord record53;
    SnOffsetMarkRecord record54;
    SnPatchReferencePlusConstantRecord record55;
    SnPatchReferencePlusConstantRecord record56;
    SnOffsetMarkRecord record57;
    SnPatchRecord record58;
    SnPatchReferencePlusConstantRecord record59;
    SnPatchReferencePlusConstantRecord record60;
    SnLineDeltaRecord record61;
    SnPatchReferencePlusConstantRecord record62;
    SnPatchReferencePlusConstantRecord record63;
    SnPatchReferencePlusConstantRecord record64;
    SnPatchReferencePlusConstantRecord record65;
    SnPatchReferencePlusConstantRecord record66;
    SnPatchReferencePlusConstantRecord record67;
    SnOffsetMarkRecord record68;
    SnPatchReferencePlusConstantRecord record69;
    SnPatchReferencePlusConstantRecord record70;
    SnPatchReferencePlusConstantRecord record71;
    SnPatchReferencePlusConstantRecord record72;
    SnOffsetMarkRecord record73;
    SnPatchReferencePlusConstantRecord record74;
    SnPatchReferencePlusConstantRecord record75;
    SnPatchReferencePlusConstantRecord record76;
    SnPatchReferencePlusConstantRecord record77;
    SnOffsetMarkRecord record78;
    SnPatchReferencePlusConstantRecord record79;
    SnPatchReferencePlusConstantRecord record80;
    SnPatchReferencePlusConstantRecord record81;
    SnPatchReferencePlusConstantRecord record82;
    SnLineDeltaRecord record83;
    SnPatchRecord record84;
    SnPatchReferencePlusConstantRecord record85;
    SnPatchReferencePlusConstantRecord record86;
    SnOffsetMarkRecord record87;
    SnPatchReferencePlusConstantRecord record88;
    SnPatchReferencePlusConstantRecord record89;
    SnPatchReferencePlusConstantRecord record90;
    SnPatchReferencePlusConstantRecord record91;
    SnPatchReferencePlusConstantRecord record92;
    SnPatchReferencePlusConstantRecord record93;
    SnOffsetMarkRecord record94;
    SnPatchReferencePlusConstantRecord record95;
    SnPatchReferencePlusConstantRecord record96;
    SnPatchReferencePlusConstantRecord record97;
    SnPatchReferencePlusConstantRecord record98;
    SnOffsetMarkRecord record99;
    SnPatchReferencePlusConstantRecord record100;
    SnPatchReferencePlusConstantRecord record101;
    SnPatchReferencePlusConstantRecord record102;
    SnPatchReferencePlusConstantRecord record103;
    SnOffsetMarkRecord record104;
    SnPatchReferencePlusConstantRecord record105;
    SnPatchReferencePlusConstantRecord record106;
    SnPatchReferencePlusConstantRecord record107;
    SnPatchReferencePlusConstantRecord record108;
    SnLineDeltaRecord record109;
    SnPatchRecord record110;
    SnOffsetMarkRecord record111;
    SnLineDeltaRecord record112;
    SnPatchRecord record113;
    SnPatchReferencePlusConstantRecord record114;
    SnPatchReferencePlusConstantRecord record115;
    SnLineDeltaRecord record116;
    SnPatchRecord record117;
    SnPatchReferencePlusConstantRecord record118;
    SnPatchReferencePlusConstantRecord record119;
    SnOffsetMarkRecord record120;
    SnPatchReferencePlusConstantRecord record121;
    SnPatchReferencePlusConstantRecord record122;
    SnPatchRecord record123;
    SnLineDeltaRecord record124;
    SnPatchRecord record125;
    SnPatchReferencePlusConstantRecord record126;
    SnPatchReferencePlusConstantRecord record127;
    SnOffsetMarkRecord record128;
    SnPatchRecord record129;
    SnPatchReferencePlusConstantRecord record130;
    SnPatchReferencePlusConstantRecord record131;
    SnOffsetMarkRecord record132;
    SnPatchRecord record133;
    SnPatchReferencePlusConstantRecord record134;
    SnPatchReferencePlusConstantRecord record135;
    SnOffsetMarkRecord record136;
    SnPatchRecord record137;
    SnPatchReferencePlusConstantRecord record138;
    SnPatchReferencePlusConstantRecord record139;
    SnLineDeltaRecord record140;
    SnPatchReferencePlusConstantRecord record141;
    SnPatchReferencePlusConstantRecord record142;
    SnPatchReferencePlusConstantRecord record143;
    SnPatchReferencePlusConstantRecord record144;
    SnLineDeltaRecord record145;
    SnPatchReferencePlusConstantRecord record146;
    SnLineDeltaRecord record147;
    SnPatchReferencePlusConstantRecord record148;
    SnPatchReferencePlusConstantRecord record149;
    SnOffsetMarkRecord record150;
    SnPatchReferencePlusConstantRecord record151;
    SnPatchReferencePlusConstantRecord record152;
    SnOffsetMarkRecord record153;
    SnPatchReferencePlusConstantRecord record154;
    SnPatchReferencePlusConstantRecord record155;
    SnLineNumberRecord record156;
    SnPatchReferencePlusConstantRecord record157;
    SnLineDeltaRecord record158;
    SnPatchReferencePlusConstantRecord record159;
    SnPatchReferencePlusConstantRecord record160;
    SnPatchReferencePlusConstantRecord record161;
    SnPatchReferencePlusConstantRecord record162;
    SnSectionSwitchRecord record163;
    SnCodeBlock38Record record164;
    SnPatchReferencePlusConstantRecord record165;
    SnPatchReferencePlusConstantRecord record166;
    SnPatchReferencePlusConstantRecord record167;
    SnPatchReferencePlusConstantRecord record168;
    SnPatchReferencePlusConstantRecord record169;
    SnPatchReferencePlusConstantRecord record170;
    SnPatchReferencePlusConstantRecord record171;
    SnPatchReferencePlusConstantRecord record172;
    SnSectionSwitchRecord record173;
    SnCodeSizeRecord record174;
} SnObjectRecords;
SnObjectRecords g_pakInterfaceSnRecords_us_E3D3B __attribute__((aligned(1))) = {
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
typedef char MenuResourceStreamSize[(sizeof(SnObjectRecords) == 1752) ? 1 : -1];
#endif
