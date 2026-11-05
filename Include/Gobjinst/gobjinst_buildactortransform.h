struct LevelActor;
#ifndef GOBJINST_GOBJINST_BUILDACTORTRANSFORM_H
#define GOBJINST_GOBJINST_BUILDACTORTRANSFORM_H
#include "Engine/graphics_math.h"
#include "Common/shared_menureply.h"
struct WeightedTable;
struct Block24;
void Gobjinst_DrawMaskedModelWithLighting(void *actor, void *unusedShadowContext, void *renderSettings, struct Block24 *lighting);
extern void MatrixFromQuaternion(f32 *q, f32 *m);
extern s32 Gobjinst_ChooseAnimationVariant(struct LevelActor *, s32, s32);
extern void Gobjinst_QueueAnimation(void *actor, u32 animationId);
extern void Lists_ClearWeightedTable(struct WeightedTable *object);
extern s32 Gobjinst_ChooseAnimationVariant(struct LevelActor *owner, s32 animationKind, s32 excludedEntry);
extern void GameObject_DrawActorShadow(char *obj, s32 shadowContext, char *info);
#endif
