#include "types.h"
#include "Data/Player_callbacks/playerstate_callback_rom_entry.h"
#include "Data/Overlays/Playerstate/linktables_addresses.h"
#include "Ai/player_team_score.h"
#include "Common/player_action_and_pose_views.h"
#include "Data/Player_callbacks/playerstate_link_record_rom_link_targets.h"
#include "Common/aiprofile.h"
#include "Data/Player_callbacks/player_sequence_callback_addresses.h"
#include "Data/Ovltbl/player_state_callback_link_targets.h"
#include "Common/player_sequence_state.h"
#include "Data/Player_callbacks/player_empty_action_hook_addresses.h"

/* G_OVERLAYFIVELINKRECORDCONSTANTWORDS.CPP */
#if defined(VERSION_US_REV1)
extern struct {
    s32 timer;
    s32 parameter;
} g_playerStateLinkRecordConstantWords __attribute__((aligned(4)));
#endif

/* G_OVERLAYFIVELINKRECORDLINKWORDS.CPP */
#if defined(VERSION_US_REV1)
void * g_playerStateLinkRecordLinkWords[2] = {
    (void *)&g_playerLateStateLinkRecordLeadingTarget, 0
};
#endif

/* G_PLAYERSTATEINITIALIZEACTORMODELEFFECTKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateInitializeActorModelEffectKindWord = 0x00010000;
#endif

/* G_PLAYERAIINITIALIZEACTORMODELEFFECTCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playeraiInitializeActorModelEffectCallbacks[2] = {
    (void *)&Playerai_InitializeActorModelEffect, (void *)&g_PlayerInterpolateTravelTargetCallbackAddressUs
};
#endif

/* G_PLAYERSTATEINITIALIZEACTORMODELEFFECTTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
#include "Common/runtime_declarations.h"
void *g_playerStateInitializeActorModelEffectTargetPointer[1] = {
    (void *)&g_collisionSurfaceExcludedFromTrace[64],
};
#endif

/* G_PLAYERSTATEINITIALIZEACTORMODELEFFECTTAILHALFWORDS.CPP */
#if defined(VERSION_US_REV1)
unsigned short g_playerStateInitializeActorModelEffectTailHalfwords[4] __attribute__((aligned(4))) = { 0x0000, 0x0000, 0x0000, 0x5E2D };
#endif

/* G_PLAYERSTATECLEARWEAPONLOCKKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateClearWeaponLockKindWord = 0x00010000;
#endif

/* G_PLAYERAICLEARPLAYERWEAPONLOCKCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playeraiClearPlayerWeaponLockCallbacks[2] = {
    (void *)&Playerai_ClearPlayerWeaponLock, (void *)&Playerai_EnterMovingSequenceState
};
#endif

/* G_PLAYERSTATECLEARWEAPONLOCKTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
void *g_playerStateClearWeaponLockTargetPointer[1] = {
    (void *)((char *)&g_portalDefaultCollisionQuery + 32),
};
#endif

/* G_PLAYERSTATECLEARWEAPONLOCKTIMERPARAMETER.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerStateClearWeaponLockTimerParameter __attribute__((aligned(4))) = {
    32768,
    24105
};
#endif

/* G_PLAYERSTATERESETWEAPONLOCKKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateResetWeaponLockKindWord = 0x00020000;
#endif

/* G_PLAYERAIRESETPLAYERWEAPONLOCKCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playeraiResetPlayerWeaponLockCallbacks[2] = {
    (void *)&g_playerStateLinkRecordRomLinkTarget_ResetPlayerWeaponLock,
    (void *)&g_playerStateLinkRecordRomLinkTarget_EnterStoppedSequenceState
};
#endif

/* G_PLAYERSTATERESETWEAPONLOCKTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
void *g_playerStateResetWeaponLockTargetPointer[1] = {
    (void *)((char *)&g_portalDefaultCollisionQuery + 32),
};
#endif

/* G_PLAYERSTATERESETWEAPONLOCKTIMERPARAMETER.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerStateResetWeaponLockTimerParameter __attribute__((aligned(4))) = {
    32768,
    24105
};
#endif

/* G_PLAYERSTATEOFFSETACTORKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateOffsetActorKindWord = 0x00030000;
#endif

/* G_PLAYERAIOFFSETACTORFORSTATE15CALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playeraiOffsetActorForForceMarkerCallbacks[2] = {
    (void *)&Playerai_OffsetActorForForceMarker, (void *)&g_PlayerUpdateHeldActorReleaseCallbackAddressUs
};
#endif

/* G_PLAYERSTATEOFFSETACTORTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
void *g_playerStateOffsetActorTargetPointer[1] = {
    (void *)&g_secondaryCollisionContext[1],
};
#endif

/* G_PLAYERSTATEOFFSETACTORTIMERPARAMETER.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerStateOffsetActorTimerParameter __attribute__((aligned(4))) = {
    0,
    9200
};
#endif

/* G_PLAYERSTATEEMPTYHOOKKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateEmptyHookKindWord = 0x00020000;
#endif

/* G_PLAYERSTATE39EMPTYHOOKCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playerLateStateEmptyHookAimTrackCallbacks[2] = {
    (void *)&g_playerLateStateEmptyHookAddress, (void *)&g_PlayerTrackNearbyAimTargetCallbackAddressUs
};
#endif

/* G_PLAYERSTATEEMPTYHOOKTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
void *g_playerStateEmptyHookTargetPointer[1] = {
    (void *)&g_secondaryCollisionContext[1],
};
#endif

/* G_PLAYERSTATEEMPTYHOOKTAILHALFWORDS.CPP */
#if defined(VERSION_US_REV1)
unsigned short g_playerStateEmptyHookTailHalfwords[4] __attribute__((aligned(4))) = { 0x0000, 0x0000, 0x0000, 0x5E24 };
#endif

/* G_PLAYERSTATEHOOKWITHTAILHALFWORDSKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateHookWithTailHalfwordsKindWord = 0x00020000;
#endif

/* G_PLAYERSTATE40CALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playerLateStateNoOperationPairCallbacks[2] = {
    (void *)&g_playerLateStateNoOperationPairLeadingTarget, (void *)&g_playerStateNoOperationCallbackWords[0x2C9]
};
#endif

/* G_PLAYERSTATEHOOKWITHTAILHALFWORDSTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
void *g_playerStateHookWithTailHalfwordsTargetPointer[1] = {
    (void *)&g_secondaryCollisionContext[1],
};
#endif

/* G_PLAYERSTATEHOOKWITHTAILHALFWORDSTAILHALFWORDS.CPP */
#if defined(VERSION_US_REV1)
unsigned short g_playerStateHookWithTailHalfwordsTailHalfwords[4] __attribute__((aligned(4))) = { 0x0000, 0x0000, 0x0000, 0x5E24 };
#endif

/* G_PLAYERSTATEHOOKWITHTIMERKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateHookWithTimerKindWord = 0x00020000;
#endif

/* G_PLAYERSTATE41CALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playerLinkTargetPairCallbacks[2] = {
    (void *)&g_playerLinkTargetPairLeadingTarget, (void *)&g_playerLinkTargetPairTrailingTarget
};
#endif

/* G_PLAYERSTATEHOOKWITHTIMERTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
void *g_playerStateHookWithTimerTargetPointer[1] = {
    (void *)&g_secondaryCollisionContext[1],
};
#endif

/* G_PLAYERSTATEHOOKWITHTIMERTIMERPARAMETER.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerStateHookWithTimerTimerParameter __attribute__((aligned(4))) = {
    0,
    7043
};
#endif

/* G_PLAYERSTATERUNENDPOSEENTRYKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateRunEndPoseEntryKindWord = 0x00020000;
#endif

/* G_PLAYERSTATERUNENDPOSEENTRYCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playerStateRunEndPoseEntryCallbacks[2] = {
    (void *)&addrLow_Playerai_UpdateSwimmingChestbursterDeathSequenceWait_us,
    (void *)&addrLow_Playerai_StartRaptorChestbursterDeathSequence_us
};
#endif

/* G_PLAYERSTATERUNENDPOSEENTRYTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
#include "Common/effectrender.h"
void *g_playerStateRunEndPoseEntryTargetPointer[1] = {
    (void *)((char *)&g_particleOwnerEffectFlags + 8),
};
#endif

/* G_PLAYERSTATERUNENDPOSEENTRYTIMERPARAMETER.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerStateRunEndPoseEntryTimerParameter __attribute__((aligned(4))) = {
    0,
    7044
};
#endif

/* G_PLAYERSTATERUNENDPOSECONTINUEDKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateRunEndPoseContinuedKindWord = 0x00010000;
#endif

/* G_PLAYERSTATERUNENDPOSECONTINUEDCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playerStateRunEndPoseContinuedCallbacks[2] = {
    (void *)&addrLow_Playerai_UpdateRaptorChestbursterDeathSequenceWait_us,
    (void *)&addrLow_Playerai_StartSwimmingRaptorChestbursterDeathSequence_us
};
#endif

/* G_PLAYERSTATERUNENDPOSECONTINUEDTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
#include "Common/effectrender.h"
void *g_playerStateRunEndPoseContinuedTargetPointer[1] = {
    (void *)((char *)&g_particleOwnerEffectFlags + 8),
};
#endif

/* G_PLAYERSTATERUNENDPOSECONTINUEDTIMERPARAMETER.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerStateRunEndPoseContinuedTimerParameter __attribute__((aligned(4))) = {
    0,
    7045
};
#endif

/* G_PLAYERSTATERUNENDPOSEFINALKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateRunEndPoseFinalKindWord = 0x00010000;
#endif

/* G_PLAYERSTATERUNENDPOSEFINALCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playerStateRunEndPoseFinalCallbacks[2] = {
    (void *)&addrLow_Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait_us,
    (void *)&g_Playerai_InitializeActorModelEffectCallbackAddressUs
};
#endif

/* G_PLAYERSTATERUNENDPOSEFINALTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
#include "Common/effectrender.h"
void *g_playerStateRunEndPoseFinalTargetPointer[1] = {
    (void *)((char *)&g_particleOwnerEffectFlags + 8),
};
#endif

/* G_PLAYERSTATERUNENDPOSEFINALTIMERPARAMETER.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerStateRunEndPoseFinalTimerParameter __attribute__((aligned(4))) = {
    0,
    7046
};
#endif

/* G_PLAYERSTATENOOPSHORTSEQUENCEWAITKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateNoopShortSequenceWaitKindWord = 0x00010000;
#endif

/* G_PLAYERAINOOPSHORTSEQUENCEWAITFIRSTDECALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playerShortSequenceWaitCallbacks[2] = {
    (void *)&Playerai_NoopBastilleSquatStart, (void *)&Playerai_NoopBastilleSquatUpdate
};
#endif

/* G_PLAYERSTATENOOPSHORTSEQUENCEWAITTARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
void *g_playerStateNoopShortSequenceWaitTargetPointer[1] = {
    (void *)&g_secondaryCollisionContext[1],
};
#endif

/* G_PLAYERSTATENOOPSHORTSEQUENCEWAITTIMERPARAMETER.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerStateNoopShortSequenceWaitTimerParameter __attribute__((aligned(4))) = {
    0,
    23300
};
#endif

/* G_PLAYERSTATENOOPERATIONSTATEKINDWORD.CPP */
#if defined(VERSION_US_REV1)
u32 g_playerStateNoOperationStateKindWord = 0x00020000;
#endif

/* G_PLAYERSTATERUNENDFLAGCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_playerStateRunEndFlagCallbacks[2] = {
    (void *)&g_playerStateNoOperationCallbackWords[0x2F5], (void *)&g_PlayerSetRunEndFlagCallbackAddressDe
};
#endif

/* G_PLAYERSTATENOOPERATIONSTATETARGETPOINTER.CPP */
#if defined(VERSION_US_REV1)
void *g_playerStateNoOperationStateTargetPointer[1] = {
    (void *)&g_secondaryCollisionContext[1],
};
#endif

/* G_PLAYERSTATENOOPERATIONSTATETIMERPARAMETER.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 timer;
    s32 parameter;
} g_playerStateNoOperationStateTimerParameter __attribute__((aligned(4))) = {
    0,
    23301
};
#endif

/* G_HUDDIALOGGROUPRECORD.CPP */
#if defined(VERSION_US_REV1)
struct {
    u32 previousStateReserved;
    s16 dialogGroups[12];
    f32 hudSpriteOffset;
} g_hudDialogGroupRecord __attribute__((aligned(4))) = {
    0x20000,
    { 0, 299, 299, 299, 299, 299, 299, 299, 299, 299, 299, 0 },
    -0.25f
};
typedef char g_hudDialogGroupRecordSizeCheck[
    (sizeof(g_hudDialogGroupRecord) == 32) ? 1 : -1];
#endif
