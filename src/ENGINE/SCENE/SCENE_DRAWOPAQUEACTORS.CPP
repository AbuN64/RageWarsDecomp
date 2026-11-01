#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/SCENERECAT10C0.H"
#include "SCENE/SCENE_UPDATEANDDRAWWORLD.H"
#include "TYPES.H"
#include <PR/gbi.h>
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

char *Scene_GetLinkedResourceSection(void *world, s32 resourceId) {
    return SetN64_GetPackSection((((struct ScenePackResourceView *) ((s8 *) world))->pack), resourceId);
}

/** Return an indexed record from the table at object offset 0xA0. */
void *Scene_GetStridedWorldRecord(struct Shared_World *object, int index) {
    char *base = (char *)object->records;
    int stride = *(int *)base;
    return base + (index * stride + 8);
}

/* Draws a scene's object list inside a Geometry_BeginModelBatch and Geometry_FlushModelBatch pass: writes four G_MOVEWORD commands setting the words at 4, 0xC, 0x14 and 0x1C to 5, 5, 0xFFFB and 0xFFFB, then draws each object through Gobjinst_DrawVisibleCachedActor unless its flag 4 is set, in which case it is deferred to the scene's 64-entry late list. */






extern Gfx *g_displayListCursor;


extern void Gobjinst_DrawVisibleCachedActor(LevelActor *object, void *camera);

void Scene_DrawOpaqueActors(SceneActorUpdateLists *scene, void *camera) {
    LevelActor *object;
    s32 count;
    s32 i;
    s32 late;
    LevelActor **objects;

    Geometry_BeginModelBatch();
    count = scene->count;
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 4, 5);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 12, 5);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 20, 0xFFFB);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 28, 0xFFFB);
    objects = scene->objects;
    for (i = 0; i < count; i++) {
        object = objects[i];
        if (object->flags & 4) {
            late = scene->lateCount;
            if (late != 64) {
                scene->late[late] = object;
                scene->lateCount = late + 1;
            }
        } else {
            Gobjinst_DrawVisibleCachedActor(object, camera);
        }
    }
    Geometry_FlushModelBatch();
}


extern void Particle_DrawRenderList(s32 world, s32 view);


void Scene_DrawWorldParticles(s32 world, s32 view) {
    Gfx *cmd;

    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 4, 1);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 12, 1);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 20, 0xFFFF);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 28, 0xFFFF);
    Geometry_BeginModelBatch();
    Particle_DrawRenderList(world + 6920, view);
    Geometry_FlushModelBatch();
}

s32 Scene_FindModelIdIndex(struct Shared_World *world, s32 modelId)
{
  s32 count;
  s32 i;
  u16 *ptr;
  void *base;
  s32 masked;
  base = world->modelIds;
  count = ((struct SceneModelIdTable *)(base))->count;
  ptr = &((struct SceneModelIdTable *)(base))->entries[0];
  i = 0;
  if (count <= 0)
  {
    goto fail;
  }
  masked = modelId & 0xFFFF;
  loop_2:
  if ((*ptr) == masked)
  {
 do { return i; } while (0);
  }

  i += 1;
  ptr += 1;
  if (i < count)
  {
    goto loop_2;
  }
  fail:
  return -1;

}

int Scene_GetModelIdAtIndex(void *world, int modelIndex) {
    unsigned short *base = (unsigned short *)((char *)((struct Shared_World *)(world))->modelIds + 8);
    return base[modelIndex];
}

/* Changes an object's model when the requested model id is present in the resource bank, then rebuilds its model data. */



extern void Gobjinst_LoadModel(ObjectSceneChangeInstanceModel *,s32,s32,s32);
static inline s32 find(SceneModelIdTable *table,u16 id) {
 s32 index=0,count; u16 *entry;entry=table->entries;count=table->count;
 if(count>0) { do {if(*entry==id) return index; index++;entry++;} while(index<count); }
 return -1;
}
void Scene_ChangeInstanceModel(SceneModelBankView *modelBank,ObjectSceneChangeInstanceModel *draw,s32 modelId,s32 extra) {
 s32 index=0;
 if(draw->id!=modelId) {
 index=find(modelBank->table,modelId);
 if(index!=-1){draw->index=index;draw->id=modelId;Gobjinst_LoadModel(draw,modelBank->modelDirectory,modelBank->directoryBank,extra);}
 }
}


void *Scene_GetModelRecordByIndexPointer(Shared_World *world, u16 *modelIndex) {
    s32 base;
    s32 idx;

    if (modelIndex == 0) {
        return 0;
    }
    base = ((char *)SetN64_GetPackSection(world->modelSections, 0)) + 8;
    idx = *modelIndex;
    return (void *)(base + idx * 100);
}


u32 Scene_GetModelSectionTwoIndex(Shared_World *world, s32 modelId) {
    s32 offset;
    s32 result;

    if (modelId == 0) {
        return -1;
    }
    offset = ((char *)SetN64_GetPackSection(world->modelSections, 2)) + 8;
    result = modelId - offset;
    return (u32)result >> 5;
}







s32 Scene_GetModelSectionTwoRecord(void *world, s32 modelId) {
    s32 raw;
    s32 base;

    raw = SetN64_GetPackSection(((Shared_World *)world)->modelSections, 2);
    base = raw + 8;
    if (modelId < 0 || modelId >= ((StridedTable *)raw)->count) {
        return 0;
    }
    return base + (modelId << 5);
}

extern void SetN64_GetPackSectionSize(s32 table, s32 index);




void Scene_SetSecondaryLevelBit(struct Shared_World *world, s32 index, s32 bitIndex, s32 enabled) {
    void *table;
    u8 *base1;
    u8 *base2;
    s32 mask;
    s32 idx;
    s32 idx2;

    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->secondaryLevels, 0), index), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base1 = (u8 *) SetN64_GetPackSection(table, 1);
    base2 = base1;
    mask = 1 << (bitIndex & 7);
    if (enabled != 0) {
        idx = bitIndex;
        if (bitIndex < 0) {
            idx = bitIndex + 7;
        }
        base1[idx >> 3] |= mask;
        return;
    }
    idx2 = bitIndex;
    if (idx2 < 0) {
        idx2 += 7;
    }
    base2[idx2 >> 3] &= ~mask;
}

void Scene_EmptyHandlerAfterSetSecondaryLevelBit(void) {
}





void Scene_SetCurrentSecondaryLevelBit(struct Shared_World *world, s32 bitIndex, s32 enabled) {
    void *secondaryLevels;
    s32 levelIndex;
    void *table;
    u8 *base1;
    u8 *base2;
    s32 mask;
    s32 idx;
    s32 idx2;

    secondaryLevels = world->secondaryLevels;
    levelIndex = world->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(secondaryLevels, 0), levelIndex), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    base1 = (u8 *) SetN64_GetPackSection(table, 1);
    base2 = base1;
    mask = 1 << (bitIndex & 7);
    if (enabled != 0) {
        idx = bitIndex;
        if (bitIndex < 0) {
            idx = bitIndex + 7;
        }
        base1[idx >> 3] |= mask;
        return;
    }
    idx2 = bitIndex;
    if (idx2 < 0) {
        idx2 += 7;
    }
    base2[idx2 >> 3] &= ~mask;
}





s32 Scene_TestCurrentSecondaryLevelBit(struct Shared_World *world, s32 bitIndex) {
    void *secondaryLevels;
    s32 levelIndex;
    void *table;
    u8 *stateBits;
    s32 mask;
    s32 i;

    secondaryLevels = world->secondaryLevels;
    levelIndex = world->level;
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(secondaryLevels, 0), levelIndex), 0);
    SetN64_GetPackSection(table, 0);
    SetN64_GetPackSectionSize((s32) table, 1);
    stateBits = (u8 *) SetN64_GetPackSection(table, 1);
    mask = 1 << (bitIndex & 7);
    i = bitIndex;
    if (i < 0) {
        i += 7;
    }
    return (stateBits[i >> 3] & mask) != 0;
}
