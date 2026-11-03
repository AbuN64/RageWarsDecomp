#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "AI/SOURCE.H"
#include "TYPES.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "ACTOR/NAV_APPLYSUPPORTINGPLATFORMMOTION.H"
#include "INSTHDR/INSTHDR_GETACTORSHADOWRADIUS.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"

typedef struct CollisionInfo CollisionInfo;

extern CollisionInfo g_supportingPlatformCollisionQuery;



extern void Graphu64_AddVec3(CVector3 *result, CVector3 *left, CVector3 *right);
extern void Graphu64_SubtractVectors(CVector3 *result, CVector3 *left, CVector3 *right);

extern void Unicol_MoveActorWithCollision(Source *actor, CVector3 pos, CollisionInfo *motionSettings);
extern void Triggered_PathMotionNoOp(u8 *platform, Source *player);




void Actor_ApplySupportingPlatformMotion(Source *player, void *unused1) {
    CVector3 saved_velocity;
    CVector3 position;
    CVector3 transformed;
    MatrixF matrix;
    u8 *object;
    f32 amount;

    object = InstHdr_GetEnabledItemValue(player);
    if ((object != 0) && (((Source *)object)->definition->kind == 2)) {
        position = player->position;
        InstHdr_GetActorTargetOffset(object, &saved_velocity);
        if (!(player->flags38 & 0x1000) || (saved_velocity.y > 0.0f)) {
            Graphu64_AddVec3(&position, &position, &saved_velocity);
        }
        saved_velocity = player->velocity;
        player->velocity.x = 0.0f;
        player->velocity.y = 0.0f;
        player->velocity.z = 0.0f;
        Graphu64_SubtractVectors(&transformed, &position, &((Source *)object)->position);
        amount = InstHdr_GetActorTargetHeight(object);
        BuildYawMatrix(&matrix, amount);
        Graphu64_TransformPoints(&matrix, &transformed, &transformed, 1);
        Graphu64_AddVec3(&transformed, &transformed, &((Source *)object)->position);
        Graphu64_SubtractVectors(&transformed, &transformed, &position);
        player->height += amount;
        Graphu64_AddVec3(&position, &position, &transformed);
        Unicol_MoveActorWithCollision(player, position, &g_supportingPlatformCollisionQuery);
        player->velocity = saved_velocity;
        if ((object[0] == 1) && (((Source *)object)->definition->kind == 2)) {
            Triggered_PathMotionNoOp(object, player);
        }
    }
}
