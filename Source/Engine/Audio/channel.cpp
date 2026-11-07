#include "include_asm.h"
#include "Common/listnode.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "types.h"
#include "Common/audio_voice_slots.h"
#include "Audio/voice_and_spatial_source_views.h"
#include "Common/runtime_declarations.h"
#include "Audio/list_and_channel_views.h"
#include "Common/triple.h"
#include "common.h"
#include "Common/gameplay_camera.h"
#include "Fx/normalize_vector.h"
#include "Common/audio_context.h"
#include "Common/cartridgereadworker.h"
#include "Audio/channel_initializevoicemix.h"
#include "Channel/lookuppanvalue.h"
#include "Common/soundinfo.h"
#include "System/engine_data_source.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Engine/Audio/channel.h"
#include "Engine/Audio/audioworld.h"
#include "Common/audio_callbacks.h"
#include "Common/resident_event_handler.h"
#include "Audio/externs.h"
#include "Common/audio_voice_allocation.h"
#include <platform_sdk.h>
#include "Audio/audio_chooseweightedsoundvariant.h"
#include "Common/viewflags.h"
#include "Graphu64/graphu64_buildlookatmatrix.h"
#include "Channel/channel_updatevoicevolume.h"
#include "Common/albank_s.h"
#include "Common/menu_match_globals.h"
#include "Texture/sound_updateaudiocontext.h"
#include "Channel/channel_startnotevoice.h"
#include "Gsky/sky_postscaledscreenmessage.h"
#include "Channel/channel_updatevoicepitch.h"
#include "Common/aiprofile.h"
#include "Audio/voice.h"
#include "Common/soundvoicepool.h"
#include "Voice/voice.h"
#include "Common/heap_arena_entry.h"
#include "Common/music_track_volume.h"
#include "Engine/Audio/T2SoundElement.h"
#include "Engine/Cache/list.h"
#include "Common/animationtriggerdefinition.h"
#include "Common/format.h"
#include "data_overlay_layouts.h"

/* CHANNEL_INITIALIZEVOICEMIX.CPP */

/* Returns the stereo pan of a sound at a position for a listener: centre without a listener, when
 * the sound is horizontally within a small radius or straight ahead; otherwise the horizontal direction
 * in listener space is compared with the forward axis through Graphu64_ArcCos and Gu_Sinf_SkyPosttargetedscreenmessage, given the
 * side's sign, and scaled around the centre by g_listenerPanCenterAndRange. */

s16 Channel_ComputeListenerRelativePan(CVector3 *position, GameplayCamera *listener) {
    CVector3 forward;
    CVector3 offset;
    CVector3 local;
    f32 pan;

    if (listener == 0) {
        return 64;
    }
    Graphu64_SubtractVectors(&offset, &listener->position, position);
    if (offset.x * offset.x + offset.z * offset.z < g_listenerPanCenterRadiusConstants) {
        return 64;
    }
    Graphu64_TransformDirectionTranspose(listener->viewOrient, &offset, &local);
    local.y = 0.0f;
    forward.x = forward.y = local.y;
    forward.z = (&g_listenerPanCenterRadiusConstants)[1];
    Graphu64_NormalizeVec3(&local.x);
    pan = Gu_Sinf(Graphu64_ArcCos(local.x * forward.x + local.y * forward.y + local.z * forward.z));
    if (local.x == 0.0f) {
        return 64;
    }
    if (0.0f < local.x) {
        if (pan < 0.0f) {
            pan = -pan;
        }
    } else {
        pan = -fabsf(pan);
    }
    return pan * g_listenerPanCenterAndRange + g_listenerPanCenterAndRange;
}

/* Updates a view's heading from its controller: clears its turn rates, takes the base angles from the controller's preset (or the heading from its default yaw), adds the stick turn derived from Graphu64_RandomBetween of the two stick axes, nudges it up for flag 0x40 and down for flag 0x80, caps it at the limit, optionally records the heading and the pitch step over the step count and the current pitch, and finally maps the heading through the 60-entry curve table g_audioPitchRatioCurve with linear interpolation. The turn is truncated to 16 bits into an int, and the next table index is its own s16. */

void Channel_InitializeVoicePitchMotion(ChannelPitchMotionView *view, SoundDescriptor *controller, s32 flags) {
    s16 x;
    s16 y;
    f32 fx;
    f32 fy;
    s32 turn;
    f32 diff;
    f32 position;
    s16 index;
    s16 next;
    f32 base;
    f32 result;
    struct Motion *motion;
    struct Angles *angles;

    motion = &view->motion;
    angles = &view->angles;
    motion->rate1 = motion->rate2 = 0.0f;
    if (controller->preset != -1) {
        *(struct Bytes12 *)angles = *(struct Bytes12 *)Audio_GetMetadataSectionFourEntry(view->presets, controller->preset);
    } else {
        angles->heading = Menu_GetFloatHighWord(controller->yaw);
    }
    x = SoundInfo_GetX(controller);
    y = SoundInfo_GetY(controller);
    fy = y;
    fx = x;
    turn = (s16)(s32)(fx + ((Graphu64_RandomBetween(fy, fx)) < 0.0f ? -(Graphu64_RandomBetween(fy, fx)) : (Graphu64_RandomBetween(fy, fx))));
    angles->heading = Menu_GetFloatHighWord(RW_BITS_TO_FLOAT(angles->heading) + turn);
    if (flags & 0x40) {
        angles->heading = Menu_GetFloatHighWord(RW_BITS_TO_FLOAT(angles->heading) + g_voicePitchRaiseStep);
    }
    if (flags & 0x80) {
        angles->heading = Menu_GetFloatHighWord(RW_BITS_TO_FLOAT(angles->heading) - g_voicePitchLowerStep);
    }
    if (RW_BITS_TO_FLOAT(angles->heading) >= g_voicePitchMaximum) {
        angles->heading = Menu_GetFloatHighWord(g_voicePitchMaximum);
    }
    if (controller->flags & 2) {
        motion->heading = RW_BITS_TO_FLOAT(angles->heading);
        diff = RW_BITS_TO_FLOAT(angles->pitch);
        diff -= RW_BITS_TO_FLOAT(angles->target);
        if (angles->steps == 0) {
            view->pitchStep = 0.0f;
        } else {
            view->pitchStep = diff / angles->steps;
        }
        view->pitch = RW_BITS_TO_FLOAT(angles->pitch);
    }
    position = (RW_BITS_TO_FLOAT(angles->heading) + g_voicePitchHeadingBias) * g_voicePitchHeadingIndexScale;
    index = position;
    if (index != position) {
        next = index + 1;
        base = g_audioPitchRatioCurve[index];
        result = base + (position - index) * (g_audioPitchRatioCurve[next] - base);
    } else {
        result = g_audioPitchRatioCurve[index];
    }
    motion->heading = result;
    angles->heading = Menu_GetFloatHighWord(result);
}

/* Starts or retunes a voice's pan: seeds the gain from the sound table (the id compared with each entry of the
 * 0x1F pairs at g_soundVolumeScales gives its scale), halves it when the shared flag says so, takes the pan angles from the
 * preset or the controller yaw, measures how loudly the listener hears it (squared distance falloff raised to the
 * power the voice kind asks for) and writes the left and right levels, interpolating the pan over the given
 * steps when the controller asks for a ramp. */
typedef struct SoundEnvelopeControl {
    u16 flags, initial, target;
    s16 frames;
    s16 delay;
    u16 reservedA;
} SoundEnvelopeControl;


typedef struct VoiceScaleEntry { f32 soundId, scale; } VoiceScaleEntry;

static inline s32 lookupPanValue(s32 panAngle) {
    if ((f32)panAngle < 0.0f) return g_voiceAttenuationTable[-panAngle];
    return g_voiceAttenuationTable[panAngle];
}

void Channel_InitializeVoiceMix(Voice *voice, SoundDescriptor *control, s32 voiceFlags) {
    AudioVolumeMix *mix;
    SoundEnvelopeControl *envelope;
    u8 *gainRange;
    s32 i;
    f32 minimumGain;
    f32 maximumGain;
    f32 gain;
    f32 attenuation;
    CVector3 *sourcePosition;
    CVector3 *listenerPosition;
    f32 dx, dy, dz;
    f32 distanceSquared;
    f32 panDelta;
    s32 panAngle;
    s32 scaledPan;
    SoundEnvelope *preset;

    mix = (AudioVolumeMix *)voice->reserved10;
    gainRange = voice->context->selectedEntry;
    voice->volumeScale = g_voiceDefaultVolumeScale;
    if (voice->soundId < 256) {
        for (i = 0; i < 31; i++) {
            if (voice->soundId == (s32)g_soundVolumeScales[i].soundId) {
                voice->volumeScale = g_soundVolumeScales[i].scale;
                break;
            }
        }
    }
    if (Cinema_IsSequenceInWindow()) {
        voice->volumeScale = voice->volumeScale * g_voiceModeVolumeScale;
    }
    envelope = (SoundEnvelopeControl *)voice->envelope;
    if (control->pitchPresetId != -1) {
        preset = Audio_GetMetadataSectionThreeEntry(voice->context, control->pitchPresetId);
        *(SoundEnvelope *)voice->envelope = *preset;
    } else {
        envelope->flags = Menu_GetFloatHighWord((f32)control->envelopeFlag);
    }
    if (!(control->flags & 0x800) && voice->fixedPosition != 1 && voice->context->listenerCamera != 0) {
        minimumGain = (f32)gainRange[0] * g_voiceGainPercentScale;
        maximumGain = (f32)gainRange[1] * g_voiceGainPercentScale;
        if (minimumGain == g_voiceGainIdentityValue) gain = g_voiceGainIdentityValue;
        else if (maximumGain == minimumGain) gain = minimumGain;
        else gain = minimumGain + Graphu64_RandomFloat(maximumGain - minimumGain);
        sourcePosition = &mix->position;
        listenerPosition = &voice->context->listenerCamera->position;
        dx = sourcePosition->x - listenerPosition->x;
        dy = sourcePosition->y - listenerPosition->y;
        dz = sourcePosition->z - listenerPosition->z;
        distanceSquared = dx * dx + dy * dy + dz * dz;
        attenuation = g_spatialSoundRangeSquared <= distanceSquared ? 0.0f : g_voiceInitialAttenuationUnit - distanceSquared / g_spatialSoundRangeSquared;
        switch (mix->curve) {
        case 2:
            mix->attenuation = attenuation;
            break;
        case 0:
            attenuation = attenuation * attenuation;
            attenuation = attenuation * attenuation;
        case 1:
            attenuation = attenuation * attenuation;
            mix->attenuation = attenuation;
            break;
        default:
            attenuation = 0.0f;
            mix->attenuation = attenuation;
            break;
        }
        mix->baseAttenuation = attenuation;
    } else {
        gain = g_voiceDefaultGain;
        mix->attenuation = gain;
        mix->baseAttenuation = gain;
    }
    if (control->flags & 4) {
        mix->left = (s32)Menu_ExpandFloatHighWord(envelope->flags);
        panDelta = Menu_ExpandFloatHighWord(envelope->initial);
        panDelta -= Menu_ExpandFloatHighWord(envelope->target);
        if (envelope->frames == 0) {
            voice->envelopeStep = 0.0f;
        } else {
            voice->envelopeStep = panDelta / envelope->frames;
        }
        voice->envelopeValue = Menu_ExpandFloatHighWord(envelope->initial);
        panAngle = (s32)Menu_ExpandFloatHighWord(envelope->flags);
        scaledPan = (s32)((f32)lookupPanValue(panAngle) * voice->envelopeValue);
        mix->left = (s32)((f32)scaledPan * gain);
        envelope->flags = Menu_GetFloatHighWord((f32)lookupPanValue(panAngle) * gain);
        mix->right = (s32)Menu_ExpandFloatHighWord(envelope->flags);
    } else {
        panAngle = (s32)Menu_ExpandFloatHighWord(envelope->flags);
        mix->left = (s32)((f32)lookupPanValue(panAngle) * gain);
        mix->right = mix->left;
    }
}

/* CHANNEL_UPDATEVOICEVOLUME.CPP */

/* Spatial mix and runtime envelope controls embedded in a sound voice. */

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

/* CHANNEL_UPDATEVOICEPITCH.CPP */

/* Ramps a voice pitch toward its target, interpolates the pitch curve and applies its scaled value to the context channel. */

static inline char *selectChannel(VoicePitchChannelContext *context, s32 slot) {
    alSndpSetSound(context->channels, context->slots[slot]);
    return context->channels;
}

static inline void apply(VoicePitchChannelContext *context, s32 slot, f32 value, ViewChannelUpdateVoicePitch *view) {
    char *channel = context->channels;

    alSndpSetSound(channel, context->slots[slot]);
    value *= view->motion.factor;
    value *= view->scale;
    alSndpSetPitch(channel, value);
}

void Channel_UpdateVoicePitch(ViewChannelUpdateVoicePitch *view) {
    VoicePitchMotion *motion;
    VoicePitchAngles *angles;
    s32 refreshed;
    s32 falling;
    f32 position;
    s32 truncated;
    s16 index;
    s16 next;
    f32 base;
    f32 result;
    char *channel;
    VoicePitchChannelContext *context;

    refreshed = 0;
    motion = &view->motion;
    angles = &view->angles;
    context = view->context;
    if ((view->flags & 0x400) && !(context->frame & 3)) {
        Channel_UpdateDistancePitchFactor(view);
        refreshed = 1;
    }
    if ((view->flags & 0xA) == 0xA) {
        if (view->angles.delay > 0) {
            view->angles.delay--;
        } else {
            falling = 0;
            if (view->pitchStep < 0.0f) {
                falling = 1;
            }
            if (falling ? view->pitch < RW_BITS_TO_FLOAT(angles->target) : RW_BITS_TO_FLOAT(angles->target) < view->pitch) {
                view->pitch -= view->pitchStep;
                if (falling) {
                    if (!(RW_BITS_TO_FLOAT(angles->target) < view->pitch)) goto clamp_done;
                } else {
                    if (!(view->pitch < RW_BITS_TO_FLOAT(angles->target))) goto clamp_done;
                }
                view->pitch = RW_BITS_TO_FLOAT(angles->target);
                clamp_done:;

                position = (view->pitch + g_voicePlaybackPitchBias) * g_voicePlaybackPitchIndexScale;
                truncated = position;
                index = (s16)truncated;
                if (index != position) {
                    next = truncated + 1;
                    base = g_audioPitchRatioCurve[index];
                    result = base + (position - index) * (g_audioPitchRatioCurve[next] - base);
                } else {
                    result = g_audioPitchRatioCurve[index];
                }
                motion->heading = result;
                channel = selectChannel(view->context, view->slot);
                alSndpSetPitch(channel, result * view->motion.factor * view->scale);
                return;
            }
        }
    }
    if (refreshed) {
        apply(view->context, view->slot, motion->heading, view);
    }
}

/* CHANNEL_STARTNOTEVOICE.CPP */

/* Updates a playing view each frame: records the result of Gsky_FindNearestCamera_ChannelStartnotevoice for its position in the context, selects its channel and checks whether it still plays; a view past its end, finished once, or whose track changed is marked done, and a done view that still plays is stopped once per frame and loses its handle; a stopped view first waits out its hold count, then is released with its slot and state cleared unless it is fading, while a playing view copies its tracked position and runs its three per-frame updates. The first channel selection matches as an inline helper returning the channel. */

ALSndPlayer;

static inline char *selectChannel_channel_startnotevoice(AudioVoiceContextView *context, s32 slot) {
    alSndpSetSound(((AudioOwnerView *)context)->sound, context->slots.ids[slot]);
    return ((AudioOwnerView *)context)->sound;
}

void Channel_UpdateVoicePlayback(ViewChannelUpdateVoicePlayback *view) {
    char *channel;
    AudioVoiceContextView *context;
    Slots *slots;
    s32 playing;

    view->context->result = Gsky_FindNearestCamera(&g_frontendScreenStatus, &view->position);
    playing = alSndpGetState(selectChannel_channel_startnotevoice(view->context, view->slot));
    if (view->time <= g_voicePlaybackTimeThreshold || ((view->flags & 4) && view->finished == 0)) {
        view->done = 1;
    }
    if (view->followTrack != 0 && view->context->track != view->trackId) {
        view->done = 1;
    }
    if (playing != 0) {
        if (view->done != 0) {
            view->done = 1;
            view->tracked = 0;
            context = view->context;
            if (view->frame != context->frame) {
                channel = ((AudioOwnerView *)context)->sound;
                alSndpSetSound(channel, context->slots.ids[view->slot]);
                if (alSndpGetState(channel) != 0) {
                    alSndpStop(channel);
                }
                view->handle = -1;
            }
            return;
        }
    } else if (view->hold > 0) {
        view->hold--;
        view->flags |= 0x10;
        return;
    }
    if ((view->flags & 0x18) == 0x10) {
        alSndpPlay(((AudioOwnerView *)view->context)->sound);
        return;
    }
    if (playing == 0) {
        context = view->context;
        slots = &context->slots;
        alSndpDeallocate(((AudioOwnerView *)context)->sound, slots->ids[view->slot]);
        slots->ids[view->slot] = -1;
        view->reserved38 = 0;
        view->reservedC = -1;
        view->reserved8 = -1;
        view->trackId = -1;
        view->reserved3A = -1;
        view->reservedB4 = -1;
        return;
    }
    if (view->tracked != 0) {
        view->position = *view->tracked;
    }
    Channel_UpdateVoiceVolume(view);
    Channel_UpdateVoicePan(view);
    Channel_UpdateVoicePitch(view);
}

/* Picks the voice slot for a new sound of the given priority: the first of the sixteen slots with no sound, else the
 * lowest-priority voice below the new priority (priority 100 voices are never taken). A taken voice is released and the
 * call returns 16 (the spare voice) when that one is free, else -1. -1 also when no voice is low enough. */
s16 Channel_SelectVoiceSlot(RecordD90 *record, s32 variant, s32 count, s16 priority, s32 soundFlags) {
    AudioVoiceContextView *context;
    Slots *slots;
    SlotCC *voice;
    VoiceQueueNode *waiting;
    s32 voicePriority;
    s32 best;
    s32 selected;
    s32 i;

    context = (AudioVoiceContextView *)record->header;
    slots = &context->slots;
    best = priority;
    selected = -1;
    voice = record->slots;
    for (i = 0; i < 16; i++) {
        if (slots->ids[i] == -1) {
            return i;
        }
        voicePriority = voice->priority;
        if (voicePriority < priority && best >= voicePriority && voicePriority != 100) {
            best = voicePriority;
            selected = i;
        }
        voice++;
    }
    if (selected == -1) {
        return -1;
    }
    if (slots->ids[selected] == -1) {
        waiting = context->queue.next;
        if (waiting != &context->queue && waiting->priority > priority) {
            return -1;
        }
        return selected;
    }
    release(&record->slots[(s16)selected]);
    if (record->slots[16].serial != -1) {
        return -1;
    }
    return 16;
}

typedef struct SoundBankState {
    ALBank *bank;
    char pad4[4];
    char pool[88];
    s16 slots[16];
    u16 allocated;
    char pad82[4];
    s16 current;
} SoundBankState;
typedef struct SoundEngine {
    char pad0[0x7C];
    SoundBankState state;
    s32 effect;
    s32 serial;
    char pad10C[0x2B8C - 0x10C];
    s16 priorityTable;
    char pad2B8E[2];
    s32 f2B90;
    char pad2B94[0x2BAC - 0x2B94];
    s32 f2BAC;
    char pad2BB0[0x2BBC - 0x2BB0];
    f32 f2BBC;
} SoundEngine;
typedef struct SoundVoiceParameters {
    s32 effect;
    char pad4[4];
    s32 reach;
    s32 reachCopy;
    s16 pitchOffset;
    char pad12[2];
    s32 zero24;
    s16 pan;
    char pad1A[0xA];
    f32 gain;
    s16 priority;
    s16 note;
    s16 variant;
    char pad2E[0x12];
    s32 zero50;
    u8 mode;
} SoundVoiceParameters;
typedef struct SoundVoice {
    char pad0[4];
    s32 userData;
    s32 slot;
    s32 serial;
    SoundVoiceParameters parameters;
    char pad58[0x48];
    s32 noteLength;
    s32 noteWord;
    s32 f_A8;
    s32 zeroAC;
    char padB0[4];
    s32 f_B4;
    f32 f_B8;
    s32 flagBC;
    s32 f_C0;
    s32 flagC4;
    char padC8[4];
} SoundVoice;
typedef struct SoundPlayer {
    SoundEngine *engine;
    SoundVoice voices[1];
} SoundPlayer;

/* Starts a note on a free voice: picks the voice with Channel_SelectVoiceSlot, asks the sound set for its sample, and
 * fills in the voice record (volume, pan, pitch, which categories its effect belongs to). Returns the voice, or
 * 0 when the note's set is too small, the chance roll fails, or no voice or sample is available. */
SoundVoice *Channel_StartNoteVoice(SoundPlayer *player, SoundDescriptor *note, s32 variant, s32 userData) {
    SoundEngine *engine;
    SoundVoice *voice;
    s16 *slots;
    s16 index;
    s16 slot;
    s16 priority;
    s32 count;
    s32 roll;
    s32 i;
    f32 pitch;
    u32 pitchByte;
    s8 notePitch;
    SoundBankState *state;
    SoundVoiceParameters *parameters;
    char *pool;

    count = SoundInfo_GetGroup(note);
    priority = (s8)SoundInfo_GetPriority(note);
    engine = player->engine;
    slots = engine->state.slots;
    if (player->engine->state.bank->instArray[0]->soundCount < count) {
        return 0;
    }
    Sound_AcquireContextLock((s32 *)engine);
    if ((s8)SoundInfo_GetMode(note) != 100) {
        roll = Graphu64_NextRandomValue();
        roll %= 100;
        roll = roll < (s8)SoundInfo_GetMode(note);
        if (!roll) {
            goto fail;
        }
    }
    index = Channel_SelectVoiceSlot((RecordD90 *)player, (s16)variant, count, priority, (s16)SoundInfo_GetFlags(note));
    if (index == -1) {
        goto fail;
    }
    voice = &player->voices[index];
    if (index == 16) {
        voice->userData = userData;
        voice->serial = player->engine->serial++;
        voice->slot = 99;
    } else {
        player->engine->state.current = index;
        state = &player->engine->state;
        pool = state->pool;
        slot = alSndpAllocate(pool, (s32)state->bank->instArray[0]->soundArray[count]);
        slots[index] = slot;
        if (slot == -1) {
            voice->serial = -1;
            voice->slot = -1;
            voice->parameters.priority = 0;
            player->engine->state.current = -1;
            fail:
            Sound_ReleaseContextLock((s32 *)player->engine);
            return 0;
        }
        pitch = (f32)priority * 1.27f;
        state->allocated++;
        voice->userData = userData;
        voice->serial = player->engine->serial++;
        voice->slot = slots[index];
        voice->noteLength = note->sample;
        pitchByte = (u32)pitch;
        alSndpSetPriority(pool, slots[index], pitchByte & 0xFF);
    }
    voice->f_A8 = player->engine->priorityTable;
    voice->f_C0 = player->engine->f2BAC;
    voice->flagBC = 0;
    for (i = 0; i < 4; i++) {
        if (voice->f_A8 == g_noteVoicePrimaryKeyTable[i]) {
            voice->flagBC = 1;
            break;
        }
    }
    voice->flagC4 = 1;
    for (i = 0; i < 6; i++) {
        if (voice->f_A8 == g_noteVoiceSecondaryKeyTable[i]) {
            voice->flagC4 = 0;
            break;
        }
    }
    voice->f_B4 = player->engine->f2B90;
    voice->zeroAC = 0;
    voice->f_B8 = player->engine->f2BBC;
    parameters = &voice->parameters;
    parameters->priority = priority;
    parameters->reachCopy = 32000;
    parameters->reach = 32000;
    parameters->zero24 = 0;
    notePitch = note->pitch;
    parameters->pan = 64;
    parameters->note = count;
    parameters->variant = variant;
    parameters->pitchOffset = notePitch;
    voice->parameters.effect = player->engine->effect;
    parameters->gain = 1.0f;
    parameters->mode = SoundInfo_GetPan(note);
    voice->noteWord = (s16)SoundInfo_GetFlags(note);
    parameters->zero50 = 0;
    Sound_ReleaseContextLock((s32 *)player->engine);
    return voice;
}

/* VOICE.CPP */

/* Releases occupied nonlocal slots unless their value equals the exclusion. */

/* Stops the selected sound slot and sets its release flag; split unsigned offset-to-pointer casts and a one-pass statement group preserve the separate table and offset schedule. */

/* Returns how strongly a listener hears a source: one minus the squared distance over the squared range g_spatialSoundRangeSquared (zero beyond it), shaped by the source's curve as the eighth power, the square or the plain value. */

void Audio_StopVoicesExceptKey(VoiceStopKeyTable *record, s32 value)
{
    s32 i;
    s32 active;
    s32 absent;
    AudioVoiceStopKeySlotView *slot = record->slots;
    i = 0;
    absent = -1;
    active = 1;
    for (; i < 16; slot++, i++)
    {
        if (((slot->used != absent) && (record->header->local != i)) && ((value == absent) || (slot->value != value)))
        {
            AudioSoundPlayerOwnerView *owner = slot->owner;
            void *sound;
            slot->active = active;
            slot->flag = 0;
            if (slot->key != owner->key)
            {
                sound = owner->sound;
                alSndpSetSound(sound, owner->samples[slot->index]);
                if (alSndpGetState(sound) != 0)
                {
                    if (active)
                    {
                        alSndpStop(sound);
                    }
                    else
                    {
                        alSndpStop(sound);
                    }
                }
                slot->state = absent;
            }
        }
    }

}

/* Initialises a voice record: its link and handle fields become -1, it stores its owner and slot index, its
   counters and flags are cleared, one flag is set, and three float fields take g_initialVoiceUnitScale. */

void Audio_InitializeVoiceRecord(void *voiceRecord, int owner, int slotIndex) {
    AudioVoiceRecordView *slot = voiceRecord;
    float unitScale = g_initialVoiceUnitScale;

    slot->f0C = -1;
    slot->f08 = -1;
    slot->f3A = -1;
    slot->f40 = -1;
    slot->fB4 = -1;
    slot->owner = owner;
    slot->index = slotIndex;
    slot->f38 = 0;
    slot->f14 = 0;
    slot->f58 = 0;
    slot->f5C = 0;
    slot->fA4 = 0;
    slot->fAC = 0;
    slot->fBC = 0;
    slot->fC0 = 0;
    slot->fC4 = 1;
    slot->f2C = unitScale;
    slot->f34 = unitScale;
    slot->fB8 = unitScale;
}

void Audio_InitializeVoicePool(s32 *voicePool, s32 ownerAddress) {
    s32 i;
    s32 idx;
    f32 t;
    f32 p;
    s32 off;
    AudioVoiceRecordView *rec;
    f32 k1;
    f32 k2;
    f32 k3;
    s32 negone;
    s32 one;

    i = 0;
    k1 = g_voiceAttenuationInputScale;
    k2 = g_voiceAttenuationOutputScale;
    *voicePool = ownerAddress;
    do {
        t = (f32)i * k1;
        p = t * t * t * t * t * k2;
        idx = 90 - i;
        i += 1;
        g_voiceAttenuationTable[idx] = (s16)(s32)p;
    } while (i < 91);

    negone = -1;
    i = 0;
    k3 = g_voicePoolInitialUnitScale;
    one = 1;
    off = i;
    do {
        rec = (AudioVoiceRecordView *)((u32)off + (u32)voicePool);
        rec = &((VoiceRecordHolder *)(rec))->record;
        rec->index = i;
        i += 1;
        rec->owner = ownerAddress;
        rec->f0C = negone;
        rec->f08 = negone;
        rec->f3A = (s16)negone;
        rec->f38 = 0;
        rec->f40 = negone;
        rec->f14 = 0;
        rec->f2C = k3;
        rec->f58 = 0;
        rec->f5C = 0;
        rec->f34 = k3;
        rec->fA4 = 0;
        rec->fAC = 0;
        rec->fB4 = negone;
        rec->fB8 = k3;
        rec->fBC = 0;
        rec->fC0 = 0;
        rec->fC4 = one;
        off += 204;
    } while (i < 17);
}

s32 Audio_GetVoiceSoundState(AudioVoiceSoundSlotView *voicePool, s16 slotIndex)
{
    s32 voiceAddress;
    s32 ownerAddress;
    void *soundPlayer;
    AudioVoiceRecordView *slot;
    AudioSoundPlayerOwnerView *owner;
    voiceAddress = (slotIndex * 204) + (s32)voicePool;
    voiceAddress = voiceAddress + 4;
    slot = (AudioVoiceRecordView *)voiceAddress;
    ownerAddress = slot->owner;
    owner = (AudioSoundPlayerOwnerView *)ownerAddress;
    soundPlayer = owner->sound;
    alSndpSetSound(soundPlayer, owner->samples[slot->index]);
    return alSndpGetState(soundPlayer);
}

void Audio_PlayVoiceSound(AudioVoiceSoundSlotView *base, s16 index)
{
    unsigned int offset = index * (sizeof(AudioVoiceSoundSlotView));
    unsigned int entry = offset;
    AudioVoiceSoundSlotView *slots;
    AudioVoiceSoundSlotView *selected;
    entry += (unsigned int) base;
    slots = base;
    do { alSndpPlay(&((AudioSoundPlayerOwnerView *)((AudioVoiceSoundSlotView *) entry)->owner)->sound); entry = (unsigned int) slots; entry += offset; selected = (AudioVoiceSoundSlotView *) entry; } while (0);
    selected->flags |= 8;
}

s32 Audio_ReleaseMatchingExclusiveVoice(RecordD90 *record, s16 value, s16 id) {
    s32 i;
    SlotCC *cur = record->slots;

    for (i = 0; i < 16; cur++, i++) {
        if (cur->used != -1 && record->header->local != i && cur->value == value && (cur->mode & 0x40) &&
            cur->id == id) {
            release(&record->slots[(s16)i]);
            return (s16)i;
        }
    }
    return -1;
}

/* Returns whether any of the sixteen occupied slots of a record, other than the one its header marks as local, holds the given key value. */

s32 Audio_HasVoiceWithKey(VoiceKeyTable *record, s32 value) {
    s32 i;
    AudioVoiceKeySlotView *slot = record->slots;

    for (i = 0; i < 16; i++, slot++) {
        if (slot->used != -1 && record->header->local != i && slot->value == value) {
            return 1;
        }
    }
    return 0;
}

/* Marks one voice slot of the pool finished and, when its key no longer matches the owner's, stops that sound. */
void Audio_StopVoiceSlot(s32 voicePoolAddress, s16 slotIndex) {
    s32 base;
    s32 a0;
    void *s1;

    base = (slotIndex * 204) + voicePoolAddress;
    base = base + 4;
    a0 = ((struct IntegerStateB4 *) base)->context;
    ((struct IntegerStateB4 *) base)->done = 1;
    ((struct IntegerStateB4 *) base)->tracked = 0;
    s1 = (void *)(a0 + 132);
    if (((struct IntegerStateB4 *) base)->frame != ((struct VoiceMatchingKeyView *) a0)->voiceKey) {
        s32 idx = ((struct IntegerStateB4 *) base)->slotIndex;
        s32 addr = a0 + idx * 2;
        alSndpSetSound(s1, ((struct SoundSlotHandleView *) addr)->soundId);
        if (alSndpGetState(s1) != 0) {
            alSndpStop(s1);
        }
        ((struct IntegerStateB4 *) base)->handle = -1;
    }
}

void Audio_ClearVoiceFlags(s32 a) {
    s32 remainingSlots;
    void *slotCursor;
    slotCursor = a + 4;
    remainingSlots = 16;
    do {
        ((SlotCC *)slotCursor)->flag = 0;
        remainingSlots -= 1;
        slotCursor += sizeof(AudioVoiceKeyedSlotView);
    } while (remainingSlots >= 0);
}

void Audio_SetVoicePositionTracking(void *voiceRecord, void *initialPosition, int trackedPositionAddress) {
    ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->position = *(Triple *)initialPosition;
    ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->tracked = (Triple *)trackedPositionAddress;
}

void Audio_SetVoiceTrackId(void *voiceRecord, int newTrackId) {
    ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->trackId = newTrackId;
}

void Audio_InitializeVoiceParameters(void *voiceRecord, void *desc, s32 extra) {
    f32 first;
    s16 index;
    s16 value;
    void *record;

    Channel_InitializeVoicePitchMotion(voiceRecord, desc, extra);
    Channel_InitializeVoiceMix(voiceRecord, desc, extra);
    ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->priority = 64;
    index = ((struct Shared_Body *)(desc))->kind;
    if (index != -1) {
        record = Audio_GetMetadataSectionFiveEntry(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->context, index);
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope = *(SoundEnvelope *)record;
        first = RW_BITS_TO_FLOAT(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope.initial);
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->step =
            (first - RW_BITS_TO_FLOAT(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope.target)) /
            ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope.frames;
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->value =
            RW_BITS_TO_FLOAT(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope.initial);
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->priority =
            (s16)(s32)RW_BITS_TO_FLOAT(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope.initial);
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->sweeping = 1;
        return;
    }

    ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->sweeping = 0;
    if (((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->trackId < 256) {
        if (((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->fixed == 0 &&
            Audio_GetSpatialPanMode(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->context) != 0) {
            value = (s8)((GameAudioContext *)((struct ViewChannelUpdateVoicePlayback *)voiceRecord)->context)->randomPan;
            goto store_value;
        }
    } else if (((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->fixed == 0 &&
        Audio_GetSpatialPanMode(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->context) != 0) {
        value = Channel_ComputeListenerRelativePan(&((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->position,
            ((struct ViewChannelUpdateVoicePlayback *)voiceRecord)->context->result);
        store_value:
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->priority = value;
    }
}

void Audio_UpdateVoicePool(void **voicePool) {
    s32 i;
    s32 activeVoiceCount;
    char *view;

    activeVoiceCount = 0;
    view = (char *)((RecordD90 *)voicePool)->slots;
    i = 0;
    do {
        if (((SlotCC *)view)->used != -1 && ((AudioSelectedHandleView *)(*voicePool))->local != i) {
            Channel_UpdateVoicePlayback(view);
            activeVoiceCount += 1;
        }
        i += 1;
        view += sizeof(AudioVoiceKeyedSlotView);
    } while (i < 16);
    g_audioPitchRatioCurveZeroWords.activeVoiceCount = activeVoiceCount;
    if (g_peakActiveVoiceCount < activeVoiceCount) {
        g_peakActiveVoiceCount = activeVoiceCount;
    }
}

/* Returns the index of the first of sixteen slots that is in use, is not the
   owner's own slot and whose two keys at 0xA0 and 0xAC equal the arguments, or -1 when none does; indexing from the second key reproduces the reference induction base. */

int Audio_FindVoiceByKeyPair(VoiceKeyPairTable *obj, int keyA, int keyB) {
    int i;
    int *keys = &obj->slots[0].keyB;

    for (i = 0; i < 16; i++) {
        if (keys[i * 51 - 43] != -1 && obj->owner->local != i && keys[i * 51 - 3] == keyA &&
            keys[i * 51] == keyB) {
            return i;
        }
    }
    return -1;
}

void Audio_StopVoicesByKey(VoiceStopKeyTable *record, s32 value) {
    s32 i;
    AudioVoiceStopKeySlotView *slot = record->slots;

    for (i = 0; i < 17; slot++, i++) {
        if (slot->used != -1 && record->header->local != i && slot->value == value) {
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
    }
}

void Audio_StopVoicesBySecondaryValue(VoiceSecondaryKeyTable *record, s32 value) {
    s32 i;
    AudioVoiceSecondarySlotView *slot = record->slots;

    for (i = 0; i < 17; slot++, i++) {
        if (slot->used != -1 && record->header->local != i && slot->value == value) {
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
    }
}

void Audio_StopVoicesByFlags(AudioVoiceFlagsPoolView *record, s32 value) {
    s32 i;
    AudioVoiceControlSlotView *slot = record->slots;

    for (i = 0; i < 17; slot++, i++) {
        if (slot->used != -1 && record->header->local != i && (slot->mask & value) != 0) {
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
    }
}

f32 Audio_ComputeDistanceAttenuation(f32 *a, f32 *b) {
    f32 dx = a[0] - b[0];
    f32 dy = a[1] - b[1];
    f32 dz = a[2] - b[2];
    f32 distSq = (dx * dx) + (dy * dy) + (dz * dz);
    if (g_spatialSoundRangeSquared <= distSq) {
        return 0.0f;
    }
    return g_voiceDistanceAttenuationConstants - (distSq / g_spatialSoundRangeSquared);
}

/* Returns whether any of the seventeen occupied slots of a record, other than the one its header marks as local, holds the given key value. */

s32 Audio_HasVoiceOrReservedSlotWithKey(VoiceKeyTable *record, s32 value) {
    s32 i;
    AudioVoiceKeySlotView *slot = record->slots;

    for (i = 0; i < 17; i++, slot++) {
        if (slot->used != -1 && record->header->local != i && slot->value == value) {
            return 1;
        }
    }
    return 0;
}

f32 Audio_InterpolatePitchTable(f32 pitch)
{
    f32 tableCoordinate;
    f32 lowerCoordinate;
    f32 lowerPitch;
    s32 integerCoordinate;
    s16 sampleIndex;
    s32 nextSampleIndex;
    tableCoordinate = (pitch + (&g_voiceDistanceAttenuationConstants)[1]) * g_pitchTableInputScale;
    integerCoordinate = (s32) tableCoordinate;
    sampleIndex = (s16) integerCoordinate;
    lowerCoordinate = (f32) sampleIndex;
    if (lowerCoordinate != tableCoordinate)
    {
        nextSampleIndex = integerCoordinate + 1;
        lowerPitch = (&g_voicePitchTableBase)[1 + sampleIndex];
        return lowerPitch + ((tableCoordinate - lowerCoordinate) * ((&g_voicePitchTableBase)[1 + ((s16) nextSampleIndex)] - lowerPitch));
    }
    return (&g_voicePitchTableBase)[1 + sampleIndex];
}

s16 Audio_RandomizeSignedRange(s16 center, s16 range) {
    f32 centerValue;
    f32 rangeValue;
    rangeValue = (f32)range;
    centerValue = (f32)center;
    return (s16)(s32)(Graphu64_RandomBetween(rangeValue, centerValue) < 0.0f
        ? centerValue - Graphu64_RandomBetween(rangeValue, centerValue)
        : centerValue + Graphu64_RandomBetween(rangeValue, centerValue));
}

f32 Audio_RandomizeScaledByteRange(u8 minimum, u8 maximum) {
    f32 first;
    f32 second;

    first = minimum * g_voiceByteRangeScale;
    second = maximum * g_voiceByteRangeScale;
    if (first == g_voiceByteRangeIdentity) {
        return g_voiceByteRangeIdentity;
    }
    if (second == first) {
        return first;
    }
    return first + Graphu64_RandomFloat(second - first);
}

f32 Audio_ComputeSpatialAttenuationCurve(char *source, char *listener)
{
    SoundSpatialSource *sound = (SoundSpatialSource *)source;
    GameplayCamera *camera = (GameplayCamera *)listener;
    CVector3 *a = &sound->position;
    CVector3 *b = &camera->position;
    f32 dx = a->x - b->x;
    f32 dy;
    f32 dz;
    f32 d;
    f32 t;

    dx *= dx;
    dy = a->y - b->y;
    dy *= dy;
    dz = a->z - b->z;
    dz *= dz;
    d = dx + dy + dz;
    if (d >= g_spatialSoundRangeSquared) {
        t = 0.0f;
    } else {
        t = g_spatialAttenuationUnitScale - d / g_spatialSoundRangeSquared;
    }
    switch (sound->curve) {
    case 2:
        return t;
    case 0:
        t *= t;
        t *= t;
    case 1:
        return t * t;
    default:
        return 0.0f;
    }
}

void Audio_SetScaledVoiceVolume(void *voiceRecord, s32 volume) {
    AudioVoiceRecordView *slot = voiceRecord;
    AudioSoundPlayerOwnerView *owner;
    s32 ownerValue;
    void *sound;

    ownerValue = slot->owner;
    owner = (AudioSoundPlayerOwnerView *)ownerValue;
    sound = owner->sound;
    alSndpSetSound(sound, owner->samples[slot->index]);
    alSndpSetVol(sound, (s16)(s32)((f32) volume * (slot->fC8)));
}

void Audio_SetScaledVoicePitch(void *voiceRecord, f32 pitch) {
    AudioVoiceRecordView *slot = voiceRecord;
    AudioSoundPlayerOwnerView *owner;
    s32 ownerValue;
    void *sound;
    f32 scaled;

    ownerValue = slot->owner;
    owner = (AudioSoundPlayerOwnerView *)ownerValue;
    sound = owner->sound;
    alSndpSetSound(sound, owner->samples[slot->index]);
    scaled = pitch * (slot->f34);
    scaled = scaled * (slot->fB8);
    alSndpSetPitch(sound, scaled);
}

ALSndPlayer;

void Audio_SetVoicePan(AudioVoiceControlSlotView *voiceRecord, s32 panValue)
{
    s32 *slotIndexPointer;
    int unusedPanMode;
    s32 ownerAddress;
    void *soundPlayer;
    ownerAddress = (s32)voiceRecord->owner;
    soundPlayer = &((AudioSoundPlayerOwnerView *)ownerAddress)->sound;
    unusedPanMode = 2;
    slotIndexPointer = &voiceRecord->index;
    alSndpSetSound(soundPlayer, ((AudioSoundPlayerOwnerView *)ownerAddress)->samples[*slotIndexPointer]);
    alSndpSetPan(soundPlayer, panValue & 0xFF);
}

void Audio_QueryVoicePlaybackState(AudioVoiceControlSlotView *voiceRecord)
{
    s16 *unusedPointer1;
    s32 ownerAddress;
    void *soundPlayer;
    ownerAddress = (s32)voiceRecord->owner;
    soundPlayer = &((AudioSoundPlayerOwnerView *)ownerAddress)->sound;
    alSndpSetSound(soundPlayer, ((AudioSoundPlayerOwnerView *)ownerAddress)->samples[voiceRecord->index]);
    alSndpGetState(soundPlayer);
}

void Audio_StartSelectedVoice(AudioVoiceControlSlotView *voiceRecord) {
    alSndpPlay(voiceRecord->owner->sound);
}

/* Marks a voice record finished and, when its key no longer matches the owner's, stops that sound. */
void Audio_StopVoiceForDifferentKey(AudioVoiceControlSlotView *voiceRecord) {
    s32 ownerValue;
    void *soundPlayer;

    ownerValue = voiceRecord->owner;
    voiceRecord->active = 1;
    voiceRecord->flag = 0;
    soundPlayer = (void *)(ownerValue + 132);
    if (voiceRecord->key != ((AudioSoundPlayerOwnerView *)ownerValue)->key) {
        alSndpSetSound(soundPlayer, ((AudioSoundPlayerOwnerView *)ownerValue)->samples[voiceRecord->index]);
        if (alSndpGetState(soundPlayer) != 0) {
            alSndpStop(soundPlayer);
        }
        voiceRecord->state = -1;
    }
}

void Audio_DeallocateVoiceSlot(AudioVoiceControlSlotView *voiceRecord) {
    void *base;
    Slots *arrayBase;
    short *slot;
    base = voiceRecord->owner;
    arrayBase = &((AudioVoiceContextView *)base)->slots;
    alSndpDeallocate(((AudioSoundPlayerOwnerView *)base)->sound, arrayBase->ids[voiceRecord->index]);
    arrayBase->ids[voiceRecord->index] = -1;
    voiceRecord->priority = 0;
    voiceRecord->releaseMarker = -1;
    voiceRecord->used = -1;
    voiceRecord->value = -1;
    voiceRecord->channel = -1;
    voiceRecord->releaseMarkerB = -1;
}

typedef struct {
    u16 key;
    u16 start;
    u16 end;
    s16 duration;
    u16 reserved[2];
} VoiceEnvelopeBlock;

struct GameAudioContext;
struct GameplayCamera;

typedef struct VoicePanEnvelopeState VoicePanEnvelopeState;
typedef struct SoundPanEnvelopeDescriptor SoundPanEnvelopeDescriptor;
typedef struct VoicePanContextView VoicePanContextView;
struct VoicePanEnvelopeState {
    char pad0[0x28];
    s16 pan;
    char pad28[0x44 - 0x28 - sizeof(s16)];
    char position;
    char pad44[0x88 - 0x44 - sizeof(char)];
    s32 sweeping;
    char pad88[0x8C - 0x88 - sizeof(s32)];
    VoiceEnvelopeBlock envelope;
    char pad8C[0x98 - 0x8C - sizeof(VoiceEnvelopeBlock)];
    f32 envelopeValue;
    char pad98[0x9C - 0x98 - sizeof(f32)];
    f32 envelopeStep;
    char pad9C[0xA8 - 0x9C - sizeof(f32)];
    s32 trackId;
    char padA8[0xB0 - 0xA8 - sizeof(s32)];
    VoicePanContextView *context;
    char padB0[0xC0 - 0xB0 - sizeof(void*)];
    s32 fixedPan;
};
struct SoundPanEnvelopeDescriptor {
    char pad0[0xC];
    s16 panEnvelopeIndex;
};
struct VoicePanContextView {
    char pad0[0x2B94];
    s8 randomPan;
    char pad2B94[0x2B98 - 0x2B94 - sizeof(s8)];
    s32 listenerCameraAddress;
};

void Audio_InitVoiceVolume(VoicePanEnvelopeState *voiceRecord, SoundPanEnvelopeDescriptor *soundDescriptor) {
    f32 first;
    s16 index;
    s16 value;
    VoiceEnvelopeBlock *record;

    voiceRecord->pan = 64;
    index = soundDescriptor->panEnvelopeIndex;
    if (index != -1) {
        record = Audio_GetMetadataSectionFiveEntry(voiceRecord->context, index);
        voiceRecord->envelope = *record;
        first = Menu_ExpandFloatHighWord(voiceRecord->envelope.start);
        voiceRecord->envelopeStep =
            (first - Menu_ExpandFloatHighWord(voiceRecord->envelope.end)) /
            voiceRecord->envelope.duration;
        voiceRecord->envelopeValue =
            Menu_ExpandFloatHighWord(voiceRecord->envelope.start);
        voiceRecord->pan =
            (s16)(s32)Menu_ExpandFloatHighWord(voiceRecord->envelope.start);
        voiceRecord->sweeping = 1;
        return;
    }

    voiceRecord->sweeping = 0;
    if (voiceRecord->trackId < 256) {
        if (voiceRecord->fixedPan == 0 &&
            Audio_GetSpatialPanMode(voiceRecord->context) != 0) {
            value = voiceRecord->context->randomPan;
            goto store_value;
        }
    } else if (voiceRecord->fixedPan == 0 &&
        Audio_GetSpatialPanMode(voiceRecord->context) != 0) {
        value = Channel_ComputeListenerRelativePan(&voiceRecord->position,
            voiceRecord->context->listenerCameraAddress);
        store_value:
        voiceRecord->pan = value;
    }
}

static inline short slot_id(Slots *slots, int index) {
    return slots->ids[index];
}

int Audio_DeallocatePoolVoice(AudioVoiceFlagsPoolView *pool, short index) {
    AudioVoiceControlSlotView *entry;
    AudioVoiceContextView *context;
    Slots *slots;
    void *owner;

    entry = &pool->slots[index + 1];
    entry--;
    owner = entry->owner;
    context = owner;
    slots = &context->slots;
    alSndpDeallocate(entry->owner->sound, slot_id(slots, entry->index));
    slots->ids[entry->index] = -1;
    entry->priority = 0;
    entry->releaseMarker = -1;
    entry->used = -1;
    entry->value = -1;
    entry->channel = -1;
    entry->releaseMarkerB = -1;
    return 0;
}

/** Reset a looping-sound voice node: its state and value become -1. */
void SoundVoicePool_ResetNode(void *cLoopingSoundData) {
    CLoopingSoundData *voice = cLoopingSoundData;
    voice->state = -1;
    voice->value = -1;
}

void SoundVoicePool_ResetNodeNoOp(void) {
}

void SoundVoicePool_Initialize(void *soundVoicePool, CLoopingSoundData *availableNodes, s32 nodeCount) {
    s32 i;

    List_InitializeIntrusive(soundVoicePool, 0, 4);
    List_InitializeIntrusive(&((SoundVoicePool *)soundVoicePool)->playing, 0, 4);
    i = 0;
    if (nodeCount > 0) {
        do {
            List_AppendIntrusive(soundVoicePool, availableNodes);
            i += 1;
            availableNodes = availableNodes + 1;
        } while (i < nodeCount);
    }
    ((SoundVoicePool *)soundVoicePool)->state = 0;
}

void *SoundVoicePool_PlaySpatialSound(void *voicePool, s32 soundId, CVector3 *soundPosition, void *position, s32 fallback) {
    CLoopingSoundData *node;
    s32 result;

    node = ((SoundVoicePool *)voicePool)->available.head;
    if (node != 0) {
        List_RemoveIntrusive(voicePool, node);
        List_AppendIntrusive(&((SoundVoicePool *)voicePool)->playing, node);
        node->state = -1;
        node->value = -1;
        result = SoundElement_PlaySoundAtPosition((s16)soundId, *soundPosition,
            (s32)position, fallback);
        node->value = result;
        g_lastStartedPoolSoundHandle = result;
        node->state = soundId;
        node->m_vSoundPos = *soundPosition;
        node->m_vSoundPosPtr = position;
    }
    return node;
}

s32 SoundVoicePool_StopNode(void *work, void *wantedNode) {
    void *playingNode;

    if (wantedNode == 0) {
        return 0;
    }

    playingNode = ((SoundVoicePool *)work)->playing.head;
    if (playingNode != 0) {
        do {
            if (playingNode == wantedNode) {
                SoundElement_StopSoundsByIdentifier(((CLoopingSoundData *)playingNode)->value);
                g_lastStoppedPoolSoundHandle = ((CLoopingSoundData *)playingNode)->value;
                List_RemoveIntrusive(&((SoundVoicePool *)work)->playing, playingNode);
                List_AppendIntrusive(work, playingNode);
                return 1;
            }
            playingNode = ((CLoopingSoundData *)playingNode)->next;
        } while (playingNode != 0);
    }
    return 0;
}

void SoundVoicePool_Pause(void *voicePool) {
    s32 value;
    SoundVoicePool *pool = voicePool;
    CLoopingSoundData *playingNode;

    playingNode = pool->playing.head;
    if (playingNode != 0) {
        do {
            SoundElement_StopSoundsByIdentifier(playingNode->value);
            value = playingNode->value;
            playingNode = playingNode->next;
            g_lastPausedPoolSoundHandle = value;
        } while (playingNode != 0);
    }
    pool->state = 1;
}

void SoundVoicePool_Resume(SoundVoicePool *soundVoicePool) {
    s32 playbackHandle;
    CLoopingSoundData *playingNode;

    playingNode = soundVoicePool->playing.head;
    if (playingNode != 0) {
        do {
            playbackHandle = SoundElement_PlaySoundAtPosition((s16)playingNode->state,
                playingNode->m_vSoundPos,
                (s32)playingNode->m_vSoundPosPtr,
                -1);
            playingNode->value = playbackHandle;
            playingNode = playingNode->next;
            g_lastResumedPoolSoundHandle = playbackHandle;
        } while (playingNode != 0);
    }
    soundVoicePool->state = 0;
}

void SoundVoicePool_RetireFinishedSounds(void *soundVoicePool) {
    SoundVoicePool *pool = soundVoicePool;
    CLoopingSoundData *playingNode;

    if (pool->state == 0) {
        playingNode = pool->playing.head;
        if (playingNode != 0) {
            do {
                if (SoundElement_CountOwnerVoices(playingNode->value) == 0) {
                    playingNode->state = -1;
                    playingNode->value = -1;
                }
                playingNode = playingNode->next;
            } while (playingNode != 0);
        }
    }
}

void SoundVoicePool_StopAll(void *soundVoicePool) {
    CLoopingSoundData *cur;
    CLoopingSoundData *next;
    s32 value;
    SoundVoicePool *pool = soundVoicePool;

    cur = pool->playing.head;
    if (cur != 0) {
        do {
            value = cur->value;
            next = cur->next;
            SoundElement_StopSoundsByIdentifier(value);
            cur->state = -1;
            cur->value = -1;
            List_RemoveIntrusive(&pool->playing, cur);
            List_AppendIntrusive(&pool->available, cur);
            cur = next;
        } while (cur != 0);
    }
}

/** Return the address of the global state word at g_soundVoicePoolGlobalState. */
s32 *SoundVoicePool_GetGlobalState(void) {
    return &g_soundVoicePoolGlobalState;
}

/** Deliberately perform no work. */
void SoundVoicePool_GetGlobalStateNoOp(void) {
}





#if !(defined(VERSION_US_REV1))
const float g_audio_ComputeDistanceAttenuationConstant[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_audio_ComputeDistanceAttenuationConstant[1] = {
    1.0f,
};
#endif





#if !(defined(VERSION_US_REV1))
const float g_audio_ComputeSpatialAttenuationCurveConstant[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float g_audio_ComputeSpatialAttenuationCurveConstant[1] = {
    1.0f,
};
#endif

/* CHANNEL_COMPUTELISTENERRELATIVEPAN_DATA.CPP */







/* CHANNEL.CPP */





/* CHANNEL_UPDATEVOICEPLAYBACK_DATA.CPP */



/* CHANNEL_UPDATEDISTANCEPITCHFACTOR_DATA.CPP */



/* G_AUDIOPITCHRATIOCURVE.CPP */

float g_audioPitchRatioCurve[121] = {
    0.0313f, 0.0324f, 0.0335f, 0.0347f, 0.0359f, 0.0372f,
    0.0385f, 0.0398f, 0.0412f, 0.0427f, 0.0442f, 0.0458f,
    0.0474f, 0.049f, 0.0508f, 0.0526f, 0.0544f, 0.0563f,
    0.0583f, 0.0604f, 0.0625f, 0.0647f, 0.067f, 0.0693f,
    0.0718f, 0.0743f, 0.0769f, 0.0797f, 0.0825f, 0.0854f,
    0.0884f, 0.0915f, 0.0947f, 0.0981f, 0.1015f, 0.1051f,
    0.1088f, 0.1127f, 0.1166f, 0.1207f, 0.125f, 0.129f,
    0.134f, 0.139f, 0.144f, 0.149f, 0.154f, 0.159f,
    0.165f, 0.171f, 0.177f, 0.183f, 0.189f, 0.196f,
    0.203f, 0.21f, 0.218f, 0.225f, 0.233f, 0.241f,
    0.25f, 0.259f, 0.268f, 0.277f, 0.287f, 0.297f,
    0.308f, 0.319f, 0.33f, 0.342f, 0.354f, 0.366f,
    0.379f, 0.392f, 0.41f, 0.42f, 0.435f, 0.451f,
    0.467f, 0.483f, 0.5f, 0.518f, 0.536f, 0.555f,
    0.574f, 0.595f, 0.616f, 0.637f, 0.66f, 0.683f,
    0.707f, 0.732f, 0.758f, 0.785f, 0.812f, 0.841f,
    0.871f, 0.901f, 0.933f, 0.966f, 1.0f, 1.04f,
    1.07f, 1.11f, 1.15f, 1.2f, 1.23f, 1.28f,
    1.32f, 1.37f, 1.41f, 1.46f, 1.52f, 1.57f,
    1.63f, 1.68f, 1.74f, 1.8f, 1.87f, 1.93f,
    2.0f,
};
#if defined(VERSION_DE)

f32 g_audioPitchRatioCurveTailFloat = 26214400.0f;
#endif
#if defined(VERSION_EU)
f32 g_audioPitchRatioCurveTailFloat = 26214400.0f;
#endif
#if defined(VERSION_EU_X)
f32 g_audioPitchRatioCurveTailFloat = 26214400.0f;
#endif
#if defined(VERSION_US)
f32 g_audioPitchRatioCurveTailFloat = 26214400.0f;
#endif
#if defined(VERSION_US_REV1)
f32 g_audioPitchRatioCurveTailFloat = 26214400.0f;
#endif
#if defined(VERSION_DE)

s32 g_audioPitchRatioCurveUnitTable[10] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1
};
#endif
#if defined(VERSION_EU)
s32 g_audioPitchRatioCurveUnitTable[10] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1
};
#endif
#if defined(VERSION_EU_X)
s32 g_audioPitchRatioCurveUnitTable[10] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1
};
#endif
#if defined(VERSION_US)
s32 g_audioPitchRatioCurveUnitTable[10] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1
};
#endif
#if defined(VERSION_US_REV1)
s32 g_audioPitchRatioCurveUnitTable[10] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1
};
#endif
#ifdef VERSION_DE

AudioVoicePoolState g_audioPitchRatioCurveZeroWords = {
    0x00000000,
    {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7F7F0000, 0x007F2929, 0x29000000,
    },
};
#endif
#ifdef VERSION_EU
AudioVoicePoolState g_audioPitchRatioCurveZeroWords = {
    0x00000000,
    0x00000000,
    "R NOUS AVOIR",
    {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7F7F0000,
        0x007F2929, 0x29000000,
    },
};
#endif
#ifdef VERSION_EU_X
AudioVoicePoolState g_audioPitchRatioCurveZeroWords = {
    0x00000000,
    {
    0x00000000, 0x3F8DA520, 0x3F8D814B, 0x3F8D5D71, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7F7F0000, 0x007F2929, 0x29000000,
    },
};
#endif
#ifdef VERSION_US
AudioVoicePoolState g_audioPitchRatioCurveZeroWords = {
    0x00000000,
    {
    0x00000000, 0x71755200, 0x00260700, 0x0010000B, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7F7F0000, 0x007F2929, 0x29000000,
    },
};
#endif
#ifdef VERSION_US_REV1
AudioVoicePoolState g_audioPitchRatioCurveZeroWords = {
    0x00000000,
    {
    0x00000000, 0x3F8E3441, 0x3F8E1080, 0x3F8DECBA, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7F7F0000, 0x007F2929, 0x29000000,
    },
};
#endif

/* LOOKUPPANVALUE.CPP */
#if defined(VERSION_US_REV1)

EngineVoiceScaleEntry g_soundVolumeScales[31] = {
    { 1.0f, 0.85f }, { 1.0f, 0.85f }, { 1.0f, 0.85f }, { 1.0f, 0.9f }, { 1.0f, 1.0f }, { 1.0f, 1.0f },
    { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f },
    { 1.0f, 1.0f }, { 1.0f, 0.9f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f },
    { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f },
    { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f },
    { 1.0f, 1.0f },
};
#endif

/* Retained data for this translation unit. */
#if !(defined(VERSION_US_REV1))
const float k_Voice[1] = {
    1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float k_voiceUnit[1] = {
    1.0f,
};
#endif

const float g_audio_InitializeVoicePoolConstant[3] = {
    0.011111111f, 3.2e+04f, 1.0f,
};

const float g_audio_InterpolatePitchTableConstant[2] = {
    6.0e+03f, 0.016666668f,
};

const float g_audio_RandomizeScaledByteRangeConstant[2] = {
    0.01f, 1.0f,
};

const float g_audio_InsertChannelLinkConstantWords_us_rev1[3] = {
    1.0e+02f, 1.0f, 64.0f,
};

const float g_channel_InitializeVoicePitchMotionConstant[5] = {
    1.0e+03f, 1.0e+03f, 1.2e+03f, 6.0e+03f, 0.016666668f,
};

const float g_channel_InitializeVoiceMixConstant[6] = {
    1.0f, 0.8f, 0.01f, 1.0f, 1.0f, 1.0f,
};

const float g_channel_UpdateDistancePitchFactorConstant[4] = {
    1.0f, 1.0f, 1.4f, 0.6f,
};

const float g_channel_UpdateVoicePitchConstant[2] = {
    6.0e+03f, 0.016666668f,
};

const float g_channel_UpdateVoicePlaybackConstant[1] = {
    0.075f,
};

float g_voicePitchTableBase = 0.00350000011f;
