#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#if VERSION_US
extern char s_pakInterfaceScreenSourceFile[];
extern char s_pakInterfaceScreenUserInRange[];
extern char s_pakInterfaceScreenFalse[];
extern char s_pakInterfaceScreenObjectNotNull[];
extern char s_pakInterfaceScreenNameIndexRange[];
extern void SM_AcknowledgeMsg(void);
extern s32 SMMU_GetActiveControlID(void *apUserList, s32 anUser);
extern void SMMU_SetActiveControl(void *apUserList, s32 anUser, s32 anControl);
extern s32 x_atoi(char *apString);
extern s32 x_stricmp(char *apA, char *apB);
extern void PAK_UpdateSingle(s32 anUser);
extern s32 PAK_Repair(s32 anUser);
extern void PAKInterface_ResetControlBackToCopyPlayer(s32 anUser);
extern s32 PAKInterface_SaveGame(s32 anUser);
extern s32 PAKInterface_FindEmptyPlayerDataSlot(s32 anUser);
extern void PAKInterface_AddPlayerToSpecificMiddleSlot(s32 anUser, s32 anRecord, s32 anFlag);
extern void PAKInterface_CopySpecificMiddlePlayerToGlobal(s32 anUser);
extern void PAKInterface_ExitScreen(s32 anUser);
extern void PAKInterface_CheckPAK(s32 anUser);
extern s32 PAKInterface_GetGlobalPlayerByMarker(s32 anMarker, s32 anSlot);
extern s32 PAKInterface_GetNextPlayerToChooseName(void);
extern void PAKInterface_UpdatePAK(s32 anUser);
extern void PAKInterface_RefreshMiddleNamesForPlayerName(s32 anUser);
extern void CPersistentPlayerData_MakeQuickPlayer(s32 anUser);
typedef union PAKAcceptValue {
    s32 m_Value;
    void *m_Pointer;
    PAKPlayerSetup *m_Setup;
} PAKAcceptValue;

/* Handles the selected memory-pak action for the active user and screen mode. */
s32 PAKInterface_OnAccept(s32 a, s32 b, s32 c, s32 d) {
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
    nUser = c & 0xffff;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 1923, s_pakInterfaceScreenUserInRange)) {
            *(char *)0 = 0;
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
                    *(char *)0 = 0;
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
                    *(char *)0 = 0;
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
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_Field189 = nTemp.m_Setup->m_Field123;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_Field18A = nTemp.m_Setup->m_Field125;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_Field18B = nTemp.m_Setup->m_Field121;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_Field18C = nTemp.m_Setup->m_Field122;
                g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_MiddleRecords[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB3C].m_Field18D = nTemp.m_Setup->m_Field130;
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
                        *(char *)0 = 0;
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
                    *(char *)0 = 0;
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
                    *(char *)0 = 0;
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
                    *(char *)0 = 0;
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
                *(char *)0 = 0;
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
                    *(char *)0 = 0;
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
