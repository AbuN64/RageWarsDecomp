#include "include_asm.h"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "TYPES.H"
#if VERSION_US
extern f32 cosf(f32 x);
extern char s_pakAssertTextString[];
extern void PAKInterface_UpdateStartGroup(s32 anUser);
extern void PAKInterface_DecPlayerNameCharacter(s32 anUser);
extern void PAKInterface_IncPlayerNameCharacter(s32 anUser);
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
            PAK_ASSERT(4206, *(u8 *)pItem->m_pText != 0, s_pakAssertTextString);
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
