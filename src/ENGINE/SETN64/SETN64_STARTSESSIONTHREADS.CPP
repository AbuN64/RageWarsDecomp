#include "COMMON/SESSIONHANDLERROW.H"
#include "TYPES.H"
#include "RENDER/SETN64_STARTSESSIONTHREADS.H"

s32 SetN64_StartBootstrapThread(s32 *);
#include "COMMON/GAME_SESSION.H"
void SetN64_StartSessionThreads(void) {
    SetN64_StartBootstrapThread(&g_gameSession);
}
