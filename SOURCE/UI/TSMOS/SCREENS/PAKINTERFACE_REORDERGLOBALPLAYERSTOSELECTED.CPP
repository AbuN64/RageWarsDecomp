#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Rebuilds the global player list in the order the users chose their records. */
void PAKInterface_ReorderGlobalPlayersToSelected(void) {
    s32 i;
    s32 j;
    s32 nSize;
    s32 nFrom;
    s32 bTaken[PAK_USERS];
    nSize = PAK_PLAYER_RECORD_SIZE;
    memcpy(g_pakInterfaceScreen->m_SaveBlock.m_Records, g_pakGlobalPlayers, PAK_SAVE_DATA_SIZE);
    i = 0;
    while (i < 4) {
        CPersistentPlayerData_Initialize(&g_pakGlobalPlayers[i]);
        bTaken[i] = 0;
        i++;
    }
    i = 0;
    while (i < 4) {
        nFrom = g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_SelectedRecord;
        if (nFrom >= 0) {
            memcpy(&g_pakGlobalPlayers[i], &g_pakInterfaceScreen->m_SaveBlock.m_Records[nFrom], nSize);
            bTaken[nFrom] = 1;
        }
        i++;
    }
    i = 0;
    while (i < 4) {
        if (bTaken[i] == 0 && g_pakInterfaceScreen->m_SaveBlock.m_Records[i].m_User >= 0) {
            j = 0;
            while (j < 4) {
                if (g_pakGlobalPlayers[j].m_User < 0) {
                    memcpy(&g_pakGlobalPlayers[j], &g_pakInterfaceScreen->m_SaveBlock.m_Records[i], nSize);
                    break;
                }
                j++;
            }
        }
        i++;
    }
}
#endif
