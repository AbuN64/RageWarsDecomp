#ifndef AI_NAV_WEAPONSELECT_H
#define AI_NAV_WEAPONSELECT_H
struct AiController;
extern s32 Nav_SelectPlayerState(struct AiController *controller);
extern int Nav_SelectWeaponFromFirstAmmoGroup(void *controller);
extern int Nav_SelectWeaponFromSecondAmmoGroup(void *controller);
extern int Nav_SelectWeaponFromThirdAmmoGroup(void *controller);
extern int Nav_SelectSecondAmmoGroupVariantOne(void *controller);
extern int Nav_SelectSecondAmmoGroupVariantTwo(void *controller);
#endif
