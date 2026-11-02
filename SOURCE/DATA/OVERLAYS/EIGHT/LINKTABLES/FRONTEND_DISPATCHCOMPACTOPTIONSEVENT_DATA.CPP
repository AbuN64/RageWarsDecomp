#include "COMMON/RESIDENT_EVENT_HANDLER.H"

#include "DATA/OVLTBL/FRONTEND_DISPATCHCOMPACTOPTIONSEVENT_DATA.H"

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_menuEventHandlers1_us_rev1[6] = {
    { 3592, 11, (ResidentEventHandler)(void *)&g_frontend_ActivateCompactOptionsPageEntry }, { 3590, 11, (ResidentEventHandler)(void *)&g_frontend_CreateGameOptionsScreenEntry }, { 3587, 11, (ResidentEventHandler)(void *)&g_frontend_DestroyCompactOptionsPageEntry }, { 2, 11, (ResidentEventHandler)(void *)&g_frontend_CloseCompactOptionsPageEntry }, { 1, 11, (ResidentEventHandler)(void *)&g_frontend_HandleCompactOptionsShortcutEntry }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
