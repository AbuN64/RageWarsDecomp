#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include <PR/abi.h>
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/MATH_HELPERS.H"
#include "TYPES.H"
#include "ENGINE/PARTICLE.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
extern void Cache_ReleaseResource(void *cache, void *resource);

/* Draws an actor's ground shadow: probes the ground under the actor through Collision_ProbeGround_de into g_currentActorInstance, and when ground is found tilts the shadow model from g_actorMatrixPool to the ground normal, scales it by the actor's size shrinking with height above the ground, fades it with height (and with lost health for actors flagged 1), places it on the ground and draws it through Geometry_DrawIntensityMask between render-mode commands. */
extern char g_actorMatrixPool;

extern char g_defaultProbeMotionSettings;

extern Ground g_currentActorInstance;


extern Gfx *g_displayListCursor;

extern s32 Unicol_MoveActorWithCollision(Shared_ParticleInstance *, CVector3, void *);

extern CQuatern Graphu64_BuildDirectionQuaternion(CVector3 *);

extern void MultiplyQuaternions(CQuatern *out, CQuatern *a, CQuatern *b);

extern s32 Graphu64_LimitVectorLength(CVector3 *, f32);

extern void MatrixFromQuaternion(f32 *q, f32 *m);

extern void ScaleMatrixLocal(f32 *, f32, f32, f32);

extern void TranslateMatrix(f32 *, f32, f32, f32);

extern void Graphu64_ConvertMatrixToFixed(f32 *, void *);

extern void Geometry_DrawIntensityMask(void *model, s32 pass, u8 alpha);

extern s32 g_playerWeaponClassMode;


extern char s_particleModelResourceTag;

extern const char g_simpPartModelsIndexText[];

extern const char s_simpPartModelText[];

extern char g_simpleModelResourceCallbackAddress;




extern s32 SetN64_GetDirectoryEntry(s32 *, s32, s32);


extern void **Cache_RequestWordCountedResource(s32,void **,s32,void *,s32);

extern s32 SetN64_LocatePackSection(s32, s32, s32, s32 *);

extern void Geometry_QueueModelInstance(void **, void *, s32, void *, void *, s32);

extern void Cache_UnlockResource(s32, void *);
extern void *Map_ReserveEntries(void *, s32);

void Particle_DrawGroundShadow(Shared_Particle *actor, GameplayCamera *view) {
    f32 matrix[16];
    CVector3 point;
    CQuatern rotation;
    CQuatern tilt;
    CQuatern roll;
    Shared_ParticleInstance probe;
    void *model;
    Ground *ground;
    f32 angle;
    f32 height;
    f32 alpha;
    f32 size;
    f32 health;
    f32 floor;
    f32 shrink;

    model = Map_ReserveEntries(&g_actorMatrixPool, 1);
    if (model == 0) {
        return;
    }
    probe = actor->inst;
    probe.velocity.x = 0.0f;
    probe.velocity.y = 0.0f;
    probe.velocity.z = 0.0f;
    probe.pos.y += 10.24f;
    point.x = probe.pos.x;
    point.y = probe.pos.y - 102400.0f;
    point.z = probe.pos.z;
    Unicol_MoveActorWithCollision(&probe, point, &g_defaultProbeMotionSettings);
    ground = &g_currentActorInstance;
    if (ground->found == 0) {
        return;
    }
    angle = 0.78539824f;
    tilt = Graphu64_BuildDirectionQuaternion(&ground->normal);
    roll.x = g_turretAimSine = Gu_Sinf(angle);
    roll.y = 0.0f;
    roll.z = 0.0f;
    roll.w = Math_Cosf(angle);
    MultiplyQuaternions(&rotation, &roll, &tilt);
    floor = ground->height;
    height = actor->inst.pos.y - floor;
    alpha = ((RW_MIN(200.0f - height * 0.30517578f, 255.0f)) < (0.0f) ? (0.0f) : (RW_MIN(200.0f - height * 0.30517578f, 255.0f)));
    size = actor->size.z * 7.68f;
    if (actor->desc->renderModel != 0) {
        size *= 8.0f;
    }
    size *= actor->desc->scaling->shadowScale;
    shrink = height * 0.1f;
    size = ((({ f32 _m = (size - shrink); if (!(_m <= (size))) _m = (size); _m; })) < (0.0f) ? (0.0f) : (({ f32 _m = (size - shrink); if (!(_m <= (size))) _m = (size); _m; })));
    if (actor->desc->flags & 1) {
        health = actor->life;
        if (0.0f < health) {
            alpha *= (health - actor->time) / health;
        }
    }
    point.x = actor->inst.pos.x;
    point.z = actor->inst.pos.z;
    point.y = floor;
    Graphu64_LimitVectorLength(&point, 20000.0f);
    MatrixFromQuaternion(&rotation, matrix);
    ScaleMatrixLocal(matrix, size, 1.0f, size);
    TranslateMatrix(matrix, point.x, point.y, point.z);
    Graphu64_ConvertMatrixToFixed(matrix, model);
    {
        Gfx *cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
        cmd = g_displayListCursor++;
        gDPSetCycleType(cmd, G_CYC_2CYCLE);
    }
    Geometry_DrawIntensityMask(model, 1, (u32)alpha);
    {
        Gfx *cmd = g_displayListCursor++;
        gDPPipeSync(cmd);
        cmd = g_displayListCursor++;
        gDPSetCycleType(cmd, G_CYC_1CYCLE);
    }
}

void Particle_DrawModel(Shared_Particle *particle, GameplayCamera *view) {
    CVector3 delta;
    void *modelTable;
    PackedMatrixWords *matrix;
    void **resource;
    s32 key;
    s32 found;
    s32 index;
    f32 amount;

    index = 0;
    if (g_playerWeaponClassMode == 1) {
        matrix = &particle->mtx[g_lightingBufferIndex];
    } else {
        matrix = Map_ReserveEntries(&g_actorMatrixPool, 1);
        if (matrix == 0) {
            return;
        }
        Graphu64_TransformPoint(view->worldToView, &particle->inst.pos, &delta);
        amount = delta.z;
        if (amount < 0.0f) {
            amount = -amount;
        }
        Particle_BuildMatrix(particle, matrix, view, amount);
    }

    if (particle->resource == 0) {
        resource = Cache_RequestResource(0, particle->desc->renderModel,
                                particle->desc->renderModel, 24,
                                0, 0, 0, &s_particleModelResourceTag, 1);
        if (resource != 0) {
            key = SetN64_GetDirectoryEntry(*resource,
                                particle->desc->renderModel, 1);
            Cache_ReleaseResource(0, resource);
            found = Cache_RequestWordCountedResource(0, &modelTable, key, &g_simpPartModelsIndexText, 1);
            if (found != 0) {
                particle->resource = SetN64_LocatePackSection(
                    (s32)modelTable, key, index % *(s32 *)modelTable,
                    &particle->resourceSize);
                Cache_ReleaseResource(0, (void *)found);
            }
        }
        if (particle->resource == 0) {
            return;
        }
    }

    resource = Cache_RequestResource(0, particle->resource,
                            particle->resource, particle->resourceSize,
                            0, 0, &g_simpleModelResourceCallbackAddress, &s_simpPartModelText, 1);
    if (resource != 0) {
        Geometry_QueueModelInstance(resource, matrix, 0,
                      &particle->lighting[g_lightingBufferIndex], 0, -1);
        Cache_UnlockResource(0, resource);
    }
}
