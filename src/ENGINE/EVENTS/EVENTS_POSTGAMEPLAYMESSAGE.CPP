#include "include_asm.h"
#include "ENGINE/EVENTS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "TYPES.H"

extern s32 Gsky_StartEmitter(void *obj, f32 amplitudeX, f32 amplitudeY, f32 amplitudeZ, f32 scale, s32 value, Triple pos);

extern f32 k_playerEventClipScale[2];

void Events_StartEnabledCameraEmitter(s32 unused0, s32 unused1, s32 unused2, Triple t, Vec4s v) {
    Gsky_StartEmitter(&g_frontendScreenStatus, (f32) v.x, (f32) v.y, (f32) v.z, (f32) v.w * k_playerEventClipScale[1], 1, t);
}

void Events_StartDisabledCameraEmitter(s32 unused0, s32 unused1, s32 unused2, Triple t, Vec4s v) {
    Gsky_StartEmitter(&g_frontendScreenStatus, (f32) v.x, (f32) v.y, (f32) v.z, (f32) v.w * k_eventEmitterAngleConstants, 0, t);
}

#include "COMMON/GAMEPLAY_SOUND_TABLE.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "ENGINE/AUDIO/CHANNEL.H"

void Events_PostGameplayMessage(void *owner, LevelActor *actor, s32 event, Triple position, ResourceManagerState params) {
    if (actor->kind == 1 && (actor->flags & 0x300000)) {
        Shared_ActorView *player = actor->controller;
        void *parent = player->message;
        if (parent != 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
            Camera_PostScreenMessage(&g_frontendScreenStatus, parent, g_gameplayEventMessageTable[params.active].sound[g_frontendScreenStatus.settings.language]);
#else
            Camera_PostScreenMessage(&g_frontendScreenStatus, parent, gameplaySoundValue(params.active));
#endif
        }
    } else {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        Camera_PostScreenMessage(&g_frontendScreenStatus, &g_frontendScreenStatus.fallbackCamera, g_gameplayEventMessageTable[params.active].sound[g_frontendScreenStatus.settings.language]);
#else
        Camera_PostScreenMessage(&g_frontendScreenStatus, &g_frontendScreenStatus.fallbackCamera, gameplaySoundValue(params.active));
#endif
    }
    if (gameplaySoundHook(params.active) != 0) {
        SoundElement_PlayDialogGroup(gameplaySoundHook(params.active));
    }
}
