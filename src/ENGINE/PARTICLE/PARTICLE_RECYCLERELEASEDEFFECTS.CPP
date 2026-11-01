#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "TYPES.H"
#include "ENGINE/PARTICLE.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"


extern void Particle_FinishActorEffects(void *actor);
extern void Particle_UpdateMatrix(void *);
extern void Fx_DetachParticleSwooshes(void *effectWorld, void *detachedEntity);










void Particle_RecycleReleasedEffects(void *recycleSystem) {
    s32 *referenceCount;
    s32 lightHandle;
    s32 flags;
    s32 i;
    s32 clear_mask;
    s32 remove_offset;
    s32 active_mask;
    s32 flagged_offset;
    s32 head_offset;
    ParticleEffect *effect;
    ParticleEffect *next;
    u8 *head_cursor;

    i = 0;
    clear_mask = 0xFDFFFEFF;
    remove_offset = 64512;
    active_mask = 0x01000000;
    flagged_offset = 0xFC14;
    do {
        __builtin_memcpy(&next, &((EffectSystem *)recycleSystem)->lists[i].head, sizeof(next));
        if (next != 0) {
            do {
                effect = next;
                next = next->next;
                flags = effect->flags;
                if (flags & 0x100) {
                  if (!(flags & 0x800)) {
                    Particle_FinishActorEffects(effect);
                    if (effect->releaseRequested != 0) {
                        Particle_UpdateMatrix(effect);
                        Fx_DetachParticleSwooshes(&g_actorParticleScene, effect);
                    }
                    lightHandle = effect->lightHandle;
                    if (lightHandle != 0) {
                        Gdynlight_ReleaseLight(&g_dynamicLightPool, lightHandle);
                        effect->lightHandle = 0;
                    }
                    referenceCount = effect->refCount;
                    if (referenceCount != 0) {
                        *referenceCount -= 1;
                    }
                    effect->flags = effect->flags & clear_mask;
                    List_RemoveIntrusive(effect->list, effect);
                    effect->list = 0;
                    List_PrependIntrusive((char *)recycleSystem + remove_offset, effect);
                    if (effect->flags & active_mask) {
                        List_RemoveIntrusive((char *)recycleSystem + flagged_offset, effect);
                    }
                  }
                }
            } while (next != 0);
        }
        i += 1;
    } while (i < 3);
}
