#ifndef CTEAMSELECT_CTEAMSELECT_DRAWTEAMICONS_H
#define CTEAMSELECT_CTEAMSELECT_DRAWTEAMICONS_H
struct TeamMenu;
struct TeamMenuIconView;
struct SharedPlayer;
void Cteamselect_DrawTeamIcons(struct TeamMenu *menu, struct TeamMenuIconView *items, s32 count, struct SharedPlayer *player);
extern s32 Cteamselect_GetFourWayStickSlot(void *object);

#endif
