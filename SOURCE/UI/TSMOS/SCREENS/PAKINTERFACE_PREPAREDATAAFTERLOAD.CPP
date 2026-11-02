#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
/* Copies the loaded save block back into the user's four middle records and takes its marker. */
void PAKInterface_PrepareDataAfterLoad(s32 anUser) {
    PAKSaveBlock *pBlock;
    u8 *pDestination;
    s32 nSize;
    PAK_ASSERT(5242, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    pBlock = &g_pakInterfaceScreen->m_SaveBlock;
    pDestination = (u8 *)&g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_MiddleRecords[0];
    nSize = PAK_SAVE_DATA_SIZE;
    memcpy(pDestination, pBlock, nSize);
    g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_Marker = g_pakInterfaceScreen->m_SaveBlock.m_Marker;
}
#endif
