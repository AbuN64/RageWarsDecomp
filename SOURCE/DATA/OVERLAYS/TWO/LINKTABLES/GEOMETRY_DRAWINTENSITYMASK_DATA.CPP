#include <ultra64.h>
#include <PR/gbi.h>
extern char g_particleQuadVertices[];
extern char g_playerModelLighting[];
#include "DATA_OVERLAY_LAYOUTS.H"

#include "include_asm.h"

#if defined(VERSION_US)
#if defined(VERSION_US)
Gfx k_GeometryDrawintensitymaskEncodedWords[89] = {
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
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
/* Display-list commands are logical 32-bit words on every host. */
#if defined(VERSION_US)
Gfx D_src_d4ac59de[17] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTexture(0x8000, 0x8000, 0, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104B50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPVertex(g_particleQuadVertices, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsMoveWd(4, 0x0004, 0x00000005),
    gsMoveWd(4, 0x000C, 0x00000005),
    gsMoveWd(4, 0x0014, 0x0000FFFB),
    gsMoveWd(4, 0x001C, 0x0000FFFB),
    gsSPEndDisplayList(),
};
#endif
#endif
#if defined(VERSION_US_REV1)
/* Display-list commands are logical 32-bit words on every host. */
#if defined(VERSION_US_REV1)
Gfx D_src_d4ac59de[17] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTexture(0x8000, 0x8000, 0, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104B50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPVertex(g_particleQuadVertices, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsMoveWd(4, 0x0004, 0x00000005),
    gsMoveWd(4, 0x000C, 0x00000005),
    gsMoveWd(4, 0x0014, 0x0000FFFB),
    gsMoveWd(4, 0x001C, 0x0000FFFB),
    gsSPEndDisplayList(),
};
#endif
#endif
#endif
