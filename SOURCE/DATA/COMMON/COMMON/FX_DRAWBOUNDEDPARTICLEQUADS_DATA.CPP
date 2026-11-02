#include "include_asm.h"
#include <PR/gbi.h>
#include "COMMON/EFFECTCONTRIBUTION.H"
/* FxBoundedParticleQuadsDisplayList.CPP */
#if defined(VERSION_US)
#if defined(VERSION_US)
unsigned short D_src_12ed218b[48] = {
    0xE300, 0x1001, 0x0000, 0x0000, 0xD700, 0x0002, 0x8000, 0x8000, 0xD9F9, 0xFBFF, 0x0000, 0x0000,
    0xD9FF, 0xFFFF, 0x0021, 0x0004, 0xFCFF, 0x97FF, 0xFFFF, 0xFE38, 0xE200, 0x001C, 0xC810, 0x4B50,
    0xDB04, 0x0004, 0x0000, 0x0001, 0xDB04, 0x000C, 0x0000, 0x0001, 0xDB04, 0x0014, 0x0000, 0xFFFF,
    0xDB04, 0x001C, 0x0000, 0xFFFF, 0x0100, 0x4008, 0x8014, 0x08E0, 0xDF00, 0x0000, 0x0000, 0x0000,
};
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded exact candidate, normalized from prior lane proof. */
Gfx g_FxDrawboundedparticlequadsEncodedWordsBlock1[12] = {
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
    gsSPEndDisplayList(),
};
#endif

/* FxBoundedParticleQuadsShortDisplayList.CPP */
#if defined(VERSION_US_REV1)
Gfx g_FxDrawboundedparticlequadsEncodedWords[11] = {
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
