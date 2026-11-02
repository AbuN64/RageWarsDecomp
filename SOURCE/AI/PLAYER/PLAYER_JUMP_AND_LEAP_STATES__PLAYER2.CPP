#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "SOUND/PLAYER_MOVEMENT_SCALAR_VIEW.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "COMMON/PROBE.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
extern s32 Player_SetPlayerState(void *, void *, s32);
extern void Player_UpdateGroundThrustAndBoost(void *, void *, void *);
extern void Player_UpdateViewAngles(void *, void *, void *);
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"

/* Runs a player's grounded movement state: updates it through Player_EaseOwnerHeightEffect_PlayerJumpAndLeapStates, eases the value at
   0x72C to zero by a quarter, applies the movement tables g_playerGroundViewAngleParameters and g_playerGroundMovementParameters, then leaves for
   state 2 when not on the ground (animation 0x5E24 for the g_playerSpecialAnimationTable state table, otherwise 1), or
   picks the animation from the stick at 0x6C0 and 0x6C4: 0xA64 at rest, 0xA67 or 0xA66 when the
   second axis dominates and 0xA65 or 0xA68 otherwise, by the sign of the dominant axis. */

extern void Player_EaseOwnerHeightEffect(void *, void *);




extern s32 g_playerSpecialAnimationTable;

extern s32 g_activeActorKind;


extern u8 *InstHdr_GetEnabledItemValue(void *item);

extern void InstHdr_GetActorTargetOffset(u8 *player, CVector3 *vector);

/* Phase1 source candidate; contract holds and immutable inputs in per-function JSON. */



extern s32 InstHdr_GetActorMotionState(void *levelActor);

extern f32 InstHdr_GetShadowGroundHeight(void *object, s32 mode);




extern int g_globalGameplayFlags;

void Player_StartMovingOnStickInput(struct SharedPlayer *player, void *bodyActor) {
    if ((player->views5E8.view6C0_51.movementSpeed != 0.0f) || (player->views5E8.view6C4_54.sideSpeed != 0.0f)) {
        Player_SetPlayerState(player, bodyActor, 3);
    }
}

void Player_EmptyHandlerAfterStartMovingOnStickInput_de(void) {
}

void Player_EmptyHandlerBeforeUpdateGroundMoveState_de(void) {
}

void Player_UpdateGroundMoveState(struct SharedPlayer *player, void *bodyActor) {
    f32 x;
    f32 y;
    f32 zero;

    Player_EaseOwnerHeightEffect(player, bodyActor);
    zero = 0.0f;
    Graphu64_EaseValueToward(&player->views5E8.view72C_75.strideRoll, zero, 0.25f);
    Player_UpdateViewAngles(player, bodyActor, &g_playerGroundViewAngleParameters);
    Player_UpdateGroundThrustAndBoost(player, bodyActor, &g_playerGroundMovementParameters);
    if (!(player->views5E8.view6AC_45.inputFlags & 0x10)) {
        Player_SetPlayerState(player, bodyActor, 2);
        if (player->views13B4.view13B4_3.character == &g_playerSpecialAnimationTable) {
            player->views5E8.view86C_125.animationId = 24100;
        } else {
            player->views5E8.view86C_125.animationId = 1;
        }
    } else {
        x = player->views5E8.view6C0_51.movementSpeed;
        if (x != zero || player->views5E8.view6C4_54.sideSpeed != zero) {
            y = player->views5E8.view6C4_54.sideSpeed;
            if (x < y) {
                if (zero < y) {
                    player->views5E8.view86C_125.animationId = 2663;
                } else {
                    player->views5E8.view86C_125.animationId = 2662;
                }
            } else if (zero < x) {
                player->views5E8.view86C_125.animationId = 2661;
            } else {
                player->views5E8.view86C_125.animationId = 2664;
            }
        } else {
            player->views5E8.view86C_125.animationId = 2660;
        }
    }
}

void Player_BeginJump(Player *player, void *bodyActor) {
    CVector3 vector;
    f32 scale;
    u8 *result;
    u8 state;
    s32 mode;
    CGameStatus *audio;

    scale = g_playerJumpInitialSpeedScale;
    if (g_activeActorKind == 7601) {
        scale = g_playerJumpInitialSpeedScaleSpecial;
    }
    ((LevelActor *)bodyActor)->position1.y =
        scale * ((Resource_u1 *)((LevelActor *)bodyActor)->definition)->value20;
    result = InstHdr_GetEnabledItemValue(bodyActor);
    if (result != 0) {
        InstHdr_GetActorTargetOffset(result, &vector);
        Graphu64_AddVec3(&((LevelActor *)bodyActor)->position1,
                      &((LevelActor *)bodyActor)->position1, &vector);
    }

    state = ((Shared_ControlView *)player->profile)->transientFlag;
    if (state == 1) {
        audio = &g_gameSettings.counters;
        if (audio->m_bFragTagOn != 0) {
            mode = audio->m_nFragTagSkin;
            switch (mode) {
        case 0:
            SoundElement_PlaySoundAtPosition(6305,
                          player->pos,
                          (s32)&player->pos, -1);
            break;
        case 1:
            SoundElement_PlaySoundAtPosition(6505,
                          player->pos,
                          (s32)&player->pos, -1);
            break;
        case 2:
            SoundElement_PlaySoundAtPosition(6405,
                          player->pos,
                          (s32)&player->pos, -1);
            break;
            }
        }
    }
}

void Player_UpdateJumpAscent(void *player, LevelActor *actor) {
    f32 scale;

    scale = g_playerJumpAscentSpeedScale;
    if (g_activeActorKind == 7601) {
        scale = g_playerJumpAscentSpeedScaleSpecial;
    }
    if (((Player *)player)->computer != 0) {
        f32 current;

        current = ((Player *)player)->poseTimer;
        if (g_playerBotJumpAscentLimit <= current) {
            goto transition;
        }
        goto scale_value;
    }
    if (!(((Player *)player)->inputFlags & 0x10)) {
        goto transition;
    } else {
        f32 current;

        current = ((Player *)player)->poseTimer;
        if (!(g_playerHumanJumpAscentLimit <= current)) {
            goto scale_value;
        }
    }
transition:
    Player_SetPlayerState(player, actor, 6);
    goto finish;
scale_value:
    actor->position1.y =
        scale * ((Resource_u1 *)actor->definition)->value20;
finish:
    Player_UpdateJumpAirMotion(player, actor);
}

void Player_UpdateJumpAirMotion(void *player, void *body) {
    s32 value;

    Graphu64_EaseValueToward(&((Player *)player)->lean, 0.0f, 0.25f);
    Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    if (!(((Player *)player)->flags660 & 0x8000)) {
        Player_UpdateGroundThrustAndBoost(player, body, &g_playerJumpMovementParameters);
    }
    if (((LevelActor *)body)->position1.y <= 0.0f) {
        if (InstHdr_GetActorMotionState(body) != 0) {
            Player_SetPlayerState(player, body, 2);
        }
    }
    if (((LevelActor *)body)->position1.y <= 0.0f) {
        if (InstHdr_GetShadowGroundHeight(body, 0) < 0.0f) {
            if (-InstHdr_GetShadowGroundHeight(body, 0) < g_playerJumpLandingHeightLimits[0]) {
                goto set_value;
            }
        } else if (InstHdr_GetShadowGroundHeight(body, 0) < g_playerJumpLandingHeightLimits[1]) {
set_value:
            if (((Player *)player)->animationTable == &g_playerSpecialAnimationTable) {
                ((Player *)player)->animation = 24110;
            } else {
                ((Player *)player)->animation = 2040;
            }
        }
    }
}

void Player_BeginLateralLeap(void *movementState, void *actorMotion) {
    if ((((struct PlayerStrafeVelocityView *) ((s8 *) movementState))->strafe) < 0.0f) {
        (((struct PlayerStrafeVelocityView *) ((s8 *) movementState))->lateralLeapSpeed) = (f32) g_playerLateralLeapNegativeInputSpeed;
    } else {
        (((struct PlayerStrafeVelocityView *) ((s8 *) movementState))->lateralLeapSpeed) = (f32) g_playerLateralLeapPositiveInputSpeed;
    }
    (((struct PlayerMovementScalarView *) ((s8 *) actorMotion))->scalar) = (f32) g_playerLateralLeapInitialVerticalSpeed;
}

void Player_UpdateLateralLeap(void *player, LevelActor *actor) {
    f32 currentLateralSpeed;

    currentLateralSpeed = ((Shared_ActorView *)player)->lateralSpeed;
    if ((currentLateralSpeed < 0.0f && ((Shared_ActorView *)player)->lateralInput >= 0.0f) ||
        (currentLateralSpeed > 0.0f && ((Shared_ActorView *)player)->lateralInput <= 0.0f) ||
        (((Shared_ActorView *)player)->actionTimer >= g_playerLateralLeapDuration)) {
        Player_SetPlayerState(player, actor, 8);
    } else {
        actor->position1.y = g_playerLateralLeapVerticalSpeed;
    }
    Player_UpdateLeapMotion((s32)player, (s32)actor);
}

void Player_UpdateLeapMotion(s32 player, s32 body) {
    Graphu64_EaseValueToward(player + 1836, 0.0f, 0.25f);
    Player_UpdateViewAngles((void *)player, (void *)body, &g_playerAirViewAngleParameters);
    Player_UpdateGroundThrustAndBoost((void *)player, (void *)body, &g_playerLeapMovementParameters);
    if (((LevelActor *)body)->position1.y <= 0.0f) {
        if (InstHdr_GetActorMotionState((void *) body) != 0) {
            Player_SetPlayerState((void *) player, (void *) body, 2);
        }
    }
}

void Player_ClearGlobalFlagBit(void) {
    int *p = &g_globalGameplayFlags;
    *p &= 0xFFEFFFFF;
}
