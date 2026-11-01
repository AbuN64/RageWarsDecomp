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



void Weaponai_DrawRedMarkerQuad(void *object, void *unused) {
    MarkerActor *actor=object;
    MarkerNode *node;
    s32 red, alpha;
    node=actor->node;
    if(node->active) {
        gSPMatrix(g_displayListCursor++, (u32)&node->matrices[g_lightingBufferIndex], G_MTX_LOAD);
        gDPPipeSync(g_displayListCursor++);
        Geometry_InvalidateMaterialKeys();
        Geometry_SetModePreset(14);
        Geometry_SetCombineMode(28);
        red=200; alpha=150;
        gSPGeometryMode(g_displayListCursor++, G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | 0x80, 0);
        gSPGeometryMode(g_displayListCursor++, 0, G_SHADE | G_SHADING_SMOOTH);
        g_weaponRedMarkerVertices[0].x=1;
        g_weaponRedMarkerVertices[0].y=1;
        g_weaponRedMarkerVertices[0].z=0;
        g_weaponRedMarkerVertices[0].flag=0;
        g_weaponRedMarkerVertices[0].s=0;
        g_weaponRedMarkerVertices[0].t=0;
        g_weaponRedMarkerVertices[0].r=red;
        g_weaponRedMarkerVertices[0].g=0;
        g_weaponRedMarkerVertices[0].b=0;
        g_weaponRedMarkerVertices[0].a=red;
        g_weaponRedMarkerVertices[1].x=-1;
        g_weaponRedMarkerVertices[1].y=1;
        g_weaponRedMarkerVertices[1].z=0;
        g_weaponRedMarkerVertices[1].flag=0;
        g_weaponRedMarkerVertices[1].s=0;
        g_weaponRedMarkerVertices[1].t=0;
        g_weaponRedMarkerVertices[1].r=red;
        g_weaponRedMarkerVertices[1].g=0;
        g_weaponRedMarkerVertices[1].b=0;
        g_weaponRedMarkerVertices[1].a=red;
        g_weaponRedMarkerVertices[2].x=15;
        g_weaponRedMarkerVertices[2].y=1;
        g_weaponRedMarkerVertices[2].z=-1;
        g_weaponRedMarkerVertices[2].flag=0;
        g_weaponRedMarkerVertices[2].s=0;
        g_weaponRedMarkerVertices[2].t=0;
        g_weaponRedMarkerVertices[2].r=red;
        g_weaponRedMarkerVertices[2].g=0;
        g_weaponRedMarkerVertices[2].b=0;
        g_weaponRedMarkerVertices[2].a=alpha;
        g_weaponRedMarkerVertices[3].x=-15;
        g_weaponRedMarkerVertices[3].y=1;
        g_weaponRedMarkerVertices[3].z=-1;
        g_weaponRedMarkerVertices[3].flag=0;
        g_weaponRedMarkerVertices[3].s=0;
        g_weaponRedMarkerVertices[3].t=0;
        g_weaponRedMarkerVertices[3].r=red;
        g_weaponRedMarkerVertices[3].g=0;
        g_weaponRedMarkerVertices[3].b=0;
        g_weaponRedMarkerVertices[3].a=alpha;
        gSPVertex(g_displayListCursor++, (u32)g_weaponRedMarkerVertices, 4, 0);
        gSP1Triangle(g_displayListCursor++, 0, 1, 2, 0);
        gSP1Triangle(g_displayListCursor++, 1, 2, 3, 0);
        if(node->extra) Fx_DrawRedParticleQuad((u32)&node->extraMatrices[g_lightingBufferIndex]);
    }
}

s32 Weaponai_FindNextUsableWeapon(void *player)
{
    s32 slot;
    s32 category;
    s32 special;
    Shared_ActorView *actor;
    char *indexed;
    char *scan;

    actor = player;
    category = actor->actions[actor->selectedAction].category;
    if (category < 0) {
        category = 0;
    }
    if (category >= 8) {
        category = 0;
    }

    category++;
    if (category < 8) {
        special = 6;
        do {
            for (slot = 0; slot < 22; slot++) {
                if (category == actor->actions[slot].category) {
                    break;
                }
            }
            if ((slot < 22) && Playerai_PlayerHasAmmoForWeapon(actor, slot)) {
                if ((slot != special) || (actor->ammo[0] >= 11)) {
                    if ((actor->remote == 0) || (slot < 18)) {
                        return slot;
                    }
                }
            }
            category++;
            slot = 0;
        } while (category < 8);
    }

    category = actor->actions[actor->selectedAction].category;
    if (category < 0) {
        category = 0;
    }
    if (category >= 8) {
        category = 0;
    }

    category--;
    if (category > 0) {
        special = 6;
        do {
            for (slot = 0; slot < 22; slot++) {
                if (category == actor->actions[slot].category) {
                    break;
                }
            }
            if ((slot < 22) && Playerai_PlayerHasAmmoForWeapon(actor, slot)) {
                if ((slot != special) || (actor->ammo[0] >= 11)) {
                    return slot;
                }
            }
            category--;
            slot = 0;
        } while (category > 0);
    }
    return 0;
}

s32 Weaponai_NextAvailableWeapon(ObjectWeaponsNextAvailableWeapon *player) {
    s32 value;
    s32 number;
    s32 index;
    s32 result;

    value = player->values[player->selected * 2];
    if (value < 0) {
        value = 0;
    }
    if (value >= 8) {
        value = 0;
    }
    value++;
    while (value < 8) {
        number = 0;
        while ((number < 22) && (value != player->values[number * 2])) {
            number++;
        }
        if ((number < 22) && (Playerai_PlayerHasAmmoForWeapon(player, number) != 0)) {
            return number;
        }
        value++;
    }
    value = player->values[player->selected * 2];
    number = 1;
    while (number < value) {
        index = 0;
        while ((index < 22) && (number != player->values[index * 2])) {
            index++;
        }
        if ((index < 22) && (Playerai_PlayerHasAmmoForWeapon(player, index) != 0)) {
            return index;
        }
        number++;
    }
    SoundElement_PlayFlatSound(3405);
    result = player->selected;
    return result;
}

void Weaponai_UpdateCallbacksAndTimers(void *actorStorage, void *stateController) {
    void *actor;
    s16 index;
    s32 value;
    f32 old_delta;
    f32 scaled_delta;
    f32 zero;
    f32 timer;
    void *callback_owner;
    void (*callback)(void *, void *);

    actor = ((WeaponMarkerActorContext *)(actorStorage))->owner;
    index = ((WeaponMarkerActorView *)(actor))->pose;
    value = g_weaponActionRecords[index].action;

    if (0.0f < ((WeaponMarkerActorView *)(actor))->cooldown) {
        return;
    }

    old_delta = g_frameElapsedTime;
    scaled_delta = old_delta * g_weaponMarkerDeltaScale;
    if (actor != 0 && (((WeaponMarkerActorView *)(actor))->reactionFlags & 0x2000)) {
        g_frameElapsedTime = scaled_delta;
    } else {
        g_frameElapsedTime = old_delta;
    }

    timer = ((WeaponMarkerControllerView *)(stateController))->timeRemainingA;
    zero = 0.0f;
    if (zero < timer) {
        ((WeaponMarkerControllerView *)(stateController))->timeRemainingA = timer - g_frameElapsedTime;
        ((WeaponMarkerActorContext *)(actorStorage))->stateFlag = 0;
    } else {
        ((WeaponMarkerActorContext *)(actorStorage))->stateFlag = 0;
    }

    if (zero < ((WeaponMarkerControllerView *)(stateController))->timeRemainingB) {
        ((WeaponMarkerControllerView *)(stateController))->timeRemainingB -= g_frameElapsedTime;
    }

    if (value == 1) {
        Actor_RequestActorState(actorStorage, stateController, 1);
    }
    if (((WeaponMarkerActorView *)(actor))->weapon != ((WeaponMarkerActorView *)(actor))->selectedAction) {
        ((WeaponMarkerActorView *)(actor))->state7E8 = 0;
        Actor_RequestActorState(actorStorage, stateController, 1);
    }

    callback_owner = ((WeaponMarkerControllerView *)(stateController))->callback_owner;
    if (callback_owner != 0) {
        callback = ((struct Hook *) ((char *) callback_owner))->fn;
        if (callback != 0) {
            callback(actorStorage, stateController);
        }
    }

    callback = ((struct WeaponMarkerCallbackView *) ((char *) g_weaponInfoByType[((WeaponMarkerActorView *) actor)->selectedAction]))->callback;
    if (callback != 0) {
        callback(actorStorage, stateController);
    }
    Playerai_UpdateHeldWeaponModel(actor);
    g_frameElapsedTime = old_delta;
}


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
