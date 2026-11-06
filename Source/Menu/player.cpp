#include "Common/gameplay_settings.h"
#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include "Common/menulistscreen.h"
#include "types.h"
#include "Menu/player_initplayersettingsscreen.h"
#include "Ui/Tsmos/Smp/smp_button.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Common/runtime_declarations.h"
#include "Common/selectionscreenstate.h"
#include "Common/menu_overlay.h"
#include "Frontend/options_list_declarations.h"
#include "Ui/smp_slider.h"
#include "Common/animation.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Ui/smp_button.h"
#include "Menu/Player/player_initplayersettingsscreen_symbols.h"
#include "Common/screen.h"
#include "Menu/menu_advancefademeter.h"
#include "Common/shared_menureply.h"
#include "Common/menu_screen_elements.h"
#include "Menu/player_storealternateplayersettingsentry.h"
#include "Scene/cache_freememory.h"
#include "Menu/Player/player_storealternateplayersettingsentry_symbols.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/aiprofile.h"
#include "Common/menu_text.h"
#include "Menu/player_selectnextplayersettingsentry.h"
#include "Render/soundelement_playflatsound.h"
#include "Menu/Player/player_selectnextplayersettingsentry_symbols.h"
#include "Ui/X_files/x_stdio.h"
#include "Menu/Player/player_builditemlabellist_symbols.h"
#include "Common/measured.h"
#include "Common/unresolved_word_access_set.h"
#include "Common/unresolved_word_accesses.h"
#include "Common/sharedplayer.h"
#include "Common/argb_color.h"
#include <platform_sdk.h>
#include "Common/shared_optionsscreen.h"
#include "Common/multiplayeroptions.h"
#include "Common/loadout.h"
#include "Common/virtual_pager.h"
#include "Common/group.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/manager.h"
#include "Common/cartridgereadworker.h"
#include "Common/audio_voice_slots.h"
#include "Common/soundvoicepool.h"
#include "Common/lightdata.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/mtx.h"
#include "Common/particle_attachment_and_owner_views.h"
#include "Common/colorentry.h"
#include "Common/worldsortentry.h"
#include "Common/results.h"
#include "Common/round_session.h"
#include "Common/hud_effects.h"
#include "Common/albank_s.h"
#include "Common/sequence_timing.h"
#include "Common/alparam_s.h"
#include "Common/audio_effect_chain.h"
#include "Common/ospihandle_s.h"
#include "Common/osviscale.h"
#include "Common/ctx.h"
#include "Common/audio_loaddecodedsamples.h"
#include "Common/cheatcode.h"
#include "Common/note_state.h"
#include "Common/frontend_video_mode.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Common/label.h"
#include "Common/player_join_requests.h"
#include "Common/characterselectionroot.h"
#include "Common/numberpadscreen.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/weapon_unlock_presets.h"
#include "Common/resultsoptionsscreen.h"
#include "Common/match_settings.h"
#include "Common/menu_model_preview.h"
#include "Common/player_item_inventory.h"
#include "Common/objb.h"
#include "Menu/player_selectnextalternateplayersettingsentry.h"
#include "Menu/Player/player_selectnextalternateplayersettingsentry_symbols.h"
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/Player/player_openalternateplayersettingsscreen_symbols.h"
#include "Frontend/frontend.h"
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#if defined(VERSION_DE)
#define PLAYER_SETTINGS_ID(id) ((id) - 2)
#else
#define PLAYER_SETTINGS_ID(id) (id)
#endif

#define ST ((void **)g_playerSettingsScreen)
/* Builds the five player-settings controls and opens their parent screen. */
s32 Player_InitPlayerSettingsScreen(s32 root) {
    g_playerSettingsScreen = (struct StateMenuSelectPlayerSettingsEntry *)Cache_AllocateMemory(100);
    ST[0] = SmpFade_CreateFadeWidget(PLAYER_SETTINGS_ID(91), PLAYER_SETTINGS_ID(92));
    SmpButton_WrapButtonWidget(PLAYER_SETTINGS_ID(94));
    g_playerSettingsScreen->a = SmpButton_CreateListWidget(PLAYER_SETTINGS_ID(100), PLAYER_SETTINGS_ID(101));
    SmpButton_AppendListText(g_playerSettingsScreen->a, g_matchOptionsCursorNormalLabel[0]);
    SmpButton_AppendListText(g_playerSettingsScreen->a, g_playerSettingsPrimaryListLabels[0]);
    g_playerSettingsScreen->b = SmpButton_CreateListWidget(PLAYER_SETTINGS_ID(97), PLAYER_SETTINGS_ID(99));
    SmpButton_AppendListText(g_playerSettingsScreen->b, g_toggleListClearLabel[0]);
    SmpButton_AppendListText(g_playerSettingsScreen->b, g_toggleListSetLabel[0]);
    g_playerSettingsScreen->c = SmpSlider_CreateSliderWidget(PLAYER_SETTINGS_ID(102), PLAYER_SETTINGS_ID(103), 248);
    g_playerSettingsScreen->d = SmpSlider_CreateSliderWidget(PLAYER_SETTINGS_ID(106), PLAYER_SETTINGS_ID(107), 248);
    g_playerSettingsScreen->e = SmpButton_CreateListWidget(PLAYER_SETTINGS_ID(104), PLAYER_SETTINGS_ID(105));
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_playerSettingsSecondaryListLabels[0]);
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_playerSettingsTapText[0]);
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_playerSettingsMixedText[0]);
    SmpButton_WrapButtonWidget(PLAYER_SETTINGS_ID(96));
    ST[1] = SmpFlicker_CreateFlickerWidget(PLAYER_SETTINGS_ID(93), 110);
    ((s32 *)g_playerSettingsScreen)[9] = 3;
    ((s32 *)g_playerSettingsScreen)[8] = -1;
    ST[11] = Node_FindWidgetByResourceId(root, PLAYER_SETTINGS_ID(95));
    ((s32 *)g_playerSettingsScreen)[10] = 0;
    Player_SelectPlayerSettingsEntry(0);
    return 0;
}
#undef ST
#undef PLAYER_SETTINGS_ID
#else
#if defined(VERSION_EU_X)
#define EU_ID(eu, eux) (eux)
#else
#define EU_ID(eu, eux) (eu)
#endif

#define ST ((void **)g_playerSettingsScreen)
/* Builds the five player-settings controls (labels picked by the current language) and opens their parent screen. */
s32 Player_InitPlayerSettingsScreen(s32 root) {
    u8 *settings = (u8 *)&g_gameSettings;
    g_playerSettingsScreen = (struct StateMenuSelectPlayerSettingsEntry *)Cache_AllocateMemory(100);
    ST[0] = SmpFade_CreateFadeWidget(EU_ID(91, 95), EU_ID(92, 96));
    SmpButton_WrapButtonWidget(EU_ID(94, 98));
    g_playerSettingsScreen->a = SmpButton_CreateListWidget(EU_ID(100, 104), EU_ID(101, 105));
    SmpButton_AppendListText(g_playerSettingsScreen->a, g_matchOptionsCursorNormalLabelByLanguage[settings[1409]]);
    SmpButton_AppendListText(g_playerSettingsScreen->a, g_alternateSettingsModeLabels[settings[1409]]);
    g_playerSettingsScreen->b = SmpButton_CreateListWidget(EU_ID(97, 101), EU_ID(99, 102));
    SmpButton_AppendListText(g_playerSettingsScreen->b, g_optionsOffLabels[settings[1409]]);
    SmpButton_AppendListText(g_playerSettingsScreen->b, g_alternateSettingsControlLabels[settings[1409]]);
    g_playerSettingsScreen->c = SmpSlider_CreateSliderWidget(EU_ID(102, 106), EU_ID(103, 107), 248);
    g_playerSettingsScreen->d = SmpSlider_CreateSliderWidget(EU_ID(106, 110), EU_ID(107, 111), 248);
    g_playerSettingsScreen->e = SmpButton_CreateListWidget(EU_ID(104, 108), EU_ID(105, 109));
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_alternateSettingsHandLabels[settings[1409]]);
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_alternateSettingsFinalChoiceLabelsEu[settings[1409]]);
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_alternateSettingsFinalChoiceLabelsEuX[settings[1409]]);
    SmpButton_WrapButtonWidget(EU_ID(96, 100));
    ST[1] = SmpFlicker_CreateFlickerWidget(EU_ID(93, 97), 110);
    ((s32 *)g_playerSettingsScreen)[9] = 3;
    ((s32 *)g_playerSettingsScreen)[8] = -1;
    ST[11] = Node_FindWidgetByResourceId(root, EU_ID(95, 99));
    ((s32 *)g_playerSettingsScreen)[10] = 0;
    Player_SelectPlayerSettingsEntry(0);
    return 0;
}
#undef ST
#undef EU_ID
#endif

/* Stores entryIndex into its own g_playerSettingsSlotByteBase entry and pushes the five settings of slot entryIndex of the g_profileSlotSettingsPrimaryListSelection table into the objects g_playerSettingsScreen holds through SmpButton_SelectListEntry_PlayerInitplayersettingsscreen and SmpSlider_SetSliderItem. */
void Player_SelectPlayerSettingsEntry(s32 entryIndex) {
    u8 *slot = &g_gameSettings.playerSettings[entryIndex].slot;

    *slot = entryIndex;
    SmpButton_SelectListEntry(g_playerSettingsScreen->a, g_profileSlotSettingsPrimaryListSelection[entryIndex * 400]);
    SmpButton_SelectListEntry(g_playerSettingsScreen->b, g_profileSlotSettingsSecondaryListSelection[entryIndex * 400]);
    SmpSlider_SetSliderItem(g_playerSettingsScreen->c, g_profileSlotSettingsPrimarySliderItem[entryIndex * 400]);
    SmpSlider_SetSliderItem(g_playerSettingsScreen->d, g_profileSlotSettingsSecondarySliderItem[entryIndex * 400]);
    SmpButton_SelectListEntry(g_playerSettingsScreen->e, g_profileSlotSettingsExtraListSelection[entryIndex * 400]);
}

/* Reads five settings from the objects g_playerSettingsScreen holds through SmpButton_GetListSelection and SmpSlider_GetSliderItem into slot entryIndex of the g_profileSlotSettingsPrimaryListSelection table and copies them into the matching bytes of the entryIndex entry of g_playerSettings_Achieve. */
void Player_StorePlayerSettingsEntry(s32 entryIndex) {
    u8 *config;

    config = (u8 *)&g_playerSettings[entryIndex];
    g_profileSlotSettingsPrimaryListSelection[entryIndex * 400] = SmpButton_GetListSelection(g_playerSettingsScreen->a);
    do {
        g_profileSlotSettingsSecondaryListSelection[entryIndex * 400] = SmpButton_GetListSelection(g_playerSettingsScreen->b);
        g_profileSlotSettingsPrimarySliderItem[entryIndex * 400] = SmpSlider_GetSliderItem(g_playerSettingsScreen->c);
        g_profileSlotSettingsSecondarySliderItem[entryIndex * 400] = SmpSlider_GetSliderItem(g_playerSettingsScreen->d);
        g_profileSlotSettingsExtraListSelection[entryIndex * 400] = SmpButton_GetListSelection(g_playerSettingsScreen->e);
    } while (0);
    config[123] = g_profileSlotSettingsPrimaryListSelection[entryIndex * 400];
    config[125] = g_profileSlotSettingsSecondaryListSelection[entryIndex * 400];
    config[121] = g_profileSlotSettingsPrimarySliderItem[entryIndex * 400];
    config[122] = g_profileSlotSettingsSecondarySliderItem[entryIndex * 400];
    config[130] = g_profileSlotSettingsExtraListSelection[entryIndex * 400];
}

void Player_SelectAlternatePlayerSettingsEntry(s32 entryIndex);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
#define ID(id) ((id) + 4)
#else
#define ID(id) (id)
#endif

/* Builds the 0x50-byte confirm popup: its three button rows (ids 0x1C9, 0x1D1, 0x1CB) get the labels of the current language,
   the two fade windows ID(0x1CF)/ID(0x1CD) are created, and item ID(0x1C7) is kept as the cursor. Returns 0. */
s32 Player_OpenAlternatePlayerSettingsScreen(void *window) {
    u8 *settings;
    void *firstList;
    g_alternatePlayerSettingsScreen = Cache_AllocateMemory(80);
    SmpButton_WrapButtonWidget(ID(454));
    firstList = SmpButton_CreateListWidget(ID(457), ID(458));
    settings = (u8 *)&g_gameSettings;
    g_alternatePlayerSettingsScreen->listA = firstList;
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listA, g_matchOptionsCursorNormalLabelByLanguage[settings[1409]]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listA, g_alternateSettingsModeLabels[settings[1409]]);
    g_alternatePlayerSettingsScreen->listB = SmpButton_CreateListWidget(ID(465), ID(466));
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listB, g_optionsOffLabels[settings[1409]]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listB, g_alternateSettingsControlLabels[settings[1409]]);
    g_alternatePlayerSettingsScreen->panels[0] = SmpSlider_CreateSliderWidget(ID(463), ID(464), 0xFF);
    g_alternatePlayerSettingsScreen->panels[1] = SmpSlider_CreateSliderWidget(ID(461), ID(462), 0xFF);
    g_alternatePlayerSettingsScreen->listC = SmpButton_CreateListWidget(ID(459), ID(460));
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listC, g_alternateSettingsHandLabels[settings[1409]]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listC, g_alternateSettingsFinalChoiceLabelsEu[settings[1409]]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listC, g_alternateSettingsFinalChoiceLabelsEuX[settings[1409]]);
    SmpButton_WrapButtonWidget(ID(456));
    g_alternatePlayerSettingsScreen->window = Node_FindWidgetByResourceId(window, ID(455));
    g_alternatePlayerSettingsScreen->selection = 0;
    Player_SelectAlternatePlayerSettingsEntry(0);
    return 0;
}
#undef ID
#endif
#undef PLAYER_SETTINGS_ID
#undef ST
#undef EU_ID

/* Calls MarkMenuEventHandled; when Menu_GetFocusedElementId reports 0x60, passes a field of the object
   g_playerSettingsScreen points to to Player_StorePlayerSettingsEntry, then sets its word at 0x20 to -1 and calls SmpSlider_SetTransitionMode
   on its first word with 2. Returns zero. */
void Player_SelectAlternatePlayerSettingsEntry(s32 entryIndex) {
    u8 *slot = &g_gameSettings.playerSettings[entryIndex].slot;

    *slot = entryIndex;
    SmpButton_SelectListEntry(g_alternatePlayerSettingsScreen->listA, g_profileSlotSettingsPrimaryListSelection[entryIndex * 400]);
    SmpButton_SelectListEntry(g_alternatePlayerSettingsScreen->listB, g_profileSlotSettingsSecondaryListSelection[entryIndex * 400]);
    SmpSlider_SetSliderItem(g_alternatePlayerSettingsScreen->panels[0], g_profileSlotSettingsPrimarySliderItem[entryIndex * 400]);
    SmpSlider_SetSliderItem(g_alternatePlayerSettingsScreen->panels[1], g_profileSlotSettingsSecondarySliderItem[entryIndex * 400]);
    SmpButton_SelectListEntry(g_alternatePlayerSettingsScreen->listC, g_profileSlotSettingsExtraListSelection[entryIndex * 400]);
}

void Player_StoreAlternatePlayerSettingsEntry(s32 entryIndex) {
    u8 *config;

    config = (u8 *)&g_playerSettings[entryIndex];
    g_profileSlotSettingsPrimaryListSelection[entryIndex * 400] = SmpButton_GetListSelection(g_alternatePlayerSettingsScreen->listA);
    do {
        g_profileSlotSettingsSecondaryListSelection[entryIndex * 400] = SmpButton_GetListSelection(g_alternatePlayerSettingsScreen->listB);
        g_profileSlotSettingsPrimarySliderItem[entryIndex * 400] = SmpSlider_GetSliderItem(g_alternatePlayerSettingsScreen->panels[0]);
        g_profileSlotSettingsSecondarySliderItem[entryIndex * 400] = SmpSlider_GetSliderItem(g_alternatePlayerSettingsScreen->panels[1]);
        g_profileSlotSettingsExtraListSelection[entryIndex * 400] = SmpButton_GetListSelection(g_alternatePlayerSettingsScreen->listC);
    } while (0);
    config[123] = g_profileSlotSettingsPrimaryListSelection[entryIndex * 400];
    config[125] = g_profileSlotSettingsSecondaryListSelection[entryIndex * 400];
    config[121] = g_profileSlotSettingsPrimarySliderItem[entryIndex * 400];
    config[122] = g_profileSlotSettingsSecondarySliderItem[entryIndex * 400];
    config[130] = g_profileSlotSettingsExtraListSelection[entryIndex * 400];
}

s32 Player_FreePlayerSettingsScreen(void) {
    Cache_FreeMemory(g_playerSettingsScreen);
    g_playerSettingsScreen = 0;
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_EmptySettingsEntryHook(void) {
    return 0;
}

s32 Player_UpdatePlayerSettingsExit(void) {
    switch (SmpSlider_GetTransitionMode(((struct MenuStepState *)g_playerSettingsScreen)->menu)) {
    case 3:
        break;
    case 4:
        MarkMenuEventHandled();
        if (((struct MenuStepState *)g_playerSettingsScreen)->value != -1) {
            SmXlate_SwitchScreen(((struct MenuStepState *)g_playerSettingsScreen)->value);
        } else {
            Menu_ReturnToPreviousScreen();
        }
        break;
    }
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_EmptySettingsConfirmHook(void) {
    return 0;
}

s32 Player_ConfirmPlayerSettingsEntry(void) {
    struct MenuStepState *state;
    MarkMenuEventHandled();
#if defined(VERSION_DE)
    if (Menu_GetFocusedElementId() == 94) {
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    if (Menu_GetFocusedElementId() == 96) {
#elif defined(VERSION_EU_X)
    if (Menu_GetFocusedElementId() == 100) {
#endif
        Player_StorePlayerSettingsEntry(((struct MenuStepState *)g_playerSettingsScreen)->item);
        state = g_playerSettingsScreen;
        state->value = -1;
        SmpSlider_SetTransitionMode(state->menu, 2);
    }
    return 0;
}

/* Calls MarkMenuEventHandled, then sets a field of the object g_playerSettingsScreen points to to -1 and
   calls SmpSlider_SetTransitionMode on the object's first word with 2, returning zero. */



/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_playerSettingsEventIds, an actor kind at g_playerSettingsEventActorKinds and a handler at g_playerSettingsEventHandlers: the first row whose event equals eventId and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */


s32 Player_CancelPlayerSettingsEntry(void) {
    struct MenuStepState *state;

    MarkMenuEventHandled();
    state = g_playerSettingsScreen;
    state->value = -1;
    SmpSlider_SetTransitionMode(state->menu, 2);
    return 0;
}

s32 Player_SelectNextPlayerSettingsEntry(s32 element, s32 eventId, s32 eventPayload, s32 buttonState) {
    s32 nextItem;

    MarkMenuEventHandled();
    if (buttonState == 1) {
        Player_StorePlayerSettingsEntry(((struct MenuStepState *)g_playerSettingsScreen)->item);
        nextItem = ((struct MenuStepState *)g_playerSettingsScreen)->item + 1;
        ((struct MenuStepState *)g_playerSettingsScreen)->item = nextItem;
        if (nextItem >= 4) {
            ((struct MenuStepState *)g_playerSettingsScreen)->item = 0;
        }
        Player_SelectPlayerSettingsEntry(((struct MenuStepState *)g_playerSettingsScreen)->item);
        XStdio_FormatBuffer(((struct MenuStepState *)g_playerSettingsScreen)->text, RW_LOCALIZED_TEXT(g_playerSettingsSlotNumberFormat, g_playerSettingsSlotNumberTranslations, g_playerSettingsSlotNumberTranslations, g_languageIndex), ((struct MenuStepState *)g_playerSettingsScreen)->item + 1);
        ((struct MenuStepState *)g_playerSettingsScreen)->label->text = (void *) (((struct MenuStepState *)g_playerSettingsScreen)->text);
        SoundElement_PlayFlatSound(3713);
        return 0;
    }
    return 0;
}

s32 Player_SelectPreviousPlayerSettingsEntry(s32 element, s32 eventId, s32 eventPayload, s32 buttonState) {
    s32 previousItem;

    MarkMenuEventHandled();
    if (buttonState == 1) {
        Player_StorePlayerSettingsEntry(((struct MenuStepState *)g_playerSettingsScreen)->item);
        previousItem = ((struct MenuStepState *)g_playerSettingsScreen)->item - 1;
        ((struct MenuStepState *)g_playerSettingsScreen)->item = previousItem;
        if (previousItem < 0) {
            ((struct MenuStepState *)g_playerSettingsScreen)->item = 3;
        }
        Player_SelectPlayerSettingsEntry(((struct MenuStepState *)g_playerSettingsScreen)->item);
        XStdio_FormatBuffer(((struct MenuStepState *)g_playerSettingsScreen)->text, RW_LOCALIZED_TEXT(g_playerSettingsSlotNumberFormat, g_playerSettingsSlotNumberTranslations, g_playerSettingsSlotNumberTranslations, g_languageIndex), ((struct MenuStepState *)g_playerSettingsScreen)->item + 1);
        ((struct MenuStepState *)g_playerSettingsScreen)->label->text = (void *) (((struct MenuStepState *)g_playerSettingsScreen)->text);
        SoundElement_PlayFlatSound(3713);
        return 0;
    }
    return 0;
}

s32 Player_DispatchPlayerSettingsEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    PlayerSettingsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_playerSettingsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_playerSettingsEventHandlers;
        index = 0;
        do {
            if (g_playerSettingsEventIds[index].value == eventId) {
                actor = eventTarget;
                actor_kind = actor->resource;
                table_kind = g_playerSettingsEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventTarget, eventId, eventCode, eventValue, repeatCount);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#if defined(VERSION_DE)
enum { k_altPlayerSettingsHeadButtonId = 450, k_altPlayerSettingsWindowWidgetId = 451, k_altPlayerSettingsTailButtonId = 452, k_altPlayerSettingsPrimaryListId = 453, k_altPlayerSettingsPrimaryListItemId = 454, k_altPlayerSettingsModeListId = 455, k_altPlayerSettingsModeListItemId = 456, k_altPlayerSettingsSliderBId = 457, k_altPlayerSettingsSliderBChildId = 458, k_altPlayerSettingsSliderAId = 459, k_altPlayerSettingsSliderAChildId = 460, k_altPlayerSettingsToggleListId = 461, k_altPlayerSettingsToggleListItemId = 462 };
#else
enum { k_altPlayerSettingsHeadButtonId = 454, k_altPlayerSettingsWindowWidgetId = 455, k_altPlayerSettingsTailButtonId = 456, k_altPlayerSettingsPrimaryListId = 457, k_altPlayerSettingsPrimaryListItemId = 458, k_altPlayerSettingsModeListId = 459, k_altPlayerSettingsModeListItemId = 460, k_altPlayerSettingsSliderBId = 461, k_altPlayerSettingsSliderBChildId = 462, k_altPlayerSettingsSliderAId = 463, k_altPlayerSettingsSliderAChildId = 464, k_altPlayerSettingsToggleListId = 465, k_altPlayerSettingsToggleListItemId = 466 };
#endif

/* Builds the alternate player settings screen under a parent window: allocates its state, opens the three
   item lists and the two panels, opens the window, resets the selection through
   Player_SelectAlternatePlayerSettingsEntry(0) and returns zero. */
s32 Player_BuildItemLabelList(void *parent) {
    void *list;

    g_alternatePlayerSettingsScreen = Cache_AllocateMemory(80);
    SmpButton_WrapButtonWidget(k_altPlayerSettingsHeadButtonId);
    list = SmpButton_CreateListWidget(k_altPlayerSettingsPrimaryListId, k_altPlayerSettingsPrimaryListItemId);
    g_alternatePlayerSettingsScreen->listA = list;
    SmpButton_AppendListText(list, g_matchOptionsCursorNormalLabel[0]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listA, g_playerSettingsPrimaryListLabels[0]);
    list = SmpButton_CreateListWidget(k_altPlayerSettingsToggleListId, k_altPlayerSettingsToggleListItemId);
    g_alternatePlayerSettingsScreen->listB = list;
    SmpButton_AppendListText(list, g_toggleListClearLabel[0]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listB, g_toggleListSetLabel[0]);
    g_alternatePlayerSettingsScreen->panels[0] = SmpSlider_CreateSliderWidget(k_altPlayerSettingsSliderAId, k_altPlayerSettingsSliderAChildId, 0xFF);
    g_alternatePlayerSettingsScreen->panels[1] = SmpSlider_CreateSliderWidget(k_altPlayerSettingsSliderBId, k_altPlayerSettingsSliderBChildId, 0xFF);
    list = SmpButton_CreateListWidget(k_altPlayerSettingsModeListId, k_altPlayerSettingsModeListItemId);
    g_alternatePlayerSettingsScreen->listC = list;
    SmpButton_AppendListText(list, g_playerSettingsSecondaryListLabels[0]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listC, g_playerSettingsTapText[0]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listC, g_playerSettingsMixedText[0]);
    SmpButton_WrapButtonWidget(k_altPlayerSettingsTailButtonId);
    g_alternatePlayerSettingsScreen->window = Node_FindWidgetByResourceId(parent, k_altPlayerSettingsWindowWidgetId);
    g_alternatePlayerSettingsScreen->selection = 0;
    Player_SelectAlternatePlayerSettingsEntry(0);
    return 0;
}
#endif

/* Calls MarkMenuEventHandled, then passes -1 to Random_SetMenuChoiceResult when Menu_GetPreviousScreenOwner reports 0x16 for zero
   and 0xB otherwise, then calls Menu_ReturnToPreviousScreen. Returns zero. */


/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_alternatePlayerSettingsEventIds, an actor kind at g_alternatePlayerSettingsEventActorKinds and a handler at g_alternatePlayerSettingsEventHandlers: the first row whose event equals eventId and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */


s32 Player_FreeAlternatePlayerSettingsScreen(void) {
    Cache_FreeMemory(g_alternatePlayerSettingsScreen);
    g_alternatePlayerSettingsScreen = 0;
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_EmptyAlternateSettingsEntryHook(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_EmptyAlternateSettingsExitHook(void) {
    return 0;
}

s32 Player_ConfirmAlternatePlayerSettingsEntry(void) {
    MarkMenuEventHandled();
#if defined(VERSION_DE)
    if (Menu_GetFocusedElementId() == 452) {
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    if (Menu_GetFocusedElementId() == 456) {
#elif defined(VERSION_EU_X)
    if (Menu_GetFocusedElementId() == 460) {
#endif
        Player_StoreAlternatePlayerSettingsEntry(((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item);
        Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 22 ? -1 : 11);
        Menu_ReturnToPreviousScreen();
    }
    return 0;
}

s32 Player_CancelAlternatePlayerSettingsEntry(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 22 ? -1 : 11);
    Menu_ReturnToPreviousScreen();
    return 0;
}

s32 Player_SelectNextAlternatePlayerSettingsEntry(s32 element, s32 eventId, s32 eventPayload, s32 selectionPressed) {
    s32 selectedEntry;

    MarkMenuEventHandled();
    if (selectionPressed == 1) {
        Player_StoreAlternatePlayerSettingsEntry(((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item);
        selectedEntry = ((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item + 1;
        ((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item = selectedEntry;
        if (selectedEntry >= 4) {
            ((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item = 0;
        }
        Player_SelectAlternatePlayerSettingsEntry(((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item);
        XStdio_FormatBuffer(((struct StyleNextState *)g_alternatePlayerSettingsScreen)->text, RW_LOCALIZED_TEXT(g_playerSettingsSlotNumberFormat, g_playerSettingsSlotNumberTranslations, g_playerSettingsSlotNumberTranslations, g_languageIndex), ((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item + 1);
        ((struct StyleNextState *)g_alternatePlayerSettingsScreen)->label->text = (void *) (((struct StyleNextState *)g_alternatePlayerSettingsScreen)->text);
        return 0;
    }
    return 0;
}

s32 Player_SelectPreviousAlternatePlayerSettingsEntry(s32 element, s32 eventId, s32 eventPayload, s32 selectionPressed) {
    s32 selectedEntry;

    MarkMenuEventHandled();
    if (selectionPressed == 1) {
        Player_StoreAlternatePlayerSettingsEntry(((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item);
        selectedEntry = ((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item - 1;
        ((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item = selectedEntry;
        if (selectedEntry < 0) {
            ((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item = 3;
        }
        Player_SelectAlternatePlayerSettingsEntry(((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item);
        XStdio_FormatBuffer(((struct StyleNextState *)g_alternatePlayerSettingsScreen)->text, RW_LOCALIZED_TEXT(g_playerSettingsSlotNumberFormat, g_playerSettingsSlotNumberTranslations, g_playerSettingsSlotNumberTranslations, g_languageIndex), ((struct StyleNextState *)g_alternatePlayerSettingsScreen)->item + 1);
        ((struct StyleNextState *)g_alternatePlayerSettingsScreen)->label->text = (void *) (((struct StyleNextState *)g_alternatePlayerSettingsScreen)->text);
        return 0;
    }
    return 0;
}

s32 Player_DispatchAlternatePlayerSettingsEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    AlternatePlayerSettingsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_alternatePlayerSettingsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_alternatePlayerSettingsEventHandlers;
        index = 0;
        do {
            if (g_alternatePlayerSettingsEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->resource;
                table_kind = g_alternatePlayerSettingsEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventObject, eventId, eventPayload, eventValue, eventExtra);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

