#include "COMMON/GAMEPLAY_CAMERA.H"
#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/INTEGERSTATE1250.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/WORLD.H"
#include "RENDER/WEAPON_INITIALIZECHARGEANDSTARTUPCUES_DATA.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "TYPES.H"


extern s32 *SoundVoicePool_GetGlobalState(void);
extern s32 SoundVoicePool_StopNode(void *, void *);

void Playerai_StartPrimaryAttachedSound(Shared_ActorView *actor, s32 soundId) {
    s32 viewAddress;
    void *soundPosition;

    viewAddress = (s32) actor->message;
    if (viewAddress != 0) {
        soundPosition = (void *)((char *)&((GameplayCamera *)viewAddress)->position);
    } else {
        soundPosition = &actor->position;
    }
    if (g_world.frozen == 0 && g_gameSession.clockPaused == 0) {
        SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), (void *)actor->weaponSoundHandle);
        actor->weaponSoundHandle = (s32)SoundVoicePool_PlaySpatialSound((void *)SoundVoicePool_GetGlobalState(), soundId, soundPosition, soundPosition, (s32)actor);
    }
}

void Playerai_StopPrimaryAttachedSound(void *player) {
    SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), (void *)(((struct PlayerLoopingSoundHandleView *) ((s8 *) player))->primarySoundHandle));
    (((struct PlayerLoopingSoundHandleView *) ((s8 *) player))->primarySoundHandle) = 0;
}

void Playerai_StartSecondaryAttachedSound(Shared_ActorView *actor, s32 soundId) {
    s32 viewAddress;
    void *soundPosition;

    if (g_world.frozen == 0 && g_gameSession.clockPaused == 0) {
        viewAddress = (s32) actor->message;
        if (viewAddress != 0) {
            soundPosition = (void *)((char *)&((GameplayCamera *)viewAddress)->position);
        } else {
            soundPosition = &actor->position;
        }
        SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), (void *)actor->weaponLoopSoundHandle);
        actor->weaponLoopSoundHandle = (s32)SoundVoicePool_PlaySpatialSound((void *)SoundVoicePool_GetGlobalState(), soundId, soundPosition, soundPosition, (s32)actor);
    }
}

void Playerai_StopSecondaryAttachedSound(void *player) {
    SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), (void *)(((struct PlayerStartupSoundView *) ((s8 *) player))->startupSoundNode));
    (((struct PlayerStartupSoundView *) ((s8 *) player))->startupSoundNode) = 0;
}

void Playerai_StartTransitionState(void *player, s32 transitionParameter) {
    (((struct PlayerWeaponTransitionParameterView *) ((s8 *) player))->transitionParameter) = transitionParameter;
    Player_SetPlayerState(player, player, 16);
}
