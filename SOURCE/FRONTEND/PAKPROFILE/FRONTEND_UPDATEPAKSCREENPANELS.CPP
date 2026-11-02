#include "COMMON/SCREEN.H"
#include "include_asm.h"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/NAME.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/MATH_HELPERS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "FRONTEND/PAKINTERFACE_UPDATEPLAYERPANELANIMATIONS.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Animates the two menu panels through open, close and countdown states and updates the active team menu. */

extern void SmXlate_SwitchScreen(s32);
extern void Tsmos_ActivateControllerState(void);
extern void SmpFlicker_RestoreFlickerValue(struct FlickerRestoreView *source);
extern void SmpFlicker_StartFlicker(struct FlickerStartView *object, s32 count);

extern s32 SmpFlicker_IsFlickerIdle(struct FlickerActivityView *object);
s32 Frontend_UpdatePakScreenPanels(s32 unused0, s32 unused1, s32 event) {
    s32 readyState;
    s32 openFramesLeft;
    s32 closeFramesLeft;
    s32 unusedPanelState;
    s32 unusedPanelTimer;
    s32 unusedPanelResult;
    MenuWidget *closeTop;
    MenuWidget *closeBottom;
    MenuWidget *openTop;
    MenuWidget *openBottom;

    if (g_selectionMessageStage < 2) {
        readyState = g_pakProfileScreenState->ready;
        switch (readyState) {
        case 1:
            openTop = g_pakProfileScreenState->top;
            openTop->x = (u16) (openTop->x + (u16) g_pakProfileScreenState->topStep);
            openBottom = g_pakProfileScreenState->bottom;
            openBottom->x = (u16) (openBottom->x - (u16) g_pakProfileScreenState->bottomStep);
            openFramesLeft = g_pakProfileScreenState->timer - 1;
            g_pakProfileScreenState->timer = openFramesLeft;
            if (openFramesLeft <= 0) {
                SoundElement_PlayFlatSound(3705);
                /* title is the panel's item handle, kept untyped in the animation state */
                Widget_SetWidgetFlag08((SlotSelectionWidget *) g_pakProfileScreenState->title, 1);
                SmpFlicker_StartFlicker(g_pakProfileScreenState->music, 4);
                g_pakProfileScreenState->ready = 4;
                g_pakProfileScreenState->timer = 4;
            }
            break;
        case 2:
            closeTop = g_pakProfileScreenState->top;
            closeTop->x = (u16) (closeTop->x - (u16) g_pakProfileScreenState->topStep);
            closeBottom = g_pakProfileScreenState->bottom;
            closeBottom->x = (u16) (closeBottom->x + (u16) g_pakProfileScreenState->bottomStep);
            closeFramesLeft = g_pakProfileScreenState->timer - 1;
            g_pakProfileScreenState->timer = closeFramesLeft;
            if (closeFramesLeft <= 0) {
                g_pakProfileScreenState->ready = 3;
                MarkMenuEventHandled();
                SmXlate_SwitchScreen(g_pakProfileScreenState->focus);
                return 0;
            }
            break;
        case 3:
            Tsmos_ActivateControllerState();
            break;
        case 4:
            g_pakProfileScreenState->timer = RW_CLAMP(g_pakProfileScreenState->timer - 1, 0, g_pakProfileScreenState->timer);
            if ((g_pakProfileScreenState->timer <= 0) && (SmpFlicker_IsFlickerIdle(g_pakProfileScreenState->music) != 0)) {
                SmpFlicker_RestoreFlickerValue(g_pakProfileScreenState->music);
                g_pakProfileScreenState->ready = 3;
            }
            break;
        case 5:
            SoundElement_PlayFlatSound(3704);
            g_pakProfileScreenState->ready = 2;
            g_pakProfileScreenState->timer = 4;
            Widget_SetWidgetFlag08((SlotSelectionWidget *) g_pakProfileScreenState->title, 0);
            break;
        }
        if (g_pakProfileScreenState->ready == 3) PAKInterface_UpdatePlayerPanelAnimations(event);
    }
    return 0;
}
