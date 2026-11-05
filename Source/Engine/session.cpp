#include "Gfxdata/audio_decodeframe_data.h"
#include "Render/sequence_prompt_state_views.h"
#include "Engine/Instance/gobjinst.h"
#include "Cache/cache_allocateresourceat.h"
#include "Common/runtime_declarations.h"
#include "Common/objb.h"
#include "World/static_model_instance_views.h"
#include "LIBC.H"
#include "Common/results.h"
#include "types.h"
#include "include_asm.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/session.h"
#include "Common/actor_definition.h"
#include "Common/shared_gameslot.h"
#include "Common/world.h"
#include "Render/effect_pool_operations.h"
#include "Common/multiplayeroptions.h"
#include "Common/triple.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/vector4f.h"
#include "Common/gameplay_camera.h"
#include "Common/propgeometry.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "World/barrel_spawnactoreffect_data.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Engine/visdata_decoderegiongrid.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Gobjinst/gameobject_movetoxzkeepheight.h"
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#include "Menu/Items/Scene/scene_registeractorinscenelists.h"
#include "Common/weapon_screen_message_operations.h"
#include "Engine/Instance/simpinst.h"
#include "Camera/collision_sweep_views.h"
#include "Engine/lighting.h"
#include "Engine/animpool.h"
#include "Render/setn64_onworldviewdraw.h"
#include "Common/frame_direction.h"
#include "Common/sessionhandlerrow.h"
#include "Fx/normalize_vector.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/game_session.h"
#include <platform_sdk.h>
#include <PR/abi.h>
#include <PR/gbi.h>
#include "Common/video_dimensions.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#if defined(VERSION_DE)
#include "Engine/session.h"
#endif
#if defined(VERSION_DE)
#include "Engine/scene_drawopaqueactors.h"
#endif
#if defined(VERSION_DE)
#include "Geometry/geometry_drawblendparts.h"
#endif
#if defined(VERSION_DE)
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#endif
#if defined(VERSION_DE)
#include "Particle/graphu64_matrixfromeulerxyz.h"
#endif
#if defined(VERSION_DE)
#include "Common/weapon_marker_and_profile_views.h"
#endif
#if defined(VERSION_DE)
#include "Camera/camera.h"
#endif
#if defined(VERSION_DE)
#include "Engine/graphics_math.h"
#endif
#if defined(VERSION_DE)
#include "Weapons/weapon_switch_actions.h"
#endif
#include "Common/display.h"
#include "Common/font_style_and_glyph_operations.h"
#include "Onscrn/onscreen_drawscaledmaskedtilegrid.h"
#include "Common/round_session.h"
#include "Common/effectrender.h"
#include "Ai/Player/playerai_findtransientplayer.h"
#include "Engine/tengine.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Common/cache_allocateresource.h"
#include "Common/group.h"
#include "Common/music_track_volume.h"
#include "Common/snapshot_actor.h"
#include "Common/worldsortentry.h"
#include "Common/level.h"
#include "Camera/ccinema_resetsequencecontext.h"
#include "Ovlgame/match_initparticlequad.h"
#include "Render/setn64_updatefadetransition.h"
#include "AUDIO/sprintf.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Ui/X_files/x_plus.h"
#include "Ovlgame/note_releaserenderbuffers.h"
#include "Resmgr/tsmos_updatefrontend.h"
#include "Texture/audiomgr_initheap.h"
#include "Common/player_message_menu.h"
#include "Common/boot_tv_type.h"
#include "System/vimgr.h"
#include "Common/pak_profile_load.h"
#include "Constants/setup_updatenamecursor_data.h"
#include "Data/Gfxdata/audio_decodeframe_data.h"
#include "Data/initialized_runtime_buffers.h"
#include "Menu/Items/Scene/ovlscene_loadsceneresources.h"
#include "Ovlgame/hud.h"
#include "Ovlgame/ovlgame_initializeplayerpool.h"
#include "Pools/pools.h"
#include "Setn64/setn64_updateframetiming.h"
#include "libultra/libultra_exchangedebuglinkwords.H"
#include "Engine/Unicol/collide.h"
#include "Engine/defs.h"
#include "ovlgame.h"
#include "Engine/sched.h"
#include "Common/viewflags.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Engine/link.h"
#include "Engine/geometry.h"
#include "Common/timing_world.h"
#include "Common/resident_event_handler.h"
#include "Common/os_timer_interrupt_internals.h"
#include "Common/resourcelockstate.h"
#include "Common/pakqueuestate.h"
#include "Common/lightdata.h"
#include "Common/frustum.h"
#include "Common/frontend_video_mode.h"
#include "Camera/ccinema_updatesequence.h"
#include "Frontend/screen_video_mode.h"
#include "Scene/cache_allocateresourceat.h"
#include "System/textload_resettexturecache.h"
#include "System/defs_togglesavedflag.h"
#include "Camera/camera.h"
#include "Setn64/setn64_drawcolorrectangle.h"
#include "Common/shared_menureply.h"
#include "Common/unsigned_quotient.h"
#include "Render/setn64_startsessionthreads.h"
#include "thread_queue.h"
#include "Common/frontend_clock_state.h"
#include "Common/level_track.h"
#include "Menu/Items/Scene/ovlscene_findplacedobjectsbykey.h"
#include "Menu/Items/Scene/scene_buildplacedactors.h"
#include "Menu/Items/Scene/scene_updatependingobjects.h"
#include "Common/track_requesttrackbykey.h"
#include "Common/round_state_variants.h"
#include "Scene/scene_updateanddrawworld.h"
#include "Engine/Cinema/cinema.h"
#include "Ui/Smos/SM_Xlate.h"
#include "Camera/gsky.h"
#include "Common/shared_optionsscreen.h"
#include "Render/timed_session_transitions.h"
#include "Engine/control.h"
#include "Setn64/setn64_drawsplashimage.h"
#include "Common/sky_layers.h"
#include "Render/control_cycleactorsnapshotmode.h"
#include "Common/shared_worldfunc.h"
#include "Render/sequence_prompt_state_views.h"
#include "Render/resident_texture_menu_views.h"
#include "Common/Lone/controller_rumble_pool.h"
#include "Common/residentstate.h"
#include "Engine/rumble.h"
#include "engine.h"
#include "Ai/player.h"
#if defined(VERSION_EU)
#include "Engine/session.h"
#endif
#if defined(VERSION_EU)
#include "Engine/scene_drawopaqueactors.h"
#endif
#if defined(VERSION_EU)
#include "Geometry/geometry_drawblendparts.h"
#endif
#if defined(VERSION_EU)
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#endif
#if defined(VERSION_EU)
#include "Particle/graphu64_matrixfromeulerxyz.h"
#endif
#if defined(VERSION_EU)
#include "Common/weapon_marker_and_profile_views.h"
#endif
#if defined(VERSION_EU)
#include "Camera/camera.h"
#endif
#if defined(VERSION_EU)
#include "Engine/graphics_math.h"
#endif
#if defined(VERSION_EU)
#include "Weapons/weapon_switch_actions.h"
#endif
#if defined(VERSION_EU_X)
#include "Engine/session.h"
#endif
#if defined(VERSION_EU_X)
#include "Engine/scene_drawopaqueactors.h"
#endif
#if defined(VERSION_EU_X)
#include "Geometry/geometry_drawblendparts.h"
#endif
#if defined(VERSION_EU_X)
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#endif
#if defined(VERSION_EU_X)
#include "Particle/graphu64_matrixfromeulerxyz.h"
#endif
#if defined(VERSION_EU_X)
#include "Common/weapon_marker_and_profile_views.h"
#endif
#if defined(VERSION_EU_X)
#include "Camera/camera.h"
#endif
#if defined(VERSION_EU_X)
#include "Engine/graphics_math.h"
#endif
#if defined(VERSION_EU_X)
#include "Weapons/weapon_switch_actions.h"
#endif
#if defined(VERSION_US)
#include "Engine/session.h"
#endif
#if defined(VERSION_US)
#include "Engine/scene_drawopaqueactors.h"
#endif
#if defined(VERSION_US)
#include "Geometry/geometry_drawblendparts.h"
#endif
#if defined(VERSION_US)
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#endif
#if defined(VERSION_US)
#include "Setn64/setn64_setuploadingbackdrop.h"
#endif
#if defined(VERSION_US)
#include "Particle/graphu64_matrixfromeulerxyz.h"
#endif
#if defined(VERSION_US)
#include "Common/weapon_marker_and_profile_views.h"
#endif
#if defined(VERSION_US)
#include "Camera/camera.h"
#endif
#if defined(VERSION_US)
#include "Engine/graphics_math.h"
#endif
#if defined(VERSION_US)
#include "Weapons/weapon_switch_actions.h"
#endif
#if defined(VERSION_US_REV1)
#include "Engine/session.h"
#endif
#if defined(VERSION_US_REV1)
#include "Engine/scene_drawopaqueactors.h"
#endif
#if defined(VERSION_US_REV1)
#include "Geometry/geometry_drawblendparts.h"
#endif
#if defined(VERSION_US_REV1)
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#endif
#if defined(VERSION_US_REV1)
#include "Particle/graphu64_matrixfromeulerxyz.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/weapon_marker_and_profile_views.h"
#endif
#if defined(VERSION_US_REV1)
#include "Data/Gfxdata/audio_decodeframe_data.h"
#endif
#if defined(VERSION_US_REV1)
#include "Camera/camera.h"
#endif
#if defined(VERSION_US_REV1)
#include "Engine/graphics_math.h"
#endif
#if defined(VERSION_US_REV1)
#include "Weapons/weapon_switch_actions.h"
#endif
#include "Data/rest_source_records.h"
#include "Common/world_scene.h"
#include "Common/unresolved_word_access_set.h"
#include "Common/unresolved_word_accesses.h"
#include "Common/level_actor.h"
#include "Common/manager.h"
#include "Common/scene_switch.h"
#include "Common/colorentry.h"
#include "Engine/scene.h"
#include "Scene/scene_findtrackedactors.h"
#include "Scene/cache_requestresource.h"
#include "Common/cache_releaseresource.h"
#include "Engine/Cache/cache.h"
#include "Engine/Instance/statinst.h"
#include <PR/R4300.h>
#include "System/engine_data_source.h"
#include "Data/Enemy/mode_lifecycle_handlers2_us_rev1_data.h"

/* SETN64.CPP */

s32 SetN64_GetPackSize(s32 *bitSet) {
    s32 *packBase;
    s32 packSize;
    SetN64_GetPackBaseAndSize(bitSet, &packBase, &packSize);
    return packSize;
}

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

int SetN64_GetRecordBlockSize(int *recordHeader) {
    return recordHeader[0] * recordHeader[1] + 8;
}

void SetN64_GetChunkStorage(struct ActorAnimationEventTable *chunk, void **storageOut, s32 *sizeOut) {
    *storageOut = chunk;
    *sizeOut = (((chunk)->entrySize) * ((chunk)->entryCount)) + 8;
}

void *SetN64_GetChunkPayload(int *chunk, int *sizeOut) {
    *sizeOut = chunk[0] * chunk[1];
    return &((ResidentDataChunk *)(chunk))->data[0];
}

/* Transposes the byte matrix after its eight-byte dimensions header and optionally copies the result back. */

void SetN64_TransposeRecords(void *sourceBlock, void *destinationBlock, s32 copyBack)
{
  struct IntPair *intPair = (struct IntPair *) sourceBlock;
  char *data = &((ResidentDataChunk *)(sourceBlock))->data[0];
  s32 columnCount;
  int firstColumn;
  s32 rowCount;
  s32 rowIndex;
  s32 columnIndex;
  s32 sourceOffset;
  u8 *sourceByte;
  u8 *destinationByte;
  firstColumn = 0;
  Libc_CopyBytes(destinationBlock, sourceBlock, 8);
  destinationByte = destinationBlock + 8;
  columnCount = intPair->second;
  rowCount = intPair->first;
  columnIndex = firstColumn;
  if (columnCount > firstColumn)
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





struct EffectSlot; void SetN64_RecycleEffectNode(void *container, struct EffectSlot *node);



void *SetN64_SpawnModelEffect(char *container, s32 *referenceCounter, s32 modelId, CVector3 rotation, CVector3 position, s32 effectOwner, f32 initialLifetime)
{
  CVector3 center;
  s32 type;
  f32 farZ;
  s32 modelResource;
  char *effectActor;
  SceneEffect *previousActiveHead;
  if (((g_screenImageResourcesEnabled) == 0) || ((type = Scene_FindModelIdIndex(&g_world, modelId), type == (-1))))
  {
    return 0;
  }
  if ((((EffectSlotPool *)container)->free) == 0)
  {
    SetN64_RecycleEffectNode(container, ((EffectSlotPool *)container)->tail);
  }
  effectActor = ((EffectSlotPool *)(container))->free;
  previousActiveHead = ((EffectSlotPool *)(container))->head;
  ((EffectSlotPool *)(container))->free = (void *) (((EffectSlot *)(effectActor))->next);
  if (previousActiveHead != 0)
  {
    ((EffectSlot *)(previousActiveHead))->prev = effectActor;
  }
  { char *next = ((EffectSlotPool *)(container))->head;
  ((EffectSlot *)(effectActor))->prev = 0;
  ((EffectSlot *)(effectActor))->next = next; }
  ((EffectSlotPool *)(container))->head = effectActor;
  if ((((EffectSlotPool *)(container))->tail) == 0)
  {
    ((EffectSlotPool *)container)->tail = effectActor;
  }
  ((EffectSlot *)(effectActor))->state = (s32) ((((EffectSlot *)(effectActor))->state) | 1);
  GameObject_ResetActorMotion(effectActor);
  ((EffectSlot *)(effectActor))->lifetime = 0;
  modelResource = Scene_GetIndexedModelResource(&g_world, type);
  ((EffectSlot *)(effectActor))->counter = referenceCounter;
  if (referenceCounter != 0)
  {
    *referenceCounter += 1;
  }
  if (g_gameSettings.local != 0)
  {
    ((EffectSlot *)(effectActor))->definition = &g_boundedEffectDefinition.header;
  }
  else
  {
    ((EffectSlot *)(effectActor))->definition = &g_defaultEffectDefinition;
  }
  ((EffectSlot *)(effectActor))->lifetime = initialLifetime;
  ((EffectSlot *)(effectActor))->lifetimeState = 0;
  ((EffectSlot *)(effectActor))->model = type;
  position.y += 10.24f;
  ((EffectSlot *)(effectActor))->position = position;
  ((EffectSlot *)(effectActor))->angle = 0;
  ((EffectSlot *)(effectActor))->angleState = 0;
  ((EffectSlot *)(effectActor))->collisionState = 0;
  ((EffectSlot *)(effectActor))->collisionScale = 1.0f;
  ((EffectSlot *)(effectActor))->collisionFlags = 0;
  ((EffectSlot *)(effectActor))->minX = (f32) (position.x - 81.92f);
  ((EffectSlot *)(effectActor))->minY = (f32) (position.y - 81.92f);
  ((EffectSlot *)(effectActor))->minZ = (f32) (position.z - 81.92f);
  ((EffectSlot *)(effectActor))->maxX = (f32) (position.x + 81.92f);
  ((EffectSlot *)(effectActor))->maxY = (f32) (position.y + 81.92f);
  farZ = position.z;
  ((EffectSlot *)(effectActor))->resource = modelResource;
  ((EffectSlot *)(effectActor))->animation = -1;
  ((EffectSlot *)(effectActor))->frame = 0;
  ((EffectSlot *)(effectActor))->frameState = 0;
  ((EffectSlot *)(effectActor))->owner = effectOwner;
  ((EffectSlot *)(effectActor))->boundsState = 0;
  ((EffectSlot *)(effectActor))->flags = 0x1A;
  ((EffectSlot *)(effectActor))->maxZ = (f32) (farZ + 81.92f);
  ((EffectSlot *)(effectActor))->rotation = rotation;
  ((EffectSlot *)(effectActor))->effectState = 0;
  center.x = ((EffectSlot *)(effectActor))->position.x;
  center.y = (((EffectSlot *)(effectActor))->position.y) + (Gobjinst_GetActorHeight(effectActor) * 0.5f);
  center.z = ((EffectSlot *)(effectActor))->position.z;
  Scene_SampleWorldLighting(&g_world, &center, &((ObjB *)effectActor)->lights);
  return effectActor;
}


/* Updates a world's active actors: counts each actor's lifetime down by the frame time and expires it when the lifetime runs out or when its bounds leave the world box g_cameraVolumeBounds (unless it is flagged 0x200); an expired active actor loses its active bit, decrements its owner's counter and moves from the active list to the free list, and every other actor is updated through SetN64_UpdateEffectMotionAndBounds. */
void SetN64_UpdateEffectPool(EffectSlotPool *world) {
    EffectSlot *actor;
    EffectSlot *next;
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

extern char g_primaryCollisionContext[];


extern void Simpinst_UpdateModelAndScale(void *staticObject);


void SetN64_UpdateEffectMotionAndBounds(EffectSlot *effect)
{
  void *collisionContext;
  f32 motionHoldTime;
  f32 radius;
  f32 x;
  CVector3 saved;
  collisionContext = g_secondaryCollisionContext;
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


struct ObjB; extern void Simple_DrawCachedModel(struct ObjB *obj);




/** Unlink an active node and return it to the global free list. */
void SetN64_RecycleGlobalEffectNode(EffectSlot *node) {
    EffectSlot *oldHead;

    if (node->state & 1) {
        node->state &= ~1;
        if (node->counter != 0) {
            (*node->counter)--;
        }
        if (node->prev != 0) {
            node->prev->next = node->next;
        }
        if (node->next != 0) {
            node->next->prev = node->prev;
        }
        if (g_effectPoolActiveHead == node) {
            g_effectPoolActiveHead = node->next;
        }
        if (g_effectPoolActiveTail == node) {
            g_effectPoolActiveTail = node->prev;
        }
        oldHead = g_effectPoolFreeHead;
        node->prev = 0;
        *(EffectSlot *volatile *) &node->next = oldHead;
        g_effectPoolFreeHead = node;
    }
}

void SetN64_DrawVisibleEffects(char *effectPool, char *view) {
    EffectSlotPool *world = (void *)effectPool;
    GameplayCamera *camera = (void *)view;
    EffectSlot *entry;
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
                Simple_DrawCachedModel((struct ObjB *)entry);
                g_menuModelFillEnabled = 0;
            }
            entry = entry->next;
        } while (entry != 0);
    }
    Geometry_FlushModelBatch();
}

void SetN64_CollectVisibleEffectNodes(EffectSlotPool *effectPool, Shared_World *results) {
    f32 *bounds;
    s32 count;
    s32 mask;
    s32 required;
    s32 limit;
    EffectSlot *node;

    node = effectPool->head;
    if (node != 0) {
        mask = 0x30000;
        required = 0x20000;
        bounds = &g_cameraVolumeBounds.max;
        limit = 512;
        do {
            Simpinst_ClearCachedResource(node);
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            if (((node->flags & (mask >> 16)) == (required >> 16)) &&
                (InstHdr_CanActorReceiveInteraction(node) != 0) &&
                !(node->flags & 0x100) &&
#else
            if (((node->visibilityFlags & mask) == required) &&
                (InstHdr_CanActorReceiveInteraction(node) != 0) &&
                !(node->flags & 0x100) &&
#endif
                (bounds[0] > node->minX) &&
                (bounds[-3] < node->maxX) &&
                (bounds[2] > node->minZ) &&
                (bounds[-1] < node->maxZ) &&
                (bounds[1] > node->minY) &&
                (bounds[-2] < node->maxY)) {
                count = results->interactiveCount;
                if (count != limit) {
                    results->interactive[count] = (LevelActor *)node;
                    results->interactiveCount = count + 1;
                }
            }
            node = node->next;
        } while (node != 0);
    }
}

void *SetN64_AllocateActorFromPool(EffectSlotPool *container)
{
  void *actor;
  void *node;
  struct EffectSlot *next;
  if ((((EffectSlotPool *)container)->free) == 0)
  {
    SetN64_RecycleEffectNode(container, ((EffectSlotPool *)container)->tail);
  }
  node = ((EffectSlotPool *)container)->free;
  next = ((EffectSlotPool *)container)->head;
  ((EffectSlotPool *)container)->free = ((EffectSlot *)(node))->next;
  if (next != 0)
  {
    next->prev = node;
  }
  actor = ((EffectSlotPool *)container)->head;
  ((EffectSlot *)(node))->prev = 0;
  ((EffectSlot *)(node))->next = actor;
  ((EffectSlotPool *)container)->head = node;
  if ((((EffectSlotPool *)container)->tail) == 0)
  {
    ((EffectSlotPool *)container)->tail = node;
  }
  ((EffectSlot *)(node))->state |= 1;
  GameObject_ResetActorMotion(node);
  ((EffectSlot *)(node))->lifetime = 0.0f;
  return node;
}





/* SETN64_RECYCLEEFFECTNODE.CPP */

/** Unlink an active node and return it to the container's free list. */
void SetN64_RecycleEffectNode(void *container, EffectSlot *actor) {
    struct EffectSlot *freeNode;

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
        if (((EffectSlotPool *)container)->head == actor) {
            ((EffectSlotPool *)container)->head = actor->next;
        }
        if (((EffectSlotPool *)container)->tail == actor) {
            ((EffectSlotPool *)container)->tail = actor->prev;
        }
        freeNode = ((EffectSlotPool *)container)->free;
        actor->prev = 0;
        actor->next = freeNode;
        ((EffectSlotPool *)container)->free = actor;
    }
}

/* SETN64_ONWORLDVIEWDRAW.CPP */

/** Perform the no-op callback. */
void SetN64_OnWorldViewDraw(void) {
}

/* SETN64_SETFRAMEDIRECTION.CPP */

void SetN64_ClearFrameDirection(Frame *frame) {
    frame->direction.x = 0.0f;
    frame->direction.y = 0.0f;
}

void SetN64_OnFrameComplete(void *schedule) {}


void SetN64_SetFrameDirection(Frame *frame, CVector3 *directionStorage) {
    frame->direction = *directionStorage;
    Graphu64_NormalizeVec3(&frame->direction.x);
}

/** Copy four scalar fields from the source into output pointers. */
void SetN64_GetRecordOutputs(RecordOutputFieldsView *source, int *word, float *third, float *fourth, float *second) {
    *word = source->outputWord;
    *second = source->secondScalar;
    *third = source->thirdScalar;
    *fourth = source->fourthScalar;
}

#if defined(VERSION_US)
/** Perform no operation. */
void SetN64_EmptyFrameDirectionHookUs(void) {
}

/** Perform no operation. */
void SetN64_EmptyFrameDirectionHookSecondUs(void) {
}
#endif

#if defined(VERSION_EU)
/** Perform no operation. */
void SetN64_EmptyFrameDirectionHookEu(void) {
}

/** Perform no operation. */
void SetN64_EmptyFrameDirectionHookSecondEu(void) {
}
#endif

/* SETN64_EMPTYSESSIONHOOKDEA.CPP */

#if defined(VERSION_US_REV1)
void SetN64_EmptySessionHookRev1A(void) {
}

void SetN64_EmptySessionHookRev1B(void) {
}

void SetN64_EmptySessionHookRev1C(void) {
}

#endif

#if defined(VERSION_DE)
void SetN64_EmptySessionHookDeA(void) {

}

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */

#endif

#if defined(VERSION_DE)
/** Perform no operation. */
void SetN64_EmptySessionHookDeB(void) {
}
#endif

/* SETN64_SETUPLOADINGBACKDROP.CPP */

#if defined(VERSION_DE)
/* Sets up the loading-screen scene: resets the camera globals, loads the 0xE10 resource, builds a
 * look-at matrix from the state's backdrop yaw field scaled by g_backdropYawRate, links it to the active view and
 * draws the backdrop through SetN64_DrawTextLines with half the video height. */


void SetN64_SetupLoadingBackdrop(TimedSessionTransitionView *state) {
    s32 handle, h2;
    u8 matrix[64];

    g_geometryFogEffectEnabled = 0;
    handle = Scene_FindModelIdIndex(&g_world, 3600);
    g_menuModelFillEnabled = 0;
    g_menuModelFillColor[0] = g_backdropModelFillValue;
    g_menuModelFillColor[1] = g_backdropModelFillValue;
    g_menuModelFillColor[2] = g_backdropModelFillValue;
    g_menuModelFillColor[3] = g_backdropModelFillValue;
    if (handle != -1) {
        Camera_SetupViewportAndFog(&g_fallbackScreenMessageEmitter);
        Graphu64_BuildTranslationMatrix(matrix, 0.0f, -100.0f, -500.0f);
        YawMatrixLocal(matrix, state->transitionTimer * g_backdropYawRate);
        SwapMatrixUpForward(matrix);
        Graphu64_ConvertMatrixToFixed(matrix, VIEW_MATRICES + g_lightingBufferIndex * 64);
        h2 = Scene_GetIndexedModelResource(&g_world, handle);
        Geometry_BeginModelBatch();
        Geometry_QueueDirectModel(h2, VIEW_MATRICES + g_lightingBufferIndex * 64, &g_defaultParticleLighting, 0, -1);
        Geometry_FlushModelBatch();
        SetN64_DrawTextLines(state, 0, (void *)g_backdropTextLinesDe, g_hudReferenceViewportWidth / 2, 190, 10, g_backdropTextScalePair, (&g_backdropTextScalePair)[1]);
    }
}
#endif

/* SETN64_DRAWFULLSCREENBACKDROP.CPP */

/* Clears the screen: clears the depth buffer over the whole screen through SetN64_ClearDepthRect, emits a full-screen scissor, the frame's colour image, fill cycle, combiner, no-op render mode, fill colour 0x10001 and a full-screen fill rectangle, then, when image 0x386 has a size, draws it stretched across the screen through OnScreen_DrawSpriteResource after Onscrn_SetupSpriteMode_Setn64Drawfullscreenbackdrop(255). Written with libultra-style display-list macros and the screen size read from g_hudReferenceViewportWidth and g_hudReferenceViewportHeight. */

void SetN64_DrawFullscreenBackdrop(void *session) {
    Frame *frame = g_gameSession.ring.current;
    s32 width;
    s32 height;
    SetN64_ClearDepthRect(session, 0, SCREEN_WD, 0, SCREEN_HT, 0);
    width = 0;
    height = 0;
    gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
    gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, (u32)((frame->colorImage)));
    gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
    gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE);
    gDPSetRenderMode(g_displayListCursor++, ((0)), 0);
    gDPSetFillColor(g_displayListCursor++, ((0x10001)));
    gDPFillRectangle(g_displayListCursor++, 0, 0, (SCREEN_WD), (SCREEN_HT));
    OnScreen_GetImageDimensions(902, 0, &width, &height);
    if (width != 0 && height != 0) {
        Onscrn_SetupSpriteMode(0xFF);
        OnScreen_DrawSpriteResource(902, 0, 0, 0, (f32)SCREEN_WD / (f32)width, (f32)SCREEN_HT / (f32)height, 1);
    }
}

/* SETN64_DRAWCREDITSLINES.CPP */

/* Draws the scrolling text lines from the current line index, fading each in with alpha sixteen times its distance below the top edge (capped at 255) and spacing lines ten 222ths of the screen height apart until past the bottom; the top edge is a zero-valued local, which keeps 0.0f in one saved register as the cartridge does. */

void SetN64_DrawCreditsLines(void) {
    s32 line;
    f32 y;
    char *text;
    f32 fade;
    s32 alpha;
    f32 top;

    top = 0.0f;
    line = g_creditsCurrentLine;
    y = g_creditsScrollPosition;
    OnScreen_SetupTextRendering();
    OnScreen_LoadTextTileModeTwo();
    OnScreen_SetTextScale(1.0f, 1.0f);
    do {
        #if defined(VERSION_EU) || defined(VERSION_EU_X)
        text = g_creditsLocalizedLines[g_gameSettings.language][line];
#else
        text = g_creditsLocalizedLines[0][line];
#endif
        if (text != 0) {
            fade = top;
            if (!(y < top)) {
                if (!(16.0f < y)) {
                    if (!(y < top)) {
                        fade = y * 16.0f;
                    }
                } else {
                    fade = 256.0f;
                }
            }
            if (fade > 255.0f) {
                fade = 255.0f;
            }
            alpha = fade;
            OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, alpha, alpha, alpha);
            if (y >= top) {
                OnScreen_DrawTextWithShadow(text, (f32)(g_hudReferenceViewportWidth * 14 / 284), (f32)(s32)y,
                              g_hudReferenceViewportWidth * 0.0028169013f, g_hudReferenceViewportHeight * 0.0045045046f, 1, alpha,
                              g_creditsTextDrawingEnabled);
            }
            line++;
        }
        y += g_hudReferenceViewportHeight * 0.045045048f;
    } while (y <= g_hudReferenceViewportHeight);
}

/* CCREDITS_UPDATESCROLL.CPP */

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))



void CCredits_UpdateScroll(void *session) {
    f32 remainingTime;
    f32 scrollBoundary;
    s32 nextLine;

    if (g_creditsSkipRequested != 0) {
        remainingTime = g_creditsLineTimer - g_frameElapsedTime;
        g_creditsLineTimer = remainingTime;
        if (remainingTime <= 0.0f) {
            Playerai_GetFirstPlayer(&g_playerViewRenderContext);
            if (g_creditsSelectSpawnOnExit != 0) {
                if (g_creditsReturnToFrontend == 0) {
                    SetN64_SelectSpawnAfterCredits(session, 1999);
                    return;
                }
                goto block_6;
            }
            if (g_creditsReturnToFrontend != 0) {
block_6:
                SetN64_SetTransitionTarget(session, 1);
                g_gameSettings.counters.m_bCreditsSeenOnce = 1;
            }
        }
    } else {
        if (g_hudReferenceViewportHeight >= 223) {
            g_creditsScrollPosition -= g_creditsNormalScrollStep;
        } else {
            g_creditsScrollPosition -= g_creditsFastScrollStep;
        }
        scrollBoundary = (f32)g_hudReferenceViewportHeight * g_creditsViewportHeightScale;
        if (g_creditsScrollPosition <= -scrollBoundary) {
            nextLine = g_creditsCurrentLine + 1;
            g_creditsCurrentLine = nextLine;
            g_creditsScrollPosition += scrollBoundary;
            if (g_creditsLocalizedLines[0][nextLine] == 0) {
                g_creditsSkipRequested = 1;
                g_creditsLineTimer = g_creditsNextLineDelay;
            }
        }
    }
}
#endif

/* SETN64.CPP */

void SetN64_InitFrameRing(RenderState *state) {
    u32 i, count, previous, next;
    CGameStatus *counters;
    Frame *view;
    osCreateMesgQueue(&g_gameSchedulerMessageQueue, (s32)g_gameSchedulerMessages, 4096);
    XPlus_FillMemory((char *)g_schedulerThreadStack, 7, 0x2000);
    Sched_InitializeSchedulerThread((void *)&g_systemScheduler, (s32)((char *)g_schedulerThreadStack + 0x2000), g_schedulerThreadPriority, 0, 1);
    osScAddClient(&g_systemScheduler, &g_gameSchedulerClient, &g_gameSchedulerMessageQueue);
    state->handle = -1;
    SetN64_BeginSessionFadeIn(state);
    g_displayListCursor = 0;
    guMtxIdent((void *)&g_skyEffectProjectionMatrix);
    if (g_systemBootMarkerComparison) {
        Control_ResetActorSnapshot();
        Items_ResetGameOptions(&g_gameSettings);
    }
    i = 0;
    CCinema_ResetSequenceContext();
    Match_InitParticleQuad();
    Ovlgame_InitializeRenderDirection(&state->settings);
    count = g_renderFrameBufferCount;
    state->transitionBlocked = 0;
    state->enabled = 1;
    state->reservedTransitionState = 0;
    state->clockPaused = 0;
    counters = &g_gameSettings.counters;
    counters->first = 0;
    counters->m_bCreditsSeenOnce = 0;
    view = state->ring.views;
    if (count) do {
        previous = count - 1;
        previous = (i + previous) % count;
        next = count + 1;
        next = (i + next) % count;
        view->done.type = 2;
        view->colorImage = g_colorImageBuffers[i];

        view->previous = &state->ring.views[previous];
        view->next = &state->ring.views[next];
        SetN64_ClearFrameDirection(view++);
        ++i;
        count = g_renderFrameBufferCount;

    } while (i < count);
    SetN64_AdvanceDisplayFrame(&state->ring.display);
    SoundElement_InitializeContext();
}

/* the render buffer record */


/* The game settings record and its round counters. */
static inline Shared_Game *currentGame(void) {
    return &g_gameSettings;
}
static inline CGameStatus *gameStatus(void) {
    return &g_gameSettings.counters;
}
/* Main game thread: brings up video and the overlays, clears the frame buffers, starts the menu and
   player state, then serves the scheduler's messages forever. */
void SetN64_RunGameLoop(GameSession *session) {
    u32 i;
    s16 *msg;
    Audiomgr_InitHeap();
#if defined(VERSION_EU)
    System_CreateVideoManagerEu(254);
#else
    System_CreateVideoManager(254);
#endif
    osViBlack(1);
#if defined(VERSION_US) || defined(VERSION_US_REV1)
    if (g_consoleTvType != 1 && g_consoleTvType != 2) {
#else
    if (g_consoleTvType != 0) {
#endif
        for (;;) {
        }
    }
    Note_ClearRenderRecord(&g_renderResourceRecord);
    Note_AllocateRenderBuffers(&g_renderResourceRecord);
    osViSwapBuffer((s32)g_colorImageBuffers[0]);
    osViBlack(0);
    if (g_consoleTvType == 0) {
        g_displayedFramebufferAndRefreshRate[1] = 50.0f;
    } else {
        g_displayedFramebufferAndRefreshRate[1] = 60.0f;
    }
    g_gameSchedulerMessage = 0;
    g_gameModeTransitionFrames = 2;
    g_schedulerRetracesSinceSwap = 0;
    g_lastFrameRetraceCount = 0;
    g_previousFrameRetraceCount = 0;
    g_secondPreviousFrameRetraceCount = 0;
    g_thirdPreviousFrameRetraceCount = 0;
    g_schedulerSwapPending = 0;
    g_schedulerFrameQueueWriteIndex = 0;
    g_schedulerQueuedFrameCount = 0;
    g_schedulerFrameQueueReadIndex = 0;
    g_displayedFramebufferAndRefreshRate[0] = 0.0f;
    g_schedulerPendingFramebuffer = 0;
    SetN64_InitFrameRing((RenderState *)session);
#if defined(VERSION_US_REV1)
    Libultra_SetDebugLinkCallback(Tengine_QueryArtsendOverride);
    osSendMesg((OSMesgQueue *)g_debugLinkNotificationQueue, (OSMesg)0xBEEFDEAD, 0);
#endif
    for (i = 0; i < g_renderFrameBufferCount; i++) {
        XPlus_FillMemory(g_colorImageBuffers[i], 0, g_hudReferenceViewportWidth * g_hudReferenceViewportHeight * 2);
    }
    Pools_ResetPlayers(session->players);
    Player_ResetMenuPool(session->menu);
    CCollision_Initialize();
    session->resource = Defs_ReadResourceWord(24) & 0x3FFFFFFF;
    Pools_ResetActorPools(session->players, 0);
    Player_InitializePlayerPool(session->menu, 0, 0);
    Scene_LoadSceneResources(&g_world, session->resource);
    if (g_controllerPresenceBits[0] == 0) {
        Ovlgame_InitializeControllerSession();
    }
    Hud_ResetHudCharTables(&session->hud);
    Note_AllocateScratchBuffer();
    Tsmos_InitFrontendOnce();
    SmXlate_SwitchScreen(2);
    g_frontendEntryState = 3;
    g_pakScanActive = 0;
    g_pakRecheckRequested = 0;
    g_pakRequestLatched = 0;
    g_pakUsable = 1;
    g_pakProbeRequested = 0;
    Control_EnableAllControllerPaks();
    gameStatus()->transitionActive = 0;
    SetN64_BeginModeTransition(session, SESSION_MODE_FRONTEND_START);
    for (;;) {
        Shared_Game *game = currentGame();
        osRecvMesg(&g_gameSchedulerMessageQueue, (OSMesg *)&g_gameSchedulerMessage, 1);
        msg = g_gameSchedulerMessage;
        switch (*msg) {
        case 1:
            SetN64_UpdateGameMode(session);
            break;
        case 2:
            if (msg == &session->ring.frames[0].done.type) {
                g_currentTaskFrame = &session->ring.frames[0];
            } else if (msg == &session->ring.frames[1].done.type) {
                g_currentTaskFrame = &session->ring.frames[1];
            } else if (msg == &session->ring.frames[2].done.type) {
                g_currentTaskFrame = &session->ring.frames[2];
            }
            if (session->mode == 20) {
                g_gameModeTransitionFrames++;
            } else {
                SetN64_UpdateFrameTiming(session);
            }
            /* The ROM keeps only the hoisted &g_gameSettings of this test: the store is dead (the next receive overwrites msg). */
            if (game->flags) {
                msg = 0;
            }
            break;
        case 4:
            g_systemBootMarker[0] = 0;
            Control_ResetControllerProfiles();
            Control_SetControllerMode(0);
            session->fastFade = 1;
            session->transitionBlocked = 1;
            SetN64_SetTransitionTarget(session, 20);
            break;
        }
    }
}



/* Starts the frame display list in the current ring buffer: segment 0, the two setup lists, the depth image, a
 * full-screen viewport (SCREEN_WD x SCREEN_HT) in g_fullScreenViewports_Setn[g_lightingBufferIndex] and a full-screen scissor. */
void SetN64_BeginFrameDisplayList(void *world) {
    UnitVp *viewport;
    g_displayListCursor = g_gameSession.ring.current->commands;
    gSPSegment(g_displayListCursor++, 0, 0);
    gSPDisplayList(g_displayListCursor++, &g_cameraViewDisplayLists[0]);
    gSPDisplayList(g_displayListCursor++, &g_cameraViewDisplayLists[1]);
    viewport = &g_fullScreenViewports[g_lightingBufferIndex];
    gDPSetDepthImage(g_displayListCursor++, g_depthImageBuffer);
    viewport->vscale[0] = SCREEN_WD * 2;
    viewport->vscale[1] = SCREEN_HT * 2;
    viewport->vscale[2] = 1023;
    viewport->vscale[3] = 0;
    viewport->vtrans[0] = SCREEN_WD * 2;
    viewport->vtrans[1] = SCREEN_HT * 2;
    viewport->vtrans[2] = 0;
    viewport->vtrans[3] = 0;
    gSPViewport(g_displayListCursor++, viewport);
    gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
}

/* rspboot text is 0xD0 bytes: it ends where the first graphics microcode text (g_graphicsMicrocodeText) starts. */


/* Fills the frame's graphics task (and the second one when the frame is dual), hands them to the scheduler,
   then advances the ring and gives the next frame the other pair of command buffers. */
void SetN64_SubmitFrameTasks(Display *display, Frame *frame)
{
    OSScTask *task;
    task = &frame->task;
    {
        s32 size, bytes;
        u64 *base;
        task->list.t.data_ptr = (u64 *)frame->commands;
        bytes = frame->commandBytes;
        size = g_graphicsMicrocodeTextSize;
        task->list.t.type = 1;
        task->list.t.ucode_boot = rspbootTextStart;
        base = g_graphicsMicrocodeDataSize;
        task->list.t.ucode_boot_size = RSP_BOOT_TEXT_SIZE;
        task->list.t.ucode_size = 0x1000;
        task->list.t.ucode_data_size = 0x800;
        task->list.t.yield_data_ptr = (u64 *)&g_graphicsTaskYieldBuffer;
        task->list.t.yield_data_size = 3072;
        task->list.t.ucode = (u64 *)g_graphicsMicrocodeText;
        task->list.t.ucode_data = (u64 *)g_graphicsMicrocodeData;
        task->list.t.flags = 0;
        task->list.t.dram_stack = 0;
        task->list.t.dram_stack_size = 0;
        task->list.t.output_buff = base;
        task->list.t.output_buff_size = (u64 *)((u8 *)base + size);
        task->list.t.data_size = bytes;
    }
    frame->task.next = 0;
    task->msgQ = &g_gameSchedulerMessageQueue;
    task->msg = &frame->done;
    task->framebuffer = frame->colorImage;
    if (frame->dual) task->flags = 3; else task->flags = 0x23;
    if (frame->dual) {
        s32 size, bytes;
        u64 *base;
        task = &frame->secondTask;
        task->list.t.data_ptr = (u64 *)frame->secondCommands;
        bytes = frame->secondCommandBytes;
        size = g_graphicsMicrocodeTextSize;
        task->list.t.type = 1;
        task->list.t.ucode_boot = rspbootTextStart;
        base = g_graphicsMicrocodeDataSize;
        task->list.t.ucode_boot_size = RSP_BOOT_TEXT_SIZE;
        task->list.t.ucode_size = 0x1000;
        task->list.t.ucode_data_size = 0x800;
        task->list.t.yield_data_ptr = (u64 *)&g_graphicsTaskYieldBuffer;
        task->list.t.yield_data_size = 3072;
        task->list.t.ucode = (u64 *)g_alternateGraphicsMicrocodeText;
        task->list.t.ucode_data = (u64 *)g_alternateGraphicsMicrocodeData;
        task->list.t.flags = 0;
        task->list.t.dram_stack = 0;
        task->list.t.dram_stack_size = 0;
        task->list.t.output_buff = base;
        task->list.t.output_buff_size = (u64 *)((u8 *)base + size);
        task->list.t.data_size = bytes;
        frame->secondTask.next = 0;
        task->flags = 0x23;
        task->msgQ = &g_gameSchedulerMessageQueue;
        task->msg = &frame->done;
        task->framebuffer = frame->colorImage;
    }
    osWritebackDCacheAll();
    Sched_SendSchedulerTask(&g_systemScheduler, &frame->task);
    if (frame->dual) Sched_SendSchedulerTask(&g_systemScheduler, &frame->secondTask);
    g_gameFrameCounter++;
    g_gameLoopFrameCount++;
    g_lightingBufferIndex ^= 1;
    display->current = &display->frames[g_gameFrameCounter % g_renderFrameBufferCount];
    display->current->commands = g_lightingBufferIndex ? g_displayListBuffers[1] : g_displayListBuffers[0];
    display->current->secondCommands = g_lightingBufferIndex ? g_secondaryDisplayListBufferZero : g_secondaryDisplayListBufferAlternate;
}

/* SETN64_CLEARDEPTHRECT.CPP */

/* Clears the depth buffer over a rectangle: switches the colour image to the depth buffer g_depthImageBuffer in fill mode after setting render mode 0x14 through Geometry_SetModePreset, fills the rectangle with the far depth value (or, for interlaced output, alternate lines with the far value and the remaining lines with 0, by single lines or by line pairs as g_frontendCurrentVideoModeIndex selects), then restores the frame's colour image and one-cycle mode. Written with libultra-style display-list macros. */

void SetN64_ClearDepthRect(void *session, s32 ulx, s32 lrx, s32 uly, s32 lry, s32 interlaced) {
    s32 y;

    gDPPipeSync(g_displayListCursor++);
    Geometry_SetModePreset(20);
    gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_hudReferenceViewportWidth, (u32)((g_depthImageBuffer)));
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
    if (!interlaced) {
        gDPSetFillColor(g_displayListCursor++, ((0xFFFCFFFC)));
        gDPFillRectangle(g_displayListCursor++, (ulx), (uly), (lrx), (lry));
    } else if (g_frontendCurrentVideoModeIndex == 0) {
        gDPSetFillColor(g_displayListCursor++, ((0xFFFCFFFC)));
        for (y = uly; y < lry; y += 2) {
            gDPFillRectangle(g_displayListCursor++, (ulx), (y), (lrx), (y));
        }
        gDPSetFillColor(g_displayListCursor++, ((0)));
        for (y = uly + 1; y < lry; y += 2) {
            gDPFillRectangle(g_displayListCursor++, (ulx), (y), (lrx), (y));
        }
    } else {
        gDPSetFillColor(g_displayListCursor++, ((0xFFFCFFFC)));
        for (y = uly; y < lry; y++) {
            if ((y & 3) < 2) {
                gDPFillRectangle(g_displayListCursor++, (ulx), (y), (lrx), (y));
            }
        }
        gDPSetFillColor(g_displayListCursor++, ((0)));
        for (y = uly; y < lry; y++) {
            if ((y & 3) >= 2) {
                gDPFillRectangle(g_displayListCursor++, (ulx), (y), (lrx), (y));
            }
        }
    }
    gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_hudReferenceViewportWidth, (u32)((g_gameSession.ring.current->colorImage)));
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
}

/* Draw a null-terminated list of scaled strings, with an optional full-screen backdrop. */
void SetN64_DrawTextLines(void *state, s32 drawBackdrop, char **lines, s32 x, s32 y, s32 lineStep, f32 scaleX, f32 scaleY) {
    Frame *frame = g_gameSession.ring.current;
    s32 i;
    char *text;

    y = y * g_hudReferenceViewportHeight / 222;
    if (drawBackdrop) {
        SetN64_ClearDepthRect(state, 0, g_hudReferenceViewportWidth, 0, g_hudReferenceViewportHeight, 0);
        gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, g_hudReferenceViewportWidth - 1, g_hudReferenceViewportHeight - 1);
        gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_hudReferenceViewportWidth, (u32)frame->colorImage);
        gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
        gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE);
        gDPSetRenderMode(g_displayListCursor++, 0, 0);
        gDPSetFillColor(g_displayListCursor++, 0x00010001);
        gDPFillRectangle(g_displayListCursor++, 0, 0, g_hudReferenceViewportWidth, g_hudReferenceViewportHeight);
    }
    OnScreen_SetupTextRendering();
    OnScreen_SetTextColors(0xFF, 0xFF, 0xFF, 200, 200, 200);
    scaleX = scaleX * g_hudReferenceViewportWidth * (1.0f / 284.0f);
    scaleY = scaleY * g_hudReferenceViewportHeight * (1.0f / 222.0f);
    scaleX *= (g_hudReferenceViewportHeight >= 223) ? 0.8f : 0.85f;
    scaleY *= 0.5f;
    OnScreen_SetTextScale(scaleX, scaleY);
    g_gameSession.hud.shadowX = 1;
    g_gameSession.hud.shadowY = 1;
    for (i = 0; lines[i] != 0; i++) {
        text = lines[i];
        Onscrn_DrawText(text, x, y, 0xFF, 1, 1, 1.0f, 1.0f);
        y = y + lineStep * scaleY;
    }
}

/* SETN64_BUILDANDSUBMITSESSIONFRAME.CPP */

/* Builds and submits the current frame, records its timing, and advances the fade transition. */

static __inline__ s32 hasFadeMode(u8 *mode) { return *mode != 0; }
void SetN64_BuildAndSubmitSessionFrame(TimingWorld *world) {
    u8 color[4];
    void (*draw)(TimingWorld *);
    f32 updatedFade;
    f32 fadeLimit;
    f32 fade;
    f32 step;
    f32 speed;
    f32 fadeOutSpeed;
    f32 nextFade;
    f32 elapsed;
    s32 alpha;
    u32 previousMode;
    u32 listBytes;
    u32 maxListBytes;
    u64 start;
    u64 end;
    u64 duration;
    u64 startTime;
    u8 fadeMode;

    start = osGetTime();
    previousMode = (u32) start;
    startTime = start;
    g_currentTaskFrame = g_gameSession.ring.current;
    Cache_SelectResourceSlot(0, g_lightingBufferIndex);
    TextLoad_ResetTextureCache();
    Geometry_InitializeModelRenderState();
    SetN64_BeginFrameDisplayList(world);
    Defs_ToggleSavedFlag();
    Control_TrackControllerPakChanges();
    Camera_UpdateViewportLayoutAndBounds(&world->viewport);
    SetN64_CommitSessionInputs(world);
    draw = g_sessionDrawHandlers[world->currentMode].draw;
    if (draw != 0) {
        draw(world);
    }
    if (g_currentTaskFrame->dual == 0) {
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
        fadeLimit = world->fade;
        alpha = 0xFF;
        if (!(fadeLimit < 0.0f)) {
            alpha = 0;
            if (!(g_sessionFrameFadeLimit < fadeLimit)) {
                alpha = 0xFF;
                if (!(fadeLimit < 0.0f)) {
                    alpha = ~(s32) (fadeLimit * g_sessionFrameFadeAlphaScale);
                }
            }
        }
        color[3] = alpha;
        SetN64_DrawColorRectangle(world, &color[0], 0, 0, g_hudReferenceViewportWidth, g_hudReferenceViewportHeight);
    }
    if (g_selectionMessageStage != 0) {
        if (g_selectionMessageStage == 20) {
            Frontend_AdvanceVideoMode();
        }
        SetN64_ClearDepthRect(world, 0, 480, 0, 360, 0);
        gDPSetScissorFrac(g_displayListCursor++,0,0,0,0x77C,0x59C);
        gDPSetColorImage(g_displayListCursor++,G_IM_FMT_RGBA,G_IM_SIZ_16b,480,g_currentTaskFrame->colorImage);
        gDPSetCycleType(g_displayListCursor++,G_CYC_FILL);
        gDPSetCombineLERP(g_displayListCursor++,0,0,0,SHADE,0,0,0,SHADE,0,0,0,SHADE,0,0,0,SHADE);
        gDPSetRenderMode(g_displayListCursor++,G_RM_NOOP,G_RM_NOOP2);
        gDPSetFillColor(g_displayListCursor++,0x10001);
        gDPFillRectangle(g_displayListCursor++,0,0,480,360);
        g_selectionMessageStage--;
    }
    gDPFullSync(g_displayListCursor++);
    gSPEndDisplayList(g_displayListCursor++);
    maxListBytes = g_maximumDisplayListBytes;
    listBytes = (u8 *)g_displayListCursor - (u8 *)g_currentTaskFrame->commands;
    g_currentTaskFrame->commandBytes = listBytes;
    if (maxListBytes < listBytes) {
        maxListBytes = listBytes;
    }
    g_maximumDisplayListBytes = maxListBytes;
    g_currentTaskFrame->dual = 0;
    g_currentTaskFrame->ticks = (s32) g_frameTimingTicks;
    end = osGetTime();
    duration = ((end - startTime) << 6) / 3;
    elapsed = (f32)duration;
    rwFrameBuildSeconds = elapsed * g_frameBuildTickScale;
    if (Cache_FinishResourceSlot(0) != 0) {
        SetN64_SubmitFrameTasks(world, g_currentTaskFrame);
    } else {
        osSendMesg(&g_gameSchedulerMessageQueue, &g_currentTaskFrame->done, 1);
    }
    if (hasFadeMode(&world->fadeMode)) {
        speed = g_sessionFrameFadeRate;
        if(world->fadeFast) speed = g_sessionFrameFastFadeRate;
        fadeOutSpeed = speed;
        fadeMode = world->fadeMode;
        if (fadeMode != 1) {
            if (fadeMode == 2) {
                fade = world->fade;
                step = 0.0f;
                if (fade > step) {
                    speed = g_frameElapsedTime;
                    updatedFade = fade - (fadeOutSpeed * speed);
                    world->fade = updatedFade;
                    if (updatedFade < step) {
                        world->fade = 0.0f;
                    }
                } else {
                    world->fade = fade - g_sessionFrameFadeHoldStep;
                }
                if (world->fade < g_sessionFrameFadeTransitionThreshold) {
                    previousMode = world->currentMode;
                    world->currentMode = 20;
                    world->fade = 0;
                    world->fadeMode = 1;
                    world->previousMode = previousMode;
                }
            }
        } else {
            step = g_frameElapsedTime;
            fade = world->fade;
            if (step < g_sessionFrameMinimumFadeStep) {
                nextFade = fade + (speed * g_sessionFrameMinimumFadeStep);
            } else {
                nextFade = fade + (speed * step);
            }
            fadeLimit = g_sessionFrameFadeMaximum;
            world->fade = nextFade;
            if (fadeLimit <= nextFade) {
                world->fadeMode = 0;
                world->fade = fadeLimit;
                world->fadeFast = 0;
            }
        }
    }
    CCinema_UpdateSequence();
}

/* SETN64_UPDATEFRAMETIMING.CPP */

static inline u32 averageFour(void) {
 s32 sum;
 s32 maximum;
 sum=g_lastFrameRetraceCount+g_previousFrameRetraceCount+g_secondPreviousFrameRetraceCount+g_thirdPreviousFrameRetraceCount;
 maximum=g_thirdPreviousFrameRetraceCount;
 if((u32)maximum<g_secondPreviousFrameRetraceCount)maximum=g_secondPreviousFrameRetraceCount;
 if((u32)maximum<g_previousFrameRetraceCount)maximum=g_previousFrameRetraceCount;
 if((u32)maximum<g_lastFrameRetraceCount)maximum=g_lastFrameRetraceCount;
 { s32 adjusted=maximum-2; return ((u32)sum-(u32)adjusted)/3; }
}
static inline s32 idlePause(TimingWorld *world) {
 if(Menu_CountLiveNodes(&g_matchEndingTeamWheelClose)==0 && Cinema_IsSequenceInWindow()!=0 && Cinema_GetSequenceRequest()==120) {
 if(g_gameSettings.counters.first==0) {
 if(world->menuNodeCount==0) { g_gameSettings.counters.first=1;Track_RequestCameraRefresh(); }
 goto checkFlag;
 }
 goto active;
 }
 checkFlag:
 if(g_gameSettings.counters.first!=0) {
 active:
 if(Cinema_GetPlaybackPauseState()!=0) return 1;
 }
 return 0;
}
/* Update the frame timestep, render the frame, and advance the session mode. */
void SetN64_UpdateFrameTiming(TimingWorld *world) {
    f32 scaledFrameTime;
    f32 unusedTimingFloat1;
    s32 unusedTimingWord2;
    s32 unusedTimingWord3;
    s32 unusedTimingWord4;
    s32 unusedTimingWord5;
    s32 unusedTimingWord6;
    s32 unusedTimingWord7;
    s32 unusedTimingWord8;
    s32 unusedTimingWord9;
    s32 idle;
    u32 unusedTimingWord10;
    u32 unusedTimingWord11;
    u32 unusedTimingWord12;
    u32 sessionMode;
    u32 unusedTimingWord13;
    u32 unusedTimingWord14;
    u32 unusedTimingWord15;
    u32 unusedTimingWord16;
    u32 unusedTimingWord17;
    u32 unusedTimingWord18;
    u64 nowTicks;
    u64 elapsedUnits;
    u64 unusedTimingTicks19;

    nowTicks = osGetTime();
    elapsedUnits = __udivdi3((nowTicks-g_previousFrameSystemTime)<<6,3000);
#if defined(VERSION_DE)
    scaledFrameTime = (f32)elapsedUnits * g_systemTimeFrameScale * g_systemTimeFrameRateDe;
#else
    scaledFrameTime = (f32)elapsedUnits * g_systemTimeFrameScale * g_systemTimeFrameRate;
#endif
    g_previousFrameSystemTime = nowTicks;
    if (Tsmos_IsFrontendActive() == 0) {
        if (SetN64_IsModeThirteen() == 0) {
            world->menuNodeCount = 0;
        } else {
            world->menuNodeCount = Menu_CountLiveNodes(&world->viewport.self.messageList.head);
        }
    }
    if (g_initialMatchStartPending != 0) {
        sessionMode = world->currentMode;
        if (sessionMode == 11) {
            world->menuNodeCount = 1;
            goto block_10;
        }
    } else {
block_10:
        sessionMode = world->currentMode;
    }
 switch(sessionMode) { case 1: case 3: case 4: {
 g_frameTimingTicks=averageFour()>1 ? averageFour():2;
 break; } default: {
 g_frameTimingTicks=averageFour()>1 ? averageFour():2;
 if(Cinema_IsSequenceInWindow()!=0) {
 if((u32)(world->currentMode-16)<2 && g_hudReferenceViewportHeight<223) {
 g_frameTimingTicks=averageFour()>1 ? averageFour():2;
 } else {
 g_frameTimingTicks=averageFour()>3 ? averageFour():4;
 }
 }
 }
 }
    g_frameElapsedTime = (f32) (g_frameTimingTicks * 15) / g_displayedFramebufferAndRefreshRate[1];
    if (Cinema_IsSequenceInWindow() != 0) {
        g_frameElapsedTime = scaledFrameTime;
    }
#if defined(VERSION_DE)
    if (Cinema_IsSequenceInWindow() != 0) {
        g_frameElapsedTime = g_frameElapsedTime * g_systemTimeFrameRate;
    }
#endif
    Cache_RunCompactionPasses(0);
    g_currentTaskFrame = g_gameSession.ring.current;
    SetN64_BuildAndSubmitSessionFrame(world);
    world->elapsedTime = world->elapsedTime + g_frameElapsedTime;
    SetN64_AdvanceGameClock(world);
    idle=idlePause(world);
    if ((idle != 0) && (world->currentMode != 16) && (world->pendingMode != 16)) {
        world->fadeMode = 2;
        world->pendingMode = 16;
    }
}

/* SETN64_STARTSESSIONTHREADS.CPP */

void SetN64_StartSessionThreads(void) {
    SetN64_StartBootstrapThread();
}

/* SETN64_ADVANCEDISPLAYFRAME.CPP */

/* Advances the frame ring and alternates the color and depth buffer pointers for the next frame. */

void SetN64_StartBootstrapThread(void) {
    XPlus_FillMemory((s32)g_bootstrapThreadStack, 0, 128);
    osCreateThread((s32)g_bootstrapThread, 0, addrLow_SetN64_RunBootstrapThread, 0, (s32)((char *)g_bootstrapThreadStack + 0x80), g_bootstrapThreadPriority);
    osStartThread(g_bootstrapThread);
}

void SetN64_StartGameThreadAndIdle(s32 *gameSession, s32 threadArgument) {
    XPlus_FillMemory((s32)g_gameThreadStack, 1, 0x8000);
    osCreateThread((s32)g_gameThread, 1, addrLow_SetN64_RunGameThread, threadArgument, (s32)g_schedulerThreadStack, g_gameThreadPriority);
    osStartThread(g_gameThread);
    {
        s32 schedulingPriority = g_videoFrameSchedulingMode;
        ((GameSession *)gameSession)->enabled = 0;
        osSetThreadPri(0, schedulingPriority);
    }
loop_1:
    goto loop_1;
}

void SetN64_AdvanceDisplayFrame(Display *display) {
 unsigned int index; Frame *frame;
 index=++g_gameFrameCounter%g_renderFrameBufferCount;
 g_gameLoopFrameCount++;
 g_lightingBufferIndex^=1;
 display->current=&display->frames[index];
 display->current->commands = g_lightingBufferIndex ? g_displayListBuffers[1] : g_displayListBuffers[0];
 frame = display->current;
 frame->secondCommands = g_lightingBufferIndex ? g_secondaryDisplayListBufferZero : g_secondaryDisplayListBufferAlternate;
}

/* SETN64_DRAWCOLORRECTANGLE.CPP */




void SetN64_DrawColorRectangle(void *session, u8 *color, s32 left, s32 top, s32 right, s32 bottom) {
    if (color[3] != 0) {
        gDPPipeSync(g_displayListCursor++);
        gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
        Geometry_SetModePreset(19);
        Geometry_SetCombineMode(25);
        gDPSetPrimColor(g_displayListCursor++, 255, 255, color[0], color[1], color[2], color[3]);
        {
            Gfx *cmd = g_displayListCursor++;
            s32 x, y, x0, y0;
            u32 high, low, high0;
            x = right;
            if (x < 0) x = 0;
            y = bottom;
            high = _SHIFTL(x,14,10);
            if (y < 0) y = 0;
            low = _SHIFTL(y,2,10) | _SHIFTL(G_FILLRECT,24,8);
            cmd->words.w0 = high | low;
            x0 = left;
            if (x0 < 0) x0 = 0;
            y0 = top;
            high0 = _SHIFTL(x0,14,10);
            if (y0 < 0) y0 = 0;
            cmd->words.w1 = high0 | _SHIFTL(y0,2,10);
        }
    }
}

/** Thin wrapper around Control_CommitControllerInputs. */
void SetN64_CommitSessionInputs(void *session) {
    Control_CommitControllerInputs();
}

void SetN64_SelectSpawnAndStartSession(GameSession *gameSession, s32 target) {
    Shared_Placed spawn;
    s32 selectionValues;

    selectionValues = target;
    if (Scene_FindPlacedObjectsByKey(&g_world, -1, selectionValues, &spawn, 1) == 0) {
        selectionValues = 0;
    }
    g_gameSettings.counters.m_GameTimeFifteenth = 0;
    g_gameSettings.counters.m_GameTimeSeconds = 0;
    g_gameSettings.counters.m_GameTimeMinutes = 0;
    g_gameSettings.counters.m_GameTimeHours = 0;
    g_gameSettings.counters.first = 0;
    gameSession->phase = 2;
    gameSession->selector = selectionValues;
    gameSession->selectionActive = 1;
    gameSession->target = SESSION_MODE_ROUND;
}

void SetN64_ResetSessionPlayerPools(GameSession *owner, s32 count, s32 forceActive) {
    Pools_ResetActorPools(owner->players, count);
    Player_InitializePlayerPool(owner->menu, count, forceActive);
}

/* SETN64_UPDATEFADETRANSITION.CPP */















void SetN64_DrawSessionFade(struct GameSession *session) {
    s8 color[4];
    f32 value;
    s32 alpha;

    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    value = session->timer;
    alpha = 0xFF;
    if (!(value < 0)) {
        alpha = 0;
        if (!((&g_systemTimeFrameRate)[1] < value)) {
            alpha = 0xFF;
            if (!(value < 0)) {
                alpha = ~(s32)(value * g_sessionFadeAlphaScale);
            }
        }
    }
    color[3] = alpha;
    SetN64_DrawColorRectangle(session, color, 0, 0, SCREEN_WD, SCREEN_HT);
}

/* Compares two byte strings lexicographically, returning -1 for either null pointer. */
int SetN64_CompareByteStrings(u8 *a, u8 *b) {
 if (!a || !b) return -1;
 while (*a && *b) {
  if (*a < *b) return -1;
  if (*a > *b) return 1;
  a++; b++;
 }
 if (*a) return 1;
 if (*b) return -1;
 return 0;
}

u8 *SetN64_CopyString(u8 *destination, u8 *source)
{
  u8 *readCursor;
  u8 *writeCursor;
  u8 firstByte;
  u8 copiedByte;
 do { firstByte = *source; readCursor = source + 1; } while (0);
  *destination = firstByte;
  writeCursor = destination - -1;
  if (firstByte & 0xFF)
  {
    do
    {
      copiedByte = *readCursor;
      readCursor += 1;
      *writeCursor = copiedByte;
      writeCursor += 1;
    }
    while (copiedByte & 0xFF);
  }
  return destination;
}

int SetN64_IsModeThirteen(void) {
    return g_gameSession.mode == 13;
}

void SetN64_RunBootstrapThread(s32 threadArgument) {
    SetN64_StartGameThreadAndIdle(&g_gameSession, threadArgument);
}

void SetN64_RunGameThread(void) {
    Libc_FormatString(g_buildVersionTextBuffer, g_buildVersionFormat, g_buildTimestampText, g_buildVersionSuffix);
    __osSetFpcCsr(__osGetFpcCsr() | 0x400);
    SetN64_RunGameLoop(&g_gameSession);
}

/** Reset three large-offset fields and mark the record active. */
void SetN64_BeginSessionFadeIn(struct GameSession *gameSession) {
    gameSession->phase = 1;
    gameSession->timer = 0;
    gameSession->fastFade = 0;
}

/* Steps the session's screen fade by the frame time g_frameElapsedTime (fastFade picks the fast rate). Phase 2 fades out: the
 * timer falls to zero, then keeps counting below it until -4 before the session switches to mode 0x14 and fades back
 * in. Phase 1 fades in, at least half the rate per frame, until the timer reaches one. */
void SetN64_UpdateFadeTransition(GameSession *session) {
    f32 step;
    f32 rate;
    f32 timer;
    f32 next;

    if (session->phase == 0) {
        return;
    }
    step = 0.1f;
    if (session->fastFade != 0) {
        step = 0.5f;
    }
    rate = step;
    switch (session->phase) {
    case 2:
        timer = session->timer;
        if (timer > 0.0f) {
            step = g_frameElapsedTime;
            next = timer - rate * step;
            session->timer = next;
            if (next < 0.0f) {
                session->timer = 0.0f;
            }
        } else {
            session->timer = timer - 1.0f;
        }
        if (session->timer < -4.0f) {
            s32 saved = session->mode;
            session->mode = SESSION_MODE_TRANSITION;
            session->timer = 0.0f;
            session->phase = 1;
            session->previousMode = saved;
        }
        break;
    case 1:
        timer = session->timer;
        if (g_frameElapsedTime < 0.5f) {
            next = timer + step * 0.5f;
        } else {
            next = timer + step * g_frameElapsedTime;
        }
        session->timer = next;
        if (next >= 1.0f) {
            session->phase = 0;
            session->timer = 1.0f;
            session->fastFade = 0;
        }
        break;
    }
}

/* SETN64_UPDATEGAMEMODE.CPP */

void SetN64_BeginModeTransition(GameSession *session, s32 targetMode) {
    s32 saved;

    saved = session->mode;
    session->phase = 1;
    session->timer = 0;
    session->mode = SESSION_MODE_TRANSITION;
    session->target = targetMode;
    session->previousMode = saved;
    if (Control_IsSnapshotActive() != 0) {
        session->timer = g_snapshotModeTransitionTimer;
    }
}

/** Set the state byte and linked value in a large object. */
void SetN64_SetTransitionTarget(GameSession *object, int value) {
    object->phase = 2;
    object->target = value;
}

typedef void (*SessionUpdateHandler)(void *);

void SetN64_UpdateGameMode(GameSession *session) {
    s32 field;
    SessionUpdateHandler fn;

    if (g_sessionUpdateResetFlag != 0) {
        g_sessionUpdateResetFlag = 0;
    }
    Control_TickSnapshotCountdown();
    field = (session)->mode;
    fn = ((SessionHandlerRow *)g_sessionUpdateHandlers)[field].update;
    if (fn != 0) {
        fn(session);
        field = (session)->mode;
    }
    if (field != 20 && g_gameModeTransitionFrames != 0) {
        g_gameModeTransitionFrames -= 1;
        SetN64_UpdateFrameTiming(session);
    }
    g_sessionUpdateCount += 1;
}

s32 SetN64_CheckTimedSessionTransition(TimedSessionTransitionView *session, f32 duration, s32 eight, s32 inputTargetMode) {
    s32 *flag = (s32 *)&g_combinedControllerProfile.pressedButtons;

    if ((*flag != 0) && (inputTargetMode != -1)) {
        session->transitionPhase = 2;
        session->transitionTarget = inputTargetMode;
        *flag = 0;
        return 1;
    }
    if ((duration * g_timedTransitionDurationScale) < session->transitionTimer) {
        session->transitionPhase = 2;
        session->transitionTarget = eight;
        return 1;
    }
    return 0;
}

/* SETN64_RESETPLAYERITEMS.CPP */









void SetN64_ResetPlayerItems(s32 sessionAddress, s32 selectionKey) {
    SessionPlayerItemResetView *object = (void *)sessionAddress;
    Pools_ResetActorPools(&object->actorPools, 1);
    Player_InitializePlayerPool(&object->playerPool, (void *)1, 0);
    Scene_SetSelection(&g_world, ~Track_RequestTrackByKey(selectionKey), 0);
    Scene_LoadPreviewBufferA(&g_world);
    Scene_LoadPreviewBufferB(&g_world);
}

/* SETN64_DRAWSESSIONWITHATTRACTTIMEOUT.CPP */

/* Requests a switch of the session into mode 0x14: when the pending 0x1000 flag is set outside modes 0xB and 0xC and a target is given it records that target with phase 2 and clears the flags; otherwise, once Cinema_IsSequenceIdle accepts the flags, it saves the current mode, enters mode 0x14 with the given argument at phase 1, and sets the timer when Control_IsSnapshotActive_Camera allows. */

void SetN64_HandleSessionTransitionInput(GameSession *session, s32 cancelTarget, s32 target) {
    s32 pending;
    s32 *flags;

    flags = (s32 *)&g_combinedControllerProfile.pressedButtons;
    pending = *flags & 0x1000;
    if ((unsigned)(session->mode - 11) < 2) {
        pending = 0;
    }
    if (pending != 0 && target != -1) {
        session->phase = 2;
        session->target = target;
        *flags = 0;
        return;
    }
    if (Cinema_IsSequenceIdle() != 0) {
        s32 mode = session->mode;

        session->phase = 1;
        session->timer = 0;
        session->mode = SESSION_MODE_TRANSITION;
        session->target = cancelTarget;
        session->previousMode = mode;
        if (Control_IsSnapshotActive() != 0) {
            session->timer = (1.0f);
        }
    }
}

/* Calls cleanup functions on a game state and optionally transitions control state when conditions change. */

void SetN64_DrawSessionWithAttractTimeout(void *session) {
    GameSession *state;
    f32 value;

    state = session;
    if (g_attractTimeoutEnabled == 1) {
        value = state->transitionTime;
        if (g_attractTimeoutBegin < value) {
            if (g_attractTimeoutFinish < value) {
                g_attractTimeoutEnabled = 0;

#if defined(VERSION_EU)
Tsmos_InitializeEuropeanFrontend
#else
InitFrontendMenus
#endif
();
                SmXlate_SwitchScreen(2);
                Frontend_RequestScreenMode(0);
                SetN64_BeginModeTransition(state, SESSION_MODE_INTRO);
                state->transitionTime = 0;
            } else if (g_combinedControllerProfile.buttons != 0) {
                g_attractTimeoutEnabled = 0;

#if defined(VERSION_EU)
Tsmos_InitializeEuropeanFrontend
#else
InitFrontendMenus
#endif
();
                SmXlate_SwitchScreen(2);
                SetN64_BeginModeTransition(state, SESSION_MODE_MAIN_MENU);
                state->transitionTime = 0;
            }
        }
    }
    Scene_UpdateAndDrawWorld(&state->world);
    Gsky_DrawPlayerListNoOp();
    OnScreen_DrawStatusBars(&state->hud);
    /* Only us-rev1 makes this call: us, eu, eu-x and de go straight on to SetN64_DrawSessionFade, two
       instructions shorter, as each cartridge's own bytes show. */
#ifdef VERSION_US_REV1
    Tengine_UpdateArtsendTexturePreview();
#endif
    SetN64_DrawSessionFade(state);
}


void SetN64_AdvanceGameClock(GameSession *world) {
    f32 t1;
    f32 t2;
    f32 t3;

    if (world->clockPaused == 0) {
        t1 = g_gameSettings.counters.m_GameTimeFifteenth + g_frameElapsedTime;
        g_gameSettings.counters.m_GameTimeFifteenth = t1;
        if (g_gameClockTickRate <= t1) {
            t2 = g_gameSettings.counters.m_GameTimeSeconds + g_gameClockUnitIncrement;
            g_gameSettings.counters.m_GameTimeFifteenth = t1 - g_gameClockTickRate;
            g_gameSettings.counters.m_GameTimeSeconds = t2;
            if (g_gameClockSecondsPerMinute <= t2) {
                t3 = g_gameSettings.counters.m_GameTimeMinutes + g_gameClockUnitIncrement;
                g_gameSettings.counters.m_GameTimeSeconds = t2 - g_gameClockSecondsPerMinute;
                g_gameSettings.counters.m_GameTimeMinutes = t3;
                if (g_gameClockSecondsPerMinute <= t3) {
                    g_gameSettings.counters.m_GameTimeMinutes = t3 - g_gameClockSecondsPerMinute;
                    g_gameSettings.counters.m_GameTimeHours = g_gameSettings.counters.m_GameTimeHours + g_gameClockUnitIncrement;
                }
            }
        }
    }
}


void SetN64_DrawSessionWithRoundTimeout(GameSession *session) {
    CGameStatus *counters = &g_gameSettings.counters;
    f32 time;
    if (counters->transitionActive == 1) {
        time = session->transitionTime;
        if (g_roundTimeoutBegin < time) {
            if (g_roundTimeoutFinish < time) {
                counters->transitionActive = 0;
                stopRoundPlatform();
                SmXlate_SwitchScreen(2);
                Frontend_RequestScreenMode(0);
                SetN64_BeginModeTransition(session, SESSION_MODE_INTRO);
                session->transitionTime = 0;
            } else if (g_combinedControllerProfile.buttons != 0) {
                counters->transitionActive = 0;
                stopRoundPlatform();
                SmXlate_SwitchScreen(2);
                SetN64_BeginModeTransition(session, SESSION_MODE_MAIN_MENU);
                session->transitionTime = 0;
            }
        }
    }
    Scene_UpdateAndDrawWorld(&session->world);
    Gsky_DrawPlayerListNoOp();
    OnScreen_DrawStatusBars(&session->hud);
#ifdef VERSION_US_REV1
    Tengine_UpdateArtsendTexturePreview();
#endif
    SetN64_DrawSessionFade(session);
}

/* SETN64_DRAWINTROBACKDROP.CPP */


/* Emits a set-color-image display list command for the current frame buffer, then draws image 0x388
 * scaled to fill the screen dimensions over the image's returned width and height, when both are nonzero. */



/* Clears g_expansionMemoryIntroEnabled when SetN64_CheckTimedSessionTransition accepts its argument with 4.0 and two fours. */

/** Perform no work for callers. */
void SetN64_OnOpeningCinemaDrawn(s32 session) {
}

void SetN64_InitializeFrontendScreenState(GameSession *gameSession) {
    g_introSelectedItem = -1;
    g_introSelectionState = 0;
    Frontend_RequestScreenMode(0);
    g_frontendScreenInitialized = 1;
    g_pakRequestLatched = 1;
    g_pakStartButtonLatched = 1;
    g_pakScanActive = 0;
    gameSession->timer = g_introInitialFadeTimer;
    SmXlate_SwitchScreen(29);
}

void SetN64_ExitSessionAndDisablePaks(void *session) {
    if (g_pakRecheckRequested != 0) {
        SetN64_SetTransitionTarget(session, 1);
        Control_DisableAllControllerPaks();
    }
}

/** Thin wrapper around SetN64_DrawSessionWithRoundTimeout. */
void SetN64_DrawRoundTimeoutSession(GameSession *session) {
    SetN64_DrawSessionWithRoundTimeout(session);
}

void SetN64_ResetSceneForIntro(void *owner) {
    s8 *menuDataBase;
    IntroBackdropStateView *menuObjectBase;
    int memoryBytes;

    SoundElement_SetMusicPlaybackEnabled(0);
    memoryBytes = 1496;
    menuDataBase = ((s8 *)(&g_matchRoundCounters)) - memoryBytes;
    ((struct IntegerStateB0 *)((&g_matchRoundCounters)))->transitionActive = 0;
    ((struct IntegerStateB0 *)((&g_matchRoundCounters)))->first = 0;
    menuDataBase[178] = 1;
    menuDataBase[29] = 0;
    menuDataBase[30] = 1;
    SetN64_ResetSessionPlayerPools(owner, 0, 0);
    Scene_LoadLevelResources(&g_world, 0, 0);
    menuObjectBase = ((s8 *)(&g_matchRoundCounters)) - (offsetof(Shared_MenuData, game.counters) - offsetof(Shared_MenuData, object));
    Pools_ResetActorPools(menuObjectBase, 1);
    (menuObjectBase)->poolClearedWord = 0;
    Textload_SetTextureEffect(0);
}

void SetN64_AdvanceIntroForMemorySize(GameSession *session) {
    s32 eight;
    s32 callResult;
    u32 result;

    result = Defs_GetMemorySize();
    eight = 4;
    if ((result > 0x400000U) && (g_expansionMemoryIntroEnabled != 0)) {
        eight = 3;
    }
    if (session->transitionTime > g_introTransitionDelay) {
        g_introExitPending = 0;
    }
    if (g_introExitPending != 0) {
        callResult = SetN64_CheckTimedSessionTransition(session, 12.0f, eight, -1);
    } else {
        callResult = SetN64_CheckTimedSessionTransition(session, 12.0f, eight, eight);
    }
    if (callResult != 0) {
        g_introExitPending = 0;
    }
}

void SetN64_DrawIntroBackdrop(void) {
    s32 width;
    s32 height;
    Gfx *cmd;

    width = 0;
    height = 0;
    gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_hudReferenceViewportWidth, (u32)g_currentRenderFrame->colorImage);
    OnScreen_GetImageDimensions(904, 0, &width, &height);
    if ((width != 0) && (height != 0)) {
        Onscrn_SetupSpriteMode(250);
        OnScreen_DrawSpriteResource(904, 0, 0, 0, (f32)g_hudReferenceViewportWidth / (f32)width, (f32)g_hudReferenceViewportHeight / (f32)height, 1);
    }
}

void SetN64_ClearSessionPlayerPools(void *owner) {
    SetN64_ResetSessionPlayerPools(owner, 0, 0);
}

void SetN64_AdvanceLoadingToSplashImage(struct GameSession *value) {
    if (SetN64_CheckTimedSessionTransition(value, 4.0f, 4, 4) != 0) {
        g_expansionMemoryIntroEnabled = 0;
    }
}

/** Preserve the empty hook. */
void SetN64_InitializeIntroText(void) {
}

void SetN64_AdvanceIntroTextToOpeningCinema(struct GameSession *session)
{
  s32 five;
  five = 5;
  SetN64_CheckTimedSessionTransition(session, 14.0f, five, five);
}

/* SETN64_DRAWCENTEREDINTROTEXT.CPP */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* The EU builds pick the text for the current menu language. */
#define LINES_TEXT g_introTextLinesByLanguage[g_languageIndex]
#else
#define LINES_TEXT g_introTextLines
#endif
void SetN64_DrawCenteredIntroText(void *state) {
    SetN64_DrawTextLines(state, 1, LINES_TEXT, g_hudReferenceViewportWidth / 2, 5, 10, 0.75f, 1.0f);
}

/* Keep this source unit's macros local to its body. */
#undef LINES_TEXT

/* SETN64_DRAWSPLASHIMAGE.CPP */




/* Clears the map-view-active flag, emits a set-color-image display list command for the current frame
 * buffer, then draws image 0x389 scaled to fill the screen dimensions over the image's returned width
 * and height, when both are nonzero. */




void SetN64_ResetSplashImageEffects(void) {
    g_splashImageTextureEffectState = 0;
    Textload_SetTextureEffect(0U);
}

void SetN64_AdvanceSplashImageToMainMenu(struct GameSession *session) {
    s32 eight;
    eight = 8;
    SetN64_CheckTimedSessionTransition(session, 12.0f, eight, eight);
}

void SetN64_DrawSplashImage(void) {
    s32 width;
    s32 height;
    Gfx *cmd;

    g_geometryFogEffectEnabled = 0;
    width = 0;
    height = 0;
    gDPSetColorImage(g_displayListCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, g_hudReferenceViewportWidth, (u32)g_currentRenderFrame->colorImage);
    OnScreen_GetImageDimensions(905, 0, &width, &height);
    if ((width != 0) && (height != 0)) {
        Onscrn_SetupSpriteMode(250);
        OnScreen_DrawSpriteResource(905, 0, 0, 0, (f32)g_hudReferenceViewportWidth / (f32)width, (f32)g_hudReferenceViewportHeight / (f32)height, 1);
    }
}

void SetN64_StartOpeningCinema(s32 sessionAddress) {
    Scene_ResetTransitionViewport();
    ((s32 (*)(s32, s32))SetN64_ResetPlayerItems)(sessionAddress, 90);
}

void SetN64_HandleOpeningCinemaInput(s32 session) {
    SetN64_HandleSessionTransitionInput(session, 7, 7);
}

void SetN64_DrawOpeningCinema(s32 session) {
    SetN64_DrawSessionWithAttractTimeout(session);
    SetN64_OnOpeningCinemaDrawn(session);
}

/** Perform no operation. */
void SetN64_InitializeUnusedModeAfterOpeningCinema(void) {
}

/** Perform no operation. */
void SetN64_UpdateUnusedModeAfterOpeningCinema(void) {
}

/** Perform no operation. */
void SetN64_DrawUnusedModeAfterOpeningCinema(void) {
}

/** Thin wrapper calling SoundElement_SetMusicPlaybackEnabled with a fixed argument. */
void SetN64_StartTitleMusic(void) {
    SoundElement_SetMusicPlaybackEnabled(16);
}

void SetN64_HandleTitleScreenInput(struct GameSession *session) {
    SetN64_CheckTimedSessionTransition(session, 20.0f, 9, 8);
}

void SetN64_InitializeMainMenuScene(void *owner) {
    SetN64_ResetSessionPlayerPools(owner, 0, 0);
    Scene_LoadLevelResources(&g_world, 0, 0);
    g_gameSettings.counters.transitionActive = 0;
    SmXlate_SwitchScreen(24);
    SoundElement_SetMusicPlaybackEnabled(52);
}

void SetN64_UpdateMainMenu(void) {
}

/** Thin wrapper around SetN64_DrawSessionWithRoundTimeout. */
void SetN64_DrawMainMenu(GameSession *session) {
    SetN64_DrawSessionWithRoundTimeout(session);
}


                                                  /* size = 0x18 */

void SetN64_StartAttractCinema(s32 sessionAddress) {
    g_attractCinemaStartCount += 1;
    Scene_ResetTransitionViewport();
    Cinema_SetResponse(0.5f);
    SetN64_ResetPlayerItems(sessionAddress, 111);
}

void SetN64_HandleAttractCinemaInput(s32 session) {
    SetN64_HandleSessionTransitionInput(session, 7, 8);
}

void SetN64_DrawAttractCinema(void *session) {
    SetN64_DrawSessionWithAttractTimeout(session);
}

void SetN64_StartPreRoundCinema(s32 sessionAddress) {
    Scene_ResetTransitionViewport();
    ((s32 (*)(s32, s32))SetN64_ResetPlayerItems)(sessionAddress, 111);
}

/* SETN64_STARTROUND.CPP */



/* Resets the menu viewport and selects the row identified by the owner's current index. */
void SetN64_HandlePreRoundCinemaInput(s32 session) {
    SetN64_HandleSessionTransitionInput(session, 12, 12);
}

void SetN64_DrawPreRoundCinema(void *session) { SetN64_DrawSessionWithAttractTimeout(session); }

void SetN64_StartSkippablePreRoundCinema(s32 sessionAddress) {
    Scene_ResetTransitionViewport();
    ((s32 (*)(s32, s32))SetN64_ResetPlayerItems)(sessionAddress, 111);
}

void SetN64_HandleSkippablePreRoundCinemaInput(s32 session) {
    SetN64_HandleSessionTransitionInput(session, 13, 8);
}

void SetN64_DrawSkippablePreRoundCinema(void *session) { SetN64_DrawSessionWithAttractTimeout(session); }

void SetN64_StartLevelIntroCinema(int sessionAddress) {
    Scene_ResetTransitionViewport();
    SetN64_ResetPlayerItems(sessionAddress, ((RoundSessionItemStateView *)sessionAddress)->selectionKeyBase + 601);
}

void SetN64_HandleLevelIntroCinemaInput(s32 session) {
    SetN64_HandleSessionTransitionInput(session, 13, 13);
}

void SetN64_DrawLevelIntroCinema(void *session) { SetN64_DrawSessionWithAttractTimeout(session); }

void SetN64_ResumeSelectedSession(GameSession *session) {
    void *dst;
    s32 field;
    f32 f;

    g_gameSettings.counters.first = 0;
    g_gameLoopFrameCount = 0;
    SetN64_CommitSessionInputs(session);
    CCollision_Initialize();
#if defined(VERSION_US_REV1)
    TextLoad_ResetArtsendTextureState();
#endif
    dst = &g_world;
#if defined(VERSION_US_REV1)
    f = (1.0f);
#else
    f = (1.0f);
#endif
    field = session->selector;
#if defined(VERSION_US_REV1)
    g_roundStartClearedWord = 0;
#endif
    g_skyRotorSpinScale = f;
    g_roundTimerStep = f;
    g_particleSimulationTimeScale = f;
    Scene_SetSelection(dst, field, 0);
    session->mode = SESSION_MODE_ROUND;
    g_initialMatchStartPending = 0;
}

/* Prepares a session for a new round: clears the round flag, resets the round state, records the round seed when Control_IsSnapshotActive_Camera allows, resets the scoreboard and player slot, restarts the arena with the session's arena setting, resets the camera timers and reloads the session's sound bank and music. */
void SetN64_StartRound(GameSession *session) {
    CGameStatus *counters;
    Shared_Game *game;

    g_gameLoopFrameCount = 0;
    SetN64_CommitSessionInputs(session);
    if (Control_IsSnapshotActive() != 0) {
        session->selector = Control_GetSnapshotActorId();
    }
    counters = &g_gameSettings.counters;
    counters->state = 0;
    counters->m_FragTagSelectionType = 3;
    game = &g_gameSettings;
    game->local = 1;
    game->mode1E = 8;
    SetN64_ResetSessionPlayerPools(session, session->arena, 0);
    if (Control_IsSnapshotActive() != 0) {
        Control_RestoreActorSnapshot();
    }
    CCollision_Initialize();
    resetRoundExtra();
    clearRoundExtra();
    g_skyRotorSpinScale = roundTimerConstant();
    g_roundTimerStep = roundTimerConstant();
    g_particleSimulationTimeScale = roundTimerConstant();
    Scene_InitPreview(&g_world, session->resource);
    Scene_SetSelection(&g_world, session->selector, 0);
}

#if !(defined(VERSION_US_REV1))
const float literals_SetN64_StartRound[1] = {
    1.0f,
};
#endif

/* SETN64_DRAWUNUSEDMODEAFTERRESUME.CPP */

void SetN64_UpdateActiveSession(void) {
}
#if defined(VERSION_US_REV1)
void SetN64_InitializeUnusedModeAfterResume(void) {
}
#endif
#if defined(VERSION_US_REV1)
void SetN64_UpdateUnusedModeAfterResume(void) {
}
#endif
#if defined(VERSION_US_REV1)
void SetN64_DrawUnusedModeAfterResume(void) {
}
#endif

#if !(defined(VERSION_US_REV1))
void SetN64_InitializeUnusedModeAfterResume(void) {
}
#endif

#if !(defined(VERSION_US_REV1))
void SetN64_UpdateUnusedModeAfterResume(void) {
}
#endif

#if !(defined(VERSION_US_REV1))
void SetN64_DrawUnusedModeAfterResume(void) {
}
#endif

/* SETN64_INITIALIZESKIPPABLECREDITSROLL.CPP */
















void SetN64_SelectSpawnAfterCredits(GameSession *scene, s32 spawnIndex) {
    Shared_Placed spawn;
    s32 selectionValues;

    selectionValues = spawnIndex;
    if (Scene_FindPlacedObjectsByKey(&g_world, -1, selectionValues, &spawn, 1) == 0) {
        selectionValues = 0;
    }
    scene->phase = 2;
    scene->selector = selectionValues;
    scene->target = SESSION_MODE_RESUME_ROUND;
}

/* Initializes the game state for a new game phase with sessionAddress as the phase identifier. */
void SetN64_InitializeCreditsRoll(s32 sessionAddress) {
    g_creditsReturnToFrontend = 0;
    g_creditsCurrentLine = 0;
    g_creditsScrollPosition = (f32)(&g_hudReferenceViewportWidth)[1];
    g_creditsSkipRequested = 0;
    Playerai_GetFirstPlayer(&g_playerViewRenderContext);
    g_creditsSelectSpawnOnExit = 0;
    Scene_ResetTransitionViewport();
    SetN64_ResetPlayerItems(sessionAddress, 130);
}

void SetN64_HandleCreditsRollInput(s32 session) {
    s32 *p;

    if (g_creditsReturnToFrontend != 0) {
        SetN64_HandleSessionTransitionInput(session, 1, 1);
        return;
    }
    p = (s32 *)&g_combinedControllerProfile.pressedButtons;
    if ((*p & 0x1000) && (g_creditsSkipRequested == 0)) {
        g_creditsSkipRequested = 1;
        *p = 0;
        g_creditsLineTimer = g_creditsInitialLineTimer;
    }
}

void SetN64_DrawCreditsRoll(s32 session) {
    SetN64_DrawSessionWithAttractTimeout((void *)session);
    SetN64_DrawCreditsLines();
    CCredits_UpdateScroll(session);
}

/* Initializes the game state for a new game phase with sessionAddress and updates the game state flag. */
void SetN64_InitializeSkippableCreditsRoll(s32 sessionAddress) {
    Shared_Game *game = &g_playerViewRenderContext.game;

    game->local = 0;
    g_creditsReturnToFrontend = 0;
    g_creditsCurrentLine = 0;
    g_creditsScrollPosition = (f32)(&g_hudReferenceViewportWidth)[1];
    g_creditsSkipRequested = 0;
    Playerai_GetFirstPlayer(&g_playerViewRenderContext);
    g_creditsSelectSpawnOnExit = 0;
    Scene_ResetTransitionViewport();
    SetN64_ResetPlayerItems(sessionAddress, 130);
    g_creditsReturnToFrontend = 1;
    g_creditsSelectSpawnOnExit = 0;
}

void SetN64_HandleSkippableCreditsRollInput(s32 session) {
    if (g_creditsReturnToFrontend != 0) {
        SetN64_HandleSessionTransitionInput(session, 1, 1);
        return;
    }
    if ((g_creditsControllerButtons & 0x1000) && (g_creditsSkipRequested == 0)) {
        g_creditsSkipRequested = 1;
        g_creditsControllerButtons = 0;
        g_creditsLineTimer = (15.0f);
    }
}

void SetN64_DrawSkippableCreditsRoll(s32 session) {
    SetN64_DrawSessionWithAttractTimeout((void *)session);
    SetN64_DrawCreditsLines();
    CCredits_UpdateScroll(session);
}


/* SETN64_CONFIGUREVIDEOANDENTERMODEUS.CPP */

/** Perform the no-op callback. */
void SetN64_InitializeTransitionMode(void) {
}

#if defined(VERSION_US)
/* View of the screen state that names only the words this step touches. */
typedef struct ScreenModeState {
    u8 unusedBeforeModeWords[0x26DB0];
    s32 modeResetPending;
    u8 unusedBeforeActiveMode[4];
    s32 activeMode;
    s32 requestedMode;
    u8 unusedBeforeVideoModeFlag[0x26DD0 - 0x26DC0];
    s32 videoModeChangeRequested;
} ScreenModeState;
/* Per-frame screen step: when the video mode change flag is set it switches the video mode (label chosen by g_frontendCurrentVideoModeIndex, Y scale from a constant, mode 2); in state 2 of g_gameModeTransitionFrames with that flag clear it latches the requested mode as the active mode, clears the mode reset flag, runs the reset calls and dispatches the 12-byte table row g_screenModeHandlers for that value. */
void SetN64_ConfigureVideoAndEnterModeUs(ScreenModeState *state) {
    void (*handler)(ScreenModeState *);
    s32 mode;
    if (state->videoModeChangeRequested != 0) {
        char *label = g_videoModeDefaultLabel;
        if (g_frontendCurrentVideoModeIndex == 0) {
            label = g_videoModeLabels;
        }
        osViSetMode(label);
        osViSetYScale(1.0f);
        osViSetSpecialFeatures(2);
    }
    if (g_gameModeTransitionFrames == 2 && state->videoModeChangeRequested == 0) {
        mode = state->requestedMode;
        state->modeResetPending = 0;
        state->activeMode = mode;
        Cinema_EndSequence();
        SoundElement_StopAudioExceptKey(-1);
        Control_SetControllerMode(0);
        handler = (void (*)(ScreenModeState *))g_screenModeHandlers[state->activeMode].initialize;
        if (handler != 0) {
            handler(state);
        }
    }
}
#endif

#if !(defined(VERSION_US))

void SetN64_EnterPendingSessionMode(void *gameSession) {
    void (*callback)(void *gameSession);
    s32 index;

    if ((g_gameModeTransitionFrames == 2) &&
        (((struct GameSession *)gameSession)->transitionBlocked == 0)) {
        index = ((struct GameSession *)gameSession)->target;
        ((struct GameSession *)gameSession)->transitionTime = 0;
        ((struct GameSession *)gameSession)->mode = index;
        Cinema_EndSequence();
        SoundElement_StopAudioExceptKey(-1);
        Control_SetControllerMode(0);
        callback = g_sessionInitializeHandlers[((struct GameSession *)gameSession)->mode].callback;
        if (callback != 0) {
            callback(gameSession);
        }
    }
}
#endif

void SetN64_DrawTransitionMode(void) {
}
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_InitializeUnusedModeAfterCredits(void) {
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_UpdateUnusedModeAfterCredits(void) {
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_DrawUnusedModeAfterCredits(void) {
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_InitializeUnusedModeBeforeTransition(void) {
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_UpdateUnusedModeBeforeTransition(void) {
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
void SetN64_DrawUnusedModeBeforeTransition(void) {
}
#endif

#if defined(VERSION_US)
/** Perform no operation. */
void SetN64_EmptyVideoModeHookUs(void) {
}

/** Perform no operation. */
void SetN64_EmptyVideoModeHookSecondUs(void) {
}
#endif

/* SIMPPOOL.CPP */

/* Opens the idle-time prompt when allowed and reports whether the pause input remains active. */


#if defined(VERSION_DE)

s32 Simppool_CheckSequencePromptRequest(struct SequencePromptRequestView *request) {
    s32 unusedInteger1;
    struct Prompt *prompt;

    if ((Menu_CountLiveNodes(&g_matchEndingTeamWheelClose) == 0) && (Cinema_IsSequenceInWindow() != 0)) {
        if (Cinema_GetSequenceRequest() == 120) {
            prompt = &((struct SequencePromptStateView *)&g_matchEndingTeamWheelClose)->prompt;
            if (prompt->opened == 0) {
                if (request->suppressPrompt == 0) {
                    prompt->opened = 1;
                    Track_RequestCameraRefresh();
                }
                goto block_6;
            }
            goto block_7;
        }
    }
block_6:
    if (g_gameSettings.counters.first != 0) {
block_7:
        if (Cinema_GetPlaybackPauseState() != 0) return 1;
    }
    return 0;
}
#endif

struct Context;

#if defined(VERSION_DE)
void Simppool_ResetEffectsAndControllers(void) {
    Rumble_FreeAllPoolNodes(&g_controllerRumblePool);
    Playerai_ResetPlayerControllers(&g_playerViewRenderContext);
}
#endif

/* SETN64_SETUPLOADINGBACKDROP.CPP */

#if defined(VERSION_EU)
/* Sets up the loading-screen scene: resets the camera globals, loads the 0xE10 resource, builds a
 * look-at matrix from the state's backdrop yaw field scaled by g_backdropYawRate, links it to the active view and
 * draws the backdrop through SetN64_DrawTextLines with half the video height. */


void SetN64_SetupLoadingBackdrop(TimedSessionTransitionView *state) {
    s32 handle, h2;
    u8 matrix[64];

    g_geometryFogEffectEnabled = 0;
    handle = Scene_FindModelIdIndex(&g_world, 3600);
    g_menuModelFillEnabled = 0;
    g_menuModelFillColor[0] = g_backdropModelFillValue;
    g_menuModelFillColor[1] = g_backdropModelFillValue;
    g_menuModelFillColor[2] = g_backdropModelFillValue;
    g_menuModelFillColor[3] = g_backdropModelFillValue;
    if (handle != -1) {
        Camera_SetupViewportAndFog(&g_fallbackScreenMessageEmitter);
        Graphu64_BuildTranslationMatrix(matrix, 0.0f, -100.0f, -500.0f);
        YawMatrixLocal(matrix, state->transitionTimer * g_backdropYawRate);
        SwapMatrixUpForward(matrix);
        Graphu64_ConvertMatrixToFixed(matrix, VIEW_MATRICES + g_lightingBufferIndex * 64);
        h2 = Scene_GetIndexedModelResource(&g_world, handle);
        Geometry_BeginModelBatch();
        Geometry_QueueDirectModel(h2, VIEW_MATRICES + g_lightingBufferIndex * 64, &g_defaultParticleLighting, 0, -1);
        Geometry_FlushModelBatch();
        SetN64_DrawTextLines(state, 0, (void *)g_backdropTextLinesByLanguage[g_languageIndex], g_hudReferenceViewportWidth / 2, 190, 10, g_backdropTextScalePair, (&g_backdropTextScalePair)[1]);
    }
}
#endif

/* CCREDITS_UPDATESCROLLEU.CPP */

#if defined(VERSION_EU) || defined(VERSION_EU_X)


void CCredits_UpdateScroll(void *object) {
    f32 time;
    f32 height;
    s32 line;
    if (g_creditsSkipRequested != 0) {
        time = g_creditsLineTimer - g_frameElapsedTime;
        g_creditsLineTimer = time;
        if (time <= 0.0f) {
            Playerai_GetFirstPlayer(&g_playerViewRenderContext);
            if (g_creditsSelectSpawnOnExit != 0) {
                if (g_creditsReturnToFrontend == 0) {
                    SetN64_SelectSpawnAfterCredits(object, 1999);
                    return;
                }
                goto advance;
            }
            if (g_creditsReturnToFrontend != 0) {
advance:
                SetN64_SetTransitionTarget(object, 1);
                g_gameSettings.counters.m_bCreditsSeenOnce = 1;
            }
        }
    } else {
        if (g_hudReferenceViewportHeight >= 223) {
            g_creditsScrollPosition -= g_creditsNormalScrollStep;
        } else {
            g_creditsScrollPosition -= g_creditsFastScrollStep;
        }
        height = (f32)g_hudReferenceViewportHeight * g_creditsViewportHeightScale;
        if (g_creditsScrollPosition <= -height) {
            line = g_creditsCurrentLine + 1;
            g_creditsCurrentLine = line;
            g_creditsScrollPosition += height;
            if (g_creditsLocalizedLines[g_languageIndex][line] == 0) {
                g_creditsSkipRequested = 1;
                g_creditsLineTimer = g_creditsNextLineDelayEu;
            }
        }
    }
}
#endif

/* SETN64_EMPTYSESSIONHOOKEUX.CPP */

#if defined(VERSION_EU_X)
/** Perform no operation. */
void SetN64_EmptySessionHookEuX(void) {
}

/** Perform no operation. */
void SetN64_EmptySessionHookSecondEuX(void) {
}
#endif

/* SETN64_SETUPLOADINGBACKDROP.CPP */

#if defined(VERSION_EU_X)
/* Sets up the loading-screen scene: resets the camera globals, loads the 0xE10 resource, builds a
 * look-at matrix from the state's backdrop yaw field scaled by g_backdropYawRate, links it to the active view and
 * draws the backdrop through SetN64_DrawTextLines with half the video height. */


void SetN64_SetupLoadingBackdrop(TimedSessionTransitionView *state) {
    s32 handle, h2;
    u8 matrix[64];

    g_geometryFogEffectEnabled = 0;
    handle = Scene_FindModelIdIndex(&g_world, 3600);
    g_menuModelFillEnabled = 0;
    g_menuModelFillColor[0] = g_backdropModelFillValue;
    g_menuModelFillColor[1] = g_backdropModelFillValue;
    g_menuModelFillColor[2] = g_backdropModelFillValue;
    g_menuModelFillColor[3] = g_backdropModelFillValue;
    if (handle != -1) {
        Camera_SetupViewportAndFog(&g_fallbackScreenMessageEmitter);
        Graphu64_BuildTranslationMatrix(matrix, 0.0f, -100.0f, -500.0f);
        YawMatrixLocal(matrix, state->transitionTimer * g_backdropYawRate);
        SwapMatrixUpForward(matrix);
        Graphu64_ConvertMatrixToFixed(matrix, VIEW_MATRICES + g_lightingBufferIndex * 64);
        h2 = Scene_GetIndexedModelResource(&g_world, handle);
        Geometry_BeginModelBatch();
        Geometry_QueueDirectModel(h2, VIEW_MATRICES + g_lightingBufferIndex * 64, &g_defaultParticleLighting, 0, -1);
        Geometry_FlushModelBatch();
        SetN64_DrawTextLines(state, 0, (void *)g_backdropTextLinesByLanguage[g_languageIndex], g_hudReferenceViewportWidth / 2, 190, 10, g_backdropTextScalePair, (&g_backdropTextScalePair)[1]);
    }
}
#endif

/* SETN64_DRAWFULLSCREENBACKDROP_DATA.CPP */

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)

#endif

#if defined(VERSION_US)
/** Perform no operation. */
void SetN64_EmptyBackdropHookUs(void) {
}
#endif

/* SETN64_SETUPLOADINGBACKDROP.CPP */

#if defined(VERSION_US)
/* Sets up the loading-screen scene: resets the camera globals, loads the 0xE10 resource, builds a
 * look-at matrix from the state's backdrop yaw field scaled by g_backdropYawRate, links it to the active view and
 * draws the backdrop through SetN64_DrawTextLines with half the video height. */


void SetN64_SetupLoadingBackdrop(TimedSessionTransitionView *state) {
    s32 handle, h2;
    u8 matrix[0x40];

    g_geometryFogEffectEnabled = 0;
    handle = Scene_FindModelIdIndex(&g_world, 0xE10);
    g_menuModelFillEnabled = 0;
    g_menuModelFillColor[0] = g_backdropModelFillValue;
    g_menuModelFillColor[1] = g_backdropModelFillValue;
    g_menuModelFillColor[2] = g_backdropModelFillValue;
    g_menuModelFillColor[3] = g_backdropModelFillValue;
    if (handle != -1) {
        Camera_SetupViewportAndFog(&g_fallbackScreenMessageEmitter);
        Graphu64_BuildTranslationMatrix(matrix, 0.0f, -100.0f, -500.0f);
        YawMatrixLocal(matrix, state->transitionTimer * g_backdropYawRate);
        SwapMatrixUpForward(matrix);
        Graphu64_ConvertMatrixToFixed(matrix, VIEW_MATRICES + g_lightingBufferIndex * 64);
        h2 = Scene_GetIndexedModelResource(&g_world, handle);
        Geometry_BeginModelBatch();
        Geometry_QueueDirectModel(h2, VIEW_MATRICES + g_lightingBufferIndex * 64, &g_defaultParticleLighting, 0, -1);
        Geometry_FlushModelBatch();
        SetN64_DrawTextLines(state, 0, (void *)g_backdropTextLinesUs, g_hudReferenceViewportWidth / 2, 0xBE, 0xA, g_backdropTextScalePair, (&g_backdropTextScalePair)[1]);
    }
}
#endif

/* SETN64_SETUPLOADINGBACKDROP.CPP */

#if defined(VERSION_US_REV1)
/* Sets up the loading-screen scene: resets the camera globals, loads the 0xE10 resource, builds a
 * look-at matrix from the state's backdrop yaw field scaled by g_backdropYawRate, links it to the active view and
 * draws the backdrop through SetN64_DrawTextLines with half the video height. */


void SetN64_SetupLoadingBackdrop(TimedSessionTransitionView *state) {
    s32 handle, h2;
    u8 matrix[64];

    g_geometryFogEffectEnabled = 0;
    handle = Scene_FindModelIdIndex(&g_world, 3600);
    g_menuModelFillEnabled = 0;
    g_menuModelFillColor[0] = g_backdropModelFillValue;
    g_menuModelFillColor[1] = g_backdropModelFillValue;
    g_menuModelFillColor[2] = g_backdropModelFillValue;
    g_menuModelFillColor[3] = g_backdropModelFillValue;
    if (handle != -1) {
        Camera_SetupViewportAndFog(&g_fallbackScreenMessageEmitter);
        Graphu64_BuildTranslationMatrix(matrix, 0.0f, -100.0f, -500.0f);
        YawMatrixLocal(matrix, state->transitionTimer * g_backdropYawRate);
        SwapMatrixUpForward(matrix);
        Graphu64_ConvertMatrixToFixed(matrix, VIEW_MATRICES + g_lightingBufferIndex * 64);
        h2 = Scene_GetIndexedModelResource(&g_world, handle);
        Geometry_BeginModelBatch();
        Geometry_QueueDirectModel(h2, VIEW_MATRICES + g_lightingBufferIndex * 64, &g_defaultParticleLighting, 0, -1);
        Geometry_FlushModelBatch();
        SetN64_DrawTextLines(state, 0, (void *)g_backdropTextLines, g_hudReferenceViewportWidth / 2, 190, 10, g_backdropTextScalePair, (&g_backdropTextScalePair)[1]);
    }
}
#endif

/* EFFECT.CPP */


/* OVLGAME_INITIALIZERENDERDIRECTION_DATA.CPP */

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const float g_ovlgameInitializeRenderDirection[1] = {
    -0.667424f,
};
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const float g_ovlgameInitializeRenderDirection[3] = {
    -0.667424f, 0.953462f, -0.572078f,
};
#endif
#endif



#if defined(VERSION_DE)

#endif


#if defined(VERSION_US_REV1)
const float g_ovlgameInitializeRenderDirection[3] = {
    -0.667424f, 0.953462f, -0.572078f,
};
#endif

/* CCREDITS_UPDATESCROLL_DATA.CPP */



/* SETN64_UPDATEFADETRANSITION_DATA.CPP */

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const char g_buildDateTimeText[21] =
    "Oct 19 1999\00010:19:36\000";
#endif
#if defined(VERSION_EU)
const char g_buildDateTimeText[21] =
    "Oct 13 1999\00015:24:28\000";
#endif
#if defined(VERSION_EU_X)
const char g_buildDateTimeText[21] =
    "Oct 15 1999\00010:56:04\000";
#endif
#if defined(VERSION_US)
const char g_buildDateTimeText[21] =
    "Oct  8 1999\00015:39:01\000";
#endif
#endif

#if defined(VERSION_US_REV1)
extern const char g_buildTimestampText[21];
#endif

/* SETN64_UPDATEFRAMETIMING_DATA.CPP */



#if defined(VERSION_DE)

#endif

/* SETN64_BEGINMODETRANSITION_DATA.CPP */



/* SETN64_CHECKTIMEDSESSIONTRANSITION_DATA.CPP */



/* SETN64_DRAWSESSIONWITHATTRACTTIMEOUT_DATA.CPP */



/* SETN64_INITIALIZEFRONTENDSCREENSTATE_DATA.CPP */



/* SETN64_ADVANCEINTROFORMEMORYSIZE_DATA.CPP */



/* SETN64_HANDLECREDITSROLLINPUT_DATA.CPP */



/* SCHED_HANDLERETRACE_DATA.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)

s32 g_schedHandleretraceWords[6] = {
    0, 0, 0, 20, 0, 0,
};
#endif
#if defined(VERSION_EU_X)

extern char g_schedHandleretraceTailBytesEuX[19];
#endif
#if defined(VERSION_EU)

extern unsigned char g_schedHandleretraceTailBytesEu[19];
#endif
#if defined(VERSION_DE)

extern unsigned char g_schedHandleretraceTailBytesDe[19];
#endif

/* PARTICLE_DRAWRENDERLIST_DATA.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)


unsigned char g_particleRenderFramePrefixByte[1] = {
    0x00,
};
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)

s32 g_particleRenderFrameState[3] = {
    0, 0, 0,
};
#endif

/* SCENE_FINDTRACKEDACTORS.CPP */

/* SCENE_14.CPP */









extern void Scene_ReleaseCachedLevelData(Shared_World *world);







struct EffectSlotPool; struct Shared_World;

/* Advances the fractional animation clock and updates every active object with the resulting tick flag. */

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)

float g_trackedActorScaleTriple[3] = {
    1.0f, 1.0f, 1.0f,
};
#endif
#endif

/* SCHED_HANDLERSPCOMPLETION_DATA.CPP */



#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)


EngineSessionHandlers g_schedHandleRspCompletionSessionHandlers[21] = {
    { (EngineSessionCallback)((u32)SetN64_InitializeFrontendScreenState - 0x80000000u), (EngineSessionCallback)((u32)SetN64_ExitSessionAndDisablePaks - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawRoundTimeoutSession - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ResetSceneForIntro - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceIntroForMemorySize - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawIntroBackdrop - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeIntroText - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceIntroTextToOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawCenteredIntroText - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ClearSessionPlayerPools - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceLoadingToSplashImage - 0x80000000u), (EngineSessionCallback)((u32)SetN64_SetupLoadingBackdrop - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ResetSplashImageEffects - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceSplashImageToMainMenu - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSplashImage - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleOpeningCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawOpeningCinema - 0x80000000u) },
    { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeAfterOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeAfterOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeAfterOpeningCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartTitleMusic - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleTitleScreenInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawFullscreenBackdrop - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeMainMenuScene - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateMainMenu - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawMainMenu - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartAttractCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleAttractCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawAttractCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartSkippablePreRoundCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleSkippablePreRoundCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSkippablePreRoundCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartPreRoundCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandlePreRoundCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawPreRoundCinema - 0x80000000u) },
    { (EngineSessionCallback)((u32)SetN64_StartLevelIntroCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleLevelIntroCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawLevelIntroCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartRound - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateActiveSession - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSessionWithRoundTimeout - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ResumeSelectedSession - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateActiveSession - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSessionWithRoundTimeout - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeAfterResume - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeAfterResume - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeAfterResume - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeCreditsRoll - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleCreditsRollInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawCreditsRoll - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeSkippableCreditsRoll - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleSkippableCreditsRollInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSkippableCreditsRoll - 0x80000000u) },
    { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeAfterCredits - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeAfterCredits - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeAfterCredits - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeBeforeTransition - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeBeforeTransition - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeBeforeTransition - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeTransitionMode - 0x80000000u), (EngineSessionCallback)((u32)SetN64_EnterPendingSessionMode - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawTransitionMode - 0x80000000u) },
};
#endif
#if defined(VERSION_EU)

EngineSessionHandlers g_schedHandleRspCompletionSessionHandlers[21] = {
    { (EngineSessionCallback)((u32)SetN64_InitializeFrontendScreenState - 0x80000000u), (EngineSessionCallback)((u32)SetN64_ExitSessionAndDisablePaks - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawRoundTimeoutSession - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ResetSceneForIntro - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceIntroForMemorySize - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawIntroBackdrop - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeIntroText - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceIntroTextToOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawCenteredIntroText - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ClearSessionPlayerPools - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceLoadingToSplashImage - 0x80000000u), (EngineSessionCallback)((u32)SetN64_SetupLoadingBackdrop - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ResetSplashImageEffects - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceSplashImageToMainMenu - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSplashImage - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleOpeningCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawOpeningCinema - 0x80000000u) },
    { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeAfterOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeAfterOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeAfterOpeningCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartTitleMusic - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleTitleScreenInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawFullscreenBackdrop - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeMainMenuScene - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateMainMenu - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawMainMenu - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartAttractCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleAttractCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawAttractCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartSkippablePreRoundCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleSkippablePreRoundCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSkippablePreRoundCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartPreRoundCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandlePreRoundCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawPreRoundCinema - 0x80000000u) },
    { (EngineSessionCallback)((u32)SetN64_StartLevelIntroCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleLevelIntroCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawLevelIntroCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartRound - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateActiveSession - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSessionWithRoundTimeout - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ResumeSelectedSession - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateActiveSession - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSessionWithRoundTimeout - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeAfterResume - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeAfterResume - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeAfterResume - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeCreditsRoll - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleCreditsRollInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawCreditsRoll - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeSkippableCreditsRoll - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleSkippableCreditsRollInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSkippableCreditsRoll - 0x80000000u) },
    { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeAfterCredits - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeAfterCredits - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeAfterCredits - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeBeforeTransition - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeBeforeTransition - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeBeforeTransition - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeTransitionMode - 0x80000000u), (EngineSessionCallback)((u32)SetN64_EnterPendingSessionMode - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawTransitionMode - 0x80000000u) },
};
#endif
#if defined(VERSION_EU_X)

EngineSessionHandlers g_schedHandleRspCompletionSessionHandlers[21] = {
    { (EngineSessionCallback)((u32)SetN64_InitializeFrontendScreenState - 0x80000000u), (EngineSessionCallback)((u32)SetN64_ExitSessionAndDisablePaks - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawRoundTimeoutSession - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ResetSceneForIntro - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceIntroForMemorySize - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawIntroBackdrop - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeIntroText - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceIntroTextToOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawCenteredIntroText - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ClearSessionPlayerPools - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceLoadingToSplashImage - 0x80000000u), (EngineSessionCallback)((u32)SetN64_SetupLoadingBackdrop - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ResetSplashImageEffects - 0x80000000u), (EngineSessionCallback)((u32)SetN64_AdvanceSplashImageToMainMenu - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSplashImage - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleOpeningCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawOpeningCinema - 0x80000000u) },
    { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeAfterOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeAfterOpeningCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeAfterOpeningCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartTitleMusic - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleTitleScreenInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawFullscreenBackdrop - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeMainMenuScene - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateMainMenu - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawMainMenu - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartAttractCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleAttractCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawAttractCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartSkippablePreRoundCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleSkippablePreRoundCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSkippablePreRoundCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartPreRoundCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandlePreRoundCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawPreRoundCinema - 0x80000000u) },
    { (EngineSessionCallback)((u32)SetN64_StartLevelIntroCinema - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleLevelIntroCinemaInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawLevelIntroCinema - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_StartRound - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateActiveSession - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSessionWithRoundTimeout - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_ResumeSelectedSession - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateActiveSession - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSessionWithRoundTimeout - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeAfterResume - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeAfterResume - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeAfterResume - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeCreditsRoll - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleCreditsRollInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawCreditsRoll - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeSkippableCreditsRoll - 0x80000000u), (EngineSessionCallback)((u32)SetN64_HandleSkippableCreditsRollInput - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawSkippableCreditsRoll - 0x80000000u) },
    { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeAfterCredits - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeAfterCredits - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeAfterCredits - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeUnusedModeBeforeTransition - 0x80000000u), (EngineSessionCallback)((u32)SetN64_UpdateUnusedModeBeforeTransition - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawUnusedModeBeforeTransition - 0x80000000u) }, { (EngineSessionCallback)((u32)SetN64_InitializeTransitionMode - 0x80000000u), (EngineSessionCallback)((u32)SetN64_EnterPendingSessionMode - 0x80000000u), (EngineSessionCallback)((u32)SetN64_DrawTransitionMode - 0x80000000u) },
};
#endif
#endif
#if defined(VERSION_US_REV1)


EngineSessionHandlers g_initialSessionHandlers[3] = {
    { (EngineSessionCallback)addrLow_SetN64_InitializeFrontendScreenState_us_rev1, (EngineSessionCallback)addrLow_SetN64_ExitSessionAndDisablePaks_us_rev1, (EngineSessionCallback)addrLow_SetN64_DrawRoundTimeoutSession_us_rev1 }, { (EngineSessionCallback)addrLow_SetN64_ResetSceneForIntro_us_rev1, (EngineSessionCallback)addrLow_SetN64_AdvanceIntroForMemorySize_us_rev1, (EngineSessionCallback)addrLow_SetN64_DrawIntroBackdrop_us_rev1 }, { (EngineSessionCallback)addrLow_SetN64_InitializeIntroText_us_rev1, (EngineSessionCallback)addrLow_SetN64_AdvanceIntroTextToOpeningCinema_us_rev1, (EngineSessionCallback)addrLow_SetN64_DrawCenteredIntroText_us_rev1 },
};
#endif

/* SETN64_BUILDANDSUBMITSESSIONFRAME_DATA.CPP */
#ifdef VERSION_DE
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)

EngineRenderState g_sessionFrameRenderState = {
    0, "\000\000\000\000\003\340\000\010", 0, 1, "\000\000\000\012\000\000\000\013"
};
#endif
#endif
#ifdef VERSION_EU
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
EngineRenderState g_sessionFrameRenderState = {
    0, "\000\000\000\000\000\000\000\010", 0, 1, "\000\000\000\000\000\000\000\010"
};
#endif
#endif
#ifdef VERSION_EU_X
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
EngineRenderState g_sessionFrameRenderState = {
    0, "were bes", 0, 1, "Munch.\000\000"
};
#endif
#endif
#ifdef VERSION_US
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
EngineRenderState g_sessionFrameRenderState = {
    0, "INFLATOR", 0, 1, "\004\000\000\000f\000\000\000"
};
#endif
#endif
#ifdef VERSION_US_REV1
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
EnginePreviewRenderState g_sessionFrameRenderState = {
    0, "eft.\000\000\000\000", 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, "ep?\000Oops"
};
#endif
#endif

/* S_SMACKFORMAT.CPP */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
SmackFormatTableLayoutA g_smackFormatTable = {
    { 0, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18 },
    0.0079651f,
    -1,
    { 0x8C500000, 0x16020007 },
    0
};
#endif
#if defined(VERSION_EU)
SmackFormatTableLayoutB g_smackFormatTable = {
    { 0, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18, 0, -1 },
    { 0.70710677f, 0.0f, -0.70710677f }
};
#endif
#if defined(VERSION_EU_X)
SmackFormatTableLayoutC g_smackFormatTable = {
    { 0, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18 },
    "k %s",
    -1,
    "or find Powe"
};
#endif
#endif
#if defined(VERSION_US_REV1)
/* Announce message block shared by the menu handler table: ids 10..18 followed by the kill-message
   text tail "nted", "Embryo Destr". us-rev1 wording; the other cartridges word this block in their
   own language, so only the versions carrying these bytes land here. */
SmackFormatTableAltLayout g_smackFormatTableAlt = {
    { 0, 10, 10, 11, 12, 13, 14, 15, 16, 17, 18 },
    "nted",
    -1,
    "Embryo Destr"
};
#endif

/* SETN64_STARTROUND_DATA.CPP */

#if defined(VERSION_US_REV1)
const float literals_SetN64_StartRound[1] = {
    1.0f,
};
#endif

/* S_BURSTETEXT.CPP */


#if defined(VERSION_US_REV1)
extern char s_bursteText[12];
#endif

#if defined(VERSION_US_REV1)
/* A word (read as a word by its users) followed by three bytes; packed so the object stays 7 bytes. */
struct {
    unsigned int word;
    unsigned char trailingBytes[3];
} __attribute__((packed)) g_burstTextPackedState = {
    0x00000001,
    { 0x00, 0x00, 0x00 },
};
#endif

/* SETN64_RESUMESELECTEDSESSION_DATA.CPP */

#if defined(VERSION_US_REV1)
float g_resumeSessionUnitScale[3] = {
    1.0f, 1.0f, 1.0f,
};

extern unsigned int g_resumeSessionZero[1];
#endif

/* The us-rev1 mode lifecycle handler words that follow g_modeLifecycleHandlers_us_rev1. */

#if defined(VERSION_US_REV1)
unsigned int g_modeLifecycleHandlerWordsUsRev1[54] = {
    (unsigned int)addrLow_SetN64_ClearSessionPlayerPools_us_rev1, (unsigned int)addrLow_SetN64_AdvanceLoadingToSplashImage_us_rev1,
    (unsigned int)addrLow_SetN64_SetupLoadingBackdrop_us_rev1,
    (unsigned int)addrLow_SetN64_ResetSplashImageEffects_us_rev1, (unsigned int)g_sessionTimedTransitionCallback, (unsigned int)addrLow_SetN64_DrawSplashImage_us_rev1, (unsigned int)addrLow_SetN64_StartOpeningCinema_us_rev1, (unsigned int)addrLow_SetN64_HandleOpeningCinemaInput_us_rev1, (unsigned int)addrLow_SetN64_DrawOpeningCinema_us_rev1, (unsigned int)addrLow_SetN64_InitializeUnusedModeAfterOpeningCinema_us_rev1, (unsigned int)addrLow_SetN64_UpdateUnusedModeAfterOpeningCinema_us_rev1,
    (unsigned int)addrLow_SetN64_DrawUnusedModeAfterOpeningCinema_us_rev1, (unsigned int)addrLow_SetN64_StartTitleMusic_us_rev1, (unsigned int)addrLow_SetN64_HandleTitleScreenInput_us_rev1, (unsigned int)addrLow_SetN64_DrawFullscreenBackdrop_us_rev1, (unsigned int)addrLow_SetN64_InitializeMainMenuScene_us_rev1, (unsigned int)addrLow_SetN64_UpdateMainMenu_us_rev1, (unsigned int)addrLow_SetN64_DrawMainMenu_us_rev1, (unsigned int)addrLow_SetN64_StartAttractCinema_us_rev1,
    (unsigned int)addrLow_SetN64_HandleAttractCinemaInput_us_rev1, (unsigned int)addrLow_SetN64_DrawAttractCinema_us_rev1, (unsigned int)addrLow_SetN64_StartSkippablePreRoundCinema_us_rev1, (unsigned int)addrLow_SetN64_HandleSkippablePreRoundCinemaInput_us_rev1, (unsigned int)addrLow_SetN64_DrawSkippablePreRoundCinema_us_rev1, (unsigned int)addrLow_SetN64_StartPreRoundCinema_us_rev1, (unsigned int)addrLow_SetN64_HandlePreRoundCinemaInput_us_rev1, (unsigned int)addrLow_SetN64_DrawPreRoundCinema_us_rev1,
    (unsigned int)addrLow_SetN64_StartLevelIntroCinema_us_rev1, (unsigned int)addrLow_SetN64_HandleLevelIntroCinemaInput_us_rev1, (unsigned int)addrLow_SetN64_DrawLevelIntroCinema_us_rev1, (unsigned int)addrLow_SetN64_StartRound_us_rev1, (unsigned int)addrLow_SetN64_UpdateActiveSession_us_rev1, (unsigned int)addrLow_SetN64_DrawSessionWithRoundTimeout_us_rev1, (unsigned int)addrLow_SetN64_ResumeSelectedSession_us_rev1, (unsigned int)addrLow_SetN64_UpdateActiveSession_us_rev1,
    (unsigned int)addrLow_SetN64_DrawSessionWithRoundTimeout_us_rev1, (unsigned int)addrLow_SetN64_InitializeUnusedModeAfterResume_us_rev1, (unsigned int)addrLow_SetN64_UpdateUnusedModeAfterResume_us_rev1, (unsigned int)addrLow_SetN64_DrawUnusedModeAfterResume_us_rev1, (unsigned int)addrLow_SetN64_InitializeCreditsRoll_us_rev1, (unsigned int)addrLow_SetN64_HandleCreditsRollInput_us_rev1, (unsigned int)addrLow_SetN64_DrawCreditsRoll_us_rev1, (unsigned int)addrLow_SetN64_InitializeSkippableCreditsRoll_us_rev1,
    (unsigned int)addrLow_SetN64_HandleSkippableCreditsRollInput_us_rev1, (unsigned int)addrLow_SetN64_DrawSkippableCreditsRoll_us_rev1, (unsigned int)addrLow_SetN64_InitializeUnusedModeAfterCredits_us_rev1, (unsigned int)addrLow_SetN64_UpdateUnusedModeAfterCredits_us_rev1, (unsigned int)addrLow_SetN64_DrawUnusedModeAfterCredits_us_rev1, (unsigned int)addrLow_SetN64_InitializeUnusedModeBeforeTransition_us_rev1, (unsigned int)addrLow_SetN64_UpdateUnusedModeBeforeTransition_us_rev1, (unsigned int)addrLow_SetN64_DrawUnusedModeBeforeTransition_us_rev1,
    (unsigned int)addrLow_SetN64_InitializeTransitionMode_us_rev1, (unsigned int)addrLow_SetN64_EnterPendingSessionMode_us_rev1, (unsigned int)addrLow_SetN64_DrawTransitionMode_us_rev1,
};
#endif

/* Retained data for this translation unit. */

const float g_EngineSetRetainedScale[1] = {
    81.92f,
};

const float g_EngineSetRetainedLimits[2] = {
    7.5f, 34.0f,
};
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
const float literals_SetN64_DrawFullscreenBackdrop[5] = {
    255.0f, 0.17453295f, 0.4f, 0.7f, 4.0f,
};
#endif

const float g_initEffectPoolConstants[1] = {
    122.88f,
};
#if defined(VERSION_DE)
const float g_ovlgameInitializeRenderDirectionRemainder[2] = {
    0.953462f, -0.572078f,
};
#endif

const float g_creditsScrollSpeedConstants[4] = {
    1.0f, 0.5f, 0.045045048f, 67.5f,
};

const float literals_SetN64_UpdateFrameTiming[11] = {
    1.0f, 255.0f, 1.0e-06f, 0.1f, 0.5f, 1.0f,
    -4.0f, 0.5f, 1.0f, 1.0e-06f, 15.0f,
};
#if defined(VERSION_DE)
const float g_frameTimingSmoothing[1] = {
    0.9f,
};
#endif

const float literals_SetN64_BeginModeTransition[1] = {
    1.0f,
};

const float literals_SetN64_CheckTimedSessionTransition[1] = {
    15.0f,
};

const float literals_SetN64_DrawSessionWithAttractTimeout[7] = {
    3.0e+01f, 675.0f, 15.0f, 1.0f, 6.0e+01f, 3.0e+01f, 675.0f,
};

const float literals_SetN64_InitializeFrontendScreenState[1] = {
    1.0f,
};

const float literals_SetN64_AdvanceIntroForMemorySize[1] = {
    45.0f,
};

const float literals_SetN64_HandleCreditsRollInput[1] = {
    15.0f,
};
#if defined(VERSION_EU_X)
char g_schedHandleretraceTailBytesEuX[19] =
    "E\000\000\000SENT\000\000\000\000\000\000\000\001\000\000\000";
#endif
#if defined(VERSION_EU)
unsigned char g_schedHandleretraceTailBytesEu[19] = {
    0x00, 0x20, 0x7C, 0xB4, 0x80, 0x11, 0x00, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00,
};
#endif
#if defined(VERSION_DE)
unsigned char g_schedHandleretraceTailBytesDe[19] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00,
};
#endif
#if defined(VERSION_US_REV1)
char s_bursteText[12] = "T BURSTE";
#endif
#if defined(VERSION_US_REV1)
unsigned int g_resumeSessionZero[1] = {
    0x00000000,
};
#endif
#if defined(VERSION_US_REV1)
const char g_buildTimestampText[21] = "Oct 13 1999\0" "14:57:39";
#endif

#if defined(VERSION_DE)
unsigned char g_sessionHookReturnStub[8] = { 0x03, 0xE0, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 };
#endif
