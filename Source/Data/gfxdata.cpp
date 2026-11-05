#include "Data/Ovl1_i/smpoverlay_dispatchpakdialogevent_data.h"
#include "Ui/ui_address_symbols.h"
#include "Data/rest_source_records.h"
#include "Data/Gfxdata/smpframeanim_dispatchevent_data.h"

/* S_GFXDATARAXVICTORYTEXT.CPP */
#if defined(VERSION_US)
const char s_GfxdataRAXVICTORYText[12] =
    "\021RAX_VICTORY";
#endif

/* SMPFRAMEANIM_DISPATCHEVENT_DATA.CPP */
#if defined(VERSION_US)
RestsmpEventHandlerTablesLayout881 k_SmpframeanimDispatchevent = { { { { 3587, 30000, (void *)&SmpFrameAnim_DestroyController },
             { 3592, 30000, (void *)&SmpFrameAnim_UpdateFrameSequence }, { 0, 0, 0 } }, { 0, 0x21475241,
             0x50484943 } }, { { { 3587, 30000, (void *)&SmpFlicker_DestroyController }, { 3592, 30000, (void *)&SmpFlicker_UpdateFlicker },
             { 0, 0, 0 } }, { 3840, 0x0A000400, 8263 } }, { { { 3587, 30000, (void *)&SmpSlider_DestroyController },
             { 3592, 30000, (void *)&Smp_UpdateFadeProgress }, { 0, 0, 0 } }, { 4096, 0x0B000000, 7495 } },
     { { { 3591, 30000, (void *)&g_SmpSlider_DimSliderItemsAddress }, { 15, 30000, (void *)&SmpSlider_HighlightSliderItems },
             { 16, 30000, (void *)&SmpList_ResetEntryCommands }, { 8, 30000, (void *)&SmpList_HandleIncrementInput },
             { 7, 30000, (void *)&SmpList_HandleDecrementInput }, { 3587, 30000, (void *)&SmpList_DestroyController },
             { 11, 30000, (void *)&SmpList_HandleStopEvent }, { 3592, 30000, (void *)&SmpList_UpdateSliderMotion },
             { 0, 0, 0 } }, 0x545F5459 }, { { { 3591, 30000, (void *)&g_SmpButton_DimListItemsAddress },
             { 15, 30000, (void *)&g_SmpButton_HighlightListItemsAddress }, { 16, 30000, (void *)&g_SmpButton_DimListItemsWithSoundAddress },
             { 8, 30000, (void *)&g_SmpButton_SelectNextListEntryAddress }, { 7, 30000, (void *)&g_SmpButton_SelectPreviousListEntryAddress },
             { 3587, 30000, (void *)&g_SmpButton_DestroyListControllerAddress }, { 0, 0, 0 } }, { 6684672,
             262144, 39 } }, { { { 3591, 30000, (void *)&g_SmpButton_DimButtonItemsAddress }, { 15, 30000, (void *)&g_SmpButton_HighlightButtonItemsAddress },
             { 16, 30000, (void *)&g_SmpButton_DimButtonItemsWithSoundAddress }, { 3587, 30000, (void *)&g_SmpButton_DestroyButtonControllerAddress },
             { 0, 0, 0 } }, 0x47524150 }, { { { 3591, 30000, (void *)&g_SmpOverlay_ReturnUnhandledEventAddress },
             { 3587, 30000, (void *)&g_SmpOverlay_FreeEventObjectAddress }, { 3592, 30000, (void *)&addrLow_SmpOverlay_SelectListWidgets_us },
             { 7, 30000, (void *)&addrLow_SmpOverlay_FollowChildSlotTarget_us }, { 5, 30000, (void *)&addrLow_SmpOverlay_FollowListSlotTarget_us },
             { 8, 30000, (void *)&addrLow_SmpOverlay_FollowOverlaySlotTarget_us }, { 6, 30000, (void *)&addrLow_SmpOverlay_FollowTextSlotTarget_us },
             { 1, 30000, (void *)&g_SmpOverlay_ForwardSlotEventAddress }, { 0, 0, 0 } }, 0x54595045 } };
#endif

#if defined(VERSION_US)
s32 g_pakDialogProbeStateStorage[3] = {
    -1, 0, 0,
};
#endif

#if defined(VERSION_US)
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
