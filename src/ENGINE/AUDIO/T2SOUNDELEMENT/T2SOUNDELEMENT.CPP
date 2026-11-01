#include "COMMON/STATERECAT34.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "AUDIO/AUDIO_CHOOSEWEIGHTEDSOUNDVARIANT.H"
#include "ENGINE/AUDIO/T2SOUNDELEMENT.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "COMMON/AUDIO_CONTEXT.H"
#include "include_asm.h"
#include "ENGINE/AUDIO/T2SOUNDELEMENT.H"
#include "TEXTURE/SOUND_UPDATEAUDIOCONTEXT.H"

/* 8025DE50_5.CPP */
/** Calls Sound_InitializeContext with &g_soundElementContext as its argument. */

struct GameAudioContext;
extern s32 Audio_PlayPositionedSoundWithScale(struct GameAudioContext *context, s32 track, CVector3 position,
                         s32 spatialMode, s32 owner, f32 volumeScale);

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

/* 8025DE50_6.CPP */
/* Return the existing owner-count result to callers that test it. */
s32 SoundElement_CountOwnerVoices(s32 owner)
{
    return Audio_CountSoundVoices((char *)&g_soundElementContext, owner);
}

/* 8025DE50_7.CPP */
void SoundElement_PlayDialogGroup(s32 callback) {
    if (g_gameSession.transitionBlocked == 0) {
        Audio_PlayDialogGroup(&g_soundElementContext, callback);
    }
}

void SoundElement_StopDialog(void) {
    Audio_StopContextDialog((s32) &g_soundElementContext);
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
