#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "TYPES.H"
#include "COMMON/MATH_HELPERS.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"

/* Draws an object's cast shadow: objects without shadow flag 0x10000000 get the blob shadow of
 * GameObject_DrawBlobShadow; otherwise, once per frame the shadow model from Map_ReserveEntries is built for an object above
 * the ground: the light of the current view (direction from its signed bytes, strength from its colour)
 * is sampled at the object through Gdynlight_AccumulateLightDirections, the shadow alpha is 128 plus 56 per unit of light (faded
 * by g_menuModelFillAlpha during a fade), the light direction is kept at least 0.15 from horizontal, and the shadow
 * is projected along it onto a plane just below the object (0.9 of its height up to 512), grown by 0.003
 * per unit of height, turned by the object's orientation and placed on the ground; the shadow is then
 * submitted through Gobjinst_DrawModelWithProjection. */
extern s32 InstHdr_CanActorCastShadow(void *);
extern f32 InstHdr_GetActorGroundHeight(char *, s32);
extern void *Map_ReserveEntries(void *, s32);
extern f32 Gu_Sqrtf(f32);
extern void Gdynlight_AccumulateLightDirections(void *, CVector3, CVector3 *, f32 *);
extern void Graphu64_BuildPlaneProjectionMatrix(f32 *, CVector3 *, f32);
extern void TranslateMatrix(void *, f32, f32, f32);
extern void Graphu64_ScaleMatrixWorld(f32 *, f32, f32, f32);
extern void Graphu64_MultiplyAffineMatrices(void *, f32 *, f32 *);
extern void Gobjinst_DrawModelWithProjection(char *, char *, void *, u8);
extern void GameObject_DrawBlobShadow(struct LevelActor *, CVector3 *, s32);
void GameObject_DrawActorShadow(char *obj, s32 unused, char *info) {
    CVector3 dir;
    f32 projection[16];
    f32 turn[16];
    f32 strength;
    f32 ground;
    f32 height;
    f32 plane;
    f32 scale;
    f32 diff;
    char *light;
    s32 alpha;
    if (((struct LevelActor *)(obj))->model == 0 || InstHdr_CanActorCastShadow(obj) == 0 || (((struct LevelActor *)(obj))->flags & 0x200000)) {
        return;
    }
    if (((struct LevelActor *)(obj))->flags & 0x10000000) {
        if (((struct LevelActor *)(obj))->shadow == 0) {
            ground = InstHdr_GetActorGroundHeight(obj, 0);
            if (((struct LevelActor *)(obj))->position0.y < ground) {
                return;
            }
            diff = ((struct LevelActor *)(obj))->position0.y - ground;
            height = (512.0f < diff) ? 512.0f : diff;
            if ((((struct LevelActor *)(obj))->shadow = Map_ReserveEntries(&g_actorMatrixPool, 1)) == 0) {
                return;
            }
            light = (char *)&((LevelActor *)obj)->lighting[g_lightingBufferIndex];
            dir.x = ((struct Shared_ParticleLighting *)(light))->direction[0] * 0.007874016f;
            dir.y = ((struct Shared_ParticleLighting *)(light))->direction[1] * 0.007874016f;
            dir.z = ((struct Shared_ParticleLighting *)(light))->direction[2] * 0.007874016f;
            strength = Gu_Sqrtf((f32)((struct Shared_ParticleLighting *)(light))->diffuse[0] * (f32)((struct Shared_ParticleLighting *)(light))->diffuse[0] +
                                         (f32)((struct Shared_ParticleLighting *)(light))->diffuse[1] * (f32)((struct Shared_ParticleLighting *)(light))->diffuse[1] +
                                         (f32)((struct Shared_ParticleLighting *)(light))->diffuse[1] * (f32)((struct Shared_ParticleLighting *)(light))->diffuse[1]) *
                       -0.00090497744f;
            Gdynlight_AccumulateLightDirections(&g_dynamicLightPool, ((Player *)(obj))->pos, &dir, &strength);
            if (strength < -1.0f) {
                strength = -1.0f;
            }
            alpha = strength * 56.0f + 128.0f;
            if (g_menuModelFillEnabled == 1) {
                alpha = alpha * g_menuModelFillColor[3] * 0.003921569f;
            }
            ((struct LevelActor *)(obj))->shadowAlpha = alpha;
            dir.y = 1.0f;
            Graphu64_NormalizeVec3(&dir);
            if (RW_ABS(dir.y) < 0.15f) {
                if (dir.y >= 0.0f) {
                    dir.y = 0.15f;
                } else {
                    dir.y = -0.15f;
                }
                Graphu64_NormalizeVec3(&dir);
            }
            plane = ground + height * 0.9f;
            Graphu64_BuildPlaneProjectionMatrix(projection, &dir, plane);
            TranslateMatrix(projection, -((struct LevelActor *)(obj))->position0.x, -plane, -((struct LevelActor *)(obj))->position0.z);
            scale = height * 0.003f + 1.0f;
            Graphu64_ScaleMatrixWorld(projection, scale, scale, scale);
            MatrixFromQuaternion((f32 *)(&((LevelActor *)obj)->rotation), turn);
            Graphu64_MultiplyAffineMatrices(((struct LevelActor *)(obj))->shadow, projection, turn);
            TranslateMatrix(((struct LevelActor *)(obj))->shadow, ((struct LevelActor *)(obj))->position0.x, ground, ((struct LevelActor *)(obj))->position0.z);
            if (((struct LevelActor *)(obj))->shadow == 0) {
                return;
            }
        }
        Gobjinst_DrawModelWithProjection(obj, info, ((struct LevelActor *)(obj))->shadow, ((struct LevelActor *)(obj))->shadowAlpha);
    } else {
        GameObject_DrawBlobShadow((struct LevelActor *)obj, ((struct ActorRenderSettings *)(info))->shadowOffset, 0);
    }
}

#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
float InstHdr_GetShadowGroundHeight(void *object, s32 mode);
f32 InstHdr_GetActorShadowRadius(Actor_u1 *actor);
s32 Graphu64_LimitVectorLength(f32 *vectorComponents, f32 maximumLength);
void ScaleMatrixLocal(void *matrix, f32 sx, f32 sy, f32 sz);

void Graphu64_ConvertMatrixToFixed(f32 *src, PackedMatrixWords *dst);
void Geometry_DrawIntensityMask(void *matrix, s32 pass, u32 alpha);
void GameObject_DrawBlobShadow(struct LevelActor *actor, CVector3 *offset, s32 raised) {
    f32 matrix[16];
    CVector3 position;
    f32 scale;
    f32 groundHeight;
    f32 height;
    f32 opacity;
    f32 shrink;
    f32 limitedRadius;
    f32 radius;
    f32 lift;
    PackedMatrixWords *packed;
    u8 targetAlpha;

    packed = Map_ReserveEntries(&g_actorMatrixPool, 1);
    if (packed != 0) {
        groundHeight = InstHdr_GetShadowGroundHeight(actor, 0);
        height = (actor->position0.y + actor->eyeHeight) - groundHeight;
        radius = InstHdr_GetActorShadowRadius((Actor_u1 *)actor);
        shrink = height * 0.1f;
        limitedRadius = radius - shrink;
        if (!(limitedRadius <= radius)) {
            limitedRadius = radius;
        }
        if (limitedRadius < 0.0f) {
            radius = 0.0f;
            limitedRadius = radius;
        } else {
            limitedRadius = radius - shrink;
            if (!(limitedRadius <= radius)) {
                limitedRadius = radius;
            }
        }
        radius = limitedRadius;
        if (raised != 0) {
            radius *= 0.5f;
            lift = 15.36f;
        } else {
            radius *= 0.7f;
            lift = 0.0f;
        }
        scale = radius;
        position.x = actor->position0.x + offset->x;
        position.z = actor->position0.z + offset->z;
        position.y = groundHeight + lift + offset->y;
        Graphu64_LimitVectorLength((f32 *)&position, 20000.0f);
        MatrixFromQuaternion(&actor->rotation, matrix);
        ScaleMatrixLocal(matrix, scale, 1.0f, scale);
        TranslateMatrix((s8 *) matrix, position.x, position.y, position.z);
        Graphu64_ConvertMatrixToFixed(matrix, (PackedMatrixWords *) packed);
        opacity = 200.0f - (height * 1.2207031f);
        targetAlpha = 0xFF;
        if (!(255.0f < opacity)) {
            targetAlpha = 0;
            if (!(opacity < 0.0f)) {
                targetAlpha = 0xFF;
                if (!(255.0f < opacity)) {
                    targetAlpha = (u8)opacity;
                }
            }
        }
        actor->shadowAlpha = (u8)(actor->shadowAlpha +
            ((s32)targetAlpha - actor->shadowAlpha) * 0.5f);
        Geometry_DrawIntensityMask(packed, raised == 0, actor->shadowAlpha);
    }
}
