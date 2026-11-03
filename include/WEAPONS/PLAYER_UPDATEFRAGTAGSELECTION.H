#ifndef WEAPONS_PLAYER_UPDATEFRAGTAGSELECTION_H
#define WEAPONS_PLAYER_UPDATEFRAGTAGSELECTION_H
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
extern void Playerai_StopInactivePlayerSounds(char *);
struct ViewState;
void Player_DrawMatchCountdown(void *unusedPlayer, struct ViewState *viewState);
struct Round;
void Player_ReleaseWaitingPlayer(struct Round *round);
void Player_UpdateFragTagSelection(s8 *world);
struct GamePlayerListView;
void Playerai_DrawPlayerModelsForView(struct GamePlayerListView *game, s32 view);
struct Shared_ActorView;
void Playerai_ToggleForceMarkerEuropean(struct Shared_ActorView *player, s32 attract);
struct PlayerWorldActorTables;
void Playerai_UpdateRoundLimits(struct PlayerWorldActorTables *world);
void Playerai_UpdateViewModelBounds(void *game, void *view);
#endif
