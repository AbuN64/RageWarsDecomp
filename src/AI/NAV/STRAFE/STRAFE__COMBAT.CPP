
/* Runs a computer rider's close attack state: refreshes its view, re-checks line of sight every fourth frame, backs off
   when its target is out of its layer or too close, re-rolls its strafe pattern and steers toward the target. */
#include "TYPES.H"
#include "COMMON/BRAIN.H"

#include "COMMON/VECTOR3.H"

struct Brain;

typedef struct Actor {
    char pad0[8];
    CVector3 pos;
    char pad14[0x24];
    s32 flags;
    char pad3C[0x30];
    f32 yaw;
    char pad70[0x168];
    struct Actor *self;
    char pad1DC[0x3F8];
    s32 slot;
    char pad5D8[0xCC];
    f32 strafe;
    f32 forward; s32 w6AC,buttons; char pad6B4[0xDA0];
    struct Brain *brain;
} Actor;



extern s32 g_lightingBufferIndex;
extern char g_navigationGraph[];

extern void Nav_RunBehaviorHandler(Brain *aiController);
extern s32 Scaled_HasLineOfSight(Brain *, Actor *);
extern void Scaled_SetBehaviourState(Brain *, s32);
extern f32 Graphu64_GetSquaredDistance(CVector3 *, CVector3 *);
extern f32 Scaled_ScaleCharacterSettingByDifficulty(Brain *controller);
extern s32 Graphu64_NextRandom(void);
extern f32 Scaled_UpdateDifficultyAimJitter(Brain *aiController);
extern f32 Nav_SteerTowardPoint(Brain *, CVector3 *, f32, f32);
extern s32 Wheel_GetDirectionSector(f32);
extern void Wheel_MeasureWheelClearance(Actor *, s32);
extern void Portal_DispatchActorBehavior(Brain *controller);
extern s32 Route_GetRouteRelation(char *, s32, s32);


extern void Nav_SteerAlongRoute(Brain *controller), Nav_UpdatePlayerSteering(Brain *controller);
void Nav_UpdatePursuitStrafe(Actor *actor) {
    s32 mine, theirs, dir, route;
    Actor *player;
    Actor *target;
    Brain *brain;
    f32 speed;
    s32 pattern;

    brain = actor->self->brain;
    Nav_RunBehaviorHandler(brain);
    player = brain->target;
    if (player != 0) {
        if (!(brain->frames & 3)) {
            brain->visible = Scaled_HasLineOfSight(brain, player);
        }
        brain->frames += 1;
        target = brain->target->self;
        mine = ((Actor *)brain->player)->flags & 0x3000;
        theirs = (target->flags & 0x3000) != 0;
        if (mine && !theirs) {
            Scaled_SetBehaviourState(brain, 12);
            return;
        }
        route = target->brain->start;
        if (brain->visible != 0) {
            if (Graphu64_GetSquaredDistance(&target->pos, &((Actor *)brain->player)->pos) < 360000.0f) {
                brain->combat = 3;
                Scaled_SetBehaviourState(brain, 7);
                return;
            }
            speed = Scaled_ScaleCharacterSettingByDifficulty(brain) * 0.4f;
            if (--brain->timer <= 0) {
                brain->timer = Graphu64_NextRandom() % 4 + 12;
                brain->pattern = Graphu64_NextRandom() % 2;
                if (Graphu64_NextRandom() % 2 == 1) {
                    brain->pattern = 2;
                }
            }
            Nav_SteerTowardPoint(brain, &target->pos, 2.0f, Scaled_UpdateDifficultyAimJitter(brain));
            pattern = brain->pattern;
            if (pattern == 0) {
                dir = Wheel_GetDirectionSector((((Actor *)brain->player)->yaw - 3.1415927f) - 1.5707964f);
                player = ((Actor *)brain->player);
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, dir);
                }
                if (!(brain->clearance[dir] < 100.0f)) {
                    ((Actor *)brain->player)->strafe = -speed;
                } else {
                    goto halt;
                }
            } else if (pattern == 1) {
                dir = Wheel_GetDirectionSector((((Actor *)brain->player)->yaw - 3.1415927f) + 1.5707964f);
                player = ((Actor *)brain->player);
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, dir);
                }
                if (brain->clearance[dir] < 100.0f) {
halt:
                    ((Actor *)brain->player)->strafe = 0.0f;
                    brain->pattern = 2;
                } else {
                    ((Actor *)brain->player)->strafe = speed;
                }
            } else {
                ((Actor *)brain->player)->strafe = 0.0f;
            }
            brain->w14 = -1;
            Portal_DispatchActorBehavior(brain);
        } else {
            brain->destination = route;
            Nav_SteerAlongRoute(brain);
            Nav_UpdatePlayerSteering(brain);
        }
        if (route != brain->node) {
            brain->node = route;
            if (Route_GetRouteRelation(g_navigationGraph, brain->start, route) == 0) {
                Scaled_SetBehaviourState(brain, 1);
            }
        }
    }
}
