#include "include_asm.h"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Resource ids of this screen are numbered per version: de -10, eu-x 4 relative to us. */
static inline s32 tabRes(s32 id) {
#if defined(VERSION_DE)
    return id - 10;
#elif defined(VERSION_EU_X)
    return id + 4;
#else
    return id;
#endif
}

s32 Menu_AnimateTabOptionsMenu(void) {
    s32 cinemaState;
    s32 transitionState;
    s32 openingFrames;
    s32 closingFrames;
    s32 lastPage;
    s32 pages;
    s32 remainingPages;
    MenuWidget *openingLeftTab;
    MenuWidget *openingRightTab;
    MenuWidget *closingLeftTab;
    MenuWidget *closingRightTab;
    Shared_OptionsScreen *timer;
    Shared_OptionsScreen *finish;
    s32 *ready;

    if (g_selectionMessageStage <= 0) {
        if ((Frontend_GetMenuImageState(g_optionsShortcutScreen) != 1) && ((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->state) == 0)) {
            (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->state) = 1;
            Tsmos_ActivateControllerState();
            return 0;
        }
        cinemaState = g_cinemaSequenceState->state3C;
        if ((cinemaState == 1) && (Cinema_IsSequenceInWindow() == cinemaState)) {
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->prompt), 0);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->footer), 0);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rumbleIcon), 0);
            g_cinemaSequenceState->state3C = 0;
        }
        ready = &g_selectionMessageReply.ready;
        if (*ready == 1) {
            *ready = 0;
            if (g_selectionMessageReply.value != -1) {
                Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pakIcon), 0);
                Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->header), 0);
                MarkMenuEventHandled();
                SmXlate_SwitchScreen(g_selectionMessageReply.value);
                return 0;
            }
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pakIcon), 1);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->header), 1);
            Menu_SetFocusedElement(tabRes(893));
            goto block_11;
        }
block_11:
        transitionState = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->page);
        switch (transitionState) {
        case 1:
            openingLeftTab = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->leftTab);
            openingLeftTab->x = (u16) (openingLeftTab->x + (u16)(((Shared_OptionsScreen *)(g_optionsShortcutScreen))->leftStep));
            openingRightTab = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rightTab);
            openingRightTab->x = (u16) (openingRightTab->x - (u16)(((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rightStep));
            openingFrames = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pages) - 1;
            (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pages) = openingFrames;
            if (openingFrames <= 0) {
                Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->marker), 1);
                Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pakIcon), 1);
                SmpFlicker_StartFlicker((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->title), 4);
                finish = (Shared_OptionsScreen *)g_optionsShortcutScreen;
                finish->page = 4;
                finish->pages = 4;
            }
        case 3:
        default:
            break;
        case 2:
            closingLeftTab = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->leftTab);
            closingLeftTab->x = (u16) (closingLeftTab->x - (u16)(((Shared_OptionsScreen *)(g_optionsShortcutScreen))->leftStep));
            closingRightTab = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rightTab);
            closingRightTab->x = (u16) (closingRightTab->x + (u16)(((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rightStep));
            closingFrames = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pages) - 1;
            (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pages) = closingFrames;
            if (closingFrames <= 0) {
                g_playerViewRenderContext.pause = 0;
                (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->page) = 3;
                Pools_ResetActorPools(&g_playerViewRenderContext.object, 0);
                Player_InitializePlayerPool(&g_playerViewRenderContext, 0, 0);
                Scene_LoadLevelResources(&g_world, 0, 0);
                if (Cache_GetResourceActivityState() == 0) {
                    Cache_SetResourceActivityState(1U);
                }
                g_playerViewRenderContext.stage = 8;
                MarkMenuEventHandled();
                SmXlate_SwitchScreen((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->selection));
                return 0;
            }
            break;
        case 4:
            timer = (Shared_OptionsScreen *)g_optionsShortcutScreen;
            pages = timer->pages;
            lastPage = pages - 1;
            if (lastPage >= 0) {
                remainingPages = pages - (pages >= lastPage);
            } else {
                remainingPages = 0;
            }
            timer->pages = remainingPages;
            if (((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pages) <= 0) && (SmpFlicker_IsFlickerIdle((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->title)) != 0)) {
                SmpFlicker_RestoreFlickerValue((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->title));
                (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->page) = 3;
            }
            break;
        case 5:
            SoundElement_PlayFlatSound(3704);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->marker), 0);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pakIcon), 0);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->footer), 1);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rumbleIcon), 1);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->prompt), 1);
            finish = (Shared_OptionsScreen *)g_optionsShortcutScreen;
            finish->page = 2;
            finish->pages = 4;
            break;
        }
        if ((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->page) != 3) {
            return 0;
        }
    }
    return 0;
}
