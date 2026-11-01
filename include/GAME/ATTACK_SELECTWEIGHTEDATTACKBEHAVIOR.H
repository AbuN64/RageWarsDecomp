#ifndef GAME_ATTACK_SELECTWEIGHTEDATTACKBEHAVIOR_H
#define GAME_ATTACK_SELECTWEIGHTEDATTACKBEHAVIOR_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/BOX_CONTACT.H"
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
