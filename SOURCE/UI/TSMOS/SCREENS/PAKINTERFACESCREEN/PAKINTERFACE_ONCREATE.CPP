#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "COMMON/SHARED_MENUREPLY.H"
#if VERSION_US
extern char s_pakInterfaceScreenSourceFile[];
extern char s_pakInterfaceScreenIsNull[];
extern char s_pakInterfaceScreenNotNull[];
extern char s_pakInterfaceScreenFalse[];
extern s32 g_pakInterfaceScreenMode;
extern s32 gnAccessingPak_CurrentMode;
extern s32 gnAccessingPak_CurrentPAK;
extern void *alloc_debug(s32 anSize, char *apFile, s32 anLine);
extern void CWipeScreen_InitWipe(void *apWipe, s32 anA, s32 anB, s32 anC, s32 anD);
extern void *SMMU_MakeScreenMultiUser(s32 anScreen, s32 anUsers);
extern void SMMU_SetActiveControl(void *apList, s32 anUser, s16 anControl);
extern void *SMFL_MakeFlicker(s32 anId, s32 anAlpha);
extern void SM_DLSetVisible(PAKUserWidget *apWidget, s32 anVisible);
extern void SetMemoryCardActive(s32 anUser);
extern void *memset(void *apDst, int anValue, u32 anSize);
extern void PAK_UpdateSingle(s32 anUser);
extern s32 PAK_CheckStatus(s32 anUser);
extern void Video_SetNextMode(s32 anMode);
extern void Tsmos_SetModeOneFlag(s32 anFlag);
extern void Sound_PlayFXGlobal(s32 anSound);
extern void k_PortalAfterIsMiddleListEmpty(s32 anValue);
/* COMMENT */
s32 PAKInterface_OnCreate(s32 a, s32 b, s32 c, s32 d) {
    s32 nRem;
    s32 i;
    s32 j;
    PAKUserWidget *pObj;
    s32 nStatus;
    if (!(g_pakInterfaceScreen == 0)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 327, s_pakInterfaceScreenIsNull)) {
            *(char *)0 = 0;
        }
    }
    g_pakInterfaceScreen = alloc_debug(13428, s_pakInterfaceScreenSourceFile, 329);
    if (!g_pakInterfaceScreen) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 330, s_pakInterfaceScreenNotNull)) {
            *(char *)0 = 0;
        }
    }
    g_pakInterfaceScreen->m_pDisplayList = a;
    CWipeScreen_InitWipe(g_pakInterfaceScreen->m_Wipe, 103, 0, 0, 0);
    g_pakInterfaceScreen->m_pUserList = SMMU_MakeScreenMultiUser(a, 4);
    SMMU_SetActiveControl(a, 0, 643);
    SMMU_SetActiveControl(a, 1, 643);
    SMMU_SetActiveControl(a, 2, 643);
    SMMU_SetActiveControl(a, 3, 643);
    for (i = 0; i < 4; i++) {
        g_pakInterfaceScreen->m_UserBusy[i] = 0;
    }
    g_pakInterfaceScreen->m_ExitPhase = 1;
    g_pakInterfaceScreen->m_ExitStep = 4;
    g_pakInterfaceScreen->m_pBarA = SM_DLFindObjectByID(a, 761);
    g_pakInterfaceScreen->m_pBarA->m_X = g_pakInterfaceScreen->m_pBarA->m_X - g_pakInterfaceScreen->m_pBarA->m_Width;
    g_pakInterfaceScreen->m_BarStepA.m_Word = (s16)(g_pakInterfaceScreen->m_pBarA->m_Width / 4);
    nRem = g_pakInterfaceScreen->m_pBarA->m_Width - g_pakInterfaceScreen->m_BarStepA.m_Word * 4;
    g_pakInterfaceScreen->m_pBarA->m_X = g_pakInterfaceScreen->m_pBarA->m_X + nRem;
    g_pakInterfaceScreen->m_pBarB = SM_DLFindObjectByID(a, 672);
    g_pakInterfaceScreen->m_pBarB->m_X = g_pakInterfaceScreen->m_pBarB->m_X + g_pakInterfaceScreen->m_pBarB->m_Width;
    g_pakInterfaceScreen->m_BarStepB.m_Word = (s16)(g_pakInterfaceScreen->m_pBarB->m_Width / 4);
    nRem = g_pakInterfaceScreen->m_pBarB->m_Width - g_pakInterfaceScreen->m_BarStepB.m_Word * 4;
    g_pakInterfaceScreen->m_pBarB->m_X = g_pakInterfaceScreen->m_pBarB->m_X - nRem;
    pObj = SM_DLFindObjectByID(a, 644);
    pObj->m_Alpha = 110;
    g_pakInterfaceScreen->m_pFlicker = SMFL_MakeFlicker(645, 255);
    g_pakInterfaceScreen->m_pFlickerWidget = SM_DLFindObjectByID(a, 645);
    SM_DLSetVisible(g_pakInterfaceScreen->m_pFlickerWidget, 0);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[0].m_pObject = SM_DLFindObjectByID(a, 762);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[1].m_pObject = SM_DLFindObjectByID(a, 673);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[2].m_pObject = SM_DLFindObjectByID(a, 763);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[3].m_pObject = SM_DLFindObjectByID(a, 760);
    g_pakInterfaceScreen->m_Mode = g_pakInterfaceScreenMode;
    for (i = 0; i < 4; i++) {
        g_pakInterfaceScreen->m_Slot[i].m_User = -1;
        g_pakInterfaceScreen->m_Slot[i].m_Record = 0;
        g_pakInterfaceScreen->m_Slot[i].m_State = 2;
    }
    switch (g_pakInterfaceScreen->m_Mode) {
    case 5:
        pObj = SM_DLFindObjectByID(a, 657);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    case 6:
        pObj = SM_DLFindObjectByID(a, 660);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    case 4:
        pObj = SM_DLFindObjectByID(a, 646);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    case 0:
        pObj = SM_DLFindObjectByID(a, 671);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    case 3:
        pObj = SM_DLFindObjectByID(a, 659);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    case 7:
        break;
    case 1:
        pObj = SM_DLFindObjectByID(a, 647);
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
        pObj = SM_DLFindObjectByID(a, 661);
        SM_DLSetVisible(pObj, 1);
        pObj->m_Alpha = 255;
        break;
    default:
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 555, s_pakInterfaceScreenFalse)) {
            *(char *)0 = 0;
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
    Tsmos_SetModeOneFlag(0);
    Sound_PlayFXGlobal(3704);
    return 0;
}
#endif
