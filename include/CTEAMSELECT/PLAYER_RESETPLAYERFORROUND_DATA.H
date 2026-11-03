#ifndef CTEAMSELECT_PLAYER_RESETPLAYERFORROUND_DATA_H
#define CTEAMSELECT_PLAYER_RESETPLAYERFORROUND_DATA_H
void TeamSelect_CloseTeamWheel(void *record);
void TeamSelect_DrawTeamWheelSprites(s32 menu, s32 unused1, s32 player);
struct TeamMenu;
void TeamSelect_ResetTeamWheel(struct TeamMenu *menu);
#endif
