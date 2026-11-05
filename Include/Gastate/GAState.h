#ifndef GASTATE_GASTATE_H
#define GASTATE_GASTATE_H
#include "types.h"
struct Anim;
void Gastate_SwitchRequestedAnimation(struct Anim *anim, s32 table, s32 key, s32 blend, s32 *switched, struct Anim *previous);
struct CGameAnimateState_t; struct CVector3_t; struct RootActor;
void Gastate_AdvanceRootMotion(struct CGameAnimateState_t *animationChannel, struct CVector3_t *translationDeltaOut, f32 *angleDeltaOut, struct RootActor *rootMotionActor);
struct Anim;
void Gastate_SwitchRequestedAnimation(struct Anim *anim, s32 table, s32 key, s32 blend, s32 *switched, struct Anim *previous);
#endif
