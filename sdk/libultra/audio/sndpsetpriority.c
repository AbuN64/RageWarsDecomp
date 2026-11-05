#include "../../include/libgultra.h"
#include "Common/sound_player_parameter_events.h"
#include "Common/contreadformat.h"

/** Store the low byte of the third argument in an indexed 0x30-byte record. */
void alSndpSetPriority(ALSndPlayer *object, short index, unsigned char value) {
    ((ALSoundState *)object->sndState)[index].priority = value;
}
