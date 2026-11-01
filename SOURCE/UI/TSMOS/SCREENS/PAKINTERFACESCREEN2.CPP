#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#if VERSION_US
extern char s_pakInterfaceScreenSourceFile[];
extern char s_pakInterfaceScreenUserInRange[];
extern char s_pakInterfaceScreenFalse[];
extern void SM_AcknowledgeMsg(void);
extern s32 PAKInterface_GetNextPlayerToChooseName(void);
/* COMMENT */
s32 PAKInterface_OnButtonDebounce(s32 a, s32 b, s32 c, s32 d) {
    s32 nUser = c & 0xffff;
    s32 i;
    if (!(nUser >= 0 && nUser <= PAKINTERFACE_MAX_USERS)) {
        if (AssertFailed(s_pakInterfaceScreenSourceFile, 943, s_pakInterfaceScreenUserInRange)) {
            *(char *)0 = 0;
        }
    }
    if (((c >> 16) & 0xffff) == 3) {
        switch (g_pakInterfaceScreen->m_Mode) {
        case 5:
            break;
        case 6:
            switch (d) {
            case 10:
            if (PAK_PLAYER(nUser).m_State == 4) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_Panel = 2;
                PAK_PLAYER(nUser).m_State = 2;
                PAK_PLAYER(nUser).m_Step = 4;
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 4:
            switch (d) {
            case 11:
            case 13:
            if (PAK_PLAYER(nUser).m_State == 0) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_Panel = 2;
                PAK_PLAYER(nUser).m_State = 2;
                PAK_PLAYER(nUser).m_Step = 4;
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            case 10:
            if (PAK_PLAYER(nUser).m_State == 4) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_Panel = 2;
                PAK_PLAYER(nUser).m_State = 2;
                PAK_PLAYER(nUser).m_Step = 4;
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 0:
            switch (d) {
            case 11:
            case 13:
            if (PAK_PLAYER(nUser).m_State == 0) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_Panel = 2;
                PAK_PLAYER(nUser).m_State = 2;
                PAK_PLAYER(nUser).m_Step = 12;
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 3:
            switch (d) {
            case 11:
            case 13:
            if (PAK_PLAYER(nUser).m_State == 0) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_Panel = 2;
                PAK_PLAYER(nUser).m_State = 2;
                PAK_PLAYER(nUser).m_Step = 13;
                PAK_PLAYER(nUser).m_Mode = 5;
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 1:
            switch (d) {
            case 11:
            case 13:
            if (PAK_PLAYER(nUser).m_State == 0) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_State = 14;
                i = PAKInterface_GetNextPlayerToChooseName();
                if (i >= 0) {
                    PAK_PLAYER(nUser).m_Panel = 2;
                    PAK_PLAYER(nUser).m_State = 2;
                    PAK_PLAYER(nUser).m_Step = 13;
                    PAK_PLAYER(nUser).m_Mode = 6;
                }
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 2:
            switch (d) {
            case 11:
            case 13:
            if (PAK_PLAYER(nUser).m_State == 0) {
                SM_AcknowledgeMsg();
                PAK_PLAYER(nUser).m_State = 14;
                i = PAKInterface_GetNextPlayerToChooseName();
                if (i >= 0) {
                    PAK_PLAYER(nUser).m_Panel = 2;
                    PAK_PLAYER(nUser).m_State = 2;
                    PAK_PLAYER(nUser).m_Step = 13;
                    PAK_PLAYER(nUser).m_Mode = 3;
                }
                PAKInterface_InitPlayerMode(nUser);
            }
                break;
            }
            break;
        case 7:
            break;
        default:
            if (AssertFailed(s_pakInterfaceScreenSourceFile, 1217, s_pakInterfaceScreenFalse)) {
                *(char *)0 = 0;
            }
            break;
        }
    }
    return 0;
}
#endif
