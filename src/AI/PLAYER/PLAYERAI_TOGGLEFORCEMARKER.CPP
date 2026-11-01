#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "include_asm.h"
#include "COMMON/INTEGERSTATE1250.H"
#include "RENDER/WEAPON_INITIALIZECHARGEANDSTARTUPCUES_DATA.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"



extern void Graphu64_GetMatrixTranslation(char *, f32 *);

extern char g_actorParticleEffectSystem;

extern void Particle_ReleaseOwnerEmitters(void *world, s32 owner);

void Player_SetPlayerResetPosition(void *actorObject, CVector3 *newResetPosition)
{
  Shared_ActorView *player = actorObject;
  void *positionRecord;
  player->resetPosition = *newResetPosition;
  positionRecord = actorObject;
  Player_SetPlayerState(positionRecord, positionRecord, 17);
}

extern void Player_BuildPlayerViewTransform(void *, MatrixF *);
void Player_TransformPointByViewOrOwnerMatrix(void *player, CVector3 *point) {
    CVector3 input;
    MatrixF matrix;
    CVector3 *input_ptr;
    MatrixF *matrix_ptr;

    PlayerForceMarkerOwnerView *object = player;
    PlayerForceMarkerMatrixView *owner;

    input = *point;
    input_ptr = &input;
    matrix_ptr = object->transformOwner;

    if (matrix_ptr != 0) {
        owner = (void *)matrix_ptr;
        matrix_ptr = &owner->viewMatrix;
    } else {
        Player_BuildPlayerViewTransform(player, &matrix);
        matrix_ptr = &matrix;
    }
    Graphu64_TransformPoint(matrix_ptr, input_ptr, point);
}

void Playerai_AddCappedEventCounter(void *player, s32 increment) {
    u16 wrappedSum;
    u16 cappedCounter;
    wrappedSum = (((struct PlayerForceMarkerCounterView *) ((s8 *) player))->eventCounter) + increment;
    cappedCounter = wrappedSum;
    (((struct PlayerForceMarkerCounterView *) ((s8 *) player))->eventCounter) = wrappedSum;
    if ((u32) (cappedCounter & 0xFFFF) >= 101U) {
        cappedCounter = 100;
    }
    (((struct PlayerForceMarkerCounterView *) ((s8 *) player))->eventCounter) = cappedCounter;
}

void Player_GetPlayerViewTranslation(void *player, f32 *origin) {
    MatrixF viewTransform;
    Player_BuildPlayerViewTransform(player, &viewTransform);
    Graphu64_GetMatrixTranslation((char *)&viewTransform, origin);
}

/** Report whether the word at offset 0x5E4 is zero. */
int Playerai_IsPlayerInactive(struct SharedPlayer *player) {
    return player->views5E4.view5E4_0.health == 0;
}

/** Return the word at offset 0x1210. */
int Playerai_IsAlternateFireHeld(struct SharedPlayer *object) {
    return object->views5E8.view1210_152.marker;
}

void Player_ReleasePlayerParticleEmitters(s32 actor) {
    Particle_ReleaseOwnerEmitters(&g_actorParticleEffectSystem, actor);
}

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "ENGINE/AUDIO/CHANNEL.H"
extern u8 *g_forceMarkerRemovedText, *g_forceMarkerAttractText, *g_forceMarkerRepulseText;
extern void BuildDirectionMatrix(Matrix *, CVector3 *);
extern void Graphu64_ScaleVector(CVector3 *out, CVector3 *in, f32 scale);
extern void Graphu64_AddVec3(CVector3 *result, CVector3 *left, CVector3 *right);
extern void TranslateMatrix(Matrix *, f32 x, f32 y, f32 z);
extern void SwapMatrixUpForward(Matrix *);
extern void Graphu64_ConvertMatrixToFixed(Matrix *src, void *dst);
/* Copy of Playerai_BuildForceMarkerTransform: orients the marker matrix along the aim normal, moves it to the marker origin
 * pushed 5.12 units off the surface and packs it into the player's marker transform. */
static inline void buildForceMarkerTransform(Shared_ActorView *player, s32 attract, CVector3 *normal) {
    Matrix matrix;
    CVector3 offset;
    BuildDirectionMatrix(&matrix, normal);
    Graphu64_ScaleVector(&offset, normal, 5.12f);
    Graphu64_AddVec3(&offset, &offset, &player->targetPosition);
    TranslateMatrix(&matrix, offset.x, offset.y, offset.z);
    SwapMatrixUpForward(&matrix);
    Graphu64_ConvertMatrixToFixed(&matrix, player->transform1600);
}
/* Toggles the player's attract/repulse marker while the aim ray hits something: a live marker is removed
 * ("ATTRACT REMOVED"); otherwise a new one is placed at the aim point for 150 frames, pulling when
 * attract is set ("ATTRACT MARKED") and pushing otherwise ("REPULSE MARKED"). */
void Playerai_ToggleForceMarker(Shared_ActorView *player, s32 attract) {
    void *screen;
    u8 *text;
    if (player->aimTarget != 0) {
        if (player->marker.time > 0.0f) {
            player->marker.time = 0;
            SoundElement_PlayFlatSound(1400);
            screen = player->message;
            if (screen == 0) return;
            text = g_forceMarkerRemovedText;
        } else {
            player->targetPosition = player->aimPoint;
            player->attract = attract;
            player->marker.time = 150.0f;
            buildForceMarkerTransform(player, attract, &player->aimNormal);
            SoundElement_PlayFlatSound(1400);
            screen = player->message;
            if (screen == 0) return;
            if (attract != 0) text = g_forceMarkerAttractText;
            else text = g_forceMarkerRepulseText;
        }
        Camera_PostScreenMessage((void *)&g_frontendScreenStatus, screen, text);
    }
}
#endif
