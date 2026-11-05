#include "../../include/libgultra.h"
#include "Common/audio_voice_allocation.h"

void alSynDelete(ALSynth *s) {
    s->head = 0;
}
