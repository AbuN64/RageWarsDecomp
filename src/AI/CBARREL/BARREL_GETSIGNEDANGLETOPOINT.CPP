#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/FIELD_VEC_B0.H"
#include "TYPES.H"
#include "COMMON/MATH_HELPERS.H"

/* 80213ED4_18.CPP */
/* Returns the signed angle between an actor's facing and the direction to a point on the ground plane:
   normalises the offset from the actor at 0x8 to the point, takes its dot product with the facing
   built from the sine and cosine of the yaw at 0x6C, clamps it to -1..1, converts it through the arc
   cosine Graphu64_ArcCos and negates it when the point lies on the other side, or returns zero when the
   point is at the actor. Scheduler lever, disclosed: the sine read sits in a do-while(0) block. */
extern f32 Gu_Sqrtf(f32);

f32 Barrel_GetSignedAngleToPoint(void *actor, CVector3 point) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 s;
    f32 c;
    f32 dot;
    f32 angle;
    dx = point.x - ((struct BarrelAnchorActorView *)actor)->pos.x;
    dz = point.z - ((struct BarrelAnchorActorView *)actor)->pos.z;
    dist = Gu_Sqrtf(dx * dx + dz * dz);
    if (dist == 0.0f) {
        return 0.0f;
    }
    do {
        s = Gu_Sinf(((struct BarrelAnchorActorView *)actor)->heading);
    } while (0);
    c = -Math_Cosf(((struct BarrelAnchorActorView *)actor)->heading);
    dot = (dx * -s + dz * c) / dist;
    dot = ((RW_MIN(dot, 1.0f))<((-1.0f))?((-1.0f)):(RW_MIN(dot, 1.0f)));
    angle = Graphu64_ArcCos(dot);
    if (dx * c + dz * s > 0.0f) {
        return angle;
    }
    return -angle;
}

/* 80213ED4_23.CPP */
#if defined(VERSION_US)
const float g_barrelFlaggedEffectRandomRanges[] = {
    450.0f, 600.0f, 450.0f, 600.0f,
};
#endif
