#ifndef COMMON_PAKQUEUESTATE_H
#define COMMON_PAKQUEUESTATE_H
struct ControllerProfile;
#ifndef COMMON_PAKQUEUESTATE_TYPES_H
#define COMMON_PAKQUEUESTATE_TYPES_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"

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




struct ControllerInputByteStateView;
typedef struct ControllerInputByteStateView ControllerInputByteStateView;


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

extern void Control_RefreshControllerConnection(void *controllerProfile);

extern int Control_IsStartButtonSet(Shared_Effect *effect);




struct ControllerInputRenderView;
typedef struct ControllerInputRenderView ControllerInputRenderView;

extern int Control_CountConnectedControllers(void);


extern void Control_ReleasePakLock(void);





extern int Control_IsButtonBSet(Shared_Effect *effect);

extern float g_controllerRumbleUpdateInterval;


struct ControllerInputByteStateView;
struct ControllerInputByteStateView {
    unsigned char padding_0[44];
    s8 taps;
    s8 age;
    s8 repeat;
    s8 held;
};

extern void Control_TrackControllerPakChanges(void);




extern void Control_PollControllerPaks(void);





extern int Control_IsButtonAPressed(struct ControllerProfile *controllerProfile);
extern void Control_ResetControllerPak(struct ControllerProfile *pakProfile);

extern int Control_IsControllerPakPresent(int controllerPort);

struct ControllerRumbleView;
typedef struct ControllerRumbleView ControllerRumbleView;

struct ControllerInputRenderView;
struct ControllerInputRenderView {
    s32 connected;
    char pad0[0x4 - 0x0 - sizeof(s32)];
    s8 port;
    char pad4[0x8 - 0x4 - sizeof(s8)];
    s32 connectResetWord1;
    char pad8[0xC - 0x8 - sizeof(s32)];
    s32 connectResetWord2;
    char padC[0x10 - 0xC - sizeof(s32)];
    s32 connectResetWord3;
    char pad10[0x14 - 0x10 - sizeof(s32)];
    s32 inputPreviousButtons;
    char pad14[0x18 - 0x14 - sizeof(s32)];
    s32 inputButtons;
    char pad18[0x1C - 0x18 - sizeof(s32)];
    s32 inputPressedButtons;
    char pad1C[0x20 - 0x1C - sizeof(s32)];
    s32 inputHistory1;
    char pad20[0x24 - 0x20 - sizeof(s32)];
    s32 inputHistory2;
    char pad24[0x28 - 0x24 - sizeof(s32)];
    s32 inputHistory3;
    char pad28[0xC4 - 0x28 - sizeof(s32)];
    s8 stickX;
    char padC4[0xC5 - 0xC4 - sizeof(s8)];
    s8 stickY;
    char padC5[0xC6 - 0xC5 - sizeof(s8)];
    s8 previousStickX;
    char padC6[0xC7 - 0xC6 - sizeof(s8)];
    s8 previousStickY;
    char padC7[0xC8 - 0xC7 - sizeof(s8)];
    s32 pakActive;
    char padC8[0xCC - 0xC8 - sizeof(s32)];
    s32 mode;
    char padCC[0xD0 - 0xCC - sizeof(s32)];
    s32 pakAmount;
    char padD0[0xD4 - 0xD0 - sizeof(s32)];
    s32 pakTimer;
    char padD4[0x220 - 0xD4 - sizeof(s32)];
    s32 reset;
};

extern void Control_CommitControllerInputs(void);

extern f32 Rumble_GetSpatialEffectLevel(void *effectPool, s32 positionXBits, s32 positionYBits, s32 positionZBits);

extern void Control_ReadControllerStates(void);
extern void Control_CommitProfileInput(void *controllerProfile);
extern s32 Tsmos_IsControllerStateActive(void);

extern s32 Control_IsAnyControllerPakEnabled(void);

#endif
#endif
