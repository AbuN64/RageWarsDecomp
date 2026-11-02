#include "COMMON/RESIDENT_EVENT_HANDLER.H"

#include "DATA/OVLTBL/FRONTEND_DISPATCHTABOPTIONSEVENT_DATA.H"

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_menuEventHandlers2_us_rev1[7] = {
    { 3592, 22, (ResidentEventHandler)(void *)&g_menu_AnimateTabOptionsMenuEntry }, { 3594, 22, (ResidentEventHandler)(void *)&g_menu_FinishTabOptionsTransitionEntry }, { 3590, 22, (ResidentEventHandler)(void *)&g_options_OpenOptionsScreenEntry }, { 3587, 22, (ResidentEventHandler)(void *)&g_frontend_DestroyTabOptionsPageEntry }, { 2, 22, (ResidentEventHandler)(void *)&g_frontend_ConsumeTabOptionsEventEntry }, { 1, 22, (ResidentEventHandler)(void *)&g_frontend_HandleTabOptionsShortcutEntry }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
