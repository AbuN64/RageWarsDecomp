#include "AI/SHARED_PICKUPGOALNODE.H"
#include "include_asm.h"
#include "COMMON/WORLD.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "RENDER/PLAYER_CONTROLLER_RESET_VIEWS.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "TYPES.H"
#include <PR/gbi.h>
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/GAMEPLAY_REACTIONS.H"
#include "RENDER/SHARED_REACTIONINTERACTION.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIPLE.H"
#include "AI/PLAYERAI.H"
#include "COMMON/GAMEPLAY_REACTION_RULES.H"
#include "COMMON/MODEL_RENDER.H"
#include "COMMON/OBJRECV5.H"
#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "RENDER/PLAYER_SPAWN_PLACEMENT.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/INTEGERSTATE2C.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "FX/CONTPAD_INITCONTROLLERINPUT.H"
#include "ACHIEVE/ACHIEVE.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_TRACK.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "AI/PLAYER_DRAWTINTEDPLAYER.H"

/* 802192C0.CPP */
/* Steps an animation cursor one frame: looks up the clip in g_world_AchieveUpdateresultsscreen, keeps the previous frame,
   and moves forward in states 1 and 2 or backward in states 3 and 4; at either end a looping clip
   (mode 1) wraps and a ping-pong clip (mode 0) reverses direction. */

extern char *Scene_GetPlatformRoute(void *world, s32 index);

void Playerai_AdvanceRouteCursor(Cursor *cursor) {
    Clip *clip;
    s32 frames;
    s32 state;

    clip = Scene_GetPlatformRoute(&g_world, cursor->clip);
    frames = clip->frames;
    state = cursor->state;
    cursor->previous = cursor->frame;
    switch (state) {
    case 1:
    case 2:
        {
            cursor->state = 1;
            if (++cursor->frame == frames) {
                switch (clip->mode) {
                case 1:
                    cursor->frame = 0;
                    break;
                case 0:
                    cursor->frame = frames - 2;
                    cursor->state = 3;
                    break;
                }
            }
        }
        break;
    case 3:
    case 4:
        {
            cursor->state = 3;
            if (--cursor->frame < 0) {
                switch (clip->mode) {
                case 0:
                    cursor->frame = 1;
                    cursor->state = 1;
                    break;
                case 1:
                    cursor->frame = frames - 1;
                    break;
                }
            }
        }
    }
}

extern s32 Scene_FindNearestRouteFrame(void *worldPointer, s32 routeIndex, void *queryPosition);

void Playerai_InitializeRouteCursor(RouteCursorState *cursorState, s8 initialState, void *position) {
    cursorState->state = 1;
    cursorState->clip = initialState;
    cursorState->frame = Scene_FindNearestRouteFrame(&g_world, initialState, position);
    cursorState->previous = 0;
}

extern void *Scene_GetPlatformRoutePoint(void *a, s32 b, s32 c);

ApproachLocation *Playerai_GetRouteCursorPoint(Cursor *cursor) {
    return Scene_GetPlatformRoutePoint(&g_world, cursor->clip, cursor->frame);
}

void *Playerai_GetRouteCursorNextPoint(Cursor *cursor) {
    return Scene_GetPlatformRoutePoint(&g_world, cursor->clip, cursor->previous);
}

/** Initialize the compact state record to its default values. */
void Playerai_InitializeCompactAnimationState(CompactAnimationState *record) {
    record->active = 1;
    record->state = 0;
    record->cursor = 0;
    record->flags = 0;
    record->clip = -1;
}

void Playerai_EmptyWeaponEffectHook(void *effect, void *player) {
    char pad[0x10];
}

extern void SetN64_ClearDepthRect(void *unused, s32 ulx, s32 lrx, s32 uly,
                          s32 lry, s32 interlaced);
extern void TranslateMatrix(char *object, f32 x, f32 y, f32 z);
extern void SwapMatrixUpForward(void *object);
extern void CopyMatrix(f32 *destinationMatrix, f32 *sourceMatrix);
extern void Graphu64_ScaleMatrixWorld(void *matrix, s32 sx, f32 scaleY, f32 scaleZ);
extern void Graphu64_ConvertMatrixToFixed(void *src, void *dst);
extern void Geometry_QueueDirectModel(s32 model, s32 transform, s32 lighting, s32 flags, s32 materialOverride);

void Playerai_DrawAnimatedSprite(char *object, char *camera) {
    f32 first[16];
    f32 second[16];
    s32 output[4];
    Gfx *command;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    char *matrix;

    Geometry_InvalidateMaterialKeys();
    if (((AnimationSprite *)(object))->model == 0 || ((AnimationSprite *)(object))->active == 0) {
        return;
    }

    Geometry_SetColorDither(192);
    Geometry_SetPrimitiveAlphaOverride(1, 32);

    command = g_displayListCursor++;
    gDPSetTexturePersp(command, G_TP_PERSP);
    command = g_displayListCursor++;
    gDPSetTextureFilter(command, G_TF_BILERP);
    Geometry_BeginModelBatch();

    x = ((GameplayCamera *)(camera))->viewLeft;
    y = ((GameplayCamera *)(camera))->viewTop;
    z = ((GameplayCamera *)(camera))->viewHeight + y;
    w = ((GameplayCamera *)(camera))->viewWidth + x;
    SetN64_ClearDepthRect(&g_gameSession, (s32)x, (s32)w, (s32)y, (s32)z, 0);

    Graphu64_BuildScaleMatrix(first, ((AnimationSprite *)(object))->scaleX,
                   ((AnimationSprite *)(object))->scaleY, ((AnimationSprite *)(object))->scaleZ);
    YawMatrix(first, ((AnimationSprite *)(object))->yaw);
    PitchMatrix(first, ((AnimationSprite *)(object))->pitch);
    TranslateMatrix((char *)first, ((AnimationSprite *)(object))->position.x,
                   ((AnimationSprite *)(object))->position.y, ((AnimationSprite *)(object))->position.z);
    SwapMatrixUpForward(first);

    matrix = (char *)second;
    CopyMatrix(second, first);
    if (g_frontendCurrentVideoModeIndex == 2) {
        Graphu64_ScaleMatrixWorld(matrix, g_playerAnimatedSpriteScaleX, g_playerAnimatedSpriteScaleYZ, g_playerAnimatedSpriteScaleYZ);
    }
    {
        s32 offset = (g_lightingBufferIndex << 6) + 16;
        Graphu64_ConvertMatrixToFixed(matrix, object + offset);
    }
    Graphu64_TransformPoint(first, (char *)&((LevelActor *)object)->transform[13], output);
    {
        s32 offset = (g_lightingBufferIndex << 6) + 16;
        Geometry_QueueDirectModel(((AnimationSprite *)(object))->model, (s32)(object + offset),
                       (intptr_t)&g_playerModelLighting, 0, -1);
    }
    Geometry_FlushModelBatch();
    Geometry_SetColorDither(0);
    Geometry_SetPrimitiveAlphaOverride(0, 32);
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char *g_tagKillerMessage[], *g_tagVictimMessage[], *g_captureFlagKillerMessage[], *g_captureFlagKillerFollowupMessage[];
static inline char *reactionText(void *text, MenuSettings *settings) { return ((char **)text)[settings->language]; }
#else
extern char *g_tagKillerMessage, *g_tagVictimMessage, *g_captureFlagKillerMessage, *g_captureFlagKillerFollowupMessage;
static inline char *reactionText(void *text, MenuSettings *settings) { return *(char **)text; }
#endif
extern void SetN64_CopyString(char *,const char *);
extern void Gsky_PostScaledScreenMessage(void *,void *,char *,f32);
static inline void nextMessage(s32 *next) {
    (*next)++;
    *next %= 4;
}

void Player_PostKillMessages(Shared_ReactionPlayer *a,Shared_ReactionPlayer *b,Shared_ReactionInteraction *unused) {
    MenuSettings *settings = &g_frontendScreenStatus.settings;
    MatchModes *modes;
    if (!settings->local) return;
    if (a!=b) {
        if (!a->statistics->isHuman) return;
        modes = &g_frontendScreenStatus.modes;
        if (modes->tag) {
            SetN64_CopyString(a->messages[a->messageNext], reactionText(&g_tagKillerMessage, settings));
            SetN64_CopyString(a->messages[a->messageNext]+10, b->statistics->name);
            if (a->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus,a->owner,a->messages[a->messageNext],1.5f);
            nextMessage(&a->messageNext);
            SetN64_CopyString(b->messages[b->messageNext], reactionText(&g_tagVictimMessage, settings));
            SetN64_CopyString(b->messages[b->messageNext]+11, a->statistics->name);
            if (b->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus,b->owner,b->messages[b->messageNext],1.5f);
        } else {
            if (!modes->captureFlag) return;
            SetN64_CopyString(a->messages[a->messageNext], reactionText(&g_captureFlagKillerMessage, settings));
            SetN64_CopyString(a->messages[a->messageNext]+10, b->statistics->name);
            if (a->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus,a->owner,a->messages[a->messageNext],1.5f);
            nextMessage(&a->messageNext);
            SetN64_CopyString(a->messages[a->messageNext], reactionText(&g_captureFlagKillerFollowupMessage, settings));
            if (a->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus,a->owner,a->messages[a->messageNext],1.5f);
            nextMessage(&a->messageNext);
            SetN64_CopyString(b->messages[b->messageNext], reactionText(&g_tagVictimMessage, settings));
            SetN64_CopyString(b->messages[b->messageNext]+11, a->statistics->name);
            if (b->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus,b->owner,b->messages[b->messageNext],1.5f);
            nextMessage(&b->messageNext);
            SetN64_CopyString(b->messages[b->messageNext], reactionText(&g_captureFlagVictimFollowupMessage, settings));
            if (b->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus,b->owner,b->messages[b->messageNext],1.5f);
        }
    }
    nextMessage(&b->messageNext);
}

/* Playerai_ApplyDamagePacket_Playerai.CPP */
/* TurretPlayerRelation, interaction and score views used to select reactions and record statistics. */

/* Selects and records a player's reaction to an interaction. */

/* Reaction thresholds are loaded from the cartridge's shared float table. */
void Playerai_ApplyStun(void *, f32);
void Playerai_CreditDamageSource(void *, void *);
s32 Player_GetPlayerIndex(void *, unsigned int);
s32 Player_GetMaxHealth(void *);
int Playerai_IsPlayerInactive(void *);
void Particle_ReleaseOwnerListOneEffects(void *, s32);
void * Scene_GetModelRecordByIndexPointer(Shared_World *, u16 *);
s32 XPlus_NextRandomInteger(void);

extern char g_actorParticleEffectSystem[];
extern Shared_MatchRules g_matchRoundCounters[];

void Playerai_ApplyDamagePacket(struct Shared_ReactionActor *attacker, void *damageState, struct Shared_ReactionInteraction *packet) {
    f32 facingSine;
    f32 sourceForwardProjection;
    f32 accumulatedStun;
    s32 *teamScoreSlot;
    s32 previousKillHistoryCursor;
    s32 healedHealth;
    s32 victimPlayerIndex;
    s32 killerPlayerIndex;
    s32 wasAlive;
    s32 statisticsValue; /* Integer result reused after each score value is stored. */
    s32 previousHealth;
    s32 nextKillHistoryCursor;
    s32 kind;
    s32 signedKillHistoryCursor;
    s32 hasSpecialSourceFlag;
    s32 clampedHealth;
    struct Shared_ReactionSource *damageSource;
    struct Shared_ReactionPlayer *damagedPlayer;
    struct Shared_ReactionPlayer *creditedPlayer;
    u16 *sourceHandle;
    s32 interactionType;
    u16 projectileType;
    s32 hitCounterIndex;
    s32 specialKillerTeam;
    s32 killerTeam;
    s32 score_owner_6;
    s32 score_owner_8;
    s32 *first_score_slot;
    s32 suicideTeam;
    u8 sourceKind;
    struct Shared_ReactionObjectKind *interactionObject;
    struct Shared_ReactionPlayer *projectileOwner;
    struct Shared_ReactionSource *reaction_source;
    struct Shared_ReactionAttribution *attributionSource;
    struct Shared_ReactionPlayerIndex *attributed_actor;
    s32 projectile_present;
    struct Shared_ReactionStatistics *victimKillStatistics;
    struct Shared_ReactionStatistics *killerTeamStatistics;
    struct Shared_ReactionFlags *sourceFlags;
    struct Shared_ReactionObjectStatistics *actorStatisticsNode;

    struct Shared_ReactionStatistics *suicideStatistics;
    struct Shared_ReactionStatistics *suicideScoreStatistics;
    struct Shared_ReactionStatistics *victimDeathStatistics;
    struct Shared_ReactionStatistics *specialKillStatistics;
    struct Shared_ReactionStatistics *specialScoreStatistics;
    struct Shared_ReactionStatistics *killerScoreStatistics;
    struct Shared_ReactionStatistics *specialHitStatistics;
    struct Shared_ReactionStatistics *countedDeathStatistics;

    creditedPlayer = 0;
    kind = -1;
    if ((Cinema_IsSequenceInWindow() == 0) && (Cinema_IsSequenceActive() == 0) && !(g_gameSettings.flags & 1)) {
        damagedPlayer = attacker->player;
        sourceHandle = damagedPlayer->sourceModelHandles;
        wasAlive = damagedPlayer->health > 0;
        if (sourceHandle == 0) {
            goto flag_clear;
        }

        while (sourceHandle != 0) {
            sourceFlags = Scene_GetModelRecordByIndexPointer(&g_world, sourceHandle);
            hasSpecialSourceFlag = 0;
            if (sourceFlags == 0) {
                break;
            }
            hasSpecialSourceFlag = 1;
            if (sourceFlags->flags52 & 0x40) {
                goto flag_done;
            }
            break;
        }
flag_clear:
        hasSpecialSourceFlag = 0;
flag_done:

        if (hasSpecialSourceFlag != 0) {
            kind = 23;
        }
        if (damagedPlayer->action == 32) {
            kind = 32;
        }
        if (packet != 0) {
            interactionObject = packet->sourceObject;
            if ((interactionObject != 0) && (interactionObject->category == 2)) {
                interactionType = interactionObject->type;
                if (interactionType == 1074) {
                    goto block_45;
                }
                if (interactionType < 1075) {
                    if (interactionType == 1029) {
                        goto block_33;
                    }
                    if (interactionType < 1030) {
                        if ((interactionType == 1026) || (interactionType == 1028)) {
                            goto block_38;
                        }
                        goto block_47;
                    }
                    if (interactionType < 1054) {
                        if (interactionType < 1051) {
                            goto block_47;
                        }
                        goto block_early_return;
                    }
                    goto block_46;
                }
                if (interactionType < 1248) {
                    if (interactionType >= 1245) {
                        goto block_early_return;
                    }
                    if (interactionType == 1084) {
                        goto block_38;
                    }
                    if (interactionType == 1242) {
                        goto block_33;
                    }
                    goto block_47;
                }
                if (interactionType == 1251) {
                    goto block_45;
                }
                goto block_47;
block_early_return:
                if (damagedPlayer->health > 0) {
                    Playerai_ApplyStun(damagedPlayer, 2.5f);
                }
                return;
block_33:
                if (damagedPlayer->health > 0) {
                    accumulatedStun = damagedPlayer->stun + g_playerDamageStunIncrement[0];
                    damagedPlayer->stun = accumulatedStun < g_playerMinimumAccumulatedStun ? g_playerMinimumAccumulatedStun : accumulatedStun;

                }
                packet->damage = 256;
                goto block_46;
block_38:
                if (damagedPlayer->reactionFlags & 0x1000) {
                    previousHealth = damagedPlayer->health;
                    if (previousHealth <= 0) {
                        packet->damage = 0;
                    } else {
                        healedHealth = previousHealth + packet->damage;
                        clampedHealth = Player_GetMaxHealth(damagedPlayer);
                        if (healedHealth < clampedHealth) {
                            clampedHealth = healedHealth;
                        }
                        damagedPlayer->health = clampedHealth;
                        goto block_45;
                    }
                }
                goto block_47;
block_45:
                packet->damage = 0;
                goto block_46;
            } else {
block_46:
                goto block_47;
            }
        } else {
block_47:
            Playerai_CreditDamageSource(damagedPlayer, packet);
            Player_ApplyPlayerDamage(damagedPlayer, attacker, packet->damage, packet->damageFlags, kind);

            damageSource = packet->sourceObject;
            if (damageSource != 0) {
                sourceKind = damageSource->kind;
                if (sourceKind != 1) {
                    if (sourceKind == 2) {
                        projectileOwner = damageSource->projectileOwner;
                        reaction_source = damageSource;
                        if (projectileOwner != 0) {
                            if (projectileOwner->category == 1) {
                                if (projectileOwner->flags & 0x300000) {
                                    creditedPlayer = projectileOwner;
                                } else if (projectileOwner->type == 1036) {
                                    creditedPlayer = projectileOwner->player;
                                }
                            }
                            projectileType = reaction_source->type;
                            if (((projectileType == 1003) || (projectileType == 1046)) && (wasAlive != 0) && (Playerai_IsPlayerInactive(damagedPlayer) != 0)) {
                                specialHitStatistics = (void *)creditedPlayer->statistics;
                                specialHitStatistics->special_hits = (u16) (specialHitStatistics->special_hits + 1);
                            }
                            facingSine = Gu_Sinf(attacker->heading);
                            sourceForwardProjection = ((damagedPlayer->positionX - reaction_source->positionX) * -facingSine) + ((damagedPlayer->positionZ - reaction_source->positionZ) * -Math_Cosf(attacker->heading));
                            if (sourceForwardProjection < g_playerDamageRearProjectionThreshold) {

                                damagedPlayer->hitDirection = 1;
                            } else if (sourceForwardProjection > g_playerDamageFrontProjectionThreshold) {

                                damagedPlayer->hitDirection = 2;
                            } else {
                                goto block_69;
                            }
                        }
                    }
                } else {
                    if (damageSource->flags & 0x300000) {
                        creditedPlayer = damageSource->player;
                    }
block_69:
                    damagedPlayer->hitDirection = 0;
                }
            } else {
                creditedPlayer = damagedPlayer;
            }
            if (creditedPlayer != 0) {
                if (packet != 0) {
                    attributionSource = packet->sourceObject;
                    projectile_present = attributionSource != 0;
                    do {
                      if (!projectile_present) { break; }
                      if (attributionSource->kind == 2) {
                        hitCounterIndex = attributionSource->type;
                        switch (hitCounterIndex) {
                            case 1028:
                            case 1039:
                                goto block_88;
                            case 1026:
                            case 1063:
                                goto block_87;
                            default:
                                if (!(packet->damageFlags & 0x100000)) {
                                    hitCounterIndex = creditedPlayer->profileIndex;
                                    goto block_86;
                                }
                                goto block_87;
                        }
                    }
                    } while (0);
                    if ((attributionSource != 0) && (attributionSource->kind == 1) && (attributionSource->flags & 0x300000)) {
                        attributed_actor = attributionSource->creditedPlayer;
                        if (!(packet->damageFlags & 0x100000)) {
                            hitCounterIndex = attributed_actor->profileIndex;
block_86:
                            ++g_playerHitCounts[hitCounterIndex];

                        }
                    }
                    goto block_87;
                }
block_87:
                if (creditedPlayer != 0) {
block_88:
                    if ((creditedPlayer != damagedPlayer) && (damagedPlayer->isBot != 0)) {
                        damagedPlayer->botRecord->lastAttacker = creditedPlayer;
                        damagedPlayer->botRecord->attackerMemoryTicks = 500;
                    }
                    if ((creditedPlayer != 0) && (damagedPlayer->health == 0)) {
                        countedDeathStatistics = (void *)damagedPlayer->statistics;
                        if (countedDeathStatistics->counted == 0) {
                            countedDeathStatistics->counted = 1U;
                            killerPlayerIndex = Player_GetPlayerIndex(&g_playerViewRenderContext, (u32) creditedPlayer);
                            victimKillStatistics = (void *)damagedPlayer->statistics;
                            if ((victimKillStatistics->isHuman == 1) && ((((struct Shared_ReactionMatchState *)(&g_playerViewRenderContext))->flagModeEnabled) != 0)) {
                                victimKillStatistics->kills_special[killerPlayerIndex]++;
                            } else {
                                damagedPlayer->statistics->kills_normal[killerPlayerIndex]++;
                            }
                            victimPlayerIndex = Player_GetPlayerIndex(&g_playerViewRenderContext, (u32) damagedPlayer);
                            if ((damagedPlayer->statistics->isHuman == 1) && ((((struct Shared_ReactionMatchState *)(&g_playerViewRenderContext))->flagModeEnabled) != 0)) {
                                creditedPlayer->statistics->deaths_special[victimPlayerIndex]++;
                            } else {
                                creditedPlayer->statistics->deaths_normal[victimPlayerIndex]++;
                            }
                            Player_PostKillMessages(damagedPlayer, creditedPlayer, packet);
                            if (creditedPlayer != 0) {
                                previousKillHistoryCursor = creditedPlayer->killHistoryIndex;
                                nextKillHistoryCursor = previousKillHistoryCursor + 1;
                                signedKillHistoryCursor = nextKillHistoryCursor;
                                if (nextKillHistoryCursor < 0) {
                                    signedKillHistoryCursor = previousKillHistoryCursor + 8;
                                }
                                statisticsValue = nextKillHistoryCursor - ((signedKillHistoryCursor >> 3) * 8);
                                creditedPlayer->killHistoryIndex = statisticsValue;
                                creditedPlayer->killHistory[statisticsValue] = damagedPlayer;
                                creditedPlayer->killHistoryTimers[creditedPlayer->killHistoryIndex] = 0xFF;
                            }
                            if (damagedPlayer != 0) {
                                damagedPlayer->lastKiller = creditedPlayer;
                                damagedPlayer->deathReactionVariant = (s32) (XPlus_NextRandomInteger() % 7);
                            }
                            if (killerPlayerIndex == victimPlayerIndex) {
                                suicideStatistics = (void *)damagedPlayer->statistics;
                                suicideStatistics->deaths_self = (u16) (suicideStatistics->deaths_self + 1);
                                suicideScoreStatistics = (void *)damagedPlayer->statistics;
                                statisticsValue = suicideScoreStatistics->score - 1;
                                suicideScoreStatistics->score = (u16) statisticsValue;
                                statisticsValue = g_teamScoringEnabled;
                                if (statisticsValue != 0) {
                                    suicideTeam = damagedPlayer->statistics->team;

                                    if (suicideTeam >= 0) {
                                        if (suicideTeam < 5) {
                                            teamScoreSlot = &g_teamScores[suicideTeam];

                                            if (g_resultReplayPending == 0) {
                                                if (g_resultExitPending != 0) {

                                                } else {
                                                    goto block_134;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                victimDeathStatistics = (void *)damagedPlayer->statistics;
                                victimDeathStatistics->deaths_other = (u16) (victimDeathStatistics->deaths_other + 1);
                                actorStatisticsNode = Portal_FindSearchNode(&g_navigationGraph, damagedPlayer->botRecord->searchNodeKey);
                                actorStatisticsNode->primaryReactionCount = (s32) (actorStatisticsNode->primaryReactionCount + 1);
                                actorStatisticsNode = Portal_FindSearchNode(&g_navigationGraph, creditedPlayer->botRecord->searchNodeKey);
                                actorStatisticsNode->secondaryReactionCount = (s32) (actorStatisticsNode->secondaryReactionCount + 1);
                                if (damagedPlayer->statistics->isHuman == 1) {
                                    if (g_matchRoundCounters->countRule != 0) {
                                        specialKillStatistics = (void *)creditedPlayer->statistics;
                                        creditedPlayer->lastCountRuleVictim = damagedPlayer;
                                        specialKillStatistics->special_kills = (u16) (specialKillStatistics->special_kills + 1);
                                        specialScoreStatistics = (void *)creditedPlayer->statistics;
                                        statisticsValue = specialScoreStatistics->score + 1;
                                        specialScoreStatistics->score = (u16) statisticsValue;
                                        statisticsValue = g_teamScoringEnabled;
                                        if (statisticsValue != 0) {
                                            specialKillerTeam = creditedPlayer->statistics->team;
                                            score_owner_6 = damagedPlayer->statistics->team;

                                            if (specialKillerTeam >= 0) {
                                                if (specialKillerTeam < 5) {
                                                    first_score_slot = &g_teamScores[specialKillerTeam];

                                                    teamScoreSlot = first_score_slot;
                                                    if (score_owner_6 != specialKillerTeam) {
                                                        do {
                                                            *first_score_slot = *first_score_slot + 1;
                                                            goto reaction_statistics_done;
                                                        } while (0);
                                                    }
                                                }
                                            }
                                        }
                                    } else if (g_matchRoundCounters->squads != 0) {
                                        creditedPlayer->lastSquadVictim = damagedPlayer;
                                    } else {
                                        goto block_124;
                                    }
                                } else {
block_124:
                                    if (g_teamScoringEnabled != 0) {
                                        killerTeamStatistics = (void *)creditedPlayer->statistics;
                                        if (killerTeamStatistics->team == damagedPlayer->statistics->team) {
                                            killerTeamStatistics->score = (u16) (killerTeamStatistics->score - 1);
                                        } else {
                                            killerTeamStatistics->score = (u16) (killerTeamStatistics->score + 1);
                                        }
                                    } else {
                                        killerScoreStatistics = (void *)creditedPlayer->statistics;
                                        killerScoreStatistics->score = (u16) (killerScoreStatistics->score + 1);
                                    }
                                    if (g_teamScoringEnabled != 0) {
                                        killerTeam = creditedPlayer->statistics->team;
                                        score_owner_8 = damagedPlayer->statistics->team;

                                        if (killerTeam >= 0) {
                                            if (killerTeam < 5) {
                                                teamScoreSlot = &g_teamScores[killerTeam];

                                                if (score_owner_8 != killerTeam) {
                                                    *teamScoreSlot = *teamScoreSlot + 1;
                                                } else {
block_134:
                                                    *teamScoreSlot = *teamScoreSlot - 1;
                                                }

                                            }
                                        }
                                    }
                                }
                            }
reaction_statistics_done:
                            Particle_RetireOwnedActors(&g_actorParticleEffectSystem, (s32) damagedPlayer);
                            Particle_ReleaseOwnerListOneEffects(&g_actorParticleEffectSystem, (s32) damagedPlayer);
                        }
                    }
                }
            }
        }
    }
}

extern void **Gobjinst_RequestAnimatedModelVariant(LevelActor *, s32);
extern void Cache_UnlockResource(s32, void *);
void Player_DrawPlayerBodyAndWeapon(LevelActor *actor, s32 animationContext, Draw *context)
{
    PlayerControllerView *player;
    void **resource;
    s32 temporaryFlag, model;

    player = actor->controller;
    if (0.0f < player->ghost) {
        temporaryFlag = 1;
        if (player->flags & 0x8000) temporaryFlag = 0;
        else player->flags |= 0x8000;
        g_menuModelFillColor[0] = 0.0f;
        g_menuModelFillEnabled = 3;
        if (player->flags & 0x4000) {
            g_menuModelFillColor[2] = 0.0f;
            g_menuModelFillColor[1] = 150.0f;
        } else {
            g_menuModelFillColor[1] = 0.0f;
            g_menuModelFillColor[2] = 150.0f;
        }
        if (player->fixedAlpha) g_menuModelFillColor[3] = 70.0f;
        else g_menuModelFillColor[3] = (u8)player->camera->fadeState;
        g_menuModelFillColor[4] = 128.0f;
        if (g_matchRoundCounters->countRule && player->controls->fragTagEnabled) actor->team = g_matchRoundCounters->teamColour;
        else actor->team = (u8)actor->definition->first;
        Geometry_DrawActorModelParts(context->model, player, actor->animationMatrices, 1,
                       &actor->lighting[g_lightingBufferIndex], 0, actor->renderPass);
        g_menuModelFillEnabled = 0;
        if (temporaryFlag) player->flags &= ~0x8000;
        if ((u32)(player->state - 17) < 2) return;
    if (player->state == 15) return;
    if (player->controls->fragTagEnabled && g_frontendScreenStatus.modes.tag) return;
    if (player->health == 0) return;
    if (player->kind == g_fragTagModelId) return;
    if (player->flags & 0x20) return;
    { s32 weaponModel = ((WeaponInfo *)g_weaponInfoByType[player->selectedWeapon])->model;
    model = weaponModel - 1203;
    if (player->selectedWeapon >= 16) model = weaponModel - 1205; }
        goto weapon;
    } else {
        if (g_frontendScreenStatus.settings.local) {
            if (player->controls->fragTagEnabled && g_frontendScreenStatus.modes.tag && player->health == 0) return;
            if (g_frontendScreenStatus.settings.local && (player->hidden || player->kind == g_playerDeathEffectModelIds) &&
                player->health == 0) return;
        }
        if (player->flags & 0x20) Player_DrawTintedPlayer(actor, animationContext, context);
        else {
            if (g_matchRoundCounters->countRule && player->controls->fragTagEnabled) actor->team = g_matchRoundCounters->teamColour;
            else actor->team = (u8)actor->definition->first;
            Geometry_DrawActorModelParts(context->model, player, actor->animationMatrices, 1,
                           &actor->lighting[g_lightingBufferIndex], 0, actor->renderPass);
            if (0.0f < player->opacity) {
                Geometry_DrawTintedModelParts(context->model, player, actor->animationMatrices, 1,
                    &actor->lighting[g_lightingBufferIndex], 0, actor->renderPass, player->red,
                    player->green, player->blue, (s32)player->opacity & 255);
            }
        }
    }
    if ((u32)(player->state - 17) < 2) return;
    if (player->state == 15) return;
    if (player->controls->fragTagEnabled && g_frontendScreenStatus.modes.tag) return;
    if (player->health == 0) return;
    if (player->kind == g_fragTagModelId) return;
    if (player->flags & 0x20) return;
    model = ((WeaponInfo *)g_weaponInfoByType[player->selectedWeapon])->model;
    model -= 1203;
    if (player->selectedWeapon >= 16) model -= 2;
weapon:
    if (model >= 0) {
        resource = Gobjinst_RequestAnimatedModelVariant(actor, model);
        if (resource) {
            Geometry_DrawModelResource(resource, actor->animationMatrices, 1,
                            &actor->lighting[g_lightingBufferIndex], 0, actor->renderPass);
            Cache_UnlockResource(0, resource);
        }
    }
}

/* 802192C0_3.CPP */
extern char g_controllerProfiles[];
void Playerai_InitializeMovementAndAim(void *playerObject) {
    char *object = playerObject;
    void *attributes;
    void *state = (char *)&((SharedPlayer *)object)->views5E8.view688_33.body;
    f32 zero;
    f32 default_value;
    f32 tail_value;
    CVector3 *tail_vector;
    s32 type;
    if (((PlayerControllerReleaseView *)(object))->computerControlled != 0) {
        attributes = g_botControllerProfile;
    } else {
        s32 index = ((PlayerControllerReleaseView *)(object))->playerIndex;
        attributes = (void *)(index << 4);
        attributes = (char *)attributes + index;
        attributes = (void *)((s32)attributes << 3);
        attributes = (char *)attributes + index;
        attributes = (void *)((s32)attributes << 2);
        attributes = g_controllerProfiles + (s32)attributes;
    }
    ContPad_InitControllerInput(state, attributes);
    ((PlayerControllerReleaseView *)(object))->forwardSpeed = 0;
    ((PlayerControllerReleaseView *)(object))->lateralSpeed = 0;
    ((PlayerControllerReleaseView *)(object))->landing = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord6CC = 0;
    ((PlayerControllerReleaseView *)(object))->active = 1;
    ((PlayerControllerReleaseView *)(object))->reservedWord6D4 = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord6D8 = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord6DC = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord6E4 = 0;
    ((PlayerControllerReleaseView *)(object))->bobStrength = 0;
    ((PlayerControllerReleaseView *)(object))->bobSpeed = 0;
    ((PlayerControllerReleaseView *)(object))->locked = 0;
    ((PlayerControllerReleaseView *)(object))->lockState = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord708 = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord70C = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord710 = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord714 = 0;
    ((PlayerControllerReleaseView *)(object))->pitchOffset = 0;
    ((PlayerControllerReleaseView *)(object))->kickYaw = 0;
    ((PlayerControllerReleaseView *)(object))->kickRoll = 0;
    ((PlayerControllerReleaseView *)(object))->swayPitch = 0;
    ((PlayerControllerReleaseView *)(object))->swayYaw = 0;
    ((PlayerControllerReleaseView *)(object))->swayRoll = 0;
    ((PlayerControllerReleaseView *)(object))->sideOffset = 0;
    ((PlayerControllerReleaseView *)(object))->weaponHeight = Playerai_GetObjectOwnerHeight(object);
    default_value = g_playerInitialMotionScale;
    ((PlayerControllerReleaseView *)(object))->forwardOffset = 0;
    (&((PlayerControllerReleaseView *)(object))->velocity)->x = (&((PlayerControllerReleaseView *)(object))->velocity)->y = (&((PlayerControllerReleaseView *)(object))->velocity)->z = 0;
    ((PlayerControllerReleaseView *)(object))->velocityScale = default_value;
    ((PlayerControllerReleaseView *)(object))->cameraOffset = 0;
    ((PlayerControllerReleaseView *)(object))->cameraScale = default_value;
    ((PlayerControllerReleaseView *)(object))->previousPosition = ((PlayerControllerReleaseView *)(object))->position;
    ((PlayerControllerReleaseView *)(object))->previousTarget = ((PlayerControllerReleaseView *)(object))->position;
    ((PlayerControllerReleaseView *)(object))->stride = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord668 = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord66C = 0;
    if (((PlayerControllerReleaseView *)(object))->model.v0 != 0) {
        ((PlayerControllerReleaseView *)(object))->heightDelta.value = ((struct ModelBlend *) ((PlayerControllerReleaseView *) object)->model.v1)->height;
    } else {
        ((PlayerControllerReleaseView *)(object))->heightDelta.word = 0;
    }
    tail_vector = &((PlayerControllerReleaseView *)(object))->reservedVector7D8;
    ((PlayerControllerReleaseView *)(object))->reservedWord7B0.word = 0;
    zero = ((PlayerControllerReleaseView *)(object))->reservedWord7B0.value;
    tail_value = g_playerInitialAimScale;
    type = 2;
    ((PlayerControllerReleaseView *)(object))->crouchDepth = 0;
    ((PlayerControllerReleaseView *)(object))->forceCrouch = 0;
    ((PlayerControllerReleaseView *)(object))->eyeOffset = 0;
    ((PlayerControllerReleaseView *)(object))->weaponChargeBlend = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord7F0 = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord7E8 = 0;
    ((PlayerControllerReleaseView *)(object))->controllerMode = 0;
    ((PlayerControllerReleaseView *)(object))->controllerTimer = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord790 = 0;
    ((PlayerControllerReleaseView *)(object))->controllerOwner = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord798 = -1;
    ((PlayerControllerReleaseView *)(object))->reservedWord79C = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord7A0 = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord7A4 = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord7A8 = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord7AC = 0;
    tail_vector->x = tail_vector->y = tail_vector->z = zero;
    ((PlayerControllerReleaseView *)(object))->aimScale = tail_value;
    ((PlayerControllerReleaseView *)(object))->reservedWord7B4 = 0;
    ((PlayerControllerReleaseView *)(object))->reservedWord7B8 = -1;
    ((PlayerControllerReleaseView *)(object))->reservedFloat7C0 = zero;
    ((PlayerControllerReleaseView *)(object))->reservedFloat7C4 = zero;
    ((PlayerControllerReleaseView *)(object))->reservedFloat7C8 = zero;
    ((PlayerControllerReleaseView *)(object))->reservedFloat7CC = zero;
    ((PlayerControllerReleaseView *)(object))->reservedFloat7D0 = zero;
    ((PlayerControllerReleaseView *)(object))->reservedFloat7D4 = zero;
    Player_SetPlayerState(object, object, type);
    ((PlayerControllerReleaseView *)(object))->controllerEnabled = 0;
    ((PlayerControllerReleaseView *)(object))->reservedFloat838 = zero;
    ((PlayerControllerReleaseView *)(object))->reservedFloat83C = zero;
    ((PlayerControllerReleaseView *)(object))->recoveryTime = zero;
    ((PlayerControllerReleaseView *)(object))->collisionState = 0;
    ((struct PlayerControllerResetStateView *) ((PlayerControllerReleaseView *) object)->profile)->state = 0;
    ((PlayerControllerReleaseView *)(object))->reservedFloat704 = zero;
    ((PlayerControllerReleaseView *)(object))->score = 0;
}

extern s32 g_playerWeaponClassMode;
CQuatern Gobjinst_BuildActorAimQuaternion(void *actor);
s16 *Playerai_GetWeaponFireMode(AimPlayer *aimPlayer, s32 weaponId);
void Player_GetPlayerViewTranslation(void *player, f32 *origin);
s32 Particle_SpawnEffectGroup(EffectSystem *sys, EffectActor *source, EffectActor *owner, s32 *refCount, s32 followTarget, s32 kind, CVector3 inheritedVelocity, CQuatern rotation, CVector3 pos, CVector3 *aim, s32 requestedMode, s32 spawnFlags);

static __inline__ s32 containsFire(s16 **entries,s32 effect) {
 s32 i=0; s16 **p=entries;
 search:
  if (*p==0) return 0;
  if ((*p)[2]==effect) return 1;
  i++; p++;
 if(i<3) goto search;
 return 0;
}
void Playerai_DispatchWeaponFireEffect(AimPlayer *aimPlayer, s32 effect) {

    AimView *weapon;
    s16 *mode;
    s16 **entries;
    CVector3 direction;
    CVector3 position;
    CQuatern aim;
    s32 value; void *extra; f32 timer;
    f32 amount;
    s16 *ammo;
    weapon = aimPlayer->view;
    if (aimPlayer->state < 2 || (s16)aimPlayer->state == 16 || (s16)aimPlayer->state == 17) return;
    aim = Gobjinst_BuildActorAimQuaternion(aimPlayer);
    if (effect == 1081 || effect == 1220 || effect == 1074 || effect == 1251 ||
        effect == 1049 || effect == 1235 || effect == 1061 || effect == 1226) aimPlayer->weaponActionMode = 2;
    mode = Playerai_GetWeaponFireMode(aimPlayer, aimPlayer->selectedWeapon);
    if (effect == 1081 || effect == 1220 || effect == 1074 || effect == 1251 ||
        effect == 1049 || effect == 1235 || effect == 1061 || effect == 1226) aimPlayer->weaponActionMode = 1;
    if (mode) {
        WeaponInfo *table = g_weaponInfoByType[aimPlayer->selectedWeapon];
        if (!aimPlayer->controlled && g_playerWeaponClassMode == 1) entries=&table->weaponClass;
        else entries=table->computerClasses;
        if (containsFire(entries,effect)) goto fire;
    }
    if (aimPlayer->selectedWeapon != 0 && aimPlayer->selectedWeapon != 16) goto spawn;
fire:
    if (weapon) aim = aimPlayer->rotation;
    if (aimPlayer->selectedWeapon != 0 && aimPlayer->selectedWeapon != 16) {
        ammo = &aimPlayer->ammo[mode[0]];
        *ammo -= (u16)mode[3];
        if (*ammo < 0) *ammo = 0;
        if (*ammo == 0) {
            if (aimPlayer->weapons[aimPlayer->selectedWeapon][1] == 3 || aimPlayer->weapons[aimPlayer->selectedWeapon][1] == 7) {
                aimPlayer->weapons[aimPlayer->selectedWeapon][0] = 0;
                aimPlayer->weapons[aimPlayer->selectedWeapon][1] = -1;
            }
        }
    }
    if (aimPlayer->equippedKind == 17) {
        if (aimPlayer->animation == 4100) {timer=aimPlayer->animationTimer; amount = g_playerWeaponFire1004Duration;}
        else if (aimPlayer->animation == 4000) {timer=aimPlayer->animationTimer; amount = g_playerWeaponFireFA0Duration;}
        else {
            if (aimPlayer->weaponKind == 8) aimPlayer->animation = 4100;
            else aimPlayer->animation = 4000;
            goto clear;
        }
        goto consume;
    }
    if (aimPlayer->animation == 1) aimPlayer->animation = 4400;
    else if (aimPlayer->animation == 4400) { timer=aimPlayer->animationTimer; amount = g_playerWeaponFire1130Duration; goto consume; }
    else if (aimPlayer->animation == 2600) aimPlayer->animation = 4405;
    else if (aimPlayer->animation == 4405) { timer=aimPlayer->animationTimer; amount = g_playerWeaponFire1135Duration; goto consume; }
    else if (aimPlayer->animation == 20) aimPlayer->animation = 4420;
    else if (aimPlayer->animation == 4420) { timer=aimPlayer->animationTimer; amount = g_playerWeaponFire1144Duration; goto consume; }
    else if (aimPlayer->selectedWeapon == 0 && aimPlayer->weaponKind == 8) aimPlayer->animation = 24158;
    else {
            if (aimPlayer->animation == 24158) { timer=aimPlayer->animationTimer; amount = g_playerWeaponFire5E5EDuration; goto consume; }
        if ((u32)(aimPlayer->animation - 24100) < 3) aimPlayer->animation = 24150;
        else if (aimPlayer->animation == 24150) { timer=aimPlayer->animationTimer; amount=g_playerWeaponFireDefaultDuration; goto consume; }
        else if (aimPlayer->animation == 24105) aimPlayer->animation = 24153;
        else if (aimPlayer->animation == 24153) { timer=aimPlayer->animationTimer; amount=g_playerWeaponFireDefaultDuration; goto consume; }
        else if (aimPlayer->animation == 24106) aimPlayer->animation = 24154;
        else if (aimPlayer->animation == 24154) { timer=aimPlayer->animationTimer; amount = g_playerWeaponFire5E5ADuration; goto consume; }
        else if (aimPlayer->animation == 24107) aimPlayer->animation = 24155;
        else if (aimPlayer->animation == 24155) { timer=aimPlayer->animationTimer; amount=g_playerWeaponFireDefaultDuration; goto consume; }
        else if (aimPlayer->animation == 24108) aimPlayer->animation = 24156;
        else {
                    if (aimPlayer->animation == 24156) { timer=aimPlayer->animationTimer; amount=g_playerWeaponFireDefaultDuration; goto consume; }
            if (aimPlayer->animation == 24109) aimPlayer->animation = 24157;
            else if (aimPlayer->animation == 24157) { timer=aimPlayer->animationTimer; amount=g_playerWeaponFireDefaultDuration; goto consume; }
            else { aimPlayer->firing = 0; goto spawn; }
        }
    }
    goto clear;
ordinary:
    timer=aimPlayer->animationTimer; amount = g_playerWeaponFireDefaultDuration;
consume:
    if (!(amount <= timer)) { aimPlayer->firing = 0; goto spawn; }
    aimPlayer->animationTimer = timer-amount;
clear:
    aimPlayer->firing = 0;
spawn:
    if (weapon && weapon->mode != 1) direction = weapon->origin;
    else Player_GetPlayerViewTranslation(aimPlayer, &direction.x);
    position = aimPlayer->position;
    extra = 0;
    if (aimPlayer->lockState == 2) extra = aimPlayer->lockedTarget;
    Particle_SpawnEffectGroup(&g_actorParticleEffectSystem, aimPlayer, aimPlayer, 0, extra, effect, position, aim,
                     direction, &aimPlayer->aim, -1, (aimPlayer->movementFlags&0x1000)?5:1);
    if (effect == 1044 || effect == 1069) {
        s32 shots = aimPlayer->shots - 1;
        if (shots < 0) shots = 0;
        aimPlayer->shots = shots;
    }
    if (aimPlayer->selectedWeapon != 9 && aimPlayer->selectedWeapon != 21 && aimPlayer->selectedWeapon != 20)
        g_playerCountedShots[aimPlayer->playerIndex]++;
}

/* Resets a player record for a new round: clears the ammo and the 22 action slots, marks every action but the first
   unavailable when the match is local and the player has a definition and no bonus, calls the setup for the current mode,
   sets the starting ammo by whether the player has a definition, and chooses the starting weapon (fixed for states 17 and
   18, none for a bonus profile, the low half of the second loadout word of the definition when the player is a computer, else the first
   action marked 1) before loading the weapon's animation table and count. */
extern void Achieve_ApplyPlayerOptionOverrides(struct Player *);
extern void Achieve_EnableLevelWeapons(struct Player *);

void Player_ResetPlayerWeapons(struct Player *player) {
    Shared_Game *game;
    s32 i;
    s32 j;
    s32 k;
    struct WeaponInfo *weaponInfo;
    AiCharacterDefinition *definition;
    for (i = 6; i >= 0; i--) {
        player->ammo[i] = 0;
    }
    for (i = 21; i >= 0; i--) {
        player->actions[i][0] = 0;
    }
    game = &g_gameSettings;
    if (game->local == 1 && player->definition != 0) {
        if (game->fragTagEnabled == 0 || player->profile->bonus == 0) {
            for (j = 1; j < 22; j++) {
                player->actions[j][0] = 0;
                player->actions[j][1] = -1;
            }
        }
        switch (g_gameSettings.controllerMode) {
        case 1:
            Achieve_ApplyProfileWeaponUnlocks(player);
            break;
        case 4:
            Achieve_EnableLevelWeapons(player);
            break;
        default:
            Achieve_ApplyPlayerOptionOverrides(player);
            break;
        }
    }
    if (player->definition == 0) {
        player->ammo[0] = 100;
        player->ammo[1] = 100;
        player->ammo[2] = 50;
    } else {
        player->ammo[0] = 50;
        player->ammo[1] = 0;
        player->ammo[2] = 0;
        player->ammo[3] = 0;
    }
    if (player->state == 17) {
        player->weapon = 16;
        player->selectedAction = 16;
        player->queuedAction = 16;
        player->lastAction = 16;
    } else if (player->state == 18) {
        player->weapon = 17;
        player->selectedAction = 17;
        player->queuedAction = 17;
        player->lastAction = 17;
    } else if (g_gameSettings.counters.m_bFragTagOn != 0 && player->profile->bonus != 0) {
        player->selectedAction = 0;
        player->weapon = 0;
        player->queuedAction = 0;
        player->lastAction = player->selectedAction;
    } else {
        if (player->computer != 0) {
            definition = player->definition;
            if (definition != 0 && definition->loadout != 0) {
                player->weapon = (u16)definition->loadout[1] - 1219;
                player->selectedAction = player->weapon;
            } else {
                player->weapon = 0;
                player->selectedAction = 0;
            }
        } else {
            for (k = 0; k < 22; k++) {
                if (player->actions[k][1] == 1) {
                    break;
                }
            }
            if (k < 22) {
                player->weapon = k;
                player->selectedAction = k;
            } else {
                player->weapon = 0;
                player->selectedAction = 0;
            }
        }
        player->queuedAction = player->selectedAction;
        player->lastAction = player->selectedAction;
    }
    if (g_frontendScreenStatus.settings.local != 0) {
        weaponInfo = g_weaponInfoByType[player->weapon];
        player->weaponAnimationTable = weaponInfo->animation;
        weaponInfo = g_weaponInfoByType[player->selectedAction];
        player->weaponAnimationCount = weaponInfo->animationCount;
    }
}

extern s32 g_activeLinkSequenceId;
extern void Player_ReleaseObjectHandles(void *);
extern void Scene_SetSelection(void *, s32, s32);
extern f32 Graphu64_GetPointDistance(f32 *a, f32 *b);
struct NavigationSearchGraphView; extern s32 Portal_FindNearestPointIndex(struct NavigationSearchGraphView *pointSet, void *point);
extern void Control_SetProfileMode(void *, s32);
extern void Player_InitActorHudState(void *);
/* Places the player at the matching level spawn. In multiplayer, choose the last
 * point tied for the greatest distance to its nearest player. Fall back when no
 * point is available, then update the controller's current cell. The single-player arm opens with a dead
 * conditional store: its join label ends cse's path, so the mismatch call keeps passing world (s1) instead
 * of being cross-jumped into the fallback's &g_world_AchieveUpdateresultsscreen call; flow and jump2 remove it. */
void Player_PlacePlayerAtSpawnPoint(struct Player *player, s32 model, s32 scale, s32 reset) {
    Shared_World *world;
    Shared_Placed single;
    Shared_Placed points[32];
    s32 count;
    s32 best;
    s32 i;
    f32 bestDistance;
    f32 distance;
    Shared_ActorView *other;
    s32 floor;
    s32 cell;
    Player_ReleaseObjectHandles(player);
    Control_SetProfileMode(((Shared_ActorView *)player)->controller, 0);
    world = &g_world;
    if (reset) {
        ((Shared_ActorView *)player)->reservedWord864 = 0;
        ((Shared_ActorView *)player)->reservedWord868 = 0;
    }
    if (g_frontendScreenStatus.settings.local) {
        count = Scene_FindPlacedObjectsByKey(world, -1, model, points, 32);
        best = -1;
        bestDistance = 0.0f;
        for (i = 0; i < count; i++) {
            distance = k_spawnNearestPlayerInitialDistance;
            for (other = g_transientPlayerList.actorList; other; other = other->next) {
                f32 d = Graphu64_GetPointDistance(&points[i].pos, &other->position.vector);
                if (d < distance) distance = d;
            }
            if (bestDistance <= distance) {
                bestDistance = distance;
                best = i;
            }
        }
        if (best == -1) goto fallback;
        ((Shared_ActorView *)player)->weapon.position0 = points[best].pos;
        ((Shared_ActorView *)player)->position.vector = ((Shared_ActorView *)player)->weapon.position0;
        ((LevelActor *)player)->yaw = ((Shared_ActorView *)player)->weapon.yaw = points[best].heading;
        floor = Scene_FindFloorPolygon(&g_world, &((Shared_ActorView *)player)->position.vector);
    } else {
        if (model != 0 && player != 0) {
            floor = 0;
        }
        if (Scene_FindPlacedObjectsByKey(world, -1, model, &single, 1) == 0) {
            goto fallback;
        }
        if (single.kind != g_activeLinkSequenceId) {
            Scene_SetSelection(world, model, scale);
            goto done;
        }
        ((Shared_ActorView *)player)->weapon.position0 = single.pos;
        ((Shared_ActorView *)player)->position.vector = ((Shared_ActorView *)player)->weapon.position0;
        ((LevelActor *)player)->yaw = ((Shared_ActorView *)player)->weapon.yaw = single.heading;
        floor = Scene_GetModelSectionTwoRecord(world, single.pad12);
    }
    ((Shared_ActorView *)player)->weapon.model = floor;
    ((Shared_ActorView *)player)->modelId = floor;
    Player_InitActorHudState(player);
    goto done;
fallback:
    Scene_SetSelection(&g_world, model, scale);
done:
    cell = Portal_FindNearestPointIndex(&g_navigationGraph, &((Shared_ActorView *)player)->position.vector);
    ((AiController *)((Shared_ActorView *)player)->owner)->current = cell;
}

/* 800C73E8.CPP */
/* ROM-grounded data: src/g_PlayeraiInitializeMovementAndAimConstantWordsUsRev1_Playerai.c */
const float g_PlayeraiInitializeMovementAndAimConstantWordsUsRev1[2] = {
    1.0f, 1.0f,
};
