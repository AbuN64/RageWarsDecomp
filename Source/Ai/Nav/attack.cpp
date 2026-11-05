#include "Ai/nav_symbols.h"
#include "Ai/ai_functions.h"
#include "Common/level_actor.h"
#include "Common/ai_behaviour_types.h"
#include "Common/sharedplayer.h"
#include "Common/actorrec.h"
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/box_contact.h"
#include "Game/attack_selectweightedattackbehavior.h"
#include "Attack/attack.h"
#include "Reselect/reselect.h"

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
    ActorDefinitionHeader *attackDefinition =
        (ActorDefinitionHeader *)(((struct AttackBehaviorDefinitionView *) (((struct WeightedAttackSelectionBrainView *) brainAddress)->actor))->attackDefinitionAddress);
    selectedBehavior = Reselect_ChooseWeightedAttackBehavior((struct WeightSource *)&attackDefinition->flags);
    (((struct WeightedAttackSelectionBrainView *) brainAddress)->selectedBehavior) = selectedBehavior;
    Scaled_SetBehaviourState(brainAddress, selectedBehavior);
}
