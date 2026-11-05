#ifndef COMMON_RESIDENTSTATE_H
#define COMMON_RESIDENTSTATE_H
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/runtime_declarations.h"
#include "Tengine/s_artsendactivatedtext.h"
#include "Tengine/s_artsenddeactivatedtext.h"
struct ResidentState;
struct ResidentState;
struct ResidentState {
    s32 count;
    s32 index;
    s32 frame;
    s32 changed;
};

struct ResidentSlot;

struct ResidentEntry;







typedef struct ResidentState ResidentState;
typedef struct ResidentSlot ResidentSlot;
typedef struct ResidentEntry ResidentEntry;



struct SelectionTextLoadApplyArtsendTextureOverride;



extern void Tengine_UpdateArtsendTexturePreview(void);


extern struct ResidentState g_artsendTextureSelection;



struct SelectionTextLoadApplyArtsendTextureOverride;
typedef struct SelectionTextLoadApplyArtsendTextureOverride SelectionTextLoadApplyArtsendTextureOverride;


struct AnimationInfo;
typedef struct AnimationInfo AnimationInfo;




struct AnimationInfo;




extern s32 g_artsendNextTextureHoldCount;

extern s32 g_artsendPreviousTextureHoldCount;

extern s32 g_artsendPreviousPageHoldCount;

extern s32 g_artsendNextPageHoldCount;

extern void Tengine_LoadSelectedTexture(void);


extern f32 g_artsendTextureTitleScale;
extern s32 g_artsendToggleButtonHeld;


/* Texture animation metadata returned to material and texture consumers. */
#include "Anim/animation_frame.h"



extern void TextLoad_ApplyArtsendTextureOverride(s32 resource, s32 **data);
extern void TextLoad_ApplyArtsendPaletteOverride(s32 resource, s32 **data);
extern s32 g_textureFrameCacheFrame;
extern s32 g_textureFrameCacheVariation;
extern s32 g_textureFrameCacheWrapS;
extern s32 g_textureFrameCacheWrapT;
#endif
