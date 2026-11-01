#include "include_asm.h"
#include "../../include/libgultra.h"
#include "../../include/VOICE_START_AND_PARAMETER_UPDATE_VIEWS.H"

/** Store the supplied halfword at offset 0x16. */
void alSynSetPriority(ALSynth *unused, ALVoice *object, s16 value) {
    AudioVoicePriorityView *record = object;
    record->priority = value;
}

