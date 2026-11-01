#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/PROBE.H"
#include "TYPES.H"
#include "ENGINE/INSTANCE/GOBJINST.H"
#include "INSTHDR/INSTHDR_GETACTORSHADOWRADIUS.H"

/* 8024D018.CPP */
/* Builds a 4x4 transform from a rotation quaternion (x, y, z, w) and a translation, with a zero fourth column and the corner set to the constant at g_actorAffineMatrixHomogeneousUnit. */

void GameObject_BuildQuaternionTranslationMatrix(f32 *m, f32 *q, f32 *t)
{
    f32 x = q[0];
    f32 xx = x * x;
    f32 y = q[1];
    f32 yy = y * y;
    f32 z = q[2];
    f32 zz = z * z;
    f32 w = q[3];
    f32 ww = w * w;
    f32 x2 = x + x;
    f32 xy = x2 * y;
    f32 w2 = w + w;
    f32 wz = w2 * z;
    f32 xz = x2 * z;
    f32 wy = w2 * y;
    f32 wx = w2 * x;
    f32 yz = (y + y) * z;

    m[0] = ww + xx - yy - zz;
    m[1] = xy + wz;
    m[2] = xz - wy;
    m[4] = xy - wz;
    m[5] = ww - xx + yy - zz;
    m[6] = yz + wx;
    m[8] = xz + wy;
    m[9] = yz - wx;
    m[10] = ww - xx - yy + zz;
    m[12] = t[0];
    m[13] = t[1];
    m[14] = t[2];
    m[3] = 0.0f;
    m[7] = 0.0f;
    m[11] = 0.0f;
    m[15] = g_actorAffineMatrixHomogeneousUnit;
}

extern int Lighting_BuildLitModel(int a, int b, void *c, void *d, int e, void *f);
extern void Cache_ReplaceResourcePairFirst(int a, int **b, int c);

void GameObject_BuildLitActorResource(void *levelActor, int **resourcePair) {
    struct LevelActor *object = levelActor;
    int *deref1;
    int deref2;
    int ret;

    deref1 = *resourcePair;
    deref2 = *deref1;
    ret = Lighting_BuildLitModel(deref2, 0, &object->bounds, object->animationMatrices, 1, levelActor);
    Cache_ReplaceResourcePairFirst(0, resourcePair, ret);
}

typedef struct InteractionDescriptor { s32 kind; char pad4[0x10]; s32 flags; } InteractionDescriptor;
typedef struct InteractionLink { char pad0[0x1C]; s32 flags; char pad20[0x83C]; s32 linked; } InteractionLink;
typedef struct InteractionActor {
    u8 kind; char pad1[0x17]; InteractionDescriptor *descriptor;
    char pad1C[0xE4]; s32 flags; char pad104[0x9C]; InteractionLink *attached;
    char pad1A4[0x34]; InteractionLink *player;
} InteractionActor;
s32 InstHdr_CanActorReceiveInteraction(InteractionActor *actor) {
    s32 flags;
    InteractionLink *link;
    s32 bit;
    switch (actor->descriptor->kind) {
    case 11:
        if (actor->kind == 1 && (actor->flags & 0x300000) != 0) {
            link = actor->player;
            if (g_gameSettings.local != 0 && link->linked != 0) return 0;
        }
    case 8: return 1;
    case 0: return actor->descriptor->flags & 2;
    case 2:
        if (actor->kind != 1) return 0;
        return actor->flags & 0x10000;
    case 1:
        if (actor->kind != 1 || (actor->flags & 0x2000) == 0) return 0;
        link = actor->attached;
        if (link == 0) return 0;
        bit = link->flags & 0x10000;
        return !bit;
    case 4: case 5: case 7: case 10:
        if (actor->kind != 1) return 0;
        flags = actor->flags;
        if (!(flags & 0x2000)) return 0;
        return flags & 0x10000;
    case 12: return actor->descriptor->flags & 1;
    }
    return 0;
}

f32 Gobjinst_GetActorHeight(Actor_u1 *actor) {
    Resource_u1 *resource;

    if (actor->kind == 1 && actor->active <= 0) {
        return InstHdr_GetInactiveActorHeight(actor);
    }
    switch (actor->resource->kind) {
    case 11:
        if (actor->kind == 1 && (actor->flags & 0x300000)) {
            return actor->state->heightDelta;
        }
        return actor->resource->valueF4;
    case 1:
    case 4:
        return actor->resource->value30;
    case 8:
        resource = actor->resource;
        if (resource->flags14 & 1) {
            return 122.88f;
        }
        return resource->value1C;
    case 7:
        return actor->resource->value20;
    case 6:
        return 102.399994f;
    case 0:
    case 5:
    case 10:
    case 12:
    case 13:
    case 14:
        return actor->resource->value1C;
    }
    return 0.0f;
}

/* 8024D018_2.CPP */
f32 Gobjinst_GetActorRadius(Actor_u1 *actor)
{
    Resource_u1 *resource;
    f32 a;
    f32 b;
    switch (actor->resource->kind) {
    case 11:
        if (actor->kind == 1 && (actor->flags & 0x300000) && actor->state->active) {
            return g_activePlayerActorRadius;
        }
        return actor->resource->valueEC;
    case 0: case 5: case 8: case 10: case 12: case 13: case 14:
        return actor->resource->radius;
    case 1: case 4:
        return actor->resource->value28;
    case 2:
        resource = actor->resource;
        if (((CollisionShapeResource *)resource)->mode == 2) {
            a = ((CollisionShapeResource *)resource)->width;
            b = ((CollisionShapeResource *)resource)->height;
            if (!(b <= a)) a = b;
            b = ((CollisionShapeResource *)resource)->depth;
            if (!(a <= b)) b = a;
            return b * g_collisionShapeRadiusScale;
        }
        return ((CollisionShapeResource *)resource)->height;
    case 7:
        return actor->resource->value1C;
    default:
        return 0.0f;
    }
}

#if defined(VERSION_DE)
const float k_GameobjectGetactorheightEncodedWords[2] = {
    122.88f, 1.42f,
};
#endif
