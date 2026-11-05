#include "data_overlay_sn_records.h"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * The code payload continues in the following function. */
typedef struct SnLineDeltaRecord { u8 opcode; SnLe16 offset; u8 lineDelta; } SnLineDeltaRecord;
typedef struct SnPatchReferencePlusConstantRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } SnPatchReferencePlusConstantRecord;
typedef struct SnOffsetMarkRecord { u8 opcode; SnLe16 offset; } SnOffsetMarkRecord;
typedef struct SnPatchRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } SnPatchRecord;
typedef struct SnSectionSwitchRecord { u8 opcode; SnLe16 section; } SnSectionSwitchRecord;
typedef struct SnCodeBlock46Record { u8 opcode; SnLe16 codeSize; u8 code[46]; } SnCodeBlock46Record;
typedef struct SnCodeSizeRecord { u8 opcode; SnLe16 codeSize; } SnCodeSizeRecord;
typedef struct SnObjectRecords {
    SnLineDeltaRecord record0;
    SnPatchReferencePlusConstantRecord record1;
    SnPatchReferencePlusConstantRecord record2;
    SnPatchReferencePlusConstantRecord record3;
    SnPatchReferencePlusConstantRecord record4;
    SnPatchReferencePlusConstantRecord record5;
    SnPatchReferencePlusConstantRecord record6;
    SnOffsetMarkRecord record7;
    SnPatchReferencePlusConstantRecord record8;
    SnPatchReferencePlusConstantRecord record9;
    SnPatchReferencePlusConstantRecord record10;
    SnPatchReferencePlusConstantRecord record11;
    SnPatchReferencePlusConstantRecord record12;
    SnPatchReferencePlusConstantRecord record13;
    SnOffsetMarkRecord record14;
    SnPatchReferencePlusConstantRecord record15;
    SnPatchReferencePlusConstantRecord record16;
    SnPatchReferencePlusConstantRecord record17;
    SnPatchReferencePlusConstantRecord record18;
    SnOffsetMarkRecord record19;
    SnPatchReferencePlusConstantRecord record20;
    SnPatchReferencePlusConstantRecord record21;
    SnLineDeltaRecord record22;
    SnPatchRecord record23;
    SnOffsetMarkRecord record24;
    SnPatchReferencePlusConstantRecord record25;
    SnPatchReferencePlusConstantRecord record26;
    SnPatchRecord record27;
    SnOffsetMarkRecord record28;
    SnPatchReferencePlusConstantRecord record29;
    SnPatchReferencePlusConstantRecord record30;
    SnPatchRecord record31;
    SnLineDeltaRecord record32;
    SnPatchReferencePlusConstantRecord record33;
    SnPatchReferencePlusConstantRecord record34;
    SnOffsetMarkRecord record35;
    SnPatchReferencePlusConstantRecord record36;
    SnPatchReferencePlusConstantRecord record37;
    SnLineDeltaRecord record38;
    SnPatchReferencePlusConstantRecord record39;
    SnLineDeltaRecord record40;
    SnPatchReferencePlusConstantRecord record41;
    SnPatchReferencePlusConstantRecord record42;
    SnPatchReferencePlusConstantRecord record43;
    SnPatchReferencePlusConstantRecord record44;
    SnPatchReferencePlusConstantRecord record45;
    SnPatchReferencePlusConstantRecord record46;
    SnOffsetMarkRecord record47;
    SnPatchReferencePlusConstantRecord record48;
    SnPatchReferencePlusConstantRecord record49;
    SnPatchReferencePlusConstantRecord record50;
    SnPatchReferencePlusConstantRecord record51;
    SnPatchReferencePlusConstantRecord record52;
    SnPatchReferencePlusConstantRecord record53;
    SnOffsetMarkRecord record54;
    SnPatchReferencePlusConstantRecord record55;
    SnPatchReferencePlusConstantRecord record56;
    SnPatchReferencePlusConstantRecord record57;
    SnPatchReferencePlusConstantRecord record58;
    SnOffsetMarkRecord record59;
    SnPatchReferencePlusConstantRecord record60;
    SnPatchReferencePlusConstantRecord record61;
    SnLineDeltaRecord record62;
    SnPatchReferencePlusConstantRecord record63;
    SnPatchReferencePlusConstantRecord record64;
    SnOffsetMarkRecord record65;
    SnPatchRecord record66;
    SnOffsetMarkRecord record67;
    SnPatchReferencePlusConstantRecord record68;
    SnPatchReferencePlusConstantRecord record69;
    SnPatchRecord record70;
    SnLineDeltaRecord record71;
    SnPatchReferencePlusConstantRecord record72;
    SnLineDeltaRecord record73;
    SnPatchReferencePlusConstantRecord record74;
    SnLineDeltaRecord record75;
    SnPatchRecord record76;
    SnOffsetMarkRecord record77;
    SnPatchReferencePlusConstantRecord record78;
    SnLineDeltaRecord record79;
    SnPatchReferencePlusConstantRecord record80;
    SnPatchReferencePlusConstantRecord record81;
    SnPatchReferencePlusConstantRecord record82;
    SnPatchReferencePlusConstantRecord record83;
    SnPatchReferencePlusConstantRecord record84;
    SnPatchReferencePlusConstantRecord record85;
    SnPatchReferencePlusConstantRecord record86;
    SnPatchReferencePlusConstantRecord record87;
    SnPatchReferencePlusConstantRecord record88;
    SnPatchReferencePlusConstantRecord record89;
    SnPatchReferencePlusConstantRecord record90;
    SnOffsetMarkRecord record91;
    SnPatchReferencePlusConstantRecord record92;
    SnPatchReferencePlusConstantRecord record93;
    SnLineDeltaRecord record94;
    SnPatchReferencePlusConstantRecord record95;
    SnPatchReferencePlusConstantRecord record96;
    SnPatchRecord record97;
    SnLineDeltaRecord record98;
    SnPatchReferencePlusConstantRecord record99;
    SnPatchReferencePlusConstantRecord record100;
    SnPatchRecord record101;
    SnLineDeltaRecord record102;
    SnPatchReferencePlusConstantRecord record103;
    SnPatchReferencePlusConstantRecord record104;
    SnLineDeltaRecord record105;
    SnPatchReferencePlusConstantRecord record106;
    SnLineDeltaRecord record107;
    SnPatchRecord record108;
    SnOffsetMarkRecord record109;
    SnPatchReferencePlusConstantRecord record110;
    SnPatchReferencePlusConstantRecord record111;
    SnOffsetMarkRecord record112;
    SnPatchReferencePlusConstantRecord record113;
    SnPatchReferencePlusConstantRecord record114;
    SnOffsetMarkRecord record115;
    SnPatchReferencePlusConstantRecord record116;
    SnPatchReferencePlusConstantRecord record117;
    SnPatchRecord record118;
    SnOffsetMarkRecord record119;
    SnPatchReferencePlusConstantRecord record120;
    SnLineDeltaRecord record121;
    SnPatchReferencePlusConstantRecord record122;
    SnPatchReferencePlusConstantRecord record123;
    SnPatchReferencePlusConstantRecord record124;
    SnPatchReferencePlusConstantRecord record125;
    SnPatchRecord record126;
    SnOffsetMarkRecord record127;
    SnPatchReferencePlusConstantRecord record128;
    SnLineDeltaRecord record129;
    SnPatchReferencePlusConstantRecord record130;
    SnPatchReferencePlusConstantRecord record131;
    SnOffsetMarkRecord record132;
    SnPatchReferencePlusConstantRecord record133;
    SnLineDeltaRecord record134;
    SnPatchReferencePlusConstantRecord record135;
    SnLineDeltaRecord record136;
    SnPatchReferencePlusConstantRecord record137;
    SnOffsetMarkRecord record138;
    SnLineDeltaRecord record139;
    SnSectionSwitchRecord record140;
    SnCodeBlock46Record record141;
    SnSectionSwitchRecord record142;
    SnCodeSizeRecord record143;
} SnObjectRecords;
SnObjectRecords g_pakInterfaceSnRecords_us_E6A20 __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 3 },
    { 10, 96, SN_LE16(2), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(6), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(14), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(18), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(26), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(30), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(48) },
    { 10, 96, SN_LE16(50), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(54), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(62), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(66), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(74), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(78), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(96) },
    { 10, 96, SN_LE16(98), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(102), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(106), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(124) },
    { 10, 96, SN_LE16(126), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(130), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(144), 2 },
    { 10, 92, SN_LE16(148), { 2, SN_LE16(396) } },
    { 50, SN_LE16(156) },
    { 10, 96, SN_LE16(158), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(162), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(172), { 2, SN_LE16(383) } },
    { 50, SN_LE16(180) },
    { 10, 96, SN_LE16(182), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(186), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(196), { 2, SN_LE16(407) } },
    { 52, SN_LE16(204), 3 },
    { 10, 96, SN_LE16(206), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(210), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(220) },
    { 10, 96, SN_LE16(222), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(226), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(236), 2 },
    { 10, 92, SN_LE16(236), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7164) } } },
    { 52, SN_LE16(244), 3 },
    { 10, 96, SN_LE16(246), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(250), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(258), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(262), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(270), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(274), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(292) },
    { 10, 96, SN_LE16(294), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(298), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(306), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(310), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(318), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(322), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(340) },
    { 10, 96, SN_LE16(342), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(346), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(350), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(354), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(368) },
    { 10, 96, SN_LE16(370), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(374), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(388), 2 },
    { 10, 96, SN_LE16(390), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(394), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(404) },
    { 10, 92, SN_LE16(404), { 2, SN_LE16(402) } },
    { 50, SN_LE16(412) },
    { 10, 96, SN_LE16(414), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(418), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(424), { 2, SN_LE16(408) } },
    { 52, SN_LE16(432), 2 },
    { 10, 92, SN_LE16(436), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7224) } } },
    { 52, SN_LE16(444), 2 },
    { 10, 92, SN_LE16(444), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7164) } } },
    { 52, SN_LE16(452), 4 },
    { 10, 92, SN_LE16(452), { 2, SN_LE16(398) } },
    { 50, SN_LE16(460) },
    { 10, 92, SN_LE16(460), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7164) } } },
    { 52, SN_LE16(468), 4 },
    { 10, 96, SN_LE16(470), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(474), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(478), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(482), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(502), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(506), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(518), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(522), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(538), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(542), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(552), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(6944) } } },
    { 50, SN_LE16(568) },
    { 10, 96, SN_LE16(570), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(574), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(588), 2 },
    { 10, 96, SN_LE16(590), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(594), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(600), { 2, SN_LE16(409) } },
    { 52, SN_LE16(616), 2 },
    { 10, 96, SN_LE16(618), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(622), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(628), { 2, SN_LE16(410) } },
    { 52, SN_LE16(636), 2 },
    { 10, 96, SN_LE16(638), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(642), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(652), 3 },
    { 10, 92, SN_LE16(652), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7164) } } },
    { 52, SN_LE16(660), 3 },
    { 10, 92, SN_LE16(664), { 2, SN_LE16(396) } },
    { 50, SN_LE16(672) },
    { 10, 96, SN_LE16(674), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(678), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(688) },
    { 10, 96, SN_LE16(690), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(694), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(704) },
    { 10, 96, SN_LE16(706), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(710), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(720), { 2, SN_LE16(383) } },
    { 50, SN_LE16(728) },
    { 10, 92, SN_LE16(728), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7164) } } },
    { 52, SN_LE16(736), 4 },
    { 10, 96, SN_LE16(738), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(742), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(750), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 98, SN_LE16(754), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 92, SN_LE16(756), { 2, SN_LE16(376) } },
    { 50, SN_LE16(776) },
    { 10, 92, SN_LE16(776), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7164) } } },
    { 52, SN_LE16(784), 5 },
    { 10, 96, SN_LE16(786), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(790), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(808) },
    { 10, 92, SN_LE16(812), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7224) } } },
    { 52, SN_LE16(820), 8 },
    { 10, 92, SN_LE16(824), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(43152) } } },
    { 52, SN_LE16(832), 4 },
    { 10, 92, SN_LE16(836), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(7224) } } },
    { 50, SN_LE16(844) },
    { 52, SN_LE16(868), 0 },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(46), { 0x6E, 0x55, 0x73, 0x65, 0x72, 0x20, 0x3E, 0x3D, 0x20, 0x30, 0x20, 0x26, 0x26, 0x20, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x20, 0x3C, 0x3D, 0x20, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x5F, 0x4D, 0x41, 0x58, 0x5F, 0x55, 0x53, 0x45, 0x52, 0x53, 0x00 } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(204) },
};
typedef char MenuResourceStreamSize[(sizeof(SnObjectRecords) == 1432) ? 1 : -1];
#endif
