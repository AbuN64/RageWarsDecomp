#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"


#if defined(VERSION_EU)
extern char g_Frontend_CreateProfileResetScreenEuropeanPackedAddress24[];
extern char g_Frontend_FreeProfileResetScreenPackedAddress24[];
extern char g_Frontend_PulseProfileResetWidgetPackedAddress24[];
extern char g_Frontend_HandleProfileResetConfirmPackedAddress24[];
extern char g_Frontend_AcknowledgeProfileResetEventPackedAddress24[];
extern char g_Frontend_ProfileResetEvent01HandlerPackedAddress24[];
extern char g_Frontend_WrapNodePairEuropeanPackedAddress24[];
extern char g_Frontend_UpdateTimedTransitionPackedAddress24[];
extern char g_Frontend_CancelNodePairMenuPackedAddress24[];
#if defined(VERSION_EU)
struct {
    ResidentEventHandlerEntry eventHandlers0[7];
    u8 alignmentFill84[8];
    ResidentEventHandlerEntry eventHandlers92[4];
} k_FrontendDispatchprofilereseteventEncodedWords __attribute__((aligned(4))) = {
    { { 3592, 24, (ResidentEventHandler)(void *)&g_Frontend_PulseProfileResetWidgetPackedAddress24 }, { 3590, 24, (ResidentEventHandler)(void *)&g_Frontend_CreateProfileResetScreenEuropeanPackedAddress24 }, { 3587, 24, (ResidentEventHandler)(void *)&g_Frontend_FreeProfileResetScreenPackedAddress24 }, { 1, 24, (ResidentEventHandler)(void *)&g_Frontend_ProfileResetEvent01HandlerPackedAddress24 }, { 2, 24, (ResidentEventHandler)(void *)&g_Frontend_AcknowledgeProfileResetEventPackedAddress24 }, { 10, 24, (ResidentEventHandler)(void *)&g_Frontend_HandleProfileResetConfirmPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x3, 0xa4, 0x61, 0x6, 0x1b, 0xd7, 0xff, 0x71 },
    { { 3590, 33, (ResidentEventHandler)(void *)&g_Frontend_WrapNodePairEuropeanPackedAddress24 }, { 2, 33, (ResidentEventHandler)(void *)&g_Frontend_CancelNodePairMenuPackedAddress24 }, { 1, 33, (ResidentEventHandler)(void *)&g_Frontend_UpdateTimedTransitionPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 } }
};
typedef char k_FrontendDispatchprofilereseteventEncodedWordsSizeCheck[(sizeof(k_FrontendDispatchprofilereseteventEncodedWords) == 140) ? 1 : -1];
#endif
#endif
