#ifndef RENDER_WEAPON_INITIALIZECHARGEANDSTARTUPCUES_DATA_H
#define RENDER_WEAPON_INITIALIZECHARGEANDSTARTUPCUES_DATA_H
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/INTEGERSTATE1250.H"
#include "COMMON/ITEMRECAT20V1.H"
struct PlayerForceMarkerCounterView {
    unsigned char padding_0[5848];
    u16 eventCounter;
};
struct PlayerTintBlendStateView {
    unsigned char padding_0[1508];
    s32 health;
    unsigned char padding_5E8[3288];
    f32 reactionReserve;
};
struct PlayerEffectTimerSet {
    char pad[0x1248];
    Timer timers[5];
};
struct PlayerAlternateFireStateView {
    unsigned char padding_0[1508];
    s32 health;
    unsigned char padding_5E8[3112];
    s32 alternateFireMarker;
    s32 alternateFireMarkerState;
};
struct PlayerWeaponDelayStateView {
    char pad0[0x170];
    char damageState;
    char pad170[0x174 - 0x170 - sizeof(char)];
    s32 delayedDamage;
    char pad174[0x11E4 - 0x174 - sizeof(s32)];
    f32 delayedDamageTimer;
    char pad11E4[0x13E0 - 0x11E4 - sizeof(f32)];
    s32 damageSource;
};
struct PlayerForceMarkerHandleView {
    char pad0[0x120C];
    s32 forceMarkerModelSelector;
};
struct PlayerWeaponTransitionParameterView {
    unsigned char padding_0[5840];
    s32 transitionParameter;
};
struct PlayerForceMarkerMatrixView {
    char pad0[0x160];
    MatrixF viewMatrix;
};
struct PlayerForceMarkerOwnerView {
    char pad0[0x5DC];
    MatrixF * transformOwner;
};
struct PlayerLoopingSoundHandleView {
    unsigned char padding_0[4540];
    s32 primarySoundHandle;
};
struct PlayerForceMarkerStateView {
    unsigned char padding_0[4684];
    s32 remainingTime;
};
extern void Playerai_StopPrimaryAttachedSound(void *);
#endif
