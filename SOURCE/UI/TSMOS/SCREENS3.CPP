#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
extern f32 cosf(f32 x);
/* Pulses the alpha of the two start-button widgets of one user with the screen clock. */
void PAKInterface_UpdateStartGroup(s32 anUser) {
    PAKUserWidget *pObject;
    u8 nAlpha;
    PAK_ASSERT(4278, anUser >= 0 && anUser < 4, s_pakAssertUserRange);
    nAlpha = (u8)(cosf((f32)anUser + (f32)g_pakInterfaceScreen->m_UserBusy[anUser] / 300.0f) * 100.0f + 150.0f);
    pObject = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pObject, 704);
    pObject->m_Alpha = nAlpha;
    pObject = SM_DLFindObjectByID(g_pakInterfaceScreen->m_PAKInterfacePlayer[anUser].m_pObject, 705);
    pObject->m_Alpha = nAlpha;
}
#endif
