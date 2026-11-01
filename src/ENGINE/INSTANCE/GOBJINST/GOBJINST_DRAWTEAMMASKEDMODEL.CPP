#include "COMMON/MODEL_RENDER.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
struct CacheResourceNode;
extern void Cache_MarkResourceInUse(s32 heap, struct CacheResourceNode *resource);

extern char g_GameObject_BuildLitActorResourceAddress;
extern char s_actorLitModelResourceTag;


extern char g_actorParticleEffectSystem;

extern void GameObject_DrawActorShadow(char *obj, s32 unused, char *info);
extern s32 Cache_RequestPairedResource(s32, s32, void *, s32, s32, void *, void *, void *, s32);
extern void Link_AnimateVertexColors(void *object, void *colors);

extern void Cache_UnlockResource(s32, s32);
extern s32 Geometry_GetViewEffect(void);
#include "particle/PARTICLE_SPAWNEFFECTGROUP.H"
extern SpawnedEffectMotionView *Particle_GetLastSpawnedEffect(void *system);

static inline void spawn(LevelActor *actor) {
    CVector3 position;

    position = actor->position0;
    position.y += Gobjinst_GetActorHeight(actor) * g_actorModelViewEffectHeightScale;
    Particle_SpawnEffectGroup((struct EffectSystem *)&g_actorParticleEffectSystem, (struct EffectActor *)actor, (struct EffectActor *)actor, 0, 0, 148,
                  actor->position1, actor->rotation, position, 0, -1, 0);
}

void Gobjinst_DrawTeamMaskedModel(LevelActor *actor, s32 unusedShadowContext, Lookup *params) {
    SpawnedEffectMotionView *effect;
    f32 scale;
    s32 *node;
    s32 resource;
    s32 *header;
    char *data;

    actor->mask = 1 << actor->team;
    if (params->drawShadow != 0) {
        GameObject_DrawActorShadow(actor, unusedShadowContext, params);
    }
    if (params->drawModel == 0) {
        return;
    }
    resource = Cache_RequestPairedResource(0, actor->flags2E4 | g_litGeometryResourceKeyFlags, params->value, 0, 0,
                             actor, &g_GameObject_BuildLitActorResourceAddress, &s_actorLitModelResourceTag, 1);
    if (resource == 0) {
        return;
    }
    Cache_MarkResourceInUse(0, resource);
    header = *(s32 **)resource;
    if (header[0] == 1) {
        char *object = (char *)header + header[1];

        Link_AnimateVertexColors(object, (char *)header + header[2]);
        data = object;
    } else {
        data = (char *)(header + 2);
    }
    Geometry_DrawModelResource(params->value, actor->animationMatrices, 1, 0, data, actor->renderPass);
    if (Geometry_GetViewEffect() != 0) {
        node = SetN64_GetPackSection(*params->value, 2);
        if ((*node != 0) &&
            (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(node, 0), 0)) & 0x8000)) {
            spawn(actor);
            effect = Particle_GetLastSpawnedEffect(&g_actorParticleEffectSystem);
            if (effect != 0) {
                scale = g_actorModelViewEffectScale;
                effect->radius = Gobjinst_GetActorRadius(actor) * scale;
                effect->height = Gobjinst_GetActorHeight(actor) * scale;
            }
        }
    }
    Cache_UnlockResource(0, resource);
}
