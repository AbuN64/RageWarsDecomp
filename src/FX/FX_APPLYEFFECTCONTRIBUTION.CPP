#include "COMMON/EFFECTCONTRIBUTION.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "RENDER/ANIMATION_FRAME_AND_RIBBON_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "FX.H"



void Fx_SetAnimatorScript(void *animator, int scriptAddress) {
    Animator *animation = animator;
    animation->mode = 0;
    animation->loop = (f32 *)scriptAddress;
    animation->script = (f32 *)scriptAddress;
}

void Fx_ApplyEffectContribution(EffectContribution *effectContribution) {
    if (effectContribution->weight != 0.0f) {
        g_menuModelFillColor[0] = effectContribution->x;
        g_menuModelFillColor[1] = effectContribution->y;
        g_menuModelFillColor[2] = effectContribution->z;
    } else {
        g_menuModelFillColor[0] = 0.0f;
        g_menuModelFillColor[1] = 0.0f;
        g_menuModelFillColor[2] = 0.0f;
    }
    g_menuModelFillColor[3] = effectContribution->weight;
    g_menuModelFillColor[4] = effectContribution->scale;
}
