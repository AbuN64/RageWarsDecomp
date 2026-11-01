#include "DATA/REST_SOURCE_RECORDS.H"
#include "DATA/OVL1_E/g_PlayerStateSpecialCallbacks05PointerWords1_Ovl1E.H"
#include "DATA/OVL1_E/g_PlayerStateSpecialCallbacks06PointerWords1_Ovl1E.H"
#include "DATA/OVL1_E/g_PlayerStateSpecialCallbacks07PointerWords1_Ovl1E.H"
#include "DATA/OVL1_E/g_PlayerStateSpecialCallbacks08PointerWords1_Ovl1E.H"

/* 800CE8DC.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC */
RestLinkerAlignmentFill4 g_weaponActionRecords_StorageLinkerAlignmentFill797 = {
    { 0, 2, 0, 0 },
};
#endif

/* 800CE8DC_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_01_us_rev1.c */
extern char g_Player_UpdateFlyModeAddress[];
RestplayerStateNormalCallbacks01WordsRecord798 g_playerStateNormalCallbacks01Words = {
    0x00000000,
    (unsigned int)g_Player_UpdateFlyModeAddress,
};
#endif

/* 800CE8E8.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8 */
RestPlayerStateNormalCallbacks01TrailWordsRecord799 g_PlayerStateNormalCallbacks01TrailWords = {
    0x801044F8,
};
#endif

/* 800CE8E8_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_01_us_rev1.c */
RestplayerStateNormalTiming01WordsRecord800 g_playerStateNormalTiming01Words = {
    0,
    1,
};
#endif

/* 800CE8F4.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4 */
RestPlayerStateNormalTiming01TrailWordsRecord801 g_PlayerStateNormalTiming01TrailWords = {
    0x00020000,
};
#endif

/* 800CE8F4_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_02_us_rev1.c */
extern char g_Player_UpdateStandingStateAddress[];
extern char g_Player_ZeroBodyVelocityCallbackAddressDe[];
RestplayerStateNormalCallbacks02WordsRecord802 g_playerStateNormalCallbacks02Words = {
    (unsigned int)g_Player_ZeroBodyVelocityCallbackAddressDe,
    (unsigned int)g_Player_UpdateStandingStateAddress,
};
#endif

/* 800CE900.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500 */
RestPlayerStateNormalCallbacks02TrailWordsRecord803 g_PlayerStateNormalCallbacks02TrailWords = {
    0x80104458,
};
#endif

/* 800CE900_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_02_us_rev1.c */
RestplayerStateNormalTiming02WordsRecord804 g_playerStateNormalTiming02Words = {
    0,
    1,
};
#endif

/* 800CE90C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C */
RestLinkerAlignmentFill4 g_PlayerStateNormalTiming02TrailLinkerAlignmentFill805 = {
    { 0, 2, 0, 0 },
};
#endif

/* 800CE90C_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_03_us_rev1.c */
extern char g_Playerai_UpdateWalkingMovementAddress[];
extern char g_PlayerStateSpecialCallbacks03EmptyCallbackPackedAddress24[];
RestplayerStateNormalCallbacks03WordsRecord806 g_playerStateNormalCallbacks03Words = {
    (unsigned int)g_PlayerStateSpecialCallbacks03EmptyCallbackPackedAddress24,
    (unsigned int)g_Playerai_UpdateWalkingMovementAddress,
};
#endif

/* 800CE918.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518 */
RestPlayerStateNormalCallbacks03TrailWordsRecord807 g_PlayerStateNormalCallbacks03TrailWords = {
    0x80104458,
};
#endif

/* 800CE918_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_03_us_rev1.c */
RestplayerStateNormalTiming03WordsRecord808 g_playerStateNormalTiming03Words = {
    0,
    2010,
};
#endif

/* 800CE924.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524 */
RestPlayerStateNormalTiming03TrailWordsRecord809 g_PlayerStateNormalTiming03TrailWords = {
    0x00030000,
};
#endif

/* 800CE924_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_04_us_rev1.c */
extern char g_PlayerStateSpecialCallbacks04EmptyCallbackPackedAddress24[];
extern char g_Player_UpdateGroundMoveStateAddressVariant2[];
RestplayerStateNormalCallbacks04WordsRecord810 g_playerStateNormalCallbacks04Words = {
    (unsigned int)g_PlayerStateSpecialCallbacks04EmptyCallbackPackedAddress24,
    (unsigned int)g_Player_UpdateGroundMoveStateAddressVariant2,
};
#endif

/* 800CE930.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530 */
RestPlayerStateNormalCallbacks04TrailWordsRecord811 g_PlayerStateNormalCallbacks04TrailWords = {
    0x80104458,
};
#endif

/* 800CE930_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_04_us_rev1.c */
RestPlayerStateNormalTiming04WordsRecord812 g_PlayerStateNormalTiming04Words = {
    0,
    2660,
};
#endif

/* 800CE93C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C */
RestLinkerAlignmentFill4 g_playerStateNormalTiming04TrailLinkerAlignmentFill813 = {
    { 0, 3, 0, 0 },
};
#endif

/* 800CE93C_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_05_us_rev1.c */
RestPlayerStateNormalCallbacks05WordsRecord814 g_PlayerStateNormalCallbacks05Words = {
    (unsigned int)g_Player_BeginJumpPackedAddress24,
    (unsigned int)g_Player_UpdateJumpAscentPackedAddress24,
};
#endif

/* 800CE948.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548 */
RestplayerStateNormalCallbacks05TrailWordsRecord815 g_playerStateNormalCallbacks05TrailWords = {
    0x80104190,
};
#endif

/* 800CE948_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_05_us_rev1.c */
RestplayerStateNormalTiming05WordsRecord816 g_playerStateNormalTiming05Words = {
    2048,
    2030,
};
#endif

/* 800CE954.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554 */
RestPlayerStateNormalTiming05TrailWordsRecord817 g_PlayerStateNormalTiming05TrailWords = {
    0x00020000,
};
#endif

/* 800CE954_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_06_us_rev1.c */
RestPlayerStateNormalCallbacks06WordsRecord818 g_PlayerStateNormalCallbacks06Words = {
    0x00000000,
    (unsigned int)g_Player_UpdateJumpAirMotionPackedAddress24,
};
#endif

/* 800CE960.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560 */
RestplayerStateNormalCallbacks06TrailWordsRecord819 g_playerStateNormalCallbacks06TrailWords = {
    0x80104190,
};
#endif

/* 800CE960_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_06_us_rev1.c */
RestPlayerStateNormalTiming06WordsRecord820 g_PlayerStateNormalTiming06Words = {
    2048,
    2030,
};
#endif

/* 800CE96C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C */
RestLinkerAlignmentFill4 g_playerStateNormalTiming06TrailLinkerAlignmentFill821 = {
    { 0, 2, 0, 0 },
};
#endif

/* 800CE96C_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_07_us_rev1.c */
RestPlayerStateNormalCallbacks07WordsRecord822 g_PlayerStateNormalCallbacks07Words = {
    (unsigned int)g_Player_BeginLateralLeapPackedAddress24,
    (unsigned int)g_Player_UpdateLateralLeapPackedAddress24,
};
#endif

/* 800CE978.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578 */
RestplayerStateNormalCallbacks07TrailWordsRecord823 g_playerStateNormalCallbacks07TrailWords = {
    0x80104458,
};
#endif

/* 800CE978_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_07_us_rev1.c */
RestPlayerStateNormalTiming07WordsRecord824 g_PlayerStateNormalTiming07Words = {
    0,
    2030,
};
#endif

/* 800CE984.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584 */
RestplayerStateNormalTiming07TrailWordsRecord825 g_playerStateNormalTiming07TrailWords = {
    0x00020000,
};
#endif

/* 800CE984_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_08_us_rev1.c */
RestplayerStateNormalCallbacks08WordsRecord826 g_playerStateNormalCallbacks08Words = {
    0x00000000,
    (unsigned int)g_Player_UpdateLeapMotionPackedAddress24,
};
#endif

/* 800CE990.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590 */
RestPlayerStateNormalCallbacks08TrailWordsRecord827 g_PlayerStateNormalCallbacks08TrailWords = {
    0x80104458,
};
#endif

/* 800CE990_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_08_us_rev1.c */
RestplayerStateNormalTiming08WordsRecord828 g_playerStateNormalTiming08Words = {
    0,
    2030,
};
#endif

/* 800CE99C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C */
RestLinkerAlignmentFill4 g_PlayerStateNormalTiming08TrailLinkerAlignmentFill829 = {
    { 0, 2, 0, 0 },
};
#endif

/* 800CE99C_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_09_us_rev1.c */
extern char g_Player_UpdateWadingStateAddress[];
extern char g_Player_ClearGlobalFlagBitPackedAddress24[];
RestplayerStateNormalCallbacks09WordsRecord830 g_playerStateNormalCallbacks09Words = {
    (unsigned int)g_Player_ClearGlobalFlagBitPackedAddress24,
    (unsigned int)g_Player_UpdateWadingStateAddress,
};
#endif

/* 800CE9A8.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8 */
RestPlayerStateNormalCallbacks09TrailWordsRecord831 g_PlayerStateNormalCallbacks09TrailWords = {
    0x80104418,
};
#endif

/* 800CE9A8_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_09_us_rev1.c */
RestplayerStateNormalTiming09WordsRecord832 g_playerStateNormalTiming09Words = {
    128,
    2210,
};
#endif

/* 800CE9B4.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4 */
RestPlayerStateNormalTiming09TrailWordsRecord833 g_PlayerStateNormalTiming09TrailWords = {
    0x00020000,
};
#endif

/* 800CE9B4_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_10_us_rev1.c */
extern char g_Player_UpdateWadingStateAddress[];
extern char g_Player_ClearGlobalFlagBitPackedAddress24[];
RestplayerStateNormalCallbacks10WordsRecord834 g_playerStateNormalCallbacks10Words = {
    (unsigned int)g_Player_ClearGlobalFlagBitPackedAddress24,
    (unsigned int)g_Player_UpdateWadingStateAddress,
};
#endif

/* 800CE9C0.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0 */
RestPlayerStateNormalCallbacks10TrailWordsRecord835 g_PlayerStateNormalCallbacks10TrailWords = {
    0x80104418,
};
#endif

/* 800CE9C0_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_10_us_rev1.c */
RestplayerStateNormalTiming10WordsRecord836 g_playerStateNormalTiming10Words = {
    128,
    2210,
};
#endif

/* 800CE9CC.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC */
RestLinkerAlignmentFill4 g_PlayerStateNormalTiming10TrailLinkerAlignmentFill837 = {
    { 0, 3, 0, 0 },
};
#endif

/* 800CE9CC_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_11_us_rev1.c */
extern char g_Player_UpdateFloatingStateAddress[];
extern char g_Player_AbsorbImpactPackedAddress24[];
RestplayerStateNormalCallbacks11WordsRecord838 g_playerStateNormalCallbacks11Words = {
    (unsigned int)g_Player_AbsorbImpactPackedAddress24,
    (unsigned int)g_Player_UpdateFloatingStateAddress,
};
#endif

/* 800CE9D8.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8 */
RestPlayerStateNormalCallbacks11TrailWordsRecord839 g_PlayerStateNormalCallbacks11TrailWords = {
    0x80103FB0,
};
#endif

/* 800CE9D8_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_11_us_rev1.c */
RestPlayerStateNormalTiming11WordsRecord840 g_PlayerStateNormalTiming11Words = {
    64,
    2210,
};
#endif

/* 800CE9E4.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8_unclaimed_CF5E4 */
RestplayerStateNormalTiming11TrailWordsRecord841 g_playerStateNormalTiming11TrailWords = {
    0x00020000,
};
#endif

/* 800CE9E4_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_12_us_rev1.c */
extern char g_Player_UpdateFloatingStateAddress[];
extern char g_Player_AbsorbImpactPackedAddress24[];
RestplayerStateNormalCallbacks12WordsRecord842 g_playerStateNormalCallbacks12Words = {
    (unsigned int)g_Player_AbsorbImpactPackedAddress24,
    (unsigned int)g_Player_UpdateFloatingStateAddress,
};
#endif

/* 800CE9F0.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8_unclaimed_CF5E4_unclaimed_CF5F0 */
RestPlayerStateNormalCallbacks12TrailWordsRecord843 g_PlayerStateNormalCallbacks12TrailWords = {
    0x80103FB0,
};
#endif

/* 800CE9F0_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_12_us_rev1.c */
RestPlayerStateNormalTiming12WordsRecord844 g_PlayerStateNormalTiming12Words = {
    64,
    2210,
};
#endif

/* 800CE9FC.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8_unclaimed_CF5E4_unclaimed_CF5F0_unclaimed_CF5FC */
RestLinkerAlignmentFill4 g_playerStateNormalTiming12TrailLinkerAlignmentFill845 = {
    { 0, 3, 0, 0 },
};
#endif

/* 800CE9FC_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_13_us_rev1.c */
extern char g_Player_DampMotionPackedAddress24[];
extern char addrLow_Player_AbsorbImpact_eu[];
RestplayerStateNormalCallbacks13WordsRecord846 g_playerStateNormalCallbacks13Words = {
    (unsigned int)g_Player_DampMotionPackedAddress24,
    (unsigned int)addrLow_Player_AbsorbImpact_eu,
};
#endif

/* 800CEA08.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8_unclaimed_CF5E4_unclaimed_CF5F0_unclaimed_CF5FC_unclaimed_CF608 */
RestPlayerStateNormalCallbacks13TrailWordsRecord847 g_PlayerStateNormalCallbacks13TrailWords = {
    0x801041B0,
};
#endif

/* 800CEA08_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_13_us_rev1.c */
RestplayerStateNormalTiming13WordsRecord848 g_playerStateNormalTiming13Words = {
    0,
    2010,
};
#endif

/* 800CEA14.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8_unclaimed_CF5E4_unclaimed_CF5F0_unclaimed_CF5FC_unclaimed_CF608_unclaimed_CF614 */
RestPlayerStateNormalTiming13TrailWordsRecord849 g_PlayerStateNormalTiming13TrailWords = {
    0x00020000,
};
#endif

/* 800CEA14_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_14_us_rev1.c */
extern char g_Player_DampMotionPackedAddress24[];
extern char addrLow_Player_AbsorbImpact_eu[];
RestplayerStateNormalCallbacks14WordsRecord850 g_playerStateNormalCallbacks14Words = {
    (unsigned int)g_Player_DampMotionPackedAddress24,
    (unsigned int)addrLow_Player_AbsorbImpact_eu,
};
#endif

/* 800CEA20.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8_unclaimed_CF5E4_unclaimed_CF5F0_unclaimed_CF5FC_unclaimed_CF608_unclaimed_CF614_unclaimed_CF620 */
RestPlayerStateNormalCallbacks14TrailWordsRecord851 g_PlayerStateNormalCallbacks14TrailWords = {
    0x801041B0,
};
#endif

/* 800CEA20_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_14_us_rev1.c */
RestPlayerStateNormalTiming14WordsRecord852 g_PlayerStateNormalTiming14Words = {
    0,
    2010,
};
#endif

/* 800CEA2C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8_unclaimed_CF5E4_unclaimed_CF5F0_unclaimed_CF5FC_unclaimed_CF608_unclaimed_CF614_unclaimed_CF620_unclaimed_CF62C */
RestLinkerAlignmentFill4 g_playerStateNormalTiming14TrailLinkerAlignmentFill853 = {
    { 0, 2, 0, 0 },
};
#endif

/* 800CEA2C_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_15_us_rev1.c */
extern char g_Player_UpdateSwimmingStateAddress[];
extern char g_Player_ResetMovementInputPackedAddress24[];
RestplayerStateNormalCallbacks15WordsRecord854 g_playerStateNormalCallbacks15Words = {
    (unsigned int)g_Player_ResetMovementInputPackedAddress24,
    (unsigned int)g_Player_UpdateSwimmingStateAddress,
};
#endif

/* 800CEA38.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8_unclaimed_CF5E4_unclaimed_CF5F0_unclaimed_CF5FC_unclaimed_CF608_unclaimed_CF614_unclaimed_CF620_unclaimed_CF62C_unclaimed_CF638 */
RestPlayerStateNormalCallbacks15TrailWordsRecord855 g_PlayerStateNormalCallbacks15TrailWords = {
    0x80104358,
};
#endif

/* 800CEA38_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_15_us_rev1.c */
RestPlayerStateNormalTiming15WordsRecord856 g_PlayerStateNormalTiming15Words = {
    256,
    2620,
};
#endif

/* 800CEA44.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8_unclaimed_CF5E4_unclaimed_CF5F0_unclaimed_CF5FC_unclaimed_CF608_unclaimed_CF614_unclaimed_CF620_unclaimed_CF62C_unclaimed_CF638_unclaimed_CF644 */
RestplayerStateNormalTiming15TrailWordsRecord857 g_playerStateNormalTiming15TrailWords = {
    0x00020000,
};
#endif

/* 800CEA44_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_16_us_rev1.c */
extern char g_Player_ResetObjectVelocityPackedAddress24[];
extern char g_Player_ResetObjectVelocityAddressVariant2[];
RestplayerStateNormalCallbacks16WordsRecord858 g_playerStateNormalCallbacks16Words = {
    (unsigned int)g_Player_ResetObjectVelocityPackedAddress24,
    (unsigned int)g_Player_ResetObjectVelocityAddressVariant2,
};
#endif

/* 800CEA50.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0_unclaimed_CF4DC_unclaimed_CF4E8_unclaimed_CF4F4_unclaimed_CF500_unclaimed_CF50C_unclaimed_CF518_unclaimed_CF524_unclaimed_CF530_unclaimed_CF53C_unclaimed_CF548_unclaimed_CF554_unclaimed_CF560_unclaimed_CF56C_unclaimed_CF578_unclaimed_CF584_unclaimed_CF590_unclaimed_CF59C_unclaimed_CF5A8_unclaimed_CF5B4_unclaimed_CF5C0_unclaimed_CF5CC_unclaimed_CF5D8_unclaimed_CF5E4_unclaimed_CF5F0_unclaimed_CF5FC_unclaimed_CF608_unclaimed_CF614_unclaimed_CF620_unclaimed_CF62C_unclaimed_CF638_unclaimed_CF644_unclaimed_CF650 */
RestPlayerStateNormalCallbacks16TrailWordsRecord859 g_PlayerStateNormalCallbacks16TrailWords = {
    0x80104458,
};
#endif

/* 800CEA50_2.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_16_us_rev1.c */
RestPlayerStateNormalTiming16WordsRecord860 g_PlayerStateNormalTiming16Words = {
    524288,
    1,
};
#endif
