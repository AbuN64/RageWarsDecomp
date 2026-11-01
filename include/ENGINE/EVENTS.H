#ifndef ENGINE_EVENTS_H
#define ENGINE_EVENTS_H
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"

struct Target;

struct Target {
    u8 kind;
    char pad1[3];
    u16 type;
};

struct Vec4s;

typedef struct Vec4s Vec4s;

extern float k_clipEventFlagTwentyScale;

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

struct PlayerEyePositionView;

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

extern float k_clipEventFlagFortyScale;

typedef struct NodeEventsStartCameraFadeAtPoint NodeEventsStartCameraFadeAtPoint;

extern float k_weaponHitHeightScale;

typedef struct Target Target;

extern s32 SoundElement_PlayPositionedSoundWithScale(s32 trackId, CVector3 soundPosition, s32 spatialMode, s32 ownerId,
                         f32 playbackScale);

extern void Weapon_SpawnTargetPlayerFireEffect(void *aiTarget, s32 unused1, s32 effect);

struct Field_s32_2E0 {
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
    SharedPlayer *player;
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
    u8 m_u8_Value4;
    u8 m_u8_Value5;
    u8 f;
    u8 m_u8_Value7;
};

extern void Events_RequestActorPosition(s32 source, void *target, s32 kind, CVector3 position, struct IntPair positionParams);

extern void Events_ConsumeEventArgument(int unused0, int unused1, int unused2, int eventArgument);

extern void Events_PreserveEventArgument(int unused0, int unused1, int unused2, int eventArgument);

extern void Events_StartCameraFadeAtPoint(s32 unused0, s32 unused1, s32 unused2, Triple testPoint, CEventValueFormat7a fadeParams);
#endif
