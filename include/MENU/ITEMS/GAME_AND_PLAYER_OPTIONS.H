#ifndef MENU_ITEMS_GAME_AND_PLAYER_OPTIONS_H
#define MENU_ITEMS_GAME_AND_PLAYER_OPTIONS_H
#include "MENU/HOLDERRECAT1CV2.H"
/* The SN debug records name the options record g_gameSettings COptions_t and its 0x96-byte player
   records CPlayerOptions_t; these are views of them with the debug member names and types. */
typedef struct CPlayerOptions {
    s16 totalSuicide;
    s16 totalDeaths;
    s16 totalKills;
    s16 totalTags;
    s16 totalCaptures;
    s16 totalSnipes;
    s16 whoTaggedMe[8];
    s16 whoITagged[8];
    s16 whoKilledMe[8];
    s16 whoIKilled[8];
    u8 weaponList[22];
    u8 weaponListSlot[22];
    u8 active; /* 0x78 */
    u8 horizAnalog;
    u8 vertAnalog;
    s8 controlType;
    u8 controlSide;
    u8 lookSpring;
    u8 autoAim;
    s8 controller; /* 0x7F */
    s8 character;
    s8 characterSkin;
    u8 weaponSelect;
    u8 handicap;
    u8 name[9]; /* 0x84 */
    u8 statsChanged;
    u8 deathmatchDone;
    u8 fragTagIsIt;
    u8 fragTagWasIt;
    u8 isBot;
    u8 team;
    u8 botSkill;
    u8 isBoss; /* 0x94 */
    u8 talsetPosse;
} CPlayerOptions;
typedef struct COptions {
    u32 cheatFlags;
    u32 cheatEnabledFlags;
    u32 difficulty;
    u8 autoSlopePitch;
    u8 overallGameType;
    u32 lightingGamma; /* 0x10 */
    u16 realOpacity;
    u8 opacity;
    u8 stereo;
    u8 musicVolume; /* 0x18 */
    u8 sfxVolume;
    u8 speechVolume;
    u8 blood;
    u8 debug;
    u8 multiPlayer;
    u8 maxPlayers;
    u8 twoPlayerScreenPref;
    f32 multiplayerSpeedScaler; /* 0x20 */
    s8 blTimedGame;
    s8 blFragLimit;
    s8 blFlagLimit;
    s8 blTagLimit;
    u8 blFriendlyFire;
    s8 blLevel;
    s8 blLevelTextureSet;
    u8 blCrosshairs;
    u8 multiWeapon[10]; /* 0x2C */
    s8 singleTrainingLevel;
    s8 singleTrainingNoOfLaps;
    s8 multiTrainingLevel;
    s8 multiTrainingNoOfLaps;
    CPlayerOptions singlePlayerOptions; /* 0x3A */
    CPlayerOptions multiPlayerOptions[8]; /* 0xD0 */
    u8 resolution; /* 0x580 */
    u8 language;
} COptions;
extern void Items_ResetGameOptions(COptions *options);
extern void Items_ResetPlayerSettings(CPlayerOptions *player, s8 controller);
/* The default-name routine sits at different addresses in the PAL and non-PAL builds. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern void Items_CopyDefaultLocalizedPlayerName(u8 *);
#define PLAYER_SET_DEFAULT_NAME Items_CopyDefaultLocalizedPlayerName
#else
extern void Items_SetDefaultPlayerName(u8 *);
#define PLAYER_SET_DEFAULT_NAME Items_SetDefaultPlayerName
#endif
/* CPlayerOptions_t's reset (Items_ResetPlayerSettings is its out-of-line copy): controls back to
   their defaults, the controller index kept, the default name set. */
static __inline__ void PlayerOptions_Reset(CPlayerOptions *player, s8 controller) {
    player->active = 0;
    player->horizAnalog = 134;
    player->vertAnalog = 132;
    player->controlSide = 0;
    player->controlType = 0;
    player->lookSpring = 1;
    player->autoAim = 0;
    player->controller = controller;
    player->character = 0;
    player->weaponSelect = 0;
    player->handicap = 0;
    player->characterSkin = 0;
    player->isBoss = 0;
    player->talsetPosse = 0;
    PLAYER_SET_DEFAULT_NAME((u8 *)player);
}
#endif
