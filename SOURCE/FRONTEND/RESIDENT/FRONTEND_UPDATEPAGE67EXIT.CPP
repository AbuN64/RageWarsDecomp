#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/SCREEN.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/LONE/RESIDENT_CHOICE_SCREEN.H"
#include "COMMON/WORLD.H"
#include "FRONTEND/MENUIMAGE.H"

/* 8042E080_89.CPP */
/* Calls Tsmos_SetModeOneFlag with 2 and returns zero. */

s32 Frontend_ClearPage67ModeFlag(void) {
    Tsmos_SetModeOneFlag(2);
    return 0;
}

/* 8042E080_90.CPP */
/* Event callback for screen g_residentChoiceScreen: on event 1 while Frontend_GetMenuImageState reports the screen in state
   1 it advances the screen through Frontend_DrawMenuImage and Frontend_AdvanceMenuImageTransition, and when that leaves it in
   state 2 it calls MarkMenuEventHandled, clears the pause word g_simpleObjectPauseState (0x180C past the match objects
   at g_frontendScreenStatus), stops those objects and the ones 0x48 bytes before them, releases resource 0x24
   of g_world_AchieveUpdateresultsscreen, restarts Cache_SetResourceActivityState when Cache_GetResourceActivityState reports it idle, and calls
   SoundElement_DisableMusicGainOverride and Stage_StartConfiguredMatch. Returns zero. */

extern s32 Frontend_GetMenuImageState(s32 *record);
extern void Frontend_DrawMenuImage(struct MenuImage *menu);
extern void Pools_ResetActorPools(struct ScreenMessageOwner *owner, s32 actorCount);
extern void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
extern void Scene_LoadLevelResources(void *, s32, s32);
extern s32 Cache_GetResourceActivityState(void);
extern void Cache_SetResourceActivityState(unsigned int);
extern void SoundElement_DisableMusicGainOverride(void);
extern void Stage_StartConfiguredMatch(void);

s32 Frontend_UpdatePage67Exit(s32 unused0, s32 unused1, s32 event) {
    s32 *pause;
    if (event == 1) {
        if (Frontend_GetMenuImageState(g_residentChoiceScreen) != 1) {
            return 0;
        }
        Frontend_DrawMenuImage(g_residentChoiceScreen);
        Frontend_AdvanceMenuImageTransition(g_residentChoiceScreen);
        if (Frontend_GetMenuImageState(g_residentChoiceScreen) != 2) {
            return 0;
        }
        MarkMenuEventHandled();
        pause = &g_frontendScreenStatus.status[7];
        *pause = 0;
        Pools_ResetActorPools((char *)pause - (((char *)&((Shared_MenuData *)0)->pause - (char *)0) - ((char *)&((Shared_MenuData *)0)->object - (char *)0)), 0);
        Player_InitializePlayerPool((char *)pause - ((char *)&((Shared_MenuData *)0)->pause - (char *)0), 0, 0);
        Scene_LoadLevelResources(&g_world, 36, 0);
        if (Cache_GetResourceActivityState() == 0) {
            Cache_SetResourceActivityState(1);
        }
        SoundElement_DisableMusicGainOverride();
        Stage_StartConfiguredMatch();
    }
    return 0;
}
