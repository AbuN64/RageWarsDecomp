#ifndef AI_PLAYER_PLAYER_MODEL_AND_HELD_WEAPON_RENDERING_H
#define AI_PLAYER_PLAYER_MODEL_AND_HELD_WEAPON_RENDERING_H
#include "types.h"
#include "Common/small_records.h"

struct ScalarPair;


#include "Common/gameplay_camera.h"
#include "Common/frag_tag_scores.h"
extern void Player_DrawPlayerModel(void *player, void *renderContext);
extern void Player_DrawHeldWeapon(void *player, struct GameplayCamera *weaponView);
#endif
