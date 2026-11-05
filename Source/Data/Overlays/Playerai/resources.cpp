#include "types.h"
#include "include_asm.h"
#include "data_overlay_sn_records.h"

/* PLAYERAI_TRYSTARTPLAYERSEQUENCE_DATA.CPP */
#if defined(VERSION_DE)
extern struct {
    unsigned int words0[66];
    char text1[4];
    unsigned int words2[32];
    float floats3[1];
    unsigned int words4[56];
    char text5[4];
    unsigned int words6[244];
    unsigned char bytes7[4];
    unsigned int words8[36];
} k_PlayeraiTrystartplayersequenceEncodedWords;
#endif

/* K_RESOURCESENCODEDWORDSBLOCK7.CPP */
#if defined(VERSION_DE)
extern struct {
    u8 retainedRecordWords[4];
} k_playeraiResourceLeadBytes __attribute__((aligned(4)));

extern unsigned int k_playeraiResourcePackedHeader[5];
#endif

/* VHANDLER_RECYCLETLBSLOT_DATA.CPP */
#if defined(VERSION_DE)
extern unsigned int k_VhandlerRecycletlbslotEncodedWords[12];
#endif

/* K_RESOURCESENCODEDWORDSBLOCK4.CPP */
#if defined(VERSION_DE)
unsigned int k_playeraiResourcePackedStream[61] = {
    0xEE25C3F1, 0x4132C220, 0xF10006EF, 0x1911AEC1, 0x1FD6270D, 0xE1DEFE1F, 0xC3FC1E1B, 0xC5311E02,
    0x2AB24F39, 0x9CA2FC75, 0xF094C0FF, 0x2E545E0C, 0xC220E0C3, 0x7FF1223B, 0x1D0FE515, 0xC20D5120,
    0x104EECA2, 0x2FC02F5E, 0xE4F4654A, 0x04FEB24D, 0x531DDBDA, 0xFFF73CC0, 0xE5FFB0F2, 0xFFF2DDC4,
    0xC11D51CF, 0xE425004B, 0x21C1D0CB, 0x4103F9D0, 0x110DC1C3, 0x35E0C24B, 0x1FE7D0C2, 0xA0C322D2,
    0xD090DD20, 0xC0133B01, 0x2FFF1DF3, 0xEEC22003, 0x1012BF12, 0x403EC222, 0x191F0430, 0x0EA010C0,
    0xF46B2FD4, 0xE3FC41E2, 0xC0E6214B, 0x413CBD1F, 0x14C0C031, 0xF4132E1F, 0x2DB0C21F, 0x007FF155,
    0x03F4E1B3, 0xE5F01AC0, 0x5D0BAC78, 0xC24FE3DB, 0xB2E8F21D, 0x1CC2F5E0, 0x25C01433, 0x4C12C07E,
    0x30CC15D4, 0x20F003C2, 0x22130C6F, 0x653D101B, 0xC11C21DE,
};

unsigned int k_ResourcesEncodedTailWord_de[1] = {
    0xD3EFE631,
};

unsigned int k_playeraiResourcePackedStreamTail[7] = {
    0x01C332F2, 0x11D113F0, 0x17F3C0FE, 0xC15B2320, 0xF11FFFC1, 0x00DF00FE, 0x0DF7FF41,
};
#endif

/* G_RESOURCESENCODEDWORDSBLOCK.CPP */
#if defined(VERSION_US)
struct {
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left;
        struct { u8 opcode; SnLe32 constant; } right; } expression; } record0;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left;
        struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left;
        struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record3;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left;
        struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record6;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left;
        struct { u8 opcode; SnLe32 constant; } right; } expression; } record7;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left;
        struct { u8 opcode; SnLe32 constant; } right; } expression; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left;
        struct { u8 opcode; SnLe16 symbol; } right; } expression; } record9;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left;
        struct { u8 opcode; SnLe16 symbol; } right; } expression; } record10;
    u8 followingRecordFragment[1];
} g_resourcesEncodedWordsBlock __attribute__((aligned(4))) = {
    { 10, 98, SN_LE16(930), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(982), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1900) } } },
    { 10, 98, SN_LE16(986), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1900) } } },
    { 10, 92, SN_LE16(992), { 2, SN_LE16(439) } },
    { 52, SN_LE16(1000), 4 },
    { 10, 92, SN_LE16(1000), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(55948) } } },
    { 52, SN_LE16(1008), 4 },
    { 10, 96, SN_LE16(1050), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1054), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1102), { 44, { 0, SN_LE32(159121) }, { 2, SN_LE16(388) } } },
    { 10, 98, SN_LE16(1106), { 44, { 0, SN_LE32(159121) }, { 2, SN_LE16(388) } } },
    { 0x0A }
};
typedef char g_resourcesEncodedWordsBlockSizeCheck[(sizeof(g_resourcesEncodedWordsBlock) == 120) ? 1 : -1];

struct {
    u8 retainedRecordWords[8];
} k_playeraiResourceTrailerBytes __attribute__((aligned(4))) = {
    { 0x60, 0x62, 0x04, 0x02, 0xB3, 0x01, 0x0A, 0x62 }
};
#endif
