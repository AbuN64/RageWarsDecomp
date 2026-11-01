#include "include_asm.h"
#include "MENU/HOLDERRECAT1CV2.H"
#include "TYPES.H"
#include "MENU/ITEMS/GAME_AND_PLAYER_OPTIONS.H"

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
