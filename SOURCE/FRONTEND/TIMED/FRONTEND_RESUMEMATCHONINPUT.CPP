#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "COMMON/GAME_SESSION.H"
#include "TYPES.H"

/* 8042E080_76.CPP */
/* On event 3 with value 0xD, clears g_simpleObjectPauseState and calls Tsmos_RequestFrontendShutdown and SoundElement_DisableMusicGainOverride. Returns
   zero. */
extern void Tsmos_RequestFrontendShutdown(void);

s32 Frontend_ResumeMatchOnInput(void *first, void *second, u32 event, s32 value) {
    if ((event >> 16) == 3) {
        if (value != 13) {
            return 0;
        }
        g_gameSession.clockPaused = 0;
        Tsmos_RequestFrontendShutdown();
        SoundElement_DisableMusicGainOverride();
    }
    return 0;
}

/* 8042E080_77.CPP */
/* Calls MarkMenuEventHandled with the arguments it was given and returns zero. */
extern void MarkMenuEventHandled();

s32 Frontend_ConsumePauseMenuEvent(void) {
    MarkMenuEventHandled();
    return 0;
}
