#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Reads the Controller Pak status of one user and picks the panel state the screen mode continues with. */
void PAKInterface_CheckPAK(s32 anUser) {
    s32 nStatus;
    s32 nNote;
    s32 bRepeat;
    PAK_ASSERT(4316, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    bRepeat = 1;
    nStatus = PAK_CheckStatus(anUser);
    do {
        switch (nStatus) {
        case -5:
        case -2:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 1;
            break;
        case -4:
        case -3:
        case -1:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 3;
            break;
        case 0:
            if (g_pakInterfaceScreen->m_Mode == 6) {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Step;
            } else if (PAK_AnySavesOnPak(pText_MultiFileName[g_engineApp.m_Language], anUser, &nNote) == 1) {
                if (PAKInterface_LoadGame(anUser, nNote) == 1) {
                    PAK_ASSERT(4349, g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Step != -1, s_pakAssertNextMode);
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Step;
                    switch (g_pakInterfaceScreen->m_Mode) {
                    case 0:
                        if (PAKInterface_FindEmptyPlayerDataSlot(anUser) == -1) {
                            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 24;
                        }
                        break;
                    case 7:
                        if (PAKInterface_IsPlayerDataListEmpty(anUser) == 1) {
                            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 15;
                        }
                        break;
                    case 2:
                        if (PAKInterface_IsPlayerDataListEmpty(anUser) == 1) {
                            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 25;
                        } else if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameTarget == 1) {
                            if (PAKInterface_FindEmptyPlayerDataSlot(anUser) == -1) {
                                g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 24;
                            }
                        }
                        break;
                    case 5:
                        if (PAKInterface_ValidatePAKAgainstGlobal(anUser) == 0) {
                            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 21;
                        }
                        break;
                    }
                } else {
                }
            } else {
                switch (g_pakInterfaceScreen->m_Mode) {
                case 0:
                case 1:
                case 7:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Marker = RandomSwapWord() % 9999999 + 1;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 15;
                    break;
                case 5:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 21;
                    break;
                case 4:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Step;
                    break;
                case 3:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 25;
                    break;
                case 2:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 25;
                    break;
                default:
                    PAK_ASSERT(4441, 0, s_pakAssertScreenMode);
                    break;
                }
            }
            break;
        default:
            PAK_ASSERT(4451, 0, s_pakAssertCheckStatus);
            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 1;
            break;
        }
    } while (bRepeat == 0);
    PAKInterface_InitPlayerMode(anUser);
}
#endif
