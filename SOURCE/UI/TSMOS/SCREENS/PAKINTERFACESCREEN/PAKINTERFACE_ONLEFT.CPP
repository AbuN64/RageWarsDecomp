#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "COMMON/WIDGETRECAT1A.H"
#if VERSION_US
extern char s_pakInterfaceScreenSourceFile[];
extern char s_pakInterfaceScreenUserInRange[];
extern char s_pakInterfaceScreenObjectNotNull[];
extern void Sound_PlayFXGlobal(s32 anSound);
/* Checks the user number in the low half of c through the assert hook; when that user's panel is in state 12 and d is 1, looks up
   the user's object (asserting it exists), resets the panel's two trailing words to 0 and 2, steps the name cursor back while it
   is above 0, gives an empty name character the value 'A', makes the user's widget opaque and plays sound effect 3700. States 13,
   19 and 20 do nothing. Returns 0. */
s32 PAKInterface_OnLeft(s32 a, s32 b, s32 c, s32 d) {
    s32 nUser = c & 0xffff;
    struct WidgetLayout *pUserObject;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 1347, s_pakInterfaceScreenUserInRange)) {
            *(char *)0 = 0;
        }
    }
    switch (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State) {
    case 12:
        if (d != 1) {
            return 0;
        }
        pUserObject = PAKInterface_GetUserObject(g_pakInterfaceScreen->m_pUserList, nUser);
        if (!pUserObject) {
            if (AssertFailed(s_pakInterfaceScreenSourceFile, 1357, s_pakInterfaceScreenObjectNotNull)) {
                *(char *)0 = 0;
            }
        }
        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB4C = 0;
        g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB48 = 2;
        if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor > 0) {
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor = g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor - 1;
        }
        if (!g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor].ch) {
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_Name[g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_NameCursor].ch = 65;
        }
        pUserObject->alpha = 255;
        Sound_PlayFXGlobal(3700);
        break;
    case 13:
    case 19:
    case 20:
        break;
    }
    return 0;
}
#endif
