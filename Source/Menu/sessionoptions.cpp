#include "include_asm.h"
#include "Common/respawn_menu_actor.h"
#include "types.h"
#include "Ovlgame/confirming_controller.h"
#include "Ovlgame/menu_handlesessionoptionpage.h"
#if ((!(defined(VERSION_EU))))
#include "Common/game_session.h"
#endif
#if ((!(defined(VERSION_EU))))
#include "Ai/Player/player_placeplayerforround.h"
#endif
#if ((!(defined(VERSION_EU))))
#include "Ovlgame/match.h"
#endif

#if defined(VERSION_EU_X) || defined(VERSION_US)
s32 Menu_ForwardRulesLock(void *unusedContext, MenuRules *menuRules) {
    Player_PlacePlayerForRound(menuRules->locked);
    return 1;
}
#endif

#if defined(VERSION_DE) || defined(VERSION_US_REV1)
s32 Menu_ForwardRulesLock(void *owner, MenuRules *rules) {
    Player_PlacePlayerForRound(rules->locked);
    return 1;
}
#endif

#if !(defined(VERSION_EU))
/* Calls Match_ResetMatchControllerState on g_gameSession when g_sessionOptionResetMode is one; otherwise clears
   the option word of the second argument's owner. Returns one. */

s32 Menu_HandleSessionOptionPage(void *menuOwner, struct Holder *holder) {
    if (g_sessionOptionResetMode == 1) {
        Match_ResetMatchControllerState(&g_gameSession);
    } else {
        holder->owner->value = 0;
    }
    return 1;
}
#endif
