#ifndef COMMON_WEAPON_SPECIAL_FIRE_H
#define COMMON_WEAPON_SPECIAL_FIRE_H
#include "types.h"
#include "Common/camera_shake.h"




extern float g_weaponShakeInitialAngle;

extern float g_weaponShakeAngleRate;

extern float g_weaponEasedSpinNegativeFeedbackLimit;

extern float g_weaponReleaseSpinTarget;


extern float g_weaponDelayStateLifetime;

struct WeaponSpecialFirePlayerView;
typedef struct WeaponSpecialFirePlayerView WeaponSpecialFirePlayerView;



extern float g_weaponEasedSpinClampedFeedback;


extern float g_weaponAlternateFireAnimationThreshold;


extern float g_weaponShakeActiveDecay;

extern float g_weaponEasedSpinPositiveFeedbackScale;


extern float g_weaponEasedSpinSpinTargetScale;

extern float g_weaponEasedSpinPositiveOutputScale;

extern float g_weaponShakeIdleDecay;


extern float g_weaponEasedSpinNegativeFeedbackScale;

struct WeaponSpecialFirePlayerView;
struct WeaponSpecialFirePlayerView {
    char pad0[0x5D8];
    char * controller;
    char pad5D8[0x62E - 0x5D8 - sizeof(char*)];
    s16 ammoMode;
    char pad62E[0x650 - 0x62E - sizeof(s16)];
    s16 weaponActionIndex;
    char pad650[0x6AC - 0x650 - sizeof(s16)];
    s32 actionFlags;
    char pad6AC[0x770 - 0x6AC - sizeof(s32)];
    s16 nextUsableWeapon;
    char pad770[0x11D8 - 0x770 - sizeof(s16)];
    f32 delay;
};
#endif
