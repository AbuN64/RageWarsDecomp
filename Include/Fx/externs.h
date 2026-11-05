#ifndef FX_EXTERNS_H
#define FX_EXTERNS_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
struct ControllerInput;
struct Player;
extern void ContPad_BuildControllerState(struct ControllerInput *input, struct Player *player);


extern f32 g_attachmentParticleEmissionThresholdDe;
extern f32 g_attachmentParticleLifetimeBaseDe;
extern f32 g_attachmentParticleLifetimeScaleDe;
extern f32 Gobjinst_GetModelParticleScale(void *);
#endif
