#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MEASUREDRECAT0V1.H"
#include "COMMON/MEASURED.H"
#include "COMMON/MEASUREDRECAT14V4.H"
#include "COMMON/MEASUREDRECAT14V2.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ARGB_COLOR.H"
#include "COMMON/MATH_HELPERS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/SCREEN.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/LOADOUT.H"
#include "COMMON/OWNERRECAT8V2.H"
#include "COMMON/GROUP.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/MANAGER.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "COMMON/LIGHTDATA.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/MTX.H"
#include "COMMON/PARTICLE_ATTACHMENT_AND_OWNER_VIEWS.H"
#include "COMMON/COLORENTRY.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/RESULTS.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/OBJRECAT18V1.H"
#include "COMMON/ALPARAM_S.H"
#include "COMMON/ALDELAY28.H"
#include "COMMON/OSPIHANDLE_S.H"
#include <ultra64.h>
#include "COMMON/OSVISCALE.H"
#include "COMMON/CTX.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "COMMON/CHEATCODE.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"
#include "COMMON/LABEL.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/STATERECAT91.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/PLAYERRECAT64E.H"
#include "COMMON/OBJB.H"
#include "TYPES.H"
#include "FRONTEND/RESULTS_REFRESHTRIALCATALOGUEWIDGETS.H"
#include "FRONTEND/RESULTS_FILLPROFILEWEAPONROWS.H"
#include "FRONTEND/RESULTS_LOADTRIALCOMPLETIONFLAGS.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

extern struct ScreenFrontendAnimateResultsOptionsScreen *g_trialCatalogueScreen;

extern s32 g_selectionMessageReply[];

extern void SmXlate_SwitchScreen(s32);


extern void SmpFlicker_StartFlicker(struct FlickerStartView *object, s32 count);

extern void Tsmos_ActivateControllerState(void);

extern s32 SmpFlicker_IsFlickerIdle(struct FlickerActivityView *object);

extern void SmpFlicker_RestoreFlickerValue(struct FlickerRestoreView *source);

s32 Results_AnimateResultsOptionsScreen(void *unused0, void *unused1, s32 delta) {
    s32 clock;

    if (g_selectionMessageReply[1] == 1) {
        g_selectionMessageReply[1] = 0;
        if (g_selectionMessageReply[0] != -1) {
            g_trialCatalogueScreen->banner->alpha = 90;
            MarkMenuEventHandled();
            SmXlate_SwitchScreen(g_selectionMessageReply[0]);
            return 0;
        }
        g_trialCatalogueScreen->banner->alpha = 0xFF;
        g_trialCatalogueScreen->state = 9;
    }
    switch (g_trialCatalogueScreen->state) {
    case 1:
        g_trialCatalogueScreen->left->x += (u16)g_trialCatalogueScreen->leftSpeed;
        g_trialCatalogueScreen->right->x -= (u16)g_trialCatalogueScreen->rightSpeed;
        if (--g_trialCatalogueScreen->timer > 0) {
            break;
        }
        SoundElement_PlayFlatSound(3705);
        Widget_SetWidgetFlag08(g_trialCatalogueScreen->button, 1);
        SmpFlicker_StartFlicker(g_trialCatalogueScreen->prompt, 4);
        g_trialCatalogueScreen->state = 4;
        g_trialCatalogueScreen->timer = 4;
        break;
    case 2:
        g_trialCatalogueScreen->left->x -= (u16)g_trialCatalogueScreen->leftSpeed;
        g_trialCatalogueScreen->right->x += (u16)g_trialCatalogueScreen->rightSpeed;
        if (--g_trialCatalogueScreen->timer > 0) {
            break;
        }
        g_trialCatalogueScreen->state = 3;
        MarkMenuEventHandled();
        if (g_gameSettings.controllerMode == 4) {
            SmXlate_SwitchScreen(3);
        } else {
            SmXlate_SwitchScreen(7);
        }
        return 0;
    case 3:
        if (g_trialCatalogueScreen->requested == 0) {
            Tsmos_ActivateControllerState();
            g_trialCatalogueScreen->requested = 1;
        }
        break;
    case 4:
        g_trialCatalogueScreen->timer = RW_CLAMP(g_trialCatalogueScreen->timer - 1, 0, g_trialCatalogueScreen->timer);
        if (g_trialCatalogueScreen->timer <= 0 && SmpFlicker_IsFlickerIdle(g_trialCatalogueScreen->prompt) != 0) {
            SmpFlicker_RestoreFlickerValue(g_trialCatalogueScreen->prompt);
            g_trialCatalogueScreen->state = 3;
        }
        break;
    case 5:
        SoundElement_PlayFlatSound(3704);
        Widget_SetWidgetFlag08(g_trialCatalogueScreen->button, 0);
        switch (g_gameSettings.controllerMode) {
        case 1:
        case 3:
        case 4:
            Results_ShowTrialPreviewBanner();
        }
        Results_HideTrialCatalogueWidgets();
        g_trialCatalogueScreen->state = 2;
        g_trialCatalogueScreen->timer = 4;
        break;
    case 8:
        g_trialCatalogueScreen->state = 3;
        Results_HideTrialCatalogueWidgets();
        Random_SetMenuChoiceResult(11);
        return 0;
    case 9:
        g_trialCatalogueScreen->state = 3;
        Results_LoadTrialCompletionFlags();
        break;
    }
    if (g_trialCatalogueScreen->state == 3) {
        clock = g_trialCatalogueScreen->clock + delta;
        g_trialCatalogueScreen->clock = clock;
        if (g_selectionMessageReply[0] == -1) {
            g_trialCatalogueScreen->pulse->alpha = (u32)(Math_Cosf(clock * 0.005f) * 100.0f + 150.0f);
        }
    }
    return 0;
}
