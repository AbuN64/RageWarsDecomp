#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MENULISTSCREEN.H"
#include "MENU/MENU_CREATESOUNDOPTIONSSCREEN.H"
#include "UI/TSMOS/SMP/SMP_FADE.H"

#if defined(VERSION_DE) || defined(VERSION_EU_X)

extern struct MenuSliderWidget *SmpSlider_CreateSliderWidget(s32 sliderWidgetId, s32 childWidgetId, s32 initialTransition);
extern void SmpSlider_SetSliderItem(struct Scroll *scroll, s32 item);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);

s32 Menu_CreateSoundOptionsScreen(void) {
    s32 cue;
    void *memory;
    memory = Cache_AllocateMemory(28);
    g_soundOptionsScreen = memory;
#if defined(VERSION_DE)
    g_soundOptionsScreen->handle = SmpFade_CreateFadeWidget(106, 107);
    cue = SmpSlider_CreateSliderWidget(109, 110, 0xFF);
#elif defined(VERSION_EU_X)
    g_soundOptionsScreen->handle = SmpFade_CreateFadeWidget(112, 113);
    cue = SmpSlider_CreateSliderWidget(115, 116, 0xFF);
#else
    g_soundOptionsScreen->handle = SmpFade_CreateFadeWidget(108, 109);
    cue = SmpSlider_CreateSliderWidget(111, 112, 0xFF);
#endif
    g_soundOptionsScreen->cue0 = cue;
    SmpSlider_SetSliderItem(cue, g_gameSettings.volume[0]);
#if defined(VERSION_DE)
    cue = SmpSlider_CreateSliderWidget(111, 112, 0xFF);
#elif defined(VERSION_EU_X)
    cue = SmpSlider_CreateSliderWidget(117, 118, 0xFF);
#else
    cue = SmpSlider_CreateSliderWidget(113, 114, 0xFF);
#endif
    g_soundOptionsScreen->cue1 = cue;
    SmpSlider_SetSliderItem(cue, g_gameSettings.volume[1]);
#if defined(VERSION_DE)
    SmpButton_WrapButtonWidget(113);
    cue = SmpFlicker_CreateFlickerWidget(108, 110);
#elif defined(VERSION_EU_X)
    SmpButton_WrapButtonWidget(119);
    cue = SmpFlicker_CreateFlickerWidget(114, 110);
#else
    SmpButton_WrapButtonWidget(115);
    cue = SmpFlicker_CreateFlickerWidget(110, 110);
#endif
    g_soundOptionsScreen->state = 3;
    g_soundOptionsScreen->ambient = cue;
    g_soundOptionsScreen->reserved14 = -1;
    return 0;
}
#endif

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
/* Phase1 source candidate; contract holds and immutable inputs in per-function JSON. */
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "TYPES.H"







extern struct MenuSliderWidget *SmpSlider_CreateSliderWidget(s32 sliderWidgetId, s32 childWidgetId, s32 initialTransition);
extern void SmpSlider_SetSliderItem(struct Scroll *scroll, s32 item);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);

/* Allocates the HUD-cue object g_soundOptionsScreen, opens its handle for 0x6C/0x6D, starts its two timed cues at the volumes in g_gameSettingsVolumeBytes and its ambient loop, then arms state 3; returns 0. */
s32 Menu_CreateSoundOptionsScreen(void) {
    s32 cue;

    /* the hub's allocation helper returns its SelectionScreenState view; this unit keeps its own HudCue view */
    g_soundOptionsScreen = (struct HudCue *) Cache_AllocateMemory(28);
    g_soundOptionsScreen->handle = SmpFade_CreateFadeWidget(108, 109);
    cue = SmpSlider_CreateSliderWidget(111, 112, 0xFF);
    g_soundOptionsScreen->cue0 = cue;
    SmpSlider_SetSliderItem(cue, g_gameSettings.volume[0]);
    cue = SmpSlider_CreateSliderWidget(113, 114, 0xFF);
    g_soundOptionsScreen->cue1 = cue;
    SmpSlider_SetSliderItem(cue, g_gameSettings.volume[1]);
    SmpButton_WrapButtonWidget(115);
    cue = SmpFlicker_CreateFlickerWidget(110, 110);
    g_soundOptionsScreen->state = 3;
    g_soundOptionsScreen->ambient = cue;
    g_soundOptionsScreen->reserved14 = -1;
    return 0;
}
#endif
