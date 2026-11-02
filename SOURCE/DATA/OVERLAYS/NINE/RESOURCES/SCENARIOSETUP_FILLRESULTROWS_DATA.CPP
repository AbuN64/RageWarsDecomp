#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "TYPES.H"

extern char Frontend_ActivateResultsAction[];
extern char Frontend_ConsumeResultsEvent[];
extern char Frontend_DestroyMatchResults[];
extern char Frontend_HandleResultsConfirmation[];
extern char Frontend_ScrollResultsBackward[];
extern char Frontend_ScrollResultsForward[];
extern char Frontend_UpdateMatchResultsTransition[];
extern char ScenarioSetup_OpenResultsScreen[];
extern char g_Frontend_ActivateResultsActionPackedAddress24[];
extern char g_Frontend_ConsumeResultsEventPackedAddress24[];
extern char g_Frontend_DestroyMatchResultsPackedAddress24[];
extern char g_Frontend_HandleResultsConfirmationPackedAddress24[];
extern char g_Frontend_ScrollResultsBackwardPackedAddress24[];
extern char g_Frontend_ScrollResultsForwardPackedAddress24[];
extern char g_Frontend_UpdateMatchResultsTransitionPackedAddress24[];
extern char g_ScenarioSetup_OpenResultsScreenPackedAddress24[];

#include "include_asm.h"

/* 800E53C0.CPP */
/* ROM-grounded data: rodata/writable/800E53C0 */
#if defined(VERSION_DE)
struct {
    void * g_matchResultBadgeScreen;
} g_ScenariosetupFillresultrowsWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_ScenariosetupFillresultrowsWords1SizeCheck[(sizeof(g_ScenariosetupFillresultrowsWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    void * g_matchResultBadgeScreen;
} g_ScenariosetupFillresultrowsWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_ScenariosetupFillresultrowsWords1SizeCheck[(sizeof(g_ScenariosetupFillresultrowsWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * g_matchResultBadgeScreen;
} g_ScenariosetupFillresultrowsWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_ScenariosetupFillresultrowsWords1SizeCheck[(sizeof(g_ScenariosetupFillresultrowsWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * g_matchResultBadgeScreen;
} g_ScenariosetupFillresultrowsWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_ScenariosetupFillresultrowsWords1SizeCheck[(sizeof(g_ScenariosetupFillresultrowsWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    void * g_matchResultBadgeScreen;
} g_ScenariosetupFillresultrowsWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_ScenariosetupFillresultrowsWords1SizeCheck[(sizeof(g_ScenariosetupFillresultrowsWords1) == 4) ? 1 : -1];
#endif

/* 800E53C4.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
#if defined(VERSION_DE)
ResidentEventHandlerEntry D_src_6d0863ff[9] = {
    { 3592, 17, (ResidentEventHandler)(void *)((char *)&Frontend_HandleResultsConfirmation - 0x80000000U) }, { 3590, 17, (ResidentEventHandler)(void *)((char *)&ScenarioSetup_OpenResultsScreen - 0x80000000U) }, { 3587, 17, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyMatchResults - 0x80000000U) }, { 2, 17, (ResidentEventHandler)(void *)((char *)&Frontend_ConsumeResultsEvent - 0x80000000U) }, { 1, 17, (ResidentEventHandler)(void *)((char *)&Frontend_ActivateResultsAction - 0x80000000U) }, { 3594, 17, (ResidentEventHandler)(void *)((char *)&Frontend_UpdateMatchResultsTransition - 0x80000000U) }, { 5, 17, (ResidentEventHandler)(void *)((char *)&Frontend_ScrollResultsBackward - 0x80000000U) }, { 6, 17, (ResidentEventHandler)(void *)((char *)&Frontend_ScrollResultsForward - 0x80000000U) },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#if defined(VERSION_EU)
#if defined(VERSION_EU)
ResidentEventHandlerEntry D_src_6d0863ff[9] = {
    { 3592, 17, (ResidentEventHandler)(void *)&g_Frontend_HandleResultsConfirmationPackedAddress24 }, { 3590, 17, (ResidentEventHandler)(void *)&g_ScenarioSetup_OpenResultsScreenPackedAddress24 }, { 3587, 17, (ResidentEventHandler)(void *)&g_Frontend_DestroyMatchResultsPackedAddress24 }, { 2, 17, (ResidentEventHandler)(void *)&g_Frontend_ConsumeResultsEventPackedAddress24 }, { 1, 17, (ResidentEventHandler)(void *)&g_Frontend_ActivateResultsActionPackedAddress24 }, { 3594, 17, (ResidentEventHandler)(void *)&g_Frontend_UpdateMatchResultsTransitionPackedAddress24 }, { 5, 17, (ResidentEventHandler)(void *)&g_Frontend_ScrollResultsBackwardPackedAddress24 }, { 6, 17, (ResidentEventHandler)(void *)&g_Frontend_ScrollResultsForwardPackedAddress24 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
ResidentEventHandlerEntry D_src_6d0863ff[9] = {
    { 3592, 17, (ResidentEventHandler)(void *)((char *)&Frontend_HandleResultsConfirmation - 0x80000000U) }, { 3590, 17, (ResidentEventHandler)(void *)((char *)&ScenarioSetup_OpenResultsScreen - 0x80000000U) }, { 3587, 17, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyMatchResults - 0x80000000U) }, { 2, 17, (ResidentEventHandler)(void *)((char *)&Frontend_ConsumeResultsEvent - 0x80000000U) }, { 1, 17, (ResidentEventHandler)(void *)((char *)&Frontend_ActivateResultsAction - 0x80000000U) }, { 3594, 17, (ResidentEventHandler)(void *)((char *)&Frontend_UpdateMatchResultsTransition - 0x80000000U) }, { 5, 17, (ResidentEventHandler)(void *)((char *)&Frontend_ScrollResultsBackward - 0x80000000U) }, { 6, 17, (ResidentEventHandler)(void *)((char *)&Frontend_ScrollResultsForward - 0x80000000U) },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
extern char g_ScenarioSetup_OpenResultsScreenPackedAddress242[];
extern char g_Frontend_DestroyMatchResultsPackedAddress242[];
extern char g_Frontend_UpdateMatchResultsTransitionPackedAddress242[];
extern char g_Frontend_HandleResultsConfirmationPackedAddress242[];
extern char g_Frontend_ActivateResultsActionPackedAddress242[];
extern char g_Frontend_ConsumeResultsEventPackedAddress242[];
extern char g_Frontend_ScrollResultsBackwardPackedAddress242[];
extern char g_Frontend_ScrollResultsForwardPackedAddress242[];
#if defined(VERSION_US)
ResidentEventHandlerEntry g_ScenariosetupFillresultrowsPointerWords1[9] = {
    { 3592, 17, (ResidentEventHandler)(void *)&g_Frontend_HandleResultsConfirmationPackedAddress242 }, { 3590, 17, (ResidentEventHandler)(void *)&g_ScenarioSetup_OpenResultsScreenPackedAddress242 }, { 3587, 17, (ResidentEventHandler)(void *)&g_Frontend_DestroyMatchResultsPackedAddress242 }, { 2, 17, (ResidentEventHandler)(void *)&g_Frontend_ConsumeResultsEventPackedAddress242 }, { 1, 17, (ResidentEventHandler)(void *)&g_Frontend_ActivateResultsActionPackedAddress242 }, { 3594, 17, (ResidentEventHandler)(void *)&g_Frontend_UpdateMatchResultsTransitionPackedAddress242 }, { 5, 17, (ResidentEventHandler)(void *)&g_Frontend_ScrollResultsBackwardPackedAddress242 }, { 6, 17, (ResidentEventHandler)(void *)&g_Frontend_ScrollResultsForwardPackedAddress242 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_ScenariosetupFillresultrowsPointerWords1[9] = {
    { 3592, 17, (ResidentEventHandler)(void *)&g_Frontend_HandleResultsConfirmationPackedAddress242 }, { 3590, 17, (ResidentEventHandler)(void *)&g_ScenarioSetup_OpenResultsScreenPackedAddress242 }, { 3587, 17, (ResidentEventHandler)(void *)&g_Frontend_DestroyMatchResultsPackedAddress242 }, { 2, 17, (ResidentEventHandler)(void *)&g_Frontend_ConsumeResultsEventPackedAddress242 }, { 1, 17, (ResidentEventHandler)(void *)&g_Frontend_ActivateResultsActionPackedAddress242 }, { 3594, 17, (ResidentEventHandler)(void *)&g_Frontend_UpdateMatchResultsTransitionPackedAddress242 }, { 5, 17, (ResidentEventHandler)(void *)&g_Frontend_ScrollResultsBackwardPackedAddress242 }, { 6, 17, (ResidentEventHandler)(void *)&g_Frontend_ScrollResultsForwardPackedAddress242 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
