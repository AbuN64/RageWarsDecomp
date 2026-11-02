#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#include <ultra64.h>
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
    PAK_ASSERT(5055, PAK_PLAYER(anUser).m_ListRows[0] != NULL, s_pakAssertRow0);
    PAK_PLAYER(anUser).m_ListRows[1] = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 730);
    PAK_ASSERT(5058, PAK_PLAYER(anUser).m_ListRows[1] != NULL, s_pakAssertRow1);
    PAK_PLAYER(anUser).m_ListRows[2] = SM_DLFindObjectByID(PAK_PLAYER(anUser).m_pWidget, 731);
    PAK_ASSERT(5061, PAK_PLAYER(anUser).m_ListRows[2] != NULL, s_pakAssertRow2);
    PAKInterface_ScrollManagementList(anUser, 1);
}
#endif
