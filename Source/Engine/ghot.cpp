#include "Common/level_actor.h"
#include "Common/aiprofile.h"
#include "include_asm.h"
#include "Engine/ghot.h"
#include "Fx/externs.h"
#include "Common/sharedplayer.h"
#include "Common/material_tree.h"
#include "Common/animationtriggerdefinition.h"
#include "types.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
#include "Common/approachlocation.h"
#include "System/events_delivercontacteffect.h"
#include "Engine/events.h"
#include "Particle/particle_spawneffectgroup.h"
#include "Common/model_render.h"
#include "Common/game_session.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Render/material_color_and_fog_views.h"
#include <PR/gbi.h>
#include "Engine/geometry.h"
#include "Render/setn64_getpacksection.h"
#include "Common/display.h"
#include "Common/frontend_clock_state.h"
#include "Common/runtime_declarations.h"
#include <PR/abi.h>
#include "Scene/cache_allocateresourceat.h"
#include <platform_sdk.h>
#include "Common/sessionhandlerrow.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/graphics_matrix_and_vector_math.h"
#include "Engine/textload.h"
#include "Engine/Cache/cache.h"
#include "Engine/cache.h"

/* GHOT.CPP */

/* Attachment event dispatch. Reference logic/order adapted to current symbols and shared types. */


void Ghot_DispatchAttachmentEffects(ModelAttachmentEffect *effectAttachments, s32 attachmentsRemaining, struct MatrixF *attachmentMatrices, LevelActor *actor, AttachmentTable *attachmentNodes) {
    Triple pos;
    Triple mapped;
    Triple zero;
    CQuatern rotation;
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
            if (effectBinding->effectMask & actor->renderFlags) {
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
                    actor->attachmentPosition = *(CVector3 *)&pos;
                    actorDefinitionKind = actor->definition->kind;
                    if (((actorDefinitionKind == 1) && (actor->animationMarker == 33)) || ((actorDefinitionKind == 11) && (((Player *)actor->controller)->pose == 38))) {
                        InstHdr_CopyActorPositionAndModel(actor, *(CVector3 *)&pos, &mapped, &room, 0, 1);
                        rotation = Graphu64_BuildDirectionQuaternion((Triple *)&actor->attachmentDirection);
                        zero.x = 0;
                        zero.y = 0;
                        zero.z = 0;
                        if (actor->motionThreshold <
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
                            Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor, 0, 0, 230, *(CVector3 *)&zero, rotation, *(CVector3 *)&mapped, 0, -1, attachmentEffectFlags | 1);
                        }
                        Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem[0], actor, actor, 0, 0, 138, *(CVector3 *)&zero, rotation, *(CVector3 *)&mapped, 0, -1, attachmentEffectFlags | 1);
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
                case SIGN_BIT_32:
                    Barrel_SpawnActorEffect(actor, 491, pos, attachmentEffectFlags);
                    break;
                case 0x8000000:
                    Barrel_SpawnActorEffect(actor, 284, pos, attachmentEffectFlags);
                    break;
                case 0x10000000:
                    actor->secondaryAttachmentPosition = *(CVector3 *)&pos;
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
                    Events_DeliverContactEffect(actor, actor, 3, -1, *(CVector3 *)&pos, *(ContactEffectStyle *)&params);
                }
            }
            effectAttachments++;
            attachmentsRemaining -= 1;
        } while (attachmentsRemaining != -1);
    }
}

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
const float g_dispatchAttachmentEffectsConstants[3] = {
    15.0f, 5.0f, 256.0f,
};
#endif

/* GEOMETRY_DRAWBLENDPARTS.CPP */


/* Draws the parts of a model resource tinted by an RGBA colour through the shared material g_tintedModelSharedMaterial: sets the tint mode g_menuModelFillEnabled to 3, clears the material's fog colour and sets its flags, records the colour as floats and its alpha on the material, advances the pass modulo 18, and when the frame's command buffer still has 3000 commands free and Geometry_SetupMaterial accepts the material sets the render mode, selects blend 1, registers the resource, loads the matrix (or sets it as segment 1), sets segment 2 to the given texture base or the model's own, sets the lighting on the first part and emits each part whose material blend bits are all set and accepted for the pass, clearing the tint mode afterwards. */




#if defined(VERSION_DE)

const float g_geometryMaterialSetupConstantsDe[3] = {
    15.0f, 5.0f, 256.0f,
};
#endif
