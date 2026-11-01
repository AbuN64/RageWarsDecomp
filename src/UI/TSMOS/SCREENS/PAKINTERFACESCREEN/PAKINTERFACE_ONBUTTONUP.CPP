#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#if VERSION_US
extern char s_pakInterfaceScreenSourceFile[];
extern char s_pakInterfaceScreenUserInRange[];
extern s32 AssertFailed(char *file, s32 line, char *expr);
/* Checks the user number in the low half of c against PAKINTERFACE_MAX_USERS through the assert hook; when that user's panel is in
   state 12, the high half of c is 3 and d is 4 or 5, sets the panel's two trailing words to 0 and 2. Returns 0 otherwise. */
s32 PAKInterface_OnButtonUp(s32 a, s32 b, s32 c, s32 d) {
    s32 nUser = c & 0xffff;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 1231, s_pakInterfaceScreenUserInRange)) {
            *(char *)0 = 0;
        }
    }
    if (g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_State == 12 && ((c >> 16) & 0xffff) == 3) {
        switch (d) {
        case 4:
        case 5:
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB4C = 0;
            g_pakInterfaceScreen->m_PAKInterfacePlayer[nUser].m_FieldB48 = 2;
            return;
        }
    }
    return 0;
}
#endif
