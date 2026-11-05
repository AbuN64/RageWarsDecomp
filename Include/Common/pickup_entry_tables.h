#ifndef COMMON_PICKUP_ENTRY_TABLES_H
#define COMMON_PICKUP_ENTRY_TABLES_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/vector4f.h"
#include "Common/aiprofile.h"

struct PowerupIdEntry;
typedef struct PowerupIdEntry PowerupIdEntry;







struct Player;


























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











extern float k_pickupBonusSelectionConstants;

/* The five 0x14-byte ammunition definitions searched at g_pickupWeaponDefinitions. */
typedef struct AmmoPickupDefinition {
    PowerupIdEntry effect;
    s32 (*apply)(void *actor, struct AmmoPickupDefinition *definition); /* +0x10 */
} AmmoPickupDefinition;



typedef struct PickupDefinition24 {
    PowerupIdEntry effect;
    s16 extraArguments[2]; /* +0x10: remaining effect arguments */
    s32 (*apply)(void *actor, struct PickupDefinition24 *definition); /* +0x14 */
} PickupDefinition24;

/* Health entries carry word quantities, unlike the halfword weapon arguments. */
typedef struct HealthPickupDefinition {
    void *resource;
    s16 id;
    s16 sound;
    s16 callback;
    s16 reservedA;
    s32 amount;
    s32 limit;
    s32 (*apply)(void *actor, struct HealthPickupDefinition *definition);
} HealthPickupDefinition;

/* Sixteen mutable ammunition records: payload, three quantities, reserved slot and handler.
   The handler is stored at +0x14, after the +0x10 third-channel quantity. */
typedef struct AmmoBundleDefinition {
    PowerupIdEntry effect;
    s16 thirdAmmo;
    s16 reserved12; /* +0x12: table slot not consumed by the bundle handler */
    s32 (*apply)(void *actor, struct AmmoBundleDefinition *definition);
} AmmoBundleDefinition;

/* Compact callback records end at +0x10; their callback occupies +0xC,
   rather than the quantity words of PowerupIdEntry. */
typedef struct TargetedPickupDefinition {
    void *resource;
    s16 id;
    s16 sound;
    s16 callback;
    s16 reservedA;
    s32 (*apply)(void *actor, struct TargetedPickupDefinition *definition, s32 target);
} TargetedPickupDefinition;

typedef struct PickupCallbackDefinition {
    void *resource;
    s16 id;
    s16 sound;
    s16 callback;
    s16 reservedA;
    s32 (*apply)(void *actor, struct PickupCallbackDefinition *definition);
} PickupCallbackDefinition;

/* Three-channel pickups extend the common two-argument effect record. */
typedef struct MultiChannelItemEffect {
    PowerupIdEntry effect;
    s16 third;
} MultiChannelItemEffect;

/* ApplySpecialPickup's float literal pool, 21 words in address order (eu and de order them differently). */
extern f32 k_pickupApplySpecialPickupLiterals[21];
#endif
