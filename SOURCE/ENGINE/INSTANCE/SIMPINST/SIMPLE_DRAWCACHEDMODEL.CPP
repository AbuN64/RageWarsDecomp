#include "COMMON/OBJB.H"
#include "COMMON/ACTOR_DEFINITION.H"
#include "COMMON/MODEL_RENDER.H"
#include "include_asm.h"
#include "SCENE/SIMPLE_INSTANCE_RECORD.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PROPGEOMETRY.H"
#include "WORLD/STATIC_MODEL_INSTANCE_VIEWS.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/FRUSTUM.H"
#include <PR/gbi.h>
#include "TYPES.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "SYSTEM/TEXTLOAD_RESETTEXTURECACHE.H"

#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/WORLD.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
void *Scene_GetActorDefinition(void *world, s32 index);
void Simple_InitSimpleInstance(ObjB *inst, CROMSimpleInstance *rec, s32 owner, char *segments) {
    CVector3 v;
    inst->state = 3;
    inst->id = rec->type;
    inst->scene = rec->visBits;
    inst->position = rec->position;
    inst->position.y = inst->position.y + 10.24f;
    inst->angle = rec->rotY * (3.1415927f / 127.0f);
    inst->scale = 0.35f;
    inst->height = 0;
    inst->bounds.min.x = rec->position.x - rec->maxRadius;
    inst->bounds.min.y = rec->position.y - rec->maxRadius;
    inst->bounds.min.z = rec->position.z - rec->maxRadius;
    inst->bounds.max.x = rec->position.x + rec->maxRadius;
    inst->bounds.max.y = rec->position.y + rec->maxRadius;
    inst->bounds.max.z = rec->position.z + rec->maxRadius;
    inst->animationKey = owner;
    inst->loadedType = -1;
    inst->resource = 0;
    inst->resourceSize = 0;
    if (rec->variation == 0xFFFF) {
        inst->definition = &g_defaultEffectDefinition;
    } else {
        inst->definition = Scene_GetActorDefinition(&g_world, rec->variation);
    }
    if (rec->region == 0xFFFF) {
        inst->room = 0;
    } else {
        inst->room = segments + (rec->region << 5);
    }
    inst->flags = rec->flags | 2;
    inst->scaleTime = 0;
    inst->frameDelta = 0;
    inst->placementId = rec->id;
    v.x = inst->position.x;
    v.y = inst->position.y + Gobjinst_GetActorHeight(inst) * 0.5f;
    v.z = inst->position.z;
    inst->lights = g_playerModelLighting[0];
    inst->cached = 0;
}

/* Draws a static object through its cached display list, building the cache on first use: emits a branch placeholder, loads the object's model, builds its rotation (the shared g_staticObjectSharedAngle angle for type 8), scale and position raised by its height offset into the current matrix slot, draws the model with its material through Geometry_DrawModelResource and Simpinst_SpawnModelEffect unless the type is 12, ends the list, patches the placeholder to skip past it and calls the cached list. The display list writes match only as block-scoped initialisers taking g_displayListCursor_SimpleDrawcachedmodel++. */












extern void **Simpinst_RequestModelVariant(ObjB *, s32);
extern void ScaleMatrixLocal(MatrixF *, f32, f32, f32);
extern s32 Graphu64_LimitVectorLength(CVector3 *, f32);
extern void TranslateMatrix(MatrixF *, f32, f32, f32);
extern void SwapMatrixUpForward(MatrixF *);
extern void Graphu64_ConvertMatrixToFixed(MatrixF *, char *);

struct ObjB; extern void Simpinst_SpawnModelEffect(struct ObjB *actor, void **resource);

void Simple_DrawCachedModel(ObjB *obj) {
    MatrixF matrix;
    void **resource;
    Gfx *branch;

    Geometry_InvalidateMaterialKeys();
    TextLoad_ResetTextureCache();
    if (obj->cached != 0) {
        gSPDisplayList(g_displayListCursor++, (unsigned int)obj->cached);
        return;
    }
    resource = Simpinst_RequestModelVariant(obj, obj->type);
    if (resource == 0) {
        return;
    }
    obj->cached = g_displayListCursor;
    gSPBranchList(g_displayListCursor++, 0);
    if (obj->definition->kind == 8) {
        BuildYawMatrix(&matrix, g_world.elapsed);
    } else {
        BuildYawMatrix(&matrix, obj->angle);
    }
    ScaleMatrixLocal(&matrix, obj->scale, obj->scale, obj->scale);
    Graphu64_LimitVectorLength(&obj->position, 20000.0f);
    TranslateMatrix(&matrix, obj->position.x, obj->position.y + obj->height, obj->position.z);
    SwapMatrixUpForward(&matrix);
    Graphu64_ConvertMatrixToFixed(&matrix, obj->matrices[g_lightingBufferIndex]);
    if (obj->definition->kind != 12) {
        Geometry_DrawModelResource(resource, obj->matrices[g_lightingBufferIndex], 0, &obj->lights, 0, obj->material);
        Simpinst_SpawnModelEffect(obj, resource);
    }
    gSPEndDisplayList(g_displayListCursor++);
    gSPBranchList(obj->cached++, (unsigned int)g_displayListCursor);
    gSPDisplayList(g_displayListCursor++, (unsigned int)obj->cached);
    Cache_UnlockResource(0, resource);
}
