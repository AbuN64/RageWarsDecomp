#ifndef AI_PLAYER_PLAYERAI_FINDTRANSIENTPLAYER_H
#define AI_PLAYER_PLAYERAI_FINDTRANSIENTPLAYER_H
struct Player16C0;
void Playerai_DrawAimMarker(struct Player16C0 *player);
void Playerai_DrawPlayersForView(void *world, void *view);
void Playerai_DrawViewMatchCountdown(void *roundContext, void *viewState);
void Playerai_DrawViewPlayer(void *world, void *view);
struct Context;
void *Playerai_FindTransientPlayer(struct Context *context);
int Playerai_GetFirstPlayer(void *world);
struct CPlayerPool_t;
void Playerai_UpdatePlayerRenderResources(struct CPlayerPool_t *playerPool, void *world);
void Playerai_UpdateViewPlayerProjection(void *roundContext, void *entity);
#endif
