#include "include_asm.h"
#include "COMMON/LONE/RESOURCE_REQUEST_QUEUE.H"
#include "COMMON/GFX_INITIALIZEFRONTENDSERVICES.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "UI/QUAG/N64_ENG.H"
#include "MENU/SMPFRAMEANIM_REGISTERFRAMEANIMCLASS.H"
#include "MENU/SMPFADE_REGISTERFADECLASS.H"
#include "MENU/SMP_SLIDER.H"
#include "MENU/SMPLIST_REGISTERLISTCLASS.H"
#include "RESMGR/FRAME_HEAP_LIFETIME.H"
#include "UI/TSMOS/SMP/SMP_FLICKER.H"
#include "UI/TSMOS/TSMOS.H"

#if defined(VERSION_EU)
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
extern int g_frontendTransitionCountdown;
extern struct Triple g_frontendShutdownState;
extern s32 Cache_WaitForResourceLoads(struct ResourceLoadWorker *resourceLoadWorker);
extern void Cache_DrainAndCompactResources(s32);
extern void Node_OpenResourceArchive(u8 *name);
extern void Tsmos_SetIdleTimer(f32);
extern void Tsmos_SetTimerState(s32);
extern void Tsmos_ActivateControllerState(void);

void Tsmos_InitializeEuropeanFrontend(void) {
    s32 *selected;
    Cache_WaitForResourceLoads(&g_resourceCacheWorker);
    Cache_DrainAndCompactResources(0);
    Gfx_InitializeFrontendServices();
    ESmem_InitializeFrameHeaps(0x3000);
    SmSmngr_InitializeScreenManager(35, (s32)g_Level_GetScreenEventTableAddress);
    Node_OpenResourceArchive(s_frontendResourceArchiveNameEuX);
    SmpOverlay_RegisterOverlayClass();
    SmpFrameAnim_RegisterFrameAnimClass();
    SmpFade_RegisterFadeClass();
    SmpButton_RegisterButtonClass();
    SmpFlicker_RegisterFlickerClass();
    SmpSlider_RegisterSliderClass();
    SmpList_RegisterListClass();
    N64Eng_RegisterNumericWidgetClass();
    g_frontendTransitionCountdown = 60;
    Tsmos_SetIdleTimer(0.0f);
    Tsmos_SetTimerState(1);
    selected = &g_frontendShutdownState.z;
    *selected = 1;
    Tsmos_ActivateControllerState();
    g_frontendShutdownState.x = 0;
    Tsmos_SetModeOneFlag(2);
}
#endif
