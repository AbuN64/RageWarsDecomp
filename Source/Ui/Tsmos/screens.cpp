#include "types.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Ui/Tsmos/Screens/pakinterface_getnextplayertochoosename.h"
#include "Ui/ui_address_symbols.h"
#include "Ui/pakinterface_decplayernamecharacter.h"
#include "Ui/pakinterface_incplayernamecharacter.h"
#include "include_asm.h"
#include "Ui/pakinterface_exitscreen.h"
#include "Ui/pakinterface_initnamemanagement.h"
#include "Ui/pakinterface_initupdateinfo.h"
#include "Ui/pakinterface_initpakmanagement.h"
#include "Ui/pakinterface_refreshmiddlenamesforplayername.h"
#include "PR/gu.h"
#include "Ui/pakinterface_updatestartgroup.h"
#include <platform_sdk.h>
#include "Ui/Tsmos/pakinterface.h"
#include "Scene/cache_freememory.h"
#include "Ui/Tsmos/Screens/pakinterface_getnactive.h"
#include "Ui/Tsmos/Screens/pakinterface_getnplayerinfoactive.h"
#include "Ui/Tsmos/Screens/pakinterface_getnplayersjoined.h"
#include "Ui/Tsmos/Screens/pakinterface_initplayerinfo.h"
#include "Ui/pakinterface_updategroups.h"

#if VERSION_US
/* COMMENT */
s32 PAKInterface_OnButtonDebounce(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed) {
    s32 nUser = playerEntryId & 0xffff;
    s32 i;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 943, s_pakInterfaceScreenUserInRange)) {
            HaltAfterFailedAssert();
        }
    }
    if (((playerEntryId >> 16) & 0xffff) == 3) {
        switch (g_pakInterfaceScreen->m_Mode) {
        case 5:
            break;
        case 6:
            switch (selectionPressed) {
            case 10:
            if (PAK_PLAYER(nUser).m_State == 4) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_Panel = 2;
                PAK_PLAYER(nUser).m_State = 2;
                PAK_PLAYER(nUser).m_Step = 4;
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 4:
            switch (selectionPressed) {
            case 11:
            case 13:
            if (PAK_PLAYER(nUser).m_State == 0) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_Panel = 2;
                PAK_PLAYER(nUser).m_State = 2;
                PAK_PLAYER(nUser).m_Step = 4;
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            case 10:
            if (PAK_PLAYER(nUser).m_State == 4) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_Panel = 2;
                PAK_PLAYER(nUser).m_State = 2;
                PAK_PLAYER(nUser).m_Step = 4;
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 0:
            switch (selectionPressed) {
            case 11:
            case 13:
            if (PAK_PLAYER(nUser).m_State == 0) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_Panel = 2;
                PAK_PLAYER(nUser).m_State = 2;
                PAK_PLAYER(nUser).m_Step = 12;
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 3:
            switch (selectionPressed) {
            case 11:
            case 13:
            if (PAK_PLAYER(nUser).m_State == 0) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_Panel = 2;
                PAK_PLAYER(nUser).m_State = 2;
                PAK_PLAYER(nUser).m_Step = 13;
                PAK_PLAYER(nUser).m_Mode = 5;
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 1:
            switch (selectionPressed) {
            case 11:
            case 13:
            if (PAK_PLAYER(nUser).m_State == 0) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_State = 14;
                i = PAKInterface_GetNextPlayerToChooseName();
                if (i >= 0) {
                    PAK_PLAYER(nUser).m_Panel = 2;
                    PAK_PLAYER(nUser).m_State = 2;
                    PAK_PLAYER(nUser).m_Step = 13;
                    PAK_PLAYER(nUser).m_Mode = 6;
                }
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 2:
            switch (selectionPressed) {
            case 11:
            case 13:
            if (PAK_PLAYER(nUser).m_State == 0) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_State = 14;
                i = PAKInterface_GetNextPlayerToChooseName();
                if (i >= 0) {
                    PAK_PLAYER(nUser).m_Panel = 2;
                    PAK_PLAYER(nUser).m_State = 2;
                    PAK_PLAYER(nUser).m_Step = 13;
                    PAK_PLAYER(nUser).m_Mode = 3;
                }
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 7:
            break;
        default:
            if (AssertFailed(s_pakInterfaceScreenSourceFile, 1217, s_pakInterfaceScreenFalse)) {
                HaltAfterFailedAssert();
            }
            break;
        }
    }
    return 0;
}
#endif

#if VERSION_US
/* COMMENT */
s32 PAKInterface_OnDown(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed, s32 fifthArgument) {
    s32 nUser = playerEntryId & 0xffff;
    PAKUserWidget *pNode;
    PAKUserWidget *pTemp;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 1432, s_pakInterfaceScreenUserInRange)) {
            HaltAfterFailedAssert();
        }
    }
    switch (PAK_PLAYER(nUser).m_State) {
    case 12:
        if (x_abs(fifthArgument) < SM_GetJoystickThreshold()) {
            PAK_PLAYER(nUser).m_FieldB4C = 0;
            PAK_PLAYER(nUser).m_FieldB48 = 2;
        }
        if (selectionPressed != 1) {
            return 0;
        }
        SM_AcknowledgeMsg();
        PAKInterface_DecPlayerNameCharacter(nUser);
        PAK_PLAYER(nUser).m_FieldB48 = 0;
        Sound_PlayFXGlobal(3713);
        break;
    case 4:
        if (selectionPressed != 1) {
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
            if (selectionPressed != 1) {
                return 0;
            }
            SM_AcknowledgeMsg();
            pNode = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, nUser);
            if (!pNode) {
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 1482, s_pakInterfaceScreenObjectNotNull)) {
                    HaltAfterFailedAssert();
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
        if (selectionPressed == 1) {
            pNode = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, nUser);
            if (!pNode) {
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 1590, s_pakInterfaceScreenObjectNotNull)) {
                    HaltAfterFailedAssert();
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
        if (selectionPressed == 1) {
            pNode = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, nUser);
            if (!pNode) {
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 1616, s_pakInterfaceScreenObjectNotNull)) {
                    HaltAfterFailedAssert();
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

#if VERSION_US
/* COMMENT */
s32 PAKInterface_OnUp(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed, s32 fifthArgument) {
    s32 nUser = playerEntryId & 0xffff;
    PAKUserWidget *pNode;
    PAKUserWidget *pTemp;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 1664, s_pakInterfaceScreenUserInRange)) {
            HaltAfterFailedAssert();
        }
    }
    switch (PAK_PLAYER(nUser).m_State) {
    case 12:
        if (x_abs(fifthArgument) < SM_GetJoystickThreshold()) {
            PAK_PLAYER(nUser).m_FieldB4C = 0;
            PAK_PLAYER(nUser).m_FieldB48 = 2;
        }
        if (selectionPressed != 1) {
            return 0;
        }
        SM_AcknowledgeMsg();
        PAK_PLAYER(nUser).m_FieldB48 = 1;
        PAKInterface_IncPlayerNameCharacter(nUser);
        Sound_PlayFXGlobal(3713);
        break;
    case 4:
        if (selectionPressed != 1) {
            return 0;
        }
        SM_AcknowledgeMsg();
        PAKInterface_ScrollManagementList(nUser, 0);
        g_pakInterfaceScreen->m_UserBusy[nUser] = 0;
        Sound_PlayFXGlobal(3700);
        break;
    case 13:
        switch (PAK_PLAYER(nUser).m_Mode) {
        case 6:
            if (selectionPressed != 1) {
                return 0;
            }
            SM_AcknowledgeMsg();
            pNode = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, nUser);
            if (!pNode) {
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 1715, s_pakInterfaceScreenObjectNotNull)) {
                    HaltAfterFailedAssert();
                }
            }
            pTemp = pNode;
            pNode = pTemp->m_pPrev;
            while (SM_DLIsDisabled(pNode)) {
                pTemp = pNode;
                pNode = pTemp->m_pPrev;
            }
            SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, nUser, pNode);
            Sound_PlayFXGlobal(3700);
            break;
        }
        break;
    case 22:
        if (selectionPressed == 1) {
            pNode = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, nUser);
            if (!pNode) {
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 1830, s_pakInterfaceScreenObjectNotNull)) {
                    HaltAfterFailedAssert();
                }
            }
            pTemp = pNode;
            pNode = pTemp->m_pPrev;
            while (SM_DLIsDisabled(pNode)) {
                pTemp = pNode;
                pNode = pTemp->m_pPrev;
            }
            SMMU_SwitchUserControlFocusByObject(g_pakInterfaceScreen->m_pUserList, nUser, pNode);
            PAKInterface_RefreshMiddleList(nUser);
            SM_AcknowledgeMsg();
        } else {
            SM_AcknowledgeMsg();
        }
        break;
    case 27:
        if (selectionPressed == 1) {
            pNode = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, nUser);
            if (!pNode) {
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 1860, s_pakInterfaceScreenObjectNotNull)) {
                    HaltAfterFailedAssert();
                }
            }
            pTemp = pNode;
            pNode = pTemp->m_pPrev;
            while (SM_DLIsDisabled(pNode)) {
                pTemp = pNode;
                pNode = pTemp->m_pPrev;
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

#if VERSION_US
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

#if VERSION_US
/* Runs the per-frame update of all four users' panels: the start group, and the pulsing name-entry character with its auto-repeat. */
void PAKInterface_UpdateGroups(s32 anTicks) {
    s32 i;
    s32 nSlot;
    PAKUserWidget *pObject;
    PAKListTextItem *pItem;
    for (i = 0; i < 4; i++) {
        switch (g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_State) {
        case 0:
            PAKInterface_UpdateStartGroup(i);
            break;
        case 12:
            pObject = SMMU_GetActiveControl(g_pakInterfaceScreen->m_pUserList, i);
            PAK_ASSERT(4200, pObject != 0, s_pakAssertListObject);
            PAK_ASSERT(4202, pObject->m_pItem->m_WidgetType == 4, s_pakAssertListObjectType);
            pItem = (PAKListTextItem *)pObject->m_pItem;
            PAK_ASSERT(4206, ((const u8 *)pItem->m_pText)[0] != 0, s_pakAssertTextString);
            pObject->m_Alpha = (u8)(cosf((f32)i + (f32)g_pakInterfaceScreen->m_UserBusy[i] / 300.0f) * 100.0f + 150.0f);
            switch (g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_FieldB48) {
            case 0:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_FieldB4C = g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_FieldB4C + 1;
                if (g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_FieldB4C >= 6) {
                    PAKInterface_DecPlayerNameCharacter(i);
                }
                break;
            case 1:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_FieldB4C = g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_FieldB4C + 1;
                if (g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_FieldB4C >= 6) {
                    PAKInterface_IncPlayerNameCharacter(i);
                }
                break;
            case 2:
                break;
            default:
                PAK_ASSERT(4231, 0, s_pakAssertScreenMode);
                break;
            }
            break;
        case 4:
            nSlot = g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_ListCursor - g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_ListTop;
            pObject = (PAKUserWidget *)g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_ListRows[nSlot];
            pObject->m_Alpha = (u8)(cosf((f32)i + (f32)g_pakInterfaceScreen->m_UserBusy[i] / 300.0f) * 100.0f + 150.0f);
            break;
        default:
            break;
        }
        g_pakInterfaceScreen->m_UserBusy[i] += anTicks;
    }
}
#endif

#if VERSION_US
/* Marks the user as having pressed start and moves the user's panel on to state 2. */
void PAKInterface_PressedStart(s32 anUser) {
    PAKUpdateInfo *pInfo;
    PAK_ASSERT(4296, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    pInfo = (PAKUpdateInfo *)g_pakUpdateInfo[anUser];
    pInfo->m_StartPressed = 1;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Panel = 2;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 2;
}
#endif

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

#if VERSION_US
/* Whether none of the user's four player data records holds a player. */
s32 PAKInterface_IsPlayerDataListEmpty(s32 anUser) {
    s32 i;
    s32 nEmpty;
    PAK_ASSERT(4466, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nEmpty = 1;
    for (i = 0; i < 4 && nEmpty == 1; i++) {
        if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[i].m_User != -1) {
            nEmpty = 0;
        }
    }
    return nEmpty;
}
#endif

#if VERSION_US
/* The first of the user's four player data records holding no player, or -1. */
s32 PAKInterface_FindEmptyPlayerDataSlot(s32 anUser) {
    s32 i;
    s32 nSlot;
    PAK_ASSERT(4486, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nSlot = -1;
    for (i = 0; i < 4 && nSlot == -1; i++) {
        if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[i].m_User == -1) {
            nSlot = i;
        }
    }
    return nSlot;
}
#endif

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

#if VERSION_US
/* Puts the player anIndex of user anUser into the first empty middle-list slot; 0 when no slot is empty. */
s32 PAKInterface_AddPlayerToMiddle(s32 anUser, s32 anIndex) {
    s32 nSlot;
    s32 nAdded;
    PAK_ASSERT(4659, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    PAK_ASSERT(4660, anIndex >= 0 && anIndex < 4, s_pakAssertIndexRange);
    nAdded = 0;
    nSlot = PAKInterface_FindEmptyMiddleSlot();
    if (nSlot >= 0) {
        g_pakInterfaceScreen->m_Slot[nSlot].m_User = anUser;
        g_pakInterfaceScreen->m_Slot[nSlot].m_Record = anIndex;
        g_pakInterfaceScreen->m_Slot[nSlot].m_State = 1;
        nAdded = 1;
    } else {
        nAdded = 0;
        PAK_ASSERT(4676, 0, s_pakAssertNoEmptySlot);
    }
    return nAdded;
}
#endif

#if VERSION_US
/* Puts the player anIndex of user anUser into the middle-list slot anSlot. */
void PAKInterface_AddPlayerToSpecificMiddleSlot(s32 anUser, s32 anIndex, s32 anSlot) {
    PAK_ASSERT(4685, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    PAK_ASSERT(4686, anIndex >= 0 && anIndex < 4, s_pakAssertIndexRange);
    PAK_ASSERT(4687, anSlot >= 0 && anSlot < 4, s_pakAssertSlotRange);
    g_pakInterfaceScreen->m_Slot[anSlot].m_User = anUser;
    g_pakInterfaceScreen->m_Slot[anSlot].m_Record = anIndex;
    g_pakInterfaceScreen->m_Slot[anSlot].m_State = 1;
}
#endif

#if VERSION_US
/* Empties the middle-list slot holding the player anIndex of user anUser; 0 when it holds none. */
s32 PAKInterface_RemovePlayerFromMiddle(s32 anUser, s32 anIndex) {
    s32 i;
    s32 nRemoved;
    PAK_ASSERT(4700, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    PAK_ASSERT(4701, anIndex >= 0 && anIndex < 4, s_pakAssertIndexRange);
    nRemoved = 0;
    for (i = 0; i < 4 && !nRemoved; i++) {
        if (g_pakInterfaceScreen->m_Slot[i].m_User == anUser && g_pakInterfaceScreen->m_Slot[i].m_Record == anIndex) {
            g_pakInterfaceScreen->m_Slot[i].m_User = -1;
            g_pakInterfaceScreen->m_Slot[i].m_State = 2;
            nRemoved = 1;
        }
    }
    return nRemoved;
}
#endif

#if VERSION_US
/* The middle-list slot holding the player anIndex of user anUser, or -1. */
s32 PAKInterface_GetPlayerInMiddleSlot(s32 anUser, s32 anIndex) {
    s32 i;
    s32 found;
    PAK_ASSERT(4725, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    PAK_ASSERT(4726, anIndex >= 0 && anIndex < 4, s_pakAssertIndexRange);
    found = -1;
    for (i = 0; i < 4 && found == -1; i++) {
        if (g_pakInterfaceScreen->m_Slot[i].m_User == anUser && g_pakInterfaceScreen->m_Slot[i].m_Record == anIndex) {
            found = i;
        }
    }
    return found;
}
#endif

#if VERSION_US
/* The first middle-list slot with no player, or -1. */
s32 PAKInterface_FindEmptyMiddleSlot(void) {
    s32 i;
    s32 slot;
    slot = -1;
    for (i = 0; i < 4 && slot == -1; i++) {
        if (g_pakInterfaceScreen->m_Slot[i].m_User == -1) {
            slot = i;
        }
    }
    return slot;
}
#endif

#if VERSION_US
/* Whether none of the four middle-list slots holds a player. */
s32 PAKInterface_IsMiddleListEmpty(void) {
    s32 i;
    s32 empty;
    empty = 1;
    for (i = 0; i < 4 && empty == 1; i++) {
        if (g_pakInterfaceScreen->m_Slot[i].m_User != -1) {
            empty = 0;
        }
    }
    return empty;
}
#endif

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

#if VERSION_US
/* Reads the Controller Pak notes into the management list rows and shows the free pages and the pages a save takes. */
void PAKInterface_InitPakManagement(s32 anUser) {
    s32 i;
    s32 bFound;
    char szName[16];
    u8 abReserved[8];
    u8 szExt[8];
    s32 anInfoA[2];
    s32 anInfoB[2];
    s32 nState;
    s32 bJapName;
    s32 nPages;
    s32 nBlocks;
    PAKLabel *pLabel;
    PAK_ASSERT(4965, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    bFound = 0;
    i = 0;
    while (i < 16 && bFound == 0) {
        if (PAK_GetNoteInfo(anUser, i, &nState, szName, szExt, &nPages, anInfoA, anInfoB) == 0) {
            if (nState == 1) {
                bJapName = IsJapName(szName, 16);
                if (bJapName == 1) {
                    x_strcpy(szName, pText_PAK_UnnamedNote[g_engineApp.m_Language]);
                }
                x_strcpy(PAK_PLAYER(anUser).m_Notes[i].m_Name, szName);
                x_sprintf(PAK_PLAYER(anUser).m_Notes[i].m_Size, s_pakFmtDecimal, nPages);
                if (szExt[0] != 0) {
                    x_sprintf(PAK_PLAYER(anUser).m_Notes[i].m_Line, s_pakFmtLineNamed, i + 1, PAK_PLAYER(anUser).m_Notes[i].m_Name, szExt);
                } else {
                    x_sprintf(PAK_PLAYER(anUser).m_Notes[i].m_Line, s_pakFmtLine, i + 1, PAK_PLAYER(anUser).m_Notes[i].m_Name);
                }
            } else {
                x_strcpy(PAK_PLAYER(anUser).m_Notes[i].m_Name, pText_PAK_Empty[g_engineApp.m_Language]);
                x_sprintf(PAK_PLAYER(anUser).m_Notes[i].m_Size, s_pakFmtDecimal, 0);
                x_sprintf(PAK_PLAYER(anUser).m_Notes[i].m_Line, s_pakFmtLine, i + 1, PAK_PLAYER(anUser).m_Notes[i].m_Name);
            }
        } else {
            x_strcpy(PAK_PLAYER(anUser).m_Notes[i].m_Name, pText_PAK_Empty[g_engineApp.m_Language]);
            x_sprintf(PAK_PLAYER(anUser).m_Notes[i].m_Size, s_pakFmtDecimal, 0);
            x_sprintf(PAK_PLAYER(anUser).m_Notes[i].m_Line, s_pakFmtLine, i + 1, PAK_PLAYER(anUser).m_Notes[i].m_Name);
            bFound = 1;
        }
        i++;
    }
    if (bFound == 0) {
        pLabel = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 726);
        PAK_ASSERT(5017, pLabel != NULL, s_pakAssertNullObject);
        if (PAK_GetPagesFree(anUser, &nPages) == 0) {
            x_sprintf(PAK_PLAYER(anUser).m_PagesFreeText, s_pakFmtDecimal, nPages);
            pLabel->m_pText = PAK_PLAYER(anUser).m_PagesFreeText;
            pLabel = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 725);
            PAK_ASSERT(5025, pLabel != NULL, s_pakAssertNullObject);
            nPages = PAKInterface_CalcSaveGameSize();
            nBlocks = PAK_PagesForBytes(nPages);
            x_sprintf(PAK_PLAYER(anUser).m_BlocksText, s_pakFmtDecimal, nBlocks);
            pLabel->m_pText = PAK_PLAYER(anUser).m_BlocksText;
        } else {
            bFound = 1;
        }
    }
    if (bFound == 1) {
        PAK_PLAYER(anUser).m_State = 1;
        PAKInterface_InitPlayerMode(anUser);
        return;
    }
    PAK_PLAYER(anUser).m_ListCursor = -1;
    PAK_PLAYER(anUser).m_ListTop = 0;
    PAK_PLAYER(anUser).m_ListRows[0] = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 729);
    PAK_ASSERT(5055, PAK_PLAYER(anUser).m_ListRows[0] != NULL, s_pakAssertTopListRowPresent);
    PAK_PLAYER(anUser).m_ListRows[1] = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 730);
    PAK_ASSERT(5058, PAK_PLAYER(anUser).m_ListRows[1] != NULL, s_pakAssertMiddleListRowPresent);
    PAK_PLAYER(anUser).m_ListRows[2] = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 731);
    PAK_ASSERT(5061, PAK_PLAYER(anUser).m_ListRows[2] != NULL, s_pakAssertBottomListRowPresent);
    PAKInterface_ScrollManagementList(anUser, 1);
}
#endif

#if VERSION_US
/* Moves the management list cursor and window one row and points the three visible rows and the size label at their text. */
void PAKInterface_ScrollManagementList(s32 anUser, s32 anDirection) {
    s32 i;
    s32 nCursor;
    PAKLabel *pLabel;
    PAK_ASSERT(5075, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    if (anDirection == 1) {
        if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListCursor < 15) {
            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListCursor = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListCursor + 1;
            if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListTop + 3 <= g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListCursor) {
                if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListTop + 3 < 15) {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListTop = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListTop + 1;
                } else {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListTop = 13;
                }
            }
        }
    } else {
        if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListCursor > 0) {
            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListCursor = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListCursor - 1;
            if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListTop > 0) {
                if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListCursor - g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListTop < 0) {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListTop = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListTop - 1;
                }
            }
        }
    }
    i = 0;
    while (i < 3) {
        g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListRows[i]->m_Alpha = 255;
        pLabel = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListRows[i];
        PAK_ASSERT(5125, pLabel != NULL, s_pakAssertNullObject);
        pLabel->m_pText = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Notes[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListTop + i].m_Line;
        i++;
    }
    nCursor = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_ListCursor;
    pLabel = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pWidget, 724);
    pLabel->m_pText = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Notes[nCursor].m_Size;
}
#endif

#if VERSION_US
/* Sets *apResult when the user's Controller Pak has a free note and enough free pages for a save block; returns the pak error code. */
s32 PAKInterface_CheckForRoomOnPak(s32 anUser, s32 *apResult) {
    s32 nNeeded;
    s32 nPages;
    s32 nNotes;
    s32 nSize;
    s32 nRet;
    PAK_ASSERT(5157, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    *apResult = 0;
    nRet = PAK_GetPagesFree(anUser, &nPages);
    if (nRet == 0) {
        nRet = PAK_GetNotesFree(anUser, &nNotes);
        if (nRet == 0) {
            nSize = PAKInterface_CalcSaveGameSize();
            nNeeded = PAK_PagesForBytes(nSize);
            if (nNotes == 0 || nPages < nNeeded) {
                *apResult = 0;
            } else {
                *apResult = 1;
            }
        }
    }
    return nRet;
}
#endif

#if VERSION_US
/* The byte size of the pak save block. */
s32 PAKInterface_CalcSaveGameSize(void) {
    s32 size;

    size = 1608;
    return size;
}
#endif

#if VERSION_US
/* Copies the user's four middle records into the save block and stamps its marker and checksum. */
void PAKInterface_PrepareSaveBlockForSave(s32 anUser) {
    PAKGlobalPlayer *pSource;
    PAKSaveBlock *pBlock;
    s32 nSize;
    PAK_ASSERT(5221, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    pSource = &g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[0];
    pBlock = &g_pakInterfaceScreen->m_SaveBlock;
    nSize = PAK_SAVE_DATA_SIZE;
    memcpy(pBlock, pSource, nSize);
    g_pakInterfaceScreen->m_SaveBlock.m_Marker = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Marker;
    g_pakInterfaceScreen->m_SaveBlock.m_Checksum = Chksum(pBlock, nSize, PAK_CHECKSUM_SEED);
}
#endif

#if VERSION_US
/* Copies the loaded save block back into the user's four middle records and takes its marker. */
void PAKInterface_PrepareDataAfterLoad(s32 anUser) {
    PAKSaveBlock *pBlock;
    PAKGlobalPlayer *pDestination;
    s32 nSize;
    PAK_ASSERT(5242, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    pBlock = &g_pakInterfaceScreen->m_SaveBlock;
    pDestination = &g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[0];
    nSize = PAK_SAVE_DATA_SIZE;
    memcpy(pDestination, pBlock, nSize);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Marker = g_pakInterfaceScreen->m_SaveBlock.m_Marker;
}
#endif

#if VERSION_US
/* Copies each slot's middle record into its global player, or marks the global player unowned. */
void PAKInterface_CopyMiddlePlayersToGlobal(void) {
    PAKGlobalPlayer *pSource;
    PAKGlobalPlayer *pGlobal;
    s32 i;
    s32 nSize;
    s32 nUser;
    s32 nRecord;
    for (i = 0; i < 4; i++) {
        nUser = g_pakInterfaceScreen->m_Slot[i].m_User;
        nRecord = g_pakInterfaceScreen->m_Slot[i].m_Record;
        pGlobal = &g_pakGlobalPlayers[i];
        if (nUser != -1) {
            pSource = &g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nRecord];
            nSize = PAK_PLAYER_RECORD_SIZE;
            memcpy(pGlobal, pSource, nSize);
            pGlobal->m_Slot = nRecord;
        } else {
            pGlobal->m_User = -1;
        }
    }
}
#endif

#if VERSION_US
/* Copies one slot's middle record into its global player and records which slot and user it came from, or marks the global player unowned. */
void PAKInterface_CopySpecificMiddlePlayerToGlobal(s32 anSlot) {
    PAKGlobalPlayer *pSource;
    PAKGlobalPlayer *pGlobal;
    s32 nSize;
    s32 nUser;
    s32 nRecord;
    nUser = g_pakInterfaceScreen->m_Slot[anSlot].m_User;
    nRecord = g_pakInterfaceScreen->m_Slot[anSlot].m_Record;
    pGlobal = &g_pakGlobalPlayers[anSlot];
    if (nUser != -1) {
        pSource = &g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nRecord];
        nSize = PAK_PLAYER_RECORD_SIZE;
        memcpy(pGlobal, pSource, nSize);
        pGlobal->m_Slot = nRecord;
        pGlobal->m_User = nUser;
    } else {
        pGlobal->m_User = -1;
    }
}
#endif

#if VERSION_US
/* Writes the user's save block to a Controller Pak note (replacing the game's existing note when there is one); returns 1 when it was written. */
s32 PAKInterface_SaveGame(s32 anUser) {
    s32 nRoom;
    s32 nRet;
    s32 nSize;
    s32 nNote;
    s32 nExt;
    char sName[16];
    PAKSaveBlock *pBlock;
    s32 bSaved;
    s32 i;
    PAK_ASSERT(5327, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    bSaved = 0;
    if (PAK_AnySavesOnPak(pText_MultiFileName[g_engineApp.m_Language], anUser, &nNote) == 1) {
        nRet = PAK_DeleteNote(anUser, nNote);
        if (nRet == 0) {
            bSaved = 1;
        }
    } else {
        nRet = PAKInterface_CheckForRoomOnPak(anUser, &nRoom);
        if (nRet == 0 && nRoom == 1) {
            bSaved = 1;
        }
    }
    if (bSaved == 1) {
        bSaved = 0;
        nRet = PAK_FindFirstAvailableExt(anUser, &nExt);
        if (nRet == 0) {
            nSize = PAKInterface_CalcSaveGameSize();
            PAKInterface_PrepareSaveBlockForSave(anUser);
            pBlock = &g_pakInterfaceScreen->m_SaveBlock;
            i = 0;
            while (i < 16) {
                sName[i] = 0;
                i++;
            }
            x_strcpy(sName, pText_MultiFileName[g_engineApp.m_Language]);
            nRet = PAK_WriteNote(anUser, nSize, pBlock, sName, &nExt, pText_GameCode[g_engineApp.m_Language]);
            if (nRet == 0) {
                bSaved = 1;
            }
        }
    }
    if (bSaved == 0) {
        g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Panel = 2;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 2;
        PAKInterface_InitPlayerMode(anUser);
    }
    return bSaved;
}
#endif

#if VERSION_US
/* Reads the user's save note into the screen's save block and keeps it when its checksum holds (else deletes the note); returns 1 when loaded. */
s32 PAKInterface_LoadGame(s32 anUser, s32 anNote) {
    s32 nRet;
    s32 nSize;
    PAKSaveBlock *pBlock;
    s32 bLoaded;
    s32 nChecksum;
    PAK_ASSERT(5398, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    bLoaded = 0;
    nSize = PAKInterface_CalcSaveGameSize();
    pBlock = &g_pakInterfaceScreen->m_SaveBlock;
    nRet = PAK_ReadNote(anUser, anNote, pBlock, nSize);
    if (nRet == 0) {
        nSize = PAK_SAVE_DATA_SIZE;
        nChecksum = Chksum(pBlock, nSize, PAK_CHECKSUM_SEED);
        if (nChecksum == pBlock->m_Checksum) {
            PAKInterface_PrepareDataAfterLoad(anUser);
            bLoaded = 1;
        } else {
            nRet = PAK_DeleteNote(anUser, anNote);
        }
    } else {
        nRet = PAK_DeleteNote(anUser, anNote);
    }
    if (bLoaded == 0) {
        g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Panel = 2;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 2;
    }
    return bLoaded;
}
#endif

#if VERSION_US
/* Counts the player slots whose state is neither empty, staged nor released. */
s32 PAKInterface_GetNActive(void) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i < 4; i++) {
        if (g_playerSlotTable->slots[i].state != PLAYER_SLOT_EMPTY && g_playerSlotTable->slots[i].state != PLAYER_SLOT_STAGED && g_playerSlotTable->slots[i].state != PLAYER_SLOT_RELEASED) {
            count++;
        }
    }
    return count;
}
#endif

#if VERSION_US
/* Counts the player slots that are neither empty nor released. */
s32 PAKInterface_GetNPlayerInfoActive(void) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i < 4; i++) {
        if (g_playerSlotTable->slots[i].state != PLAYER_SLOT_EMPTY && g_playerSlotTable->slots[i].state != PLAYER_SLOT_RELEASED) {
            count++;
        }
    }
    return count;
}
#endif

#if VERSION_US
/* Counts the player slots whose state is not empty. */
s32 PAKInterface_GetNPlayersJoined(void) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i < 4; i++) {
        if (g_playerSlotTable->slots[i].state != PLAYER_SLOT_EMPTY) {
            count++;
        }
    }
    return count;
}
#endif

#if VERSION_US
/* Returns -1 when any slot is live; otherwise the index of the first staged slot, or -1 when none is. */
s32 PAKInterface_GetNextPlayerToChooseName(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_playerSlotTable->slots[i].state != PLAYER_SLOT_EMPTY && g_playerSlotTable->slots[i].state != PLAYER_SLOT_RELEASED && g_playerSlotTable->slots[i].state != PLAYER_SLOT_STAGED) {
            return -1;
        }
    }
    i = 0;
    while (i < 4) {
        if (g_playerSlotTable->slots[i].state == PLAYER_SLOT_STAGED) {
            return i;
        }
        i++;
    }
    return -1;
}
#endif

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

#if VERSION_US

/* Reports a slot number outside 0..3 through the assert hook, then writes through a null pointer. */
void PAKInterface_InitPlayerInfo(s32 anSlot) {
    if (anSlot >= 0 && anSlot < 4) {
        return;
    }
    if (AssertFailed(s_playerSlotsSourceFile, 5579, s_playerSlotsAssertSlotIndex)) {
        HaltAfterFailedAssert();
    }
}
#endif

#if VERSION_US
/* Starts leaving the screen: disables input and picks the target the frontend mode returns to when the caller passes -2. */
void PAKInterface_ExitScreen(s32 anTarget) {
    TSMOS_InputDisable();
    g_pakInterfaceScreen->m_ExitPhase = 5;
    g_pakInterfaceScreen->m_ExitStep = 4;
    g_pakInterfaceScreen->m_ExitTarget = anTarget;
    if (anTarget == -2) {
        switch (g_engineApp.m_FrontendMode) {
        case 0:
            g_pakInterfaceScreen->m_ExitTarget = 7;
            break;
        case 1:
            g_pakInterfaceScreen->m_ExitTarget = 7;
            break;
        case 2:
            g_pakInterfaceScreen->m_ExitTarget = 9;
            break;
        case 3:
            g_pakInterfaceScreen->m_ExitTarget = 7;
            break;
        case 4:
            g_pakInterfaceScreen->m_ExitTarget = 10;
            break;
        default:
            PAK_ASSERT(5705, 0, s_pakAssertExitMode);
            break;
        }
    }
}
#endif

#if VERSION_US
/* Copies a user's quick-play record from the middle list into a free global slot and reports whether it was added. */
s32 PAKInterface_AddQuickPlayerToGlobal(s32 anUser) {
    s32 nRecord;
    s32 nGlobal;
    s32 nRet;
    PAKGlobalPlayer *pSource;
    PAKGlobalPlayer *pGlobal;
    PAK_ASSERT(5720, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nRet = 0;
    nRecord = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_QuickRecord;
    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_RecordState[nRecord] == 1) {
        nGlobal = PAKInterface_FindEmptyGlobalSlot();
        if (nGlobal >= 0) {
            PAKInterface_InitGlobalSlot(0, nGlobal);
            pSource = &g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[nRecord];
            pGlobal = &g_pakGlobalPlayers[nGlobal];
            memcpy(pGlobal, pSource, PAK_PLAYER_RECORD_SIZE);
            pGlobal->m_User = anUser;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Mode = 0;
            PAKInterface_RefreshMiddleList(-1);
            nRet = 1;
        }
    }
    return nRet;
}
#endif

#if VERSION_US
void PAKInterface_RemoveQuickPlayerFromGlobal(s32 anSlot) {
    PAK_ASSERT(5753, anSlot >= 0 && anSlot < 4, s_pakAssertSlotRange);
    if (g_pakInterfaceScreen->m_Slot[anSlot].m_State == 1) {
        CPersistentPlayerData_Initialize(&g_pakGlobalPlayers[anSlot]);
        g_pakInterfaceScreen->m_Slot[anSlot].m_State = 2;
        PAKInterface_RefreshMiddleList(-1);
    }
}
#endif

#if VERSION_US
s32 PAKInterface_GetGlobalPlayerByMarker(s32 anMarker, s32 anSlot) {
    s32 i;
    PAK_ASSERT(5770, anSlot >= 0 && anSlot < 4, s_pakAssertSlotRange);
    i = 0;
    while (i < 4) {
        if (g_pakGlobalPlayers[i].m_Slot == anSlot && g_pakGlobalPlayers[i].m_Marker == anMarker) {
            return i;
        }
        i++;
    }
    return -1;
}
#endif

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

#if VERSION_US
void PAKInterface_UpdatePAK(s32 anUser) {
    s32 i;
    s32 nSlot;
    s32 nSize;
    PAK_ASSERT(5817, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nSize = 400;
    for (i = 0; i < 4; i++) {
        if (g_pakGlobalPlayers[i].m_Quick == 0 && g_pakGlobalPlayers[i].m_User == anUser
            && g_pakUpdateInfo[i][PAK_UPDATE_ACTIVE] == 1 && g_pakUpdateInfo[i][PAK_UPDATE_PENDING] == 0) {
            nSlot = g_pakGlobalPlayers[i].m_Slot;
            memcpy(&g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[nSlot], &g_pakGlobalPlayers[i], nSize);
        }
    }
}
#endif

#if VERSION_US
void PAKInterface_InitUpdateInfo(s32 anUser) {
    s32 i;
    s32 nCount;
    s32 nStringId;
    PAKListItem *pItem;
    PAK_ASSERT(5841, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nCount = 0;
    for (i = 0; i < 4; i++) {
        switch (nCount) {
        case 0:
            nStringId = 696;
            break;
        case 1:
            nStringId = 739;
            break;
        case 2:
            nStringId = 740;
            break;
        case 3:
            nStringId = 741;
            break;
        }
        if (g_pakGlobalPlayers[i].m_Quick == 0 && g_pakGlobalPlayers[i].m_User == anUser
            && g_pakUpdateInfo[i][PAK_UPDATE_ACTIVE] == 1 && g_pakUpdateInfo[i][PAK_UPDATE_PENDING] == 0) {
            pItem = PAKInterface_AddListItem(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pWidget, nStringId);
            pItem->m_pPlayer = &g_pakGlobalPlayers[i];
            nCount++;
        }
    }
}
#endif

#if VERSION_US
void PAKInterface_ResetControlBackToCopyPlayer(s32 anUser) {
    s32 nCopyUser;
    nCopyUser = g_pakInterfaceScreen->m_Slot[0].m_User;
    PAKInterface_SetControlOwner(g_pakInterfaceScreen->m_pUserList, nCopyUser, 0);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_State = 17;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameTarget = 0;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[nCopyUser].m_Panel = 2;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[nCopyUser].m_State = 2;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[nCopyUser].m_Step = 13;
    g_pakInterfaceScreen->m_PAKInterfacePlayer[nCopyUser].m_Mode = 3;
    PAKInterface_InitPlayerMode(nCopyUser);
    PAKInterface_RefreshMiddleNamesForCopy(-1);
}
#endif

#if VERSION_US
void PAKInterface_IncPlayerNameCharacter(s32 anUser) {
    u8 c;
    void *pUserObject;
    g_pakInterfaceScreen->m_UserBusy[anUser] = 0;
    pUserObject = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, anUser);
    PAK_ASSERT(5914, pUserObject != 0, s_pakAssertUserObject);
    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch == 0) {
        g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch = 65;
    }
    c = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch;
    c++;
    if (c >= 91) {
        c = 32;
    }
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch = c;
}
#endif

#if VERSION_US
void PAKInterface_DecPlayerNameCharacter(s32 anUser) {
    u8 c;
    void *pUserObject;
    g_pakInterfaceScreen->m_UserBusy[anUser] = 0;
    pUserObject = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, anUser);
    PAK_ASSERT(5944, pUserObject != 0, s_pakAssertUserObject);
    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch == 0) {
        g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch = 65;
    }
    c = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch;
    c--;
    if (c < 32) {
        c = 90;
    }
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_NameCursor].ch = c;
}
#endif

/* The PAK sync code payload belongs to the retained SN object records of the US
 * PAK interface; it is not a second native screen handler. */

/* US screen callbacks share the original unoptimized compiler unit. */
#if VERSION_US
/* COMMENT */
s32 PAKInterface_OnCreate(s32 screenHandle, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed) {
    s32 nRem;
    s32 i;
    s32 j;
    PAKUserWidget *pObj;
    s32 nStatus;
    if (!(g_pakInterfaceScreen == 0)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 327, s_pakInterfaceScreenIsNull)) {
            HaltAfterFailedAssert();
        }
    }
    g_pakInterfaceScreen = alloc_debug(13428, s_pakInterfaceScreenSourceFile, 329);
    if (!g_pakInterfaceScreen) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 330, s_pakInterfaceScreenNotNull)) {
            HaltAfterFailedAssert();
        }
    }
    g_pakInterfaceScreen->m_pDisplayList = screenHandle;
    CWipeScreen_InitWipe(g_pakInterfaceScreen->m_Wipe, 103, 0, 0, 0);
    g_pakInterfaceScreen->m_pUserList = SMMU_MakeScreenMultiUser(screenHandle, 4);
    SMMU_SetActiveControl(screenHandle, 0, 643);
    SMMU_SetActiveControl(screenHandle, 1, 643);
    SMMU_SetActiveControl(screenHandle, 2, 643);
    SMMU_SetActiveControl(screenHandle, 3, 643);
    for (i = 0; i < 4; i++) {
        g_pakInterfaceScreen->m_UserBusy[i] = 0;
    }
    g_pakInterfaceScreen->m_ExitPhase = 1;
    g_pakInterfaceScreen->m_ExitStep = 4;
    g_pakInterfaceScreen->m_pBarA = SM_DLFindObjectByID(screenHandle, 761);
    g_pakInterfaceScreen->m_pBarA->m_X = g_pakInterfaceScreen->m_pBarA->m_X - g_pakInterfaceScreen->m_pBarA->m_Width;
    g_pakInterfaceScreen->m_BarStepA.m_Word = (s16)(g_pakInterfaceScreen->m_pBarA->m_Width / 4);
    nRem = g_pakInterfaceScreen->m_pBarA->m_Width - g_pakInterfaceScreen->m_BarStepA.m_Word * 4;
    g_pakInterfaceScreen->m_pBarA->m_X = g_pakInterfaceScreen->m_pBarA->m_X + nRem;
    g_pakInterfaceScreen->m_pBarB = SM_DLFindObjectByID(screenHandle, 672);
    g_pakInterfaceScreen->m_pBarB->m_X = g_pakInterfaceScreen->m_pBarB->m_X + g_pakInterfaceScreen->m_pBarB->m_Width;
    g_pakInterfaceScreen->m_BarStepB.m_Word = (s16)(g_pakInterfaceScreen->m_pBarB->m_Width / 4);
    nRem = g_pakInterfaceScreen->m_pBarB->m_Width - g_pakInterfaceScreen->m_BarStepB.m_Word * 4;
    g_pakInterfaceScreen->m_pBarB->m_X = g_pakInterfaceScreen->m_pBarB->m_X - nRem;
    pObj = SM_DLFindObjectByID(screenHandle, 644);
    pObj->m_Alpha = 110;
    g_pakInterfaceScreen->m_pFlicker = SMFL_MakeFlicker(645, 255);
    g_pakInterfaceScreen->m_pFlickerWidget = SM_DLFindObjectByID(screenHandle, 645);
    SM_DLSetVisible(g_pakInterfaceScreen->m_pFlickerWidget, 0);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[0].m_pObject = SM_DLFindObjectByID(screenHandle, 762);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[1].m_pObject = SM_DLFindObjectByID(screenHandle, 673);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[2].m_pObject = SM_DLFindObjectByID(screenHandle, 763);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[3].m_pObject = SM_DLFindObjectByID(screenHandle, 760);
    g_pakInterfaceScreen->m_Mode = g_pakInterfaceScreenMode;
    for (i = 0; i < 4; i++) {
        g_pakInterfaceScreen->m_Slot[i].m_User = -1;
        g_pakInterfaceScreen->m_Slot[i].m_Record = 0;
        g_pakInterfaceScreen->m_Slot[i].m_State = 2;
    }
    switch (g_pakInterfaceScreen->m_Mode) {
    case 5:
        pObj = SM_DLFindObjectByID(screenHandle, 657);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    case 6:
        pObj = SM_DLFindObjectByID(screenHandle, 660);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    case 4:
        pObj = SM_DLFindObjectByID(screenHandle, 646);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    case 0:
        pObj = SM_DLFindObjectByID(screenHandle, 671);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    case 3:
        pObj = SM_DLFindObjectByID(screenHandle, 659);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    case 7:
        break;
    case 1:
        pObj = SM_DLFindObjectByID(screenHandle, 647);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        for (i = 0; i < 4; i++) {
            if (g_pakGlobalPlayers[i].m_User >= 0 && g_pakGlobalPlayers[i].m_Quick == 1) {
                g_pakGlobalPlayers[i].m_User = -1;
                g_pakGlobalPlayers[i].m_Quick = 0;
            }
            if (g_pakGlobalPlayers[i].m_User >= 0) {
                g_pakInterfaceScreen->m_Slot[i].m_User = 0;
                g_pakInterfaceScreen->m_Slot[i].m_Record = i;
                g_pakInterfaceScreen->m_Slot[i].m_State = 1;
            }
        }
        k_PortalAfterIsMiddleListEmpty(-1);
        break;
    case 2:
        pObj = SM_DLFindObjectByID(screenHandle, 661);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    default:
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 555, s_pakInterfaceScreenFalse)) {
            HaltAfterFailedAssert();
        }
        break;
    }
    i = 0;
    while (i < 4) {
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_State = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_pWidget = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_Panel = -1;
        PAKInterface_InitPlayerMode(i);
        SetMemoryCardActive(i);
        for (j = 0; j < 4; j++) {
            CPersistentPlayerData_Initialize(&g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_MiddleRecords[j]);
        }
        j = 0;
        while (j < 16) {
            memset(g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_Notes[j].m_Name, 0, 20);
            memset(g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_Notes[j].m_Size, 0, 10);
            j++;
        }
        memset(g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_PagesFreeText, 0, 10);
        memset(g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_BlocksText, 0, 10);
        memset(g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_TextAB8, 0, 10);
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_ListCursor = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_QuickRecord = 0;
        for (j = 0; j < 4; j++) {
            g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_RecordState[j] = 2;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_pSlotObject[j] = 0;
        }
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_FieldB3C = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_NameTarget = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_Marker = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_Mode = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_Step = -1;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_SelectedRecord = -1;
        i++;
    }
    g_pakInterfaceScreen->m_ExitTarget = -1;
    switch (g_pakInterfaceScreen->m_Mode) {
    case 5:
        i = 0;
        while (i < 4) {
            g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_State = 14;
            i++;
        }
        i = 0;
        while (i < 4) {
            if (g_pakGlobalPlayers[i].m_Quick == 0 && g_pakGlobalPlayers[i].m_User >= 0 && g_pakUpdateInfo[i][PAK_UPDATE_ACTIVE] == 1 && g_pakUpdateInfo[i][PAK_UPDATE_PENDING] == 0) {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[g_pakGlobalPlayers[i].m_User].m_Panel = 2;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[g_pakGlobalPlayers[i].m_User].m_State = 2;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[g_pakGlobalPlayers[i].m_User].m_Step = 6;
            }
            i++;
        }
        i = 0;
        while (i < 4) {
            PAKInterface_InitPlayerMode(i);
            i++;
        }
        break;
    case 6:
        if (gnAccessingPak_CurrentMode == 0) {
            for (i = 0; i < 4; i++) {
                PAK_UpdateSingle(i);
                nStatus = PAK_CheckStatus(i);
                switch (nStatus) {
                case -4:
                case -3:
                case -1:
                case 0:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_Panel = 2;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_State = 2;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[i].m_Step = 4;
                    PAKInterface_InitPlayerMode(i);
                    break;
                }
            }
        } else {
            PAK_UpdateSingle(gnAccessingPak_CurrentPAK);
            nStatus = PAK_CheckStatus(gnAccessingPak_CurrentPAK);
            switch (nStatus) {
            case -4:
            case -3:
            case -1:
            case 0:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[gnAccessingPak_CurrentPAK].m_Panel = 2;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[gnAccessingPak_CurrentPAK].m_State = 2;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[gnAccessingPak_CurrentPAK].m_Step = 4;
                PAKInterface_InitPlayerMode(gnAccessingPak_CurrentPAK);
                break;
            }
        }
        break;
    case 7:
        g_pakInterfaceScreen->m_PAKInterfacePlayer[0].m_Panel = 2;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[0].m_State = 2;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[0].m_Step = 13;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[0].m_Mode = 6;
        PAKInterface_InitPlayerMode(0);
        break;
    }
    Video_SetNextMode(0);
    TSMOS_InputDisable();
    Tsmos_SetMenuModelFlag(0);
    Sound_PlayFXGlobal(3704);
    return 0;
}
#endif

#if VERSION_US
/* COMMENT */
s32 PAKInterface_OnRender(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed) {
    s32 i;
    if (playerEntryId == 1) {
        if (g_pakInterfaceScreen->m_ExitPhase == 3) {
            for (i = 0; i < 4; i++) {
                if (PAK_PLAYER(i).m_Panel > 0) {
                    PAK_PLAYER(i).m_Panel = PAK_PLAYER(i).m_Panel - 1;
                    if (PAK_PLAYER(i).m_Panel == 0) {
                        PAK_PLAYER(i).m_Panel = -1;
                        TSMOS_InputDisable();
                        PAK_UpdateSingle(i);
                        PAKInterface_CheckPAK(i);
                        Tsmos_ActivateControllerState();
                    }
                }
            }
        }
        if (CWipeScreen_GetState(&g_pakInterfaceScreen->m_Wipe) == 1) {
            CWipeScreen_DrawWipe(&g_pakInterfaceScreen->m_Wipe);
            CWipeScreen_UpdateWipe(&g_pakInterfaceScreen->m_Wipe);
            if (CWipeScreen_GetState(&g_pakInterfaceScreen->m_Wipe) == 2) {
                if (g_pakInterfaceScreen->m_Mode == 5) {
                    SM_AcknowledgeMsg();
                    switch (g_engineApp.m_FrontendMode) {
                    case 0:
                        MultiTallyScreen_ContinueGame();
                        break;
                    case 2:
                        MultiTallyScreen_CoOpContinueGame();
                        break;
                    case 1:
                    case 3:
                    case 4:
                        ScenarioTallyScreen_ContinueGame();
                        break;
                    default:
                        if (AssertFailed(s_pakInterfaceScreenSourceFile, 826, s_pakInterfaceScreenFalse)) {
                            HaltAfterFailedAssert();
                        }
                        break;
                    }
                }
                return 0;
            }
        }
    }
    return 0;
}
#endif

#if VERSION_US
typedef union PAKAcceptValue {
    s32 m_Value;
    void *m_Pointer;
    PAKPlayerSetup *m_Setup;
} PAKAcceptValue;

/* Handles the selected memory-pak action for the active user and screen mode. */
s32 PAKInterface_OnAccept(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed) {
    s32 nIndex = 0;
    s32 nUser;
    s32 nCtrl;
    s32 nSlot;
    s32 nResult;
    s32 nCount;
    s32 nCursor;
    PAKNameWidget *pWidget;
    PAKLabel *pLabel;
    s32 nRoom;
    PAKAcceptValue nTemp;
    void *pCopyTarget;
    s32 nUserA;
    s32 nSlotA;
    SM_AcknowledgeMsg();
    nUser = playerEntryId & 0xffff;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 1923, s_pakInterfaceScreenUserInRange)) {
            HaltAfterFailedAssert();
        }
    }
    nCtrl = SMMU_GetActiveControlID(g_pakInterfaceScreen->m_pUserList, nUser);
    switch (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State) {
    case 1:
        switch (nCtrl) {
        case 748:
            switch (g_pakInterfaceScreen->m_Mode) {
            case 0:
            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                PAKInterface_InitPlayerMode(nUser);
                break;
            case 2:
                if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameTarget == 1) {
                    PAKInterface_ResetControlBackToCopyPlayer(nUser);
                } else {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                }
                PAKInterface_InitPlayerMode(nUser);
                break;
            case 7:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 26;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Step = 1;
                PAKInterface_InitPlayerMode(nUser);
                break;
            default:
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 1962, s_pakInterfaceScreenFalse)) {
                    HaltAfterFailedAssert();
                }
                break;
            }
            break;
        case 747:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 3:
        switch (nCtrl) {
        case 699:
            switch (g_pakInterfaceScreen->m_Mode) {
            case 0:
            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                PAKInterface_InitPlayerMode(nUser);
                break;
            case 7:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 26;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Step = 1;
                PAKInterface_InitPlayerMode(nUser);
                break;
            case 2:
                if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameTarget == 1) {
                    PAKInterface_ResetControlBackToCopyPlayer(nUser);
                } else {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                }
                PAKInterface_InitPlayerMode(nUser);
                break;
            default:
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 2006, s_pakInterfaceScreenFalse)) {
                    HaltAfterFailedAssert();
                }
                break;
            }
            break;
        case 698:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 28;
            PAKInterface_InitPlayerMode(nUser);
            break;
        case 700:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 15:
        switch (nCtrl) {
        case 750:
            nResult = PAKInterface_CheckForRoomOnPak(nUser, &nRoom);
            if (nResult == 0) {
                if (nRoom == 1) {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 12;
                } else {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 11;
                }
            } else {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
            }
            PAKInterface_InitPlayerMode(nUser);
            break;
        case 751:
            switch (g_pakInterfaceScreen->m_Mode) {
            case 7:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 26;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Step = 15;
                break;
            default:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                break;
            }
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 16:
        switch (nCtrl) {
        case 694:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_Slot = (u8)g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_User = (u8)nUser;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_Marker = g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Marker;
            if (g_pakInterfaceScreen->m_Mode == 7) {
                nTemp.m_Setup = &g_engineApp.m_PlayerSetup;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_QuickSetup[0] = nTemp.m_Setup->m_QuickSetupSource[2];
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_QuickSetup[1] = nTemp.m_Setup->m_QuickSetupSource[4];
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_QuickSetup[2] = nTemp.m_Setup->m_QuickSetupSource[0];
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_QuickSetup[3] = nTemp.m_Setup->m_QuickSetupSource[1];
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_QuickSetup[4] = nTemp.m_Setup->m_QuickSetupSource[6];
            }
            if (PAKInterface_SaveGame(nUser) == 1) {
                switch (g_pakInterfaceScreen->m_Mode) {
                case 0:
                    if (PAKInterface_FindEmptyPlayerDataSlot(nUser) >= 0) {
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 23;
                    } else {
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                    }
                    break;
                case 7:
                    PAKInterface_AddPlayerToSpecificMiddleSlot(nUser, 0, 0);
                    PAKInterface_CopySpecificMiddlePlayerToGlobal(0);
                    SM_AcknowledgeMsg();
                    PAKInterface_ExitScreen(9);
                    return 0;
                    break;
                default:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 13;
                    break;
                }
                PAKInterface_InitPlayerMode(nUser);
            }
            break;
        case 695:
            switch (g_pakInterfaceScreen->m_Mode) {
            case 0:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 23;
                break;
            case 1:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 23;
                break;
            case 7:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 23;
                break;
            default:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 13;
                break;
            }
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 12:
        nSlot = PAKInterface_FindEmptyPlayerDataSlot(nUser);
        if (nSlot >= 0) {
            pWidget = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_pWidget, 753);
            nCursor = 0;
            while (pWidget->m_Flags & 0x10) {
                pLabel = pWidget->m_pLabel;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nSlot].m_Name[nCursor] = *pLabel->m_pText;
                nTemp.m_Pointer = pWidget;
                if (((PAKNameWidget *)nTemp.m_Pointer)->m_pNext) {
                    pWidget = ((PAKNameWidget *)nTemp.m_Pointer)->m_pNext;
                } else {
                    break;
                }
                nCursor++;
                if (!(nCursor < 7)) {
                    if (AssertFailed(s_pakInterfaceScreenSourceFile, 2189, s_pakInterfaceScreenNameIndexRange)) {
                        HaltAfterFailedAssert();
                    }
                }
            }
            nCursor = 6;
            for (; nCursor > 0; nCursor--) {
                if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nSlot].m_Name[nCursor] == 0 || g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nSlot].m_Name[nCursor] == 32) {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nSlot].m_Name[nCursor] = 0;
                } else {
                    break;
                }
            }
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 16;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C = nSlot;
        } else {
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 3;
        }
        PAKInterface_InitPlayerMode(nUser);
        break;
    case 11:
        switch (nCtrl) {
        case 720:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 4;
            PAKInterface_InitPlayerMode(nUser);
            break;
        case 721:
            switch (g_pakInterfaceScreen->m_Mode) {
            case 0:
            case 1:
            case 3:
            case 4:
            case 5:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                PAKInterface_InitPlayerMode(nUser);
                break;
            case 2:
                if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameTarget == 1) {
                    PAKInterface_ResetControlBackToCopyPlayer(nUser);
                } else {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                }
                PAKInterface_InitPlayerMode(nUser);
                break;
            case 7:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 26;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Step = 11;
                PAKInterface_InitPlayerMode(nUser);
                break;
            default:
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 2252, s_pakInterfaceScreenFalse)) {
                    HaltAfterFailedAssert();
                }
                break;
            }
            break;
        }
        break;
    case 4:
        switch (nCtrl) {
        case 728:
            switch (g_pakInterfaceScreen->m_Mode) {
            case 6:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                break;
            case 0:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 15;
                break;
            case 4:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                break;
            case 2:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
                break;
            case 7:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
                break;
            case 1:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                break;
            default:
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 2298, s_pakInterfaceScreenFalse)) {
                    HaltAfterFailedAssert();
                }
                break;
            }
            PAKInterface_InitPlayerMode(nUser);
            break;
        case 727:
            nIndex = g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_ListCursor;
            nCount = x_atoi(g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Notes[nIndex].m_Size);
            if (nCount > 0) {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 8;
                PAKInterface_InitPlayerMode(nUser);
            }
            break;
        }
        break;
    case 8:
        switch (nCtrl) {
        case 718:
            nIndex = g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_ListCursor;
            if (!PAK_DeleteNote(nUser, nIndex)) {
                if (!x_stricmp(pText_MultiFileName[g_engineApp.m_Language], g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Notes[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_ListCursor].m_Name)) {
                    for (nCursor = 0; nCursor < 4; nCursor++) {
                        nTemp.m_Value = PAKInterface_GetGlobalPlayerByMarker(g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Marker, g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nCursor].m_Slot);
                        if (nTemp.m_Value != -1) {
                            CPersistentPlayerData_Initialize(&g_pakGlobalPlayers[nTemp.m_Value]);
                        }
                    }
                }
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 4;
                PAKInterface_InitPlayerMode(nUser);
            } else {
                PAK_UpdateSingle(nUser);
                PAKInterface_CheckPAK(nUser);
            }
            break;
        case 717:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 4;
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 7:
        switch (nCtrl) {
        case 715:
            nIndex = g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_QuickRecord;
            nTemp.m_Value = PAKInterface_GetGlobalPlayerByMarker(g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Marker, g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nIndex].m_Slot);
            if (nTemp.m_Value != -1) {
                CPersistentPlayerData_Initialize(&g_pakGlobalPlayers[nTemp.m_Value]);
            }
            CPersistentPlayerData_Initialize(&g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nIndex]);
            if (PAKInterface_SaveGame(nUser) == 1) {
                switch (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Mode) {
                case 5:
                    switch (g_pakInterfaceScreen->m_Mode) {
                    case 0:
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Step = 12;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Mode = 0;
                        break;
                    case 2:
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Step = 9;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Mode = 3;
                        break;
                    default:
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 13;
                        break;
                    }
                    break;
                default:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 13;
                    break;
                }
                PAKInterface_InitPlayerMode(nUser);
            }
            break;
        case 714:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 13;
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 9:
        switch (nCtrl) {
        case 711:
            nSlot = PAKInterface_FindEmptyPlayerDataSlot(nUser);
            if (nSlot >= 0) {
                nIndex = 0;
                nUserA = g_pakInterfaceScreen->m_Slot[nIndex].m_User;
                nSlotA = g_pakInterfaceScreen->m_Slot[nIndex].m_Record;
                nTemp.m_Pointer = &g_pakInterfaceScreen->m_PAKInterfacePlayer[nUserA].m_MiddleRecords[nSlotA];
                pCopyTarget = &g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nSlot];
                memcpy(pCopyTarget, nTemp.m_Pointer, 400);
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C = nSlot;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nSlot].m_Slot = (u8)nSlot;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[nSlot].m_Marker = g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Marker;
            }
            if (PAKInterface_SaveGame(nUser) == 1) {
                switch (g_pakInterfaceScreen->m_Mode) {
                case 2:
                    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameTarget == 1) {
                        PAKInterface_ResetControlBackToCopyPlayer(nUser);
                    } else {
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                    }
                    break;
                default:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 13;
                    break;
                }
                PAKInterface_InitPlayerMode(nUser);
            }
            break;
        case 710:
            switch (g_pakInterfaceScreen->m_Mode) {
            case 2:
                if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameTarget == 1) {
                    PAKInterface_ResetControlBackToCopyPlayer(nUser);
                } else {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                }
                break;
            default:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 13;
                break;
            }
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 13:
        switch (nCtrl) {
        case 691:
            switch (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Mode) {
            case 0:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                break;
            case 3:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 17;
                nResult = PAKInterface_GetNextPlayerToChooseName();
                if (nResult >= 0) {
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nResult].m_Panel = 2;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nResult].m_State = 2;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nResult].m_Step = 13;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nResult].m_Mode = 3;
                    PAKInterface_InitPlayerMode(nResult);
                }
                break;
            case 6:
                switch (g_pakInterfaceScreen->m_Mode) {
                case 1:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 17;
                    nResult = PAKInterface_GetNextPlayerToChooseName();
                    if (nResult >= 0) {
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nResult].m_Panel = 2;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nResult].m_State = 2;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nResult].m_Step = 13;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nResult].m_Mode = 6;
                        PAKInterface_InitPlayerMode(nResult);
                    }
                    break;
                case 7:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 26;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Step = 13;
                    break;
                }
                break;
            case 5:
                switch (g_pakInterfaceScreen->m_Mode) {
                case 3:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                    break;
                case 0:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Step = 12;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Mode = 0;
                    break;
                case 2:
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Step = 9;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Mode = 3;
                    break;
                }
                break;
            }
            PAKInterface_InitPlayerMode(nUser);
            break;
        default:
            nIndex = 0;
            switch (nCtrl) {
            case 692:
                nIndex = 0;
                break;
            case 689:
                nIndex = 1;
                break;
            case 686:
                nIndex = 2;
                break;
            case 690:
                nIndex = 3;
                break;
            default:
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 2626, s_pakInterfaceScreenFalse)) {
                    HaltAfterFailedAssert();
                }
                break;
            }
            switch (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Mode) {
            case 0:
                break;
            case 3:
                if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_RecordState[nIndex] == 1) {
                    PAKInterface_AddPlayerToSpecificMiddleSlot(nUser, nIndex, 0);
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_QuickRecord = nIndex;
                    g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 27;
                    PAKInterface_InitPlayerMode(nUser);
                }
                break;
            case 6:
                switch (g_pakInterfaceScreen->m_Mode) {
                case 1:
                    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_RecordState[nIndex] == 1) {
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_QuickRecord = nIndex;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 22;
                        PAKInterface_InitPlayerMode(nUser);
                    }
                    break;
                case 7:
                    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_RecordState[nIndex] == 1) {
                        PAKInterface_AddPlayerToSpecificMiddleSlot(nUser, nIndex, 0);
                        PAKInterface_CopySpecificMiddlePlayerToGlobal(0);
                        SM_AcknowledgeMsg();
                        PAKInterface_ExitScreen(9);
                        return 0;
                    }
                    break;
                }
                break;
            case 5:
                switch (g_pakInterfaceScreen->m_Mode) {
                case 0:
                case 2:
                case 3:
                    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_RecordState[nIndex] != 2) {
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_QuickRecord = nIndex;
                        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 7;
                        PAKInterface_InitPlayerMode(nUser);
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
        break;
    case 22:
        switch (nCtrl) {
        case 648:
            nIndex = 0;
            break;
        case 649:
            nIndex = 1;
            break;
        case 650:
            nIndex = 2;
            break;
        case 651:
            nIndex = 3;
            break;
        case 652:
            PAKInterface_ExitScreen(3);
            return 0;
            break;
        case 653: case 654: case 655:
            ;
        }
        PAKInterface_AddPlayerToSpecificMiddleSlot(nUser, g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_QuickRecord, nIndex);
        PAKInterface_CopySpecificMiddlePlayerToGlobal(nIndex);
        pWidget = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_pSlotObject[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_QuickRecord], 687);
        if (!pWidget) {
            if (AssertFailed(s_pakInterfaceScreenSourceFile, 2946, s_pakInterfaceScreenObjectNotNull)) {
                HaltAfterFailedAssert();
            }
        }
        SM_DLSetVisible(pWidget, 1);
        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_RecordState[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_QuickRecord] = 0;
        g_pakInterfaceScreen->m_Slot[nIndex].m_State = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_SelectedRecord = nIndex;
        PAKInterface_RefreshMiddleNamesForPlayerName(nUser);
        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 13;
        PAKInterface_InitPlayerMode(nUser);
        break;
    case 27:
        switch (nCtrl) {
        case 662:
            nIndex = 0;
            break;
        case 663:
            nIndex = 1;
            break;
        case 664:
            nIndex = 2;
            break;
        case 665:
            nIndex = 3;
            break;
        case 666:
            PAKInterface_ExitScreen(3);
            return 0;
            break;
        case 667: case 668: case 669:
            ;
        }
        if (nIndex != nUser) {
            SMMU_SetActiveControl(g_pakInterfaceScreen->m_pUserList, nUser, 1);
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nIndex].m_Panel = 2;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nIndex].m_State = 2;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nIndex].m_Step = 9;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nIndex].m_Mode = 3;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nIndex].m_NameTarget = 1;
            PAKInterface_InitPlayerMode(nIndex);
        } else {
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nIndex].m_State = 9;
            PAKInterface_InitPlayerMode(nIndex);
        }
        break;
    case 6:
        switch (nCtrl) {
        case 743:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
            PAKInterface_InitPlayerMode(nUser);
            break;
        case 742:
            PAKInterface_UpdatePAK(nUser);
            if (PAKInterface_SaveGame(nUser) == 1) {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                PAKInterface_InitPlayerMode(nUser);
            }
            break;
        }
        break;
    case 21:
        switch (nCtrl) {
        case 736:
            switch (g_pakInterfaceScreen->m_Mode) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                PAKInterface_InitPlayerMode(nUser);
                break;
            default:
                if (AssertFailed(s_pakInterfaceScreenSourceFile, 3223, s_pakInterfaceScreenFalse)) {
                    HaltAfterFailedAssert();
                }
                break;
            }
            break;
        case 737:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 23:
        switch (nCtrl) {
        case 683:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 12;
            PAKInterface_InitPlayerMode(nUser);
            break;
        case 684:
            switch (g_pakInterfaceScreen->m_Mode) {
            case 7:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 26;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Step = 23;
                break;
            default:
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
                break;
            }
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 24:
        switch (nCtrl) {
        case 681:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 13;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Mode = 5;
            PAKInterface_InitPlayerMode(nUser);
            break;
        case 680:
            if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameTarget == 1) {
                PAKInterface_ResetControlBackToCopyPlayer(nUser);
            } else {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
            }
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 25:
        switch (nCtrl) {
        case 745:
            if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameTarget == 1) {
                PAKInterface_ResetControlBackToCopyPlayer(nUser);
            } else {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 14;
            }
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 26:
        switch (nCtrl) {
        case 677:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[0].m_Panel = 2;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[0].m_State = 2;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[0].m_Step = 13;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[0].m_Mode = 6;
            PAKInterface_InitPlayerMode(nUser);
            break;
        case 678:
            CPersistentPlayerData_MakeQuickPlayer(0);
            SM_AcknowledgeMsg();
            PAKInterface_ExitScreen(9);
            return 0;
            break;
        }
        break;
    case 28:
        switch (nCtrl) {
        case 734:
            if (PAK_Repair(nUser)) {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 29;
                PAKInterface_InitPlayerMode(nUser);
            } else {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
                PAKInterface_InitPlayerMode(nUser);
            }
            break;
        case 733:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
        break;
    case 29:
        switch (nCtrl) {
        case 702:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Panel = 2;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State = 2;
            PAKInterface_InitPlayerMode(nUser);
            break;
        }
    default:
        break;
    }
    return 0;
}
#endif

#if VERSION_US
/* The first update of the screen has nothing to do: ignores all four arguments and reports 0. */
s32 PAKInterface_OnInitialUpdate(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed) {
    return 0;
}
#endif

#if VERSION_US
/* Releases the screen object through Cache_FreeMemory, clears g_pakInterfaceScreen, re-activates the controller state and
   calls Tsmos_SetMenuModelFlag with 1. */
s32 PAKInterface_OnDestroy(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed) {
    Cache_FreeMemory(g_pakInterfaceScreen);
    g_pakInterfaceScreen = 0;
    Tsmos_ActivateControllerState();
    Tsmos_SetMenuModelFlag(1);
    return 0;
}
#endif

#if VERSION_US
/* Checks the user number in the low half of playerEntryId against PAKINTERFACE_MAX_USERS through the assert hook; when that user's panel is in
   state 12, the high half of playerEntryId is 3 and selectionPressed is 4 or 5, sets the panel's two trailing words to 0 and 2. Returns 0 otherwise. */
s32 PAKInterface_OnButtonUp(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed) {
    s32 nUser = playerEntryId & 0xffff;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 1231, s_pakInterfaceScreenUserInRange)) {
            HaltAfterFailedAssert();
        }
    }
    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State == 12 && ((playerEntryId >> 16) & 0xffff) == 3) {
        switch (selectionPressed) {
        case 4:
        case 5:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB4C = 0;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB48 = 2;
            return;
        }
    }
    return 0;
}
#endif

#if VERSION_US
/* Checks the user number in the low half of playerEntryId through the assert hook; when that user's panel is in state 12 and selectionPressed is 1, looks up
   the user's object (asserting it exists), resets the panel's two trailing words to 0 and 2, steps the name cursor forward while
   it stays below 7, gives an empty name character the value 'A', makes the user's widget opaque and plays sound effect 3700. Returns 0. */
s32 PAKInterface_OnRight(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed) {
    s32 nUser = playerEntryId & 0xffff;
    struct WidgetLayout *pUserObject;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 1260, s_pakInterfaceScreenUserInRange)) {
            HaltAfterFailedAssert();
        }
    }
    switch (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State) {
    case 12:
        pUserObject = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, nUser);
        if (!pUserObject) {
            if (AssertFailed(s_pakInterfaceScreenSourceFile, 1266, s_pakInterfaceScreenObjectNotNull)) {
                HaltAfterFailedAssert();
            }
        }
        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB4C = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB48 = 2;
        if (selectionPressed != 1) {
            return 0;
        } else {
            if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor + 1 < 7) {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor = g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor + 1;
            }
            if (!g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor].ch) {
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor].ch = 65;
            }
            pUserObject->alpha = 255;
            Sound_PlayFXGlobal(3700);
        }
        break;
    }
    return 0;
}
#endif

#if VERSION_US
/* Checks the user number in the low half of playerEntryId through the assert hook; when that user's panel is in state 12 and selectionPressed is 1, looks up
   the user's object (asserting it exists), resets the panel's two trailing words to 0 and 2, steps the name cursor back while it
   is above 0, gives an empty name character the value 'A', makes the user's widget opaque and plays sound effect 3700. States 13,
   19 and 20 do nothing. Returns 0. */
s32 PAKInterface_OnLeft(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed) {
    s32 nUser = playerEntryId & 0xffff;
    struct WidgetLayout *pUserObject;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 1347, s_pakInterfaceScreenUserInRange)) {
            HaltAfterFailedAssert();
        }
    }
    switch (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State) {
    case 12:
        if (selectionPressed != 1) {
            return 0;
        }
        pUserObject = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, nUser);
        if (!pUserObject) {
            if (AssertFailed(s_pakInterfaceScreenSourceFile, 1357, s_pakInterfaceScreenObjectNotNull)) {
                HaltAfterFailedAssert();
            }
        }
        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB4C = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB48 = 2;
        if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor > 0) {
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor = g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor - 1;
        }
        if (!g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor].ch) {
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor].ch = 65;
        }
        pUserObject->alpha = 255;
        Sound_PlayFXGlobal(3700);
        break;
    case 13:
    case 19:
    case 20:
        break;
    }
    return 0;
}
#endif

#if VERSION_US
/* Cancel the current dialog, name entry or profile transfer. */
s32 PAKInterface_OnCancel(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed) {
    s32 user;
    SM_AcknowledgeMsg();
    if (g_pakInterfaceScreen->m_Mode == 7) {
        PAKInterface_ExitScreen(3);
        return 0;
    }
    user = playerEntryId & 0xffff;
    if (!(user >= 0 && user < 5)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 3406, s_pakInterfaceScreenUserInRange)) HaltAfterFailedAssert();
    }
    switch (PAK_PLAYER(user).m_State) {
    case 0:
        if (PAKInterface_GetNPlayersJoined() <= 0) {
            SM_AcknowledgeMsg();
            PAKInterface_ExitScreen(27);
            return 0;
        }
        break;
    case 12:
        SM_AcknowledgeMsg();
        PAK_PLAYER(user).m_Name[PAK_PLAYER(user).m_NameCursor].ch = 32;
        break;
    case 22:
        SM_AcknowledgeMsg();
        PAKInterface_RefreshMiddleNamesForPlayerName(-1);
        PAK_PLAYER(user).m_State = 13;
        PAKInterface_InitPlayerMode(user);
        break;
    case 27:
        SM_AcknowledgeMsg();
        PAKInterface_RefreshMiddleNamesForCopy(-1);
        PAK_PLAYER(user).m_State = 13;
        PAKInterface_InitPlayerMode(user);
        break;
    }
    return 0;
}
#endif

#if VERSION_US
/* Dispatch matching screen messages until the handler-table sentinel. */
s32 PAKInterfaceProc(PAKDialogMessage *a, s32 b, s32 c, s32 d, s32 e) {
    s32 i;
    for (i = 0; g_pakInterfaceHandlers[i].invoke; i++) {
        if (g_pakInterfaceHandlers[i].message == b) {
            if (g_pakInterfaceHandlers[i].control == a->control || g_pakInterfaceHandlers[i].control == 30000) {
                return g_pakInterfaceHandlers[i].invoke(a, b, c, d, e);
            }
        }
    }
    return 0;
}
#endif

#if VERSION_US
/* Select the initial screen mode after checking the original enum range. */
void PAKInterface_SetInitialScreenMode(s32 mode) {
    if (!(mode >= 0 && mode < 8)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 3542, s_pakInterfaceInitialModeRange)) HaltAfterFailedAssert();
    }
    g_pakInterfaceScreenMode = mode;
}
#endif
