#include "include_asm.h"
#include <PR/gbi.h>
#include "COMMON/EFFECTCONTRIBUTION.H"
#if defined(VERSION_US)
#if defined(VERSION_US)
unsigned short D_src_b18a148a[48] = {
    0xE300, 0x1001, 0x0000, 0x0000, 0xD700, 0x0002, 0x8000, 0x8000, 0xD9F9, 0xFBFF, 0x0000, 0x0000,
    0xD9FF, 0xFFFF, 0x0021, 0x0004, 0xFCFF, 0x97FF, 0xFFFD, 0xFE38, 0xE200, 0x001C, 0xC810, 0x4B50,
    0xDB04, 0x0004, 0x0000, 0x0001, 0xDB04, 0x000C, 0x0000, 0x0001, 0xDB04, 0x0014, 0x0000, 0xFFFF,
    0xDB04, 0x001C, 0x0000, 0xFFFF, 0x0100, 0x4008, 0x8014, 0x08E0, 0xDF00, 0x0000, 0x0000, 0x0000,
};
#endif
#endif

#if defined(VERSION_US)
char s_FxDrawredparticlequadMPACTequText[8] =
    "MPACTequ";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
Gfx g_fxDrawredparticlequadDataConstantWords[12] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTexture(0x8000, 0x8000, 0, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104B50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPVertex(g_particleQuadVertices, 4, 0),
    gsSPEndDisplayList(),
};
#endif
