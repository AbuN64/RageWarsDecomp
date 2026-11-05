#include "data_overlay_sn_records.h"
#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * The code payload continues in the following function. */
typedef struct SnLineDeltaRecord { u8 opcode; SnLe16 offset; u8 lineDelta; } SnLineDeltaRecord;
typedef struct SnPatchRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 reference; } expression; } SnPatchRecord;
typedef struct SnOffsetMarkRecord { u8 opcode; SnLe16 offset; } SnOffsetMarkRecord;
typedef struct SnPatchReferencePlusConstantRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 reference; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } SnPatchReferencePlusConstantRecord;
typedef struct SnPatchConstantPlusReferenceRecord { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left; struct { u8 opcode; SnLe16 reference; } right; } expression; } SnPatchConstantPlusReferenceRecord;
typedef struct SnLineNumberRecord { u8 opcode; SnLe16 offset; SnLe32 line; } SnLineNumberRecord;
typedef struct SnSectionSwitchRecord { u8 opcode; SnLe16 section; } SnSectionSwitchRecord;
typedef struct SnCodeBlock20Record { u8 opcode; SnLe16 codeSize; u8 code[20]; } SnCodeBlock20Record;
typedef struct SnCodeSizeRecord { u8 opcode; SnLe16 codeSize; } SnCodeSizeRecord;
typedef struct SnObjectRecords {
    SnLineDeltaRecord record0;
    SnPatchRecord record1;
    SnOffsetMarkRecord record2;
    SnPatchRecord record3;
    SnOffsetMarkRecord record4;
    SnOffsetMarkRecord record5;
    SnPatchReferencePlusConstantRecord record6;
    SnLineDeltaRecord record7;
    SnPatchRecord record8;
    SnOffsetMarkRecord record9;
    SnPatchRecord record10;
    SnOffsetMarkRecord record11;
    SnOffsetMarkRecord record12;
    SnPatchReferencePlusConstantRecord record13;
    SnLineDeltaRecord record14;
    SnPatchRecord record15;
    SnOffsetMarkRecord record16;
    SnPatchRecord record17;
    SnOffsetMarkRecord record18;
    SnOffsetMarkRecord record19;
    SnPatchReferencePlusConstantRecord record20;
    SnLineDeltaRecord record21;
    SnPatchRecord record22;
    SnOffsetMarkRecord record23;
    SnPatchRecord record24;
    SnOffsetMarkRecord record25;
    SnOffsetMarkRecord record26;
    SnPatchReferencePlusConstantRecord record27;
    SnLineDeltaRecord record28;
    SnPatchRecord record29;
    SnOffsetMarkRecord record30;
    SnPatchRecord record31;
    SnOffsetMarkRecord record32;
    SnOffsetMarkRecord record33;
    SnPatchReferencePlusConstantRecord record34;
    SnLineDeltaRecord record35;
    SnPatchReferencePlusConstantRecord record36;
    SnLineDeltaRecord record37;
    SnPatchRecord record38;
    SnOffsetMarkRecord record39;
    SnPatchRecord record40;
    SnOffsetMarkRecord record41;
    SnLineDeltaRecord record42;
    SnPatchReferencePlusConstantRecord record43;
    SnLineDeltaRecord record44;
    SnPatchConstantPlusReferenceRecord record45;
    SnPatchConstantPlusReferenceRecord record46;
    SnPatchConstantPlusReferenceRecord record47;
    SnPatchConstantPlusReferenceRecord record48;
    SnLineDeltaRecord record49;
    SnPatchConstantPlusReferenceRecord record50;
    SnPatchConstantPlusReferenceRecord record51;
    SnOffsetMarkRecord record52;
    SnPatchConstantPlusReferenceRecord record53;
    SnPatchConstantPlusReferenceRecord record54;
    SnLineDeltaRecord record55;
    SnPatchConstantPlusReferenceRecord record56;
    SnPatchConstantPlusReferenceRecord record57;
    SnLineDeltaRecord record58;
    SnPatchReferencePlusConstantRecord record59;
    SnPatchReferencePlusConstantRecord record60;
    SnOffsetMarkRecord record61;
    SnPatchReferencePlusConstantRecord record62;
    SnPatchReferencePlusConstantRecord record63;
    SnOffsetMarkRecord record64;
    SnPatchReferencePlusConstantRecord record65;
    SnPatchReferencePlusConstantRecord record66;
    SnLineNumberRecord record67;
    SnPatchReferencePlusConstantRecord record68;
    SnLineDeltaRecord record69;
    SnPatchReferencePlusConstantRecord record70;
    SnOffsetMarkRecord record71;
    SnPatchReferencePlusConstantRecord record72;
    SnLineDeltaRecord record73;
    SnPatchRecord record74;
    SnOffsetMarkRecord record75;
    SnPatchRecord record76;
    SnOffsetMarkRecord record77;
    SnLineDeltaRecord record78;
    SnPatchReferencePlusConstantRecord record79;
    SnLineDeltaRecord record80;
    SnPatchReferencePlusConstantRecord record81;
    SnPatchReferencePlusConstantRecord record82;
    SnPatchReferencePlusConstantRecord record83;
    SnPatchReferencePlusConstantRecord record84;
    SnPatchRecord record85;
    SnOffsetMarkRecord record86;
    SnPatchReferencePlusConstantRecord record87;
    SnLineDeltaRecord record88;
    SnPatchReferencePlusConstantRecord record89;
    SnLineDeltaRecord record90;
    SnPatchReferencePlusConstantRecord record91;
    SnPatchReferencePlusConstantRecord record92;
    SnLineDeltaRecord record93;
    SnPatchReferencePlusConstantRecord record94;
    SnPatchReferencePlusConstantRecord record95;
    SnLineDeltaRecord record96;
    SnPatchReferencePlusConstantRecord record97;
    SnPatchReferencePlusConstantRecord record98;
    SnLineDeltaRecord record99;
    SnPatchReferencePlusConstantRecord record100;
    SnLineDeltaRecord record101;
    SnPatchRecord record102;
    SnLineDeltaRecord record103;
    SnPatchReferencePlusConstantRecord record104;
    SnOffsetMarkRecord record105;
    SnPatchReferencePlusConstantRecord record106;
    SnPatchReferencePlusConstantRecord record107;
    SnPatchRecord record108;
    SnLineNumberRecord record109;
    SnPatchReferencePlusConstantRecord record110;
    SnLineDeltaRecord record111;
    SnPatchReferencePlusConstantRecord record112;
    SnLineDeltaRecord record113;
    SnPatchReferencePlusConstantRecord record114;
    SnPatchReferencePlusConstantRecord record115;
    SnPatchRecord record116;
    SnOffsetMarkRecord record117;
    SnPatchReferencePlusConstantRecord record118;
    SnPatchReferencePlusConstantRecord record119;
    SnPatchRecord record120;
    SnLineNumberRecord record121;
    SnPatchReferencePlusConstantRecord record122;
    SnLineDeltaRecord record123;
    SnPatchReferencePlusConstantRecord record124;
    SnPatchReferencePlusConstantRecord record125;
    SnPatchRecord record126;
    SnOffsetMarkRecord record127;
    SnPatchReferencePlusConstantRecord record128;
    SnPatchReferencePlusConstantRecord record129;
    SnPatchRecord record130;
    SnOffsetMarkRecord record131;
    SnPatchReferencePlusConstantRecord record132;
    SnPatchReferencePlusConstantRecord record133;
    SnPatchRecord record134;
    SnOffsetMarkRecord record135;
    SnPatchReferencePlusConstantRecord record136;
    SnPatchReferencePlusConstantRecord record137;
    SnLineDeltaRecord record138;
    SnPatchReferencePlusConstantRecord record139;
    SnPatchReferencePlusConstantRecord record140;
    SnOffsetMarkRecord record141;
    SnPatchReferencePlusConstantRecord record142;
    SnLineDeltaRecord record143;
    SnPatchReferencePlusConstantRecord record144;
    SnPatchReferencePlusConstantRecord record145;
    SnOffsetMarkRecord record146;
    SnPatchReferencePlusConstantRecord record147;
    SnPatchReferencePlusConstantRecord record148;
    SnLineNumberRecord record149;
    SnPatchReferencePlusConstantRecord record150;
    SnLineDeltaRecord record151;
    SnPatchReferencePlusConstantRecord record152;
    SnPatchReferencePlusConstantRecord record153;
    SnLineDeltaRecord record154;
    SnPatchReferencePlusConstantRecord record155;
    SnPatchReferencePlusConstantRecord record156;
    SnLineDeltaRecord record157;
    SnPatchReferencePlusConstantRecord record158;
    SnPatchReferencePlusConstantRecord record159;
    SnLineDeltaRecord record160;
    SnPatchReferencePlusConstantRecord record161;
    SnPatchReferencePlusConstantRecord record162;
    SnLineDeltaRecord record163;
    SnPatchReferencePlusConstantRecord record164;
    SnPatchReferencePlusConstantRecord record165;
    SnLineDeltaRecord record166;
    SnPatchReferencePlusConstantRecord record167;
    SnPatchReferencePlusConstantRecord record168;
    SnLineNumberRecord record169;
    SnPatchReferencePlusConstantRecord record170;
    SnLineDeltaRecord record171;
    SnPatchReferencePlusConstantRecord record172;
    SnPatchReferencePlusConstantRecord record173;
    SnLineDeltaRecord record174;
    SnPatchReferencePlusConstantRecord record175;
    SnPatchReferencePlusConstantRecord record176;
    SnPatchReferencePlusConstantRecord record177;
    SnPatchReferencePlusConstantRecord record178;
    SnLineDeltaRecord record179;
    SnPatchReferencePlusConstantRecord record180;
    SnOffsetMarkRecord record181;
    SnPatchReferencePlusConstantRecord record182;
    SnPatchReferencePlusConstantRecord record183;
    SnLineNumberRecord record184;
    SnPatchReferencePlusConstantRecord record185;
    SnLineDeltaRecord record186;
    SnPatchReferencePlusConstantRecord record187;
    SnLineDeltaRecord record188;
    SnPatchConstantPlusReferenceRecord record189;
    SnPatchConstantPlusReferenceRecord record190;
    SnPatchConstantPlusReferenceRecord record191;
    SnPatchConstantPlusReferenceRecord record192;
    SnPatchConstantPlusReferenceRecord record193;
    SnPatchConstantPlusReferenceRecord record194;
    SnPatchConstantPlusReferenceRecord record195;
    SnPatchConstantPlusReferenceRecord record196;
    SnLineDeltaRecord record197;
    SnPatchReferencePlusConstantRecord record198;
    SnPatchReferencePlusConstantRecord record199;
    SnPatchConstantPlusReferenceRecord record200;
    SnPatchConstantPlusReferenceRecord record201;
    SnOffsetMarkRecord record202;
    SnPatchReferencePlusConstantRecord record203;
    SnPatchReferencePlusConstantRecord record204;
    SnPatchConstantPlusReferenceRecord record205;
    SnPatchConstantPlusReferenceRecord record206;
    SnOffsetMarkRecord record207;
    SnPatchReferencePlusConstantRecord record208;
    SnPatchReferencePlusConstantRecord record209;
    SnPatchConstantPlusReferenceRecord record210;
    SnPatchConstantPlusReferenceRecord record211;
    SnLineNumberRecord record212;
    SnPatchReferencePlusConstantRecord record213;
    SnLineDeltaRecord record214;
    SnPatchReferencePlusConstantRecord record215;
    SnOffsetMarkRecord record216;
    SnPatchReferencePlusConstantRecord record217;
    SnLineNumberRecord record218;
    SnPatchReferencePlusConstantRecord record219;
    SnLineDeltaRecord record220;
    SnPatchReferencePlusConstantRecord record221;
    SnLineDeltaRecord record222;
    SnPatchRecord record223;
    SnPatchRecord record224;
    SnLineDeltaRecord record225;
    SnPatchReferencePlusConstantRecord record226;
    SnLineDeltaRecord record227;
    SnPatchRecord record228;
    SnOffsetMarkRecord record229;
    SnPatchRecord record230;
    SnLineDeltaRecord record231;
    SnPatchReferencePlusConstantRecord record232;
    SnLineDeltaRecord record233;
    SnPatchReferencePlusConstantRecord record234;
    SnPatchReferencePlusConstantRecord record235;
    SnOffsetMarkRecord record236;
    SnPatchReferencePlusConstantRecord record237;
    SnPatchReferencePlusConstantRecord record238;
    SnOffsetMarkRecord record239;
    SnPatchReferencePlusConstantRecord record240;
    SnPatchReferencePlusConstantRecord record241;
    SnOffsetMarkRecord record242;
    SnPatchReferencePlusConstantRecord record243;
    SnOffsetMarkRecord record244;
    SnPatchReferencePlusConstantRecord record245;
    SnLineNumberRecord record246;
    SnPatchReferencePlusConstantRecord record247;
    SnLineDeltaRecord record248;
    SnPatchReferencePlusConstantRecord record249;
    SnLineDeltaRecord record250;
    SnPatchRecord record251;
    SnPatchRecord record252;
    SnPatchRecord record253;
    SnOffsetMarkRecord record254;
    SnPatchRecord record255;
    SnPatchRecord record256;
    SnPatchRecord record257;
    SnLineDeltaRecord record258;
    SnPatchReferencePlusConstantRecord record259;
    SnLineDeltaRecord record260;
    SnPatchReferencePlusConstantRecord record261;
    SnPatchReferencePlusConstantRecord record262;
    SnPatchRecord record263;
    SnPatchRecord record264;
    SnOffsetMarkRecord record265;
    SnPatchReferencePlusConstantRecord record266;
    SnPatchReferencePlusConstantRecord record267;
    SnPatchRecord record268;
    SnPatchRecord record269;
    SnOffsetMarkRecord record270;
    SnPatchReferencePlusConstantRecord record271;
    SnPatchReferencePlusConstantRecord record272;
    SnPatchRecord record273;
    SnPatchRecord record274;
    SnOffsetMarkRecord record275;
    SnPatchRecord record276;
    SnPatchRecord record277;
    SnPatchReferencePlusConstantRecord record278;
    SnOffsetMarkRecord record279;
    SnPatchReferencePlusConstantRecord record280;
    SnLineDeltaRecord record281;
    SnPatchReferencePlusConstantRecord record282;
    SnLineDeltaRecord record283;
    SnPatchReferencePlusConstantRecord record284;
    SnPatchReferencePlusConstantRecord record285;
    SnOffsetMarkRecord record286;
    SnPatchReferencePlusConstantRecord record287;
    SnPatchReferencePlusConstantRecord record288;
    SnOffsetMarkRecord record289;
    SnPatchReferencePlusConstantRecord record290;
    SnPatchReferencePlusConstantRecord record291;
    SnOffsetMarkRecord record292;
    SnPatchReferencePlusConstantRecord record293;
    SnPatchReferencePlusConstantRecord record294;
    SnOffsetMarkRecord record295;
    SnPatchReferencePlusConstantRecord record296;
    SnOffsetMarkRecord record297;
    SnPatchReferencePlusConstantRecord record298;
    SnLineDeltaRecord record299;
    SnPatchRecord record300;
    SnLineDeltaRecord record301;
    SnPatchRecord record302;
    SnLineDeltaRecord record303;
    SnPatchRecord record304;
    SnLineDeltaRecord record305;
    SnPatchRecord record306;
    SnLineDeltaRecord record307;
    SnPatchReferencePlusConstantRecord record308;
    SnOffsetMarkRecord record309;
    SnLineDeltaRecord record310;
    SnLineDeltaRecord record311;
    SnLineDeltaRecord record312;
    SnOffsetMarkRecord record313;
    SnPatchReferencePlusConstantRecord record314;
    SnOffsetMarkRecord record315;
    SnLineDeltaRecord record316;
    SnLineDeltaRecord record317;
    SnLineDeltaRecord record318;
    SnOffsetMarkRecord record319;
    SnPatchReferencePlusConstantRecord record320;
    SnPatchReferencePlusConstantRecord record321;
    SnPatchRecord record322;
    SnOffsetMarkRecord record323;
    SnPatchReferencePlusConstantRecord record324;
    SnPatchReferencePlusConstantRecord record325;
    SnOffsetMarkRecord record326;
    SnPatchRecord record327;
    SnOffsetMarkRecord record328;
    SnPatchRecord record329;
    SnLineDeltaRecord record330;
    SnPatchReferencePlusConstantRecord record331;
    SnOffsetMarkRecord record332;
    SnLineDeltaRecord record333;
    SnLineDeltaRecord record334;
    SnLineDeltaRecord record335;
    SnOffsetMarkRecord record336;
    SnLineDeltaRecord record337;
    SnLineDeltaRecord record338;
    SnPatchReferencePlusConstantRecord record339;
    SnPatchReferencePlusConstantRecord record340;
    SnLineDeltaRecord record341;
    SnPatchReferencePlusConstantRecord record342;
    SnLineDeltaRecord record343;
    SnPatchReferencePlusConstantRecord record344;
    SnPatchReferencePlusConstantRecord record345;
    SnLineDeltaRecord record346;
    SnPatchReferencePlusConstantRecord record347;
    SnPatchReferencePlusConstantRecord record348;
    SnPatchReferencePlusConstantRecord record349;
    SnPatchReferencePlusConstantRecord record350;
    SnLineDeltaRecord record351;
    SnPatchReferencePlusConstantRecord record352;
    SnPatchReferencePlusConstantRecord record353;
    SnLineDeltaRecord record354;
    SnPatchReferencePlusConstantRecord record355;
    SnPatchReferencePlusConstantRecord record356;
    SnOffsetMarkRecord record357;
    SnPatchRecord record358;
    SnLineDeltaRecord record359;
    SnPatchRecord record360;
    SnLineDeltaRecord record361;
    SnPatchReferencePlusConstantRecord record362;
    SnLineDeltaRecord record363;
    SnPatchRecord record364;
    SnLineNumberRecord record365;
    SnPatchReferencePlusConstantRecord record366;
    SnLineDeltaRecord record367;
    SnPatchReferencePlusConstantRecord record368;
    SnPatchReferencePlusConstantRecord record369;
    SnPatchRecord record370;
    SnLineDeltaRecord record371;
    SnPatchReferencePlusConstantRecord record372;
    SnPatchReferencePlusConstantRecord record373;
    SnPatchRecord record374;
    SnOffsetMarkRecord record375;
    SnPatchReferencePlusConstantRecord record376;
    SnPatchReferencePlusConstantRecord record377;
    SnPatchRecord record378;
    SnOffsetMarkRecord record379;
    SnPatchReferencePlusConstantRecord record380;
    SnPatchReferencePlusConstantRecord record381;
    SnPatchRecord record382;
    SnLineDeltaRecord record383;
    SnPatchReferencePlusConstantRecord record384;
    SnPatchReferencePlusConstantRecord record385;
    SnLineDeltaRecord record386;
    SnPatchRecord record387;
    SnLineDeltaRecord record388;
    SnPatchConstantPlusReferenceRecord record389;
    SnPatchConstantPlusReferenceRecord record390;
    SnPatchReferencePlusConstantRecord record391;
    SnPatchReferencePlusConstantRecord record392;
    SnSectionSwitchRecord record393;
    SnCodeBlock20Record record394;
    SnPatchReferencePlusConstantRecord record395;
    SnPatchReferencePlusConstantRecord record396;
    SnPatchReferencePlusConstantRecord record397;
    SnPatchReferencePlusConstantRecord record398;
    SnPatchReferencePlusConstantRecord record399;
    SnSectionSwitchRecord record400;
    SnCodeSizeRecord record401;
} SnObjectRecords;
SnObjectRecords g_pakInterfaceSnRecords_us_E56AB __attribute__((aligned(1))) = {
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
typedef char MenuResourceStreamSize[(sizeof(SnObjectRecords) == 3449) ? 1 : -1];
#endif
