#include "include_asm.h"
#include "TYPES.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "../../sdk/include/PFS/OVLGAME_INITIALIZERENDERDIRECTION.H"
#include "OVLGAME/DIRECTION.H"

/* DIRECTION.CPP */
/* DIRECTION.CPP */
extern const f32 g_defaultEffectDirectionX;
extern const f32 g_defaultEffectDirectionZ;

void Ovlgame_InitializeRenderDirection(RenderSettings *state) {
    state->direction.x = g_defaultEffectDirectionX;
    state->direction.y = g_defaultEffectDirectionY;
    state->direction.z = g_defaultEffectDirectionZ;
    Graphu64_NormalizeVec3(&state->direction.x);
    state->ready = 1;
}

#if defined(VERSION_EU_X)
unsigned int g_OvlgameInitializeRenderDirectionTrailingPad[1] = {
    0x00000000,
};
#endif

/* OVLGAME_INITIALIZERENDERDIRECTION.CPP */
/* k_OvlgameInitializerenderdirectionZeroWords_OvlgameInitializerenderdirection.CPP */
/* k_OvlgameInitializerenderdirectionZeroWords_OvlgameInitializerenderdirection.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: zero word after Ovlgame_InitializeRenderDirection */
unsigned int k_OvlgameInitializerenderdirectionZeroWords[1] = {
    0x00000000,
};
#endif

/* g_OvlgameInitializerenderdirectionEncodedWords_OvlgameInitializerenderdirection.CPP */

/* 8044E2B8_4.CPP */
