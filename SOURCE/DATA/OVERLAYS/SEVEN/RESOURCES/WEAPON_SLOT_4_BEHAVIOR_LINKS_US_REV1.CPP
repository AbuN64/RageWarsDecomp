#include "TYPES.H"
#include "AMMO/AMMO.H"
#include "WEAPON_STATE_TABLES/WEAPON_STATE_TABLES.H"







#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    f32 scale;
    void * primaryStates;
    void * primaryActions;
    void * primaryReserved;
    void * alternateStates;
    void * alternateActions;
    void * alternateReserved;
} g_weaponSlot4BehaviorLinksUsRev1 __attribute__((aligned(4))) = {
    1.0471977f,
    (void *)&g_weaponAmmoSlotCapacity4,
    (void *)&g_weaponAmmoSlotCapacity5,
    0,
    (void *)&g_weaponAmmoSlotCapacity33,
    (void *)&g_weaponAmmoSlotCapacity34,
    0
};
typedef char g_weaponSlot4BehaviorLinksUsRev1SizeCheck[(sizeof(g_weaponSlot4BehaviorLinksUsRev1) == 28) ? 1 : -1];
#endif
#endif
