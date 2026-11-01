#include "COMMON/PROBE.H"
#include "COMMON/OBJ.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"

/* Returns the rotation that turns an actor's aim toward a target point: a player's forward axis is its
 * aiming orientation from Gobjinst_BuildActorAimQuaternion applied to +z, anyone else looks along +z; the target is the
 * player's lock-on at 0x1F0 or else whatever Playerai_FindNearestPlayer finds at the point, and with no target the
 * identity is returned. Otherwise the forward axis turns about its cross product with the direction from
 * the point up to three quarters of the target's height, by half the angle between them, composed with the
 * player's aiming orientation; the sine is kept in g_turretAimSine. */





extern char g_playerViewRenderContext;


extern CQuatern Gobjinst_BuildActorAimQuaternion(char *);

extern void MatrixFromQuaternion(f32 *q, f32 *m);


extern char *Playerai_FindNearestPlayer(void *, CVector3);

extern f32 Gobjinst_GetActorHeight(char *);

extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);


extern void Graphu64_CrossVectors(CVector3 *, CVector3 *, CVector3 *);

extern void MultiplyQuaternions(CQuatern *, CQuatern *, CQuatern *);

extern void Graphu64_CrossVectors(CVector3 *out, CVector3 *a, CVector3 *b);


CQuatern Gobjinst_BuildTargetAimOrientation(char *actor, CVector3 point) {
    CVector3 origin;
    CVector3 dir;
    CVector3 forward;
    CVector3 local;
    CVector3 axis;
    CQuatern turn;
    CQuatern aim;
    CQuatern result;
    f32 matrix[16];
    char *target;
    char *found;
    f32 angle;
    f32 scale;

    target = 0;
    if (actor != 0 && *(u8 *)actor == 1) {
        target = ((LevelActor *)(actor))->lockOn;
        aim = Gobjinst_BuildActorAimQuaternion(actor);
        MatrixFromQuaternion(&aim, matrix);
        local.x = 0.0f;
        local.y = 0.0f;
        local.z = 1.0f;
        Graphu64_TransformPoint(matrix, &local, &forward);
    } else {
        forward.x = 0.0f;
        forward.y = 0.0f;
        forward.z = 1.0f;
    }
    if (target == 0) {
        found = Playerai_FindNearestPlayer(&g_playerViewRenderContext, point);
        if (found != 0) {
            target = found;
        }
        if (target == 0) {
            result.x = result.y = result.z = 0.0f;
            result.w = 1.0f;
            return result;
        }
    }
    origin = ((ActorBarrelIsTargetInViewCone *)(target))->position;
    origin.y += ((ActorBarrelIsTargetInViewCone *)(target))->eye;
    origin.y += Gobjinst_GetActorHeight(target) * 0.75f;
    Graphu64_SubtractVectors(&dir, &origin, &point);
    Graphu64_NormalizeVec3(&dir);
    Graphu64_CrossVectors(&axis, &forward, &dir);
    Graphu64_NormalizeVec3(&axis);
    angle = Graphu64_ArcCos(forward.x * dir.x + forward.y * dir.y + forward.z * dir.z) * 0.5f;
    scale = Gu_Sinf(angle);
    turn.x = axis.x * scale;
    turn.y = axis.y * scale;
    turn.z = axis.z * scale;
    g_turretAimSine = scale;
    turn.w = Math_Cosf(angle);
    if (actor != 0 && *(u8 *)actor == 1) {
        MultiplyQuaternions(&result, &aim, &turn);
    } else {
        result = turn;
    }
    return result;
}

CQuatern Gobjinst_BuildActorDirectionTilt(ActorDirectionTiltInput *input) {
    CVector3 source;
    CVector3 up;
    CVector3 axis;
    CQuatern result;
    f32 angle;
    f32 scale;
    int state;

    state = input->state;
    if (state == 0) {
        goto default_source;
    }
    if (state < 0) {
        goto default_source;
    }
    if (state < 4) {
        goto input_source;
    }
default_source:
    source.x = 0.0f;
    source.y = g_actorBoneAimSourceY;
    source.z = 0.0f;
    goto source_ready;
input_source:
    source = input->direction;
source_ready:

    up.x = 0.0f;
    up.y = g_actorBoneAimUpY;
    up.z = 0.0f;
    Graphu64_CrossVectors(&axis, &up, &source);
    Graphu64_NormalizeVec3(&axis);

    angle = Graphu64_ArcCos((up.x * source.x) +
                          (up.y * source.y) +
                          (up.z * source.z));
    angle *= g_actorBoneAimAngleScale;
    scale = Gu_Sinf(angle);
    result.x = axis.x * scale;
    result.y = axis.y * scale;
    result.z = axis.z * scale;
    g_turretAimSine = scale;
    result.w = Math_Cosf(angle);

    return result;
}
