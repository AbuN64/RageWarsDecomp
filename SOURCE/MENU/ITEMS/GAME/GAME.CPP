#include "include_asm.h"
#include "MENU/HOLDERRECAT1CV2.H"
#include "TYPES.H"
#include "MENU/ITEMS/GAME_AND_PLAYER_OPTIONS.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <ultra64.h>
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "MENU/ITEMS/ITEMS_CYCLESCENEMASK.H"
#include "RENDER/SETN64_UPDATEFADETRANSITION.H"
#include "MENU/ITEMS/MENU_VALUE_AND_LINE_TEXT.H"
#include "ENGINE/DEFS.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/MENURECAT20V1.H"
#include "COMMON/NODERECAT2A8.H"
#include "FRONTEND/SCREEN_VIDEO_MODE.H"
#include "DATA/REST_SOURCE_RECORDS.H"
#include "FRONTEND/SCREEN.H"
#include "GAME/GAME.H"
#include "MENU/MENU_CREATEMENUFROMPARAMETERS.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"

/* Clears the word held in g_controllerPakProbeState. */
extern f32 g_controllerPakProbeState;

/* Returns the name the object at offset 0x5D8 of an actor's owner holds, falling back to
   g_playerPartnerNameFallback when the actor has no owner or the owner has no such object. */

/* Updates the selected menu option in response to the current input state. */
unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);

 /* extern */
 /* extern */
 /* extern */
extern char g_combinedControllerProfile;

/* Replaces the option halfword g_gamePackedOptions with what Menu_AdjustValue returns for the second argument,
   that halfword, 0x10, 0, 0x100 and 0, then stores its low byte in the byte after it, or 0xFF when
   the value is 0xFF or more. Returns zero. */
/* Replaces the byte at offset 0x79 of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 8, 8, 0xF8 and 0, and returns zero. */
#if defined(VERSION_EU)
/* Points an option field at the settings byte 0x79 of the holder's owner settings (or the defaults g_playerPartnerNameFallback) as a signed offset from 128 in steps of eight, using the text g_playerOption79ZeroText for zero and otherwise the text g_playerOption79StepText_eu formatted with g_playerMenuStepFormatGerman for a positive or g_playerMenuStepFormat for a negative step four bytes before the length Menu_CountLineChars reports, returning zero. */
/* Points an option field at the settings byte 0x79 of the holder's owner settings (or the defaults g_playerPartnerNameFallback) as a signed offset from 128 in steps of eight, using the text g_playerOption79ZeroText for zero and otherwise the text g_playerOption79StepText_eu_x formatted with g_playerMenuStepFormatGerman for a positive or g_playerMenuStepFormat for a negative step four bytes before the length Menu_CountLineChars reports, returning zero. */
/* Points an option field at the settings byte 0x79 of the holder's owner settings (or the defaults g_playerPartnerNameFallback) as a signed offset from 128 in steps of eight, using the text g_playerOption79ZeroText for zero and otherwise the text g_playerOption79StepText formatted with g_playerMenuStepFormatGerman for a positive or g_fmtSpaceDec3_Playeroption for a negative step four bytes before the length Menu_CountLineChars reports, returning zero. */
extern char *g_playerOption79StepText_eu;
#elif defined(VERSION_EU_X)
extern char *g_playerOption79StepText_eu_x;
#endif

#if defined(VERSION_EU)
/* Replaces the byte at offset 0x7A of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 8, 8, 0xF8 and 0, and returns zero. Adapted from Items_AdjustPlayerOption79 with the settings byte 0x7A changed. */
extern char *g_playerOption7AStepText_eu;
#elif defined(VERSION_EU_X)
extern char *g_playerOption7AStepText_eu_x;
#endif

/* Points a field's text at g_playerFlag82OnText when the byte at offset 0x82 of the settings the second argument's owner holds, or of the defaults g_playerPartnerNameFallback without an owner, is one, and at g_playerFlag82OffText otherwise, returning zero. Adapted from Pak_UpdateOwnerModeText with the settings lookup of Items_TogglePlayerFlag82 and the texts g_playerFlag82OnText and g_playerFlag82OffText changed, and a zero result local declared first to give the owner and settings pointers the cartridge's registers. */
/* Toggles the byte at offset 0x82 of the settings the object at offset 0x5D8 of the second
   argument's owner holds, or of the defaults g_playerPartnerNameFallback when there is no owner, and returns zero. */
/* Counts the timer g_controllerPakProbeState down by g_frameElapsedTime without passing zero, then sets bit 24 of the flag word at offset 8 of a record unless Defs_GetMemorySize reports 0x400000, in which case the bit is cleared, stores what Frontend_GetScreenModePalette_Playeroption returns at offset 0x14 and returns zero. Adapted from Pak_UpdateScreenModeAvailability with the timer countdown added, Defs_GetMemorySize called without arguments and bit 24 instead of bit 23 changed. */
extern f32 g_frameElapsedTime;

extern s32 Defs_GetMemorySize(void);



#if defined(VERSION_EU)
/* Picks the label for each of the eight option rows (ids 2..9): the first text when the row's flag is set, else the second. */
typedef struct { s32 id; u8 pad4[0x10]; char ***text; } OptionRowEu;
#endif
#if defined(VERSION_EU_X)
#include "TYPES.H"
#endif

/* ITEMS_COPYDEFAULTLOCALIZEDPLAYERNAME.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
extern u8 *g_playerPartnerSuffixByLanguage[];
extern u8 *g_playerNamePrefixByLanguage[];
extern u8 *g_localizedPlayerNameSuffixes[];
extern u8 *g_playerNameSuffixByLanguage[];

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

/* G_ITEMSCONSTANTWORDSBLOCK1.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E27C4 */
unsigned int g_itemsConstantWordsBlock1[3] = {
    0x00000014, 0x00000019, 0x00000005,
};
#endif

/* MENU_ITEM_STATUS_TEXT_STORAGE.CPP */
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

/* ITEMS.CPP */
#if defined(VERSION_DE)
/* 800DE794.CPP */
char g_itemsConstantWords[12] =
    "d\000\000\000 %3d\000\000\000";
#endif

/* AMMO.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* 800E2774.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/playerDrawPulsingMenuSpriteConstantWordsPoolUsRev1.c */
const float g_Player_DrawPulsingMenuSpriteConstantWords_us_rev1[1] = {
    0.5f,
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* 80442BC8_5.CPP */

#if defined(VERSION_US)
const float g_Player_DrawPulsingMenuSpriteConstantWords_us[1] = {
    0.5f,
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ammoEncodedWordsBlock1UsRev1Data.CPP */

/* ammoCountFormatData.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_ammoCountFormat[8] =
    " %03d\000\000\000";
#endif
#endif

#if defined(VERSION_US)
const unsigned char unbake_fill_0[] = {0x00, 0x0A, 0x00, 0x04, 0x00, 0x00, 0x00, 0x14};
#endif

#if defined(VERSION_US_REV1)
const unsigned char unbake_fill_1[] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10};
#endif

/* ITEMS_FORMATPACKEDGAMEOPTION.CPP */
/* ROM-grounded data: src/g_fmtDec2Pad.c */
const char g_fmtDec2Pad[5] =
    "%02d\000";

/* ITEMS_FORMATPLAYEROPTION79STEP_DATA.CPP */
/* ROM-grounded data: rodata/shared/800E2788 */
const char g_ItemsFormatplayeroption79stepBytes1[7] = "  %02d";

/* AMMO.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
/* 800E2774.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/playerDrawPulsingMenuSpriteConstantWordsPoolUsRev1.c */
const float g_Player_DrawPulsingMenuSpriteConstantWords_us_rev1[1] = {
    0.5f,
};
#endif
#endif

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
/* 80442BC8_5.CPP */

#if defined(VERSION_US)
const float g_Player_DrawPulsingMenuSpriteConstantWords_us[1] = {
    0.5f,
};
#endif
#endif

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
/* ammoEncodedWordsBlock1UsRev1Data.CPP */

/* ammoCountFormatData.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_ammoCountFormat[8] =
    " %03d\000\000\000";
#endif
#endif

/* G_FMTSPACEDEC3.CPP */
#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* ROM-grounded data: rodata/shared/800E2790 */
const char g_fmtSpaceDec3[6] =
    " %03d";
#endif

/* ITEMS_RESETGAMEOPTIONS.CPP */
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

/* ITEMS_SETDEFAULTPLAYERNAME.CPP */
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
#include "TYPES.H"

/* Copies an eight-byte preset into offset 0x84 of a record, choosing the preset table by the record's kind byte at 0x7F: kinds 1 to 3 use their own tables, kinds 4 to 7 leave the record unchanged, and any other kind uses the default table. */
extern u8 *g_defaultPlayerNameOne;
extern u8 *g_defaultPlayerNameTwo;
extern u8 *g_defaultPlayerNameThree;
extern u8 *g_defaultPlayerNameFour;

void Items_SetDefaultPlayerName(u8 *record) {
    s32 i;

    switch ((signed char)record[127]) {
    case 0:
    default:
        for (i = 0; i < 8; i++) {
            (record + i)[132] = g_defaultPlayerNameOne[i];
        }
        return;
    case 1:
        for (i = 0; i < 8; i++) {
            (record + i)[132] = g_defaultPlayerNameTwo[i];
        }
        return;
    case 2:
        for (i = 0; i < 8; i++) {
            (record + i)[132] = g_defaultPlayerNameThree[i];
        }
        return;
    case 3:
        for (i = 0; i < 8; i++) {
            (record + i)[132] = g_defaultPlayerNameFour[i];
        }
        return;
    case 4:
    case 5:
    case 6:
    case 7:
        return;
    }
}
#endif

/* ITEMS_CYCLESCENEMASK.CPP */
/* Replaces the signed byte at offset 0x7B of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 1, 0, 1 and 1, returning zero. Adapted from Items_AdjustPlayerOption7E with the settings byte made the signed byte at 0x7B. */

/* Points an option field at the text g_playerOption7BText0 when the signed byte at offset 0x7B of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) is zero and at g_playerOption7BText1 when it is one, returning zero. Adapted from Items_SelectPlayerOption7EText with the settings byte made the signed byte at 0x7B and the texts changed. */

/* Replaces the byte at offset 0x7C of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 1, 0, 1 and 1, and returns zero. */

/* Points a field's text at g_playerOption7CText0 when the byte at offset 0x7C of the settings the second argument's owner holds (or of the defaults g_playerPartnerNameFallback without an owner or settings) is zero, at g_playerOption7CText1 when it is one, and leaves it otherwise, returning zero. Adapted from Items_SelectPlayerFlag82Text with the settings pointer checked for null, the byte offset 0x7C, and a nested test over the texts g_playerOption7CText0 and g_playerOption7CText1 changed. */

/* Replaces the byte at offset 0x7D of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 1, 0, 1 and 1, and returns zero. Adapted from Items_AdjustPlayerOption7C with the settings byte 0x7D changed. */

/* Points an option field at the text g_playerOption7DText0 when the byte at offset 0x7D of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) is zero and at g_playerOption7DText1 when it is one, returning zero. */

/* Replaces the byte at offset 0x7E of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) with what Menu_AdjustValue returns for the second argument, that byte, 1, 0, 1 and 1, and returns zero. Adapted from Items_AdjustPlayerOption7C with the settings byte 0x7E changed. */

/* Points an option field at the text g_playerOption7EText0 when the byte at offset 0x7E of the second argument's owner settings (or the defaults g_playerPartnerNameFallback) is zero and at g_playerOption7EText1 when it is one, returning zero. Adapted from Items_SelectPlayerOption7DText with the settings byte 0x7E and the texts g_playerOption7EText0 and g_playerOption7EText1 changed. */

/* Replaces the option byte g_particleSpriteViewMode with what Menu_AdjustValue returns for the second argument, that
   byte, 1, 0, 2 and 1, and returns zero. */

/* Replaces the option byte g_gameSettingsTwoPlayerScreenPreference with what Menu_AdjustValue returns for the second argument, that
   byte, 1, 0, 1 and 1, and returns zero. */

/* Updates the menu item visibility and text for the current configuration. */

                                /* extern */

void Items_ResetScreenModeFadeCooldown(void) {
    *(s32 *)&g_controllerPakProbeState = 0;
}

char *Items_GetPlayerSettingsText(struct PlayerSettingsTextHolder *actor) {
    char *name = g_playerPartnerNameFallback.text;

    if (actor->owner != 0 && actor->owner->settings != 0) {
        name = actor->owner->settings->text;
    }
    return name;
}

s32 Items_CycleSceneMask(void) {
 if(((s32 (*)(char *))Control_IsLeftPressed)(&g_combinedControllerProfile)) {
 switch(g_gameSettings.sceneMask) {
 case 8: g_gameSettings.sceneMask=32; break;
 case 16: g_gameSettings.sceneMask=8; break;
 case 32: g_gameSettings.sceneMask=16; break;
 }
 }
 if(((s32 (*)(char *))Control_IsRightPressed)(&g_combinedControllerProfile) || Control_IsAButtonPressed(&g_combinedControllerProfile)) {
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
        item->table = g_sceneMaskLabelTable8;
        break;
    case 16:
        item->table = g_sceneMaskLabelTable0x10;
        break;
    case 32:
        item->table = g_sceneMaskLabelTable0x20;
        break;
    }
    return 0;
}

s32 Items_AdjustPlayerOption7B(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7B = Menu_AdjustValue(holder, settings->option7B, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOption7BText(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    switch (settings->option7B) {
    case 0:
        field->text = &g_playerOption7BText0;
        break;
    case 1:
        field->text = &g_playerOption7BText1;
        break;
    }
    return 0;
}

s32 Items_AdjustPlayerOption7C(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7C = Menu_AdjustValue(holder, settings->option7C, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOption7CText(struct PakActionLabelView *field, struct PlayerSettingsTextHolder *holder) {
    s32 result = 0;
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    if (settings->option7C != 0) {
        if (settings->option7C == 1) {
            field->text = g_playerOption7CText1;
        }
    } else {
        field->text = g_playerOption7CText0;
    }
    return result;
}

s32 Items_AdjustPlayerOption7D(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7D = Menu_AdjustValue(holder, settings->option7D, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOption7DText(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    switch (settings->option7D) {
    case 0:
        field->text = &g_playerOption7DText0;
        break;
    case 1:
        field->text = &g_playerOption7DText1;
        break;
    }
    return 0;
}

s32 Items_AdjustPlayerOption7E(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7E = Menu_AdjustValue(holder, settings->option7E, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectPlayerOption7EText(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    switch (settings->option7E) {
    case 0:
        field->text = &g_playerOption7EText0;
        break;
    case 1:
        field->text = &g_playerOption7EText1;
        break;
    }
    return 0;
}

s32 Items_AdjustFirstListMode(void *first, void *second) {
    u8 *option = &g_gameSettings.bloodMode;

    *option = Menu_AdjustValue(second, *option, 1, 0, 2, 1);
    return 0;
}

s32 Items_SelectFirstListModeText(struct PakActionLabelView *field) {
    switch (g_gameSettings.bloodMode) {
    case 0:
        field->text = g_bloodModeText0;
        break;
    case 1:
        field->text = g_bloodModeText1;
        break;
    case 2:
        field->text = g_bloodModeText2;
        break;
    default:
        return 0;
    }
    return 0;
}

s32 Items_AdjustGameOption1F(void *first, void *second) {
    u8 *option = &g_gameSettings.twoPlayerScreenPreference;

    *option = Menu_AdjustValue(second, *option, 1, 0, 1, 1);
    return 0;
}

s32 Items_SelectGameOption1FText(MenuOptionLabelView *textRow) {
    s32 unusedResult;

    if ((SetN64_IsModeThirteen() != 0) && (g_gameSettings.local == 0)) {
        textRow->flags = textRow->flags & 0xFEFFFFFF;
    } else {
        textRow->flags = textRow->flags | 0x01000000;
    }
    switch (g_gameSettings.twoPlayerScreenPreference) {                           /* irregular */
    case 0:
        textRow->label = &g_gameOptionOneFZeroText;
        break;
    case 1:
        textRow->label = &g_gameOptionOneFOneText;
        break;
    }
    return 0;
}

/* ITEMS_FORMATPACKEDGAMEOPTION.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/SHARED_GAMESLOT.H"
#include "ENGINE/DEFS.H"
#include "MENU/ITEMS/MENU_VALUE_AND_LINE_TEXT.H"

s32 Items_FormatPackedGameOption(LayeredText *field) {
    char *text;
    s32 value = g_gameSettings.packedOptions >> 4;

    if (value == 0) {
        field->text = g_packedGameOptionZeroText;
    } else if (value == 16) {
        field->text = g_packedGameOptionSixteenText;
    } else {
        field->text = (u8 **)&g_packedGameOptionValueText;
        text = (char *)field->text[g_gameSettings.language];
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_fmtDec2Pad, value);
    }
    return 0;
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Shows g_packedGameOptionZeroText in a field when the top twelve bits of g_gamePackedOptions are zero, g_packedGameOptionSixteenText when they are sixteen, and otherwise points the field at g_packedGameOptionValueText and formats their value into it with g_fmtDec2Pad_ItemsFormatpackedgameoption two bytes before the length Menu_CountLineChars reports, returning zero. Adapted from Pak_FormatMusicPreview with the value taken from the top twelve bits of the halfword g_gamePackedOptions, a second fixed text for sixteen, and the texts and format changed. */

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Items_FormatPackedGameOption(LayeredText *field) {
    char *text;
    s32 value = g_gameSettings.packedOptions >> 4;

    if (value == 0) {
        field->text = g_packedGameOptionZeroText;
    } else if (value == 16) {
        field->text = g_packedGameOptionSixteenText;
    } else {
        field->text = (u8 **)&g_packedGameOptionValueText;
        text = (char *)*(u8 **)&g_packedGameOptionValueText;
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 2), g_fmtDec2Pad, value);
    }
    return 0;
}

#endif
#endif

/* PLAYEROPTION.CPP */
s32 Items_AdjustPackedGameOption(void *first, void *second) {
    u16 *option = &g_gamePackedOptions;
    u8 limited;

    *option = Menu_AdjustValue(second, *option, 16, 0, 256, 0);
    limited = 0xFF;
    if (*option < 0xFF) {
        limited = ((u8 *) option)[1];
    }
    ((u8 *) option)[2] = limited;
    return 0;
}

s32 Items_AdjustPlayerOption79(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option79 = Menu_AdjustValue(holder, settings->option79, 8, 8, 248, 0);
    return 0;
}

s32 Items_FormatPlayerOption79Step(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;
    s32 step;
    char *text;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    step = (settings->option79 - 128) / 8;
    if (step == 0) {
        field->text = &g_playerOption79ZeroText;
    } else if (step > 0) {
#if defined(VERSION_EU)
        field->text = &g_playerOption79StepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOption79StepText_eu_x;
#else
        field->text = &g_playerOption79StepText;
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
        field->text = &g_playerOption79StepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOption79StepText_eu_x;
#else
        field->text = &g_playerOption79StepText;
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
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtSpaceDec3, step);
#endif
    }
    return 0;
}

s32 Items_AdjustPlayerOption7A(void *first, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    settings->option7A = Menu_AdjustValue(holder, settings->option7A, 8, 8, 248, 0);
    return 0;
}

s32 Items_FormatPlayerOption7AStep(struct Field *field, struct PlayerSettingsTextHolder *holder) {
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;
    s32 step;
    char *text;

    if (holder->owner != 0 && holder->owner->settings != 0) {
        settings = holder->owner->settings;
    }
    step = (settings->option7A - 128) / 8;
    if (step == 0) {
        field->text = &g_playerOption7AZeroText;
    } else if (step > 0) {
#if defined(VERSION_EU)
        field->text = &g_playerOption7AStepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOption7AStepText_eu_x;
#else
        field->text = &g_playerOption7AStepText;
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
        field->text = &g_playerOption7AStepText_eu;
#elif defined(VERSION_EU_X)
        field->text = &g_playerOption7AStepText_eu_x;
#else
        field->text = &g_playerOption7AStepText;
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
        Defs_FormatIntegerValue(text + (Menu_CountLineChars(field) - 4), g_fmtSpaceDec3, step);
#endif
    }
    return 0;
}

s32 Items_SelectPlayerFlag82Text(struct PakActionLabelView *field, struct PlayerSettingsTextHolder *holder) {
    s32 result = 0;
    struct PlayerOptions *settings = &g_playerPartnerNameFallback;

    if (holder->owner != 0) {
        settings = holder->owner->settings;
    }
    if (settings->flag82 == 1) {
        field->text = g_playerFlag82OnText;
    } else {
        field->text = g_playerFlag82OffText;
    }
    return result;
}

s32 Items_TogglePlayerFlag82(void *unused, struct PlayerSettingsTextHolder *holder) {
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

s32 Items_UpdateScreenModeMenuItem(struct MenuTextResultView *record) {
    g_controllerPakProbeState -= g_frameElapsedTime;
    if (g_controllerPakProbeState <= 0.0f) {
        g_controllerPakProbeState = 0.0f;
    }
    if (Defs_GetMemorySize() != 0x400000) {
        record->flags |= 0x1000000;
    } else {
        record->flags &= ~0x1000000;
    }
    record->value = Frontend_GetScreenModePalette();
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
