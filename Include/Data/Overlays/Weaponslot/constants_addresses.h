#ifndef DATA_OVERLAYS_WEAPONSLOT_CONSTANTS_ADDRESSES_H
#define DATA_OVERLAYS_WEAPONSLOT_CONSTANTS_ADDRESSES_H
/* Overlay symbols known only by address in the version symbol maps. */
extern char g_weaponSecondaryPresentationLabel[];
extern char g_weaponPrimaryPresentationLabel[];
extern unsigned int g_ActorStateEntryFragmentEncodedWords[];
extern void *k_triggerActorActionHandlers[];
extern unsigned int k_breakableActionHandlers[];
extern char g_actionMotionDispatchTriggerPairs_us[];
extern char g_damageDispatchTriggerPairs_us[];
extern char g_movingMotionDispatchTriggerPairs_us[];
extern char g_triggeredMotionDispatchTriggerPairs_us[];
extern char g_turretDispatchTriggerPairs_us[];
#endif
