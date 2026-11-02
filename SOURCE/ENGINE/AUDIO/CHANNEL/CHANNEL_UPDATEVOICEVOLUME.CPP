#include "include_asm.h"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "AUDIO/VOICE_AND_SPATIAL_SOURCE_VIEWS.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "AUDIO/EXTERNS.H"
#include "COMMON/AUDIO_CONTEXT.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/SHAREDRECV4.H"
#include "COMMON/TRIPLE.H"
#include <ultra64.h>
int Cinema_IsSequenceActive(void);
f32 Graphu64_ApproachValue(f32 current, f32 target, f32 rate);

/* Spatial mix and runtime envelope controls embedded in a sound voice. */
#include "ENGINE/AUDIO/CHANNEL.H"

typedef struct AudioVolumeControl {
    u16 levels[3];
    s16 frames;
    s16 delay;
    u16 reservedA;
} AudioVolumeControl;

typedef struct AudioVolumeVoice {
    s32 slotIndex, sound, primaryKey, secondaryKey;
    AudioVolumeMix mix;
    AudioVolumeControl control;
    f32 envelopeValue, envelopeStep;
    u8 reserved88[0x18];
    s32 pending, flags, soundId, releasePending;
    GameAudioContext *context;
    s32 reservedWordA;
    f32 reservedFloat;
    s32 reservedWordB, fixedPosition, musicGainScalingEnabled;
    f32 volumeScale;
} AudioVolumeVoice;

/* Converts the attenuated level to a volume and applies it, scaled, to the voice sound. */
static inline void apply_volume(AudioVolumeVoice *voice, f32 level) {
    GameAudioContext *outputContext;
    ALSndPlayer *outputSound;
    s32 volume;

    outputContext = voice->context;
    outputSound = outputContext->list;
    volume = (s32)level;
    alSndpSetSound(outputSound, outputContext->handles[voice->slotIndex]);
    alSndpSetVol(outputSound, (s16)(s32)((f32)volume * voice->volumeScale));
}

/* Updates spatial attenuation and the volume envelope, then applies the scaled level. */
void Channel_UpdateVoiceVolume(AudioVolumeVoice *voice) {
    AudioVolumeMix *mix;
    u16 *envelope;
    GameAudioContext *context;
    GameplayCamera *listener;
    CVector3 *position;
    CVector3 *ear;
    f32 distance, radius, squared;
    f32 dx, dy, dz;
    f32 masterGain, falloff, level;
    s32 increasing;
    s32 value;

    listener = voice->context->listenerCamera;
    radius = listener->farPlane;
    squared = radius < 3072.0f ? 3072.0f : radius;
    squared *= radius < 3072.0f ? 3072.0f : radius;
    g_spatialSoundRangeSquared = squared;
    switch (voice->mix.curve) {
    case 0:
        break;
    case 2:
        g_spatialSoundRangeSquared = squared + squared * 0.5f;
        break;
    case 1:
        g_spatialSoundRangeSquared = squared + squared * 0.25f;
        break;
    }
    mix = &voice->mix;
    envelope = voice->control.levels;
    context = voice->context;
    if (voice->flags & 0x200) {
        masterGain = context->blue;
    } else {
        masterGain = context->red;
        if (voice->musicGainScalingEnabled && context->dialogEnabled) {
            masterGain *= 0.5f;
        }
    }
    if ((voice->flags & 0x400) && voice->fixedPosition == 0 && !(voice->flags & 0x800)) {
        listener = voice->context->listenerCamera;
        position = &mix->position;
        ear = &listener->position;
        dx = position->x - ear->x;
        dy = position->y - ear->y;
        dz = position->z - ear->z;
        distance = dx * dx + dy * dy + dz * dz;
        if (g_spatialSoundRangeSquared <= distance) {
            falloff = 0.0f;
        } else {
            falloff = 1.0f - distance / g_spatialSoundRangeSquared;
        }
        switch (mix->curve) {
        case 2:
            level = falloff;
            break;
        case 0:
            falloff *= falloff;
            falloff *= falloff;
            /* Fall through to the final square. */
        case 1:
            falloff *= falloff;
            level = falloff;
            break;
        default:
            level = 0.0f;
            break;
        }
        if (Cinema_IsSequenceActive() != 0) {
            mix->attenuation = Graphu64_ApproachValue(mix->attenuation, level, 0.017f);
        } else {
            mix->attenuation = level;
        }
    } else {
        mix->attenuation = 1.0f;
    }
    if (voice->flags & 4) {
        if (voice->control.delay > 0) {
            voice->control.delay--;
        } else {
            increasing = 0;
            if (voice->envelopeStep < 0.0f) {
                increasing = 1;
            }
            if (increasing ? voice->envelopeValue < Menu_ExpandFloatHighWord(envelope[2]) :
                             Menu_ExpandFloatHighWord(envelope[2]) < voice->envelopeValue) {
                voice->envelopeValue -= voice->envelopeStep;
                if (increasing) {
                    if (Menu_ExpandFloatHighWord(envelope[2]) < voice->envelopeValue) {
                        voice->envelopeValue = Menu_ExpandFloatHighWord(envelope[2]);
                    }
                } else if (voice->envelopeValue < Menu_ExpandFloatHighWord(envelope[2])) {
                    voice->envelopeValue = Menu_ExpandFloatHighWord(envelope[2]);
                    if (voice->envelopeValue == 0.0f) {
                        ALSndPlayer *stoppedSound;
                        GameAudioContext *stopContext;

                        stopContext = voice->context;
                        voice->releasePending = 1;
                        voice->mix.tracked = 0;
                        stoppedSound = stopContext->list;
                        if (voice->mix.frame != stopContext->frame) {
                            alSndpSetSound(stoppedSound, stopContext->handles[voice->slotIndex]);
                            if (alSndpGetState(stoppedSound)) {
                                alSndpStop(stoppedSound);
                            }
                            voice->sound = -1;
                        }
                    }
                }
            }
        }
        value = (s32)(Menu_ExpandFloatHighWord(voice->control.levels[0]) * voice->envelopeValue);
        mix->left = value;
        apply_volume(voice, (f32)value * mix->attenuation * masterGain);
    } else {
        f32 attenuation;

        if (voice->flags & 0x400) {
            attenuation = mix->attenuation;
        } else {
            attenuation = mix->baseAttenuation;
        }
        apply_volume(voice, (f32)mix->left * attenuation * masterGain);
    }
}

/* Updates a voice pan from its sweep, position or centered fallback and applies it to the owner sound. */

extern s32 Audio_GetSpatialPanMode(AudioOwnerView *);
extern s16 Channel_ComputeListenerRelativePan(void *, GameplayCamera *);



static inline void apply_pan(VoiceChannelUpdateVoicePan *voice, u8 pan) {
    AudioOwnerView *owner = voice->owner;
    char *sound = owner->sound;

    alSndpSetSound(sound, owner->samples[voice->index]);
    alSndpSetPan(sound, pan);
}

void Channel_UpdateVoicePan(VoiceChannelUpdateVoicePan *voice) {
    s32 rising;
    VoiceVolumeParameters *params;

    params = &voice->params;
    if (Audio_GetSpatialPanMode(voice->owner) == 0) {
        apply_pan(voice, 64);
        return;
    }
    if (voice->sweeping != 0) {
        if (voice->delay > 0) {
            voice->delay--;
        } else {
            rising = 0;
            if (voice->step < 0.0f) {
                rising = 1;
            }
            if (rising ? voice->value < RW_BITS_TO_FLOAT(voice->target) : RW_BITS_TO_FLOAT(voice->target) < voice->value) {
                voice->value -= voice->step;
                if (rising) {
                    if (!(RW_BITS_TO_FLOAT(voice->target) < voice->value)) goto clamp_done;
                } else {
                    if (!(voice->value < RW_BITS_TO_FLOAT(voice->target))) goto clamp_done;
                }
                voice->value = RW_BITS_TO_FLOAT(voice->target);
clamp_done:
                ;
            }
        }
        params->pan = voice->value;
        goto apply;
    }
    if ((voice->flags & 0x400) && voice->fixed == 0) {
        params->pan = Channel_ComputeListenerRelativePan(voice->position, voice->owner->listener);
    apply:
        apply_pan(voice, params->pan);
        return;
    }
    params->pan = 64;
}

/* Fades emitter 0x8AC with the listener's distance: optionally resets its level, stores the squared
 * distance to the listener, lowers the level by a step while the distance grows and raises it while it
 * shrinks (clamped to the g_distancePitchFactorBounds range, remembering the distance), and otherwise eases the level one
 * step toward the rest level g_distancePitchRestFactor. */
void Channel_UpdateDistancePitchFactor(Emitter *emitter) {
    char *listener;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 distance;
    f32 level;
    f32 current;

    if (emitter->id != 2220) {
        return;
    }
    if (emitter->reset != 0) {
        emitter->level = g_distancePitchInitialFactor;
    }
    listener = ((AudioOwnerView *)emitter->scene)->listener;
    dx = emitter->x - ((GameplayCamera *)listener)->position.x;
    dy = emitter->y - ((GameplayCamera *)listener)->position.y;
    dz = emitter->z - ((GameplayCamera *)listener)->position.z;
    distance = dx * dx + dy * dy + dz * dz;
    emitter->distance = distance;
    if (emitter->lastDistance < distance) {
        emitter->level -= g_voicePitchTableBase;
    } else if (distance < emitter->lastDistance) {
        emitter->level += g_voicePitchTableBase;
    } else {
        current = emitter->level;
        if (g_distancePitchRestFactor < current) {
            level = current - g_voicePitchTableBase;
            if (level < g_distancePitchRestFactor) {
                level = g_distancePitchRestFactor;
            }
            emitter->level = level;
        } else if (current < g_distancePitchRestFactor) {
            level = current + g_voicePitchTableBase;
            if (g_distancePitchRestFactor < level) {
                level = g_distancePitchRestFactor;
            }
            emitter->level = level;
        }
        return;
    }
    level = emitter->level;
    if (g_distancePitchFactorBounds < level) {
        emitter->level = g_distancePitchFactorBounds;
    } else if (level < (&g_distancePitchFactorBounds)[1]) {
        emitter->level = (&g_distancePitchFactorBounds)[1];
    }
    emitter->lastDistance = emitter->distance;
}
