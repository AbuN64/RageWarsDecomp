#include "COMMON/VIEWFLAGS.H"

void Gsky_SetDamageEffect(RacerViewport *racer, signed char effectMode, signed char delay) {
    if (racer != 0) {
        racer->mode548 = effectMode;
        racer->mode549 = delay;
    }
}
