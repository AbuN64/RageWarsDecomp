#ifndef SYSTEM_TIMED_EFFECT_AND_ITEM_MENU_VIEWS_H
#define SYSTEM_TIMED_EFFECT_AND_ITEM_MENU_VIEWS_H
#include "Common/hud_effects.h"
#include "Common/runtime_declarations.h"
struct EffectColorContribution;
struct EffectColorContribution {
    char pad0[0x14];
    f32 auxiliaryAlpha;
    char pad14[0x24 - 0x14 - sizeof(f32)];
    f32 alpha;
    char pad24[0x34 - 0x24 - sizeof(f32)];
    f32 red;
    char pad34[0x38 - 0x34 - sizeof(f32)];
    f32 green;
    char pad38[0x3C - 0x38 - sizeof(f32)];
    f32 blue;
};

struct GameSprite {
    s32 format;
    char *data;
    s32 primaryData;
    s32 secondaryData;
    f32 width;
    f32 height;
    f32 extentX;
    f32 extentY;
    f32 step;
};
typedef struct GameSprite GameSprite;
extern void Fx_AccumulateEffectComponents(struct EffectColorContribution *contribution);
extern void Fx_AddTimedCallback(s32 ownerAddress, s32 callback, s32 callbackData, s32 remainingCalls, f32 interval);
extern void Fx_ClampScalarRange(f32 *scalarPointer);
#endif
