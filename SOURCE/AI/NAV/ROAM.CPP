#include "COMMON/NAVIGATION_GRAPH.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "AI/SOURCE.H"
#include "TYPES.H"
#include "COMMON/SELF.H"
#include "include_asm.h"
#include "COMMON/VECTOR4F.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/INTEGERSTATE244.H"
#include "AI/NAV/ROAM.H"

/* ROAMGOAL.CPP */
extern s32 g_navigationGraph;

extern void *Portal_GetGraphPoint(void *, s32);

void Nav_SelectFlaggedRoamingGoal(void *controller)
{
    s32 choices[32];
    s32 count;
    s32 result;
    s32 fill;

    result = 0;
    count = result;
    fill = -1;
    {
        s32 index = 31;
        do {
            choices[index] = fill;
            index--;
        } while (index >= 0);

        {
            s32 *table = &g_navigationGraph;
        index = 0;
        if (table[1] > 0) {
            do {
                if (navigation_point_flags((NavigationPoint *)Portal_GetGraphPoint(table, index)) & 0x800) {
                    choices[count] = index;
                    count++;
                }
                index++;
            } while (index < table[1]);
        }
        }
    }

    if (count == 0) {
        s32 global_count = g_navigationNodeCount;
        s32 *table = &g_navigationGraph;
        s32 tries = 0;
        s32 candidate;
        if (global_count >= 2) {
            candidate = ((NavigationBrainView *)controller)->goal;
loop:
            if (tries < 10) {
                candidate = Graphu64_NextRandom() % table[1];
                if (navigation_point_flags((NavigationPoint *)Portal_GetGraphPoint(table, candidate)) & 0x400) {
                    candidate = ((NavigationBrainView *)controller)->goal;
                }
                tries++;
                if (candidate != ((NavigationBrainView *)controller)->goal) {
                    goto store_both;
                }
                goto loop;
            } else {
                ((NavigationBrainView *)controller)->goal = candidate;
                goto store_c;
            }
        } else {
            candidate = 1;
        }
store_both:
        ((NavigationBrainView *)controller)->goal = candidate;
store_c:
        ((NavigationBrainView *)controller)->nextNode = candidate;
    } else {
        result = choices[Graphu64_NextRandom() % count];
    }

    ((NavigationBrainView *)controller)->goal = result;
    ((NavigationBrainView *)controller)->nextNode = result;
}

/* ROAM.CPP */
/* Runs a computer player's think step: when it has reached its goal node or the goal at 0x22C is past
   the node count g_navigationNodeCount, it picks a new goal as Nav_InitRoamingWithJumps does (Nav_SelectFlaggedRoamingGoal for a player
   flagged at 0x94 in mode 12, otherwise up to ten random nodes of g_navigationGraph not flagged 0x400); then
   it counts down the jump timer at 0x320 and on expiry makes its player jump (bit 0x10 at 0x6B0)
   unless the player is in state 0xF, holds input bits 0x3000 or the bot is busy at 0x314, rerolls an
   expired timer to 15 times 3 to 9 frames, and runs Nav_RunBehaviorHandler, Nav_SteerAlongRoute and Nav_UpdatePlayerSteering. */

extern void Nav_RunBehaviorHandler(void *);
extern void Nav_SteerAlongRoute(void *);
extern void Nav_UpdatePlayerSteering(void *);

void Nav_UpdateRoamingWithJumps(Shared_Actor *actorContext) {
    void *actor = ((Shared_ActorView *)(actorContext->entity))->owner;
    void *player;
    s32 busy;
    s32 held;
    s32 state;

    if (((NavigationBrainView *)(actor))->node == ((NavigationBrainView *)(actor))->goal
        || !(((NavigationBrainView *)(actor))->goal < g_navigationNodeCount)) {
        void *data = ((Shared_ActorView *)(*(void **) actor))->controls;
        if (((PlayerProfileStatusView *)(data))->display && ((PlayerProfileStatusView *)(data))->kind == 12) {
            Nav_SelectFlaggedRoamingGoal(actor);
        } else {
            s32 global_count = g_navigationNodeCount;
            s32 *table = &g_navigationGraph;
            s32 tries = 0;
            s32 candidate;

            if (global_count >= 2) {
                candidate = ((NavigationBrainView *)(actor))->goal;
loop:
                if (tries < 10) {
                    candidate = Graphu64_NextRandom() % table[1];
                    if (navigation_point_flags((NavigationPoint *)(Portal_GetGraphPoint(table, candidate))) & 0x400) {
                        candidate = ((NavigationBrainView *)(actor))->goal;
                    }
                    tries++;
                    if (candidate != ((NavigationBrainView *)(actor))->goal) {
                        goto store_both;
                    }
                    goto loop;
                } else {
                    ((NavigationBrainView *)(actor))->goal = candidate;
                    goto store_c;
                }
            } else {
                candidate = 1;
            }
store_both:
            ((NavigationBrainView *)(actor))->goal = candidate;
store_c:
            ((NavigationBrainView *)(actor))->nextNode = candidate;
        }
    }
    if (--((NavigationBrainView *)(actor))->jumpTimer == 0) {
        player = *(void **) actor;
        state = ((Shared_ActorView *)(player))->action != 15;
        busy = ((NavigationBrainView *)(actor))->busy != 0;
        held = (((Shared_ActorView *)(player))->unk_0x0038 & 0x3000) != 0;
        if (state && !held && !busy) {
            ((Shared_ActorView *)(player))->unk_0x06B0 |= 0x10;
        }
    }
    if (((NavigationBrainView *)(actor))->jumpTimer < 0) {
        ((NavigationBrainView *)(actor))->jumpTimer = (Graphu64_NextRandom() % 7 + 3) * 15;
    }
    Nav_RunBehaviorHandler(actor);
    Nav_SteerAlongRoute(actor);
    Nav_UpdatePlayerSteering(actor);
}

void Nav_InitRoamingWithJumps(Shared_Actor *actorStorage)
{
    void *actor = ((Shared_ActorView *)(actorStorage->entity))->owner;

    ((NavigationBrainView *)(actor))->state = 0;
    {
        void *data = ((Shared_ActorView *)(*(void **)actor))->controls;
        if (((PlayerProfileStatusView *)(data))->display && ((PlayerProfileStatusView *)(data))->kind == 12) {
            Nav_SelectFlaggedRoamingGoal(actor);
        } else {
            s32 global_count = g_navigationNodeCount;
            s32 *table = &g_navigationGraph;
            s32 tries = 0;
            s32 candidate;

            if (global_count >= 2) {
                candidate = ((NavigationBrainView *)(actor))->goal;
loop:
                if (tries < 10) {
                    candidate = Graphu64_NextRandom() % table[1];
                    if (navigation_point_flags((NavigationPoint *)(Portal_GetGraphPoint(table, candidate))) & 0x400) {
                        candidate = ((NavigationBrainView *)(actor))->goal;
                    }
                    tries++;
                    if (candidate != ((NavigationBrainView *)(actor))->goal) {
                        goto store_both;
                    }
                    goto loop;
                } else {
                    ((NavigationBrainView *)(actor))->goal = candidate;
                    goto store_c;
                }
            } else {
                candidate = 1;
            }
store_both:
            ((NavigationBrainView *)(actor))->goal = candidate;
store_c:
            ((NavigationBrainView *)(actor))->nextNode = candidate;
        }
    }
    Scaled_ResetBehaviorState(actor);
    ((NavigationBrainView *)(actor))->jumpTimer = -1;
}

void Nav_ChooseNewRoamingGoal(void *controller)
{
    s32 *table = &g_navigationGraph;
    s32 tries = 0;
    s32 candidate;

    if (table[1] >= 2) {
        candidate = ((NavigationBrainView *)(controller))->goal;
loop:
        if (tries < 10) {
            candidate = Graphu64_NextRandom() % table[1];
            if (navigation_point_flags((NavigationPoint *)(Portal_GetGraphPoint(table, candidate))) & 0x400) {
                candidate = ((NavigationBrainView *)(controller))->goal;
            }
            tries++;
            if (candidate != ((NavigationBrainView *)(controller))->goal) {
                goto store_both;
            }
            goto loop;
        } else {
            ((NavigationBrainView *)(controller))->goal = candidate;
            goto store_c;
        }
    } else {
        candidate = 1;
    }
store_both:
    ((NavigationBrainView *)(controller))->goal = candidate;
store_c:
    ((NavigationBrainView *)(controller))->nextNode = candidate;
}
