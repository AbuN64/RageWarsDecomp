#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/GAMEPLAY_ROUND_RULES.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/VIEWFLAGS.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "CAMERA/GSKY_RESETHEADBOB.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"

extern const f32 g_playerImpactMinimumVerticalSpeed;

extern void TeamSelect_EmptyWeaponWheelHook();

extern s32 SoundElement_PlaySoundAtPosition(s16 track, CVector3 soundPosition, s32 position, s32 ownerId);

/* Runs a player's landing state: sets state 0xD when the value at 0x6C8 is zero or 0xE otherwise,
   applies the movement tables g_playerFloatViewAngleParameters and g_playerFloatMovementParameters, picks animation 0x8A2 for the model
   g_fragTagModelId or, unless animation 0x1144 is still running with the byte at 0x10E clear, 0x8A2, 0x8A7
   or 0x14 by the stick at 0x6C0 against g_playerFloatForwardAnimationThreshold and g_playerFloatReverseAnimationThreshold, and switches to state 3 once the
   timer at 0x658 passes g_playerFloatPoseMinimumDuration without input bit 0x20000. */

extern void Player_UpdateViewAngles(void *, void *, void *);

extern void Player_UpdateFlyingThrustAndBoost(void *, void *, void *);




extern f32 g_playerRoundEndWaitConstants;

extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);


extern void Graphu64_ScaleVector(struct CVector3_t *,struct CVector3_t *,f32);

extern void Graphu64_AddVec3(CVector3 *, CVector3 *, CVector3 *);

extern void Player_ReleaseObjectHandles(s32 object);

void Player_AbsorbImpact(void *player, LevelActor *actor) {
    f32 value;
    f32 minimum;
    ((Shared_ActorView *)player)->forwardSpeed *= g_playerImpactHorizontalDamping;
    ((Shared_ActorView *)player)->lateralSpeed *= g_playerImpactHorizontalDamping;

    value = actor->position1.y * g_playerImpactVerticalDamping;
    minimum = g_playerImpactMinimumVerticalSpeed;
    actor->position1.y = value;
    if (value < minimum) {
        actor->position1.y = minimum;
    }

    ((Shared_ActorView *)player)->collisionState = 0;
    Gsky_ResetHeadBob(((Shared_ActorView *)player)->message);
    TeamSelect_EmptyWeaponWheelHook(((FragTagPlayerStateView *)player)->animationState);

    if (actor->motionState & 0x8000) {
        SoundElement_PlaySoundAtPosition(730, actor->position0, 0, -1);
    } else {
        SoundElement_PlaySoundAtPosition(732, actor->position0, 0, -1);
    }
}

/** Scales the floats at 0x6C0 and 0x6C4 of the first object and the float at 0x20 of the second by g_playerMotionDamping. */








void Player_DampMotion(void *actorState, void *levelActor) {
    Shared_ActorView *actor = actorState;
    LevelActor *other = levelActor;
    actor->forwardSpeed = actor->forwardSpeed * (g_playerMotionDamping);
    actor->lateralSpeed = actor->lateralSpeed * (g_playerMotionDamping);
    other->position1.y = other->position1.y * (g_playerMotionDamping);
}

void Player_UpdateFloatPose(void *playerState, LevelActor *actor) {
    Player *player;
    s32 busy;
    f32 x;

    player = playerState;
    if (player->landing == 0.0f) {
        player->pose = 13;
    } else {
        player->pose = 14;
    }
    Player_UpdateViewAngles(player, actor, &g_playerFloatViewAngleParameters);
    Player_UpdateFlyingThrustAndBoost(player, actor, &g_playerFloatMovementParameters);
    busy = 0;
    if (player->animation == 4420) {
        busy = player->animationDone == 0;
    }
    if (player->objectId == g_fragTagModelId) {
        player->animation = 2210;
    } else if (!busy) {
        x = player->stick;
        if (g_playerFloatForwardAnimationThreshold <= x) {
            player->animation = 2210;
        } else if (x <= g_playerFloatReverseAnimationThreshold) {
            player->animation = 2215;
        } else {
            player->animation = 20;
        }
    }
    if (!(actor->motionState & 0x20000) && player->poseTimer > g_playerFloatPoseMinimumDuration) {
        Player_SetPlayerState(player, actor, 3);
    }
}

void Player_ResetMovementInput(void *motionPlayerState, LevelActor *actor)
{
  f32 roundEndMovementScale;
  f32 *movementScale;
  s8 *playerStateBytes;
  playerStateBytes = (s8 *) motionPlayerState;
  roundEndMovementScale = (f32) g_playerRoundEndWaitConstants;
  ((Player *)playerStateBytes)->stick = 0;
  movementScale = &((Player *)motionPlayerState)->movementScale;
  ((Player *)motionPlayerState)->state6C4 = 0;
  *movementScale = roundEndMovementScale;
  actor->position1.x = 0;
  actor->position1.y = 0;
  actor->position1.z = 0;
}

void Player_ResetObjectVelocity(void *unused, void *object) {
    LevelActor *actor = object;
    actor->position1.x = 0.0f;
    actor->position1.y = 0.0f;
    actor->position1.z = 0.0f;
}

/** Perform no operation. */
void Player_EmptyHandlerAfterResetObjectVelocity_de(void) {
}

/** Perform no operation. */
void Player_EmptyHandlerBeforeAimPreviousPositionAtReset_de(void) {
}

void Player_AimPreviousPositionAtReset(void *aimPlayerState) {
    CVector3 vector;
    CVector3 *weaponAimPositionPtr;

    weaponAimPositionPtr = &((Shared_ActorView *)aimPlayerState)->weapon.aimPosition;
    Graphu64_SubtractVectors(&vector, &((Shared_ActorView *)aimPlayerState)->resetPosition, weaponAimPositionPtr);
    Graphu64_NormalizeVec3(&vector);
    Graphu64_ScaleVector(&vector, &vector, 30.0f);
    Graphu64_AddVec3(&((Player *)aimPlayerState)->previousPosition, weaponAimPositionPtr, &vector);
}

void Player_EmptyHandlerAfterAimPreviousPositionAtReset_de(void) {
}

void Player_ResetStunAndReleaseHandles(void *widget) {
    LevelActor *actor = widget;
    Shared_ActorView *player = widget;
    actor->flags &= 0xFF7FFFFF;
    player->stun = 0;
    player->marker.time = 0.0f;
    actor->flags |= 0x01000000;
    Player_ReleaseObjectHandles((s32) widget);
}

void Player_EmptyHandlerAfterResetStunAndReleaseHandles_de(void) {
}

/** Reset two object fields and replace the control word's mode bit. */
void Player_ResetStunFlags(void *actorState) {
    Shared_ActorView *actor = actorState;
    actor->flags &= 0xFF7FFFFF;
    actor->stun = 0;
    actor->marker.word = 0;
    actor->flags |= 0x01000000;
}

/** Perform the no-op callback at VRAM 0x8022D278. */
void Player_EmptyHandlerAfterResetStunFlags_de(void) {
}
