#include "TYPES.H"
extern char g_weaponFireStateCallbackTable[];
#include "include_asm.h"
#if defined(VERSION_US)
/* 800C9F00.CPP */
extern char addrLow_Weaponai_InitializeSwitchForSingleRound_us[];
extern char addrLow_Weaponai_UpdateAlternateFire_us[];
extern char addrLow_Weapon_UpdateIdleWeaponSelection_us[];
extern char addrLow_Weaponai_UpdateSpinAndAlternateFire_us[];
extern char addrLow_Weaponai_SelectReleasedFireState_us[];
extern char addrLow_Weaponai_UpdateHeldFire_us[];
extern char addrLow_Weapon_InitializeChargeForWeaponFive_eu_us[];
extern char addrLow_Weapon_StartState0_eu[];
extern char addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant1[];
extern char addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant4[];
extern char addrLow_Weapon_UpdateTriggerReleaseState_us[];
extern char addrLow_Weapon_ReleaseHandlesAndExitState39_us[];
extern char addrLow_Weapon_PlayStartupCue9E2_us[];
extern char addrLow_Weapon_AdvanceSpinAndTriggerMode_us[];
#if defined(VERSION_US)
struct {
    f32 targetFacingEaseRate;
    f32 reactionReserveApproachRate;
    f32 aimRates[3];
    s16 weaponAnimationDurationPairs[30];
    s32 handMirrorAxesAndFlags[5];
    f32 weaponRestOffset;
    void * nextTable;
    u32 stateTableHeaderReserved[7];
    s32 state0Id;
    void * state0Enter;
    void * state0Update;
    u32 state0Reserved;
    s32 state0Animation;
    f32 state0Rate;
    s32 state0Threshold;
    u32 state0Flags;
    s32 state1Id;
    void * state1Enter;
    void * state1Update;
    u32 state1Reserved;
    s32 state1Animation;
    f32 state1Rate;
    s32 state1Threshold;
    u32 state1Flags;
    s32 state2Id;
    void * state2Enter;
    void * state2Update;
    u32 state2Reserved;
    s32 state2Animation;
    f32 state2Rate;
    s32 state2Threshold;
    u32 state2Flags;
    s32 state3Id;
    void * state3Enter;
    void * state3Update;
    u32 state3Reserved;
    s32 state3Animation;
    f32 state3Rate;
    s32 state3Threshold;
    u32 state3Flags;
    s32 state4Id;
    void * state4Enter;
    void * state4Update;
    u32 state4Reserved;
    void * state4AnimationList;
    f32 state4Rate;
    s32 state4Threshold;
    u32 state4Flags;
    s32 state5Id;
    void * state5Enter;
    void * state5Update;
    u32 state5Reserved;
    void * state5AnimationList;
    f32 state5Rate;
    s32 state5Threshold;
    u32 state5Flags;
    s32 state6Id;
    void * state6Enter;
    void * state6Update;
    u32 state6Reserved;
    s32 state6Animation;
    f32 state6Rate;
    s32 state6Threshold;
    u32 state6Flags;
    s32 state7Id;
    void * state7Enter;
    void * state7Update;
    u32 state7Reserved;
    s32 state7Animation;
    f32 state7Rate;
    s32 state7Threshold;
    u32 state7Flags;
    void * table8Next;
    u32 table8HeaderReserved[7];
    s32 state9Id;
    void * state9Enter;
    void * state9Update;
    u32 state9Reserved;
    s32 state9Animation;
    f32 state9Rate;
    s32 state9Threshold;
    u32 state9Flags;
    s32 state10Id;
    void * state10Enter;
    void * state10Update;
    u32 state10Reserved;
    s32 state10Animation;
    f32 state10Rate;
    s32 state10Threshold;
    u32 state10Flags;
    s32 state11Id;
    void * state11Enter;
    void * state11Update;
    u32 state11Reserved;
    s32 state11Animation;
    f32 state11Rate;
    s32 state11Threshold;
    u32 state11Flags;
    s32 state12Id;
    void * state12Enter;
    void * state12Update;
    u32 state12Reserved;
    s32 state12Animation;
    f32 state12Rate;
    s32 state12Threshold;
    u32 state12Flags;
    void * table13Next;
    u32 table13HeaderReserved[7];
    s32 state14Id;
    void * state14Enter;
    void * state14Update;
    u32 state14Reserved;
    s32 state14Animation;
    f32 state14Rate;
    s32 state14Threshold;
    u32 state14Flags;
    s32 state15Id;
    void * state15Enter;
    void * state15Update;
    u32 state15Reserved;
    s32 state15Animation;
    f32 state15Rate;
    s32 state15Threshold;
    u32 state15Flags;
    s32 state16Id;
    void * state16Enter;
    void * state16Update;
    u32 state16Reserved;
    s32 state16Animation;
    f32 state16Rate;
    s32 state16Threshold;
    u32 state16Flags;
    s32 state17Id;
    void * state17Enter;
    void * state17Update;
    u32 state17Reserved;
    s32 state17Animation;
    f32 state17Rate;
    s32 state17Threshold;
    u32 state17Flags;
    s32 state18Id;
    void * state18Enter;
    void * state18Update;
    u32 state18Reserved;
    s32 state18Animation;
    f32 state18Rate;
    s32 state18Threshold;
    u32 state18Flags;
} g_weaponSwitchStateWordsUs __attribute__((aligned(4))) = {
    0.349999994f,
    0.00625000009f,
    { 7.53039893e+28f, 0.0f, 1.0f },
    { 20210, 10, 20220, 10, 20230, 10, 20240, 10, -1, 0, 20550, 10, 20551, 10, 20552, 10, 20553, 10, -1, 0, 20510, 10, 20520, 10, 20530, 10, 20540, 10, -1, 0 },
    { 0, 0, 0, 0, 0 },
    -3.0f,
    0,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    0,
    (void *)&addrLow_Weaponai_InitializeSwitchForSingleRound_us,
    (void *)&addrLow_Weapon_StartState0_eu,
    0x0,
    20000,
    1.0f,
    0,
    0x0,
    1,
    (void *)&addrLow_Weapon_ReleaseHandlesAndExitState39_us,
    (void *)&addrLow_Weapon_UpdateIdleWeaponSelection_us,
    0x0,
    20010,
    1.0f,
    2,
    0x0,
    2,
    (void *)&addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant1,
    (void *)&addrLow_Weaponai_UpdateAlternateFire_us,
    0x0,
    20100,
    1.0f,
    0,
    0x0,
    3,
    0,
    (void *)&addrLow_Weaponai_UpdateAlternateFire_us,
    0x0,
    20110,
    1.0f,
    0,
    0x0,
    4,
    (void *)&addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant4,
    (void *)&addrLow_Weapon_UpdateTriggerReleaseState_us,
    0x0,
    (void *)((char *)&g_weaponSwitchStateWordsUs + 20),
    1.0f,
    3,
    0x0,
    8,
    (void *)&addrLow_Weapon_InitializeChargeForWeaponFive_eu_us,
    (void *)&addrLow_Weaponai_UpdateHeldFire_us,
    0x0,
    (void *)((char *)&g_weaponSwitchStateWordsUs + 40),
    1.0f,
    3,
    0x0,
    7,
    0,
    (void *)&addrLow_Weapon_UpdateIdleWeaponSelection_us,
    0x0,
    20249,
    1.0f,
    3,
    0x0,
    -1,
    0,
    0,
    0x0,
    0,
    0.0f,
    0,
    0x0,
    (void *)&g_weaponFireStateCallbackTable,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    2,
    0,
    (void *)&addrLow_Weaponai_UpdateSpinAndAlternateFire_us,
    0x0,
    20100,
    1.0f,
    0,
    0x0,
    3,
    0,
    (void *)&addrLow_Weaponai_UpdateSpinAndAlternateFire_us,
    0x0,
    20110,
    1.0f,
    0,
    0x0,
    5,
    (void *)&addrLow_Weapon_PlayStartupCue9E2_us,
    (void *)&addrLow_Weapon_AdvanceSpinAndTriggerMode_us,
    0x0,
    20200,
    1.0f,
    3,
    0x0,
    -1,
    0,
    0,
    0x0,
    0,
    0.0f,
    0,
    0x0,
    (void *)&g_weaponFireStateCallbackTable,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    4,
    0,
    (void *)&addrLow_Weaponai_SelectReleasedFireState_us,
    0x0,
    20200,
    1.0f,
    3,
    0x0,
    8,
    0,
    (void *)&addrLow_Weaponai_SelectReleasedFireState_us,
    0x0,
    20200,
    1.0f,
    3,
    0x20,
    5,
    0,
    (void *)&addrLow_Weapon_UpdateTriggerReleaseState_us,
    0x0,
    20210,
    1.0f,
    3,
    0x20,
    9,
    0,
    (void *)&addrLow_Weapon_UpdateTriggerReleaseState_us,
    0x0,
    20550,
    1.0f,
    3,
    0x20,
    -1,
    0,
    0,
    0x0,
    0,
    0.0f,
    0,
    0x0
};
typedef char g_weaponSwitchStateWordsUsSizeCheck[(sizeof(g_weaponSwitchStateWordsUs) == 744) ? 1 : -1];
#endif
#endif
