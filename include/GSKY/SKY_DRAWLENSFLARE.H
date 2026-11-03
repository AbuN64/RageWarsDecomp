#ifndef GSKY_SKY_DRAWLENSFLARE_H
#define GSKY_SKY_DRAWLENSFLARE_H
struct ClipView;
void Gsky_DrawObjectFlares(struct ClipView *view);
struct LensFlareEffectState;
void Sky_InitializeLensFlareState(struct LensFlareEffectState *effectState);
#endif
