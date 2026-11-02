#ifndef FRONTEND_JOIN_RANDOMIZEJOINREQUESTENTRIES_H
#define FRONTEND_JOIN_RANDOMIZEJOINREQUESTENTRIES_H
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/REQUESTRECAT10.H"
extern s32 g_rewardScoreBudgets[];
extern struct TextEntry g_rewardItemTiers[][17];
extern struct PlayerJoinRequestEntry g_joinRequestEntries[3];
extern void Join_RandomizeJoinRequestEntries(s32, s32);
#endif
