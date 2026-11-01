#include "COMMON/WORLDRECAT1B6A4.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/WORLD.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/COLORENTRY.H"
#include "ENGINE/SCENE.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "ENGINE/SCENE_DRAWTRANSITIONCOLOROVERLAY.H"
#include "ENGINE/DEFS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/GAME_SESSION.H"

/* SCENE_12.CPP */
/* Draws each selected entry in the object range with shared position and scale. */

extern void Rumble_AllocatePoolNode(s32,void *,Triple,f32,f32,s32);

extern void SetN64_DrawColorRectangle(void *unused, s8 *color, s32 left, s32 top,
                          s32 right, s32 bottom);

void Scene_SetTypeThreeActorStateBits(void *world) {
    Shared_World *object;
    s32 count;
    s32 i;
    s32 offset;
    LevelActor *entry;
    s32 field;
    s32 three;

    object = world;
    count = object->actorCount;
    i = 0;
    if (count > 0) {
        three = 3;
        offset = 0;
        do {
            object = world;
            entry = (void *)((char *)object->actors + offset);
            field = ((struct Def *)entry->definition)->type;
            if (field != three) {
                i += 1;
            } else {
                Rumble_SetActorStateBit(world, entry, 1);
                i += 1;
            }
            offset += 744;
        } while (i < count);
    }
}

void Scene_ClearTypeThreeActorStateBits(void *world) {
    Shared_World *object;
    s32 count;
    s32 i;
    s32 offset;
    LevelActor *entry;
    s32 field;
    s32 three;

    object = world;
    count = object->actorCount;
    i = 0;
    if (count > 0) {
        three = 3;
        offset = 0;
        do {
            object = world;
            entry = (void *)((char *)object->actors + offset);
            field = ((struct Def *)entry->definition)->type;
            if (field != three) {
                i += 1;
            } else {
                Rumble_SetActorStateBit(world, entry, 0);
                i += 1;
            }
            offset += 744;
        } while (i < count);
    }
}

/** Return an indexed record from the world's strided table. */
void *Scene_GetEffectCurveRecord(Shared_World *world, s32 index) {
    StridedTable *table = world->stridedRecords;
    void *base = table;
    char *bytes = base;
    s32 stride = table->stride;
    return bytes + (index * stride + 8);
}

void CScene_StartEventClips(ObjectCSceneStartEventClips *scene,s32 resource,s32 group,Triple pos,ScalarPair scale) {
 s32 groupFirstIndex,groupLastIndex; void *data; s32 count; StridedTable *clipRecords; s32 i; StridedTable *clipGroups;
 f32 firstValue,secondValue;
 clipGroups=scene->clipGroupKeys;
 firstValue=scale.first;secondValue=scale.second;
 data=clipGroups->data;count=clipGroups->count;
 if(Defs_FindSortedGroupRange(data,count,group,&groupFirstIndex,&groupLastIndex)) {
  for(i=groupFirstIndex;i<=groupLastIndex;i++) {
   clipRecords=scene->clipDefinitions;
   Rumble_AllocatePoolNode(resource,(char *)clipRecords+(i*clipRecords->stride+8),pos,firstValue,secondValue,0);
  }
 }
}

void *Scene_GetActorDefinition(void *world, s32 index) {
    void *result;

    if (index == -1) {
        goto ret_null;
    }
    result = SetN64_GetPackSection(((struct ScenePackSectionTableView *) ((s8 *) world))->sectionTable, index);
    goto end;
ret_null:
    result = 0;
end:
    return result;
}

void *Scene_FindActorDefinition(Shared_World *world, s32 selection, s32 modelKind) {
    s32 *descriptor;
    s32 count;
    s32 i;
    ActorDefinitionHeader *entry;

    descriptor = world->actorDefinitions;
    count = *descriptor;
    for (i = 0; i < count; i++) {
        entry = SetN64_GetPackSection(world->actorDefinitions, i);
        if (selection != -1 && entry->kind != selection) {
            continue;
        }
        if (modelKind == -1) {
            return entry;
        }
        if (entry->character != modelKind) {
            continue;
        }
        return entry;
    }
    return 0;
}

/* Collects up to max records of container (indices actorCursor to actorCount) whose modelId, kindDescriptor->kindId and kindDescriptor->teamId match key0, key1 and key2 (each skipped when -1) into out, returning the count. */
s32 Scene_CollectMatchingLevelActors(Container *container, s32 key0, s32 key1, s32 key2, SceneActorMatchRecord **out, s32 max) {
    s32 i = container->actorCursor;
    s32 end = container->actorCount;
    SceneActorMatchRecord *base = container->actors;
    s32 count = 0;
    SceneActorMatchRecord *rec;

    for (; i < end; i++) {
        rec = &base[i];
        if (count >= max) {
            return count;
        }
        if ((key0 == -1 || rec->modelId == key0) && (key1 == -1 || rec->kindDescriptor->kindId == key1)
            && (key2 == -1 || rec->kindDescriptor->teamId == key2)) {
            *out++ = rec;
            count++;
        }
    }
    return count;
}

void Scene_DrawTransitionColorOverlay(Shared_World *world) {
    s8 color[4];
    s32 state;
    ColorEntry *entry;
    f32 alpha;
    s32 converted;

    state = world->frozen;
    if (state == 0) {
        return;
    }
    if (state < 0) {
        return;
    }
    if (state >= 3) {
        return;
    }
    {
        entry = &g_emacText[world->selectionState];
        if (entry->value != 0.0f) {
            color[0] = entry->red;
            color[1] = entry->green;
            color[2] = entry->blue;
            alpha = (world->selectionTimer * g_transitionAlphaScaleTable[1]) /
                    entry->value;
            if (!(g_transitionAlphaUnsignedConversionBase <= alpha)) {
                converted = (s32)alpha;
            } else {
                converted = (s32)(alpha - g_transitionAlphaUnsignedConversionBase);
                converted |= 0x80000000;
            }
            color[3] = converted;
            SetN64_DrawColorRectangle(&g_gameSession, color, 0, 0, g_hudReferenceViewportWidth,
                          g_hudReferenceViewportHeight);
        }
    }
}

/* SCENE_13.CPP */
char *Scene_GetPlatformRoute(void *world, s32 index) {
    return SetN64_GetPackSection(SetN64_GetPackSection((((struct SceneNestedPackSectionTableView *) ((s8 *) world))->nestedSectionTable), index), 0);
}
