#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Copies the user's four middle records into the save block and stamps its marker and checksum. */
void PAKInterface_PrepareSaveBlockForSave(s32 anUser) {
    u8 *pSource;
    PAKSaveBlock *pBlock;
    s32 nSize;
    PAK_ASSERT(5221, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    pSource = (u8 *)&g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[0];
    pBlock = &g_pakInterfaceScreen->m_SaveBlock;
    nSize = PAK_SAVE_DATA_SIZE;
    memcpy(pBlock, pSource, nSize);
    g_pakInterfaceScreen->m_SaveBlock.m_Marker = g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Marker;
    g_pakInterfaceScreen->m_SaveBlock.m_Checksum = Chksum(pBlock, nSize, PAK_CHECKSUM_SEED);
}
#endif
