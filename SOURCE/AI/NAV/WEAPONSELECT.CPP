#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/NAVIGATION_ACTOR_SEARCH_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/S2.H"
#include "GAME/WEAPONSELECT.H"
#include "COMMON/SELF.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "DATA/REST_SOURCE_RECORDS.H"

/* PLAYERSTATE.CPP */
struct AiController; s32 Scaled_SetBehaviourState(struct AiController *controller, s32 behaviourId);
s32 Scaled_MatchesBehaviorStateFilter(void *);
s32 Scaled_IsBehaviorStateEight(void *);
f32 Scaled_GetScaledAggression(void *);
s32 Nav_ShouldSeekUnclaimedTeamMarker(void *);
s32 Nav_GetWeaponPickupGoalClass(void *);
s32 Playerai_GetWeaponClassId(void *, s16);
s32 Playerai_GetWeaponAmmo(void *, s16);
s32 Player_GetMaxHealth(void *);
s32 Player_GetAmmoCapacity(void *, s32, s32);
extern CGameStatus g_matchRoundCounters;

/* Choose the next AI state from game objectives, supplies and the current target. */
s32 Nav_SelectPlayerState(AiController *controller) {
    s32 nextState;
    s32 health;
    s32 maxHealth;
    s32 ammoCount;
    s32 capacity;
    s32 ammoType;
    s32 healthThreshold;
    s32 state;
    f32 healthPercent;
    f32 ammoPercent;
    s32 ammo0;
    s32 ammo1;
    s32 ammo2;
    Player *carrier;
    CGameStatus *gameStatus;

    health = controller->player->health >> 8;
    maxHealth = Player_GetMaxHealth(controller->player) >> 8;
    healthPercent = (f32)health / (f32)maxHealth * 100.0f;
    ammoCount = Playerai_GetWeaponAmmo(controller->player, controller->player->selectedAction);
    ammoType = Playerai_GetWeaponClassId(controller->player, controller->player->selectedAction);
    capacity = Player_GetAmmoCapacity(controller->player, ammoType, 1);
    if (capacity != 0 && ammoCount != -1) {
        ammoPercent = (f32)ammoCount / (f32)capacity * 100.0f;
    } else {
        ammoPercent = 100.0f;
    }
    ammo0 = controller->player->ammo[0];
    ammo1 = controller->player->ammo[1];
    ammo2 = controller->player->ammo[2];
    carrier = Playerai_FindPlayerWithMarker((char *)&g_playerViewRenderContext);
    if (carrier != 0 && g_playerViewRenderContext.game.counters.m_bCTFOn != 0) {
        if (carrier == controller->player) {
            nextState = 10;
            Scaled_SetBehaviourState(controller, nextState);
            return 1;
        }
        if (controller->target != 0) {
            nextState = 1;
            Scaled_SetBehaviourState(controller, nextState);
            return 1;
        }
    }
    gameStatus = &g_matchRoundCounters;
    if (gameStatus->m_bFragTagOn != 0 && controller->player->profile->bonus != 0) {
        if (gameStatus->m_FragTagFlipTimer > 0) {
            if (controller->state != 2) {
                Scaled_SetBehaviourState(controller, 2);
                return controller->behaviorStateWordB = controller->behaviorStateWordA = 1;
            }
            return 1;
        }
        nextState = 11;
        Scaled_SetBehaviourState(controller, nextState);
        return 1;
    }
    healthThreshold = (s32)((1.0f - Scaled_GetScaledAggression(controller)) * 80.0f);
    if (g_gameSettings.counters.enabled != 0 && controller->player->profile->enabled != 0) {
        healthThreshold = 0;
    }
    if (Scaled_IsBehaviorStateEight(controller) == 0 && healthPercent < (f32)healthThreshold) {
        controller->routeState = 1;
        nextState = 8;
        Scaled_SetBehaviourState(controller, nextState);
        return 1;
    }
    if (Scaled_IsBehaviorStateEight(controller) == 0 && ammoPercent < 10.0f) {
        controller->routeState = Nav_GetWeaponPickupGoalClass(controller);
        nextState = 8;
        Scaled_SetBehaviourState(controller, nextState);
        return 1;
    }
    state = controller->state;
    if ((state == 3 || state == 4 || state == 13) && ammo0 < 10 && ammo1 < 10 && ammo2 <= 0) {
        controller->routeState = 4;
        nextState = 8;
        Scaled_SetBehaviourState(controller, nextState);
        return 1;
    }
    if (Scaled_MatchesBehaviorStateFilter(controller) != 0 && controller->target == 0) {
        nextState = 2;
        Scaled_SetBehaviourState(controller, nextState);
        return 1;
    }
    if (Nav_ShouldSeekUnclaimedTeamMarker(controller) != 0 && (state = controller->state) != 9) {
        if (state == 1 || state == 2) {
            nextState = 9;
            Scaled_SetBehaviourState(controller, nextState);
            return 1;
        }
    } else if (Scaled_IsBehaviorStateEight(controller) != 0 && (f32)healthThreshold < healthPercent && 10.0f < ammoPercent) {
        nextState = 2;
        Scaled_SetBehaviourState(controller, nextState);
        return 1;
    } else if (Scaled_MatchesBehaviorStateFilter(controller) == 0 && Scaled_IsBehaviorStateEight(controller) == 0 && controller->target != 0) {
        if (controller->player->profile->enabled != 0) {
            if (controller->player->profile->character == 12) {
                Scaled_SetBehaviourState(controller, 13);
                return 1;
            }
        }
        Scaled_SetBehaviourState(controller, 1);
        return 1;
    }
    return 1;

}

/* WEAPONSELECT.CPP */
/* Picks a computer player's next weapon: in state 14 defers to Nav_RequestRandomArmedWeapon; otherwise gathers the loaded weapons it carries (slot kinds from 0x4C3, with ammunition and allowed by Nav_IsWeaponAllowed_de), filtering the specials by the record's weapon mode (mode 0 or an unknown mode, reset to 0, skips class-1 weapons and treats kind 6 as 5; modes 0 and 1 skip class-2 weapons; mode 2 allows all), and unless it already holds one of them and should keep it (holding kind 4 in gear 2, Particle_CountOwnerListOneEffects reporting a threat, or a 79 percent roll through Nav_RollRandom_de) chooses one at random into 0x770, clearing the brain's switch timer at 0x2E4 when it changes. */

extern WeaponInfo *g_weaponInfoByType[];

extern char g_actorParticleEffectSystem[];

extern s32 Playerai_PlayerHasAmmoForWeapon(SharedPlayer *, s32);

extern s32 Particle_CountOwnerListOneEffects(char *, SharedPlayer *);

void Nav_SelectAvailableWeapon(WeaponSelectBrain *brain, s32 *ammo) {
    s32 choices[8];
    u32 count;
    s32 holding;
    u32 i;
    s32 weapon;
    s32 pick;

    if (brain->player->views1450.view1450_1.computer == 0) {
        return;
    }
    if (brain->player->views5DC.view5E0_9.state == 14) {
        Nav_RequestRandomArmedWeapon(brain);
        return;
    }
    holding = count = 0;
    for (i = count; i < 8; i++) {
        weapon = brain->player->views18.view18_2.model->slots[i];
        weapon -= 1219;
        if (weapon < 0 || ammo[i] == 0 || Playerai_PlayerHasAmmoForWeapon(brain->player, weapon) == 0) {
            continue;
        }
        if ((u32)weapon >= 2) {
            switch (brain->player->views5D8.view5D8_1.record->difficulty) {
            case 1:
                goto second;
            case 0:
                break;
            case 2:
                goto add;
            default:
                brain->player->views5D8.view5D8_1.record->difficulty = 0;
                break;
            }
            if (*g_weaponInfoByType[weapon]->weaponClass == 1) {
                continue;
            }
            if (weapon == 6) {
                weapon = 5;
            }
        second:
            if (*g_weaponInfoByType[weapon]->weaponClass == 2) {
                continue;
            }
        }
    add:
        choices[count++] = weapon;
        if (weapon == brain->player->views5E8.view62E_14.weapon) {
            holding = 1;
        }
    }
    if (holding) {
        if (brain->player->views5E8.view62E_14.weapon == 4 && brain->player->views1C.view594_39.gear == 2) {
            return;
        }
        if (Particle_CountOwnerListOneEffects(g_actorParticleEffectSystem, brain->player) > 0) {
            return;
        }
        if (Graphu64_NextRandom() % 100 >= 21) {
            return;
        }
    }
    if (count == 0) {
        return;
    }
    pick = choices[Graphu64_NextRandom() % count];
    brain->player->views5E8.view770_92.nextWeapon = pick;
    if (pick != brain->player->views5E8.view62E_14.weapon) {
        brain->switchTimer = 0;
    }
}

int Nav_SelectWeaponFromFirstAmmoGroup(void *controller) {
    WeaponSelectBrain *brain = controller;
    char *ammo = brain->player->views18.view18_1.track;
    Nav_SelectAvailableWeapon(brain, ammo + ((char *)&((WeaponSelectionDefinition *)0)->ammoGroups[0] - (char *)0));
    return 1;
}

int Nav_SelectWeaponFromSecondAmmoGroup(void *controller) {
    WeaponSelectBrain *brain = controller;
    char *ammo = brain->player->views18.view18_1.track;
    Nav_SelectAvailableWeapon(brain, ammo + ((char *)&((WeaponSelectionDefinition *)0)->ammoGroups[1] - (char *)0));
    return 1;
}

int Nav_SelectWeaponFromThirdAmmoGroup(void *controller) {
    WeaponSelectBrain *brain = controller;
    char *ammo = brain->player->views18.view18_1.track;
    Nav_SelectAvailableWeapon(brain, ammo + ((char *)&((WeaponSelectionDefinition *)0)->ammoGroups[2] - (char *)0));
    return 1;
}

int Nav_SelectSecondAmmoGroupVariantOne(void *controller) {
    WeaponSelectBrain *brain = controller;
    char *ammo = brain->player->views18.view18_1.track;
    Nav_SelectAvailableWeapon(brain, ammo + ((char *)&((WeaponSelectionDefinition *)0)->ammoGroups[1] - (char *)0));
    return 1;
}

int Nav_SelectSecondAmmoGroupVariantTwo(void *controller) {
    WeaponSelectBrain *brain = controller;
    char *ammo = brain->player->views18.view18_1.track;
    Nav_SelectAvailableWeapon(brain, ammo + ((char *)&((WeaponSelectionDefinition *)0)->ammoGroups[1] - (char *)0));
    return 1;
}

/* RANDOMWEAPON.CPP */
void Nav_RequestRandomArmedWeapon(void *brain) {
    AiController *controller = brain;
    s32 chosenWeapon;

    if ((Graphu64_NextRandom() % 100) < 21) {
        do {
            chosenWeapon = Weapon_PickRandomArmedWeapon(controller->player);
        } while (chosenWeapon >= 16);
        ((Shared_ActorView *)controller->player)->nextWeapon = chosenWeapon;
        if (chosenWeapon != ((Shared_ActorView *)controller->player)->selectedAction) {
            controller->actionDelay = 0;
        }
    }
}

/* ACTION_MIXED_CONSTANT_FRAGMENTS__WEAPONSELECT.CPP */
/* 800C6B74_2.CPP */

/* 800C6E84_14.CPP */
#if defined(VERSION_EU_X)
unsigned int k_ActionMixedConstantFragmentsEncodedWordsBlock1[2] = {
    0x3C5F0B72, 0x3FE52EDF,
};
#endif

#if defined(VERSION_EU)
unsigned int k_ActionMixedConstantFragmentsEncodedWords[2] = {
    0x01014824, 0x40896000,
};
#endif

/* NAV_SELECTPLAYERSTATE.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C7028 */
unsigned int g_NavSelectplayerstateEncodedWords[2] = {
    0x3F800000, 0x3FE52EDF,
};
#endif

/* NAV_CONSTANTS__WEAPONSELECT.CPP */
/* 800C1CF4.CPP */

/* 800C1E68.CPP */
#if defined(VERSION_US)
char s_OvldatELoaderRText[8] =
    "eLoaderR";
#endif
/* 800C209C.CPP */
