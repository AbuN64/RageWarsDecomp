#include "MENU/BUILT_MENU.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"

#if defined(VERSION_DE)
/* Resets the game-over timer to 120.0f and clears bit 26 of the flags in the record at 0xC of menuContext. */
void Items_ResetGameOverTimer(MenuBuildState *menuContext) {
    g_gameSettings.counters.m_GameOverTimer = 120.0f;
    menuContext->entries[1].flags &= 0xFBFFFFFF;
}
#endif
