#ifndef PLAYER_UPDATEPLAYERCAMERA_PLAYER_UPDATEPLAYERCAMERA_H
#define PLAYER_UPDATEPLAYERCAMERA_PLAYER_UPDATEPLAYERCAMERA_H
struct LevelActor;
s32 Player_AddAmmo(void *player, s32 slot, s32 amount);
struct Shared_HudPlayer;
struct Shared_HudView;
void Player_DrawHeadsUpDisplay(struct Shared_HudPlayer *player, struct Shared_HudView *view);
struct SharedPlayer;
struct PlayerBodyMotionView;
struct SharedMovement;
void Player_UpdateFlyingThrustAndBoost(struct SharedPlayer *player, struct PlayerBodyMotionView *body, struct SharedMovement *movementProfile);
struct PlayerBodyPositionYawView;
void Player_UpdateGroundThrustAndBoost(struct SharedPlayer *player, struct PlayerBodyPositionYawView *body, struct SharedMovement *movementProfile);
struct PlayerWeaponsUpdatePlayerCamera;
struct BodyWeaponsUpdatePlayerCamera;
void Player_UpdatePlayerCamera(struct PlayerWeaponsUpdatePlayerCamera *player, struct BodyWeaponsUpdatePlayerCamera *body);
void Player_UpdateWeaponSwayAndBob(struct SharedPlayer *player, struct LevelActor *camera);
#endif
