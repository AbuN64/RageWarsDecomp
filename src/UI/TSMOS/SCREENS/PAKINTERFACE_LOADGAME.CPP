#include "include_asm.h"
#include "UI/TSMOS/PAKINTERFACE.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
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
