#include "COMMON/ENTRYRECATE.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "COMMON/VIEWFLAGS.H"
#include "TYPES.H"
#include "PICKUP.H"
#include "ENGINE/AUDIO/CHANNEL.H"
#include "include_asm.h"
#include "COMMON/RESPONSE.H"

/* 802ABDBC_16.CPP */

extern void Player_AddAmmo(void *, s16, s16);

/** Apply a three-channel effect descriptor and its optional payloads. */
s32 Pickup_ApplyAmmoBundle(ActorPickupCanCollect *player, MultiChannelItemEffect *ammoBundle) {
    void *resource;
    s32 sound;
    s32 callback;

    Player_AddAmmo(player, 0, ammoBundle->effect.index);
    Player_AddAmmo(player, 1, ammoBundle->effect.argument);
    Player_AddAmmo(player, 2, ammoBundle->third);

    resource = ammoBundle->effect.resource;
    sound = ammoBundle->effect.sound;
    callback = ammoBundle->effect.callback;
    if (player->owner != 0) {
        Gsky_StartFade(player->owner,
                      128, 50, 50, 75, 0, 0, 2);
        if (resource != 0) {
            Camera_PostScreenMessage(&g_frontendScreenStatus,
                          player->owner,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                          ((void **)resource)[g_languageIndex]);
#else
                          *(void **)resource);
#endif
        }
    }
    if (sound != 0) {
        SoundElement_PlaySoundAtPosition(sound,
                      player->position, 0, -1);
    }
    if (callback != 0) {
        SoundElement_PlayDialogGroup(callback);
    }
    return 1;
}

void *Pickup_FindBonusEntry(s32 bonusId) {
    char *v1;
    s32 i;
    Shared_PickupAmmoDefinition *record;

    v1 = (char *)g_pickupAmmoDefinitions;
    i = 15;
    do {
        record = (Shared_PickupAmmoDefinition *)v1;
        i -= 1;
        if (record->id != bonusId) {
            v1 += sizeof(PickupDefinition24);
        } else {
            return v1;
        }
    } while (i != -1);
    return 0;
}

/** Apply optional resource, sound, and callback effects for an actor. */
void Pickup_ShowFeedback(void *recipientActor, void *resource, s32 sound, s32 callback) {
    if (((Shared_ActorView *)recipientActor)->message != 0) {
        Gsky_StartFade(((Shared_ActorView *)recipientActor)->message,
                      128, 50, 50, 75, 0, 0, 2);
        if (resource != 0) {
            Camera_PostScreenMessage(&g_frontendScreenStatus,
                          ((Shared_ActorView *)recipientActor)->message,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                          ((void **)resource)[g_frontendScreenStatus.settings.language]);
#else
                          *(void **)resource);
#endif
        }
    }
    if (sound != 0) {
        SoundElement_PlaySoundAtPosition((s16)sound,
                      ((LevelActor *)recipientActor)->position0, 0, -1);
    }
    if (callback != 0) {
        SoundElement_PlayDialogGroup(callback);
    }
}

s32 Pickup_ToggleEffectAndFlash(Shared_ActorView *actorView) {
    f32 value;
    f32 input;
    f32 threshold;
    u32 converted;

    actorView->pickupEffectToggle =
        actorView->pickupEffectToggle == 0;
    if (actorView->message != 0) {
        input = k_pickupBonusSelectionConstants;
        ((RacerViewport *)actorView->message)->pad124 = 0;
        value = Graphu64_RandomFloat(input);
        threshold = (&k_pickupBonusSelectionConstants)[1];
        if (!(threshold <= value)) {
            converted = (s32)value;
        } else {
            converted = (s32)(value - threshold) | 0x80000000;
        }
        Gsky_StartFade(actorView->message, 0xFF, 0xFF, 0xFF,
                      0xFF, (u8)converted, 1, 0);
    }
    return 1;
}

/* PickupHandleItemUpdateUnit.CPP */
/** Return the one status used by callers. */
int Pickup_HandleItemUpdate(void) {
    return 1;
}


