#include "Data/rest_source_records.h"
#include "Ui/ui_address_symbols.h"
#include "Data/Ovl1_i/smpoverlay_dispatchpakdialogevent_data.h"

#if defined(VERSION_US_REV1)
ButtonWidgetHandlerTailUsRev1Layout g_smpOverlayPlayerCountWidgetHandlers = {
    (void *)&g_Frontend_UpdatePlayerCountScreenAddress,
    { 3591, 30000 },
    (void *)&g_SmpOverlay_ReturnUnhandledEventAddress,
    { 3587, 30000 },
    (void *)&g_SmpOverlay_FreeEventObjectAddress,
    { 3592, 30000 },
    (void *)&addrLow_SmpOverlay_SelectListWidgets_us,
    { 7, 30000 },
    (void *)&addrLow_SmpOverlay_FollowChildSlotTarget_us,
    { 5, 30000 },
    (void *)&addrLow_SmpOverlay_FollowListSlotTarget_us,
    { 8, 30000 },
    (void *)&addrLow_SmpOverlay_FollowOverlaySlotTarget_us,
    { 6, 30000 },
    (void *)&addrLow_SmpOverlay_FollowTextSlotTarget_us,
    { 1, 30000 },
    { (void *)&g_SmpOverlay_ForwardSlotEventAddress, 0, 0, 0 },
    19
};
#endif

#if defined(VERSION_US_REV1)
s32 g_pakDialogProbeStateStorage[3] = {
    -1, 0, 0,
};
#endif

#if defined(VERSION_US_REV1)
RestPakDialogEventHandlerRecordsUsRecord g_pakDialogEventHandlerRecordsUs = {
    3592,
    29,
    (unsigned int)g_SmpOverlay_TickPakDialogAddress,
    3590,
    29,
    (unsigned int)g_SmpOverlay_CreatePakDialogAddress,
    3587,
    29,
    (unsigned int)g_SmpOverlay_DestroyPakDialogAddress,
    1,
    29,
    (unsigned int)g_SmpOverlay_HandlePakDialogChoiceAddress,
    2,
    29,
    (unsigned int)g_SmpOverlay_ConsumePakDialogEventAddress,
    10,
    29,
    (unsigned int)g_SmpOverlay_ReturnUnhandledPakDialogEventAddress,
    { 0x00000000, 0x00000000, 0x00000000 },
};
#endif
