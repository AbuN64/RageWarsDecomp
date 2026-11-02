#include "DATA_OVERLAY_SN_RECORDS.H"

#include "TYPES.H"
#if defined(VERSION_US)
struct {
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record0;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record3;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record6;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record7;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record8;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record9;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record10;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record11;
    struct { u8 opcode; SnLe16 offset; } record12;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record13;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record14;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record15;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record16;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record17;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record18;
    struct { u8 opcode; SnLe16 offset; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record23;
    struct { u8 opcode; SnLe16 offset; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record25;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record28;
    struct { u8 opcode; SnLe16 offset; } record29;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record30;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record31;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record32;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record33;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record34;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record35;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record36;
    struct { u8 opcode; SnLe16 offset; } record37;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record38;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record39;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record40;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record41;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record42;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record43;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record44;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record45;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record46;
    struct { u8 opcode; SnLe16 offset; } record47;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record48;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record49;
    struct { u8 opcode; SnLe16 offset; } record50;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record51;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record52;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record53;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record54;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record55;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record56;
    struct { u8 opcode; SnLe16 offset; } record57;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record58;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record59;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record60;
    struct { u8 opcode; SnLe16 offset; } record61;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record62;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record63;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record64;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record65;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record66;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record67;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record68;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record69;
    struct { u8 opcode; SnLe16 offset; } record70;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record71;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record72;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record73;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record74;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record75;
    struct { u8 opcode; SnLe16 offset; } record76;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record77;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record78;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record79;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record80;
    struct { u8 opcode; SnLe16 offset; } record81;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record82;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record83;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record84;
    struct { u8 opcode; SnLe16 offset; } record85;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record86;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record87;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record88;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record89;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record90;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record91;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record92;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record93;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record94;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record95;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record96;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record97;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record98;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record99;
    struct { u8 opcode; SnLe16 offset; } record100;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record101;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record102;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record103;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record104;
    struct { u8 opcode; SnLe16 offset; } record105;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record106;
    struct { u8 opcode; SnLe16 section; } record107;
    struct { u8 opcode; SnLe16 codeSize; u8 code[408]; } record108;
    struct { u8 opcode; SnLe16 section; } record109;
    struct { u8 opcode; SnLe16 codeSize; } record110;
} k_PortalAfterFindEmptyPlayerDataSlot __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 6 },
    { 10, 92, SN_LE16(0), { 2, SN_LE16(433) } },
    { 10, 96, SN_LE16(10), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(14), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(144), 11 },
    { 10, 96, SN_LE16(146), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(150), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(200), 6 },
    { 10, 92, SN_LE16(200), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47408) } } },
    { 52, SN_LE16(208), 3 },
    { 10, 96, SN_LE16(210), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(214), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(264) },
    { 10, 92, SN_LE16(264), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47408) } } },
    { 52, SN_LE16(272), 3 },
    { 10, 96, SN_LE16(274), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(278), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(322), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(326), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(376) },
    { 10, 92, SN_LE16(376), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47408) } } },
    { 52, SN_LE16(384), 4 },
    { 10, 96, SN_LE16(386), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(390), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(440) },
    { 10, 92, SN_LE16(440), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47408) } } },
    { 52, SN_LE16(448), 4 },
    { 10, 96, SN_LE16(450), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(454), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(504) },
    { 10, 92, SN_LE16(504), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47408) } } },
    { 52, SN_LE16(512), 3 },
    { 10, 96, SN_LE16(514), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(518), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(526), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 98, SN_LE16(530), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 92, SN_LE16(532), { 2, SN_LE16(376) } },
    { 50, SN_LE16(552) },
    { 10, 92, SN_LE16(552), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47408) } } },
    { 52, SN_LE16(560), 6 },
    { 10, 92, SN_LE16(560), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47520) } } },
    { 52, SN_LE16(568), 3 },
    { 10, 96, SN_LE16(570), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(574), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(582), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 98, SN_LE16(586), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 92, SN_LE16(588), { 2, SN_LE16(376) } },
    { 50, SN_LE16(608) },
    { 10, 96, SN_LE16(610), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(614), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(664) },
    { 10, 92, SN_LE16(664), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47520) } } },
    { 52, SN_LE16(672), 2 },
    { 10, 92, SN_LE16(684), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47548) } } },
    { 10, 92, SN_LE16(692), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(45580) } } },
    { 52, SN_LE16(700), 3 },
    { 10, 92, SN_LE16(704), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(712) },
    { 52, SN_LE16(736), 0 },
    { 52, SN_LE16(736), 3 },
    { 52, SN_LE16(736), 0 },
    { 50, SN_LE16(756) },
    { 52, SN_LE16(756), 3 },
    { 10, 92, SN_LE16(784), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47680) } } },
    { 10, 96, SN_LE16(794), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(798), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(806), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(810), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(812), { 2, SN_LE16(376) } },
    { 52, SN_LE16(832), 4 },
    { 50, SN_LE16(840) },
    { 10, 92, SN_LE16(876), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47732) } } },
    { 10, 92, SN_LE16(884), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47860) } } },
    { 52, SN_LE16(892), 2 },
    { 10, 96, SN_LE16(894), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(898), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(988) },
    { 56, SN_LE16(992), SN_LE32(4471) },
    { 10, 92, SN_LE16(1004), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47692) } } },
    { 52, SN_LE16(1012), 6 },
    { 10, 92, SN_LE16(1020), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47876) } } },
    { 50, SN_LE16(1028) },
    { 52, SN_LE16(1052), 0 },
    { 52, SN_LE16(1052), 4 },
    { 52, SN_LE16(1052), 0 },
    { 50, SN_LE16(1072) },
    { 52, SN_LE16(1072), 3 },
    { 10, 92, SN_LE16(1100), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(47996) } } },
    { 10, 96, SN_LE16(1110), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(1114), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(1122), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(1126), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(1128), { 2, SN_LE16(376) } },
    { 52, SN_LE16(1148), 3 },
    { 52, SN_LE16(1156), 2 },
    { 10, 92, SN_LE16(1192), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(48048) } } },
    { 10, 92, SN_LE16(1200), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(48180) } } },
    { 52, SN_LE16(1208), 2 },
    { 10, 96, SN_LE16(1210), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1214), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1304) },
    { 56, SN_LE16(1312), SN_LE32(4491) },
    { 10, 92, SN_LE16(1324), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(48008) } } },
    { 52, SN_LE16(1332), 6 },
    { 10, 92, SN_LE16(1340), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(48196) } } },
    { 50, SN_LE16(1348) },
    { 52, SN_LE16(1372), 0 },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(408), { 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x2D, 0x3E, 0x6D, 0x5F, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x5B, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x5D, 0x2E, 0x6D, 0x5F, 0x4E, 0x61, 0x6D, 0x65, 0x4D, 0x61, 0x6E, 0x61, 0x67, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x2E, 0x6D, 0x5F, 0x70, 0x53, 0x6C, 0x6F, 0x74, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x5B, 0x30, 0x5D, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x00, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x2D, 0x3E, 0x6D, 0x5F, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x5B, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x5D, 0x2E, 0x6D, 0x5F, 0x4E, 0x61, 0x6D, 0x65, 0x4D, 0x61, 0x6E, 0x61, 0x67, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x2E, 0x6D, 0x5F, 0x70, 0x53, 0x6C, 0x6F, 0x74, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x5B, 0x31, 0x5D, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x00, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x2D, 0x3E, 0x6D, 0x5F, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x5B, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x5D, 0x2E, 0x6D, 0x5F, 0x4E, 0x61, 0x6D, 0x65, 0x4D, 0x61, 0x6E, 0x61, 0x67, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x2E, 0x6D, 0x5F, 0x70, 0x53, 0x6C, 0x6F, 0x74, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x5B, 0x32, 0x5D, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x00, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x2D, 0x3E, 0x6D, 0x5F, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x5B, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x5D, 0x2E, 0x6D, 0x5F, 0x4E, 0x61, 0x6D, 0x65, 0x4D, 0x61, 0x6E, 0x61, 0x67, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x2E, 0x6D, 0x5F, 0x70, 0x53, 0x6C, 0x6F, 0x74, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x5B, 0x33, 0x5D, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x00, 0x70, 0x54, 0x65, 0x78, 0x74, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x00, 0x00, 0x70, 0x53, 0x65, 0x6C, 0x65, 0x63, 0x74, 0x65, 0x64, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00 } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(2704) }
};
typedef char k_PortalAfterFindEmptyPlayerDataSlotSizeCheck[(sizeof(k_PortalAfterFindEmptyPlayerDataSlot) == 1367) ? 1 : -1];
#endif
