#include "DATA/REST_SOURCE_RECORDS.H"
extern char addrLow_SmpFlicker_DestroyController[];
extern char addrLow_SmpFlicker_UpdateFlicker[];
extern char addrLow_SmpFrameAnim_DestroyController[];
extern char addrLow_SmpFrameAnim_UpdateFrameSequence[];
extern char addrLow_SmpList_DestroyController[];
extern char addrLow_SmpList_HandleDecrementInput[];
extern char addrLow_SmpList_HandleIncrementInput[];
extern char addrLow_SmpList_HandleStopEvent[];
extern char addrLow_SmpList_ResetEntryCommands[];
extern char addrLow_SmpList_UpdateSliderMotion[];
extern char addrLow_SmpSlider_DestroyController[];
extern char addrLow_SmpSlider_HighlightSliderItems[];
extern char addrLow_Smp_UpdateFadeProgress[];
extern char g_SmpButton_DestroyButtonControllerAddress[];
extern char g_SmpButton_DestroyListControllerAddress[];
extern char g_SmpButton_DimButtonItemsAddress[];
extern char g_SmpButton_DimButtonItemsWithSoundAddress[];
extern char g_SmpButton_DimListItemsAddress[];
extern char g_SmpButton_DimListItemsWithSoundAddress[];
extern char g_SmpButton_HighlightButtonItemsAddress[];
extern char g_SmpButton_HighlightListItemsAddress[];
extern char g_SmpButton_SelectNextListEntryAddress[];
extern char g_SmpButton_SelectPreviousListEntryAddress[];
extern char g_SmpOverlay_FollowSlotTarget2cAddress[];
extern char g_SmpOverlay_FollowSlotTarget30Address[];
extern char g_SmpOverlay_FollowSlotTarget34Address[];
extern char g_SmpOverlay_FollowSlotTarget38Address[];
extern char g_SmpOverlay_ForwardSlotEventAddress[];
extern char g_SmpOverlay_FreeEventObjectAddress[];
extern char g_SmpOverlay_ReturnUnhandledEventAddress[];
extern char g_SmpOverlay_SetListWidgetFlag40Address[];
extern char g_SmpSlider_DimSliderItemsAddress[];

#if defined(VERSION_US)
extern char addrLow_SmpFrameAnim_UpdateFrameSequence[];
extern char addrLow_SmpFrameAnim_DestroyController[];
extern char addrLow_SmpFlicker_UpdateFlicker[];
extern char addrLow_SmpFlicker_DestroyController[];
extern char addrLow_Smp_UpdateFadeProgress[];
extern char addrLow_SmpSlider_DestroyController[];
extern char g_SmpSlider_DimSliderItemsAddress[];
extern char addrLow_SmpSlider_HighlightSliderItems[];
extern char addrLow_SmpList_ResetEntryCommands[];
extern char addrLow_SmpList_HandleIncrementInput[];
extern char addrLow_SmpList_HandleDecrementInput[];
extern char addrLow_SmpList_HandleStopEvent[];
extern char addrLow_SmpList_UpdateSliderMotion[];
extern char addrLow_SmpList_DestroyController[];
extern char g_SmpButton_DimListItemsAddress[];
extern char g_SmpButton_HighlightListItemsAddress[];
extern char g_SmpButton_DimListItemsWithSoundAddress[];
extern char g_SmpButton_SelectNextListEntryAddress[];
extern char g_SmpButton_SelectPreviousListEntryAddress[];
extern char g_SmpButton_DestroyListControllerAddress[];
extern char g_SmpButton_DimButtonItemsAddress[];
extern char g_SmpButton_HighlightButtonItemsAddress[];
extern char g_SmpButton_DimButtonItemsWithSoundAddress[];
extern char g_SmpButton_DestroyButtonControllerAddress[];
extern char g_SmpOverlay_ReturnUnhandledEventAddress[];
extern char g_SmpOverlay_FollowSlotTarget34Address[];
extern char g_SmpOverlay_FollowSlotTarget2cAddress[];
extern char g_SmpOverlay_FollowSlotTarget38Address[];
extern char g_SmpOverlay_FollowSlotTarget30Address[];
extern char g_SmpOverlay_ForwardSlotEventAddress[];
extern char g_SmpOverlay_FreeEventObjectAddress[];
extern char g_SmpOverlay_SetListWidgetFlag40Address[];
RestSmpframeanimDispatcheventEncodedWordsLayout518 k_SmpframeanimDispatcheventEncodedWords = {
    { 3587, 30000 },
    (void *)&addrLow_SmpFrameAnim_DestroyController,
    { 3592, 30000 },
    { (void *)&addrLow_SmpFrameAnim_UpdateFrameSequence, 0, 0, 0, 0 },
    "!GRAPHIC",
    { 3587, 30000 },
    (void *)&addrLow_SmpFlicker_DestroyController,
    { 3592, 30000 },
    { (void *)&addrLow_SmpFlicker_UpdateFlicker, 0, 0, 0 },
    3840,
    0x0A000400,
    { 8263, 3587, 30000 },
    (void *)&addrLow_SmpSlider_DestroyController,
    { 3592, 30000 },
    { (void *)&addrLow_Smp_UpdateFadeProgress, 0, 0, 0 },
    4096,
    0x0B000000,
    { 7495, 3591, 30000 },
    (void *)&g_SmpSlider_DimSliderItemsAddress,
    { 15, 30000 },
    (void *)&addrLow_SmpSlider_HighlightSliderItems,
    { 16, 30000 },
    (void *)&addrLow_SmpList_ResetEntryCommands,
    { 8, 30000 },
    (void *)&addrLow_SmpList_HandleIncrementInput,
    { 7, 30000 },
    (void *)&addrLow_SmpList_HandleDecrementInput,
    { 3587, 30000 },
    (void *)&addrLow_SmpList_DestroyController,
    { 11, 30000 },
    (void *)&addrLow_SmpList_HandleStopEvent,
    { 3592, 30000 },
    { (void *)&addrLow_SmpList_UpdateSliderMotion, 0, 0, 0 },
    "T_TY",
    { 3591, 30000 },
    (void *)&g_SmpButton_DimListItemsAddress,
    { 15, 30000 },
    (void *)&g_SmpButton_HighlightListItemsAddress,
    { 16, 30000 },
    (void *)&g_SmpButton_DimListItemsWithSoundAddress,
    { 8, 30000 },
    (void *)&g_SmpButton_SelectNextListEntryAddress,
    { 7, 30000 },
    (void *)&g_SmpButton_SelectPreviousListEntryAddress,
    { 3587, 30000 },
    { (void *)&g_SmpButton_DestroyListControllerAddress, 0, 0, 0 },
    { 6684672, 262144, 39, 3591, 30000 },
    (void *)&g_SmpButton_DimButtonItemsAddress,
    { 15, 30000 },
    (void *)&g_SmpButton_HighlightButtonItemsAddress,
    { 16, 30000 },
    (void *)&g_SmpButton_DimButtonItemsWithSoundAddress,
    { 3587, 30000 },
    { (void *)&g_SmpButton_DestroyButtonControllerAddress, 0, 0, 0 },
    "GRAP",
    { 3591, 30000 },
    (void *)&g_SmpOverlay_ReturnUnhandledEventAddress,
    { 3587, 30000 },
    (void *)&g_SmpOverlay_FreeEventObjectAddress,
    { 3592, 30000 },
    (void *)&g_SmpOverlay_SetListWidgetFlag40Address,
    { 7, 30000 },
    (void *)&g_SmpOverlay_FollowSlotTarget34Address,
    { 5, 30000 },
    (void *)&g_SmpOverlay_FollowSlotTarget2cAddress,
    { 8, 30000 },
    (void *)&g_SmpOverlay_FollowSlotTarget38Address,
    { 6, 30000 },
    (void *)&g_SmpOverlay_FollowSlotTarget30Address,
    { 1, 30000 },
    { (void *)&g_SmpOverlay_ForwardSlotEventAddress, 0, 0, 0 },
    "TYPE",
};
#endif
