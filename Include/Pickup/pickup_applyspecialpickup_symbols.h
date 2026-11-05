#ifndef PICKUP_PICKUP_APPLYSPECIALPICKUP_SYMBOLS_H
#define PICKUP_PICKUP_APPLYSPECIALPICKUP_SYMBOLS_H
#include "types.h"
typedef struct Shared_MenuBonusColumn Shared_MenuBonusColumn;
struct Shared_MenuBonusColumn {
    u8 value;
    u8 rest[399];
};
#include "types.h"
extern struct Shared_MenuBonusColumn g_playerPrimaryBonusProfileCounters[];
extern struct Shared_MenuBonusColumn g_playerSecondaryBonusProfileCounters[];
extern struct Shared_MenuBonusColumn g_playerPickupProfileCounters[];
extern struct Shared_MenuBonusColumn g_playerAmmoBonusProfileCounters[];
#if (defined(VERSION_EU_X))
extern const f32 g_specialPickupShieldDurationEu[2];
extern f32 k_pickupEuropeanEffectDuration;
extern char g_pickupEuropeanEffectUpdateRomEntry[], g_pickupEuropeanEffectDrawRomEntry[];
#endif
#if (defined(VERSION_EU))
extern const f32 g_specialPickupShieldDurationEu[2];
extern f32 k_pickupEuropeanEffectDuration;
extern const f32 g_specialPickupShieldDurationEu[2];
extern f32 k_pickupEuropeanEffectDuration;
extern char g_pickupEuropeanEffectUpdateRomEntry[], g_pickupEuropeanEffectDrawRomEntry[];
#endif
#endif
