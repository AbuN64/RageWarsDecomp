#ifndef GSKY_SKY_H
#define GSKY_SKY_H
#include "COMMON/DESCRIPTORRECAT29.H"
#include "SCHED/SKY_POSTSCREENMESSAGE.H"
extern void Sky_DrawClippedEffectFan(SkyLayerRuntimeView *object, ClipView *view);
extern void Sky_InitializeEffect(Effect *effect, s16 *definition, s16 mask, f32 scale, f32 offset0, f32 offset1, f32 offset2);
extern s32 Sky_UpdateRotor(Rotor *rotor, s32 mask, f32 fallback, s32 boosting, f32 boost, Host *host);
extern void *Sky_AllocateEffectNode(struct SkyEffectObjectListsView *sceneOwner);
extern void Sky_ReleaseEffectNode(s32 sceneAddress, s32 effectNode);
extern void Sky_SwapEntries(int *leftEntry, int *rightEntry);
extern s32 Sky_CompareRotorSpeedsDescending(void * *, void * *);
extern int Sky_CompareRotorSpeeds(void *first, void *second);
#endif
