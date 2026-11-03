#include "DATA_OVERLAY_SN_RECORDS.H"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * Boundary gap at +0xD79: code payload continues in following function. */
typedef struct MenuStreamRecord0 { u8 opcode; SnLe16 offset; u8 lineDelta; } MenuStreamRecord0;
typedef struct MenuStreamRecord1 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } MenuStreamRecord1;
typedef struct MenuStreamRecord2 { u8 opcode; SnLe16 offset; } MenuStreamRecord2;
typedef struct MenuStreamRecord3 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } MenuStreamRecord3;
typedef struct MenuStreamRecord4 { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left; struct { u8 opcode; SnLe16 reference; } right; } expression; } MenuStreamRecord4;
typedef struct MenuStreamRecord5 { u8 opcode; SnLe16 offset; SnLe32 line; } MenuStreamRecord5;
typedef struct MenuStreamRecord6 { u8 opcode; SnLe16 section; } MenuStreamRecord6;
typedef struct MenuStreamRecord7 { u8 opcode; SnLe16 codeSize; u8 code[20]; } MenuStreamRecord7;
typedef struct MenuStreamRecord8 { u8 opcode; SnLe16 codeSize; } MenuStreamRecord8;
typedef struct MenuResourceStreamRecords {
    MenuStreamRecord0 record0;
    MenuStreamRecord1 record1;
    MenuStreamRecord2 record2;
    MenuStreamRecord1 record3;
    MenuStreamRecord2 record4;
    MenuStreamRecord2 record5;
    MenuStreamRecord3 record6;
    MenuStreamRecord0 record7;
    MenuStreamRecord1 record8;
    MenuStreamRecord2 record9;
    MenuStreamRecord1 record10;
    MenuStreamRecord2 record11;
    MenuStreamRecord2 record12;
    MenuStreamRecord3 record13;
    MenuStreamRecord0 record14;
    MenuStreamRecord1 record15;
    MenuStreamRecord2 record16;
    MenuStreamRecord1 record17;
    MenuStreamRecord2 record18;
    MenuStreamRecord2 record19;
    MenuStreamRecord3 record20;
    MenuStreamRecord0 record21;
    MenuStreamRecord1 record22;
    MenuStreamRecord2 record23;
    MenuStreamRecord1 record24;
    MenuStreamRecord2 record25;
    MenuStreamRecord2 record26;
    MenuStreamRecord3 record27;
    MenuStreamRecord0 record28;
    MenuStreamRecord1 record29;
    MenuStreamRecord2 record30;
    MenuStreamRecord1 record31;
    MenuStreamRecord2 record32;
    MenuStreamRecord2 record33;
    MenuStreamRecord3 record34;
    MenuStreamRecord0 record35;
    MenuStreamRecord3 record36;
    MenuStreamRecord0 record37;
    MenuStreamRecord1 record38;
    MenuStreamRecord2 record39;
    MenuStreamRecord1 record40;
    MenuStreamRecord2 record41;
    MenuStreamRecord0 record42;
    MenuStreamRecord3 record43;
    MenuStreamRecord0 record44;
    MenuStreamRecord4 record45;
    MenuStreamRecord4 record46;
    MenuStreamRecord4 record47;
    MenuStreamRecord4 record48;
    MenuStreamRecord0 record49;
    MenuStreamRecord4 record50;
    MenuStreamRecord4 record51;
    MenuStreamRecord2 record52;
    MenuStreamRecord4 record53;
    MenuStreamRecord4 record54;
    MenuStreamRecord0 record55;
    MenuStreamRecord4 record56;
    MenuStreamRecord4 record57;
    MenuStreamRecord0 record58;
    MenuStreamRecord3 record59;
    MenuStreamRecord3 record60;
    MenuStreamRecord2 record61;
    MenuStreamRecord3 record62;
    MenuStreamRecord3 record63;
    MenuStreamRecord2 record64;
    MenuStreamRecord3 record65;
    MenuStreamRecord3 record66;
    MenuStreamRecord5 record67;
    MenuStreamRecord3 record68;
    MenuStreamRecord0 record69;
    MenuStreamRecord3 record70;
    MenuStreamRecord2 record71;
    MenuStreamRecord3 record72;
    MenuStreamRecord0 record73;
    MenuStreamRecord1 record74;
    MenuStreamRecord2 record75;
    MenuStreamRecord1 record76;
    MenuStreamRecord2 record77;
    MenuStreamRecord0 record78;
    MenuStreamRecord3 record79;
    MenuStreamRecord0 record80;
    MenuStreamRecord3 record81;
    MenuStreamRecord3 record82;
    MenuStreamRecord3 record83;
    MenuStreamRecord3 record84;
    MenuStreamRecord1 record85;
    MenuStreamRecord2 record86;
    MenuStreamRecord3 record87;
    MenuStreamRecord0 record88;
    MenuStreamRecord3 record89;
    MenuStreamRecord0 record90;
    MenuStreamRecord3 record91;
    MenuStreamRecord3 record92;
    MenuStreamRecord0 record93;
    MenuStreamRecord3 record94;
    MenuStreamRecord3 record95;
    MenuStreamRecord0 record96;
    MenuStreamRecord3 record97;
    MenuStreamRecord3 record98;
    MenuStreamRecord0 record99;
    MenuStreamRecord3 record100;
    MenuStreamRecord0 record101;
    MenuStreamRecord1 record102;
    MenuStreamRecord0 record103;
    MenuStreamRecord3 record104;
    MenuStreamRecord2 record105;
    MenuStreamRecord3 record106;
    MenuStreamRecord3 record107;
    MenuStreamRecord1 record108;
    MenuStreamRecord5 record109;
    MenuStreamRecord3 record110;
    MenuStreamRecord0 record111;
    MenuStreamRecord3 record112;
    MenuStreamRecord0 record113;
    MenuStreamRecord3 record114;
    MenuStreamRecord3 record115;
    MenuStreamRecord1 record116;
    MenuStreamRecord2 record117;
    MenuStreamRecord3 record118;
    MenuStreamRecord3 record119;
    MenuStreamRecord1 record120;
    MenuStreamRecord5 record121;
    MenuStreamRecord3 record122;
    MenuStreamRecord0 record123;
    MenuStreamRecord3 record124;
    MenuStreamRecord3 record125;
    MenuStreamRecord1 record126;
    MenuStreamRecord2 record127;
    MenuStreamRecord3 record128;
    MenuStreamRecord3 record129;
    MenuStreamRecord1 record130;
    MenuStreamRecord2 record131;
    MenuStreamRecord3 record132;
    MenuStreamRecord3 record133;
    MenuStreamRecord1 record134;
    MenuStreamRecord2 record135;
    MenuStreamRecord3 record136;
    MenuStreamRecord3 record137;
    MenuStreamRecord0 record138;
    MenuStreamRecord3 record139;
    MenuStreamRecord3 record140;
    MenuStreamRecord2 record141;
    MenuStreamRecord3 record142;
    MenuStreamRecord0 record143;
    MenuStreamRecord3 record144;
    MenuStreamRecord3 record145;
    MenuStreamRecord2 record146;
    MenuStreamRecord3 record147;
    MenuStreamRecord3 record148;
    MenuStreamRecord5 record149;
    MenuStreamRecord3 record150;
    MenuStreamRecord0 record151;
    MenuStreamRecord3 record152;
    MenuStreamRecord3 record153;
    MenuStreamRecord0 record154;
    MenuStreamRecord3 record155;
    MenuStreamRecord3 record156;
    MenuStreamRecord0 record157;
    MenuStreamRecord3 record158;
    MenuStreamRecord3 record159;
    MenuStreamRecord0 record160;
    MenuStreamRecord3 record161;
    MenuStreamRecord3 record162;
    MenuStreamRecord0 record163;
    MenuStreamRecord3 record164;
    MenuStreamRecord3 record165;
    MenuStreamRecord0 record166;
    MenuStreamRecord3 record167;
    MenuStreamRecord3 record168;
    MenuStreamRecord5 record169;
    MenuStreamRecord3 record170;
    MenuStreamRecord0 record171;
    MenuStreamRecord3 record172;
    MenuStreamRecord3 record173;
    MenuStreamRecord0 record174;
    MenuStreamRecord3 record175;
    MenuStreamRecord3 record176;
    MenuStreamRecord3 record177;
    MenuStreamRecord3 record178;
    MenuStreamRecord0 record179;
    MenuStreamRecord3 record180;
    MenuStreamRecord2 record181;
    MenuStreamRecord3 record182;
    MenuStreamRecord3 record183;
    MenuStreamRecord5 record184;
    MenuStreamRecord3 record185;
    MenuStreamRecord0 record186;
    MenuStreamRecord3 record187;
    MenuStreamRecord0 record188;
    MenuStreamRecord4 record189;
    MenuStreamRecord4 record190;
    MenuStreamRecord4 record191;
    MenuStreamRecord4 record192;
    MenuStreamRecord4 record193;
    MenuStreamRecord4 record194;
    MenuStreamRecord4 record195;
    MenuStreamRecord4 record196;
    MenuStreamRecord0 record197;
    MenuStreamRecord3 record198;
    MenuStreamRecord3 record199;
    MenuStreamRecord4 record200;
    MenuStreamRecord4 record201;
    MenuStreamRecord2 record202;
    MenuStreamRecord3 record203;
    MenuStreamRecord3 record204;
    MenuStreamRecord4 record205;
    MenuStreamRecord4 record206;
    MenuStreamRecord2 record207;
    MenuStreamRecord3 record208;
    MenuStreamRecord3 record209;
    MenuStreamRecord4 record210;
    MenuStreamRecord4 record211;
    MenuStreamRecord5 record212;
    MenuStreamRecord3 record213;
    MenuStreamRecord0 record214;
    MenuStreamRecord3 record215;
    MenuStreamRecord2 record216;
    MenuStreamRecord3 record217;
    MenuStreamRecord5 record218;
    MenuStreamRecord3 record219;
    MenuStreamRecord0 record220;
    MenuStreamRecord3 record221;
    MenuStreamRecord0 record222;
    MenuStreamRecord1 record223;
    MenuStreamRecord1 record224;
    MenuStreamRecord0 record225;
    MenuStreamRecord3 record226;
    MenuStreamRecord0 record227;
    MenuStreamRecord1 record228;
    MenuStreamRecord2 record229;
    MenuStreamRecord1 record230;
    MenuStreamRecord0 record231;
    MenuStreamRecord3 record232;
    MenuStreamRecord0 record233;
    MenuStreamRecord3 record234;
    MenuStreamRecord3 record235;
    MenuStreamRecord2 record236;
    MenuStreamRecord3 record237;
    MenuStreamRecord3 record238;
    MenuStreamRecord2 record239;
    MenuStreamRecord3 record240;
    MenuStreamRecord3 record241;
    MenuStreamRecord2 record242;
    MenuStreamRecord3 record243;
    MenuStreamRecord2 record244;
    MenuStreamRecord3 record245;
    MenuStreamRecord5 record246;
    MenuStreamRecord3 record247;
    MenuStreamRecord0 record248;
    MenuStreamRecord3 record249;
    MenuStreamRecord0 record250;
    MenuStreamRecord1 record251;
    MenuStreamRecord1 record252;
    MenuStreamRecord1 record253;
    MenuStreamRecord2 record254;
    MenuStreamRecord1 record255;
    MenuStreamRecord1 record256;
    MenuStreamRecord1 record257;
    MenuStreamRecord0 record258;
    MenuStreamRecord3 record259;
    MenuStreamRecord0 record260;
    MenuStreamRecord3 record261;
    MenuStreamRecord3 record262;
    MenuStreamRecord1 record263;
    MenuStreamRecord1 record264;
    MenuStreamRecord2 record265;
    MenuStreamRecord3 record266;
    MenuStreamRecord3 record267;
    MenuStreamRecord1 record268;
    MenuStreamRecord1 record269;
    MenuStreamRecord2 record270;
    MenuStreamRecord3 record271;
    MenuStreamRecord3 record272;
    MenuStreamRecord1 record273;
    MenuStreamRecord1 record274;
    MenuStreamRecord2 record275;
    MenuStreamRecord1 record276;
    MenuStreamRecord1 record277;
    MenuStreamRecord3 record278;
    MenuStreamRecord2 record279;
    MenuStreamRecord3 record280;
    MenuStreamRecord0 record281;
    MenuStreamRecord3 record282;
    MenuStreamRecord0 record283;
    MenuStreamRecord3 record284;
    MenuStreamRecord3 record285;
    MenuStreamRecord2 record286;
    MenuStreamRecord3 record287;
    MenuStreamRecord3 record288;
    MenuStreamRecord2 record289;
    MenuStreamRecord3 record290;
    MenuStreamRecord3 record291;
    MenuStreamRecord2 record292;
    MenuStreamRecord3 record293;
    MenuStreamRecord3 record294;
    MenuStreamRecord2 record295;
    MenuStreamRecord3 record296;
    MenuStreamRecord2 record297;
    MenuStreamRecord3 record298;
    MenuStreamRecord0 record299;
    MenuStreamRecord1 record300;
    MenuStreamRecord0 record301;
    MenuStreamRecord1 record302;
    MenuStreamRecord0 record303;
    MenuStreamRecord1 record304;
    MenuStreamRecord0 record305;
    MenuStreamRecord1 record306;
    MenuStreamRecord0 record307;
    MenuStreamRecord3 record308;
    MenuStreamRecord2 record309;
    MenuStreamRecord0 record310;
    MenuStreamRecord0 record311;
    MenuStreamRecord0 record312;
    MenuStreamRecord2 record313;
    MenuStreamRecord3 record314;
    MenuStreamRecord2 record315;
    MenuStreamRecord0 record316;
    MenuStreamRecord0 record317;
    MenuStreamRecord0 record318;
    MenuStreamRecord2 record319;
    MenuStreamRecord3 record320;
    MenuStreamRecord3 record321;
    MenuStreamRecord1 record322;
    MenuStreamRecord2 record323;
    MenuStreamRecord3 record324;
    MenuStreamRecord3 record325;
    MenuStreamRecord2 record326;
    MenuStreamRecord1 record327;
    MenuStreamRecord2 record328;
    MenuStreamRecord1 record329;
    MenuStreamRecord0 record330;
    MenuStreamRecord3 record331;
    MenuStreamRecord2 record332;
    MenuStreamRecord0 record333;
    MenuStreamRecord0 record334;
    MenuStreamRecord0 record335;
    MenuStreamRecord2 record336;
    MenuStreamRecord0 record337;
    MenuStreamRecord0 record338;
    MenuStreamRecord3 record339;
    MenuStreamRecord3 record340;
    MenuStreamRecord0 record341;
    MenuStreamRecord3 record342;
    MenuStreamRecord0 record343;
    MenuStreamRecord3 record344;
    MenuStreamRecord3 record345;
    MenuStreamRecord0 record346;
    MenuStreamRecord3 record347;
    MenuStreamRecord3 record348;
    MenuStreamRecord3 record349;
    MenuStreamRecord3 record350;
    MenuStreamRecord0 record351;
    MenuStreamRecord3 record352;
    MenuStreamRecord3 record353;
    MenuStreamRecord0 record354;
    MenuStreamRecord3 record355;
    MenuStreamRecord3 record356;
    MenuStreamRecord2 record357;
    MenuStreamRecord1 record358;
    MenuStreamRecord0 record359;
    MenuStreamRecord1 record360;
    MenuStreamRecord0 record361;
    MenuStreamRecord3 record362;
    MenuStreamRecord0 record363;
    MenuStreamRecord1 record364;
    MenuStreamRecord5 record365;
    MenuStreamRecord3 record366;
    MenuStreamRecord0 record367;
    MenuStreamRecord3 record368;
    MenuStreamRecord3 record369;
    MenuStreamRecord1 record370;
    MenuStreamRecord0 record371;
    MenuStreamRecord3 record372;
    MenuStreamRecord3 record373;
    MenuStreamRecord1 record374;
    MenuStreamRecord2 record375;
    MenuStreamRecord3 record376;
    MenuStreamRecord3 record377;
    MenuStreamRecord1 record378;
    MenuStreamRecord2 record379;
    MenuStreamRecord3 record380;
    MenuStreamRecord3 record381;
    MenuStreamRecord1 record382;
    MenuStreamRecord0 record383;
    MenuStreamRecord3 record384;
    MenuStreamRecord3 record385;
    MenuStreamRecord0 record386;
    MenuStreamRecord1 record387;
    MenuStreamRecord0 record388;
    MenuStreamRecord4 record389;
    MenuStreamRecord4 record390;
    MenuStreamRecord3 record391;
    MenuStreamRecord3 record392;
    MenuStreamRecord6 record393;
    MenuStreamRecord7 record394;
    MenuStreamRecord3 record395;
    MenuStreamRecord3 record396;
    MenuStreamRecord3 record397;
    MenuStreamRecord3 record398;
    MenuStreamRecord3 record399;
    MenuStreamRecord6 record400;
    MenuStreamRecord8 record401;
} MenuResourceStreamRecords;
MenuResourceStreamRecords g_frontendMenuResourceStream1 __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 74 },
    { 10, 92, SN_LE16(8), { 2, SN_LE16(381) } },
    { 50, SN_LE16(20) },
    { 10, 92, SN_LE16(28), { 2, SN_LE16(383) } },
    { 50, SN_LE16(36) },
    { 50, SN_LE16(48) },
    { 10, 92, SN_LE16(48), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2212) } } },
    { 52, SN_LE16(56), 4 },
    { 10, 92, SN_LE16(64), { 2, SN_LE16(381) } },
    { 50, SN_LE16(76) },
    { 10, 92, SN_LE16(84), { 2, SN_LE16(383) } },
    { 50, SN_LE16(92) },
    { 50, SN_LE16(104) },
    { 10, 92, SN_LE16(104), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2212) } } },
    { 52, SN_LE16(112), 4 },
    { 10, 92, SN_LE16(120), { 2, SN_LE16(381) } },
    { 50, SN_LE16(132) },
    { 10, 92, SN_LE16(140), { 2, SN_LE16(383) } },
    { 50, SN_LE16(148) },
    { 50, SN_LE16(160) },
    { 10, 92, SN_LE16(160), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2212) } } },
    { 52, SN_LE16(168), 4 },
    { 10, 92, SN_LE16(176), { 2, SN_LE16(381) } },
    { 50, SN_LE16(188) },
    { 10, 92, SN_LE16(196), { 2, SN_LE16(383) } },
    { 50, SN_LE16(204) },
    { 50, SN_LE16(216) },
    { 10, 92, SN_LE16(216), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2212) } } },
    { 52, SN_LE16(224), 4 },
    { 10, 92, SN_LE16(232), { 2, SN_LE16(381) } },
    { 50, SN_LE16(244) },
    { 10, 92, SN_LE16(252), { 2, SN_LE16(383) } },
    { 50, SN_LE16(260) },
    { 50, SN_LE16(272) },
    { 10, 92, SN_LE16(272), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2212) } } },
    { 52, SN_LE16(280), 7 },
    { 10, 92, SN_LE16(280), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2212) } } },
    { 52, SN_LE16(288), 4 },
    { 10, 92, SN_LE16(296), { 2, SN_LE16(381) } },
    { 50, SN_LE16(308) },
    { 10, 92, SN_LE16(316), { 2, SN_LE16(383) } },
    { 50, SN_LE16(324) },
    { 52, SN_LE16(336), 8 },
    { 10, 92, SN_LE16(356), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2088) } } },
    { 52, SN_LE16(364), 3 },
    { 10, 96, SN_LE16(394), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(402), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 10, 96, SN_LE16(442), { 44, { 0, SN_LE32(14) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(450), { 44, { 0, SN_LE32(14) }, { 2, SN_LE16(384) } } },
    { 52, SN_LE16(464), 3 },
    { 10, 96, SN_LE16(498), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(506), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 50, SN_LE16(508) },
    { 10, 96, SN_LE16(538), { 44, { 0, SN_LE32(14) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(546), { 44, { 0, SN_LE32(14) }, { 2, SN_LE16(384) } } },
    { 52, SN_LE16(548), 4 },
    { 10, 96, SN_LE16(578), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(586), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 52, SN_LE16(596), 2 },
    { 10, 96, SN_LE16(598), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(602), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(632) },
    { 10, 96, SN_LE16(634), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(638), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(672) },
    { 10, 96, SN_LE16(674), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(678), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 56, SN_LE16(712), SN_LE32(518) },
    { 10, 92, SN_LE16(724), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(1696) } } },
    { 52, SN_LE16(732), 18 },
    { 10, 92, SN_LE16(736), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52984) } } },
    { 50, SN_LE16(744) },
    { 10, 92, SN_LE16(744), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2212) } } },
    { 52, SN_LE16(752), 4 },
    { 10, 92, SN_LE16(760), { 2, SN_LE16(381) } },
    { 50, SN_LE16(772) },
    { 10, 92, SN_LE16(780), { 2, SN_LE16(383) } },
    { 50, SN_LE16(788) },
    { 52, SN_LE16(800), 10 },
    { 10, 92, SN_LE16(800), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2212) } } },
    { 52, SN_LE16(808), 2 },
    { 10, 96, SN_LE16(810), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(814), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(822), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 98, SN_LE16(826), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 92, SN_LE16(828), { 2, SN_LE16(376) } },
    { 50, SN_LE16(848) },
    { 10, 92, SN_LE16(848), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2212) } } },
    { 52, SN_LE16(856), 5 },
    { 10, 92, SN_LE16(876), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(3704) } } },
    { 52, SN_LE16(884), 2 },
    { 10, 96, SN_LE16(886), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(890), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(936), 29 },
    { 10, 96, SN_LE16(938), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(942), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(988), 2 },
    { 10, 96, SN_LE16(990), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(994), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1044), 2 },
    { 10, 92, SN_LE16(1048), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(1056), 3 },
    { 10, 92, SN_LE16(1060), { 2, SN_LE16(385) } },
    { 52, SN_LE16(1068), 3 },
    { 10, 92, SN_LE16(1088), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2572) } } },
    { 50, SN_LE16(1096) },
    { 10, 96, SN_LE16(1138), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1142), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1188), { 2, SN_LE16(386) } },
    { 56, SN_LE16(1196), SN_LE32(602) },
    { 10, 92, SN_LE16(1208), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2428) } } },
    { 52, SN_LE16(1216), 4 },
    { 10, 92, SN_LE16(1236), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2844) } } },
    { 52, SN_LE16(1244), 2 },
    { 10, 96, SN_LE16(1286), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1290), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1348), { 2, SN_LE16(387) } },
    { 50, SN_LE16(1356) },
    { 10, 96, SN_LE16(1398), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1402), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1460), { 2, SN_LE16(387) } },
    { 56, SN_LE16(1468), SN_LE32(606) },
    { 10, 92, SN_LE16(1480), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2576) } } },
    { 52, SN_LE16(1488), 5 },
    { 10, 96, SN_LE16(1530), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1534), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1556), { 2, SN_LE16(387) } },
    { 50, SN_LE16(1564) },
    { 10, 96, SN_LE16(1606), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1610), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1632), { 2, SN_LE16(387) } },
    { 50, SN_LE16(1640) },
    { 10, 96, SN_LE16(1682), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1686), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1708), { 2, SN_LE16(387) } },
    { 50, SN_LE16(1716) },
    { 10, 96, SN_LE16(1718), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1722), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1768), 4 },
    { 10, 96, SN_LE16(1770), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1774), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1820) },
    { 10, 92, SN_LE16(1840), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(3364) } } },
    { 52, SN_LE16(1848), 2 },
    { 10, 96, SN_LE16(1850), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1854), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1920) },
    { 10, 96, SN_LE16(1922), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1926), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 56, SN_LE16(1988), SN_LE32(619) },
    { 10, 92, SN_LE16(2000), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(3180) } } },
    { 52, SN_LE16(2008), 7 },
    { 10, 96, SN_LE16(2010), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2014), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2060), 4 },
    { 10, 96, SN_LE16(2062), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2066), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2112), 2 },
    { 10, 96, SN_LE16(2114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2118), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2164), 3 },
    { 10, 96, SN_LE16(2166), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2170), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2216), 2 },
    { 10, 96, SN_LE16(2218), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2222), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2272), 2 },
    { 10, 96, SN_LE16(2274), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2278), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 56, SN_LE16(2328), SN_LE32(561) },
    { 10, 92, SN_LE16(2340), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(2216) } } },
    { 52, SN_LE16(2348), 87 },
    { 10, 96, SN_LE16(2350), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2354), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2364), 4 },
    { 10, 96, SN_LE16(2366), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2370), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(2412), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5220) } } },
    { 10, 92, SN_LE16(2432), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5220) } } },
    { 52, SN_LE16(2440), 4 },
    { 10, 92, SN_LE16(2460), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(3900) } } },
    { 50, SN_LE16(2468) },
    { 10, 96, SN_LE16(2470), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2474), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 56, SN_LE16(2524), SN_LE32(656) },
    { 10, 92, SN_LE16(2536), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(3800) } } },
    { 52, SN_LE16(2544), 3 },
    { 10, 92, SN_LE16(2564), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(4420) } } },
    { 52, SN_LE16(2572), 2 },
    { 10, 96, SN_LE16(2602), { 44, { 0, SN_LE32(14) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(2610), { 44, { 0, SN_LE32(14) }, { 2, SN_LE16(384) } } },
    { 10, 96, SN_LE16(2650), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(2658), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 10, 96, SN_LE16(2698), { 44, { 0, SN_LE32(158040) }, { 2, SN_LE16(388) } } },
    { 10, 98, SN_LE16(2706), { 44, { 0, SN_LE32(158040) }, { 2, SN_LE16(388) } } },
    { 10, 96, SN_LE16(2750), { 44, { 0, SN_LE32(158065) }, { 2, SN_LE16(388) } } },
    { 10, 98, SN_LE16(2758), { 44, { 0, SN_LE32(158065) }, { 2, SN_LE16(388) } } },
    { 52, SN_LE16(2768), 5 },
    { 10, 96, SN_LE16(2770), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2774), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(2806), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(2814), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 50, SN_LE16(2860) },
    { 10, 96, SN_LE16(2862), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2866), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(2898), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(2906), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 50, SN_LE16(2952) },
    { 10, 96, SN_LE16(2954), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2958), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(2990), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 10, 98, SN_LE16(2998), { 44, { 0, SN_LE32(13) }, { 2, SN_LE16(384) } } },
    { 56, SN_LE16(3044), SN_LE32(659) },
    { 10, 92, SN_LE16(3056), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(3904) } } },
    { 52, SN_LE16(3064), 12 },
    { 10, 92, SN_LE16(3084), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(4480) } } },
    { 50, SN_LE16(3092) },
    { 10, 92, SN_LE16(3096), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 56, SN_LE16(3104), SN_LE32(671) },
    { 10, 92, SN_LE16(3116), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(4424) } } },
    { 52, SN_LE16(3124), 2 },
    { 10, 92, SN_LE16(3124), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5220) } } },
    { 52, SN_LE16(3132), 4 },
    { 10, 96, SN_LE16(3134), { 2, SN_LE16(389) } },
    { 10, 98, SN_LE16(3138), { 2, SN_LE16(389) } },
    { 52, SN_LE16(3148), 2 },
    { 10, 92, SN_LE16(3168), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(4824) } } },
    { 52, SN_LE16(3176), 3 },
    { 10, 92, SN_LE16(3180), { 2, SN_LE16(390) } },
    { 50, SN_LE16(3188) },
    { 10, 92, SN_LE16(3192), { 2, SN_LE16(391) } },
    { 52, SN_LE16(3204), 2 },
    { 10, 92, SN_LE16(3252), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(4616) } } },
    { 52, SN_LE16(3260), 6 },
    { 10, 96, SN_LE16(3262), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3266), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3316) },
    { 10, 96, SN_LE16(3318), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3322), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3372) },
    { 10, 96, SN_LE16(3374), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3378), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3428) },
    { 10, 92, SN_LE16(3432), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(3440) },
    { 10, 92, SN_LE16(3440), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(4804) } } },
    { 56, SN_LE16(3448), SN_LE32(679) },
    { 10, 92, SN_LE16(3460), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(4508) } } },
    { 52, SN_LE16(3468), 19 },
    { 10, 92, SN_LE16(3468), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5128) } } },
    { 52, SN_LE16(3476), 4 },
    { 10, 96, SN_LE16(3478), { 2, SN_LE16(392) } },
    { 10, 98, SN_LE16(3482), { 2, SN_LE16(392) } },
    { 10, 92, SN_LE16(3484), { 2, SN_LE16(390) } },
    { 50, SN_LE16(3492) },
    { 10, 96, SN_LE16(3494), { 2, SN_LE16(392) } },
    { 10, 98, SN_LE16(3498), { 2, SN_LE16(392) } },
    { 10, 92, SN_LE16(3500), { 2, SN_LE16(391) } },
    { 52, SN_LE16(3512), 2 },
    { 10, 92, SN_LE16(3560), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(4924) } } },
    { 52, SN_LE16(3568), 6 },
    { 10, 96, SN_LE16(3570), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3574), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(3578), { 2, SN_LE16(392) } },
    { 10, 98, SN_LE16(3582), { 2, SN_LE16(392) } },
    { 50, SN_LE16(3628) },
    { 10, 96, SN_LE16(3630), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3634), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(3638), { 2, SN_LE16(392) } },
    { 10, 98, SN_LE16(3642), { 2, SN_LE16(392) } },
    { 50, SN_LE16(3688) },
    { 10, 96, SN_LE16(3690), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3694), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(3698), { 2, SN_LE16(392) } },
    { 10, 98, SN_LE16(3702), { 2, SN_LE16(392) } },
    { 50, SN_LE16(3748) },
    { 10, 96, SN_LE16(3750), { 2, SN_LE16(392) } },
    { 10, 98, SN_LE16(3754), { 2, SN_LE16(392) } },
    { 10, 92, SN_LE16(3756), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(3764) },
    { 10, 92, SN_LE16(3764), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5128) } } },
    { 52, SN_LE16(3772), 5 },
    { 10, 92, SN_LE16(3772), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5220) } } },
    { 52, SN_LE16(3780), 4 },
    { 10, 96, SN_LE16(3782), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3786), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3796) },
    { 10, 96, SN_LE16(3798), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3802), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3812) },
    { 10, 96, SN_LE16(3814), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3818), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3828) },
    { 10, 96, SN_LE16(3830), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3834), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3844) },
    { 10, 92, SN_LE16(3848), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(3856) },
    { 10, 92, SN_LE16(3856), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5220) } } },
    { 52, SN_LE16(3864), 10 },
    { 10, 92, SN_LE16(3868), { 2, SN_LE16(393) } },
    { 52, SN_LE16(3876), 3 },
    { 10, 92, SN_LE16(3876), { 2, SN_LE16(394) } },
    { 52, SN_LE16(3884), 3 },
    { 10, 92, SN_LE16(3888), { 2, SN_LE16(395) } },
    { 52, SN_LE16(3896), 2 },
    { 10, 92, SN_LE16(3900), { 2, SN_LE16(396) } },
    { 52, SN_LE16(3908), 2 },
    { 10, 92, SN_LE16(3912), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5276) } } },
    { 50, SN_LE16(3920) },
    { 52, SN_LE16(3944), 0 },
    { 52, SN_LE16(3944), 3 },
    { 52, SN_LE16(3944), 0 },
    { 50, SN_LE16(3972) },
    { 10, 92, SN_LE16(3976), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5340) } } },
    { 50, SN_LE16(3984) },
    { 52, SN_LE16(4004), 0 },
    { 52, SN_LE16(4004), 5 },
    { 52, SN_LE16(4004), 0 },
    { 50, SN_LE16(4036) },
    { 10, 96, SN_LE16(4038), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4042), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(4044), { 2, SN_LE16(397) } },
    { 50, SN_LE16(4052) },
    { 10, 96, SN_LE16(4054), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4058), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(4060) },
    { 10, 92, SN_LE16(4060), { 2, SN_LE16(398) } },
    { 50, SN_LE16(4068) },
    { 10, 92, SN_LE16(4072), { 2, SN_LE16(395) } },
    { 52, SN_LE16(4080), 2 },
    { 10, 92, SN_LE16(4084), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5448) } } },
    { 50, SN_LE16(4092) },
    { 52, SN_LE16(4116), 0 },
    { 52, SN_LE16(4116), 3 },
    { 52, SN_LE16(4116), 0 },
    { 50, SN_LE16(4148) },
    { 52, SN_LE16(4148), 2 },
    { 52, SN_LE16(4164), 3 },
    { 10, 96, SN_LE16(4166), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4170), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4188), 2 },
    { 10, 92, SN_LE16(4208), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5916) } } },
    { 52, SN_LE16(4216), 2 },
    { 10, 96, SN_LE16(4218), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4222), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4276), 2 },
    { 10, 96, SN_LE16(4278), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4282), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(4326), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4330), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4384), 2 },
    { 10, 96, SN_LE16(4386), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4390), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4444), 2 },
    { 10, 96, SN_LE16(4446), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4450), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(4500) },
    { 10, 92, SN_LE16(4500), { 2, SN_LE16(394) } },
    { 52, SN_LE16(4508), 2 },
    { 10, 92, SN_LE16(4512), { 2, SN_LE16(390) } },
    { 52, SN_LE16(4520), 2 },
    { 10, 92, SN_LE16(4524), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(45460) } } },
    { 52, SN_LE16(4532), 2 },
    { 10, 92, SN_LE16(4532), { 2, SN_LE16(398) } },
    { 56, SN_LE16(4540), SN_LE32(778) },
    { 10, 92, SN_LE16(4552), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(5548) } } },
    { 52, SN_LE16(4560), 21 },
    { 10, 96, SN_LE16(4562), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4566), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(4576), { 2, SN_LE16(399) } },
    { 52, SN_LE16(4596), 2 },
    { 10, 96, SN_LE16(4598), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4602), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(4612), { 2, SN_LE16(400) } },
    { 50, SN_LE16(4620) },
    { 10, 96, SN_LE16(4622), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4626), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(4636), { 2, SN_LE16(401) } },
    { 50, SN_LE16(4644) },
    { 10, 96, SN_LE16(4646), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4650), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(4660), { 2, SN_LE16(399) } },
    { 52, SN_LE16(4680), 2 },
    { 10, 96, SN_LE16(4682), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4686), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4704), 2 },
    { 10, 92, SN_LE16(4704), { 2, SN_LE16(402) } },
    { 52, SN_LE16(4712), 2 },
    { 10, 96, SN_LE16(4714), { 44, { 0, SN_LE32(157725) }, { 2, SN_LE16(388) } } },
    { 10, 98, SN_LE16(4718), { 44, { 0, SN_LE32(157725) }, { 2, SN_LE16(388) } } },
    { 10, 96, SN_LE16(4738), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(168) } } },
    { 10, 98, SN_LE16(4742), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(168) } } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(20), { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 10, 8, SN_LE16(0), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(6116) } } },
    { 10, 8, SN_LE16(4), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(6148) } } },
    { 10, 8, SN_LE16(8), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(6132) } } },
    { 10, 8, SN_LE16(12), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(6148) } } },
    { 10, 8, SN_LE16(16), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(6148) } } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(264) },
};
typedef char MenuResourceStreamSize[(sizeof(MenuResourceStreamRecords) == 3449) ? 1 : -1];
#endif
