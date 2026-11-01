#include "include_asm.h"
#include "ENGINE/GHOT.H"

/* Attachment event dispatch. Reference logic/order adapted to current symbols and shared types. */
#include "FX/EXTERNS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OBJRECAT4V7.H"
#include "ENGINE/GHOT.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "TYPES.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"

extern char g_actorParticleEffectSystem;
extern void Graphu64_ScaleVector(struct CVector3_t *,struct CVector3_t *,f32);
extern void InstHdr_CopyActorPositionAndModel(void *, Triple, Triple *, s32 *, s32, s32);
extern struct CacheResourceBlockView Graphu64_BuildDirectionQuaternion(Triple *);
#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"
extern void Events_DeliverContactEffect(void *, void *, s32, s32, Triple, AttachmentEffectArgs);

void Ghot_DispatchAttachmentEffects(ModelAttachmentEffect *effectAttachments, s32 attachmentsRemaining, struct MatrixF *attachmentMatrices, AttachmentEffectActorView *actor, AttachmentTable *attachmentNodes) {
    Triple pos;
    Triple mapped;
    Triple zero;
    struct CacheResourceBlockView rotation;
    AttachmentEffectArgs params;
    s32 room;
    f32 actorParticleScale;
    f32 lifetime;
    s32 actorDefinitionKind;
    s32 attachmentEffectFlags;
    s32 particleLifeRange;
    u16 attachmentNodeIndex;
    u32 attachmentMask;
    u8 *node;
    AttachmentEffectBinding *effectBinding;

    attachmentsRemaining = attachmentsRemaining - 1;
    if (attachmentsRemaining != -1) {
        do {
            effectBinding = (void *)&effectAttachments->effectMask;
            if (effectBinding->effectMask & actor->attachmentEffectMask) {
                attachmentNodeIndex = effectBinding->boneIndex;
                node = attachmentNodes->bytes + attachmentNodeIndex * attachmentNodes->stride;
                attachmentEffectFlags = (*node == 5) * 2;
                Graphu64_TransformPoint(&attachmentMatrices[attachmentNodeIndex], effectAttachments, &pos);
                Graphu64_ScaleVector(&pos, &pos, 0.000015258789f);
                particleLifeRange = 0;
                attachmentMask = effectBinding->effectMask;
                switch (attachmentMask) {                  /* irregular */
#if !defined(VERSION_DE)
                case 2:
                    Barrel_SpawnActorEffect(actor, 81, pos, attachmentEffectFlags);
                    break;
                case 8:
                    Barrel_SpawnActorEffect(actor, 92, pos, attachmentEffectFlags);
                    break;
#endif
                case 1:
                case 4:
                case 16:
                case 32:
                    break;
                case 64:
                    actor->attachmentPosition = pos;
                    actorDefinitionKind = *actor->definition;
                    if (((actorDefinitionKind == 1) && (actor->action == 33)) || ((actorDefinitionKind == 11) && (actor->player->action == 38))) {
                        InstHdr_CopyActorPositionAndModel(actor, pos, &mapped, &room, 0, 1);
                        rotation = Graphu64_BuildDirectionQuaternion(&actor->attachmentDirection);
                        zero.x = 0;
                        zero.y = 0;
                        zero.z = 0;
                        if (actor->effectThresholdValue <
#if defined(VERSION_US)
                            g_attachmentParticleEmissionThreshold
#elif defined(VERSION_EU)
                            g_attachmentParticleEmissionThreshold
#elif defined(VERSION_EU_X)
                            g_attachmentParticleEmissionThreshold
#elif defined(VERSION_DE)
                            g_attachmentParticleEmissionThresholdDe
#else
                            g_attachmentParticleEmissionThreshold
#endif
                        ) {
                            Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor, 0, 0, 230, *(CVector3 *)&zero, *(CQuatern *)&rotation, *(CVector3 *)&mapped, 0, -1, attachmentEffectFlags | 1);
                        }
                        Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor, 0, 0, 138, *(CVector3 *)&zero, *(CQuatern *)&rotation, *(CVector3 *)&mapped, 0, -1, attachmentEffectFlags | 1);
                    }
                    break;
                case 128:
                    Barrel_SpawnActorEffect(actor, 172, pos, attachmentEffectFlags);
                    break;
                case 0x100:
                    Barrel_SpawnActorEffect(actor, 173, pos, attachmentEffectFlags);
                    break;
                case 0x200:
                    Barrel_SpawnActorEffect(actor, 174, pos, attachmentEffectFlags);
                    break;
                case 0x400:
                    Barrel_SpawnActorEffect(actor, 175, pos, attachmentEffectFlags);
                    break;
                case 0x800:
                    Barrel_SpawnActorEffect(actor, 176, pos, attachmentEffectFlags);
                    break;
                case 0x1000:
                    Barrel_SpawnActorEffect(actor, 177, pos, attachmentEffectFlags);
                    break;
                case 0x2000:
                    Barrel_SpawnActorEffect(actor, 178, pos, attachmentEffectFlags);
                    break;
                case 0x4000:
                    Barrel_SpawnActorEffect(actor, 179, pos, attachmentEffectFlags);
                    break;
                case 0x8000:
                    Barrel_SpawnActorEffect(actor, 180, pos, attachmentEffectFlags);
                    break;
                case 0x10000:
                    Barrel_SpawnActorEffect(actor, 181, pos, attachmentEffectFlags);
                    break;
                case 0x20000:
                    Barrel_SpawnActorEffect(actor, 182, pos, attachmentEffectFlags);
                    break;
                case 0x40000:
                    Barrel_SpawnActorEffect(actor, 183, pos, attachmentEffectFlags);
                    break;
                case 0x80000:
                    Barrel_SpawnActorEffect(actor, 184, pos, attachmentEffectFlags);
                    break;
                case 0x100000:
                    Barrel_SpawnActorEffect(actor, 185, pos, attachmentEffectFlags);
                    break;
                case 0x200000:
                    Barrel_SpawnActorEffect(actor, 186, pos, attachmentEffectFlags);
                    break;
                case 0x400000:
                    Barrel_SpawnActorEffect(actor, 187, pos, attachmentEffectFlags);
                    break;
                case 0x20000000:
                    Barrel_SpawnActorEffect(actor, 489, pos, attachmentEffectFlags);
                    break;
                case 0x40000000:
                    Barrel_SpawnActorEffect(actor, 490, pos, attachmentEffectFlags);
                    break;
                case 0x80000000:
                    Barrel_SpawnActorEffect(actor, 491, pos, attachmentEffectFlags);
                    break;
                case 0x8000000:
                    Barrel_SpawnActorEffect(actor, 284, pos, attachmentEffectFlags);
                    break;
                case 0x10000000:
                    actor->secondaryAttachmentPosition = pos;
                    break;
                case 0x800000:
                    particleLifeRange = 5;
                    break;
                case 0x1000000:
                    particleLifeRange = 10;
                    break;
                case 0x2000000:
                    particleLifeRange = 15;
                    break;
                case 0x4000000:
                    particleLifeRange = 20;
                    break;
                }
                if (particleLifeRange != 0) {
                    actorParticleScale = Gobjinst_GetModelParticleScale(actor);
                    params.fields.lifeRange = particleLifeRange << 8;
                    params.fields.countRange = 0;
                    params.fields.countBase = 0;
                    params.fields.modifier = 0;
                    params.fields.chance = 0;
#if defined(VERSION_US)
                    lifetime = g_attachmentParticleLifetimeBase;
#elif defined(VERSION_EU)
                    lifetime = g_attachmentParticleLifetimeBase;
#elif defined(VERSION_EU_X)
                    lifetime = g_attachmentParticleLifetimeBase;
#elif defined(VERSION_DE)
                    lifetime = g_attachmentParticleLifetimeBaseDe;
#else
                    lifetime = g_attachmentParticleLifetimeBase;
#endif
                    lifetime /= actorParticleScale;
#if defined(VERSION_US)
                    lifetime *= g_attachmentParticleLifetimeScale;
#elif defined(VERSION_EU)
                    lifetime *= g_attachmentParticleLifetimeScale;
#elif defined(VERSION_EU_X)
                    lifetime *= g_attachmentParticleLifetimeScale;
#elif defined(VERSION_DE)
                    lifetime *= g_attachmentParticleLifetimeScaleDe;
#else
                    lifetime *= g_attachmentParticleLifetimeScale;
#endif
                    params.fields.lifeBase = (s16)(s32)lifetime;
                    Events_DeliverContactEffect(actor, actor, 3, -1, pos, params);
                }
            }
            effectAttachments++;
            attachmentsRemaining -= 1;
        } while (attachmentsRemaining != -1);
    }
}

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Ghot_DispatchAttachmentEffectsConstantWords_Ghot.c */
const float g_Ghot_DispatchAttachmentEffectsConstantWords[3] = {
    15.0f, 5.0f, 256.0f,
};
#endif


