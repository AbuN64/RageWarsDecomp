#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/SELF.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ACTORREC.H"
#include "TYPES.H"
#include "include_asm.h"
#include "GAME/ATTACK_SELECTWEIGHTEDATTACKBEHAVIOR.H"

s32 Reselect_ChooseWeightedAttackBehavior(WeightSource *weights);
extern s32 Scaled_SetBehaviourState(void *, s32);

/* Reconsider an existing attack on one of four signed random remainders. */
void ReselectCloseAttack(void *brainAddress) {
    CloseAttackBrain *brain = brainAddress;
    WeightSource *weights;
    s32 selectedState;
    if (Graphu64_NextRandom() % 4 == 1) {
        weights = (WeightSource *)(&((ActorDefinitionHeader *)((Player *)brain->player)->definition)->flags);
        selectedState = Reselect_ChooseWeightedAttackBehavior(weights);
        brain->combat = selectedState;
        Scaled_SetBehaviourState(brainAddress, selectedState);
    }
}

s32 Reselect_ChooseWeightedAttackBehavior(WeightSource *weights) {
    s32 first;
    s32 second;
    s32 third;
    s32 first_end;
    s32 second_end;
    s32 total;
    s32 value;

    first = (s32)weights->first;
    second = (s32)weights->second;
    third = (s32)weights->third;
    first_end = 0;
    if (first > 0) {
        first_end = first;
    }
    second_end = 0;
    if (second > 0) {
        second_end = first_end + second;
    }
    total = first + second + third;
    if (total == 0) {
        return 3;
    }
    value = (Graphu64_NextRandom() % total) + 1;
    if (first_end < value) {
        if (second_end >= value) {
            return 4;
        }
        return 3;
    }
    return 5;
}



