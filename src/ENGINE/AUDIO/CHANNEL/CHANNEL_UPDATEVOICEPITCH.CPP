#include "COMMON/OBJRECAT4V6.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "AUDIO/VOICE_AND_SPATIAL_SOURCE_VIEWS.H"
#include "COMMON/TRIPLE.H"
#include "COMMON.H"

/* Ramps a voice pitch toward its target, interpolates the pitch curve and applies its scaled value to the context channel. */

extern void Channel_UpdateDistancePitchFactor(ViewChannelUpdateVoicePitch *);



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
