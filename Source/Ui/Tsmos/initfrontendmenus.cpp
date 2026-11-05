#include "include_asm.h"
#include "Common/Lone/resource_request_queue.h"
#include "Common/Lone/g_languageindex.h"
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

#if defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_DE) || defined(VERSION_EU_X)
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/statepair.h"
#include "Resmgr/tsmos_setidletimer.h"
#include "Common/widget_texture_retention.h"
#include "Common/resourcelockstate.h"
#include "Common/shared_menureply.h"
#include "Ui/g_frontendshutdownstate.h"
#include "Engine/decmprsr.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Ui/tsmos_settimerstate.h"

void InitFrontendMenus(void) {
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
    g_frontendShutdownState.z = 1;
    Tsmos_ActivateControllerState();
    g_frontendShutdownState.x = 0;
    Tsmos_SetMenuModelFlag(2);
#if defined(VERSION_DE)
    Node_LoadLanguageStringsIfAny(0);
#elif defined(VERSION_EU_X)
    Node_LoadLanguageStringsIfAny(g_languageIndex);
#endif
}
#endif
