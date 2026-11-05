#ifndef ENGINE_EVENTS_H
#define ENGINE_EVENTS_H
struct Clip;
struct ParamsEventsStartActorEmitter;
struct EventCounterParameters;
struct SoundActor;
struct SoundSource;
#include "Common/small_records.h"
extern float k_eventEmitterAngleConstants;
#include "Engine/Instance/gobjinst.h"
#include "Common/globals.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"



struct Extra {
    s32 id;
    f32 scale;
};
typedef struct Extra Extra;

struct Shield {
    char pad0[0x66];
    char effectKind; /* 0x66: impact response variant (4 or 5) */
    u8 reserved67;
    f32 factor;
};
typedef struct Shield Shield;


struct Shield;
struct ActorEmitterSource;
struct CameraEventsSpawnAttachedEffect;
struct ClipEventTargetView;
struct ContextEventsStartActorEmitter;
struct EffectSpawnSourceView;
struct Filter;
struct LevelActor;
struct SharedPlayer;
struct Shared_ReactionActor;
struct Target;

struct Target {
    u8 kind;
    char pad1[3];
    u16 type;
};

struct Vec4s;

typedef struct Vec4s Vec4s;

extern float k_clipEventLowFlagScale;

struct ResourceManagerState;

struct Triple;

extern float k_damageSpecialScale;

struct ActorEventsComputeDamageScale;

struct PlayerDamageFlagsView;

struct ActorEventsComputeDamageScale {
    char pad0[8];
    CVector3 position;
    char pad14[0x70 - 0x14];
    f32 height;
    char pad74[0x100 - 0x74];
    s32 flags;
    char pad104[0x1D8 - 0x104];
    struct PlayerDamageFlagsView *player;
};

struct Body;

struct Character;

struct Controller;

struct Controls;

struct Ctrl;

struct Held;

struct Mode;

struct Model;

struct Mount;

struct Profile;

struct Record;

struct Settings;

struct Shared_Body;

struct Shared_Hud;

struct Shared_Model;

struct Shared_Profile;

struct Shared_StateInfo;

struct Shared_Voice;

struct StateInfo;

struct TeamInfo;

struct View;

struct GameplayCamera;

struct ActorEventsSpawnRiderImpactEffect;

typedef void ( *EventsDispatchCallbackCallback)(void *, void *, signed int, CVector3, struct ResourceManagerState);

struct EventCallbackEntry;

extern float k_clipEventDefaultScale;

struct ClipEventTargetView;

typedef struct ClipEventTargetView ClipEventTargetView;

struct s_CEventValueFormat7a;

typedef struct s_CEventValueFormat7a CEventValueFormat7a;

extern float k_damageDefaultScale;

typedef struct ActorEventsSpawnRiderImpactEffect ActorEventsSpawnRiderImpactEffect;

struct Carrier;

typedef struct EventCallbackEntry EventCallbackEntry;

typedef struct Carrier Carrier;

typedef struct ActorEventsComputeDamageScale ActorEventsComputeDamageScale;

extern float k_playerEventClipHeightAndAngle;

struct NodeEventsStartCameraFadeAtPoint;

struct NodeEventsStartCameraFadeAtPoint {
    s32 unused;
    struct NodeEventsStartCameraFadeAtPoint *next;
};

extern float k_damageEuropeanFalloffScale;

extern float k_clipEventHighFlagScale;

typedef struct NodeEventsStartCameraFadeAtPoint NodeEventsStartCameraFadeAtPoint;

extern float k_weaponHitHeightScale;

typedef struct Target Target;

extern s32 SoundElement_PlayPositionedSoundWithScale(s32 trackId, CVector3 soundPosition, s32 spatialMode, s32 ownerId,
                         f32 playbackScale);

extern void Weapon_SpawnTargetPlayerFireEffect(void *aiTarget, s32 behaviorFlags, s32 effect);

struct ActorEventBitWord {
    char pad[0x2E0];
    s32 value;
};

struct TripleEventsFireWithinHeightRange {
    s32 x;
    f32 y;
    s32 z;
};

struct CameraEventsSpawnAttachedEffect {
    char pad0[0xE4];
    CVector3 position;
    CVector3 offset;
};

struct EffectSpawnSourceView {
    unsigned char active;
    char pad1[7];
    CVector3 position;
    s32 id;
    char pad18[4];
    CVector3 velocity;
};

struct Spawn {
    CVector3 position;
    s32 kind;
    f32 size;
};

struct EffectSpawnModeView {
    char pad0[0x1];
    s8 team;
};

/* Damage packet passed by value to the area-hit callbacks. */
typedef struct Shared_DamageParameters {
    u16 radius;
    u16 damage;
    union {
        s32 control;
        struct { s8 impulse; u8 reserved[3]; };
    };
} Shared_DamageParameters;

struct EventCallbackEntry {
    EventsDispatchCallbackCallback callback;
    s32 unused;
};

struct ClipEventTargetView {
    u8 type;
    u8 pad1[0x17];
    s32 *kind;
    u8 pad1C[0xB4];
    s32 value;
};

extern void Events_DispatchCallback(void *actor, void *source, s32 event, CVector3 position, struct ResourceManagerState state);

extern void Events_ForwardCallback(void *sourceActor, void *targetActor, s32 eventKind, CVector3 eventPosition, ResourceManagerState eventParams);

struct ActorEventsSpawnRiderImpactEffect {
    char pad0[0x1D8];
    struct SharedPlayer *player;
};

struct Carrier {
    struct ActorEventsComputeDamageScale *owner;
    char pad4[0x10];
    s32 slot;
    Shield shield;
};

struct Vec4s {
    s16 x;
    s16 y;
    s16 z;
    s16 w;
};

struct s_CEventValueFormat7a {
    u8 a;
    u8 b;
    u8 c;
    u8 m_FadeStep;
    u8 m_FadeRed;
    u8 f;
    u8 m_FadeBlue;
};

extern void Events_RequestActorPosition(s32 source, void *target, s32 kind, CVector3 position, struct IntPair positionParams);

extern void Events_ConsumeEventArgument(int source, int target, int kind, int eventArgument);

extern void Events_PreserveEventArgument(int source, int target, int kind, int eventArgument);
extern void Events_RunSecondNodeOperation(s32 actor, s32 unusedTarget, s32 unusedKind, CVector3 position);
extern void Events_SetActorEventBit(void *sourceActor, s32 targetActor, s32 eventKind, s32 eventPositionBase, s32 eventPositionY, s32 eventPositionZ, s32 eventParams);
extern void Events_SpawnActorEffect(void *actor, int target, int kind, struct Triple input, int event);

extern void Events_StartCameraFadeAtPoint(s32 source, s32 target, s32 kind, Triple testPoint, CEventValueFormat7a fadeParams);
extern void Events_StopClipEvent(s32 source, s32 target, s32 kind, s32 eventPositionWord, s32 positionYWord, s32 positionZWord, s32 eventParams);
extern void Events_SpawnActorEffect(void *actor, int target, int kind, Triple input, int event);
extern void Events_ApplyFlag100RadialDamage(s32 source, s32 target, s32 kind, Triple position, struct IntPair params);
extern void Events_ApplyFlag100RadialKnockback(s32 source, s32 target, s32 kind, Triple position, struct IntPair params);
extern void Events_ApplyFlag200RadialDamage(s32 source, s32 target, s32 kind, Triple position, struct IntPair params);
extern void Events_ApplyFlag200RadialKnockback(s32 source, s32 target, s32 kind, Triple position, struct IntPair params);
extern void Events_ApplyFlag400RadialDamage(s32 source, s32 target, s32 kind, Triple position, struct IntPair params);
extern void Events_ApplyDirectDamage(unsigned char *source, s32 target, s32 kind, Triple position, struct IntPair params);
extern void Events_ApplyRadialDamage(s32 source, s32 target, s32 kind, Triple position, struct IntPair params);
extern void Events_ApplyRadialDamageWithKnockback(s32 source, s32 target, s32 kind, Triple position, struct IntPair params);
extern void Events_SetActorLoopingSound(void *sourceActor, struct LevelActor *object, s32 third, struct IntPair pair, s32 fifth, s32 sixth);
extern void Events_StopActorLoopingSound(void *sourceActor, struct LevelActor *object, s32 third, struct IntPair pair);
extern void Events_DeactivateActor(struct LevelActor *object, s32 second, s32 third, struct IntPair pair);
extern void Events_ApplyFlag400RadialKnockback(s32 source, s32 target, s32 kind, Triple position, struct IntPair params);
extern void Events_StartActorEmitter(struct ActorEmitterSource *sourceActor, struct ContextEventsStartActorEmitter *targetContext, s32 eventKind, Triple emitterPosition, struct ParamsEventsStartActorEmitter emitterParams);
extern void Events_SpawnFilteredActorEffect(void *actor, struct Filter *filter, s32 unusedEventKind, Triple position, struct IntPair effectParams);
extern void Events_StartEnabledCameraEmitter(s32 sourceActor, s32 targetActor, s32 eventKind, Triple t, Vec4s v);
extern void Events_StartDisabledCameraEmitter(s32 sourceActor, s32 targetActor, s32 eventKind, Triple t, Vec4s v);
extern void Events_PostGameplayMessage(void *owner, struct LevelActor *actor, s32 event, Triple position, ResourceManagerState params);
extern void Events_SpawnAttachedEffect(struct EffectSpawnSourceView *source, void *hostObject, s32 eventKind, Spawn spawn);
extern s32 Events_SpawnPositionedEffect(s32 sourceActor, struct LevelActor *targetActor, s32 eventKind, Triple eventPosition, Extra effectParams);
extern void Events_PlayClipEvent(s32 unusedSource, struct ClipEventTargetView *targetActor, s32 unusedEventKind, CVector3 soundPosition, struct Clip clipParams);
extern void Events_RunActorNodeOperation(s32 actor, s32 unusedTarget, s32 unusedKind, CVector3 position);
extern void Events_FireWithinHeightRange(struct LevelActor *sourceActor, s32 target, s32 kind, struct TripleEventsFireWithinHeightRange eventPosition, struct IntPair params);
extern void Events_PlayTeamEffect(struct SoundActor *actor, struct SoundSource *source, s32 eventKind, CVector3 position, struct EventCounterParameters params);

extern f32 Events_GetActorSizeScale(u8 *other);
extern void Events_ApplyDamageEvent(struct Shared_ReactionActor *source, struct Shared_ReactionActor *target, s32 kind, CVector3 position, Shared_DamageParameters params, s32 falloff, s32 knockback, s32 flags);
extern void Events_UpdateNodeAtPosition(void *actor, CVector3 input, s32 enableNodeFlag);
extern char g_actorParticleEffectSystem[];
extern const f32 k_damageEventScaleConstants[16];
extern f32 k_damageRadiusScale;
extern f32 k_eventEmitterAndClipScaleConstants;
extern f32 k_positionedSoundAlternateGain;
extern f32 k_positionedSoundDefaultGain;
extern s32 g_damageShieldSelection;
extern struct Shield g_damageFallbackShield;
struct CCollisionResults;
extern struct CCollisionResults *g_collisionCurrentActor;
extern f32 k_playerEventClipScale[2];
struct EventMaskActorView;
extern void Events_PlayTeamClip(struct EventMaskActorView *, struct EventMaskActorView *, s32, CVector3, struct EventCounterParameters);
#endif
