#include "Common/world.h"
#include "Common/level_actor.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Common/motion_step.h"
#include "Common/rendersortrecord.h"
#include "types.h"
#include "Engine/Unicol/PLTFMCOL.h"
#include "Pickup/pickup_cancollect.h"
#include "Common/approachlocation.h"
#include "Engine/Unicol/Instcol/instcol.h"
#include "Common/box_contact.h"
#include "Common/sharedplayer.h"
#include "Common/resident_event_handler.h"
#include "Common/output.h"
#include "Common/objb.h"
#include "Engine/Unicol/instcol.h"
#include "Common/ppdecom_unpackresource.h"
#include "Common/texture_request.h"
#include "Scene/cache_requestresource.h"
#include "Render/setn64_getpacksection.h"
#include "Common/shared_gameslot.h"
#include "Ai/Player/player_startplayeranimation.h"
#include "Game/builddirectionmatrix.h"
#include "Gobjinst/gobjinst_requestanimatedmodelvariant.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Ppdecom/ppdecom_quicksortrecords.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Common/Lone/collision_current_actor.h"
#include "Engine/Unicol/Instcol/instcol_processentitycontacts.h"
#include "Instcol/instcol.h"
#include "Collide/ccollision_testsegmentdisk.h"
#include "System/events_delivercontacteffect.h"
#include "Particle/particle_releaseownerlistoneeffects.h"
#include "Collide/ccollision_intersectsegmentbox.h"
#include "Scene/cache_allocateresourceat.h"
#include "Common/vector4f.h"

/* INSTCOL.CPP */

/* Tests a contact sweep against instance collision. The query is read-only (0x30 bytes);
 * contact storage is local (0xDC bytes). Floor and ceiling crossings use opposite signed
 * height tests, and their normal constants are -1 and +1 in all five ROMs. */
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
 * shape heights and 0x54, its horizontal bounds widened by the radius and the shape's 0x400 flag;
 * then Instcol_TestEntityContact is run for every entity other than the object itself, except type 1 entities without
 * a body when the shape is flagged 1 and type 3 entities when the shape is not flagged 0x20. */

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
const float k_InstcolConstants[2] = {
    1.0f, 1.0f,
};
#endif

#if defined(VERSION_DE)
/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
const unsigned int k_instcolStaleConstants[2] = {
    0x0023F858, 0x0023F880,
};
#endif

/* INSTCOL_PROCESSENTITYCONTACTS.CPP */

s32 CInstanceCollision_TestBoxFaces(BoxContactRay *ray, void *bounds, BoxContactActor *actor, CVector3 *origin,
    CVector3 *vertices, BoxContactTransform *transform, s32 index) {
    CVector3 *corners[4], *current;
    CVector3 normal, delta, hit, edge, offset;
    BoxContactPolygon polygon;
    CVector3 effectPosition;
    ContactEffectStyle style;
    ContactProjectile *projectile;
    s32 face, i, next, inside, found;
    f32 denominator, distance, fraction;
    found = 0;
    for (face = 0; face < 6; face++) {
        switch (face) {
        case 0:
            corners[0] = &vertices[7]; corners[1] = &vertices[6];
            corners[2] = &vertices[5]; corners[3] = &vertices[4];
            Graphu64_SubtractVectors(&normal, &vertices[4], &vertices[0]); break;
        case 1:
            corners[0] = &vertices[4]; corners[1] = &vertices[5];
            corners[2] = &vertices[1]; corners[3] = &vertices[0];
            Graphu64_SubtractVectors(&normal, &vertices[0], &vertices[3]); break;
        case 2:
            corners[0] = &vertices[7]; corners[1] = &vertices[4];
            corners[2] = &vertices[0]; corners[3] = &vertices[3];
            Graphu64_SubtractVectors(&normal, &vertices[3], &vertices[2]); break;
        case 3:
            corners[0] = &vertices[6]; corners[1] = &vertices[7];
            corners[2] = &vertices[3]; corners[3] = &vertices[2];
            Graphu64_SubtractVectors(&normal, &vertices[2], &vertices[1]); break;
        case 4:
            corners[0] = &vertices[5]; corners[1] = &vertices[6];
            corners[2] = &vertices[2]; corners[3] = &vertices[1];
            Graphu64_SubtractVectors(&normal, &vertices[1], &vertices[0]); break;
        case 5:
            corners[0] = &vertices[0]; corners[1] = &vertices[1];
            corners[2] = &vertices[2]; corners[3] = &vertices[3];
            Graphu64_SubtractVectors(&normal, &vertices[3], &vertices[7]); break;
        }
        denominator = (normal.x * ray->direction.x + normal.y * ray->direction.y + normal.z * ray->direction.z);
        if (denominator == 0.0f) continue;
        Graphu64_SubtractVectors(&delta, origin, corners[0]);
        distance = (delta.x * normal.x + delta.y * normal.y + delta.z * normal.z);
        if (distance == 0.0f) continue;
        fraction = -distance / denominator;
        if (!(fraction < ray->nearest.t)) continue;
        hit.x = origin->x + fraction * ray->direction.x;
        hit.y = origin->y + fraction * ray->direction.y;
        hit.z = origin->z + fraction * ray->direction.z;
        inside = 1;
        for (i = 0; i < 4; i++) {
            next = i == 3 ? 0 : i + 1;
            current = corners[i];
            Graphu64_SubtractVectors(&edge, corners[next], current);
            Graphu64_SubtractVectors(&offset, &hit, current);
            if ((edge.x * offset.x + edge.y * offset.y + edge.z * offset.z) < 0.0f) { inside = 0; break; }
        }
        if (!inside) continue;
        if (InstHdr_UsesDefaultDefinitionHandling(actor)) polygon.kind = ray->material->alternateKind;
        else polygon.kind = ray->material->kind;
        polygon.type = 8;
        polygon.response = ray->material->response;
        polygon.count = 0; polygon.flags = 0;
        polygon.normal = normal; polygon.valid = 1; polygon.point = *corners[0];
        if (!CCollision_TestSegmentPolygon(ray, &polygon, 1)) continue;
        ray->nearest.actor = actor; ray->nearest.index = index;
        if (transform) ray->nearest.transform = *transform;
        found = 1;
        projectile = ray->projectile;
        if (projectile->type != 2 || (projectile->kind != 1044 && projectile->kind != 1069)) continue;
        if (projectile->owner == actor) {
            Player_ReleaseObjectHandles(actor->widget);
            ray->projectile->contactState = found;
            return 0;
        }
        if (projectile->lastHit == actor) continue;
        projectile->lastHit = actor;
        ray->projectile->ticks = 0;
        Graphu64_InterpolateVector(&effectPosition, ray->nearest.t, &ray->projectile->position, &ray->end);
        style.kind = 5; style.flags = 0x2300; style.mode = 5;
        style.red = ray->projectile->color.x;
        style.green = ray->projectile->color.y;
        style.blue = ray->projectile->color.z;
        Events_DeliverContactEffect(actor, ray->projectile, 2, -1, effectPosition, style);
        if (*actor->kind == 11 && ray->projectile->kind == 1069) {
            Particle_GetEffectResource(ray->projectile);
            Player_AddImpulse(actor, 2.0f);
        }
    }
    return found;
}

/* Tests a ray against an actor's collision boxes: an animated actor tests each of its parts in its
 * part mask whose bone sphere overlaps the ray bounds and is hit by the ray, enlarging the parts flagged
 * as soft for driven vehicles; other actors test the box of their shape bank resource, or their own box. */

void CInstanceCollision_TraceActorBounds(BoxContactRay *ray, BoxContactActor *actor, CVector3 *origin, Box *bounds) {
    CVector3 vertices[8];
    CVector3 corners[8];
    CVector3 center;
    f32 matrix[4][4];
    Box box;
    f32 t;
    s32 count;
    s32 driven;
    void **resource;
    void **shape;
    Box *own;
    CVector3 *corner;
    BoxContactPartTable *table;
    BoxContactTransform *part;
    f32 *extent;
    f32 size;
    f32 big;
    f32 radius;
    s32 soft;
    s32 i;
    s32 flags;
    BoxContactBone *bone;

    driven = 0;
    if (ray->material->flags & 0x20000) {
        if (*actor->kind == 1 || *actor->kind == 4) {
            driven = 1;
        }
    }
    soft = 0;
    if (actor->bones != 0) {
        resource = Gobjinst_RequestAnimatedModelVariant(actor, actor->animation);
    } else {
        resource = 0;
    }
    if (resource != 0) {
        big = actor->scale.y;
        if (!(actor->scale.x <= big)) {
            big = actor->scale.x;
        }
        size = actor->scale.z;
        if (!(big <= size)) {
            size = big;
        }
        table = SetN64_GetPackSection(*resource, 5);
        count = table->count;
        for (i = 0; i < count; i++) {
            part = (BoxContactTransform *)&table->records[i * table->stride];
            if (!(part->mask & actor->partMask)) {
                continue;
            }
            if (driven) {
                flags = part->flags & 3;
                soft = 0;
                if (flags < 4) {
                    soft = flags >= 0;
                }
            }
            bone = &actor->bones[i];
            center.x = bone->whole[3][0];
            center.y = bone->whole[3][1];
            center.z = bone->whole[3][2];
            radius = part->radius * size + 1.0f;
            if (soft) {
                radius *= 1.5f;
            }
            box.min.x = center.x - radius;
            box.min.y = center.y - radius;
            box.min.z = center.z - radius;
            box.max.x = center.x + radius;
            box.max.y = center.y + radius;
            box.max.z = center.z + radius;
            if (bounds->min.x < box.max.x && box.min.x < bounds->max.x && bounds->min.z < box.max.z &&
                box.min.z < bounds->max.z && bounds->min.y < box.max.y && box.min.y < bounds->max.y &&
                CCollision_IntersectSegmentBox(ray, &box, &t)) {
                Graphu64_ConvertMatrixToFloat(matrix, &actor->bones[i]);
                if (soft) {
                    ScaleMatrixLocal(matrix, 1.5f, 1.5f, 1.5f);
                }
                Graphu64_TransformPoints(matrix, part->corners, vertices, 8);
                CInstanceCollision_TestBoxFaces(ray, bounds, actor, origin, vertices, part, i);
            }
        }
        Cache_UnlockResource(0, resource);
        return;
    }
    shape = Cache_RequestResource(0, actor->shapeId, actor->shapeId, actor->shapeBank, 4, 0, 0, "anim object info", 1);
    if (shape != 0) {
        extent = SetN64_GetPackSection(*shape, 0);
        corners[0].x = extent[0];
        corners[0].y = extent[1];
        corners[0].z = extent[2];
        corners[1].x = extent[3];
        corners[1].y = extent[1];
        corners[1].z = extent[2];
        corners[2].x = extent[3];
        corners[2].y = extent[1];
        corners[2].z = extent[5];
        corners[3].x = extent[0];
        corners[3].y = extent[1];
        corners[3].z = extent[5];
        corners[4].x = extent[0];
        corners[4].y = extent[4];
        corners[4].z = extent[2];
        corners[5].x = extent[3];
        corners[5].y = extent[4];
        corners[5].z = extent[2];
        corners[6].x = extent[3];
        corners[6].y = extent[4];
        corners[6].z = extent[5];
        corners[7].x = extent[0];
        corners[7].y = extent[4];
        corners[7].z = extent[5];
        Graphu64_TransformPoints(actor->transform, corners, vertices, 8);
        Cache_UnlockResource(0, shape);
    } else {
        own = &actor->box;
        corner = vertices;
        corner[0].x = own->min.x;
        corner[0].y = own->min.y;
        corner[0].z = own->min.z;
        corner[1].x = own->max.x;
        corner[1].y = own->min.y;
        corner[1].z = own->min.z;
        corner[2].x = own->max.x;
        corner[2].y = own->min.y;
        corner[2].z = own->max.z;
        corner[3].x = own->min.x;
        corner[3].y = own->min.y;
        corner[3].z = own->max.z;
        corner[4].x = own->min.x;
        corner[4].y = own->max.y;
        corner[4].z = own->min.z;
        corner[5].x = own->max.x;
        corner[5].y = own->max.y;
        corner[5].z = own->min.z;
        corner[6].x = own->max.x;
        corner[6].y = own->max.y;
        corner[6].z = own->max.z;
        corner[7].x = own->min.x;
        corner[7].y = own->max.y;
        corner[7].z = own->max.z;
    }
    CInstanceCollision_TestBoxFaces(ray, bounds, actor, origin, vertices, 0, -1);
}

/* Collect overlapping actors, sort their contact distances, and dispatch each contact within range. */
typedef struct SortedCandidate { LevelActor *object; f32 distance; } SortedCandidate;
typedef struct HitState {
    u32 flags;
    s8 mode;
} HitState;
typedef struct HitOwner {
    u8 kind;
    u8 pad1[7];
    CVector3 position;
    u8 pad14[0x104];
    u32 *rules;
    u8 pad11C[0x10];
    LevelActor *target;
} HitOwner;
typedef struct HitSelf {
    HitOwner *owner;
    u8 pad4[0x3C];
    HitState *state;
    u8 pad44[0x40];
    Box box;
    u8 pad9C[0xE0];
    f32 range;
} HitSelf;

void InstCol_ProcessEntityContacts(HitSelf *self) {
    HitState *state = self->state;
    u8 scratch[48];
    SortedCandidate list[32];
    SortedCandidate *entry;
    HitOwner *owner;
    Shared_World *world;
    Shared_Game *game;
    LevelActor *candidate;
    s32 total;
    s32 count;
    s32 i, contactIndex;
    s32 kind;
    f32 distance;
    if (state->mode == 0 || !(state->flags & 0x10000)) {
        return;
    }
    entry = list;
    count = i = 0;
    owner = self->owner;
    world = &g_world;
    total = world->moverCount;
    for (; i < total; i++) {
        if (count >= 32) break;
        candidate = world->movers[i];
        if ((LevelActor *)owner == candidate) {
            continue;
        }
        if (state->mode == 7 && g_collisionCurrentActor->instance0 == (void *)candidate) {
            continue;
        }
        if ((state->flags & 0x8000) && candidate->type == 1615) {
            continue;
        }
        if (owner->kind == 2 && owner->target == candidate) {
            if (*owner->rules & 0x40) {
                continue;
            }
            kind = *(s32 *)candidate->definition;
            if (kind == 1 || kind == 4) {
                continue;
            }
        }
        if (!(self->box.max.x > candidate->bounds.min.x)) continue;
        if (!(self->box.min.x < candidate->bounds.max.x)) continue;
        if (!(self->box.max.z > candidate->bounds.min.z)) continue;
        if (!(self->box.min.z < candidate->bounds.max.z)) continue;
        if (!(self->box.max.y > candidate->bounds.min.y)) continue;
        if (!(self->box.min.y < candidate->bounds.max.y)) continue;
        if (CCollision_IntersectSegmentBox(self, &candidate->bounds, &distance) != 0) {
            entry->object = candidate;
            entry->distance = distance;
            count++;
            entry++;
        }
    }
    if (count == 0) {
        return;
    }
    PpDecom_QuickSortRecords(list, count, 8, CInstanceCollision_CompareSortedContacts, CInstanceCollision_SwapSortedContacts);
    entry = list;
    for (contactIndex = 0; contactIndex < count; contactIndex++, entry++) {
        if (!(entry->distance < self->range)) {
            return;
        }
        candidate = entry->object;
        if ((candidate->flags & 0x300000) && (game = &g_gameSettings)->local == 0) {
            CInstanceCollision_BuildSweepQuery(self, scratch);
            Instcol_TestEntityContact(self, scratch, candidate);
        } else {
            CInstanceCollision_TraceActorBounds(self, candidate, &owner->position, &self->box);
        }
    }
}

#if defined(VERSION_DE)
float k_InstcolProcessentitycontactsConstants[3] = {
    1.0f, -1.0f, 1.0f,
};
#endif

/* CCOLLISION_EXPANDBOXCOORDINATES.CPP */

/** Expand six source floats into the fixed 24-float vertex pattern. */
void CCollision_ExpandBoxCoordinates(float *s, float *d) {
    d[0]=s[0]; d[1]=s[1]; d[2]=s[2]; d[3]=s[3];
    d[4]=s[1]; d[5]=s[2]; d[6]=s[3]; d[7]=s[1];
    d[8]=s[5]; d[9]=s[0]; d[10]=s[1]; d[11]=s[5];
    d[12]=s[0]; d[13]=s[4]; d[14]=s[2]; d[15]=s[3];
    d[16]=s[4]; d[17]=s[2]; d[18]=s[3]; d[19]=s[4];
    d[20]=s[5]; d[21]=s[0]; d[22]=s[4]; d[23]=s[5];
}

/** Swap two eight-byte pairs. */
void CRenderSortRecord_Swap(RenderSortRecord *left, RenderSortRecord *right) {
    RenderSortRecord temporary = *left;
    *left = *right;
    *right = temporary;
}

/** Order two render-sort records by depth. */
int CRenderSortRecord_CompareDepth(RenderSortRecord *left, RenderSortRecord *right) {
    return left->depth < right->depth ? -1 : 1;
}

/* NAVIGATION_CONSTANT_STORAGE_RETAINED_WORDS_EU_EU_X_US.CPP */

#if defined(VERSION_EU_X)
struct {
    u8 retainedFloatWords[12];
} g_navigationConstantStorageRetainedWords __attribute__((aligned(4))) = {
    { 0x4F, 0x00, 0x00, 0x00, 0x47, 0x80, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00 }
};
#endif
