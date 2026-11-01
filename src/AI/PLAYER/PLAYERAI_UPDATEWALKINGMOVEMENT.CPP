#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/VECTOR4F.H"

extern void Graphu64_EaseValueToward(f32 *value, f32 target, f32 rate);
extern void Player_UpdateViewAngles(SharedPlayer *,PlayerBodyPositionYawView *,char *);
extern char g_playerSpecialAnimationTable;
extern f32 g_frameElapsedTime;
extern f32 g_playerWalkingCrouchThreshold,g_playerWalkingCrouchReleaseThreshold,g_playerWalkingJumpDelayLimit,g_playerWalkingStepSpeedThreshold,g_playerWalkingStepInterval,g_playerWalkAnimationSwapTime,g_playerWalkFireFA0Duration,g_playerWalkFire1004Duration,g_playerWalkFire5E5BDuration,g_playerWalkFire5E56Duration,g_playerWalkFire5E5CDuration,g_playerWalkFire5E57Duration,g_playerWalkFire5E59Duration,g_playerWalkFire5E54Duration,g_playerWalkFire5E5ADuration,g_playerWalkFire5E55Duration;
/* State callbacks receive an opaque actor context. */
void Playerai_UpdateWalkingMovement(void *playerContext, void *bodyContext) {
    SharedPlayer *player = playerContext;
    PlayerBodyPositionYawView *body = bodyContext;
    f32 strafeSpeed;
    f32 elapsedStepTime;
    f32 forwardSpeedMagnitude;
    s32 currentFireAnimation;
    s32 leftStrafeAnimation;
    s32 rightStrafeAnimation;
    s32 forwardAnimation;
    s32 backwardAnimation;
    s32 crouchingView;
    s32 crouchingMovement;
    s32 jumpStarted;
    s32 animationChoice;
    char *primaryFireMode;
    char *secondaryFireMode;
    u16 kind;
    s32 nextAnimation;

    Player_EaseOwnerHeightEffect(playerContext);
    Graphu64_EaseValueToward(&player->views5E8.view72C_75.strideRoll, 0.0f, 0.25f);
    crouchingView = 1;
    if (!(player->views5E8.view718_70.crouch > g_playerWalkingCrouchThreshold)) {
        crouchingView = 0;
    }
    if (crouchingView != 0) {
        Player_UpdateViewAngles(player, body, &g_playerGroundViewAngleParameters);
    } else {
        Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    }
    crouchingMovement = 1;
    if (!(player->views5E8.view718_70.crouch > g_playerWalkingCrouchReleaseThreshold)) {
        crouchingMovement = 0;
    }
    if (crouchingMovement != 0) {
        Player_UpdateGroundThrustAndBoost(player, body, &g_playerGroundMovementParameters);
    } else {
        Player_UpdateGroundThrustAndBoost(player, body, &g_playerJumpMovementParameters);
    }
    if ((player->views5E8.view7E8_105.zoomed == 0) && !(player->views5E8.view6E4_61.jumpDelay > g_playerWalkingJumpDelayLimit) && !(body->flags & 0xC0000) && (body->model->flags & 2) && (player->views5E8.view6B0_46.actionFlags & 0x10) && (player->views5E8.view11D8_147.jumpCooldown <= 0.0f)) { Player_SetPlayerState(player, body, 5); jumpStarted = 1; } else jumpStarted = 0;
    if (jumpStarted == 0) {
        if ((player->views5E8.view6C0_51.movementSpeed == 0.0f) && (player->views5E8.view6C4_54.sideSpeed == 0.0f)) {
            Player_SetPlayerState(player, body, 2);
        }
        if (((body->flags & 0x5000) == 0x4000) && (player->views5E8.view6D0_71.onGround != 0)) {
            elapsedStepTime = player->views5E8.view11C4_144.soundTime + g_frameElapsedTime;
            player->views5E8.view11C4_144.soundTime = elapsedStepTime;
            if ((player->views5E8.view6C8_56.speed > g_playerWalkingStepSpeedThreshold) && (g_playerWalkingStepInterval <= elapsedStepTime)) {
                player->views5E8.view11C4_144.soundTime = (f32) (elapsedStepTime - g_playerWalkingStepInterval);
            }
        }
        kind = player->views1C.viewE4_7.kind;
        if (kind == g_playerSpecialModelIds[2]) {
            if (player->views5E8.view86C_125.animationId == 2010 && player->views1C.view104_11.idleTime >= g_playerWalkAnimationSwapTime) player->views5E8.view86C_125.animationId = 2011; else player->views5E8.view86C_125.animationId = 2010;
            return;
        }
        if (kind == g_playerSpecialModelIds[0]) {
            currentFireAnimation = player->views5E8.view86C_125.animationId;
            if (currentFireAnimation == 4000 && player->views1C.view104_11.idleTime < g_playerWalkFireFA0Duration) return;
            if (currentFireAnimation == 4100 && player->views1C.view104_11.idleTime < g_playerWalkFire1004Duration) return;
        }
        if (body->flags & 0xC0000) {
            if (player->views5E8.view6C0_51.movementSpeed >= 0.0f) player->views5E8.view86C_125.animationId = 2610;
            else player->views5E8.view86C_125.animationId = 2615;
            return;
        }
        forwardSpeedMagnitude = player->views5E8.view6C0_51.movementSpeed;
        if (forwardSpeedMagnitude < 0.0f) forwardSpeedMagnitude = -forwardSpeedMagnitude;
        strafeSpeed = player->views5E8.view6C4_54.sideSpeed;
        if (strafeSpeed < 0.0f) {
            if (forwardSpeedMagnitude < -strafeSpeed) goto sideways;
            goto forward;
        }
        if (forwardSpeedMagnitude < strafeSpeed) {
sideways:
            if (player->views5E8.view6C4_54.sideSpeed < 0.0f) {
                if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) { player->views5E8.view86C_125.animationId = 2050; return; }
                leftStrafeAnimation = player->views5E8.view86C_125.animationId;
                if ((u32)(leftStrafeAnimation - 24150) < 7U) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFire5E5BDuration) player->views5E8.view86C_125.animationId = 24107;
                    return;
                }
                if (leftStrafeAnimation == 24158) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFire5E56Duration) player->views5E8.view86C_125.animationId = 24107;
                    return;
                }
                player->views5E8.view86C_125.animationId = 24107;
            } else {
                if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) { player->views5E8.view86C_125.animationId = 2060; return; }
                rightStrafeAnimation = player->views5E8.view86C_125.animationId;
                if ((u32)(rightStrafeAnimation - 24150) < 7U) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFire5E5CDuration) player->views5E8.view86C_125.animationId = 24108;
                    return;
                }
                if (rightStrafeAnimation == 24158) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFire5E57Duration) player->views5E8.view86C_125.animationId = 24108;
                    return;
                }
                player->views5E8.view86C_125.animationId = 24108;
            }
        } else {
forward:
            if (player->views5E8.view6C0_51.movementSpeed >= 0.0f) {
                if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) { player->views5E8.view86C_125.animationId = 2010; return; }
                forwardAnimation = player->views5E8.view86C_125.animationId;
                if ((u32)(forwardAnimation - 24150) < 9U) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFire5E59Duration) player->views5E8.view86C_125.animationId = 24105;
                    return;
                }
                if (forwardAnimation == 24158) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFire5E54Duration) player->views5E8.view86C_125.animationId = 24105;
                    return;
                }
                player->views5E8.view86C_125.animationId = 24105;
            } else {
                if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) { player->views5E8.view86C_125.animationId = 2015; return; }
                backwardAnimation = player->views5E8.view86C_125.animationId;
                if ((u32)(backwardAnimation - 24150) < 7U) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFire5E5ADuration) player->views5E8.view86C_125.animationId = 24106;
                    return;
                }
                nextAnimation = 24158;
                if (backwardAnimation != nextAnimation) {
                    nextAnimation = 24106;
                    player->views5E8.view86C_125.animationId = nextAnimation;
                } else {
                    nextAnimation = 24106;
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFire5E55Duration) player->views5E8.view86C_125.animationId = nextAnimation;
                }
            }
        }
    }
}
