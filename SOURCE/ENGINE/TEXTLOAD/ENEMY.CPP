#include <ultra64.h>
#include <PR/gbi.h>


/* k_enemyTextBytes_Enemy.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/shared/800D0EFC */
/* Light colour bytes (r, g, b, pad): bytes so every host reads the same colour. */
const char k_enemyTextBytes[4] = "888";
#endif

/* g_enemyLightingDisplayListStorage_Enemy.CPP */
#if defined(VERSION_US_REV1)
/* A light (colour, colour copy, direction) read bytewise by the RSP, then the display list words that follow it. */
struct {
    unsigned char light[16];
    unsigned int list[12];
} g_enemyLightingDisplayListStorage = {
    { 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xD9000000, 0x00000000, 0xD9FFFFFF, 0x00000001,
      0xDB020000, 0x00000018, 0xDC08060A, 0x800D0EE8, 0xDC08090A, 0x800D0EE0, 0xDF000000, 0x00000000 },
};
#endif

/* g_enemyConstantWords_Enemy.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
Gfx g_enemyConstantWords[12] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 20, 2, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 23, 1, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 16, 1, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 19, 1, 0x00080000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 12, 2, 0x00002000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 9, 3, 0x00000C00),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 8, 1, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 2, 0x00000000),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};
#endif

/* g_enemyConstantWordsBlock1_Enemy.CPP */
#if defined(VERSION_US_REV1)
Gfx g_enemyConstantWordsBlock1[16] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 1, 0, 0, 4, 1, 0, 4, 1),
    gsDPSetTileSize(1, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 2, 0, 0, 3, 2, 0, 3, 2),
    gsDPSetTileSize(2, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 3, 0, 0, 2, 3, 0, 2, 3),
    gsDPSetTileSize(3, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 4, 0, 0, 1, 4, 0, 1, 4),
    gsDPSetTileSize(4, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 5, 0, 0, 0, 5, 0, 0, 5),
    gsDPSetTileSize(5, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif

/* g_enemyConstantWordsBlock2_Enemy.CPP */
#if defined(VERSION_US_REV1)
Gfx g_enemyConstantWordsBlock2[16] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 1, 5, 0, 1, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 1, 0, 1, 4, 1, 1, 4, 1),
    gsDPSetTileSize(1, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 2, 0, 1, 3, 2, 1, 3, 2),
    gsDPSetTileSize(2, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 3, 0, 1, 2, 3, 1, 2, 3),
    gsDPSetTileSize(3, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 4, 0, 1, 1, 4, 1, 1, 4),
    gsDPSetTileSize(4, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 5, 0, 1, 0, 5, 1, 0, 5),
    gsDPSetTileSize(5, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif

/* g_enemyConstantWordsBlock3_Enemy.CPP */
#if defined(VERSION_US_REV1)
Gfx g_enemyConstantWordsBlock3[19] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 15, 0, 5, 15),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 1, 0, 0, 5, 0, 0, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 2, 0, 0, 4, 1, 0, 4, 1),
    gsDPSetTileSize(2, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 3, 0, 0, 3, 2, 0, 3, 2),
    gsDPSetTileSize(3, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 4, 0, 0, 2, 3, 0, 2, 3),
    gsDPSetTileSize(4, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 5, 0, 0, 1, 4, 0, 1, 4),
    gsDPSetTileSize(5, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 6, 0, 0, 0, 5, 0, 0, 5),
    gsDPSetTileSize(6, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00040000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif

/* g_enemyConstantWordsBlock4_Enemy.CPP */
#if defined(VERSION_US_REV1)
Gfx g_enemyConstantWordsBlock4[19] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1372, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 14, 0, 5, 14),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 1, 0, 0, 5, 0, 0, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 256, 2, 0, 0, 4, 1, 0, 4, 1),
    gsDPSetTileSize(2, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 320, 3, 0, 0, 3, 2, 0, 3, 2),
    gsDPSetTileSize(3, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 336, 4, 0, 0, 2, 3, 0, 2, 3),
    gsDPSetTileSize(4, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 340, 5, 0, 0, 1, 4, 0, 1, 4),
    gsDPSetTileSize(5, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 342, 6, 0, 0, 0, 5, 0, 0, 5),
    gsDPSetTileSize(6, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00040000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif

/* g_enemyConstantWordsBlock5_Enemy.CPP */
#if defined(VERSION_US_REV1)
Gfx g_enemyConstantWordsBlock5[19] = {
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1408, 0),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, 0, 0, 0, 6, 0, 0, 6, 0),
    gsDPSetTileSize(0, 0, 0, 252, 252),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 256, 1, 0, 0, 5, 1, 0, 5, 1),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 320, 2, 0, 0, 4, 2, 0, 4, 2),
    gsDPSetTileSize(2, 0, 0, 60, 60),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 336, 3, 0, 0, 3, 3, 0, 3, 3),
    gsDPSetTileSize(3, 0, 0, 28, 28),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 344, 4, 0, 0, 2, 4, 0, 2, 4),
    gsDPSetTileSize(4, 0, 0, 12, 12),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 348, 5, 0, 0, 1, 5, 0, 1, 5),
    gsDPSetTileSize(5, 0, 0, 4, 4),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 350, 6, 0, 0, 0, 6, 0, 0, 6),
    gsDPSetTileSize(6, 0, 0, 0, 0),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 17, 2, 0x00000000),
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPEndDisplayList(),
};
#endif
