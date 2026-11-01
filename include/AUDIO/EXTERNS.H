#ifndef AUDIO_EXTERNS_H
#define AUDIO_EXTERNS_H
#include "TYPES.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "ENGINE/AUDIO/RAXPLAYER.H"
/* Finds and releases the first occupied nonlocal sound slot with matching value, identifier and flag 0x40, returning its index or -1. */










static __inline__ void release(SlotCC *slot) {
    AudioSoundPlayerOwnerView *owner = slot->owner;
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
