#include "COMMON/WORLD.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/ROUND_STATE_VARIANTS.H"

/* Player state, projectiles, effects and linked-actor transitions. */
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/VECTOR4F.H"
#include "RENDER/PLAYER_CONTROLLER_RESET_VIEWS.H"
#include "COMMON/RESULTS.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "RENDER/PLAYER_SPAWN_PLACEMENT.H"
/* Apply player transitions, regional control gates, and localized linked-actor notifications. */






extern const Shared_HeightBonuses g_playerDeathHeightOffsets;
extern const f32 g_playerDeathMotionCenter;
extern const f32 g_playerDeathMovingSpeed;
extern s32 g_playerDeathEffectModelIds[2];



                                                  /* size = 0x18 */




void *Portal_GetGraphPoint(void *, s32);
s32 Portal_FindNearestPointIndex(void *, void *);
s32 Player_SetPlayerState(void *, void *, s32);
void *Gsky_PostScaledScreenMessage(void *, void *, void *, f32); CQuatern Gobjinst_BuildActorAimQuaternion(char *);
s32 Gobjinst_GetModelRenderMode(void *);
void InstHdr_CopyActorPositionAndModel(void *, Triple, void *, s32 *, s32, s32); /* extern */
s32 SoundElement_PlaySoundAtPosition(s16, CVector3, s32, s32); /* extern */
void Control_SetProfileMode(void *, s32);
void Link_DispatchActorLinks(void *, s32, void *);
void Link_DispatchObjectLinks(s32, s32, void *);
s32 Particle_SpawnEffectGroup(void *, void *, void *, s32 *, s32, s32, CVector3, CQuatern, CVector3, CVector3 *, s32, s32); /* extern */
void Particle_ReleaseOwnerListTwoEffects(void *, s32);
s32 Scene_FindModelIdIndex(struct Shared_World *, s32);
void Scene_SetLevelRecordStateBit(void *, void *, s32);
void *SetN64_SpawnModelEffect(void *, s32 *, s32, CVector3, CVector3, s32, f32); /* extern */
struct EffectPoolNode;
void SetN64_RecycleGlobalEffectNode(struct EffectPoolNode *);
s32 XPlus_NextRandomInteger(void);
s32 Player_ResetPlayerForRound(void *, s8, s32);         /* extern */
void Player_PlacePlayerForRound(void *);
void Player_ReleaseObjectHandles(void *);


extern s32 g_actorParticleEffectSystem;


extern s32 g_navigationGraph;
extern struct Shared_GlobalRuntimeState g_transientPlayerList;










 /* unable to generate initializer: non-zero padding; const */








void Playerai_HandlePlayerDeath(struct Shared_ActorView *player, void *attacker, s32 damageFlags, s32 state) {
    CVector3 spawnPosition;
    struct CVector3_t spawnVector;
    struct CVector3_t motionVector;
    struct Shared_GlobalPlayers *playersGlobal;
    struct Shared_GlobalFlowState *flow;
    struct Shared_GlobalFlowState *laterFlow;
    struct GameLocalizationState *localization;
    s32 *messageContext;
    CQuatern motionOutput;
    s32 spawnProbeResult;

    s8 *settingsBase;
    struct Shared_PlayerSettingsRecord *playerSettingsRecord;
    s16 firstAmmoCount;
    s16 secondAmmoCount;
    s16 thirdAmmoCount;
    s32 previousAction;
    s16 deathSound;
    s16 unusedShort;
    void *resetMessageTarget;
    void *releaseMessageTarget;
    s32 deathEffectFrame;
    void *spawnedAmmoPickup;
    s32 unusedDeathWord;
    s32 firstAmmoRandom;
    s32 firstAmmoQuotient;
    s32 secondAmmoRandom;
    s32 secondAmmoQuotient;
    s32 thirdAmmoRandom;
    s32 thirdAmmoQuotient;
    s32 unusedEffectWord;
    s32 motionRandomX;
    s32 motionRandomY;
    s32 motionRandomZ;
    s32 firstAmmoDrop;
    s32 secondAmmoDrop;
    s32 thirdAmmoDrop;
    s32 unusedPickupWord;
    s32 ammoPickupType;
    s32 deathEffectFlags;
    s32 i;

    s32 loopLimit;
    s32 hasAmmoDrop;
    s32 playerArrayOffset;
    s32 signedMotionRandomX;
    s32 signedMotionRandomY;
    s32 signedMotionRandomZ;
    s32 movingAtDeath;
    struct Shared_PickupAmmoDefinition *thirdAmmoDropRecord;
    struct Shared_PickupAmmoDefinition *firstAmmoDropRecord;
    struct Shared_PickupAmmoDefinition *secondAmmoDropRecord;
    u16 ammoDropActorKind;
    u16 deathEffectActorKind;
    u32 ammoPickupMode;
    void *retiredAmmoPickup;
    void *roundPlayer;
    void *nearestSpawnPoint;
    void *roundPlayerModel;
    void *existingAmmoPickup;
    void *resetMessageActor;
    void *childActor;

    Control_SetProfileMode(((struct Shared_ActorView *)player)->controller, 0);
    if (((struct Shared_ActorView *)player)->action == 39) {
        Player_SetPlayerState(player, attacker, 2);
    }
    ((struct Shared_ActorView *)player)->reservedWord1218 = 0;
    Link_DispatchActorLinks(attacker, 1, attacker);
    Player_ReleaseObjectHandles(player);
    Playerai_ResetDamageTimers((s32)player);
    ((struct Shared_ActorView *)player)->stun = 0;
    ((struct Shared_ActorView *)player)->marker.time = 0;
    Particle_ReleaseOwnerListTwoEffects(&g_actorParticleEffectSystem, (s32)player);
    flow = &g_transientPlayerList.flow;
    if ((flow->active != 0)
        && gameplayTransitionEnabled(player->controls->germanActive)
        && (i = 0, (((struct Shared_ActorView *)player)->controls->mode == 14))) {
        flow->count = (s32) (flow->count + 1);
        playersGlobal = (struct Shared_GlobalPlayers *)&g_playerViewRenderContext;
        if (playersGlobal->count > 0) {
            settingsBase = (s8 *)&g_playerSettings;
            playerSettingsRecord = (struct Shared_PlayerSettingsRecord *)settingsBase;
            playerArrayOffset = 0;
settings_loop:
            do {
                roundPlayer = playersGlobal->players + playerArrayOffset;
                if (playerSettingsRecord->active != 0) {
                    if (((struct Shared_PlayerSettingsView *)settingsBase)->state == 1) {
                    ((struct Shared_ActorView *)roundPlayer)->actorState = (s32) ((struct Shared_PlayerSettingsView *)settingsBase)->state;
                    Player_ResetPlayerForRound(roundPlayer, playerSettingsRecord->character, 1);
                    roundPlayerModel = ((struct Shared_ActorView *)roundPlayer)->model;
                    ((struct Shared_ModelView *)roundPlayerModel)->flags = (s32) (((struct Shared_ModelView *)roundPlayerModel)->flags & ~4);
                    Actor_RequestActorState(&((struct Shared_ActorView *)roundPlayer)->weapon, &((struct Shared_ActorView *)roundPlayer)->weapon.behaviorFlags, 2);
                    Player_PlacePlayerAtSpawnPoint(roundPlayer, ((struct Shared_PlayerSettingsView *)settingsBase)->effect, 0, 0);
                    List_RemoveIntrusive(playersGlobal->controller, roundPlayer);
                    List_PrependIntrusive(&playersGlobal->effects, roundPlayer);
                    } else if (((struct Shared_PlayerSettingsView *)settingsBase)->state < 3) {
                        Player_PlacePlayerForRound(roundPlayer);
                    }
                }
block_13:
                do {
                    playerSettingsRecord++;
                } while (0);
                loopLimit = playersGlobal->count;
                do {
                    i += 1;
                } while (0);
                playerArrayOffset += 5864;
                if (i < loopLimit) goto settings_loop;
            } while (0);
        }
        if (g_gameSettings.counters.m_nTalsetLives < 3) {
            ((struct Shared_ActorView *)player)->special = 0;
            Player_SetPlayerState(player, attacker, 46);
            return;
        } else {
            goto block_17;
        }
    } else {
block_17:
        if (g_frontendScreenStatus.settings.local != 0) {
            if ((((struct Shared_ActorView *)player)->ammo[0] > 0) || (((struct Shared_ActorView *)player)->ammo[1] > 0) || (((struct Shared_ActorView *)player)->ammo[2] > 0)) {
                ammoPickupMode = ((struct Shared_ActorView *)player)->mode;
                hasAmmoDrop = 0;
                switch (ammoPickupMode) {
case 0:
default:
                    ammoPickupType = ((struct Shared_ActorView *)player)->projectileIndex + 3033;
                    break;
case 1:
                    ammoPickupType = ((struct Shared_ActorView *)player)->projectileIndex + 3035;
                    break;
case 2:
                    ammoPickupType = ((struct Shared_ActorView *)player)->projectileIndex + 3037;
                    break;
case 3:
                    ammoPickupType = ((struct Shared_ActorView *)player)->projectileIndex + 3039;
                    break;
case 4:
                    ammoPickupType = ((struct Shared_ActorView *)player)->projectileIndex + 3041;
                    break;
case 5:
                    ammoPickupType = ((struct Shared_ActorView *)player)->projectileIndex + 3043;
                    break;
case 6:
                    ammoPickupType = ((struct Shared_ActorView *)player)->projectileIndex + 3045;
                    break;
case 7:
                    ammoPickupType = ((struct Shared_ActorView *)player)->projectileIndex + 3047;
                    break;
                }
                Scene_FindModelIdIndex(&g_world, ammoPickupType);
                existingAmmoPickup = ((struct Shared_ActorView *)player)->projectiles[((struct Shared_ActorView *)player)->projectileIndex];
                if (existingAmmoPickup != 0) {
                    ((struct Shared_ProjectileView *)existingAmmoPickup)->flags = (u16) (((struct Shared_ProjectileView *)existingAmmoPickup)->flags | 1);
                    retiredAmmoPickup = ((struct Shared_ActorView *)player)->projectiles[((struct Shared_ActorView *)player)->projectileIndex];
                    if (((struct Shared_ProjectileView *)retiredAmmoPickup)->flags & 8) {
                        SetN64_RecycleGlobalEffectNode(retiredAmmoPickup);
                    } else {
                        Scene_SetLevelRecordStateBit(&g_world, retiredAmmoPickup, 1);
                        Link_DispatchObjectLinks(((struct Shared_ProjectileView *)((struct Shared_ActorView *)player)->projectiles[((struct Shared_ActorView *)player)->projectileIndex])->source, 0x400, player);
                    }
                }
                ammoDropActorKind = ((struct Shared_ActorView *)player)->kind;
                if (ammoDropActorKind == g_playerSpecialModelIds[0]) {
                    hasAmmoDrop = 0;
                } else if (ammoDropActorKind == g_playerSpecialModelIds[1]) {
                    hasAmmoDrop = 0;
                } else {
                    switch (XPlus_NextRandomInteger() % 3) {            /* switch 2; irregular */
                    case 0:                         /* switch 2 */
                        firstAmmoCount = ((struct Shared_ActorView *)player)->ammo[0];
                        firstAmmoDrop = 0;
                        if (firstAmmoCount != 0) {
                            firstAmmoRandom = XPlus_NextRandomInteger();
                            firstAmmoQuotient = firstAmmoRandom / firstAmmoCount;
                            if (firstAmmoCount == 0) {

                            }
                            if ((firstAmmoCount == -1) && (firstAmmoQuotient == 0x80000000)) {

                            }
                            firstAmmoDrop = firstAmmoRandom % firstAmmoCount;
                        }
                        if (firstAmmoDrop != 0) {
                            hasAmmoDrop = 1;
                            firstAmmoDropRecord = &g_pickupAmmoDefinitions[((struct Shared_ActorView *)player)->projectileBase + ((struct Shared_ActorView *)player)->projectileIndex];
                            firstAmmoDropRecord->firstAmmoDrop = (s16) firstAmmoDrop;
                            firstAmmoDropRecord->secondAmmoDrop = 0;
                            firstAmmoDropRecord->thirdAmmoDrop = 0;
                        }
                        break;
                    case 1:                         /* switch 2 */
                        secondAmmoCount = ((struct Shared_ActorView *)player)->ammo[1];
                        secondAmmoDrop = 0;
                        if (secondAmmoCount != 0) {
                            secondAmmoRandom = XPlus_NextRandomInteger();
                            secondAmmoQuotient = secondAmmoRandom / secondAmmoCount;
                            if (secondAmmoCount == 0) {

                            }
                            if ((secondAmmoCount == -1) && (secondAmmoQuotient == 0x80000000)) {

                            }
                            secondAmmoDrop = secondAmmoRandom % secondAmmoCount;
                        }
                        if (secondAmmoDrop != 0) {
                            hasAmmoDrop = 1;
                            secondAmmoDropRecord = &g_pickupAmmoDefinitions[((struct Shared_ActorView *)player)->projectileBase + ((struct Shared_ActorView *)player)->projectileIndex];
                            secondAmmoDropRecord->secondAmmoDrop = (s16) secondAmmoDrop;
                            secondAmmoDropRecord->firstAmmoDrop = 0;
                            secondAmmoDropRecord->thirdAmmoDrop = 0;
                        }
                        break;
                    case 2:                         /* switch 2 */
                        thirdAmmoCount = ((struct Shared_ActorView *)player)->ammo[2];
                        thirdAmmoDrop = 0;
                        if (thirdAmmoCount != 0) {
                            thirdAmmoRandom = XPlus_NextRandomInteger();
                            thirdAmmoQuotient = thirdAmmoRandom / thirdAmmoCount;
                            if (thirdAmmoCount == 0) {

                            }
                            if ((thirdAmmoCount == -1) && (thirdAmmoQuotient == 0x80000000)) {

                            }
                            thirdAmmoDrop = thirdAmmoRandom % thirdAmmoCount;
                        }
                        if (thirdAmmoDrop != 0) {
                            hasAmmoDrop = 1;
                            thirdAmmoDropRecord = &g_pickupAmmoDefinitions[((struct Shared_ActorView *)player)->projectileBase + ((struct Shared_ActorView *)player)->projectileIndex];
                            thirdAmmoDropRecord->thirdAmmoDrop = (s16) thirdAmmoDrop;
                            thirdAmmoDropRecord->firstAmmoDrop = 0;
                            thirdAmmoDropRecord->secondAmmoDrop = 0;
                        }
                        break;
                    }
                }
                if (hasAmmoDrop != 0) {
                    nearestSpawnPoint = Portal_GetGraphPoint(&g_navigationGraph, Portal_FindNearestPointIndex(&g_navigationGraph, &player->position.vector));
                    InstHdr_CopyActorPositionAndModel(player, player->position.words, &spawnPosition, &spawnProbeResult, 0, 0);
                    if (nearestSpawnPoint != 0) {
                        spawnPosition = *(CVector3 *)nearestSpawnPoint;
                    }
                    spawnVector.x = 0;
                    spawnVector.y = 0.0f;
                    spawnVector.z = 0;
                    spawnedAmmoPickup = SetN64_SpawnModelEffect(&g_modelEffectPool, 0, ammoPickupType, spawnVector, spawnPosition, 0, 0);
                    if (spawnedAmmoPickup != 0) {
                        spawnPosition.y += g_playerDeathHeightOffsets.spawn;
                        ((struct Shared_ActorView *)player)->projectiles[((struct Shared_ActorView *)player)->projectileIndex] = (void *)spawnedAmmoPickup;
                    }
                } else {
                    ((struct Shared_ActorView *)player)->projectiles[((struct Shared_ActorView *)player)->projectileIndex] = 0;
                }
                ((struct Shared_ActorView *)player)->projectileIndex = (s32) (((struct Shared_ActorView *)player)->projectileIndex == 0);
            }
            if ((((struct Shared_ActorView *)player)->controls->transientFlag != 0) && (laterFlow = &g_transientPlayerList.flow, laterFlow->transition != 0)) {
                if (g_fragTagObjectiveActor != 0) {
                    Actor_RequestActorState(g_fragTagObjectiveActor, ((struct Shared_SpecialObjectView *)g_fragTagObjectiveActor)->segment, 1);
                    ((struct Shared_SpecialObjectView *)g_fragTagObjectiveActor)->reset = 0;
                    laterFlow->reset = 0;
                    SoundElement_PlayFlatSound(720);
                    resetMessageActor = g_transientPlayerList.actorList;
                    if (resetMessageActor != 0) {
                        messageContext = &g_transientPlayerList.messageContext;
                        localization = &g_transientPlayerList.localization;
                        do {
                            resetMessageTarget = ((struct Shared_ActorView *)resetMessageActor)->message;
                            if (resetMessageTarget != 0) {
                                Camera_PostScreenMessage(gameplayMessageContext(messageContext), resetMessageTarget, gameplayResetMessage(localization->language));
                            }
                            resetMessageActor = ((struct Shared_ActorView *)resetMessageActor)->next;
                        } while (resetMessageActor != 0);
                    }
                }
                ((struct Shared_ActorView *)player)->controls->transientFlag = 0U;
                ((struct Shared_ActorView *)player)->controls->resetFlag = 0;
            }
            childActor = g_transientPlayerList.actorList;
            if (childActor != 0) {
                messageContext = &g_transientPlayerList.messageContext;
                localization = &g_transientPlayerList.localization;
                do {
                    if ((childActor != player) && (((struct Shared_ActorView *)childActor)->parent == player)) {
                        releaseMessageTarget = ((struct Shared_ActorView *)childActor)->message;
                        ((struct Shared_ActorView *)childActor)->pending = 0;
                        ((struct Shared_ActorView *)childActor)->parent = 0;
                        if (releaseMessageTarget != 0) {
                            Gsky_PostScaledScreenMessage(gameplayMessageContext(messageContext), releaseMessageTarget, gameplayReleaseMessage(localization->language), 1.0f);
                        }
                    }
                    childActor = ((struct Shared_ActorView *)childActor)->next;
                } while (childActor != 0);
            }
        }
        ((struct Shared_ActorView *)player)->reservedWord1238 = -1;
        ((struct Shared_ActorView *)player)->reservedWord1230 = 0;
        ((struct Shared_ActorView *)player)->reservedWord1234 = 0;
        ((struct Shared_ActorView *)player)->reservedWord1240 = 0;
        ((struct Shared_ActorView *)player)->impulseFlags = (s32) (((struct Shared_ActorView *)player)->impulseFlags & 0xFFFF0000);
        if (damageFlags & 0x4000) {
            if ((u32) (((struct Shared_ActorView *)player)->state - 17) < 2U) {
                ((struct Shared_ActorView *)player)->special = 1;
            }
        }
        if (((struct Shared_ActorView *)player)->special == 0) {
            deathSound = 700;
            if (state != 31) {
                deathSound = Playerai_SelectCharacterSound(player, 5015);
            }
            SoundElement_PlaySoundAtPosition(deathSound, player->position.vector, (s32)&player->position.vector, -1);
        } else {
            SoundElement_PlaySoundAtPosition(2555, player->position.vector, (s32)&player->position.vector, -1);
        }
        SoundElement_PlayFlatSound(530);
        if ((((struct Shared_ActorView *)player)->special != 0) || (deathEffectActorKind = ((struct Shared_ActorView *)player)->kind, (deathEffectActorKind == g_playerDeathEffectModelIds[0])) || (deathEffectActorKind == g_playerDeathEffectModelIds[1])) {
            spawnVector.x = player->position.vector.x;
            spawnVector.y = player->position.vector.y + g_playerDeathHeightOffsets.projectile;
            deathEffectFlags = 1;
            spawnVector.z = player->position.vector.z;
            signedMotionRandomX = XPlus_NextRandomInteger();
            motionRandomX = signedMotionRandomX;
            if (motionRandomX < 0) {
                signedMotionRandomX = motionRandomX + 1023;
            }
            motionVector.x = (f32) (motionRandomX - ((signedMotionRandomX >> 10) << 10)) - g_playerDeathMotionCenter;
            signedMotionRandomY = XPlus_NextRandomInteger();
            motionRandomY = signedMotionRandomY;
            if (motionRandomY < 0) {
                signedMotionRandomY = motionRandomY + 1023;
            }
            motionVector.y = (f32) (motionRandomY - ((signedMotionRandomY >> 10) << 10)) - g_playerDeathMotionCenter;
            signedMotionRandomZ = XPlus_NextRandomInteger();
            motionRandomZ = signedMotionRandomZ;
            if (motionRandomZ < 0) {
                signedMotionRandomZ = motionRandomZ + 1023;
            }
            motionVector.z = (f32) (motionRandomZ - ((signedMotionRandomZ >> 10) << 10)) - g_playerDeathMotionCenter;
            motionOutput = Gobjinst_BuildActorAimQuaternion((char *)player);
            deathEffectFrame = ((struct Shared_ActorView *)player)->frameValue;
            if (Gobjinst_GetModelRenderMode(player) == 5) {
                deathEffectFlags = 3;
            }
            Particle_SpawnEffectGroup(&g_actorParticleEffectSystem, player, player, 0, deathEffectFrame, 100, motionVector, motionOutput, spawnVector, 0, -1, deathEffectFlags);
        }
        if (state != -1) {
            Player_SetPlayerState(player, attacker, state);
            return;
        }
        if (((struct Shared_ActorView *)player)->state != 17) {
            if (((struct Shared_ActorView *)player)->action == 10 && (damageFlags & 0x4000)) {
                Player_SetPlayerState(player, attacker, 42);
                return;
            }
            if (damageFlags & 0x4000) {
                Player_SetPlayerState(player, attacker, 41);
                return;
            }
        }
        movingAtDeath = 1;
        if (!(((struct Shared_ActorView *)player)->speed > g_playerDeathMovingSpeed)) {
            movingAtDeath = 0;
        }
        if (movingAtDeath != 0) {
            Player_SetPlayerState(player, attacker, 28);
            return;
        }
        previousAction = ((struct Shared_ActorView *)player)->action;
        if ((previousAction ^ 0xF) == 0) {
            Player_SetPlayerState(player, attacker, 33);
            return;
        }
        if (previousAction == 9) {
            Player_SetPlayerState(player, attacker, 31);
            return;
        }
        if (previousAction == 10) {
            Player_SetPlayerState(player, attacker, 31);
            return;
        }
        if (previousAction == 11) {
            Player_SetPlayerState(player, attacker, 31);
            return;
        }
        if (previousAction == 12) {
            Player_SetPlayerState(player, attacker, 31);
            return;
        }
        if (damageFlags & 0x1000) {
            Player_SetPlayerState(player, attacker, 31);
            return;
        }
        if (damageFlags & 0x200) {
            Player_SetPlayerState(player, attacker, 25);
            return;
        }
        if ((((struct Shared_ActorView *)player)->state != 17) && (((struct Shared_ActorView *)player)->specialState == 1)) {
            Player_SetPlayerState(player, attacker, 30);
            return;
        }
        if (((struct Shared_ActorView *)player)->specialState == 2) {
            Player_SetPlayerState(player, attacker, 29);
            return;
        }
        Player_SetPlayerState(player, attacker, 22);
        return;
    }
}

#ifndef FIELD
#define FIELD(type, base, off) (*(type *)((char *)(base) + (off)))
#endif
extern f32 g_playerDamageRumbleScale, g_playerDamageRumbleMaximum;
extern unsigned char * g_playerHealthDropMessage;
extern char g_matchRoundCounters[];
extern s32 Playerai_IsRoundEndState(void *);
extern s32 Player_GetMaxHealth(void *);
extern void CScene_StartEventClips(void *, void *, s32, CVector3, f32, f32);
extern void Gsky_SetDamageEffect(void *, s32, s32);
extern void Playerai_AddCappedEventCounter(void *, u16);
/* Applies damage to a player: ignored while the game is paused, the player is protected or the damage
 * source is not allowed; scales the amount by one fifth with armour (0x80C); when the health stays above
 * zero and drops through half of the maximum it respawns the weapon (Player_PlacePlayerAtSpawnPoint); lowers the health
 * (with a flash sound at random), starts the knock-back and the hit effect scaled by the damage, and on death
 * reports the kill through Playerai_HandlePlayerDeath. */
/* Exact for us and us-rev1; de/eu/eu-x add extra checks (0x1450, 0x94) and keep their asm. */
void Player_ApplyPlayerDamage(void *player, void *attacker, s32 amount, s32 damageFlags, s32 kind) {
    s32 oldHealth = FIELD(s32, player, 1508);
    s32 health;
    s32 threshold;
    s32 step;
    s32 found;
    s32 dead;
    s32 wasDead;
    s32 intensity;
    s32 delay;
    s32 roll;
    s32 shifted;
    char *state;
    s32 remaining;
    if (Cinema_IsSequenceActive() != 0 || Playerai_IsRoundEndState(player) != 0 || g_world.frozen != 0) {
        return;
    }
    if ((FIELD(u32, &g_gameSettings, 0) & 1) && kind != 32) {
        return;
    }
    if (FIELD(u16, player, 1616) < 2) {
        return;
    }
    if (FIELD(s32, player, 2060) != 0) {
        amount = amount / 5;
    }
    if (0.0f < FIELD(f32, player, 1648) && kind != 32) {
        return;
    }
    wasDead = FIELD(s32, player, 1508) == 0;
    if (FIELD(u32, player, 4652) & 0x100) {
        health = FIELD(s32, player, 1508) - amount;
        if (health < 0) {
            health = 0;
        }
        step = Player_GetMaxHealth(player);
        found = 0;
        for (threshold = 2; threshold < 5; threshold++) {
            step = step - step / 2;
            if (step < FIELD(s32, player, 1508) && health < step && health > 0) {
                found = 1;
                break;
            }
        }
        if (found != 0) {
            Player_PlacePlayerAtSpawnPoint(player, FIELD(s32, player, 1516), 0, 1);
        }
    }
#if defined(VERSION_DE) || defined(VERSION_EU_X)
    if (FIELD(s32, player, 5200) != 0 && FIELD(s32, state = g_matchRoundCounters, 152) != 0 &&
#else
    state = g_matchRoundCounters;
    if (FIELD(s32, state, 152) != 0 &&
#endif
#if defined(VERSION_DE) || defined(VERSION_EU_X)
        FIELD(u8, FIELD(void *, player, 1496), 148) != 0 &&
#endif
        FIELD(s8, FIELD(void *, player, 1496), 128) == 11 && FIELD(s32, state, 160) > 0) {
        FIELD(s32, state, 160) -= amount >> 8;
        if (FIELD(s32, state, 160) <= 0) {
            FIELD(s32, state, 160) = 0;
            switch (FIELD(u8, FIELD(void *, player, 1496), 147)) {
            case 0:
                FIELD(s32, state, 164) = 75;
                break;
            case 1:
                FIELD(s32, state, 164) = 60;
                break;
            case 2:
                FIELD(s32, state, 164) = 60;
                break;
            }
            Player_SetPlayerState(player, player, 45);
        }
        amount = 0;
    }
    if (FIELD(s32, player, 1508) != 0) {
        FIELD(s32, player, 5064) = FIELD(s32, player, 1508) - amount < -7679;
    }
    remaining = FIELD(s32, player, 1508) - amount;
    if (remaining < 0) {
        remaining = 0;
    }
    FIELD(s32, player, 1508) = remaining;
    roll = Graphu64_NextRandom();
    if ((roll % 2) == 1) {
        if (FIELD(s32, player, 1508) > 0) {
            s32 id = Playerai_SelectCharacterSound((struct Shared_ActorView *)player, 5005);
            if (SoundElement_HasActiveOrPendingSound(id) == 0) {
                SoundElement_PlaySoundAtPosition((s16)id, FIELD(CVector3, player, 8), (s32)((char *)player + 8), -1);
            }
        }
    }
    FIELD(s32, player, 372) = FIELD(s32, player, 1508);
    FIELD(s32, player, 1116) = FIELD(s32, player, 1508);
    dead = FIELD(s32, player, 1508) == 0;
    if (dead != 0) {
        if (wasDead == 0) {
            Playerai_HandlePlayerDeath((struct Shared_ActorView *)player, attacker, damageFlags, kind);
        }
        intensity = 0xFF;
        delay = 12;
    } else {
        shifted = amount >> 8;
        intensity = shifted * 255 / 20;
        intensity = ((intensity > 0xFF ? 0xFF : intensity) < 128) ? 128 : (intensity > 0xFF ? 0xFF : intensity);
        delay = 30;
        if (FIELD(void *, player, 1500) != 0) {
            if (oldHealth > 3840 && FIELD(s32, player, 1508) <= 3840 && g_frontendScreenStatus.settings.local == 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                Camera_PostScreenMessage(&g_frontendScreenStatus, FIELD(void *, player, 1500), ((u8 **)&g_playerHealthDropMessage)[g_frontendScreenStatus.settings.language]);
#else
                Camera_PostScreenMessage(&g_frontendScreenStatus, FIELD(void *, player, 1500), (u8 *)g_playerHealthDropMessage);
#endif
            }
        }
        if ((amount >> 8) != 0) {
            f32 strength;
            CVector3 zero;
            strength = ((f32)(amount >> 8) * g_playerDamageRumbleScale > g_playerDamageRumbleMaximum) ? g_playerDamageRumbleMaximum : (f32)(amount >> 8) * g_playerDamageRumbleScale;
            zero.x = 0;
            zero.y = 0;
            zero.z = 0;
            CScene_StartEventClips(&g_world, (char *)&((ControllerProfile *)FIELD(void *, player, 1688))->effectPool, 17, zero, g_playerHeightScalePair_us, strength);
        }
    }
    if (dead == 0 && FIELD(s16, player, 1616) != 18 && FIELD(void *, player, 1500) != 0) {
        s32 hit;
        if (FIELD(s32, player, 5844) == 0) {
            Gsky_SetDamageEffect(FIELD(void *, player, 1500), intensity & 0xFF, delay);
        }
        hit = amount * 15;
        if (hit > 100) {
            hit = 100;
        }
        Playerai_AddCappedEventCounter(player, (u16)hit);
    }
    return;
}

#include "COMMON/FIELD_VEC_B0.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "TYPES.H"


extern s32 Playerai_IsRoundEndState(void *actorObject);
extern void Player_DrainReserveAndDamage(void *actor, f32 amount, void *damageSource);
extern void Playerai_StartDamageTimer(void *obj, f32 target, f32 rate, void *kind,
                          s32 tag);
extern void Playerai_AddReactionReserve(void *actor, f32 amount, void *source);
extern void Player_StartSourceEffect(void *actor, void *effectSource);

void Playerai_ApplyProjectileStatus(void *playerObject, void *unused1, s32 unused2, void *projectileEvent) {
    Player *actor = playerObject;
    Shared_Particle *event = projectileEvent;
    CGameStatus *audio;
    u16 type;

    if (actor->health == 0) {
        return;
    }
    if (Playerai_IsRoundEndState(actor) != 0) {
        return;
    }
    if (actor->damageCooldown > 0.0f) {
        return;
    }
    audio = &g_gameSettings.counters;
    if (audio->enabled != 0 &&
#if defined(VERSION_DE) || defined(VERSION_EU_X)
        actor->profile->enabled != 0 &&
#endif
        actor->profile->character == 11 &&
        audio->m_nBastilleShield > 0) {
        return;
    }
    if (actor->reactionFlags & 0x8000) {
        return;
    }

    type = event->inst.type;
    switch (type) {
    case 1019:
    case 1229:
        Player_DrainReserveAndDamage(actor, 0.1f, event->owner);
        return;
    case 1021:
    case 1231:
        Player_DrainReserveAndDamage(actor, 0.125f, event->owner);
        return;
    case 1022:
    case 1232:
        Player_DrainReserveAndDamage(actor, 0.3f, event->owner);
        return;
    case 1074:
    case 1251:
        Playerai_StartDamageTimer(actor, 80.0f, 2.0f, event->owner, 1);
        return;
    case 1032:
    case 1248:
        Playerai_AddReactionReserve(actor, 0.25f, event->owner);
        return;
    case 1049:
    case 1235:
        Player_StartSourceEffect(actor, event->owner);
        return;
    case 297:
        actor->cooldown = 0;
        actor->pending = 0;
        if (!(actor->reactionFlags & 0x8000)) {
            if (actor->reactionOwner == 0) {
                actor->reactionOwner = event->owner;
            }
            Player_SetPlayerState(actor, actor, 38);
        }
        return;
    }
}
