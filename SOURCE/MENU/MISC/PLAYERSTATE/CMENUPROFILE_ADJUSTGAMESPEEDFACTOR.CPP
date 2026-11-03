#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/PLAYERSETTINGS.H"
#include "TYPES.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "MENU/MISC/CMENUPROFILE_ADJUSTGAMESPEEDFACTOR.H"
#include "ENGINE/DEFS.H"
#include "MENU/MENU_CREATEMENUFROMPARAMETERS.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"

/** Always returns 0. */
s32 CMenuProfile_GameSpeedReturnZero(void) {
    return 0;
}

/* Returns 1 if any of g_matchRoundCounters's elapsed, state or round fields is nonzero, otherwise 0. */




s32 CMenuProfile_HasDialogRoundProgress(void) {
    CGameStatus *s = &g_gameSettings.counters;
    s32 result;

    result = 0;
    if ((s->round != 0) || (s->elapsed != 0) || (s->state != 0)) {
        result = 1;
    }
    return result;
}

/* Clears menuContext->selectionPlayer's alternateDialogFlag flag and its characterKindView's characterKind, then forwards to Menu_OpenDialog. */


extern char g_playerMenuDialogTable[];







s32 CMenuProfile_OpenPrimaryPlayerDialog(void *unused0, PlayerDialogMenuContext *menuContext) {
    Obj1C *selectionPlayer;

    selectionPlayer = menuContext->selectionPlayer;
    selectionPlayer->alternateDialogFlag = 0;
    selectionPlayer->characterKindView->characterKind = 0;
    Menu_OpenDialog((char *)&((GameplayCamera *)selectionPlayer->dialogParentBase)->messageList, &g_playerMenuDialogTable, selectionPlayer, selectionPlayer->dialogController, selectionPlayer->dialogParameter);
    return 1;
}

/* Sets menuContext->selectionPlayer's alternateDialogFlag flag and clears its characterKindView's characterKind, then forwards to Menu_OpenDialog. */








s32 CMenuProfile_OpenAlternatePlayerDialog(void *unused0, PlayerDialogMenuContext *menuContext) {
    Obj1C *selectionPlayer;

    selectionPlayer = menuContext->selectionPlayer;
    selectionPlayer->alternateDialogFlag = 1;
    selectionPlayer->characterKindView->characterKind = 0;
    Menu_OpenDialog((char *)&((GameplayCamera *)selectionPlayer->dialogParentBase)->messageList, &g_playerMenuDialogTable, selectionPlayer, selectionPlayer->dialogController, selectionPlayer->dialogParameter);
    return 1;
}

/* Steps the selection g_profileGameSpeedSelection through Menu_AdjustValue (a second step when Control_IsRightPressed or
   Control_IsAButtonPressed_Character reports the object's controller busy), then sets g_gameSettingsSpeedFactor to the chosen entry of the
   float table k_gameSpeedSelectionOffsets plus the offset in g_profileGameSpeedPreview, clamped between g_profileGameSpeedWrapLimit and (2.0f). */










extern unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);

s32 CMenuProfile_AdjustGameSpeedFactor(void *menuItem, struct GameSpeedMenuValue *obj)
{
    f32 scale;

    g_profileGameSpeedSelection = Menu_AdjustValue(obj, g_profileGameSpeedSelection, 1, 0, 15, 0);
    if (((s32 (*)(s32))Control_IsRightPressed)(obj->controllerIndex) != 0 || Control_IsAButtonPressed(obj->controllerIndex) != 0) {
        Menu_AdjustValue(obj, g_profileGameSpeedSelection, 1, 0, 15, 0);
    }
    scale = k_gameSpeedSelectionOffsets[g_profileGameSpeedSelection] + g_profileGameSpeedPreview.scale;
    if (!(scale < g_profileGameSpeedWrapLimit)) {
        if (!(scale > (2.0f))) {
            if (scale < g_profileGameSpeedWrapLimit) {
                scale = g_profileGameSpeedWrapLimit;
            }
        } else {
            scale = (2.0f);
        }
    } else {
        scale = g_profileGameSpeedWrapLimit;
    }
    g_gameSettings.speedFactor = scale;
    return 0;
}

#include "COMMON/SHARED_DEBUGFIELD.H"
#include "COMMON/SHARED_GAMESLOT.H"
extern f32 g_profileGameSpeedDefault;
extern char *g_profileGameSpeedScaledLabel[], *g_profileGameSpeedDefaultLabel[];
extern char g_profileGameSpeedFormat[];


s32 CMenuProfile_UpdateGameSpeedLabel(Shared_DebugWidget *widget) {
    char *text;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Shared_Game *game = &g_gameSettings;
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    if (game->speedFactor == g_profileGameSpeedDefault) {
#else
    if (g_gameSettings.speedFactor == g_profileGameSpeedDefault) {
#endif
        widget->text = g_profileGameSpeedDefaultLabel;
    } else {
        widget->text = g_profileGameSpeedScaledLabel;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        text = widget->text[game->language];
#else
        text = *widget->text;
#endif
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(widget) - 3), g_profileGameSpeedFormat, g_profileGameSpeedSelection - 5);
    }
    return 0;
}
