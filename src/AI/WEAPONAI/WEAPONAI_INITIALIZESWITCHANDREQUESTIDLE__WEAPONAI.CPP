#include "COMMON/RESOURCELOADSTATE.H"
#include "COMMON/WORLD.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "include_asm.h"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "WEAPONS/PLAYERRECAT1450V1.H"
#include "TYPES.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "ENGINE/AUDIO/CHANNEL.H"

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
extern s32 g_gameLoopFrameCount;




void Weaponai_InitializeSwitchAndRequestIdle(void *actor, void *weaponFireState) {
    s16 index;
    u16 unsigned_index;
    void *owner;
    void *state;

    state = ((Shared_ActorView *)actor)->self;
    index = ((Shared_ActorView *)state)->nextWeapon;
    unsigned_index = (u16)((Shared_ActorView *)state)->nextWeapon;
    if ((((Shared_ActorView *)state)->selectedAction != index) || (g_world.mode != 4)) {
        if (Weapon_IsPrimarySwitchGroup(index) != 0) {
            ((Shared_ActorView *)state)->weaponChanged = 1;
        } else if (Weapon_IsSecondarySwitchGroup(index) != 0) {
            ((Shared_ActorView *)state)->secondaryChanged = 1;
        } else if (Weapon_IsSpecialSwitchGroup(index) != 0) {
            ((Shared_ActorView *)state)->specialChanged = 1;
        }
        ((Shared_ActorView *)state)->selectedAction = unsigned_index;
        ((WeaponFireState *)weaponFireState)->animation = ((WeaponInfo *)g_weaponInfoByType[(s16)unsigned_index])->animation;
        ((WeaponFireState *)weaponFireState)->animationCount = ((WeaponInfo *)(g_weaponInfoByType[((Shared_ActorView *)state)->selectedAction]))->animationCount;
        owner = ((Shared_ActorView *)state)->message;
        if ((owner != 0) && ((u32)g_gameLoopFrameCount >= 5U)) {
            Camera_PostScreenMessage(&g_frontendScreenStatus, owner,
                *(void **)*(void **)g_weaponInfoByType[((Shared_ActorView *)state)->selectedAction]);
        }
        ((WeaponFireState *)weaponFireState)->spinStep = 0;
        ((WeaponFireState *)weaponFireState)->spin = 0;
        ((Shared_Actor *)actor)->color = 0;
        ((WeaponFireState *)weaponFireState)->charge = 0;
    }
    Actor_RequestActorState(actor, weaponFireState, 0);
}

void Weaponai_InitializeSwitchForSingleRound(void *actor, WeaponFireState *fireState) {
    s16 nextWeapon;
    u16 nextWeaponUnsigned;
    void *messageOwner;
    char *player;

    player = ((Shared_ActorView *)actor)->self;
    nextWeapon = ((Shared_ActorView *)player)->nextWeapon;
    nextWeaponUnsigned = (u16)((Shared_ActorView *)player)->nextWeapon;
    if ((((Shared_ActorView *)player)->selectedAction != nextWeapon) || (g_world.mode != 4)) {
        if (Weapon_IsPrimarySwitchGroup(nextWeapon) != 0) {
            ((Shared_ActorView *)player)->weaponChanged = 1;
        } else if (Weapon_IsSecondarySwitchGroup(nextWeapon) != 0) {
            ((Shared_ActorView *)player)->secondaryChanged = 1;
        } else if (Weapon_IsSpecialSwitchGroup(nextWeapon) != 0) {
            ((Shared_ActorView *)player)->specialChanged = 1;
        }
        ((Shared_ActorView *)player)->selectedAction = nextWeaponUnsigned;
        fireState->animation = ((WeaponInfo *)(g_weaponInfoByType[(s16)nextWeaponUnsigned]))->animation;
        fireState->animationCount = ((WeaponInfo *)(g_weaponInfoByType[((Shared_ActorView *)player)->selectedAction]))->animationCount;
        messageOwner = ((Shared_ActorView *)player)->message;
        if ((messageOwner != 0) && ((u32)g_gameLoopFrameCount >= 5U)) {
            Camera_PostScreenMessage(&g_frontendScreenStatus, messageOwner,
                          **(void ***)g_weaponInfoByType[((Shared_ActorView *)player)->selectedAction]);
        }
        fireState->spinStep = 0;
        fireState->spin = 0;
        ((Shared_Actor *)actor)->color = 0;
        fireState->charge = 0;
    }
    fireState->mode = 1;
    fireState->rounds = 1;
}
#endif

#include "TYPES.H"
#include "WEAPONS/PLAYER_INVENTORY.H"

typedef struct WeaponOwner { u8 pad0[0x1D8]; WeaponPlayer *player; } WeaponOwner;
typedef struct WeaponSlot {
    u8 pad0[0x130];
    f32 delay;
    u8 pad134[0x13C - 0x134];
    s32 mode13C;
    u8 pad140[0x144 - 0x140];
    s32 flag144;
    f32 timer148;
} WeaponSlot;
s32 Particle_CountOwnerListOneEffects(s32 *, void *);
extern s32 g_actorParticleEffectSystem;
s32 Weaponai_CanStartFiring(void *owner, void *slot) {
    WeaponOwner *weaponOwner = (WeaponOwner *)owner;
    WeaponSlot *weaponSlot = (WeaponSlot *)slot;
    WeaponPlayer *player = weaponOwner->player;
    if (weaponSlot->delay > 0.0f || !Player_HasAmmoForMode(player, player->mode)) return 0;
    if ((player->status->flag8F == 1 && g_gameSettings.counters.m_bFragTagOn != 0) || player->recoil > 0.0f || player->busy != 0) return 0;
    switch ((s16)(player->mode - 1)) {
    case 10:
        if (player->flags6AC & 0x4000) return 0;
        break;
    case 17:
        if (player->state788 != 2) return 0;
        break;
    case 8:
        if (weaponSlot->timer148 > 0.0f && weaponSlot->mode13C == 2) return 0;
        if (player->ammo < 50 && weaponSlot->mode13C == 2) return 0;
        if (player->ammo < 10) {
            if (weaponSlot->mode13C == 1) return 0;
        }
        break;
    case 11:
        if (Particle_CountOwnerListOneEffects(&g_actorParticleEffectSystem, player) >= 3) return 0;
        break;
    case 0:
        if (weaponSlot->flag144 == 0) return 0;
        break;
    }
    return 1;
}
