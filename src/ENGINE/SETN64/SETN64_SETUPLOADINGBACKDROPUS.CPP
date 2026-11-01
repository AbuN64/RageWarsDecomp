#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/GAME_SESSION.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include <ultra64.h>
#include <PR/abi.h>
#include "COMMON/AIPROFILE.H"
#include "COMMON/OBJRECAT20V1.H"
#include <PR/gbi.h>
#include "TYPES.H"
#include "COMMON/VIDEO_DIMENSIONS.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "ENGINE/SETN64.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

#if defined(VERSION_US)
/* Sets up the loading-screen scene: resets the camera globals, loads the 0xE10 resource, builds a
 * look-at matrix from the state's field at 0x26DB0 scaled by g_backdropYawRate, links it to the active view and
 * draws the backdrop through SetN64_DrawTextLines with half the video height. */
#include "ENGINE/SETN64.H"
extern s32 g_lightingBufferIndex;
extern f32 g_backdropModelFillValue, g_backdropYawRate, g_backdropTextScalePair;
extern struct MenuModelScreen g_fallbackScreenMessageEmitter[];
extern s32 g_backdropTextLinesUs;
extern s32 Scene_FindModelIdIndex(void *, s32);
extern s32 Scene_GetIndexedModelResource(void *, s32);
extern void Camera_SetupViewportAndFog(void *);
extern void Graphu64_BuildTranslationMatrix(void *, f32, f32, f32);
extern void YawMatrixLocal(void *, f32);
extern void SwapMatrixUpForward(void *);
extern void Graphu64_ConvertMatrixToFixed(void *, void *);
extern void Geometry_QueueDirectModel(s32, void *, void *, s32, s32);
void SetN64_SetupLoadingBackdropUs(TimedSessionTransitionView *state) {
    s32 handle, h2;
    u8 matrix[0x40];

    g_geometryFogEffectEnabled = 0;
    handle = Scene_FindModelIdIndex(&g_world, 0xE10);
    g_menuModelFillEnabled = 0;
    g_menuModelFillColor[0] = g_backdropModelFillValue;
    g_menuModelFillColor[1] = g_backdropModelFillValue;
    g_menuModelFillColor[2] = g_backdropModelFillValue;
    g_menuModelFillColor[3] = g_backdropModelFillValue;
    if (handle != -1) {
        Camera_SetupViewportAndFog(&g_fallbackScreenMessageEmitter);
        Graphu64_BuildTranslationMatrix(matrix, 0.0f, -100.0f, -500.0f);
        YawMatrixLocal(matrix, state->transitionTimer * g_backdropYawRate);
        SwapMatrixUpForward(matrix);
        Graphu64_ConvertMatrixToFixed(matrix, VIEW_MATRICES + g_lightingBufferIndex * 64);
        h2 = Scene_GetIndexedModelResource(&g_world, handle);
        Geometry_BeginModelBatch();
        Geometry_QueueDirectModel(h2, VIEW_MATRICES + g_lightingBufferIndex * 64, &g_defaultParticleLighting, 0, -1);
        Geometry_FlushModelBatch();
        SetN64_DrawTextLines(state, 0, (void *)g_backdropTextLinesUs, g_hudReferenceViewportWidth / 2, 0xBE, 0xA, g_backdropTextScalePair, (&g_backdropTextScalePair)[1]);
    }
}
#endif
