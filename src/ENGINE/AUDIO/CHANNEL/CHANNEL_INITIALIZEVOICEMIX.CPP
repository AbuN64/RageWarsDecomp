#include "include_asm.h"
#include "COMMON/LISTNODE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "COMMON/OBJRECAT4V6.H"
#include "AUDIO/VOICE_AND_SPATIAL_SOURCE_VIEWS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "AUDIO/LIST_AND_CHANNEL_VIEWS.H"
#include "COMMON/TRIPLE.H"
#include "COMMON.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "COMMON/AUDIO_CONTEXT.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "AUDIO/CHANNEL_INITIALIZEVOICEMIX.H"

/* Returns the stereo pan of a sound at a position for a listener: centre (0x40) without a listener, when
 * the sound is horizontally within a small radius or straight ahead; otherwise the horizontal direction
 * in listener space is compared with the forward axis through Graphu64_ArcCos and Gu_Sinf_SkyPosttargetedscreenmessage, given the
 * side's sign, and scaled around the centre by g_listenerPanCenterAndRange. */

extern void Graphu64_TransformDirectionTranspose(void *, CVector3 *, CVector3 *);



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
extern struct Bytes12 *Audio_GetMetadataSectionFourEntry(GameAudioContext *, s32);
extern unsigned short Menu_GetFloatHighWord(f32);

extern s32 SoundInfo_GetX(SoundDescriptor *);
extern s32 SoundInfo_GetY(SoundDescriptor *);


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
        *(struct Bytes12 *)angles = *Audio_GetMetadataSectionFourEntry(view->presets, controller->preset);
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

#include "ENGINE/AUDIO/CHANNEL.H"

typedef struct VoiceScaleEntry { f32 soundId, scale; } VoiceScaleEntry;
extern VoiceScaleEntry g_soundVolumeScales[];
extern float g_voiceDefaultGain;
extern SoundEnvelope *Audio_GetMetadataSectionThreeEntry(GameAudioContext *context, int index);
static inline s32 lookupPanValue(s32 panAngle) {
    if ((f32)panAngle < 0.0f) return g_voiceAttenuationTable[-panAngle];
    return g_voiceAttenuationTable[panAngle];
}

void Channel_InitializeVoiceMix(Voice *voice, SoundDescriptor *control, s32 unused2) {
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
