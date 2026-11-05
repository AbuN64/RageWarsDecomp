#ifndef AUDIO_EXTERNS_H
#define AUDIO_EXTERNS_H
#include "types.h"
#include "Common/audio_voice_slots.h"
#include "Common/runtime_declarations.h"
#include "Engine/Audio/RAXPlayer.h"
struct AudioSoundPlayerOwnerView;
struct SlotCC;
/* Finds and releases the first occupied nonlocal sound slot with matching value, identifier and flag 0x40, returning its index or -1. */










static __inline__ void release(struct SlotCC *slot) {
    struct AudioSoundPlayerOwnerView *owner = slot->owner;
    void *sound;

    slot->active = 1;
    slot->flag = 0;
    if (slot->key != owner->key) {
        sound = owner->sound;
        alSndpSetSound(sound, owner->samples[slot->index]);
        if (alSndpGetState(sound) != 0) {
            alSndpStop(sound);
        }
        slot->state = -1;
    }
}
#endif
