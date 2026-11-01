#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/WORLD.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/OBJB.H"
#include "TYPES.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"

/* Releases the two handles at offsets 0x11BC and 0x11C0 of an object: each goes to SoundVoicePool_StopNode
   with what SoundVoicePool_GetGlobalState returns, and each is then cleared. */


extern void *SoundVoicePool_GetGlobalState();
extern void SoundVoicePool_StopNode(void *, s32);

void Player_ReleaseObjectHandles(struct ItemsHandleOwner *object) {
    SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), object->first);
    object->first = 0;
    SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), object->second);
    object->second = 0;
}

/* Stores the second argument at 0x5E0 of the actor, calls Playerai_InitializePlayerHealth and Player_ResetPlayerWeapons on it, then starts sound g_world_AchieveUpdateresultsscreen for it through Scene_ChangeInstanceModel with 0x66, g_fragTagModelId or its type's entry of g_characterModelIds chosen by the options g_motionVisibilitySettings and g_resultExitPending.
   Adapted from Playerai_UpdateCharacterModel with a leading field store and two calls added and the g_gameSettings offsets changed to the symbols g_motionVisibilitySettings and g_resultExitPending. */


extern void Playerai_InitializePlayerHealth(void *);
extern void Player_ResetPlayerWeapons(void *);











void Player_StartPlayerAnimation(Player *animatedPlayer, s32 animationState) {
    s32 modelResource;

    animatedPlayer->state = animationState;
    Playerai_InitializePlayerHealth(animatedPlayer);
    Player_ResetPlayerWeapons(animatedPlayer);
    if (g_gameSettings.local == 0) {
        modelResource = 102;
    } else if (g_resultExitPending != 0 && ((Shared_ControlView *)animatedPlayer->profile)->transientFlag != 0) {
        modelResource = g_fragTagModelId;
    } else {
        modelResource = g_characterModelIds[((Shared_PickupAmmoDefinition *)animatedPlayer->definition)->firstAmmoDrop];
        animatedPlayer->playerId = ((Shared_ControlView *)animatedPlayer->profile)->playerId;
    }
    ((void (*)(void *, void *, s32, s32))Scene_ChangeInstanceModel)(&g_world, animatedPlayer, modelResource, animatedPlayer->animation);
}
