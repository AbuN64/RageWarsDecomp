#ifndef COMMON_BALLISTICPARAMS_H
#define COMMON_BALLISTICPARAMS_H
#include "Gobjinst/gameobject_getactorheight.h"
#include "types.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "common.h"
#include "Common/shared_optionsscreen.h"
#include "Common/approachlocation.h"
#include "Graphu64/graphu64_packfixedmatrix.h"

#include "Common/shared_particleinstance.h"

struct Shared_MenuData;
struct Shared_Particle;
extern f32 g_particleNeighborScale;








extern f32 g_particleTrackingMinimum;











void Playerai_ApplyPlayerForces(void *, void *);
f32 InstHdr_GetActorBaseOffset(void *);
void Graphu64_InterpolateQuaternionWithLinearFallback(struct CQuatern_t *, f32, struct CQuatern_t *, struct CQuatern_t *);
void Graphu64_ClampMotionLength(struct CVector3_t *motion, f32 maximumLength);
void MatrixFromQuaternion(f32 *, f32 *);


void Particle_UpdateSineMotion(struct Shared_Particle *particle, f32 amplitudeScale);
f32 Gu_Sqrtf(f32);
            /* extern */
extern struct Shared_MenuData g_playerViewRenderContext;
extern struct Shared_GlobalRuntimeState g_transientPlayerList;
#endif
