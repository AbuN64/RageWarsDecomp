#include "COMMON/RESOURCELOADSTATE.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "AI/WEAPONAI.H"
#include "COMMON/LONE/WEAPON_LOCKED_NOTICE_TEXT.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIPLE.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "COMMON/PLAYERPROFILES.H"

/* Handles a player's attack trigger: nothing while cooling down past g_weaponTriggerCooldownLimit; the trigger is the
 * controller latch at 0x23C (cleared when read) for a flagged controlled player, else flag 0x2000; when it
 * fires and Weaponai_CanStartFiring accepts the attack, a ranged attack (type 2) that may fire takes action 8 and
 * returns 2, otherwise action 4 starts with the combo byte cleared and returns 1. Adapted from
 * Weaponai_TryEnterAlternateStateEight with the fire check as the same static helper. */
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PLAYER_GETPLAYERINDEX.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/VECTOR4F.H"
/* AttackTrigger* are unresolved canonical player/actor/control/attack types. */







extern s32 Player_GetProfileAchievementFlag(void *, s16);
extern void Gsky_PostTargetedScreenMessage(void *, void *, s32, s32, f32);










typedef struct AttackTriggerPlayer AttackTriggerPlayer;
typedef struct AttackTriggerActor AttackTriggerActor;
typedef struct AttackTriggerControl AttackTriggerControl;
typedef struct AttackTriggerAction AttackTriggerAction;
struct AttackTriggerPlayer {
    char pad0[0x5D4];
    s32 playerIndex;
    char pad5D4[0x5DC - 0x5D4 - sizeof(s32)];
    void* camera;
    char pad5DC[0x62E - 0x5DC - sizeof(void*)];
    s16 weaponMode;
    char pad62E[0x6AC - 0x62E - sizeof(s16)];
    s32 inputFlags;
    char pad6AC[0x11D8 - 0x6AC - sizeof(s32)];
    f32 cooldown;
    char pad11D8[0x1450 - 0x11D8 - sizeof(f32)];
    s32 computerControlled;
    char pad1450[0x1454 - 0x1450 - sizeof(s32)];
    char* control;
};
struct AttackTriggerActor {
    char pad0[0x100];
    s32 flags;
    char pad100[0x1D8 - 0x100 - sizeof(s32)];
    char* player;
};
struct AttackTriggerControl {
    char pad0[0x23C];
    s32 fireRequested;
};
struct AttackTriggerAction {
    char pad0[0xCB];
    u8 triggerConsumed;
    char padCB[0x13C - 0xCB - sizeof(u8)];
    s32 fireMode;
};




extern s16 g_weaponActionRecords[];
/* Updates alternate fire, falling back to another weapon when neither mode has
 * ammunition. Reports unavailable modes, preserves the selected action captured
 * on entry, then processes the attack trigger. */
#include "COMMON/AIPROFILE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
typedef struct AlternateModeInfo { u8 pad0[0x14]; u32 flags; } AlternateModeInfo;
/* The adjacent exact can_fire supplies the same readiness check; this call site
 * owns its distinct message-duration literal and localized European strings. */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/INTEGERSTATE244.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "WEAPONS/PLAYERRECAT1450V1.H"


extern s16 g_weaponActionRecords[];
extern s16 Weaponai_FindNextUsableWeapon(void *player);
extern s32 SoundElement_PlaySoundAtPosition(s16 track, CVector3 position, s32 emitterKey, s32 ownerId);












/* The PAL copy of Weapon_UpdateIdleWeaponSelection: the weapon switch and the idle request are two calls here. */
void Weaponai_UpdateAfterAmmoModeChange(LevelActor *levelActor, void *weaponSlot) {
    s32 state;
    void *actor;
    CGameStatus *audio;
    s32 mode;

    actor = levelActor->controller;
    state = *(s16 *)((char *)g_weaponActionRecords +
                     (((Shared_ActorView *)actor)->action * sizeof(struct WeaponActionRecord)));
    if ((s8)((Dest *)weaponSlot)->count != 0) {
        if (Player_HasAmmoForMode(actor, ((Shared_ActorView *)actor)->selectedAction) == 0) {
            if (((Dest *)weaponSlot)->fireMode == 2) {
                ((Dest *)weaponSlot)->fireMode = 1;
                if (Player_HasAmmoForMode(actor, ((Shared_ActorView *)actor)->selectedAction) == 0) {
                    ((Shared_ActorView *)actor)->nextWeapon = Weaponai_FindNextUsableWeapon(actor);
                }
            }
        }
    }
    Playerai_EndHeldAlternateFire(actor);
    ((Shared_ActorView *)actor)->marker.word = 0;
    ((WeaponAnimationState *)((Shared_ActorView *)actor)->controller)->speed = 0;
    ((Dest *)weaponSlot)->fireCounter = 0;

    audio = &g_gameSettings.counters;
    if ((audio->m_bFragTagOn != 0) &&
        (((Shared_ActorView *)actor)->controls->transientFlag != 0)) {
        if (((Shared_ActorView *)actor)->unk_0x06B0 & 0x2000) {
            mode = audio->m_nFragTagSkin;
            switch (mode) {
            case 0:
                SoundElement_PlaySoundAtPosition(6305,
                              ((Shared_ActorView *)actor)->position.vector,
                              (s32)&((Player *)actor)->pos, -1);
                break;
            case 1:
                SoundElement_PlaySoundAtPosition(6505,
                              ((Shared_ActorView *)actor)->position.vector,
                              (s32)&((Player *)actor)->pos, -1);
                break;
            case 2:
                SoundElement_PlaySoundAtPosition(6405,
                              ((Shared_ActorView *)actor)->position.vector,
                              (s32)&((Player *)actor)->pos, -1);
                break;
            }
        }
    } else if ((state != 1) && (state != 7) &&
               ((s8)((Dest *)weaponSlot)->count != 0)) {
        Weaponai_ApplyWeaponSwitch(levelActor, weaponSlot);
        Actor_RequestActorState(levelActor, weaponSlot, 0);
    }
}
#endif
