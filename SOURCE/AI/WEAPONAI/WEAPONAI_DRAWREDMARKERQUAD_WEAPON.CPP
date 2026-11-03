#include "include_asm.h"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/PLAYER_RECORD_AND_FRAGTAG_VIEWS.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "TYPES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "WEAPONS/WEAPONAI_DRAWREDMARKERQUAD.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

extern s32 Playerai_PlayerHasAmmoForWeapon(void *player, s32 requestedWeaponType);



extern WeaponActionRecord g_weaponActionRecords[];








#include "COMMON/WORLD.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/VECTOR4F.H"
#include "WEAPONS/PLAYERRECAT1450V1.H"
#include "TYPES.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"

extern s32 g_gameLoopFrameCount;
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "ENGINE/AUDIO/CHANNEL.H"














void Weaponai_ApplyWeaponSwitch(void *part, void *body) {
    s16 index;
    u16 unsigned_index;
    void *owner;
    void *state;

    state = ((Shared_ActorView *)part)->self;
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
        ((WeaponFireState *)body)->animation = ((WeaponInfo *)g_weaponInfoByType[(s16)unsigned_index])->animation;
        ((WeaponFireState *)body)->animationCount = ((WeaponInfo *)(g_weaponInfoByType[((Shared_ActorView *)state)->selectedAction]))->animationCount;
        owner = ((Shared_ActorView *)state)->message;
        if ((owner != 0) && ((u32)g_gameLoopFrameCount >= 5U)) {
            Camera_PostScreenMessage(&g_frontendScreenStatus, owner,
                #if defined(VERSION_EU) || defined(VERSION_EU_X)
                (*(void ***)g_weaponInfoByType[((Shared_ActorView *)state)->selectedAction])[g_frontendScreenStatus.settings.language]);
#else
                *(void **)*(void **)g_weaponInfoByType[((Shared_ActorView *)state)->selectedAction]);
#endif
        }
        ((WeaponFireState *)body)->spinStep = 0;
        ((WeaponFireState *)body)->spin = 0;
        ((Shared_Actor *)part)->color = 0;
        ((WeaponFireState *)body)->charge = 0;
    }
}
