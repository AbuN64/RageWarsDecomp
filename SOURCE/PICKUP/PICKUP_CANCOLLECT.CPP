#include "COMMON/GAMEPLAY_CAMERA.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ENTRYRECATE.H"
#include "TYPES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "INSTHDR/INSTHDR_GETACTORSHADOWRADIUS.H"
#include "PICKUP/PICKUP_CANCOLLECT.H"
#include "PLAYER_UPDATEPLAYERCAMERA/PLAYER_UPDATEPLAYERCAMERA.H"

/* Returns whether a player actor can use the item picked up through InstHdr_GetActorType: never for non-players or disabled actors, always during a team round when the model says so, and otherwise by the item's table: a g_pickupPowerupDefinitions power-up when the actor's team matches a g_playerSpecialModelIds entry or its slot is free while not both states 3 and 7 are in use, a g_pickupWeaponDefinitions weapon when on those teams or below the level from Player_GetAmmoCapacity_PickupCancollect, a g_pickupHealthDefinitions item when Player_GetMaxHealth_Player exceeds the actor's count at 0x5E4, any g_pickupAmmoDefinitions item, and a g_pickupSpecialDefinitions item unless it is item 0xBD6. */

extern s32 Player_GetAmmoCapacity(Player *actor, s16 index, s32 capacityMode);
extern s32 Player_GetMaxHealth(Player *actor, s32 id);
static inline PowerupIdEntry *find_entry(char *table, s32 count, s32 size, s32 id) {
    PowerupIdEntry *entry;
    s32 i;
    entry = (PowerupIdEntry *)table;
    for (i=count; i!=-1; --i) {
        if (entry->id == id) return entry;
        entry=(PowerupIdEntry *)((char *)entry+size);
    }
    return 0;
}
s32 Pickup_CanCollect(s32 prop, Player *actor) {
    PowerupIdEntry *powerup;
    PowerupIdEntry *weapon;
    PowerupIdEntry *item;
    PowerupIdEntry *bonus;
    PowerupIdEntry *special;
    s32 id;
    s32 level;
    s32 noState3;
    s32 noState7;
    s32 i;
    Player *player;
    id = InstHdr_GetActorType(prop);
    if (((actor)->kind == 1 && ((actor)->weaponFlags & 0x300000) != 0)) {
        player = actor;
        if (player->health == 0) {
            return 0;
        }
        if (g_gameSettings.counters.m_bFragTagOn != 0 && player->profile->bonus != 0) {
            return 1;
        }
        powerup = find_entry(&g_pickupPowerupDefinitions, 3, 24, id);
        if (powerup != 0) {
            noState3 = 1;
            noState7 = 1;
            if (player->objectId == g_playerSpecialModelIds[0] || player->objectId == g_playerSpecialModelIds[1]) {
                return 1;
            }
            if (player->weaponSlots[powerup->index].action != -1) {
                return 0;
            }
            for (i = 0; i < 22; i++) {
                if (player->weaponSlots[i].action == 3) {
                    noState3 = 0;
                } else if (player->weaponSlots[i].action == 7) {
                    noState7 = 0;
                }
            }
            if (noState3 || noState7) {
                return 1;
            }
            return 0;
        }
        weapon = find_entry(&g_pickupWeaponDefinitions, 5, 20, id);
        if (weapon != 0) {
            level = Player_GetAmmoCapacity(player, weapon->index, 0);
            if (player->objectId == g_playerSpecialModelIds[0] || player->objectId == g_playerSpecialModelIds[1]) {
                return 1;
            }
            return player->ammo[weapon->index] < level;
        }
        item = find_entry(&g_pickupHealthDefinitions, 7, 24, id);
        if (item != 0) {
            return player->health < Player_GetMaxHealth(player, id);
        }
        bonus = find_entry((char *)g_pickupAmmoDefinitions, 15, 24, id);
        if (bonus != 0) {
            return 1;
        }
        special = find_entry(&g_pickupSpecialDefinitions, 2, 16, id);
        if (special != 0) {
            if ((player->objectId == g_playerSpecialModelIds[0] || player->objectId == g_playerSpecialModelIds[1]) && special->id != 3030) {
                return 1;
            }
            return special->id != 3030;
        }
        return 0;
    }
    return ((actor)->kind == 1 && ((actor)->weaponFlags & 0x300000) != 0);
}
typedef struct Handler Handler;
/* Dispatches an item effect with the given id to an actor that can receive it: looks the id up in each item handler table in turn (g_pickupPowerupDefinitions, g_pickupWeaponDefinitions, g_pickupHealthDefinitions, g_pickupSingleDefinitions, g_pickupAmmoDefinitions, g_pickupTargetedDefinitions and g_pickupSpecialDefinitions) and returns the first nonzero handler result, clearing the given target from every actor's two lock-on slots after the g_pickupAmmoDefinitions handler. */
extern Other *g_transientPlayerList;
static inline Handler *find_handler(char *table, s32 count, s32 size, s32 id) {
    Handler *entry;
    s32 i;
    entry = (Handler *)table;
    i = count;
    do {
        if (entry->id == id) {
            return entry;
        }
        i--;
        entry = (Handler *)((char *)entry + size);
    } while (i != -1);
    return 0;
}
s32 Pickup_DispatchHandler(Other *actor, s32 target, s32 id) {
    Handler *entry;
    Other *other;
    s32 result;
    result = 0;
    if (actor->enabled != 0) {
        entry = find_handler(&g_pickupPowerupDefinitions, 3, 24, id);
        if (entry != 0) {
            result = entry->handle14(actor, entry);
        }
        if (result != 0) {
            return result;
        }
        entry = find_handler(&g_pickupWeaponDefinitions, 5, 20, id);
        if (entry != 0) {
            result = entry->handle10(actor, entry);
        }
        if (result != 0) {
            return result;
        }
        entry = find_handler(&g_pickupHealthDefinitions, 7, 24, id);
        if (entry != 0) {
            result = entry->handle14(actor, entry);
        }
        if (result != 0) {
            return result;
        }
        entry = find_handler(&g_pickupSingleDefinitions, 1, 20, id);
        if (entry != 0) {
            result = entry->handle10(actor, entry);
        }
        if (result != 0) {
            return result;
        }
        entry = find_handler((char *)g_pickupAmmoDefinitions, 15, 24, id);
        if (entry != 0) {
            result = entry->handle14(actor, entry);
        }
        for (other = g_transientPlayerList; other != 0; other = other->next) {
            if (other->lockOn[0] == target) {
                other->lockOn[0] = 0;
            } else if (other->lockOn[1] == target) {
                other->lockOn[1] = 0;
            }
        }
        if (result != 0) {
            return result;
        }
        entry = find_handler(&g_pickupTargetedDefinitions, 15, 16, id);
        if (entry != 0) {
            result = entry->handleC.targeted(actor, entry, target);
        }
        if (result != 0) {
            return result;
        }
        entry = find_handler(&g_pickupSpecialDefinitions, 2, 16, id);
        if (entry != 0) {
            result = entry->handleC.plain(actor, entry);
        }
    }
    return result;
}

#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MENU_ABBDC_VERSIONS.H"
extern WeaponInfo *g_weaponInfoByType[];
#include "COMMON/MENU_MATCH_GLOBALS.H"
extern struct CCameraText_t *Camera_PostScreenMessage(struct ScreenMessageOwner *owner, struct GameplayCamera *pool, u8 *text);
extern s32 SoundElement_PlaySoundAtPosition(s16, CVector3, s32, s32);

s32 Pickup_ApplyWeaponPickup(Player *player, MultiChannelItemEffect *pickup)
{
    s32 changed = 0;
    s32 owned;
    WeaponInfo *weapon;
    u8 **label;
    s32 sound, event;
    if (pickup->effect.argument != -1 && player->weaponSlots[pickup->effect.index].owned) {
        changed = Player_AddAmmo(player, pickup->effect.argument, pickup->third);
        if (!changed) {
            Shared_Game *game = &g_gameSettings;
            if (!(game->local && player->profile->bonus && game->fragTagEnabled)) return 0;
        }
    }
    if (g_frontendScreenStatus.settings.local) { if (!(g_weaponInfoByType[pickup->effect.index]->flags & 8)) return 0; }
    else if (g_weaponInfoByType[pickup->effect.index]->flags & 8) return 0;
    owned = player->weaponSlots[pickup->effect.index].owned;
    player->weaponSlots[pickup->effect.index].owned = 1;
    weapon = g_weaponInfoByType[pickup->effect.index];
    if (player->selectedAction < pickup->effect.index) {
        if (player->movementFlags & 0x1000 ? weapon->flags & 2 : weapon->flags & 1) {
            if (!g_frontendScreenStatus.settings.local && !owned) player->weapon = pickup->effect.index;
        }
    }
    label = pickup->effect.resource; sound = pickup->effect.sound; event = pickup->effect.callback;
    if (player->camera) {
        Gsky_StartFade(player->camera, 128, 50, 50, 75, 0, 0, 2);
        if (label != 0) Camera_PostScreenMessage(&g_frontendScreenStatus, player->camera, label[MENU_LANGUAGE]);
    }
    if (sound) SoundElement_PlaySoundAtPosition(sound, player->pos, 0, -1);
    if (event) SoundElement_PlayDialogGroup(event);
    if (!changed) Player_AddAmmo(player, pickup->effect.argument, pickup->third);
    return 1;
}
