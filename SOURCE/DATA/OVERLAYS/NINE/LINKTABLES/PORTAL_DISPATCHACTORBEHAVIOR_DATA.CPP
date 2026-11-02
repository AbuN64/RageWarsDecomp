#include "DATA_OVERLAY_SN_RECORDS.H"

#include "TYPES.H"
#if defined(VERSION_US)
struct {
    u8 precedingRecordFragment[7];
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record5;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record6;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record7;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record9;
    struct { u8 opcode; SnLe16 offset; } record10;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record12;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record13;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record14;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record15;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record16;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record17;
    struct { u8 opcode; SnLe16 offset; } record18;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record23;
    struct { u8 opcode; SnLe16 offset; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record25;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record28;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record29;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record32;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record33;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record34;
    struct { u8 opcode; SnLe16 section; } record35;
    struct { u8 opcode; SnLe16 codeSize; u8 code[125]; } record36;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record37;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record38;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record39;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record40;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record41;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record42;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record43;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record44;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record45;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record46;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record47;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record48;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record49;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record50;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record51;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record52;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record53;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record54;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record55;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record56;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record57;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record58;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record59;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record60;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record61;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record62;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record63;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record64;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record65;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record66;
    struct { u8 opcode; SnLe16 section; } record67;
    u8 followingRecordFragment[2];
} k_PortalDispatchactorbehaviorEncodedWordsUs __attribute__((aligned(4))) = {
    { 0x02, 0x00, 0x00, 0x20, 0x80, 0x00, 0x00 },
    { 10, 96, SN_LE16(58), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(62), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(70), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(74), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(76), { 2, SN_LE16(376) } },
    { 52, SN_LE16(96), 3 },
    { 52, SN_LE16(104), 3 },
    { 10, 96, SN_LE16(106), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(164) },
    { 10, 96, SN_LE16(166), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(170), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(220), { 2, SN_LE16(383) } },
    { 52, SN_LE16(228), 3 },
    { 10, 96, SN_LE16(230), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(234), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(244), { 2, SN_LE16(411) } },
    { 50, SN_LE16(256) },
    { 10, 96, SN_LE16(270), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(274), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(282), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(988) } } },
    { 10, 98, SN_LE16(286), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(988) } } },
    { 10, 92, SN_LE16(288), { 2, SN_LE16(376) } },
    { 50, SN_LE16(308) },
    { 10, 92, SN_LE16(316), { 2, SN_LE16(425) } },
    { 52, SN_LE16(324), 6 },
    { 10, 96, SN_LE16(326), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(330), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(344), { 2, SN_LE16(380) } },
    { 52, SN_LE16(352), 2 },
    { 10, 96, SN_LE16(354), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(358), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(430), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1080) } } },
    { 10, 98, SN_LE16(434), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1080) } } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(125), { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 10, 8, SN_LE16(5), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(33156) } } },
    { 10, 8, SN_LE16(9), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(34176) } } },
    { 10, 8, SN_LE16(13), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(34460) } } },
    { 10, 8, SN_LE16(17), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(34648) } } },
    { 10, 8, SN_LE16(21), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(34932) } } },
    { 10, 8, SN_LE16(25), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(35584) } } },
    { 10, 8, SN_LE16(29), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(35592) } } },
    { 10, 8, SN_LE16(33), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(35888) } } },
    { 10, 8, SN_LE16(37), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(36444) } } },
    { 10, 8, SN_LE16(41), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(37004) } } },
    { 10, 8, SN_LE16(45), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(37572) } } },
    { 10, 8, SN_LE16(49), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(37760) } } },
    { 10, 8, SN_LE16(53), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(38044) } } },
    { 10, 8, SN_LE16(57), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(38996) } } },
    { 10, 8, SN_LE16(61), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(39292) } } },
    { 10, 8, SN_LE16(65), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(39804) } } },
    { 10, 8, SN_LE16(69), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(40088) } } },
    { 10, 8, SN_LE16(73), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(39292) } } },
    { 10, 8, SN_LE16(77), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(40644) } } },
    { 10, 8, SN_LE16(81), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(40644) } } },
    { 10, 8, SN_LE16(85), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(40644) } } },
    { 10, 8, SN_LE16(89), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(40668) } } },
    { 10, 8, SN_LE16(93), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(35228) } } },
    { 10, 8, SN_LE16(97), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(40952) } } },
    { 10, 8, SN_LE16(101), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(41236) } } },
    { 10, 8, SN_LE16(105), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(41520) } } },
    { 10, 8, SN_LE16(109), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(41804) } } },
    { 10, 8, SN_LE16(113), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(42088) } } },
    { 10, 8, SN_LE16(117), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(42452) } } },
    { 10, 8, SN_LE16(121), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(42736) } } },
    { 6, SN_LE16(2) },
    { 0x02, 0xA8 }
};
typedef char k_PortalDispatchactorbehaviorEncodedWordsUsSizeCheck[(sizeof(k_PortalDispatchactorbehaviorEncodedWordsUs) == 864) ? 1 : -1];
struct { u8 codeSizeHigh; } k_PortalDispatchactorbehaviorEncodedWordsUsTail = { 1 };
typedef char k_PortalDispatchactorbehaviorEncodedWordsUsTailSizeCheck[(sizeof(k_PortalDispatchactorbehaviorEncodedWordsUsTail) == 1) ? 1 : -1];
#endif
