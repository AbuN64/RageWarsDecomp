#ifndef GSKY_SKY_H
#define GSKY_SKY_H
#include "Common/sky_layers.h"
#include "Sched/sky_postscreenmessage.h"
struct Effect;
struct Host;
struct Rotor;
struct SkyLayerRuntimeView;
extern void Sky_DrawClippedEffectFan(struct SkyLayerRuntimeView *object, struct ClipView *view);
extern void Sky_InitializeEffect(struct Effect *effect, s16 *definition, s16 mask, f32 scale, f32 offset0, f32 offset1, f32 offset2);
extern s32 Sky_UpdateRotor(struct Rotor *rotor, s32 mask, f32 fallback, s32 boosting, f32 boost, struct Host *host);
extern void *Sky_AllocateEffectNode(struct Scene *sceneOwner);
extern void Sky_ReleaseEffectNode(s32 sceneAddress, s32 effectNode);
extern void Sky_SwapEntries(int *leftEntry, int *rightEntry);
extern s32 Sky_CompareRotorSpeedsDescending(void * *, void * *);
extern int Sky_CompareRotorSpeeds(void *first, void *second);
struct Scene;
struct ClipView;
void Sky_DrawDepthSortedSceneEffects(struct Scene *scene, struct ClipView *view);
#endif
