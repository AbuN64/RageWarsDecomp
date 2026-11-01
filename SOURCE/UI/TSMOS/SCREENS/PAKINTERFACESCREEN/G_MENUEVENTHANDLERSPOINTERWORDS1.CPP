#include "DATA/OVL1_J/ScreenPointerWordBlock.H"
#include "DATA/UI/EVENT_HANDLER_RECORD.H"
#if defined(VERSION_US_REV1)
/* 80408CB0_12.CPP */
/* ScreenPointerWordBlock.CPP */
/* ROM-grounded data: rodata/unresolved/800E5834_unclaimed_E644C */
EventHandlerRecord g_Screen1PointerWords1[1] = {
    { 3590, 18, g_Achieve_CreateResultsScreenAddress },
};
EventHandlerRecord g_MenuEventHandlersPointerWords1[5] = {
    { 3587, 18, g_CPlayerPreview_CloseSelectionMessageScreenAddress },
    { 2, 18, g_Achieve_AcknowledgeResultsEventAddress },
    { 1, 18, g_Achieve_HandleResultsMenuChoiceAddress },
    { 3594, 18, g_Achieve_UpdateResultsScreenAddress },
    { 0, 0, 0 },
};
/* ScreenRetainedTextFragment.CPP */
char g_frontendScreenRetainedTextFragment[12] = "RE_WAR_CRYeq";
#endif
