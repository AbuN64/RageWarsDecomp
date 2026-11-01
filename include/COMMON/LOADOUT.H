#ifndef COMMON_LOADOUT_H
#define COMMON_LOADOUT_H
#include "TYPES.H"
#include "COMMON/ACTIVE.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct Loadout;
struct Loadout {
    char pad0[0x108];
    int capacity[1];
};
struct Loadout;
struct PlayerWeaponsGetAmmoCapacity;
struct PlayerWeaponsGetAmmoCapacity {
    char pad0[0x18];
    struct Loadout *loadout;
    char pad1C[0x5D4 - 0x1C];
    int character;
    char pad5D8[0x1450 - 0x5D8];
    int isBot;
};



struct Entry190;
struct Entry190 {
    s32 value;
    u8 pad[0x18C];
};

struct CacheResourceBlockView;


struct PlayerViewRenderListNode;
struct PlayerViewRenderListNode {
    char pad0[0xE4];
    u16 modelKind;
    char padE4[0x5DC - 0xE4 - sizeof(u16)];
    void * view;
    char pad5DC[0x16E0 - 0x5DC - sizeof(void*)];
    void * next;
};

struct PlayerHealthDefinitionView;
struct PlayerHealthDefinitionView {
    char pad0[0x18];
    void * definition;
    char pad18[0x5D4 - 0x18 - sizeof(void*)];
    s32 playerIndex;
    char pad5D4[0x5D8 - 0x5D4 - sizeof(s32)];
    char * options;
    char pad5D8[0x1450 - 0x5D8 - sizeof(char*)];
    s32 computerControlled;
};


struct Entry190;
typedef struct Entry190 Entry190;

struct CacheResourceBlockView;


struct PlayerSequenceFadeView;
typedef struct PlayerSequenceFadeView PlayerSequenceFadeView;

struct PlayerSequenceFadeView;
struct PlayerSequenceFadeView {
    char pad0[0x840];
    f32 value;
    char pad844[4];
    s32 override;
};

extern f32 Playerai_GetSequenceFade(PlayerSequenceFadeView *rampState);

struct PlayerViewListNode;
struct PlayerViewListNode {
    char pad0[0x5DC];
    void * view;
    char pad5DC[0x16E0 - 0x5DC - sizeof(void*)];
    void * next;
};


struct IntegerStateD4;
typedef struct IntegerStateD4 IntegerStateD4;



extern float g_playerOwnerHeightScale;

struct PlayerWeaponsGetAmmoCapacity;
typedef struct PlayerWeaponsGetAmmoCapacity PlayerWeaponsGetAmmoCapacity;


struct Node_Weapons_EndRound;
struct Node_Weapons_EndRound {
    u8 pad0[0x5D8];
    u8 *state;
    u8 pad5DC[0x280];
    s32 roundEndTimer;
    u8 pad860[0xE80];
    struct Node_Weapons_EndRound *next;
};



struct IntegerStateD4;
struct IntegerStateD4 {
    unsigned char padding_0[208];
    s32 clearedWord;
};


struct PlayerTimeScaleListNode;
struct PlayerTimeScaleListNode {
    char pad0[0x670];
    f32 timeScale;
    char pad670[0x16E0 - 0x670 - sizeof(f32)];
    char * next;
};

extern int Playerai_SetPositionAndFloor(void *player, void *newPosition);

struct Context;
extern void *Playerai_GetPlayerByViewIndex(struct Context *context, u32 viewPlayerIndex);

extern void Playerai_UpdateHeldWeaponPose(void *player);



struct TrackedRecordValueView;
typedef struct TrackedRecordValueView TrackedRecordValueView;

extern float g_playerNearestLiveDistanceLimit;




extern void Playerai_StopActiveEffect(Shared_Effect *effect);


extern void Playerai_SetAllPlayerTimeScales(char *object, f32 timeScale);

extern void Playerai_SetTrackedRecordValue(TrackedRecordValueView *record, int newValue);




extern float g_playerUndefinedActorHeight;



struct Node_Weapons_EndRound;
typedef struct Node_Weapons_EndRound Node_Weapons_EndRound;

struct GlobalState;
typedef struct GlobalState GlobalState;




struct PlayerPositionListNode;
typedef struct PlayerPositionListNode PlayerPositionListNode;


struct TrackedRecordValueView;
struct TrackedRecordValueView {
    char pad0[0x4];
    int value;
    char pad4[0xB4 - 0x4 - sizeof(int)];
    int repeatedValue;
};








struct PlayerHealthDefinitionView;
typedef struct PlayerHealthDefinitionView PlayerHealthDefinitionView;


struct PlayerViewListNode;
typedef struct PlayerViewListNode PlayerViewListNode;

struct PlayerViewRenderListNode;
typedef struct PlayerViewRenderListNode PlayerViewRenderListNode;

struct GlobalState;
struct GlobalState {
    u8 pad0[0x1C];
    s32 reservedWordFirst;
    s32 primaryFireMode;
    s32 alternateFireMode;
    s32 reservedWordSecond;
    u8 pad2C[0x28];
    s32 restricted; /* 0x54 */
    u8 pad58[0x10];
    s32 restrictionActive; /* 0x68 */
};

struct Node_Weapons_EndRound;

struct PlayerTimeScaleListNode;
typedef struct PlayerTimeScaleListNode PlayerTimeScaleListNode;

struct PlayerPositionListNode;
struct PlayerPositionListNode {
    char pad0[0x8];
    f32 positionX;
    char pad8[0xC - 0x8 - sizeof(f32)];
    f32 positionY;
    char padC[0x10 - 0xC - sizeof(f32)];
    f32 positionZ;
    char pad10[0x16E0 - 0x10 - sizeof(f32)];
    void * next;
};

extern float g_playerDefaultOwnerHeight;
#endif
