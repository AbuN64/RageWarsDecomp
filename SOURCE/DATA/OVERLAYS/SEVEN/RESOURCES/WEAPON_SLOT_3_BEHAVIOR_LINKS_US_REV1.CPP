
#if defined(VERSION_US_REV1)
extern char g_weaponAmmoSlotCapacity2[];
extern char g_weaponAmmoSlotCapacity3[];
extern char g_weaponAmmoSlotCapacity31[];
extern char g_weaponAmmoSlotCapacity32[];
void * g_weaponSlot3BehaviorLinksUsRev1[7] = {
    0, (void *)&g_weaponAmmoSlotCapacity2, (void *)&g_weaponAmmoSlotCapacity3, 0,
    (void *)&g_weaponAmmoSlotCapacity31, (void *)&g_weaponAmmoSlotCapacity32, 0,
};
#endif
