#include "COMMON/VECTOR4F.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "ENGINE/INSTANCE/GOBJINST.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WORLD.H"
#include "TYPES.H"
#include "ENGINE/INSTANCE/GOBJINST_INITIALIZEPLACEDACTOR.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Finds the hit box of an object nearest a point: with the object's bone matrices (0xB4, else 0xB8) and its
 * hit-box resource from Gobjinst_RequestAnimatedModelVariant, each box whose mask matches the object's mask 0x17C has the average
 * of its eight corners carried through its bone matrix, and the box whose center lies nearest the point is
 * copied out, taking weight 1 for a controlled actor unless the global option g_motionVisibilitySettings is set. The
 * resource is released afterwards; returns whether a box was found. */








extern s32 *Gobjinst_RequestAnimatedModelVariant(char *, s8);



extern void Graphu64_AddVec3(CVector3 *, CVector3 *, CVector3 *);

extern void Graphu64_ScaleVector(CVector3 *, CVector3 *, f32);

extern void Graphu64_ConvertMatrixToFloat(f32 *, char *);


extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);


extern TypeEntry *g_actorTypeOperations[];

extern char *g_gamePlayerAndMenuState;


extern void *Scene_GetActorDefinition(void *, s32);

extern s32 Rumble_TestActorStateBit(void *, void *);

extern void Gobjinst_InitializeActor(void *, u16, u16, s32, void *, s32, s32, f32,
                          CVector3, u8, CVector3, CVector3, s32);

s32 Gobjinst_FindNearestBoneBounds(char *obj, CVector3 point, Box70 *out) {
    CVector3 center;
    CVector3 diff;
    f32 matrix[16];
    s32 *resource;
    s32 count;
    struct ActorAnimationEventTable *table;
    Box70 *box;
    Box70 *best;
    char *bones;
    s32 i;
    s32 j;
    f32 dist;
    f32 bestDist;

    bones = ((struct BoneBoundsActorView *) obj)->poseMatrices;
    if (bones == 0) {
        bones = ((struct BoneBoundsActorView *) obj)->previousPoseMatrices;
        if (bones == 0) {
            return 0;
        }
    }
    resource = Gobjinst_RequestAnimatedModelVariant(obj, ((struct BoneBoundsActorView *) obj)->team);
    if (resource == 0) {
        return 0;
    }
    table = SetN64_GetPackSection(*resource, 5);
    count = table->entryCount;
    bestDist = 3.4028235e38f;
    best = 0;
    for (i = 0; i < count; i++) {
        box = (Box70 *)((char *)table + (i * table->entrySize + 8));
        if (box->mask & ((struct BoneBoundsActorView *) obj)->boneMask) {
            center = box->corners[0];
            for (j = 1; j < 8; j++) {
                Graphu64_AddVec3(&center, &center, &box->corners[j]);
            }
            Graphu64_ScaleVector(&center, &center, 0.125f);
            Graphu64_ConvertMatrixToFloat(matrix, &((Matrix *)bones)[i]);
            Graphu64_TransformPoint(matrix, &center, &diff);
            Graphu64_SubtractVectors(&diff, &diff, &point);
            dist = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
            if (dist < bestDist) {
                best = box;
                bestDist = dist;
            }
        }
    }
    if (best != 0) {
        *out = *best;
        if ((((struct BoneBoundsActorView *) obj)->flags & 0x300000) && g_gameSettings.local == 0) {
            ((struct Shield *) ((char *) out))->factor = 1.0f;
        }
    }
    Cache_UnlockResource(0, resource);
    return best != 0;
}

void Gobjinst_DispatchActorTypeUpdate(char *actor)
{
    s32 type;
    s32 i;
    s32 count;
    s32 limit;
    char *object;
    TypeEntry *entry;

    type = ((struct LevelActor *)(actor))->definition->kind;
    if ((u32)type < 15) {
        goto valid_type;
    }
zero_entry:
    entry = 0;
    goto selected;
special_entry:
    entry = (TypeEntry *)g_actorDefinitionTable;
    goto selected;
valid_type:
    if (type == 11) {
        count = g_playerCount;
        i = 0;
        if (count > 0) {
            limit = count;
            object = g_gamePlayerAndMenuState;
            do {
                if (object == actor) {
                    goto zero_entry;
                }
                if ((char *)&((SharedPlayer *)object)->views1C.view2E8_27.weapon == actor) {
                    goto special_entry;
                }
                i++;
                object += sizeof(SharedPlayer);
            } while (i < limit);
        }
    }
    entry = g_actorTypeOperations[type];

selected:
    if (entry != 0 && entry->callback != 0) {
        entry->callback(actor, &((LevelActor *)actor)->behaviorFlags);
    }
    if ((((struct LevelActor *)(actor))->flags & 0x08000000) != 0) {
        (((struct LevelActor *)(actor))->updateCount)++;
    }
}

void Gobjinst_InitializePlacedActor(void *actorStorage, LevelPlacedActorRecord *placement, s32 mode, s32 index) {
    void *resource0;
    s32 resource1;
    s32 lookup;
    s32 amountRaw;
    f32 fzero;
    f32 amount;
    CVector3 zero;

    resource0 = Scene_GetActorDefinition(&g_world, placement->resource22);
    if (placement->resource20 == 0xFFFF) {
        resource1 = 0;
    } else {
        resource1 = Scene_GetModelSectionTwoRecord(&g_world, placement->resource20);
    }
    amountRaw = placement->amount24;
    fzero = 0.0f;
    amount = amountRaw * g_actorOffsetTransformConstants[1];
    zero.x = zero.y = zero.z = fzero;
    lookup = Rumble_TestActorStateBit(&g_world, actorStorage);
    Gobjinst_InitializeActor(actorStorage, placement->actorKind, placement->actorVariant, placement->actorId,
                  resource0, placement->ownerIndex == 0xFF ? -1 : placement->ownerIndex,
                  resource1, amount, *(CVector3 *)placement->vec4, placement->spawnFlags,
                  *(CVector3 *)placement->vec10, zero, lookup);
}

void Gobjinst_UpdateModelBounds(void *actorStorage, int model) {
    Actor36 *actor = actorStorage;
    ActorBoneBoundsCallback fn = actor->update;
    fn(actorStorage, actor->state);
    Graphu64_TransformBoundingBox(actor->matrix, model, &actor->box);
}
