#include "COMMON/SHAREDPLAYER.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/PLAYER_POOL_AND_INODE_CACHE_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "TYPES.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "RENDER/PLAYER_SPAWN_PLACEMENT.H"
#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "MENU/PAK_LOAD.H"

/* Starts a player's run: in a multiplayer session (g_motionVisibilitySettings) picks the lap count from the chosen track through Player_GetLevelProgress_MatchGetresulttext in mode 1 or from the loaded course in mode 4 for a human player, sets the run type at 0x5EA (1, or 3 in single player), clears 0x13C8 and 0x85C around Player_ResetRespawnedPlayer, then starts its vehicle through Player_PlacePlayerAtSpawnPoint with model 0xC1D for a computer player in state 12 during stage 9 and its own model otherwise, doubled when g_playerCount is two or more. */






extern char g_localPlayerProfiles[];
extern Course *g_currentStagePreset;
extern s32 g_activeLinkSequenceId;

extern s32 Player_GetLevelProgress(char *, s32);
extern void Player_ResetRespawnedPlayer(SharedPlayer *);
extern void Playerai_EndRound(void *);

extern u8 g_gameControllerMode; /* MIXED Player_PlacePlayerForRound */
extern u8 g_motionVisibilitySettings; /* MIXED Player_PlacePlayerForRound */
void Player_PlacePlayerForRound(SharedPlayer *player) {
    s32 scale;

    scale = (g_playerCount >= 2) * 2;
    if (g_motionVisibilitySettings != 0) {
        if (g_gameControllerMode == 1 && player->views1450.view1450_1.computer == 0) {
            player->views133C.view133C_1.laps = ((u8)Player_GetLevelProgress(g_localPlayerProfiles + player->views1C.view5D4_46.slot * sizeof(Profile), player->views5D8.view5D8_1.record->characterId) >> 1) + 1;
        }
        if (g_gameControllerMode == 4 && player->views1450.view1450_1.computer == 0 && g_currentStagePreset != 0) {
            player->views133C.view133C_1.laps = g_currentStagePreset->laps;
        }
        player->views5E8.view5EA_4.runType = 1;
    } else {
        player->views5E8.view5EA_4.runType = 3;
    }
    player->views13C8.view13C8_1.w13C8 = 0;
    Player_ResetRespawnedPlayer(player);
    player->views5E8.view85C_120.w85C = 0;
    if (player->views5DC.view5E0_9.state == 12 && player->views1450.view1450_1.computer != 0 && g_activeLinkSequenceId == 9) {
        Player_PlacePlayerAtSpawnPoint(player, 3101, scale, 1);
    } else {
        Player_PlacePlayerAtSpawnPoint(player, player->views5E8.view5EC_6.model, scale, 1);
    }
}

/* Ends a human player's run. Outside a networked session (or as its local host) the countdown at 0x133C ticks
 * down and, on reaching zero, clears humanWon and calls Playerai_EndRound on the menu data. Then a human player with
 * countdown left respawns with the chosen model (scaled when two or more players are in) and resets; otherwise
 * the run is settled through Player_SetPlayerState, except for a local idle player whose profile has no bonus. */
void Player_UpdateRunEndPlayer(struct Player *player)
{
    s32 modelScale = (g_playerCount >= 2) * 2;

    if (!(g_playerViewRenderContext.game.flags & 2) || g_playerViewRenderContext.game.local) {
        if ((g_playerViewRenderContext.game.controllerMode == 1 || g_playerViewRenderContext.game.controllerMode == 4) && player->computer == 0) {
            if (player->countdown > 0) {
                player->countdown--;
            }
            if (player->countdown == 0) {
                g_playerViewRenderContext.game.humanWon = 0;
                Playerai_EndRound(&g_playerViewRenderContext);
            }
        }
    }
    {
        Shared_Game *game = &g_playerViewRenderContext.game;

        if ((game->controllerMode == 1 || game->controllerMode == 4) && player->computer == 0) {
            if (player->countdown <= 0) {
                if (game->local && player->animationDone == 0 && player->profile->bonus == 0) {
                    return;
                }
                Player_SetPlayerState(player, player, 18);
            } else {
                Player_PlacePlayerAtSpawnPoint(player, player->model, modelScale, 1);
                Player_ResetRespawnedPlayer(player);
            }
        } else {
            Player_SetPlayerState(player, player, 18);
        }
        player->resetState = 0;
    }
}
