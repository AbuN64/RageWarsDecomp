#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/MODEL_RENDER.H"
#include "COMMON/OBJRECV5.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"

/* GOBJINST_6.CPP */
/* Refreshes the actor's animation from the lookup through GameObject_DrawActorShadow and Geometry_DrawModelResource and, when the lookup's third node carries flag 0x8000, spawns a 0x94 effect at the actor scaled by its size, then clears g_menuModelFillEnabled. Adapted from Gobjinst_SpawnAnimatedModelViewEffect with its body moved into a static inline helper, the Gobjinst_DrawMaskedModel update calls added before it, the g_actorModelViewEffectConstants scale constants and the trailing g_menuModelFillEnabled clear changed. */

extern char g_actorParticleEffectSystem;

extern void GameObject_DrawActorShadow(char *obj, s32 unused, char *info);

extern s32 Geometry_GetViewEffect(void);

extern SpawnedEffectMotionView *Particle_GetLastSpawnedEffect(void *system);

extern f32 Gobjinst_GetActorRadius(void *actor);
extern f32 Gobjinst_GetActorHeight(void *actor);
static inline void Gobjinst_SpawnViewEffectForModel(FadedActorRenderView *actor, Lookup *lookup) {
    CVector3 position;
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;

    if (Geometry_GetViewEffect() != 0) {
        node = SetN64_GetPackSection(*lookup->value, 2);
        if ((*node != 0) &&
            (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
            position = actor->position0;
            position.y += Gobjinst_GetActorHeight(actor) * g_actorModelViewEffectConstants[1];
            Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor, 0, 0, 148,
                          actor->position1, actor->rotation, position, 0, -1, 0);
            effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem);
            if (effect != 0) {
                scale = g_actorPartsViewEffectTuning;
                effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                effect->height = Gobjinst_GetActorHeight(actor) * scale;
            }
        }
    }
}

static inline void spawn(LevelActor *actor) {
    CVector3 position;

    position = actor->position0;
    position.y += Gobjinst_GetActorHeight(actor) * *(&g_actorPartsViewEffectTuning + 1);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor, 0, 0, 148,
                  actor->position1, actor->rotation, position, 0, -1, 0);
}

void Gobjinst_DrawActorModelWithViewEffects(FadedActorRenderView *actor, void *context, Lookup *lookup) {
    s32 one;

    if (lookup->drawShadow != 0) {
        GameObject_DrawActorShadow(actor, context, lookup);
    }
    if (lookup->drawModel != 0) {
        one = 1;
        Geometry_DrawModelResource(lookup->value, actor->animation, one,
                      &actor->lighting[g_lightingBufferIndex],
                      0, actor->pass);
        Gobjinst_SpawnViewEffectForModel(actor, lookup);
    }
    g_menuModelFillEnabled = 0;
}

void Gobjinst_DrawActorPartsWithViewEffects(LevelActor *actor, PlayerControllerView *player, s32 animationContext, Draw *params) {
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;

    if (params->updateAnimation != 0) {
        GameObject_DrawActorShadow(actor, animationContext, params);
    }
    if (params->drawModel != 0) {
        Geometry_DrawActorModelParts(params->model, player, actor->animationMatrices, 1, &actor->lighting[g_lightingBufferIndex], 0, actor->renderPass);
        if (Geometry_GetViewEffect() != 0) {
            node = SetN64_GetPackSection(*params->model, 2);
            if ((*node != 0) &&
                (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
                spawn(actor);
                effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem);
                if (effect != 0) {
                    scale = g_actorBlendedViewEffectTuning;
                    effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                    effect->height = Gobjinst_GetActorHeight(actor) * scale;
                }
            }
        }
    }
    g_menuModelFillEnabled = 0;
}

/* GOBJINST_7.CPP */
/* Optionally runs GameObject_DrawActorShadow, then starts the actor's current block through Geometry_DrawBlendParts and, when the resulting animation node is flagged, spawns an effect at the actor raised by its height and scales it to the actor's size, always clearing g_menuModelFillEnabled at the end. Adapted from Gobjinst_DrawActorPartsWithViewEffects with Geometry_DrawActorModelParts changed to Geometry_DrawBlendParts and the height and scale constants taken from g_actorBlendedViewEffectTuning[1] and g_actorBlendedViewEffectScale. */

extern void Geometry_DrawBlendParts(void **value, s32 unused, s32 matrix, s32 segment, BlendPartBlockView *block, s32 textures, s32 pass);



static inline void spawn_blend_effect(TintedPlayerRenderActor *actor) {
    CVector3 position;

    position = actor->position0;
    position.y += Gobjinst_GetActorHeight(actor) * *(&g_actorBlendedViewEffectTuning + 1);
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor, 0, 0, 148,
                  actor->position1, actor->rotation, position, 0, -1, 0);
}

void Gobjinst_DrawBlendPartsWithViewEffects(TintedPlayerRenderActor *actor, s32 drawView, s32 animationContext, Lookup *params) {
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;

    if (params->drawShadow != 0) {
        GameObject_DrawActorShadow(actor, animationContext, params);
    }
    if (params->drawModel != 0) {
        Geometry_DrawBlendParts(params->value, drawView, actor->poseMatrices, 1, &actor->blocks[g_lightingBufferIndex], 0, actor->renderVariant);
        if (Geometry_GetViewEffect() != 0) {
            node = SetN64_GetPackSection(*params->value, 2);
            if ((*node != 0) &&
                (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
                spawn_blend_effect(actor);
                effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem);
                if (effect != 0) {
                    scale = g_actorBlendedViewEffectScale;
                    effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                    effect->height = Gobjinst_GetActorHeight(actor) * scale;
                }
            }
        }
    }
    g_menuModelFillEnabled = 0;
}
