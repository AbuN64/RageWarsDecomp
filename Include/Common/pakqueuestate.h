#ifndef COMMON_PAKQUEUESTATE_H
#define COMMON_PAKQUEUESTATE_H
struct Shared_Effect;
struct ControllerProfile;
#ifndef COMMON_PAKQUEUESTATE_TYPES_H
#define COMMON_PAKQUEUESTATE_TYPES_H
#include "types.h"

/* Status and message queue for controller-pak operations. */
typedef struct PakQueueState {
    s8 status;
    char reserved1[7];
    OSMesgQueue queue;
} PakQueueState;

/* The controller-pak message queue: the queue member of the PakQueueState that starts 8 bytes lower. */
extern OSMesgQueue g_controllerReadMessageQueue;

/* The four controller profiles, one per port. */
extern struct ControllerProfile g_controllerProfiles[4];
/* The combined input record of all four controllers (Control_ReadControllerStates). */
extern struct ControllerProfile g_combinedControllerProfile;
#include "Common/runtime_declarations.h"







struct ControllerRumbleView;
struct ControllerRumbleView {
    s32 flags;
    s8 enabled;
    char pad05[3];
    s32 x;
    s32 y;
    s32 z;
    char pad14[0xB4];
    s32 active;
    s32 state;
    f32 amount;
    f32 timer;
    char status[104];
    char object[1];
};

extern void Control_RefreshControllerConnection(struct ControllerProfile *profile);

extern int Control_IsStartButtonSet(struct Shared_Effect *effect);





extern int Control_CountConnectedControllers(void);


extern void Control_ReleasePakLock(void);





extern int Control_IsButtonBSet(struct Shared_Effect *effect);

extern float g_controllerRumbleUpdateInterval;



extern void Control_TrackControllerPakChanges(void);




extern void Control_PollControllerPaks(void);





extern int Control_IsButtonAPressed(struct ControllerProfile *controllerProfile);
extern void Control_ResetControllerPak(struct ControllerProfile *pakProfile);

extern int Control_IsControllerPakPresent(int controllerPort);

struct ControllerRumbleView;
typedef struct ControllerRumbleView ControllerRumbleView;


extern void Control_CommitControllerInputs(void);

extern f32 Rumble_GetSpatialEffectLevel(void *effectPool, s32 positionXBits, s32 positionYBits, s32 positionZBits);

extern void Control_ReadControllerStates(void);
extern void Control_CommitProfileInput(struct ControllerProfile *controllerProfile);
extern s32 Tsmos_IsControllerStateActive(void);

extern s32 Control_IsAnyControllerPakEnabled(void);

#endif
#endif
