#include "COMMON/DESCRIPTORRECAT29.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/BOX_CONTACT.H"
#include "COMMON/LEGACY_COLLISION_ACTOR.H"
#include "COMMON/MOTION_STEP.H"
#include "COMMON/WORLD.H"
#include "COMMON/OUTPUT.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "ENGINE/UNICOL/COLLIDE.H"

/* Tests a ray against a polygon with a radius: intersects the ray from 0x44 to 0x50 with the polygon's plane
 * through CCollision_IntersectFrontPlaneFraction and accepts a parameter nearer than the ray's nearest hit, also allowing a slightly
 * negative one (above -g_collisionSlackThreshold * g_collisionSegmentPolygonSlackFactor[1] scaled by the ray's 0x80 factor) except for kind 7 and
 * types 5 and 6; the hit point is then placed with Graphu64_InterpolateVector and tested against the polygon with the
 * given point and radius through CCollision_IsPointInsideDisk. On a hit the polygon record is optionally kept as the ray's
 * nearest hit. Adapted from CCollision_TestSegmentPolygon with the radius test and the slack constant. */









extern s32 CCollision_IntersectFrontPlaneFraction(PolygonCCollisionTestSegmentPolygon *, CVector3 *, CVector3 *, f32 *);

extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);

extern s32 CCollision_IsPointInsideDisk(PolygonCCollisionTestSegmentPolygon *, CVector3 *, f32, CVector3 *);

static inline s32 accepts(CapsuleSweep *ray, PolygonCCollisionTestSegmentPolygon *poly) {
    if (poly->t <= 0.0f) {
        if (poly->kind == 7) {
            return 0;
        }
        if ((u32)(poly->type - 5) < 2) {
            return 0;
        }
        if (poly->t * ray->slack < -(g_collisionSlackThreshold * g_collisionSegmentDiskSlackFactor)) {
            return 0;
        }
    }
    if (poly->t >= ray->nearest.t) {
        return 0;
    }
    return 1;
}

extern World *g_collisionCurrentActor;

extern void *Scene_GetModelRecordByIndexPointer(Shared_World *, u16 *);

s32 CCollision_TestSegmentDisk(CapsuleSweep *ray, PolygonCCollisionTestSegmentPolygon *poly, CVector3 *point, f32 radius, s32 keep) {
    if (CCollision_IntersectFrontPlaneFraction(poly, &ray->start, &ray->end, &poly->t) == 0) {
        return 0;
    }
    if (accepts(ray, poly) == 0) {
        return 0;
    }
    Graphu64_InterpolateVector(&poly->hit, poly->t, &ray->start, &ray->end);
    if (CCollision_IsPointInsideDisk(poly, point, radius, &poly->hit) == 0) {
        return 0;
    }
    if (keep != 0) {
        ray->nearest = *poly;
    }
    return 1;
}

void CCollision_ClearResultFlags(void)
{
  g_collisionCurrentActor->resultFlagsF = (g_collisionCurrentActor->state = (g_collisionCurrentActor->resultFlagsE = (g_collisionCurrentActor->resultFlagsD = (g_collisionCurrentActor->resultFlagsC = (g_collisionCurrentActor->resultFlagsB = (g_collisionCurrentActor->resultFlagsA = 0))))));
}

void CCollision_UpdateSurfaceResponseFlags(ActorMotion *motion, MotionContactResult *contact) {
    s32 contactFlags;
    s32 clearedFlags;

    clearedFlags = motion->flags & ~0xE00;
    motion->flags = clearedFlags;
    contactFlags = contact->flags;
    if (contactFlags & 0x20000000) {
        motion->flags = clearedFlags | 0x200;
        return;
    }
    if (contactFlags & 0x40000000) {
        motion->flags = clearedFlags | 0x400;
        return;
    }
    if (contactFlags < 0) {
        motion->flags = clearedFlags | 0x800;
    }
}

void CCollision_UpdateMaterialFlags(ActorMotion *motion, MotionContactResult *contact) {
    s32 material;
    s32 currentMotionFlags;
    s32 flags;
    s32 baseMotionFlags;

    flags = motion->flags;
    if (flags & 0x1000) {
        motion->flags = flags & ~0x2000;
    }
    currentMotionFlags = motion->flags;
    baseMotionFlags = currentMotionFlags & 0xFFFC7FFF;
    motion->flags = baseMotionFlags;
    if (currentMotionFlags & 0x7000) {
        material = contact->material;
        switch (material) {
        case 8:
            motion->flags = baseMotionFlags | 0x10000;
            return;
        case 7:
            motion->flags = baseMotionFlags | 0x8000;
            break;
        }
    }
}

void CCollision_UpdateModelSurfaceFlags(void *motionStorage, u16 *surfaceKey)
{
  char *o = (char *) motionStorage;
  s32 initialMotionFlags;
  s32 currentMotionFlags;
  s32 updatedMotionFlags;
  void *surfaceRecord;
  initialMotionFlags = ((Shared_CollisionMoveFrame *)o)->motionFlags;
  if (initialMotionFlags & 0x1000)
  {
    ((Shared_CollisionMoveFrame *)o)->motionFlags = initialMotionFlags & (~0x2000);
  }
  currentMotionFlags = ((Shared_CollisionMoveFrame *)o)->motionFlags;
  ((Shared_CollisionMoveFrame *)o)->motionFlags = currentMotionFlags & 0xFFFC7FFF;
  if (currentMotionFlags & 0x7000)
  {
    surfaceRecord = Scene_GetModelRecordByIndexPointer(&g_world, surfaceKey);
    if (surfaceRecord != 0)
    {
      if ((((ModelBlend *)surfaceRecord)->collisionFlags) & 0x400000)
      {
        ;
        ((Shared_CollisionMoveFrame *)o)->motionFlags = (((Shared_CollisionMoveFrame *)o)->motionFlags) | 0x8000;
      }
      else
        if ((((ModelBlend *)surfaceRecord)->materialFlags) & 0x80)
      {
        updatedMotionFlags = (((Shared_CollisionMoveFrame *)o)->motionFlags) | 0x10000;
        ((Shared_CollisionMoveFrame *)o)->motionFlags = updatedMotionFlags;
      }
    }
  }
}

s32 CCollision_IsNearerContact(BoxContactRay *ray, BoxContactPolygon *polygon) {
    f32 hitT;
    s32 isNearer;

    hitT = polygon->t;
    if (hitT <= 0.0f) {
        if (polygon->kind == 7) {
            return 0;
        }
        if ((u32) (polygon->type - 5) < 2) {
            return 0;
        }
        if ((hitT * ray->slack) < -(g_collisionSlackThreshold * g_collisionContactSlackFactor)) {
            return 0;
        }
    }
    isNearer = 0;
    {
        f32 b = polygon->t;
        if (!(ray->nearest.t <= b)) {
            isNearer = 1;
        }
    }
    return isNearer;
}
