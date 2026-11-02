#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
s32 PAKInterface_ValidatePAKAgainstGlobal(s32 anUser) {
    s32 i;
    s32 nValid;
    PAK_ASSERT(5792, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nValid = 1;
    for (i = 0; i < 4; i++) {
        if (g_pakGlobalPlayers[i].m_Quick == 0 && g_pakGlobalPlayers[i].m_User == anUser
            && g_pakGlobalPlayers[i].m_Marker != g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Marker) {
            nValid = 0;
        }
    }
    return nValid;
}
#endif
