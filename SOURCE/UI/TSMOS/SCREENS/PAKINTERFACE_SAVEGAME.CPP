#include "include_asm.h"
#include "UI/TSMOS/PAKINTERFACE.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
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
