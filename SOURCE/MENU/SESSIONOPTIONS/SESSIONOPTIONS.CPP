#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ACTORRECAT260.H"
#include "TYPES.H"
#include "OVLGAME/SHAREDRECAT224.H"
#include "OVLGAME/MENU_HANDLESESSIONOPTIONPAGE.H"

/* 8043D54C_2.CPP */
#if defined(VERSION_EU_X) || defined(VERSION_US)
s32 Menu_ForwardRulesLock(void *unusedContext, MenuRules *menuRules) {
    Player_PlacePlayerForRound(menuRules->locked);
    return 1;
}
#endif

#if defined(VERSION_DE) || defined(VERSION_US_REV1)
s32 Menu_ForwardRulesLock(void *unused, MenuRules *rules) {
    Player_PlacePlayerForRound(rules->locked);
    return 1;
}
#endif

/* 8043D54C_3.CPP */
#if !(defined(VERSION_EU))
/* Calls Match_ResetMatchControllerState on g_gameSession when g_sessionOptionResetMode is one, otherwise clears the word at offset
   0x5D0 of the owner at offset 0x1C of the second argument. Returns one. */

#include "COMMON/GAME_SESSION.H"
extern void Match_ResetMatchControllerState(void *);

s32 Menu_HandleSessionOptionPage(void *unused, struct Holder *holder) {
    if (g_sessionOptionResetMode == 1) {
        Match_ResetMatchControllerState(&g_gameSession);
    } else {
        holder->owner->value = 0;
    }
    return 1;
}
#endif



