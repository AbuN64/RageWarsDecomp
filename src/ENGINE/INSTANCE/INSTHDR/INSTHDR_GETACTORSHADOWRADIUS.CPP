#include "include_asm.h"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/PROBE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "ENGINE/INSTANCE/INSTHDR.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LEGACY_COLLISION_ACTOR.H"
#include "COMMON/FIELD_VEC_B0.H"
#include "COMMON/VECTOR4F.H"
#include "SOUND/PLAYER_MOVEMENT_SCALAR_VIEW.H"
#include "COMMON/WORLD.H"
#include "INSTHDR/INSTHDR_GETACTORSHADOWRADIUS.H"
#include "COMMON/PROPGEOMETRY.H"
#include "COMMON/REC.H"
#include "COMMON/OBJ.H"

/* 8024E130_2.CPP */
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
    if (*(u8 *)actorStorage == 1) {
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

/* 8024E130_3.CPP */
void InstHdr_CopyActorPositionAndModel(void *actor, Triple t, void *positionOut, s32 *modelOut, s32 unusedPositionMode, s32 unusedModelMode);

extern f32 Region_GetPolygonHeight(struct Node75 *node, f32 x, f32 z);

extern void Barrel_ComputeTargetOffset(void *player, void *motionState, void *result);

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
    InstHdr_CopyActorPositionAndModel(actor, *(Triple *)&t, positionOut, &groundNode, 0, 0);
    output->y = Region_GetPolygonHeight((struct Node75 *)groundNode, output->x, output->z);
}

/** Return offset 0x34 only when the type byte at offset 0 is 1. */
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

f32 InstHdr_GetActorGroundHeight(Shared_CollisionActor *actor)
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

void InstHdr_GetActorTargetOffset(u8 *player, void *vector) {
    CAIMovementInfo offset;

    if (*player == 1) {
        Barrel_ComputeTargetOffset(player, (char *)&((Player *)player)->motion, &offset);
        *(CVector3 *)vector = offset.first;
        return;
    }
    *(s32 *)vector = 0;
    ((Triple *)vector)->y = 0;
    ((Triple *)vector)->z = 0;
}

f32 InstHdr_GetActorTargetHeight(u8 *player) {
    CAIMovementInfo offset;
    if (*player == 1) {
        Barrel_ComputeTargetOffset(player, (char *)&((Player *)player)->motion, &offset);
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

/* 8024E130_4.CPP */
extern struct PlayerMovementScalarView *Scene_GetModelRecordByIndexPointer(Shared_World *, void *);

/* Returns the float at offset 0x20 of the entry Scene_GetModelRecordByIndexPointer finds in g_world_AchieveUpdateresultsscreen for an object's
   key at 0x14, when the key's flag halfword at 2 has bit 0 set; zero otherwise. */

void InstHdr_CopyActorPositionAndModel(void *levelActor, Triple t, void *positionOut, s32 *modelOut, s32 unused6, s32 unused7) {
    char unused[0x150];
    Triple *output = positionOut;
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

/** Return floating-point zero to callers at VRAM 0x8024E854. */
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

/* 8024E914.CPP */
extern int Scene_GetModelIdAtIndex(void *world, int modelIndex);

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


/* 8024E130.CPP */
/** Return the zero status used by callers at VRAM 0x8024E130. */
int InstHdr_ReturnUnusedActorStatus(void) {
    return 0;
}

/** Return zero. */
int InstHdr_ReturnUnusedActorStatusAlternate(void) {
    return 0;
}

/** Return the empty result used by callers at VRAM 0x8024E140. */
int InstHdr_ReturnUnusedActorQuery(void) {
    return 0;
}

/** Return whether this object is active for its current behavior class. */
s32 InstHdr_CanActorCastShadow(void *actor) {
    if (*(u8 *)actor == 1) {
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
    if (*(u8 *)actor != 1) {
        return 0;
    }
    if (!(((LevelActor *)actor)->flags & 0x2000)) {
        return 0;
    }
    actor = ((ActorMotionState *)((Player *)actor)->motion)->hooks;
    if (actor == 0) {
        goto ret1;
    }
    if (((ActorMotionHooks *)actor)->flags & 0x10000) {
        return 0;
    }
ret1:
    return 1;
}

/* Reports whether an actor's current state counts as active: states 1 and 5 always do, and state 11 does for a live mirrored actor whose controller flag at 0x80C is set or for which Cinema_IsSequenceInWindow agrees. */

extern s32 Cinema_IsSequenceInWindow(char *actor);

s32 InstHdr_IsActorControllerActive(char *actor)
{
    switch (((LevelActor *)actor)->definition->kind) {
    case 1:
    case 5:
        return 1;
    case 11:
        if (*(u8 *)actor != 1) {
            return 0;
        }
        if (!(((LevelActor *)actor)->flags & 0x300000)) {
            return 0;
        }
        if (((Player *)((Shared_Actor *)actor)->entity)->controllerEnabled != 0 || Cinema_IsSequenceInWindow(actor) != 0) {
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

/** Report whether the object pointed to at offset 0x18 equals one. */
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
const unsigned int k_InstHdrUsesDefaultDefinitionHandlingJumpTablePad = 0x00000000;
#endif

/* 800C3D3C.CPP */
