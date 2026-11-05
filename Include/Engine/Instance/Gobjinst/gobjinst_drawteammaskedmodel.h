#ifndef ENGINE_INSTANCE_GOBJINST_GOBJINST_DRAWTEAMMASKEDMODEL_H
#define ENGINE_INSTANCE_GOBJINST_GOBJINST_DRAWTEAMMASKEDMODEL_H
#include "Common/model_render.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/triple.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/link.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
extern void Cache_MarkResourceInUse(s32 heap, struct CacheResourceNode *resource);
extern char g_GameObject_BuildLitActorResourceAddress;
extern char s_actorLitModelResourceTag;
extern char g_actorParticleEffectSystem[];
extern void GameObject_DrawActorShadow(char *obj, s32 shadowContext, char *info);
#endif
