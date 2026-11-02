#include "WEAPONS/PLAYERRECAT1450V1.H"
#include "AI/WEAPONAI.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"


/** Thin wrapper around Actor_RequestActorState_Damageai. */
void Weaponai_ForwardActorStateRequest(void *actor, void *stateController, s32 action) {
    Actor_RequestActorState(actor, stateController, action);
}
