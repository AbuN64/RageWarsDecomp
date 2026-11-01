#include "include_asm.h"
#include "COMMON/TRIPLE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/WORLDRECAT1B6A4.H"
#include "TYPES.H"
#include "COMMON/TRIGGER_AND_FLOAT_VALUE_OPERATIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/SCENERECAT10C0.H"
#include "COMMON/OBJB.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "ENGINE/SCENE_SAMPLEWORLDLIGHTING.H"
#include "COMMON/GAMEPLAY_REACTIONS.H"

extern void Link_DispatchTriggerExit(RecGobjinstSampleBoneTranslation *trigger);








void Scene_DispatchSecondaryTriggersOfKind(void *world, s32 triggerKind) {
    RecGobjinstSampleBoneTranslation *trigger;
    RecGobjinstSampleBoneTranslation *edgeTrigger;
    s32 remainingFaces;
    s32 remainingEdges;

    remainingFaces = ((SceneVisibilityGeometryView *)(world))->nfaces;
    trigger = ((SceneVisibilityGeometryView *)(world))->faces;
    remainingFaces -= 1;
    if (remainingFaces != -1) {
        do {
            if (((Record14 *)(trigger))->kind == triggerKind) {
                Link_DispatchTriggerExit(trigger);
            }
            remainingFaces -= 1;
            trigger += 1;
        } while (remainingFaces != -1);
    }

    remainingEdges = ((SceneVisibilityGeometryView *)(world))->nedges;
    edgeTrigger = ((SceneVisibilityGeometryView *)(world))->edges;
    remainingEdges -= 1;
    if (remainingEdges != -1) {
        do {
            if (((Record14 *)(edgeTrigger))->kind == triggerKind) {
                Link_DispatchTriggerExit(edgeTrigger);
            }
            remainingEdges -= 1;
            edgeTrigger += 1;
        } while (remainingEdges != -1);
    }
}

s32 Scene_QueueTriggerTimer(SceneVisibilityGeometryView *world, Record14 *trigger) {
    void *rec;
    f32 val;
    s32 flag;

    rec = world->listB.head;
    if (rec != 0) {
        List_RemoveIntrusive(&world->listB, rec);
        List_PrependIntrusive(&world->listA, rec);
        ((CActiveLink *)(rec))->object = trigger;
    } else {
        rec = world->listA.tail;
        Link_DispatchTrigger(((CActiveLink *)(rec))->object);
        ((CActiveLink *)(rec))->object = trigger;
    }
    val = recordValue((s32) trigger->lifetime);
    ((CActiveLink *)(rec))->remaining = val;
    flag = trigger->flags & 2;
    if (flag != 0) {
        ((CActiveLink *)(rec))->remaining = val * g_triggerTimerFrameScale;
    }
    return flag;
}










void Scene_UpdateTriggerTimers(void *world) {
    void *node;
    void *next;
    void *object;
    s32 remove;
    s32 expired;
    f32 zero;
    f32 value;

    node = ((SceneVisibilityGeometryView *)(world))->listA.head;
    remove = 0;
    if (node != 0) {
        zero = 0.0f;
        do {
            object = ((CActiveLink *)(node))->object;
            next = ((CActiveLink *)(node))->next;
            expired = remove;
            if (((Record14 *)(object))->flags & 2) {
                value = ((CActiveLink *)(node))->remaining - g_frameElapsedTime;
                ((CActiveLink *)(node))->remaining = value;
                if (value <= zero) {
                    expired = 1;
                    remove = 1;
                }
            }
            if (expired != 0) {
                Link_DispatchTrigger(object);
            }
            if (remove != 0) {
                List_RemoveIntrusive(&((SceneVisibilityGeometryView *)(world))->listA, node);
                List_PrependIntrusive(&((SceneVisibilityGeometryView *)(world))->listB, node);
            }
            node = next;
            remove = 0;
        } while (node != 0);
    }
}

/* Lights a point: blends the light volumes around it when the world's sectors hold any and lighting is on (g_vertexLightingMode), else copies the default lights g_playerModelLighting. */












extern void Scene_FindLightVolumes(Shared_World *world, CVector3 *point, SceneLightVolume **volumes, s32 *total);
static inline s32 worldHasLightVolumes(Shared_World *world) {
    s32 i;
    for (i = 0; i < world->sectorCount; i++) {
        if (((LightVolumeList *)SetN64_GetPackSection(world->sectors[i].resource->pack, 2))->count != 0) {
            return 1;
        }
    }
    return 0;
}
void Scene_SampleWorldLighting(Shared_World *world, CVector3 *position, Shared_ParticleLighting *out) {
    SceneLightVolume *volumes[10];
    s32 count;
    if (!worldHasLightVolumes(world) || g_vertexLightingMode == 0) {
        *out = g_playerModelLighting[0];
    } else {
        Scene_FindLightVolumes(world, position, volumes, &count);
        Scene_SampleVolumeLighting(volumes, count, position, out);
    }
}

/* Searches the counted pointer list at offset 0x1B664 of a world record for the first entry whose definition id at 0x18->0xC equals the given id, returning it or null. Adapted from Scene_FindSwitchByDefinitionId with the list offset changed to 0x1B664. */







SceneDefinitionActorView *Scene_FindTypeFourteenActorByDefinitionId(SceneTypeFourteenActorListView *world, s32 id) {
    s32 i;
    SceneDefinitionActorView *found = 0;

    for (i = 0; i < world->count; i++) {
        if (world->list[i]->def->input == id) {
            found = world->list[i];
            break;
        }
    }
    return found;
}

/* Returns the object in the world's object list nearest to the current player actor, comparing whole-unit distances and starting from a bound of 9999999. */







extern Player *Playerai_GetFirstPlayer(void *list);
#ifdef VERSION_EU
#endif

Player *Scene_FindNearestObjectToFirstPlayer(ScenePlayerObjectListView *world) {
    CVector3 delta;
    Player *player;
    Player *object;
    Player *nearest;
    s32 best;
    s32 distance;
    s32 i;

#ifdef VERSION_EU
    player = Playerai_GetFirstPlayer(&g_playerViewRenderContext);
#else
    player = Playerai_GetFirstPlayer(&g_playerViewRenderContext);
#endif
    best = 9999999;
    nearest = 0;
    for (i = 0; i < world->count; i++) {
        object = world->objects[i];
        Graphu64_SubtractVectors(&delta, &object->pos, &player->pos);
        distance = Gu_Sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        if (distance <= best) {
            nearest = object;
            best = distance;
        }
    }
    return nearest;
}

/* Registers an object with a world after preparing it with Gobjinst_RotatePoseMatrixBuffers: adds it to the lists of objects accepted by InstHdr_CanActorReceiveInteraction and InstHdr_HasEnabledMotionHooks, to the list of all objects, to the type 1 list (storing its slot in the object), to the list of objects flagged 2, to the type 5 list, and to the lists of model 0x64F and model 0x64D objects, each while that list has room. */







extern void Gobjinst_RotatePoseMatrixBuffers(void *actorRenderState);
extern s32 InstHdr_CanActorReceiveInteraction(ObjectSceneRegisterActorInSceneLists *object);
extern s32 InstHdr_HasEnabledMotionHooks(ObjectSceneRegisterActorInSceneLists *object);

void Scene_RegisterActorInSceneLists(SceneActorCategoryListsView *world, ObjectSceneRegisterActorInSceneLists *object) {
    Gobjinst_RotatePoseMatrixBuffers(object);
    if (InstHdr_CanActorReceiveInteraction(object) != 0) {
        s32 n = world->countA;
        if (n != 512) {
            world->listA[n] = object;
            world->countA = n + 1;
        }
    }
    if (InstHdr_HasEnabledMotionHooks(object) != 0) {
        s32 n = world->countB;
        if (n != 128) {
            world->listB[n] = object;
            world->countB = n + 1;
        }
    }
    {
        s32 n = world->countAll;
        if (n < 128) {
            world->all[n] = object;
            world->countAll = n + 1;
        }
    }
    {
        s32 n = world->countType1;
        if (n < 64 && object->descriptor->value == 1) {
            world->type1[n] = object;
            object->slot = world->countType1++;
        }
    }
    {
        s32 n = world->countFlagged;
        if (n < 32 && (object->flags & 2)) {
            world->flagged[n] = object;
            world->countFlagged = n + 1;
        }
    }
    {
        s32 n = world->countType5;
        if (n < 16 && object->descriptor->value == 5) {
            world->type5[n] = object;
            world->countType5 = n + 1;
        }
    }
    {
        s32 n = world->count64F;
        if (n < 32 && object->model == 1615) {
            world->model64F[n] = object;
            world->count64F = n + 1;
        }
    }
    if (object->model == 1613) {
        s32 n = world->count64D;
        if (n < 4) {
            world->model64D[n] = object;
            world->count64D = n + 1;
        }
    }
}

/* Returns the nearest other object matching the optional team, kind and active filters, by squared distance. */
SceneNearestActorView *Scene_FindNearestMatchingActor(WorldSceneFindNearestMatchingActor *world, SceneNearestActorView *self, s32 team, s32 kind, s32 activeOnly) {
    s32 i;
    SceneNearestActorView *obj;
    SceneNearestActorView *best;
    f32 min;
    f32 dx, dy, dz, distSq;

    s32 count;

    i = 0;
    min = 3.4028235e38f;
    count = world->count;
    best = 0;
    for (; i < count; i++) {
        obj = &world->objects[i];
        if (obj == self) {
            continue;
        }
        if (team != -1 && obj->team != team) {
            continue;
        }
        if (kind != -1 && *obj->kind != kind) {
            continue;
        }
        if (activeOnly && obj->active == 0) {
            continue;
        }
        dx = self->x - obj->x;
        dy = self->y - obj->y;
        dz = self->z - obj->z;
        distSq = dx * dx + dy * dy + dz * dz;
        if (distSq < min) {
            min = distSq;
            best = obj;
        }
    }
    return best;
}

/* Returns the entry in an object's pointer list at 0x1024, counted at 0x10A4, whose position lies nearest a given position, or null when none lies closer than g_transitionAlphaScaleTable. Adapted from Playerai_FindNearestPlayer with the linked list walk replaced by a do-while loop, guarded by the zero index against the count, over a counted array of entry pointers read before the guard, the position read from a record at offset 8, and the differences taken from the position. */





struct ScenePositionEntry *Scene_FindNearestListedEntry(struct SceneListedEntryOwnerView *owner, struct ScenePositionEntry *pos) {
    s32 i;
    struct ScenePositionEntry *best;
    f32 min;
    struct ScenePositionEntry **entries;
    f32 dx, dy, dz, distSq;
    struct ScenePositionEntry *e;
    s32 n;
    struct ScenePositionEntry **p;

    i = 0;
    best = 0;
    min = (3.4028234663852886e+38f);
    n = owner->count;
    entries = owner->entries;
    if (i < n) {
        p = entries;
        do {
            e = *p;
            dx = pos->x - e->x;
            dx = dx * dx;
            dy = pos->y - e->y;
            dy = dy * dy;
            dz = pos->z - e->z;
            dz = dz * dz;
            distSq = (dx + dy) + dz;
            if (distSq < min) {
                min = distSq;
                best = e;
            }
            i++;
            p++;
        } while (i < n);
    }
    return best;
}

/* Finds the first of the object's listed actors (count at 0xE50, pointers from 0xC50) linked to an id
   at 0x1D8, clears that actor's link and relinks every other actor with that id to it; returns the
   actor, or 0. */




ActorLinkedControllerView *Scene_ResolveActorLinkGroup(SceneActorLinkGroupView *obj, int id) {
    int i;
    ActorLinkedControllerView *found;
    int count;
    ActorLinkedControllerView **list;

    i = 0;
    found = 0;
    count = obj->count;
    list = obj->actors;
    for (; i < count; i++) {
        if (list[i]->link == id) {
            found = list[i];
            found->link = 0;
            break;
        }
    }
    for (i = 0; i < count; i++) {
        if (list[i]->link == id) {
            list[i]->link = (int)found;
        }
    }
    return found;
}

void Scene_ClearActorLinksById(void *scene, s32 linkId) {
    s32 count;
    s32 i;
    void **arr;
    void *entry;

    i = 0;
    count = ((SceneActorUpdateLists *)((scene)))->count;
    arr = &((SceneActorUpdateLists *)((scene)))->objects[0];
    if (count > 0) {
        do {
            entry = *arr;
            if (((ActorLinkedControllerView *)((entry)))->link == linkId) {
                ((ActorLinkedControllerView *)((entry)))->link = 0;
            }
            i += 1;
            arr += 1;
        } while (i < count);
    }
}

extern void Barrel_FillDamagePacket(CDamageInfo *event, void *target, s32 damage, f32 radius, s32 flags, Shield *shield);
extern void Barrel_RunDamageHook(LevelActor *actor, s32 *behavior, CDamageInfo *event);
void Scene_ApplyDamageToTypeOneActors(Shared_World *world, s32 damage, s32 flags) {
    CDamageInfo event;
    LevelActor **actors;
    s32 count;
    s32 i;

    Barrel_FillDamagePacket(&event, 0, damage, 102.399994f, flags, 0);
    count = world->kind1Count;
    actors = world->kind1;
    for (i = 0; i < count; i++) {
        Barrel_RunDamageHook(actors[i], &actors[i]->behaviorFlags, &event);
    }
}
