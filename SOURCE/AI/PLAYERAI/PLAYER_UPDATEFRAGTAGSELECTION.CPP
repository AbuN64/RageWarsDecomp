#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/OBJRECV5.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_ROUND_RULES.H"
#include "COMMON/LOADOUT.H"
#include "TYPES.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/ANIMATIONTRIGGERDEFINITION.H"
#include "COMMON/SELF.H"
#include "COMMON/VIEWFLAGS.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"
#include "RENDER/PLAYER_SPAWN_PLACEMENT.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/PARTICLE_LIGHTING.H"
#include "COMMON/WORLD.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "WEAPONS/WEAPONAI_DRAWREDMARKERQUAD.H"
#include "COMMON/GAME_SESSION.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/TRIPLE.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"

extern void Playerai_EndRound(void *);
s32 Player_CheckTotalScoreWin(Root *);
s32 Player_CheckTeamPointWin(struct World *);

/* 80225D10_4.CPP */

/* Updates round state, player health and round-start presentation. */

typedef struct FragTagPlayerStateView FragTagCandidatePlayerView;

typedef struct FragTagSelectionProfileView FragTagCandidateProfileView;

typedef struct FragTagPlayerInputView FragTagSelectedPlayerView;

typedef struct FragTagCameraStateView FragTagCameraView;

typedef struct FragTagTeamProfileView FragTagSelectedTeamProfileView;

typedef struct FragTagAssignmentProfileView FragTagPreviousProfileView;

void TeamSelect_EmptyWeaponWheelHook(void *);

void Playerai_InitializePlayerHealth(void *);

void * Playerai_GetPlayerByIndex(void *, u32);

void * Playerai_GetEligiblePlayerByIndex(void *, u32);

 /* extern */
/* Provider passes the position identity as a 32-bit address; see SoundElement_PlaySoundAtPosition_PlayerUpdatefragtagselection
 * and the published Weapon_UpdateIdleWeaponSelection caller. */

/* Advances an elimination round when rule g_resultReplayPending is on and not paused (Cinema_IsSequenceActive,
   Cinema_IsSequenceInWindow): counts the players still in, clears g_ctfWaitingPlayerFlag while one is waiting, then by the
   round state at 0x84 of g_matchRoundCounters revives the first waiting player (crediting a point in state 1,
   scheduling g_ctfMode = 3 otherwise) or moves to state 2, and ends the round through Playerai_EndRound
   when Player_CheckTeamPointWin_PlayerUpdatefragtagselection reports it over. */

extern u8 g_gameControllerMode; /* MIXED Player_UpdateFragTagSelection */
extern u8 g_playerHudSpriteMode; /* MIXED Player_UpdateFragTagSelection */
void Player_UpdateFragTagSelection(s8 *world) {
    CGameStatus *initial_rules;
    CGameStatus *select_rules;
    CGameStatus *case2_rules;
    CGameStatus *case3_entry;
    CGameStatus *case3_loop;
    CGameStatus *case4_entry;
    CGameStatus *case6_entry;
    CGameStatus *case4_loop;
    CGameStatus *case6_active_rules;
    CGameStatus *rules;
    u32 state;
    s32 restoredHealth;
    s32 unusedRotatingWord;
    s32 unusedChosenWord;
    s32 unusedFlippedWord;
    f32 scaled6x;
    f32 scaled6y;
    f32 scaled5x;
    f32 scaled5y;
    f32 scaled_x4;
    f32 scaled_y4;
    f32 scaled_x;
    f32 scaled_y;
    f32 banner_half;
    f32 banner_size;
    f32 allPlayersViewWidth;
    f32 allPlayersScaleX;
    f32 rotatingViewHeight;
    f32 rotatingScaleY;
    f32 chosenViewHeight;
    f32 chosenScaleY;
    f32 flippedViewWidth;
    f32 flippedScaleX;
    f32 allPlayersViewHeight;
    f32 allPlayersScaleY;
    f32 rotatingViewWidth;
    f32 chosenViewWidth;
    f32 flippedViewHeight;
    f32 flippedScaleY;
    s32 nextRotatingPosition;
    s32 nextChosenPosition;
    s32 selectionMode;
    s32 eligiblePlayerCount;
    s32 remainingFlipTicks;
    s32 ruleOrRandomValue; /* Reused for each initialized rule and actor-kind result in the health loops. */
    s32 randomPlayerQuotient;
    s32 nextChosenIndex;
    s32 selectedPlayerIndex;
    s8 unusedRotatingByte;
    s8 unusedChosenByte;
    s8 initialCharacter;
    s8 flippedCharacter;
    s32 playerIndex;
    FragTagSelectedTeamProfileView *rotatingPlayerProfile;
    FragTagSelectedTeamProfileView *chosenPlayerProfile;
    PlayerCameraTargetView *allPlayersView;
    FragTagCameraView *rotatingView;
    FragTagCameraView *chosenView;
    FragTagCameraView *flippedView;
    FragTagSelectedPlayerView *flippedPlayer;
    FragTagCandidatePlayerView *player;
    FragTagSelectedPlayerView *rotatingPlayer;
    FragTagSelectedPlayerView *chosenPlayer;
    FragTagCandidateProfileView *playerProfile;
    FragTagPreviousProfileView *priorFlipProfile;
    FragTagSelectedTeamProfileView *flippedProfile;

    if ((Cinema_IsSequenceActive() == 0) && (Cinema_IsSequenceInWindow() == 0) && ((initial_rules = &g_gameSettings.counters)->m_bFragTagOn != 0)) {
        if ((Player_CheckTotalScoreWin(world) != 0) && (initial_rules->elapsed == 0)) {
            Playerai_EndRound(world);
            return;
        }
        eligiblePlayerCount = Playerai_CountEligiblePlayers(world);
        if (eligiblePlayerCount > 0) {
            state = g_fragTagSelectionState;
            switch (state) {
            case 0:
            default:
                Playerai_ClearPlayerResetFlags(world);
                Playerai_ResetAllPlayerHealth(world);
                g_fragTagSelectionState = 1;
                return;
            case 1:
                Playerai_ResetAllPlayerHealth(world);
                if (eligiblePlayerCount > 0) {
                    selectionMode = (select_rules = &g_gameSettings.counters)->m_FragTagSelectionType;
                    if (selectionMode == 3) {
                        ruleOrRandomValue = Graphu64_NextRandom();
                        randomPlayerQuotient = ruleOrRandomValue / eligiblePlayerCount;
                        if (eligiblePlayerCount == 0) {

                        }
                        if ((eligiblePlayerCount == -1) && (randomPlayerQuotient == 0x80000000)) {

                        }
                        selectedPlayerIndex = ruleOrRandomValue % eligiblePlayerCount;
                        select_rules->m_FragTagMode = selectionMode;
                        select_rules->m_FragTagPlayerChosen = selectedPlayerIndex;
                        select_rules->m_FragTagPlayerPos = selectedPlayerIndex;
                        return;
                    } else {
                        nextChosenIndex = select_rules->m_FragTagPlayerChosen + 1;
                        if (eligiblePlayerCount == 0) {

                        }
                        if ((eligiblePlayerCount == -1) && ((nextChosenIndex / eligiblePlayerCount) == 0x80000000)) {

                        }
                        selectedPlayerIndex = nextChosenIndex % eligiblePlayerCount;
                        select_rules->m_FragTagMode = 4;
                        select_rules->m_FragTagPlayerChosen = selectedPlayerIndex;
                        select_rules->m_FragTagPlayerPos = selectedPlayerIndex;
                        return;
                    }
                }
                goto state_end;
            case 2:
                if (eligiblePlayerCount > 0) {
                    (case2_rules = &g_gameSettings.counters)->m_FragTagMode = 5;
                    case2_rules->m_FragTagFlipTimer = 225;
                    case2_rules->m_FragTagPlayerPos = (s32) case2_rules->m_FragTagPlayerChosen;
                }
                Playerai_ResetAllPlayerHealth(world);
                return;
            case 5:                                 /* switch 1 */
                playerIndex = 0;
                if (eligiblePlayerCount >= 0) {
                    banner_half = g_fragTagRotatingBannerHalfWidth;
                    banner_size = g_fragTagRotatingBannerSize;
                    do {
                        player = Playerai_GetPlayerByIndex(world, playerIndex);
                        if (player != 0) {
                            playerProfile = player->profile;
                            if (playerProfile->assigned == 0) {
                                allPlayersView = player->view;
                                if ((allPlayersView != 0) && (allPlayersView->disabled == 0)) {
                                    Onscrn_SetupSpriteMode((s32) g_playerHudSpriteMode);
                                    allPlayersViewWidth = allPlayersView->viewportWidth;
                                    allPlayersViewHeight = allPlayersView->viewportHeight;
                                    scaled5x = allPlayersViewWidth * banner_half;
                                    scaled5y = allPlayersViewHeight * banner_half;
                                    allPlayersScaleX = allPlayersViewWidth / (f32) g_hudReferenceViewportWidth;
                                    allPlayersScaleY = allPlayersViewHeight / (f32) g_hudReferenceViewportHeight;
                                    OnScreen_DrawSpriteResource(507, 0, (s16) (s32) ((allPlayersView->viewportX + scaled5x) - (allPlayersScaleX * banner_size)), (s16) (s32) ((allPlayersView->viewportY + scaled5y) - (allPlayersScaleY * banner_size)), allPlayersScaleX, allPlayersScaleY, 1);
                                }
                                player->profile->fragTagEnabled = 1;
                                switch (g_fragTagSelectSoundVariant) {
                                case 0:
                                    SoundElement_PlaySoundAtPosition(6305, player->position, (s32)&player->position, -1);
                                    break;
                                case 1:
                                    SoundElement_PlaySoundAtPosition(6505, player->position, (s32)&player->position, -1);
                                    break;
                                case 2:
                                    SoundElement_PlaySoundAtPosition(6405, player->position, (s32)&player->position, -1);
                                    break;
                                }
                                TeamSelect_EmptyWeaponWheelHook(&player->animationState);
                                player->reserved11B4 = 0;
                                Actor_RequestActorState(&player->bodyStateStorage, &player->weaponStateStorage, 1);
                                Player_PlacePlayerAtSpawnPoint(player, player->spawnPoint, 0, 1);
                                Playerai_InitializePlayerHealth(player);
                                player->health = (s32) g_playerRespawnHealth;
                            } else {
                                if ((g_selectedProfileHealthOptionEnabled != 0) && (playerProfile->selected != 0)) {
                                    initialCharacter = playerProfile->team;
                                    if (initialCharacter == 11) {
                                    restoredHealth = 0x19000;
                                    } else if (initialCharacter == 12) {
                                    restoredHealth = 0x19000;
                                    } else if (initialCharacter == 14) {
                                    restoredHealth = 76800;
                                    } else if (initialCharacter == 13) {
                                    restoredHealth = 76800;
                                    } else {
                                        restoredHealth = player->model->modelId << 8;
                                    }
                                } else {
                                    restoredHealth = player->model->modelId << 8;
                                }
                                if ((g_gameControllerMode == 1) && (player->computerControlled == 0)) {
                                    restoredHealth += g_characterHealthBonuses[player->playerIndex].value;
                                }
                                player->health = restoredHealth;
                                player->restoredHealth = restoredHealth;
                            }
                        }
                        playerIndex += 1;
                    } while (eligiblePlayerCount >= (s32) playerIndex);
                }
                Playerai_ClearPlayerResetFlags(world);
                g_fragTagSelectionState = 6;
                return;
            case 3:
                case3_entry = &g_gameSettings.counters;
                if (eligiblePlayerCount == 0) {

                }
                if ((eligiblePlayerCount == -1) && (((s32) case3_entry->m_FragTagPlayerPos / eligiblePlayerCount) == 0x80000000)) {

                }
                case3_entry->m_FragTagFlipTimer = 0;
                rotatingPlayer = Playerai_GetEligiblePlayerByIndex(world, (u32) ((s32) case3_entry->m_FragTagPlayerPos % eligiblePlayerCount));
                rotatingView = rotatingPlayer->view;
                if ((rotatingView != 0) && (rotatingView->disabled == 0)) {
                    Onscrn_SetupSpriteMode((s32) g_playerHudSpriteMode);
                    rotatingViewWidth = rotatingView->viewportWidth;
                    rotatingViewHeight = rotatingView->viewportHeight;
                    scaled_x = rotatingViewWidth * g_fragTagRotatingViewCenterScale;
                    scaled_y = rotatingViewHeight * g_fragTagRotatingViewCenterScale;
                    rotatingScaleY = rotatingViewHeight / (f32) g_hudReferenceViewportHeight;
                    OnScreen_DrawSpriteResource(507, 0, (s16) (s32) ((rotatingView->viewportX + scaled_x) - ((rotatingViewWidth / (f32) g_hudReferenceViewportWidth) * g_fragTagRotatingViewIconOffset)), (s16) (s32) ((rotatingView->viewportY + scaled_y) - (rotatingScaleY * g_fragTagRotatingViewIconOffset)), (rotatingViewWidth / (f32) g_hudReferenceViewportWidth), rotatingScaleY, 1);
                }
                rules = &g_gameSettings.counters;
                nextRotatingPosition = rules->m_FragTagPlayerPos + 1;
                rules->m_FragTagPlayerPos = nextRotatingPosition;
                if (nextRotatingPosition >= (((5 - eligiblePlayerCount) * 20) - rules->m_FragTagPlayerChosen)) {
                    Playerai_ClearPlayerResetFlags(world);
                    rules->m_FragTagMode = 7;
                    rotatingPlayer->profile->fragTagEnabled = 1U;
                    switch (g_fragTagSelectSoundVariant) {
                    case 0:
                        SoundElement_PlaySoundAtPosition(6305, rotatingPlayer->position, (s32)&rotatingPlayer->position, -1);
                        break;
                    case 1:
                        SoundElement_PlaySoundAtPosition(6505, rotatingPlayer->position, (s32)&rotatingPlayer->position, -1);
                        break;
                    case 2:
                        SoundElement_PlaySoundAtPosition(6405, rotatingPlayer->position, (s32)&rotatingPlayer->position, -1);
                        break;
                    }
                    TeamSelect_EmptyWeaponWheelHook(&rotatingPlayer->animationState);
                    rotatingPlayer->reserved11B4 = 0;
                    Actor_RequestActorState(&rotatingPlayer->bodyStateStorage, &rotatingPlayer->weaponStateStorage, 1);
                    Player_PlacePlayerAtSpawnPoint(rotatingPlayer, rotatingPlayer->spawnPoint, 0, 1);
                    Playerai_InitializePlayerHealth(rotatingPlayer);
                }
                playerIndex = 0;
                if (eligiblePlayerCount >= 0) {
                    rotatingPlayerProfile = rotatingPlayer->profile;
                    case3_loop = &g_gameSettings.counters;
                    do {
                        if (rotatingPlayerProfile->fragTagEnabled != 0) {
                            rotatingPlayer->health = (s32) case3_loop->mask;
                        } else {
                            ruleOrRandomValue = g_selectedProfileHealthOptionEnabled;
                            if ((ruleOrRandomValue != 0) && (rotatingPlayerProfile->selected != 0)) {
                                ruleOrRandomValue = rotatingPlayerProfile->team;
                                if (ruleOrRandomValue == 11) {
                                    restoredHealth = 0x19000;
                                    } else if (ruleOrRandomValue == 12) {
                                    restoredHealth = 0x19000;
                                    } else if (ruleOrRandomValue == 14) {
                                    restoredHealth = 76800;
                                    } else if (ruleOrRandomValue == 13) {
                                    restoredHealth = 76800;
                                    } else {
                                        restoredHealth = rotatingPlayer->model->modelId << 8;
                                    }
                            } else {
                                restoredHealth = rotatingPlayer->model->modelId << 8;
                            }
                            ruleOrRandomValue = g_gameControllerMode;
                            if ((ruleOrRandomValue == 1) && (rotatingPlayer->computerControlled == 0)) {
                                restoredHealth += g_characterHealthBonuses[rotatingPlayer->playerIndex].value;
                            }
                            rotatingPlayer->health = restoredHealth;
                            rotatingPlayer->restoredHealth = restoredHealth;
                        }
                        playerIndex += 1;
                    } while (eligiblePlayerCount >= playerIndex);
                    return;
                }
                goto state_end;
            case 4:
                case4_entry = &g_gameSettings.counters;
                if (eligiblePlayerCount == 0) {

                }
                if ((eligiblePlayerCount == -1) && (((s32) case4_entry->m_FragTagPlayerPos / eligiblePlayerCount) == 0x80000000)) {

                }
                case4_entry->m_FragTagFlipTimer = 0;
                chosenPlayer = Playerai_GetEligiblePlayerByIndex(world, (u32) ((s32) case4_entry->m_FragTagPlayerPos % eligiblePlayerCount));
                chosenView = chosenPlayer->view;
                if ((chosenView != 0) && (chosenView->disabled == 0)) {
                    Onscrn_SetupSpriteMode((s32) g_playerHudSpriteMode);
                    chosenViewWidth = chosenView->viewportWidth;
                    chosenViewHeight = chosenView->viewportHeight;
                    scaled_x4 = chosenViewWidth * g_fragTagChosenViewCenterScale;
                    scaled_y4 = chosenViewHeight * g_fragTagChosenViewCenterScale;
                    chosenScaleY = chosenViewHeight / (f32) g_hudReferenceViewportHeight;
                    OnScreen_DrawSpriteResource(507, 0, (s16) (s32) ((chosenView->viewportX + scaled_x4) - ((chosenViewWidth / (f32) g_hudReferenceViewportWidth) * g_fragTagChosenViewIconOffset)), (s16) (s32) ((chosenView->viewportY + scaled_y4) - (chosenScaleY * g_fragTagChosenViewIconOffset)), (chosenViewWidth / (f32) g_hudReferenceViewportWidth), chosenScaleY, 1);
                }
                rules = &g_gameSettings.counters;
                nextChosenPosition = rules->m_FragTagPlayerPos + 1;
                rules->m_FragTagPlayerPos = nextChosenPosition;
                if (nextChosenPosition >= (((5 - eligiblePlayerCount) * 20) - rules->m_FragTagPlayerChosen)) {
                    Playerai_ClearPlayerResetFlags(world);
                    rules->m_FragTagMode = 7;
                    chosenPlayer->profile->fragTagEnabled = 1U;
                    switch (g_fragTagSelectSoundVariant) {
                    case 0:
                        SoundElement_PlaySoundAtPosition(6305, chosenPlayer->position, (s32)&chosenPlayer->position, -1);
                        break;
                    case 1:
                        SoundElement_PlaySoundAtPosition(6505, chosenPlayer->position, (s32)&chosenPlayer->position, -1);
                        break;
                    case 2:
                        SoundElement_PlaySoundAtPosition(6405, chosenPlayer->position, (s32)&chosenPlayer->position, -1);
                        break;
                    }
                    TeamSelect_EmptyWeaponWheelHook(&chosenPlayer->animationState);
                    chosenPlayer->reserved11B4 = 0;
                    Actor_RequestActorState(&chosenPlayer->bodyStateStorage, &chosenPlayer->weaponStateStorage, 1);
                    Player_PlacePlayerAtSpawnPoint(chosenPlayer, chosenPlayer->spawnPoint, 0, 1);
                    Playerai_InitializePlayerHealth(chosenPlayer);
                }
                playerIndex = 0;
                if (eligiblePlayerCount >= 0) {
                    chosenPlayerProfile = chosenPlayer->profile;
                    case4_loop = &g_gameSettings.counters;
                    do {
                        if (chosenPlayerProfile->fragTagEnabled != 0) {
                            chosenPlayer->health = (s32) case4_loop->mask;
                        } else {
                            ruleOrRandomValue = g_selectedProfileHealthOptionEnabled;
                            if ((ruleOrRandomValue != 0) && (chosenPlayerProfile->selected != 0)) {
                                ruleOrRandomValue = chosenPlayerProfile->team;
                                if (ruleOrRandomValue == 11) {
                                    restoredHealth = 0x19000;
                                    } else if (ruleOrRandomValue == 12) {
                                    restoredHealth = 0x19000;
                                    } else if (ruleOrRandomValue == 14) {
                                    restoredHealth = 76800;
                                    } else if (ruleOrRandomValue == 13) {
                                    restoredHealth = 76800;
                                    } else {
                                        restoredHealth = chosenPlayer->model->modelId << 8;
                                    }
                            } else {
                                restoredHealth = chosenPlayer->model->modelId << 8;
                            }
                            ruleOrRandomValue = g_gameControllerMode;
                            if ((ruleOrRandomValue == 1) && (chosenPlayer->computerControlled == 0)) {
                                restoredHealth += g_characterHealthBonuses[chosenPlayer->playerIndex].value;
                            }
                            chosenPlayer->health = restoredHealth;
                            chosenPlayer->restoredHealth = restoredHealth;
                        }
                        playerIndex += 1;
                    } while (eligiblePlayerCount >= playerIndex);
                    return;
                }
                goto state_end;
            case 6:
                case6_entry = &g_gameSettings.counters;
                remainingFlipTicks = case6_entry->m_FragTagFlipTimer - 1;
                case6_entry->m_FragTagFlipTimer = remainingFlipTicks;
                if (remainingFlipTicks <= 0) {
                    case6_entry->m_FragTagFlipTimer = 0;
                    if (g_pickupSavedMusicPlaybackEnabled != 0) {
                        SoundElement_SetMusicPlaybackEnabled(g_pickupSavedMusicPlaybackEnabled);
                    }
                    playerIndex = 0;
                    banner_half = g_fragTagChosenBannerHalfWidth;
                    banner_size = g_fragTagChosenBannerSize;
                    do {
                        flippedPlayer = Playerai_GetPlayerByIndex(world, playerIndex);
                        if (flippedPlayer != 0) {
                            priorFlipProfile = flippedPlayer->profile;
                            if (priorFlipProfile->fragTagEnabled == 0) {
                                flippedView = flippedPlayer->view;
                                if ((flippedView != 0) && (flippedView->disabled == 0)) {
                                    Onscrn_SetupSpriteMode((s32) g_playerHudSpriteMode);
                                    flippedViewWidth = flippedView->viewportWidth;
                                    flippedViewHeight = flippedView->viewportHeight;
                                    scaled6x = flippedViewWidth * banner_half;
                                    scaled6y = flippedViewHeight * banner_half;
                                    flippedScaleX = flippedViewWidth / (f32) g_hudReferenceViewportWidth;
                                    flippedScaleY = flippedViewHeight / (f32) g_hudReferenceViewportHeight;
                                    OnScreen_DrawSpriteResource(507, 0, (s16) (s32) ((flippedView->viewportX + scaled6x) - (flippedScaleX * banner_size)), (s16) (s32) ((flippedView->viewportY + scaled6y) - (flippedScaleY * banner_size)), flippedScaleX, flippedScaleY, 1);
                                }
                                flippedPlayer->profile->fragTagEnabled = 1U;
                                switch (g_fragTagSelectSoundVariant) {
                                case 0:
                                    SoundElement_PlaySoundAtPosition(6305, flippedPlayer->position, (s32)&flippedPlayer->position, -1);
                                    break;
                                case 1:
                                    SoundElement_PlaySoundAtPosition(6505, flippedPlayer->position, (s32)&flippedPlayer->position, -1);
                                    break;
                                case 2:
                                    SoundElement_PlaySoundAtPosition(6405, flippedPlayer->position, (s32)&flippedPlayer->position, -1);
                                    break;
                                }
                                TeamSelect_EmptyWeaponWheelHook(&flippedPlayer->animationState);
                                flippedPlayer->reserved11B4 = 0;
                                Actor_RequestActorState(&flippedPlayer->bodyStateStorage, &flippedPlayer->weaponStateStorage, 1);
                                Player_PlacePlayerAtSpawnPoint(flippedPlayer, flippedPlayer->spawnPoint, 0, 1);
                                Playerai_InitializePlayerHealth(flippedPlayer);
                            } else {
                                priorFlipProfile->assigned = 0;
                                flippedPlayer->profile->fragTagEnabled = 0U;
                                Player_PlacePlayerAtSpawnPoint(flippedPlayer, flippedPlayer->spawnPoint, 0, 1);
                            }
                            flippedProfile = flippedPlayer->profile;
                            if (flippedProfile->fragTagEnabled != 0) {
                                case6_active_rules = &g_gameSettings.counters;
                                flippedPlayer->health = (s32) case6_active_rules->mask;
                                flippedPlayer->restoredHealth = (s32) case6_active_rules->mask;
                            } else {
                                if ((g_selectedProfileHealthOptionEnabled != 0) && (flippedProfile->selected != 0)) {
                                    flippedCharacter = flippedProfile->team;
                                    if (flippedCharacter == 11) {
                                    restoredHealth = 0x19000;
                                    } else if (flippedCharacter == 12) {
                                    restoredHealth = 0x19000;
                                    } else if (flippedCharacter == 14) {
                                    restoredHealth = 76800;
                                    } else if (flippedCharacter == 13) {
                                    restoredHealth = 76800;
                                    } else {
                                        restoredHealth = flippedPlayer->model->modelId << 8;
                                    }
                                } else {
                                    restoredHealth = flippedPlayer->model->modelId << 8;
                                }
                                if ((g_gameControllerMode == 1) && (flippedPlayer->computerControlled == 0)) {
                                    restoredHealth += g_characterHealthBonuses[flippedPlayer->playerIndex].value;
                                }
                                flippedPlayer->health = restoredHealth;
                                flippedPlayer->restoredHealth = restoredHealth;
                            }
                        }
                        playerIndex += 1;
                    } while ((s32) playerIndex < 8);
                    g_fragTagSelectionState = 7;
                    return;
                }
                goto state_end;
            case 7:
                g_fragTagSelectionClearedFlag = 0;
                goto state_end;
            }
state_end:;
        }
    }
}

static inline void Weapons_CountRelease(s16 *counter) {
    (*counter)++;
}
static inline s32 Weapons_CountPlayersIn(Round *round) {
    ActorNode *node;
    s32 count = 0;
    for (node = round->players; node != 0; node = node->next) {
        if (node->scores->waitState == 0) {
            count += 1;
        }
    }
    return count;
}
static inline ActorNode *Weapons_FindWaitingPlayer(Round *round) {
    ActorNode *node;
    for (node = round->players; node != 0; node = node->next) {
        if ((node->scores->waitingRequest == 1) || (node->scores->waitState == 1)) {
            break;
        }
    }
    return node;
}
void Player_ReleaseWaitingPlayer(Round *round) {
    s32 count;
    ActorNode *node;
    CGameStatus *state;
    s32 waiting;
    if ((g_gameSettings.counters.m_bCTFOn != 0) && (Cinema_IsSequenceActive() == 0) && (Cinema_IsSequenceInWindow() == 0)) {
        count = Weapons_CountPlayersIn(round);
        if (count > 0) {
            waiting = Weapons_FindWaitingPlayer(round) != 0;
            if (waiting) {
                g_ctfWaitingPlayerFlag = 0;
            }
            state = &g_gameSettings.counters;
            switch (state->m_CTFMode) {
            case 0:
            default:
                if (count > 0) {
                    node = Weapons_FindWaitingPlayer(round);
                    if (node != 0) {
                        node->scores->waitState = 0;
                        g_gameSettings.counters.m_CTFMode = 3;
                    }
                } else {
                    state->m_CTFMode = 2;
                }
                break;
            case 1:
                state->m_CTFMode = 2;
                node = Weapons_FindWaitingPlayer(round);
                if (node != 0) {
                    node->scores->waitState = 0;
                    Weapons_CountRelease(&node->scores->score);
                    g_ctfWaitingPlayerFlag = 0;
                }
                break;
            case 2:
            case 3:
                break;
            }
            if ((Player_CheckTeamPointWin(round) != 0) && (g_gameSettings.counters.elapsed == 0)) {
                Playerai_EndRound(round);
            }
        }
    }
}

/* The round settings and counters, read through fresh getters so each block rebuilds the address. */
static inline Shared_Game *currentGame(void) {
    return &g_gameSettings;
}
static inline CGameStatus *gameStatus(void) {
    return &g_gameSettings.counters;
}
/* Returns 1 when a team (team rounds) or a player has reached the score limit. With a controller
   mode set, humanWon records whether the human team or a human player got there; in mode 1 a
   computer winner does not end the round. */
s32 Player_CheckScoreLimit(Round *round) {
    Shared_Game *game;
    ActorNode *player;
    u32 team, i;
    u32 slot;
    u8 mode;
    if (Cinema_IsSequenceActive() || Cinema_IsSequenceInWindow()
#if !defined(VERSION_US)
        || gameStatus()->mode == 0
#endif
    ) {
        return 0;
    }
    if (gameStatus()->teams != 0) {
#if defined(VERSION_US)
        if (gameStatus()->mode == 0) {
            return 0;
        }
#endif
        team = 0xFF;
        game = currentGame();
        if (game->controllerMode != 0) {
            slot = 0;
            while (game->slots[slot].enabled == 0) {
                slot++;
            }
            team = g_gameSettings.slots[slot].team;
        }
        for (i = 0; (s32)i < 5; i++) {
            if (gameStatus()->mode <= gameStatus()->scores[i]) {
                mode = currentGame()->controllerMode;
                if (mode == 0) {
                    return 1;
                }
                if (i == team) {
                    gameStatus()->humanWon = 1;
                    return 1;
                }
                gameStatus()->humanWon = 0;
                if (mode != 1) {
                    return 1;
                }
            }
        }
    } else {
        for (player = round->players; player != 0; player = player->next) {
            if (gameStatus()->mode <= player->scores->score) {
                mode = currentGame()->controllerMode;
                if (mode != 0) {
                    if (player->kind < 4) {
                        gameStatus()->humanWon = 1;
                        return 1;
                    }
                    gameStatus()->humanWon = 0;
                    if (mode == 1) {
                        continue;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

/* 80225D10_5.CPP */
/* Checks accumulated opponent scores and updates the completion flag. */

extern int Player_GetPlayerIndex(Root *,FragTagPlayerListNode *);

/* Reports whether a team's points reached the point target (none when it is 0); in a trial it records
   in humanWon whether that team is the human side's and, when it is not, keeps looking. */

/* Ends a match when its conditions are met, unless a menu or pause is up (Cinema_IsSequenceActive,
   Cinema_IsSequenceInWindow), the match is locked at 0x1C of the rules g_matchRoundCounters or the game g_matchEndingTeamWheelClose disallows
   it at 0xCC9: outside a cutscene (Menu_CountLiveNodes_PlayerUpdatefragtagselection) the time limit at 0x14 of the rules counts down by
   the frame time while Playerai_CountActivePlayers says the clock runs and ends the match when it expires (clearing
   humanWon at 0xA8 of the rules in trial kind 3); outside a cutscene a score limit reached through Player_CheckScoreLimit
   ends it while the rules' limit at 0x18 is set and 0x54 is clear; and when g_selectedProfileHealthOptionEnabled asks, it counts
   the active players among the first eight and how many of them are out, ending the match once all
   are out, directly or, when a mode 14 player takes part, only after the rules' round count at 0x9C
   reaches 3, marking humanWon. */

extern s32 Menu_CountLiveNodes(struct CMenu_t **);

extern s32 Playerai_CountActivePlayers(PlayerWorldActorTables *);

static inline SharedPlayer *player_at(PlayerWorldActorTables *world, u32 index) {
    SharedPlayer *player;
    s32 count;

    player = 0;
    count = 0;
    if (index < 8U) {
        player = world->players;
        if (player != 0) {
            do {
                if (count == (s32) index) {
                    return player;
                }
                player = player->views16E0.view16E0_2.next;
                count += 1;
            } while (player != 0);
        }
    }
    return player;
}

extern s32 g_gameplayRoundState;

extern void *SoundVoicePool_GetGlobalState(void);

extern s32 SoundVoicePool_StopNode(void *, void *);

extern void Gobjinst_UpdateActorController(void *base);

extern void Gobjinst_UpdateActorRootDisplacement(struct Actor36 *actor);

extern void GameObject_DrawBlobShadow(void *actor, CVector3 *offset, s32 raised);

extern void Cache_UnlockResource(s32 cache, s32 resource);

/* Draws the per-player overlays for one view between Geometry_BeginModelBatch and Geometry_FlushModelBatch: for each player
   in the list from 0x20 it draws the scope model 0xC84 or 0xC85 (by the zoom mode at 0x120C) at the
   player's view matrix while zoomed in at 0x11FC, the player's display through Weaponai_DrawRedMarkerQuad when it
   belongs to this view and is enabled at 0x1210, and in team games (0x24 or 0x78 of g_matchRoundCounters) a
   teammate marker through Playerai_DrawAimMarker for every other player on the viewing player's team. */

extern void *Gsky_FindScreenMessage(s32);

extern s32 Scene_FindModelIdIndex(struct Shared_World *, s32);

extern void *Scene_GetIndexedModelResource(char *, s32);

extern void Geometry_QueueDirectModel(void *, void *, char *, s32, s32);

extern void Playerai_DrawAimMarker(void *);

extern s32 g_gameLoopFrameCount;

extern s32 g_playerWeaponClassMode;

s32 Player_CheckTotalScoreWin(Root *root) {
    GameRules *initial=g_gameSession.match.rules; GameRules *state;
 FragTagPlayerListNode *node; int i,sum,skip; unsigned char *settings;
 if(initial->totalScoreTarget==0) return 0;
 node=root->players; state=initial;
 if(node) { settings=(unsigned char *)state - ((char *)&((Shared_Game *)0)->counters - (char *)0); }
 for(;node;node=node->next) {
  skip=Player_GetPlayerIndex(root,node);
  sum=0;
  for(i=0;i<8;i++) {
   if(i!=skip) {
    sum+=node->scores->score[i];
    if(sum>=state->totalScoreTarget) {
     { unsigned char trialKind=settings[13]; if(trialKind) {
      if(node->playerIndex<4) {state->humanWon=1;return 1;}
      state->humanWon=0;
      if(trialKind==1) continue;
     }
     } return 1;
    }
   }
  }
 }
 return 0;
}

s32 Player_CheckTeamPointWin(struct World *world) {
    GameRules *target;
    GameRules *rules;
    Settings580 *settings;
    Settings580 *trial;
    s32 humanTeam;
    s32 i;
    s32 team;
    s32 kind;

    target = g_gameSession.match.rules;
    if (target->pointTarget == 0) {
        return 0;
    }
    i = 0;
    settings = &g_gameSession.match.settings;
    humanTeam = 0xFF;
    if (settings->trialKind != 0) {
        for (; settings->roster[i].active == 0; i++) {
        }
        humanTeam = g_gameSession.match.settings.roster[i].team;
    }
    for (team = 0; team < 5; team++) {
        rules = g_gameSession.match.rules;
        if (rules->teamPoints[team] >= rules->pointTarget) {
            if (team == humanTeam) {
                rules->humanWon = 1;
                return 1;
            }
            trial = &g_gameSession.match.settings;
            kind = trial->trialKind;
            rules->humanWon = 0;
            if (kind == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void Playerai_UpdateRoundLimits(PlayerWorldActorTables *world) {
    SharedPlayer *player;
    GameRules *rules;
    GameSessionState *game;
    GameRules *limits;
    s32 i;
    s32 active;
    s32 out;
    s32 special;

    if (Cinema_IsSequenceActive() == 0 && Cinema_IsSequenceInWindow() == 0) {
        rules = g_gameSession.match.rules;
        if (rules->locked != 0 || g_gameSession.match.settings.allowed == 0) {
            return;
        }
        if (Menu_CountLiveNodes(&g_gameSession.match.messages.head) == 0 && rules->timeLimit > 0.0f && g_gameSession.clockPaused == 0) {
            if (Playerai_CountActivePlayers(world) != 0) {
                rules->timeLimit -= g_frameElapsedTime;
            }
            if (rules->timeLimit <= 0.0f && rules->locked == 0) {
                rules->timeLimit = 0.0f;
                if (g_gameSession.match.settings.trialKind == 3) {
                    rules->humanWon = 0;
                }
                Playerai_EndRound(world);
            }
        }
        game = &g_gameSession.match;
        if (Menu_CountLiveNodes(&game->messages.head) == 0 && Player_CheckScoreLimit(world) != 0) {
            limits = game->rules;
            if (limits->locked == 0 && g_gameSession.clockPaused == 0 && limits->scoreLimit > 0 && limits->sudden == 0) {
                Playerai_EndRound(world);
            }
        }
        if (g_gameSettings.counters.enabled != 0) {
            active = 0;
            out = 0;
            special = 0;
            for (i = 0; i < 8; i++) {
                player = player_at(world, i);
                if (player != 0 && player->views5D8.view5D8_1.record->display != 0) {
                    active++;
                    if (player->views5E4.view5E4_3.alive == 0) {
                        out++;
                    }
                    if (player->views5D8.view5D8_1.record->characterId == 14) {
                        special = 1;
                    }
                }
            }
            if (out == active) {
                if (special) {
                    limits = g_gameSession.match.rules;
                    if (limits->rounds >= 3) {
                        limits->humanWon = 1;
                        Playerai_EndRound(world);
                    }
                } else {
                    g_gameSettings.counters.humanWon = 1;
                    Playerai_EndRound(world);
                }
            }
        }
    }
}

void Playerai_StopInactivePlayerSounds(char *game) {
    char *actor;

    if (g_gameplayRoundState == 11 || g_gameplayRoundState == 8) {
        return;
    }
    actor = ((GamePlayerListView *)(game))->players;
    while (actor != 0) {
        if (Cinema_IsSequenceInWindow() != 0 || ((ObjRecV5 *)(actor))->voiceActive == 0) {
            void *work;

            work = SoundVoicePool_GetGlobalState();
            SoundVoicePool_StopNode(work, ((ObjRecV5 *)(actor))->firstResourceHandle.v0);
            ((ObjRecV5 *)(actor))->firstResourceHandle.v1 = 0;
            work = SoundVoicePool_GetGlobalState();
            SoundVoicePool_StopNode(work, ((ObjRecV5 *)(actor))->secondResourceHandle.v0);
            ((ObjRecV5 *)(actor))->secondResourceHandle.v1 = 0;
        } else if (g_frontendScreenStatus.status[7] == 0) {
            void *owner = ((ObjRecV5 *)(actor))->view;
            s32 blocked;

            if (owner == 0) {
                blocked = 0;
            } else {
                blocked = ((View *)(owner))->shieldActive != 0;
            }
            if (blocked == 0) {
                Block *base;
                s32 old_value;
                s32 new_value;
                f32 saved_value;

                base = &((ObjRecV5 *)(actor))->actorBlock;
                old_value = ((FragTagSelectionActorView *)actor)->value86C;
                saved_value = g_frameElapsedTime;
                ((FragTagSelectionActorView *)actor)->flags |= 0x200;
                base->value = 16;
                base->flags &= 0xFFFDFFFF;
                Gobjinst_UpdateActorController(base);
                if (((ObjRecV5 *)(actor))->cooldown <= 0.0f) {
                    Gobjinst_UpdateActorRootDisplacement((char *)base);
                }
                new_value = ((ObjRecV5 *)(actor))->controllerState;
                g_frameElapsedTime = saved_value;
                if (old_value != new_value) {
                    ((ObjRecV5 *)(actor))->stateChangeClear = 0;
                }
                ((ObjRecV6 *)(actor))->savedPosition = ((ObjRecV5 *)(actor))->currentPosition;
                ((ObjRecV6 *)(actor))->savedYaw = ((ObjRecV5 *)(actor))->yaw;
                ((ObjRecV6 *)(actor))->savedSourceHandle = ((ObjRecV5 *)(actor))->sourceHandle;
                ((ObjRecV6 *)(actor))->savedResourceBlock = ((ObjRecV5 *)(actor))->resourceBlock;
                ((ObjRecV6 *)(actor))->savedFlags &= ~0x200;
            }
        }
        actor = ((ObjRecV5 *)(actor))->next;
    }
}

void Playerai_UpdateViewModelBounds(void *game, void *view) {
    void *node;

    node = ((WorldPlayerHeadView *)(game))->players;
    if (node != 0) {
        do {
            void *owner;

            owner = ((FragTagLinkedActorView *)(node))->owner;
            if (owner != 0) {
                if (owner == view) {
                    void *actor;

                    actor = &((FragTagLinkedActorView *)(node))->actorBlock;
                    if (((PlayerViewModeView *)(owner))->viewMode == 0) {
                        if (((CachedPlayerModelView *)(actor))->renderFlags & 0x40000) {
                            void *resource;

                            resource = Cache_RequestResource(
                                0, ((CachedPlayerModelView *)(actor))->resourceKey,
                                ((CachedPlayerModelView *)(actor))->resourceKey,
                                ((CachedPlayerModelView *)(actor))->resourceFlags,
                                4, 0, 0, g_playerModelResourceTag, 1);
                            if (resource != 0) {
                                void *linked;
                                void *linkedOwner;

                                linked = ((CachedPlayerModelView *)(actor))->player;
                                Gobjinst_UpdateModelBounds(actor, (s32)SetN64_GetPackSection(*(void **)resource, 0));
                                linkedOwner = ((LinkedActorOwnerView *)(linked))->owner;
                                if (linkedOwner != 0) {
                                    CVector3 delta;

                                    delta.x = ((ViewPositionXView *)(linkedOwner))->positionX -
                                              ((CachedPlayerModelView *)(actor))->positionX;
                                    delta.y = 0.0f;
                                    delta.z = ((ViewPositionZView *)(((LinkedActorOwnerView *)(linked))->owner))->positionZ -
                                              ((CachedPlayerModelView *)(actor))->positionZ;
                                    GameObject_DrawBlobShadow(actor, &delta, 1);
                                }
                                Cache_UnlockResource(0, (s32)resource);
                            }
                        }
                    } else {
                        goto generic;
                    }
                } else if (owner != 0) {
generic:
                    if (((FragTagLinkedActorView *)(node))->flags & 0x40000) {
                        void *resource;

                        resource = Cache_RequestResource(
                            0, ((FragTagLinkedActorView *)(node))->resourceKey,
                            ((FragTagLinkedActorView *)(node))->resourceKey,
                            ((FragTagLinkedActorView *)(node))->resourceFlags,
                            4, 0, 0, g_playerModelResourceTag, 1);
                        if (resource != 0) {
                            Gobjinst_UpdateModelBounds(node, (s32)SetN64_GetPackSection(*(void **)resource, 0));
                            Cache_UnlockResource(0, (s32)resource);
                        }
                    }
                }
            }
            node = ((FragTagLinkedActorView *)(node))->next;
        } while (node != 0);
    }
}

void Playerai_DrawPlayerModelsForView(GamePlayerListView *game, s32 view) {
    char *player;
    GameRules *match;
    s32 team;
    s32 zoomed;
    s32 model;

    match = g_gameSession.match.rules;
    team = -1;
    if (match->teams != 0 || match->teamRule != 0) {
        team = ((struct Record *) ((struct PlayerSettingsOwnerView *) Gsky_FindScreenMessage(view))->settings)->team;
    }
    Geometry_BeginModelBatch();
    for (player = game->players; player != 0; player = ((FragTagPlayerListView *)(player))->nextPlayer) {
        zoomed = 0;
        if (((FragTagPlayerListView *)(player))->zoomLevel > 0.0f) {
            zoomed = 1;
        }
        if (zoomed) {
            if (((FragTagPlayerListView *)(player))->zoomModelVariant != 0) {
                model = Scene_FindModelIdIndex(&g_world, 3204);
            } else {
                model = Scene_FindModelIdIndex(&g_world, 3205);
            }
            if (model != -1) {
                Geometry_QueueDirectModel(Scene_GetIndexedModelResource(&g_world, model), (char *)&((Shared_ActorView *)player)->transform1600, &g_defaultParticleLighting, 0, -1);
            }
        }
        if (((FragTagPlayerListView *)(player))->weaponHandle != 0 && ((FragTagPlayerListView *)(player))->alternateFireState != 0 && ((FragTagPlayerListView *)(player))->weaponHandle == view) {
            Weaponai_DrawRedMarkerQuad((char *)&((SharedPlayer *)player)->views1C.view2E8_27.weapon, (char *)&((SharedPlayer *)player)->views1C.view458_29.ammo);
        }
        if ((g_gameSession.match.rules->teams != 0 || g_gameSession.match.rules->teamRule != 0)
            && ((struct Record *) ((FragTagPlayerListView *) player)->profile)->team == team && Gsky_FindScreenMessage(view) != player) {
            Playerai_DrawAimMarker(player);
        }
    }
    Geometry_FlushModelBatch();
}

void Player_DrawMatchCountdown(void *unusedPlayer, ViewState *viewState) {
    f32 x;
    f32 y;
    f32 center_x;
    f32 center_y;
    f32 scale_x;
    f32 scale_y;
    f32 position;
    HudGlobals *hud;

    if (Cinema_IsSequenceActive() != 0) {
        return;
    }
    if (Cinema_IsSequenceInWindow() != 0) {
        return;
    }
    hud = (HudGlobals *)&g_playerHudSpriteMode;
    Onscrn_SetupSpriteMode(hud->fade);
    if (((HudState *)&hud->state)->timer <= 0.0f) {
        return;
    }

    position = ((HudState *)&hud->state)->timer * g_playerMatchCountdownTimeScale;
    x = (f32)(s32)(position * g_playerMatchCountdownDigitScales);
    scale_x = viewState->width / (f32)g_hudReferenceViewportWidth;
    position -= x * ((ScalarPair *)&g_playerMatchCountdownDigitScales)->second;
    scale_y = viewState->height / (f32)((struct IntPair *)&g_hudReferenceViewportWidth)->second;
    if ((x < g_playerMatchCountdownDigitLimit) && (position < g_playerMatchCountdownFractionLimit) &&
        ((g_gameLoopFrameCount % 15U) < 5U)) {
        return;
    }

    if (g_playerWeaponClassMode == 1) {
        if (g_frontendCurrentVideoModeIndex == 0) {
            center_x = (f32)g_hudReferenceViewportWidth * g_playerMatchCountdownCenterXScale;
            scale_x *= g_playerMatchCountdownSpriteScale;
            center_y = g_playerMatchCountdownStandardPosition[0];
            scale_y *= g_playerMatchCountdownSpriteScale;
        } else {
            center_y = g_playerMatchCountdownAlternatePosition[0];
            center_x = (f32)g_hudReferenceViewportWidth * g_playerMatchCountdownStandardPosition[1];
        }
    } else {
        center_x = (f32)g_hudReferenceViewportWidth * g_playerMatchCountdownAlternatePosition[1];
        center_y = (f32)(((struct IntPair *)&g_hudReferenceViewportWidth)->second - 10) * g_playerMatchCountdownAlternatePosition[1];
    }

    OnScreen_DrawSpriteNumber((s32)x, center_x - (scale_x * g_playerMatchCountdownDigitOffsets),
                   center_y, scale_x, scale_y, 1, 1, 0);
    OnScreen_DrawSpriteNumber((s32)position, center_x + (2.0f * scale_x),
                   center_y, scale_x, scale_y, 1, 0, 2);
    OnScreen_SetupTextRendering();
    Onscrn_DrawText(&g_playerMatchCountdownText,
                  (s32)(center_x - (scale_x * ((ScalarPair *)&g_playerMatchCountdownDigitOffsets)->second)),
                  (s32)(center_y - (scale_y * g_playerMatchCountdownSpriteOffsets[0])),
                  0xFF, 0, 0, scale_x, scale_y);
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
extern void BuildDirectionMatrix(Matrix *, CVector3 *);
extern void TranslateMatrix(Matrix *, f32 x, f32 y, f32 z);
extern void SwapMatrixUpForward(Matrix *);
extern void Graphu64_ConvertMatrixToFixed(Matrix *src, void *dst);
static inline void buildForceMarkerTransform(Shared_ActorView *player, s32 attract, CVector3 *normal) {
    Matrix matrix;
    CVector3 offset;
    BuildDirectionMatrix(&matrix, normal);
    Graphu64_ScaleVector(&offset, normal, 5.12f);
    Graphu64_AddVec3(&offset, &offset, &player->targetPosition);
    TranslateMatrix(&matrix, offset.x, offset.y, offset.z);
    SwapMatrixUpForward(&matrix);
    Graphu64_ConvertMatrixToFixed(&matrix, player->transform1600);
}
extern const float g_forceMarkerDurationEuropean;
void Playerai_ToggleForceMarkerEuropean(Shared_ActorView *player, s32 attract) {
    void *screen;
    if (player->aimTarget != 0) {
        if (player->marker.time > 0.0f) {
            player->marker.time = 0;
            SoundElement_PlayFlatSound(1400);
            screen = player->message;
            if (screen == 0) return;
            Camera_PostScreenMessage((void *)&g_frontendScreenStatus, screen, (u8 *)g_forceMarkerRemovedTextEuropean[g_frontendScreenStatus.settings.language]);
        } else {
            player->targetPosition = player->aimPoint;
            player->attract = attract;
            player->marker.time = g_forceMarkerDurationEuropean;
            buildForceMarkerTransform(player, attract, &player->aimNormal);
            SoundElement_PlayFlatSound(1400);
            screen = player->message;
            if (screen == 0) return;
            if (attract != 0) Camera_PostScreenMessage((void *)&g_frontendScreenStatus, screen, (u8 *)g_forceMarkerAttractTextEuropean[g_frontendScreenStatus.settings.language]);
            else Camera_PostScreenMessage((void *)&g_frontendScreenStatus, screen, (u8 *)g_forceMarkerRepulseTextEuropean[g_frontendScreenStatus.settings.language]);
        }
    }
}
#endif

/* 80225D10_6.CPP */
static inline s32 playerHasForce(ForcePlayer *player, f32 zero) { s32 value = 0; if (zero < player->strength) value = 1; return value; }
void Playerai_ApplyPlayerForces(void *listObject, void *bodyObject) {
    ForcePlayerList *list = listObject;
    ForceBody *body = bodyObject;
    ForcePlayer *player;
    s32 changed;
    CVector3 delta, direction;
    f32 distance, force, dot;
    f32 one, zero;
    player = list->head;
    changed = 0;
    if (player != 0) {
        zero = 0.0f;
        one = g_playerForceMarkerUnit;
    do {
        if (player->active != 0 && playerHasForce(player, zero)) {
            Graphu64_SubtractVectors(&delta, &player->origin, &body->position);
            distance = (delta.x * delta.x + delta.y * delta.y) + delta.z * delta.z;
            Graphu64_NormalizeVec3(&delta);
            changed = 1;
            if (g_playerForceMarkerMaximumDistance < distance) {
                force = g_playerForceMarkerStrength / distance;
                if (g_frameElapsedTime < one) force *= g_frameElapsedTime;
                if (player->attract == 0) force = -force;
                direction = body->velocity;
                Graphu64_NormalizeVec3(&direction);
                dot = delta.x * direction.x + delta.y * direction.y;
                dot += delta.z * direction.z;
                if (dot < zero) dot = -dot;
                dot += one;
                dot *= g_playerForceMarkerProjectionScale;
                force *= dot;
                Graphu64_ScaleVector(&delta, &delta, force);
            }
            Graphu64_AddVec3(&body->velocity, &body->velocity, &delta);
        }
        player = player->next;
    } while (player != 0);
    }
    if (changed != 0) {
        delta = body->velocity;
        Graphu64_NormalizeVec3(&delta);
        body->direction = delta;
    }
}

/* 800C7C90.CPP */
const float k_PlayerUpdatefragtagselectionEncodedWords[8] = {
    0.5f, 32.0f, 0.5f, 32.0f,
    0.5f, 32.0f, 0.5f, 32.0f,
};

/* 800C7CB0.CPP */
const char s_playerAnimObjectInfoText[24] = "player anim object info";
