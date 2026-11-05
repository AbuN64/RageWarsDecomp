#include "Data/rest_source_records.h"
#include "Frontend/frontend_address_symbols.h"
#include "include_asm.h"
#include "Data/Ovl1_i/smpoverlay_dispatchpakdialogevent_data.h"
#include "Common/triple.h"

/* unit SMP_CONTROLLER_EVENTS.CPP */
#if defined(VERSION_DE)
/* Menu state seed block: seventeen zero words followed by a six-word tail. The zeros are the
   runtime's cleared fields; the tail words are cartridge settings — small numbers on eu, eu-x and
   us-rev1, and packed text or values on de, eu and us. */
extern RestsmpControllerStateAndEventWordsLayout872 g_smpControllerStateAndEventWords;
#elif defined(VERSION_EU)
RestsmpControllerStateAndEventWordsLayout873 g_smpControllerStateAndEventWords = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0x257301E8, 0x1580FFFC },
    1,
    4.758789f,
    { 0x03135820, 0x018B6022 }
};
#elif defined(VERSION_EU_X)
RestsmpControllerStateAndEventWordsLayout874 g_smpControllerStateAndEventWords = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 181, 200, 1, 198, 138, 130 }
};
#endif
#if defined(VERSION_EU_X)
RestsmpEventHandlerTablesLayout880 g_smpEventHandlerTables = { { 3587, 30000, 4300588, 3592, 30000, 4299552,
         0, 0, 0, 203, 183, 185, 3587, 30000, 4301948, 3592, 30000, 4300624, 0, 0, 0, 158, 162, 163, 3587,
         30000, 4303216, 3592, 30000, 4301984, 0, 0, 0, 4329512, 3594, 7, 3591, 30000, 4304256, 15, 30000,
         4304312, 16, 30000, 4304368, 8, 30000, 4304464, 7, 30000, 4304576, 3587, 30000, 4304816, 11,
         30000, 4304688, 3592, 30000, 4304732, 0, 0, 0, 0, 3591, 30000, 4305792, 15, 30000, 4305840, 16,
         30000, 4305888, 8, 30000, 4305976, 7, 30000, 4306076, 3587, 30000, 4306176, 0, 0, 0, 3592, 27,
         4333804, 3591, 30000, 4307268, 15, 30000, 4307316, 16, 30000, 4307364, 3587, 30000, 4307452,
         0, 0, 0, 7, 3591, 30000, 4308852, 3587, 30000, 4309576, 3592, 30000, 4309608, 7, 30000, 4308860,
         5, 30000, 4309008, 8, 30000, 4309156, 6, 30000, 4309304, 1, 30000, 4309452, 0, 0, 0, 4403020 } };
#endif
#if defined(VERSION_EU)
RestsmpEventHandlerTablesLayout881 g_smpEventHandlerTables = { { { { 3587, 30000, (void *)&addrLow_SmpFrameAnim_DestroyController },
             { 3592, 30000, (void *)&addrLow_SmpFrameAnim_UpdateFrameSequence }, { 0, 0, 0 } }, { 0x400B5000,
             0x01785822, 0x19600002 } }, { { { 3587, 30000, (void *)&addrLow_SmpFlicker_DestroyController },
             { 3592, 30000, (void *)&addrLow_SmpFlicker_UpdateFlicker }, { 0, 0, 0 } }, { 0, 0x97340380,
             0x0C000489 } }, { { { 3587, 30000, (void *)&addrLow_SmpSlider_DestroyController }, { 3592, 30000, (void *)&addrLow_Smp_UpdateFadeProgress },
             { 0, 0, 0 } }, { 0x900801D9, 0x30A70001, 0x15000006 } }, { { { 3591, 30000, (void *)&addrLow_SmpSlider_DimSliderItems },
             { 15, 30000, (void *)&addrLow_SmpSlider_HighlightSliderItems }, { 16, 30000, (void *)&addrLow_SmpList_ResetEntryCommands },
             { 8, 30000, (void *)&addrLow_SmpList_HandleIncrementInput }, { 7, 30000, (void *)&addrLow_SmpList_HandleDecrementInput },
             { 3587, 30000, (void *)&addrLow_SmpList_DestroyController }, { 11, 30000, (void *)&addrLow_SmpList_HandleStopEvent },
             { 3592, 30000, (void *)&addrLow_SmpList_UpdateSliderMotion }, { 0, 0, 0 } }, 0x4B017F46 },
     { { { 3591, 30000, (void *)&addrLow_SmpButton_DimListItems }, { 15, 30000, (void *)&addrLow_SmpButton_HighlightListItems },
             { 16, 30000, (void *)&addrLow_SmpButton_DimListItemsWithSound }, { 8, 30000, (void *)&addrLow_SmpButton_SelectNextListEntry },
             { 7, 30000, (void *)&addrLow_SmpButton_SelectPreviousListEntry }, { 3587, 30000, (void *)&addrLow_SmpButton_DestroyListController },
             { 0, 0, 0 } }, { 0xE9030E7A, 0x4BB2B9C6, 0xE919147C } }, { { { 3591, 30000, (void *)&addrLow_SmpButton_DimButtonItems },
             { 15, 30000, (void *)&addrLow_SmpButton_HighlightButtonItems }, { 16, 30000, (void *)&addrLow_SmpButton_DimButtonItemsWithSound },
             { 3587, 30000, (void *)&addrLow_SmpButton_DestroyButtonController }, { 0, 0, 0 } }, 0x1260000D },
     { { { 3591, 30000, (void *)&addrLow_SmpOverlay_ReturnUnhandledEvent }, { 3587, 30000, (void *)&addrLow_SmpOverlay_FreeEventObject },
             { 3592, 30000, (void *)&addrLow_SmpOverlay_SetListWidgetFlag40 }, { 7, 30000, (void *)&addrLow_SmpOverlay_FollowSlotTarget34 },
             { 5, 30000, (void *)&addrLow_SmpOverlay_FollowSlotTarget2c }, { 8, 30000, (void *)&addrLow_SmpOverlay_FollowSlotTarget38 },
             { 6, 30000, (void *)&addrLow_SmpOverlay_FollowSlotTarget30 }, { 1, 30000, (void *)&addrLow_SmpOverlay_ForwardSlotEvent },
             { 0, 0, 0 } }, 0xE9171C7C } };
#endif

/* unit SMPOVERLAY_REFRESHPAKDIALOG_DATA.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
s32 g_pakDialogProbeStateStorage[3] = {
    -1, 0, 0,
};
#endif

/* unit SMPOVERLAY_DISPATCHPAKDIALOGEVENT_DATA.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
RestSmpOverlayDispatchPakDialogEventDataLayout455 g_smpOverlayDispatchPakDialogEventData = {
    { 3592, 29, 4310028, 3590, 29, 4309676, 3587, 29, 4309980, 1, 29, 4310164, 2, 29, 4310132, 10, 29, 4310124, 0, 0, 0 },
    { 0x96969600, 0x96969600 },
    { -4.112e+05f, -4.112e+05f },
    { 12800, 0 },
    (void *)&g_resultsLivesPluralFormat,
    510
};
#endif
#if defined(VERSION_EU)
RestSmpOverlayDispatchPakDialogEventDataLayout456 g_smpOverlayDispatchPakDialogEventData = {
    { 3592, 29, 4311132, 3590, 29, 4310780, 3587, 29, 4311084, 1, 29, 4311268, 2, 29, 4311236, 10, 29, 4311228, 0, 0, 0 },
    { 0x96969600, 0x96969600 },
    { -4.112e+05f, -4.112e+05f },
    { 12800, 0 },
    7529382.5f,
    0x21CE0020
};
#endif
#if defined(VERSION_EU_X)
RestSmpOverlayDispatchPakDialogEventDataLayout457 g_smpOverlayDispatchPakDialogEventData = {
    { 3592, 29, 4311132, 3590, 29, 4310780, 3587, 29, 4311084, 1, 29, 4311268, 2, 29, 4311236, 10, 29, 4311228, 0, 0, 0 },
    { 0x96969600, 0x96969600 },
    { -4.112e+05f, -4.112e+05f },
    { 12800, 0, 3590, 11 }
};
#endif
#endif
