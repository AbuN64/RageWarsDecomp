#include "Engine/scene.h"
#include "include_asm.h"
#include "Achieve/achieve_address_symbols.h"
#include "Common/shared_menureply.h"
#include "Common/active.h"
#include "Common/shared_gameslot.h"
#include "types.h"
#include "Ui/X_files/x_plus.h"
#include "Common/level_goal.h"
#include "Frontend/join_player_names.h"
#include "Common/self.h"
#include "Common/player_join_requests.h"
#include "Common/rectangle_draw.h"
#include "Engine/control.h"
#include "Common/runtime_declarations.h"
#include "Frontend/random_setuprandomteams.h"
#include "Frontend/random_chooserandomcharacter.h"
#include "X_files/x_plus.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Common/world.h"
#include "Common/gameplay_settings.h"
#include "Render/soundelement_playflatsound.h"
#include "Scene/scene_findtrackedactors.h"

/* unit RANDOM_REPLACETEXTOCCURRENCES.CPP */
/* Marks the pair ending at g_selectionMessageReply.ready as set by storing one there, and stores its argument in the
   word before it; Random_SetSelectedStage fills the pair ending at g_selectedLevelId. */
void Random_SetMenuChoiceResult(s32 value) {
    s32 *pair = &g_selectionMessageReply.ready;

    pair[0] = 1;
    pair[-1] = value;
}

/* Stores a pair of words: the second argument in g_selectedLevelId and the first in the word before
   it; Random_SetMenuChoiceResult does the same for the pair ending at g_selectionMessageReply.ready. */
void Random_SetSelectedStage(s32 first, s32 second) {
    s32 *pair = &g_selectedLevelId;

    pair[0] = second;
    pair[-1] = first;
}

/* Replaces every occurrence of the second string in the first with the third, in place: while
   XPlus_FindPatternEnd finds a match (returning the position just past it), it copies the text before
   the match into a 200-byte buffer, appends the replacement through XPlus_AppendString, appends the
   rest of the text, copies the buffer back and searches again. */
void Random_ReplaceTextOccurrences(char *text, char *find, char *replacement) {
    char buffer[200];
    char *match;
    s32 findLength;
    s32 length;
    s32 before;
    s32 copied;
    s32 i;
    s32 j;

    match = (char *)XPlus_FindPatternEnd((u8 *)text, (u8 *)find);
    findLength = XPlus_StringLength(find);
    while (match != 0) {
        length = XPlus_StringLength(text);
        before = match - text - findLength;
        i = 0;
        if (i < before) {
            do {
                buffer[i] = text[i];
                i++;
            } while (i < before);
        }
        buffer[before] = 0;
        XPlus_AppendString((u8 *)buffer, (u8 *)replacement);
        j = XPlus_StringLength(buffer);
        i = before + findLength;
        if (i < length) {
            do {
                buffer[j] = text[i];
                j++;
                i++;
                buffer[j] = 0;
            } while (i < length);
        }
        copied = XPlus_StringLength(buffer);
        i = 0;
        if (i < copied) {
            do {
                text[i] = buffer[i];
                i++;
            } while (i < copied);
        }
        text[copied] = 0;
        match = (char *)XPlus_FindPatternEnd((u8 *)text, (u8 *)find);
    }
}

/* Applies the selected rule settings and refreshes the menu state. */

#include "Common/game_session.h"
#include "X_files/x_plus.h"
#include "Random/random_chooserandomcharacter.h"
#include "Ovlgame/match.h"
#include "Frontend/frontend_address_symbols.h"
#include "Common/stagepreset.h"
#include "Frontend/frontend.h"
void Random_StartFragTagMatch(void) {
 Shared_Game *g=&g_gameSettings;
 if(g->controllerMode != 0) Random_InitGameStatus((f32)g_currentStagePreset->time,0,g_currentStagePreset->score,g_currentStagePreset->other,1,0,0);
 else Random_InitGameStatus((f32)g->laps,0,g->trialScore,g->trialOther,1,0,0);
 Match_StartMatchTransition(&g_gameSession,Random_GetStageTransitionResource());
}

/* Applies the selected rule settings and refreshes the menu state. */
void Random_StartCaptureTheFlagMatch(void) {
 Shared_Game *g=&g_gameSettings;
 if(g->controllerMode != 0) Random_InitGameStatus((f32)g_currentStagePreset->time,0,g_currentStagePreset->score,g_currentStagePreset->other,0,1,1);
 else Random_InitGameStatus((f32)g->laps,0,g->trialScore,g->trialOther,0,1,1);
 Match_StartMatchTransition(&g_gameSession,Random_GetStageTransitionResource());
}

/* Applies the selected rule settings and refreshes the menu state. */
void Random_StartTeamMatch(void) {
 Shared_Game *g=&g_gameSettings;
 if(g->controllerMode != 0) Random_InitGameStatus((f32)g_currentStagePreset->time,g_currentStagePreset->limit,g_currentStagePreset->score,g_currentStagePreset->other,0,1,0);
 else Random_InitGameStatus((f32)g->laps,g_gameSettings.players,g->trialScore,g->trialOther,0,1,0);
 Match_StartMatchTransition(&g_gameSession,Random_GetStageTransitionResource());
}

/* Applies the selected rule settings and refreshes the menu state. */
void Random_StartIndividualMatch(void) {
 Shared_Game *g=&g_gameSettings;
 if(g->controllerMode != 0) Random_InitGameStatus((f32)g_currentStagePreset->time,g_currentStagePreset->score,g_currentStagePreset->score,g_currentStagePreset->other,0,0,0);
 else Random_InitGameStatus((f32)g->laps,g_gameSettings.players,g->trialScore,g->trialOther,0,0,0);
 Match_StartMatchTransition(&g_gameSession,Random_GetStageTransitionResource());
}

/* Starts the match status block: the frag tag limit, the second score limit, the frag tag, team and
 * capture-the-flag switches and the mode, the time limit scaled by 900 (15 in controller modes 2 and 3,
 * -1 when there is no limit), then clears the score and count rows. */
static inline CGameStatus *GameCounters(void) { return &g_gameSettings.counters; }
void Random_InitGameStatus(f32 duration, s32 mode, s32 fragTagLimit, s32 otherLimit,
                     s32 fragTagOn, s32 teams, s32 ctfOn) {
    s32 i;
    GameCounters()->m_FragTagLimit = fragTagLimit;
    GameCounters()->m_CTFPlayerWithFlag = 0;
    GameCounters()->otherLimit = otherLimit;
    GameCounters()->m_bFragTagOn = fragTagOn;
    GameCounters()->teams = teams;
    GameCounters()->m_bCTFOn = ctfOn;
    if ((u32)(g_gameSettings.controllerMode - 2) < 2) {
        GameCounters()->timeLimit = duration * 15.0f;
    } else {
        GameCounters()->timeLimit = duration * 900.0f;
    }
    GameCounters()->mask = 0xA00;
    GameCounters()->mode = mode;
    GameCounters()->elapsed = 0;
    for (i = 0; i < 5; i++) {
        GameCounters()->scores[i] = 0;
        GameCounters()->counts[i] = 0;
    }
    GameCounters()->round = 0;
    if (GameCounters()->timeLimit == 0.0f) {
        GameCounters()->timeLimit = -1.0f;
    }
}

/* unit RANDOM_SETUPRANDOMTEAMS.CPP */
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
 * The last loop looks for the last enabled seat and discards the answer; it is kept only to leave the same seat counter state. */
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

/* unit RANDOM_CHOOSERANDOMCHARACTER.CPP */
/* Returns 0xBC2 plus ten times either the halfword at offset 2 of what Scene_GetBlLevelData finds for
   g_selectedLevelId in g_world_AchieveUpdateresultsscreen, when the option byte g_gameControllerMode is one, or g_selectedLevelId itself. */





s32 Random_GetStageTransitionResource(void) {
    return (g_gameSettings.controllerMode == 1 ? ((s16 *)Scene_GetBlLevelData(&g_world, g_selectedLevelId))[1] : g_selectedLevelId) * 10 + 3010;
}


/* Characters 0 and 5 may appear only once among the eight enabled players. */
static inline s32 characterAvailable(s32 character, s32 firstUniqueCharacter, s32 secondUniqueCharacter) {
    s32 available;
    s32 i;
    Shared_PlayerSettingsRecord *players = g_playerSettings;
    if (character == firstUniqueCharacter || character == secondUniqueCharacter) {
        for (available = 1, i = 0; i < 8; i++) {
            if (players[i].enabled && players[i].character == character) {
                available = 0;
            }
        }
    } else {
        available = 1;
    }
    return available;
}

s32 Random_ChooseRandomCharacter(void) {
    s32 character;
    do {
        character = Graphu64_NextRandom() % 11;
    } while (!characterAvailable(character, 0, 5));
    return character;
}
