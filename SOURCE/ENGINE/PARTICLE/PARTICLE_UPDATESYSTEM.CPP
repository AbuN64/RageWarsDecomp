#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "TYPES.H"
#include "ENGINE/PARTICLE.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "SYSTEM/EVENTS_DELIVERCONTACTEFFECT.H"
extern char g_actorParticleScene, g_dynamicLightPool;

/* Sets an actor's field 0x14C to 1 when something is near it: a world object from g_world_AchieveUpdateresultsscreen whose field 0x174 is positive within 256 units, a player from the g_transientPlayerList list other than the actor's owner whose field 0x5E4 is positive within 256 units, or another actor of type 0xC or 0x22 from the given list within 512 units (all compared as squared distances). */








extern SharedPlayer *g_transientPlayerList;
extern void Graphu64_SubtractVectors(CVector3 *out, CVector3 *a, CVector3 *b);

void Particle_MarkCrowdedActor(s32 unused, ActorParticleMarkCrowdedActor *actor, ActorParticleMarkCrowdedActor **others, s32 count) {
    CVector3 delta;
    Shared_World *world;
    SharedPlayer *player;
    s32 i;
    s32 objectCount;

    world = &g_world;
    objectCount = world->kind1Count;
    for (i = 0; i < objectCount; i++) {
        if (world->kind1[i]->active > 0) {
            Graphu64_SubtractVectors(&delta, &world->kind1[i]->position0, &actor->position);
            if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z <= 65536.0f) {
                actor->crowded = 1;
                return;
            }
        }
    }
    for (player = g_transientPlayerList; player != 0; player = player->views16E0.view16E0_1.next) {
        if (actor->owner != player && player->views5E4.view5E4_2.health > 0) {
            Graphu64_SubtractVectors(&delta, &player->views0.view8_4.position, &actor->position);
            if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z <= 65536.0f) {
                actor->crowded = 1;
                return;
            }
        }
    }
    for (i = 0; i < count; i++) {
        if (others[i] != actor && (others[i]->type == 12 || others[i]->type == 34)) {
            Graphu64_SubtractVectors(&delta, &others[i]->position, &actor->position);
            if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z <= 262144.0f) {
                actor->crowded = 1;
                return;
            }
        }
    }
}

#include "TYPES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
/* Views of the SN debug records this pass reads, with their original member names: CParticle_t (0x1F8 bytes),
 * CParticleSystem_t (0xFC70), CROMParticleEffect_t (0x3C), CROMParticleImpact_t (0xC4) and CDLight_t (0x18). */
typedef struct CDLight_t CDLight_t;
typedef struct CROMParticleImpact_t {
    struct IntPair m_ImpactEventValue[14];
    u16 m_ImpactParticleType[14];
    u16 m_ImpactEventType[14];
    u16 m_ImpactSoundType[14];
} CROMParticleImpact_t;
typedef struct CROMParticleEffect_t {
    u32 m_dwFlags;
    char pad4[0x18 - 0x4];
    CROMParticleImpact_t *m_pImpact;
    char pad1C[0x3C - 0x1C];
} CROMParticleEffect_t;
typedef struct CParticle_t {
    char pad0[0x4];
    u16 m_nObjType; /* ah.ih.m_nObjType */
    char pad6[0x2];
    CVector3 m_vPos; /* ah.ih.m_vPos */
    char pad14[0x5C - 0x14];
    u32 m_dwFlags;
    char pad60[0x118 - 0x60];
    CROMParticleEffect_t *m_pEffect;
    char pad11C[0x130 - 0x11C];
    s32 *m_pOwnerCount;
    char pad134[0x4];
    CDLight_t *m_pDLight;
    char pad13C[0x4];
    f32 m_cFrame;
    char pad144[0x14C - 0x144];
    s16 m_nFrames;
    char pad14E[0x198 - 0x14E];
    f32 m_Alpha;
    char pad19C[0x1D0 - 0x19C];
    s8 m_Alignment;
    char pad1D1[0x1D9 - 0x1D1];
    u8 m_ActiveSwooshes;
    char pad1DA[0x1E4 - 0x1DA];
    IntrusiveList *m_pActiveList;
    struct CParticle_t *m_pLast;
    struct CParticle_t *m_pNext;
    struct CParticle_t *m_pDrawLast;
    struct CParticle_t *m_pDrawNext;
} CParticle_t;
typedef struct CParticleSystem_t {
    CParticle_t m_ParticleVars[128];
    IntrusiveList m_FreeList;
    IntrusiveList m_DrawList;
    IntrusiveList m_ActiveList[3];
    void *m_pParticleData;
    CParticle_t *m_pLastCreatedParticle;
} CParticleSystem_t;
extern const f32 g_particleLightColorFadeScale,g_particleLightMovementDistanceSquared;
extern void Particle_Update(void *),Particle_FinishActorEffects(void *),Particle_UpdateMatrix(void *);
extern void Fx_DetachParticleSwooshes(void *,void *);
extern void Particle_SpawnChildEffect(void *,s32,s32,s32);
extern void SoundElement_PlaySoundAtPosition(s16,CVector3,s32,s32);
extern void Graphu64_SubtractVectors(CVector3 *,CVector3 *,CVector3 *);
/* Frees a particle: runs its end hook (and its swoosh teardown when it has swooshes), hands its dynamic light back to
 * g_dynamicLightPool, drops one owner count, unlinks it from its active list onto the free list and, when flagged, from the
 * draw list. */
static __inline__ void Particle_Free(CParticleSystem_t *world, CParticle_t *p) {
    Particle_FinishActorEffects(p);
    if (p->m_ActiveSwooshes) {
        Particle_UpdateMatrix(p);
        Fx_DetachParticleSwooshes(&g_actorParticleScene, p);
    }
    if (p->m_pDLight) {
        Gdynlight_ReleaseLight(&g_dynamicLightPool, (s32)p->m_pDLight);
        p->m_pDLight = 0;
    }
    if (p->m_pOwnerCount) {
        --*p->m_pOwnerCount;
    }
    p->m_dwFlags &= 0xFDFFFEFF;
    List_RemoveIntrusive(p->m_pActiveList, p);
    p->m_pActiveList = 0;
    List_PrependIntrusive(&world->m_FreeList, p);
    if (p->m_dwFlags & 0x01000000) {
        List_RemoveIntrusive(&world->m_DrawList, p);
    }
}
/* Steps the particle system once: marks every particle on the three active lists, then (outside a pause) advances the
 * ones in the play box (or of type 0x41E), fires the impact events of the expired ones and frees them, and lets each
 * collected type 34 particle react to the others and each type 87 particle expire the non-87 ones within range. */
void Particle_UpdateSystem(CParticleSystem_t *world) {
    CParticle_t *colliders[128];
    CParticle_t *stepped[128];
    struct IntPair value;
    CVector3 delta;
    CParticle_t *p;
    CParticle_t *node;
    CParticle_t *focus;
    CParticle_t **begin;
    CROMParticleEffect_t *effect;
    CDLight_t *light;
    s32 count;
    s32 idx;
    s32 pairCount;
    s32 i;
    s32 j;
    s32 event;
    u32 particleType;
    u32 eventType;
    u32 soundType;
    f32 savedStep;
    count = 0;
    savedStep = g_frameElapsedTime;
    for (idx = 0; idx < 3; idx++) {
        for (node = (world->m_ActiveList + idx)->head; node != 0; node = node->m_pNext) {
            node->m_dwFlags = (node->m_dwFlags & 0xFFEFFFFF) | 0x02000000;
            stepped[count++] = node;
        }
    }
    if (g_frontendScreenStatus.status[7] != 0 || g_world.frozen != 0) {
        return;
    }
    g_frameElapsedTime = savedStep;
    g_frameElapsedTime = savedStep * g_particleSimulationTimeScale;
    pairCount = 0;
    for (idx = 0; idx < count; idx++) {
        p = stepped[idx];
        if ((p->m_dwFlags & 0x02000100) != 0x02000100) {
            continue;
        }
        p->m_dwFlags &= 0xFFEFFF87;
        if (p->m_pDLight) {
            p->m_pDLight->m_bEnabled = 0;
        }
        if (p->m_cFrame < (f32)p->m_nFrames && p->m_nFrames != 1 && !(p->m_dwFlags & 0x1000)) {
            if ((g_cameraVolumeBounds.max.x > p->m_vPos.x && g_cameraVolumeBounds.max.y > p->m_vPos.y && g_cameraVolumeBounds.max.z > p->m_vPos.z &&
                 g_cameraVolumeBounds.min.x <= p->m_vPos.x && g_cameraVolumeBounds.min.y <= p->m_vPos.y && g_cameraVolumeBounds.min.z <= p->m_vPos.z) ||
                p->m_nObjType == 1054) {
                Particle_Update(p);
                light = p->m_pDLight;
                if (light) {
                    light->m_bEnabled = 1;
                    light->x = p->m_vPos.x;
                    light->y = p->m_vPos.y;
                    light->z = p->m_vPos.z;
                    light->m_ColorFade = p->m_Alpha * g_particleLightColorFadeScale;
                }
                p->m_cFrame += g_frameElapsedTime;
            } else {
                if (!(p->m_dwFlags & 0x100)) {
                    continue;
                }
                if (!(p->m_dwFlags & 0x800)) {
                    Particle_Free(world, p);
                }
            }
        } else {
            effect = p->m_pEffect;
            event = Particle_HasSurfaceFlag(p) ? 12 : 10;
            particleType = effect->m_pImpact->m_ImpactParticleType[event];
            eventType = effect->m_pImpact->m_ImpactEventType[event];
            value = effect->m_pImpact->m_ImpactEventValue[event];
            soundType = effect->m_pImpact->m_ImpactSoundType[event];
            if (eventType != 0xFFFF) {
                Events_DeliverContactEffect(p, p, eventType, -1, p->m_vPos, value);
            }
            if (particleType != 0xFFFF) {
                Particle_SpawnChildEffect(p, particleType, p->m_Alignment, 1);
            }
            if (soundType != 0xFFFF) {
                SoundElement_PlaySoundAtPosition(soundType, p->m_vPos, 0, -1);
            }
            if (!(p->m_dwFlags & 0x100)) {
                continue;
            }
            if (!(p->m_dwFlags & 0x800)) {
                Particle_Free(world, p);
            }
        }
        if (p->m_dwFlags & 0x100) {
            switch (p->m_nObjType) {
            case 12:
            case 34:
            case 87:
                colliders[pairCount++] = p;
                break;
            }
        }
    }
    if (pairCount != 0) {
        begin = colliders;
        for (i = 0; i < pairCount; i++) {
            focus = begin[i];
            switch (focus->m_nObjType) {
            case 34:
                Particle_MarkCrowdedActor((s32)world, focus, begin, pairCount);
                break;
            case 87:
                for (j = 0; j < pairCount; j++) {
                    p = begin[j];
                    if (p->m_nObjType != 87) {
                        Graphu64_SubtractVectors(&delta, &p->m_vPos, &focus->m_vPos);
                        if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z <= g_particleLightMovementDistanceSquared) {
                            p->m_nFrames = 1;
                        }
                    }
                }
                break;
            case 12:
                break;
            }
        }
    }
    g_frameElapsedTime = savedStep;
}

#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include <PR/gbi.h>
#include "COMMON/GAMEPLAY_CAMERA.H"
/* A particle on the world's render list; the list links through next. */
typedef struct DrawParticle {
    Shared_Particle particle;
    char reserved1DC[0x18];
    struct DrawParticle *next;
} DrawParticle;
/* The particle world as the draw pass sees it: the free list, then the render list. */
typedef struct ParticleDrawWorld {
    char reserved[0xFC00];
    IntrusiveList free;
    IntrusiveList render;
} ParticleDrawWorld;
extern Gfx *g_displayListCursor;
extern GlobalsMenuSetOptionsSceneSelection g_gameplayCameraList;
extern s32 g_playerWeaponClassMode, g_lightingBufferIndex;
extern float g_particleRibbonHeightScale;
extern void Geometry_SetColorDither(s32 ditherMode);
extern s32 Visdata_TestBoxAgainstFrustum(CQuatern *planes, Box *box);
extern void Particle_DrawSprite(Shared_Particle *particle, GameplayCamera *view);
extern void Fx_AddParticleRibbonSamples(ParticleRibbonStorageView *effectWorld, Shared_Particle *particle, PackedMatrixWords *matrix);
void Particle_DrawRenderList(ParticleDrawWorld *world, GameplayCamera *view) {
    Box box;
    CVector3 transformed;
    DrawParticle *node;
    s32 visible, built;
    f32 zScale, xyScale, xScale, maximum, height, radius;
    f32 minX, maxX, minY, maxY, minZ, maxZ;
    f32 depth;
    GameplayCamera *camera;
    u32 skipAttached;
    if (world->render.head != 0) {
        gDPPipeSync(g_displayListCursor++);
        gDPSetAlphaDither(g_displayListCursor++, G_AD_NOISE);
        Geometry_SetColorDither(128);
        gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
        gSPGeometryMode(g_displayListCursor++, 0x60400, 0);
        for (node = world->render.head; node != 0; node = node->next) {
            visible = 0;
            built = node->particle.flags & 0x100000;
            if (node->particle.inst.region == 0) {
                if (!(node->particle.flags & 0x400000) && node->particle.desc->renderModel == 0) {
                    zScale = node->particle.size.z;
                    xyScale = node->particle.size.y * zScale;
                    xScale = node->particle.size.x * zScale;
                    if (!(xScale <= xyScale)) xyScale = xScale;
                    maximum = zScale;
                    if (!(xyScale <= maximum)) maximum = xyScale;
                    height = maximum * g_particleRibbonHeightScale;
                    radius = height * g_particleOwnerImpactRadiusAndStrength[0];
                    minX = node->particle.inst.pos.x - radius;
                    box.min.x = minX;
                    maxX = node->particle.inst.pos.x + radius;
                    box.max.x = maxX;
                    minY = node->particle.inst.pos.y - radius;
                    box.min.y = minY;
                    maxY = node->particle.inst.pos.y + height;
                    box.max.y = maxY;
                    minZ = node->particle.inst.pos.z - radius;
                    box.min.z = minZ;
                    maxZ = node->particle.inst.pos.z + radius;
                    box.max.z = maxZ;
                    if (minX < view->clipBounds[1].x && view->clipBounds[0].x < maxX &&
                        minZ < view->clipBounds[1].z && view->clipBounds[0].z < maxZ &&
                        minY < view->clipBounds[1].y && view->clipBounds[0].y < maxY &&
                        Visdata_TestBoxAgainstFrustum(view->clipPlanes, &box)) {
                        visible = 1;
                    }
                } else visible = 1;
            }
            do {
                if (visible) {
                    if (!built) {
                        if (g_playerWeaponClassMode == 1) {
                            camera = g_gameplayCameraList.camera;
                            Graphu64_TransformPoint(camera->worldToView, &node->particle.inst.pos, &transformed);
                            depth = transformed.z;
                            if (depth < 0.0f) depth = -depth;
                            Particle_BuildMatrix(&node->particle, &node->particle.mtx[g_lightingBufferIndex], camera, depth);
                        } else {
                            Particle_BuildMatrix(&node->particle, &node->particle.mtx[g_lightingBufferIndex], 0, 0.0f);
                        }
                        node->particle.flags |= 0x100000;
                    }
                    if (node->particle.desc->renderModel != 0) Particle_DrawModel(&node->particle, view);
                    else Particle_DrawSprite(&node->particle, view);
                    if (node->particle.desc->flags & 0x100000) {
                        Particle_DrawGroundShadow(&node->particle, view);
                    }
                    if (!node->particle.drawWhenHidden || built) break;
                    skipAttached = node->particle.desc->flags & 0x10000;
                } else {
                    if (!node->particle.drawWhenHidden || built) break;
                    if (g_playerWeaponClassMode == 1) {
                        camera = g_gameplayCameraList.camera;
                        Graphu64_TransformPoint(camera->worldToView, &node->particle.inst.pos, &transformed);
                        depth = transformed.z;
                        if (depth < 0.0f) depth = -depth;
                        Particle_BuildMatrix(&node->particle, &node->particle.mtx[g_lightingBufferIndex], camera, depth);
                    } else {
                        Particle_BuildMatrix(&node->particle, &node->particle.mtx[g_lightingBufferIndex], 0, 0.0f);
                    }
                    node->particle.flags |= 0x100000;
                    skipAttached = node->particle.desc->flags & 0x10000;
                }
                if (!skipAttached) {
                    Fx_AddParticleRibbonSamples(&g_actorParticleScene, &node->particle, &node->particle.mtx[g_lightingBufferIndex]);
                }
            } while (0);
        }
        gDPPipeSync(g_displayListCursor++);
        gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
        Geometry_SetColorDither(0);
        gDPSetAlphaDither(g_displayListCursor++, G_AD_NOTPATTERN);
    }
}

#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
typedef struct DraftActions827C8 {
    struct IntPair params[14]; u16 animation[14], effect[14], sound[14];
} DraftActions827C8;
typedef struct DraftModel827C8 { u8 pad[0x18]; DraftActions827C8 *actions; } DraftModel827C8;
typedef struct DraftActor827C8 {
    u8 pad[4]; u16 type; u8 pad6[2]; CVector3 position;
    u8 pad14[0x48]; u32 flags; u8 pad60[0xB8]; DraftModel827C8 *model;
    u8 pad11C[0x10]; s32 owner; s32 *refs; u8 pad134[4]; s32 effect;
    u8 pad13C[0x94]; s8 animation; u8 pad1D1[8]; u8 linked;
    u8 pad1DA[0xA]; void *list; u8 pad1E8[4]; struct DraftActor827C8 *next;
} DraftActor827C8;
typedef struct DraftWorld827C8 { u8 pad[0xFC00]; u8 freeList[20], activeList[20], padFC28[0x14]; DraftActor827C8 *actors; } DraftWorld827C8;
extern void Particle_SpawnChildEffect(void *, s32, s32, s32), Particle_FinishActorEffects(void *), Particle_UpdateMatrix(void *);
extern void Fx_DetachParticleSwooshes(void *, void *);
void Particle_ReleaseOwnerEmitters(DraftWorld827C8 *world, s32 owner)
{
  DraftActor827C8 *actor;
  DraftActor827C8 *next;
  DraftActions827C8 *actions;
  DraftModel827C8 *model;
  struct IntPair params;
  s32 animation;
  s32 effect;
  s32 sound;
  s32 count = 0;
  s32 index;
  actor = world->actors;
  while (actor)
  {
    next = actor->next;
    if (((actor->type == 1054) && (actor->flags & 0x100)) && (actor->owner == owner))
    {
      model = actor->model;
      actor->flags &= ~0x100;
      index = (Particle_HasSurfaceFlag(actor)) ? (12) : (10);
      actions = model->actions;
      animation = actions->animation[index];
      effect = actions->effect[index];
      params = actions->params[index];
      sound = model->actions->sound[index];
      if (effect != 0xFFFF)
      {
        Events_DeliverContactEffect(actor, actor, effect, -1, actor->position, params);
      }
      if (animation != 0xFFFF)
      {
        Particle_SpawnChildEffect(actor, animation, actor->animation, 1);
      }
      if (sound != 0xFFFF)
      {
        SoundElement_PlaySoundAtPosition((s16) sound, actor->position, 0, -1);
      }
      actor->flags |= 0x100;
      if (actor->flags & 0x100)
      {
      if (!(actor->flags & 0x800))
      {
        Particle_FinishActorEffects(actor);
        if (actor->linked)
        {
          Particle_UpdateMatrix(actor);
          Fx_DetachParticleSwooshes(&g_actorParticleScene, actor);
        }
        if (actor->effect)
        {
          Gdynlight_ReleaseLight(&g_dynamicLightPool, actor->effect);
          actor->effect = 0;
        }
        if (actor->refs)
        {
          --(*actor->refs);
        }
        actor->flags &= 0xFDFFFEFF;
        List_RemoveIntrusive(actor->list, actor);
        actor->list = 0;
        List_PrependIntrusive(world->freeList, actor);
        if (actor->flags & 0x1000000)
        {
          List_RemoveIntrusive(world->activeList, actor);
        }
      }
      }
      count++;
    }
    actor = next;
  }

  if (count)
  {
    SoundElement_PlayFlatSound(2330);
    SoundElement_PlayFlatSound(2330);
  }
}

#include "TYPES.H"

typedef struct EffectTable {
    struct IntPair pairs[14];
    u16 animations[14], effects[14], sounds[14];
} EffectTable;
typedef struct ActorDefinition {
    u32 flags;
    char pad04[0x14];
    EffectTable *effects;
} ActorDefinition;
typedef struct Actor {
    char pad00[4]; u16 kind; char pad06[2];
    CVector3 position;
    char pad14[0x48]; u32 flags;
    char pad60[0xB8]; ActorDefinition *definition;
    char pad11C[0x14]; s32 *counter; void *owner; s32 handle;
    char pad13C[0x94]; s8 channel; char pad1D1[8]; u8 linked;
    char pad1DA[0xA]; void *list;
    char pad1E8[4]; struct Actor *next;
} Actor;
typedef struct ActorWorld {
    char pad00[0xFC00]; IntrusiveList active, secondary;
    char padFC28[0x14]; Actor *head;
} ActorWorld;
extern void Particle_SpawnChildEffect(void *, s32, s32, s32);
extern void Particle_FinishActorEffects(void *);
extern void Particle_UpdateMatrix(void *);

void Particle_RetireOwnedActors(ActorWorld *world, void *owner) {
    Actor *actor, *next;
    ActorDefinition *definition;
    s32 index;
    s32 animation, effect, sound;
    struct IntPair pair;
    actor = world->head;
    while (actor != 0) {
        next = actor->next;
        if ((actor->kind == 1054 || actor->kind == 1007) &&
            (actor->flags & 0x100) && actor->owner == owner) {
            definition = actor->definition;
            index = Particle_HasSurfaceFlag(actor) ? 12 : 10;
            animation = definition->effects->animations[index];
            effect = definition->effects->effects[index];
            pair = definition->effects->pairs[index];
            sound = definition->effects->sounds[index];
            if (effect != 0xFFFF)
                Events_DeliverContactEffect(actor, actor, effect, -1, actor->position, pair);
            if (animation != 0xFFFF)
                Particle_SpawnChildEffect(actor, animation, actor->channel, 1);
            if (sound != 0xFFFF)
                SoundElement_PlaySoundAtPosition((s16)sound, actor->position, 0, -1);
            if (actor->flags & 0x100) {
                if (!(actor->flags & 0x800)) {
                    Particle_FinishActorEffects(actor);
                    if (actor->linked) {
                        Particle_UpdateMatrix(actor);
                        Fx_DetachParticleSwooshes(&g_actorParticleScene, actor);
                    }
                    if (actor->handle) {
                        Gdynlight_ReleaseLight(&g_dynamicLightPool, actor->handle);
                        actor->handle = 0;
                    }
                    if (actor->counter) --*actor->counter;
                    actor->flags &= 0xFDFFFEFF;
                    List_RemoveIntrusive(actor->list, actor);
                    actor->list = 0;
                    List_PrependIntrusive(&world->active, actor);
                    if (actor->flags & 0x1000000)
                        List_RemoveIntrusive(&world->secondary, actor);
                }
            }
        }
        actor = next;
    }
}
