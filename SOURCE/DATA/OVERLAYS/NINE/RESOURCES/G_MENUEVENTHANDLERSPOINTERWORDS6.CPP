#include "COMMON/RESIDENT_EVENT_HANDLER.H"


#if defined(VERSION_US_REV1)
extern char g_Frontend_CreatePakProfileScreenPackedAddress24[];
/* ROM-grounded data: rodata/unresolved/800E54A8_unclaimed_E60CC */
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_OverlaysNineResourcesRetainedPointerWords1[1] = {
    { 3590, 19, (ResidentEventHandler)(void *)&g_Frontend_CreatePakProfileScreenPackedAddress24 }
};
#endif

extern char g_frontend_HandlePakProfileInputEntry[];
extern char g_PAKInterface_MoveNameCursorForwardPackedAddress242[];
extern char g_PAKInterface_MoveNameCursorBackwardPackedAddress242[];
extern char g_PAKInterface_HandleNextPanelSelectionPackedAddress242[];
extern char g_PAKInterface_HandlePakMenuConfirmPackedAddress242[];
extern char g_PAKInterface_ActivatePlayerPanelActionPackedAddress242[];
extern char g_PAKInterface_HandlePlayerPanelBackPackedAddress242[];
extern char g_Frontend_DestroyPakProfileScreenPackedAddress242[];
extern char g_Frontend_ResetNameRepeatOnEventPackedAddress242[];
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_MenuEventHandlersPointerWords6[10] = {
    { 3587, 19, (ResidentEventHandler)(void *)&g_Frontend_DestroyPakProfileScreenPackedAddress242 }, { 2, 19, (ResidentEventHandler)(void *)&g_PAKInterface_HandlePlayerPanelBackPackedAddress242 }, { 1, 19, (ResidentEventHandler)(void *)&g_PAKInterface_ActivatePlayerPanelActionPackedAddress242 }, { 10, 19, (ResidentEventHandler)(void *)&g_frontend_HandlePakProfileInputEntry }, { 11, 19, (ResidentEventHandler)(void *)&g_Frontend_ResetNameRepeatOnEventPackedAddress242 }, { 5, 19, (ResidentEventHandler)(void *)&g_PAKInterface_HandlePakMenuConfirmPackedAddress242 }, { 6, 19, (ResidentEventHandler)(void *)&g_PAKInterface_HandleNextPanelSelectionPackedAddress242 }, { 8, 19, (ResidentEventHandler)(void *)&g_PAKInterface_MoveNameCursorForwardPackedAddress242 },
    { 7, 19, (ResidentEventHandler)(void *)&g_PAKInterface_MoveNameCursorBackwardPackedAddress242 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
