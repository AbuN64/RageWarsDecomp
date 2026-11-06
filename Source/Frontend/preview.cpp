#include "Common/gameplay_camera.h"
#include "Camera/camera_address_symbols.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Common/sharedplayer.h"
#include "Common/label.h"
#include "types.h"
#include "Frontend/frontend_drawmodelpreview.h"
#include "Common/world.h"
#include "Common/scene_switch.h"
#include "Common/actor_definition.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Engine/graphics_math.h"
#include "Engine/session.h"
#include "Game/builddirectionmatrix.h"
#include "Gobjinst/gameobject_loadmodel.h"
#include "Gobjinst/gobjinst_buildactorpose.h"
#include "include_asm.h"
#include "Common/frontend_clock_state.h"
#include "Common/particle_lighting.h"
#include "Common/runtime_declarations.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/texture.h"
#include "Common/menu_model_preview.h"

/* unit FRONTEND_DRAWMODELPREVIEW.CPP */
typedef struct FrontendModelHeader {
    u8 prefix[28];
    u16 definitionIndex;
} FrontendModelHeader;
/* Scans the world's preview model id table for entries equal to id. For each one it loads the model's index and info
 * resources; when the model's actor definition has the expected character and the preview's kind, it binds model i to
 * the preview (Gobjinst_LoadModel with extra) and stops. */
void Preview_SelectMatchingPreviewModel(ModelPreview *preview, s32 id, s32 extra, s32 expected) {
    ModelPreviewActor *previewState = &preview->sub190;
    Shared_World *scene = &g_world;
    struct SceneModelIdTable *list = scene->modelIds;
    s32 count = list->count;
    u16 *entries = list->entries;
    s32 i;
    s32 found = 0;
    void *modelName;
    void **indexResource;
    void **modelResource;
    void *modelData;
    ActorDefinitionHeader *definition;
    s32 modelSize;

    for (i = 0; i < count && !found; i++) {
        Shared_World *world = &g_world;

        if (entries[i] == id) {
            modelName = SetN64_GetDirectoryEntry(world->indexedDirectory, (void *)world->indexedBank, i);
            indexResource = Cache_RequestResource(0, (u32)modelName, (u32)modelName, 24, 0, 0, 0, "anim object index", 1);
            if (indexResource != 0) {
                modelData = SetN64_LocatePackSection(*indexResource, modelName, 0, &modelSize);
                modelResource = Cache_RequestResource(0, (u32)modelData, (u32)modelData, modelSize, 0, 0, 0, "anim object info", 1);
                if (modelResource != 0) {
                    definition = Scene_GetActorDefinition(world, ((FrontendModelHeader *)SetN64_GetPackSection(*modelResource, 0))->definitionIndex);
                    if (definition->character == expected && definition->kind == preview->actorKind) {
                        previewState->modelIndex = i;
                        previewState->type = id;
                        Gobjinst_LoadModel(previewState, world->indexedDirectory, (void *)world->indexedBank, extra);
                        found = 1;
                    }
                    Cache_UnlockResource(0, (struct CacheResourceNode *)modelResource);
                }
                Cache_UnlockResource(0, (struct CacheResourceNode *)indexResource);
            }
        }
    }
}
#include <platform_sdk.h>
#include "Common/globals.h"
#include "Common/frontend_clock_state.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/sessionhandlerrow.h"
#include "Common/shared_menureply.h"
#include "Common/triple.h"
#include "Menu/Gfx/combine_configureprimitiverenderflags.h"
#include "types.h"
#include <PR/gbi.h>
#include "Particle/graphu64_matrixfromeulerxyz.h"
void Gobjinst_UpdateActorRootDisplacement(struct Actor36 *actor);

void Gobjinst_RotatePoseMatrixBuffers(void *actorRenderState);

void Preview_DrawModelPreview(ModelPreview *self) {
    CVector3 local10;
    CVector3 local20;
    MenuModelScreen *view;
    ModelPreviewActor *draw;
    s32 saved;
    view = g_fallbackScreenMessageEmitter;
    draw = &self->sub190;
    if (self->modelLoaded != 0) {
        saved = g_geometryFogEffectEnabled;
        g_geometryFogEffectEnabled = 0;
        {
            Gfx *g = g_displayListCursor++;
            gSPMatrix(g, (u32)((GameplayCamera *)view)->projection[g_lightingBufferIndex], G_MTX_LOAD | G_MTX_PROJECTION);
        }
        local10 = self->facing;
        Graphu64_TransformPoint(&view->camera, &local10, &local20);
        if (Cache_GetResourceActivityState() == 0) {
            Cache_SetResourceActivityState(1);
        }
        Combine_ConfigurePrimitiveRenderFlags(0x33335);
        gDPPipeSync(g_displayListCursor++);
        gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
        gDPSetTexturePersp(g_displayListCursor++, G_TP_PERSP);
        gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
        Geometry_InitializeModelRenderState();
        draw->position = local20;
        draw->referencePosition = local20;
        Gobjinst_RotatePoseMatrixBuffers(draw);
        draw->position = local20;
        draw->referencePosition = local20;
        if (self->updatePose != 0 || draw->animationPending == 0) {
            Gobjinst_UpdateActorRootDisplacement(draw);
            if (self->pitchDegrees != 0) {
                PitchMatrixLocal(&draw->transform, (f32)self->pitchDegrees * 0.017453294f);
            }
        }
        draw->yaw = self->angleDegrees * 0.017453294f;
        draw->position = local20;
        draw->referencePosition = local20;
        Geometry_BeginModelBatch();
        Gobjinst_DrawVisibleCachedActor(draw, view);
        draw->lightingZero = g_menuModelPreviewLighting;
        draw->lightingOne = g_menuModelPreviewLighting;
        Geometry_FlushModelBatch();
        g_geometryFogEffectEnabled = saved;
    }
}

#include "Common/world.h"
#include "Ui/X_files/x_plus.h"
#include "Gobjinst/gobjinst_findnearestbonebounds.h"
#include "Scene/scene_drawtransitioncoloroverlay.h"
#include "Frontend/frontend_address_symbols.h"
/* Starts a menu model preview: loads the projection, spawns the model through Scene_FindActorDefinition, keeps a copy
 * of its record, places it scaled to the screen and runs its first update. Returns the copy, or 0 when no model. */
void *Preview_InitModelPreview(ModelPreview *self, s32 id, s32 modelKind, s32 previewModelId, s32 extra, CVector3 position, CVector3 facing,
                       f32 scale, s32 pitchDegrees) {
    CVector3 scales;
    CVector3 local60;
    CVector3 local70;
    CVector3 local80;
    MenuModelScreen *view;
    ModelPreviewActor *draw;
    Gfx *g;
    f32 ratio;
    PreviewActorDefinition *source;
    XPlus_FillMemory(&local60, 0, sizeof(local60));
    g = g_displayListCursor++;
    view = g_fallbackScreenMessageEmitter;
    gSPMatrix(g, &view->matrices[g_lightingBufferIndex], G_MTX_LOAD | G_MTX_PROJECTION);
    self->updatePose = 1;
    self->pitchDegrees = pitchDegrees;
    draw = &self->sub190;
    source = Scene_FindActorDefinition(&g_world, id, modelKind);
    if (source == 0) {
        self->modelLoaded = 0;
        return 0;
    }
    self->angleDegrees = scale;
    self->actorKind = id;
    self->modelLoaded = 1;
    self->copy4 = *source;
    self->position = position;
    self->facing = facing;
    self->copy4.kind = 0;
    self->copy4.gate = 0;
    self->copy4.flags = 0;
    self->copy4.boundsA = 0;
    self->copy4.boundsB = 0;
    self->copy4.presetFloat = 10240.0f;
    ratio = view->width / (f32)g_hudReferenceViewportWidth;
    scales.x = self->position.x * ratio;
    scales.z = self->position.z * ratio;
    scales.y = self->position.y * (view->height / (f32)g_hudReferenceViewportHeight);
    draw->scale = scales;
    local70 = self->facing;
    Graphu64_TransformPoint(&view->camera, &local70, &local80);
    Gobjinst_InitializeActor(draw, -1, previewModelId, g_defaultCameraSurfaceType, &self->copy4, -1, 0, self->angleDegrees * 0.017453294f, local80, 0,
                     self->position, local60, 0);
    Gobjinst_DispatchActorTypeUpdate(draw);
    if (self->actorKind == 9) {
        Preview_SelectPreviewModel(self, previewModelId, extra, modelKind);
    }
    return &self->copy4;
}

/* Copies the three-word vector passed by value into the preview's position. */
void Preview_SetPreviewPosition(PreviewPositionView *preview, CVector3 v) {
    preview->position = v;
}

/* Copies the three-word vector passed by value into the preview's facing. */
void Preview_SetPreviewFacing(PreviewFacingView *preview, CVector3 v) {
    preview->facing = v;
}

/* Stores angle as the preview's angle. */
void Preview_SetPreviewAngle(PreviewAngleView *preview, s32 angle) {
    preview->angle = angle;
}

/* Stores the transform-update flag of the preview object; Menu_ApplySlotValueGfx_FrontendDrawmodelpreview and Frontend_ConfirmEquipmentSelection call
   it with zero, Preview_InitModelPreview writes the same flag directly and Preview_DrawModelPreview reads it. */
void Preview_SetPreviewTransformUpdate(struct Object49C *object, s32 value) {
    object->value = value;
}

/* Clears the preview model type (sub190.type = 0xFFFF), then selects the matching preview model. */
void Preview_SelectPreviewModel(ModelPreview *preview, s32 id, s32 extra, s32 expected) {
    preview->sub190.type = 0xFFFF;
    Preview_SelectMatchingPreviewModel(preview, id, extra, expected);
}

/* unit PREVIEW.CPP */
#include <PR/abi.h>
#include "types.h"
#include <PR/gbi.h>
#include "Menu/Gfx/combine_configureprimitiverenderflags.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include <platform_sdk.h>
#include "Game/builddirectionmatrix.h"
#include "Geometry/geometry_drawblendparts.h"
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#include "Graphu64/builddirectionmatrix.h"
#include "N64_eng/N64_Eng.h"
#include "Frontend/frontend_address_symbols.h"
#include "Camera/camera_address_symbols.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Frontend/frontend.h"
#include "Cache/cache_allocateresourceat.h"
#include "Scene/cache_requestresource.h"

/* Draws a menu model with screen-scaled translation, animated and fixed rotations, restoring the render-state flag afterward; the unsigned offset-to-pointer cast preserves matrix-address scheduling. */
#if !(defined(VERSION_US_REV1))

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
  if(item->speed.z!=0.0f)RollMatrixLocal(&matrix,time*item->speed.z*g_menuModelPreviewRollAndRotationScales[0]);
  if(item->rotation.x!=0.0f)PitchMatrixLocal(&matrix,item->rotation.x*g_menuModelPreviewRollAndRotationScales[1]);
  if(item->rotation.y!=0.0f)YawMatrixLocal(&matrix,item->rotation.y*g_menuModelPreviewRollAndRotationScales[2]);
  if(item->rotation.z!=0.0f)RollMatrixLocal(&matrix,item->rotation.z*g_menuModelPreviewRollAndRotationScales[3]);
  ratio=g_fallbackScreenMessageEmitter[0].width/(f32)g_hudReferenceViewportWidth;
  scale.x=item->scale.x*ratio;
  scale.z=item->scale.z*ratio;
  scale.y=item->scale.y*(g_fallbackScreenMessageEmitter[0].height/(f32)*(&g_hudReferenceViewportWidth+1));
  ScaleMatrixLocal(&matrix,scale.x,scale.y,scale.z);SwapMatrixUpForward(&matrix);
  Graphu64_ConvertMatrixToFixed(&matrix,&item->matrices[g_lightingBufferIndex]);
  model=Scene_GetIndexedModelResource(&g_world,item->model);Geometry_BeginModelBatch();
  Geometry_QueueDirectModel(model,&item->matrices[g_lightingBufferIndex],&g_defaultParticleLighting,0,item->flags);
  Geometry_FlushModelBatch();
 }
 g_geometryFogEffectEnabled=saved;
}

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US)
char k_PreviewEncodedBytes[8] =
    "equR\000\000I\001";
#endif

#if defined(VERSION_EU_X)
unsigned int k_previewAlignMaskAndLimit[2] = {
    0xFFFFFFF8, 0x00000017,
};
#endif

#if defined(VERSION_EU)
unsigned int k_previewInstructionWords[2] = {
    0x02098024, 0x2251FFFA,
};
#endif

#if defined(VERSION_DE)
unsigned int k_previewPointerPair[2] = {
    0x00439D80, 0x00439D88,
};
#endif

/* Initializes the six object parameters and clears its transient state. */
s32 Model_SetPreviewModel(struct RecordFrontendSetPreviewModel *record, s32 count);

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

/* Stores the preview rotation vector of the object. */
void Frontend_SetPreviewRotation(struct PreviewRotationView *object, struct Triple vector) {
    object->rotation = vector;
}

/* Returns the preview rotation vector of the object by value. */
struct Triple Frontend_GetPreviewRotation(struct PreviewRotationView *object) {
    return object->rotation;
}

/* Stores the preview rotation speed vector of the object. */
void Frontend_SetPreviewRotationSpeed(struct ModelPreviewRotationSpeedView *object, struct Triple vector) {
    object->vector = vector;
}

/* Returns the preview rotation speed vector of the object by value. */
struct Triple Frontend_GetPreviewRotationSpeed(struct ModelPreviewRotationSpeedView *object) {
    return object->vector;
}

#if defined(VERSION_US_REV1)

#endif

/* unit MENU_MODEL_PREVIEW_ANGLE_AND_UNIT_SCALE.CPP */
#if defined(VERSION_US_REV1)
float g_menuModelPreviewAngleAndUnitScale[2] = {
    0.017453294f, 1.0f,
};
#endif

/* Retained data for this translation unit. */
#if !(defined(VERSION_US_REV1))
const float g_menuModelPreviewAngleScale[1] = {
    0.017453294f,
};
#endif
#if !(defined(VERSION_US_REV1))
const float k_PreviewEncodedWords[4] = {
    0.017453294f, 0.017453294f, 0.017453294f, 0.017453294f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_menuModelPreviewDegreesToRadians[6] = {
    0.017453294f, 0.017453294f, 0.017453294f, 0.017453294f, 0.017453294f, 0.017453294f,
};
#endif
