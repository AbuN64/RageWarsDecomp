#include "Common/contreadformat.h"
#include "include_asm.h"
#include "../../include/libgultra.h"
#include "Common/vector4f.h"
#include "Common/runtime_declarations.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Common/sequence_timing.h"
#include "types.h"

void alSndpDeallocate(ALSndPlayer *a, ALSndId b) {
    void *soundState;
    soundState = (b * 0x30) + (((ALSndPlayer *) ((s8 *) a))->sndState);
    if ((((ALSoundState *) ((s8 *) soundState))->state) == 0) {
        (((ALSoundState *) ((s8 *) soundState))->sound) = 0;
        if ((((ALSndPlayer *) ((s8 *) a))->target) == b) {
            (((ALSndPlayer *) ((s8 *) a))->target) = -1;
        }
    }
}

