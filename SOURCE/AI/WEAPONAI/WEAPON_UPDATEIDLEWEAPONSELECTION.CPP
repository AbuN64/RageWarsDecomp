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

/* 800C3144.CPP */
#if defined(VERSION_EU)
const unsigned int k_WeaponUpdateidleweaponselectionEncodedWordsBlock1[1] = { 0x00000000 };
#endif

/* 8022F3E8_6.CPP */
#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
extern char g_weaponActionRecords;

extern s16 Weaponai_FindNextUsableWeapon(void *player);
extern s32 SoundElement_PlaySoundAtPosition(s16 track, CVector3 position, s32 emitterKey, s32 ownerId);

void Weapon_UpdateIdleWeaponSelection(LevelActor *levelActor, void *weaponFireState) {
    s32 state;
    void *actor;
    CGameStatus *audio;
    s32 mode;

    actor = levelActor->controller;
    state = *(s16 *)(&g_weaponActionRecords +
                     (((Shared_ActorView *)actor)->action * sizeof(struct WeaponActionRecord)));
    if ((s8)((Dest *)weaponFireState)->count != 0) {
        if (Player_HasAmmoForMode(actor, ((Shared_ActorView *)actor)->selectedAction) == 0) {
            if (((Dest *)weaponFireState)->fireMode == 2) {
                ((Dest *)weaponFireState)->fireMode = 1;
                if (Player_HasAmmoForMode(actor, ((Shared_ActorView *)actor)->selectedAction) == 0) {
                    ((Shared_ActorView *)actor)->nextWeapon = Weaponai_FindNextUsableWeapon(actor);
                }
            }
        }
    }
    Playerai_EndHeldAlternateFire(actor);
    ((Shared_ActorView *)actor)->marker.word = 0;
    ((WeaponAnimationState *)((Shared_ActorView *)actor)->controller)->speed = 0;
    ((Dest *)weaponFireState)->fireCounter = 0;

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
               ((s8)((Dest *)weaponFireState)->count != 0)) {
        Weaponai_InitializeSwitchAndRequestIdle(levelActor, weaponFireState);
    }
}
#endif
