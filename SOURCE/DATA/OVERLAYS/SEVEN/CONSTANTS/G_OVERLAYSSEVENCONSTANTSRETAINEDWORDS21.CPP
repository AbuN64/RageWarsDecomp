#include "TYPES.H"
#include "AMMO/AMMO.H"





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
} g_OverlaysSevenConstantsRetainedWords21 __attribute__((aligned(4))) = {
    0.785398245f,
    (void *)&g_weaponAmmoSlotCapacity27,
    0,
    0,
    (void *)&g_weaponAmmoSlotCapacity56,
    0,
    0
};
typedef char g_OverlaysSevenConstantsRetainedWords21SizeCheck[(sizeof(g_OverlaysSevenConstantsRetainedWords21) == 28) ? 1 : -1];
#endif
#endif
