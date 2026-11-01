#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Points each of the four middle-list name widgets at the player it shows: the user's selected middle record for the control the user has active, else the global player of that slot. */
void PAKInterface_RefreshMiddleNamesForPlayerName(s32 anUser) {
    s32 i;
    s32 nStringId;
    PAKUserWidget *pObject;
    PAKListItem *pItem;
    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                nStringId = 649;
                break;
            case 1:
                nStringId = 651;
                break;
            case 2:
                nStringId = 653;
                break;
            case 3:
                nStringId = 655;
                break;
        }
        pObject = SM_DLFindObjectByID(g_pakInterfaceScreen->m_pDisplayList, nStringId);
        PAK_ASSERT(4859, pObject != 0, s_pakAssertListObject);
        SM_DLSetDisabled(pObject, 0);
        PAK_ASSERT(4873, pObject->m_pItem->m_WidgetType == 4, s_pakAssertListObjectType);
        pItem = pObject->m_pItem;
        PAK_ASSERT(4875, pItem != 0, s_pakAssertListItem);
        if (anUser != -1 && pObject == SMMU_GetActiveControl(g_pakInterfaceScreen->m_pUserList, anUser)) {
            pItem->m_pPlayer = &g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_QuickRecord];
        } else if (g_pakGlobalPlayers[i].m_User >= 0) {
            pItem->m_pPlayer = &g_pakGlobalPlayers[i];
        } else {
            pItem->m_pPlayer = 0;
        }
    }
}
#endif
