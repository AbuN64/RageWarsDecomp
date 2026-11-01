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
typedef struct SimpleInstanceOut {
    s8 kind;
    u8 pad1[3];
    u16 type;
    u8 pad6[2];
    CVector3 position;
    void *region;
    void *variation;
    u8 pad1C[0x50 - 0x1C];
    s32 owner;
    s32 f54;
    s32 f58;
    s32 f5C;
    u8 pad60[0x174 - 0x60];
    f32 rotY;
    u8 pad178[4];
    CVector3 boxMin;
    CVector3 boxMax;
    f32 f194;
    s32 f198;
    u16 flags;
    u16 id;
    s32 f1A0;
    s32 f1A4;
    Shared_ParticleLighting light;
    s32 visBits;
    s32 f1C4;
} SimpleInstanceOut;
void Simple_InitSimpleInstance(SimpleInstanceOut *inst, CROMSimpleInstance *rec, s32 owner, char *segments) {
    CVector3 v;
    inst->kind = 3;
    inst->type = rec->type;
    inst->visBits = rec->visBits;
    inst->position = rec->position;
    inst->position.y = inst->position.y + 10.24f;
    inst->rotY = rec->rotY * (3.1415927f / 127.0f);
    inst->f194 = 0.35f;
    inst->f198 = 0;
    inst->boxMin.x = rec->position.x - rec->maxRadius;
    inst->boxMin.y = rec->position.y - rec->maxRadius;
    inst->boxMin.z = rec->position.z - rec->maxRadius;
    inst->boxMax.x = rec->position.x + rec->maxRadius;
    inst->boxMax.y = rec->position.y + rec->maxRadius;
    inst->boxMax.z = rec->position.z + rec->maxRadius;
    inst->owner = owner;
    inst->f54 = -1;
    inst->f58 = 0;
    inst->f5C = 0;
    if (rec->variation == 0xFFFF) {
        inst->variation = &g_defaultEffectDefinition;
    } else {
        inst->variation = Scene_GetActorDefinition(&g_world, rec->variation);
    }
    if (rec->region == 0xFFFF) {
        inst->region = 0;
    } else {
        inst->region = segments + (rec->region << 5);
    }
    inst->flags = rec->flags | 2;
    inst->f1A0 = 0;
    inst->f1A4 = 0;
    inst->id = rec->id;
    v.x = inst->position.x;
    v.y = inst->position.y + Gobjinst_GetActorHeight(inst) * 0.5f;
    v.z = inst->position.z;
    inst->light = g_playerModelLighting[0];
    inst->f1C4 = 0;
}

/* Draws a static object through its cached display list, building the cache on first use: emits a branch placeholder, loads the object's model, builds its rotation (the shared g_staticObjectSharedAngle angle for type 8), scale and position raised by its height offset into the current matrix slot, draws the model with its material through Geometry_DrawModelResource and Simpinst_SpawnModelEffect unless the type is 12, ends the list, patches the placeholder to skip past it and calls the cached list. The display list writes match only as block-scoped initialisers taking g_displayListCursor_SimpleDrawcachedmodel++. */












extern void **Simpinst_RequestModelVariant(StaticObject *, s32);
extern void ScaleMatrixLocal(MatrixF *, f32, f32, f32);
extern s32 Graphu64_LimitVectorLength(CVector3 *, f32);
extern void TranslateMatrix(MatrixF *, f32, f32, f32);
extern void SwapMatrixUpForward(MatrixF *);
extern void Graphu64_ConvertMatrixToFixed(MatrixF *, char *);

extern void Simpinst_SpawnModelEffect(StaticObject *, void **);

void Simple_DrawCachedModel(StaticObject *obj) {
    MatrixF matrix;
    void **resource;
    Gfx *branch;

    Geometry_InvalidateMaterialKeys();
    TextLoad_ResetTextureCache();
    if (obj->cached != 0) {
        gSPDisplayList(g_displayListCursor++, (unsigned int)obj->cached);
        return;
    }
    resource = Simpinst_RequestModelVariant(obj, obj->model);
    if (resource == 0) {
        return;
    }
    obj->cached = g_displayListCursor;
    gSPBranchList(g_displayListCursor++, 0);
    if (*obj->type == 8) {
        BuildYawMatrix(&matrix, g_world.elapsed);
    } else {
        BuildYawMatrix(&matrix, obj->angle);
    }
    ScaleMatrixLocal(&matrix, obj->scale, obj->scale, obj->scale);
    Graphu64_LimitVectorLength(&obj->position, 20000.0f);
    TranslateMatrix(&matrix, obj->position.x, obj->position.y + obj->height, obj->position.z);
    SwapMatrixUpForward(&matrix);
    Graphu64_ConvertMatrixToFixed(&matrix, obj->matrices[g_lightingBufferIndex]);
    if (*obj->type != 12) {
        Geometry_DrawModelResource(resource, obj->matrices[g_lightingBufferIndex], 0, obj->lights, 0, obj->material);
        Simpinst_SpawnModelEffect(obj, resource);
    }
    gSPEndDisplayList(g_displayListCursor++);
    gSPBranchList(obj->cached++, (unsigned int)g_displayListCursor);
    gSPDisplayList(g_displayListCursor++, (unsigned int)obj->cached);
    Cache_UnlockResource(0, resource);
}
