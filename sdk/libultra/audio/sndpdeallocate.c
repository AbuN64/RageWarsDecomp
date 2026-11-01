#include "include_asm.h"
#include "../../include/libgultra.h"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJRECAT18V1.H"
#include "TYPES.H"

void alSndpDeallocate(ALSndPlayer *a, ALSndId b) {
    void *soundState;
    soundState = (b * 0x30) + (((struct SoundPlayerStateTableView *) ((s8 *) a))->soundStates);
    if ((((struct Shared_GameMode *) ((s8 *) soundState))->state) == 0) {
        (((struct Shared_GameMode *) ((s8 *) soundState))->sound) = 0;
        if ((((struct SoundPlayerStateTableView *) ((s8 *) a))->selectedSoundIndex) == b) {
            (((struct SoundPlayerStateTableView *) ((s8 *) a))->selectedSoundIndex) = -1;
        }
    }
}

