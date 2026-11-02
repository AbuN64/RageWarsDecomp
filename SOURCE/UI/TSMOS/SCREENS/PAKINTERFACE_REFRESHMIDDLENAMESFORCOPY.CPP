#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Enables the name widget of each connected controller and points the active user's widget at the user's selected middle record. */
void PAKInterface_RefreshMiddleNamesForCopy(s32 anUser) {
    s32 i;
    s32 nStringId;
    PAKUserWidget *pObject;
    PAKListItem *pItem;
    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                nStringId = 663;
                break;
            case 1:
                nStringId = 665;
                break;
            case 2:
                nStringId = 667;
                break;
            case 3:
                nStringId = 669;
                break;
        }
        pObject = SM_DLFindObjectByID(g_pakInterfaceScreen->m_pDisplayList, nStringId);
        PAK_ASSERT(4926, pObject != 0, s_pakAssertListObject);
        if (ControllerConnected(i) == 1) {
            SM_DLSetDisabled(pObject, 0);
        } else {
            SM_DLSetDisabled(pObject, 1);
            PAK_ASSERT(4940, pObject->m_pItem->m_WidgetType == 4, s_pakAssertListObjectType);
            pItem = pObject->m_pItem;
            PAK_ASSERT(4942, pItem != 0, s_pakAssertListItem);
            if (anUser != -1 && pObject == SMMU_GetActiveControl(g_pakInterfaceScreen->m_pUserList, anUser)) {
                pItem->m_pPlayer = &g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_QuickRecord];
            } else {
                pItem->m_pPlayer = 0;
            }
        }
    }
}
#endif
