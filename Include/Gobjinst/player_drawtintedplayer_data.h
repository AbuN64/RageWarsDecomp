#ifndef GOBJINST_PLAYER_DRAWTINTEDPLAYER_DATA_H
#define GOBJINST_PLAYER_DRAWTINTEDPLAYER_DATA_H
#include "Gobjinst/gameobject_getactorheight.h"
struct Draw;
struct PlayerControllerView;
struct TintedPlayerRenderActor;
struct LevelActor;
#include "Common/level_actor.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/runtime_declarations.h"
#include "Common/frag_tag_scores.h"
#include "Common/gameplay_reactions.h"
extern void Gobjinst_DrawActorPartsWithViewEffects(struct LevelActor *actor, struct PlayerControllerView *player, s32 animationContext, struct Draw *params);
extern void Gobjinst_DrawBlendPartsWithViewEffects(struct TintedPlayerRenderActor *actor, s32 drawView, s32 animationContext, struct Lookup *params);
struct Lookup;
extern char g_actorParticleEffectSystem[];
extern void GameObject_DrawActorShadow(char *obj, s32 shadowContext, char *info);
extern void Geometry_DrawBlendParts(void **resource, s32 drawView, s32 matrix, s32 segment, s32 lights, void *textures, s32 pass);

void Gobjinst_DrawActorModelWithViewEffects(struct LevelActor *actor, void *context, struct Lookup *lookup);
#endif
