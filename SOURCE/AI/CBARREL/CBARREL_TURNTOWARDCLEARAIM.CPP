#include "COMMON/FIELD_VEC_B0.H"
#include "TYPES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "AI/CBARREL.H"

extern f32 Barrel_FindClearAimAngle(void *actor, f32 targetX, f32 targetY, f32 targetZ,
                        void *target, f32 clearance);


void Cbarrel_TurnTowardClearAim(void *actor, s32 unusedEvent, CTeamSelectTeam *target, f32 maximumTurn) {
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;

    if (target != 0) {
        f1 = Barrel_FindClearAimAngle(actor, target->x, target->y, target->z,
                           target, g_barrelClearAimClearance);
        f3 = f1;
        if (maximumTurn < f1) {
            f1 = maximumTurn;
        } else {
            f0 = -maximumTurn;
            if (f1 < f0) {
                f1 = f0;
            }
        }
        f1 = f1 * g_frameElapsedTime;
        f2 = f1;
        if (f1 < 0.0f) {
            f2 = -f1;
        }
        if (f3 < 0.0f) {
            if (-f3 < f2) {
                goto clamp;
            }
        } else if (f3 < f2) {
clamp:
            f1 = f3;
        }
        Barrel_AddActorYaw(actor, f1);
    }
}
