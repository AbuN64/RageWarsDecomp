#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ACTORREC.H"
#include "TYPES.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/BOX_CONTACT.H"
#include "GAME/ATTACK_SELECTWEIGHTEDATTACKBEHAVIOR.H"

extern void ReselectCloseAttack(void *);


s32 Scaled_SetBehaviourState(void *, s32);

s32 Reselect_ChooseWeightedAttackBehavior(s32);

/* The original MIPS preserves a0 for either close-attack update. */
s32 UpdateCloseAttack(void *brainAddress) {
    AiController *brain = brainAddress;
    if (brain->target != 0) {
        if ((u32)(brain->state - 3) < 3U) {
            ReselectCloseAttack(brainAddress);
            return 1;
        }
        Attack_SelectWeightedAttackBehavior(brainAddress);
        return 1;
    }
    return 1;
}

void Attack_SelectWeightedAttackBehavior(void *brainAddress) {
    s32 selectedBehavior;
    selectedBehavior = Reselect_ChooseWeightedAttackBehavior((((struct AttackBehaviorDefinitionView *) ((s8 *) ((struct WeightedAttackSelectionBrainView *) ((s8 *) brainAddress))->actor))->attackDefinitionAddress) + ((char *)&((ActorDefinitionHeader *)0)->flags - (char *)0));
    (((struct WeightedAttackSelectionBrainView *) ((s8 *) brainAddress))->selectedBehavior) = selectedBehavior;
    Scaled_SetBehaviourState(brainAddress, selectedBehavior);
}
