#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ENTRYRECATE.H"
#include "TYPES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"

/* Returns whether a player actor can use the item picked up through InstHdr_GetActorType: never for non-players or disabled actors, always during a team round when the model says so, and otherwise by the item's table: a g_pickupPowerupDefinitions power-up when the actor's team matches a g_playerSpecialModelIds entry or its slot is free while not both states 3 and 7 are in use, a g_pickupWeaponDefinitions weapon when on those teams or below the level from Player_GetAmmoCapacity_PickupCancollect, a g_pickupHealthDefinitions item when Player_GetMaxHealth_Player exceeds the actor's count at 0x5E4, any g_pickupAmmoDefinitions item, and a g_pickupSpecialDefinitions item unless it is item 0xBD6. */
extern s32 InstHdr_GetActorType(s32 prop);
extern s32 Player_GetAmmoCapacity(ActorPickupCanCollect *actor, s16 index, s32 capacityMode);
extern s32 Player_GetMaxHealth(ActorPickupCanCollect *actor, s32 id);
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
s32 Pickup_CanCollect(s32 prop, ActorPickupCanCollect *actor) {
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
    ActorPickupCanCollect *player;
    id = InstHdr_GetActorType(prop);
    if (((actor)->type == 1 && ((actor)->flags & 0x300000) != 0)) {
        player = actor;
        if (player->count == 0) {
            return 0;
        }
        if (g_gameSettings.counters.m_bFragTagOn != 0 && player->model->fragTagEnabled != 0) {
            return 1;
        }
        powerup = find_entry(&g_pickupPowerupDefinitions, 3, 24, id);
        if (powerup != 0) {
            noState3 = 1;
            noState7 = 1;
            if (player->team == g_playerSpecialModelIds[0] || player->team == g_playerSpecialModelIds[1]) {
                return 1;
            }
            if (player->slots[powerup->index].pad1 != -1) {
                return 0;
            }
            for (i = 0; i < 22; i++) {
                if (player->slots[i].pad1 == 3) {
                    noState3 = 0;
                } else if (player->slots[i].pad1 == 7) {
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
            if (player->team == g_playerSpecialModelIds[0] || player->team == g_playerSpecialModelIds[1]) {
                return 1;
            }
            return player->levels[weapon->index] < level;
        }
        item = find_entry(&g_pickupHealthDefinitions, 7, 24, id);
        if (item != 0) {
            return player->count < Player_GetMaxHealth(player, id);
        }
        bonus = find_entry((char *)g_pickupAmmoDefinitions, 15, 24, id);
        if (bonus != 0) {
            return 1;
        }
        special = find_entry(&g_pickupSpecialDefinitions, 2, 16, id);
        if (special != 0) {
            if ((player->team == g_playerSpecialModelIds[0] || player->team == g_playerSpecialModelIds[1]) && special->id != 3030) {
                return 1;
            }
            return special->id != 3030;
        }
        return 0;
    }
    return ((actor)->type == 1 && ((actor)->flags & 0x300000) != 0);
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
typedef struct DraftConfigAB97C { u8 pad[0x8F]; u8 mode; } DraftConfigAB97C;
typedef struct DraftChoiceAB97C { s8 enabled, kind; } DraftChoiceAB97C;
typedef struct DraftWeaponAB97C { u8 pad[0x14]; u32 flags; } DraftWeaponAB97C;
typedef struct DraftPlayerAB97C {
    u8 pad[8]; CVector3 position; u8 pad14[0x24]; u32 flags;
    u8 pad3C[0x59C]; DraftConfigAB97C *config; void *ui;
    u8 pad5E0[0x22]; DraftChoiceAB97C choices[22]; s16 current;
    u8 pad630[0x140]; s16 next;
} DraftPlayerAB97C;
typedef struct DraftPickupAB97C { u8 **label; s16 pad4, sound, event, padA, index, ammoType, ammoAmount; } DraftPickupAB97C;
extern DraftWeaponAB97C *g_weaponInfoByType[];
#include "COMMON/MENU_MATCH_GLOBALS.H"
extern struct CCameraText_t *Camera_PostScreenMessage(struct ScreenMessageOwner *owner, struct ScreenMessagePool *pool, u8 *text);
extern s32 Player_AddAmmo(void *, s32, s32), SoundElement_PlaySoundAtPosition(s16, CVector3, s32, s32);

s32 Pickup_ApplyWeaponPickup(DraftPlayerAB97C *player, DraftPickupAB97C *pickup)
{
    s32 changed = 0;
    s32 owned;
    DraftWeaponAB97C *weapon;
    u8 **label;
    s32 sound, event;
    if (pickup->ammoType != -1 && player->choices[pickup->index].enabled) {
        changed = Player_AddAmmo(player, pickup->ammoType, pickup->ammoAmount);
        if (!changed) {
            Shared_Game *game = &g_gameSettings;
            if (!(game->local && player->config->mode && game->fragTagEnabled)) return 0;
        }
    }
    if (g_frontendScreenStatus.settings.local) { if (!(g_weaponInfoByType[pickup->index]->flags & 8)) return 0; }
    else if (g_weaponInfoByType[pickup->index]->flags & 8) return 0;
    owned = player->choices[pickup->index].enabled;
    player->choices[pickup->index].enabled = 1;
    weapon = g_weaponInfoByType[pickup->index];
    if (player->current < pickup->index) {
        if (player->flags & 0x1000 ? weapon->flags & 2 : weapon->flags & 1) {
            if (!g_frontendScreenStatus.settings.local && !owned) player->next = pickup->index;
        }
    }
    label = pickup->label; sound = pickup->sound; event = pickup->event;
    if (player->ui) {
        Gsky_StartFade(player->ui, 128, 50, 50, 75, 0, 0, 2);
        if (label != 0) Camera_PostScreenMessage(&g_frontendScreenStatus, player->ui, label[MENU_LANGUAGE]);
    }
    if (sound) SoundElement_PlaySoundAtPosition(sound, player->position, 0, -1);
    if (event) SoundElement_PlayDialogGroup(event);
    if (!changed) Player_AddAmmo(player, pickup->ammoType, pickup->ammoAmount);
    return 1;
}
