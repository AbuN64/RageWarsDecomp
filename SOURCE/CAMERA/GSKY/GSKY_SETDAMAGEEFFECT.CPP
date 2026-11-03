#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/VIEWFLAGS.H"

void Gsky_SetDamageEffect(GameplayCamera *racer, signed char effectMode, signed char delay) {
    if (racer != 0) {
        racer->damageEffectMode = effectMode;
        racer->damageEffectDelay = delay;
    }
}
