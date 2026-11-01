#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/PROPGEOMETRY.H"
#include "WORLD/STATIC_MODEL_INSTANCE_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MATH_HELPERS.H"
#include "COMMON/LEGACY_COLLISION_ACTOR.H"
#include "COMMON/OBJRECAT4V7.H"
#include "TYPES.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "ENGINE/INSTANCE/SIMPINST.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

extern f32 g_simpleObjectViewEffectRotationAndHeight;

extern char g_actorParticleEffectSystem;



extern f32 Gobjinst_GetActorHeight(ActorSimpleInstanceSpawnModelEffect *actor);

#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"
extern void Cache_ReleaseResource(void *cache, void *resource);

extern SpawnedEffectMotionView *Particle_GetLastSpawnedEffect(void *system);

extern f32 Gobjinst_GetActorRadius(ActorSimpleInstanceSpawnModelEffect *actor);

/* Places an actor's ground shadow: the shadow size is the smaller of half the vertical offset from
 * InstHdr_GetActorShadowRadius and that minus a tenth of the actor's height above its ground height at 0x40, vanishing
 * when negative; a transform is built from the actor's orientation, scaled flat by the shadow size,
 * positioned at the ground under the actor, stored as the actor's per-frame matrix and submitted through
 * Geometry_DrawIntensityMask. */


extern CQuatern Insthdr_BuildActorGroundRotation(void *);

extern void Graphu64_LimitVectorLength(CVector3 *, f32);

extern void MatrixFromQuaternion(f32 *, f32 *);

extern void ScaleMatrixLocal(f32 *, f32, f32, f32);

extern void TranslateMatrix(f32 *, f32, f32, f32);

extern void Graphu64_ConvertMatrixToFixed(f32 *, void *);

extern void Geometry_DrawIntensityMask(void *, s32, s32);



extern void **Cache_RequestWordCountedResource(s32,void **,s32,void *,s32);

extern s32 SetN64_GetDirectoryEntry(s32 *, s32, s32);

extern s32 SetN64_LocatePackSection(s32, s32, s32, s32 *);

extern void Cache_UnlockResource(s32, void *);

extern char g_simpleModelResourceCallbackAddress;




void Simpinst_SpawnModelEffect(ActorSimpleInstanceSpawnModelEffect *actor, void **resource) {
    CVector3 position;
    CQuatern rotation;
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;

    if (Geometry_GetViewEffect() != 0) {
        rotation.x = rotation.y = rotation.z = 0.0f;
        rotation.w = g_simpleObjectViewEffectRotationAndHeight;
        node = SetN64_GetPackSection(*resource, 2);
        if ((*node != 0) &&
            (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
            position = actor->position0;
            position.y += Gobjinst_GetActorHeight(actor) * *(&g_simpleObjectViewEffectRotationAndHeight + 1);
            Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor, 0, 0, 148,
                          actor->position1, rotation, position, 0, -1, 0);
            effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem);
            if (effect != 0) {
                scale = g_simpleObjectViewEffectScale;
                effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                effect->height = Gobjinst_GetActorHeight(actor) * scale;
            }
        }
    }
}

void Simpinst_DrawGroundShadow(void *actor) {
    f32 matrix[16];
    CVector3 position;
    CQuatern rotation;
    f32 ground;
    f32 height;
    f32 size;
    ground = ((Shared_CollisionActor *)actor)->groundY;
    height = ((Shared_CollisionActor *)actor)->y - ground;
    if (!(RW_MIN_LT(InstHdr_GetActorShadowRadius(actor) * 0.5f, InstHdr_GetActorShadowRadius(actor) * 0.5f - height * 0.1f) < 0.0f)) {
        size = RW_MIN_LT(InstHdr_GetActorShadowRadius(actor) * 0.5f, InstHdr_GetActorShadowRadius(actor) * 0.5f - height * 0.1f);
    } else {
        size = 0.0f;
    }
    rotation = Insthdr_BuildActorGroundRotation(actor);
    position.x = ((Shared_CollisionActor *)actor)->x;
    position.z = ((Shared_CollisionActor *)actor)->z;
    position.y = ground;
    Graphu64_LimitVectorLength(&position, 20000.0f);
    MatrixFromQuaternion(&rotation.x, matrix);
    ScaleMatrixLocal(matrix, size, 1.0f, size);
    TranslateMatrix(matrix, position.x, position.y, position.z);
    Graphu64_ConvertMatrixToFixed(matrix, (char *)actor + ((g_lightingBufferIndex << 6) + ((char *)&((LevelActor *)0)->bounds - (char *)0)));
    Geometry_DrawIntensityMask((char *)actor + ((g_lightingBufferIndex << 6) + ((char *)&((LevelActor *)0)->bounds - (char *)0)), 1, 150);
}

void Simpinst_RefreshModelResourceUsage(StaticObject *staticObject) {
    void *variantDirectory;
    void **resource;
    s32 key;
    s32 found;
    s32 index;

    index = staticObject->model;
    if (index != staticObject->animation) {
        resource = Cache_RequestResource(0, staticObject->animationKey,
                                staticObject->animationKey, 24,
                                0, 0, 0, &g_simpleObjectModelResourceTagData + 4, 1);
        if (resource != 0) {
            key = SetN64_GetDirectoryEntry(*resource, staticObject->animationKey, 1);
            Cache_ReleaseResource(0, resource);
            found = Cache_RequestWordCountedResource(0, &variantDirectory, key, g_simpModelsIndexText, 1);
            if (found != 0) {
                staticObject->resource = SetN64_LocatePackSection((s32)variantDirectory, key,
                                                    index % *(s32 *)variantDirectory,
                                                    &staticObject->resourceSize);
                staticObject->animation = index;
                Cache_ReleaseResource(0, (void *)found);
            }
        }
    }
    if (staticObject->resource != 0) {
        resource = Cache_RequestResource(0, staticObject->resource,
                                staticObject->resource, staticObject->resourceSize,
                                0, 0, &g_simpleModelResourceCallbackAddress, g_simpModelText, 0);
    } else {
        resource = 0;
    }
    if (resource != 0) {
        Geometry_RefreshMaterialResources(resource);
        Cache_UnlockResource(0, resource);
    }
}
