#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "TYPES.H"

extern s32 Frontend_CreatePakProfileScreen(void *screen);
extern char Frontend_CreatePakProfileScreenDe[];
extern char Frontend_CreatePakProfileScreenEu[];
extern char Frontend_CreatePakProfileScreenEux[];
extern s32 Frontend_DestroyPakProfileScreen(void);
extern char Frontend_DestroyPakProfileScreen_Address[];
extern s32 Frontend_HandlePakProfileInput(s32 a,s32 b,u32 event,s32 key);
extern int Frontend_ResetNameRepeatOnEvent(int unused0, int unused1, unsigned int message, int arg);
extern s32 Frontend_ReturnProfileEventZero(void);
extern s32 Frontend_UpdatePakScreenExit(void *unused0, void *unused1, s32 event);
extern s32 Frontend_UpdatePakScreenPanels(s32 unused0, s32 unused1, s32 event);
extern s32 PAKInterface_ActivatePlayerPanelAction(s32 unused0, s32 unused1, s32 playerEntryId);
extern s32 PAKInterface_HandleNextPanelSelection(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed, s32 fifth);
extern s32 PAKInterface_HandlePakMenuConfirm(s32 unused0, s32 unused1, s32 packedPlayerEvent, s32 pressState, s32 fifth);
extern s32 PAKInterface_HandlePlayerPanelBack(void *unused0, void *unused1, u16 player);
extern s32 PAKInterface_MoveNameCursorBackward(s32 unused0, s32 unused1, s32 playerEntryId, s32 selectionPressed);
extern s32 PAKInterface_MoveNameCursorForward(s32 unusedA, s32 unusedB, s32 index, s32 mode);
extern char g_Frontend_DestroyPakProfileScreenPackedAddress24[];
extern char g_Frontend_HandlePakProfileInputPackedAddress24[];
extern char g_Frontend_ResetNameRepeatOnEventPackedAddress24[];
extern char g_Frontend_ReturnProfileEventZeroPackedAddress24[];
extern char g_Frontend_UpdatePakScreenExitPackedAddress24[];
extern char g_Frontend_UpdatePakScreenPanelsPackedAddress24[];
extern char g_PAKInterface_ActivatePlayerPanelActionPackedAddress24[];
extern char g_PAKInterface_HandleNextPanelSelectionPackedAddress24[];
extern char g_PAKInterface_HandlePakMenuConfirmPackedAddress24[];
extern char g_PAKInterface_HandlePlayerPanelBackPackedAddress24[];
extern char g_PAKInterface_MoveNameCursorBackwardPackedAddress24[];
extern char g_PAKInterface_MoveNameCursorForwardPackedAddress24[];

#include "include_asm.h"
#include "DATA/SCENARIO_SETUP/FRONTEND_DISPATCHPAKPROFILEEVENT_DATA.H"

/* 800E5494_2.CPP */
/* ROM-grounded data: rodata/writable/800E54A0 */
#if defined(VERSION_DE)
struct {
    s32 g_pakProfileRequestedPhase;
    void * g_pakProfileScreenState;
} g_FrontendDispatchpakprofileeventWords1 __attribute__((aligned(4))) = {
    0,
    0
};
typedef char g_FrontendDispatchpakprofileeventWords1SizeCheck[(sizeof(g_FrontendDispatchpakprofileeventWords1) == 8) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    s32 g_pakProfileRequestedPhase;
    void * g_pakProfileScreenState;
} g_FrontendDispatchpakprofileeventWords1 __attribute__((aligned(4))) = {
    0,
    0
};
typedef char g_FrontendDispatchpakprofileeventWords1SizeCheck[(sizeof(g_FrontendDispatchpakprofileeventWords1) == 8) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    s32 g_pakProfileRequestedPhase;
    void * g_pakProfileScreenState;
} g_FrontendDispatchpakprofileeventWords1 __attribute__((aligned(4))) = {
    0,
    0
};
typedef char g_FrontendDispatchpakprofileeventWords1SizeCheck[(sizeof(g_FrontendDispatchpakprofileeventWords1) == 8) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    s32 g_pakProfileRequestedPhase;
    void * g_pakProfileScreenState;
} g_FrontendDispatchpakprofileeventWords1 __attribute__((aligned(4))) = {
    0,
    0
};
typedef char g_FrontendDispatchpakprofileeventWords1SizeCheck[(sizeof(g_FrontendDispatchpakprofileeventWords1) == 8) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    s32 g_pakProfileRequestedPhase;
    void * g_pakProfileScreenState;
} g_FrontendDispatchpakprofileeventWords1 __attribute__((aligned(4))) = {
    0,
    0
};
typedef char g_FrontendDispatchpakprofileeventWords1SizeCheck[(sizeof(g_FrontendDispatchpakprofileeventWords1) == 8) ? 1 : -1];
#endif

/* 800E54A8.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
#if defined(VERSION_DE)
ResidentEventHandlerEntry D_src_95297a43[14] = {
    { 3591, 19, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnProfileEventZero - 0x80000000U) }, { 3594, 19, (ResidentEventHandler)(void *)((char *)&Frontend_UpdatePakScreenExit - 0x80000000U) }, { 3592, 19, (ResidentEventHandler)(void *)((char *)&Frontend_UpdatePakScreenPanels - 0x80000000U) }, { 3590, 19, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePakProfileScreenDe - 0x80000000U) }, { 3587, 19, (ResidentEventHandler)(void *)&Frontend_DestroyPakProfileScreen_Address }, { 2, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_HandlePlayerPanelBack - 0x80000000U) }, { 1, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_ActivatePlayerPanelAction - 0x80000000U) }, { 10, 19, (ResidentEventHandler)(void *)((char *)&Frontend_HandlePakProfileInput - 0x80000000U) },
    { 11, 19, (ResidentEventHandler)(void *)((char *)&Frontend_ResetNameRepeatOnEvent - 0x80000000U) }, { 5, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_HandlePakMenuConfirm - 0x80000000U) }, { 6, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_HandleNextPanelSelection - 0x80000000U) }, { 8, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_MoveNameCursorForward - 0x80000000U) }, { 7, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_MoveNameCursorBackward - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#if defined(VERSION_EU)
#if defined(VERSION_EU)
ResidentEventHandlerEntry D_src_95297a43[14] = {
    { 3591, 19, (ResidentEventHandler)(void *)&g_Frontend_ReturnProfileEventZeroPackedAddress24 }, { 3594, 19, (ResidentEventHandler)(void *)&g_Frontend_UpdatePakScreenExitPackedAddress24 }, { 3592, 19, (ResidentEventHandler)(void *)&g_Frontend_UpdatePakScreenPanelsPackedAddress24 }, { 3590, 19, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePakProfileScreenEu - 0x80000000U) }, { 3587, 19, (ResidentEventHandler)(void *)&g_Frontend_DestroyPakProfileScreenPackedAddress24 }, { 2, 19, (ResidentEventHandler)(void *)&g_PAKInterface_HandlePlayerPanelBackPackedAddress24 }, { 1, 19, (ResidentEventHandler)(void *)&g_PAKInterface_ActivatePlayerPanelActionPackedAddress24 }, { 10, 19, (ResidentEventHandler)(void *)&g_Frontend_HandlePakProfileInputPackedAddress24 },
    { 11, 19, (ResidentEventHandler)(void *)&g_Frontend_ResetNameRepeatOnEventPackedAddress24 }, { 5, 19, (ResidentEventHandler)(void *)&g_PAKInterface_HandlePakMenuConfirmPackedAddress24 }, { 6, 19, (ResidentEventHandler)(void *)&g_PAKInterface_HandleNextPanelSelectionPackedAddress24 }, { 8, 19, (ResidentEventHandler)(void *)&g_PAKInterface_MoveNameCursorForwardPackedAddress24 }, { 7, 19, (ResidentEventHandler)(void *)&g_PAKInterface_MoveNameCursorBackwardPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
ResidentEventHandlerEntry D_src_95297a43[14] = {
    { 3591, 19, (ResidentEventHandler)(void *)((char *)&Frontend_ReturnProfileEventZero - 0x80000000U) }, { 3594, 19, (ResidentEventHandler)(void *)((char *)&Frontend_UpdatePakScreenExit - 0x80000000U) }, { 3592, 19, (ResidentEventHandler)(void *)((char *)&Frontend_UpdatePakScreenPanels - 0x80000000U) }, { 3590, 19, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePakProfileScreenEux - 0x80000000U) }, { 3587, 19, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyPakProfileScreen - 0x80000000U) }, { 2, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_HandlePlayerPanelBack - 0x80000000U) }, { 1, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_ActivatePlayerPanelAction - 0x80000000U) }, { 10, 19, (ResidentEventHandler)(void *)((char *)&Frontend_HandlePakProfileInput - 0x80000000U) },
    { 11, 19, (ResidentEventHandler)(void *)((char *)&Frontend_ResetNameRepeatOnEvent - 0x80000000U) }, { 5, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_HandlePakMenuConfirm - 0x80000000U) }, { 6, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_HandleNextPanelSelection - 0x80000000U) }, { 8, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_MoveNameCursorForward - 0x80000000U) }, { 7, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_MoveNameCursorBackward - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded exact candidate, normalized from prior lane proof. */
#if defined(VERSION_US)
ResidentEventHandlerEntry g_FrontendDispatchpakprofileeventPointerWords1[3] = {
    { 3591, 19, (ResidentEventHandler)(void *)&g_Frontend_ReturnProfileEventZeroPackedAddress242 }, { 3594, 19, (ResidentEventHandler)(void *)&g_Frontend_UpdatePakScreenExitPackedAddress242 }, { 3592, 19, (ResidentEventHandler)(void *)&g_Frontend_UpdatePakScreenPanelsPackedAddress242 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_FrontendDispatchpakprofileeventPointerWords1[3] = {
    { 3591, 19, (ResidentEventHandler)(void *)&g_Frontend_ReturnProfileEventZeroPackedAddress242 }, { 3594, 19, (ResidentEventHandler)(void *)&g_Frontend_UpdatePakScreenExitPackedAddress242 }, { 3592, 19, (ResidentEventHandler)(void *)&g_Frontend_UpdatePakScreenPanelsPackedAddress242 }
};
#endif
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
ResidentEventHandlerEntry g_FrontendDispatchpakprofileeventPointerWords2[11] = {
    { 3590, 19, (ResidentEventHandler)(void *)((char *)&Frontend_CreatePakProfileScreen - 0x80000000U) }, { 3587, 19, (ResidentEventHandler)(void *)((char *)&Frontend_DestroyPakProfileScreen - 0x80000000U) }, { 2, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_HandlePlayerPanelBack - 0x80000000U) }, { 1, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_ActivatePlayerPanelAction - 0x80000000U) }, { 10, 19, (ResidentEventHandler)(void *)((char *)&Frontend_HandlePakProfileInput - 0x80000000U) }, { 11, 19, (ResidentEventHandler)(void *)((char *)&Frontend_ResetNameRepeatOnEvent - 0x80000000U) }, { 5, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_HandlePakMenuConfirm - 0x80000000U) }, { 6, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_HandleNextPanelSelection - 0x80000000U) },
    { 8, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_MoveNameCursorForward - 0x80000000U) }, { 7, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_MoveNameCursorBackward - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
