#include "include_asm.h"
#include "COMMON/GROUP.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "ENGINE/INSTANCE/GOBJINST.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "COMMON/AIPROFILE.H"
#include "TYPES.H"

/* 800C891C.CPP */

/* GameObject_ApplyMaterialCurrents_GameobjectMovetoxzkeepheight.CPP */
extern void Insthdr_ResetInstanceRenderIndices(signed char *prop);

extern f32 g_materialCurrentStrengthScales[];
extern f32 g_frameElapsedTime[];

extern s32 InstHdr_GetActorMotionState(ActorHorizontalMovementView *);

extern f32 Graphu64_GetHorizontalAngle(CVector3 *);

extern void Graphu64_ScaleVector(CVector3 *, CVector3 *, f32);

 extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);

static inline s32 currentEnabled(ActorHorizontalMovementView *actor) {
    if (actor->flags & 0x3000) return 1;
    if (actor->flags & 0x4000) return InstHdr_GetActorMotionState(actor);
    return 0;
}

void GameObject_ApplyMaterialCurrents(ActorHorizontalMovementView *actor, HorizontalMovementSurfaceView *material, CVector3 *movement, s32 applyDirectionalCurrent) {
    ActorHorizontalMovementView *rider;
    f32 speed;
    CVector3 v10,v20;
    f32 blendedYaw;
    f32 currentTargetYaw;
    f32 strength;
    f32 currentHeading;
    f32 unusedFloat;
    f32 unusedFloat1;
    f32 previousVerticalCurrent;
    f32 actorYaw;
    f32 unusedFloat2;
    f32 unusedFloat3;
    f32 currentBlend;
    f32 unusedFloat4;
    f32 currentYawStep;
    f32 wrappedTargetYaw;
    f32 targetAngle,oldAngle;
    s32 unusedValue;
    s32 unusedValue1;
    s32 riderMotionFlags;
    s32 actorCurrentEnabled;
    u16 flags;
    CVector3 *actorCurrent;

    if (actor->kind == 1) {
        rider=actor;
        actorCurrentEnabled=currentEnabled(actor);
        riderMotionFlags = rider->flags & 3;
    } else {
        actorCurrentEnabled = 0;
        riderMotionFlags = 0;
    }
    if ((riderMotionFlags != 0) || ((actorCurrentEnabled == 0) && !(material->flags & 0x8000))) {
        actor->current.x = 0.0f;
        actor->current.y = 0.0f;
        actor->current.z = 0.0f;
        return;
    }
    if ((material->flags & 0x100) && (applyDirectionalCurrent != 0)) {
        v10.x = (f32) material->x * 0.007874016f;
        v10.y = (f32) material->y * 0.007874016f;
        v10.z = (f32) material->z * 0.007874016f;
        strength = (f32) material->strength;
        speed=strength * 3.0f;
        currentYawStep = (strength + 1.0f) * 0.00872664712369442f;
        Graphu64_ScaleVector(&v10,&v10,speed);
        flags = material->flags;
        if (flags & 0x600) {
            if (flags & 0x400) {
                currentYawStep = -currentYawStep;
            }
            if (actor->kind == 1) {
                actor->yaw = (f32) (actor->yaw + currentYawStep);
            }
        }
        if ((material->flags & 0x2000) && (actor->kind == 1)) {
            rider=actor;
            v20=v10;
            v20.y = 0.0f;
            currentHeading = Graphu64_GetHorizontalAngle(&v20);
            actorYaw = actor->yaw;
            currentTargetYaw = currentHeading;
            blendedYaw = actorYaw;
            if (currentHeading != actorYaw) {
                Graphu64_WrapPeriodicValue(&blendedYaw);
                Graphu64_WrapPeriodicValue(&currentTargetYaw);
                if (blendedYaw > currentTargetYaw) {
                    wrappedTargetYaw=currentTargetYaw+6.2831855f;
                    if ((wrappedTargetYaw-blendedYaw)<(blendedYaw-currentTargetYaw)) currentTargetYaw=wrappedTargetYaw;
                } else {
                    wrappedTargetYaw=currentTargetYaw-6.2831855f;
                    if ((blendedYaw-wrappedTargetYaw)<(currentTargetYaw-blendedYaw)) currentTargetYaw=wrappedTargetYaw;
                }
                targetAngle=currentTargetYaw; oldAngle=blendedYaw;
                if (oldAngle < targetAngle) {
                    blendedYaw=oldAngle+((f32)material->strength*g_materialCurrentStrengthScales[1]*g_frameElapsedTime[0]*0.017453294f);
                    if (targetAngle<blendedYaw) blendedYaw=targetAngle;
                } else {
                    blendedYaw=oldAngle-((f32)material->strength*g_materialCurrentStrengthScales[1]*g_frameElapsedTime[0]*0.017453294f);
                    if (blendedYaw<targetAngle) blendedYaw=targetAngle;
                }
                Graphu64_WrapPeriodicValue(&blendedYaw);
            }
            rider->yaw = blendedYaw;
        }
    } else {
        v10.x = 0.0f;
        v10.y = 0.0f;
        v10.z = 0.0f;
    }
    currentBlend = (f32) material->strength * g_materialCurrentStrengthScales[0] * g_frameElapsedTime[0];
    currentBlend = ((currentBlend < 0.0f ? 0.0f : currentBlend) > 1.0f ? 1.0f : (currentBlend < 0.0f ? 0.0f : currentBlend));
    actorCurrent=&actor->current;
    Graphu64_InterpolateVector(actorCurrent, currentBlend, actorCurrent, &v10);
    movement->x = (f32) (movement->x + actor->current.x);
    movement->z = (f32) (movement->z + actor->current.z);
    if (material->flags & 0x100) {
        if (v10.y != 0.0f) {
            actor->vertical = 0.0f;
        } else {
            previousVerticalCurrent = actor->current.y;
            actor->current.y = (f32) (previousVerticalCurrent + ((v10.y - previousVerticalCurrent) * 0.2f));
        }
        actor->vertical = (f32) (actor->vertical + ((2.0f * (actor->current.y * 10.24f)) + 4.0f));
        return;
    }
    actor->current.y += (v10.y-actor->current.y)*0.2f;
}

/* Resets an object through Insthdr_ResetInstanceRenderIndices, then clears its words from 0x1C to 0x38 and at 0x40, 0x44
   and 0x4C, sets the word at 0x3C to -1 and stores g_resetActorFloorDirectionY in the float at 0x48. */

void GameObject_ResetActorMotion(void *levelActor) {
    float k;

    Insthdr_ResetInstanceRenderIndices(levelActor);
    k = g_resetActorFloorDirectionY;
    ((LevelActor *)levelActor)->position1.x = 0;
    ((LevelActor *)levelActor)->position1.y = 0;
    ((LevelActor *)levelActor)->position1.z = 0;
    ((LevelActor *)levelActor)->motionAngles.x = 0;
    ((LevelActor *)levelActor)->motionAngles.y = 0;
    ((LevelActor *)levelActor)->motionAngles.z = 0;
    ((LevelActor *)levelActor)->attached = 0;
    ((LevelActor *)levelActor)->motionState = 0;
    ((LevelActor *)levelActor)->motionIndex = -1;
    ((LevelActor *)levelActor)->floorHeight = 0;
    ((LevelActor *)levelActor)->floorDirection.x = 0;
    ((LevelActor *)levelActor)->floorDirection.z = 0;
    ((LevelActor *)levelActor)->floorDirection.y = k;
}

extern CollisionQuery g_portalAlternateCollisionQuery;
extern f32 Region_GetPolygonHeight(s32, f32, f32);
extern s32 Unicol_MoveActorWithCollision(Shared_ParticleInstance *, CVector3, s32 *);

void GameObject_MoveToXZKeepHeight(Shared_ParticleInstance *actor, f32 x, f32 z) {
    CVector3 saved;
    CVector3 position;
    s32 keep;
    f32 height;

    height = actor->pos.y - Region_GetPolygonHeight(actor->region, actor->pos.x, actor->pos.z);
    saved = actor->velocity;
    actor->velocity.x = actor->velocity.y = actor->velocity.z = 0.0f;
    position.x = x;
    position.y = actor->pos.y;
    position.z = z;
    keep = g_portalAlternateCollisionQuery.w[0];
    Unicol_MoveActorWithCollision(actor, position, g_portalAlternateCollisionQuery.w);
    g_portalAlternateCollisionQuery.w[0] = keep;
    actor->velocity = saved;
    actor->pos.y = Region_GetPolygonHeight(actor->region, actor->pos.x, actor->pos.z) + height;
}
