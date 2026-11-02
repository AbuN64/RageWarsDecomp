#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include <PR/gbi.h>
#include "ONSCRN.H"
#include "include_asm.h"

/* Text_DrawTileGrid.CPP */
extern Gfx *g_displayListCursor;

void OnScreen_GetImageEntry(OnScreenImageTableView **handle, s32 index, void **out, u8 *tag);
void OnScreen_DrawScaledIntensityTexture(void *pTexture, f32 XPos, f32 YPos, int TextureWidth, int TextureHeight, f32 ScaleX, f32 ScaleY);
void OnScreen_DrawIntensityTexture(void *pTexture, int XPos, int YPos, int TextureWidth, int TextureHeight);
void OnScreen_DrawScaledMaskedImage(void *pTexture, void *pOpacity, float XPos, float YPos, int TextureWidth, int TextureHeight, float ScaleX, float ScaleY);
void OnScreen_DrawTextureWithOpacity(void *pTexture, void *pOpacity, int XPos, int YPos, int TextureWidth, int TextureHeight);

void Text_DrawTileGrid(void *handle, s32 index, s32 initialX, s16 initialY, f32 scaleX, f32 scaleY, s32 scaled) {
    void *resource;
    u8 intensity;
    TextureTileGrid *grid;
    gDPPipeSync(g_displayListCursor++);
    if(handle != NULL) {
        OnScreen_GetImageEntry(handle,index,&resource,&intensity);
        grid=resource;
        if(grid != NULL) {
            if(intensity != 0) {
                if(scaled != 0) {
                    TextureTileGrid *branchGrid=grid;
                    TextureTileBlock *tile;
                    u32 width, height;
                    f32 x, y, column, row, startX;
                    y=(f32)initialY;
                    tile=(TextureTileBlock *)branchGrid->blocks;
                    height=0;
                    row=(f32)branchGrid->rows;
                    startX=(f32)(s16)initialX;
                    while(row-- != 0.0f) {
                        column=(f32)branchGrid->columns;
                        x=startX;
                        while(column-- != 0.0f) {
                            height=tile->height;
                            width=tile->width;
                            OnScreen_DrawScaledIntensityTexture(tile->pixels,x,y,width,height,scaleX,scaleY);
                            x+=(f32)width*scaleX;
                            tile=(TextureTileBlock *)((u8 *)tile+((width*height>>1)));
                            tile++;
                        }
                        y+=(f32)height*scaleY;
                    }
                }
                else {
                    TextureTileGrid *branchGrid=grid;
                    TextureTileBlock *tile;
                    u32 width,height;
                    s32 x,column,row;
                    s16 y;
                    y=initialY;
                    tile=(TextureTileBlock *)branchGrid->blocks;
                    height=0;
                    row=branchGrid->rows;
                    row--;
                    while(row != -1) {
                        column=branchGrid->columns;
                        column--;
                        x=(s16)initialX;
                        while(column != -1) {
                            width=tile->width;
                            height=tile->height;
                            OnScreen_DrawIntensityTexture(tile->pixels,x,y,width,height);
                            x+=width;
                            tile=(TextureTileBlock *)((u8 *)tile+((width*height>>1)));
                            tile++;
                            --column;
                        }
                        y=(s16)(y+height);
                        --row;
                    }
                }
            }
            else {
                if(scaled != 0) {
                    TextureTileGrid *branchGrid=grid;
                    TextureTileBlock *tile;
                    u32 width, height;
                    f32 x, y, column, row, startX;
                    y=(f32)initialY;
                    tile=(TextureTileBlock *)branchGrid->blocks;
                    height=0;
                    row=(f32)branchGrid->rows;
                    startX=(f32)(s16)initialX;
                    while(row-- != 0.0f) {
                        column=(f32)branchGrid->columns;
                        x=startX;
                        while(column-- != 0.0f) {
                            height=tile->height;
                            width=tile->width;
                            OnScreen_DrawScaledMaskedImage(tile->pixels,tile->pixels+width*height*2,x,y,width,height,scaleX,scaleY);
                            x+=(f32)width*scaleX;
                            tile=(TextureTileBlock *)((u8 *)tile+(width*height*2+(width*height>>1)));
                            tile++;
                        }
                        y+=(f32)height*scaleY;
                    }
                }
                else {
                    TextureTileGrid *branchGrid=grid;
                    TextureTileBlock *tile;
                    u32 width,height;
                    s32 x,column,row;
                    s16 y;
                    y=initialY;
                    tile=(TextureTileBlock *)branchGrid->blocks;
                    height=0;
                    row=branchGrid->rows;
                    row--;
                    while(row != -1) {
                        column=branchGrid->columns;
                        column--;
                        x=(s16)initialX;
                        while(column != -1) {
                            width=tile->width;
                            height=tile->height;
                            OnScreen_DrawTextureWithOpacity(tile->pixels,tile->pixels+width*height*2,x,y,width,height);
                            x+=width;
                            tile=(TextureTileBlock *)((u8 *)tile+(width*height*2+(width*height>>1)));
                            tile++;
                            --column;
                        }
                        y=(s16)(y+height);
                        --row;
                    }
                }
            }
            Cache_MarkResourceInUse(0,handle);
        }
    }
}

/* 800CB384.CPP */

/* 800CB380.CPP */
/* ROM-grounded data: src/g_OnScreen_DrawStatusBarsConstantWords_TextDrawtilegrid.c */
const float g_OnScreen_DrawStatusBarsConstantWords[1] = {
    0.7f,
};
