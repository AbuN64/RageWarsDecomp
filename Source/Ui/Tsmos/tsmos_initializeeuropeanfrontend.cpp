#include "include_asm.h"
#include "Common/Lone/resource_request_queue.h"
#include "Common/gfx_initializefrontendservices.h"
#include "Common/menu_overlay.h"
#include "Math/smsmngr_initializescreenmanager.h"
#include "Ui/Quag/N64_Eng.h"
#include "Menu/smpframeanim_registerframeanimclass.h"
#include "Menu/smpfade_registerfadeclass.h"
#include "Menu/smp_slider.h"
#include "Menu/smplist_registerlistclass.h"
#include "Resmgr/frame_heap_lifetime.h"
#include "Ui/Tsmos/Smp/smp_flicker.h"
#include "Ui/Tsmos/TSMOS.h"

#if defined(VERSION_EU)
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/statepair.h"
#include "Resmgr/tsmos_setidletimer.h"
#include "Common/resourcelockstate.h"
#include "Common/shared_menureply.h"
#include "Ui/g_frontendshutdownstate.h"
#include "Engine/decmprsr.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Ui/tsmos_settimerstate.h"

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
    Tsmos_SetMenuModelFlag(2);
}
#endif
