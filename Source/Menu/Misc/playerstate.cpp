#include "Ai/Nav/Patrol/patrol.h"
#include "Engine/events.h"
extern s32 g_profileBlueBloodScoreLabel;
#include "Frontend/player_menu_records.h"
#include "Menu/cmenuprofile_opentimedplayerdialog.h"
#include "Menu/built_menu.h"
#include "Common/aiprofile.h"
#include "Common/shared_optionsscreen.h"
#include "Common/gameplay_settings.h"
#include "Menu/playersettings.h"
#include "Common/runtime_declarations.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/sharedplayer.h"
#include "Common/pakqueuestate.h"
#include "Common/gameplay_transition.h"
#include <platform_sdk.h>
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Menu/Misc/cmenuprofile_activatefirstconfirmingplayer.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Render/control_cycleactorsnapshotmode.h"
#include "Common/selectionscreenstate.h"
#include "Engine/control.h"
#include "Menu/Misc/Playerstate/cmenuprofile_activatefirstconfirmingplayer_symbols.h"
#include "include_asm.h"
#include "Common/gameplay_camera.h"
#include "Common/rendercounters.h"
#include "Menu/Misc/cmenuprofile_adjustgamespeedfactor.h"
#include "Engine/defs.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Common/triple.h"
#include "Menu/Misc/Playerstate/cmenuprofile_adjustgamespeedfactor_symbols.h"
#include "Common/shared_debugfield.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/shared_menuselection.h"
#include "Common/gameplay_movement.h"
#include "Menu/Misc/Playerstate/cmenuprofile_formatprofilequantitylabel_symbols.h"
#include "Menu/cmenuprofile_opentimedplayerdialog.h"
#include "Menu/Misc/cmenuprofile_opentimedplayerdialog.h"
#include "Common/Lone/g_pakprofileactiondialogresource.h"
#include "Common/sessionhandlerrow.h"
#include "Menu/Misc/Playerstate/cmenuprofile_opentimedplayerdialog_symbols.h"
#include "Menu/Pak/timer_cancelpendingoperation.h"
#include "Render/soundelement_playflatsound.h"
#include "Menu/menu_createmenufromtemplate.h"
#include "Ovlgame/player_startplayeranimation.h"
#include "Control/control.h"

/* Advances the frame timer g_profileConfirmationElapsedTime by g_frameElapsedTime and, once it reaches
   threshold g_profileGameSpeedPreview, clears a flag at g_gameSettings.counters+0x24 and reports the
   round over through Playerai_EndRound on the menu root g_playerViewRenderContext. */
void Playerai_EndRound(void *roundContext);

/** Runs Menu_AdjustValue on a byte in menuContext->owner->controls[0x83] and writes the result back into that byte. */
void CMenuProfile_ActivateFirstConfirmingPlayer(void) {
    StatusStep *status;
    PlayerSettings *settings;
    s32 i;
    s32 active;
    i = 7;
    status = g_gameSettingsRecordActiveFlagBase;
    for (; i >= 0; i--) {
        ((StatusView *)status)->active = 0;
        status--;
    }
    i = 0;
    active = 1;
    settings = g_playerSettings;
    for (; i < 4; i++) {
        if (Control_IsAButtonPressed(&g_controllerProfiles[i]) != 0) {
            settings[i].active = active;
            settings[i].selected = i;
            break;
        }
    }
}

ControllerProfile *CMenuProfile_FindConfirmingController(s32 *out) {
    s32 i;
    ControllerProfile *s;
    i = 0;
    s = g_controllerProfiles;
    while (i < 4) {
        if (Control_IsAButtonPressed(s) != 0) {
            *out = i;
            return s;
        }
        i++;
        s++;
    }
    *out = -1;
    return 0;
}

/* Counts the connected controllers; returns 0 as soon as one connected controller's player slot is not enabled. */
s32 CMenuProfile_CountReadyConnectedPlayers(void) {
    char *rosterRecord;
    s32 controllerIndex;
    s32 connectedCount;
    s32 controllerOffset;

    connectedCount = 0;
    controllerIndex = 0;
    rosterRecord = (char *)&g_gameSettings;
    controllerOffset = 0;
loop_1:
    if (*(s32 *) ((char *) g_controllerProfiles + controllerOffset) != 0) {
        connectedCount += 1;
        if (((FlaggedRosterView *)rosterRecord)->flag == 0) {
            return 0;
        }
    }
    rosterRecord += sizeof(Shared_PlayerSettingsRecord);
    controllerIndex += 1;
    controllerOffset += 548;
    if (controllerIndex >= 4) {
        return connectedCount;
    }
    goto loop_1;
}

/** Clears the global counter/flag g_profileConfirmationElapsedTime. */
void CMenuProfile_ResetRoundEndDelay(void) {
    g_profileConfirmationElapsedTime = 0;
}

s32 CMenuProfile_UpdateRoundEndDelay(void) {
    f32 time;
    CGameStatus *counters;

    time = g_profileConfirmationElapsedTime + g_frameElapsedTime;
    g_profileConfirmationElapsedTime = time;
    if ((120.0f) <= time) {
        counters = &g_gameSettings.counters;
        counters->teams = 0;
        Playerai_EndRound((char *)counters - offsetof(Shared_MenuData, game.counters));
        return 1;
    }
    return 0;
}

s32 CMenuProfile_SetFirstResultLabel(MenuBuildEntry *labelItem) {
    labelItem->resource = (s32)(&g_profileBlueBloodScoreLabel);
    return 0;
}

s32 CMenuProfile_SetSecondResultLabel(MenuBuildEntry *labelItem) {
    labelItem->resource = (s32)(&g_redBloodScoreText);
    return 0;
}

/* Always returns 0. */
s32 CMenuProfile_ControllerSelectionReturnZero(void) {
    return 0;
}

/** True if any of three flags inside the g_gameSettings.counters record are set. */
s32 CMenuProfile_HasRoundProgress(void) {
    CGameStatus *base = &g_gameSettings.counters;
    s32 result;

    result = 0;
    if ((base->round != 0) || (base->elapsed != 0) || (base->state != 0)) {
        result = 1;
    }
    return result;
}

s32 CMenuProfile_ResetPlayerControllerProfile(s32 entry, PlayerProfileMenuContext *menu) {
    PakMenuSlot **slot;

    g_gameSettings.counters.m_FragTagMode = 0;
    slot = &menu->widget;
    Control_DisableControllerPak((*slot)->controllerPort);
    Control_ResetControllerPak(*slot);
    Control_SetProfileMode(*slot, 1);
    menu->owner->playerStateDirty = 0;
    return 1;
}

s32 CMenuProfile_HasSavedRoundProgress(void) {
    s32 hasProgress;
    CGameStatus *state;

    state = &g_gameSettings.counters;
    hasProgress = 0;
    if ((state->round != 0) || (state->elapsed != 0) || (state->state != 0)) {
        hasProgress = 1;
    }
    return hasProgress;
}

s32 CMenuProfile_AdjustControllerSelection(void *menuItem, void *menuContext) {
    Player *p;
    u8 *bytep;
    s32 result;

    p = (void *)((PlayerProfileMenuContext *)menuContext)->owner;
    bytep = &p->profile->menuSelection;
    result = Menu_AdjustValue(menuContext, *bytep, 1, 0, 10, 0);
    *bytep = (u8)result;
    return 0;
}

const float g_CMenuProfile_AdjustGameSpeedFactorConstantWords[2] = {
    1.0f, 0.5f,
};

/** Always returns 0. */
s32 CMenuProfile_GameSpeedReturnZero(void) {
    return 0;
}

/* Returns 1 if any of g_gameSettings.counters's elapsed, state or round fields is nonzero, otherwise 0. */
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
s32 CMenuProfile_OpenPrimaryPlayerDialog(void *entry, PlayerDialogMenuContext *menuContext) {
    Obj1C *selectionPlayer;

    selectionPlayer = menuContext->selectionPlayer;
    selectionPlayer->alternateDialogFlag = 0;
    selectionPlayer->characterKindView->character = 0;
    Menu_OpenDialog((char *)&((GameplayCamera *)selectionPlayer->dialogParentBase)->messageList, &g_playerMenuDialogTable, selectionPlayer, selectionPlayer->dialogController, selectionPlayer->dialogParameter);
    return 1;
}

/* Sets menuContext->selectionPlayer's alternateDialogFlag flag and clears its characterKindView's characterKind, then forwards to Menu_OpenDialog. */
s32 CMenuProfile_OpenAlternatePlayerDialog(void *entry, PlayerDialogMenuContext *menuContext) {
    Obj1C *selectionPlayer;

    selectionPlayer = menuContext->selectionPlayer;
    selectionPlayer->alternateDialogFlag = 1;
    selectionPlayer->characterKindView->character = 0;
    Menu_OpenDialog((char *)&((GameplayCamera *)selectionPlayer->dialogParentBase)->messageList, &g_playerMenuDialogTable, selectionPlayer, selectionPlayer->dialogController, selectionPlayer->dialogParameter);
    return 1;
}

/* Steps the selection g_profileGameSpeedSelection through Menu_AdjustValue (a second step when Control_IsRightPressed or
   Control_IsAButtonPressed_Character reports the object's controller busy), then sets g_gameSettingsSpeedFactor to the chosen entry of the
   float table k_gameSpeedSelectionOffsets plus the offset in g_profileGameSpeedPreview, clamped between g_profileGameSpeedWrapLimit and (2.0f). */
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

struct Field;

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
#define PROFILE_QUANTITY_DEFAULT_LABELS_EU g_profileQuantityDefaultLabelsEuStorage
#else
#endif
#else
#endif

s32 CMenuProfile_FormatProfileQuantityLabel(struct Field *field, Shared_MenuHandle *holder) {
    s32 value = holder->owner->views5D8.view5D8_9.profile->quantity;
    char *text;

    if (value == 0) {
        field->text = g_profileQuantityZeroLabels;
    } else if (value == 10) {
        field->text = g_profileHandicapMaxLabels;
    } else {
        switch (holder->selection->index) {
        case 0:
        default:
#if defined(VERSION_EU) || defined(VERSION_EU_X)
            field->text = PROFILE_QUANTITY_DEFAULT_LABELS_EU;
#else
            field->text = g_profileQuantityDefaultLabels;
#endif
            break;
        case 1:
            field->text = g_profileQuantityChoiceLabels[0];
            break;
        case 2:
            field->text = g_profileQuantityChoiceLabels[1];
            break;
        case 3:
            field->text = g_profileQuantityChoiceLabels[2];
            break;
        }
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        text = field->text[g_languageIndex];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_profileAlternateQuantityFormat, value);
#else
        text = *field->text;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_profileQuantityFormat, value);
#endif
    }
    return 0;
}
#undef PROFILE_QUANTITY_DEFAULT_LABELS_EU

/* Restarts a round for the player passed in menuContext: clears the world timer flag g_pakPlayerMessagePending via
   Timer_ClearTimerFlag, cancels the active countdown sound through SoundElement_StopAudioExceptKey, then reallocates a
   fresh scoreboard entry via Menu_OpenDialog using menuContext's fields at 0x1C and 0x20, and always
   reports success. */

/** Runs a target's animation/state transition through Menu_AdjustValue and stores the new state. */
s32 CMenuProfile_ToggleProfileMode(void *menuItem, ProfileModeMenuContext *menuContext) {
    ProfileOptions *profileOptions;

    profileOptions = (ProfileOptions *)menuContext->selectionPlayer->characterKindView;
    profileOptions->profileMode = Menu_AdjustValue(menuContext, profileOptions->profileMode, 1, 0, 1, 1);
    return 0;
}

/** Forwards menuOwner through and menuContext as the first parameter, adding the g_profilePrimaryMenuResource record. */
s32 CMenuProfile_OpenPrimaryProfileMenu(void *entry, void *menuOwner, void *menuContext) {
    Menu_AllocateMenu(menuContext, menuOwner, &g_profilePrimaryMenuResource);
    return 1;
}

s32 CMenuProfile_BindSelectedDebugField(Shared_DebugWidget *widget, Shared_MenuHandle *handle) {
    widget->field = g_profileSelectionResources[handle->selection->index];
    return 0;
}

/* Forwards menuOwner through and menuContext as the first parameter, adding the g_profileSecondaryMenuResource record. */
s32 CMenuProfile_OpenSecondaryProfileMenu(void *entry, void *menuOwner, void *menuContext) {
    Menu_AllocateMenu(menuContext, menuOwner, &g_profileSecondaryMenuResource);
    return 1;
}

s32 CMenuProfile_UpdateProfileModeLabel(MenuBuildEntry *modeLabel, struct MenuCMenuProfileUpdateProfileModeLabel *menu) {
    switch (menu->owner->record->mode) {
    case 0:
        modeLabel->resource = (s32)(&g_profileModeZeroLabel);
        break;
    case 1:
        modeLabel->resource = (s32)(&g_profileMenuLabelWords);
        break;
    }
    return 0;
}

/** Forwards the pointed-to inner byte field on to Control_EnableControllerPak_CmenuprofileOpentimedplayerdialog. */
void CMenuProfile_EnableOwnerControllerPak(ControllerPortOwnerView *menuOwner) {
    Control_EnableControllerPak(menuOwner->controller->controllerPort);
}

void CMenuProfile_EnableControllerPakAndClearState(struct Shared_PakMenu *pakMenu) {
    Control_EnableControllerPak(pakMenu->owner->controllerPort);
    g_pakPlayerMessagePending = 0;
}

s32 CMenuProfile_HasProfileRoundProgress(void) {
    CGameStatus *state = &g_gameSettings.counters;

    return state->round != 0 || state->elapsed != 0 || state->state != 0;
}

s32 CMenuProfile_OpenTimedPlayerDialog(void *entry, Arg1Struct *menuContext) {
    s32 val1C;

    val1C = menuContext->player;
    Timer_ClearTimerFlag();
    ((s32 (*)(s32))SoundElement_StopAudioExceptKey)(-1);
    Menu_OpenDialog(&g_matchEndingTeamWheelClose, &g_pakProfileActionDialogResource, val1C, menuContext->controller, 0);
    return 1;
}

/** Return 0. */
s32 CMenuProfile_ProfileModeReturnZero(void) {
    return 0;
}

#if !(defined(VERSION_DE))
/* Handles the team option of a menu: unless Control_IsAButtonPressed_Character reports the confirm input, it steps the owner's team a field through Menu_StepValue between 1 and 18, applies it with Player_StartPlayerAnimation_CmenuprofileUpdateplayeranimationchoice and redraws it with Menu_SelectPreviewModel, returning zero; on confirm it applies the team, plays the sound g_profilePlayerAnimationChoices gives for the player's slot at 0x5E0 and shows the resource g_characterPreviewMenuRomResource_CmenuprofileUpdateplayeranimationchoice through Menu_AllocateMenu, returning one. */
s32 CMenuProfile_UpdatePlayerAnimationChoice(void *previewWidget, MenuCMenuProfileUpdatePlayerAnimationChoice *menu, void *menuContext) {
    SharedPlayer *player = menu->player;
    struct AiProfile *settings = player->views5D8.view5D8_7.settings;

    if (Control_IsAButtonPressed(menu->input) != 0) {
        Player_StartPlayerAnimation(player, settings->character);
        SoundElement_PlayFlatSound(g_profilePlayerAnimationChoices[player->views5DC.view5E0_10.slot].mode);
        Menu_AllocateMenu(menuContext, menu, g_characterPreviewMenuRomResource);
        return 1;
    }
    settings->character = Menu_StepValue(menu, settings->character, 1, 0, 18, 1);
    Player_StartPlayerAnimation(player, settings->character);
    Menu_SelectPreviewModel(previewWidget, 11, settings->character);
    return 0;
}
#endif
