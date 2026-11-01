#include "DATA_OVERLAY_SN_RECORDS.H"
#include "include_asm.h"
#if defined(VERSION_DE) || defined(VERSION_US)
#ifdef VERSION_US
struct {
    u8 precedingRecordFragment[10];
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; SnLe16 section; } record5;
    struct { u8 opcode; SnLe16 codeSize; u8 code[2164]; } record6;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record7;
    struct { u8 opcode; SnLe16 offset; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record9;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record10;
    struct { u8 opcode; SnLe16 offset; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record12;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record13;
    struct { u8 opcode; SnLe16 offset; } record14;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record15;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record16;
    struct { u8 opcode; SnLe16 offset; } record17;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record18;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; SnLe16 offset; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record22;
    struct { u8 opcode; SnLe16 offset; } record23;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record24;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record25;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record28;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record29;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record32;
    struct { u8 opcode; SnLe16 offset; } record33;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record34;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record35;
    struct { u8 opcode; SnLe16 offset; } record36;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record37;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record38;
    struct { u8 opcode; SnLe16 offset; } record39;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record40;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record41;
    struct { u8 opcode; SnLe16 offset; } record42;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record43;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record44;
    struct { u8 opcode; SnLe16 offset; } record45;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record46;
    struct { u8 opcode; SnLe16 offset; } record47;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record48;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record49;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record50;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record51;
    struct { u8 opcode; SnLe16 offset; } record52;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record53;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record54;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record55;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record56;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record57;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record58;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record59;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record60;
    struct { u8 opcode; SnLe16 offset; } record61;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record62;
    struct { u8 opcode; SnLe16 offset; } record63;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record64;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record65;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record66;
    struct { u8 opcode; SnLe16 offset; } record67;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record68;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record69;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record70;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record71;
    struct { u8 opcode; SnLe16 offset; } record72;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record73;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record74;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record75;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record76;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record77;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record78;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record79;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record80;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record81;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record82;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record83;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record84;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record85;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record86;
    struct { u8 opcode; SnLe16 offset; } record87;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record88;
    struct { u8 opcode; SnLe16 offset; } record89;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record90;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record91;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record92;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record93;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record94;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record95;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record96;
    struct { u8 opcode; SnLe16 offset; } record97;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record98;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record99;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record100;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record101;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record102;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record103;
    struct { u8 opcode; SnLe16 offset; } record104;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record105;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record106;
    struct { u8 opcode; SnLe16 offset; } record107;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record108;
    struct { u8 opcode; SnLe16 offset; } record109;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record110;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record111;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record112;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record113;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record114;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record115;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record116;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record117;
    struct { u8 opcode; SnLe16 offset; } record118;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record119;
    struct { u8 opcode; SnLe16 offset; } record120;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record121;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record122;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record123;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record124;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record125;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record126;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record127;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record128;
    struct { u8 opcode; SnLe16 offset; } record129;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record130;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record131;
    struct { u8 opcode; SnLe16 offset; } record132;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record133;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record134;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record135;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record136;
    struct { u8 opcode; SnLe16 offset; } record137;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record138;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record139;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record140;
    struct { u8 opcode; SnLe16 offset; } record141;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record142;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record143;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record144;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record145;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record146;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record147;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record148;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record149;
    struct { u8 opcode; SnLe16 offset; } record150;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record151;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record152;
    struct { u8 opcode; SnLe16 offset; } record153;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record154;
    struct { u8 opcode; SnLe16 offset; } record155;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record156;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record157;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record158;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record159;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record160;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record161;
    struct { u8 opcode; SnLe16 offset; } record162;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record163;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record164;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record165;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record166;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record167;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record168;
    struct { u8 opcode; SnLe16 offset; } record169;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record170;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record171;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record172;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record173;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record174;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record175;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record176;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record177;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record178;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record179;
    struct { u8 opcode; SnLe16 offset; } record180;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record181;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record182;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record183;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record184;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record185;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record186;
    struct { u8 opcode; SnLe16 offset; } record187;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record188;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record189;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record190;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record191;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record192;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record193;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record194;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record195;
    struct { u8 opcode; SnLe16 offset; } record196;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record197;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record198;
    struct { u8 opcode; SnLe16 offset; } record199;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record200;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record201;
    struct { u8 opcode; SnLe16 offset; } record202;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record203;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record204;
    struct { u8 opcode; SnLe16 offset; } record205;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record206;
    struct { u8 opcode; SnLe16 offset; } record207;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record208;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record209;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record210;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record211;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record212;
    struct { u8 opcode; SnLe16 offset; } record213;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record214;
    struct { u8 opcode; SnLe16 offset; } record215;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record216;
    struct { u8 opcode; SnLe16 offset; } record217;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record218;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record219;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record220;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record221;
    struct { u8 opcode; SnLe16 codeSize; u8 codeFragment[95]; } record222;
} k_LibsnEnumeratememoryrangesEncodedWords __attribute__((aligned(4))) = {
    { 0x00, 0x2C, 0x04, 0x02, 0x00, 0x00, 0x44, 0x70, 0x00, 0x00 },
    { 10, 8, SN_LE16(16), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 10, 8, SN_LE16(20), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28756) } } },
    { 10, 8, SN_LE16(24), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 10, 8, SN_LE16(28), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28772) } } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(2164), { 0xAF, 0xC0, 0x00, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x02, 0x00, 0x01, 0xAF, 0xC2, 0x00, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x02, 0x00, 0x02, 0xAF, 0xC2, 0x00, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x02, 0x00, 0x03, 0xAF, 0xC2, 0x00, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x04, 0x00, 0x03, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x21, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x10, 0x8F, 0xC3, 0x00, 0x14, 0x10, 0x43, 0x00, 0x53, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8C, 0x44, 0x00, 0x04, 0x8F, 0xC5, 0x00, 0x14, 0x24, 0x06, 0x00, 0x01, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x10, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x02, 0xAC, 0x43, 0x00, 0x6C, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x10, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x02, 0xAC, 0x43, 0x00, 0x58, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x10, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x09, 0xAC, 0x43, 0x00, 0x60, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x10, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x03, 0xAC, 0x43, 0x00, 0x5C, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x10, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x01, 0xAC, 0x43, 0x0B, 0x88, 0x8F, 0xC4, 0x00, 0x10, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x10, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x09, 0xAC, 0x43, 0x00, 0x58, 0x8F, 0xC4, 0x00, 0x10, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x24, 0x03, 0x02, 0xE6, 0x10, 0x43, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x24, 0x03, 0x02, 0xE7, 0x10, 0x43, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x0E, 0xAC, 0x43, 0x00, 0x58, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x03, 0x00, 0x01, 0x14, 0x43, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x0E, 0xAC, 0x43, 0x00, 0x58, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x24, 0x03, 0x02, 0xE0, 0x10, 0x43, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x24, 0x03, 0x02, 0xE1, 0x10, 0x43, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x03, 0x00, 0x00, 0x8C, 0x63, 0x00, 0x00, 0x8C, 0x62, 0x00, 0x54, 0x28, 0x43, 0x00, 0x06, 0x10, 0x60, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x0E, 0xAC, 0x43, 0x00, 0x58, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x04, 0x00, 0x00, 0x24, 0x84, 0x00, 0x00, 0x24, 0x05, 0x0C, 0x97, 0x3C, 0x06, 0x00, 0x00, 0x24, 0xC6, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x02, 0xAC, 0x43, 0x00, 0x6C, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x02, 0xAC, 0x43, 0x00, 0x58, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x24, 0x03, 0x02, 0xAB, 0x10, 0x43, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x24, 0x03, 0x02, 0xAC, 0x10, 0x43, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x0C, 0xAC, 0x43, 0x00, 0x58, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8C, 0x43, 0x00, 0x54, 0x24, 0x02, 0x00, 0x07, 0x10, 0x62, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x1A, 0xAC, 0x43, 0x00, 0x58, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x17, 0xAC, 0x43, 0x00, 0x60, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x0E, 0xAC, 0x43, 0x00, 0x58, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x24, 0x03, 0x02, 0xA8, 0x10, 0x43, 0x00, 0x27, 0x00, 0x00, 0x00, 0x00, 0x24, 0x03, 0x02, 0xA9, 0x10, 0x43, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x0D, 0xAC, 0x43, 0x00, 0x58, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x05, 0xAC, 0x43, 0x00, 0x5C, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x8C, 0x43, 0x0B, 0x88, 0x24, 0x02, 0x00, 0x01, 0x14, 0x62, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x0E, 0xAC, 0x43, 0x00, 0x58, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x24, 0x03, 0x02, 0xE9, 0x10, 0x43, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x8C, 0x43, 0x0B, 0x88, 0x24, 0x02, 0x00, 0x01, 0x14, 0x62, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10, 0x21, 0x24, 0x03, 0x00, 0x0E, 0xAC, 0x43, 0x00, 0x58, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x24, 0x03, 0x02, 0xA5, 0x10, 0x43, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x24, 0x03, 0x02, 0xA6, 0x10, 0x43, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x24, 0x03, 0x00, 0x02, 0xAC, 0x43, 0x00, 0x6C, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x24, 0x03, 0x00, 0x02, 0xAC, 0x43, 0x00, 0x58, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x24, 0x03, 0x00, 0x0D, 0xAC, 0x43, 0x00, 0x60, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x24, 0x03, 0x00, 0x06, 0xAC, 0x43, 0x00, 0x5C, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x04, 0x00, 0x09, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x21, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC2, 0x00, 0x18, 0x24, 0x03, 0x02, 0xDD } },
    { 52, SN_LE16(0), 3 },
    { 50, SN_LE16(4) },
    { 10, 92, SN_LE16(4), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 52, SN_LE16(12), 3 },
    { 50, SN_LE16(20) },
    { 10, 92, SN_LE16(20), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 52, SN_LE16(28), 3 },
    { 50, SN_LE16(36) },
    { 10, 92, SN_LE16(36), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 52, SN_LE16(44), 3 },
    { 50, SN_LE16(52) },
    { 10, 92, SN_LE16(52), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 52, SN_LE16(60), 3 },
    { 10, 92, SN_LE16(64), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(64660) } } },
    { 50, SN_LE16(72) },
    { 10, 92, SN_LE16(76), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31464) } } },
    { 50, SN_LE16(84) },
    { 10, 92, SN_LE16(84), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 52, SN_LE16(92), 9 },
    { 52, SN_LE16(108), 4 },
    { 10, 96, SN_LE16(110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(128), { 2, SN_LE16(422) } },
    { 52, SN_LE16(136), 3 },
    { 10, 96, SN_LE16(138), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(142), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(192) },
    { 10, 96, SN_LE16(194), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(198), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(248) },
    { 10, 96, SN_LE16(250), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(254), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(304) },
    { 10, 96, SN_LE16(306), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(310), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(360) },
    { 10, 96, SN_LE16(362), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(366), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(416) },
    { 10, 92, SN_LE16(420), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(428) },
    { 10, 92, SN_LE16(428), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29232) } } },
    { 52, SN_LE16(436), 3 },
    { 10, 96, SN_LE16(438), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(442), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(492) },
    { 10, 92, SN_LE16(496), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(504), 2 },
    { 10, 92, SN_LE16(504), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(512), 159 },
    { 10, 92, SN_LE16(540), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29464) } } },
    { 52, SN_LE16(548), 3 },
    { 10, 96, SN_LE16(550), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(554), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(604) },
    { 10, 92, SN_LE16(608), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(616) },
    { 10, 92, SN_LE16(616), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29464) } } },
    { 52, SN_LE16(624), 3 },
    { 10, 92, SN_LE16(628), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(66520) } } },
    { 50, SN_LE16(636) },
    { 10, 92, SN_LE16(640), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(61412) } } },
    { 52, SN_LE16(660), 2 },
    { 10, 96, SN_LE16(662), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(666), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(716) },
    { 10, 92, SN_LE16(720), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(728), 2 },
    { 10, 92, SN_LE16(728), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29464) } } },
    { 52, SN_LE16(736), 2 },
    { 10, 92, SN_LE16(736), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(744), 4 },
    { 10, 92, SN_LE16(772), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29812) } } },
    { 52, SN_LE16(780), 3 },
    { 10, 96, SN_LE16(782), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(786), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(812), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29548) } } },
    { 52, SN_LE16(820), 13 },
    { 10, 96, SN_LE16(822), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(826), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(876) },
    { 10, 92, SN_LE16(880), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(888) },
    { 10, 92, SN_LE16(888), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29672) } } },
    { 52, SN_LE16(896), 3 },
    { 10, 96, SN_LE16(898), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(902), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(910), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 98, SN_LE16(914), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 92, SN_LE16(916), { 2, SN_LE16(376) } },
    { 50, SN_LE16(936) },
    { 10, 92, SN_LE16(936), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29672) } } },
    { 52, SN_LE16(944), 2 },
    { 10, 92, SN_LE16(944), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29812) } } },
    { 52, SN_LE16(952), 3 },
    { 10, 96, SN_LE16(954), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(958), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1008) },
    { 10, 96, SN_LE16(1010), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1014), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1064) },
    { 10, 92, SN_LE16(1068), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1076) },
    { 10, 92, SN_LE16(1076), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29812) } } },
    { 52, SN_LE16(1084), 2 },
    { 10, 92, SN_LE16(1084), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(1092), 3 },
    { 10, 92, SN_LE16(1120), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30168) } } },
    { 52, SN_LE16(1128), 3 },
    { 10, 96, SN_LE16(1130), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1134), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1184) },
    { 10, 92, SN_LE16(1188), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1196) },
    { 10, 92, SN_LE16(1196), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30168) } } },
    { 52, SN_LE16(1204), 3 },
    { 10, 96, SN_LE16(1206), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1210), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1228), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30084) } } },
    { 52, SN_LE16(1236), 3 },
    { 10, 96, SN_LE16(1238), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1242), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1292) },
    { 10, 96, SN_LE16(1294), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1298), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1348) },
    { 10, 92, SN_LE16(1348), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30148) } } },
    { 52, SN_LE16(1356), 4 },
    { 10, 96, SN_LE16(1358), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1362), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1412) },
    { 10, 92, SN_LE16(1412), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30148) } } },
    { 52, SN_LE16(1420), 2 },
    { 10, 92, SN_LE16(1424), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1432) },
    { 10, 92, SN_LE16(1432), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30168) } } },
    { 52, SN_LE16(1440), 2 },
    { 10, 92, SN_LE16(1440), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(1448), 3 },
    { 10, 92, SN_LE16(1476), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30504) } } },
    { 52, SN_LE16(1484), 3 },
    { 10, 96, SN_LE16(1486), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1490), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1540) },
    { 10, 96, SN_LE16(1542), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1546), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1596) },
    { 10, 92, SN_LE16(1600), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1608) },
    { 10, 92, SN_LE16(1608), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30504) } } },
    { 52, SN_LE16(1616), 3 },
    { 10, 96, SN_LE16(1618), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1622), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1680), 2 },
    { 10, 92, SN_LE16(1684), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(67732) } } },
    { 50, SN_LE16(1692) },
    { 10, 92, SN_LE16(1692), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30484) } } },
    { 52, SN_LE16(1700), 2 },
    { 10, 96, SN_LE16(1702), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1706), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1756), 2 },
    { 10, 92, SN_LE16(1760), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1768) },
    { 10, 92, SN_LE16(1768), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30504) } } },
    { 52, SN_LE16(1776), 2 },
    { 10, 92, SN_LE16(1776), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(1784), 3 },
    { 10, 92, SN_LE16(1800), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30696) } } },
    { 52, SN_LE16(1808), 3 },
    { 10, 96, SN_LE16(1810), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1814), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1872), 3 },
    { 10, 92, SN_LE16(1876), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(67732) } } },
    { 50, SN_LE16(1884) },
    { 10, 92, SN_LE16(1884), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30676) } } },
    { 52, SN_LE16(1892), 2 },
    { 10, 96, SN_LE16(1894), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1898), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1948), 2 },
    { 10, 92, SN_LE16(1952), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1960) },
    { 10, 92, SN_LE16(1960), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30696) } } },
    { 52, SN_LE16(1968), 2 },
    { 10, 92, SN_LE16(1968), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(1976), 3 },
    { 10, 92, SN_LE16(2004), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30876) } } },
    { 52, SN_LE16(2012), 7 },
    { 10, 96, SN_LE16(2014), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2018), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2028) },
    { 10, 96, SN_LE16(2030), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2034), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2044) },
    { 10, 96, SN_LE16(2046), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2050), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2060) },
    { 10, 96, SN_LE16(2062), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2066), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2076) },
    { 10, 92, SN_LE16(2080), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(2088) },
    { 10, 92, SN_LE16(2088), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30876) } } },
    { 52, SN_LE16(2096), 11 },
    { 10, 92, SN_LE16(2100), { 2, SN_LE16(423) } },
    { 52, SN_LE16(2108), 3 },
    { 10, 92, SN_LE16(2108), { 2, SN_LE16(402) } },
    { 50, SN_LE16(2116) },
    { 10, 92, SN_LE16(2120), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(64660) } } },
    { 50, SN_LE16(2128) },
    { 10, 92, SN_LE16(2132), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31464) } } },
    { 50, SN_LE16(2140) },
    { 10, 92, SN_LE16(2140), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30876) } } },
    { 52, SN_LE16(2148), 2 },
    { 10, 92, SN_LE16(2148), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(2156), 3 },
    { 2, SN_LE16(1316), { 0x10, 0x43, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x24, 0x03, 0x02, 0xDE, 0x10, 0x43, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xC4, 0x00, 0x14, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x02, 0x00, 0x00, 0x8C, 0x42, 0x00, 0x00, 0x8F, 0xC3, 0x00, 0x14, 0x00, 0x60, 0x20, 0x21, 0x00, 0x04, 0x28, 0xC0, 0x00, 0xA3, 0x28, 0x21, 0x00, 0x05, 0x20, 0xC0, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0x80, 0x00, 0x83, 0x20, 0x21, 0x00, 0x04, 0x18, 0xC0, 0x00, 0x43, 0x10 } }
};
typedef char k_LibsnEnumeratememoryrangesEncodedWordsSizeCheck[(sizeof(k_LibsnEnumeratememoryrangesEncodedWords) == 4220) ? 1 : -1];
#endif
#if defined(VERSION_US)
unsigned int g_libsnHostMemoryRanges_LibsnEnumeratememoryrangesData[3] = {
    0x21240300, 0x1DAC4300, 0x588FC400,
};
#endif
#endif
