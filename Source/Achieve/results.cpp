#include "Common/stagepreset.h"
#include "Common/runtime_declarations.h"
#include "include_asm.h"
#include "Common/level_goal.h"
#include "Render/material_color_and_fog_views.h"
#include "Achieve/achieve.h"
#include "Achieve/match_getresulttext.h"
#include "Common/playerprofiles.h"
#include "Ui/X_files/x_plus.h"
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/frontend_clock_state.h"
#include "Common/menulistscreen.h"
#include "Common/shared_menureply.h"
#include "Common/shared_gameslot.h"
#include "Common/menuselectionmessage.h"
#include "Achieve/achieve_openresultsfrontend.h"
#include "Ui/Tsmos/TSMOS.h"
#include "Common/selectionscreenstate.h"
#include "Common/shared_optionsscreen.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/menu_match_globals.h"
#include "Common/world.h"
#include "Common/resultsoptionsscreen.h"
#include "Achieve/achieve_advanceresultmodelpreview.h"
#include "Achieve/cplayerpreview_resetselectionmessagestate.h"
#include "Scene/cache_freememory.h"
#include "Frontend/menuimage.h"
#include "Frontend/menu_image.h"
#include "Match_reason/match_reason.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Frontend/pakinterface_setscreenphase.h"
#include "Achieve/achieve_address_symbols.h"
#include "Common/aiprofile.h"
#include "Common/multiplayeroptions.h"
#include "Achieve/achieve_dispatchresultsactorevent.h"
#include "Common/screen.h"



#include "Common/menu_text.h"
#include "Common/shared_worldfunc.h"
#include "Frontend/results_setup_text.h"
#include "types.h"
#include "Common/selectionscreenstate.h"
#include "Common/sharedplayer.h"
#include "Common/shared_gameslot.h"
#include "Common/rendercounters.h"
#include "Common/active.h"
#include "Common/menu_match_globals.h"
#include "Common/world.h"
#include "Achieve/modelpreviewscreen.h"
#include "Engine/defs.h"
#include "Engine/scene_findtrackedactors.h"
#include "Frontend/menuimage.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Achieve/achieve_createresultsscreen.h"
#include "Achieve/cplayerpreview_resetselectionmessagestate.h"
#include "Common/player_join_requests.h"
#include "Ui/X_files/x_stdio.h"
#include "Menu/Player_preview/Achieve/achieve.h"
/* Opens the level results screen: allocates the preview state, records the finished level for the winning
   player, unlocks the level-end achievements and fills the level name and status lines. */
static inline Shared_Game *Results_CurrentGame(void) { return &g_gameSettings; }
s32 Achieve_CreateResultsScreen(MenuWidget *menu) {
    char levelName[64];
    MenuWidget *item;
    Active *preset;
    SlotSelectionPlayerConfig *config;
    Shared_Game *game;
    CGameStatus *counters;
    s32 achievement;
    s32 time;
    s32 slot;
    s32 character;
    Shared_Game *nameGame;
    s32 *level;
    s32 i;

    g_resultsModelPreviewScreen = (ModelPreviewScreen *)Cache_AllocateMemory(sizeof(ModelPreviewScreen));
    ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window = menu;
    Widget_SetWidgetFlag08(menu, 0);
    Frontend_InitMenuImage(g_resultsModelPreviewScreen, 103, 0, 0, 0);
    Frontend_StartMenuImageTransition(g_resultsModelPreviewScreen);
    ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->cursor = 1;
    Node_FindWidgetByResourceId(menu, 619 + PREVIEW_ID_SHIFT)->alpha = 110;
    Node_FindWidgetByResourceId(menu, 624 + PREVIEW_ID_SHIFT)->alpha = 20;
    Node_FindWidgetByResourceId(menu, 621 + PREVIEW_ID_SHIFT)->alpha = 20;
    Node_FindWidgetByResourceId(menu, 640 + PREVIEW_ID_SHIFT)->alpha = 25;
    config = g_playerSettings;
    ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player = 0;
    for (i = 0; i < 4; i++) {
        if (config[i].active == 1) {
            ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player = i;
            break;
        }
    }
    CPlayerPreview_ResetSelectionMessageState();
    ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->badge = -1;
    game = &g_gameSettings;
    switch (game->controllerMode) {
    case 1:
        if (game->humanWon == 1) {
            Achieve_MarkLevelPlayed(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player);
            ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[0].model = -1;
            if (g_currentStagePreset->recorded != 0) {
                slot = g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].slot;
                if (Defs_TestBit(g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].slotLevels[slot], g_selectedLevelId) == 1) {
                    item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, 638 + PREVIEW_ID_SHIFT);
                    Widget_SetWidgetFlag08(item, 1);
                    item->alpha = 175;
                    item->text = RW_LOCALIZED_TEXT(g_resultPreviouslyCompletedText, g_resultPreviouslyCompletedTranslations, g_resultPreviouslyCompletedTranslations, Results_CurrentGame()->language);
                    goto completion_reward_done;
                }
            }
            {
                ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[0].model = Match_ApplyLevelCompletionReward(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player);
                ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[0].image = Match_GetResultText(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[0].model);
            }
completion_reward_done:
            ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->badge = -1;
            switch (g_selectedLevelId) {
            case 4:
                achievement = 45;
                break;
            case 9:
                achievement = 46;
                break;
            case 22:
                achievement = 47;
                break;
            case 35:
                achievement = 48;
                break;
            default:
                achievement = -1;
                break;
            }
            if (achievement != -1 && Defs_TestBit(g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].achievementFlags, achievement) == 0) {
                Defs_SetBitValue(g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].achievementFlags, achievement, 1);
                ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->badge = achievement;
                Achieve_UpdateUnlockTiers(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player);
            }
            if (g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].count >= 18) {
                Defs_SetBitValue(&g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].groupFlags, 1, 1);
            }
            if (g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].count >= 36) {
                Defs_SetBitValue(&g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].groupFlags, 2, 1);
            }
            if (g_selectedLevelId >= 35) {
                Defs_SetBitValue(g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].kindFlags, g_playerSettings[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].character, 1);
                XPlus_FillMemory(g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].levelFlags[0], 0, 5);
                character = Achieve_AwardCharacterCompletionUnlock(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player);
                nameGame = Results_CurrentGame();
                if (character >= 0) {
                    character = Key_FindKeyIndex(character);
                    XStdio_FormatBuffer(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->resultText, RW_LOCALIZED_TEXT(g_resultCharacterUnlockFormat, g_resultCharacterUnlockTranslations, g_resultCharacterUnlockTranslations, nameGame->language), RW_LOCALIZED_TEXT(g_resultCharacterHeadings[character].name[0], g_resultCharacterHeadingTranslations[character].name, g_resultCharacterHeadingTranslations[character].name, nameGame->language));
                    item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, 639 + PREVIEW_ID_SHIFT);
                    item->alpha = 175;
                    Widget_SetWidgetFlag08(item, 1);
                    item->text = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->resultText;
                }
            }
        } else {
            nameGame = Results_CurrentGame();
            XPlus_CopyString(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->resultText, resultsUnavailable(nameGame));
            item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, 639 + PREVIEW_ID_SHIFT);
            item->alpha = 175;
            Widget_SetWidgetFlag08(item, 1);
            item->text = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->resultText;
        }
        break;
    case 3:
        counters = &game->counters;
        if (counters->humanWon == 1) {
            Achieve_MarkLevelPlayed(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player);
            level = &g_selectedLevelId;
            preset = Achieve_CopyPreset(*level, 3, 0);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
            time = counters->timeLimit * 0.06666667f;
#else
            time = counters->timeLimit * g_resultTimeToSeconds;
#endif
            if (g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].times[*level] == 0) {
                g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].times[*level] = preset->time - time;
            } else if (preset->time - time < g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].times[*level]) {
                g_localPlayerProfiles[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player].times[*level] = preset->time - time;
            }
            if (g_selectedLevelId == 35) {
                item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, 639 + PREVIEW_ID_SHIFT);
                item->alpha = 175;
                Widget_SetWidgetFlag08(item, 1);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                item->text = RW_LOCALIZED_TEXT(g_resultTrialsCompleteText, g_resultTrialsCompleteTranslations, g_resultTrialsCompleteTranslations, g_languageIndex);
#else
                item->text = g_resultTrialsCompleteText;
#endif
            }
        } else {
            nameGame = Results_CurrentGame();
            XPlus_CopyString(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->resultText, resultsUnavailable(nameGame));
            item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, 639 + PREVIEW_ID_SHIFT);
            item->alpha = 175;
            Widget_SetWidgetFlag08(item, 1);
            item->text = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->resultText;
        }
        break;
    case 4:
        if (game->humanWon == 1) {
            Achieve_MarkLevelPlayed(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player);
            if (g_selectedLevelId == 35) {
                item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, 639 + PREVIEW_ID_SHIFT);
                item->alpha = 175;
                Widget_SetWidgetFlag08(item, 1);
                item->text = RW_LOCALIZED_TEXT(g_resultCampaignCompleteText, g_resultCampaignCompleteTranslations, g_resultCampaignCompleteTranslations, Results_CurrentGame()->language);
            }
        } else {
            nameGame = Results_CurrentGame();
            XPlus_CopyString(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->resultText, resultsUnavailable(nameGame));
            item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, 639 + PREVIEW_ID_SHIFT);
            item->alpha = 175;
            Widget_SetWidgetFlag08(item, 1);
            item->text = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->resultText;
        }
        break;
    }
    Achieve_UpdatePlayerPreviewStats();
    Achieve_ConfigureResultModelPreview();
    SmpButton_WrapButtonWidget(622 + PREVIEW_ID_SHIFT);
    SmpButton_WrapButtonWidget(623 + PREVIEW_ID_SHIFT);
    SmpButton_WrapButtonWidget(627 + PREVIEW_ID_SHIFT);
    Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(menu, 623 + PREVIEW_ID_SHIFT), 1);
    for (i = 0; i < 4; i++) {
        if (g_localPlayerProfiles[i].player >= 0 && g_localPlayerProfiles[i].fresh == 0) {
            Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(menu, 623 + PREVIEW_ID_SHIFT), 0);
            break;
        }
    }
    Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, 625 + PREVIEW_ID_SHIFT)->text = RW_LOCALIZED_TEXT(g_resultModeHeadingText, g_resultModeHeadingTranslations, g_resultModeHeadingTranslations, Results_CurrentGame()->language);
    item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, 626 + PREVIEW_ID_SHIFT);
    switch (g_currentResultMode.kind) {
    case 0:
        item->text = RW_LOCALIZED_TEXT(g_resultChallengeModeText, g_resultChallengeModeTranslations, g_resultChallengeModeTranslations, Results_CurrentGame()->language);
        break;
    case 1:
        item->text = RW_LOCALIZED_TEXT(g_resultTrialModeText, g_resultTrialModeTranslations, g_resultTrialModeTranslations, Results_CurrentGame()->language);
        break;
    default:
        item->text = RW_LOCALIZED_TEXT(g_resultTrialModeText, g_resultTrialModeTranslations, g_resultTrialModeTranslations, g_languageIndex);
        break;
    }
    item = Node_FindWidgetByResourceId(menu, 620 + PREVIEW_ID_SHIFT);
    Scene_CopyLevelName(&g_world, g_selectedLevelId, levelName, 63);
    XPlus_CopyString(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->nameText, XPlus_UppercaseString(levelName));
    item->text = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->nameText;
    ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->item24 = Node_FindWidgetByResourceId(menu, 628 + PREVIEW_ID_SHIFT);
    ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->ready = 1;
    g_frontendScreenStatus.status[7] = 1;
    g_resultsModelPreviewScreen->started = 0;
    Tsmos_DeactivateControllerState();
    return 0;
}

#include "types.h"
#include "Common/resident_event_handler.h"
#include "Achieve/modelpreviewscreen.h"
#include "Common/menu_model_preview.h"

#if defined(VERSION_DE)
#define PREVIEW_NUMBER_FORMAT g_resultPreviewNumberFormatDe
#elif defined(VERSION_US)
#define PREVIEW_NUMBER_FORMAT g_resultPreviewNumberFormatUs
#elif defined(VERSION_US_REV1)
#define PREVIEW_NUMBER_FORMAT k_AchieveEncodedBytes
#elif defined(VERSION_EU)
#define PREVIEW_NUMBER_FORMAT g_resultPreviewNumberFormatEu
#elif defined(VERSION_EU_X)
#define PREVIEW_NUMBER_FORMAT g_resultPreviewNumberFormatEuX
#endif

/* Fill the selected player's preview statistics and optional rank badge. */
void Achieve_UpdatePlayerPreviewStats(void) {
    MenuWidget *item, *lastItem;
    SlotSelectionPlayerConfig *record;
    s32 denominator;
    s32 player;
    s32 statIndex;
    s32 percent;

    player = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->player;
    statIndex = player;
    record = &g_playerSettings[player];
    item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, (629 + PREVIEW_ID_SHIFT));
    Widget_SetWidgetFlag08(item, 1);
    item->alpha = 150;
    item->value = g_characterPortraitRecords[Key_FindKeyIndex((s32) record->kind)].portrait;
    item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, (630 + PREVIEW_ID_SHIFT));
    Widget_SetWidgetFlag08(item, 1);
    item->alpha = 175;
    item->text = g_localPlayerProfiles[player].name;
    item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, (631 + PREVIEW_ID_SHIFT));
    Widget_SetWidgetFlag08(item, 1);
    item->alpha = 115;
    item->text = Match_UpdateRankText(player);
    item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, (632 + PREVIEW_ID_SHIFT));
    Widget_SetWidgetFlag08(item, 1);
    item->alpha = 175;
    XStdio_FormatBuffer(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->killsText, PREVIEW_NUMBER_FORMAT, record->kills);
    item->text = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->killsText;
    item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, (633 + PREVIEW_ID_SHIFT));
    Widget_SetWidgetFlag08(item, 1);
    item->alpha = 175;
    XStdio_FormatBuffer(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->scoreText, PREVIEW_NUMBER_FORMAT, record->score + record->total);
    item->text = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->scoreText;
    item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, (634 + PREVIEW_ID_SHIFT));
    Widget_SetWidgetFlag08(item, 1);
    item->alpha = 175;
    denominator = g_playerCountedShots[statIndex];
    percent = 0;
    if (denominator > 0) {
        percent = (s32) (g_playerHitCounts[statIndex] * 100) / denominator;
    }
    XStdio_FormatBuffer(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->ratioText, g_resultPercentFormat, percent);
    item->text = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->ratioText;
    item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, (635 + PREVIEW_ID_SHIFT));
    Widget_SetWidgetFlag08(item, 1);
    item->alpha = 175;
    lastItem=item;
    switch (g_currentResultMode.kind) {
    case 0: XStdio_FormatBuffer(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->otherText, PREVIEW_NUMBER_FORMAT, record->other); break;
    case 1: XStdio_FormatBuffer(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->otherText, PREVIEW_NUMBER_FORMAT, record->selected); break;
    default: XStdio_FormatBuffer(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->otherText, PREVIEW_NUMBER_FORMAT, 0); break;
    }
    lastItem->text = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->otherText;
    if (((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->badge != -1) {
        item = Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window, (636 + PREVIEW_ID_SHIFT));
        item->alpha = 150;
        Widget_SetWidgetFlag08(item, 1);
        item->value = g_resultAchievementBadgeImages[((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->badge];
    }
}

#undef PREVIEW_NUMBER_FORMAT

/* This function's literal pool (retained rodata): 0.3, 0.009, 3.0, -5.0, -100.0, -30.0. */
/* Shows the selected preview row's model: sets its image widget, scales the model (0.3 for the listed models,
   0.009 otherwise; 0.3 with a lower camera for 0x1390/0x1392), places it and resets the row's fade. */
void Achieve_ConfigureResultModelPreview(void) {
 SetupModelVector scale,offset,angle,position;
 s32 index, displacement, model;
 MenuWidget *item;
 ModelPreviewScreen *slot;
 index=((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->selected;
 displacement=index*20;
 model=((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[index].model;
 if(model>=0) {
  item=(MenuWidget *)Node_FindWidgetByResourceId(((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->window,RESULTS_MODEL_PREVIEW_IMAGE_WIDGET_ID);
  Widget_SetWidgetFlag08(item,1);
  item->alpha=175;
  item->image=((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[index].image;
  if ((u32)(model-5001)<2U || model==5023 || model==5024 || model==5057 || model==5016 || model==5053) {
   scale.value.x=g_resultPreviewLargeScale; scale.value.y=g_resultPreviewLargeScale; scale.value.z=g_resultPreviewLargeScale;
  } else { scale.value.x=g_resultPreviewSmallScale; scale.value.y=g_resultPreviewSmallScale; scale.value.z=g_resultPreviewSmallScale; }
  angle.value.x=0;angle.value.y=0;angle.value.z=0;
  position.value.x=0;position.value.y=g_resultPreviewRotationSpeedY;position.value.z=0;
  offset.value.x=0;offset.value.y=(&g_resultPreviewRotationSpeedY)[1];offset.value.z=g_resultPreviewCameraZ;
  if (model==5008 || model==5010) {
   offset.value.x=0;offset.value.y=(&g_resultPreviewCameraZ)[1];offset.value.z=g_resultPreviewCameraZ;
   scale.value.x=g_resultPreviewLowerCameraScale;scale.value.y=g_resultPreviewLowerCameraScale;scale.value.z=g_resultPreviewLowerCameraScale;
  }
  Frontend_InitModelPreviewTransform(&((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->modelWorkspace,0,scale.words,offset.words);
  Frontend_SetPreviewRotation(&((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->modelWorkspace,angle.words);
  Frontend_SetPreviewRotationSpeed(&((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->modelWorkspace,position.words);
  Model_SetPreviewModel(&((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->modelWorkspace,model);
  ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[index].state=0;
  ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[index].fade=10;
 }
}

#include "Common/resident_event_handler.h"
#include "Achieve/modelpreviewscreen.h"
#include "Common/menu_model_preview.h"
#include "types.h"
#include "Widget/widget_findwidgetatpoint.h"
#include "Achieve/achieve_address_symbols.h"
#include "Frontend/frontend.h"
#include "Achieve/match_updateranktext.h"
#if defined(VERSION_DE)
#define Preview_DrawMenuModelItem Frontend_DrawResultModelPreviewDe
#else
void Preview_DrawMenuModelItem(MenuModelItem *item);
#endif
void Achieve_ConfigureResultModelPreview(void);

/* Advances the selected row's model preview animation one step: the preview scale (fade) ramps up by 2
   toward 0x96 in state 0, holds in state 2 while the countdown (holdTicks) runs, and ramps back down to 10 in
   state 1, then moves the selection on. */
void Achieve_AdvanceResultModelPreview(void) {
    s32 selected;
    s32 nextFadeScale;
    s32 nextHoldTicks;
    s32 nextFadeOutScale;
    s32 previewState;
    s32 holdTicks;

    selected = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->selected;
    /* The screen state word read below has no shared field name yet. */
    if ((((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].model >= 0) && (((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->ready != 0)) {
        g_menuModelFillEnabled = 1;
        g_menuModelFillColor[3] = (f32) ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].fade;
        Preview_DrawMenuModelItem((void *)&((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->modelWorkspace);
        g_menuModelFillColor[3] = g_resultPreviewDefaultAlpha;
        previewState = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].state;
        g_menuModelFillEnabled = 0;
        switch (previewState) {                          /* irregular */
        case 0:
            nextFadeScale = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].fade + 2;
            ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].fade = nextFadeScale;
            if (nextFadeScale >= 151) {
                ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].fade = 150;
                ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].state = 2;
                if (selected <= 0 && ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected + 1].model > 0) {
                    ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].holdTicks = 150;
                    return;
                }
                ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].holdTicks = 911;
                return;
            }
            break;
        case 2:
            holdTicks = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].holdTicks;
            if (holdTicks != 911) {
                nextHoldTicks = holdTicks - 1;
                ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].holdTicks = nextHoldTicks;
                if (nextHoldTicks <= 0) {
                    ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].state = 1;
                    return;
                }
            }
            break;
        case 1:
            nextFadeOutScale = ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].fade - 2;
            ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].fade = nextFadeOutScale;
            if (nextFadeOutScale < 10) {
                ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->rows[selected].fade = 10;
                ((union ModelPreviewScreen *)g_resultsModelPreviewScreen)->selected += 1;
                Achieve_ConfigureResultModelPreview();
            }
            break;
        }
    }
}

/* Calls InitFrontendMenus and Tsmos_DeactivateControllerState, then SmXlate_SwitchScreen with 0x12. */
void Achieve_OpenResultsFrontend(void) {

#if defined(VERSION_EU)
Tsmos_InitializeEuropeanFrontend
#else
InitFrontendMenus
#endif
();
    Tsmos_DeactivateControllerState();
    SmXlate_SwitchScreen(18);
}

void Achieve_SelectPostResultScreen(void) {
    s32 next;
    CGameStatus *layout = &g_gameSettings.counters;
    layout->m_bCTFOn = 0;
    layout->m_bFragTagOn = 0;
    if (layout->humanWon == 1 && g_selectedLevelId >= 35) {
        switch (g_gameSettings.controllerMode) {
        case 4:
            next = 3;
            break;
        default:
            next = 3;
            break;
        case 1:
            next = 7;
            break;
        case 3:
            next = 3;
            break;
        }
    } else {
        next = 10;
    }
    SmXlate_SwitchScreen(next);
}

/* Resets the selection message state of g_resultsModelPreviewScreen: sets its first and second fields to -1 and its third field to zero. */
void CPlayerPreview_ResetSelectionMessageState(void) {
    struct SelectionMessageScreen *state = g_resultsModelPreviewScreen;

    state->first = -1;
    state->second = -1;
    state->third = 0;
}

/* Releases the object g_resultsModelPreviewScreen holds through Cache_FreeMemory, clears g_resultsModelPreviewScreen and returns zero. */
s32 CPlayerPreview_CloseSelectionMessageScreen(void) {
    Cache_FreeMemory(g_resultsModelPreviewScreen);
    g_resultsModelPreviewScreen = 0;
    return 0;
}

/* Event handler placeholder: ignores the event and returns zero. */
s32 Achieve_ResultScreenReturnZero(void) {
    return 0;
}

/* Handles event 1 on the screen g_resultsModelPreviewScreen: unless Frontend_GetMenuImageState reports its menu in state 1 it
   calls Achieve_AdvanceResultModelPreview; otherwise it advances the menu with Frontend_DrawMenuImage and Frontend_AdvanceMenuImageTransition and,
   once Frontend_GetMenuImageState reports 2, acts on the choice at 0x1C: choice 0 calls MarkMenuEventHandled, clears
   g_resultReplayPending and g_resultExitPending and leaves through SmXlate_SwitchScreen for screen 0xA unless g_campaignCompletionMenuEnabled is 1
   and g_selectedLevelId is at least 35, in which case it leaves for screen 7 when option g_gameControllerMode is 1
   and screen 3 otherwise; choice 1 calls Frontend_RequestScreenMode_AchieveUpdateresultsscreen(0), shows the window argument, stops the
   objects at g_frontendScreenStatus and 0x48 before it, releases g_world_AchieveUpdateresultsscreen through Scene_LoadLevelResources and sets the
   word at 0x17F0 of g_frontendScreenStatus to 8. Returns zero. */
s32 Achieve_UpdateResultsScreen(void *window, void *callbackContext, s32 event) {
    s32 state;
    char *object;
    s32 next;

    if (event != 1) {
        return 0;
    }
    state = Frontend_GetMenuImageState((Shared_OptionsScreen *)&g_resultsModelPreviewScreen->rules);
    if (state == event) {
        Frontend_DrawMenuImage(&g_resultsModelPreviewScreen->rules);
        Frontend_AdvanceMenuImageTransition(&g_resultsModelPreviewScreen->rules);
        if (Frontend_GetMenuImageState((Shared_OptionsScreen *)&g_resultsModelPreviewScreen->rules) != 2) {
            return 0;
        }
        if (g_resultsModelPreviewScreen->rules.locked != 0) {
            if (g_resultsModelPreviewScreen->rules.locked != state) {
                return 0;
            }
            Frontend_RequestScreenMode(0);
            Widget_SetWidgetFlag08(window, 1);
            object = &g_frontendScreenStatus;
            Pools_ResetActorPools(object, 0);
            Player_InitializePlayerPool(object - ((char *)&((Shared_MenuData *)0)->object - (char *)0), 0, 0);
            Scene_LoadLevelResources(&g_world, 0, 0);
            ((MatchMenuObjects *)(object))->transition = 8;
        } else {
            MarkMenuEventHandled();
            g_resultReplayPending = 0;
            g_resultExitPending = 0;
            if (g_campaignCompletionMenuEnabled == state && g_selectedLevelId >= 35) {
                switch (g_gameSettings.controllerMode) {
                case 4:
                    next = 3;
                    break;
                default:
                    next = 3;
                    break;
                case 1:
                    next = 7;
                    break;
                case 3:
                    next = 3;
                    break;
                }
            } else {
                next = 10;
            }
            SmXlate_SwitchScreen(next);
            return 0;
        }
    } else {
        Achieve_AdvanceResultModelPreview();
    }
    return 0;
}

/* Runs the screen g_resultsModelPreviewScreen each frame until stage 1 of g_selectionMessageStage: on its first frame it marks
   the word at 0x90, passes 0x272 to Menu_SetFocusedElement, or 0x273 when Widget_ListHasFlag100_AchieveUpdateresultsscreen
   reports zero for item 0x273 of the window argument, also 0x272 when g_campaignCompletionMenuEnabled is clear, and calls Tsmos_ActivateControllerState; then, once the
   reply pair ending at g_selectionMessageReply.ready is marked, it clears the mark and either hides the item at 0x24,
   clears the word at 0x1C0, calls MarkMenuEventHandled and leaves through SmXlate_SwitchScreen with the reply,
   or for a reply of -1 shows the item again and sets 0x1C0 to one. Returns zero. Written from the
   assembly; the conditional tests the zero case first. */
s32 Achieve_UpdateResultSelectionMessage(void *window) {
    s32 *pair;
    s32 marked;
    if (g_selectionMessageStage > 0) {
        return 0;
    }
    if (g_resultsModelPreviewScreen->started == 0) {
        g_resultsModelPreviewScreen->started = 1;
#if defined(VERSION_DE)
        Menu_SetFocusedElement(Widget_ListHasFlag100(Node_FindWidgetByResourceId(window, 623)) == 0 ? 623 : 622);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        Menu_SetFocusedElement(Widget_ListHasFlag100(Node_FindWidgetByResourceId(window, 627)) == 0 ? 627 : 626);
#elif defined(VERSION_EU_X)
        Menu_SetFocusedElement(Widget_ListHasFlag100(Node_FindWidgetByResourceId(window, 632)) == 0 ? 632 : 631);
#endif
        if (g_gameSettings.counters.humanWon == 0) {
#if defined(VERSION_DE)
            Menu_SetFocusedElement(622);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            Menu_SetFocusedElement(626);
#elif defined(VERSION_EU_X)
            Menu_SetFocusedElement(631);
#endif
        }
        Tsmos_ActivateControllerState();
    }
    pair = &g_selectionMessageReply.ready;
    marked = pair[0];
    if (marked == 1) {
        pair[0] = 0;
        if (pair[-1] != -1) {
            Widget_SetWidgetFlag08(g_resultsModelPreviewScreen->item, 0);
            g_resultsModelPreviewScreen->busy = 0;
            MarkMenuEventHandled();
            SmXlate_SwitchScreen(pair[-1]);
            return 0;
        }
        Widget_SetWidgetFlag08(g_resultsModelPreviewScreen->item, 1);
        g_resultsModelPreviewScreen->busy = marked;
    }
    return 0;
}

#if defined(VERSION_DE)
enum { MSG_BACK = 623, MSG_HIDE = 622, MSG_LEAVE = 627 };
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
enum { MSG_BACK = 627, MSG_HIDE = 626, MSG_LEAVE = 631 };
#else
enum { MSG_BACK = 632, MSG_HIDE = 631, MSG_LEAVE = 636 };
#endif

s32 Achieve_HandleResultsMenuChoice(void) {
    MarkMenuEventHandled();
    if (Frontend_GetMenuImageState((Shared_OptionsScreen *)&g_resultsModelPreviewScreen->rules) != 1) {
        g_frontendScreenStatus.status[7] = 0;
        switch (Menu_GetFocusedElementId()) {
        case MSG_HIDE:
            Frontend_StartMenuImageTransition(g_resultsModelPreviewScreen);
            g_resultsModelPreviewScreen->rules.locked = 0;
            break;
        case MSG_BACK:
            PAKInterface_SetScreenPhase(5);
            SmXlate_SwitchScreen(19);
            return 0;
        case MSG_LEAVE:
            Random_SetMenuChoiceResult(33);
            break;
        default:
            return 0;
        }
        return 0;
    }
    return 0;
}

/* Calls MarkMenuEventHandled with the arguments it was given and returns zero. */
s32 Achieve_AcknowledgeResultsEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

/* Calls the handler registered for event (tables g_resultsActorEventIds, g_resultsActorEventKinds, g_resultsActorEventHandlers). A row matches when its event equals event and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */

s32 Achieve_DispatchResultsActorEvent(ActorDefinitionHeader *actor, s32 event, s32 itemId, s32 value, s32 context) {
    ResultsActorEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_resultsActorEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_resultsActorEventHandlers;
        index = 0;
        do {
            if (g_resultsActorEventIds[index].value == event) {
                actor_kind = actor->character;
                table_kind = g_resultsActorEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(actor, event, itemId, value, context);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

const float g_resultPreviewLowerCameraScale = 0.3f;

/* Retained data for this translation unit. */

const float g_resultPreviewTransformConstants[6] = {
    0.3f, 0.009f, 3.0f, -5.0f,
    -1e+02f, -3e+01f,
};

const float g_resultModelPreviewByteMaxConstant[1] = {
    255.0f,
};
