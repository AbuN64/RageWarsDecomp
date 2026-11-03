#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * Boundary gap at +0x598: code payload continues in following function. */
typedef struct MenuStreamRecord0 { u8 opcode; SnLe16 offset; u8 lineDelta; } MenuStreamRecord0;
typedef struct MenuStreamRecord1 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } MenuStreamRecord1;
typedef struct MenuStreamRecord2 { u8 opcode; SnLe16 offset; } MenuStreamRecord2;
typedef struct MenuStreamRecord3 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } MenuStreamRecord3;
typedef struct MenuStreamRecord4 { u8 opcode; SnLe16 section; } MenuStreamRecord4;
typedef struct MenuStreamRecord5 { u8 opcode; SnLe16 codeSize; u8 code[46]; } MenuStreamRecord5;
typedef struct MenuStreamRecord6 { u8 opcode; SnLe16 codeSize; } MenuStreamRecord6;
typedef struct MenuResourceStreamRecords {
    MenuStreamRecord0 record0;
    MenuStreamRecord1 record1;
    MenuStreamRecord1 record2;
    MenuStreamRecord1 record3;
    MenuStreamRecord1 record4;
    MenuStreamRecord1 record5;
    MenuStreamRecord1 record6;
    MenuStreamRecord2 record7;
    MenuStreamRecord1 record8;
    MenuStreamRecord1 record9;
    MenuStreamRecord1 record10;
    MenuStreamRecord1 record11;
    MenuStreamRecord1 record12;
    MenuStreamRecord1 record13;
    MenuStreamRecord2 record14;
    MenuStreamRecord1 record15;
    MenuStreamRecord1 record16;
    MenuStreamRecord1 record17;
    MenuStreamRecord1 record18;
    MenuStreamRecord2 record19;
    MenuStreamRecord1 record20;
    MenuStreamRecord1 record21;
    MenuStreamRecord0 record22;
    MenuStreamRecord3 record23;
    MenuStreamRecord2 record24;
    MenuStreamRecord1 record25;
    MenuStreamRecord1 record26;
    MenuStreamRecord3 record27;
    MenuStreamRecord2 record28;
    MenuStreamRecord1 record29;
    MenuStreamRecord1 record30;
    MenuStreamRecord3 record31;
    MenuStreamRecord0 record32;
    MenuStreamRecord1 record33;
    MenuStreamRecord1 record34;
    MenuStreamRecord2 record35;
    MenuStreamRecord1 record36;
    MenuStreamRecord1 record37;
    MenuStreamRecord0 record38;
    MenuStreamRecord1 record39;
    MenuStreamRecord0 record40;
    MenuStreamRecord1 record41;
    MenuStreamRecord1 record42;
    MenuStreamRecord1 record43;
    MenuStreamRecord1 record44;
    MenuStreamRecord1 record45;
    MenuStreamRecord1 record46;
    MenuStreamRecord2 record47;
    MenuStreamRecord1 record48;
    MenuStreamRecord1 record49;
    MenuStreamRecord1 record50;
    MenuStreamRecord1 record51;
    MenuStreamRecord1 record52;
    MenuStreamRecord1 record53;
    MenuStreamRecord2 record54;
    MenuStreamRecord1 record55;
    MenuStreamRecord1 record56;
    MenuStreamRecord1 record57;
    MenuStreamRecord1 record58;
    MenuStreamRecord2 record59;
    MenuStreamRecord1 record60;
    MenuStreamRecord1 record61;
    MenuStreamRecord0 record62;
    MenuStreamRecord1 record63;
    MenuStreamRecord1 record64;
    MenuStreamRecord2 record65;
    MenuStreamRecord3 record66;
    MenuStreamRecord2 record67;
    MenuStreamRecord1 record68;
    MenuStreamRecord1 record69;
    MenuStreamRecord3 record70;
    MenuStreamRecord0 record71;
    MenuStreamRecord1 record72;
    MenuStreamRecord0 record73;
    MenuStreamRecord1 record74;
    MenuStreamRecord0 record75;
    MenuStreamRecord3 record76;
    MenuStreamRecord2 record77;
    MenuStreamRecord1 record78;
    MenuStreamRecord0 record79;
    MenuStreamRecord1 record80;
    MenuStreamRecord1 record81;
    MenuStreamRecord1 record82;
    MenuStreamRecord1 record83;
    MenuStreamRecord1 record84;
    MenuStreamRecord1 record85;
    MenuStreamRecord1 record86;
    MenuStreamRecord1 record87;
    MenuStreamRecord1 record88;
    MenuStreamRecord1 record89;
    MenuStreamRecord1 record90;
    MenuStreamRecord2 record91;
    MenuStreamRecord1 record92;
    MenuStreamRecord1 record93;
    MenuStreamRecord0 record94;
    MenuStreamRecord1 record95;
    MenuStreamRecord1 record96;
    MenuStreamRecord3 record97;
    MenuStreamRecord0 record98;
    MenuStreamRecord1 record99;
    MenuStreamRecord1 record100;
    MenuStreamRecord3 record101;
    MenuStreamRecord0 record102;
    MenuStreamRecord1 record103;
    MenuStreamRecord1 record104;
    MenuStreamRecord0 record105;
    MenuStreamRecord1 record106;
    MenuStreamRecord0 record107;
    MenuStreamRecord3 record108;
    MenuStreamRecord2 record109;
    MenuStreamRecord1 record110;
    MenuStreamRecord1 record111;
    MenuStreamRecord2 record112;
    MenuStreamRecord1 record113;
    MenuStreamRecord1 record114;
    MenuStreamRecord2 record115;
    MenuStreamRecord1 record116;
    MenuStreamRecord1 record117;
    MenuStreamRecord3 record118;
    MenuStreamRecord2 record119;
    MenuStreamRecord1 record120;
    MenuStreamRecord0 record121;
    MenuStreamRecord1 record122;
    MenuStreamRecord1 record123;
    MenuStreamRecord1 record124;
    MenuStreamRecord1 record125;
    MenuStreamRecord3 record126;
    MenuStreamRecord2 record127;
    MenuStreamRecord1 record128;
    MenuStreamRecord0 record129;
    MenuStreamRecord1 record130;
    MenuStreamRecord1 record131;
    MenuStreamRecord2 record132;
    MenuStreamRecord1 record133;
    MenuStreamRecord0 record134;
    MenuStreamRecord1 record135;
    MenuStreamRecord0 record136;
    MenuStreamRecord1 record137;
    MenuStreamRecord2 record138;
    MenuStreamRecord0 record139;
    MenuStreamRecord4 record140;
    MenuStreamRecord5 record141;
    MenuStreamRecord4 record142;
    MenuStreamRecord6 record143;
} MenuResourceStreamRecords;
MenuResourceStreamRecords g_frontendMenuResourceStream5 __attribute__((aligned(1))) = {
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
typedef char MenuResourceStreamSize[(sizeof(MenuResourceStreamRecords) == 1432) ? 1 : -1];
#endif
