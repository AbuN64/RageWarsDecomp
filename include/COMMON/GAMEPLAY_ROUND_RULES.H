#ifndef COMMON_GAMEPLAY_ROUND_RULES_H
#define COMMON_GAMEPLAY_ROUND_RULES_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"


typedef struct FragTagPlayerStateView FragTagPlayerStateView;
struct FragTagPlayerStateView {
    char pad0[0x8];
    CVector3 position; /* +0x8: actor position, shared player provider and sound CVector3 argument. */
    char pad14[0x4];
    struct FragTagActorModelView * model; /* +0x18: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad1C[0x158];
    s32 restoredHealth; /* +0x174: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad178[0x170];
    s8 bodyStateStorage; /* +0x2E8: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad2E9[0x16F];
    s8 weaponStateStorage; /* +0x458: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad459[0x17B];
    s32 playerIndex; /* +0x5D4: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    struct FragTagActiveProfileView * profile; /* +0x5D8: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    void * view; /* +0x5DC: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad5E0[0x4];
    s32 health; /* +0x5E4: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad5E8[0x4];
    s32 spawnPoint; /* +0x5EC: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad5F0[0x348];
    char animationState[2172]; /* +0x938: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    s32 reserved11B4; /* +0x11B4: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad11B8[0x298];
    s32 computerControlled; /* +0x1450: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
};


typedef struct FragTagSelectionProfileView FragTagSelectionProfileView;
struct FragTagSelectionProfileView {
    char pad0[0x80];
    s8 team; /* +0x80: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad81[0xF];
    u8 assigned; /* +0x90: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad91[0x3];
    u8 selected; /* +0x94: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
};


typedef struct PlayerCameraTargetView PlayerCameraTargetView;
struct PlayerCameraTargetView {
    u8 pad0[0x128];
    CVector3 position; /* 0x128 */
    u8 pad134[0xC];
    CQuatern orientation; /* 0x140 */
    u8 pad150[0x10];
    f32 transform[16]; /* 0x160 */
    u8 pad1A0[0x29C - 0x1A0];
    f32 viewportWidth; /* +0x29C: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    f32 viewportHeight; /* +0x2A0: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    f32 viewportX; /* +0x2A4: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    f32 viewportY; /* +0x2A8: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad2AC[0x2B8];
    s32 disabled; /* +0x564: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
};



typedef struct FragTagActiveProfileView FragTagActiveProfileView;
struct FragTagActiveProfileView {
    char pad0[0x8F];
    s8 fragTagEnabled; /* +0x8F: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
};


typedef struct FragTagActorModelView FragTagActorModelView;
struct FragTagActorModelView {
    char pad0[0x18];
    s32 modelId; /* +0x18: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
};


typedef struct FragTagPlayerInputView FragTagPlayerInputView;
struct FragTagPlayerInputView {
    char pad0[0x8];
    CVector3 position; /* +0x8: actor position, shared player provider and sound CVector3 argument. */
    char pad14[0x4];
    struct FragTagActorModelView * model; /* +0x18: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad1C[0x158];
    s32 restoredHealth; /* +0x174: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad178[0x170];
    s8 bodyStateStorage; /* +0x2E8: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad2E9[0x16F];
    s8 weaponStateStorage; /* +0x458: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad459[0x17B];
    s32 playerIndex; /* +0x5D4: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    struct FragTagEnableProfileView * profile; /* +0x5D8: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    void * view; /* +0x5DC: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad5E0[0x4];
    s32 health; /* +0x5E4: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad5E8[0x4];
    s32 spawnPoint; /* +0x5EC: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad5F0[0x348];
    char animationState[2172]; /* +0x938: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    s32 reserved11B4; /* +0x11B4: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad11B8[0x298];
    s32 computerControlled; /* +0x1450: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
};


typedef struct FragTagCameraStateView FragTagCameraStateView;
struct FragTagCameraStateView {
    char pad0[0x29C];
    f32 viewportWidth; /* +0x29C: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    f32 viewportHeight; /* +0x2A0: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    f32 viewportX; /* +0x2A4: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    f32 viewportY; /* +0x2A8: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad2AC[0x2B8];
    s32 disabled; /* +0x564: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
};


typedef struct FragTagEnableProfileView FragTagEnableProfileView;
struct FragTagEnableProfileView {
    char pad0[0x8F];
    u8 fragTagEnabled; /* +0x8F: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
};


typedef struct FragTagTeamProfileView FragTagTeamProfileView;
struct FragTagTeamProfileView {
    char pad0[0x80];
    s8 team; /* +0x80: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad81[0xE];
    u8 fragTagEnabled; /* +0x8F: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    char pad90[0x4];
    u8 selected; /* +0x94: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
};


typedef struct FragTagAssignmentProfileView FragTagAssignmentProfileView;
struct FragTagAssignmentProfileView {
    char pad0[0x8F];
    u8 fragTagEnabled; /* +0x8F: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
    s8 assigned; /* +0x90: src/Player_UpdateFragTagSelection_GameplayRoundRules.c */
};


#endif
