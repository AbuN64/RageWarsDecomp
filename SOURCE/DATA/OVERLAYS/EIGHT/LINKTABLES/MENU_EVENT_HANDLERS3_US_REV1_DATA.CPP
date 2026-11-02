#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "TYPES.H"

#include "DATA/OVLTBL/MENU_EVENT_HANDLERS3_US_REV1_DATA.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E451C_unclaimed_E5128_unclaimed_E5130 */
#if defined(VERSION_US_REV1)
void * g_MenuEventHandlers3UsRev1EncodedWords[1] = {
    (void *)&g_options_CreateOptionsPageEntry
};
#endif

#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_menuEventHandlers3_us_rev1[4] = {
    { 3587, 4, (ResidentEventHandler)(void *)&g_menu_DestroyOptionsPageEntry }, { 2, 4, (ResidentEventHandler)(void *)&g_frontend_CloseOptionsPageEntry }, { 1, 4, (ResidentEventHandler)(void *)&g_frontend_HandleOptionsPageShortcutEntry }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
