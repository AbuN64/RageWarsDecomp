#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/PLAYER_RECORD_AND_FRAGTAG_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "GFX/TEXT/PLAYER_CAMERA_CALLBACK.H"


/* Initialises an object: clears the words at 0x8, 0x9C, 0xA4, 0xA8, 0xB4 and 0xB8, sets the words at
   0x0 and 0x4 to -1, writes the two constants at k_playerRecordDefaultPair into the floats at 0xAC and 0xB0, the two
   at k_playerRecordDefaultVectorValues into the floats at 0x90, 0x94 and 0x98 (the first of them twice) and k_playerRecordDefaultScalar into
   the float at 0xA0. */


void Player_InitRecordDefaults(void *record) {
    PlayerRecordDefaultsView *obj = record;
    float f1 = k_playerRecordDefaultPair;
    float f2 = *(float *)((char *)&k_playerRecordDefaultPair + 4);
    float f0 = k_playerRecordDefaultVectorValues;
    float f3 = *(float *)((char *)&k_playerRecordDefaultVectorValues + 4);
    float f4 = k_playerRecordDefaultScalar;

    obj->reservedStateOne = 0;
    obj->resetState = 0;
    obj->reservedStateTwo = 0;
    obj->secondKey = -1;
    obj->firstKey = -1;
    obj->reservedState = 0;
    obj->vectorState = 0;
    obj->scalarState = 0;
    obj->defaultFirstFloat = f1;
    obj->defaultSecondFloat = f2;
    obj->initialVectorX = f0;
    obj->initialVectorY = f3;
    obj->initialVectorZ = f0;
    obj->scalarValue = f4;
}

s32 Playerai_TryEnterMotionFlagState(void *player, void *bodyActor) {
    s16 state = ((Shared_ActorView *)player)->action;
    s32 blocked;

    if ((state == 21) || (state == 19) || (state == 20)) {
        blocked = 1;
    } else {
        blocked = 0;
    }
    if (blocked == 0) {
        if ((((LevelActor *)bodyActor)->motionState & 0x20000) == 0) {
            return 0;
        }
        if (((Shared_ActorView *)player)->action == 13) {
            return 0;
        }
        if (((Shared_ActorView *)player)->action == 14) {
            return 0;
        }
        Player_SetPlayerState(player, bodyActor, 13);
        return 1;
    }
    return 0;
}

s32 Playerai_TryEnterBodyFlagState(void *player, void *bodyActor) {
    s16 state = ((Shared_ActorView *)player)->action;
    s32 blocked;
    s32 flags;

    if ((state == 21) || (state == 19) || (state == 20)) {
        blocked = 1;
    } else {
        blocked = 0;
    }
    if (blocked == 0) {
        if (((MovementDescriptor *)((LevelActor *)bodyActor)->definition)->body.header.flags & 1) {
            if (((Shared_ActorView *)player)->action == 38) {
                return 0;
            }
            if (((Shared_ActorView *)player)->unk_0x0664 & 0x8000) {
                return 0;
            }
            flags = ((LevelActor *)bodyActor)->motionState;
            if (flags & 0x80) {
                goto fire;
            }
        }
        return 0;
    }
    return 0;
fire:
    ((LevelActor *)bodyActor)->motionState = flags | 0x100;
    Player_SetPlayerState(player, bodyActor, 15);
    return 1;
}

s32 Player_TryStartJump(void *player, LevelActor *actor) {
    f32 jumpDelay;

    if (((Shared_ActorView *)player)->unk_0x07E8 == 0) {
        jumpDelay = ((Shared_ActorView *)player)->unk_0x06E4;
        if (!(g_playerJumpInputDelayLimit < jumpDelay)) {
            if (!(actor->motionState & 0xC0000)) {
                if (((MovementDescriptor *)actor->definition)->body.header.flags & 2) {
                    if ((((Shared_ActorView *)player)->unk_0x06B0 & 0x10) && (((Shared_ActorView *)player)->stun <= 0.0f)) {
                        Player_SetPlayerState(player, actor, 5);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

/** Return zero. */
int Player_ReturnZeroStub(void *unused0, void *unused1, s32 *unused2) {
    return 0;
}

void Player_ZeroBodyVelocity(void *unusedPlayer, LevelActor *actor) {
    actor->position1.x = 0;
    actor->position1.y = 0;
    actor->position1.z = 0;
}
