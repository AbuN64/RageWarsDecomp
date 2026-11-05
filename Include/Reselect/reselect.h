#ifndef RESELECT_RESELECT_H
#define RESELECT_RESELECT_H
struct WeightSource;
s32 Reselect_ChooseWeightedAttackBehavior(struct WeightSource *weights);
extern void ReselectCloseAttack(void *);
#endif
