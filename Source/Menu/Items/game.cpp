#include "Menu/built_menu.h"
extern s32 g_twoPlayerLayoutVerticalText;
#include "include_asm.h"
#include "Menu/player_settings_text.h"
#include "types.h"
#include "Menu/Items/game_and_player_options.h"
#include "Common/game_session.h"
#include "Common/shared_gameslot.h"
#include <platform_sdk.h>
#include "Common/runtime_declarations.h"
#include "Common/sessionhandlerrow.h"
#include "Menu/Items/items_cyclescenemask.h"
#include "Render/setn64_updatefadetransition.h"
#include "Menu/Items/menu_value_and_line_text.h"
#include "Engine/defs.h"
#include "Common/textlayermetrics.h"
#include "Common/triple.h"
#include "Common/pak_enter_player_options.h"
#include "Common/frontend_video_mode.h"
#include "Frontend/screen_video_mode.h"
#include "Data/rest_source_records.h"
#include "Frontend/screen.h"
#include "Game/game.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/effectrender.h"
#include "Common/pakqueuestate.h"
#include "Menu/Items/Game/game_symbols.h"
#if ((!(defined(VERSION_EU) || defined(VERSION_EU_X))))
#include "Common/gameplay_settings.h"
#endif
#include "Menu/menu_event_handlers.h"

/* Updates the selected menu option in response to the current input state. */

/* Replaces a field of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 8, 8, 0xF8 and 0, and returns zero. */
#if defined(VERSION_EU)
/* Points an option field at the holder's owner settings value (or the defaults g_playerPartnerNameFallback) as a signed offset from 128 in steps of eight, using the text g_playerOptionStickHorizontalNormalText for zero and otherwise the text g_playerOptionStickHorizontalStepText formatted with g_playerMenuStepFormatGerman for a positive or g_fmtSpaceDec_Playeroption for a negative step into the last four characters of the field text (the length Menu_CountLineChars reports), returning zero. */
#elif defined(VERSION_EU_X)
#endif

#if defined(VERSION_EU)
/* Replaces a field of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 8, 8, 0xF8 and 0, and returns zero. */
#elif defined(VERSION_EU_X)
#endif

#if defined(VERSION_EU)
/* Picks the label for each of the eight option rows (ids 2..9): the first text when the row's flag is set, else the second. */
typedef struct { s32 id; u8 pad4[0x10]; char ***text; } OptionRowEu;
#endif
#if defined(VERSION_EU_X)
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)

/* Fills the record's eight-byte name from the language table the record's slot selects: slots 0 (and any
   slot out of range) to 3 pick the partner suffix, name prefix, localized suffix and name suffix tables; slots 4 to 7 leave the name alone. */
void Items_CopyDefaultLocalizedPlayerName(Shared_PlayerSettingsRecord *record) {
    s32 i;
    Shared_Game *game;

    switch ((s8)record->slot) {
    default:
    case 0:
        i = 0;
        game = &g_gameSettings;
        do {
            record->name[i] = g_playerPartnerSuffixByLanguage[game->language][i];
            i++;
        } while (i < 8);
        break;
    case 1:
        i = 0;
        game = &g_gameSettings;
        do {
            record->name[i] = g_playerNamePrefixByLanguage[game->language][i];
            i++;
        } while (i < 8);
        break;
    case 2:
        i = 0;
        game = &g_gameSettings;
        do {
            record->name[i] = g_localizedPlayerNameSuffixes[game->language][i];
            i++;
        } while (i < 8);
        break;
    case 3:
        i = 0;
        game = &g_gameSettings;
        do {
            record->name[i] = g_playerNameSuffixByLanguage[game->language][i];
            i++;
        } while (i < 8);
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        break;
    }
}
#endif

#if defined(VERSION_US_REV1)
unsigned int g_gameItemsLayoutWords[3] = {
    0x00000014, 0x00000019, 0x00000005,
};
#endif

#if defined(VERSION_US)
struct {
    unsigned int words0[1];
    char text1[8];
} g_menuItemStatusTextStorage = {
    {
        0x00001452, 0x41585F50, 0x555F5354,
    },
    "AX_PU_ST",
};
#endif

#if defined(VERSION_DE)
char g_itemsConstantWords[12] =
    "d\000\000\000 %3d\000\000\000";
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
const float g_Player_DrawPulsingMenuSpriteConstantWords_us_rev1[1] = {
    0.5f,
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)

#if defined(VERSION_US)
extern const float g_Player_DrawPulsingMenuSpriteConstantWords_us[1];
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_ammoCountFormat[8] =
    " %03d\000\000\000";
#endif
#endif

#if defined(VERSION_US)

#endif

#if defined(VERSION_US_REV1)

#endif

extern const char g_fmtDecPadShort[5];



#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_US_REV1)
const float g_Player_DrawPulsingMenuSpriteConstantWords_us_rev1[1] = {
    0.5f,
};
#endif
#endif

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))

#if defined(VERSION_US)
extern const float g_Player_DrawPulsingMenuSpriteConstantWords_us[1];
#endif
#endif

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_ammoCountFormat[8] =
    " %03d\000\000\000";
#endif
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
extern const char g_fmtSpaceWidePaddedDec[6];
#endif

#if defined(VERSION_DE)
/* Resets the options record g_gameSettings (COptions_t) to its defaults: sound, opacity, cheats, battle
   limits, the ten multiplayer weapons, the training levels and every player's options. */
void Items_ResetGameOptions(COptions *options) {
    s32 i;
    options->stereo = 1;
    options->musicVolume = 128;
    options->sfxVolume = 250;
    options->speechVolume = 0xFF;
    options->realOpacity = 128;
    options->opacity = options->realOpacity;
    options->lightingGamma = 0;
    options->difficulty = 16;
    options->cheatFlags = 0;
    options->cheatEnabledFlags = 0;
    options->cheatFlags = 0x04000000;
    options->cheatEnabledFlags = 0x04000000;
#if defined(VERSION_DE)
    options->blood = 0;
#else
    options->blood = 1;
#endif
    options->debug = 0;
    options->cheatEnabledFlags = 0xFFFFFFFF;
    options->twoPlayerScreenPref = 0;
    options->resolution = 0;
    options->blTimedGame = 10;
    options->blFragLimit = 10;
    options->blFlagLimit = 10;
    options->blTagLimit = 10;
    options->blFriendlyFire = 1;
    options->blLevel = 0;
    options->blLevelTextureSet = 0;
    options->blCrosshairs = 1;
    options->multiplayerSpeedScaler = 1.0f;
    for (i = 0; i < 10; i++) {
        options->multiWeapon[i] = 1;
    }
    options->singleTrainingLevel = 0;
    options->singleTrainingNoOfLaps = 3;
    options->multiTrainingLevel = 0;
    options->multiTrainingNoOfLaps = 3;
    for (i = 0; i < 8; i++) {
        PlayerOptions_Reset(&options->multiPlayerOptions[i], i);
    }
    PlayerOptions_Reset(&options->singlePlayerOptions, 0);
    options->singlePlayerOptions.active = 1;
    options->multiPlayer = 0;
    options->maxPlayers = 1;
    options->overallGameType = 0;
}
#endif

#if !(defined(VERSION_DE))
/* Resets the options record g_gameSettings (COptions_t) to its defaults: sound, opacity, cheats, battle
   limits, the ten multiplayer weapons, the training levels and every player's options. */
void Items_ResetGameOptions(COptions *options) {
    s32 i;
    options->stereo = 1;
    options->musicVolume = 128;
    options->sfxVolume = 250;
    options->speechVolume = 0xFF;
    options->realOpacity = 128;
    options->opacity = options->realOpacity;
    options->lightingGamma = 0;
    options->difficulty = 16;
    options->cheatFlags = 0;
    options->cheatEnabledFlags = 0;
    options->cheatFlags = 0x04000000;
    options->cheatEnabledFlags = 0x04000000;
#if defined(VERSION_DE)
    options->blood = 0;
#else
    options->blood = 1;
#endif
    options->debug = 0;
    options->cheatEnabledFlags = 0xFFFFFFFF;
    options->twoPlayerScreenPref = 0;
    options->resolution = 0;
    options->blTimedGame = 10;
    options->blFragLimit = 10;
    options->blFlagLimit = 10;
    options->blTagLimit = 10;
    options->blFriendlyFire = 1;
    options->blLevel = 0;
    options->blLevelTextureSet = 0;
    options->blCrosshairs = 1;
    options->multiplayerSpeedScaler = 1.0f;
    for (i = 0; i < 10; i++) {
        options->multiWeapon[i] = 1;
    }
    options->singleTrainingLevel = 0;
    options->singleTrainingNoOfLaps = 3;
    options->multiTrainingLevel = 0;
    options->multiTrainingNoOfLaps = 3;
    for (i = 0; i < 8; i++) {
        PlayerOptions_Reset(&options->multiPlayerOptions[i], i);
    }
    PlayerOptions_Reset(&options->singlePlayerOptions, 0);
    options->singlePlayerOptions.active = 1;
    options->multiPlayer = 0;
    options->maxPlayers = 1;
    options->overallGameType = 0;
}
#endif

/* The out-of-line copy of CPlayerOptions_t's reset (PlayerOptions_Reset). */
void Items_ResetPlayerSettings(CPlayerOptions *player, s8 controller) {
    PlayerOptions_Reset(player, controller);
}

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))

/* Copies an eight-byte default name into a player-settings record, choosing the preset by the record's slot:
   slots 1 to 3 use their own tables, slots 4 to 7 leave the record unchanged, and any other slot uses the first table. */
void Items_SetDefaultPlayerName(u8 *recordBytes) {
    Shared_PlayerSettingsRecord *record = (Shared_PlayerSettingsRecord *)recordBytes;
    const u8 *preset;
    s32 i;

    switch ((s8)record->slot) {
    case 1:
        preset = (const u8 *)g_defaultPlayerNames[1];
        break;
    case 2:
        preset = (const u8 *)g_defaultPlayerNames[2];
        break;
    case 3:
        preset = (const u8 *)g_defaultPlayerNames[3];
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        return;
    case 0:
    default:
        preset = (const u8 *)g_defaultPlayerNames[0];
        break;
    }
    for (i = 0; i < 8; i++) {
        record->name[i] = preset[i];
    }
}
#endif

/* Updates the menu item visibility and text for the current configuration. */

void Items_ResetScreenModeFadeCooldown(void) {
    g_controllerPakProbeState = 0.0f;
}

char *Items_GetPlayerSettingsText(struct PlayerSettingsTextHolder *actor) {
    char *name = g_playerPartnerNameFallback.text;

    if (actor->owner != 0 && actor->owner->settings != 0) {
        name = actor->owner->settings->text;
    }
    return name;
}

s32 Items_CycleSceneMask(void) {
 if(Control_IsLeftPressed(&g_combinedControllerProfile)) {
 switch(g_gameSettings.sceneMask) {
 case 8: g_gameSettings.sceneMask=32; break;
 case 16: g_gameSettings.sceneMask=8; break;
 case 32: g_gameSettings.sceneMask=16; break;
 }
 }
 if(Control_IsRightPressed(&g_combinedControllerProfile) || Control_IsAButtonPressed(&g_combinedControllerProfile)) {
 switch(g_gameSettings.sceneMask) {
 case 8: g_gameSettings.sceneMask=16; break;
 case 16: g_gameSettings.sceneMask=32; break;
 case 32: g_gameSettings.sceneMask=8; break;
 }
 }
 return 0;
}

/* Sets bit 24 of the item's flags when g_gameSessionMode is 8 (clears it otherwise) and points the item at the text table for the configuration g_gameOptions (8, 0x10 or 0x20); returns 0. */
s32 Items_SelectSceneMaskText(SceneMaskLabelItem *item) {
    if (g_gameSession.mode == 8) {
        item->flags |= 0x01000000;
    } else {
        item->flags &= ~0x01000000;
    }
    switch (g_gameSettings.sceneMask) {
    case 8:
        item->table = g_sceneMaskLabelTables[0];
        break;
    case 16:
        item->table = g_sceneMaskLabelTables[1];
        break;
    case 32:
        item->table = g_sceneMaskLabelTables[2];
        break;
    }
    return 0;
}

s32 Items_AdjustPlayerOptionControlType(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7B = Menu_AdjustValue(holder, settings->option7B, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOptionControlTypeText(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    switch (settings->option7B) {
    case 0:
        field->text = &g_playerOptionControlTypeExpertText;
        break;
    case 1:
        field->text = &g_playerOptionControlTypeArcadeText;
        break;
    }
    return 0;
}

s32 Items_AdjustPlayerOptionControlSide(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7C = Menu_AdjustValue(holder, settings->option7C, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOptionControlSideText(struct PakActionLabelView *field, struct PlayerSettingsTextHolder *holder) {
    s32 result = 0;
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    if (settings->option7C != 0) {
        if (settings->option7C == 1) {
            field->text = g_playerOptionControlSideLeftText;
        }
    } else {
        field->text = g_playerOptionControlSideRightText;
    }
    return result;
}

s32 Items_AdjustPlayerOptionLookSpring(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7D = Menu_AdjustValue(holder, settings->option7D, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOptionLookSpringText(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    switch (settings->option7D) {
    case 0:
        field->text = &g_playerOptionLookSpringOffText;
        break;
    case 1:
        field->text = &g_playerOptionLookSpringOnText;
        break;
    }
    return 0;
}

s32 Items_AdjustPlayerOptionAutoAim(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7E = Menu_AdjustValue(holder, settings->option7E, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOptionAutoAimText(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    switch (settings->option7E) {
    case 0:
        field->text = &g_playerOptionAutoAimOffText;
        break;
    case 1:
        field->text = &g_playerOptionAutoAimOnText;
        break;
    }
    return 0;
}

s32 Items_AdjustBloodColor(void *first, void *second) {
    u8 *option = &g_gameSettings.bloodMode;

    *option = Menu_AdjustValue(second, *option, 1, 0, 2, 1);
    return 0;
}

s32 Items_SelectBloodColorText(struct PakActionLabelView *field) {
    switch (g_gameSettings.bloodMode) {
    case 0:
        field->text = g_bloodColorOffText;
        break;
    case 1:
        field->text = g_bloodColorRedText;
        break;
    case 2:
        field->text = g_bloodColorGreenText;
        break;
    default:
        return 0;
    }
    return 0;
}

s32 Items_AdjustSplitScreenPreference(void *first, void *second) {
    u8 *option = &g_gameSettings.twoPlayerScreenPreference;

    *option = Menu_AdjustValue(second, *option, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectSplitScreenPreferenceText(MenuBuildEntry *textRow) {
    s32 unusedResult;

    if ((SetN64_IsModeThirteen() != 0) && (g_gameSettings.local == 0)) {
        textRow->flags = textRow->flags & 0xFEFFFFFF;
    } else {
        textRow->flags = textRow->flags | 0x01000000;
    }
    switch (g_gameSettings.twoPlayerScreenPreference) {                           /* irregular */
    case 0:
        textRow->resource = (s32)(&g_gameOptionSplitScreenLayoutHorizontalText);
        break;
    case 1:
        textRow->resource = (s32)(&g_twoPlayerLayoutVerticalText);
        break;
    }
    return 0;
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)

s32 Items_FormatPackedGameOption(LayeredText *field) {
    char *text;
    s32 value = g_gameSettings.packedOptions >> 4;

    if (value == 0) {
        field->text = g_packedGameOptionZeroText;
    } else if (value == 16) {
        field->text = g_opacityOpaqueText;
    } else {
        field->text = &g_packedGameOptionValueText;
        text = field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_fmtDecPadShort, value);
    }
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Shows g_packedGameOptionZeroText in a field when the top twelve bits of g_gamePackedOptions are zero, g_opacityOpaqueText when they are sixteen, and otherwise points the field at g_packedGameOptionValueText and formats their value into it with g_fmtDecPadShort_ItemsFormatpackedgameoption into the last two characters of the field text (the length Menu_CountLineChars reports), returning zero. */
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Items_FormatPackedGameOption(LayeredText *field) {
    char *text;
    s32 value = g_gameSettings.packedOptions >> 4;

    if (value == 0) {
        field->text = g_packedGameOptionZeroText;
    } else if (value == 16) {
        field->text = g_opacityOpaqueText;
    } else {
        field->text = &g_packedGameOptionValueText;
        text = g_packedGameOptionValueText;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_fmtDecPadShort, value);
    }
    return 0;
}

#endif
#endif

s32 Items_AdjustPackedGameOption(void *first, void *second) {
    u8 limited;

    g_gamePackedOptions = Menu_AdjustValue(second, g_gamePackedOptions, 16, 0, 256, 0);
    limited = 0xFF;
    if (g_gamePackedOptions < 0xFF) {
        limited = g_gamePackedOptions & 0xFF;
    }
    g_playerHudSpriteMode = limited;
    return 0;
}

s32 Items_AdjustPlayerOptionStickHorizontal(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option79 = Menu_AdjustValue(holder, settings->option79, 8, 8, 248, 0);
    return 0;
}

s32 Items_FormatPlayerOptionStickHorizontalStep(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;
    s32 step;
    char *text;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    step = (settings->option79 - 128) / 8;
    if (step == 0) {
        field->text = &g_playerOptionStickHorizontalNormalText;
    } else if (step > 0) {
#if defined(VERSION_EU)
        field->text = g_playerOptionStickHorizontalStepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOptionStickHorizontalStepText_eu_x;
#else
        field->text = &g_playerOptionStickHorizontalStepText;
#endif
        text =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
field->text[g_gameSettings.language]
#else
*field->text
#endif
;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuStepFormatGerman, step);
    } else {
#if defined(VERSION_EU)
        field->text = g_playerOptionStickHorizontalStepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOptionStickHorizontalStepText_eu_x;
#else
        field->text = &g_playerOptionStickHorizontalStepText;
#endif
        text =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
field->text[g_gameSettings.language]
#else
*field->text
#endif
;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuStepFormat, step);
#else
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtSpaceWidePaddedDec, step);
#endif
    }
    return 0;
}

s32 Items_AdjustPlayerOptionStickVertical(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7A = Menu_AdjustValue(holder, settings->option7A, 8, 8, 248, 0);
    return 0;
}

s32 Items_FormatPlayerOptionStickVerticalStep(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;
    s32 step;
    char *text;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    step = (settings->option7A - 128) / 8;
    if (step == 0) {
        field->text = &g_playerOptionStickVerticalNormalText;
    } else if (step > 0) {
#if defined(VERSION_EU)
        field->text = g_playerOptionStickVerticalStepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOptionStickVerticalStepText_eu_x;
#else
        field->text = &g_playerOptionStickVerticalStepText;
#endif
        text =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
field->text[g_gameSettings.language]
#else
*field->text
#endif
;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuStepFormatGerman, step);
    } else {
#if defined(VERSION_EU)
        field->text = g_playerOptionStickVerticalStepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOptionStickVerticalStepText_eu_x;
#else
        field->text = &g_playerOptionStickVerticalStepText;
#endif
        text =
#if defined(VERSION_EU) || defined(VERSION_EU_X)
field->text[g_gameSettings.language]
#else
*field->text
#endif
;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_playerMenuStepFormat, step);
#else
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtSpaceWidePaddedDec, step);
#endif
    }
    return 0;
}

s32 Items_SelectQuickWeaponSelectText(struct PakActionLabelView *field, struct PlayerSettingsTextHolder *holder) {
    s32 result = 0;
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0) {
        settings = holder->owner->settings;
    }
    if (settings->flag82 == 1) {
        field->text = g_weaponSelectQuickText;
    } else {
        field->text = g_weaponSelectNormalText;
    }
    return result;
}

s32 Items_ToggleQuickWeaponSelect(void *entry, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0) {
        settings = holder->owner->settings;
    }
    if (settings->flag82 == 1) {
        settings->flag82 = 0;
    } else {
        settings->flag82 = 1;
    }
    return 0;
}

s32 Items_UpdateScreenModeMenuItem(struct MenuBuildEntry *record) {
    g_controllerPakProbeState -= g_frameElapsedTime;
    if (g_controllerPakProbeState <= 0.0f) {
        g_controllerPakProbeState = 0.0f;
    }
    if (Defs_GetMemorySize() != 0x400000) {
        record->flags |= 0x1000000;
    } else {
        record->flags &= ~0x1000000;
    }
    record->resource = Frontend_GetScreenModePalette();
    return 0;
}

s32 Items_RequestScreenModeFade(void) {
    if (g_controllerPakProbeState == 0.0f) {
        Frontend_StartScreenModeFade();
        g_controllerPakProbeState = (18.0f);
        g_frontendSavedVideoModeIndex = (u8)g_frontendCurrentVideoModeIndex;
    }
    return 0;
}

/* Retained data for this translation unit. */
#if defined(VERSION_US)
const unsigned char unbakeFill0[] = {0x00, 0x0A, 0x00, 0x04, 0x00, 0x00, 0x00, 0x14};
#endif
#if defined(VERSION_US_REV1)
const unsigned char unbakeFill1[] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10};
#endif

const char g_ItemsFormatplayeroptionStepBytes[7] = "  %02d";
#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
const float g_Player_DrawPulsingMenuSpriteConstantWords_us[1] = {
    0.5f,
};
#endif
#endif

const char g_fmtDecPadShort[5] =
    "%02d\000";
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_US)
const float g_Player_DrawPulsingMenuSpriteConstantWords_us[1] = {
    0.5f,
};
#endif
#endif
#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
const char g_fmtSpaceWidePaddedDec[6] =
    " %03d";
#endif
