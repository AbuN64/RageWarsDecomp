#ifndef COMMON_SHARED_GAMESLOT_H
#define COMMON_SHARED_GAMESLOT_H
#include "TYPES.H"
#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RENDERCOUNTERS.H"
typedef struct Shared_GameSlot Shared_GameSlot;
struct Shared_GameSlot {
    u8 enabled;
    u8 controlOptionBytes[6];
    u8 slot;
    s8 kind;
    u8 appearanceAndMatchBytes[16];
    u8 controller;
    u8 team; u8 botSkill;
    u8 role;
    u8 escort;
    u8 secondListMode;
    u8 slotStridePadding[119];
};
typedef struct Shared_Game Shared_Game;
struct Shared_Game {
    u32 flags;
    s32 unlockedLevels; /* 0x04: one bit per level, tested with levelBit() */
    u32 sceneMask; /* 0x08: bits tested against each actor definition */
    u8 autoSlopePitch;
    u8 controllerMode;
    u8 gammaAlignmentPadding[2];
    u32 lightingGamma; /* 0x10 */
    u16 packedOptions; /* 0x14 */
    u8 hudFade;
    u8 stereo;
    u8 volume[3]; /* 0x18: the three audio option bytes */
    u8 bloodMode;
    u8 debugMode;
    u8 local;
    u8 mode1E;
    u8 twoPlayerScreenPreference;
    /* The ROM addresses these overlapping arrays from Game+0xD0 and +0x148.
     * Each 0x96-byte settings record's +0x78/+0x7F fields are the same
     * enabled/slot bytes used by the existing slots array. */
    union {
        struct {
            f32 speedFactor; /* 0x20 */
            s8 laps; /* +0x24 */
            s8 players; /* +0x25 */
            s8 trialOther; /* +0x26: Random_StartFragTagMatch */
            s8 trialScore; /* +0x27 */
            u8 multiplayerRuleBytes[3];
            u8 bonusIcon; /* +0x2B: shows the 0x2DA HUD icon */
            u8 firstMultiplayerWeaponEnabled;
            u8 menuToggles[9]; /* +0x2D: on/off rows 2..9 of the options list (+0x34 unused) */
            u8 trainingLevelAndLapOptions[4];
            Shared_PlayerSettingsRecord defaults; /* +0x3A: the record a new player starts from */
            u8 firstPlayerCountersAndWeapons[0x148 - 0xD0];
            Shared_GameSlot slots[8];
            u8 reservedBytes[0x34];
            s32 fragTagEnabled;
            u8 reservedBytes1[0x40];
            s32 split;
            u32 reservedElements[3];
            s32 humanWon;
            s32 threePlayerLayout;
        };
        struct {
            u8 reserved20[0xB0];
            Shared_PlayerSettingsRecord playerSettings[8];
            u8 resolution;
            u8 language;
            u8 reserved582[0x32];
            s32 state;
            u8 reserved5B8[0x20];
            CGameStatus counters; /* +0x5D8: g_matchRoundCounters */
        };
    };
    /* origin/legacy shared/game.h retains the complete 0xCAC-byte game record. */
    u8 reserved688[0xCAC - 0x688];
};
extern Shared_Game g_gameSettings;

#endif
