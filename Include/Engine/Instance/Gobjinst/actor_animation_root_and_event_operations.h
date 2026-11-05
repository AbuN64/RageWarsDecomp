#ifndef ENGINE_INSTANCE_GOBJINST_ACTOR_ANIMATION_ROOT_AND_EVENT_OPERATIONS_H
#define ENGINE_INSTANCE_GOBJINST_ACTOR_ANIMATION_ROOT_AND_EVENT_OPERATIONS_H
#include "Common/actorresourceheader.h"
#include "Engine/Instance/gobjinst.h"
#include "Common/sharedplayer.h"
#include "Common/approachlocation.h"
#include "Common/level_actor.h"
#include "Common/localdecoderange.h"
#include "Common/mtx.h"
#include "types.h"
#include "Game/builddirectionmatrix.h"
#include "Scene/cache_requestresource.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Render/setn64_getpacksection.h"
#include "Scene/cache_allocateresourceat.h"
#include "System/events_delivercontacteffect.h"
extern s32 Gastate_GetAnimationEventEntries(void *animationState);
#endif
