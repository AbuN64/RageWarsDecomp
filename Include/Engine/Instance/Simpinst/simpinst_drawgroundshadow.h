#ifndef ENGINE_INSTANCE_SIMPINST_SIMPINST_DRAWGROUNDSHADOW_H
#define ENGINE_INSTANCE_SIMPINST_SIMPINST_DRAWGROUNDSHADOW_H
#include "Engine/geometry.h"
#include "Engine/graphics_math.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Common/objb.h"
#include "Common/level_actor.h"
#include "Common/propgeometry.h"
#include "World/static_model_instance_views.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/math_helpers.h"
#include "Common/legacy_collision_actor.h"
#include "Common/material_tree.h"
#include "types.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Engine/Instance/simpinst.h"
#include "Scene/cache_requestresource.h"
#include "Render/setn64_getpacksection.h"
extern char g_actorParticleEffectSystem[];
extern CQuatern Insthdr_BuildActorGroundRotation(char *obj);
extern void MatrixFromQuaternion(f32 *, f32 *);
#endif
