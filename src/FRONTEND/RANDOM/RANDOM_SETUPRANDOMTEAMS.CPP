#include "include_asm.h"
#include "COMMON/LEVEL_GOAL.H"
#include "FRONTEND/JOIN_PLAYER_NAMES.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/SELF.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/ACTIVE.H"
#include "COMMON/RECTANGLE_DRAW.H"
#include "ENGINE/CONTROL.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "FRONTEND/RANDOM_SETUPRANDOMTEAMS.H"
#include "FRONTEND/RANDOM_CHOOSERANDOMCHARACTER.H"

extern u8 *XPlus_CopyString(u8 *dst, u8 *name);

/* Seats a joining player (request: kind+1, team, rank) in the highest free player slot, filling its index, kind (random for 20), team (random for 3, at most 2), rank and name (per language on the European cartridges); returns the slot or -1 when all are taken. */
s32 Random_AddStageOpponent(u8 *request) {
    s32 i;
    s32 kind;
    s32 team;
    u8 *name;
    s32 result;
    Shared_PlayerSettingsRecord *player;
    Shared_Game *settings;

    for (i = 7; i > 0; i--) {
        settings = &g_gameSettings;
        if (settings->playerSettings[i].enabled != 1) {
            break;
        }
    }
    result = -1;
    if (i >= 0) {
        player = &g_gameSettings.playerSettings[i];
        player->locked = 1;
        player->enabled = 1;
        player->slot = i;
        kind = request[0] - 1;
        if (kind == 19) {
            player->character = Random_ChooseRandomCharacter();
        } else {
            player->character = kind;
        }
        team = request[1];
        if (team == 3) {
            player->team = Graphu64_NextRandom() % 3;
        } else {
            player->team = team;
        }
        if ((u8)player->team >= 3) {
            player->team = 2;
        }
        player->variant = (u8)player->team;
        player->rank = request[2];
        switch (player->character) {
        case 15:
            name = joinName15();
            break;
        case 16:
            name = joinName16();
            break;
        default:
            name = joinTeamName((u8)player->team * 17 + Key_FindKeyIndex(player->character));
            break;
        }
        XPlus_CopyString(player->name, name);
        result = i;
    }
    return result;
}

/* Sets up the attract-mode demo match: shuffles the character/level tables, seats 2-4 random players (the first group of
 * 1-2 as unlocked, the rest locked) with random costumes and names, and picks the level goal in g_currentResultMode.
 * The last loop looks for the last enabled seat and never uses the answer: flow deletes its store after loop.c has
 * hoisted the 1 and strength-reduced the seat offset, so the ROM keeps only the counter, a0=1 and the 0xD0+0x96*i offset. */
void Random_SetupRandomTeams(void) {
    s32 characters[4];
    s32 arenas[4];
    LevelGoal *levelGoal;
    s32 i, firstIndex, secondIndex, swappedCharacter;
    s32 playerCount, unlockedCount;
    Shared_PlayerSettingsRecord *player;
    Shared_Game *game;
    characters[0] = 0;
    characters[1] = 3;
    characters[2] = 8;
    characters[3] = 5;
    arenas[0] = 0;
    arenas[1] = 3;
    arenas[2] = 27;
    arenas[3] = 1;
    for (i = 0; i < 100; i++) {
        firstIndex = Graphu64_NextRandom() % 4;
        secondIndex = Graphu64_NextRandom() % 4;
        swappedCharacter = characters[firstIndex];
        characters[firstIndex] = characters[secondIndex];
        characters[secondIndex] = swappedCharacter;
    }
    playerCount = Graphu64_NextRandom() % 3 + 2;
    unlockedCount = Graphu64_NextRandom() % playerCount + 1;
    if (unlockedCount == 3) {
        unlockedCount = 2;
    }
    game = &g_gameSettings;
    for (i = 0; i < 8; i++) {
        player = &game->playerSettings[i];
        player->controlMode = 0;
        player->active = 0;
        player->enabled = 0;
        player->locked = 0;
    }
    for (i = 0; i < unlockedCount; i++) {
        player = &game->playerSettings[4 + i];
        player->enabled = 1;
        player->character = characters[i];
        player->locked = 0;
        player->team = 2;
        player->variant = Graphu64_NextRandom() % 3;
        XPlus_CopyString(player->name, joinTeamName((s8)player->variant * 17 + Key_FindKeyIndex(player->character)));
    }
    for (i = 0; i < playerCount - unlockedCount; i++) {
        player = &game->playerSettings[4 + unlockedCount + i];
        player->enabled = 1;
        player->character = characters[i + unlockedCount];
        player->locked = 1;
        player->team = 2;
        player->variant = Graphu64_NextRandom() % 3;
        XPlus_CopyString(player->name, joinTeamName((s8)player->variant * 17 + Key_FindKeyIndex(player->character)));
    }
    for (i = 0; i < 8; i++) {
        player = &game->playerSettings[i];
        if (player->enabled == 1) {
            firstIndex = i;
        }
    }
    g_gameSettings.counters.transitionActive = 1;
    game->local = 1;
    game->mode1E = 8;
    game->controllerMode = 0;
    game->laps = 0;
    game->players = 0;
    levelGoal = &g_currentResultMode;
    levelGoal->kind = 2;
    levelGoal->goal = arenas[Graphu64_NextRandom() % 4];
}
