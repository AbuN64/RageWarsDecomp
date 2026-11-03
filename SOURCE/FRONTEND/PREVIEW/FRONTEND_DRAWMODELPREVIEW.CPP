#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/LONE/g_defaultCameraSurfaceType.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LABEL.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_DRAWMODELPREVIEW.H"

#include "COMMON/WORLD.H"
#include "COMMON/SCENERECAT10C0.H"
#include "COMMON/ACTOR_DEFINITION.H"
#include "ENGINE/SCENE_DRAWTRANSITIONCOLOROVERLAY.H"
#include "ENGINE/SETN64.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "GOBJINST/GAMEOBJECT_LOADMODEL.H"
#include "GOBJINST/GOBJINST_BUILDACTORPOSE.H"




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
#include <ultra64.h>
#include "COMMON/GLOBALS.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/TRIPLE.H"
#include "MENU/GFX/COMBINE_CONFIGUREPRIMITIVERENDERFLAGS.H"
#include "TYPES.H"
#include <PR/gbi.h>
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
void Gobjinst_UpdateActorRootDisplacement(struct Actor36 *actor);

void Gobjinst_RotatePoseMatrixBuffers(void *actorRenderState);

extern MenuModelScreen g_fallbackScreenMessageEmitter[];
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
            u32 address = (u32)(g_lightingBufferIndex << 6);
            address += ((char *)&((GameplayCamera *)0)->projection - (char *)0);
            address += (u32)view;
            gSPMatrix(g, (u32)address, G_MTX_LOAD | G_MTX_PROJECTION);
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

#include "COMMON/WORLD.H"
#include "UI/X_FILES/X_PLUS.H"
extern void *Scene_FindActorDefinition(void *, s32, s32, void *);
extern void Gobjinst_InitializeActor(void *, s32, s32, s32, void *, s32, s32, f32, CVector3, s32, CVector3, CVector3, s32);
extern void Gobjinst_DispatchActorTypeUpdate(char *actor);
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
    source = Scene_FindActorDefinition(&g_world, id, modelKind, g);
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

/* Copies the three-word vector passed by value into the object's vector at 0x480. */





void Preview_SetPreviewPosition(PreviewPositionView *preview, CVector3 v) {
    preview->position = v;
}

/* Copies the three-word vector passed by value into the object's vector at 0x48C. */





void Preview_SetPreviewFacing(PreviewFacingView *preview, CVector3 v) {
    preview->facing = v;
}

/* Stores angle into the word at 0x498 of the object preview. */



void Preview_SetPreviewAngle(PreviewAngleView *preview, s32 angle) {
    preview->angle = angle;
}

/* Stores a value into the word at offset 0x49C of an object; Menu_ApplySlotValueGfx_FrontendDrawmodelpreview and Frontend_ConfirmEquipmentSelection call
   it with zero, Preview_InitModelPreview writes the same word directly and Preview_DrawModelPreview reads it. */


void Preview_SetPreviewTransformUpdate(struct Object49C *object, s32 value) {
    object->value = value;
}

/* Clears the preview model type (sub190.type = 0xFFFF), then selects the matching preview model. */
void Preview_SelectPreviewModel(ModelPreview *preview, s32 id, s32 extra, s32 expected) {
    preview->sub190.type = 0xFFFF;
    Preview_SelectMatchingPreviewModel(preview, id, extra, expected);
}




