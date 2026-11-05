#ifndef WEAPON_STATE_TABLES_WEAPON_STATE_TABLES_H
#define WEAPON_STATE_TABLES_WEAPON_STATE_TABLES_H
struct WeaponEventSource;
struct WeaponFireState;
struct LevelActor;
struct Shared_Actor;
/* One state of a weapon fire-state script: the state number, its enter
   handler, the selector callback that drives it and its animation. */
typedef struct WeaponStateStep {
    int state;
    unsigned int enterAddress;
    unsigned int selectorAddress;
    unsigned int selectorFlags;
    int animation;
    float speed;
    int threshold;
    unsigned int animationFlags;
} WeaponStateStep;

/* Fire-state header of the charged alternate script: state ids, its spin
   rate and the callback references (callback table first). */
typedef struct WeaponChargedAlternateFireState {
    int stateIds[7];
    float spinRate;
    void * callbacks[8];
} WeaponChargedAlternateFireState;

/* us-rev1 rom 0xD04C4-0xD070C: the weapon fire-state scripts, each a
   fire-state header (callback table at word 7), its states and a -1 end. */
typedef struct WeaponStateScriptTable {
    void * alternateAmmoFireState[15];
    WeaponStateStep alternateAmmoSteps[3];
    int alternateAmmoEnd;
    void * alternateTriggerFireState[15];
    WeaponStateStep alternateTriggerSteps[1];
    int alternateTriggerEnd;
    WeaponChargedAlternateFireState chargedAlternateFireState;
    WeaponStateStep chargedAlternateSteps[3];
    int chargedAlternateEnd;
    void * forceMarkerFireState[15];
    WeaponStateStep forceMarkerSteps[2];
    int forceMarkerEnd;
    void * fireStateInitializer[9];
} WeaponStateScriptTable;
extern WeaponStateScriptTable g_weaponStateScripts;
extern void Weapon_ApproachSpinPhaseAndRelease(void *actor, struct WeaponFireState *fireState);
extern void Weapon_InitializeFireStateCallbacks(void *actor, void *fireState);
extern void Weapon_RequestReleaseOnEnabledEvent(void *a, struct WeaponEventSource *b);
extern void Weapon_UpdateAlternateTriggerCompletion(struct LevelActor *actor, struct WeaponFireState *fireState);
extern void Weaponai_TryEnterAlternateAmmoMode(struct Shared_Actor *actor, struct WeaponFireState *fireState);
extern void Weaponai_TryEnterChargedAlternateMode(struct Shared_Actor *actor, struct WeaponFireState *fireState);
extern void Weaponai_UpdateForceMarkerTrigger(struct Shared_Actor *actor, struct WeaponFireState *attack);
extern unsigned short g_weaponAmmoRequirementPairs[120][2];
extern void Weaponai_SettleSpinToThirdTurn(struct Shared_Actor *actor, struct WeaponFireState *fireState);
#endif
