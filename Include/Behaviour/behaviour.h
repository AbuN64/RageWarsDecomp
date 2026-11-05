#ifndef BEHAVIOUR_BEHAVIOUR_H
#define BEHAVIOUR_BEHAVIOUR_H
struct WheelProbeState;
void Nav_ResetWheelProbeState(struct WheelProbeState *player);
extern void Nav_RunBehaviorHandler(void *);
extern void Nav_RunBehaviorHandler(void *aiController);
#if defined(VERSION_DE)
extern void Nav_RunBehaviorHandler(void *aiController);
#endif
#if !defined(VERSION_DE)
extern void Nav_RunBehaviorHandler(void *aiController);
#endif
#if !(defined(VERSION_EU))
extern void Nav_RunBehaviorHandler(void *);
#endif
#if defined(VERSION_EU)
extern void Nav_RunBehaviorHandler(void *aiController);
#endif
#endif
