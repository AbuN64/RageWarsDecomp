#ifndef COMMON_SHAREDPLAYER_H
#define COMMON_SHAREDPLAYER_H
#include "TYPES.H"
struct SharedPlayer;
typedef struct SharedPlayer SharedPlayer;
struct Box;
typedef struct Box Box;

#include "COMMON/VECTOR3.H"

struct Box;
struct Box {
    CVector3 min;
    CVector3 max;
};

struct NavigationNodeOwnerView;
typedef struct NavigationNodeOwnerView NavigationNodeOwnerView;

struct Shared_Input;
typedef struct Shared_Input Shared_Input;

struct MemoryUsageStats;
struct MemoryUsageStats {
    int value;
};

struct Triple;
struct Triple {
    s32 x;
    s32 y;
    s32 z;
};

struct Triple;
typedef struct Triple Triple;

struct Settings;
struct Settings {
    char pad0[0x78];
    s32 flag78;
    s32 pad7C;
    s32 flag80;
};

struct Held;
struct Held {
    u8 type;
    char pad1[0x100 - 0x1];
    s32 flags;
    char pad104[0x122C - 0x104];
    s32 options;
};

struct Model;
struct Model {
    s32 kind; /* 0x00: definition class */
    char pad4[0x10];
    u32 flags; /* +0x14: Player_UpdateSwimmingState */
    char pad18[0x34];
    s32 slots[8];
    char pad6C[0xF4 - 0x6C];
    f32 height; /* 0xF4: weapon height source */
};

struct Shared_Quad;
struct Shared_Quad {
    union { s32 w[4]; f32 f[4]; }; /* Integer transport or quaternion coefficients. */
};

/* A mount's embedded animation record and current animation selector. */
struct Mount {
    char pad0[0x170];
    char animation[52];
    s8 animationId;
};

struct Rider;
struct Rider {
    char pad0[0x37];
    s8 direction;
    char pad38[0x1C];
    char frame[16];
    f32 throttle;
    char pad68[0x38];
    CVector3 base;
    char padAC[0x7C];
    f32 change;
};

struct Shared_Effect;
typedef struct Shared_Effect Shared_Effect;

struct Shared_Slot;
typedef struct Shared_Slot Shared_Slot;

struct Matrix;
typedef struct Matrix Matrix;

struct Profile;
struct Profile {
    union {
        struct {
    u8 name[8];
    s32 time;
    s8 owner;
    s8 player;
    s8 fresh; /* +0xE: cleared once the profile has been shown */
    u8 slot;
    char pad10[4];
    u8 bonus2;
    u8 bonus0;
    u8 bonus1;
    u8 count;
    u8 levelProgress[13]; /* +0x18: completion count for levels 0-10 and bonuses 17-18. */
    u8 rank;
    u8 plays[36]; /* +0x26: per-character match count */
    u8 achievementFlags[0x54 - 0x4A]; /* +0x4A: one bit per achievement */
    u8 kindFlags[0x6C - 0x54]; /* +0x54: one bit per character kind finished with */
    char pad6C[0x79 - 0x6C];
    u8 unlockFlags[4]; /* +0x79: Player_HasProfileUnlockFlag / Player_SetAchievementFlag2F */
    u8 groupFlags; /* +0x7D: bits 0-2 for the level-count milestones */
    u8 levelFlags[4][5]; /* +0x7E: one bit per level finished, per game mode 1-4 (Achieve_MarkLevelPlayed) */
    char pad92[0x94 - 0x92];
    s32 times[(0x124 - 0x94) / 4]; /* +0x94: best time per level */
    u8 trackFlags; /* +0x124: Achieve_AwardMilestoneCompletion */
    u8 slotLevels[20][5]; /* +0x125: one bit per level, per save slot */
    u8 setting[5];
    char pad18E[0x190 - 0x18E];
        };
        struct { char pad0[0x6C]; s32 wins, kills, deaths; } statistics;
    };
};
typedef struct Profile Profile;

struct Shared_Emitter;
typedef struct Shared_Emitter Shared_Emitter;

struct Matrix;
struct Matrix {
    f32 m[16];
};

struct Controls;
struct Controls {
    char pad0[0x80];
    s8 mode;
    char pad81[0x94 - 0x81];
    u8 team;
    u8 active;
};

struct Shared_Quad;
typedef struct Shared_Quad Shared_Quad;

struct Shared_Emitter;
struct Shared_Model;
struct Shared_Emitter {
    char pad0[0x8];
    CVector3 pos;
    struct Shared_Model * model;
    char pad18[0x28];
    f32 reservedFloat;
    char pad44[0x18];
    Shared_Quad rotation;
    f32 yaw;
};

struct Shared_Effect;
struct Shared_Effect {
    char pad0[0xB4];
    s32 state;
};

struct Record;
struct Record {
    char pad0[0x80];
    s8 characterId; /* Player_PlacePlayerForRound passes it to Player_GetLevelProgress_MatchGetresulttext */
    char pad81[0x8F - 0x81];
    u8 fragTagEnabled;
    char pad90[0x92 - 0x90];
    u8 team;
    u8 difficulty;
    u8 display;
};

struct View;
typedef struct View View;
struct View {
    char pad0[0x58];
    u16 *key; /* 0x58 */
    f32 blendOffset; /* 0x5C */
    char pad60[0x128 - 0x60];
    CVector3 position;
    char pad134[0x29C - 0x134];
    f32 viewport[4]; /* 0x29C: width, height, x, y */
    char pad2AC[0x340 - 0x2AC];
    CVector3 normal;
    f32 distance;
    char pad350[0x518 - 0x350];
    s32 lastKey; /* 0x518 */
    f32 blendTime;
    u8 color[4];
    u8 secondaryColor[4];
    f32 blendA;
    f32 previousA;
    f32 blendB;
    f32 previousB;
    char pad538[4];
    u32 blendN;
    u32 previousN;
    char pad544[0x554 - 0x544];
    char menu[16]; /* 0x554 */
    s32 shieldActive;
};

struct Shared_Body;
struct Shared_Body {
    char pad0[0xC];
    s16 kind;
    char padE[0xE6];
    f32 ceiling;
};

struct Shared_Input;
struct Shared_Shadow;
struct Shared_Input {
    s32 word0;
    s32 word4;
    s32 word8;
    s32 wordC;
    struct Shared_Shadow * shadow;
    s32 word14;
    s32 word18;
    s32 word1C;
    s32 word20;
    s32 held;
    s32 pressed;
    s32 reservedWord;
    s32 reservedWord1;
    s32 reservedWord2;
};

struct Shared_Slot;
struct Shared_Slot {
    s8 owned;
    s8 pad1;
};

struct Body;
struct Body {
    u8 pad[0x24];
    f32 speed;
};
struct BarrelAnchorActorView;
struct Controller;
struct BarrelAnchorActorView {
    u8 type;
    u8 pad1[7];
    CVector3 pos;
    s32 room;
    s32 *kind;
    u8 pad1C[0x50];
    f32 heading; /* 0x6C */
    f32 height;
    u8 pad74[0x70];
    u16 id;
    u8 padE6[0x1A];
    s32 flags100;
    u8 pad104[0x1A4 - 0x104];
    s8 aiMode; /* 0x1A4: CAI_t m_Mode */
    u8 pad1A5[0x1D8 - 0x1A5];
    struct Controller *controller;
    u8 pad1DC[0x238 - 0x1DC];
    s16 animType; /* 0x238: CAI_t m_AnimType */
    u8 pad23A[0x2E0 - 0x23A];
    s32 flags2E0;
};

struct Controller {
    u8 pad0[0xB0];
    s32 rawButtons;
    u8 padB4[0x62E - 0xB4];
    s16 currentWeapon; /* 0x62E: CPlayerLoadSaveData_t m_CurrentWeapon */
    u8 pad630[0x6AC - 0x630];
    u32 buttons; /* 0x6AC: CPlayerContState_t m_dwButtons */
    u8 pad6B0[0x788 - 0x6B0];
    s32 state;
    u8 pad78C[8];
    struct BarrelAnchorActorView *owner;
};
struct Ctrl;
struct Ctrl {
    u8 pad[0x8F];
    u8 flag;
};
struct RibbonClockNode;
typedef struct RibbonClockNode RibbonClockNode;

struct RibbonClockNode;
struct RibbonClockNode {
    struct RibbonClockNode *next;
    struct RibbonClockNode *prev;
    f32 time;
    char padC[0x28 - 0xC];
    s32 matrix[2][16];
    f32 offset;
    f32 length;
};

struct Mode;
struct Mode {
    char pad0[8];
    RibbonClockNode *physics;
    char padC[12];
};
struct StateInfo;
struct StateInfo {
    void (*enter)(void *, void *);
    s32 pad4;
    s32 pad8;
    s32 timer;
    s32 parameter;
    s32 pad14;
};
struct Body;
struct Character {
    char pad0[0x108];
    s32 caps[4]; /* 0x108: per ammo type maximum */
};
struct Controller;
struct Controls;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct Profile;
struct Record;
struct Rider;
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

struct ActorOwnerView;
typedef struct ActorOwnerView ActorOwnerView;

struct PakStatusProfile;
struct PakStatusProfile {
    u16 words[4];
    char pad8[0x78];
    u8 flags;
    char pad81[3];
    u8 name[8];
};

struct PlayerDamageFlagsView;
struct PlayerDamageFlagsView {
    char pad0[0x122C];
    s32 flags;
};


struct ParticleKindListView;
struct ParticleKindListView {
    char pad0[0x4];
    u16 kind;
};

struct ActorEmitterSource;
struct ActorEmitterSource {
    u8 actorKind;
    char pad0[0x100 - 0x0 - sizeof(u8)];
    s32 flags;
};

struct ActorEmitterSource;
typedef struct ActorEmitterSource ActorEmitterSource;

struct CacheResourceBlockView;
struct Pack;
struct CacheResourceBlockView {
    union { int first; struct Pack *pack; void *data; };
    int second;
    int third;
    int fourth;
};

struct AttackBehaviorDefinitionView;
typedef struct AttackBehaviorDefinitionView AttackBehaviorDefinitionView;

struct FragTagProfileFlagView;
typedef struct FragTagProfileFlagView FragTagProfileFlagView;

struct LinkedWorldFlagsView;
typedef struct LinkedWorldFlagsView LinkedWorldFlagsView;

struct LinkedWorldFlagsView;
struct LinkedWorldFlagsView {
    char pad0[0x14];
    int flags;
};


struct PakMenuSlot;
struct PakMenuSlot {
    char pad0[0x4];
    s8 controllerPort;
    char pad05[0xB0 - 5];
    s32 inputFlags; /* controller input flags used by Controller Pak selection */
};

struct ActorOwnerView;
struct ActorOwnerView {
    char pad0[0x5D8];
    struct PakStatusProfile *profile;
    char * owner;
    char pad5E0[0x698 - 0x5E0];
    struct Controller *controller;
};

struct PakMenuSlot;
typedef struct PakMenuSlot PakMenuSlot;

struct NavigationNodeOwnerView;
struct NavigationNodeOwnerView {
    char pad[0x294];
    s32 active;
};


struct FragTagProfileFlagView;
struct FragTagProfileFlagView {
    char pad0[0x8F];
    u8 fragTagEnabled;
};

extern float g_particleSimulationTimeScale;


struct ParticleKindListView;
typedef struct ParticleKindListView ParticleKindListView;


struct AttackBehaviorDefinitionView;

struct LinkedActorOwnerView;
typedef struct LinkedActorOwnerView LinkedActorOwnerView;

struct LinkedActorOwnerView;
struct LinkedActorOwnerView {
    char pad0[0x5DC];
    void * owner;
};


struct Saved;
struct Saved {
    u16 values[4];
    u8 flag;
    u8 pad[3];
    u8 bytes[8];
    u32 checksum; /* 0x14: checksum over the preceding 20 bytes. */
};

struct PlayerDamageFlagsView;
typedef struct PlayerDamageFlagsView PlayerDamageFlagsView;


struct PlayerSavedProfileOwner;
struct PakStatusProfile;
struct PlayerSavedProfileOwner {
    char pad[0x5D8];
    struct PakStatusProfile *settings;
};


struct AnimationEventMaskView;
struct AnimationEventMaskView {
    int value;
};

extern int g_pakStartButtonLatched;

struct PakStatusProfile;
typedef struct PakStatusProfile PakStatusProfile;
#endif
