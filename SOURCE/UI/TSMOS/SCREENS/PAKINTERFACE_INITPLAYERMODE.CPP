#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
extern s32 gnAccessingPak_CurrentMode;
extern s32 gnAccessingPak_CurrentPAK;
extern char s_pakAssertTextObject[];
extern char s_pakAssertTextString[];
extern char *SM_GetStringByID(s32 anId);
extern void OptionsData_ReplaceString(char *apText, const char *apToken, const char *apValue);
extern void SM_DLSetHighlighted(PAKUserWidget *apObject, s32 anHighlighted);
extern void SMMU_SetActiveControl(void *apList, s32 anUser, s16 anControl);
extern void SMMU_BlockUser(void *apUserList, s32 anUser, s32 anBlocked);
extern void CWipeScreen_StartWipe(void *apWipe);
extern s32 GetNActive(void);
extern void PAKInterface_ExitScreen(s32 anTarget);
extern void PAKInterface_InitNameManagement(s32 anUser);
extern void PAKInterface_InitUpdateInfo(s32 anUser);
extern void PAKInterface_InitPakManagement(s32 anUser);
extern void PAKInterface_RefreshMiddleNamesForPlayerName(s32 anUser);
/* Shows the panel for the user's current state: finds its widget, makes it visible and focuses its control. */
void PAKInterface_InitPlayerMode(s32 anUser) {
    PAKUserWidget *pObject;
    PAKListTextItem *pTextObject;
    PAKUserWidget *pTemp;
    char *pTextString;
    s32 nSlot;
    s32 nControl;
    s32 nAlpha;
    s32 i;
    PAK_ASSERT(3561, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nAlpha = 150;
    if (PAK_PLAYER(anUser).m_pWidget != 0) {
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 0);
    }
    pObject = SMMU_GetActiveControl(g_pakInterfaceScreen->m_pUserList, anUser);
    PAK_ASSERT(3572, pObject != 0, s_pakAssertListObject);
    SM_DLSetHighlighted(pObject, 0);
    SMMU_SetActiveControl(g_pakInterfaceScreen->m_pDisplayList, anUser, 643);
    switch (PAK_PLAYER(anUser).m_State) {
    case 0:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 703);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pTextObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 707);
        PAK_ASSERT(3588, pTextObject != 0, s_pakAssertTextObject);
        pTextObject->m_pText = PAK_PLAYER(anUser).m_ModeText;
        switch (g_pakInterfaceScreen->m_Mode) {
        case 0:
            pTextString = SM_GetStringByID(836);
            break;
        case 1:
        case 7:
            pTextString = SM_GetStringByID(840);
            break;
        case 2:
            pTextString = SM_GetStringByID(838);
            break;
        case 3:
            pTextString = SM_GetStringByID(839);
            break;
        case 4:
        case 6:
            pTextString = SM_GetStringByID(841);
            break;
        case 5:
            pTextString = SM_GetStringByID(837);
            break;
        default:
            PAK_ASSERT(3622, 0, s_pakAssertScreenMode);
            pTextString = SM_GetStringByID(836);
            break;
        }
        PAK_ASSERT(3627, pTextString != 0, s_pakAssertTextString);
        x_strcpy(PAK_PLAYER(anUser).m_ModeText, SM_GetStringByID(pTextObject->m_StringId));
        OptionsData_ReplaceString(PAK_PLAYER(anUser).m_ModeText, "[MODE]", pTextString);
        if (g_pakInterfaceScreen->m_Mode == 6) {
            pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 706);
            PAK_ASSERT(3637, pObject != 0, s_pakAssertListObject);
            SM_DLSetVisible(pObject, 0);
        }
        break;
    case 1:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 746);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 748);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    case 2:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 722);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        break;
    case 3:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 697);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 698);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    case 4:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 723);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 728);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        PAKInterface_InitPakManagement(anUser);
        break;
    case 22:
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        nSlot = 0;
        while (g_pakInterfaceScreen->m_Slot[nSlot].m_State == 0) {
            nSlot++;
        }
        nControl = 649;
        switch (nSlot) {
        case 0:
            nControl = 649;
            break;
        case 1:
            nControl = 651;
            break;
        case 2:
            nControl = 653;
            break;
        case 3:
            nControl = 655;
            break;
        default:
            nControl = 649;
            break;
        }
        SMMU_SetActiveControl(g_pakInterfaceScreen->m_pDisplayList, anUser, nControl);
        PAKInterface_RefreshMiddleNamesForPlayerName(anUser);
        break;
    case 5:
        break;
    case 6:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 738);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 742);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        PAKInterface_InitUpdateInfo(anUser);
        break;
    case 7:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 712);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 714);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        nSlot = PAK_PLAYER(anUser).m_QuickRecord;
        pTextObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 713);
        PAK_ASSERT(3755, pTextObject != 0, s_pakAssertTextObject);
        pTextObject->m_pText = PAK_PLAYER(anUser).m_MiddleRecords[nSlot].m_Name;
        break;
    case 8:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 716);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 717);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        nSlot = PAK_PLAYER(anUser).m_ListCursor;
        pTextObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 713);
        PAK_ASSERT(3777, pTextObject != 0, s_pakAssertTextObject);
        pTextObject->m_pText = PAK_PLAYER(anUser).m_Notes[nSlot].m_Name;
        break;
    case 9:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 708);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 710);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        nSlot = 0;
        pTextObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 709);
        PAK_ASSERT(3798, pTextObject != 0, s_pakAssertTextObject);
        pTextObject->m_pText = PAK_PLAYER(g_pakInterfaceScreen->m_Slot[nSlot].m_User).m_MiddleRecords[g_pakInterfaceScreen->m_Slot[nSlot].m_Record].m_Name;
        break;
    case 10:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 674);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        break;
    case 11:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 719);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 720);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    case 12:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 752);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 753);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        PAK_PLAYER(anUser).m_NameCursor = 0;
        for (i = 0; i < 7; i++) {
            if (i == 0) {
                PAK_PLAYER(anUser).m_Name[i].ch = 65;
            } else {
                PAK_PLAYER(anUser).m_Name[i].ch = 0;
                PAK_PLAYER(anUser).m_Name[i].attr = 0;
            }
        }
        PAK_PLAYER(anUser).m_FieldB4C = 0;
        PAK_PLAYER(anUser).m_FieldB48 = 2;
        i = 0;
        for (;;) {
            pObject->m_Alpha = 255;
            PAK_ASSERT(3856, pObject->m_pItem->m_WidgetType == 4, s_pakAssertListObjectType);
            pTextObject = (PAKListTextItem *)pObject->m_pItem;
            pTextObject->m_pText = (char *)&PAK_PLAYER(anUser).m_Name[i];
            i++;
            pTemp = pObject;
            pObject = (PAKUserWidget *)((PAKNameWidget *)pTemp)->m_pNext;
            if (pObject == 0) break;
        }
        break;
    case 13:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 685);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 692);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        PAKInterface_InitNameManagement(anUser);
        break;
    case 14:
    case 17:
        SMMU_SetActiveControl(g_pakInterfaceScreen->m_pDisplayList, anUser, 643);
        SMMU_BlockUser(g_pakInterfaceScreen->m_pUserList, anUser, 1);
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 675);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        if (GetNActive() == 0) {
            switch (g_pakInterfaceScreen->m_Mode) {
            case 0:
            case 4:
                PAKInterface_ExitScreen(27);
                break;
            case 5:
                TSMOS_InputDisable();
                CWipeScreen_StartWipe(g_pakInterfaceScreen->m_Wipe);
                break;
            case 6:
                PAKInterface_ExitScreen(29);
                if (gnAccessingPak_CurrentMode == 1) {
                    gnAccessingPak_CurrentPAK = gnAccessingPak_CurrentPAK - 1;
                }
                if (gnAccessingPak_CurrentMode == 0) {
                    gnAccessingPak_CurrentPAK = -1;
                }
                break;
            default:
                PAKInterface_ExitScreen(27);
                break;
            }
        }
        break;
    case 15:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 749);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 751);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    case 16:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 693);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 695);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        nSlot = PAK_PLAYER(anUser).m_FieldB3C;
        pTextObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 696);
        PAK_ASSERT(3998, pTextObject != 0, s_pakAssertTextObject);
        pTextObject->m_pText = PAK_PLAYER(anUser).m_MiddleRecords[nSlot].m_Name;
        break;
    case 18:
        break;
    case 19:
        break;
    case 20:
        break;
    case 21:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 735);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 736);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    case 23:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 682);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 684);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    case 24:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 679);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 680);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    case 25:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 744);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 745);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    case 26:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 676);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 677);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    case 27:
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        SMMU_SetActiveControl(g_pakInterfaceScreen->m_pDisplayList, anUser, 663);
        for (i = 0; i < 4; i++) {
            switch (i) {
            case 0:
                nControl = 663;
                break;
            case 1:
                nControl = 665;
                break;
            case 2:
                nControl = 667;
                break;
            case 3:
                nControl = 669;
                break;
            }
            if (ControllerConnected(i) == 1) {
                SMMU_SetActiveControl(g_pakInterfaceScreen->m_pDisplayList, anUser, nControl);
                break;
            }
        }
        PAKInterface_RefreshMiddleNamesForCopy(anUser);
        break;
    case 28:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 732);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 733);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    case 29:
        PAK_PLAYER(anUser).m_pWidget = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pObject, 701);
        SM_DLSetVisible(PAK_PLAYER(anUser).m_pWidget, 1);
        pObject = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 702);
        SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, anUser, pObject);
        break;
    default:
        PAK_ASSERT(4173, 0, s_pakAssertScreenMode);
        break;
    }
    ((PAKUserWidget *)PAK_PLAYER(anUser).m_pWidget)->m_Alpha = (u8)nAlpha;
}
#endif
