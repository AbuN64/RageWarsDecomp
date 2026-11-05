#ifndef AI_NAV_COMBAT_H
#define AI_NAV_COMBAT_H
struct CloseAttackActor;
struct Player;
extern void Nav_UpdatePursuitStrafe(struct Player *actor);
extern void Nav_InitCloseCombat(struct CloseAttackActor *actor);
#endif
