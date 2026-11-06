#include "Common/navigation_graph.h"
#include "Common/probe.h"
#include "Common/obj.h"
#include "Common/shared_gameslot.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/math_helpers.h"
#include "Common/actor_header.h"
#include "Common/level_actor.h"
#include "types.h"
#include "Engine/Instance/insthdr.h"
#include "Fx/normalize_vector.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Ai/shared_pickupgoalnode.h"
#include "Gregion/gregion.h"
#include "Gobjinst/gobjinst_buildtargetaimorientation.h"
#include "Plane/plane.h"
#include "Portal/portal_isnodemovementblocked.h"
#include "include_asm.h"
#include "common.h"
#include "Common/legacy_collision_actor.h"
#include "Sound/player_movement_scalar_view.h"
#include "Common/world.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Common/propgeometry.h"
#include "Common/rec.h"
#include "Cbarrel/barrel_spawnactoreffect.h"
#include "Engine/gregion.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Ai/cbarrel.h"

/* INSTHDR.CPP */

/* Returns a player's body lean on the ground: a controlled player on an accepted floor (Region_TestPolygonSlopeFlag) that
 * is not held (flag 1) nor in states 1 or 2 computes a tilt toward the floor normal from Region_GetNodeNormal_Insthdr by
 * three eighths of its slope (at most 25 degrees), which the body tilt from Gobjinst_BuildActorDirectionTilt then replaces,
 * and leans along its heading by three quarters of the ground slope ahead from CPlane_GetSlopeAngle (at most 25),
 * blending lean and tilt halfway through Graphu64_InterpolateQuaternionWithLinearFallback; other players take Gobjinst_BuildActorDirectionTilt's tilt, and
 * objects without a floor or held players get the identity. The sine is kept in g_turretAimSine. */

static inline s32 is_held(char *obj) {
    return (((LevelActor *)obj)->kind != 1) ? 0 : (((LevelActor *)(obj))->flags & 1);
}

/* Plays a sound effect for an actor at a position: snaps the position to the nearest registered emitter
 * in g_navigationGraph when there is one, draws a random direction and (except for sound 0xBD7) scales it to a
 * velocity of 409.6, then starts the sound through SetN64_SpawnModelEffect on g_modelEffectPool with the actor's id and
 * the given volume. */








extern CNavData g_navigationGraph;


struct CNavData_t; extern s32 Portal_FindNearestPointIndex(struct CNavData_t *pointSet, void *point);








/* Callers write the lean through a pointer (the MIPS hidden result pointer); a native host cannot call a
 * struct-returning function that way, so the host entry takes the pointer and the body stays by value. */
CQuatern Insthdr_BuildActorGroundRotation(char *obj) {
    CVector3 normal;
    CVector3 up;
    CVector3 axis;
    CQuatern tilt;
    CQuatern lean;
    CQuatern result;
    Probe probe;
    f32 slope;
    f32 sine;
    f32 cosine;
    f32 angle;
    f32 half;
    char *self;

    if (((LevelActor *)(obj))->model != 0 && is_held(obj) == 0) {
        if (((LevelActor *)obj)->kind == 1) {
            self = obj;
            if (((LevelActor *)(obj))->motionState & 3) {
                goto identity;
            }
            if (((LevelActor *)(obj))->flags & 0x300000) {
                if (Region_TestPolygonSlopeFlag(((LevelActor *)(obj))->model) != 0) {
                    goto identity;
                }
                Region_GetNodeNormal(&normal, ((LevelActor *)(obj))->model);
                up.x = 0.0f;
                up.y = 1.0f;
                up.z = 0.0f;
                Graphu64_CrossVectors(&axis, &up, &normal);
                Graphu64_NormalizeVec3(&axis);
                slope = Graphu64_ArcCos(up.x * normal.x + up.y * normal.y + up.z * normal.z);
                g_turretAimSine = Gu_Sinf(RW_MIN(slope, 0.43633235f) * 0.375f);
                tilt.x = axis.x * g_turretAimSine;
                tilt.y = axis.y * g_turretAimSine;
                tilt.z = axis.z * g_turretAimSine;
                tilt.w = Math_Cosf(RW_MIN(slope, 0.43633235f) * 0.375f);
                tilt = Gobjinst_BuildActorDirectionTilt(obj);
                sine = Gu_Sinf(((LevelActor *)(self))->yaw);
                cosine = Math_Cosf(((LevelActor *)(self))->yaw);
                probe.dir = ((LevelActor *)(self))->floorDirection;
                probe.start.x = ((LevelActor *)(self))->position0.x;
                probe.start.y = ((LevelActor *)(self))->floorHeight;
                probe.start.z = ((LevelActor *)(self))->position0.z;
                slope = CPlane_GetSlopeAngle(&probe, ((LevelActor *)(obj))->position0.x, ((LevelActor *)(obj))->position0.z, ((LevelActor *)(obj))->position0.x - sine,
                    ((LevelActor *)(obj))->position0.z - cosine);
                slope = RW_MIN(slope, 25.0f) * 0.75f;
                half = 0.5f;
                angle = slope * half;
                g_turretAimSine = Gu_Sinf(angle);
                lean.y = 0.0f;
                lean.x = cosine * g_turretAimSine;
                lean.z = -sine * g_turretAimSine;
                lean.w = Math_Cosf(angle);
                Graphu64_InterpolateQuaternionWithLinearFallback(&result, half, &lean, &tilt);
                return result;
            }
        }
        return Gobjinst_BuildActorDirectionTilt(obj);
    }
    identity:
    tilt.x = tilt.y = tilt.z = 0.0f;
    tilt.w = 1.0f;
    return tilt;
}

void Insthdr_PlayActorGraphSound(void *actor, CVector3 pos, s32 sound, f32 volume) {
    CVector3 up;
    CVector3 dir;
    CVector3 velocity;
    CVector3 at;
    SoundRequest request;
    CVector3 *emitter;

    emitter = Portal_GetGraphPoint(&g_navigationGraph, Portal_FindNearestPointIndex(&g_navigationGraph, &pos));
    request.position = pos;
    at = request.position;
    request.owner = ((struct LevelActor *)actor)->model;
    if (emitter != 0) {
        at = *emitter;
    }
    up.x = 0.0f;
    up.y = g_actorAimBasisConstants[1];
    up.z = 0.0f;
    dir.x = dir.y = dir.z = up.x;
    Graphu64_NormalizeVec3(&dir);
    if (sound != 3031) {
        Graphu64_ScaleVector(&velocity, &dir, 409.59998f);
    }
    SetN64_SpawnModelEffect((intptr_t)&g_modelEffectPool, 0, sound, velocity, at, request.owner, volume);
}

/** Reset three byte-sized fields. */
void Insthdr_ResetInstanceRenderIndices(signed char *prop) {
    prop[3] = -1;
    prop[1] = 0;
    prop[2] = 0;
}

s32 Insthdr_GetSharedModelFlag20(void *actorStorage)
{
    struct EffectOwnerObject *object = actorStorage;
    struct Model *model;
    s32 kind;

    model = (struct Model *)object->owner;
    kind = model->kind;
    if ((kind == 1) || (kind == 4)) {
        do { return model->flags & 0x20; } while (0);
    }
    return 0;
}

s32 Insthdr_GetSharedModelFlag40(void *actorStorage)
{
    struct EffectOwnerObject *object = actorStorage;
    struct Model *model;
    s32 kind;

    model = (struct Model *)object->owner;
    kind = model->kind;
    if ((kind == 1) || (kind == 4)) {
        if (model) {
            return model->flags & 0x40;
        } else {
            return model->flags & 0x40;
        }
    }
    return 0;
}

int Insthdr_GetModelPropertyFlag1(void *other) {
    Actor_u1 *actor = other;
    Resource_u1 *resource = actor->resource;
    unsigned int defaultResult = 0;
    if (resource->kind != 1) {
        return defaultResult;
    }
    if (defaultResult) {
        return resource->flags14 & 1;
    } else {
        return resource->flags14 & 1;
    }
}

int Insthdr_GetModelPropertyFlag2(void *actorStorage) {
    Actor_u1 *actor = actorStorage;
    Resource_u1 *resource = actor->resource;
    unsigned int defaultResult = 0;
    if (resource->kind != 1) {
        return defaultResult;
    }
    if (defaultResult) {
        return resource->flags14 & 2;
    } else {
        return resource->flags14 & 2;
    }
}

s32 Insthdr_GetSharedModelFlag80(void *actorStorage)
{
    struct EffectOwnerObject *object = actorStorage;
    struct Model *model;
    s32 kind;

    model = (struct Model *)object->owner;
    kind = model->kind;
    if ((kind == 1) || (kind == 4)) {
        if (model) {
            return model->flags & 0x80;
        } else {
            return model->flags & 0x80;
        }
    }
    return 0;
}

s32 Insthdr_GetSharedModelFlag100(void *actorStorage)
{
    struct EffectOwnerObject *object = actorStorage;
    struct Model *model;
    s32 kind;

    model = (struct Model *)object->owner;
    kind = model->kind;
    if ((kind == 1) || (kind == 4)) {
        do { return model->flags & 0x100; } while (0);
    }
    return 0;
}

int Insthdr_GetModelPropertyFlag200(void *actorStorage) {
    Actor_u1 *actor = actorStorage;
    Resource_u1 *resource = actor->resource;
    unsigned int defaultResult = 0;
    if (resource->kind != 1) {
        return defaultResult;
    }
    if (defaultResult) {
        return resource->flags14 & 0x200;
    } else {
        return resource->flags14 & 0x200;
    }
}

s32 Insthdr_HasActorTerritory(void *actorStorage)
{
    struct EffectOwnerObject *object = actorStorage;
    struct Model *model;
    s32 kind;

    model = (struct Model *)object->owner;
    kind = model->kind;
    if ((kind == 1) || (kind == 4)) {
        if (model) {
            return model->flags & 0x10;
        } else {
            return model->flags & 0x10;
        }
    }
    return 0;
}

s32 Insthdr_IsKindElevenEnabledForLocalMode(void *actorStorage) {
    void *actorDefinition;
    actorDefinition = (((struct LevelActor *) ((s8 *) actorStorage))->definition);
    if ((((struct ActorDefinitionHeader *) ((s8 *) actorDefinition))->kind) == 11) {
        if (g_gameSettings.local != 0) {
            return (((struct ActorDefinitionHeader *) ((s8 *) actorDefinition))->flags) & 1;
        }
        return 1;
    }
    return 0;
}

int Insthdr_GetModelCollisionFlag1(void *actorStorage) {
    Actor_u1 *actor = actorStorage;
    Resource_u1 *resource = actor->resource;
    unsigned int defaultResult = 0;
    if (resource->kind != 1) {
        return defaultResult;
    }
    if (defaultResult) {
        return resource->flags4C & 1;
    } else {
        return resource->flags4C & 1;
    }
}

s32 Insthdr_IsInactiveOrCollisionOption2(LevelActor *actor) {
    void *definition = actor->definition;
    s32 actorKind = ((ModelBlend *)definition)->kind;

    if (actorKind != 1) {
        if (actorKind != 11) {
            goto ret0;
        }
        return 1;
    }
    {
        s32 result = 0;
        if (actor->active <= 0 || (((ModelBlend *)definition)->collisionOptions & 2)) {
            result = 1;
        }
        return result;
    }
    ret0:
    return 0;
}

s32 Insthdr_IsInactiveOrCollisionOption4(void *actor) {
    ModelBlend *modelBlend;
    s32 result;

    modelBlend = ((LevelActor *)actor)->definition;
    if (modelBlend->kind == 1) {
        result = 0;
        if (((LevelActor *)actor)->active <= 0 || (modelBlend->collisionOptions & 4)) {
            result = 1;
        }
        return result;
    }
    return 0;
}

int Insthdr_GetModelCollisionFlag8(void *actorStorage) {
    Actor_u1 *actor = actorStorage;
    Resource_u1 *resource = actor->resource;
    unsigned int defaultResult = 0;
    if (resource->kind != 1) {
        return defaultResult;
    }
    if (defaultResult) {
        return resource->flags4C & 8;
    } else {
        return resource->flags4C & 8;
    }
}

s32 Insthdr_IsInactiveOrCollisionOption800(LevelActor *actor) {
    ModelBlend *definition;
    s32 result;

    definition = actor->definition;
    if (definition->kind == 1) {
        result = 0;
        if (actor->active <= 0 || (definition->collisionOptions & 0x800)) {
            result = 1;
        }
        return result;
    }
    return 0;
}

s32 Insthdr_GetModelCollisionFlag1000(void *actorStorage)
{
    Actor_u1 *actor = actorStorage;
    unsigned int defaultResult;
    Resource_u1 *actorDefinition;
    actorDefinition = actor->resource;
    defaultResult = 0;
    if ((actorDefinition->kind) != 1)
    {
        return defaultResult;
    }
    if (defaultResult)
    {
        return (actorDefinition->flags4C) & 0x1000;
    }
    else
    {
        return (actorDefinition->flags4C) & 0x1000;
    }
}

s32 Insthdr_IsInactiveOrCollisionOption10(LevelActor *actor) {
    ModelBlend *definition;
    s32 result;

    definition = actor->definition;
    if (definition->kind == 1) {
        result = 0;
        if (actor->active <= 0 || (definition->collisionOptions & 0x10)) {
            result = 1;
        }
        return result;
    }
    return 0;
}

int Insthdr_GetModelCollisionFlag20(void *actorStorage) {
    Actor_u1 *actor = actorStorage;
    Resource_u1 *resource = actor->resource;
    unsigned int defaultResult = 0;
    if (resource->kind != 1) {
        return defaultResult;
    }
    if (defaultResult) {
        return resource->flags4C & 0x20;
    } else {
        return resource->flags4C & 0x20;
    }
}

s32 Insthdr_GetModelCollisionFlag200(void *actorStorage)
{
    Actor_u1 *actor = actorStorage;
    Resource_u1 *actorDefinition;
    int typeOne;
    actorDefinition = actor->resource;
    typeOne = 1;
    if ((actorDefinition->kind) != typeOne)
    {
        return 0;
    }
    if (typeOne)
    {
        return (actorDefinition->flags4C) & 0x200;
    }
}

int Insthdr_GetModelCollisionFlag400(void *actorStorage) {
    Actor_u1 *actor = actorStorage;
    Resource_u1 *resource = actor->resource;
    unsigned int defaultResult = 0;
    if (resource->kind != 1) {
        return defaultResult;
    }
    if (defaultResult) {
        return resource->flags4C & 0x400;
    } else {
        return resource->flags4C & 0x400;
    }
}

s32 Insthdr_GetModelCollisionFlag2000(void *actorStorage)
{
    Actor_u1 *actor = actorStorage;
    Resource_u1 *modelDefinition;
    int propertyByteOffset;
    Resource_u1 *actorDefinition;
    actorDefinition = actor->resource;
    modelDefinition = actorDefinition;
    if ((modelDefinition->kind) != 1)
    {
        if (actorDefinition || propertyByteOffset)
        {
            return 0;
        }
        else
        {
            return 0;
        }
    }
    propertyByteOffset = 76;
    return (actorDefinition->flags4C) & 0x2000;
}

int Insthdr_GetModelCollisionFlag4000(void *actorStorage) {
    Actor_u1 *actor = actorStorage;
    Resource_u1 *resource = actor->resource;
    unsigned int defaultResult = 0;
    if (resource->kind != 1) {
        return defaultResult;
    }
    if (defaultResult) {
        return resource->flags4C & 0x4000;
    } else {
        return resource->flags4C & 0x4000;
    }
}

/* INSTHDR_GETACTORSHADOWRADIUS.CPP */

/** Return the vertical offset selected by the actor's current state. */
f32 InstHdr_GetActorShadowRadius(Actor_u1 *actor) {
    Resource_u1 *state;

    {
        s32 state_value = actor->resource->kind;
        s32 sw_state_value = state_value - 1;
        if ((unsigned int)sw_state_value > 10) {
            goto sw_state_default;
        }
        switch (sw_state_value) {
        case 0: goto sw_state_1;
        case 1: goto sw_state_2;
        case 2: goto sw_state_default;
        case 3: goto sw_state_default;
        case 4: goto sw_state_5;
        case 5: goto sw_state_default;
        case 6: goto sw_state_default;
        case 7: goto sw_state_8;
        case 8: goto sw_state_default;
        case 9: goto sw_state_default;
        case 10: goto sw_state_11;
        }
    }
    do {
        sw_state_11:
        return actor->resource->valueEC;
        sw_state_1:
        return actor->resource->value2C;
        sw_state_2:
        state = actor->resource;
        if (((CollisionShapeResource *)state)->mode == 0) {
            return g_inactiveCollisionShapeShadowRadius;
        }
        return ((CollisionShapeResource *)state)->height;
        sw_state_5:
        return actor->resource->radius;
        sw_state_8:
        state = actor->resource;
        if ((state->flags14 & 1) != 0) {
            return g_hiddenStaticObjectShadowRadius;
        }
        return state->radius;
        sw_state_default:
        return g_defaultActorShadowRadius;

    } while (0);
}

f32 InstHdr_GetInactiveActorHeight(Actor_u1 *actor) {
    Resource_u1 *resource = actor->resource;
    s32 kind = resource->kind;

    switch (kind) {
    case 11:
        return resource->valueF8;
    case 4:
    case 1:
        return resource->value34;
    default:
        return 0.0f;
    }
}

f32 InstHdr_GetActorBaseOffset(void *actorStorage) {
    Resource_u1 *nested;
    if (((LevelActor *)actorStorage)->kind == 1) {
        return ((LevelActor *)actorStorage)->eyeHeight;
    }
    nested = ((Actor_u1 *)actorStorage)->resource;
    if (nested->kind == 0) {
        return nested->value20;
    }
    return 0.0f;
}

typedef struct MeasureObject MeasureObject;
typedef struct MeasureDefinition {
    s32 kind;
    char pad4[0x14];
    f32 value18;
    char pad1C[0x10];
    f32 value2C;
    char pad30[0xC0];
    f32 valueF0;
} MeasureDefinition;
typedef struct MeasureResource {
    char pad0[0x14];
    u16 packedValue;
} MeasureResource;
typedef struct MeasureModel {
    char pad0[0x30];
    MeasureResource *resource;
} MeasureModel;
typedef struct MeasureOwner {
    char pad0[0x80C];
    MeasureObject *redirect;
} MeasureOwner;
struct MeasureObject {
    u8 kind;
    char pad1[0x17];
    MeasureDefinition *definition;
    char pad1C[0xE4];
    u32 flags;
    char pad104[0x14];
    MeasureModel *model;
    char pad11C[0xBC];
    MeasureOwner *owner;
};

f32 InstHdr_GetActorReach(MeasureObject *object) {
    MeasureDefinition *definition;
    top:
    definition = object->definition;
    switch (definition->kind) {
    case 11:
        if (object->kind == 1 && (object->flags & 0x300000) != 0 &&
            object->owner->redirect != 0) {
            object = object->owner->redirect;
            goto top;
        }
        return object->definition->valueF0;
    case 4:
    case 1:
        return definition->value2C;
    case 5:
        return definition->value18;
    default:
        if (object->kind == 2) {
            return Menu_ExpandFloatHighWord(object->model->resource->packedValue);
        }
        return 0.0f;
    }
}



/** Return a nested float field when the nested record type is one, else zero. */
float InstHdr_GetTypeOneResourceValue50(void *object) {
    Actor_u1 *actor = object;
    Resource_u1 *nested = actor->resource;
    if (nested->kind == 1) {
        return nested->value50;
    }
    return 0.0f;
}

/** Return a nested float field when the nested record type is one, else zero. */
float InstHdr_GetActorTerritoryRadius(void *object) {
    Actor_u1 *actor = object;
    Resource_u1 *nested = actor->resource;
    if (nested->kind == 1) {
        return nested->value3C;
    }
    return 0.0f;
}

void InstHdr_ProjectPositionToActorGround(void *actor, void *position, void *positionOut) {
    CVector3 *source = position;
    CVector3 *output = positionOut;
    ActorSurfaceSampleVector t;
    s32 groundNode;

    t.a = source->x;
    t.b = 0;
    t.c = source->z;
    InstHdr_CopyActorPositionAndModel(actor, *(CVector3 *)&t, positionOut, &groundNode, 0, 0);
    output->y = Region_GetPolygonHeight((struct Node75 *)groundNode, output->x, output->z);
}

/** Return the item value when the item kind is 1, else 0. */
int InstHdr_GetTypeOneItemValue(void *actorStorage) {
    struct InstanceItemValueView *item = actorStorage;
    if (item->kind == 1) {
        return (int)item->value;
    }
    return 0;
}

/** Return the low three mode bits when the record type is one. */
int InstHdr_GetActorMotionState(void *levelActor) {
    LevelActor *actor = levelActor;
    if (actor->kind == 1) {
        return actor->motionState & 7;
    }
    return 0;
}

f32 InstHdr_GetActorGroundHeight(Shared_CollisionActor *actor, s32 unusedFlag)
{
    if ((actor->type) != 1)
    {
        if (actor)
        {
            return actor->y;
        }
        else
        {
            return actor->y;
        }
    }
    return actor->groundY;
}

/** Select one of two float fields according to the leading byte. */
float InstHdr_GetShadowGroundHeight(Shared_CollisionActor *object, s32 mode) {
    if (object->type != 1) {
        return object->y;
    }
    return object->groundY;
}

void *InstHdr_GetEnabledItemValue(struct InstanceItemValueView *item) {
    if (item->kind == 1 && item->value != 0 && (item->flags & 3) != 0) {
        return item->value;
    }
    return 0;
}

/* Barrel_ComputeTargetOffset writes this 0x3c-byte result. */
struct ActorTargetOffsetResult {
    CVector3 first, firstNormalized;
    f32 firstLength;
    CVector3 flat, flatNormalized;
    f32 flatLength, height;
};

void InstHdr_GetActorTargetOffset(u8 *player, void *vector) {
    struct ActorTargetOffsetResult offset;

    if (*player == 1) {
        Barrel_ComputeTargetOffset(player, (char *)&((LevelActor *)player)->behaviorFlags, (struct CAIMovementInfo *)&offset);
        *(CVector3 *)vector = offset.first;
        return;
    }
    *(s32 *)vector = 0;
    ((Triple *)vector)->y = 0;
    ((Triple *)vector)->z = 0;
}

f32 InstHdr_GetActorTargetHeight(u8 *player) {
    struct ActorTargetOffsetResult offset;
    if (*player == 1) {
        Barrel_ComputeTargetOffset(player, (char *)&((LevelActor *)player)->behaviorFlags, (struct CAIMovementInfo *)&offset);
        return offset.height;
    }
    return 0.0f;
}

/** Return the low three mode bits when the record type is one. */
int InstHdr_GetActorMotionFlags(void *levelActor) {
    LevelActor *actor = levelActor;
    if (actor->kind == 1) {
        return actor->motionState & 7;
    }
    return 0;
}

/* Returns the float of the entry Scene_GetModelRecordByIndexPointer finds in g_world_AchieveUpdateresultsscreen for an object's
   key at 0x14, when the key's flag halfword at 2 has bit 0 set; zero otherwise. */

void InstHdr_CopyActorPositionAndModel(struct LevelActor *levelActor, CVector3 t, CVector3 *positionOut, s32 *modelOut, s32 positionMode, s32 modelMode) {
    char frameScratch[0x150];
    CVector3 *output = positionOut;
    *output = t;
    *modelOut = ((LevelActor *)levelActor)->model;
}

int InstHdr_FindActorModelEntry(void *actorStorage) {
    int actorModel = ((LevelActor *)actorStorage)->model;
    int result = 0;
    if (actorModel != 0) {
        result = (int)Scene_GetModelRecordByIndexPointer(&g_world, (void *)actorModel);
    }
    return result;
}

f32 InstHdr_GetModelRecordValue20(struct ActorSurfaceKeyView *object) {
    struct PlayerMovementScalarView *entry;

    if (object->key != 0 && (object->key->flags & 1)) {
        entry = Scene_GetModelRecordByIndexPointer(&g_world, object->key);
        if (entry != 0) {
            return entry->scalar;
        }
    }
    return 0.0f;
}

/** Return zero as the actor float value for callers that need no value. */
float InstHdr_ReturnUnusedActorFloat(void) {
    return 0.0f;
}

f32 InstHdr_GetActorTriangleTopOffset(void *actor) {
    f32 previousVertexHeight;
    f32 upperPairHeight;
    f32 highestVertexHeight;
    void *groundTriangle;
    groundTriangle = (((struct ActorSurfaceHeightView *) ((s8 *) actor))->groundTriangle);
    upperPairHeight = (((struct PaddedFloatView *) ((s8 *) ((struct Node75 *) ((s8 *) groundTriangle))->cur))->value);
    previousVertexHeight = (((struct PaddedFloatView *) ((s8 *) ((struct Node75 *) ((s8 *) groundTriangle))->prev))->value);
    if (!(previousVertexHeight <= upperPairHeight)) {
        upperPairHeight = previousVertexHeight;
    }
    highestVertexHeight = (((struct PaddedFloatView *) ((s8 *) ((struct Node75 *) ((s8 *) groundTriangle))->next))->value);
    if (!(upperPairHeight <= highestVertexHeight)) {
        highestVertexHeight = upperPairHeight;
    }
    return highestVertexHeight - (((struct ActorSurfaceHeightView *) ((s8 *) actor))->surfaceBaseHeight);
}

f32 InstHdr_GetActorTriangleBottomOffset(void *actor) {
    f32 previousVertexHeight;
    f32 lowerPairHeight;
    f32 lowestVertexHeight;
    void *groundTriangle;
    groundTriangle = (((struct ActorSurfaceHeightView *) ((s8 *) actor))->groundTriangle);
    lowerPairHeight = (((struct PaddedFloatView *) ((s8 *) ((struct Node75 *) ((s8 *) groundTriangle))->cur))->value);
    previousVertexHeight = (((struct PaddedFloatView *) ((s8 *) ((struct Node75 *) ((s8 *) groundTriangle))->prev))->value);
    if (!(lowerPairHeight <= previousVertexHeight)) {
        lowerPairHeight = previousVertexHeight;
    }
    lowestVertexHeight = (((struct PaddedFloatView *) ((s8 *) ((struct Node75 *) ((s8 *) groundTriangle))->next))->value);
    if (!(lowestVertexHeight <= lowerPairHeight)) {
        lowestVertexHeight = lowerPairHeight;
    }
    return (((struct ActorSurfaceHeightView *) ((s8 *) actor))->surfaceBaseHeight) - lowestVertexHeight;
}

s32 InstHdr_HasTypeOneFlagOne(void *actorStorage)
{
    LevelActor *actor = actorStorage;
    int constantTrue;
    constantTrue = 1;
    if ((actor->kind) != 1)
    {
        if (constantTrue)
        {
            return 0;
        }
    }
    return (actor->flags) & 1;
}

int InstHdr_GetActorType(void *prop) {
    if (((LevelActor *)prop)->kind == 1) {
        return ((LevelActor *)prop)->type;
    }
    return Scene_GetModelIdAtIndex(&g_world, (u16)((LevelActor *)prop)->modelIndex);
}

/** Return the selected record field, or negative one for another type. */
int InstHdr_GetActorMotionIndex(void *record) {
    int result = -1;
    if (((LevelActor *)record)->kind == 1) {
        result = ((LevelActor *)record)->motionIndex;
    }
    return result;
}

/** Return the zero status that callers treat as no result. */
int InstHdr_ReturnUnusedActorStatus(void *owner) {
    return 0;
}

/** Return zero. */
int InstHdr_ReturnUnusedActorStatusAlternate(void) {
    return 0;
}

/** Return the empty (zero) result for callers that need no value. */
int InstHdr_ReturnUnusedActorQuery(void) {
    return 0;
}

/** Return whether this object is active for its current behavior class. */
s32 InstHdr_CanActorCastShadow(void *actor) {
    if (((LevelActor *)actor)->kind == 1) {
        if ((((LevelActor *)actor)->flags & 0x300000) != 0) {
            return 1;
        }
    }
    switch (((LevelActor *)actor)->definition->kind) {
    case 1:
    case 2:
    case 5:
    case 8:
    case 9:
        return 1;
    default:
        return 0;
    }
}

s32 InstHdr_HasEnabledMotionHooks(void *actor) {
    if (((LevelActor *)actor)->kind != 1) {
        return 0;
    }
    if (!(((LevelActor *)actor)->flags & 0x2000)) {
        return 0;
    }
    actor = ((ActorMotionState *)&((LevelActor *)actor)->behaviorFlags)->hooks;
    if (actor == 0) {
        goto ret1;
    }
    if (((ActorMotionHooks *)actor)->flags & 0x10000) {
        return 0;
    }
    ret1:
    return 1;
}

/* Reports whether an actor's current state counts as active: states 1 and 5 always do, and state 11 does for a live mirrored actor whose controller flag is set or for which Cinema_IsSequenceInWindow agrees. */

s32 InstHdr_IsActorControllerActive(char *actor)
{
    switch (((LevelActor *)actor)->definition->kind) {
    case 1:
    case 5:
        return 1;
    case 11:
        if (((LevelActor *)actor)->kind != 1) {
            return 0;
        }
        if (!(((LevelActor *)actor)->flags & 0x300000)) {
            return 0;
        }
        if (((Player *)((Shared_Actor *)actor)->entity)->controllerEnabled != 0 || Cinema_IsSequenceInWindow() != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

/** Return bit two of the nested state word. */
unsigned int InstHdr_UsesGroundRotation(char *object) {
    return (((struct NavigationTrack *)((LevelActor *)object)->definition)->flags >> 2) & 1;
}

/** Report whether the object pointed to equals one. */
int InstHdr_IsDefinitionKindOne(LevelActor *actor) {
    return actor->definition->kind == 1;
}

int InstHdr_UsesDefaultDefinitionHandling(LevelActor *source) {
    switch (source->definition->kind) {
    case 0: case 2: case 3: case 5: case 6: case 7: case 8: case 10: case 12: case 13: case 14:
    default:
        return 1;
    case 1: case 4: case 9: case 11:
        return 0;
    }
}

#if defined(VERSION_EU_X)
/* Zero word after the jump table; no instruction reads it. */

#endif

/* IS.CPP */



/* ACTOR_HEADER_DEFAULT_CONSTANTS_AND_FRAGMENTS.CPP */



#if defined(VERSION_US)
char s_ActorHeaderDefaultConstantsAndFragmentsAlTimeTText[8] =
    "alTimeT\000";
#endif

#if defined(VERSION_DE)
float k_ActorHeaderDefaultConstantsAndFragments[2] = {
    0.35f, 0.5f,
};
#endif

#if defined(VERSION_EU_X)
float k_ActorHeaderDefaultConstantsAndFragments[2] = {
    128.0f, 255.0f,
};
#endif

/* G_ACTORHEADERBYTERANGECONSTANTS.CPP */

#if defined(VERSION_US_REV1)
float g_actorHeaderByteRangeConstants[2] = {
    128.0f, 255.0f,
};
#endif

/* Retained data for this translation unit. */
#if defined(VERSION_EU_X)
const unsigned int k_instHdrUsesDefaultDefinitionHandlingZeroTail = 0x00000000;
#endif

const float g_Insthdr_PlayActorGraphSoundConstants[1] = {
    1.0f,
};

const float g_InstHdr_GetActorShadowRadiusConstantTail[3] = {
    256.0f, 81.92f, 61.44f,
};
