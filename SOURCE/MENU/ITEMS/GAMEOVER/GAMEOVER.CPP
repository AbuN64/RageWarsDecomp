#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"

#if defined(VERSION_DE)
typedef struct { char pad0[0x30]; u32 flags; } GameOverMenuFlagsView;
typedef struct { char pad0[0xC]; GameOverMenuFlagsView *rec; } GameOverMenuContext;
/* Resets the game-over timer to 120.0f and clears bit 26 of the flags in the record at 0xC of menuContext. */
void Items_ResetGameOverTimer(GameOverMenuContext *menuContext) {
    g_gameSettings.counters.m_GameOverTimer = 120.0f;
    menuContext->rec->flags &= 0xFBFFFFFF;
}
#endif
