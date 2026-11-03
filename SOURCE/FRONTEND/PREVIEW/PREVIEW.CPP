#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/WORLD.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "include_asm.h"
#include "COMMON/PARTICLE_LIGHTING.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/TEXTURE.H"
#include "COMMON/OBJECTRECAT28.H"
#include <PR/abi.h>
#include "TYPES.H"
#include <PR/gbi.h>
#include "MENU/GFX/COMBINE_CONFIGUREPRIMITIVERENDERFLAGS.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <ultra64.h>
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "GEOMETRY/GEOMETRY_DRAWBLENDPARTS.H"
#include "MENU/ITEMS/SCENE/SCENE_FINDACTORTRIGGERRANGE.H"

/* 8043962C_13.CPP */
/* Draws a menu model with screen-scaled translation, animated and fixed rotations, restoring the render-state flag afterward; the unsigned offset-to-pointer cast preserves matrix-address scheduling. */
extern MenuModelScreen g_fallbackScreenMessageEmitter[]; extern Gfx *g_displayListCursor;
extern s32 g_lightingBufferIndex, g_hudReferenceViewportWidth;
#if defined(VERSION_DE)
extern float g_menuModelPreviewPitchSpeedScale;
extern float g_menuModelPreviewRollAndRotationScales;
#elif defined(VERSION_EU)
extern float g_menuModelPreviewPitchSpeedScale;
extern float g_menuModelPreviewRollAndRotationScales;
#elif defined(VERSION_EU_X)
extern float g_menuModelPreviewPitchSpeedScale;
extern float g_menuModelPreviewRollAndRotationScales;
#elif defined(VERSION_US)
extern float g_menuModelPreviewPitchSpeedScale;
extern float g_menuModelPreviewRollAndRotationScales;
#elif defined(VERSION_US_REV1)
extern float g_menuModelPreviewPitchSpeedScale;
extern float g_menuModelPreviewRollAndRotationScales;
#endif
 extern void YawMatrixLocal(Matrix *,f32); extern void RollMatrixLocal(Matrix *,f32);
 extern void SwapMatrixUpForward(Matrix *);
extern s32 N64Eng_GetFrameCounter(void); extern void Graphu64_ConvertMatrixToFixed(Matrix *,void *);


#if !(defined(VERSION_US_REV1))
const float g_menuModelPreviewAngleScale[1] = {
    0.017453294f,
};
#endif
void Preview_DrawMenuModelItem(MenuModelItem *item) {
 Matrix matrix;
 CVector3 position, transformed, scale;
 s32 model;
 s32 saved;
 f32 time, ratio;
 saved=g_geometryFogEffectEnabled; g_geometryFogEffectEnabled=0;
 if (item->model != -1) {
  Combine_ConfigurePrimitiveRenderFlags(0x33335);
  gDPPipeSync(g_displayListCursor++);
  gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
  gDPSetTexturePersp(g_displayListCursor++, G_TP_PERSP);
  gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
  Geometry_InitializeModelRenderState();
  {Gfx *g=g_displayListCursor++; char *address=(char *)(u32)(g_lightingBufferIndex<<6); address += ((char *)&((GameplayCamera *)0)->projection - (char *)0); address+=(u32)g_fallbackScreenMessageEmitter; gSPMatrix(g, (u32)address, G_MTX_LOAD | G_MTX_PROJECTION);}
  position=item->position;
  Graphu64_TransformPoint(&g_fallbackScreenMessageEmitter[0].camera,&position,&transformed);
  Graphu64_BuildTranslationMatrix(&matrix, transformed.x, transformed.y, transformed.z);
  time=N64Eng_GetFrameCounter();
  if(item->speed.x!=0.0f)PitchMatrixLocal(&matrix,time*item->speed.x*g_menuModelPreviewPitchSpeedScale);
#if defined(VERSION_DE)
  if(item->speed.y!=0.0f)YawMatrixLocal(&matrix,time*item->speed.y*(0.01745329424738884f));
#elif defined(VERSION_EU)
  if(item->speed.y!=0.0f)YawMatrixLocal(&matrix,time*item->speed.y*(0.01745329424738884f));
#elif defined(VERSION_EU_X)
  if(item->speed.y!=0.0f)YawMatrixLocal(&matrix,time*item->speed.y*(0.01745329424738884f));
#elif defined(VERSION_US)
  if(item->speed.y!=0.0f)YawMatrixLocal(&matrix,time*item->speed.y*(0.01745329424738884f));
#elif defined(VERSION_US_REV1)
  if(item->speed.y!=0.0f)YawMatrixLocal(&matrix,time*item->speed.y*g_menuModelPreviewYawSpeedScale);
#endif
  if(item->speed.z!=0.0f)RollMatrixLocal(&matrix,time*item->speed.z*g_menuModelPreviewRollAndRotationScales);
  if(item->rotation.x!=0.0f)PitchMatrixLocal(&matrix,item->rotation.x*(*(&g_menuModelPreviewRollAndRotationScales+1)));
  if(item->rotation.y!=0.0f)YawMatrixLocal(&matrix,item->rotation.y*(*(&g_menuModelPreviewRollAndRotationScales+2)));
  if(item->rotation.z!=0.0f)RollMatrixLocal(&matrix,item->rotation.z*(*(&g_menuModelPreviewRollAndRotationScales+3)));
  ratio=g_fallbackScreenMessageEmitter[0].width/(f32)g_hudReferenceViewportWidth;
  scale.x=item->scale.x*ratio;
  scale.z=item->scale.z*ratio;
  scale.y=item->scale.y*(g_fallbackScreenMessageEmitter[0].height/(f32)*(&g_hudReferenceViewportWidth+1));
  ScaleMatrixLocal(&matrix,scale.x,scale.y,scale.z);SwapMatrixUpForward(&matrix);
  Graphu64_ConvertMatrixToFixed(&matrix,item->matrices+(g_lightingBufferIndex<<6));
  model=Scene_GetIndexedModelResource(&g_world,item->model);Geometry_BeginModelBatch();
  Geometry_QueueDirectModel(model,item->matrices+(g_lightingBufferIndex<<6),&g_defaultParticleLighting,0,item->flags);
  Geometry_FlushModelBatch();
 }
 g_geometryFogEffectEnabled=saved;
}

#if !(defined(VERSION_US_REV1))
const float k_PreviewEncodedWords[4] = {
    0.017453294f, 0.017453294f, 0.017453294f, 0.017453294f,
};
#endif

#if defined(VERSION_US)
char k_PreviewEncodedBytes[8] =
    "equR\000\000I\001";
#endif

#if defined(VERSION_EU_X)
unsigned int k_PreviewEncodedWordsBlock2[2] = {
    0xFFFFFFF8, 0x00000017,
};
#endif

#if defined(VERSION_EU)
unsigned int k_PreviewEncodedWordsBlock3[2] = {
    0x02098024, 0x2251FFFA,
};
#endif

#if defined(VERSION_DE)
unsigned int k_PreviewEncodedWordsBlock1[2] = {
    0x00439D80, 0x00439D88,
};
#endif

/* 8043962C_14.CPP */
/* Initializes the six object parameters and clears its transient state. */
s32 Model_SetPreviewModel(struct RecordFrontendSetPreviewModel *record, s32 count);

 /* extern */

 /* extern */
s32 Frontend_InitModelPreviewTransform(StateFrontendInitModelPreviewTransform *preview, s32 modelId, Triple first, Triple second) {
    preview->second = second;
    preview->first = first;
    preview->rotationXBits = 0;
    preview->rotationYBits = 0;
    preview->rotationZBits = 0;
    preview->rotationSpeedXBits = 0;
    preview->rotationSpeedYBits = 0;
    preview->rotationSpeedZBits = 0;
    Model_SetPreviewModel(preview, modelId);
    Model_SetPreviewRenderFlags(preview, 0);
    return preview->modelId;
}

/* Stores a three-word vector passed by value into offset 0x1C of an object. */

void Frontend_SetPreviewRotation(struct PreviewRotationView *object, struct Triple vector) {
    object->rotation = vector;
}

/* Returns by value the three-word vector at offset 0x1C of an object. */

struct Triple Frontend_GetPreviewRotation(struct PreviewRotationView *object) {
    return object->rotation;
}

/* Stores a three-word vector passed by value into offset 0x28 of an object. */

void Frontend_SetPreviewRotationSpeed(struct ModelPreviewRotationSpeedView *object, struct Triple vector) {
    object->vector = vector;
}

/* Returns by value the three-word vector at offset 0x28 of an object. */

struct Triple Frontend_GetPreviewRotationSpeed(struct ModelPreviewRotationSpeedView *object) {
    return object->vector;
}

/* 800E1F80.CPP */

#if defined(VERSION_US_REV1)
const float g_menuModelPreviewAngleScalesUsRev1[6] = {
    0.017453294f, 0.017453294f, 0.017453294f, 0.017453294f, 0.017453294f, 0.017453294f,
};
#endif
