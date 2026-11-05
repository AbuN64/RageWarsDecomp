#include "Engine/session.h"
#include "Ai/Weapon/weapon.h"
#include "Ai/Nav/Patrol/patrol.h"
#include "frontend_symbols.h"
#include "Engine/graphics_math.h"
#include "Common/navigation_graph.h"
#include "Ai/shared_pickupgoalnode.h"
#include "include_asm.h"
#include "Common/world.h"
#include "Common/aiprofile.h"
#include "Render/player_controller_reset_views.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "types.h"
#include <PR/gbi.h>
#include "Common/gameplay_camera.h"
#include "Common/libsn_and_resident_callbacks.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/sessionhandlerrow.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Common/game_session.h"
#include "Common/gameplay_reactions.h"
#include "Render/shared_reactioninteraction.h"
#include "Common/menu_match_globals.h"
#include "Common/level_actor.h"
#include "Common/shared_gameslot.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Common/vector4f.h"
#include "Common/effectrender.h"
#include "Common/runtime_declarations.h"
#include "Common/triple.h"
#include "Ai/playerai.h"
#include "Common/gameplay_reaction_rules.h"
#include "Common/model_render.h"
#include "Common/frag_tag_scores.h"
#include "Weapons/player_movement_interfaces.h"
#include "Render/player_spawn_placement.h"
#include "Common/sharedplayer.h"
#include "Common/integerstate2c.h"
#include "Common/multiplayeroptions.h"
#include "Common/resident_event_handler.h"
#include "Common/resourceloadstate.h"
#include "Fx/contpad_initcontrollerinput.h"
#include "Achieve/achieve.h"
#include "Common/gameplay_transition.h"
#include "Common/level_track.h"
#include "Common/ai_behaviour_types.h"
#include "Ai/player_drawtintedplayer.h"
#include "Achieve/achieve_match_setup.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Ai/Player/player_resetplayerforround.h"
#include "Ai/Player/player_startplayeranimation.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Game/builddirectionmatrix.h"
#include "Geometry/geometry_drawblendparts.h"
#include "Gobjinst/gobjinst_requestanimatedmodelvariant.h"
#include "Gsky/sky_postscaledscreenmessage.h"
#include "Menu/Items/Scene/scene_updatependingobjects.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
#include "Particle/particle_releaseownerlistoneeffects.h"
#include "Particle/particle_updatesystem.h"
#include "Playerai/playerai__playerai.h"
#include "Render/control_cycleactorsnapshotmode.h"
#include "Render/playerai_toggleforcemarker.h"
#include "Render/setn64_updatefadetransition.h"
#include "Weapons/playerai_applystun.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Scene/cache_allocateresourceat.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Engine/Setn64/setn64_cleardepthrect.h"
#include "Engine/Scene/scene_findtrackedactors.h"
#include "Ai/ai_shared_symbols.h"
#include "Common/pakqueuestate.h"
#include "Ai/playerai_symbols.h"
#include "Common/shared_optionsscreen.h"
#include "Common/gameplay_round_rules.h"
#include "Common/loadout.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Common/rendercounters.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/shared_menureply.h"
#include "Common/animationtriggerdefinition.h"
#include "Common/self.h"
#include "Common/viewflags.h"
#include "Weapons/actor_requestactorstate.h"
#include "Common/particle_lighting.h"
#include "Common/font_style_and_glyph_operations.h"
#include "Weapons/weaponai_drawredmarkerquad.h"
#include "Scene/cache_requestresource.h"
#include "Render/setn64_getpacksection.h"
#include "Fx/normalize_vector.h"
#include "Ai/Player/playerai_findtransientplayer.h"
#include "Audio/voice.h"
#include "Engine/Instance/gobjinst.h"
#include "Engine/Instance/gobjinst_getactoroffsetpositionandmodel.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Gsky/gsky_findscreenmessage.h"
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#include "Weapons/player_updatefragtagselection.h"
#include "Gobjinst/gameobject_loadmodel.h"
#include "Ai/player_ammo_gift.h"
#include "Ai/Player/player_updatefragtagselection_data_player_updatefragtagselection_data.h"
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Render/soundelement_playflatsound.h"
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Engine/Audio/Voice/voice.h"
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Ai/Player/player_model_and_held_weapon_rendering.h"
#include "Ai/Playerai/playerai_playerai.h"
#include "Ai/player_updatefragtagselection.h"
#endif

/* Steps an animation cursor one frame: looks up the clip in g_world_AchieveUpdateresultsscreen, keeps the previous frame,
   and moves forward in states 1 and 2 or backward in states 3 and 4; at either end a looping clip
   (mode 1) wraps and a ping-pong clip (mode 0) reverses direction. */


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


void Playerai_InitializeRouteCursor(RouteCursorState *cursorState, s32 initialState, void *position) {
    cursorState->state = 1;
    cursorState->clip = initialState;
    cursorState->frame = Scene_FindNearestRouteFrame(&g_world, initialState, position);
    cursorState->previous = 0;
}


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
    char unusedStackPadding[0x10]; /* reserves the original stack frame size */
}


void Playerai_DrawAnimatedSprite(char *object, char *camera) {
    f32 first[16];
    f32 second[16];
    s32 output[4];
    Gfx *command;
    f32 x;
    f32 y;
    f32 z;
    f32 viewRight;
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
    viewRight = ((GameplayCamera *)(camera))->viewWidth + x;
    SetN64_ClearDepthRect(&g_gameSession, (s32)x, (s32)viewRight, (s32)y, (s32)z, 0);

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
static inline char *reactionText(void *text, MenuSettings *settings) { return ((char **)text)[settings->language]; }
#else
static inline char *reactionText(void *text, MenuSettings *settings) { return *(char **)text; }
#endif


static inline void nextMessage(s32 *next) {
    (*next)++;
    *next %= 4;
}

void Player_PostKillMessages(Shared_ReactionPlayer *killer, Shared_ReactionPlayer *victim, Shared_ReactionInteraction *interaction) {
    MenuSettings *settings = &g_frontendScreenStatus.settings;
    MatchModes *modes;
    if (!settings->local) return;
    if (killer != victim) {
        if (!killer->statistics->isHuman) return;
        modes = &g_frontendScreenStatus.modes;
        if (modes->tag) {
            SetN64_CopyString(killer->messages[killer->messageNext], reactionText(&g_tagKillerMessage, settings));
            SetN64_CopyString(killer->messages[killer->messageNext]+10, victim->statistics->name);
            if (killer->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, killer->owner, killer->messages[killer->messageNext], 1.5f);
            nextMessage(&killer->messageNext);
            SetN64_CopyString(victim->messages[victim->messageNext], reactionText(&g_tagVictimMessage, settings));
            SetN64_CopyString(victim->messages[victim->messageNext]+11, killer->statistics->name);
            if (victim->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, victim->owner, victim->messages[victim->messageNext], 1.5f);
        } else {
            if (!modes->captureFlag) return;
            SetN64_CopyString(killer->messages[killer->messageNext], reactionText(&g_captureFlagKillerMessage, settings));
            SetN64_CopyString(killer->messages[killer->messageNext]+10, victim->statistics->name);
            if (killer->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, killer->owner, killer->messages[killer->messageNext], 1.5f);
            nextMessage(&killer->messageNext);
            SetN64_CopyString(killer->messages[killer->messageNext], reactionText(&g_captureFlagKillerFollowupMessage, settings));
            if (killer->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, killer->owner, killer->messages[killer->messageNext], 1.5f);
            nextMessage(&killer->messageNext);
            SetN64_CopyString(victim->messages[victim->messageNext], reactionText(&g_tagVictimMessage, settings));
            SetN64_CopyString(victim->messages[victim->messageNext]+11, killer->statistics->name);
            if (victim->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, victim->owner, victim->messages[victim->messageNext], 1.5f);
            nextMessage(&victim->messageNext);
            SetN64_CopyString(victim->messages[victim->messageNext], reactionText(&g_captureFlagVictimFollowupMessage, settings));
            if (victim->owner) Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, victim->owner, victim->messages[victim->messageNext], 1.5f);
        }
    }
    nextMessage(&victim->messageNext);
}

/* TurretPlayerRelation, interaction and score views used to select reactions and record statistics. */

/* Selects and records a player's reaction to an interaction. */

/* Reaction thresholds are loaded from the cartridge's shared float table. */



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
                            sourceForwardProjection =
                                ((damagedPlayer->positionX - reaction_source->positionX) * -facingSine)
                                + ((damagedPlayer->positionZ - reaction_source->positionZ) * -Math_Cosf(attacker->heading));
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
                            if ((victimKillStatistics->isHuman == 1)
                                    && (g_gameSettings.counters.m_bFragTagOn != 0)) {
                                victimKillStatistics->kills_special[killerPlayerIndex]++;
                            } else {
                                damagedPlayer->statistics->kills_normal[killerPlayerIndex]++;
                            }
                            victimPlayerIndex = Player_GetPlayerIndex(&g_playerViewRenderContext, (u32) damagedPlayer);
                            if ((damagedPlayer->statistics->isHuman == 1)
                                    && (g_gameSettings.counters.m_bFragTagOn != 0)) {
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
                                    if (g_matchRoundCounters.m_bFragTagOn != 0) {
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
                                    } else if (g_matchRoundCounters.m_bCTFOn != 0) {
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
        if (g_matchRoundCounters.m_bFragTagOn && player->controls->fragTagEnabled) actor->team = (u8)g_matchRoundCounters.m_nFragTagSkin;
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
            if (g_matchRoundCounters.m_bFragTagOn && player->controls->fragTagEnabled) actor->team = (u8)g_matchRoundCounters.m_nFragTagSkin;
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
        attributes = (char *)g_controllerProfiles + (s32)attributes;
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
    (&((PlayerControllerReleaseView *)(object))->velocity)->x = (&((PlayerControllerReleaseView *)(object))->velocity)->y =
        (&((PlayerControllerReleaseView *)(object))->velocity)->z = 0;
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


static __inline__ s32 containsFire(s16 **entries, s32 effect) {
 s32 i = 0; s16 **p = entries;
 search:
  if (*p == 0) return 0;
  if ((*p)[2] == effect) return 1;
  i++; p++;
 if (i<3) goto search;
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
        if (!aimPlayer->controlled && g_playerWeaponClassMode == 1) entries = &table->weaponClass;
        else entries = table->computerClasses;
        if (containsFire(entries, effect)) goto fire;
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
        if (aimPlayer->animation == 4100) {timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[0];}
        else if (aimPlayer->animation == 4000) {timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[1];}
        else {
            if (aimPlayer->weaponKind == 8) aimPlayer->animation = 4100;
            else aimPlayer->animation = 4000;
            goto clear;
        }
        goto consume;
    }
    if (aimPlayer->animation == 1) aimPlayer->animation = 4400;
    else if (aimPlayer->animation == 4400) { timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[2]; goto consume; }
    else if (aimPlayer->animation == 2600) aimPlayer->animation = 4405;
    else if (aimPlayer->animation == 4405) { timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[3]; goto consume; }
    else if (aimPlayer->animation == 20) aimPlayer->animation = 4420;
    else if (aimPlayer->animation == 4420) { timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[4]; goto consume; }
    else if (aimPlayer->selectedWeapon == 0 && aimPlayer->weaponKind == 8) aimPlayer->animation = 24158;
    else {
            if (aimPlayer->animation == 24158) { timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[5]; goto consume; }
        if ((u32)(aimPlayer->animation - 24100) < 3) aimPlayer->animation = 24150;
        else if (aimPlayer->animation == 24150) { timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[7]; goto consume; }
        else if (aimPlayer->animation == 24105) aimPlayer->animation = 24153;
        else if (aimPlayer->animation == 24153) { timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[7]; goto consume; }
        else if (aimPlayer->animation == 24106) aimPlayer->animation = 24154;
        else if (aimPlayer->animation == 24154) { timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[6]; goto consume; }
        else if (aimPlayer->animation == 24107) aimPlayer->animation = 24155;
        else if (aimPlayer->animation == 24155) { timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[7]; goto consume; }
        else if (aimPlayer->animation == 24108) aimPlayer->animation = 24156;
        else {
                    if (aimPlayer->animation == 24156) { timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[7]; goto consume; }
            if (aimPlayer->animation == 24109) aimPlayer->animation = 24157;
            else if (aimPlayer->animation == 24157) { timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[7]; goto consume; }
            else { aimPlayer->firing = 0; goto spawn; }
        }
    }
    goto clear;
ordinary:
    timer = aimPlayer->animationTimer; amount = g_playerWeaponFireDurations[7];
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


void Player_ResetPlayerWeapons(struct Player *player) {
    Shared_Game *game;
    s32 i;
    s32 j;
    s32 actionSlot;
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
            for (actionSlot = 0; actionSlot < 22; actionSlot++) {
                if (player->actions[actionSlot][1] == 1) {
                    break;
                }
            }
            if (actionSlot < 22) {
                player->weapon = actionSlot;
                player->selectedAction = actionSlot;
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


extern f32 Graphu64_GetPointDistance(f32 *a, f32 *b);
struct CNavData_t; extern s32 Portal_FindNearestPointIndex(struct CNavData_t *pointSet, void *point);


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
    Player *other;
    s32 floor;
    s32 cell;
    Player_ReleaseObjectHandles(player);
    Control_SetProfileMode(((Player *)player)->weaponAnimation, 0);
    world = &g_world;
    if (reset) {
        ((Player *)player)->reservedWord864 = 0;
        ((Player *)player)->reservedWord868 = 0;
    }
    if (g_frontendScreenStatus.settings.local) {
        count = Scene_FindPlacedObjectsByKey(world, -1, model, points, 32);
        best = -1;
        bestDistance = 0.0f;
        for (i = 0; i < count; i++) {
            distance = k_spawnNearestPlayerInitialDistance;
            for (other = g_transientPlayerList.actorList; other; other = other->next) {
                f32 d = Graphu64_GetPointDistance(&points[i].pos, &other->pos);
                if (d < distance) distance = d;
            }
            if (bestDistance <= distance) {
                bestDistance = distance;
                best = i;
            }
        }
        if (best == -1) goto fallback;
        ((Player *)player)->actorParts[1].position0 = points[best].pos;
        ((Player *)player)->pos = ((Player *)player)->actorParts[1].position0;
        ((LevelActor *)player)->yaw = ((Player *)player)->actorParts[1].yaw = points[best].heading;
        floor = Scene_FindFloorPolygon(&g_world, &((Player *)player)->pos);
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
        ((Player *)player)->actorParts[1].position0 = single.pos;
        ((Player *)player)->pos = ((Player *)player)->actorParts[1].position0;
        ((LevelActor *)player)->yaw = ((Player *)player)->actorParts[1].yaw = single.heading;
        floor = Scene_GetModelSectionTwoRecord(world, single.modelSectionIndex);
    }
    ((Player *)player)->actorParts[1].model = floor;
    ((Player *)player)->actorParts[0].model = floor;
    Player_InitActorHudState(player);
    goto done;
fallback:
    Scene_SetSelection(&g_world, model, scale);
done:
    cell = Portal_FindNearestPointIndex(&g_navigationGraph, &((Player *)player)->pos);
    ((AiController *)((Player *)player)->controller)->current = cell;
}

const float g_PlayeraiInitializeMovementAndAimConstantWordsUsRevision[2] = {
    1.0f, 1.0f,
};

/* Reports a win when, for some player, the scores earned against the other seven players reach the match's total score target. */
s32 Player_CheckTotalScoreWin(Root *);
s32 Player_CheckTeamPointWin(struct Shared_World *);


/* Updates round state, player health and round-start presentation. */

typedef struct FragTagPlayerStateView FragTagCandidatePlayerView;

typedef struct FragTagSelectionProfileView FragTagCandidateProfileView;

typedef struct FragTagPlayerInputView FragTagSelectedPlayerView;

typedef struct FragTagCameraStateView FragTagCameraView;

typedef struct FragTagTeamProfileView FragTagSelectedTeamProfileView;

typedef struct FragTagAssignmentProfileView FragTagPreviousProfileView;


/* Provider passes the position identity as a 32-bit address; see SoundElement_PlaySoundAtPosition_PlayerUpdatefragtagselection
 * and the published Weapon_UpdateIdleWeaponSelection caller. */

/* Advances an elimination round when rule g_resultReplayPending is on and not paused (Cinema_IsSequenceActive,
   Cinema_IsSequenceInWindow): counts the players still in, clears g_ctfWaitingPlayerFlag while one is waiting, then by the
   round state of g_matchRoundCounters revives the first waiting player (crediting a point in state 1,
   scheduling g_ctfMode = 3 otherwise) or moves to state 2, and ends the round through Playerai_EndRound
   when Player_CheckTeamPointWin_PlayerUpdatefragtagselection reports it over. */

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
                        if ((eligiblePlayerCount == -1) && (randomPlayerQuotient == S32_MIN_BITS)) {

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
                        if ((eligiblePlayerCount == -1) && ((nextChosenIndex / eligiblePlayerCount) == S32_MIN_BITS)) {

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
                                    OnScreen_DrawSpriteResource(507, 0,
                                        (s16) (s32) ((allPlayersView->viewportX + scaled5x) - (allPlayersScaleX * banner_size)),
                                        (s16) (s32) ((allPlayersView->viewportY + scaled5y) - (allPlayersScaleY * banner_size)),
                                        allPlayersScaleX, allPlayersScaleY, 1);
                                }
                                player->profile->fragTagEnabled = 1;
                                switch (g_fragTagSelectSoundVariant) {
                                case 0:
                                    SoundElement_PlaySoundAtPosition(6305, player->position, (intptr_t)&player->position, -1);
                                    break;
                                case 1:
                                    SoundElement_PlaySoundAtPosition(6505, player->position, (intptr_t)&player->position, -1);
                                    break;
                                case 2:
                                    SoundElement_PlaySoundAtPosition(6405, player->position, (intptr_t)&player->position, -1);
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
                if ((eligiblePlayerCount == -1) && (((s32) case3_entry->m_FragTagPlayerPos / eligiblePlayerCount) == S32_MIN_BITS)) {

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
                    OnScreen_DrawSpriteResource(507, 0,
                        (s16) (s32) ((rotatingView->viewportX + scaled_x)
                            - ((rotatingViewWidth / (f32) g_hudReferenceViewportWidth) * g_fragTagRotatingViewIconOffset)),
                        (s16) (s32) ((rotatingView->viewportY + scaled_y) - (rotatingScaleY * g_fragTagRotatingViewIconOffset)),
                        (rotatingViewWidth / (f32) g_hudReferenceViewportWidth), rotatingScaleY, 1);
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
                        SoundElement_PlaySoundAtPosition(6305, rotatingPlayer->position, (intptr_t)&rotatingPlayer->position, -1);
                        break;
                    case 1:
                        SoundElement_PlaySoundAtPosition(6505, rotatingPlayer->position, (intptr_t)&rotatingPlayer->position, -1);
                        break;
                    case 2:
                        SoundElement_PlaySoundAtPosition(6405, rotatingPlayer->position, (intptr_t)&rotatingPlayer->position, -1);
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
                if ((eligiblePlayerCount == -1) && (((s32) case4_entry->m_FragTagPlayerPos / eligiblePlayerCount) == S32_MIN_BITS)) {

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
                    OnScreen_DrawSpriteResource(507, 0,
                        (s16) (s32) ((chosenView->viewportX + scaled_x4)
                            - ((chosenViewWidth / (f32) g_hudReferenceViewportWidth) * g_fragTagChosenViewIconOffset)),
                        (s16) (s32) ((chosenView->viewportY + scaled_y4) - (chosenScaleY * g_fragTagChosenViewIconOffset)),
                        (chosenViewWidth / (f32) g_hudReferenceViewportWidth), chosenScaleY, 1);
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
                        SoundElement_PlaySoundAtPosition(6305, chosenPlayer->position, (intptr_t)&chosenPlayer->position, -1);
                        break;
                    case 1:
                        SoundElement_PlaySoundAtPosition(6505, chosenPlayer->position, (intptr_t)&chosenPlayer->position, -1);
                        break;
                    case 2:
                        SoundElement_PlaySoundAtPosition(6405, chosenPlayer->position, (intptr_t)&chosenPlayer->position, -1);
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
                                    OnScreen_DrawSpriteResource(507, 0,
                                        (s16) (s32) ((flippedView->viewportX + scaled6x) - (flippedScaleX * banner_size)),
                                        (s16) (s32) ((flippedView->viewportY + scaled6y) - (flippedScaleY * banner_size)),
                                        flippedScaleX, flippedScaleY, 1);
                                }
                                flippedPlayer->profile->fragTagEnabled = 1U;
                                switch (g_fragTagSelectSoundVariant) {
                                case 0:
                                    SoundElement_PlaySoundAtPosition(6305, flippedPlayer->position, (intptr_t)&flippedPlayer->position, -1);
                                    break;
                                case 1:
                                    SoundElement_PlaySoundAtPosition(6505, flippedPlayer->position, (intptr_t)&flippedPlayer->position, -1);
                                    break;
                                case 2:
                                    SoundElement_PlaySoundAtPosition(6405, flippedPlayer->position, (intptr_t)&flippedPlayer->position, -1);
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

/* Checks accumulated opponent scores and updates the completion flag. */


/* Reports whether a team's points reached the point target (none when it is 0); in a trial it records
   in humanWon whether that team is the human side's and, when it is not, keeps looking. */

/* Ends a match when its conditions are met, unless a menu or pause is up (Cinema_IsSequenceActive,
   Cinema_IsSequenceInWindow), the match is locked of the rules g_matchRoundCounters or the game g_matchEndingTeamWheelClose disallows
   it: outside a cutscene (Menu_CountLiveNodes_PlayerUpdatefragtagselection) the time limit of the rules counts down by
   the frame time while Playerai_CountActivePlayers says the clock runs and ends the match when it expires (clearing
   humanWon of the rules in trial kind 3); outside a cutscene a score limit reached through Player_CheckScoreLimit
   ends it while the rules' limit is set and 0x54 is clear; and when g_selectedProfileHealthOptionEnabled asks, it counts
   the active players among the first eight and how many of them are out, ending the match once all
   are out, directly or, when a mode 14 player takes part, only after the rules' round count
   reaches 3, marking humanWon. */


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




s32 Player_CheckTotalScoreWin(Root *root) {
    GameRules *initial = g_gameSession.match.rules; GameRules *state;
 FragTagPlayerListNode *node; int i, sum, skip;
 if (initial->totalScoreTarget == 0) return 0;
 node = root->players; state = initial;
 for (;node;node = node->next) {
  skip = Player_GetPlayerIndex(root, node);
  sum = 0;
  for (i = 0;i<8;i++) {
   if (i != skip) {
    sum += node->scores->score[i];
    if (sum >= state->totalScoreTarget) {
     { unsigned char controllerMode = g_gameSession.match.settings.trialKind; if (controllerMode) {
      if (node->playerIndex<4) {state->humanWon = 1;return 1;}
      state->humanWon = 0;
      if (controllerMode == 1) continue;
     }
     } return 1;
    }
   }
  }
 }
 return 0;
}

s32 Player_CheckTeamPointWin(struct Shared_World *world) {
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

    if (g_gameplayRoundState.state == 11 || g_gameplayRoundState.state == 8) {
        return;
    }
    actor = ((Shared_MenuData *)(game))->transientPlayers;
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

    node = ((Shared_MenuData *)(game))->transientPlayers;
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
                                linkedOwner = ((Player *)(linked))->camera;
                                if (linkedOwner != 0) {
                                    CVector3 delta;

                                    delta.x = ((GameplayCamera *)(linkedOwner))->position.x -
                                              ((CachedPlayerModelView *)(actor))->positionX;
                                    delta.y = 0.0f;
                                    delta.z = ((Player *)(linked))->camera->position.z -
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

void Playerai_DrawPlayerModelsForView(Shared_MenuData *game, s32 view) {
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
    for (player = game->transientPlayers; player != 0; player = ((FragTagPlayerListView *)(player))->nextPlayer) {
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
                Geometry_QueueDirectModel(Scene_GetIndexedModelResource(&g_world, model), (char *)&((Player *)player)->transform1600, &g_defaultParticleLighting, 0, -1);
            }
        }
        if (((FragTagPlayerListView *)(player))->weaponHandle != 0
                && ((FragTagPlayerListView *)(player))->alternateFireState != 0
                && ((FragTagPlayerListView *)(player))->weaponHandle == view) {
            Weaponai_DrawRedMarkerQuad((char *)&((SharedPlayer *)player)->views1C.view2E8_27.weapon,
                (char *)&((SharedPlayer *)player)->views1C.view458_29.ammo);
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



static inline void buildForceMarkerTransform(Player *player, s32 attract, CVector3 *normal) {
    Matrix matrix;
    CVector3 offset;
    BuildDirectionMatrix(&matrix, normal);
    Graphu64_ScaleVector(&offset, normal, 5.12f);
    Graphu64_AddVec3(&offset, &offset, &player->aimPosition);
    TranslateMatrix(&matrix, offset.x, offset.y, offset.z);
    SwapMatrixUpForward((struct CMatrix4 *)&matrix);
    Graphu64_ConvertMatrixToFixed(&matrix, player->transform1600);
}
extern const float g_forceMarkerDurationEuropean;
void Playerai_ToggleForceMarkerEuropean(Player *player, s32 attract) {
    void *screen;
    if (player->aimTarget != 0) {
        if (player->zoom > 0.0f) {
            player->zoom = 0;
            SoundElement_PlayFlatSound(1400);
            screen = player->camera;
            if (screen == 0) return;
            Camera_PostScreenMessage((void *)&g_frontendScreenStatus, screen,
                (u8 *)g_forceMarkerRemovedTextEuropean[g_frontendScreenStatus.settings.language]);
        } else {
            player->aimPosition = player->aimPoint;
            player->zoomMode = attract;
            player->zoom = g_forceMarkerDurationEuropean;
            buildForceMarkerTransform(player, attract, &player->aimNormal);
            SoundElement_PlayFlatSound(1400);
            screen = player->camera;
            if (screen == 0) return;
            if (attract != 0) Camera_PostScreenMessage((void *)&g_frontendScreenStatus, screen,
                (u8 *)g_forceMarkerAttractTextEuropean[g_frontendScreenStatus.settings.language]);
            else Camera_PostScreenMessage((void *)&g_frontendScreenStatus, screen,
                (u8 *)g_forceMarkerRepulseTextEuropean[g_frontendScreenStatus.settings.language]);
        }
    }
}
#endif

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

const float k_PlayerUpdatefragtagselectionData[8] = {
    0.5f, 32.0f, 0.5f, 32.0f,
    0.5f, 32.0f, 0.5f, 32.0f,
};

const char s_playerAnimObjectInfoText[24] = "player anim object info";

const float g_playerAiActorHalfConstant[1] = {
    0.5f,
};

const float k_PlayeraiUpdatewalkingmovementData[16] = {
    5.12f, 5.12f, 11.25f, 5.12f,
    6.0f, 1e+01f, 8.0f, 12.0f,
    8.0f, 23.0f, 8.0f, 23.0f,
    8.0f, 23.0f, 7.0f, 23.0f,
};

/* Leading word of the target-facing distance limit pair (read as f32[], symbol_addrs name); Playerai_UpdateTargetFacing
   (PLAYERAI_INITIALIZEPLAYERHEALTH.CPP) only reads element [1], the f32 1024.0f right after it. */
s32 g_playerTargetFacingDistanceLimits = 1024;

/* The colon drawn between minutes and seconds on the match countdown; identical in every version. */
const char g_matchCountdownSeparatorText[4] __attribute__((aligned(4))) = ":\000\000\000";

#if !(defined(VERSION_US_REV1))
const float k_PlayeraiBuildforcemarkertransformData[1] = {
    15.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_PlayeraiBuildforcemarkertransformData[1] = {
    15.0f,
};
#endif

const float k_PlayeraiBuildforcemarkertransformUnit[1] = {
    1.0f,
};

#if !(defined(VERSION_US_REV1))
const float k_playeraiForceMarkerTransformReach[1] = {
    15.0f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_playeraiForceMarkerTransformReach[1] = {
    15.0f,
};
#endif

const float k_playeraiForceMarkerTransformRange[1] = {
    105.0f,
};
