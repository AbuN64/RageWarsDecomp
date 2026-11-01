#include <ultra64.h>
#include <PR/gbi.h>
extern char g_particleQuadVertices[];
extern char g_playerModelLighting[];
#include "DATA_OVERLAY_LAYOUTS.H"


#if defined(VERSION_US)
#if defined(VERSION_US)
Gfx k_LinktablesEncodedWordsBlock5[11] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTextureL(0x8000, 0x8000, 0, 0xFF, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104E50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPEndDisplayList(),
};
#endif
#endif
