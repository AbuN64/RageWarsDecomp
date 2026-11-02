#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "TYPES.H"

#include "DATA/SCENARIO_SETUP/FRONTEND_DISPATCHRESIDENTACTOREVENT_DATA.H"

/* 800E55C8.CPP */
#if defined(VERSION_US_REV1)
extern char g_Frontend_CreatePauseConfirmationPackedAddress242[];
extern char g_Timed_DestroyPauseConfirmationPackedAddress242[];
extern char g_Timed_SetConfirmationInputModePackedAddress242[];
extern char g_Timed_FinishPauseConfirmationTransitionPackedAddress242[];
extern char g_Frontend_ReturnConfirmationEventZeroPackedAddress242[];
extern char g_Frontend_ConsumeConfirmationEventPackedAddress242[];
extern char g_Timed_UpdateTimedScreenPackedAddress242[];
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_MenuEventHandlersPointerWords2[8] = {
    { 3591, 31, (ResidentEventHandler)(void *)&g_Timed_SetConfirmationInputModePackedAddress242 }, { 3592, 31, (ResidentEventHandler)(void *)&g_Frontend_ReturnConfirmationEventZeroPackedAddress242 }, { 3594, 31, (ResidentEventHandler)(void *)&g_Timed_FinishPauseConfirmationTransitionPackedAddress242 }, { 3590, 31, (ResidentEventHandler)(void *)&g_Frontend_CreatePauseConfirmationPackedAddress242 }, { 3587, 31, (ResidentEventHandler)(void *)&g_Timed_DestroyPauseConfirmationPackedAddress242 }, { 1, 31, (ResidentEventHandler)(void *)&g_Timed_UpdateTimedScreenPackedAddress242 }, { 2, 31, (ResidentEventHandler)(void *)&g_Frontend_ConsumeConfirmationEventPackedAddress242 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

/* 800E5628.CPP */
#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_MenuEventHandlersPointerWords3[8] = {
    { 3591, 32, (ResidentEventHandler)(void *)&g_Timed_SetConfirmationInputModePackedAddress243 }, { 3592, 32, (ResidentEventHandler)(void *)&g_Frontend_ReturnConfirmationEventZeroPackedAddress243 }, { 3594, 32, (ResidentEventHandler)(void *)&g_Timed_FinishPauseConfirmationTransitionPackedAddress243 }, { 3590, 32, (ResidentEventHandler)(void *)&g_Frontend_CreatePauseConfirmationPackedAddress243 }, { 3587, 32, (ResidentEventHandler)(void *)&g_Timed_DestroyPauseConfirmationPackedAddress243 }, { 1, 32, (ResidentEventHandler)(void *)&g_Timed_UpdateTimedScreenPackedAddress243 }, { 2, 32, (ResidentEventHandler)(void *)&g_Frontend_ConsumeConfirmationEventPackedAddress243 }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

/* 800E5688.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E555C_unclaimed_E61C8_unclaimed_E6228_unclaimed_E6288 */
#if defined(VERSION_US_REV1)
struct {
    u8 alignmentFill[8];
} g_FrontendDispatchresidentactoreventWords1 __attribute__((aligned(4))) = {
    { 0x71, 0x75, 0x04, 0x2E, 0x65, 0x6F, 0x73, 0x00 }
};
#endif
#endif
