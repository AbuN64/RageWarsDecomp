#include "COMMON/PARTICLE_LIGHTING.H"
#ifndef COMMON_OBJRECV5_H
#define COMMON_OBJRECV5_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
struct ObjRecV5;
typedef struct ObjRecV5 ObjRecV5;

extern float g_playerTargetFacingTurnThreshold;

extern float g_playerTargetFacingBodyYawPeriod;



struct Rules;
#include "GAME/PLAYER_RULES.H"

struct Scores;
struct Scores {
    char pad[0x1c];
    short score[8];
};
struct FragTagPlayerListNode;
struct Scores;
struct FragTagPlayerListNode {
    char pad[0x5d4];
    int playerIndex;
    struct Scores *scores;
    char pad5dc[0x1104];
    struct FragTagPlayerListNode *next;
};

struct FragTagPlayerListNode;
struct Root;
struct Root {
    char pad[0x20];
    struct FragTagPlayerListNode *players;
};

struct Stats;
typedef struct Stats Stats;

struct CacheResourceBlockView;
struct ObjRecV6;
struct ObjRecV6 {
    char pad0[0x2F0];
    Triple savedPosition;
    char pad2F0[0x2FC - 0x2F0 - sizeof(Triple)];
    s32 savedSourceHandle;
    char pad2FC[0x344 - 0x2FC - sizeof(s32)];
    struct CacheResourceBlockView savedResourceBlock;
    char pad344[0x354 - 0x344 - sizeof(struct CacheResourceBlockView)];
    f32 savedYaw;
    char pad354[0x3E8 - 0x354 - sizeof(f32)];
    s32 savedFlags;
};

extern float g_playerMatchCountdownDigitLimit;

extern float g_playerTargetFacingPositiveWrapThreshold;

struct HudGlobals;
struct HudGlobals {
    u8 fade;
    u8 reserved;
    u8 state;
};

struct ObjRecV6;
typedef struct ObjRecV6 ObjRecV6;

struct SubActor;
struct SubActor {
    char pad0[4];
    s16 score; /* +0x04: Player_CheckScoreLimit tests it against the score limit */
    char pad6[0x8F - 6];
    u8 waitingRequest;
    u8 waitState;
};

struct FragTagLinkedActorView;
typedef struct FragTagLinkedActorView FragTagLinkedActorView;

struct PlayerProfileView;
struct PlayerProfileView {
    char pad0[146];
    u8 reservedByte;
    u8 difficulty;
};
struct TransientDamagePlayerView;
struct PlayerProfileView;
struct TransientDamagePlayerView {
    u8 actorKind;
    char pad1[227];
    unsigned short objectId;
    char pade6[26];
    int flags;
    char pad104[40];
    struct TransientDamagePlayerView * projectileOwner;
    char pad130[168];
    struct TransientDamagePlayerView * player;
    char pad1dc[1020];
    struct PlayerProfileView * profile;
    char pad5dc[3700];
    int computerControlled;
};

struct Held;
typedef struct Held Held;

struct Rules;


struct Round;
typedef struct Round Round;

extern float g_playerTargetFacingBodyYawThreshold;

struct TransientPlayerResetView;
struct TransientPlayerResetView {
    char pad0[0x70];
    s32 floorClearance;
    char pad70[0x358 - 0x70 - sizeof(s32)];
    s32 scanClearedWord;
    char pad358[0x16E0 - 0x358 - sizeof(s32)];
    void * nextPlayer;
};

struct PlayerDamageVisualState;
struct PlayerDamageVisualState {
    char pad0[0x170];
    char damageState;
    char pad170[0x5E4 - 0x170 - sizeof(char)];
    s32 health;
};


extern float g_playerTargetFacingYawPeriod;

struct WorldWeaponsUpdateWorldPlayers;
struct WorldWeaponsUpdateWorldPlayers {
    char pad0[0x20];
    SharedPlayer *players;
    char pad24[0x40 - 0x24];
    s32 spin;
};

struct ActorNode;
typedef struct ActorNode ActorNode;

struct Receiver;
struct Receiver {
    char pad[0x5A4];
    s32 index;
    s32 amount;
};


extern float g_playerMatchCountdownDigitOffsets;

struct CPlayerDamageOverTime_t;
struct CPlayerDamageOverTime_t {
    char pad0[0x4];
    f32 m_FramesRemaining;
    char pad4[0x8 - 0x4 - sizeof(f32)];
    void * m_pDamageSource;
    char pad8[0xC - 0x8 - sizeof(void*)];
    f32 m_TotalDamage;
    char padC[0x10 - 0xC - sizeof(f32)];
    f32 m_DamageIssued;
    char pad10[0x14 - 0x10 - sizeof(f32)];
    s32 m_bIsInflator;
};

struct SubActor;
typedef struct SubActor SubActor;



struct Body;
struct Character;
struct Controller;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct Profile;
struct Record;
struct PlayerProfileStatusView;
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

struct PlayerWorldActorTables;
struct PlayerWorldActorTables {
    char pad0[0x20];
    SharedPlayer *players;
};

struct IntegerStateB4C;
typedef struct IntegerStateB4C IntegerStateB4C;

extern void Playerai_UpdateMountedMovement();

struct ViewState;
struct ViewState {
    u8 bytes[668];
    f32 width;
    f32 height;
};

struct PlayerControllerView;
typedef struct PlayerControllerView PlayerControllerView;




struct IntegerStateB4C;
struct IntegerStateB4C {
    char pad0[0xB48];
    s32 itemCount2;
};

struct CPlayerDamageOverTime_t;
typedef struct CPlayerDamageOverTime_t CPlayerDamageOverTime;

struct Game;
struct Game {
    s32 state;
    char pad4[0x24 - 0x4];
    Rules rules;
};


struct FadeEmitterView;
typedef struct FadeEmitterView FadeEmitterView;

struct ActorNode;
struct SubActor;
struct ActorNode {
    char pad0[0x5D4];
    s32 kind; /* +0x5D4: below 4 for the human players */
    struct SubActor *scores;
    char pad1[0x16E0 - 0x5D8 - 4];
    struct ActorNode *next;
};

struct Receiver;
typedef struct Receiver Receiver;

struct FragTagSelectionActorView;
typedef struct FragTagSelectionActorView FragTagSelectionActorView;

struct FragTagLinkedActorView;
struct FragTagLinkedActorView {
    char pad0[0xC4];
    s32 resourceKey;
    char padC4[0xD0 - 0xC4 - sizeof(s32)];
    s32 resourceFlags;
    char padD0[0x100 - 0xD0 - sizeof(s32)];
    s32 flags;
    char pad100[0x2E8 - 0x100 - sizeof(s32)];
    char actorBlock;
    char pad2E8[0x5DC - 0x2E8 - sizeof(char)];
    void * owner;
    char pad5DC[0x16E0 - 0x5DC - sizeof(void*)];
    void * next;
};

extern float g_playerTargetFacingNegativeWrapThreshold;

struct DamageSourceFlagsView;
typedef struct DamageSourceFlagsView DamageSourceFlagsView;

struct TransientPlayerWorldCounts;
struct TransientPlayerWorldCounts {
    char pad0[0x944];
    s32 itemCount1;
};

struct TransientWorldItemSlotView;
typedef struct TransientWorldItemSlotView TransientWorldItemSlotView;

struct TransientPlayerWorldCounts;
typedef struct TransientPlayerWorldCounts TransientPlayerWorldCounts;

extern float g_playerMatchCountdownCenterXScale;

struct FragTagPlayerListView;
typedef struct FragTagPlayerListView FragTagPlayerListView;

struct TransientWorldPlayerSlotView;
typedef struct TransientWorldPlayerSlotView TransientWorldPlayerSlotView;


struct FragTagPlayerListView;
struct FragTagPlayerListView {
    char pad0[0x5D8];
    char * profile;
    char pad5D8[0x5DC - 0x5D8 - sizeof(char*)];
    s32 weaponHandle;
    char pad5DC[0x11FC - 0x5DC - sizeof(s32)];
    f32 zoomLevel;
    char pad11FC[0x120C - 0x11FC - sizeof(f32)];
    s32 zoomModelVariant;
    char pad120C[0x1210 - 0x120C - sizeof(s32)];
    s32 alternateFireState;
    char pad1210[0x16E0 - 0x1210 - sizeof(s32)];
    char * nextPlayer;
};

struct HudGlobals;
typedef struct HudGlobals HudGlobals;

struct FadeEmitterView;
struct FadeEmitterView {
    char pad0[0x128];
    Triple position;
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
struct FadeEmitterView;

struct Game;
typedef struct Game Game;

struct MenuWeaponsUpdateWorldPlayers;
struct MenuWeaponsUpdateWorldPlayers {
    char pad0[0xCC9];
    u8 allowed;
    char padCCA[0x1278 - 0xCCA];
    s32 open;
    char pad127C[0x1284 - 0x127C];
    MenuRules rules;
};

struct TransientPlayerDamagePacket;
struct TransientDamagePlayerView;
struct TransientPlayerDamagePacket {
    struct TransientDamagePlayerView *source;
    int amount;
};

struct WorldWeaponsUpdateWorldPlayers;
typedef struct WorldWeaponsUpdateWorldPlayers WorldWeaponsUpdateWorldPlayers;

struct Stats;
struct Stats {
    char pad0[0x3C];
    s16 kills[8];
};

struct HudState;
typedef struct HudState HudState;

struct HudState;
struct HudState {
    u8 reserved[0x5D4];
    f32 timer;
};

struct Player16C0;
typedef struct Player16C0 Player16C0;

extern float g_playerMatchCountdownSpriteScale;

struct Player16C0;
struct Player16C0 {
    char pad0[0x5E4];
    s32 alive;
    char pad5E8[0x1640 - 0x5E8];
    UnitMtx markers[2];
};

struct TransientPlayerResetView;
typedef struct TransientPlayerResetView TransientPlayerResetView;

struct Body;
struct Controller;
struct Controls;
struct Ctrl;
struct Desc;
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

struct TransientWorldPlayerSlotView;
struct TransientWorldPlayerSlotView {
    char pad0[0x144];
    void * itemSlots;
};

struct Inventory;
struct Inventory {
    char pad[0x5F4];
    s16 items[3];
};

struct Inventory;
typedef struct Inventory Inventory;


struct TransientWorldItemSlotView;
struct TransientWorldItemSlotView {
    unsigned char padding_0[2376];
    void *secondItemSlots;
};


struct TransientPlayerDamagePacket;
typedef struct TransientPlayerDamagePacket TransientPlayerDamagePacket;

struct ViewState;
typedef struct ViewState ViewState;

struct Root;
typedef struct Root Root;

struct MenuWeaponsUpdateWorldPlayers;
typedef struct MenuWeaponsUpdateWorldPlayers MenuWeaponsUpdateWorldPlayers;

struct RulesWeaponsDrawTintedPlayer;
typedef struct RulesWeaponsDrawTintedPlayer RulesWeaponsDrawTintedPlayer;

struct TransientDamagePlayerView;
typedef struct TransientDamagePlayerView TransientDamagePlayerView;

struct CPlayerPool_t;
extern s32 Playerai_FindHighestScoringPlayerIndex(struct CPlayerPool_t *game);

extern float g_playerMatchCountdownDigitScales;

extern float g_playerMatchCountdownTimeScale;

union PlayerResourceHandle;
typedef union PlayerResourceHandle PlayerResourceHandle;

union PlayerResourceHandle;
union PlayerResourceHandle {
    void * v0;
    s32 v1;
};

struct CacheResourceBlockView;
struct ObjRecV5;
struct ObjRecV5 {
    char pad0[0x8];
    Triple currentPosition;
    char pad8[0x14 - 0x8 - sizeof(Triple)];
    s32 sourceHandle;
    char pad14[0x5C - 0x14 - sizeof(s32)];
    struct CacheResourceBlockView resourceBlock;
    char pad5C[0x6C - 0x5C - sizeof(struct CacheResourceBlockView)];
    f32 yaw;
    char pad6C[0x10E - 0x6C - sizeof(f32)];
    u8 stateChangeClear;
    char pad10E[0x2E8 - 0x10E - sizeof(u8)];
    Block actorBlock;
    char pad2E8[0x5DC - 0x2E8 - sizeof(Block)];
    void * view;
    char pad5DC[0x5EA - 0x5DC - sizeof(void*)];
    s16 voiceActive;
    char pad5EA[0x86C - 0x5EA - sizeof(s16)];
    s32 controllerState;
    char pad86C[0x11BC - 0x86C - sizeof(s32)];
    PlayerResourceHandle firstResourceHandle;
    char pad11BC[0x11C0 - 0x11BC - sizeof(PlayerResourceHandle)];
    PlayerResourceHandle secondResourceHandle;
    char pad11C0[0x11D8 - 0x11C0 - sizeof(PlayerResourceHandle)];
    f32 cooldown;
    char pad11D8[0x16E0 - 0x11D8 - sizeof(f32)];
    char * next;
};

struct PlayerWorldActorTables;
typedef struct PlayerWorldActorTables PlayerWorldActorTables;

struct PlayerControllerView;
struct PlayerControllerView {
    char pad0[0xE4];
    u16 kind;
    char padE6[0x5D8 - 0xE6];
    FragTagProfileFlagView *controls;
    struct GameplayCamera *camera;
    s32 state;
    s32 health;
    char pad5E8[0x62E - 0x5E8];
    s16 selectedWeapon;
    char pad630[0x11D8 - 0x630];
    f32 ghost;
    char pad11DC[0x122C - 0x11DC];
    u32 flags;
    f32 tintTime;
    char pad1234[4];
    s32 tintMode;
    u8 red, green, blue, reserved123F;
    f32 opacity;
    char pad1244[0x13C8 - 0x1244];
    s32 hidden;
    char pad13CC[0x1450 - 0x13CC];
    s32 fixedAlpha;
};

struct FragTagPlayerListNode;
typedef struct FragTagPlayerListNode FragTagPlayerListNode;

struct DamageSourceFlagsView;
struct DamageSourceFlagsView {
    char pad0[0x100];
    s32 flags;
    char pad100[0x122C - 0x100 - sizeof(s32)];
    s32 statusFlags;
};

struct RulesWeaponsDrawTintedPlayer;
struct RulesWeaponsDrawTintedPlayer {
    char pad0[0x54];
    s32 teams;
    char pad58[0x73 - 0x58];
    u8 colour;
};

extern float g_playerMatchCountdownFractionLimit;


struct PlayerDamageVisualState;
typedef struct PlayerDamageVisualState PlayerDamageVisualState;

struct FragTagSelectionActorView;
struct FragTagSelectionActorView {
    u8 pad000[0x3E8];
    s32 flags;
    u8 pad3EC[0x480];
    s32 value86C;
};

struct ActorNode;
struct Round;
struct Round {
    char pad0[0x20];
    struct ActorNode *players;
};

struct PlayerControllerView;


struct SharedPlayer;

typedef struct ForcePlayer ForcePlayer;
struct ForcePlayer { u8 pad0[0x5D0]; s32 active; u8 pad5D4[0xC28]; f32 strength; CVector3 origin; s32 attract; u8 pad1210[0x4D0]; ForcePlayer *next; };
typedef struct { u8 pad0[0x20]; ForcePlayer *head; } ForcePlayerList;
typedef struct { u8 pad0[8]; CVector3 position; u8 pad14[8]; CVector3 velocity; u8 pad28[0x14C]; CVector3 direction; } ForceBody;

extern char g_playerRideViewAngleParameters;
extern SharedMovement g_playerRideMovementParameters[2];
extern CVector3 g_playerRideOffset;

extern char s_playersText[];

void Playerai_ClearPlayerResetFlags(char *);
void Playerai_ResetAllPlayerHealth(void *);
s32 Playerai_CountEligiblePlayers(char *);
extern f32 g_fragTagRotatingBannerHalfWidth;
extern f32 g_fragTagRotatingBannerSize;
extern f32 g_fragTagRotatingViewCenterScale;
extern f32 g_fragTagRotatingViewIconOffset;
extern f32 g_fragTagChosenViewCenterScale;
extern f32 g_fragTagChosenViewIconOffset;
extern f32 g_fragTagChosenBannerHalfWidth;
extern f32 g_fragTagChosenBannerSize;
extern s32 g_pickupSavedMusicPlaybackEnabled;

extern void Gobjinst_UpdateModelBounds(void *actorStorage, s32 model);

extern void Playerai_AddReactionReserve(void *actor, f32 amount, void *source);

extern void Playerai_DrawCachedModelAndShadow(void *actorIn, s32 shadowMode);
extern s32 Gobjinst_BuildAnimatedPose(void *actorStorage, s32 resourceRequestMode);
struct WeaponMenuView;
#endif
