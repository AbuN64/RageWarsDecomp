#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "ENGINE/AUDIO/CHANNEL.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/WORLD.H"
#include "COMMON/VIEWFLAGS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ENTRYRECATE.H"
#include "PICKUP.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

void *Pickup_FindPowerupEntry(s32 itemId) {
    char *v1;
    s32 i;

    v1 = &g_pickupPowerupDefinitions;
    i = 3;
    do {
        i -= 1;
        if (((struct PowerupIdEntry *)(v1))->id != itemId) {
            v1 += sizeof(PickupDefinition24);
        } else {
            return v1;
        }
    } while (i != -1);
    return 0;
}





void *Pickup_FindAmmoEntry(s32 pickupId) {
    char *v1;
    s32 i;

    v1 = &g_pickupWeaponDefinitions;
    i = 5;
    do {
        i -= 1;
        if (((struct PowerupIdEntry *)(v1))->id != pickupId) {
            v1 += sizeof(AmmoPickupDefinition);
        } else {
            return v1;
        }
    } while (i != -1);
    return 0;
}





void *Pickup_FindHealthEntry(s32 pickupId) {
    char *v1;
    s32 i;

    v1 = &g_pickupHealthDefinitions;
    i = 7;
    do {
        i -= 1;
        if (((struct PowerupIdEntry *)(v1))->id != pickupId) {
            v1 += sizeof(PickupDefinition24);
        } else {
            return v1;
        }
    } while (i != -1);
    return 0;
}





void *Pickup_FindSingleEntry(s32 pickupId) {
    char *v1;
    s32 i;

    v1 = &g_pickupSingleDefinitions;
    i = 1;
    do {
        i -= 1;
        if (((struct PowerupIdEntry *)(v1))->id != pickupId) {
            v1 += sizeof(AmmoPickupDefinition);
        } else {
            return v1;
        }
    } while (i != -1);
    return 0;
}





void *Pickup_FindTargetedEntry(s32 pickupId) {
    char *v1;
    s32 i;

    v1 = &g_pickupTargetedDefinitions;
    i = 15;
    do {
        i -= 1;
        if (((struct PowerupIdEntry *)(v1))->id != pickupId) {
            v1 += sizeof(PowerupIdEntry);
        } else {
            return v1;
        }
    } while (i != -1);
    return 0;
}





void *Pickup_FindSpecialEntry(s32 pickupId) {
    char *v1;
    s32 i;

    v1 = &g_pickupSpecialDefinitions;
    i = 2;
    do {
        i -= 1;
        if (((struct PowerupIdEntry *)(v1))->id != pickupId) {
            v1 += sizeof(PowerupIdEntry);
        } else {
            return v1;
        }
    } while (i != -1);
    return 0;
}

extern int InstHdr_GetActorType(void *prop);
extern s32 Pickup_DispatchHandler(void *actor, void *target, s32 pickupId);
extern void SetN64_RecycleGlobalEffectNode(void *node);
extern void Scene_SetLevelRecordStateBit(void *world, void *levelBitRecord, s32 recordIndex);
extern void Link_DispatchObjectLinks(s32 triggerKey, s32 triggerFlags, void *actor);





void Pickup_TryCollectActor(void *actor, void *pickup) {
    u16 collectedFlags;
    u16 pickupFlags;

    pickupFlags = ((struct Shared_ProjectileView *)(pickup))->flags;
    if (pickupFlags & 8) {
        if (((struct Shared_ProjectileView *)(pickup))->stateFlags & 1) {
            goto block_4;
        }
    } else if (!(pickupFlags & 1)) {
block_4:
        if (Pickup_DispatchHandler(actor, pickup, InstHdr_GetActorType(pickup)) != 0) {
            collectedFlags = ((struct Shared_ProjectileView *)(pickup))->flags | 1;
            ((struct Shared_ProjectileView *)(pickup))->flags = collectedFlags;
            if (collectedFlags & 8) {
                SetN64_RecycleGlobalEffectNode(pickup);
                return;
            }
            Scene_SetLevelRecordStateBit(&g_world, pickup, 1);
            Link_DispatchObjectLinks(((struct Shared_ProjectileView *)(pickup))->source, 0x400, actor);
        }
    }
}

#include "COMMON/MENU_MATCH_GLOBALS.H"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif
extern void Player_AddAmmo(void *, s16, s16);
extern s32 SoundElement_PlaySoundAtPosition(s16 track, CVector3 soundPosition, s32 position, s32 ownerId);


/** Apply an effect descriptor's optional setup, resource, sound, and callback. */
s32 Pickup_ApplyAmmo(void *player, void *pickupEntry) {
    void *resource;
    s32 sound;
    s32 callback;
    if (((struct PowerupIdEntry *)(pickupEntry))->index != -1) {
        Player_AddAmmo(player, ((struct PowerupIdEntry *)(pickupEntry))->index,
                      ((struct PowerupIdEntry *)(pickupEntry))->argument);
    }

    resource = ((PowerupIdEntry *)pickupEntry)->resource;
    sound = ((struct PowerupIdEntry *)(pickupEntry))->sound;
    callback = ((struct PowerupIdEntry *)(pickupEntry))->callback;
    if (((struct ActorPickupCanCollect *)(player))->owner != 0) {
        Gsky_StartFade(((struct ActorPickupCanCollect *)(player))->owner,
                      128, 50, 50, 75, 0, 0, 2);
        if (resource != 0) {
            Camera_PostScreenMessage(&g_frontendScreenStatus,
                          ((struct ActorPickupCanCollect *)(player))->owner,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                          ((void **)resource)[g_languageIndex]);
#else
                          *(void **)resource);
#endif
        }
    }
    if (sound != 0) {
        SoundElement_PlaySoundAtPosition(sound,
                      ((ActorPickupCanCollect *)player)->position, 0, -1);
    }
    if (callback != 0) {
        SoundElement_PlayDialogGroup(callback);
    }
    return 1;
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif
extern s32 Player_GetMaxHealth(void *player);


/** Advance a timed effect and apply its optional resource, sound, and callback. */
s32 Pickup_ApplyHealth(void *player, void *pickup) {
    s32 result;
    void *resource;
    s32 sound;
    s32 callback;

    result = 0;
    if (((struct ActorPickupCanCollect *)(player))->count > 0) {
        s32 limit;

        ((struct ActorPickupCanCollect *)(player))->count +=
            ((struct TimedItemEffect *)(pickup))->amount << 8;
        limit = Player_GetMaxHealth(player);
        if (((struct ActorPickupCanCollect *)(player))->count < limit) {
            limit = ((struct ActorPickupCanCollect *)(player))->count;
        }
        result = 1;
        ((struct ActorPickupCanCollect *)(player))->count = limit;
        ((struct ActorPickupCanCollect *)(player))->active = limit;
    }

    if (result != 0) {
        resource = ((PowerupIdEntry *)pickup)->resource;
        sound = ((struct TimedItemEffect *)(pickup))->sound;
        callback = ((struct TimedItemEffect *)(pickup))->callback;
        if (((struct ActorPickupCanCollect *)(player))->owner != 0) {
            Gsky_StartFade(((struct ActorPickupCanCollect *)(player))->owner,
                          128, 50, 50, 75, 0, 0, 2);
            if (resource != 0) {
                Camera_PostScreenMessage(&g_frontendScreenStatus,
                              ((struct ActorPickupCanCollect *)(player))->owner,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                          ((void **)resource)[g_languageIndex]);
#else
                          *(void **)resource);
#endif
            }
        }
        if (sound != 0) {
            SoundElement_PlaySoundAtPosition(sound,
                          ((ActorPickupCanCollect *)player)->position, 0, -1);
        }
        if (callback != 0) {
            SoundElement_PlayDialogGroup(callback);
        }
    }
    return result;
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif




/** Apply an accumulating effect descriptor and its optional payloads. */
s32 Pickup_ApplyLifePoints(void *player, void *pickup) {
    void *resource;
    s32 sound;
    s32 callback;
    s32 amount;

    amount = ((struct ActorPickupCanCollect *)(player))->fraction +
             (u16)((struct PowerupIdEntry *)(pickup))->index;
    ((struct ActorPickupCanCollect *)(player))->fraction = amount;
    if ((s16)amount >= 100) {
        ((struct ActorPickupCanCollect *)(player))->fraction = amount - 100;
        if (((struct ActorPickupCanCollect *)(player))->lives < 9) {
            ((struct ActorPickupCanCollect *)(player))->lives =
                (u16)((struct ActorPickupCanCollect *)(player))->lives + 1;
        }
    }

    resource = ((PowerupIdEntry *)pickup)->resource;
    sound = ((struct PowerupIdEntry *)(pickup))->sound;
    callback = ((struct PowerupIdEntry *)(pickup))->callback;
    if (((struct ActorPickupCanCollect *)(player))->owner != 0) {
        Gsky_StartFade(((struct ActorPickupCanCollect *)(player))->owner,
                      128, 50, 50, 75, 0, 0, 2);
        if (resource != 0) {
            Camera_PostScreenMessage(&g_frontendScreenStatus,
                          ((struct ActorPickupCanCollect *)(player))->owner,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                          ((void **)resource)[g_languageIndex]);
#else
                          *(void **)resource);
#endif
        }
    }
    if (sound != 0) {
        SoundElement_PlaySoundAtPosition(sound,
                      ((ActorPickupCanCollect *)player)->position, 0, -1);
    }
    if (callback != 0) {
        SoundElement_PlayDialogGroup(callback);
    }
    return 1;
}

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "TYPES.H"

extern void addrLow_Pickup_ToggleEffectAndFlash(void);
extern void addrLow_Pickup_HandleItemUpdate(void);
#include "COMMON/MENU_MATCH_GLOBALS.H"

typedef struct PickupPowerupDefinitionView PickupPowerupDefinitionView;
typedef struct PickupPowerupPayloadView PickupPowerupPayloadView;
typedef struct ActivationSlot ActivationSlot;
typedef struct ActivationActor ActivationActor;
struct PickupPowerupDefinitionView {
    char pad0[0x18];
    PickupPowerupPayloadView *payloadRecord;
};
typedef struct EffectAmount { char pad[0xC]; f32 amount; } EffectAmount;
struct PickupPowerupPayloadView { char pad[0x14]; EffectAmount payload; };
struct ActivationSlot {
    void **resource;
    u16 pickupId;
    char pad4[0x6 - 0x4 - sizeof(u16)];
    s16 soundId;
    char pad6[0x8 - 0x6 - sizeof(s16)];
    s16 dialogGroupId;
};
struct ActivationActor {
    char pad0[0x8];
    s32 positionX;
    char pad8[0xC - 0x8 - sizeof(s32)];
    s32 positionY;
    char padC[0x10 - 0xC - sizeof(s32)];
    s32 positionZ;
    char pad10[0x5DC - 0x10 - sizeof(s32)];
    void* messageCamera;
    char pad5DC[0x670 - 0x5DC - sizeof(void*)];
    f32 powerupTimerOne;
    char pad670[0x674 - 0x670 - sizeof(f32)];
    f32 powerupTimerTwo;
    char pad674[0x678 - 0x674 - sizeof(f32)];
    f32 powerupAmount;
    char pad678[0xD40 - 0x678 - sizeof(f32)];
    char itemMenu;
};

/** Apply a scripted effect command and its optional sound callbacks. */
s32 Pickup_ApplyPowerup(ActivationActor *player, ActivationSlot *pickup, PickupPowerupDefinitionView *effectDefinition) {
    void **resource;
    EffectAmount *state_value;
    s32 sound;
    s32 callback;
    s16 command;

    state_value = &effectDefinition->payloadRecord->payload;
    command = pickup->pickupId - 1800;
    switch (command) {
    case 0:
        player->powerupTimerOne = 120.0f;
        break;
    case 1:
        player->powerupTimerTwo = 120.0f;
        break;
    case 2:
    case 3:
        player->powerupAmount += state_value->amount;
        break;
    case 7:
        ItemMenu_SetEntry(&player->itemMenu, 1, 0, 2045,
                       0, 0, 0, addrLow_Pickup_ToggleEffectAndFlash, addrLow_Pickup_HandleItemUpdate);
        break;

    default: break;
    }

    resource = pickup->resource;
    sound = pickup->soundId;
    callback = pickup->dialogGroupId;
    if (player->messageCamera != 0) {
        Gsky_StartFade(player->messageCamera,
                      128, 50, 50, 75, 0, 0, 2);
        if (resource != 0) {
            Camera_PostScreenMessage(&g_frontendScreenStatus,
                          player->messageCamera,
                          *resource);
        }
    }
    if (sound != 0) {
        SoundElement_PlaySoundAtPosition(sound,
                      *(CVector3 *)&player->positionX, 0, -1);
    }
    if (callback != 0) {
        SoundElement_PlayDialogGroup(callback);
    }
    return 1;
}
#endif
