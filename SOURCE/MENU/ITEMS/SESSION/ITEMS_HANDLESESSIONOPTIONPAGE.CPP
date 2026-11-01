#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#if defined(VERSION_EU)
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "OVLGAME/SHAREDRECAT224.H"
/* 8042FBEC_14.CPP */
s32 Items_ForwardRulesLock(void *unused, MenuRules *rules) {
    Player_PlacePlayerForRound(rules->locked);
    return 1;
}
extern char g_gameSession[];
extern void Match_ResetMatchControllerState(void *);
/* Pak/option page handler: while g_sessionOptionResetMode is 1 it runs Match_ResetMatchControllerState on the session, otherwise it clears the
   flag word at 0x5D0 of the record at 0x1C of its second argument. Returns one. */
s32 Items_HandleSessionOptionPage(void *unused, void **menu) {
    if (g_sessionOptionResetMode == 1) {
        Match_ResetMatchControllerState(g_gameSession);
    } else {
        ((Shared_ActorView *)menu[7])->actorState = 0;
    }
    return 1;
}
#endif
