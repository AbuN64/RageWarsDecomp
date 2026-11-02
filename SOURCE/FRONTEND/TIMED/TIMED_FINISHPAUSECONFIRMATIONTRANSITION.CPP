#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/SCREEN.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/WORLD.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "TYPES.H"
#include "FRONTEND/MENUIMAGE.H"
#include "FRONTEND/SCREEN.H"

/* Event callback for screen g_pauseTimedMenu: on event 1 while Frontend_GetMenuImageState reports the screen in state 1 it advances the screen through Frontend_DrawMenuImage and Frontend_AdvanceMenuImageTransition, and when that leaves it in state 2 it calls Frontend_RequestScreenMode_AchieveUpdateresultsscreen(0) and MarkMenuEventHandled, clears the pause word g_simpleObjectPauseState (0x180C past the match objects at g_frontendScreenStatus), stops those objects and the ones 0x48 bytes before them, releases resource 0x24 of g_world_AchieveUpdateresultsscreen, restarts Cache_SetResourceActivityState when Cache_GetResourceActivityState reports it idle, stores 8 at 0x17F0 past the match objects, passes the screen's word at 0x1C to SmXlate_SwitchScreen and calls SoundElement_DisableMusicGainOverride, returning zero. Adapted from Frontend_UpdatePage67Exit with the screen g_residentChoiceScreen changed to g_pauseTimedMenu, a Frontend_RequestScreenMode_AchieveUpdateresultsscreen(0) call added, and the trailing Stage_StartConfiguredMatch call replaced by the store of 8 and the SmXlate_SwitchScreen call before SoundElement_DisableMusicGainOverride. */

extern MenuRules *g_pauseTimedMenu;


extern s32 Frontend_GetMenuImageState(s32 *record);
extern void Frontend_DrawMenuImage(struct MenuImage *menu);
extern void Pools_ResetActorPools(struct DraftOwnerA370 *owner, s32 actorCount);
extern void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
extern void Scene_LoadLevelResources(void *, s32, s32);
extern s32 Cache_GetResourceActivityState(void);
extern void Cache_SetResourceActivityState(unsigned int);
extern void SmXlate_SwitchScreen(s32);
extern void SoundElement_DisableMusicGainOverride(void);

s32 Timed_FinishPauseConfirmationTransition(s32 unused0, s32 unused1, s32 event) {
    s32 *pause;
    if (event == 1) {
        if (Frontend_GetMenuImageState(g_pauseTimedMenu) != 1) {
            return 0;
        }
        Frontend_DrawMenuImage(g_pauseTimedMenu);
        Frontend_AdvanceMenuImageTransition(g_pauseTimedMenu);
        if (Frontend_GetMenuImageState(g_pauseTimedMenu) != 2) {
            return 0;
        }
        Frontend_RequestScreenMode(0);
        MarkMenuEventHandled();
        pause = &g_frontendScreenStatus.status[7];
        *pause = 0;
        Pools_ResetActorPools((char *)pause - (((char *)&((Shared_MenuData *)0)->pause - (char *)0) - ((char *)&((Shared_MenuData *)0)->object - (char *)0)), 0);
        Player_InitializePlayerPool((char *)pause - ((char *)&((Shared_MenuData *)0)->pause - (char *)0), 0, 0);
        Scene_LoadLevelResources(&g_world, 36, 0);
        if (Cache_GetResourceActivityState() == 0) {
            Cache_SetResourceActivityState(1);
        }
        pause[-7] = 8;
        SmXlate_SwitchScreen((void *)g_pauseTimedMenu->locked);
        SoundElement_DisableMusicGainOverride();
    }
    return 0;
}
