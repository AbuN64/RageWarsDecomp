#ifndef OVLGAME_MATCH_H
#define OVLGAME_MATCH_H
extern int g_sessionOptionResetMode;
void Match_ResetMatchControllerState(char *match);
extern void Match_ResetGameClockAndSelectSpawn(struct GameSession *);

#include "Common/game_session.h"
extern void Match_StartMatchTransition(struct GameSession *, s32);
#endif
