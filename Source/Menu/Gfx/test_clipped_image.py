"""Exercise image clipping through the actual routine and mocked renderer seams.

Usage: python3 Source/Menu/Gfx/test_clipped_image.py <scratch-directory>
"""
from pathlib import Path
import subprocess
import sys
import tempfile

source = Path(__file__).with_name("combine.cpp").read_text()
start = source.index("void Combine_DrawClippedImageRectangle(")
end = source.index("\nvoid Combine_DrawTextureRectangleChunks", start)
routine = source[start:end]
harness = r'''#include <assert.h>
#include <stdio.h>
typedef int s32; typedef unsigned int u32; typedef float f32; typedef int Gfx;
#define G_OFF 0
#define G_ON 1
static int g_combineBoundImageMaskComponent, g_combineImageRequiresChunks;
static int g_combinePipelineSyncPending, g_combineTextureRenderMode, g_combineTextureTileMode;
static int g_combineTexturedRectangleState, g_combineTexturingEnabled=1;
static u32 g_combineRectangleColor;
static f32 g_textureRectangleInclusivePixelOffset=1.0f;
static struct { int translucencyEnabled,combineEnabled,texturingEnabled; } g_combineRenderSwitches={1,1,0};
static int emitted,chunks,x0,y0,x1,y1;
static f32 u0,v0,u1,v1;
static void Combine_SetRenderMode(int v) {(void)v;}
static void Combine_SetCombineMode(int v) {(void)v;}
static void Combine_SetPrimitiveVertexMode(int v) {(void)v;}
static void rectangleSync_gfxDrawclippedgradientquad(void) {}
static void rectangleEmit_gfxDrawclippedgradientquad(u32 a,u32 b) {(void)a;(void)b;}
static void rectangleEmitTextureState_gfxDrawclippedgradientquad(int v) {(void)v;}
static f32 scaleClip_gfxDrawclippedgradientquad(f32 a,f32 b) {return a*b;}
static void Combine_DrawClippedGradientQuad(f32 x,f32 y,f32 w,f32 h,u32 a,u32 b,u32 c,u32 d) {(void)x;(void)y;(void)w;(void)h;(void)a;(void)b;(void)c;(void)d;}
static void N64Eng_GetClipBounds(int *l,int *t,int *r,int *b) {*l=0;*t=0;*r=99;*b=99;}
static void Rect_EmitTextureRect(int l,int t,int r,int b,float u,float v,float s,float q) {
 ++emitted; x0=l;y0=t;x1=r;y1=b;u0=u;v0=v;u1=s;v1=q;
}
static void Combine_DrawTextureRectangleChunks(int l,int t,int r,int b,float u,float v,float s,float q) {
 ++chunks;Rect_EmitTextureRect(l,t,r,b,u,v,s,q);
}
'''
harness += routine
harness += r'''static void draw(float x,float y,float w,float h,float u,float v,float s,float t) {
 emitted=chunks=0;
 Combine_DrawClippedImageRectangle(x,y,0,w,h,u,v,s,t,0xffffffff);
}
int main(void) {
 int side,checks=0;
 const float rejected[4][2]={{-20,10},{100,10},{10,-20},{10,100}};
 for(side=0;side<4;++side){draw(rejected[side][0],rejected[side][1],10,10,0,0,1,1);assert(!emitted);++checks;}
 draw(10,20,20,30,0,0,1,1);assert(emitted==1 && !chunks && x0==10 && y0==20 && x1==29 && y1==49);++checks;
 draw(-10,20,20,30,0,0,1,1);assert(emitted==1 && x0==0 && x1==9 && u0==0.5f && u1==1);++checks;
 draw(90,20,20,30,0,0,1,1);assert(emitted==1 && x0==90 && x1==99 && u1==0.45f);++checks;
 draw(10,-10,20,20,0,0,1,1);assert(emitted==1 && y0==0 && y1==9 && v0==0.5f);++checks;
 draw(10,90,20,20,0,0,1,1);assert(emitted==1 && y0==90 && y1==99 && v1==0.45f);++checks;
 draw(10,20,20,30,1,1,0,0);assert(emitted==1 && chunks==1);++checks;
 g_combineImageRequiresChunks=1;draw(10,20,20,30,0,0,1,1);assert(emitted==1 && chunks==1);++checks;
 printf("image clipping passed %d rejection, edge, UV and chunk cases\n",checks);
 return 0;
}
'''
with tempfile.TemporaryDirectory(prefix="image-clipping-", dir=sys.argv[1]) as temporary:
    path = Path(temporary)
    (path / "test.c").write_text(harness)
    subprocess.run(["cc", "-std=c99", str(path / "test.c"), "-o", str(path / "test")], check=True)
    subprocess.run([str(path / "test")], check=True)
