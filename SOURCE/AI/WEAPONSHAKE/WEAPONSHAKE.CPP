#include "COMMON/STATERECAT10.H"
#include "TYPES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "include_asm.h"
/* 80231F5C_15.CPP */
u32 Weapon_UpdateShakeAxis(CShakeAxis *state) {
    f32 scale;
    f32 step;

    if (state->value > state->m_LastShake) {
        state->m_LastShake = state->value;
    }
    if (state->m_Amp == 0.0f) {
        state->m_Angle = g_weaponShakeInitialAngle;
    }
    if (state->m_Amp < state->m_LastShake + state->m_LastShake) {
        state->m_Amp = state->m_LastShake + state->m_LastShake;
    }

    step = g_frameElapsedTime;
    scale = g_weaponShakeAngleRate;
    state->value = Graphu64_DecayToZero(state->value, step * scale);
    state->m_LastShake = Graphu64_DecayToZero(state->m_LastShake, g_frameElapsedTime * scale);

    switch (state->mode) {
    case 1:
        if (state->m_Amp > 0.0f) {
            state->m_Angle += (state->m_Amp + state->m_Amp) * (g_frameElapsedTime * scale);
            state->m_Amp = Graphu64_DecayToZero(state->m_Amp, g_weaponShakeActiveDecay);
        }
        break;
    case 0:
        if (state->m_Amp > 0.0f) {
            state->m_Amp = Graphu64_DecayToZero(state->m_Amp, g_weaponShakeIdleDecay);
        }
        break;
    }

    return state->m_Amp == 0.0f;
}
const float k_WeaponshakeEncodedWords[4] = {
    9e+01f, 3.0f, 6.0f, 6.0f,
};
