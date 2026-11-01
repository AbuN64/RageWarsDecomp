#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#include <ultra64.h>
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
