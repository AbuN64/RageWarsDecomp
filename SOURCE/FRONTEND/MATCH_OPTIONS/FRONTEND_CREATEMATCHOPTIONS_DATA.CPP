#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"
extern char Frontend_ActivateMatchOptionAction[];
extern char Frontend_CreateMatchOptions[];
extern char Frontend_DestroyMatchOptions[];
extern char Frontend_ExitMatchOptions[];
extern char Frontend_RefreshMatchSlotsOnZeroEvent[];
extern char Frontend_RefreshMatchSlotsOnZeroEventAlt[];
extern char Frontend_ResetMatchOptionOnEvent[];
extern char Frontend_ReturnMatchOptionsEventZero[];
extern char g_Frontend_ActivateMatchOptionActionPackedAddress24[];
extern char g_Frontend_CreateMatchOptionsPackedAddress24[];
extern char g_Frontend_ExitMatchOptionsPackedAddress24[];
extern char g_Frontend_MatchOptionsEvent0E03ScenarioSetupEvent0E08HandlerPackedAddress24[];
extern char g_Frontend_RefreshMatchSlotsOnZeroEventAltPackedAddress24[];
extern char g_Frontend_RefreshMatchSlotsOnZeroEventPackedAddress24[];
extern char g_Frontend_ResetMatchOptionOnEventPackedAddress24[];
extern char g_Frontend_ReturnMatchOptionsEventZeroPackedAddress24[];
#include "include_asm.h"
#if defined(VERSION_DE)
/* 800E4EBC_2.CPP */
/* ROM-grounded data: rodata/writable/800E4EF0 */
struct {
    void * g_matchOptionsScreen;
} g_FrontendCreatematchoptionsWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendCreatematchoptionsWords1SizeCheck[(sizeof(g_FrontendCreatematchoptionsWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    void * g_matchOptionsScreen;
} g_FrontendCreatematchoptionsWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendCreatematchoptionsWords1SizeCheck[(sizeof(g_FrontendCreatematchoptionsWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * g_matchOptionsScreen;
} g_FrontendCreatematchoptionsWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendCreatematchoptionsWords1SizeCheck[(sizeof(g_FrontendCreatematchoptionsWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * g_matchOptionsScreen;
} g_FrontendCreatematchoptionsWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendCreatematchoptionsWords1SizeCheck[(sizeof(g_FrontendCreatematchoptionsWords1) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    void * g_matchOptionsScreen;
} g_FrontendCreatematchoptionsWords1 __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendCreatematchoptionsWords1SizeCheck[(sizeof(g_FrontendCreatematchoptionsWords1) == 4) ? 1 : -1];
#endif
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
#if defined(VERSION_DE)
/* 800E4EF4.CPP */
struct {
    ResidentEventHandlerEntry eventHandlers0[7];
    u8 alignmentFill84[8];
} D_src_8e351802 __attribute__((aligned(4))) = {
    { { 3590, 21, (ResidentEventHandler)(void *)((char *)&Frontend_CreateMatchOptions - 0x80000000U) }, { 3587, 21, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyMatchOptions - 0x80000000U) }, { 3594, 21, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnMatchOptionsEventZero - 0x80000000U) }, { 2, 21, (ResidentEventHandler)(void *)((char *)&Frontend_ExitMatchOptions - 0x80000000U) }, { 1, 21, (ResidentEventHandler)(void *)((char *)&Frontend_ActivateMatchOptionAction - 0x80000000U) }, { 10, 21, (ResidentEventHandler)(void *)((char *)&Frontend_ResetMatchOptionOnEvent - 0x80000000U) }, { 8, 874, (ResidentEventHandler)(void *)((char *)&Frontend_RefreshMatchSlotsOnZeroEventAlt - 0x80000000U) } },
    { 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x3, 0x6a }
};
typedef char D_src_8e351802SizeCheck[(sizeof(D_src_8e351802) == 92) ? 1 : -1];
#endif
#endif
#if defined(VERSION_EU)
#if defined(VERSION_EU)
ResidentEventHandlerEntry D_src_8e351802[9] = {
    { 3590, 21, (ResidentEventHandler)(void *)&g_Frontend_CreateMatchOptionsPackedAddress24 }, { 3587, 21, (ResidentEventHandler)(void *)&g_Frontend_MatchOptionsEvent0E03ScenarioSetupEvent0E08HandlerPackedAddress24 }, { 3594, 21, (ResidentEventHandler)(void *)&g_Frontend_ReturnMatchOptionsEventZeroPackedAddress24 }, { 2, 21, (ResidentEventHandler)(void *)&g_Frontend_ExitMatchOptionsPackedAddress24 }, { 1, 21, (ResidentEventHandler)(void *)&g_Frontend_ActivateMatchOptionActionPackedAddress24 }, { 10, 21, (ResidentEventHandler)(void *)&g_Frontend_ResetMatchOptionOnEventPackedAddress24 }, { 8, 878, (ResidentEventHandler)(void *)&g_Frontend_RefreshMatchSlotsOnZeroEventAltPackedAddress24 }, { 7, 878, (ResidentEventHandler)(void *)&g_Frontend_RefreshMatchSlotsOnZeroEventPackedAddress24 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
ResidentEventHandlerEntry D_src_8e351802[9] = {
    { 3590, 21, (ResidentEventHandler)(void *)((char *)&Frontend_CreateMatchOptions - 0x80000000U) }, { 3587, 21, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyMatchOptions - 0x80000000U) }, { 3594, 21, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnMatchOptionsEventZero - 0x80000000U) }, { 2, 21, (ResidentEventHandler)(void *)((char *)&Frontend_ExitMatchOptions - 0x80000000U) }, { 1, 21, (ResidentEventHandler)(void *)((char *)&Frontend_ActivateMatchOptionAction - 0x80000000U) }, { 10, 21, (ResidentEventHandler)(void *)((char *)&Frontend_ResetMatchOptionOnEvent - 0x80000000U) }, { 8, 882, (ResidentEventHandler)(void *)((char *)&Frontend_RefreshMatchSlotsOnZeroEventAlt - 0x80000000U) }, { 7, 882, (ResidentEventHandler)(void *)((char *)&Frontend_RefreshMatchSlotsOnZeroEvent - 0x80000000U) },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#endif
#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
extern char g_Frontend_CreateMatchOptionsPackedAddress242[];
extern char g_Frontend_DestroyMatchOptionsPackedAddress24[];
extern char g_Frontend_ReturnMatchOptionsEventZeroPackedAddress242[];
extern char g_Frontend_ResetMatchOptionOnEventPackedAddress242[];
extern char g_Frontend_ActivateMatchOptionActionPackedAddress242[];
extern char g_Frontend_ExitMatchOptionsPackedAddress242[];
extern char g_Frontend_RefreshMatchSlotsOnZeroEventPackedAddress242[];
extern char g_Frontend_RefreshMatchSlotsOnZeroEventAltPackedAddress242[];
#if defined(VERSION_US)
ResidentEventHandlerEntry g_FrontendCreatematchoptionsPointerWords1[9] = {
    { 3590, 21, (ResidentEventHandler)(void *)&g_Frontend_CreateMatchOptionsPackedAddress242 }, { 3587, 21, (ResidentEventHandler)(void *)&g_Frontend_DestroyMatchOptionsPackedAddress24 }, { 3594, 21, (ResidentEventHandler)(void *)&g_Frontend_ReturnMatchOptionsEventZeroPackedAddress242 }, { 2, 21, (ResidentEventHandler)(void *)&g_Frontend_ExitMatchOptionsPackedAddress242 }, { 1, 21, (ResidentEventHandler)(void *)&g_Frontend_ActivateMatchOptionActionPackedAddress242 }, { 10, 21, (ResidentEventHandler)(void *)&g_Frontend_ResetMatchOptionOnEventPackedAddress242 }, { 8, 878, (ResidentEventHandler)(void *)&g_Frontend_RefreshMatchSlotsOnZeroEventAltPackedAddress242 }, { 7, 878, (ResidentEventHandler)(void *)&g_Frontend_RefreshMatchSlotsOnZeroEventPackedAddress242 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_FrontendCreatematchoptionsPointerWords1[9] = {
    { 3590, 21, (ResidentEventHandler)(void *)&g_Frontend_CreateMatchOptionsPackedAddress242 }, { 3587, 21, (ResidentEventHandler)(void *)&g_Frontend_DestroyMatchOptionsPackedAddress24 }, { 3594, 21, (ResidentEventHandler)(void *)&g_Frontend_ReturnMatchOptionsEventZeroPackedAddress242 }, { 2, 21, (ResidentEventHandler)(void *)&g_Frontend_ExitMatchOptionsPackedAddress242 }, { 1, 21, (ResidentEventHandler)(void *)&g_Frontend_ActivateMatchOptionActionPackedAddress242 }, { 10, 21, (ResidentEventHandler)(void *)&g_Frontend_ResetMatchOptionOnEventPackedAddress242 }, { 8, 878, (ResidentEventHandler)(void *)&g_Frontend_RefreshMatchSlotsOnZeroEventAltPackedAddress242 }, { 7, 878, (ResidentEventHandler)(void *)&g_Frontend_RefreshMatchSlotsOnZeroEventPackedAddress242 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
