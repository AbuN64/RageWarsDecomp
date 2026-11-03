#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#if VERSION_US
extern char s_pakInterfaceScreenSourceFile[];
extern char s_pakInterfaceScreenUserInRange[];
extern void SM_AcknowledgeMsg(void);
extern s32 PAKInterface_GetNPlayersJoined(void);
extern void PAKInterface_ExitScreen(s32 mode);
extern void PAKInterface_RefreshMiddleNamesForPlayerName(s32 user);
extern void PAKInterface_RefreshMiddleNamesForCopy(s32 user);
extern void PAKInterface_InitPlayerMode(s32 user);
/* Cancel the current dialog, name entry or profile transfer. */
s32 PAKInterface_OnCancel(s32 a, s32 b, s32 c, s32 d) {
    s32 user;
    SM_AcknowledgeMsg();
    if (g_pakInterfaceScreen->m_Mode == 7) {
        PAKInterface_ExitScreen(3);
        return 0;
    }
    user = c & 0xffff;
    if (!(user >= 0 && user < 5)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 3406, s_pakInterfaceScreenUserInRange)) *(char *)0 = 0;
    }
    switch (PAK_PLAYER(user).m_State) {
    case 0:
        if (PAKInterface_GetNPlayersJoined() <= 0) {
            SM_AcknowledgeMsg();
            PAKInterface_ExitScreen(27);
            return 0;
        }
        break;
    case 12:
        SM_AcknowledgeMsg();
        PAK_PLAYER(user).m_Name[PAK_PLAYER(user).m_NameCursor].ch = 32;
        break;
    case 22:
        SM_AcknowledgeMsg();
        PAKInterface_RefreshMiddleNamesForPlayerName(-1);
        PAK_PLAYER(user).m_State = 13;
        PAKInterface_InitPlayerMode(user);
        break;
    case 27:
        SM_AcknowledgeMsg();
        PAKInterface_RefreshMiddleNamesForCopy(-1);
        PAK_PLAYER(user).m_State = 13;
        PAKInterface_InitPlayerMode(user);
        break;
    }
    return 0;
}
#endif
