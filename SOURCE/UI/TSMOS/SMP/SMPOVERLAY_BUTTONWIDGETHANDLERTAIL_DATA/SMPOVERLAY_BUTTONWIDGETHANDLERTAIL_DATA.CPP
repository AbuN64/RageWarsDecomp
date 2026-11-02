#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_Frontend_UpdatePlayerCountScreenAddress[];
extern char g_SmpOverlay_FollowSlotTarget2cAddress[];
extern char g_SmpOverlay_FollowSlotTarget30Address[];
extern char g_SmpOverlay_FollowSlotTarget34Address[];
extern char g_SmpOverlay_FollowSlotTarget38Address[];
extern char g_SmpOverlay_ForwardSlotEventAddress[];
extern char g_SmpOverlay_FreeEventObjectAddress[];
extern char g_SmpOverlay_ReturnUnhandledEventAddress[];
extern char g_SmpOverlay_SetListWidgetFlag40Address[];

/* g_buttonWidgetHandlerTailUsRev1_SmpbuttonDispatchlisteventData.CPP */
#if defined(VERSION_US_REV1)
extern char g_SmpOverlay_ReturnUnhandledEventAddress[];
extern char g_SmpOverlay_FollowSlotTarget34Address[];
extern char g_SmpOverlay_FollowSlotTarget2cAddress[];
extern char g_SmpOverlay_FollowSlotTarget38Address[];
extern char g_SmpOverlay_FollowSlotTarget30Address[];
extern char g_SmpOverlay_ForwardSlotEventAddress[];
extern char g_SmpOverlay_FreeEventObjectAddress[];
extern char g_SmpOverlay_SetListWidgetFlag40Address[];
extern char g_Frontend_UpdatePlayerCountScreenAddress[];
RestbuttonWidgetHandlerTailUsRev1Layout454 g_buttonWidgetHandlerTailUsRev1 = {
    (void *)&g_Frontend_UpdatePlayerCountScreenAddress,
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
    19,
};
#endif
