#ifndef FRONTEND_JOIN_RANDOMIZEJOINREQUESTENTRIES_H
#define FRONTEND_JOIN_RANDOMIZEJOINREQUESTENTRIES_H
#include "Common/runtime_declarations.h"
#include "Common/menu_options_and_results.h"
#include "Common/player_join_requests.h"
extern s32 g_rewardScoreBudgets[];
extern struct TextEntry g_rewardItemTiers[][17];
extern struct PlayerJoinRequestEntry g_joinRequestEntries[3];
extern void Join_RandomizeJoinRequestEntries(s32, s32);
#endif
