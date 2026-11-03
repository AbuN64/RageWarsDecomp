#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ENTRYRECAT8V4.H"
#include "TYPES.H"
#include "MENU/TRACK_UPDATETRACKCAMERA.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Evaluates keyframe track 3 of the current record's resource at time t: before the first key or
   after the last it holds that key's value, otherwise it finds the surrounding keys and blends
   their values with the smoothstep weight 3u^2 - 2u^3; an empty track yields g_trackSplineOutputBounds[1]. */
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
f32 Track_EvaluateTrackScalar(f32 t) {
    s32 *track;
    ScalarPair *key;
    s32 count;
    s32 i;
    f32 u;
    track = SetN64_GetPackSection(g_cinemaSequenceState->resource, 3);
    key = (ScalarPair *)(track + 2);
    count = track[1];
    for (i = 0; i < count; i++) {
    }
    if (count == 0) {
        return g_trackSplineOutputBounds[1];
    }
    if (t <= key[0].second) {
        return key[0].first;
    }
    if (key[count - 1].second <= t) {
        return key[count - 1].first;
    }
    while (key->second < t) {
        key++;
    }
    u = (t - key[-1].second) / (key->second - key[-1].second);
    u = u * (u * g_trackSmoothInterpolationConstants) - 2.0f * u * u * u;
    return key[-1].first * ((*(&g_trackSmoothInterpolationConstants + 1)) - u) + key->first * u;
}

#include "COMMON/WORLD.H"
#include "GRAPHU64/GRAPHU64_GETANGLEDISTANCE.H"
#include "MENU/ITEMS/SCENE/SCENE_BUILDCACHEDGEOMETRY.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
extern f32 g_trackCameraScaleAndYawOffset[];
extern u8 g_defaultProbeMotionSettings[];
extern void CCinema_DrawMessages(void);
extern CVector3 Track_GetTrackEyePosition(f32);
extern CVector3 Track_GetTrackTargetPosition(f32);


extern void Graphu64_TransformPoint(void *matrix, void *inputPoint, void *transformedPoint);

extern s32 Unicol_MoveActorWithCollision(SharedTrackObject *, f32, f32, f32, void *);

/* Follow the keyframe camera and keep the collision result across world cleanup. */
void Track_UpdateTrackCamera(SharedTrackCamera *camera) {
    CVector3 eye;
    CVector3 target;
    CVector3 delta;
    SharedTrackObjectPrefix saved;
    f32 matrix[16];
    CVector3 rotated;
    SharedTrackObject *actor;
    s32 collisionHit;
    f32 yaw;
    f32 pitch;
    f32 scale;

    if (g_cinemaSequenceState->active == 0) {
        return;
    }
    if (Cinema_IsSequenceInWindow() == 0) {
        return;
    }
    if (g_cinemaSequenceState->time < g_cinemaSequenceState->start || g_cinemaSequenceState->end < g_cinemaSequenceState->time) {
        return;
    }
    if (g_cinemaSequenceState->messageCount > 0) {
        CCinema_DrawMessages();
    }
    eye = Track_GetTrackEyePosition(g_cinemaSequenceState->time);
    target = Track_GetTrackTargetPosition(g_cinemaSequenceState->time);
    scale = g_trackCameraScaleAndYawOffset[0];
    Graphu64_ScaleVector(&eye, &eye, scale);
    Graphu64_ScaleVector(&target, &target, scale);
    camera->distance = 0.0f;
    Graphu64_SubtractVectors(&delta, &target, &eye);
    if (((g_cinemaSequenceState->spec.flags & 1) && g_cinemaSequenceState->target != 0) || (g_cinemaSequenceState->spec.flags & 2)) {
        actor = g_transientPlayerList.actorList;
        if ((g_cinemaSequenceState->spec.flags & 1) && g_cinemaSequenceState->target != 0) {
            g_cinemaSequenceState->position = g_cinemaSequenceState->target->prefix.position;
            g_cinemaSequenceState->yaw = g_cinemaSequenceState->target->yaw + g_trackCameraScaleAndYawOffset[1];
        }
        if (g_cinemaSequenceState->spec.flags & 2) {
            if (actor != 0) {
                g_cinemaSequenceState->position = actor->prefix.position;
                g_cinemaSequenceState->yaw = actor->yaw;
            } else {
                g_cinemaSequenceState->position.x = 0.0f;
                g_cinemaSequenceState->position.y = 0.0f;
                g_cinemaSequenceState->position.z = 0.0f;
                g_cinemaSequenceState->yaw = 0.0f;
            }
        }
        Graphu64_IdentityMatrix(matrix);
        Graphu64_MatrixFromEulerXYZ(matrix, 0.0f, g_cinemaSequenceState->yaw, 0.0f);
        Graphu64_TransformPoint(matrix, &target, &rotated);
        target = rotated;
        Graphu64_TransformPoint(matrix, &eye, &rotated);
        eye = rotated;
        Graphu64_AddVec3(&target, &target, &g_cinemaSequenceState->position);
        Graphu64_AddVec3(&eye, &eye, &g_cinemaSequenceState->position);
        Graphu64_SubtractVectors(&delta, &target, &eye);
        if (actor != 0) {
            saved = actor->prefix;
            actor->prefix.position = target;
            Scene_RequestVisibleGridSections(&g_world);
            collisionHit = Unicol_MoveActorWithCollision(actor, eye.x, eye.y, eye.z, g_defaultProbeMotionSettings);
            Scene_UnlockActiveSectionResources(&g_world);
            actor->prefix = saved;
            if (collisionHit != 0) {
                eye = *(CVector3 *)&g_particleContactState;
            }
        }
    }
    yaw = Graphu64_GetHorizontalAngle(&delta);
    pitch = Graphu64_GetVerticalAngle(&delta);
    camera->distance += yaw;
    camera->pitch = -pitch;
    camera->position = eye;
}
