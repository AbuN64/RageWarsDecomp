#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "SOUND/EXTERNS.H"
#include "COMMON/PLAYER_ACTION_AND_POSE_VIEWS.H"
#include "TYPES.H"
#include "SOUND/PLAYERAI_OFFSETACTORFORSTATE15.H"

extern void Playerai_UpdateSequenceWait(void *);


extern s32 InstHdr_FindActorModelEntry(void *);

extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);

extern f32 Graphu64_GetHorizontalAngle(CVector3 *direction);

extern void TeamSelect_EmptyWeaponWheelHook();

extern void Playerai_UpdateMountedMovement(void *, void *);


void Playerai_UpdateSequence50Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartSequence50(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 50); }

void Playerai_UpdateSequence30Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartSequence30(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 30); }

void Playerai_UpdateSequence40Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartSequence40(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 40); }

void Playerai_UpdateSequence11Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartSequence11(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 11); }

void Playerai_UpdateSequence12Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartSequence12(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 12); }

void Playerai_UpdateSequence13Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartSequence13(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 13); }

void Playerai_UpdateSequence14Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartSequence14(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 14); }

void Playerai_UpdateSequence15Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartSequence15(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 15); }

void Playerai_UpdateSequence20Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartSequence20(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 20); }

void Playerai_UpdateSequence70Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartSequence70(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 70); }

void Playerai_UpdateSequence60Wait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartPlayerSequence60(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 60); }

void Playerai_UpdateSequence60RunEndPose(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartPlayerSequence71(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 71); }

/** Thin wrapper around Playerai_UpdateSequenceWait. */
void Playerai_UpdateSequence71RunEndPose(void *sequencePlayer) {
    Playerai_UpdateSequenceWait(sequencePlayer);
}

/** Thin wrapper around Playerai_TryStartPlayerSequence with player fixed third argument. */
void Playerai_StartPlayerSequence72(void *player, void *sequenceActor) {
    Playerai_TryStartPlayerSequence(player, sequenceActor, 72);
}

/** Thin wrapper around Playerai_UpdateSequenceWait. */
void Playerai_UpdateSequence72RunEndPose(void *sequencePlayer) {
    Playerai_UpdateSequenceWait(sequencePlayer);
}

/** Thin wrapper around Playerai_TryStartPlayerSequence with player fixed third argument. */
void Playerai_StartPlayerSequence73(void *player, void *sequenceActor) {
    Playerai_TryStartPlayerSequence(player, sequenceActor, 73);
}

/** Thin wrapper around Playerai_UpdateSequenceWait. */
void Playerai_UpdateSequence73RunEndPose(void *sequencePlayer) {
    Playerai_UpdateSequenceWait(sequencePlayer);
}

/** Thin wrapper around Playerai_TryStartPlayerSequence with player fixed third argument. */
void Playerai_StartPlayerSequence74(void *player, void *sequenceActor) {
    Playerai_TryStartPlayerSequence(player, sequenceActor, 74);
}

/** Thin wrapper around Playerai_UpdateSequenceWait. */
void Playerai_UpdateSequence74RunEndPose(void *sequencePlayer) {
    Playerai_UpdateSequenceWait(sequencePlayer);
}

void Playerai_InitializeActorModelEffect(void *effectPlayerState, void *sourceActor) {
    char *o = (char *)effectPlayerState;
    char *a1 = (char *)sourceActor;
    s32 actorModelEntry;
    CVector3 modelEffectOffset;
    CVector3 effectDisplacement;

    actorModelEntry = InstHdr_FindActorModelEntry(sourceActor);
    ((Shared_ActorView *)o)->effectModel = (void *)actorModelEntry;
    if (actorModelEntry != 0) {
        ((Shared_ActorView *)o)->modelState = 0;
        ((Shared_ActorView *)o)->effectPosition.x = ((LevelActor *)a1)->position0.x;
        ((Shared_ActorView *)o)->effectPosition.y = ((LevelActor *)a1)->position0.y;
        ((Shared_ActorView *)o)->effectPosition.z = ((LevelActor *)a1)->position0.z;
        modelEffectOffset.x = ((ModelBlend *)actorModelEntry)->effectOffset.x;
        modelEffectOffset.y = ((ModelBlend *)actorModelEntry)->effectOffset.y;
        modelEffectOffset.z = ((ModelBlend *)actorModelEntry)->effectOffset.z;
        Graphu64_SubtractVectors(&effectDisplacement, &modelEffectOffset, &((Shared_ActorView *)o)->effectPosition);
        effectDisplacement.y = 0.0f;
        ((Shared_ActorView *)o)->modelDistance = Graphu64_GetHorizontalAngle(&effectDisplacement);
    }
}

void Playerai_ClearPlayerWeaponLock(void *lockedPlayerState) {
    struct Player *player = lockedPlayerState;
    TeamSelect_EmptyWeaponWheelHook(&player->weaponBusy);
    player->locked = 0;
}

void Playerai_EnterMovingSequenceState(void *player, void *body) {
    struct SharedPlayer *a0 = player;
    void *a1 = body;

    Playerai_UpdateMountedMovement(player, body);
    if (a0->views5E8.view6C0_51.movementSpeed != 0.0f) {
        Player_SetPlayerState(a0, a1, 37);
    }
}

void Playerai_ResetPlayerWeaponLock(void *lockedPlayerState) {
    struct Player *player = lockedPlayerState;
    TeamSelect_EmptyWeaponWheelHook(&player->weaponBusy);
    player->locked = 0;
}

void Playerai_EnterStoppedSequenceState(void *player, void *body) {
    struct SharedPlayer *a0 = player;
    void *a1 = body;

    Playerai_UpdateMountedMovement(player, body);
    if (a0->views5E8.view6C0_51.movementSpeed == 0.0f) {
        Player_SetPlayerState(a0, a1, 36);
    }
}

void Playerai_OffsetActorForState15(Actor126 *actor, Object126 *positionedObject) {
    Object126 *object;
    f32 angle;
    f32 object_angle;
    f32 sine;
    f32 cosine;

    actor->flags |= 0x800000;
    actor->value1D4 = k_playerState15EffectValue;
    if (actor->state652 == 15) {
        object = positionedObject;
        object_angle = object->angle;
        angle = g_playerForceMarkerTilt;
        sine = Gu_Sinf(object_angle + angle);
        cosine = Math_Cosf(object->angle + angle);
        sine *= g_playerForceMarkerBasisScale;
        cosine *= g_playerForceMarkerBasisScale;
        object->x += sine;
        object->y += cosine;
        object->angle += actor->offset728;
        actor->offset728 = 0.0f;
    }
}
