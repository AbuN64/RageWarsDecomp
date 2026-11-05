#ifndef UI_MATCH_REASON_H
#define UI_MATCH_REASON_H
#include "types.h"

struct MatchScoreScreen;
extern void Frontend_ShowResultRankBadge(s32,s32,u16);
/* The match-result badge screen shared by the scenario setup and match reason screens. */
extern struct MatchScoreScreen *g_matchResultBadgeScreen;
#endif
