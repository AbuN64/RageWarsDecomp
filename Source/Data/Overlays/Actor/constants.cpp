#include "types.h"
#include "Ai/Devices/actionai.h"
#include "Data/Action_callbacks/action_setbreakablestate_address.h"
#include "Data/Action_callbacks/breakable_proximity_and_health_callback_addresses.h"
#include "Data/Action_callbacks/actor_motion_callback_labels.h"
#include "Common/listheader.h"
#include "Engine/link.h"
#include "Data/Action_callbacks/action_activate_rom_entry.h"
#include "Ai/Devices/Actionhit/actionhit.h"
#include "Common/aiprofile.h"
#include "Data/Action_callbacks/breakable_hit_callback_addresses.h"
#include "Level/actionhit.h"
#include "Data/Action_callbacks/action_handler_addresses.h"
#include "Common/animationtriggerdefinition.h"
#include "Data/Action_callbacks/damageai_getactivationsound.h"
#include "Ai/Devices/Damageai/damageai.h"
#include "Data/Action_callbacks/damageai_addresses.h"
#include "Ai/Devices/Devicecallback/devicecallback.h"
#include "Data/Action_callbacks/damageai_getdefinitionvalue.h"
#include "Ai/Devices/Movingai/movingai.h"
#include "Ai/Devices/Spawnai/spawnai_spawnai.h"
#include "Data/Action_callbacks/actor_state_callback_labels.h"
#include "Render/movingai.h"
#include "Data/Action_callbacks/device_spawn_and_motion_rom_entries.h"
#include "Data/Action_callbacks/movingai_getdevicehealth_address.h"
#include "Ai/Devices/Playermatrix/playermatrix.h"
#include "Render/playermatrix.h"
#include "Render/triggered_updatetriggeredmotion.h"
#include "Data/Action_callbacks/actor_state_callback_address.h"

/* G_ACTIONAIUPDATETRIGGERFLAGCALLBACK.CPP */
#if defined(VERSION_US_REV1)
void * g_actionaiUpdateTriggerFlagCallback[2] = {
    (void *)&g_defaultActorCollisionInfo, (void *)&Actionai_UpdateTriggerFlag
};
#endif

/* G_ACTIONAIUPDATETRIGGERFLAGANIMATIONFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_actionaiUpdateTriggerFlagAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_actionaiUpdateTriggerFlagAnimationFragmentSizeCheck[
    (sizeof(g_actionaiUpdateTriggerFlagAnimationFragment) == 12) ? 1 : -1];
#endif

/* G_OVERLAYTHREEACTORSTATEENTRYFRAGMENTSETBREAKABLESTATE.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
} g_actorStateEntryFragmentSetBreakableState __attribute__((aligned(4))) = {
    1,
    (void *)&Action_SetBreakableState
};
typedef char g_actorStateEntryFragmentSetBreakableStateSizeCheck[
    (sizeof(g_actorStateEntryFragmentSetBreakableState) == 8) ? 1 : -1];
#endif

/* G_ACTORSTATEANIMATIONFRAGMENTENCODEDWORDS.CPP */
#if defined(VERSION_US_REV1)
void * g_ActorStateAnimationFragmentEncodedWords[3] = {
    (void *)&Action_UpdateBreakableProximity, (void *)&g_defaultActorCollisionInfo, (void *)&Actionai_UpdateHealthFlag
};

struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_breakableProximityAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_breakableProximityAnimationFragmentSizeCheck[
    (sizeof(g_breakableProximityAnimationFragment) == 12) ? 1 : -1];
#endif

/* G_OVERLAYTHREEACTORSTATEENTRYFRAGMENTSETDRAWHANDLERCLEARMOTIONFLAGS.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
    void * update;
} g_actorStateEntryFragmentSetDrawHandlerClearMotionFlags __attribute__((aligned(4))) = {
    2,
    (void *)&Actionai_SetDrawHandler,
    (void *)&Actionai_ClearMotionFlags
};
typedef char g_actorStateEntryFragmentSetDrawHandlerClearMotionFlagsSizeCheck[
    (sizeof(g_actorStateEntryFragmentSetDrawHandlerClearMotionFlags) == 12) ? 1 : -1];
#endif

/* G_DEFAULTCOLLISIONINFONULLPAIR.CPP */
#if defined(VERSION_US_REV1)
void * g_defaultCollisionInfoNullPair[2] = {
    (void *)&g_defaultActorCollisionInfo, 0,
};
#endif

/* G_DEFAULTCOLLISIONINFONULLANIMATIONFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_defaultCollisionInfoNullAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_defaultCollisionInfoNullAnimationFragmentSizeCheck[
    (sizeof(g_defaultCollisionInfoNullAnimationFragment) == 12) ? 1 : -1];
#endif

/* G_DEFAULTCOLLISIONINFONULLENDFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
ActorEndFragment g_defaultCollisionInfoNullEndFragment __attribute__((aligned(4))) = {
    -1
};
typedef char g_defaultCollisionInfoNullEndFragmentSizeCheck[
    (sizeof(g_defaultCollisionInfoNullEndFragment) == 4) ? 1 : -1];
#endif

/* K_BREAKABLEACTIONHANDLERS.CPP */
#if defined(VERSION_US_REV1)
unsigned int k_breakableActionHandlers[42] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    (unsigned int)Actionai_InitBreakableMotion,
    (unsigned int)Action_ActivateBreakableState, 0x00000000, 0x00000000, (unsigned int)Action_RequestStateOn,
    (unsigned int)Actionai_EnableTrigger, (unsigned int)Action_RequestStateOff, (unsigned int)Actionai_DisableTrigger,
    (unsigned int)Link_RequestOwnerTrack,
    (unsigned int)Link_RequestGlobalTrack, (unsigned int)Link_ClearActorFlagMask, 0x00000000,
    (unsigned int)Link_PlayTriggerSoundCallback, (unsigned int)Link_PlayTriggerSound,
    (unsigned int)Link_DispatchTriggerAudio, (unsigned int)Link_SelectTriggerMusic,
    (unsigned int)Link_SetTriggerTrackCallback,
    (unsigned int)Link_SetTriggerTrack, (unsigned int)Link_ClearActorStateBit, 0x00000000,
    (unsigned int)Link_SetActorStateBit, 0x00000000, (unsigned int)Link_SetActorFlagMask, 0x00000000, 0x00000004,
    0x0004CCCC, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000,
};
#endif

/* G_DEFAULTCOLLISIONINFONULLENTRYFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
char g_defaultCollisionInfoNullEntryFragment[8] __attribute__((aligned(4))) = "\000\000\000\000\000 Lh";
#endif

/* G_ACTIONUPDATEBREAKABLEHITCALLBACK.CPP */
#if defined(VERSION_US_REV1)
unsigned int g_actionUpdateBreakableHitCallback[3] = {
    (unsigned int)Action_UpdateBreakableHit, (unsigned int)&g_secondaryCollisionContext[6], 0x00005212,
};
#endif

/* G_ACTIONUPDATEBREAKABLEHITANIMATIONFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_actionUpdateBreakableHitAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_actionUpdateBreakableHitAnimationFragmentSizeCheck[
    (sizeof(g_actionUpdateBreakableHitAnimationFragment) == 12) ? 1 : -1];
#endif

/* G_OVERLAYTHREEACTORSTATEENTRYFRAGMENTDEACTIVATEBREAKABLERESOLVEBREAKABLEHIT.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
    void * update;
} g_actorStateEntryFragmentDeactivateBreakableResolveBreakableHit __attribute__((aligned(4))) = {
    1,
    (void *)&Action_DeactivateBreakable,
    (void *)&Action_ResolveBreakableHit
};
typedef char g_actorStateEntryFragmentDeactivateBreakableResolveBreakableHitSizeCheck[
    (sizeof(g_actorStateEntryFragmentDeactivateBreakableResolveBreakableHit) == 12) ? 1 : -1];
#endif

/* G_SECONDARYCOLLISIONCONTEXTANIMIDPAIR.CPP */
#if defined(VERSION_US_REV1)
unsigned int g_secondaryCollisionContextAnimIdPair[2] = {
    (unsigned int)&g_secondaryCollisionContext[6], 0x0000521C,
};

struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_unitScaleZeroThresholdRecord __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_unitScaleZeroThresholdRecordSizeCheck[(sizeof(g_unitScaleZeroThresholdRecord) == 12) ? 1 : -1];
#endif

/* G_SECONDARYCOLLISIONCONTEXTANIMIDENDFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
ActorEndFragment g_secondaryCollisionContextAnimIdEndFragment __attribute__((aligned(4))) = {
    -1
};
typedef char g_secondaryCollisionContextAnimIdEndFragmentSizeCheck[
    (sizeof(g_secondaryCollisionContextAnimIdEndFragment) == 4) ? 1 : -1];
#endif

/* K_TRIGGERACTORACTIONHANDLERS.CPP */
#if defined(VERSION_US_REV1)
void * k_triggerActorActionHandlers[23] = {
    0, 0, 0, 0, 0, 0, 0, (void *)&Action_SetEnterHandler,
    (void *)&Action_ToggleActorState, 0, 0, (void *)&Action_RequestInactiveState, (void *)&Action_EnableTriggerActor,
    (void *)&Action_RequestActiveState, (void *)&Action_DisableTriggerActor, 0,
    0, 0, 0, 0, 0, 0, 0
};
#endif

/* G_DAMAGEAIGETACTIVATIONSOUNDCALLBACK.CPP */
#if defined(VERSION_US_REV1)
void * g_damageAIGetActivationSoundCallback[2] = {
    (void *)&g_defaultActorCollisionInfo, (void *)&DamageAI_GetActivationSound
};
#endif

/* G_DAMAGEAIGETACTIVATIONSOUNDANIMATIONFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_damageAIGetActivationSoundAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_damageAIGetActivationSoundAnimationFragmentSizeCheck[
    (sizeof(g_damageAIGetActivationSoundAnimationFragment) == 12) ? 1 : -1];
#endif

/* G_DAMAGEAIGETACTIVATIONSOUNDENTRYFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
} g_damageAIGetActivationSoundEntryFragment __attribute__((aligned(4))) = {
    1
};
typedef char g_damageAIGetActivationSoundEntryFragmentSizeCheck[
    (sizeof(g_damageAIGetActivationSoundEntryFragment) == 4) ? 1 : -1];
#endif

/* G_DAMAGEAIACTIVATEACTORCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_damageAIActivateActorCallbacks[4] = {
    (void *)&DamageAI_ActivateActor, (void *)&DamageAI_ClearCollisionFlagsOnHit, (void *)&g_defaultActorCollisionInfo,
    (void *)&DamageAI_GetActivationMode
};

struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_damageAIActivateActorAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_damageAIActivateActorAnimationFragmentSizeCheck[
    (sizeof(g_damageAIActivateActorAnimationFragment) == 12) ? 1 : -1];
#endif

/* G_DAMAGEAIACTIVATEACTORENTRYFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
} g_damageAIActivateActorEntryFragment __attribute__((aligned(4))) = {
    2
};
typedef char g_damageAIActivateActorEntryFragmentSizeCheck[
    (sizeof(g_damageAIActivateActorEntryFragment) == 4) ? 1 : -1];
#endif

/* G_DEVICERESPONDTOACTIVATIONCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_deviceRespondToActivationCallbacks[4] = {
    (void *)&Device_RespondToActivation, (void *)&Device_ClearCollisionFlagsOnHit, (void *)&g_defaultActorCollisionInfo,
    (void *)&DamageAI_GetDefinitionValue
};

struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_deviceRespondToActivationAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_deviceRespondToActivationAnimationFragmentSizeCheck[
    (sizeof(g_deviceRespondToActivationAnimationFragment) == 12) ? 1 : -1];
#endif

/* G_DEVICERESPONDTOACTIVATIONENDFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
ActorEndFragment g_deviceRespondToActivationEndFragment __attribute__((aligned(4))) = {
    -1
};
typedef char g_deviceRespondToActivationEndFragmentSizeCheck[
    (sizeof(g_deviceRespondToActivationEndFragment) == 4) ? 1 : -1];
#endif

/* G_MOVINGAICHOOSETRIGGERDELAYCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
struct {
    unsigned int w0[27];
    unsigned short h1[30];
    unsigned int w2[8];
} g_damageActorStateDispatchRecord = {
    {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        (unsigned int)DamageAI_InitializeDispatch, (unsigned int)DamageAI_RequestCurrentActorState, 0x00000000,
        0x00000000,
        (unsigned int)Device_RequestAndSetActiveState, (unsigned int)Device_EnableTriggerActor,
        (unsigned int)Link_ClearActorStateBit, 0x00000000,
        (unsigned int)Link_SetActorStateBit, 0x00000000, (unsigned int)Link_ClearActorFlagMask, 0x00000000,
        (unsigned int)Link_SetActorFlagMask, 0x00000000, (unsigned int)Link_CaptureActorTransform, 0x00000000,
        (unsigned int)Link_DeactivateActorState, 0x00000000, 0x420A3D70, 0x3FDD2F1C,
    },
    {
        0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x06A5, 0x03E8, 0x06A6, 0x01F4, 0x06A7, 0x000A, 0xFFFF, 0x0000,
        0x06A6, 0x01F4, 0x06A7, 0x000A, 0xFFFF, 0x0000, 0x06B8, 0x03E8, 0x06BA, 0x01F4, 0x06BB, 0x000A,
        0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000,
    },
    {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    },
};

void * g_movingAIChooseTriggerDelayCallbacks[3] = {
    0, (void *)&MovingAI_ChooseTriggerDelay, (void *)&MovingAI_UpdateTriggerDelay
};
#endif

/* G_RESERVEDANIMATIONIDRECORD.CPP */
#if defined(VERSION_US_REV1)
struct {
    void * reserved;
    s32 animation;
} g_reservedAnimationIdRecord __attribute__((aligned(4))) = {
    0,
    21200
};
typedef char g_reservedAnimationIdRecordSizeCheck[(sizeof(g_reservedAnimationIdRecord) == 8) ? 1 : -1];
#endif

/* G_RESERVEDANIMATIONIDANIMATIONFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_reservedAnimationIdAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x400
};
typedef char g_reservedAnimationIdAnimationFragmentSizeCheck[
    (sizeof(g_reservedAnimationIdAnimationFragment) == 12) ? 1 : -1];
#endif

/* G_RESERVEDANIMATIONIDENTRYFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
} g_reservedAnimationIdEntryFragment __attribute__((aligned(4))) = {
    1
};
typedef char g_reservedAnimationIdEntryFragmentSizeCheck[
    (sizeof(g_reservedAnimationIdEntryFragment) == 4) ? 1 : -1];
#endif

/* G_SPAWNAIDISPATCHSPAWNCHOICECALLBACKS.CPP */
#if defined(VERSION_US_REV1)
struct {
    void * enter;
    void * update;
    void * reserved;
    s32 animation;
} g_spawnAIDispatchSpawnChoiceCallbacks __attribute__((aligned(4))) = {
    (void *)&SpawnAI_DispatchSpawnChoice,
    (void *)&MovingAI_RequestInactiveOnEvent,
    0,
    21210
};
typedef char g_spawnAIDispatchSpawnChoiceCallbacksSizeCheck[
    (sizeof(g_spawnAIDispatchSpawnChoiceCallbacks) == 16) ? 1 : -1];

struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_spawnAIDispatchSpawnChoiceAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x400
};
typedef char g_spawnAIDispatchSpawnChoiceAnimationFragmentSizeCheck[
    (sizeof(g_spawnAIDispatchSpawnChoiceAnimationFragment) == 12) ? 1 : -1];
#endif

/* G_SPAWNAIDISPATCHSPAWNCHOICEENDFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
ActorEndFragment g_spawnAIDispatchSpawnChoiceEndFragment __attribute__((aligned(4))) = {
    -1
};
typedef char g_spawnAIDispatchSpawnChoiceEndFragmentSizeCheck[
    (sizeof(g_spawnAIDispatchSpawnChoiceEndFragment) == 4) ? 1 : -1];
#endif

/* G_ACTORSTATEENTRYFRAGMENTENCODEDWORDS.CPP */
#if defined(VERSION_US_REV1)
unsigned int g_ActorStateEntryFragmentEncodedWords[24] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    (unsigned int)SpawnAI_InitializeActorDispatch,
    (unsigned int)SpawnAI_InitializeActionDelay, 0x00000000, 0x00000000, (unsigned int)MovingAI_SetActorStateActive,
    (unsigned int)MovingAI_EnableTriggerActor, (unsigned int)MovingAI_ClearActorStateActive,
    (unsigned int)MovingAI_DisableTriggerActor, 0x41D70A3E,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

char g_actorStateEntryFragmentGdBytes[12] __attribute__((aligned(4))) = "\000\000\000\000\000\000\000\000\000 gd";
#endif

/* G_MOVINGAIGETDEVICEHEALTHCALLBACK.CPP */
#if defined(VERSION_US_REV1)
void * g_movingAIGetDeviceHealthCallback[2] = {
    (void *)&g_defaultActorCollisionInfo, (void *)&MovingAI_GetDeviceHealth
};
#endif

/* G_MOVINGAIGETDEVICEHEALTHANIMATIONFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_movingAIGetDeviceHealthAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x0
};
typedef char g_movingAIGetDeviceHealthAnimationFragmentSizeCheck[
    (sizeof(g_movingAIGetDeviceHealthAnimationFragment) == 12) ? 1 : -1];
#endif

/* G_MOVINGAIGETDEVICEHEALTHENDFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
ActorEndFragment g_movingAIGetDeviceHealthEndFragment __attribute__((aligned(4))) = {
    -1
};
typedef char g_movingAIGetDeviceHealthEndFragmentSizeCheck[
    (sizeof(g_movingAIGetDeviceHealthEndFragment) == 4) ? 1 : -1];
#endif

/* G_MOVINGAIANDPLAYERMATRIXCALLBACKS.CPP */
#if defined(VERSION_US_REV1)
void * g_movingAIInitializeMotionDispatchCallbacks[35] = {
    0, 0, 0, 0, 0, 0, 0, (void *)&MovingAI_InitializeMotionDispatch,
    (void *)&MovingAI_InitializeDeviceHealth, 0, 0, (void *)&Triggered_StartTriggerAnimation, 0,
    (void *)&Triggered_ClearCollisionAndActivate, (void *)&Triggered_EnableTriggeredActorState,
    (void *)&Triggered_DeactivateForSequence,
    (void *)&Triggered_DisableTriggeredActorState, (void *)&Link_RequestOwnerTrack, (void *)&Link_RequestGlobalTrack,
    (void *)&Link_PlayTriggerSoundCallback, (void *)&Link_PlayTriggerSound, (void *)&Link_DispatchTriggerAudio,
    (void *)&Link_SelectTriggerMusic, (void *)&Link_SetTriggerTrackCallback,
    (void *)&Link_SetTriggerTrack, (void *)&Triggered_SetPairedDefinitionBytes, 0, 0, 0, 0, 0, 0,
    0, 0, 0
};

void * g_playerMatrixClearUnsupportedOpenFlagCallbacks[3] = {
    0, (void *)&PlayerMatrix_ClearUnsupportedOpenFlag, (void *)&PlayerMatrix_UpdateOpeningDelay
};
#endif

/* G_TRIGGEREDSELECTMOTIONSOUNDCALLBACK.CPP */
#if defined(VERSION_US_REV1)
unsigned int g_triggeredSelectMotionSoundCallback[2] = {
    0x801040B0, (unsigned int)Triggered_SelectMotionSound,
};
#endif

/* G_TRIGGEREDSELECTMOTIONSOUNDANIMATIONFRAGMENT.CPP */
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    s32 threshold;
    u32 flags;
} g_triggeredSelectMotionSoundAnimationFragment __attribute__((aligned(4))) = {
    1.0f,
    0,
    0x400
};
typedef char g_triggeredSelectMotionSoundAnimationFragmentSizeCheck[
    (sizeof(g_triggeredSelectMotionSoundAnimationFragment) == 12) ? 1 : -1];
#endif
