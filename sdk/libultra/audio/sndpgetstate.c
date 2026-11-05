#include "Common/contreadformat.h"
#include "include_asm.h"
#include "../../include/libgultra.h"
#include "Common/vector4f.h"
#include "Common/sound_player_parameter_events.h"
#include "types.h"

s32 alSndpGetState(ALSndPlayer *soundPlayer) {
    return (((ALSoundState *) ((s8 *) ((((ALSndPlayer *) ((s8 *) soundPlayer))->target * 0x30) + ((ALSndPlayer *) ((s8 *) soundPlayer))->sndState)))->state);
}

