#include "DATA_OVERLAY_SN_RECORDS.H"

#include "TYPES.H"
#if defined(VERSION_US)
struct {
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record0;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record1;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record6;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record7;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record8;
    struct { u8 opcode; SnLe16 offset; } record9;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record10;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record12;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record13;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record14;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record15;
    struct { u8 opcode; SnLe16 offset; } record16;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record17;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record18;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record22;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record23;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record25;
    struct { u8 opcode; SnLe16 offset; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record28;
    struct { u8 opcode; SnLe16 offset; } record29;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; SnLe16 offset; } record32;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record33;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record34;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record35;
    struct { u8 opcode; SnLe16 offset; } record36;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record37;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record38;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record39;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record40;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record41;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record42;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record43;
    struct { u8 opcode; SnLe16 offset; } record44;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record45;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record46;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record47;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record48;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record49;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record50;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record51;
    struct { u8 opcode; SnLe16 offset; } record52;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record53;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record54;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record55;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record56;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record57;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record58;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record59;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record60;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record61;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record62;
    struct { u8 opcode; SnLe16 offset; } record63;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record64;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record65;
    struct { u8 opcode; SnLe16 offset; } record66;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record67;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record68;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record69;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record70;
    struct { u8 opcode; SnLe16 offset; } record71;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record72;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record73;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record74;
    struct { u8 opcode; SnLe16 offset; } record75;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record76;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record77;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record78;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record79;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record80;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record81;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record82;
    struct { u8 opcode; SnLe16 offset; } record83;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record84;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record85;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record86;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record87;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record88;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record89;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record90;
    struct { u8 opcode; SnLe16 offset; } record91;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record92;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record93;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record94;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record95;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record96;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record97;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record98;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record99;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record100;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record101;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record102;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record103;
    struct { u8 opcode; SnLe16 offset; } record104;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record105;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record106;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record107;
    struct { u8 opcode; SnLe16 offset; } record108;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record109;
    struct { u8 opcode; SnLe16 offset; } record110;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record111;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record112;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record113;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record114;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record115;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record116;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record117;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record118;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record119;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record120;
    struct { u8 opcode; SnLe16 offset; } record121;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record122;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record123;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record124;
    struct { u8 opcode; SnLe16 offset; } record125;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record126;
    struct { u8 opcode; SnLe16 offset; } record127;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record128;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record129;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record130;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record131;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record132;
    struct { u8 opcode; SnLe16 offset; } record133;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record134;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record135;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record136;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record137;
    struct { u8 opcode; SnLe16 offset; } record138;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record139;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record140;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record141;
    struct { u8 opcode; SnLe16 offset; } record142;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record143;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record144;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record145;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record146;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record147;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record148;
    struct { u8 opcode; SnLe16 offset; } record149;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record150;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record151;
    struct { u8 opcode; SnLe16 offset; } record152;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record153;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record154;
    struct { u8 opcode; SnLe16 offset; } record155;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record156;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record157;
    struct { u8 opcode; SnLe16 offset; } record158;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record159;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record160;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record161;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record162;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record163;
    struct { u8 opcode; SnLe16 offset; } record164;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record165;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record166;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record167;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record168;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record169;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record170;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record171;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record172;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record173;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record174;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record175;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record176;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record177;
    struct { u8 opcode; SnLe16 offset; } record178;
    struct { u8 opcode; SnLe16 offset; } record179;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record180;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record181;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record182;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record183;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record184;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record185;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record186;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record187;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record188;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record189;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record190;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record191;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record192;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record193;
    struct { u8 opcode; SnLe16 offset; } record194;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record195;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record196;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left; struct { u8 opcode; SnLe16 symbol; } right; } expression; } record197;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left; struct { u8 opcode; SnLe16 symbol; } right; } expression; } record198;
    struct { u8 opcode; SnLe16 offset; } record199;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record200;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record201;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record202;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record203;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record204;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record205;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record206;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record207;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record208;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record209;
    struct { u8 opcode; SnLe16 offset; } record210;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record211;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record212;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record213;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record214;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record215;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record216;
    struct { u8 opcode; SnLe16 offset; } record217;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record218;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record219;
    struct { u8 opcode; SnLe16 offset; } record220;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record221;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record222;
    struct { u8 opcode; SnLe16 offset; } record223;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record224;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record225;
    struct { u8 opcode; SnLe16 offset; } record226;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record227;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record228;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record229;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record230;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record231;
    struct { u8 opcode; SnLe16 offset; } record232;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record233;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record234;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record235;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record236;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record237;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record238;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record239;
    struct { u8 opcode; SnLe16 offset; } record240;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record241;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record242;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record243;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record244;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record245;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record246;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record247;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record248;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record249;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record250;
    struct { u8 opcode; SnLe16 offset; } record251;
    struct { u8 opcode; SnLe16 offset; } record252;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record253;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record254;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record255;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record256;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record257;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record258;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record259;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record260;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record261;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record262;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record263;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record264;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record265;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record266;
    struct { u8 opcode; SnLe16 offset; } record267;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record268;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record269;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record270;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record271;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record272;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record273;
    struct { u8 opcode; SnLe16 section; } record274;
    struct { u8 opcode; SnLe16 codeSize; u8 code[301]; } record275;
    struct { u8 opcode; SnLe16 section; } record276;
    u8 followingRecordFragment[2];
} k_PortalAfterRefreshMiddleNamesForCopy __attribute__((aligned(4))) = {
    { 52, SN_LE16(0), 3 },
    { 52, SN_LE16(0), 0 },
    { 52, SN_LE16(28), 2 },
    { 10, 92, SN_LE16(56), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51452) } } },
    { 10, 96, SN_LE16(66), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(70), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(78), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(82), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(84), { 2, SN_LE16(376) } },
    { 50, SN_LE16(104) },
    { 10, 92, SN_LE16(132), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51528) } } },
    { 10, 96, SN_LE16(142), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(146), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(154), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1816) } } },
    { 10, 98, SN_LE16(158), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1816) } } },
    { 10, 92, SN_LE16(160), { 2, SN_LE16(376) } },
    { 50, SN_LE16(180) },
    { 10, 92, SN_LE16(208), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51604) } } },
    { 10, 96, SN_LE16(218), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(222), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(230), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1844) } } },
    { 10, 98, SN_LE16(234), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1844) } } },
    { 10, 92, SN_LE16(236), { 2, SN_LE16(376) } },
    { 52, SN_LE16(256), 3 },
    { 10, 96, SN_LE16(258), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(262), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(296) },
    { 10, 96, SN_LE16(298), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(302), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(336) },
    { 10, 96, SN_LE16(338), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(342), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(376) },
    { 52, SN_LE16(400), 0 },
    { 52, SN_LE16(400), 3 },
    { 52, SN_LE16(400), 0 },
    { 50, SN_LE16(424) },
    { 52, SN_LE16(424), 3 },
    { 10, 92, SN_LE16(452), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51848) } } },
    { 10, 96, SN_LE16(462), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(466), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(474), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(478), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(480), { 2, SN_LE16(376) } },
    { 50, SN_LE16(500) },
    { 10, 92, SN_LE16(528), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51924) } } },
    { 10, 96, SN_LE16(538), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(542), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(550), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1816) } } },
    { 10, 98, SN_LE16(554), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1816) } } },
    { 10, 92, SN_LE16(556), { 2, SN_LE16(376) } },
    { 52, SN_LE16(576), 3 },
    { 50, SN_LE16(580) },
    { 10, 92, SN_LE16(612), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51976) } } },
    { 10, 92, SN_LE16(620), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52180) } } },
    { 52, SN_LE16(628), 2 },
    { 10, 96, SN_LE16(630), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(634), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(678), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(682), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(724), 3 },
    { 10, 96, SN_LE16(726), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(730), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(764) },
    { 10, 96, SN_LE16(766), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(770), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(804) },
    { 56, SN_LE16(812), SN_LE32(4705) },
    { 10, 92, SN_LE16(824), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(51932) } } },
    { 52, SN_LE16(832), 12 },
    { 10, 92, SN_LE16(840), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52196) } } },
    { 50, SN_LE16(848) },
    { 52, SN_LE16(872), 0 },
    { 52, SN_LE16(872), 3 },
    { 52, SN_LE16(872), 0 },
    { 50, SN_LE16(896) },
    { 52, SN_LE16(896), 3 },
    { 10, 92, SN_LE16(924), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52320) } } },
    { 10, 96, SN_LE16(934), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(938), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(946), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(950), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(952), { 2, SN_LE16(376) } },
    { 50, SN_LE16(972) },
    { 10, 92, SN_LE16(1000), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52396) } } },
    { 10, 96, SN_LE16(1010), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(1014), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(1022), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1816) } } },
    { 10, 98, SN_LE16(1026), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1816) } } },
    { 10, 92, SN_LE16(1028), { 2, SN_LE16(376) } },
    { 52, SN_LE16(1048), 3 },
    { 50, SN_LE16(1056) },
    { 10, 92, SN_LE16(1092), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52448) } } },
    { 10, 92, SN_LE16(1100), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52580) } } },
    { 52, SN_LE16(1108), 2 },
    { 10, 96, SN_LE16(1110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1158), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1162), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1204), 3 },
    { 56, SN_LE16(1212), SN_LE32(4730) },
    { 10, 92, SN_LE16(1224), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52408) } } },
    { 52, SN_LE16(1232), 10 },
    { 10, 92, SN_LE16(1240), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52596) } } },
    { 50, SN_LE16(1248) },
    { 52, SN_LE16(1272), 0 },
    { 52, SN_LE16(1272), 4 },
    { 52, SN_LE16(1272), 0 },
    { 50, SN_LE16(1284) },
    { 52, SN_LE16(1284), 3 },
    { 50, SN_LE16(1292) },
    { 10, 92, SN_LE16(1328), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52684) } } },
    { 10, 92, SN_LE16(1336), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52768) } } },
    { 52, SN_LE16(1344), 2 },
    { 10, 96, SN_LE16(1346), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1350), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1392), 2 },
    { 56, SN_LE16(1400), SN_LE32(4750) },
    { 10, 92, SN_LE16(1412), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52644) } } },
    { 52, SN_LE16(1420), 8 },
    { 10, 92, SN_LE16(1428), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52784) } } },
    { 50, SN_LE16(1436) },
    { 52, SN_LE16(1456), 0 },
    { 52, SN_LE16(1456), 3 },
    { 52, SN_LE16(1456), 0 },
    { 50, SN_LE16(1468) },
    { 52, SN_LE16(1468), 3 },
    { 50, SN_LE16(1476) },
    { 10, 92, SN_LE16(1512), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52868) } } },
    { 10, 92, SN_LE16(1520), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52948) } } },
    { 52, SN_LE16(1528), 2 },
    { 10, 96, SN_LE16(1530), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1534), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1576) },
    { 56, SN_LE16(1580), SN_LE32(4767) },
    { 10, 92, SN_LE16(1592), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52828) } } },
    { 52, SN_LE16(1600), 6 },
    { 10, 92, SN_LE16(1608), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52964) } } },
    { 50, SN_LE16(1616) },
    { 52, SN_LE16(1636), 0 },
    { 52, SN_LE16(1636), 56 },
    { 52, SN_LE16(1636), 0 },
    { 50, SN_LE16(1656) },
    { 52, SN_LE16(1656), 5 },
    { 10, 92, SN_LE16(1676), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53736) } } },
    { 52, SN_LE16(1684), 2 },
    { 10, 92, SN_LE16(1720), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53156) } } },
    { 10, 92, SN_LE16(1752), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53156) } } },
    { 52, SN_LE16(1760), 3 },
    { 50, SN_LE16(1768) },
    { 10, 92, SN_LE16(1768), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53172) } } },
    { 52, SN_LE16(1776), 3 },
    { 50, SN_LE16(1784) },
    { 10, 92, SN_LE16(1784), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53172) } } },
    { 52, SN_LE16(1792), 3 },
    { 50, SN_LE16(1800) },
    { 10, 92, SN_LE16(1800), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53172) } } },
    { 52, SN_LE16(1808), 4 },
    { 50, SN_LE16(1816) },
    { 10, 92, SN_LE16(1816), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53172) } } },
    { 52, SN_LE16(1824), 3 },
    { 10, 96, SN_LE16(1826), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1830), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1844), { 2, SN_LE16(381) } },
    { 50, SN_LE16(1856) },
    { 10, 96, SN_LE16(1870), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(1874), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(1882), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 98, SN_LE16(1886), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 92, SN_LE16(1888), { 2, SN_LE16(376) } },
    { 52, SN_LE16(1908), 3 },
    { 10, 92, SN_LE16(1916), { 2, SN_LE16(434) } },
    { 52, SN_LE16(1924), 11 },
    { 10, 96, SN_LE16(1950), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(1954), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(1962), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1036) } } },
    { 10, 98, SN_LE16(1966), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1036) } } },
    { 10, 92, SN_LE16(1968), { 2, SN_LE16(376) } },
    { 50, SN_LE16(1988) },
    { 50, SN_LE16(2000) },
    { 10, 96, SN_LE16(2014), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(2018), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(2026), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1776) } } },
    { 10, 98, SN_LE16(2030), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1776) } } },
    { 10, 92, SN_LE16(2032), { 2, SN_LE16(376) } },
    { 52, SN_LE16(2052), 2 },
    { 10, 96, SN_LE16(2070), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2074), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(2084), { 2, SN_LE16(411) } },
    { 52, SN_LE16(2104), 3 },
    { 10, 96, SN_LE16(2150), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2154), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(2162), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2166), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2248) },
    { 10, 92, SN_LE16(2248), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53716) } } },
    { 52, SN_LE16(2256), 3 },
    { 10, 96, SN_LE16(2286), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(2294), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 50, SN_LE16(2304) },
    { 10, 96, SN_LE16(2338), { 2, SN_LE16(384) } },
    { 10, 98, SN_LE16(2342), { 2, SN_LE16(384) } },
    { 10, 92, SN_LE16(2352), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53716) } } },
    { 52, SN_LE16(2360), 2 },
    { 56, SN_LE16(2368), SN_LE32(4836) },
    { 10, 92, SN_LE16(2380), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53008) } } },
    { 52, SN_LE16(2388), 54 },
    { 52, SN_LE16(2412), 0 },
    { 52, SN_LE16(2412), 7 },
    { 52, SN_LE16(2412), 0 },
    { 50, SN_LE16(2432) },
    { 52, SN_LE16(2432), 5 },
    { 10, 92, SN_LE16(2452), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(54456) } } },
    { 52, SN_LE16(2460), 2 },
    { 10, 92, SN_LE16(2496), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53932) } } },
    { 10, 92, SN_LE16(2528), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53932) } } },
    { 52, SN_LE16(2536), 3 },
    { 50, SN_LE16(2544) },
    { 10, 92, SN_LE16(2544), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53948) } } },
    { 52, SN_LE16(2552), 3 },
    { 50, SN_LE16(2560) },
    { 10, 92, SN_LE16(2560), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53948) } } },
    { 52, SN_LE16(2568), 3 },
    { 50, SN_LE16(2576) },
    { 10, 92, SN_LE16(2576), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53948) } } },
    { 52, SN_LE16(2584), 4 },
    { 50, SN_LE16(2592) },
    { 10, 92, SN_LE16(2592), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53948) } } },
    { 52, SN_LE16(2600), 3 },
    { 10, 96, SN_LE16(2602), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2606), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(2620), { 2, SN_LE16(381) } },
    { 50, SN_LE16(2632) },
    { 10, 96, SN_LE16(2646), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(2650), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(2658), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 98, SN_LE16(2662), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(296) } } },
    { 10, 92, SN_LE16(2664), { 2, SN_LE16(376) } },
    { 52, SN_LE16(2684), 3 },
    { 10, 92, SN_LE16(2688), { 2, SN_LE16(430) } },
    { 50, SN_LE16(2708) },
    { 10, 92, SN_LE16(2716), { 2, SN_LE16(434) } },
    { 10, 92, SN_LE16(2724), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(54096) } } },
    { 52, SN_LE16(2732), 2 },
    { 10, 92, SN_LE16(2740), { 2, SN_LE16(434) } },
    { 52, SN_LE16(2748), 8 },
    { 10, 96, SN_LE16(2774), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(2778), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(2786), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1036) } } },
    { 10, 98, SN_LE16(2790), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1036) } } },
    { 10, 92, SN_LE16(2792), { 2, SN_LE16(376) } },
    { 50, SN_LE16(2812) },
    { 50, SN_LE16(2824) },
    { 10, 96, SN_LE16(2838), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(2842), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(2850), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1776) } } },
    { 10, 98, SN_LE16(2854), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1776) } } },
    { 10, 92, SN_LE16(2856), { 2, SN_LE16(376) } },
    { 52, SN_LE16(2876), 2 },
    { 10, 96, SN_LE16(2894), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2898), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(2908), { 2, SN_LE16(411) } },
    { 52, SN_LE16(2928), 3 },
    { 10, 96, SN_LE16(2974), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2978), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(2986), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2990), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3072) },
    { 10, 92, SN_LE16(3072), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(54436) } } },
    { 52, SN_LE16(3080), 2 },
    { 56, SN_LE16(3088), SN_LE32(4903) },
    { 10, 92, SN_LE16(3100), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53784) } } },
    { 52, SN_LE16(3108), 49 },
    { 52, SN_LE16(3132), 0 },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(301), { 0x00, 0x00, 0x00, 0x25, 0x64, 0x00, 0x00, 0x25, 0x64, 0x2E, 0x25, 0x73, 0x2E, 0x25, 0x73, 0x00, 0x00, 0x00, 0x00, 0x25, 0x64, 0x2E, 0x25, 0x73, 0x00, 0x00, 0x00, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x2D, 0x3E, 0x6D, 0x5F, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x5B, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x5D, 0x2E, 0x6D, 0x5F, 0x50, 0x61, 0x6B, 0x4D, 0x61, 0x6E, 0x61, 0x67, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x2E, 0x6D, 0x5F, 0x70, 0x53, 0x6C, 0x6F, 0x74, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x5B, 0x30, 0x5D, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x00, 0x00, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x2D, 0x3E, 0x6D, 0x5F, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x5B, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x5D, 0x2E, 0x6D, 0x5F, 0x50, 0x61, 0x6B, 0x4D, 0x61, 0x6E, 0x61, 0x67, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x2E, 0x6D, 0x5F, 0x70, 0x53, 0x6C, 0x6F, 0x74, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x5B, 0x31, 0x5D, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x00, 0x00, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x2D, 0x3E, 0x6D, 0x5F, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x5B, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x5D, 0x2E, 0x6D, 0x5F, 0x50, 0x61, 0x6B, 0x4D, 0x61, 0x6E, 0x61, 0x67, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x2E, 0x6D, 0x5F, 0x70, 0x53, 0x6C, 0x6F, 0x74, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x5B, 0x32, 0x5D, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00 } },
    { 6, SN_LE16(2) },
    { 0x02, 0x50 }
};
typedef char k_PortalAfterRefreshMiddleNamesForCopySizeCheck[(sizeof(k_PortalAfterRefreshMiddleNamesForCopy) == 2668) ? 1 : -1];
struct { u8 codeSizeHigh; } k_PortalAfterRefreshMiddleNamesForCopyTail = { 0x1A };
#endif
