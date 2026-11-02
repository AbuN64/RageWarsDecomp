#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "COMMON/MENU_UI_PROVIDERS.H"
#include "COMMON/WORLD.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "TYPES.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "FRONTEND/MENUIMAGE.H"
#include "FRONTEND/SCREEN.H"

/* Event callback for the match setup screen g_optionsShortcutScreen: on event 1 with the screen in state 1 it
   advances it, and once it reaches state 2 either goes back (choice 0: resets the mode, shows the
   item and queues sound 0x259 past g_selectedLevelId) or starts the match (choice 1: picks the arena,
   clears the pause word, then either sets the mode from the settings and active human players or
   stops the match objects and calls Stage_StartConfiguredMatch). Returns zero. */






extern struct Shared_OptionsScreen *g_optionsShortcutScreen;







extern s32 Frontend_GetMenuImageState(s32 *record);
extern void Frontend_DrawMenuImage(struct MenuImage *menu);
extern void Widget_SetWidgetFlag08(void *object, int enabled);
extern s32 Track_RequestTrackByKey(s32);
extern void MarkMenuEventHandled();

extern void Tsmos_RequestFrontendShutdown(void);
extern void Pools_ResetActorPools(struct DraftOwnerA370 *owner, s32 actorCount);
extern void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
extern void Scene_LoadLevelResources(void *, s32, s32);
extern void Stage_StartConfiguredMatch(void);




s32 Menu_FinishTabOptionsTransition(void *item, s32 unused1, s32 event) {
    s32 state;
    s32 humans;
    s32 i;
    Shared_Game *settings;
    u8 *player;
    s32 *pause;

    if (event == 1) {
        state = Frontend_GetMenuImageState(g_optionsShortcutScreen);
        if (state != event) {
            return 0;
        }
        Frontend_DrawMenuImage(g_optionsShortcutScreen);
        Frontend_AdvanceMenuImageTransition(g_optionsShortcutScreen);
        if (Frontend_GetMenuImageState(g_optionsShortcutScreen) != 2) {
            return 0;
        }
        if (g_optionsShortcutScreen->choice != 0 && g_optionsShortcutScreen->choice != state) {
            return 0;
        }
        if (g_optionsShortcutScreen->choice == 0) {
            Frontend_RequestScreenMode(0);
            Widget_SetWidgetFlag08(item, 1);
            Track_RequestTrackByKey(g_selectedLevelId + 601);
            g_cinemaSequenceState->targetD8 = -1;
            g_cinemaSequenceState->state3C = state;
        } else {
            MarkMenuEventHandled();
            if (g_optionsShortcutScreen->arena == 0 && SoundElement_GetMusicPlaybackEnabled() != 0) {
                SoundElement_SetMusicPlaybackEnabled(Graphu64_NextRandom() % 4 + 56);
            } else {
                SoundElement_SetMusicPlaybackEnabled(g_optionsShortcutScreen->arena);
            }
            pause = &g_frontendScreenStatus.status[7];
            *pause = 0;
            if (g_optionsShortcutScreen->mode == -1) {
                humans = 0;
                i = 0;
                player = (u8 *)pause - (((char *)&((Shared_MenuData *)0)->pause - (char *)0) - ((char *)&((Shared_MenuData *)0)->game - (char *)0));
                do {
                    if (((Shared_Game *)player)->playerSettings[i].locked == 0 && ((Shared_Game *)player)->playerSettings[i].enabled == 1) {
                        humans++;
                    }
                    i++;
                } while (i < 4);
                settings = &g_gameSettings;
                if (settings->resolution == 2 && humans >= 2) {
                    Frontend_RequestScreenMode(1);
                } else {
                    Frontend_RequestScreenMode(settings->resolution);
                }
                Tsmos_RequestFrontendShutdown();
                return 0;
            }
            Pools_ResetActorPools((u8 *)pause - (((char *)&((Shared_MenuData *)0)->pause - (char *)0) - ((char *)&((Shared_MenuData *)0)->object - (char *)0)), 0);
            Player_InitializePlayerPool((u8 *)pause - ((char *)&((Shared_MenuData *)0)->pause - (char *)0), 0, 0);
            Scene_LoadLevelResources(&g_world, 0, 0);
            Stage_StartConfiguredMatch();
        }
    }
    return 0;
}
