#ifndef COMMON_STATERECAT10_H
#define COMMON_STATERECAT10_H
#include "TYPES.H"
struct CShakeAxis_t;
typedef struct CShakeAxis_t CShakeAxis;



extern float g_weaponShakeInitialAngle;

extern float g_weaponShakeAngleRate;

extern float g_weaponActionFiveNegativeFeedbackLimit;

extern float g_weaponReleaseSpinTarget;


extern float g_weaponStateEightDelay;

struct WeaponSpecialFirePlayerView;
typedef struct WeaponSpecialFirePlayerView WeaponSpecialFirePlayerView;

struct CShakeAxis_t;
struct CShakeAxis_t {
    s32 mode;
    f32 value;
    f32 m_LastShake;
    f32 m_Amp;
    f32 m_Angle;
};

extern float g_weaponActionFiveClampedFeedback;


extern float g_weaponAlternateFireAnimationThreshold;


extern float g_weaponShakeActiveDecay;

extern float g_weaponActionFivePositiveFeedbackScale;


extern float g_weaponActionFiveSpinTargetScale;

extern float g_weaponActionFivePositiveOutputScale;

extern float g_weaponShakeIdleDecay;


extern float g_weaponActionFiveNegativeFeedbackScale;

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
