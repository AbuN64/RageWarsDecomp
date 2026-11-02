#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "FRONTEND/FRONTEND_ACCUMULATEPLAYERSTATISTICS.H"

extern s8 g_profileSlotIndices[][400];
extern PlayerStatisticsCountView g_playerSettings[];

/* Adds the current record's deltas to both running totals of each player still in play, capping each at 99999. */
void Frontend_AccumulatePlayerStatistics(void) {
    s32 playerIndex;
    s32 accumulatedCount;
    PlayerStatisticsCountView *playerOptions;

    for (playerIndex = 0; playerIndex < 4; playerIndex++) {
        if (g_profileSlotIndices[playerIndex][0] >= 0) {
            playerOptions = &g_playerSettings[playerIndex];
            accumulatedCount = g_playerStatisticsAccumulatedKills[playerIndex][0] + playerOptions->totalKills;
            if (accumulatedCount > 99999) {
                g_playerStatisticsAccumulatedKills[playerIndex][0] = 99999;
            } else {
                g_playerStatisticsAccumulatedKills[playerIndex][0] = accumulatedCount;
            }
            accumulatedCount = g_playerStatisticsAccumulatedDeaths[playerIndex][0] + playerOptions->totalDeaths;
            if (accumulatedCount > 99999) {
                g_playerStatisticsAccumulatedDeaths[playerIndex][0] = 99999;
            } else {
                g_playerStatisticsAccumulatedDeaths[playerIndex][0] = accumulatedCount;
            }
        }
    }
}
