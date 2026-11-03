#ifndef PLAYERAI_PLAYERAI_PLAYERAI_H
#define PLAYERAI_PLAYERAI_PLAYERAI_H
struct Player;
void Player_ResetPlayerWeapons(struct Player *player);
struct Cursor;
void Playerai_AdvanceRouteCursor(struct Cursor *cursor);
void Playerai_DrawAnimatedSprite(char *object, char *camera);
struct CompactAnimationState;
void Playerai_InitializeCompactAnimationState(struct CompactAnimationState *record);
#endif
