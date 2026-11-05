#ifndef PICKUP_PICKUP_DEFINITIONS_H
#define PICKUP_PICKUP_DEFINITIONS_H
#include "types.h"

struct PickupHealthDefinition;
struct PickupPowerupDefinition;
struct PickupSpecialDefinition;
struct PickupWeaponDefinition;
/* Identity of a power-up or weapon pickup: the item id, its sound, the weapon slot it feeds and the argument it carries. */
typedef struct PickupIds {
    s16 id;
    s16 sound;
    s16 callback;
    s16 reserved;
    s16 slot;
    s16 argument;
} PickupIds;

/* Identity of a health or special pickup. */
typedef struct PickupShortIds {
    s16 id;
    s16 sound;
    s16 reserved[2];
} PickupShortIds;

/* The `label` of each record is the address of its screen text; `handler` words are the addresses of the
   functions that apply the pickup (called as handler(actor, record)). */
typedef struct PickupPowerupDefinition {
    u32 label;
    PickupIds ids;
    u32 flags;
    u32 handler;
} PickupPowerupDefinition;

typedef struct PickupWeaponDefinition {
    u32 label;
    PickupIds ids;
    u32 handler;
} PickupWeaponDefinition;

typedef struct PickupHealthDefinition {
    u32 label;
    PickupShortIds ids;
    u32 values[2];
    u32 handler;
} PickupHealthDefinition;

typedef struct PickupSpecialDefinition {
    u32 label;
    PickupShortIds ids;
    u32 handler;
} PickupSpecialDefinition;

typedef s32 (*PickupHandler)(void *actor, void *record);

extern struct PickupPowerupDefinition g_pickupPowerupDefinitions[4];
extern struct PickupWeaponDefinition g_pickupWeaponDefinitions[6];
extern struct PickupHealthDefinition g_pickupHealthDefinitions[8];
extern struct PickupSpecialDefinition g_pickupSpecialDefinitions[3];
#endif
