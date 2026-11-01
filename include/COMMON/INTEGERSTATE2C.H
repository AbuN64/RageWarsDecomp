#ifndef COMMON_INTEGERSTATE2C_H
#define COMMON_INTEGERSTATE2C_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
struct CountedEffectActionConfig;
struct CountedEffectActionConfig {
    char pad0[0x8];
    s32 firstWaitBase;
    char pad8[0xC - 0x8 - sizeof(s32)];
    s32 firstWaitSpread;
    char padC[0x24 - 0xC - sizeof(s32)];
    s32 secondWaitBase;
    char pad24[0x28 - 0x24 - sizeof(s32)];
    s32 secondWaitSpread;
};


extern float g_actionBurstRestartRandomRange;

extern float g_actionBurstRandomRange;



extern float g_difficultyAimPositiveJitter;

struct NavigationRawByteStorage;
typedef struct NavigationRawByteStorage NavigationRawByteStorage;



extern float g_difficultyEngagementOtherMultiplier;

extern float g_actionSettingsRandomRange;

struct Shared_WeaponSlot;
typedef struct Shared_WeaponSlot Shared_WeaponSlot;




extern float g_aiCharacterSettingEasyScale;





extern float g_actionBurstAlternateDelayRandomRange;


extern float g_actionBurstPrimaryDelayRandomRange;


extern float g_aiCharacterSettingHardScale;

extern float g_difficultyAimNegativeJitter;

extern float g_aiCharacterSettingBaseScale;

extern float g_aiAttackRangeEasyScale;

struct CountedEffectActionState;
struct CountedEffectActionState {
    char pad0[0x64];
    char * targetView;
    char pad64[0x23C - 0x64 - sizeof(char*)];
    s32 effectCountShortfallFlag;
    char pad23C[0x240 - 0x23C - sizeof(s32)];
    s32 actionFlagFrames;
    char pad240[0x2E4 - 0x240 - sizeof(s32)];
    s32 phaseCountdown;
    char pad2E4[0x2E8 - 0x2E4 - sizeof(s32)];
    s32 waitTimer;
};

extern float g_aiAggressionEasyScale;


extern float g_meterActionEffectDistanceLimit;

extern float g_actionPulseChanceRandomRange;

extern float g_aiAttackRangeHardScale;



extern float g_difficultyEngagementFirstMultiplier;



extern float g_actionPulseChanceBase;


struct Shared_Arg0;
typedef struct Shared_Arg0 Shared_Arg0;

struct Shared_Node;
struct Shared_Node {
    s32 nodeKey;
    char pad4[0xC];
    struct Shared_Node * next;
    char pad14[0x20];
    void * linkedActor;
};

struct Shared_Arg0;
struct Shared_Node;
struct Shared_Arg0 {
    s32 * pointStorage;
    char pad4[0x20];
    struct Shared_Node * searchNodes;
};




extern float g_alternatingActionWaitRandomScale;


struct CountedEffectActionState;
typedef struct CountedEffectActionState CountedEffectActionState;

extern float g_meterActionChanceBase;


extern float g_meterActionChanceRandomRange;

extern float g_timedActionWaitRandomScale;

extern float g_aiAggressionBaseScale;

struct Shared_Node;
typedef struct Shared_Node Shared_Node;

struct NavigationRawByteStorage;
struct NavigationRawByteStorage {
    char bytes[1];
};


extern float g_actionBurstAlternateChance;

struct Shared_WeaponSlot;
struct ActorModelIndexView;
struct Shared_WeaponSlot {
    char pad0[0x8];
    char positionBytes;
    char pad9[0xF];
    struct ActorModelIndexView * model;
    char pad1C[0xC8];
    u16 objectId;
    char padE6[0x2];
};

struct Shared_WeaponSlot;



struct AiController;
struct AiConfig;
extern void Portal_UpdateAlternatingActionBursts(struct AiController *controller, struct AiConfig *aiConfig);

extern void Portal_InitializeRandomActionSettings(void *object, void *settings);


extern float g_difficultyEngagementScale;

struct Controls;
typedef struct Controls Controls;

extern float g_portalEngagementScale;


extern float g_aiAggressionHardScale;


struct CountedEffectActionConfig;
typedef struct CountedEffectActionConfig CountedEffectActionConfig;


extern float g_actionBurstAlternateAngleLimit;


extern float g_aiAttackRangeBaseScale;




extern void Portal_UpdateMeterGatedActionBurst(void *object, void *settings);



extern void Portal_UpdateCountedEffectAction(CountedEffectActionState *controller, CountedEffectActionConfig *config);

extern float g_alternatingActionTargetRange;


extern void Portal_UpdateRandomActionPulse(void *controller, void *settings);



extern void Portal_UpdateTimedActionBurst(void *controller, void *settings);


extern void Portal_UpdateHeldActionBurst(void *controller, void *settings);

extern float g_actionBurstPrimaryAngleLimit;


#include "COMMON/SHAREDCALLBACK5.H"
typedef struct AiCharacterDefinition {
    u8 pad0[0x28];
    f32 aggression; /* 0x28 */
    f32 engagement; /* 0x2C */
    f32 attackRange; /* 0x30 */
    f32 characterSetting; /* 0x34 */
    u8 pad38[0x14];
    u32 loadout[4]; /* 0x4C: word-sized item IDs; low half of [1] is the starting weapon ID. */
} AiCharacterDefinition;
typedef struct AiConfig {
    s32 primaryDelayBase; /* 0x0 */
    s32 primaryDelaySpread; /* 0x4 */
    s32 primaryDurationBase; /* 0x8 */
    s32 primaryDurationSpread; /* 0xC */
    s32 alternateCountdownBase; /* 0x10 */
    s32 alternateCountdownSpread; /* 0x14 */
    s32 pulseChancePercent; /* 0x18 */
    s32 alternateDelayBase; /* 0x1C */
    s32 alternateDelaySpread; /* 0x20 */
    s32 alternateDurationBase; /* 0x24 */
    s32 alternateDurationSpread; /* 0x28 */
    s32 meterCooldownBase; /* 0x2C */
    s32 meterCooldownSpread; /* 0x30 */
    s32 meterThreshold; /* 0x34 */
} AiConfig;
#endif
