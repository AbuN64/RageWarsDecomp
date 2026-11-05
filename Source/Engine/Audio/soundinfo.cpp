#include "include_asm.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/resident_event_handler.h"
#include "Common/box_contact.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/soundinfo.h"
#include "Common/stream.h"
#include "Game/soundinfo.h"

/* SOUNDINFO.CPP */

short SoundInfo_GetGroup(void *soundDescriptor) {
    return ((SoundDescriptor *)soundDescriptor)->group;
}

short SoundInfo_GetSample(void *desc) {
    return ((SoundDescriptor *)desc)->sample;
}

/** Return the sound's playback priority. */
int SoundInfo_GetPriority(void *object) {
    return ((SoundDescriptor *)object)->priority;
}

/** Return the sound's playback mode. */
int SoundInfo_GetMode(SoundDescriptor *note) {
    return note->mode;
}

/** Return the pitch preset id of the sound. */
int SoundInfo_GetPitchPresetId(char *object) {
    return ((SoundDescriptor *)object)->pitchPresetId;
}

short SoundInfo_GetPreset(void *soundDescriptor) {
    return ((SoundDescriptor *)soundDescriptor)->preset;
}

/** Return the stereo pan, stored in the top two bits of the flags halfword. */
unsigned int SoundInfo_GetPan(void *soundDescriptor) {
    return ((SoundDescriptor *)soundDescriptor)->flags >> 14;
}

signed char SoundInfo_GetPitch(void *desc) {
    return ((SoundDescriptor *)desc)->pitch;
}

/** Return the envelope flag byte of the sound. */
signed char SoundInfo_GetEnvelopeFlag(void *object) {
    return ((SoundDescriptor *)object)->envelopeFlag;
}

/** Return the sound's yaw. */
int SoundInfo_GetYaw(void *object) {
    return ((SoundDescriptor *)object)->yaw;
}

unsigned short SoundInfo_GetFlags(void *soundDescriptor) {
    return ((SoundDescriptor *)soundDescriptor)->flags & 0x3FFF;
}

short SoundInfo_GetX(SoundDescriptor *controller) {
    return controller->x;
}

/** Return the sound's Y position. */
int SoundInfo_GetY(SoundDescriptor *object) {
    return object->y;
}

/** Return the reserved halfword of the sound descriptor. */
int SoundInfo_GetReservedHalf(void *soundDescriptor) {
    return ((SoundDescriptor *)soundDescriptor)->reservedHalf;
}

#if defined(VERSION_US)
/* Padding up to the next 16-byte object boundary; nothing reads it. */
unsigned int g_soundinfoZeroTail[1] = {
    0x00000000,
};
#endif
