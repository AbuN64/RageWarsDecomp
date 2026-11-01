#ifndef COMMON_FONT_STYLE_AND_GLYPH_OPERATIONS_H
#define COMMON_FONT_STYLE_AND_GLYPH_OPERATIONS_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
extern void OnScreen_LoadTextTileModeOne(void);

struct OnScreenImageTableView;
typedef struct OnScreenImageTableView OnScreenImageTableView;

struct OverlayScriptTableView;


extern s32 g_creditsTextDrawingEnabled;



extern f32 OnScreen_GetGlyphWidth(void);


struct OverlayScriptPrimaryRangeView;


struct FontStyle;
typedef struct FontStyle FontStyle;


extern void OnScreen_LoadTextTileModeTwo(void);


struct OverlayScriptSecondaryRangeView;


extern float g_maskedImageTextureCoordinateScale;

struct COverlay;
typedef struct COverlay COverlay;

struct COverlay;

extern float g_hudStatusBarTextScale;




extern float g_onscreenDefaultTextScale;

struct FontStyle;
struct FontStyle {
    char pad0[0xA0];
    s32 envR;
    s32 envG;
    s32 envB;
    s32 primR;
    s32 primG;
    s32 primB;
    f32 width;
    f32 height;
    s32 shadowX; /* 0xC0 */
    s32 shadowY; /* 0xC4 */
};



struct OverlayScriptSecondaryRangeView;
typedef struct OverlayScriptSecondaryRangeView OverlayScriptSecondaryRangeView;


struct OnScreenImageTableView;

struct OverlayScriptTableView;
typedef struct OverlayScriptTableView OverlayScriptTableView;


extern FontStyle g_tutorialStatusBars;


struct OverlayScriptPrimaryRangeView;
typedef struct OverlayScriptPrimaryRangeView OverlayScriptPrimaryRangeView;

extern u8 g_fontGlyphLookup[];
extern u8 g_fontAlternateGlyphLookup[];
#endif
