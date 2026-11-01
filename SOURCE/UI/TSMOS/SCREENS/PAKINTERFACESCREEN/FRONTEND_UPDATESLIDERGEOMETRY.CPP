#include "DATA/OVL1_J/g_FrontendUpdateslidergeometryEncodedWords_FrontendUpdateslidergeometry.H"
#include "DATA/OVL1_J/g_frontendSliderTransitionHandlerWords_FrontendUpdateslidergeometry.H"
#include "DATA/UI/EVENT_HANDLER_RECORD.H"
#if defined(VERSION_US_REV1)
/* 80408CB0_14.CPP */
/* 80408CB0_14.CPP */
/* g_FrontendUpdateslidergeometryEncodedWords_FrontendUpdateslidergeometry.CPP */
/* ROM-grounded data: rodata/unresolved/800E58A8_unclaimed_E64C0 */
EventHandlerRecord g_FrontendUpdateslidergeometryEncodedWords[1] = {
    { 3590, 6, addrLow_Menu_CreateSoundOptionsScreen },
};
EventHandlerRecord g_frontendSliderEventHandlerWords[4] = {
    { 3587, 6, addrLow_Menu_FreeSoundOptionsScreen },
    { 2, 6, addrLow_Menu_CancelSoundOptionsScreen },
    { 1, 6, addrLow_Menu_ConfirmSoundOptionsScreen },
    { 0, 0, 0 },
};
/* g_frontendSliderTransitionHandlerWords_FrontendUpdateslidergeometry.CPP */
EventHandlerRecord g_frontendSliderTransitionHandlerWords[7] = {
    { 3591, 13, addrLow_Menu_SoundSliderReturnZero },
    { 3592, 13, addrLow_Menu_ApplySoundSliders },
    { 3590, 13, addrLow_Menu_CreateSoundSliders },
    { 3587, 13, addrLow_Menu_FreeSoundSliders },
    { 2, 13, addrLow_Menu_CancelSoundSliderPopup },
    { 1, 13, addrLow_Menu_ConfirmSoundSliderPopup },
    { 0, 0, 0 },
};
#endif
