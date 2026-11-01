#include "COMMON/WORLD.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MOTION_STEP.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RENDERSORTRECORD.H"
#include "TYPES.H"

extern f32 Gobjinst_GetActorRadius(void *);
extern f32 InstHdr_GetActorBaseOffset(void *);
extern f32 Gobjinst_GetActorHeight(void *);
extern void CPlatformCollision_ProcessRiderMotion(void *, void *);
extern void CPlatformCollision_TraceShape(void *, void *);
extern s32 Pickup_CanCollect(void *, void *);
extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);
extern s32 CCollision_TestSegmentPolygon(void *, void *, s32);
extern s32 CCollision_TestRayCylinder(void *, CVector3 *, f32, f32, f32, s32, void *, s32);
/* Hand C from us-rev1 8023EEF0..8023F42C.
 * The query is read-only (0x30 bytes); contact storage is local (0xDC).
 * Floor/ceiling crossings use opposite signed height tests. Their normal
 * constants are -1/+1 in all five ROMs (us-rev1 ROM 0xC93D0/0xC93D4). */
static inline f32 Anim_GetContactRadius(struct Query *sweep, f32 actorRadius) {
    return sweep->radius + actorRadius;
}

static inline s8 Anim_GetSurfaceKind(LevelActor *entity) {
    if (entity->definition->gate & 0x80) return 2;
    return 7;
}

void Instcol_TestEntityContact(ActorMotion *motion, struct Query *sweep, LevelActor *entity) {
    LevelActor *owner;
    CCollisionInfo2_t *surface;
    f32 bounds[4];
    CVector3 point;
    CVector3 normal;
    BoxContactPolygon contact;
    f32 entityX;
    f32 entityZ;
    f32 radius;
    f32 bottom;
    f32 top;
    f32 ownerX;
    f32 ownerZ;
    f32 time;
    f32 deltaX;
    f32 deltaZ;
    s32 special;

    entityX = entity->position0.x;
    entityZ = entity->position0.z;
    radius = Gobjinst_GetActorRadius(entity);
    bounds[0] = entityX - radius;
    bounds[2] = entityX + radius;
    bounds[1] = entityZ - radius;
    bounds[3] = entityZ + radius;
    if (!(bounds[0] < sweep->maxX && sweep->minX < bounds[2] &&
          bounds[1] < sweep->maxZ && sweep->minZ < bounds[3])) {
        return;
    }
    special = 0;
    owner = motion->actor;
    surface = motion->surface;
    if (owner->kind == 1 && owner->definition->kind == 2) {
        if (entity->kind == owner->kind) {
            CPlatformCollision_ProcessRiderMotion(motion, entity);
        }
        return;
    }
    if (entity->kind == 1 && entity->definition->kind == 2) {
        if (owner->kind == entity->kind) {
            CPlatformCollision_TraceShape(motion, entity);
        }
        return;
    }
    if (entity->kind == 3) {
        if (Pickup_CanCollect(entity, owner) == 0) {
            return;
        }
        special = 1;
    }
    contact.type = 7;
    contact.response = 0.0f;
    contact.count = 0;
    contact.flags = 0;
    contact.valid = 1;
    contact.actor = (BoxContactActor *)entity;
    contact.index = -1;
    bottom = entity->position0.y + InstHdr_GetActorBaseOffset(entity);
    top = Gobjinst_GetActorHeight(entity) + bottom;
    if (sweep->flag != 0) {
        normal.x = normal.z = 0.0f;
    }
    ownerX = owner->position0.x;
    ownerZ = owner->position0.z;
    radius = Anim_GetContactRadius(sweep, radius);
    if (sweep->flag != 0) {
        if (motion->velocity.y != 0.0f) {
            if (sweep->top1 <= bottom && bottom < sweep->top2) {
                time = (bottom - sweep->top1) / motion->velocity.y;
                if (time < motion->blend) {
                    Graphu64_InterpolateVector(&point, time, &owner->position0, &motion->end);
                    deltaX = entityX - point.x;
                    deltaZ = entityZ - point.z;
                    if (deltaX * deltaX + deltaZ * deltaZ < radius * radius) {
                        contact.kind = 7;
                        contact.point = point;
                        contact.normal.x = 0.0f;
                        contact.normal.z = 0.0f;
                        contact.normal.y = -1.0f;
                        CCollision_TestSegmentPolygon(motion, &contact, 1);
                    }
                }
            }
            if (top <= sweep->bottom1 && sweep->bottom2 < top) {
                time = (top - sweep->bottom1) / motion->velocity.y;
                if (time < motion->blend) {
                    Graphu64_InterpolateVector(&point, time, &owner->position0, &motion->end);
                    deltaX = entityX - point.x;
                    deltaZ = entityZ - point.z;
                    if (deltaX * deltaX + deltaZ * deltaZ < radius * radius) {
                        if (surface->InstanceBehavior == 1) {
                            contact.kind = surface->InstanceBehavior;
                        } else {
                            contact.kind = Anim_GetSurfaceKind(entity);
                        }
                        contact.point = point;
                        contact.normal.x = 0.0f;
                        contact.normal.z = 0.0f;
                        contact.normal.y = 1.0f;
                        CCollision_TestSegmentPolygon(motion, &contact, 1);
                    }
                }
            }
        }
    }
    contact.kind = special != 0 ? 7 : surface->InstanceBehavior;
    CCollision_TestRayCylinder(motion, &entity->position0, radius,
                    top - sweep->bottom, bottom - sweep->top, 1, &contact, 1);
    if (special != 0 && motion->specialCandidate != entity &&
        sweep->bottom1 <= top && bottom < sweep->top1) {
        deltaX = entityX - ownerX;
        deltaZ = entityZ - ownerZ;
        if (deltaX * deltaX + deltaZ * deltaZ < radius * radius) {
            contact.t = 0.0f;
            contact.normal.x = 0.0f;
            contact.normal.y = 0.0f;
            contact.normal.z = 0.0f;
            contact.hit = motion->start;
            *(BoxContactPolygon *)&motion->collisionState = contact;
        }
    }
}

typedef struct Query Query;
/* Queries the registered entities an object may collide with: when the object's shape is enabled and is
 * not the null shape, a query holds the object's radius, its vertical span and that span offset by the
 * shape heights at 0x48 and 0x54, its horizontal bounds widened by the radius and the shape's 0x400 flag;
 * then Instcol_TestEntityContact is run for every entity other than the object itself, except type 1 entities without
 * a body at 0x174 when the shape is flagged 1 and type 3 entities when the shape is not flagged 0x20. */

extern void Instcol_TestEntityContact(ActorMotion *, Query *, LevelActor *);

void CInstanceCollision_TraceInteractiveActors(char *obj) {
    Query query;
    Query *q;
    CCollisionInfo2_t *shape;
    void *self;
    s32 count;
    s32 i;
    u8 *entity;
    Shared_World *table;
    f32 radius;
    f32 bound;

    shape = ((ActorMotion *)obj)->surface;
    if (shape->InstanceBehavior == 0 || shape == (void *)&g_collisionSurfaceExcludedFromTrace) {
        return;
    }
    table = &g_world;
    q = &query;
    radius = ((ActorMotion *)obj)->radius;
    self = ((ActorMotion *)obj)->actor;
    q->radius = radius;
    count = table->interactiveCount;
    q->flag = shape->dwFlags & 0x400;
    q->bottom = ((ActorMotion *)obj)->bottom;
    q->top = q->bottom + ((ActorMotion *)obj)->height;
    q->bottom1 = ((ActorMotion *)obj)->start.y + q->bottom;
    q->top1 = ((ActorMotion *)obj)->start.y + q->top;
    q->bottom2 = ((ActorMotion *)obj)->end.y + q->bottom;
    q->top2 = ((ActorMotion *)obj)->end.y + q->top;
    bound = ((ActorMotion *)obj)->end.x;
    if (!(bound <= ((ActorMotion *)obj)->start.x)) {
        bound = ((ActorMotion *)obj)->start.x;
    }
    q->minX = bound - radius;
    bound = ((ActorMotion *)obj)->end.x;
    if (!(((ActorMotion *)obj)->start.x <= bound)) {
        bound = ((ActorMotion *)obj)->start.x;
    }
    q->maxX = bound + radius;
    bound = ((ActorMotion *)obj)->end.z;
    if (!(bound <= ((ActorMotion *)obj)->start.z)) {
        bound = ((ActorMotion *)obj)->start.z;
    }
    q->minZ = bound - radius;
    bound = ((ActorMotion *)obj)->end.z;
    if (!(((ActorMotion *)obj)->start.z <= bound)) {
        bound = ((ActorMotion *)obj)->start.z;
    }
    q->maxZ = bound + radius;
    for (i = 0; i < count; i++) {
        entity = (u8 *)table->interactive[i];
        if (entity == self) {
            continue;
        }
        switch (*entity) {
        case 2:
            break;
        case 1:
            if ((shape->dwFlags & 1) && ((LevelActor *)entity)->active == 0) {
                continue;
            }
            break;
        case 3:
            if (!(shape->dwFlags & 0x20)) {
                continue;
            }
            break;
        }
        Instcol_TestEntityContact(obj, &query, entity);
    }
}

void CInstanceCollision_BuildSweepQuery(ActorMotion *motion, f32 *queryStorage)
{
  f32 *height;
  f32 bottomOffset;
  f32 value;
  u32 *surfaceFlags;
  f32 bound;
  surfaceFlags = &motion->surface->dwFlags;
  ((Query *)queryStorage)->radius = motion->radius;
  ((Query *)queryStorage)->flag = (*surfaceFlags) & 0x400;
  bottomOffset = motion->bottom;
  ((Query *)queryStorage)->bottom = bottomOffset;
  height = &motion->height;
  ((Query *)queryStorage)->top = bottomOffset + (*height);
  ((Query *)queryStorage)->bottom1 = (motion->start.y) + ((Query *)queryStorage)->bottom;
  ((Query *)queryStorage)->top1 = (motion->start.y) + ((Query *)queryStorage)->top;
  ((Query *)queryStorage)->bottom2 = (motion->end.y) + ((Query *)queryStorage)->bottom;
  ((Query *)queryStorage)->top2 = (motion->end.y) + ((Query *)queryStorage)->top;
  value = motion->end.x;
  bound = motion->start.x;
  if (!(value <= bound))
  {
    value = bound;
  }
  ((Query *)queryStorage)->minX = value - ((Query *)queryStorage)->radius;
  value = motion->end.x;
  bound = motion->start.x;
  if (!(bound <= value))
  {
    value = bound;
  }
  ((Query *)queryStorage)->maxX = value + ((Query *)queryStorage)->radius;
  value = motion->end.z;
  bound = motion->start.z;
  if (!(value <= bound))
  {
    value = bound;
  }
  ((Query *)queryStorage)->minZ = value - ((Query *)queryStorage)->radius;
  value = motion->end.z;
  bound = motion->start.z;
  if (!(bound <= value))
  {
    value = bound;
  }
  ((Query *)queryStorage)->maxZ = value + ((Query *)queryStorage)->radius;
}


#if defined(VERSION_US)
const char s_InstcolTEosTText[8] =
    "_t\004.eosT";
#endif

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
const float k_InstcolEncodedWordsBlock3[2] = {
    1.0f, 1.0f,
};
#endif


#if defined(VERSION_DE)
/* Alignment fill to the next 16-byte object boundary. */
const unsigned int k_InstcolEncodedWordsBlock1AlignmentPad[2] = {
    0x0023F858, 0x0023F880,
};
#endif
