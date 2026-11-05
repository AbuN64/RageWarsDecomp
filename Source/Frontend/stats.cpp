#include "Common/menu_options_and_results.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Frontend/frontend_accumulateplayerstatistics.h"
#include "Common/gameplay_settings.h"
#include "Frontend/frontend_address_symbols.h"

/* unit STATS.CPP */
/* Adds the current record's deltas to both running totals of each player still in play, capping each at 99999. */
void Frontend_AccumulatePlayerStatistics(void) {
    s32 playerIndex;
    s32 accumulatedCount;
    Shared_PlayerSettingsRecord *playerOptions;

    for (playerIndex = 0; playerIndex < 4; playerIndex++) {
        if (g_profileSlotIndices[playerIndex][0] >= 0) {
            playerOptions = &g_playerSettings[playerIndex];
            accumulatedCount = g_playerStatisticsAccumulatedKills[playerIndex][0] + playerOptions->score /* kills */;
            if (accumulatedCount > 99999) {
                g_playerStatisticsAccumulatedKills[playerIndex][0] = 99999;
            } else {
                g_playerStatisticsAccumulatedKills[playerIndex][0] = accumulatedCount;
            }
            accumulatedCount = g_playerStatisticsAccumulatedDeaths[playerIndex][0] + playerOptions->unknown02 /* deaths */;
            if (accumulatedCount > 99999) {
                g_playerStatisticsAccumulatedDeaths[playerIndex][0] = 99999;
            } else {
                g_playerStatisticsAccumulatedDeaths[playerIndex][0] = accumulatedCount;
            }
        }
    }
}
