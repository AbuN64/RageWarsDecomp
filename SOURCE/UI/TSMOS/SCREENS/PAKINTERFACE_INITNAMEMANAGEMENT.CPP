#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Binds the four middle-list slot widgets of the user's name screen and focuses its first enabled row. */
void PAKInterface_InitNameManagement(s32 anUser) {
    s32 i;
    PAKUserWidget *pObject;
    PAKUserWidget *pVisible;
    PAKListItem *pItem;
    PAKUserWidget *pTemp;
    PAK_ASSERT(4508, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_QuickRecord = 0;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[0] = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pWidget, 692);
    PAK_ASSERT(4515, g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[0] != 0, s_pakAssertSlotObject);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[1] = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pWidget, 689);
    PAK_ASSERT(4518, g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[1] != 0, s_pakAssertSlotObject);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[2] = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pWidget, 686);
    PAK_ASSERT(4521, g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[2] != 0, s_pakAssertSlotObject);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[3] = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pWidget, 690);
    PAK_ASSERT(4524, g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[3] != 0, s_pakAssertSlotObject);
    i = 0;
    while (i < 4) {
        g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_RecordState[i] = 2;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[i]->m_Alpha = 255;
        pObject = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[i], 687);
        PAK_ASSERT(4536, pObject != 0, s_pakAssertListObject);
        SM_DLSetDisabled(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[i], 0);
        pItem = (PAKListItem *)SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[i], 688);
        PAK_ASSERT(4542, pItem != 0, s_pakAssertListObject);
        if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[i].m_User != -1) {
            pItem->m_pPlayer = &g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[i];
            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_RecordState[i] = 1;
            if (g_pakInterfaceScreen->m_Mode == 1) {
                pVisible = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[i], 687);
                PAK_ASSERT(4555, pVisible != 0, s_pakAssertListObject);
                SM_DLSetVisible(pVisible, 0);
                if (PAKInterface_GetGlobalPlayerByMarker(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Marker, g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[i].m_Slot) != -1) {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_RecordState[i] = 0;
                    SM_DLSetDisabled(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[i], 1);
                    pVisible = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pSlotObject[i], 687);
                    PAK_ASSERT(4566, pVisible != 0, s_pakAssertListObject);
                    SM_DLSetVisible(pVisible, 1);
                }
            }
        } else {
            ((PAKListTextItem *)pItem)->m_pText = pText_PAK_Empty[g_engineApp.m_Language];
            SM_DLSetVisible(pObject, 0);
        }
        i++;
    }
    pObject = SMMU_GetActiveControl(g_pakInterfaceScreen->m_pUserList, anUser);
    PAK_ASSERT(4619, pObject != 0, s_pakAssertListObject);
    {
        while (SM_DLIsDisabled(pObject)) {
            pTemp = pObject;
            pObject = pTemp->m_pNext;
        }
    }
    SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
}
#endif
