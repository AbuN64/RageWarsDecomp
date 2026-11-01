#ifndef COMMON_ENTRYRECATE_H
#define COMMON_ENTRYRECATE_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"

struct PowerupIdEntry;
typedef struct PowerupIdEntry PowerupIdEntry;


struct Other;
struct Other {
    char pad0[0x5E4];
    s32 enabled;
    char pad5E8[0x1224 - 0x5E8];
    s32 lockOn[2];
    char pad122C[0x16E0 - 0x122C];
    struct Other *next;
};





struct Shared_ActorView;



struct ActorPickupCanCollect;
struct ActorPickupCanCollect {
    u8 type;
    u8 pad1[7];
    CVector3 position; /* 0x08: provider SoundElement_PlaySoundAtPosition_PlayerUpdatefragtagselection takes CVector3 */
    u8 pad14[0xE4 - 0x14];
    u16 team;
    char padE6[0x100 - 0xE6];
    s32 flags;
    u8 pad104[0x174 - 0x104];
    s32 active; /* 0x174 */
    u8 pad178[0x5D8 - 0x178];
    FragTagProfileFlagView *model;
    void *owner; /* 0x5DC */
    u8 pad5E0[4];
    s32 count;
    u16 fraction; /* 0x5E8 */
    s16 lives; /* 0x5EA */
    u8 pad5EC[8];
    s16 levels[7];
    char pad602[0x602 - 0x602];
    Shared_Slot slots[22];
};



struct Other;
typedef struct Other Other;

















struct PowerupIdEntry;
struct PowerupIdEntry {
    void *resource;
    s16 id;
    s16 sound;
    s16 callback;
    s16 reservedA;
    s16 index;
    s16 argument;
};




struct ActorPickupCanCollect;
typedef struct ActorPickupCanCollect ActorPickupCanCollect;







extern float k_pickupBonusSelectionConstants;

/* The five 0x14-byte ammunition definitions searched at g_pickupWeaponDefinitions. */
typedef struct AmmoPickupDefinition {
    u8 reserved0[4];
    s16 kind;
    u8 reserved6[6];
    s16 slot;
    u8 reservedE[6];
} AmmoPickupDefinition;



typedef struct PickupDefinition24 {
    PowerupIdEntry effect;
    s16 values[4];
} PickupDefinition24;

/* Three-channel pickups extend the common two-argument effect record. */
typedef struct MultiChannelItemEffect {
    PowerupIdEntry effect;
    s16 third;
} MultiChannelItemEffect;

extern f32 k_pickupApplySpecialPickupLiteralF32At00;
extern f32 k_pickupApplySpecialPickupLiteralF32At08;
extern f32 k_pickupApplySpecialPickupLiteralF32At10;
extern f32 k_pickupApplySpecialPickupLiteralF32At14;
extern f32 k_pickupApplySpecialPickupLiteralF32At1C;
extern f32 k_pickupApplySpecialPickupLiteralF32At24;
extern f32 k_pickupApplySpecialPickupLiteralF32At28;
extern f32 k_pickupApplySpecialPickupLiteralF32At2C;
extern f32 k_pickupApplySpecialPickupLiteralF32At30;
extern f32 k_pickupApplySpecialPickupLiteralF32At34;
extern f32 k_pickupApplySpecialPickupLiteralF32At38;
extern f32 k_pickupApplySpecialPickupLiteralF32At3C;
extern f32 k_pickupApplySpecialPickupLiteralF32At44;
extern f32 k_pickupApplySpecialPickupLiteralF32At4C;
#endif
