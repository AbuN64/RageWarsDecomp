#ifndef COMMON_LEVEL_GOAL_H
#define COMMON_LEVEL_GOAL_H
#include "TYPES.H"
/* The level goal the rule set picks: its kind (0 rounds, 1 laps, 2 single laps, 3 targets) and the
 * target the players race or fight to. */
typedef struct LevelGoal {
    s32 kind;
    s32 goal;
} LevelGoal;
extern LevelGoal g_currentResultMode;
#endif
