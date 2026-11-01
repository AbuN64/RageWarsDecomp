#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "TYPES.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/GAMEPLAY_MOVEMENT.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "DATA/PLAYER_SWIMMING/PLAYER_SWIMMING_SOUND_IDS.H"
#include "WEAPONS/G_PLAYERSWIMCONSTANTS.H"

extern char g_playerSpecialAnimationTable;
s32 InstHdr_GetActorMotionState(void *);
extern void Graphu64_EaseValueToward(f32 *value, f32 target, f32 rate);
/* Updates swimming turn, pitch, stride motion, sounds, and animation. */
void Player_UpdateSwimmingState(SharedPlayer *player, SharedPlayer *body) {
    Shared_Game *game;
    f32 detachDistance;
    f32 jumpHeadingOffset;
    f32 previousClimbSpeed;
    f32 strafeHeadingOffset;
    f32 motionSine;
    f32 motionIntermediate;
    f32 jumpedHeading;
    f32 releaseTurn;
    f32 movementHeading;
    f32 jumpTurn;
    f32 strideRoll;
    f32 climbInput;
    f32 strafeInput;
    f32 rollInput;
    f32 strideTime;
    f32 climbAcceleration;
    f32 strafeAcceleration;
    f32 pitchLimit;
    f32 adjustedJumpHeading;
    f32 climbSpeedLimit;
    f32 strafeSpeedLimit;
    f32 turnLimit;
    f32 targetPitch;
    s32 surfaceFlagsOrActorKind;
    s32 jumpStarted;
    s32 descending;
    f32 *eyex;
    f32 *eyey;
    f32 *eyez;
    s32 actorKindOrAnimation;
    s32 ascending;

    if (!(body->views1C.view38_3.flags & 0x100)) {
        player->views5E8.view724_72.pitch = 0.0f;
        player->turnAccumulator = 0.0f;
        if (InstHdr_GetActorMotionState(body) == 0) {
            detachDistance = g_playerSwimConstants;
            player->views5E8.view6E8_79.movementPosition.x -= Gu_Sinf(body->views1C.view6C_5.heading) * detachDistance;
            player->views5E8.view6E8_79.movementPosition.z -= Math_Cosf(body->views1C.view6C_5.heading) * detachDistance;
        }
        Player_SetPlayerState(player, body, 5);
        return;
    }
    motionIntermediate = player->views5E8.view69C_39.stick;
    if ((g_playerClimbTurnZero < motionIntermediate) || (motionIntermediate < g_playerClimbTurnZero)) {
        player->turnAccumulator += motionIntermediate * g_playerClimbTurnInputScale;
    }
    motionIntermediate = player->turnAccumulator;
    turnLimit = g_playerClimbTurnMaximum;
    if (turnLimit < motionIntermediate) player->turnAccumulator = turnLimit;
    else if (motionIntermediate < g_playerClimbTurnMinimum) player->turnAccumulator=g_playerClimbTurnMinimum;
    Graphu64_EaseValueToward(&player->views5E8.view728_73.kickPitch, player->turnAccumulator * g_playerClimbYawSwayScale, 0.5f);
    targetPitch = -player->views5E8.view69C_39.pitchInput * g_playerClimbPitchInputScale;
    pitchLimit = g_playerClimbPitchMinimum;
    if ((targetPitch < pitchLimit) || (pitchLimit = g_playerClimbPitchMaximum, (pitchLimit < targetPitch))) {
        targetPitch = pitchLimit;
    }
    Graphu64_EaseValueToward(&player->views5E8.view724_72.pitch, targetPitch * g_playerClimbPitchScale, 0.0625f);
    if ((player->views5E8.view7E8_105.zoomed == 0) && !(player->views5E8.view6E4_61.jumpDelay > g_playerClimbJumpDelayLimit) && !(body->views1C.view38_3.flags & 0xC0000) && (body->views18.view18_2.model->flags & 2) && (player->views5E8.view6B0_46.actionFlags & 0x10) && (player->views5E8.view11D8_147.jumpCooldown <= 0.0f)) { Player_SetPlayerState(player, body, 5); jumpStarted = 1; } else jumpStarted = 0;
    if (jumpStarted != 0) {
        jumpedHeading = body->views1C.view6C_5.heading + player->views5E8.view728_73.kickPitch;
        body->views1C.view6C_5.heading = jumpedHeading;
        jumpTurn = player->views5E8.view728_73.kickPitch;
        if (g_playerClimbJumpPositiveWrapThreshold <= jumpTurn) {
            adjustedJumpHeading = jumpedHeading + g_playerClimbJumpPositiveYawPeriod;
            goto block_25;
        }
        if (jumpTurn <= g_playerClimbJumpNegativeWrapThreshold) {
            adjustedJumpHeading = jumpedHeading - g_playerClimbJumpNegativeYawPeriod;
block_25:
            body->views1C.view6C_5.heading = adjustedJumpHeading;
        }
        movementHeading = body->views1C.view6C_5.heading;
        jumpHeadingOffset = g_playerClimbJumpHeadingOffset;
        motionSine = Gu_Sinf(movementHeading + jumpHeadingOffset);
        motionIntermediate = Math_Cosf(body->views1C.view6C_5.heading + jumpHeadingOffset);
        body->views1C.view1C_0.localDisplacement.x += motionSine * g_playerClimbJumpDisplacementScale;
        body->views1C.view1C_0.localDisplacement.z += motionIntermediate * g_playerClimbJumpDisplacementScale;
        releaseTurn = player->views5E8.view728_73.kickPitch;
        if (g_playerClimbReleasePositiveWrapThreshold <= releaseTurn) {
            body->views1C.view6C_5.heading += g_playerClimbReleasePositiveYawPeriod;
        } else if (releaseTurn <= g_playerClimbReleaseNegativeWrapThreshold) {
            body->views1C.view6C_5.heading -= g_playerClimbReleaseNegativeYawPeriod;
        }
        player->views5E8.view728_73.kickPitch = 0.0f;
        player->turnAccumulator = 0.0f;
        return;
    }
    strideRoll = player->views5E8.view6DC_60.strideSign * player->views5E8.view6C0_51.movementSpeed * Gu_Sinf(player->views5E8.view658_23.stride * g_playerClimbStrideFrequency);
    rollInput = player->views5E8.view6A8_44.lift;
    if (rollInput > 0.0f || rollInput < 0.0f)
        Graphu64_EaseValueToward(&player->views5E8.view72C_75.strideRoll, strideRoll, 0.25f);
    else Graphu64_EaseValueToward(&player->views5E8.view72C_75.strideRoll, 0.0f, 0.9f);
    climbInput = player->views5E8.view6A8_44.lift;
    ascending = climbInput > 0.0f;
    descending = climbInput < 0.0f;
    previousClimbSpeed = player->views5E8.view6C0_51.movementSpeed;
    if ((ascending != 0) || (descending != 0)) {
        climbAcceleration = climbInput * g_playerClimbAcceleration;
        if (climbInput < 0.0f) {
            climbSpeedLimit = -climbInput * g_playerClimbReverseSpeedScale;
        } else {
            climbSpeedLimit = climbInput * g_playerClimbForwardSpeedScale;
        }
        player->views5E8.view6C0_51.movementSpeed = Graphu64_IntegrateBoundedValue(player->views5E8.view6C0_51.movementSpeed, climbAcceleration, climbSpeedLimit);
    } else {
        player->views5E8.view6C0_51.movementSpeed = Graphu64_DecayToZero(previousClimbSpeed, g_playerClimbForwardSpeedDecay);
    }
    strafeInput = player->views5E8.view6A4_42.strafe;
    if (strafeInput != 0.0f) {
        strafeAcceleration = strafeInput * g_playerClimbStrafeAcceleration;
        if (strafeInput < 0.0f) {
            strafeSpeedLimit = -strafeInput * g_playerClimbLeftSpeedScale;
        } else {
            strafeSpeedLimit = strafeInput * g_playerClimbRightSpeedScale;
        }
        player->views5E8.view6C4_54.sideSpeed = Graphu64_IntegrateBoundedValue(player->views5E8.view6C4_54.sideSpeed, strafeAcceleration, strafeSpeedLimit);
    } else {
        player->views5E8.view6C4_54.sideSpeed = Graphu64_DecayToZero(player->views5E8.view6C4_54.sideSpeed, g_playerClimbStrafeSpeedDecay);
    }
    if ((player->views5E8.view6C0_51.movementSpeed == 0.0f) && (player->views5E8.view6C4_54.sideSpeed == 0.0f)) {
        player->views5E8.view658_23.stride = 0.0f;
        if (previousClimbSpeed != 0.0f) {
            player->views5E8.view6DC_60.strideSign = -player->views5E8.view6DC_60.strideSign;
        }
    } else {
        strideTime = player->views5E8.view658_23.stride;
        if (g_playerClimbStridePeriod < strideTime) {
            player->views5E8.view6DC_60.strideSign = -player->views5E8.view6DC_60.strideSign;
            player->views5E8.view658_23.stride = strideTime - g_playerClimbStridePeriod;
            player->views5E8.view6C0_51.movementSpeed *= g_playerClimbSpeedDamping;
            player->views5E8.view6C4_54.sideSpeed *= g_playerClimbSpeedDamping;
            game = &g_gameSettings;
            if ((game->local != 0) && ((player->views5D8.view5D8_9.profile->remote != 1) || (game->fragTagEnabled == 0))) {
                surfaceFlagsOrActorKind = player->views1C.view38_3.flags;
                if (surfaceFlagsOrActorKind & 0x200) {
                    SoundElement_PlaySoundAtPosition(g_playerClimbStepSound, body->views0.view8_4.position, 0, -1);
                } else if (surfaceFlagsOrActorKind & 0x400) {
                    SoundElement_PlaySoundAtPosition(g_playerClimbReleaseSound, body->views0.view8_4.position, 0, -1);
                } else if (surfaceFlagsOrActorKind & 0x800) {
                    SoundElement_PlaySoundAtPosition(g_playerClimbJumpSound, body->views0.view8_4.position, 0, -1);
                } else {
                    SoundElement_PlaySoundAtPosition(strideSound(player->views5DC.view5E0_10.slot), body->views0.view8_4.position, 0, -1);
                }
            }
        }
    }
    eyex = &player->views5E8.view6E8_79.movementPosition.x;
    eyey = &player->views5E8.view6E8_79.movementPosition.y;
    eyez = &player->views5E8.view6E8_79.movementPosition.z;
    movementHeading = body->views1C.view6C_5.heading;
    strafeHeadingOffset = g_playerClimbStrafeHeadingOffset;
    motionSine = Gu_Sinf(movementHeading - strafeHeadingOffset);
    motionIntermediate = Math_Cosf(body->views1C.view6C_5.heading - strafeHeadingOffset);
    {
    f32 horizontal = *eyex + motionSine * player->views5E8.view6C4_54.sideSpeed * player->views5E8.view66C_29.movementTimeScale;
    f32 coefficient = k_playerSwimmingVerticalMotionScale;
    f32 frameDelta = g_frameElapsedTime;
    *eyex = horizontal;
    *eyez += motionIntermediate * player->views5E8.view6C4_54.sideSpeed * player->views5E8.view66C_29.movementTimeScale;
    motionIntermediate = *eyey + player->views5E8.view6C0_51.movementSpeed * (frameDelta * coefficient);
    *eyey = motionIntermediate;
    actorKindOrAnimation = g_fragTagModelId;
    surfaceFlagsOrActorKind = player->views1C.viewE4_7.kind;
    if (surfaceFlagsOrActorKind != actorKindOrAnimation) { if (player->views5E8.view6C0_51.movementSpeed > 0.0f) { if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) player->views5E8.view86C_125.animationId = 2630; else player->views5E8.view86C_125.animationId = 24104; } else { if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) player->views5E8.view86C_125.animationId = 2620; else player->views5E8.view86C_125.animationId = 24103; } } else { actorKindOrAnimation = 2630; player->views5E8.view86C_125.animationId = actorKindOrAnimation; }
}}
