#ifndef WEAPONS_PLAYER_UPDATEFRAGTAGSELECTION_H
#define WEAPONS_PLAYER_UPDATEFRAGTAGSELECTION_H
#include "Common/scene_frame_and_effect_updates.h"
extern void Playerai_StopInactivePlayerSounds(char *);
struct ViewState;
void Player_DrawMatchCountdown(void *unusedPlayer, struct ViewState *viewState);
struct Round;
void Player_ReleaseWaitingPlayer(struct Round *round);
void Player_UpdateFragTagSelection(s8 *world);
struct Shared_MenuData;
void Playerai_DrawPlayerModelsForView(struct Shared_MenuData *game, s32 view);
struct Player;
void Playerai_ToggleForceMarkerEuropean(struct Player *player, s32 attract);
struct PlayerWorldActorTables;
void Playerai_UpdateRoundLimits(struct PlayerWorldActorTables *world);
void Playerai_UpdateViewModelBounds(void *game, void *view);
#endif
