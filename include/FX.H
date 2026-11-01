#ifndef FX_H
#define FX_H
#include "TYPES.H"
#include "COMMON/EFFECTCONTRIBUTION.H"
#include "RENDER/RIBBON_DRAW.H"
#include "RENDER/ANIMATION_FRAME_AND_RIBBON_VIEWS.H"
#include "COMMON/OBJRECAT18V6.H"
#include "SYSTEM/TIMED_EFFECT_AND_ITEM_MENU_VIEWS.H"

typedef struct { char padding[144]; f32 matrix[7]; } DrawMatrixScratch;

extern void Fx_ApplyEffectContribution(EffectContribution *effectContribution);
extern void Fx_SetAnimatorScript(void *animator, int scriptAddress);

void Linked_BuildColoredRibbonVertices(RibbonActor *actor, RibbonClockNode *clock, Vtx *vertices, Morph *morph);

extern void Fx_UpdateChildTransform(struct Node44 *node, void *parentTransform);
extern void Fx_UpdateNodeFractions(void *node);
extern void Fx_ConfigureSpriteImage(GameImage * image, GameImage * texture, GameSprite * GameSprite);
#endif
