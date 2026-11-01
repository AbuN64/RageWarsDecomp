#include "TYPES.H"

extern char g_weaponAmmoSlotCapacity0[];
extern char g_weaponAmmoSlotCapacity1[];


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
} g_weaponSlot2BehaviorLinksUsRev1 __attribute__((aligned(4))) = {
    0.87266469f,
    (void *)&g_weaponAmmoSlotCapacity0,
    (void *)&g_weaponAmmoSlotCapacity1,
    0,
    (void *)&g_weaponAmmoSlotCapacity0,
    (void *)&g_weaponAmmoSlotCapacity1,
    0
};
typedef char g_weaponSlot2BehaviorLinksUsRev1SizeCheck[(sizeof(g_weaponSlot2BehaviorLinksUsRev1) == 28) ? 1 : -1];
#endif
#endif
