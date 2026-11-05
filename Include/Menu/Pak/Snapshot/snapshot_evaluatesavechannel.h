#ifndef MENU_PAK_SNAPSHOT_SNAPSHOT_EVALUATESAVECHANNEL_H
#define MENU_PAK_SNAPSHOT_SNAPSHOT_EVALUATESAVECHANNEL_H
#include "types.h"
/* Scores a channel for saving; returns 1 and fills bestCh and bestScore when a note of this game is found. */
extern s32 Snapshot_EvaluateSaveChannel(void *menu, s32 ch, s32 *bestCh, s32 *bestScore);
#endif
