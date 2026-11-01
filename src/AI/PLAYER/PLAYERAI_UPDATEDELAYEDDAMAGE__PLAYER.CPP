#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/INTEGERSTATE1250.H"
#include "RENDER/WEAPON_INITIALIZECHARGEANDSTARTUPCUES_DATA.H"
#include "TYPES.H"

extern void Barrel_FillDamagePacket(void *packet, s32 damageSource, s32 damage, f32 radius, s32 damageFlags, s32 shield);
extern void Playerai_ApplyDamagePacket(void *attacker, void *damageState, void *packet);
extern f32 g_frameElapsedTime;
extern s32 g_gameSettings;






void Playerai_UpdateDelayedDamage(void *player) {
    Slot damage;
    f32 remainingDelay;
    f32 previousDelay;

    previousDelay = ((PlayerWeaponDelayStateView *)(player))->delayedDamageTimer;
    if (previousDelay > 0.0f) {
        remainingDelay = previousDelay - g_frameElapsedTime;
        ((PlayerWeaponDelayStateView *)(player))->delayedDamageTimer = remainingDelay;
        if ((remainingDelay <= 0.0f) && !(g_gameSettings & 1)) {
            Barrel_FillDamagePacket(&damage,
                          ((PlayerWeaponDelayStateView *)(player))->damageSource,
                          ((PlayerWeaponDelayStateView *)(player))->delayedDamage + 6400,
                          25.599998f, 0x4000, 0);
            Playerai_ApplyDamagePacket(player, &((PlayerWeaponDelayStateView *)(player))->damageState, &damage);
        }
    }
}
