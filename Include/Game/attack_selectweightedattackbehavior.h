#ifndef GAME_ATTACK_SELECTWEIGHTEDATTACKBEHAVIOR_H
#define GAME_ATTACK_SELECTWEIGHTEDATTACKBEHAVIOR_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/box_contact.h"
struct WeightSource {
    char pad[0x2C];
    f32 first;
    f32 second;
    f32 third;
};
struct WeightedAttackSelectionBrainView {
    void * actor;
    char pad0[0x230 - 0x0 - sizeof(void*)];
    s32 selectedBehavior;
};
struct AttackBehaviorDefinitionView {
    char pad0[0x18];
    s32 attackDefinitionAddress;
};
extern void Attack_SelectWeightedAttackBehavior(void *brainAddress);
#endif
