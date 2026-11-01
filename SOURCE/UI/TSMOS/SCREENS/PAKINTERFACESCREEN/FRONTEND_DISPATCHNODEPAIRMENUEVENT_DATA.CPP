#include "DATA/OVL1_J/FRONTEND_DISPATCHNODEPAIRMENUEVENT_DATA.H"
#include "DATA/UI/EVENT_HANDLER_RECORD.H"
#if defined(VERSION_US_REV1)
/* 80408CB0_15.CPP */
/* frontendDispatchnodepairmenueventEncodedWordsData.CPP */
/* ROM-grounded data: rodata/unresolved/800E5954_unclaimed_E65A8 */
unsigned int g_FrontendDispatchnodepairmenueventEncodedWords[2] = {
    0x000B0000, 0x00000011,
};
EventHandlerRecord g_menuEventHandlers4_us_rev1[4] = {
    { 3590, 33, (void *)0x00439F10 },
    { 2, 33, g_frontend_CancelNodePairMenuEntry },
    { 1, 33, g_frontend_UpdateTimedTransitionEntry },
    { 0, 0, 0 },
};
#endif
