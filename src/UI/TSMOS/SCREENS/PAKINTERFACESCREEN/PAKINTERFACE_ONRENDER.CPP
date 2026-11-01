#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "COMMON/SHARED_MENUREPLY.H"
#if VERSION_US
extern char s_pakInterfaceScreenSourceFile[];
extern char s_pakInterfaceScreenFalse[];
extern void SM_AcknowledgeMsg(void);
extern void PAK_UpdateSingle(s32 anUser);
extern void PAKInterface_CheckPAK(s32 anUser);
extern s32 CWipeScreen_GetState(void *apWipe);
extern void CWipeScreen_DrawWipe(void *apWipe);
extern void CWipeScreen_UpdateWipe(void *apWipe);
extern void MultiTallyScreen_ContinueGame(void);
extern void MultiTallyScreen_CoOpContinueGame(void);
extern void ScenarioTallyScreen_ContinueGame(void);
/* COMMENT */
s32 PAKInterface_OnRender(s32 a, s32 b, s32 c, s32 d) {
    s32 i;
    if (c == 1) {
        if (g_pakInterfaceScreen->m_ExitPhase == 3) {
            for (i = 0; i < 4; i++) {
                if (PAK_PLAYER(i).m_Panel > 0) {
                    PAK_PLAYER(i).m_Panel = PAK_PLAYER(i).m_Panel - 1;
                    if (PAK_PLAYER(i).m_Panel == 0) {
                        PAK_PLAYER(i).m_Panel = -1;
                        TSMOS_InputDisable();
                        PAK_UpdateSingle(i);
                        PAKInterface_CheckPAK(i);
                        Tsmos_ActivateControllerState();
                    }
                }
            }
        }
        if (CWipeScreen_GetState(&g_pakInterfaceScreen->m_Wipe) == 1) {
            CWipeScreen_DrawWipe(&g_pakInterfaceScreen->m_Wipe);
            CWipeScreen_UpdateWipe(&g_pakInterfaceScreen->m_Wipe);
            if (CWipeScreen_GetState(&g_pakInterfaceScreen->m_Wipe) == 2) {
                if (g_pakInterfaceScreen->m_Mode == 5) {
                    SM_AcknowledgeMsg();
                    switch (g_engineApp.m_FrontendMode) {
                    case 0:
                        MultiTallyScreen_ContinueGame();
                        break;
                    case 2:
                        MultiTallyScreen_CoOpContinueGame();
                        break;
                    case 1:
                    case 3:
                    case 4:
                        ScenarioTallyScreen_ContinueGame();
                        break;
                    default:
                        if (AssertFailed(s_pakInterfaceScreenSourceFile, 826, s_pakInterfaceScreenFalse)) {
                            *(char *)0 = 0;
                        }
                        break;
                    }
                }
                return 0;
            }
        }
    }
    return 0;
}
#endif
