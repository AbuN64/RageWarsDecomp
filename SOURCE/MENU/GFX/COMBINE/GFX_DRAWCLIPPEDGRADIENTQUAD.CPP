#include "COMMON/TEXTURE.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include <ultra64.h>
#include <PR/gbi.h>
#include "COMMON/ARGB_COLOR.H"
#include <PR/abi.h>
#include "COMMON/TRIPLE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MENU/IMAGE_AND_DISPLAY_COMMAND_VIEWS.H"
#include "MENU/GFX/COMBINE_CONFIGUREPRIMITIVERENDERFLAGS.H"
#include "MENU/GFX/RECT.H"
#include "MENU/GFX/IMAGE.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "COMMON/RECTANGLE_DRAW.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "MENU/GFX/GFX_DRAWTEXTURERECTANGLECHUNKS.H"
#include "MENU/GFX/GFX_DRAWCLIPPEDGRADIENTQUAD.H"
#include "include_asm.h"
#include "DATA/REST_SOURCE_RECORDS.H"
#include "MENU/BUILD/DEFINITION_DATA.H"
#include "UI/QUAG/N64_ENG.H"

/* GFX_DRAWCLIPPEDGRADIENTQUAD.CPP */
/* Clips a screen rectangle to the viewport N64Eng_GetClipBounds reports, interpolating the four corner
   colours along each clipped edge, then writes the corners into vertices 0-3 with gSPModifyVertex
   (screen position, colour rotated to RGBA, texture coordinates 0) and draws them as an outline of
   four lines, or as two triangles when g_combineRenderSwitches.combineEnabled is set. */
/* Sets vertex index's screen position, colour and texture coordinates. */
static inline void put_vertex(s32 index, s32 x, s32 y, u32 color) {
    Gfx *g;

    g = g_displayListCursor++;
    gSPModifyVertex(g, index, G_MWO_POINT_XYSCREEN, (x << 18) | ((y & 0xFFFF) << 2));
    g = g_displayListCursor++;
    gSPModifyVertex(g, index, G_MWO_POINT_RGBA, (color << 8) | (color >> 24));
    g = g_displayListCursor++;
    gSPModifyVertex(g, index, G_MWO_POINT_ST, 0);
}

void Combine_DrawClippedGradientQuad(f32 x, f32 y, f32 w, f32 h, u32 col0, u32 col1, u32 col2, u32 col3) {
    s32 left;
    s32 top;
    s32 right_edge;
    s32 bottom_edge;
    f32 right;
    f32 bottom;
    f32 t;
    f32 edge;
    ArgbColor *c0 = (ArgbColor *)&col0;
    ArgbColor *c1 = (ArgbColor *)&col1;
    ArgbColor *c2 = (ArgbColor *)&col2;
    ArgbColor *c3 = (ArgbColor *)&col3;

    right = (x + w) - 1.0f;
    bottom = (y + h) - 1.0f;
    N64Eng_GetClipBounds(&left, &top, &right_edge, &bottom_edge);
    if ((f32)right_edge < x || (f32)bottom_edge < y || right < (f32)left || bottom < (edge = (f32)top)) {
        return;
    }
    if (y < edge) {
        t = (bottom - edge) / h;
        y = edge;
        c0->r = (u32)(c2->r - (c2->r - c0->r) * t);
        c0->g = (u32)(c2->g - (c2->g - c0->g) * t);
        c0->b = (u32)(c2->b - (c2->b - c0->b) * t);
        c0->a = (u32)(c2->a - (c2->a - c0->a) * t);
        c1->r = (u32)(c3->r - (c3->r - c1->r) * t);
        c1->g = (u32)(c3->g - (c3->g - c1->g) * t);
        c1->b = (u32)(c3->b - (c3->b - c1->b) * t);
        c1->a = (u32)(c3->a - (c3->a - c1->a) * t);
    }
    edge = (f32)bottom_edge;
    if (edge < bottom) {
        t = (edge - y) / h;
        bottom = edge;
        c2->r = (u32)(c0->r + (c2->r - c0->r) * t);
        c2->g = (u32)(c0->g + (c2->g - c0->g) * t);
        c2->b = (u32)(c0->b + (c2->b - c0->b) * t);
        c2->a = (u32)(c0->a + (c2->a - c0->a) * t);
        c3->r = (u32)(c1->r + (c3->r - c1->r) * t);
        c3->g = (u32)(c1->g + (c3->g - c1->g) * t);
        c3->b = (u32)(c1->b + (c3->b - c1->b) * t);
        c3->a = (u32)(c1->a + (c3->a - c1->a) * t);
    }
    edge = (f32)left;
    if (x < edge) {
        t = (right - edge) / w;
        x = edge;
        c0->r = (u32)(c1->r - (c1->r - c0->r) * t);
        c0->g = (u32)(c1->g - (c1->g - c0->g) * t);
        c0->b = (u32)(c1->b - (c1->b - c0->b) * t);
        c0->a = (u32)(c1->a - (c1->a - c0->a) * t);
        c2->r = (u32)(c3->r - (c3->r - c2->r) * t);
        c2->g = (u32)(c3->g - (c3->g - c2->g) * t);
        c2->b = (u32)(c3->b - (c3->b - c2->b) * t);
        c2->a = (u32)(c3->a - (c3->a - c2->a) * t);
    }
    edge = (f32)right_edge;
    if (edge < right) {
        t = (edge - x) / w;
        right = edge;
        c1->r = (u32)(c0->r + (c1->r - c0->r) * t);
        c1->g = (u32)(c0->g + (c1->g - c0->g) * t);
        c1->b = (u32)(c0->b + (c1->b - c0->b) * t);
        c1->a = (u32)(c0->a + (c1->a - c0->a) * t);
        c3->r = (u32)(c2->r + (c3->r - c2->r) * t);
        c3->g = (u32)(c2->g + (c3->g - c2->g) * t);
        c3->b = (u32)(c2->b + (c3->b - c2->b) * t);
        c3->a = (u32)(c2->a + (c3->a - c2->a) * t);
    }
    right += 1.0f;
    bottom += 1.0f;
    put_vertex(0, x, y, col0);
    put_vertex(1, x, bottom, col2);
    put_vertex(2, right, bottom, col3);
    put_vertex(3, right, y, col1);
    if (g_combineRenderSwitches.combineEnabled == 0) {
        gSPLine3D(g_displayListCursor++, 0, 1, 0);
        gSPLine3D(g_displayListCursor++, 1, 2, 0);
        gSPLine3D(g_displayListCursor++, 2, 3, 0);
        gSPLine3D(g_displayListCursor++, 3, 0, 0);
    } else {
        gSP2Triangles(g_displayListCursor++, 0, 1, 2, 0, 2, 3, 0, 0);
    }
}

/* Switches the graphics combiner and emits a pipeline sync once per frame. */
extern int g_combineCachedCombineMode;
static inline void Gradient_PipeSync(void){g_combinePipelineSyncPending=1;gDPPipeSync(g_displayListCursor++);}

void Combine_SetCombineMode(s32 mode){
 if(mode!=g_combineCachedCombineMode){
 g_combineCachedCombineMode=mode;
 if(!g_combinePipelineSyncPending)Gradient_PipeSync();
 gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
 switch(mode){
 case 1: if(g_primitiveRenderFlagSelect3000){gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT);}else{gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, 1, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, 1);}break;
 case 2: if(g_primitiveRenderFlagSelect3000){gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, PRIMITIVE);}else{gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, 1, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, 1);}break;
 case 3: gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, 1, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, 1);break;
 case 4: if(g_primitiveRenderFlagSelect3000){gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0);}else{gDPSetCombineLERP(g_displayListCursor++, TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, TEXEL0, 0, SHADE, 0, 0, 0, 0, 1);}break;
 case 5: if(g_primitiveRenderFlagSelect3000){gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE);}else{gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, 1, 0, 0, 0, SHADE, 0, 0, 0, 1);}break;
 }
 }
}

/* Selects vertex mode when it differs from g_combineCachedPrimitiveMode: mode 9 loads an identity model matrix
   through XMath_SetIdentityMatrix and Image_EmitMatrix, transforms the point (0, 0, g_gradientQuadProjectionDepth) by the view
   g_uiPointTransform, loads four white vertices at that point and marks each vertex's screen position for
   modification. */

extern s32 g_combineCachedPrimitiveMode;

extern char g_uiPointTransform;

extern void XMath_SetIdentityMatrix(s32 matrixAddress);
extern s32 ESmem_AllocateFrameHeapHigh(s32 byteCount);

void Combine_SetPrimitiveVertexMode(s32 mode) {
    CVector3 point;
    CVector3 projected;
    Matrix identity;
    Vtx10 *vertices;
    s32 count;
    s32 i;

    if (mode == g_combineCachedPrimitiveMode) {
        return;
    }
    if (mode == 9) {
        XMath_SetIdentityMatrix(&identity);
        Image_EmitMatrix(&identity);
        point.x = 0.0f;
        point.y = 0.0f;
        point.z = g_gradientQuadProjectionDepth;
        Graphu64_TransformPoint(&g_uiPointTransform, &point, &projected);
        count = 4;
        vertices = ESmem_AllocateFrameHeapHigh(64);
        for (i = 0; i < count; i++) {
            vertices[i].v.ob[0] = projected.x;
            vertices[i].v.ob[1] = projected.y;
            vertices[i].v.ob[2] = projected.z;
            vertices[i].v.tc[0] = 0;
            vertices[i].v.tc[1] = 0;
            vertices[i].v.cn[0] = 0xFF;
            vertices[i].v.cn[1] = 0xFF;
            vertices[i].v.cn[2] = 0xFF;
            vertices[i].v.cn[3] = 0xFF;
        }
        {
            Gfx *cmd = g_displayListCursor++;
            gSPVertex(cmd, (u32)vertices, count, 0);
        }
        for (i = 0; i < count; i++) {
            Gfx *cmd = g_displayListCursor++;
            gSPModifyVertex(cmd, i, G_MWO_POINT_ZSCREEN, 0);
        }
    }
    g_combineCachedPrimitiveMode = mode;
}

/* Selects render mode 11 or 12 (always 11 while g_combineRenderSwitches's enable word is clear) when it differs
   from the cached mode g_combineCachedRenderMode: flushes through Rect_ResetRenderState and applies the mode word built
   from the mode's base bits (0x53 or 0x33, with bit 2 when the first switch is set), then 0x300 or
   0x500, 0x3000 or 0x5000 and 0x30000 or 0x50000 chosen by the three further switches, through
   Combine_ConfigurePrimitiveRenderFlags. */

extern s32 g_combineCachedRenderMode;

void Combine_SetRenderMode(s32 mode) {
    s32 bits;

    if (g_combineRenderSwitches.combineEnabled == 0) {
        mode = 11;
    }
    if (mode == g_combineCachedRenderMode) {
        return;
    }
    g_combineCachedRenderMode = mode;
    if (mode == 11) {
        Rect_ResetRenderState();
        bits = g_combineRenderSwitches.texturingEnabled ? 0x55 : 0x53;
        bits |= g_combineRenderSwitches.translucencyEnabled ? 0x300 : 0x500;
        Combine_ConfigurePrimitiveRenderFlags(bits | (g_primitiveRenderFlagSelect3000 ? 0x3000 : 0x5000) | (g_primitiveRenderFlagSelect30000 ? 0x30000 : 0x50000));
    } else if (mode == 12) {
        Rect_ResetRenderState();
        bits = g_combineRenderSwitches.texturingEnabled ? 0x35 : 0x33;
        bits |= g_combineRenderSwitches.translucencyEnabled ? 0x300 : 0x500;
        Combine_ConfigurePrimitiveRenderFlags(bits | (g_primitiveRenderFlagSelect3000 ? 0x3000 : 0x5000) | (g_primitiveRenderFlagSelect30000 ? 0x30000 : 0x50000));
    }
}

/* COMBINE.CPP */
/* Emits the display-list state for the requested flag groups: records which of five two-bit flag pairs are fully set, clears the pending-sync flag and emits one pipe sync through the shared inline helper, then the other-mode and geometry-mode commands (adding the lighting bit for the fifth group) and the render mode chosen by the fourth and fifth groups, then stores the flag record. */

extern s32 g_combineRenderStateEnabled;

static inline void Combine_PipeSync(void) {
    Gfx *cmd;

    if (g_combinePipelineSyncPending == 0) {
        cmd = g_displayListCursor++;
        g_combinePipelineSyncPending = 1;
        gDPPipeSync(cmd);
    }
}

void Combine_ConfigurePrimitiveRenderFlags(s32 flags) {
    s32 plain;
    PrimitiveRenderSwitches groups;
    s32 mode;
    u32 cycle1;
    u32 cycle2;

    groups.texturingEnabled = (flags & 0x5) == 0x5;
    groups.combineEnabled = (flags & 0x30) == 0x30;
    groups.translucencyEnabled = (flags & 0x300) == 0x300;
    groups.coverageBlend = (flags & 0x3000) == 0x3000;
    groups.depthBufferEnabled = (flags & 0x30000) == 0x30000;
    Rect_ResetRenderState();
    g_combinePipelineSyncPending = 0;
    Combine_PipeSync();
    plain = groups.combineEnabled == 0;
    g_combineCachedRenderMode = plain ? 11 : 12;
    gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
    gSPGeometryMode(g_displayListCursor++, G_ZBUFFER | G_SHADE | G_CULL_FRONT | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH, 0);
    gSPGeometryMode(g_displayListCursor++, 0, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    if (groups.depthBufferEnabled) gSPGeometryMode(g_displayListCursor++, 0, G_ZBUFFER);
    cycle1 = 0;
    cycle2 = 0;
    mode = groups.coverageBlend != 0;
    if (groups.depthBufferEnabled) {
        mode += 2;
    }
    switch (mode) {
        case 0:
            cycle1 = 0xC084000;
            cycle2 = 0x3024000;
            break;
        case 1:
            cycle1 = 0x404240;
            cycle2 = 0x104240;
            break;
        case 2:
            cycle1 = 4465200;
            cycle2 = 0x112230;
            break;
        case 3:
            cycle1 = 0x404A50;
            cycle2 = 1067600;
            break;
    }
    g_combineRenderStateEnabled = 1;
    gDPSetRenderMode(g_displayListCursor++, cycle1, cycle2);
    g_combineRenderSwitches = groups;
}

/* GFX_DRAWTEXTURERECTANGLECHUNKS.CPP */
/* Makes palette the current texture lookup table for a texture of the given bit depth: returns 1
   when it already is (g_combineLoadedPalette); otherwise records it, emits one pipeline sync if none is pending
   and, for 4-bit and 8-bit textures, enables the RGBA16 lookup table and loads the 16 or 256
   palette entries (texture image, tile sync, tile, load sync, load TLUT, pipeline sync), or for
   16-bit textures turns the lookup table off; returns 0. */

extern void *g_combineLoadedPalette;

static inline void Chunks_PipeSync(void) {
    Gfx *cmd;

    if (g_combinePipelineSyncPending == 0) {
        g_combinePipelineSyncPending = 1;
        cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
    }
}

extern s32 Frontend_GetImagePixelType(u8 *);

static inline u32 blockWord16(void) {
   s32 num; s32 count;
   num=(g_combineBoundImage->stride/16>0 ? g_combineBoundImage->stride/16+2047:2048);
   count=((g_combineBoundImage->stride*g_combineBoundImage->rows+3)>>2)-1;
   if(count>=2048) count=2047;
 return _SHIFTL(G_TX_LOADTILE,24,3) | _SHIFTL(count,12,12) | _SHIFTL(g_combineBoundImage->stride/16>0 ? num/(g_combineBoundImage->stride/16):num,0,12);
}

static inline u32 blockWord8(void) {
   s32 num; s32 count;
   num=(g_combineBoundImage->stride/8>0 ? g_combineBoundImage->stride/8+2047:2048);
   count=((g_combineBoundImage->stride*g_combineBoundImage->rows+1)>>1)-1;
   if(count>=2048) count=2047;
 return _SHIFTL(G_TX_LOADTILE,24,3) | _SHIFTL(count,12,12) | _SHIFTL(g_combineBoundImage->stride/8>0 ? num/(g_combineBoundImage->stride/8):num,0,12);
}

static inline u32 blockWord4(void) {
   s32 num; s32 count;
   num=(g_combineBoundImage->stride/4>0 ? g_combineBoundImage->stride/4+2047:2048);
   count=g_combineBoundImage->stride*g_combineBoundImage->rows-1;
   if(count>=2048) count=2047;
 return _SHIFTL(G_TX_LOADTILE,24,3) | _SHIFTL(count,12,12) | _SHIFTL(g_combineBoundImage->stride/4>0 ? num/(g_combineBoundImage->stride/4):num,0,12);
}

static __inline__ void rectangleEmit(u32 w0, u32 w1) { Gfx *cmd = g_displayListCursor++; cmd->words.w0 = w0; cmd->words.w1 = w1; }

static __inline__ void rectangleSync(void) {
 Gfx *cmd;
 if (g_combinePipelineSyncPending == 0) { g_combinePipelineSyncPending = 1; cmd = g_displayListCursor++; gDPPipeSync(cmd); }
}

static inline f32 scaleClip(f32 delta, f32 ratio) { return ratio * delta; }

s32 Combine_LoadPalette(s32 bits, void *palette) {
    s32 result;

    result = 1;
    if (g_combineLoadedPalette != palette) {
        g_combineLoadedPalette = palette;
        Chunks_PipeSync();
        if (bits == 4) {
            gDPSetTextureLUT(g_displayListCursor++, G_TT_RGBA16);
            gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (unsigned int)palette);
            gDPTileSync(g_displayListCursor++);
            gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
            gDPLoadSync(g_displayListCursor++);
            gDPLoadTLUTCmd(g_displayListCursor++, G_TX_LOADTILE, 15);
            gDPPipeSync(g_displayListCursor++);
        } else if (bits == 8) {
            gDPSetTextureLUT(g_displayListCursor++, G_TT_RGBA16);
            gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (unsigned int)palette);
            gDPTileSync(g_displayListCursor++);
            gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 256, G_TX_LOADTILE, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
            gDPLoadSync(g_displayListCursor++);
            gDPLoadTLUTCmd(g_displayListCursor++, G_TX_LOADTILE, 255);
            gDPPipeSync(g_displayListCursor++);
        } else if (bits == 16) gDPSetTextureLUT(g_displayListCursor++, G_TT_NONE);
        result = 0;
    }
    return result;
}

void Combine_BindImageTexture(Texture *image) {
 s32 paletteSame,flags,size;
 Texture *tex=image;
 if (image == 0) {
 g_combineBoundImageWidth=0; g_combineBoundImageHeight=0; g_combineBoundImage=0;
 g_combineImageRequiresChunks=0; g_combineImageChunkState=0; g_combineBoundImageMaskComponent=0;
 } else {
 g_combineBoundImage=tex; g_combineImageChunkState=0;
 g_combineBoundImageWidth=tex->width; g_combineBoundImageHeight=tex->height;
 g_combineBoundImagePixelType=Frontend_GetImagePixelType(&tex->format);
 g_combineBoundImageMaskComponent=Frontend_HasImageFormatMaskComponent(&g_combineBoundImage->format);
 flags=tex->flags;size=tex->size;
 g_combineImageRequiresChunks=0;
 if(flags>0 && size>2048) g_combineImageRequiresChunks=1;
 if(flags==0 && size>4096) g_combineImageRequiresChunks=1;
 paletteSame=Combine_LoadPalette(g_combineBoundImagePixelType,g_combineBoundImage->palette);
 if(g_combineImageRequiresChunks==0) {
  if(g_combineBoundImagePixelType==4) {
   gDPSetTextureImage(g_displayListCursor++,G_IM_FMT_CI,G_IM_SIZ_16b,1,g_combineBoundImage->data);
   gDPSetTile(g_displayListCursor++,G_IM_FMT_CI,G_IM_SIZ_16b,0,0,7,0,2,0,0,2,0,0);
   gDPLoadSync(g_displayListCursor++);
   { Gfx *g = g_displayListCursor++; g->words.w0 = _SHIFTL(G_LOADBLOCK,24,8); g->words.w1 = blockWord16(); }
   gDPPipeSync(g_displayListCursor++);
   gDPSetTile(g_displayListCursor++,G_IM_FMT_CI,G_IM_SIZ_4b,(((s16)(u16)g_combineBoundImage->stride >> 1)+7)>>3,0,0,0,2,0,0,2,0,0);
   gDPSetTileSize(g_displayListCursor++,0,0,0,(g_combineBoundImage->stride-1)*4,(g_combineBoundImage->rows-1)*4);
  }
  else if(g_combineBoundImagePixelType==8) {
   if(paletteSame==0) {
    gDPSetTile(g_displayListCursor++,G_IM_FMT_CI,G_IM_SIZ_16b,0,0,7,0,2,0,0,2,0,0);
    gDPPipeSync(g_displayListCursor++);
   }
   gDPLoadSync(g_displayListCursor++);
   gDPSetTile(g_displayListCursor++,G_IM_FMT_CI,G_IM_SIZ_8b,(g_combineBoundImage->stride+7)>>3,0,0,0,2,0,0,2,0,0);
   gDPSetTileSize(g_displayListCursor++,0,0,0,(g_combineBoundImage->stride-1)*4,(g_combineBoundImage->rows-1)*4);
   gDPSetTextureImage(g_displayListCursor++,G_IM_FMT_CI,G_IM_SIZ_16b,1,g_combineBoundImage->data);
   { Gfx *g = g_displayListCursor++; g->words.w0 = _SHIFTL(G_LOADBLOCK,24,8); g->words.w1 = blockWord8(); }
  }
  else if(g_combineBoundImagePixelType==16) {
   gDPSetTextureImage(g_displayListCursor++,G_IM_FMT_RGBA,G_IM_SIZ_16b,1,g_combineBoundImage->data);
   gDPSetTile(g_displayListCursor++,G_IM_FMT_RGBA,G_IM_SIZ_16b,0,0,7,0,2,0,0,2,0,0);
   gDPLoadSync(g_displayListCursor++);
   { Gfx *g = g_displayListCursor++; g->words.w0 = _SHIFTL(G_LOADBLOCK,24,8); g->words.w1 = blockWord4(); }
   gDPPipeSync(g_displayListCursor++);
   gDPSetTile(g_displayListCursor++,G_IM_FMT_RGBA,G_IM_SIZ_16b,(g_combineBoundImage->stride*2+7)>>3,0,0,0,2,0,0,2,0,0);
   gDPSetTileSize(g_displayListCursor++,0,0,0,(g_combineBoundImage->stride-1)*4,(g_combineBoundImage->rows-1)*4);
  }
 }
 }
}

void Combine_DrawClippedImageRectangle(f32 x, f32 y, f32 unusedDepth, f32 width, f32 height, f32 startU, f32 startV, f32 endU, f32 endV, u32 color) {
    s32 clipLeft;
    s32 clipTop;
    s32 clipRight;
    s32 clipBottom;
    Gfx *unusedDisplayListCursor1;
    Gfx *unusedDisplayListCursor2;
    Gfx *unusedDisplayListCursor3;
    Gfx *unusedDisplayListCursor4;
    Gfx *unusedDisplayListCursor5;
    Gfx *unusedDisplayListCursor6;
    Gfx *unusedDisplayListCursor7;
    Gfx *unusedDisplayListCursor8;
    Gfx *unusedDisplayListCursor9;
    Gfx *unusedDisplayListCursor10;
    f32 rectangleX;
    f32 rectangleY;
    f32 savedLeft;
    f32 savedTop;
    f32 delta;
    f32 horizontalClipDelta;
    f32 rightU;
    f32 bottomV;
    f32 rectangleHeight;
    f32 savedStartU;
    f32 savedStartV;
    s32 defaultMode;
    s32 textureRenderMode;
    s32 mode;
    f32 leftU;
    f32 topV;
    f32 rectangleWidth;
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
    u32 packedRgbColor;

    rectangleWidth = width;
    rectangleHeight = height;
    leftU = startU;
    topV = startV;
    rightU = endU;
    rectangleX = x;
    bottomV = endV;
    rectangleY = y;
    if ((g_combineRenderSwitches.translucencyEnabled == 0) || (g_combineRenderSwitches.combineEnabled == 0)) {
        g_combineTexturedRectangleState = 0;
        g_combinePipelineSyncPending = 0;
        Combine_SetRenderMode(12);
        Combine_SetCombineMode(5);
        if (g_combineTextureTileMode != 7) {
            g_combineTextureTileMode = 7;
            rectangleSync();
            rectangleEmit(0xE3000C00, 0);

        }
        if (g_combineTextureRenderMode != 14) {
            g_combineTextureRenderMode = 14;
            rectangleSync();
            rectangleEmit(0xD7000000, 0x80008000);

        }
        if (g_combineRenderSwitches.texturingEnabled == 0) {
            Combine_SetPrimitiveVertexMode(9);
            Combine_DrawClippedGradientQuad(rectangleX, rectangleY, rectangleWidth, rectangleHeight, (u32) color, (u32) color, (u32) color, (u32) color);
        }
    } else if (g_combineRenderSwitches.texturingEnabled == 0) {
        g_combinePipelineSyncPending = 0;
        Combine_SetRenderMode(12);
        defaultMode = 13;
        textureRenderMode = defaultMode;
        if (g_combineTexturingEnabled == 0) {
            textureRenderMode = 14;
        }
        if (textureRenderMode != g_combineTextureRenderMode) {
            g_combineTextureRenderMode = textureRenderMode;
            rectangleSync();
            if (textureRenderMode == defaultMode) rectangleEmit(0xD7000002, 0x80008000);
            else if (textureRenderMode == 14) rectangleEmit(0xD7000000, 0x80008000);
        }
        if (color != g_combineRectangleColor) {
            g_combineRectangleColor = color;
            packedRgbColor = (((u32) color >> 16) << 24) | ((color & 0xFF00) << 8) | ((color & 0xFF) << 8);
            rectangleEmit(0xFB000000, packedRgbColor);
            rectangleEmit(0xFA000000, packedRgbColor | ((u32)color >> 24));
        }
        if (g_combineTextureTileMode != 7) {
            g_combineTextureTileMode = 7;
            rectangleSync();
            rectangleEmit(0xE3000C00, 0);

        }
        mode = 2;
        if (g_combineBoundImageMaskComponent != 0) {
            mode = 1;
        }
        Combine_SetCombineMode(mode);
        left = (s32) rectangleX;
        top = (s32) rectangleY;
        g_combineTexturedRectangleState = 19;
        right = (s32) ((rectangleX + rectangleWidth) - g_textureRectangleInclusivePixelOffset);
        bottom = (s32) ((rectangleY + rectangleHeight) - g_textureRectangleInclusivePixelOffset);
        if (right < left) {
            savedLeft = (f32) left;
            left = right;
            right = (s32) savedLeft;
            savedStartU = leftU;
            leftU = rightU;
            rightU = savedStartU;
            rectangleWidth = -rectangleWidth;
        }
        if (bottom < top) {
            savedTop = (f32) top;
            top = bottom;
            bottom = (s32) savedTop;
            savedStartV = topV;
            topV = bottomV;
            bottomV = savedStartV;
            rectangleHeight = -rectangleHeight;
        }
        N64Eng_GetClipBounds(&clipLeft, &clipTop, &clipRight, &clipBottom);
        if ((clipRight < right) || (left < clipLeft) || (clipBottom < bottom) || (top < clipTop)) {
            if ((clipRight >= left) && (clipBottom >= top) && (right >= clipLeft) && (bottom >= clipTop)) {
                if (top < clipTop) {
                    delta = bottomV - topV;
                    delta=scaleClip(delta, ((f32) (clipTop - top) / rectangleHeight));
                    top = clipTop;
                    rectangleHeight = (f32) ((bottom - top) + 1);
                    topV = (topV + delta);
                }
                if (clipBottom < bottom) {
                    delta = ((f32) (clipBottom - top) / rectangleHeight) * (bottomV - topV);
                    bottom = clipBottom;
                    bottomV = topV + delta;
                }
                if (left < clipLeft) {
                    horizontalClipDelta = rightU - leftU;
                    horizontalClipDelta=scaleClip(horizontalClipDelta, ((f32) (clipLeft - left) / rectangleWidth));
                    left = clipLeft;
                    rectangleWidth = (f32) ((right - left) + 1);
                    leftU = (leftU + horizontalClipDelta);
                }
                if (clipRight < right) {
                    horizontalClipDelta = ((f32) (clipRight - left) / rectangleWidth) * (rightU - leftU);
                    right = clipRight;
                    rightU = leftU + horizontalClipDelta;
                }
                goto block_51;
            }
        } else {
block_51:
            if ((rightU < leftU) || (bottomV < topV) || (g_combineImageRequiresChunks != 0)) {
                Combine_DrawTextureRectangleChunks(left, top, right, bottom, leftU, topV, rightU, bottomV);
            } else {
                Rect_EmitTextureRect(left, top, right, bottom, leftU, topV, rightU, bottomV);
            }
        }
    }
}

void Combine_DrawTextureRectangleChunks(s32 x0, s32 y0, s32 x1, s32 y1, f32 u0, f32 v0, f32 u1, f32 v1) {
    s32 scale;
    s32 dsdx;
    s32 dtdy;
    s32 rowBytes;
    s32 rows;
    s32 sStart;
    s32 vOff;
    s32 started;
    s32 bpp;
    s32 w;
    s32 st4;
    s32 h;
    s32 stride;
    s32 dx;
    s32 dy;
    s32 chunk;
    s32 y;
    s32 yNext;
    s32 yTop;
    s32 yBot;
    s32 tOff;
    u32 data;
    f32 fh;
    s32 intH;

    started = 0;
    if (g_combineBoundImage->width == 0) {
        return;
    }
    if (g_combineBoundImage->height == 0) {
        return;
    }
    if (x0 == x1) {
        return;
    }
    if (y0 == y1) {
        return;
    }
    w = g_combineBoundImage->width;
    dx = x1 - x0 + 1;
    dsdx = (s32)((u1 - u0) * (f32)w * g_textureRectangleDerivativeScale) / dx;
    h = g_combineBoundImage->height;
    fh = (v1 - v0) * (f32)h;
    dy = y1 - y0 + 1;
    intH = (s32)fh;
    dtdy = (s32)(fh * g_textureRectangleDerivativeScale) / dy;
    stride = g_combineBoundImage->stride;
    bpp = g_combineBoundImagePixelType;
    g_combineImageChunkState = 0;
    if (intH == 0) {
        scale = 1000;
    } else {
        scale = (s32)((f32)dy * g_textureRectangleDerivativeScale / fh);
    }
    x0 = x0 << 10;
    y0 = y0 << 10;
    y1 = y1 << 10;
    x1 = x1 << 10;
    vOff = (s32)(v0 * (f32)h * g_textureRectangleCoordinateScales[0]);
    switch (bpp) {
    case 4:
        st4 = (s16)(u16)g_combineBoundImage->stride;
        chunk = (0x1000 / st4) & ~1;
        rowBytes = st4 / 2;
        break;
    case 8:
        chunk = (0x800 / g_combineBoundImage->stride) & ~1;
        rowBytes = g_combineBoundImage->stride;
        break;
    case 16:
        rowBytes = g_combineBoundImage->stride * 2;
        chunk = (0x800 / g_combineBoundImage->stride) & ~1;
        break;
    case 24:
        rowBytes = g_combineBoundImage->stride * 4;
        chunk = (0x400 / g_combineBoundImage->stride) & ~1;
        break;
    default:
        rowBytes = 0;
        chunk = 0;
        break;
    }
    if (g_combineBoundImage->height < chunk) {
        chunk = g_combineBoundImage->height;
    }
    rows = g_combineBoundImage->height;
    sStart = (s32)(u0 * (f32)w * g_textureRectangleCoordinateScales[1]);
    y = 0;
    if (rows >= 0) {
        do {
            yNext = y + chunk;
            yTop = y0 + (scale * (y * 0x400 - vOff) >> 10);
            yBot = y0 + (scale * (yNext * 0x400 - vOff) >> 10) - 0x400;
            data = g_combineBoundImage->data + y * rowBytes;
            y = yNext;
            tOff = 0;
            if (yBot < yTop) {
                tOff = yTop;
                yTop = yBot;
                yBot = tOff;
                tOff = (chunk - 1) * 0x400;
            }
            if (yTop <= y1 && y0 <= yBot) {
                if (yTop < y0) {
                    tOff = tOff + ((s32)((y0 - yTop) * dtdy) >> 10);
                    yTop = y0;
                }
                if (y1 < yBot) {
                    yBot = y1;
                }
                if (g_combineImageRequiresChunks == 0) {
                    switch (bpp) {
                    case 4:
                        gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, data);
                        gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                        gDPLoadSync(g_displayListCursor++);
                        gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, ((((stride * chunk + 3) >> 2) - 1) < 2047 ? (((stride * chunk + 3) >> 2) - 1) : 2047), ((1 << 11) + (1 > stride / 16 ? 1 : stride / 16) - 1) / (1 > stride / 16 ? 1 : stride / 16));
                        gDPPipeSync(g_displayListCursor++);
                        gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_4b, ((stride >> 1) + 7) >> 3, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                        gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (stride - 1) * 4, (chunk - 1) * 4);
                        break;
                    case 8:
                        gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, data);
                        gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                        gDPLoadSync(g_displayListCursor++);
                        gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, ((((stride * chunk + 1) >> 1) - 1) < 2047 ? (((stride * chunk + 1) >> 1) - 1) : 2047), ((1 << 11) + (1 > stride / 8 ? 1 : stride / 8) - 1) / (1 > stride / 8 ? 1 : stride / 8));
                        gDPPipeSync(g_displayListCursor++);
                        gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_8b, (stride + 7) >> 3, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                        gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (stride - 1) * 4, (chunk - 1) * 4);
                        break;
                    case 16:
                        gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, data);
                        gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                        gDPLoadSync(g_displayListCursor++);
                        gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, ((stride * chunk - 1) < 2047 ? (stride * chunk - 1) : 2047), ((1 << 11) + (1 > stride / 4 ? 1 : stride / 4) - 1) / (1 > stride / 4 ? 1 : stride / 4));
                        gDPPipeSync(g_displayListCursor++);
                        gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, (stride * 2 + 7) >> 3, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                        gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (stride - 1) * 4, (chunk - 1) * 4);
                        break;
                    }
                } else {
                    switch (bpp) {
                    case 4:
                        gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, data);
                        gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                        gDPLoadSync(g_displayListCursor++);
                        gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, ((((stride * chunk + 3) >> 2) - 1) < 2047 ? (((stride * chunk + 3) >> 2) - 1) : 2047), 0);
                        gDPPipeSync(g_displayListCursor++);
                        gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_4b, ((stride >> 1) + 7) >> 3, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                        gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (stride - 1) * 4, (chunk - 1) * 4);
                        break;
                    case 8:
                        if (!started) {
                            started = 1;
                            gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                            gDPSetTile(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_8b, (stride + 7) >> 3, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                            gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (stride - 1) * 4, (chunk - 1) * 4);
                            gDPPipeSync(g_displayListCursor++);
                        }
                        gDPLoadSync(g_displayListCursor++);
                        gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, data);
                        gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, ((((stride * chunk + 1) >> 1) - 1) < 2047 ? (((stride * chunk + 1) >> 1) - 1) : 2047), 0);
                        break;
                    case 16:
                        gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, data);
                        gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                        gDPLoadSync(g_displayListCursor++);
                        gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, ((stride * chunk - 1) < 2047 ? (stride * chunk - 1) : 2047), 0);
                        gDPPipeSync(g_displayListCursor++);
                        gDPSetTile(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, (stride * 2 + 7) >> 3, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
                        gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, (stride - 1) * 4, (chunk - 1) * 4);
                        break;
                    }
                }
                gSPTextureRectangle(g_displayListCursor++, x0 >> 8, yTop >> 8, (x1 >> 8) + 4, (yBot >> 8) + 4, 0, sStart >> 5, tOff >> 5, dsdx, dtdy);
            }
        } while (y <= rows);
    }
}

/* GFX_DRAWCLIPPEDIMAGERECTANGLE_DATA.CPP */
/* 800E142C.CPP */
/* ROM-grounded data: src/g_combine_SetPrimitiveVertexModeConstantWords_GfxDrawclippedimagerectangleData.c */
const float g_combine_SetPrimitiveVertexModeConstantWords[1] = {
    -100.0f,
};

/* 800E1430.CPP */
/* ROM-grounded data: src/g_combine_DrawClippedImageRectangleConstantWords1_GfxDrawclippedimagerectangleData.c */
const float g_combine_DrawClippedImageRectangleConstantWords1[1] = {
    1.0f,
};

/* 800E1434.CPP */
/* ROM-grounded data: src/g_combine_DrawClippedImageRectangleConstantWords2_GfxDrawclippedimagerectangleData.c */
const float g_combine_DrawClippedImageRectangleConstantWords2[3] = {
    1024.0f, 1024.0f, 1024.0f,
};

/* MENU_ITEM_FRAGMENTS.CPP */
/* k_Ovl3EncodedWords_Ovl3.CPP */
#if defined(VERSION_US_REV1)

RestOvl3EncodedWordsLayout597 k_Ovl3EncodedWords = {
    { 0, 147536, 524288 },
};

struct {
    short type1;
    unsigned short reserved021;
    unsigned int flags1;
} g_menuItemFragment1Part2 = {
    0x0001,
    0x0000,
    0x90000000,
};
#endif

/* g_menuItemFragment2_Ovl3.CPP */
#if defined(VERSION_US_REV1)
extern char g_menuPaged_Menu_DrawMenuOptionSprite[];

struct {
    short x1;
    short y1;
    unsigned char red1;
    unsigned char green1;
    unsigned char blue1;
    unsigned char alpha1;
    int resource1;
} g_menuItemFragment2 = {
    0x0000,
    0x0000,
    0x00,
    0x00,
    0xFF,
    0x01,
    0x00000385,
};

struct {
    unsigned int resourceCallback1;
} g_menuItemFragment3 = {
    (unsigned int)g_menuPaged_Menu_DrawMenuOptionSprite,
};

struct {
    unsigned int callback1;
    unsigned int initializeCallback1;
    unsigned int parameter1;
    short type1;
    unsigned short reserved021;
    unsigned int flags1;
    short x1;
    short y1;
    unsigned char red1;
    unsigned char green1;
    unsigned char blue1;
    unsigned char alpha1;
} g_menuItemFragment4 = {
    0x00000000,
    0x00000000,
    0x00000000,
    0x0000,
    0x0000,
    0x08000041,
    0x0000,
    0x000A,
    0x00,
    0x00,
    0xFF,
    0x01,
};
#endif

/* G_MENUITEMFRAGMENT5.CPP */
#if defined(VERSION_US_REV1)

struct {
    int resource1;
} g_menuItemFragment5 = {
    0x800D7710,
};
#endif
