#include "Common/music_track_volume.h"
#include "Common/game_session.h"
#include "Common/sharedplayer.h"
#include "types.h"
#include "Engine/Audio/T2SoundElement.h"
#include "Render/soundelement_playflatsound.h"
#include "Common/audio_context.h"
#include "include_asm.h"
#include "Texture/sound_updateaudiocontext.h"
#include "Sound/sound.h"
#include "Audio/audio_chooseweightedsoundvariant.h"
#include "Common/soundinfo.h"
#include "Common/runtime_declarations.h"
#include "System/sound_context_music_and_voice_control.h"
#include "System/sound_context_lock_and_activity.h"
#include "Engine/Audio/T2soundelement/sound_context_control.h"
#include "Audioworld/sound_updateaudiocontext.h"

/* T2SOUNDELEMENT.CPP */

/** Calls Sound_InitializeContext with &g_soundElementContext as its argument. */

void SoundElement_InitializeContext(void) {
    Sound_InitializeContext(&g_soundElementContext);
}

s32 SoundElement_PlaySoundAtPosition(s16 track, CVector3 soundPosition, s32 position, s32 ownerId) {
    if (g_gameSession.transitionBlocked != 0) {
        return -1;
    }
    return Sound_PlaySoundAtPosition(&g_soundElementContext, track, soundPosition, position, ownerId);
}

s32 SoundElement_PlayPositionedSoundWithScale(s32 trackId, CVector3 soundPosition, s32 spatialMode, s32 ownerId, f32 playbackScale) {
    if (g_gameSession.transitionBlocked != 0) {
        return -1;
    }
    return Audio_PlayPositionedSoundWithScale(&g_soundElementContext, (s16)trackId, soundPosition, spatialMode, ownerId, playbackScale);
}

s32 SoundElement_PlayFlatSound(s32 track) {
    s32 playbackResult;
    s32 previousMixValue;

    if (g_gameSession.transitionBlocked != 0) {
        return -1;
    }
    {
        CVector3 vec;
        register f32 zero = 0.0f;

        vec.z = zero;
        vec.y = zero;
        vec.x = zero;
        previousMixValue = Audio_GetVoiceMixValue(&g_soundElementContext);
        Audio_SetVoiceMixValue(&g_soundElementContext, 1);
        playbackResult = Sound_PlaySoundAtPosition(&g_soundElementContext, (s16)track, vec, 0, -1);
        Audio_SetVoiceMixValue(&g_soundElementContext, previousMixValue);
    }
    return playbackResult;
}

s32 SoundElement_PlayInstrumentAtPosition(s32 index, CVector3 position, s32 voiceParameter) {
    if (g_gameSession.transitionBlocked != 0) {
        return -1;
    }
    return Sound_PlayInstrumentAtPosition(&g_soundElementContext, index, position, voiceParameter);
}

int SoundElement_PlayFlatInstrument(int index) {
    int playbackResult;
    int previousMixValue;

    if (g_gameSession.transitionBlocked != 0) {
        return -1;
    }
    {
        CVector3 vec;
        register float zero = (float)0;

        vec.z = zero;
        vec.y = zero;
        vec.x = zero;
        previousMixValue = Audio_GetVoiceMixValue(&g_soundElementContext);
        Audio_SetVoiceMixValue(&g_soundElementContext, 1);
        playbackResult = Sound_PlayInstrumentAtPosition(&g_soundElementContext, index, vec, 0);
        Audio_SetVoiceMixValue(&g_soundElementContext, previousMixValue);
    }
    return playbackResult;
}

/* Return the existing owner-count result to callers that test it. */
s32 SoundElement_CountOwnerVoices(s32 owner)
{
    return Audio_CountSoundVoices((char *)&g_soundElementContext, owner);
}

void SoundElement_PlayDialogGroup(s32 callback) {
    if (g_gameSession.transitionBlocked == 0) {
        Audio_PlayDialogGroup(&g_soundElementContext, callback);
    }
}

void SoundElement_StopDialog(void) {
    Audio_StopContextDialog((intptr_t) &g_soundElementContext);
}

void SoundElement_StopSoundsByIdentifier(s32 soundId) {
    Sound_StopSoundsByIdentifier(&g_soundElementContext, soundId);
}

void SoundElement_StopAudioByKey(s32 matchingKey) {
    Audio_StopAudioByKey(&g_soundElementContext, matchingKey);
}

void SoundElement_StopAudioBySecondaryValue(s32 matchingValue) {
    Audio_StopAudioBySecondaryValue(&g_soundElementContext, matchingValue);
}

void SoundElement_StopAudioByMask(s32 matchingFlags) {
    Audio_StopAudioByMask(&g_soundElementContext, matchingFlags);
}

void SoundElement_StopAudioExceptKey(s32 retainedKey) {
    Audio_StopAudioExceptKey(&g_soundElementContext, retainedKey);
}

void SoundElement_UpdateContext(void) {
    Sound_UpdateAudioContext(&g_soundElementContext);
}

/* SOUND_CONTEXT_CONTROL.CPP */

struct AudioLevelSettingView; void Audio_SetClampedAudioLevel(struct AudioLevelSettingView *obj, float value);

void SoundElement_SetTrackAndPeriodicPlayback(int trackId)
{
    int hasTrack;
    hasTrack = trackId != 0;
    g_soundElementContext.track = (s32) trackId;
    if (hasTrack)
    {
        if (1)
        {
            SoundElement_EnablePeriodicSound();
        }
        return;
    }
    SoundElement_DisablePeriodicSound();
}

void SoundElement_SetVoiceMixValue(s32 mixValue) {
    Audio_SetVoiceMixValue(&g_soundElementContext, mixValue);
}

int SoundElement_GetMusicPlaybackEnabled(void) {
    return g_musicPlaybackEnabled;
}

void SoundElement_SetMusicPlaybackEnabled(s32 a) {
    if (g_gameSession.transitionBlocked == 0) {
        s32 *p = &g_musicPlaybackEnabled;
        if (*p != a) {
            *p = a;
            if (a == 0) {
                SoundElement_FadeOutMusic();
            }
        }
    }
}

void SoundElement_FadeOutMusic(void) {
    Audio_FadeOutContextMusic((intptr_t) &g_soundElementContext);
}

void SoundElement_StopMusic(void) {
    Audio_StopContextMusic((intptr_t) &g_soundElementContext);
}

void SoundElement_EnableMusicGainOverride(void) {
    Audio_EnableContextMusicGainOverride((intptr_t) &g_soundElementContext);
}

void SoundElement_DisableMusicGainOverride(void) {
    Audio_DisableContextMusicGainOverride((intptr_t) &g_soundElementContext);
}

void SoundElement_DisablePeriodicSound(void) {
    Audio_SetPeriodicSoundEnabled(&g_soundElementContext, 0);
}

void SoundElement_EnablePeriodicSound(void) {
    Audio_SetPeriodicSoundEnabled(&g_soundElementContext, 1);
}

void SoundElement_SetListenerCamera(s32 listenerCameraAddress) {
    Audio_SetListenerCamera(&g_soundElementContext, listenerCameraAddress);
}

void SoundElement_SetMusicGainScalingEnabled(s32 enabled) {
    Audio_SetMusicGainScalingEnabled(&g_soundElementContext, enabled);
}

void SoundElement_SetClampedAudioLevel(f32 level) {
    Audio_SetClampedAudioLevel(&g_soundElementContext, level);
}

void SoundElement_ClearVoiceFlags(void) {
    Audio_ClearContextVoiceFlags((intptr_t) &g_soundElementContext);
}

void SoundElement_AcquireContextLock(void) {
    Sound_AcquireContextLock(&g_soundElementContext);
}

void SoundElement_ReleaseContextLock(void) {
    Sound_ReleaseContextLock(&g_soundElementContext);
}

struct GameAudioContext;

s32 SoundElement_HasActiveOrPendingSound(s32 wantedKey) {
    return Sound_HasActiveOrPendingSound(&g_soundElementContext, wantedKey);
}
