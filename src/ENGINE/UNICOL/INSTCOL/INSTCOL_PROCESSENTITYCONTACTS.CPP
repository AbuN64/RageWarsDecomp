#include "COMMON/BOX_CONTACT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/OUTPUT.H"
#include "COMMON/RENDERSORTRECORD.H"
#include "COMMON/OBJB.H"
#include "TYPES.H"
#include "ENGINE/UNICOL/INSTCOL.H"
#include "include_asm.h"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/TEXTURE_REQUEST.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/WORLD.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/SHARED_GAMESLOT.H"

/* 8023EEF0_3.CPP */
s32 CCollision_TestSegmentPolygon(CapsuleSweep *ray, PolygonCCollisionTestSegmentPolygon *poly, s32 keep);
void Player_ReleaseObjectHandles(struct ItemsHandleOwner *);
void Graphu64_InterpolateVector(CVector3 *, f32, void *, void *);
void Events_DeliverContactEffect(void *, void *, s32, s32, CVector3, ContactEffectStyle);
s32 Particle_GetEffectResource(void *);

s32 CInstanceCollision_TestBoxFaces(BoxContactRay *ray, void *unused, BoxContactActor *actor, CVector3 *origin,
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

/* 8023F740.CPP */
/* Tests a ray against an actor's collision boxes: an animated actor tests each of its parts in its
 * part mask whose bone sphere overlaps the ray bounds and is hit by the ray, enlarging the parts flagged
 * as soft for driven vehicles; other actors test the box of their shape bank resource, or their own box. */

s32 CCollision_IntersectSegmentBox(Ray *ray, Box *box, f32 *out);

void **Gobjinst_RequestAnimatedModelVariant(MenuPanelRoot *actor, s32 variantIndex);

void Graphu64_ConvertMatrixToFloat(f32 *dst, PackedMatrixWords *src);

void ScaleMatrixLocal(void *matrix, f32 sx, f32 sy, f32 sz);

void Graphu64_TransformPoints(f32 *m, f32 *in, f32 *out, u32 count);

void Cache_UnlockResource(void *cache, CacheResourceNode *resource);

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
            part = (BoxContactTransform *)((char *)table + (i * table->stride + 8));
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
    u8 pad1[0x117];
    u32 *rules; /* 0x118 */
    u8 pad11C[0x10];
    LevelActor *target; /* 0x12C */
} HitOwner;
typedef struct HitSelf {
    HitOwner *owner; /* 0 */
    u8 pad4[0x3C];
    HitState *state; /* 0x40 */
    u8 pad44[0x40];
    Box box; /* 0x84 */
    u8 pad9C[0xE0];
    f32 range; /* 0x17C */
} HitSelf;
extern LevelActor **g_collisionCurrentActor;
extern char CInstanceCollision_SwapSortedContacts[], CInstanceCollision_CompareSortedContacts[];
extern void PpDecom_QuickSortRecords();
extern void CInstanceCollision_BuildSweepQuery(void *, void *);
void InstCol_ProcessEntityContacts(HitSelf *self) {
    HitState *state = self->state;
    u8 scratch[48];
    SortedCandidate list[32];
    SortedCandidate *entry;
    u8 *ownerPosition;
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
    ownerPosition = (u8 *)owner + 8;
    world = &g_world;
    total = world->moverCount;
    for (; i < total; i++) {
        if (count >= 32) break;
        candidate = world->movers[i];
        if ((LevelActor *)owner == candidate) {
            continue;
        }
        if (state->mode == 7 && *g_collisionCurrentActor == candidate) {
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
            CInstanceCollision_TraceActorBounds(self, candidate, ownerPosition, &self->box);
        }
    }
}



#if defined(VERSION_DE)
float k_InstcolProcessentitycontactsEncodedWordsBlock1[3] = {
    1.0f, -1.0f, 1.0f,
};
#endif
