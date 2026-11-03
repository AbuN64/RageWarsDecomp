#ifndef AI_PLAYER_PLAYER_BUILDPLAYERVIEWTRANSFORM_H
#define AI_PLAYER_PLAYER_BUILDPLAYERVIEWTRANSFORM_H
struct PlayerList;
void Player_AllocPlayerList(struct PlayerList *list, int count);
struct Player;
struct CQuatern_t;
void Player_BuildPlayerOrientation(struct Player *player, struct CQuatern_t *output);
void Player_BuildPlayerViewTransform(struct Player *player, f32 out[4][4]);
#endif
