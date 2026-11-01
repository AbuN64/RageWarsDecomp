#include "WORLD/STATIC_MODEL_INSTANCE_VIEWS.H"
#include "../../../sdk/include/LIBC.H"
#include "COMMON/RESULTS.H"
#include "TYPES.H"
#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "ENGINE/SETN64.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ACTOR_DEFINITION.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/WORLD.H"
#include "RENDER/EFFECT_POOL_OPERATIONS.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/TRIPLE.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/PROPGEOMETRY.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "WORLD/BARREL_SPAWNACTOREFFECT_DATA.H"

/* 8028FD2C_4.CPP */
s32 SetN64_GetPackSize(s32 *bitSet) {
    s32 *packBase;
    s32 packSize;
    SetN64_GetPackBaseAndSize(bitSet, &packBase, &packSize);
    return packSize;
}

/* 8028FD2C_6.CPP */
/** Return the byte address named by an indexed word offset from the base. */
void *SetN64_GetPackSection(void *table, s32 index) {
    s32 *entry = (s32 *)table + index;
    return (char *)table + entry[1];
}

s32 SetN64_GetSizedPackSection(s32 packAddress, s32 sectionIndex, s32 *sectionSizeOut) {

    s32 *next = (s32 *)(packAddress + ((sectionIndex + 1) * 4));
    s32 *entry = (s32 *)(packAddress + (sectionIndex * 4));
    *sectionSizeOut = next[1] - entry[1];
    return packAddress + entry[1];
}

s32 SetN64_GetPackSectionSize(s32 *table, s32 index) {
    s32 nextIndex = index + 1;
    s32 *next = &table[nextIndex];
    s32 *entry = &table[index];
    s32 size;
    s32 *output = &size;
    *output = next[1] - entry[1];
    return size;
}

/* 8028FD2C_7.CPP */
/** Add an indexed word from the first argument to the second argument. */
int SetN64_GetDirectoryEntry(int *directory, int bankOffset, int level) {
    directory += level;
    return bankOffset + directory[1];
}

s32 SetN64_LocatePackSection(void *directory, s32 bankOffset, s32 sectionIndex, s32 *sectionSizeOut) {

    s32 *next = (s32 *)(directory + ((sectionIndex + 1) * 4));
    s32 *entry = (s32 *)(directory + (sectionIndex * 4));
    *sectionSizeOut = next[1] - entry[1];
    return bankOffset + entry[1];
}

s32 SetN64_GetPackSectionOffsetAndSize(s32 directoryAddress, s32 sectionIndex, s32 *sectionSizeOut) {

    s32 *next = (s32 *)(directoryAddress + ((sectionIndex + 1) * 4));
    s32 *entry = (s32 *)(directoryAddress + (sectionIndex * 4));
    *sectionSizeOut = next[1] - entry[1];
    return entry[1];
}

void SetN64_GetPackBaseAndSize(int *directory, int **packBaseOut, int *packSizeOut) {
    int *p;
    *packBaseOut = directory;
    p = directory + *directory;
    *packSizeOut = p[1];
}

/* 8028FD2C_9.CPP */
int SetN64_GetRecordBlockSize(int *recordHeader) {
    return recordHeader[0] * recordHeader[1] + 8;
}

void SetN64_GetChunkStorage(void *chunk, void **storageOut, s32 *sizeOut) {
    *storageOut = chunk;
    *sizeOut = ((((struct ActorAnimationEventTable *) ((s8 *) chunk))->entrySize) * (((struct ActorAnimationEventTable *) ((s8 *) chunk))->entryCount)) + 8;
}

/* 8028FD2C_11.CPP */
void *SetN64_GetChunkPayload(int *chunk, int *sizeOut) {
    *sizeOut = chunk[0] * chunk[1];
    return &((ResidentDataChunk *)(chunk))->data[0];
}

/* Transposes the byte matrix after its eight-byte dimensions header and optionally copies the result back. */



void SetN64_TransposeRecords(void *sourceBlock, void *destinationBlock, s32 copyBack)
{
  char *data = &((ResidentDataChunk *)(sourceBlock))->data[0];
  s32 columnCount;
  int first_column;
  s32 rowCount;
  s32 rowIndex;
  s32 columnIndex;
  s32 sourceOffset;
  u8 *sourceByte;
  u8 *destinationByte;
  first_column = 0;
  Libc_CopyBytes(destinationBlock, sourceBlock, 8);
  destinationByte = destinationBlock + 8;
  columnCount = ((struct IntPair *) sourceBlock)->second;
  rowCount = ((struct IntPair *) sourceBlock)->first;
  columnIndex = first_column;
  if (columnCount > first_column)
  {
    do
    {
      rowIndex = 0;
      if (rowCount > 0)
      {
        sourceOffset = columnIndex;
        do
        {
          sourceByte = data + sourceOffset;
          sourceOffset += columnCount;
          rowIndex += 1;
          *destinationByte = *sourceByte;
          destinationByte += 1;
        }
        while (rowIndex < rowCount);
      }
      columnIndex += 1;
    }
    while (columnIndex < columnCount);
  }
  if (copyBack != 0)
  {
    Libc_CopyBytes(sourceBlock, destinationBlock, (columnCount * rowCount) + 8);
  }
}

/* Spawns a pooled object and registers its bounds and height. */

void GameObject_ResetActorMotion(void *);
s32 Scene_FindModelIdIndex(struct Shared_World *, s32);
s32 Scene_GetIndexedModelResource(void *, s32);
void Scene_SampleWorldLighting(void *, CVector3 *, void *);
void SetN64_RecycleEffectNode(void *, void *);

extern s32 g_screenImageResourcesEnabled[];

void *SetN64_SpawnModelEffect(char *container, s32 *referenceCounter, s32 modelId, CVector3 rotation, CVector3 position, s32 effectOwner, f32 initialLifetime)
{
  CVector3 center;
  s32 type;
  f32 far_z;
  s32 modelResource;
  char *effectActor;
  char *previousActiveHead;
  if (((*g_screenImageResourcesEnabled) == 0) || ((type = Scene_FindModelIdIndex(&g_world, modelId), type == (-1))))
  {
    return 0;
  }
  if ((((EffectSlotPool *)(container))->free) == 0)
  {
    SetN64_RecycleEffectNode(container, ((EffectSlotPool *)(container))->tail);
  }
  effectActor = ((EffectSlotPool *)(container))->free;
  previousActiveHead = ((EffectSlotPool *)(container))->head;
  ((EffectSlotPool *)(container))->free = (void *) (((SceneEffect *)(effectActor))->next);
  if (previousActiveHead != 0)
  {
    ((SceneEffect *)(previousActiveHead))->prev = effectActor;
  }
  { char *next = ((EffectSlotPool *)(container))->head;
  ((SceneEffect *)(effectActor))->prev = 0;
  ((SceneEffect *)(effectActor))->next = next; }
  ((EffectSlotPool *)(container))->head = effectActor;
  if ((((EffectSlotPool *)(container))->tail) == 0)
  {
    ((EffectSlotPool *)(container))->tail = effectActor;
  }
  ((SceneEffect *)(effectActor))->state = (s32) ((((SceneEffect *)(effectActor))->state) | 1);
  GameObject_ResetActorMotion(effectActor);
  ((SceneEffect *)(effectActor))->lifetime = 0;
  modelResource = Scene_GetIndexedModelResource(&g_world, type);
  ((SceneEffect *)(effectActor))->counter = referenceCounter;
  if (referenceCounter != 0)
  {
    *referenceCounter += 1;
  }
  if (g_gameSettings.local != 0)
  {
    ((SceneEffect *)(effectActor))->definition = &g_boundedEffectDefinition.header;
  }
  else
  {
    ((SceneEffect *)(effectActor))->definition = &g_defaultEffectDefinition;
  }
  ((SceneEffect *)(effectActor))->lifetime = initialLifetime;
  ((SceneEffect *)(effectActor))->lifetimeState = 0;
  ((SceneEffect *)(effectActor))->model = type;
  position.y += 10.24f;
  ((SceneEffect *)(effectActor))->position = position;
  ((SceneEffect *)(effectActor))->angle = 0;
  ((SceneEffect *)(effectActor))->angleState = 0;
  ((SceneEffect *)(effectActor))->collisionState = 0;
  ((SceneEffect *)(effectActor))->collisionScale = 1.0f;
  ((SceneEffect *)(effectActor))->collisionFlags = 0;
  ((SceneEffect *)(effectActor))->minX = (f32) (position.x - 81.92f);
  ((SceneEffect *)(effectActor))->minY = (f32) (position.y - 81.92f);
  ((SceneEffect *)(effectActor))->minZ = (f32) (position.z - 81.92f);
  ((SceneEffect *)(effectActor))->maxX = (f32) (position.x + 81.92f);
  ((SceneEffect *)(effectActor))->maxY = (f32) (position.y + 81.92f);
  far_z = position.z;
  ((SceneEffect *)(effectActor))->resource = modelResource;
  ((SceneEffect *)(effectActor))->animation = -1;
  ((SceneEffect *)(effectActor))->frame = 0;
  ((SceneEffect *)(effectActor))->frameState = 0;
  ((SceneEffect *)(effectActor))->owner = effectOwner;
  ((SceneEffect *)(effectActor))->boundsState = 0;
  ((SceneEffect *)(effectActor))->flags = 0x1A;
  ((SceneEffect *)(effectActor))->maxZ = (f32) (far_z + 81.92f);
  ((SceneEffect *)(effectActor))->rotation = rotation;
  ((SceneEffect *)(effectActor))->effectState = 0;
  center.x = ((SceneEffect *)(effectActor))->position.x;
  center.y = (((SceneEffect *)(effectActor))->position.y) + (Gobjinst_GetActorHeight(effectActor) * 0.5f);
  center.z = ((SceneEffect *)(effectActor))->position.z;
  Scene_SampleWorldLighting(&g_world, &center, &((StaticObject *)effectActor)->lights);
  return effectActor;
}

/* Updates a world's active actors: counts each actor's lifetime down by the frame time and expires it when the lifetime runs out or when its bounds leave the world box g_cameraVolumeBounds (unless it is flagged 0x200); an expired active actor loses its active bit, decrements its owner's counter and moves from the active list to the free list, and every other actor is updated through SetN64_UpdateEffectMotionAndBounds. */

extern f32 g_frameElapsedTime;

void SetN64_UpdateEffectPool(EffectSlotPool *world) {
    SceneEffect *actor;
    SceneEffect *next;
    s32 expired;
    f32 lifetime;

    next = world->head;
    if (next == 0) {
        return;
    }
    do {
        actor = next;
        next = actor->next;
        expired = 0;
        if (actor->lifetime > 0.0f) {
            lifetime = actor->lifetime - g_frameElapsedTime;
            actor->lifetime = lifetime;
            if (lifetime <= 0.0f) {
                expired = 1;
            }
        }
        if (!((g_cameraVolumeBounds.max.x > actor->minX) && (g_cameraVolumeBounds.min.x < actor->maxX) &&
              (g_cameraVolumeBounds.max.z > actor->minZ) && (g_cameraVolumeBounds.min.z < actor->maxZ) &&
              (g_cameraVolumeBounds.max.y > actor->minY) && (g_cameraVolumeBounds.min.y < actor->maxY))) {
            if (!(actor->flags & 0x200)) {
                expired = 1;
            }
        }
        if (expired) {
            if (actor->state & 1) {
                actor->state &= ~1;
                if (actor->counter != 0) {
                    (*actor->counter)--;
                }
                if (actor->prev != 0) {
                    actor->prev->next = actor->next;
                }
                if (actor->next != 0) {
                    actor->next->prev = actor->prev;
                }
                if (world->head == actor) {
                    world->head = actor->next;
                }
                if (world->tail == actor) {
                    world->tail = actor->prev;
                }
                actor->next = world->free;
                actor->prev = 0;
                world->free = actor;
            }
        } else {
            SetN64_UpdateEffectMotionAndBounds(actor);
        }
    } while (next != 0);
}

void SetN64_InitializeEffectSlot(struct EffectSlot *effectSlot) {
    effectSlot->definition = &g_defaultEffectDefinition;
    effectSlot->active = 3;
    effectSlot->state = 0;
}

extern char g_primaryCollisionContext;
extern char g_secondaryCollisionContext;

extern void Simpinst_UpdateModelAndScale(SceneEffect *);
extern void Unicol_MoveActorWithCollision(SceneEffect *, f32, f32, f32, void *);

void SetN64_UpdateEffectMotionAndBounds(SceneEffect *effect)
{
  void *collisionContext;
  f32 motionHoldTime;
  f32 radius;
  f32 x;
  CVector3 saved;
  collisionContext = &g_secondaryCollisionContext;
  if (!(effect->definition->gate & 4))
  {
    collisionContext = &g_primaryCollisionContext;
  }
  motionHoldTime = effect->lifetimeState;
  if (motionHoldTime > 0.0f)
  {
    effect->lifetimeState = (f32) (motionHoldTime - g_frameElapsedTime);
    saved = effect->position;
  }
  Simpinst_UpdateModelAndScale(effect);
  if (effect->definition != (&g_defaultEffectDefinition))
  {
    effect->rotation.x = 0.0f;
    effect->rotation.y = 0.0f;
    effect->rotation.z = 0.0f;
  }
  Unicol_MoveActorWithCollision(effect, effect->position.x, effect->position.y, effect->position.z, collisionContext);
  x = effect->position.x;
  radius = g_effectDefaultRadius;
  effect->minX = (f32) (x - radius);
  effect->minY = (f32) (effect->position.y - radius);
  effect->minZ = (f32) (effect->position.z - radius);
  effect->maxX = (f32) (effect->position.x + radius);
  {
    f32 z = effect->position.z + radius;
    f32 y = effect->position.y + radius;
    effect->maxY = y;
    effect->maxZ = z;
  }
}

/* 8028FD2C_12.CPP */
extern s32 Visdata_TestBoxAgainstFrustum(void *frustum, void *box);

extern void Simple_DrawCachedModel(void *obj);

extern f32 g_cameraVolumeBoundsMinZ[];

extern s32 InstHdr_CanActorReceiveInteraction(void *actor);

/** Unlink an active node and return it to the global free list. */
void SetN64_RecycleGlobalEffectNode(EffectPoolNode *node) {
    EffectPoolNode *oldHead;

    if (node->flags & 1) {
        node->flags &= ~1;
        if (node->reference_count != 0) {
            (*node->reference_count)--;
        }
        if (node->previous != 0) {
            node->previous->next = node->next;
        }
        if (node->next != 0) {
            node->next->previous = node->previous;
        }
        if (g_effectPoolActiveHead == node) {
            g_effectPoolActiveHead = node->next;
        }
        if (g_effectPoolActiveTail == node) {
            g_effectPoolActiveTail = node->previous;
        }
        oldHead = g_effectPoolFreeHead;
        node->previous = 0;
        *(EffectPoolNode *volatile *) &node->next = oldHead;
        g_effectPoolFreeHead = node;
    }
}

void SetN64_DrawVisibleEffects(char *effectPool, char *view) {
    EffectSlotPool *world = (void *)effectPool;
    GameplayCamera *camera = (void *)view;
    SceneEffect *entry;
    f32 value;
    f32 upper;
    f32 scale;
    f32 zero;

    Geometry_BeginModelBatch();
    entry = world->head;
    if (entry != 0) {
        zero = 0.0f;
        upper = g_effectDefaultUpperBound;
        scale = g_effectDefaultScale;
        do {
            if ((camera->clipBounds[1].x > entry->minX) &&
                (camera->clipBounds[0].x < entry->maxX) &&
                (camera->clipBounds[1].z > entry->minZ) &&
                (camera->clipBounds[0].z < entry->maxZ) &&
                (camera->clipBounds[1].y > entry->minY) &&
                (camera->clipBounds[0].y < entry->maxY) &&
                (Visdata_TestBoxAgainstFrustum(camera->clipPlanes, &entry->minX) != 0)) {
                value = entry->lifetime;
                g_menuModelFillEnabled = 0;
                if ((value > zero) && (value <= upper)) {
                    g_menuModelFillEnabled = 1;
                    g_menuModelFillColor[3] = value * scale;
                }
                Simple_DrawCachedModel(entry);
                g_menuModelFillEnabled = 0;
            }
            entry = entry->next;
        } while (entry != 0);
    }
    Geometry_FlushModelBatch();
}

void SetN64_CollectVisibleEffectNodes(VisibleEffectPoolView *effectPool, Results *results) {
    f32 *bounds;
    s32 count;
    s32 mask;
    s32 required;
    s32 limit;
    NodeSetN64CollectVisibleEffectNodes *node;

    node = effectPool->head;
    if (node != 0) {
        mask = 0x30000;
        required = 0x20000;
        bounds = g_cameraVolumeBoundsMinZ + 1;
        limit = 512;
        do {
            Simpinst_ClearCachedResource(node);
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            if ((((*(u16 *)&node->flags) & (mask >> 16)) == (required >> 16)) &&
                (InstHdr_CanActorReceiveInteraction(node) != 0) &&
                !(*(u16 *)&node->flags & 0x100) &&
#else
            if (((node->flags & mask) == required) &&
                (InstHdr_CanActorReceiveInteraction(node) != 0) &&
                !(*(u16 *)&node->flags & 0x100) &&
#endif
                (bounds[0] > node->x0) &&
                (bounds[-3] < node->y0) &&
                (bounds[2] > node->x2) &&
                (bounds[-1] < node->y2) &&
                (bounds[1] > node->x1) &&
                (bounds[-2] < node->y1)) {
                count = results->count;
                if (count != limit) {
                    results->nodes[count] = node;
                    results->count = count + 1;
                }
            }
            node = node->next;
        } while (node != 0);
    }
}

void *SetN64_AllocateActorFromPool(ActorPoolFreeListView *container)
{
  void *actor;
  void *node;
  struct EffectPoolNode *next;
  if ((container->freeHead) == 0)
  {
    SetN64_RecycleEffectNode(container, container->activeTail);
  }
  node = container->freeHead;
  next = container->next;
  container->freeHead = ((VisibleEffectNodeLinks *)(node))->next;
  if (next != 0)
  {
    next->previous = node;
  }
  actor = container->next;
  ((VisibleEffectNodeLinks *)(node))->previous = 0;
  ((VisibleEffectNodeLinks *)(node))->next = actor;
  container->next = node;
  if ((container->activeTail) == 0)
  {
    container->activeTail = node;
  }
  ((VisibleEffectNodeLinks *)(node))->flags |= 1;
  GameObject_ResetActorMotion(node);
  ((VisibleEffectNodeLinks *)(node))->clearedWord = 0;
  return node;
}

/* 800CA494.CPP */
/* ROM-grounded data: src/g_EngineSetn64RetainedWords1_Setn64.c */
const float g_EngineSetn64RetainedWords1[1] = {
    81.92f,
};

/* 800CA498.CPP */
/* ROM-grounded data: src/g_EngineSetn64RetainedWords2_Setn64.c */
const float g_EngineSetn64RetainedWords2[2] = {
    7.5f, 34.0f,
};
