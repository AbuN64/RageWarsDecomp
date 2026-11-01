#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#if VERSION_US
extern char s_pakInterfaceScreenSourceFile[];
extern char s_pakInterfaceScreenUserInRange[];
extern char s_pakInterfaceScreenObjectNotNull[];
extern void Sound_PlayFXGlobal(s32 anSound);
extern s32 x_abs(s32 anValue);
extern s32 SM_GetJoystickThreshold(void);
extern void SM_AcknowledgeMsg(void);
extern s32 SM_DLIsDisabled(PAKUserWidget *apWidget);
extern void SMMU_SwitchUserControlFocusByObject(void *apUserList, s32 anUser, PAKUserWidget *apWidget);
extern void PAKInterface_DecPlayerNameCharacter(s32 anUser);
/* COMMENT */
s32 PAKInterface_OnDown(s32 a, s32 b, s32 c, s32 d, s32 e) {
    s32 nUser = c & 0xffff;
    PAKUserWidget *pNode;
    PAKUserWidget *pTemp;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 1432, s_pakInterfaceScreenUserInRange)) {
            *(char *)0 = 0;
        }
    }
    switch (PAK_PLAYER(nUser).m_State) {
    case 12:
        if (x_abs(e) < SM_GetJoystickThreshold()) {
            PAK_PLAYER(nUser).m_FieldB4C = 0;
            PAK_PLAYER(nUser).m_FieldB48 = 2;
        }
        if (d != 1) {
            return 0;
        }
        SM_AcknowledgeMsg();
        PAKInterface_DecPlayerNameCharacter(nUser);
        PAK_PLAYER(nUser).m_FieldB48 = 0;
        Sound_PlayFXGlobal(3713);
        break;
    case 4:
        if (d != 1) {
            return 0;
        }
        SM_AcknowledgeMsg();
        PAKInterface_ScrollManagementList(nUser, 1);
        g_pakInterfaceScreen->m_UserBusy[nUser] = 0;
        Sound_PlayFXGlobal(3700);
        break;
    case 13:
        switch (PAK_PLAYER(nUser).m_Mode) {
        case 6:
            if (d != 1) {
                return 0;
            }
            SM_AcknowledgeMsg();
            pNode = PAKInterface_GetPAKUserWidgetect(g_pakInterfaceScreen->m_pUserList, nUser);
            if (!pNode) {
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 1482, s_pakInterfaceScreenObjectNotNull)) {
                    *(char *)0 = 0;
                }
            }
            pTemp = pNode;
            pNode = pTemp->m_pNext;
            while (SM_DLIsDisabled(pNode)) {
                pTemp = pNode;
                pNode = pTemp->m_pNext;
            }
            SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, nUser, pNode);
            Sound_PlayFXGlobal(3700);
            break;
        }
        break;
    case 22:
        if (d == 1) {
            pNode = PAKInterface_GetPAKUserWidgetect(g_pakInterfaceScreen->m_pUserList, nUser);
            if (!pNode) {
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 1590, s_pakInterfaceScreenObjectNotNull)) {
                    *(char *)0 = 0;
                }
            }
            pTemp = pNode;
            pNode = pTemp->m_pNext;
            while (SM_DLIsDisabled(pNode)) {
                pTemp = pNode;
                pNode = pTemp->m_pNext;
            }
            SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, nUser, pNode);
            PAKInterface_RefreshMiddleList(nUser);
            SM_AcknowledgeMsg();
        } else {
            SM_AcknowledgeMsg();
        }
        break;
    case 27:
        if (d == 1) {
            pNode = PAKInterface_GetPAKUserWidgetect(g_pakInterfaceScreen->m_pUserList, nUser);
            if (!pNode) {
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 1616, s_pakInterfaceScreenObjectNotNull)) {
                    *(char *)0 = 0;
                }
            }
            pTemp = pNode;
            pNode = pTemp->m_pNext;
            while (SM_DLIsDisabled(pNode)) {
                pTemp = pNode;
                pNode = pTemp->m_pNext;
            }
            SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, nUser, pNode);
            PAKInterface_RefreshMiddleNamesForCopy(nUser);
            SM_AcknowledgeMsg();
        } else {
            SM_AcknowledgeMsg();
        }
        break;
    default:
        break;
    }
    return 0;
}
#endif
