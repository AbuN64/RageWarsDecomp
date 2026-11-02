#include "include_asm.h"
#include "COMMON/EFFECTCONTRIBUTION.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "RENDER/ANIMATION_FRAME_AND_RIBBON_VIEWS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"

/* Animator exists in COMMON/RUNTIME_DECLARATIONS.H; active owning contract is pending. */




void Fx_UpdateAnimatorScript(Animator *a) {
    s32 next;
    f32 op0;
    f32 op1;
    f32 op2;
    f32 op3;
    f32 op4;
    f32 op5;

    next = 0;
    switch (a->mode) {
    case 0:
        if (a->loop != 0) {
            next = 1;
        }
        break;
    case 1:
        a->time -= g_frameElapsedTime;
        if (a->time < 0.0f) {
            next = 1;
        }
        break;
    case 4:
        a->time += g_frameElapsedTime;
        if (a->valueDuration <= a->time) {
            a->time = a->valueDuration;
            next = 1;
        }
        op1 = a->time / a->valueDuration;
        op0 = 1.0f - op1;
        a->value = op0 * a->valueFrom + op1 * a->valueTo;
        break;
    case 6:
        a->time += g_frameElapsedTime;
        if (a->colourDuration <= a->time) {
            a->time = a->colourDuration;
            next = 1;
        }
        op1 = a->time / a->colourDuration;
        op0 = 1.0f - op1;
        a->rgb[0] = op0 * a->rgbFrom[0] + op1 * a->rgbTo[0];
        a->rgb[1] = op0 * a->rgbFrom[1] + op1 * a->rgbTo[1];
        a->rgb[2] = op0 * a->rgbFrom[2] + op1 * a->rgbTo[2];
        a->alpha = op0 * a->alphaFrom + op1 * a->alphaTo;
        break;
    }
    while (next) {
        a->mode = *a->script++;
        next = 0;
        switch (a->mode) {
        case 0:
            a->script = 0;
            a->loop = 0;
            break;
        case 1:
            op5 = *a->script++;
            a->time = op5;
            break;
        case 2:
            op0 = *a->script++;
            op1 = *a->script++;
            a->mode = 1;
            a->time = Graphu64_RandomBetween(op0, op1);
            break;
        case 3:
            next = 1;
            op4 = *a->script++;
            a->value = op4;
            break;
        case 4:
            op4 = *a->script++;
            op5 = *a->script++;
            a->valueFrom = a->value;
            a->time = 0.0f;
            a->valueTo = op4;
            a->valueDuration = op5;
            break;
        case 5:
            next = 1;
            op2 = *a->script++;
            op3 = *a->script++;
            op1 = *a->script++;
            op4 = *a->script++;
            a->rgb[0] = op2;
            a->rgb[1] = op3;
            a->rgb[2] = op1;
            a->alpha = op4;
            break;
        case 6:
            op2 = *a->script++;
            op3 = *a->script++;
            op1 = *a->script++;
            op4 = *a->script++;
            op5 = *a->script++;
            a->rgbFrom[0] = a->rgb[0];
            a->rgbFrom[1] = a->rgb[1];
            a->rgbFrom[2] = a->rgb[2];
            a->alphaFrom = a->alpha;
            a->time = 0.0f;
            a->rgbTo[0] = op2;
            a->rgbTo[1] = op3;
            a->rgbTo[2] = op1;
            a->alphaTo = op4;
            a->colourDuration = op5;
            break;
        case 7:
            next = 1;
            a->script++;
            break;
        case 8:
            next = 1;
            a->script = a->loop;
            break;
        }
    }
}

/* Fill colour state (RENDER_4/8026AC38.H names it f32 g_menuModelFillColor[5]). This unit's original declared the five floats as
 * separate globals: the ROM gives every clamp access its own lui, which only a scalar declaration produces (an array
 * element, struct member or pointer view keeps the address in a register). Q042 MIXED by unit. */
extern s32 g_menuModelFillEnabled;
extern f32 g_menuModelFillColor; /* MIXED g_menuModelFillColor red */
extern f32 g_menuModelFillGreen; /* MIXED g_menuModelFillGreen green */
extern f32 g_menuModelFillBlue; /* MIXED g_menuModelFillBlue blue */
extern f32 g_menuModelFillAlpha; /* MIXED g_menuModelFillAlpha alpha */
extern f32 g_menuModelFillTargetAlpha; /* MIXED g_menuModelFillTargetAlpha fade target alpha */
typedef struct FillFade {
    f32 alpha;
    f32 target;
} FillFade;
#define FILL_FADE ((FillFade *)&g_menuModelFillAlpha)

void Fx_UpdateFillMode(void) {
    f32 target;
    f32 alpha;

    if (g_menuModelFillColor < 0.0f) g_menuModelFillColor = 0.0f; else if (g_menuModelFillColor > 255.0f) g_menuModelFillColor = 255.0f;
    if (g_menuModelFillGreen < 0.0f) g_menuModelFillGreen = 0.0f; else if (g_menuModelFillGreen > 255.0f) g_menuModelFillGreen = 255.0f;
    if (g_menuModelFillBlue < 0.0f) g_menuModelFillBlue = 0.0f; else if (g_menuModelFillBlue > 255.0f) g_menuModelFillBlue = 255.0f;
    if (g_menuModelFillAlpha < 0.0f) g_menuModelFillAlpha = 0.0f; else if (g_menuModelFillAlpha > 255.0f) g_menuModelFillAlpha = 255.0f;
    if (g_menuModelFillTargetAlpha < 0.0f) g_menuModelFillTargetAlpha = 0.0f; else if (g_menuModelFillTargetAlpha > 255.0f) g_menuModelFillTargetAlpha = 255.0f;
    target = FILL_FADE->target;
    alpha = FILL_FADE->alpha;
    if (target == 255.0f && alpha == 0.0f) {
        g_menuModelFillEnabled = 0;
        return;
    }
    if (target != 255.0f && alpha == 0.0f) {
        g_menuModelFillEnabled = 1;
        FILL_FADE->alpha = FILL_FADE->target;
        return;
    }
    if (target == 255.0f && alpha != 0.0f) {
        g_menuModelFillEnabled = 3;
        return;
    }
    if (target != 255.0f && alpha != 0.0f) {
        g_menuModelFillEnabled = 6;
    }
}
