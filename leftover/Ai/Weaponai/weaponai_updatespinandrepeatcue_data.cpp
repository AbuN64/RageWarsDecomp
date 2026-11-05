#include "include_asm.h"

extern const float g_weaponChargeCooldownLimit;
extern const float g_weaponChargeSpinScale;
extern const float g_weaponChargeCueInterval;
const float g_weaponChargeCooldownLimit = 0.1f;
const float g_weaponChargeSpinScale = 0.017453294f;
const float g_weaponChargeCueInterval = 2.5f;

const float g_Weaponai_SettleSpinToThirdTurnConstantWords_us_C3A98[12] = {
    0.013613569f, 6.2831855f, 1.0471976f, 3.1415927f,
    5.2359877f, 1.7904929f, 1.0f, 1.7904929f,
    1.0f, 1.7904929f, 1.7904929f, 1.0f,
};
