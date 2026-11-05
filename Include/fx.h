#ifndef FX_H
#define FX_H
#include "types.h"
#include "Common/effectcontribution.h"
#include "Render/ribbon_draw.h"
#include "Render/animation_frame_and_ribbon_views.h"
#include "Common/hud_effects.h"
#include "System/timed_effect_and_item_menu_views.h"

struct EffectContribution;
struct GameImage;
struct GameSprite;
struct Morph;
struct RibbonSegment;
typedef struct { char padding[144]; f32 matrix[7]; } DrawMatrixScratch;

extern void Fx_ApplyEffectContribution(struct EffectContribution *effectContribution);
extern void Fx_SetAnimatorScript(void *animator, int scriptAddress);

void Linked_BuildColoredRibbonVertices(struct RibbonActor *actor, struct RibbonSegment *clock, Vtx *vertices, struct Morph *morph);

extern void Fx_UpdateChildTransform(struct RibbonActor *node, void *parentTransform);
extern void Fx_UpdateNodeFractions(void *node);
extern void Fx_ConfigureSpriteImage(struct GameImage * image, struct GameImage * texture, struct GameSprite * GameSprite);
typedef struct GameImage {
    char pad0[8];
    struct ImageHeader *header;
    s32 primaryData;
    s32 secondaryData;
    char pad14[0x3C - 0x14];
    s32 flags;
} GameImage;

#endif
