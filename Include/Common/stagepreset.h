#ifndef COMMON_STAGEPRESET_H
#define COMMON_STAGEPRESET_H
#include "types.h"

struct StagePreset;
/* The stage entry of the match being set up; one record serves frontend, results and in-game readers. */
struct StagePreset {
    u8 recorded;           /* nonzero when finishing the level is recorded per save slot; also the variant code */
    u8 reservedAfterRecorded[4];
    u8 opponents[7][4];    /* seven opponent records: kind first, then the opponent's settings */
    u8 score;
    u8 limit;
    u8 other;
    u8 time;
    u8 reservedAfterTime[3];
    u8 laps;
};
typedef struct StagePreset StagePreset;

extern struct StagePreset *g_currentStagePreset;

#endif
