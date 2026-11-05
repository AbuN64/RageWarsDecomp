#include "Ai/Nav/roam.h"
#include "frontend_symbols.h"
#include "Common/output.h"
#include "Common/navigation_graph.h"
#include "Common/world.h"
#include "Common/vector4f.h"
#include "Common/shared_worldfunc.h"
#include "Common/runtime_declarations.h"
#include "Common/gameplay_transition.h"
#include "Common/round_state_variants.h"
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Common/rendercounters.h"
#include "Common/sharedplayer.h"
#include "Common/selectionscreenstate.h"
#include "Render/player_controller_reset_views.h"
#include "Common/results.h"
#include "Engine/Cache/list.h"
#include "Weapons/actor_requestactorstate.h"
#include "Render/soundelement_playflatsound.h"
#include "Render/player_spawn_placement.h"
#include "Ai/Player/playerai_buildforcemarkertransform.h"
#include "Ai/Player/player_death__playerai.h"
#include "Ai/Player/player_placeplayerforround.h"
#include "Ai/Player/player_startplayeranimation.h"
#include "Engine/Instance/gobjinst_getactoroffsetpositionandmodel.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Engine/session.h"
#include "Gsky/sky_postscaledscreenmessage.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Particle/ghot_dispatchattachmenteffects_data.h"
#include "Particle/particle_releaseownerlistoneeffects.h"
#include "Render/control_cycleactorsnapshotmode.h"
#include "Render/playerai_toggleforcemarker.h"
#include "Ai/player_death_motion.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Camera/gsky_setdamageeffect.h"
#include "Ai/player_message_history.h"
#include "Ai/player_startsourceeffect__player.h"
#include "Ai/ai_shared_symbols.h"
#include "Ai/shared_pickupgoalnode.h"
#include "Common/ballisticparams.h"
#include "Common/triple.h"
#include "Common/aiprofile.h"
#include "Common/shared_particleinstance.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Gobjinst/player_drawtintedplayer_data.h"
#include "Ai/Player/player_updatefragtagselection_data_player_updatefragtagselection_data.h"
#include "Common/geometry_blend_and_instance_views.h"
#include <PR/gbi.h>
#include "Common/sessionhandlerrow.h"
#include "Fx/fx_drawboundedparticlequads.h"
#include "Engine/Geometry/geometry_setupmaterial.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/gameplay_camera.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/multiplayeroptions.h"
#include "Common/player_sequence_state.h"
#include "Common/resourceloadstate.h"
#include "Gobjinst/gobjinst_buildactorpose.h"
#include "Menu/Items/Scene/scene_registeractorinscenelists.h"
#include "Common/game_session.h"
#include "Engine/Setn64/setn64_cleardepthrect.h"
#include "Ai/Player/player_drawredmarkerprism_playerai.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Ai/ai_functions.h"
#include <platform_sdk.h>
#include "Common/resident_event_handler.h"
#include "Common/obj.h"
#include "Fx/normalize_vector.h"
#include "Ai/Player/playerai_computeaimrotation.h"
#include "Game/builddirectionmatrix.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Engine/Instance/Gobjinst/gastate_advancerootmotion_data.h"
#include "Common/mtx.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Ai/player_symbols.h"
#include "Common/approachlocation.h"
#include "Common/Lone/particle_collision_probe_result.h"
#include "Weapons/aim_types.h"
#include "Ai/Player/playerai_updateaimandlockmarker.h"
#include "Ai/Player/player_buildplayerviewtransform.h"
#include "Libsn/nav_isballisticarcobstructed_data.h"
#include "Common/Lone/collision_current_actor.h"
#include "Common/legacy_collision_actor.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Gsky/gsky_projecttoscreen.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "include_asm.h"
#include "Common/audio_voice_slots.h"
#include "Common/menu_model_preview.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Common/gameplay_movement.h"
#include "Common/effectrender.h"
#include "Common/objb.h"
#include "Ai/Player/player_updateplayereffectlights.h"
#include "Engine/gdynlight.h"
#include "Placeplayerlight/placeplayerlight.h"
#include "Ai/player_light_pattern_names.h"
#include "Ai/Player/playerai_drawammocounters.h"
#include "Weapons/player_movement_interfaces.h"
#include "Common/menu_match_globals.h"
#include "Engine/Audio/channel.h"
#include "Player_updateplayercamera/player_updateplayercamera.h"
#include "Graphu64/graphu64_buildlookatmatrix.h"
#include "Engine/Audio/T2SoundElement.h"
#include "Ai/cteamselect.h"
#include "Common/animationtriggerdefinition.h"
#include "Data/Player_swimming/player_swimming_sound_ids.h"
#include "Weapons/g_playerswimconstants.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Engine/ccinema_drawmessages.h"
#include "Menu/pak_load.h"
#include "Common/frag_tag_scores.h"
#include "Ai/Player/playerai_entermovingsequencestate_data.h"
#include "Common/viewflags.h"
#include "Data/Weapon_callbacks/playerai_initializeplayerhealth.h"
#include "Engine/Unicol/unicol.h"
#include "Ai/Playerai/playerai_playerai.h"
#include "Cbarrel/barrel_spawnactoreffect.h"
#include "Common/brain.h"
#include "Common/group.h"
#include "Common/reserved_shared_declarations.h"
#include "Frontend/frontend_opengameplayfrontend.h"
#include "Ui/X_files/x_plus.h"
#include "Engine/Audio/T2soundelement/sound_context_control.h"
#include "Common/weapon_select_brain.h"
#include "Common/player_action_and_pose_views.h"
#include "Ai/Player/player_updatefragtagselection_data__player_updatefragtagselection_data.h"
#include "Playerai/g_playerstext.h"
#include "Weapons/player_updatefragtagselection.h"
#include "Engine/control.h"
#include "Ui/Tsmos/tsmos_activatecontrollerstate.h"
#include "Scene/cache_allocateresourceat.h"
#include "Weapons/playerai_applystun.h"
#include "Camera/Gsky/gsky_startfade.h"
#include "Common/shared_optionsscreen.h"
#include <PR/abi.h>
#include "Common/loadout.h"
#include "Common/player_score_table.h"
#include "Common/player_pool_and_inode_cache_views.h"
#include "Ai/Player/player_model_and_held_weapon_rendering.h"
#include "Ai/Player/playerai_findtransientplayer.h"
#include "Gsky/gsky_loadprojectionmatrix.h"
#include "Gobjinst/gobjinst_buildactortransform.h"
#include "Common/actor_header.h"
#include "Common/level_actor.h"
#include "Common/resultsoptionsscreen.h"
#include "Common/playerprofiles.h"
#include "Engine/rumble.h"
#include "Gobjinst/gameobject_loadmodel.h"
#include "Engine/Cinema/cinema.h"
#include "Render/weapon_initializechargeandstartupcues_data.h"
#include "Audio/voice.h"
#include "Engine/Audio/Voice/voice.h"
#include "Particle/particle_updatesystem.h"
#include "Common/particle_lighting.h"
#include "Geometry/geometry_drawblendparts.h"
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#include "Common/gameplay_reactions.h"
#include "Render/shared_reactioninteraction.h"
#include "../../sdk/include/AUDIO/sprintf.H"
#include "Common/player_record_and_fragtag_views.h"
#include "Common/gameplay_round_rules.h"
#include "Common/ai_behaviour_types.h"
#include "Common/actorresourceheader.h"
#include "Scene/cache_requestresource.h"
#include "Render/setn64_getpacksection.h"
#include "Gfx/Text/playerai_applydamageovertime_data.h"
#include "Ai/Player/playerai_applydamageovertime__player_updatefragtagselection_data.h"
#include "Engine/Instance/gobjinst.h"
#include "Ai/Player/player_death_playerai.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Gfx/player_updatefragtagselection_data.h"
#include "Common/track_spline.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Data/Gfxdata/audio_decodeframe_data.h"
#include "Ai/playerai_applydamageovertime_data__player_updatefragtagselection_data.h"
#include "World/playerprofile.h"
#include "Common/Lone/g_currentstagepreset.h"
#include "Gfx/Text/player_camera_callback.h"
#include "Sound/player_movement_scalar_view.h"
#include "Common/probe.h"
#include "Camera/gsky_resetheadbob.h"
#include "Sound/externs.h"
#include "Engine/contpad.h"
#include "Fx/contpad_initcontrollerinput.h"
#include "Common/pakqueuestate.h"
#include "Common/cache_releaseresource.h"
#include "Common/soundinfo.h"
#include "World/playerai_respawnfragtagplayer.h"
#include "Engine/gregion.h"
#include "Sound/playerai_sequence_waits.h"
#include "Ai/ai_address_labels.h"
#include "Ai/nav_symbols.h"
#if ((defined(VERSION_EU))) || ((defined(VERSION_EU_X)))
#include "Data/Player_callbacks/playerstate_link_record_rom_link_targets.h"
#endif
#include "Data/rest_source_records.h"
#include "Ui/Tsmos/Screens/pakinterface_loadgame.h"
#include "Ai/cbarrel.h"
#include "Ai/playerai_updatedelayeddamage__player.h"
#include "Ai/Weapon/weapon.h"

/* Player state, projectiles, effects and linked-actor transitions. */
/* Apply player transitions, regional control gates, and localized linked-actor notifications. */






extern const Shared_HeightBonuses g_playerDeathHeightOffsets;
extern const f32 g_playerDeathMotionCenter;
extern const f32 g_playerDeathMovingSpeed;



                                                  /* size = 0x18 */




void *Portal_GetGraphPoint(void *, s32);
struct CNavData_t; s32 Portal_FindNearestPointIndex(struct CNavData_t *pointSet, void *point);
 CQuatern Gobjinst_BuildActorAimQuaternion(char *);




struct EffectSlot;

s32 XPlus_NextRandomInteger(void);





extern char g_actorParticleEffectSystem[];


extern CNavData g_navigationGraph;










 /* unable to generate initializer: non-zero padding; const */








void Playerai_HandlePlayerDeath(struct Player *player, void *attacker, s32 damageFlags, s32 state) {
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

    Control_SetProfileMode(((struct Player *)player)->weaponAnimation, 0);
    if (((struct Player *)player)->pose == 39) {
        Player_SetPlayerState(player, attacker, 2);
    }
    ((struct Player *)player)->reservedWord1218 = 0;
    Link_DispatchActorLinks(attacker, 1, attacker);
    Player_ReleaseObjectHandles(player);
    Playerai_ResetDamageTimers((s32)player);
    ((struct Player *)player)->cooldown = 0;
    ((struct Player *)player)->zoom = 0;
    Particle_ReleaseOwnerListTwoEffects(&g_actorParticleEffectSystem, (s32)player);
    flow = &g_transientPlayerList.flow;
    if ((flow->active != 0)
        && gameplayTransitionEnabled(player->profile->enabled)
        && (i = 0, (((struct Player *)player)->profile->character == 14))) {
        flow->count = (s32) (flow->count + 1);
        playersGlobal = (struct Shared_GlobalPlayers *)&g_playerViewRenderContext;
        if (playersGlobal->count > 0) {
            settingsBase = &g_playerSettings;
            playerSettingsRecord = (struct Shared_PlayerSettingsRecord *)settingsBase;
            playerArrayOffset = 0;
settings_loop:
            do {
                roundPlayer = playersGlobal->players + playerArrayOffset;
                if (playerSettingsRecord->active != 0) {
                    if (((struct Shared_PlayerSettingsView *)settingsBase)->state == 1) {
                    ((struct Player *)roundPlayer)->actorState = (s32) ((struct Shared_PlayerSettingsView *)settingsBase)->state;
                    Player_ResetPlayerForRound(roundPlayer, playerSettingsRecord->character, 1);
                    roundPlayerModel = ((struct Player *)roundPlayer)->definition;
                    ((struct Shared_ModelView *)roundPlayerModel)->flags = (s32) (((struct Shared_ModelView *)roundPlayerModel)->flags & ~4);
                    Actor_RequestActorState(&((struct Player *)roundPlayer)->actorParts[1], &((struct Player *)roundPlayer)->actorParts[1].behaviorFlags, 2);
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
            ((struct Player *)player)->overkill = 0;
            Player_SetPlayerState(player, attacker, 46);
            return;
        } else {
            goto block_17;
        }
    } else {
block_17:
        if (g_frontendScreenStatus.settings.local != 0) {
            if ((((struct Player *)player)->ammo[0] > 0) || (((struct Player *)player)->ammo[1] > 0) || (((struct Player *)player)->ammo[2] > 0)) {
                ammoPickupMode = ((struct Player *)player)->slot;
                hasAmmoDrop = 0;
                switch (ammoPickupMode) {
case 0:
default:
                    ammoPickupType = ((struct Player *)player)->projectileIndex + 3033;
                    break;
case 1:
                    ammoPickupType = ((struct Player *)player)->projectileIndex + 3035;
                    break;
case 2:
                    ammoPickupType = ((struct Player *)player)->projectileIndex + 3037;
                    break;
case 3:
                    ammoPickupType = ((struct Player *)player)->projectileIndex + 3039;
                    break;
case 4:
                    ammoPickupType = ((struct Player *)player)->projectileIndex + 3041;
                    break;
case 5:
                    ammoPickupType = ((struct Player *)player)->projectileIndex + 3043;
                    break;
case 6:
                    ammoPickupType = ((struct Player *)player)->projectileIndex + 3045;
                    break;
case 7:
                    ammoPickupType = ((struct Player *)player)->projectileIndex + 3047;
                    break;
                }
                Scene_FindModelIdIndex(&g_world, ammoPickupType);
                existingAmmoPickup = ((struct Player *)player)->projectiles[((struct Player *)player)->projectileIndex];
                if (existingAmmoPickup != 0) {
                    ((struct Shared_ProjectileView *)existingAmmoPickup)->flags = (u16) (((struct Shared_ProjectileView *)existingAmmoPickup)->flags | 1);
                    retiredAmmoPickup = ((struct Player *)player)->projectiles[((struct Player *)player)->projectileIndex];
                    if (((struct Shared_ProjectileView *)retiredAmmoPickup)->flags & 8) {
                        SetN64_RecycleGlobalEffectNode(retiredAmmoPickup);
                    } else {
                        Scene_SetLevelRecordStateBit(&g_world, retiredAmmoPickup, 1);
                        Link_DispatchObjectLinks(((struct Shared_ProjectileView *)((struct Player *)player)->projectiles[((struct Player *)player)->projectileIndex])->source, 0x400, player);
                    }
                }
                ammoDropActorKind = ((struct Player *)player)->objectId;
                if (ammoDropActorKind == g_playerSpecialModelIds[0]) {
                    hasAmmoDrop = 0;
                } else if (ammoDropActorKind == g_playerSpecialModelIds[1]) {
                    hasAmmoDrop = 0;
                } else {
                    switch (XPlus_NextRandomInteger() % 3) {            /* switch 2; irregular */
                    case 0:                         /* switch 2 */
                        firstAmmoCount = ((struct Player *)player)->ammo[0];
                        firstAmmoDrop = 0;
                        if (firstAmmoCount != 0) {
                            firstAmmoRandom = XPlus_NextRandomInteger();
                            firstAmmoQuotient = firstAmmoRandom / firstAmmoCount;
                            if (firstAmmoCount == 0) {

                            }
                            if ((firstAmmoCount == -1) && (firstAmmoQuotient == S32_MIN_BITS)) {

                            }
                            firstAmmoDrop = firstAmmoRandom % firstAmmoCount;
                        }
                        if (firstAmmoDrop != 0) {
                            hasAmmoDrop = 1;
                            firstAmmoDropRecord = &g_pickupAmmoDefinitions[((struct Player *)player)->projectileBase + ((struct Player *)player)->projectileIndex];
                            firstAmmoDropRecord->firstAmmoDrop = (s16) firstAmmoDrop;
                            firstAmmoDropRecord->secondAmmoDrop = 0;
                            firstAmmoDropRecord->thirdAmmoDrop = 0;
                        }
                        break;
                    case 1:                         /* switch 2 */
                        secondAmmoCount = ((struct Player *)player)->ammo[1];
                        secondAmmoDrop = 0;
                        if (secondAmmoCount != 0) {
                            secondAmmoRandom = XPlus_NextRandomInteger();
                            secondAmmoQuotient = secondAmmoRandom / secondAmmoCount;
                            if (secondAmmoCount == 0) {

                            }
                            if ((secondAmmoCount == -1) && (secondAmmoQuotient == S32_MIN_BITS)) {

                            }
                            secondAmmoDrop = secondAmmoRandom % secondAmmoCount;
                        }
                        if (secondAmmoDrop != 0) {
                            hasAmmoDrop = 1;
                            secondAmmoDropRecord = &g_pickupAmmoDefinitions[((struct Player *)player)->projectileBase + ((struct Player *)player)->projectileIndex];
                            secondAmmoDropRecord->secondAmmoDrop = (s16) secondAmmoDrop;
                            secondAmmoDropRecord->firstAmmoDrop = 0;
                            secondAmmoDropRecord->thirdAmmoDrop = 0;
                        }
                        break;
                    case 2:                         /* switch 2 */
                        thirdAmmoCount = ((struct Player *)player)->ammo[2];
                        thirdAmmoDrop = 0;
                        if (thirdAmmoCount != 0) {
                            thirdAmmoRandom = XPlus_NextRandomInteger();
                            thirdAmmoQuotient = thirdAmmoRandom / thirdAmmoCount;
                            if (thirdAmmoCount == 0) {

                            }
                            if ((thirdAmmoCount == -1) && (thirdAmmoQuotient == S32_MIN_BITS)) {

                            }
                            thirdAmmoDrop = thirdAmmoRandom % thirdAmmoCount;
                        }
                        if (thirdAmmoDrop != 0) {
                            hasAmmoDrop = 1;
                            thirdAmmoDropRecord = &g_pickupAmmoDefinitions[((struct Player *)player)->projectileBase + ((struct Player *)player)->projectileIndex];
                            thirdAmmoDropRecord->thirdAmmoDrop = (s16) thirdAmmoDrop;
                            thirdAmmoDropRecord->firstAmmoDrop = 0;
                            thirdAmmoDropRecord->secondAmmoDrop = 0;
                        }
                        break;
                    }
                }
                if (hasAmmoDrop != 0) {
                    nearestSpawnPoint = Portal_GetGraphPoint(&g_navigationGraph, Portal_FindNearestPointIndex(&g_navigationGraph, &player->pos));
                    InstHdr_CopyActorPositionAndModel(player, player->pos, &spawnPosition, &spawnProbeResult, 0, 0);
                    if (nearestSpawnPoint != 0) {
                        spawnPosition = *(CVector3 *)nearestSpawnPoint;
                    }
                    spawnVector.x = 0;
                    spawnVector.y = 0.0f;
                    spawnVector.z = 0;
                    spawnedAmmoPickup = SetN64_SpawnModelEffect(&g_modelEffectPool, 0, ammoPickupType, spawnVector, spawnPosition, 0, 0);
                    if (spawnedAmmoPickup != 0) {
                        spawnPosition.y += g_playerDeathHeightOffsets.spawn;
                        ((struct Player *)player)->projectiles[((struct Player *)player)->projectileIndex] = (void *)spawnedAmmoPickup;
                    }
                } else {
                    ((struct Player *)player)->projectiles[((struct Player *)player)->projectileIndex] = 0;
                }
                ((struct Player *)player)->projectileIndex = (s32) (((struct Player *)player)->projectileIndex == 0);
            }
            if ((((struct Player *)player)->profile->bonus != 0) && (laterFlow = &g_transientPlayerList.flow, laterFlow->transition != 0)) {
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
                            resetMessageTarget = ((struct Player *)resetMessageActor)->camera;
                            if (resetMessageTarget != 0) {
                                Camera_PostScreenMessage(gameplayMessageContext(messageContext), resetMessageTarget,
                                    gameplayResetMessage(localization->language));
                            }
                            resetMessageActor = ((struct Player *)resetMessageActor)->next;
                        } while (resetMessageActor != 0);
                    }
                }
                ((struct Player *)player)->profile->bonus = 0U;
                ((struct Player *)player)->profile->state90 = 0;
            }
            childActor = g_transientPlayerList.actorList;
            if (childActor != 0) {
                messageContext = &g_transientPlayerList.messageContext;
                localization = &g_transientPlayerList.localization;
                do {
                    if ((childActor != player) && (((struct Player *)childActor)->effectSource == player)) {
                        releaseMessageTarget = ((struct Player *)childActor)->camera;
                        ((struct Player *)childActor)->pending = 0;
                        ((struct Player *)childActor)->effectSource = 0;
                        if (releaseMessageTarget != 0) {
                            Gsky_PostScaledScreenMessage(gameplayMessageContext(messageContext), releaseMessageTarget,
                                gameplayReleaseMessage(localization->language), 1.0f);
                        }
                    }
                    childActor = ((struct Player *)childActor)->next;
                } while (childActor != 0);
            }
        }
        ((struct Player *)player)->reservedWord1238 = -1;
        ((struct Player *)player)->reservedWord1230 = 0;
        ((struct Player *)player)->reservedWord1234 = 0;
        ((struct Player *)player)->opacity = 0;
        ((struct Player *)player)->reactionFlags = (s32) (((struct Player *)player)->reactionFlags & 0xFFFF0000);
        if (damageFlags & 0x4000) {
            if ((u32) (((struct Player *)player)->state - 17) < 2U) {
                ((struct Player *)player)->overkill = 1;
            }
        }
        if (((struct Player *)player)->overkill == 0) {
            deathSound = 700;
            if (state != 31) {
                deathSound = Playerai_SelectCharacterSound(player, 5015);
            }
            SoundElement_PlaySoundAtPosition(deathSound, player->pos, (intptr_t)&player->pos, -1);
        } else {
            SoundElement_PlaySoundAtPosition(2555, player->pos, (intptr_t)&player->pos, -1);
        }
        SoundElement_PlayFlatSound(530);
        if ((((struct Player *)player)->overkill != 0) || (deathEffectActorKind = ((struct Player *)player)->objectId, (deathEffectActorKind == g_playerDeathEffectModelIds)) || (deathEffectActorKind == (&g_playerDeathEffectModelIds)[1])) {
            spawnVector.x = player->pos.x;
            spawnVector.y = player->pos.y + g_playerDeathHeightOffsets.projectile;
            deathEffectFlags = 1;
            spawnVector.z = player->pos.z;
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
            deathEffectFrame = ((struct Player *)player)->actorParts[0].lockOn;
            if (Gobjinst_GetModelRenderMode(player) == 5) {
                deathEffectFlags = 3;
            }
            Particle_SpawnEffectGroup(&g_actorParticleEffectSystem, player, player, 0, deathEffectFrame, 100, motionVector,
                motionOutput, spawnVector, 0, -1, deathEffectFlags);
        }
        if (state != -1) {
            Player_SetPlayerState(player, attacker, state);
            return;
        }
        if (((struct Player *)player)->state != 17) {
            if (((struct Player *)player)->pose == 10 && (damageFlags & 0x4000)) {
                Player_SetPlayerState(player, attacker, 42);
                return;
            }
            if (damageFlags & 0x4000) {
                Player_SetPlayerState(player, attacker, 41);
                return;
            }
        }
        movingAtDeath = 1;
        if (!(((struct Player *)player)->crouchDepth > g_playerDeathMovingSpeed)) {
            movingAtDeath = 0;
        }
        if (movingAtDeath != 0) {
            Player_SetPlayerState(player, attacker, 28);
            return;
        }
        previousAction = ((struct Player *)player)->pose;
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
        if ((((struct Player *)player)->state != 17) && (((struct Player *)player)->specialState == 1)) {
            Player_SetPlayerState(player, attacker, 30);
            return;
        }
        if (((struct Player *)player)->specialState == 2) {
            Player_SetPlayerState(player, attacker, 29);
            return;
        }
        Player_SetPlayerState(player, attacker, 22);
        return;
    }
}


/* Applies damage to a player: ignored while the game is paused, the player is protected or the damage
 * source is not allowed; scales the amount by one fifth with armour; when the health stays above
 * zero and drops through half of the maximum it respawns the weapon (Player_PlacePlayerAtSpawnPoint); lowers the health
 * (with a flash sound at random), starts the knock-back and the hit effect scaled by the damage, and on death
 * reports the kill through Playerai_HandlePlayerDeath. */
/* de, eu and eu-x add the round-state gate and a further check, kept in their assembly. */
void Player_ApplyPlayerDamage(void *player, void *attacker, s32 amount, s32 damageFlags, s32 kind) {
    s32 oldHealth = ((struct Player *)player)->health;
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
    CGameStatus *state;
    s32 remaining;
    if (Cinema_IsSequenceActive() != 0 || Playerai_IsRoundEndState(player) != 0 || g_world.frozen != 0) {
        return;
    }
    if ((g_gameSettings.flags & 1) && kind != 32) {
        return;
    }
    if ((u16)((struct Player *)player)->pose < 2) {
        return;
    }
    if (((SharedPlayer *)player)->views5E8.view80C_107.mount != 0) {
        amount = amount / 5;
    }
    if (0.0f < ((SharedPlayer *)player)->views5E8.view670_30.shield && kind != 32) {
        return;
    }
    wasDead = ((struct Player *)player)->health == 0;
    if (((SharedPlayer *)player)->views122C.view122C_0.flags & 0x100) {
        health = ((struct Player *)player)->health - amount;
        if (health < 0) {
            health = 0;
        }
        step = Player_GetMaxHealth(player);
        found = 0;
        for (threshold = 2; threshold < 5; threshold++) {
            step = step - step / 2;
            if (step < ((struct Player *)player)->health && health < step && health > 0) {
                found = 1;
                break;
            }
        }
        if (found != 0) {
            Player_PlacePlayerAtSpawnPoint(player, ((struct Player *)player)->model, 0, 1);
        }
    }
#if defined(VERSION_DE) || defined(VERSION_EU_X)
    if (((SharedPlayer *)player)->views1450.view1450_5.f1450 != 0 && (state = (CGameStatus *)&g_matchRoundCounters)->enabled != 0 &&
#else
    state = &g_matchRoundCounters;
    if (state->enabled != 0 &&
#endif
#if defined(VERSION_DE) || defined(VERSION_EU_X)
        ((struct Player *)player)->profile->enabled != 0 &&
#endif
        ((struct Player *)player)->profile->character == 11 && state->m_nBastilleShield > 0) {
        state->m_nBastilleShield -= amount >> 8;
        if (state->m_nBastilleShield <= 0) {
            state->m_nBastilleShield = 0;
            switch (((struct Player *)player)->profile->difficulty) {
            case 0:
                state->m_nBastilleTimer = 75;
                break;
            case 1:
                state->m_nBastilleTimer = 60;
                break;
            case 2:
                state->m_nBastilleTimer = 60;
                break;
            }
            Player_SetPlayerState(player, player, 45);
        }
        amount = 0;
    }
    if (((struct Player *)player)->health != 0) {
        ((SharedPlayer *)player)->views13C8.view13C8_2.f13C8 = ((struct Player *)player)->health - amount < -7679;
    }
    remaining = ((struct Player *)player)->health - amount;
    if (remaining < 0) {
        remaining = 0;
    }
    ((struct Player *)player)->health = remaining;
    roll = Graphu64_NextRandom();
    if ((roll % 2) == 1) {
        if (((Player *)player)->health > 0) {
            s32 id = Playerai_SelectCharacterSound((struct Player *)player, 5005);
            if (SoundElement_HasActiveOrPendingSound(id) == 0) {
                SoundElement_PlaySoundAtPosition((s16)id, ((struct Player *)player)->pos,
                    (s32)&((struct Player *)player)->pos, -1);
            }
        }
    }
    ((SharedPlayer *)player)->views1C.view174_17.bodyHealth = ((struct Player *)player)->health;
    ((SharedPlayer *)player)->views1C.view45C_31.mirroredHealth = ((struct Player *)player)->health;
    dead = ((struct Player *)player)->health == 0;
    if (dead != 0) {
        if (wasDead == 0) {
            Playerai_HandlePlayerDeath((struct Player *)player, attacker, damageFlags, kind);
        }
        intensity = 0xFF;
        delay = 12;
    } else {
        shifted = amount >> 8;
        intensity = shifted * 255 / 20;
        intensity = ((intensity > 0xFF ? 0xFF : intensity) < 128) ? 128 : (intensity > 0xFF ? 0xFF : intensity);
        delay = 30;
        if (((struct Player *)player)->camera != 0) {
            if (oldHealth > 3840 && ((struct Player *)player)->health <= 3840 && g_frontendScreenStatus.settings.local == 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                Camera_PostScreenMessage(&g_frontendScreenStatus, ((struct Player *)player)->camera,
                    ((u8 **)&g_playerHealthDropMessage)[g_frontendScreenStatus.settings.language]);
#else
                Camera_PostScreenMessage(&g_frontendScreenStatus, ((struct Player *)player)->camera, (u8 *)g_playerHealthDropMessage);
#endif
            }
        }
        if ((amount >> 8) != 0) {
            f32 strength;
            strength = ((f32)(amount >> 8) * g_playerDamageRumbleScale > g_playerDamageRumbleMaximum) ? g_playerDamageRumbleMaximum : (f32)(amount >> 8)
                * g_playerDamageRumbleScale;
            {
                Triple position;
                position.x = 0;
                position.y = 0;
                position.z = 0;
                CScene_StartEventClips(&g_world,
                    (s32)&((ControllerProfile *)((Player *)player)->weaponAnimation)->effectPool,
                    17, position, g_playerHeightScalePair_us, strength);
            }
        }
    }
    if (dead == 0 && ((struct Player *)player)->pose != 18 && ((struct Player *)player)->camera != 0) {
        s32 hit;
        if (((SharedPlayer *)player)->views16D4.view16D4_1.f16D4 == 0) {
            Gsky_SetDamageEffect(((struct Player *)player)->camera, intensity & 0xFF, delay);
        }
        hit = amount * 15;
        if (hit > 100) {
            hit = 100;
        }
        Playerai_AddCappedEventCounter(player, (u16)hit);
    }
    return;
}



void Playerai_ApplyProjectileStatus(void *playerObject, void *linkedActor, s32 statusArg, void *projectileEvent) {
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

/* Draws a player's marker when it is enabled: loads the player's matrix for the current view
   g_lightingBufferIndex from its table, sets the render and geometry modes, fills the eight vertices of
   a red prism in g_playerDeathEffectVertices (alpha 150 on the upper and 100 on the lower corners), emits them with the
   eight triangles joining them, and passes the same colour and alphas to Fx_DrawRedParticleQuad with the
   matrix from the table when 0x147C is set. */




void Player_DrawRedMarkerPrism(PlayerMarkerPrismView *player) {
    s32 red;
    s32 low;
    s32 high;

    if (player->marker != 0) {
        gSPMatrix(g_displayListCursor++, &player->views[g_lightingBufferIndex], G_MTX_LOAD);
        gDPPipeSync(g_displayListCursor++);
        Geometry_InvalidateMaterialKeys();
        Geometry_SetModePreset(14);
        Geometry_SetCombineMode(28);
        red = 200;
        low = 100;
        high = 150;
        gSPGeometryMode(g_displayListCursor++, G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | 0x80, 0);
        gSPGeometryMode(g_displayListCursor++, 0, G_SHADE | G_SHADING_SMOOTH);
        g_playerDeathEffectVertices[0].x = 0;
        g_playerDeathEffectVertices[0].y = 1;
        g_playerDeathEffectVertices[0].z = 0;
        g_playerDeathEffectVertices[0].flag = 0;
        g_playerDeathEffectVertices[0].s = 0;
        g_playerDeathEffectVertices[0].t = 0;
        g_playerDeathEffectVertices[0].r = red;
        g_playerDeathEffectVertices[0].g = 0;
        g_playerDeathEffectVertices[0].b = 0;
        g_playerDeathEffectVertices[0].a = high;
        g_playerDeathEffectVertices[1].x = 1;
        g_playerDeathEffectVertices[1].y = 0;
        g_playerDeathEffectVertices[1].z = 0;
        g_playerDeathEffectVertices[1].flag = 0;
        g_playerDeathEffectVertices[1].s = 0;
        g_playerDeathEffectVertices[1].t = 0;
        g_playerDeathEffectVertices[1].r = red;
        g_playerDeathEffectVertices[1].g = 0;
        g_playerDeathEffectVertices[1].b = 0;
        g_playerDeathEffectVertices[1].a = high;
        g_playerDeathEffectVertices[2].x = 0;
        g_playerDeathEffectVertices[2].y = -1;
        g_playerDeathEffectVertices[2].z = 0;
        g_playerDeathEffectVertices[2].flag = 0;
        g_playerDeathEffectVertices[2].s = 0;
        g_playerDeathEffectVertices[2].t = 0;
        g_playerDeathEffectVertices[2].r = red;
        g_playerDeathEffectVertices[2].g = 0;
        g_playerDeathEffectVertices[2].b = 0;
        g_playerDeathEffectVertices[2].a = low;
        g_playerDeathEffectVertices[3].x = -1;
        g_playerDeathEffectVertices[3].y = -1;
        g_playerDeathEffectVertices[3].z = 0;
        g_playerDeathEffectVertices[3].flag = 0;
        g_playerDeathEffectVertices[3].s = 0;
        g_playerDeathEffectVertices[3].t = 0;
        g_playerDeathEffectVertices[3].r = red;
        g_playerDeathEffectVertices[3].g = 0;
        g_playerDeathEffectVertices[3].b = 0;
        g_playerDeathEffectVertices[3].a = low;
        g_playerDeathEffectVertices[4].x = 0;
        g_playerDeathEffectVertices[4].y = 1;
        g_playerDeathEffectVertices[4].z = -1;
        g_playerDeathEffectVertices[4].flag = 0;
        g_playerDeathEffectVertices[4].s = 0;
        g_playerDeathEffectVertices[4].t = 0;
        g_playerDeathEffectVertices[4].r = red;
        g_playerDeathEffectVertices[4].g = 0;
        g_playerDeathEffectVertices[4].b = 0;
        g_playerDeathEffectVertices[4].a = high;
        g_playerDeathEffectVertices[5].x = 1;
        g_playerDeathEffectVertices[5].y = 0;
        g_playerDeathEffectVertices[5].z = -1;
        g_playerDeathEffectVertices[5].flag = 0;
        g_playerDeathEffectVertices[5].s = 0;
        g_playerDeathEffectVertices[5].t = 0;
        g_playerDeathEffectVertices[5].r = red;
        g_playerDeathEffectVertices[5].g = 0;
        g_playerDeathEffectVertices[5].b = 0;
        g_playerDeathEffectVertices[5].a = high;
        g_playerDeathEffectVertices[6].x = 0;
        g_playerDeathEffectVertices[6].y = -1;
        g_playerDeathEffectVertices[6].z = -1;
        g_playerDeathEffectVertices[6].flag = 0;
        g_playerDeathEffectVertices[6].s = 0;
        g_playerDeathEffectVertices[6].t = 0;
        g_playerDeathEffectVertices[6].r = red;
        g_playerDeathEffectVertices[6].g = 0;
        g_playerDeathEffectVertices[6].b = 0;
        g_playerDeathEffectVertices[6].a = low;
        g_playerDeathEffectVertices[7].x = -1;
        g_playerDeathEffectVertices[7].y = -1;
        g_playerDeathEffectVertices[7].z = -1;
        g_playerDeathEffectVertices[7].flag = 0;
        g_playerDeathEffectVertices[7].s = 0;
        g_playerDeathEffectVertices[7].t = 0;
        g_playerDeathEffectVertices[7].r = red;
        g_playerDeathEffectVertices[7].g = 0;
        g_playerDeathEffectVertices[7].b = 0;
        g_playerDeathEffectVertices[7].a = low;
        gSPVertex(g_displayListCursor++, (u32) g_playerDeathEffectVertices, 8, 0);
        gSP1Triangle(g_displayListCursor++, 0, 1, 4, 0);
        gSP1Triangle(g_displayListCursor++, 1, 4, 5, 0);
        gSP1Triangle(g_displayListCursor++, 1, 2, 5, 0);
        gSP1Triangle(g_displayListCursor++, 2, 5, 6, 0);
        gSP1Triangle(g_displayListCursor++, 2, 3, 6, 0);
        gSP1Triangle(g_displayListCursor++, 3, 6, 7, 0);
        gSP1Triangle(g_displayListCursor++, 3, 0, 7, 0);
        gSP1Triangle(g_displayListCursor++, 0, 7, 4, 0);
        if (player->second != 0) {
            Fx_DrawRedParticleQuad((u32)&player->markers[g_lightingBufferIndex]);
        }
    }
}

void Player_DrawPlayerModel(void *player, void *camera) {
    CVector3 pos;
    s32 value;
    Gfx *cmd;

    pos = ((LevelActor *)player)->position0;
    pos.y += ((LevelActor *)player)->eyeHeight;
    pos.y += Gobjinst_GetActorHeight(player) * ((ScalarPair *)&g_playerHeightScalePair_us)->second;
    Scene_SampleWorldLighting(&g_world, &pos,
                  &((LevelActor *)player)->lighting[g_lightingBufferIndex]);

    value = 102;
    if (g_gameSettings.local != 0) {
        if ((g_resultExitPending != 0) &&
            (((Player *)player)->profile->bonus != 0)) {
            value = g_fragTagModelId;
        } else {
            value = g_characterModelIds[((MovementDescriptor *)((LevelActor *)player)->definition)->body.header.character];
            ((LevelActor *)player)->renderPass =
                ((Player *)player)->profile->variant;
        }
    }
    ((void (*)(void *, void *, s32, s32))Scene_ChangeInstanceModel)(&g_world, player, value,
                  ((Player *)player)->animation);

    cmd = g_displayListCursor++;
    gDPPipeSync(cmd);
    cmd = g_displayListCursor++;
    gDPSetCycleType(cmd, G_CYC_2CYCLE);
    cmd = g_displayListCursor++;
    gSPGeometryMode(cmd, 0, G_FOG);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 4, 2);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 12, 2);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 20, 0xFFFE);
    cmd = g_displayListCursor++;
    gMoveWd(cmd, G_MW_CLIP, 28, 0xFFFE);

    Gobjinst_DrawVisibleCachedActor(player, camera);
    if (((Player *)player)->overlay != 0) {
        Player_DrawRedMarkerPrism(player);
    }
}

void Player_DrawHeldWeapon(void *player, GameplayCamera *camera) {
    WeaponInfo *entry;
    f32 *rect;
    f32 x;
    f32 y;
    f32 left;
    f32 right;
    f32 top;
    f32 bottom;

    if ((((Player *)player)->selectedAction != -1) &&
        (((Player *)player)->respawnHealth != 0)) {
        gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
        gDPSetTexturePersp(g_displayListCursor++, G_TP_PERSP);
        Geometry_InvalidateMaterialKeys();

        entry = g_weaponInfoByType[((Player *)player)->selectedAction];
        rect = &camera->viewWidth;
        x = rect[0];
        y = rect[1];
        left = entry->scopeBounds[0] * x + rect[2];
        right = entry->scopeBounds[2] * x + rect[2];
        top = entry->scopeBounds[1] * y + rect[3];
        bottom = entry->scopeBounds[3] * y + rect[3];
        SetN64_ClearDepthRect(&g_gameSession, (s32)left, (s32)right, (s32)top,
                      (s32)bottom, camera->monochrome);

        gSPGeometryMode(g_displayListCursor++, 0, G_FOG);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, 4, 1);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, 12, 1);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, 20, 0xFFFF);
        gMoveWd(g_displayListCursor++, G_MW_CLIP, 28, 0xFFFF);
        Geometry_BeginModelBatch();
        Gobjinst_DrawVisibleCachedActor(&((Player *)player)->actorParts[1], camera);
        Geometry_FlushModelBatch();
    }
}

/* Whether the target's view reports an active shield. */
static inline s32 Weapons_TargetShielded(TargetLockTargetView *target) {
    View *view = target->view;
    if (view == NULL) {
        return 0;
    }
    return view->shieldActive != 0;
}
/* Checks whether the player's current weapon can lock onto the target. Kind 0 and 7 targets never lock. */
s32 Playerai_CanLockTarget(TargetLockAttackerView *attacker, TargetLockTargetView *target) {
    s16 weapon;
    s8 mode;
    s32 canLock;

    weapon = attacker->weaponId;
    if (weapon == 18) {
        if (target->renderFlags & 0x300000) {
            if (!(target->definition->flags & 0x20)) {
                return 0;
            }
            mode = target->targetLockState;
            if (mode == 38 || mode == weapon || target->health == 0) {
                return 0;
            }
            if (!Weapons_TargetShielded(target)) {
                return Cbarrel_TestTargetEyeObstruction(attacker, &attacker->targetProbeState, target) == 0;
            }
            return 0;
        }
        if (target->definition->kind == 1) {
            if (!(target->definition->flags & 0x2400)) {
                return 0;
            }
            mode = target->targetLockState;
            if (mode == 33 || mode == 52 || mode == 60 || mode == 61) {
                return 0;
            }
            if (target->health != 0) {
                return Cbarrel_TestTargetEyeObstruction(attacker, &attacker->targetProbeState, target) == 0;
            }
            return 0;
        }
    }
    switch (target->definition->kind) {
    case 4:
        if (target->health != 0) {
            return Cbarrel_TestTargetEyeObstruction(attacker, &attacker->targetProbeState, target) == 0;
        }
        return 0;
    case 0:
    case 7:
        return 0;
    case 11:
        canLock = 0;
        mode = target->targetLockState;
        if (mode != 38 && mode != 18 && target->health != 0 && !Weapons_TargetShielded(target)) {
            canLock = 1;
        }
        return canLock;
    }
    return 0;
}

struct TargetLockAttackerView;
struct TargetLockTargetView;


CQuatern Playerai_ComputeAimRotation(DraftAimPlayer *player, DraftAimPlayer **target,
                            CVector3 *targetPosition)
{
    CVector3 candidate, direction, origin;
    CVector3 bestPosition;
    CVector3 forward, unit;
    CVector3 bestDirection;
    CVector3 axis;
    CQuatern correction, facing, result;
    DraftAimPlayer *other, *best;
    u8 *enable;
    f32 angle, dot, threshold, half, amount, scale;
    s32 count, i, firstSpecial, secondSpecial;

    bestPosition.x = 0.0f;
    bestPosition.y = 0.0f;
    bestPosition.z = 0.0f;
    bestDirection.x = 0.0f;
    bestDirection.y = 0.0f;
    bestDirection.z = 0.0f;
    result.x = result.y = result.z = bestPosition.x;
    result.w = g_playerAimDefaultRotationW;
    best = 0;
    if (player->weapon != -1) angle = ((DraftAimWeapon *)g_weaponInfoByType[player->weapon])->angle;
    else angle = bestPosition.x;
    threshold = Math_Cosf(angle * g_playerAimConeAngleScale);
    if (angle != 0.0f) {
        unit.x = 0.0f;
        unit.y = 0.0f;
        unit.z = g_playerAimForwardDistance;
        Gobjinst_TransformVectorByActorAim(&forward, player, unit);
        origin = player->position;
        origin.y += Playerai_GetObjectOwnerHeight(player);
        enable = &g_frontendScreenStatus.settings.local;
        if (*enable) {
            other = g_transientPlayerList.actorList;
            if (other) {
                firstSpecial = 18;
                scale = g_playerAimPrimaryTurnScale;
                do {
                if (Playerai_CanLockTarget((void *)player, (void *)other) && other != player) {
                    if (player->weapon == firstSpecial) candidate = other->specialAim;
                    else {
                        candidate = other->position;
                        candidate.y += other->height;
                        candidate.y += Gobjinst_GetActorHeight(other) * scale;
                    }
                    Graphu64_SubtractVectors(&direction, &candidate, &origin);
                    Graphu64_NormalizeVec3(&direction.x);
                    dot = forward.x * direction.x + forward.y * direction.y +
                          forward.z * direction.z;
                    if (threshold < dot) {
                        threshold = dot;
                        bestPosition = candidate;
                        best = other;
                    }
                }
                            } while ((other = other->next) != 0);
            }
        }
        count = g_world.registeredCount;
        i = 0;
        if (i < count) {
            secondSpecial = 18;
            scale = g_playerAimSecondaryTurnScale;
            do {
            other = (void *)g_playerAimCandidateActors[i];
            if (Playerai_CanLockTarget((void *)player, (void *)other)) {
                if (player->weapon == secondSpecial) candidate = other->specialAim;
                else {
                    candidate = other->position;
                    candidate.y += other->height;
                    candidate.y += Gobjinst_GetActorHeight(other) * scale;
                }
                Graphu64_SubtractVectors(&direction, &candidate, &origin);
                Graphu64_NormalizeVec3(&direction.x);
                dot = forward.x * direction.x + forward.y * direction.y +
                      forward.z * direction.z;
                if (threshold < dot) {
                    threshold = dot;
                    best = other;
                    bestPosition = candidate;
                    bestDirection = direction;
                }
            }
                        i++;
            } while (i < count);
        }
    }
    *target = best;
    *targetPosition = bestPosition;
    if (best) {
        Graphu64_CrossVectors(&axis, &forward, &bestDirection);
        Graphu64_NormalizeVec3(&axis.x);
        scale = g_playerAimFallbackTurnScale;
        threshold = Graphu64_ArcCos(threshold);
        amount = Gu_Sqrtf(g_playerAimTurnRootBase - threshold / (angle * scale));
        amount = Gu_Sqrtf(amount);
        threshold *= amount;
        threshold *= scale;
        amount = Gu_Sinf(threshold);
        correction.x = axis.x * amount;
        correction.y = axis.y * amount;
        correction.z = axis.z * amount;
        g_turretAimSine = amount;
        correction.w = Math_Cosf(threshold);
        facing = Gobjinst_BuildActorAimQuaternion((char *)player);
        MultiplyQuaternions(&result, &facing, &correction);
    }
    return result;
}

/* Builds a player's aiming marker matrices for the current view g_lightingBufferIndex and turns the marker on at
   0x1214: a beam from the eye (the view position, or Player_GetPlayerViewTranslation without a view) toward the
   target point, pitched straight up or down when nearly vertical, is stored in the table; the
   laser from the weapon muzzle to the aim point (lowered by the view's height above
   the muzzle) in the table; and with a surface normal given, a dot flattened against the
   surface and lifted along the normal is stored in the table. */
static inline f32 aimAbs(f32 value) { return value < 0.0f ? -value : value; }





void Player_BuildAimMarkerMatrices(SharedPlayer *player, CVector3 *target, CVector3 *normal) {
    CVector3 to;
    CVector3 eye;
    CVector3 lift;
    CVector3 direction;
    CVector3 aim;
    CVector3 origin;
    Matrix matrix;
    CQuatern turn;
    f32 scale;
    f32 height;
    f32 aimHeight;

    if (player->views5DC.view5DC_2.view != 0) {
        origin = player->views5DC.view5DC_2.view->position;
    } else {
        Player_GetPlayerViewTranslation(player, &origin);
    }
    eye = origin;
    to = *target;
    Graphu64_SubtractVectors(&direction, &to, &eye);
    Graphu64_NormalizeVec3(&direction);
    Graphu64_IdentityMatrix(&matrix);
    if (0.99999899f <= direction.y) {
        Graphu64_MatrixFromEulerXYZ(&matrix, -1.57079649f, player->views1C.view6C_5.heading, 0.0f);
    } else if (direction.y <= -0.99999899f) {
        Graphu64_MatrixFromEulerXYZ(&matrix, 1.57079649f, player->views1C.view6C_5.heading, 0.0f);
    } else {
        BuildDirectionMatrix(&matrix, &direction);
    }
    TranslateMatrix(&matrix, eye.x, eye.y, eye.z);
    TranslateMatrixLocal(&matrix, 0.0f, 0.0f, g_playerAimMarkerDepth);
    ScaleMatrixLocal(&matrix, 0.05f, 1.0f, g_playerAimMarkerDepth - Graphu64_GetPointDistance(&eye, &to));
    Graphu64_ConvertMatrixToFixed(&matrix, &player->views1480.view1480_1.beams[g_lightingBufferIndex]);

    aim = player->views1464.view1464_1.aim;
    if (player->views5DC.view5DC_2.view != 0) {
        height = player->views5DC.view5DC_2.view->position.y - player->views1C.view260_26.muzzle.y;
        aimHeight = aim.y;
        height = height < 0.0f ? aimHeight + height : aimHeight - height;
        aim.y = height;
    }
    Graphu64_SubtractVectors(&direction, &aim, &player->views1C.view260_26.muzzle);
    Graphu64_NormalizeVec3(&direction);
    Graphu64_IdentityMatrix(&matrix);
    BuildDirectionMatrix(&matrix, &direction);
    TranslateMatrix(&matrix, player->views1C.view260_26.muzzle.x, player->views1C.view260_26.muzzle.y, player->views1C.view260_26.muzzle.z);
    scale = 1.0f;
    ScaleMatrixLocal(&matrix, scale, scale, -Graphu64_GetPointDistance(&origin, &player->views1464.view1464_1.aim));
    Graphu64_ConvertMatrixToFixed(&matrix, &player->views1500.view1500_1.lasers[g_lightingBufferIndex]);

    if (normal != 0) {
        lift = *normal;
        turn = Graphu64_BuildDirectionQuaternion(&lift);
        MatrixFromQuaternion(&turn, &matrix);
        PitchMatrixLocal(&matrix, 1.57079649f);
        Graphu64_NormalizeVec3(&lift);
        Graphu64_ScaleVector(&lift, &lift, 2.048f);
        Graphu64_AddVec3(&eye, &eye, &lift);
        TranslateMatrix(&matrix, to.x, to.y, to.z);
        ScaleMatrixLocal(&matrix, 1.536f, scale, 1.536f);
        Graphu64_ConvertMatrixToFixed(&matrix, &player->views1580.view1580_1.dots[g_lightingBufferIndex]);
    }
    player->views5E8.view1214_155.marker = 1;
}

s32 CCollision_SweepPoint(char *, CVector3, CVector3, s32);


void Playerai_UpdateAimAndLockMarker(AimPlayer *player) {
    AimOutput aimResult;
    CVector3 localForward;
    CVector3 smoothOffset;
    CVector3 desired;
    f32 matrix[16];
    CVector3 current;
    CQuatern aimRotation;
    AimWeapon *weapon;
    AimOutput probeLow;
    CQuatern probeHigh;
    CVector3 direction;
    AimActor *lockedTarget, *probeTarget;
    CVector3 *aimOffsetOutput, *smoothPosition, *outputPosition, *unusedAimOffset, *smoothVelocity, *outputVelocity;
    f32 smoothingFactor, springAcceleration, springDamping, hitDistance, lockElapsed, targetSwitchDelay, initialLockDelay;
    s16 selectedWeapon, unusedWeaponVariant;
    s32 aimIcon;
    s32 unusedWeaponFlags, allowFallbackLock, lockedIcon;
    AimActor *rayHitActor, *target;
    AimView *view;
    lockedTarget = NULL;
    view = player->view;
    springAcceleration = g_playerAimSpringAcceleration;
    springDamping = g_playerAimSpringDamping;
    if (view) { switch (view->mode) { case 1: Player_BuildPlayerViewTransform(player, matrix); Player_GetPlayerViewTranslation(player, &current.x); break;
        default: CopyMatrix(matrix,
        view->matrix); current =
            view->origin; break; } } else { Player_BuildPlayerViewTransform(player, matrix); Player_GetPlayerViewTranslation(player, &current.x); }
    localForward.x = 0.0f;
    localForward.y = 0;
    localForward.z = g_playerAimProbeDistance;
    Graphu64_TransformPoint(matrix, &localForward, &desired);
    if (CCollision_SweepPoint((char *)player, current, desired, (intptr_t) &g_particleCollisionProbeResult) != 0) {
        player->aim = (*(CVector3 *)&g_collisionCurrentActor->vecE4);
        player->normal = (*(CVector3 *)&g_collisionCurrentActor->vecF0);
        player->target = g_collisionCurrentActor->instance0;
    } else {
        player->aim = desired;
        player->target = NULL;
    }
    localForward.x = 0.0f;
    localForward.y = 0;
    localForward.z = g_playerAimLockProbeDistance;
    Graphu64_TransformPoint(matrix, &localForward, &desired);
    if (player->enabled != 0) {
        if ((CCollision_SweepPoint((char *)player, current, desired, (intptr_t) &g_playerCollisionProbe) != 0)
                && (rayHitActor = g_collisionCurrentActor->instance0, (rayHitActor != NULL))) {
            if (rayHitActor->kind == 1) {
                if (rayHitActor->flags & 0x300000) {
                    Graphu64_SubtractVectors((CVector3 *)&aimRotation, &rayHitActor->pos, &player->worldPosition);
                    hitDistance = Gu_Sqrtf((aimRotation.x * aimRotation.x) + (aimRotation.y * aimRotation.y) + (aimRotation.z * aimRotation.z));
                    direction = localForward;
                    Graphu64_NormalizeVec3(&direction);
                    Graphu64_ScaleVector(&probeLow.xyz, &direction, hitDistance);
                    Graphu64_TransformPoint(matrix, &probeLow.xyz, (CVector3 *)&probeHigh);
                    player->aim2 = (*(CVector3 *)&probeHigh);
                    Player_BuildAimMarkerMatrices((void *)player, (CVector3 *)&probeHigh, &(*(CVector3 *)&g_collisionCurrentActor->vecF0));
                } else {
                    goto block_14;
                }
            } else {
                goto block_15;
            }
        } else {
block_14:
block_15:
            player->aim2 = player->aim;
            Player_BuildAimMarkerMatrices((void *)player, &player->aim, &(*(CVector3 *)&g_collisionCurrentActor->vecF0));
        }
    } else {
        player->aim2 = desired;
    }
    if (player->selectedWeapon == 1 && player->weaponActionMode == 2) {
        aimIcon = 710;
    } else {
        weapon = g_weaponInfoByType[player->selectedWeapon]; aimIcon = weapon->idle;
    }
    selectedWeapon = player->selectedWeapon;
    lockedIcon = aimIcon + 100;
    allowFallbackLock = 1;
    if ((selectedWeapon == 1) || (selectedWeapon == 18)) {
        targetSwitchDelay = g_playerAimLockDelay;
        initialLockDelay = targetSwitchDelay;
    } else {
        targetSwitchDelay = 0.0f;
        initialLockDelay = 0.0f;
    }
    switch (player->selectedWeapon) {
    case 7:
        if (player->alternateAimMode != 0) {
            aimIcon = 740;
            lockedIcon = -1;
        }
        break;
    case 2:
        if (player->alternateAimMode != 0) {
            aimIcon = 700;
            lockedIcon = -1;
        }
        break;
    case 1:
    case 18:
        aimRotation = Playerai_ComputeAimRotation(player, &lockedTarget, &aimResult.words);
        allowFallbackLock = 0;
        break;
    default:
        lockedIcon = -1;
        break;
    }
    aimRotation = Gobjinst_BuildActorAimQuaternion((char *)player);
    player->rotation = aimRotation;
    probeLow.xyz = player->aim;
    probeLow.xyz.x -= g_playerAimProbeRadius;
    (*(CVector3 *)&probeHigh) = player->aim;
    (*(CVector3 *)&probeHigh).x += g_playerAimProbeRadius;
    probeLow.xyz = player->aim;
    probeLow.xyz.z -= g_playerAimProbeRadius;
    (*(CVector3 *)&probeHigh) = player->aim;
    (*(CVector3 *)&probeHigh).z += g_playerAimProbeRadius;
    probeLow.xyz = player->aim;
    probeLow.xyz.y -= g_playerAimProbeRadius;
    (*(CVector3 *)&probeHigh) = player->aim;
    (*(CVector3 *)&probeHigh).y += g_playerAimProbeRadius;
    if (lockedTarget == NULL) {
        aimResult.xyz = desired;
        if ((player->controller->active != 0) && (allowFallbackLock != 0)) {
            probeHigh = Playerai_ComputeAimRotation(player, &probeTarget, &probeLow.words);
            if (probeTarget != NULL) {
                player->rotation = probeHigh;
            }
        }
        if (lockedTarget == NULL) {
            player->lockedTarget = NULL;
        }
    }
    if (aimIcon == -1) {
        player->lockState = 0;
    } else if (player->lockState == 0) {
        player->lockState = 1;
        player->out = desired;
        player->velocity.x = 0;
        player->velocity.y = 0;
        player->velocity.z = 0;
        player->smooth = desired;
        player->smoothVelocity.x = 0;
        player->smoothVelocity.y = 0;
        player->smoothVelocity.z = 0;
    }
    smoothPosition = &player->smooth;
    smoothingFactor = g_playerAimTargetSpringScale;
    Graphu64_SubtractVectors(&smoothOffset, &aimResult.xyz, smoothPosition);
    Graphu64_ScaleVector(&smoothOffset, &smoothOffset, springAcceleration * smoothingFactor);
    smoothVelocity = &player->smoothVelocity;
    Graphu64_AddVec3(smoothVelocity, smoothVelocity, &smoothOffset);
    Graphu64_AddVec3(smoothPosition, smoothPosition, smoothVelocity);
    Graphu64_ScaleVector(smoothVelocity, smoothVelocity, springDamping * smoothingFactor);
    if (lockedTarget != NULL) {
        weapon = g_weaponInfoByType[player->selectedWeapon]; player->lockedAimModelResource = weapon->locked+100;
    } else {
        player->lockedAimModelResource = lockedIcon;
    }
    switch (player->lockState) {
    case 1:
        if ((lockedTarget == NULL) || (player->lockedTarget != lockedTarget)) {
            player->lockedTarget = lockedTarget;
            player->lockTimer = 0.0f;
        }
        lockElapsed = player->lockTimer + g_frameElapsedTime;
        player->lockTimer = lockElapsed;
        if (initialLockDelay <= lockElapsed) {
            player->lockState = 2;
            player->lockTimer = 0.0f;
        }
        goto reset_position;
    case 2:
            if (player->candidateTarget != lockedTarget) {
                player->candidateTarget = lockedTarget;
                player->lockTimer = 0.0f;
            } else {
                player->lockTimer += g_frameElapsedTime;
            }
            if ((lockedTarget != NULL) && (player->lockedTarget != lockedTarget) && (targetSwitchDelay <= player->lockTimer)) {
                player->lockedTarget = lockedTarget;
                player->lockTimer = 0.0f;
            }
            target = player->lockedTarget;
            lockedTarget = target;
            if (target != NULL) {
                if (Playerai_CanLockTarget((void *)player, (void *)target) == 0) {
                    player->lockState = 1;
                    player->lockTimer = 0.0f;
                }
                if (player->selectedWeapon == 18) {
                    aimResult.xyz = lockedTarget->focus;
                } else {
                    aimResult.xyz = lockedTarget->pos;
                    aimResult.xyz.y = aimResult.xyz.y + lockedTarget->height;
                    aimResult.xyz.y += Gobjinst_GetActorHeight(lockedTarget) * g_playerAimTargetHeightScale;
                }
                if (player->selectedWeapon == 1 && player->weaponActionMode == 2) {
                    aimIcon = 711;
                } else {
                    weapon = g_weaponInfoByType[player->selectedWeapon]; aimIcon = weapon->locked;
                }
            } else {
                goto reset_position;
            }
        break;
    case 0:
reset_position:
        aimResult.xyz = desired;
        break;
    default:
        break;
    }
    aimOffsetOutput = &smoothOffset;
    outputPosition = &player->out;
    Graphu64_SubtractVectors(aimOffsetOutput, &aimResult.xyz, outputPosition);
    Graphu64_ScaleVector(&smoothOffset, &smoothOffset, springAcceleration);
    outputVelocity = &player->velocity;
    Graphu64_AddVec3(outputVelocity, outputVelocity, &smoothOffset);
    Graphu64_AddVec3(outputPosition, outputPosition, outputVelocity);
    Graphu64_ScaleVector(outputVelocity, outputVelocity, springDamping);
    player->aimModelResource = (s32) aimIcon;
}

/* Draws an icon sprite for a view: icons 0x2DA, 0x2E4, 0x2BC and 0x2EF to 0x2F2 sit at the centre of
   the view's viewport, any other icon is placed at a world point projected through Gsky_ProjectToScreen_PlayerUpdateplayereffectlightsData when
   the point lies in front of the view's plane and within 64 pixels of the screen g_hudReferenceViewportWidth, remapped
   into the viewport when g_motionVisibilitySettings is set; the sprite is drawn back by its scaled size less one. */


void Playerai_DrawProjectedAimIcon(View *view, CVector3 *point, s32 icon, f32 frame, f32 scale, f32 size) {
    f32 x;
    f32 y;
    f32 offset;

    if (icon == 730 || icon == 740 || icon == 700 || icon == 751 || icon == 752
        || icon == 753 || icon == 754) {
        x = view->viewport[2] + view->viewport[0] * 0.5f;
        y = view->viewport[3] + view->viewport[1] * 0.5f;
    } else {
        if (!(view->normal.x * point->x + view->normal.y * point->y + view->normal.z * point->z
              <= view->distance)) {
            return;
        }
        Gsky_ProjectToScreen(view, point, &x, &y);
        if (x < -64.0f || (f32) (g_hudReferenceViewportWidth + 64) < x || y < -64.0f
            || (f32) (*(&g_hudReferenceViewportWidth + 1) + 64) < y) {
            return;
        }
        if (g_gameSettings.local != 0) {
            x = view->viewport[2] + x / g_hudReferenceViewportWidth * view->viewport[0];
            y = view->viewport[3] + y / *(&g_hudReferenceViewportWidth + 1) * view->viewport[1];
        }
    }
    offset = scale * size - 1.0f;
    OnScreen_DrawSpriteResource(icon, frame, x - offset, y - offset, size, size, 1);
}

void Playerai_DrawAimHud(SharedPlayer *player, void *view) {
    s32 icon;
    s32 show;
    f32 scale;

    player->views5E8.view7BC_102.timer += g_frameElapsedTime;
    if (player->views5E8.view788_94.icons == 0) {
        return;
    }
    if (player->views5D8.view5D8_9.profile->remote == 1 && g_gameSettings.counters.m_bFragTagOn != 0) {
        return;
    }
    if (player->views5E8.view650_17.action == 39) {
        return;
    }
    if (player->views1C.view594_40.mode == 2 && player->views5E8.view62E_14.weapon == 3) {
        return;
    }
    if (Tsmos_IsFrontendActive() != 0) {
        return;
    }
    if (player->views5E8.view798_96.carried == 730) {
        if (player->views1C.view594_40.mode == 1) {
            if (player->views1C.viewE4_7.kind != g_playerSpecialModelIds[0] && player->views1C.viewE4_7.kind != g_playerSpecialModelIds[1]) {
                player->views5E8.view798_96.carried = 751;
                if ((u8) player->views1C.view48C_35.state - 2U < 2) {
                    player->views5E8.view7BC_102.timer = 0.0f;
                } else if (player->views1C.view523_37.busy != 0) {
                    player->views5E8.view7BC_102.timer = 0.0f;
                } else {
                    player->views5E8.view7BC_102.timer = 1.0f;
                }
            }
        } else if (player->views1C.viewE4_7.kind != g_playerSpecialModelIds[0] && player->views1C.viewE4_7.kind != g_playerSpecialModelIds[1]) {
            player->views5E8.view798_96.carried = 753;
            if (player->views5E8.view62E_14.weapon == 9 && player->views1C.view5A0_42.charge > 0.0f) {
                player->views5E8.view7BC_102.timer = 1.0f;
            } else if (player->views1C.view48C_35.state == 11 || player->views1C.view48C_35.state == 3 || player->views1C.view48C_35.state == 2) {
                player->views5E8.view7BC_102.timer = 0.0f;
            } else if (player->views1C.view523_37.busy != 0) {
                player->views5E8.view7BC_102.timer = 0.0f;
            } else {
                player->views5E8.view7BC_102.timer = 1.0f;
            }
        } else {
            player->views5E8.view798_96.carried = 770;
            player->views5E8.view7BC_102.timer = 0.0f;
        }
    }
    Onscrn_SetupSpriteMode(0xFF);

    icon = player->views5E8.view7B8_100.target;
    show = 1;
    if (icon == 730 && g_frontendScreenStatus.settings.local != 0) {
        show = g_playerAimHudEnabled;
    }
    if (icon != -1) {
        switch (icon) {
        case 730:
        case 751:
        case 752:
            scale = 8.0f;
            break;
        case 700:
        case 740:
        case 753:
        case 754:
        case 770:
        case 800:
        case 810:
        case 811:
        case 860:
        case 861:
            scale = 32.0f;
            break;
        default:
            scale = 16.0f;
            break;
        }
        if (show) {
            Playerai_DrawProjectedAimIcon(view, &player->views5E8.view7C0_104.targetPosition, icon, player->views5E8.view7BC_102.timer, scale, 1.0f);
        }
    }

    icon = player->views5E8.view798_96.carried;
    show = 1;
    if (icon == 730 && g_frontendScreenStatus.settings.local != 0) {
        show = g_playerAimHudEnabled;
    }
    if (icon != -1) {
        switch (icon) {
        case 730:
        case 751:
        case 752:
            scale = 8.0f;
            break;
        case 700:
        case 740:
        case 753:
        case 754:
        case 770:
        case 800:
            scale = 32.0f;
            break;
        case 755:
        case 756:
        default:
            scale = 16.0f;
            break;
        }
        if (show) {
            Playerai_DrawProjectedAimIcon(view, &player->views5E8.view79C_98.carriedPosition, icon, player->views5E8.view7BC_102.timer, scale, 1.0f);
        }
    }
}

/* Gdynlight allocates the same CDLight records initialized by Ovlgame. */
#if defined(VERSION_US)
#define PLAYER_SECOND_LIGHT_RADIUS g_playerSecondaryLightRadiusUs
#else
#define PLAYER_SECOND_LIGHT_RADIUS g_playerSecondaryLightRadius
#endif

/* Position one effect light, reading its scale and radius at their use sites. */
static inline void placePlayerLight(struct Player *player, CDLight *light,
                                    f32 offsetZ, const f32 *heightScale, const f32 *radius) {
    CVector3 offset;
    CVector3 position;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = offsetZ;
    Gobjinst_TransformVectorByActorAim(&position, player, offset);
    Graphu64_AddVec3(&position, &position, &player->pos);
    light->m_bEnabled = 1;
    light->x = (s16)position.x;
    light->y = (s16)(position.y + Gobjinst_GetActorHeight(player) * *heightScale);
    light->z = (s16)position.z;
    light->m_ColorFade = *radius;
}
/* Keep the timer lights and the special-mode light in step with player state. */
void Player_UpdatePlayerEffectLights(struct Player *player) {
    CDLight *light;
    s32 flicker;
    if (g_gameSettings.flags & 0x4000) {
        player->rangeTimer = 0.0f;
    } else if (player->rangeNodes[2] != 0) {
        Gdynlight_ReleaseLight(&g_dynamicLightPool, (s32)player->rangeNodes[2]);
        player->rangeNodes[2] = 0;
    }
    if (player->rangeTimer != 0.0f) {
        light = (CDLight *)player->rangeNodes[0];
        if (light == 0) {
            light = Gdynlight_AllocateLightNode(&g_dynamicLightPool, &PLAYER_EFFECT_LIGHT_PATTERN);
        }
        if (light != 0) {
            player->rangeNodes[0] = (struct CDLight_t *)light;
            placePlayerLight(player, light, g_playerPrimaryLightForwardOffset, &g_playerPrimaryLightHeight, &g_playerPrimaryLightRadius);
        }
        light = (CDLight *)player->rangeNodes[1];
        if (light == 0) {
            light = Gdynlight_AllocateLightNode(&g_dynamicLightPool, &g_playerSecondaryLightPattern);
        }
        if (light != 0) {
            player->rangeNodes[1] = (struct CDLight_t *)light;
            placePlayerLight(player, light, g_playerSecondaryLightForwardOffset, &g_playerSecondaryLightHeight, &PLAYER_SECOND_LIGHT_RADIUS);
        }
        if (player->rangeTimer < g_playerRangeLightFlickerInterval) {
            flicker = 1;
            if (player->rangeTimer < g_playerRangeLightRapidFlickerInterval) {
                flicker ^= (Graphu64_NextRandom() % 100) < 50;
            } else {
                if ((Graphu64_NextRandom() % 100) < 15) {
                    flicker = 0;
                }
            }
            if (player->rangeNodes[0] != 0) {
                ((CDLight *)player->rangeNodes[0])->m_bEnabled = flicker;
            }
            if (player->rangeNodes[1] != 0) {
                ((CDLight *)player->rangeNodes[1])->m_bEnabled = flicker;
            }
        }
    } else {
        if (player->rangeNodes[0] != 0) {
            Gdynlight_ReleaseLight(&g_dynamicLightPool, (s32)player->rangeNodes[0]);
            player->rangeNodes[0] = 0;
        }
        if (player->rangeNodes[1] != 0) {
            Gdynlight_ReleaseLight(&g_dynamicLightPool, (s32)player->rangeNodes[1]);
            player->rangeNodes[1] = 0;
        }
    }
    if (g_gameSettings.flags & 0x4000) {
        light = (CDLight *)player->rangeNodes[2];
        if (light == 0) {
            light = Gdynlight_AllocateLightNode(&g_dynamicLightPool, &PLAYER_MODE_LIGHT_PATTERN);
        }
        if (light != 0) {
            player->rangeNodes[2] = (struct CDLight_t *)light;
            placePlayerLight(player, light, 0.0f, &g_playerRangeLightHeight, &g_playerRangeLightRadius);
        }
        if ((player->actionFlags & 0x20) && player->rangeNodes[2] != 0) {
            CDLight *entry = (CDLight *)player->rangeNodes[2];
            if (entry->m_pROMLight == &PLAYER_MODE_LIGHT_PATTERN) {
                entry->m_pROMLight = (struct LightData *)&g_playerAlternateModeLightPattern;
            } else {
                entry->m_pROMLight = (struct LightData *)&PLAYER_MODE_LIGHT_PATTERN;
            }
        }
    }
}

#undef PLAYER_SECOND_LIGHT_RADIUS

void Playerai_DrawAmmoCounters(PowerHudPlayer *player, Shared_HudView *view) {
    f32 sx, sy, numberScale, offset, halfWidth, x, y;
    sx = view->width/(f32)g_hudReferenceViewportWidth;
    sy = view->height/(f32)g_hudReferenceViewportHeight;
    if (Frontend_GetScreenMode() == 0) {
        numberScale = g_playerAmmoNumberScaleStandard;
        offset = g_playerAmmoNumberOffsetStandard;
    } else {
        numberScale = g_playerAmmoNumberScaleAlternate;
        offset = g_playerAmmoNumberOffsetAlternate;
    }
    halfWidth = sx*g_playerAmmoIconHalfWidth;
    if (player->first != player->a.last || player->refreshA) {
        if (Frontend_GetScreenMode() == 0) OnScreen_StartMoverScript(&player->a, g_playerAmmoCounterAMoverScript);
        else OnScreen_StartMoverScript(&player->a, g_playerAmmoCounterAMoverScript+12);
        player->refreshA = 0;
        player->a.last = player->first;
    }
    if (player->second != player->b.last || player->refreshB) {
        if (Frontend_GetScreenMode() == 0) OnScreen_StartMoverScript(&player->b, g_playerAmmoCounterBMoverScript-12);
        else OnScreen_StartMoverScript(&player->b, g_playerAmmoCounterBMoverScript);
        player->refreshB = 0;
        player->b.last = player->second;
    }
    if (player->third != player->c.last || player->refreshC) {
        if (Frontend_GetScreenMode() == 0) OnScreen_StartMoverScript(&player->c, g_playerAmmoCounterCMoverScriptStandard);
        else OnScreen_StartMoverScript(&player->c, g_playerAmmoCounterCMoverScriptAlternate);
        player->refreshC = 0;
        player->c.last = player->third;
    }
    if (Playerai_GetSelectedAmmoIcon(player) != -1) {
        if (player->a.object && player->a.state && player->weapon<18) {
            x = player->a.x*sx+view->x;
            y = player->a.y*sy+view->y+view->height;
            x += offset;
            OnScreen_DrawSpriteResource(3050, 0, (s16)(x-halfWidth), (s16)(y-sy*g_playerAmmoCounterAIconYOffset), sx, sy, 1);
            x -= sx*g_playerAmmoCounterANumberXOffset;
            y -= sy*g_playerAmmoCounterANumberYOffset;
            OnScreen_DrawSpriteNumber(player->first, x, y, sx*numberScale, sy, 1, 0, 0);
        }
        if (player->b.object && player->b.state && player->weapon<18) {
            x = player->b.x*sx+view->x;
            y = player->b.y*sy+view->y+view->height;
            x += offset;
            OnScreen_DrawSpriteResource(3051, 0, (s16)(x-halfWidth), (s16)(y-sy*g_playerAmmoCounterBIconYOffset), sx, sy, 1);
            x -= sx*g_playerAmmoCounterBNumberXOffset;
            y -= sy*g_playerAmmoCounterBNumberYOffset;
            OnScreen_DrawSpriteNumber(player->second, x, y, sx*numberScale, sy, 1, 0, 0);
        }
        if (player->c.object && player->c.state && player->weapon<18) {
            x = player->c.x*sx+view->x;
            y = player->c.y*sy+view->y+view->height;
            x += offset;
            OnScreen_DrawSpriteResource(3052, 0, (s16)(x-halfWidth), (s16)(y-sy*g_playerAmmoCounterCIconYOffset), sx, sy, 1);
            x -= sx*g_playerAmmoCounterCNumberXOffset;
            y -= sy*g_playerAmmoCounterCNumberYOffset;
            OnScreen_DrawSpriteNumber(player->third, x, y, sx*numberScale, sy, 1, 0, 0);
        }
    }
}

/* Runs a player's standing and walking state for its body: settles the weapon sway through
   Player_UpdateWeaponSwayAndBob, turns the view through Player_UpdateViewAngles with the crouching tuning g_playerGroundViewAngleParameters while the
   crouch is past 5.12 or the standing tuning g_playerAirViewAngleParameters otherwise, and unless a jump releases
   the player into mode 5 it hands strafing or lifting (outside zoom mode 2) to mode
   3; then, unless an unfinished pickup, reload or wave animation is playing, it picks the animation at
   0x86C: for the idle character g_fragTagModelId the fidget animations 1 and 2 alternate after 12 and 21 time
   units, and otherwise the turning animations follow the heading change this frame (0xA28
   while the body is falling, with a separate set for the character g_playerSpecialAnimationTable). */




static inline s32 try_jump_Player_UpdateFlyMode(SharedPlayer *player, BodyPlayerUpdateStandingState *body) {
    if (player->views5E8.view7E8_106.zoomed == 0 && !(11.25f < player->views5E8.view6E4_62.depth) && !(body->flags & 0xC0000)
        && (body->surface->flags & 2) && (player->views5E8.view6B0_47.input & 0x10) && player->views5E8.view11D8_149.stun <= 0.0f) {
        Player_SetPlayerState(player, body, 5);
        return 1;
    }
    return 0;
}

void Player_UpdateFlyMode(void *player, void *bodyActor) {
    CVector3 direction;
    f32 held;
    f32 value;
    s32 flags;
    s32 result;
    void *data;

    if (((PlayerFlyModeView *)player)->action == 0 &&
        !(((PlayerFlyModeView *)player)->motionFlags & 0xE000)) {
        ((PlayerFlyModeView *)player)->action = 1;
    }
    ((PlayerFlyModeView *)player)->lean = 0;

    held = (&g_playerFlyYawInputScale)[1];
    Graphu64_EaseValueToward(&((PlayerFlyBodyView *)(bodyActor))->yaw,
                  ((PlayerFlyBodyView *)bodyActor)->yaw +
                      (f32)((ControllerAxesView *)((PlayerFlyModeView *)player)->controller)->x * g_playerFlyYawInputScale,
                  held);
    Graphu64_EaseValueToward(&((PlayerFlyModeView *)(player))->pitch,
                  ((PlayerFlyModeView *)player)->pitch +
                      (f32)-((ControllerAxesView *)((PlayerFlyModeView *)player)->controller)->y * g_playerFlyPitchInputScale,
                  held);

    value = ((PlayerFlyModeView *)player)->lateralInput;
    if (value != 0.0f) {
        f32 step;
        f32 limit;
        step = value * (&g_playerFlyPitchInputScale)[1];
        if (value < 0.0f) {
            limit = -value * g_playerFlyReverseSpeedScale;
        } else {
            limit = value * g_playerFlyForwardSpeedScale;
        }
        ((PlayerFlyModeView *)player)->forwardSpeed =
            Graphu64_IntegrateBoundedValue(((PlayerFlyModeView *)player)->forwardSpeed, step, limit);
    } else {
        ((PlayerFlyModeView *)player)->forwardSpeed =
            Graphu64_DecayToZero(((PlayerFlyModeView *)player)->forwardSpeed, g_playerFlyForwardSpeedDecay);
    }

    value = ((PlayerFlyModeView *)player)->forwardInput;
    if (value != 0.0f) {
        f32 step;
        f32 limit;
        step = value * g_playerFlyStrafeAcceleration;
        if (value < 0.0f) {
            limit = -value * g_playerFlyLeftSpeedScale;
        } else {
            limit = value * g_playerFlyRightSpeedScale;
        }
        ((PlayerFlyModeView *)player)->lateralSpeed =
            Graphu64_IntegrateBoundedValue(((PlayerFlyModeView *)player)->lateralSpeed, step, limit);
    } else {
        ((PlayerFlyModeView *)player)->lateralSpeed =
            Graphu64_DecayToZero(((PlayerFlyModeView *)player)->lateralSpeed, g_playerFlyStrafeSpeedDecay);
    }

    flags = ((PlayerFlyModeView *)player)->motionFlags;
    if (flags & 0x10) {
        ((PlayerFlyBodyView *)bodyActor)->verticalSpeed =
            Graphu64_IntegrateBoundedValue(((PlayerFlyBodyView *)bodyActor)->verticalSpeed, g_playerFlyRiseAcceleration, 71.68f);
    } else if (flags & 0x2020) {
        ((PlayerFlyBodyView *)bodyActor)->verticalSpeed =
            Graphu64_IntegrateBoundedValue(((PlayerFlyBodyView *)bodyActor)->verticalSpeed, g_playerFlyFallAcceleration, 71.68f);
    } else {
        ((PlayerFlyBodyView *)bodyActor)->verticalSpeed =
            Graphu64_DecayToZero(((PlayerFlyBodyView *)bodyActor)->verticalSpeed, g_playerFlyVerticalSpeedDecay);
    }

    {
        f32 angle;
        angle = ((PlayerFlyBodyView *)bodyActor)->yaw;
        angle += (held = g_playerFlyPositiveYawPeriod);
        direction.x = ((PlayerFlyModeView *)player)->forwardSpeed * Gu_Sinf(angle);
    }
    direction.y = ((PlayerFlyBodyView *)bodyActor)->verticalSpeed;
    direction.z = ((PlayerFlyModeView *)player)->forwardSpeed *
                  Math_Cosf(((PlayerFlyBodyView *)bodyActor)->yaw + held);
    held = g_playerFlyNegativeYawPeriod;
    direction.x += ((PlayerFlyModeView *)player)->lateralSpeed *
                   Gu_Sinf(((PlayerFlyBodyView *)bodyActor)->yaw - held);
    direction.z += ((PlayerFlyModeView *)player)->lateralSpeed *
                   Math_Cosf(((PlayerFlyBodyView *)bodyActor)->yaw - held);

    Graphu64_ScaleVector(&direction, &direction, g_frameElapsedTime);
    Graphu64_AddVec3(&((PlayerFlyModeView *)(player))->previousPosition,
                  &((PlayerFlyModeView *)(player))->previousPosition, &direction);
    result = Scene_FindFloorPolygon(&g_world, &((PlayerFlyBodyView *)bodyActor)->position);
    if (result != 0) {
        ((PlayerFlyBodyView *)bodyActor)->model = result;
    }

    if (((PlayerFlyModeView *)player)->action == 1 &&
        (((PlayerFlyModeView *)player)->motionFlags & 0xE000) == 0xE000 &&
        (((PlayerFlyModeView *)player)->inputFlags & 0xE000)) {
        Player_SetPlayerState(player, bodyActor, 2);
        data = ((PlayerFlyModeView *)player)->view;
        if (data != 0) {
            Camera_PostScreenMessage(&g_frontendScreenStatus, data, &s_flyModeOffText);
        }
    }
}

void Player_UpdateStandingState(SharedPlayer *player, BodyPlayerUpdateStandingState *body) {
    f32 heading;
    s32 crouching;
    s32 animate;

    Player_UpdateWeaponSwayAndBob(player, body);
    heading = body->heading;
    crouching = 5.12f < player->views5E8.view718_70.crouch;
    if (crouching) {
        Player_UpdateViewAngles(player, body, &g_playerGroundViewAngleParameters);
    } else {
        Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    }
    heading = body->heading - heading;
    if (try_jump_Player_UpdateFlyMode(player, body)) {
        return;
    }
    if (player->views5E8.view6A4_42.strafe != 0.0f || (player->views5E8.view7E8_106.zoomed != 2 && player->views5E8.view6A8_44.lift != 0.0f)) {
        Player_SetPlayerState(player, body, 3);
    }
    animate = 1;
    if ((player->views5E8.view86C_127.animation == 4400 || player->views5E8.view86C_127.animation == 4405) && player->views1C.view10E_13.idle == 0) {
        animate = 0;
    }
    if ((player->views5E8.view86C_127.animation == 24150 || player->views5E8.view86C_127.animation == 24158) && player->views1C.view10E_13.idle == 0) {
        animate = 0;
    }
    if ((player->views5E8.view86C_127.animation == 4000 || player->views5E8.view86C_127.animation == 4100) && player->views1C.view10E_13.idle == 0) {
        animate = 0;
    }
    if (animate) {
        if (player->views1C.viewE4_7.kind == g_fragTagModelId) {
            if (player->views5E8.view86C_127.animation == 1 && 12.0f <= player->views1C.view104_11.idleTime) {
                player->views5E8.view86C_127.animation = 2;
            } else if (player->views5E8.view86C_127.animation == 2 && 21.0f <= player->views1C.view104_11.idleTime) {
                player->views5E8.view86C_127.animation = 1;
            } else if ((u32) (player->views5E8.view86C_127.animation - 1) >= 2) {
                player->views5E8.view86C_127.animation = 1;
            }
        } else if (player->views13B4.view13B4_3.character == &g_playerSpecialAnimationTable) {
            if (body->flags & 0xC0000) {
                player->views5E8.view86C_127.animation = 2600;
            } else if (0.017453294f < heading) {
                player->views5E8.view86C_127.animation = 24102;
            } else if (heading < -0.017453294f) {
                player->views5E8.view86C_127.animation = 24101;
            } else {
                player->views5E8.view86C_127.animation = 24100;
            }
        } else {
            if (body->flags & 0xC0000) {
                player->views5E8.view86C_127.animation = 2600;
            } else if (0.017453294f < heading) {
                player->views5E8.view86C_127.animation = 2910;
            } else if (heading < -0.017453294f) {
                player->views5E8.view86C_127.animation = 2900;
            } else {
                player->views5E8.view86C_127.animation = 1;
            }
        }
    }
}

/* State callbacks receive an opaque actor context. */
void Playerai_UpdateWalkingMovement(void *playerContext, void *bodyContext) {
    SharedPlayer *player = playerContext;
    PlayerBodyPositionYawView *body = bodyContext;
    f32 strafeSpeed;
    f32 elapsedStepTime;
    f32 forwardSpeedMagnitude;
    s32 currentFireAnimation;
    s32 leftStrafeAnimation;
    s32 rightStrafeAnimation;
    s32 forwardAnimation;
    s32 backwardAnimation;
    s32 crouchingView;
    s32 crouchingMovement;
    s32 jumpStarted;
    s32 animationChoice;
    char *primaryFireMode;
    char *secondaryFireMode;
    u16 kind;
    s32 nextAnimation;

    Player_EaseOwnerHeightEffect(playerContext);
    Graphu64_EaseValueToward(&player->views5E8.view72C_75.strideRoll, 0.0f, 0.25f);
    crouchingView = 1;
    if (!(player->views5E8.view718_70.crouch > g_playerWalkingCrouchThreshold)) {
        crouchingView = 0;
    }
    if (crouchingView != 0) {
        Player_UpdateViewAngles(player, body, &g_playerGroundViewAngleParameters);
    } else {
        Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    }
    crouchingMovement = 1;
    if (!(player->views5E8.view718_70.crouch > g_playerWalkingCrouchReleaseThreshold)) {
        crouchingMovement = 0;
    }
    if (crouchingMovement != 0) {
        Player_UpdateGroundThrustAndBoost(player, body, &g_playerGroundMovementParameters);
    } else {
        Player_UpdateGroundThrustAndBoost(player, body, &g_playerJumpMovementParameters);
    }
    if ((player->views5E8.view7E8_105.zoomed == 0)
            && !(player->views5E8.view6E4_61.jumpDelay > g_playerWalkingJumpDelayLimit) && !(body->flags & 0xC0000)
            && (body->model->flags & 2) && (player->views5E8.view6B0_46.actionFlags & 0x10)
            && (player->views5E8.view11D8_147.jumpCooldown <= 0.0f)) { Player_SetPlayerState(player, body, 5); jumpStarted = 1; } else jumpStarted = 0;
    if (jumpStarted == 0) {
        if ((player->views5E8.view6C0_51.movementSpeed == 0.0f) && (player->views5E8.view6C4_54.sideSpeed == 0.0f)) {
            Player_SetPlayerState(player, body, 2);
        }
        if (((body->flags & 0x5000) == 0x4000) && (player->views5E8.view6D0_71.onGround != 0)) {
            elapsedStepTime = player->views5E8.view11C4_144.soundTime + g_frameElapsedTime;
            player->views5E8.view11C4_144.soundTime = elapsedStepTime;
            if ((player->views5E8.view6C8_56.speed > g_playerWalkingStepSpeedThreshold) && (g_playerWalkingStepInterval <= elapsedStepTime)) {
                player->views5E8.view11C4_144.soundTime = (f32) (elapsedStepTime - g_playerWalkingStepInterval);
            }
        }
        kind = player->views1C.viewE4_7.kind;
        if (kind == g_playerSpecialModelIds[2]) {
            if (player->views5E8.view86C_125.animationId == 2010
                    && player->views1C.view104_11.idleTime >= g_playerWalkAnimationSwapTime) player->views5E8.view86C_125.animationId =
                        2011; else player->views5E8.view86C_125.animationId = 2010;
            return;
        }
        if (kind == g_playerSpecialModelIds[0]) {
            currentFireAnimation = player->views5E8.view86C_125.animationId;
            if (currentFireAnimation == 4000 && player->views1C.view104_11.idleTime < g_playerWalkFireDurations[0]) return;
            if (currentFireAnimation == 4100 && player->views1C.view104_11.idleTime < g_playerWalkFireDurations[1]) return;
        }
        if (body->flags & 0xC0000) {
            if (player->views5E8.view6C0_51.movementSpeed >= 0.0f) player->views5E8.view86C_125.animationId = 2610;
            else player->views5E8.view86C_125.animationId = 2615;
            return;
        }
        forwardSpeedMagnitude = player->views5E8.view6C0_51.movementSpeed;
        if (forwardSpeedMagnitude < 0.0f) forwardSpeedMagnitude = -forwardSpeedMagnitude;
        strafeSpeed = player->views5E8.view6C4_54.sideSpeed;
        if (strafeSpeed < 0.0f) {
            if (forwardSpeedMagnitude < -strafeSpeed) goto sideways;
            goto forward;
        }
        if (forwardSpeedMagnitude < strafeSpeed) {
sideways:
            if (player->views5E8.view6C4_54.sideSpeed < 0.0f) {
                if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) { player->views5E8.view86C_125.animationId = 2050; return; }
                leftStrafeAnimation = player->views5E8.view86C_125.animationId;
                if ((u32)(leftStrafeAnimation - 24150) < 7U) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFireDurations[2]) player->views5E8.view86C_125.animationId = 24107;
                    return;
                }
                if (leftStrafeAnimation == 24158) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFireDurations[3]) player->views5E8.view86C_125.animationId = 24107;
                    return;
                }
                player->views5E8.view86C_125.animationId = 24107;
            } else {
                if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) { player->views5E8.view86C_125.animationId = 2060; return; }
                rightStrafeAnimation = player->views5E8.view86C_125.animationId;
                if ((u32)(rightStrafeAnimation - 24150) < 7U) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFireDurations[4]) player->views5E8.view86C_125.animationId = 24108;
                    return;
                }
                if (rightStrafeAnimation == 24158) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFireDurations[5]) player->views5E8.view86C_125.animationId = 24108;
                    return;
                }
                player->views5E8.view86C_125.animationId = 24108;
            }
        } else {
forward:
            if (player->views5E8.view6C0_51.movementSpeed >= 0.0f) {
                if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) { player->views5E8.view86C_125.animationId = 2010; return; }
                forwardAnimation = player->views5E8.view86C_125.animationId;
                if ((u32)(forwardAnimation - 24150) < 9U) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFireDurations[6]) player->views5E8.view86C_125.animationId = 24105;
                    return;
                }
                if (forwardAnimation == 24158) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFireDurations[7]) player->views5E8.view86C_125.animationId = 24105;
                    return;
                }
                player->views5E8.view86C_125.animationId = 24105;
            } else {
                if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) { player->views5E8.view86C_125.animationId = 2015; return; }
                backwardAnimation = player->views5E8.view86C_125.animationId;
                if ((u32)(backwardAnimation - 24150) < 7U) {
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFireDurations[8]) player->views5E8.view86C_125.animationId = 24106;
                    return;
                }
                nextAnimation = 24158;
                if (backwardAnimation != nextAnimation) {
                    nextAnimation = 24106;
                    player->views5E8.view86C_125.animationId = nextAnimation;
                } else {
                    nextAnimation = 24106;
                    if (player->views1C.view104_11.idleTime >= g_playerWalkFireDurations[9]) player->views5E8.view86C_125.animationId = nextAnimation;
                }
            }
        }
    }
}

/* Runs a player's wading state for its body: sets the movement mode to 9 when still and 10
   when moving, settles the roll kick, turns the view and moves the body through Player_UpdateViewAngles
   and Player_UpdateGroundThrustAndBoost with tunings g_playerAirViewAngleParameters and g_playerClimbMovementParameters,
       and leaves the state (clearing the strokes
  , release mode 3) once the body loses surface flag 0x2000; otherwise looking down past 40
   degrees while lifting lowers the eye height and sets flag 0x100000 of g_globalGameplayFlags
   (cleared otherwise), the weapon sways on three sine waves of the state time, a jump input
   0x10 in shallow enough ground that allows it releases the player into mode 5, and otherwise the
   animation follows the vertical speed and a moving player plays the tuning's step sound
   whenever the step timer passes 11.25. Adapted from Player_UpdateFloatingState with the jump check as
   an inline function and the g_globalGameplayFlags flags read as an array. */




static inline s32 try_jump_Player_UpdateWadingState(SharedPlayer *player, BodyPlayerUpdateWadingState *body) {
    if (player->views5E8.view7E8_106.zoomed == 0 && !(11.25f < player->views5E8.view6E4_62.depth) && !(body->flags & 0xC0000)
        && (body->surface->flags & 2) && (player->views5E8.view6B0_47.input & 0x10) && player->views5E8.view11D8_149.stun <= 0.0f) {
        Player_SetPlayerState(player, body, 5);
        return 1;
    }
    return 0;
}

void Player_UpdateWadingState(SharedPlayer *player, BodyPlayerUpdateWadingState *body) {
    s32 idle;

    if (player->views5E8.view6C8_57.speed == 0.0f) {
        player->views5E8.view650_18.mode = 9;
    } else {
        player->views5E8.view650_18.mode = 10;
    }
    Graphu64_EaseValueToward(&player->views5E8.view72C_76.kickRoll, 0.0f, 0.25f);
    Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    Player_UpdateGroundThrustAndBoost(player, body, &g_playerClimbMovementParameters);
    if (!(body->flags & 0x2000)) {
        TeamSelect_EmptyWeaponWheelHook();
        Player_SetPlayerState(player, body, 3);
        return;
    }
    if (player->views5E8.view724_72.pitch * 57.295776f < -40.0f && player->views5E8.view6A8_44.lift > 0.0f) {
        player->views5E8.view6EC_65.height -= 10.24f;
        g_globalGameplayFlags[0] |= 0x100000;
    } else {
        g_globalGameplayFlags[0] &= ~0x100000;
    }
    player->views5E8.view730_79.sway[0] = Gu_Sinf(player->views5E8.view658_24.swimTime * 0.06981318f) * 0.043633237f;
    player->views5E8.view730_79.sway[1] = Gu_Sinf(player->views5E8.view658_24.swimTime * 0.08726647496f) * 0.043633237f;
    player->views5E8.view730_79.sway[2] = Gu_Sinf(player->views5E8.view658_24.swimTime * 0.10471976548f) * 0.043633237f;
    if (!try_jump_Player_UpdateWadingState(player, body)) {
        idle = 0;
        if (player->views5E8.view86C_127.animation == 4420) {
            idle = player->views1C.view10E_13.idle == 0;
        }
        if (player->views1C.viewE4_7.kind == g_fragTagModelId) {
            player->views5E8.view86C_127.animation = 2210;
        } else if (!idle) {
            if (1.024f <= player->views5E8.view6C0_52.climb) {
                player->views5E8.view86C_127.animation = 2210;
            } else if (player->views5E8.view6C0_52.climb <= -1.024f) {
                player->views5E8.view86C_127.animation = 2215;
            } else {
                player->views5E8.view86C_127.animation = 20;
            }
        }
        player->views5E8.view11C4_144.soundTime += g_frameElapsedTime;
        if (5.12f < player->views5E8.view6C8_57.speed && 11.25f < player->views5E8.view11C4_144.soundTime) {
            player->views5E8.view11C4_144.soundTime = 0.0f;
            SoundElement_PlaySoundAtPosition(g_playerClimbMovementParameters.strokeSound, *(CVector3 *)&body->x, 0, -1);
        }
    }
}

/* Runs a player's floating movement state for its body: sets the movement mode to 11 when
   still and 12 when moving (speed), turns the view through Player_UpdateViewAngles with tuning
   g_playerSwimViewAngleParameters, sways the weapon on three sine waves of the state time, moves the body through
   Player_UpdateFlyingThrustAndBoost with tuning g_playerSwimMovementParameters, and once the state time passes 2 without the body's flag
   0x1000 it ends the state: clears the strokes and the body's 0x20, plays sound 0x2DE, clears
   0x840 and hands the player to Player_SetPlayerState (mode 2 when body flags 3 are set, else 10); it then
   picks the animation from the vertical speed (kept while idle animation 0x1144
   plays) and, while moving faster than 5.12, plays the tuning's stroke sound and sound 0x2E0 whenever
   the sound timer passes 45, restarting it at a random value below 15. */


void Player_UpdateFloatingState(SharedPlayer *player, BodyPlayerUpdateFloatingState *body) {
    s32 idle;

    if (player->views5E8.view6C8_57.speed == 0.0f) {
        player->views5E8.view650_18.mode = 11;
    } else {
        player->views5E8.view650_18.mode = 12;
    }
    Player_UpdateViewAngles(player, body, &g_playerSwimViewAngleParameters);
    player->views5E8.view730_79.sway[0] = 2.0f * Gu_Sinf(player->views5E8.view658_24.swimTime * 0.06981318f) * 0.017453294f;
    player->views5E8.view730_79.sway[1] = 2.0f * Gu_Sinf(player->views5E8.view658_24.swimTime * 0.08726647496f) * 0.017453294f;
    player->views5E8.view730_79.sway[2] = 2.0f * Gu_Sinf(player->views5E8.view658_24.swimTime * 0.10471976548f) * 0.017453294f;
    Player_UpdateFlyingThrustAndBoost(player, body, &g_playerSwimMovementParameters);
    if (!(body->flags & 0x1000) && 2.0f < player->views5E8.view658_24.swimTime) {
        TeamSelect_EmptyWeaponWheelHook();
        body->stroke = 0;
        SoundElement_PlaySoundAtPosition(734, *(CVector3 *)&body->x, 0, -1);
        player->views5E8.view840_118.surfaced = 0;
        if (body->flags & 3) {
            Player_SetPlayerState(player, body, 2);
        } else {
            Player_SetPlayerState(player, body, 10);
        }
    }
    idle = 0;
    if (player->views5E8.view86C_127.animation == 4420) {
        idle = player->views1C.view10E_13.idle == 0;
    }
    if (player->views1C.viewE4_7.kind == g_fragTagModelId) {
        player->views5E8.view86C_127.animation = 2210;
    } else if (!idle) {
        if (1.024f <= player->views5E8.view6C0_52.climb) {
            player->views5E8.view86C_127.animation = 2210;
        } else if (player->views5E8.view6C0_52.climb <= -1.024f) {
            player->views5E8.view86C_127.animation = 2215;
        } else {
            player->views5E8.view86C_127.animation = 20;
        }
    }
    player->views5E8.view11C4_144.soundTime += g_frameElapsedTime;
    if (5.12f < player->views5E8.view6C8_57.speed && 45.0f < player->views5E8.view11C4_144.soundTime) {
        player->views5E8.view11C4_144.soundTime = Graphu64_RandomFloat(15.0f);
        SoundElement_PlaySoundAtPosition(g_playerSwimMovementParameters.strokeSound, *(CVector3 *)&body->x, 0, -1);
        SoundElement_PlaySoundAtPosition(736, *(CVector3 *)&body->x, 0, -1);
    }
}

s32 InstHdr_GetActorMotionState(void *);
/* Updates swimming turn, pitch, stride motion, sounds, and animation. */
void Player_UpdateSwimmingState(SharedPlayer *player, SharedPlayer *body) {
    Shared_Game *game;
    f32 detachDistance;
    f32 jumpHeadingOffset;
    f32 previousClimbSpeed;
    f32 strafeHeadingOffset;
    f32 motionSine;
    f32 motionIntermediate;
    f32 jumpedHeading;
    f32 releaseTurn;
    f32 movementHeading;
    f32 jumpTurn;
    f32 strideRoll;
    f32 climbInput;
    f32 strafeInput;
    f32 rollInput;
    f32 strideTime;
    f32 climbAcceleration;
    f32 strafeAcceleration;
    f32 pitchLimit;
    f32 adjustedJumpHeading;
    f32 climbSpeedLimit;
    f32 strafeSpeedLimit;
    f32 turnLimit;
    f32 targetPitch;
    s32 surfaceFlagsOrActorKind;
    s32 jumpStarted;
    s32 descending;
    f32 *eyex;
    f32 *eyey;
    f32 *eyez;
    s32 actorKindOrAnimation;
    s32 ascending;

    if (!(body->views1C.view38_3.flags & 0x100)) {
        player->views5E8.view724_72.pitch = 0.0f;
        player->turnAccumulator = 0.0f;
        if (InstHdr_GetActorMotionState(body) == 0) {
            detachDistance = g_playerSwimConstants;
            player->views5E8.view6E8_79.movementPosition.x -= Gu_Sinf(body->views1C.view6C_5.heading) * detachDistance;
            player->views5E8.view6E8_79.movementPosition.z -= Math_Cosf(body->views1C.view6C_5.heading) * detachDistance;
        }
        Player_SetPlayerState(player, body, 5);
        return;
    }
    motionIntermediate = player->views5E8.view69C_39.stick;
    if ((g_playerClimbTurnZero < motionIntermediate) || (motionIntermediate < g_playerClimbTurnZero)) {
        player->turnAccumulator += motionIntermediate * g_playerClimbTurnInputScale;
    }
    motionIntermediate = player->turnAccumulator;
    turnLimit = g_playerClimbTurnMaximum;
    if (turnLimit < motionIntermediate) player->turnAccumulator = turnLimit;
    else if (motionIntermediate < g_playerClimbTurnMinimum) player->turnAccumulator = g_playerClimbTurnMinimum;
    Graphu64_EaseValueToward(&player->views5E8.view728_73.kickPitch, player->turnAccumulator * g_playerClimbYawSwayScale, 0.5f);
    targetPitch = -player->views5E8.view69C_39.pitchInput * g_playerClimbPitchInputScale;
    pitchLimit = g_playerClimbPitchMinimum;
    if ((targetPitch < pitchLimit) || (pitchLimit = g_playerClimbPitchMaximum, (pitchLimit < targetPitch))) {
        targetPitch = pitchLimit;
    }
    Graphu64_EaseValueToward(&player->views5E8.view724_72.pitch, targetPitch * g_playerClimbPitchScale, 0.0625f);
    if ((player->views5E8.view7E8_105.zoomed == 0)
            && !(player->views5E8.view6E4_61.jumpDelay > g_playerClimbJumpDelayLimit)
            && !(body->views1C.view38_3.flags & 0xC0000) && (body->views18.view18_2.model->flags & 2)
            && (player->views5E8.view6B0_46.actionFlags & 0x10)
            && (player->views5E8.view11D8_147.jumpCooldown <= 0.0f)) { Player_SetPlayerState(player, body, 5); jumpStarted = 1; } else jumpStarted = 0;
    if (jumpStarted != 0) {
        jumpedHeading = body->views1C.view6C_5.heading + player->views5E8.view728_73.kickPitch;
        body->views1C.view6C_5.heading = jumpedHeading;
        jumpTurn = player->views5E8.view728_73.kickPitch;
        if (g_playerClimbJumpPositiveWrapThreshold <= jumpTurn) {
            adjustedJumpHeading = jumpedHeading + g_playerClimbJumpPositiveYawPeriod;
            goto block_25;
        }
        if (jumpTurn <= g_playerClimbJumpNegativeWrapThreshold) {
            adjustedJumpHeading = jumpedHeading - g_playerClimbJumpNegativeYawPeriod;
block_25:
            body->views1C.view6C_5.heading = adjustedJumpHeading;
        }
        movementHeading = body->views1C.view6C_5.heading;
        jumpHeadingOffset = g_playerClimbJumpHeadingOffset;
        motionSine = Gu_Sinf(movementHeading + jumpHeadingOffset);
        motionIntermediate = Math_Cosf(body->views1C.view6C_5.heading + jumpHeadingOffset);
        body->views1C.view1C_0.localDisplacement.x += motionSine * g_playerClimbJumpDisplacementScale;
        body->views1C.view1C_0.localDisplacement.z += motionIntermediate * g_playerClimbJumpDisplacementScale;
        releaseTurn = player->views5E8.view728_73.kickPitch;
        if (g_playerClimbReleasePositiveWrapThreshold <= releaseTurn) {
            body->views1C.view6C_5.heading += g_playerClimbReleasePositiveYawPeriod;
        } else if (releaseTurn <= g_playerClimbReleaseNegativeWrapThreshold) {
            body->views1C.view6C_5.heading -= g_playerClimbReleaseNegativeYawPeriod;
        }
        player->views5E8.view728_73.kickPitch = 0.0f;
        player->turnAccumulator = 0.0f;
        return;
    }
    strideRoll = player->views5E8.view6DC_60.strideSign * player->views5E8.view6C0_51.movementSpeed
        * Gu_Sinf(player->views5E8.view658_23.stride * g_playerClimbStrideFrequency);
    rollInput = player->views5E8.view6A8_44.lift;
    if (rollInput > 0.0f || rollInput < 0.0f)
        Graphu64_EaseValueToward(&player->views5E8.view72C_75.strideRoll, strideRoll, 0.25f);
    else Graphu64_EaseValueToward(&player->views5E8.view72C_75.strideRoll, 0.0f, 0.9f);
    climbInput = player->views5E8.view6A8_44.lift;
    ascending = climbInput > 0.0f;
    descending = climbInput < 0.0f;
    previousClimbSpeed = player->views5E8.view6C0_51.movementSpeed;
    if ((ascending != 0) || (descending != 0)) {
        climbAcceleration = climbInput * g_playerClimbAcceleration;
        if (climbInput < 0.0f) {
            climbSpeedLimit = -climbInput * g_playerClimbReverseSpeedScale;
        } else {
            climbSpeedLimit = climbInput * g_playerClimbForwardSpeedScale;
        }
        player->views5E8.view6C0_51.movementSpeed = Graphu64_IntegrateBoundedValue(player->views5E8.view6C0_51.movementSpeed,
            climbAcceleration, climbSpeedLimit);
    } else {
        player->views5E8.view6C0_51.movementSpeed = Graphu64_DecayToZero(previousClimbSpeed, g_playerClimbForwardSpeedDecay);
    }
    strafeInput = player->views5E8.view6A4_42.strafe;
    if (strafeInput != 0.0f) {
        strafeAcceleration = strafeInput * g_playerClimbStrafeAcceleration;
        if (strafeInput < 0.0f) {
            strafeSpeedLimit = -strafeInput * g_playerClimbLeftSpeedScale;
        } else {
            strafeSpeedLimit = strafeInput * g_playerClimbRightSpeedScale;
        }
        player->views5E8.view6C4_54.sideSpeed = Graphu64_IntegrateBoundedValue(player->views5E8.view6C4_54.sideSpeed, strafeAcceleration, strafeSpeedLimit);
    } else {
        player->views5E8.view6C4_54.sideSpeed = Graphu64_DecayToZero(player->views5E8.view6C4_54.sideSpeed, g_playerClimbStrafeSpeedDecay);
    }
    if ((player->views5E8.view6C0_51.movementSpeed == 0.0f) && (player->views5E8.view6C4_54.sideSpeed == 0.0f)) {
        player->views5E8.view658_23.stride = 0.0f;
        if (previousClimbSpeed != 0.0f) {
            player->views5E8.view6DC_60.strideSign = -player->views5E8.view6DC_60.strideSign;
        }
    } else {
        strideTime = player->views5E8.view658_23.stride;
        if (g_playerClimbStridePeriod < strideTime) {
            player->views5E8.view6DC_60.strideSign = -player->views5E8.view6DC_60.strideSign;
            player->views5E8.view658_23.stride = strideTime - g_playerClimbStridePeriod;
            player->views5E8.view6C0_51.movementSpeed *= g_playerClimbSpeedDamping;
            player->views5E8.view6C4_54.sideSpeed *= g_playerClimbSpeedDamping;
            game = &g_gameSettings;
            if ((game->local != 0) && ((player->views5D8.view5D8_9.profile->remote != 1) || (game->fragTagEnabled == 0))) {
                surfaceFlagsOrActorKind = player->views1C.view38_3.flags;
                if (surfaceFlagsOrActorKind & 0x200) {
                    SoundElement_PlaySoundAtPosition(g_playerClimbStepSound, body->views0.view8_4.position, 0, -1);
                } else if (surfaceFlagsOrActorKind & 0x400) {
                    SoundElement_PlaySoundAtPosition(g_playerClimbReleaseSound, body->views0.view8_4.position, 0, -1);
                } else if (surfaceFlagsOrActorKind & 0x800) {
                    SoundElement_PlaySoundAtPosition(g_playerClimbJumpSound, body->views0.view8_4.position, 0, -1);
                } else {
                    SoundElement_PlaySoundAtPosition(strideSound(player->views5DC.view5E0_10.slot), body->views0.view8_4.position, 0, -1);
                }
            }
        }
    }
    eyex = &player->views5E8.view6E8_79.movementPosition.x;
    eyey = &player->views5E8.view6E8_79.movementPosition.y;
    eyez = &player->views5E8.view6E8_79.movementPosition.z;
    movementHeading = body->views1C.view6C_5.heading;
    strafeHeadingOffset = g_playerClimbStrafeHeadingOffset;
    motionSine = Gu_Sinf(movementHeading - strafeHeadingOffset);
    motionIntermediate = Math_Cosf(body->views1C.view6C_5.heading - strafeHeadingOffset);
    {
    f32 horizontal = *eyex + motionSine * player->views5E8.view6C4_54.sideSpeed * player->views5E8.view66C_29.movementTimeScale;
    f32 coefficient = k_playerSwimmingVerticalMotionScale;
    f32 frameDelta = g_frameElapsedTime;
    *eyex = horizontal;
    *eyez += motionIntermediate * player->views5E8.view6C4_54.sideSpeed * player->views5E8.view66C_29.movementTimeScale;
    motionIntermediate = *eyey + player->views5E8.view6C0_51.movementSpeed * (frameDelta * coefficient);
    *eyey = motionIntermediate;
    actorKindOrAnimation = g_fragTagModelId;
    surfaceFlagsOrActorKind = player->views1C.viewE4_7.kind;
    if (surfaceFlagsOrActorKind != actorKindOrAnimation) { if (player->views5E8.view6C0_51.movementSpeed > 0.0f) {
        if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) player->views5E8.view86C_125.animationId = 2630;
        else player->views5E8.view86C_125.animationId = 24104; } else {
        if (player->views13B4.view13B4_3.character != &g_playerSpecialAnimationTable) player->views5E8.view86C_125.animationId = 2620;
        else player->views5E8.view86C_125.animationId = 24103; } } else { actorKindOrAnimation = 2630;
        player->views5E8.view86C_125.animationId = actorKindOrAnimation; }
}}

/* Handles a player's death: stops the body's motion to 0x24 and runs Player_ReleaseObjectHandles_PlayeraiResetplayerafterdeath; in a
   single player game (g_motionVisibilitySettings) a player with limited lives gets the death menu for its
   profile slot 0 to 3 on its view, and when g_selectedProfileHealthOptionEnabled asks and the player is out of a team game, once
   every active player among the first eight is out the team is revived through Player_PlacePlayerForRound (every
   active player in mode 2 when the mode 14 leader is down, and the leader in modes below 3); in
   multiplayer the view shows the respawn menu, g_playerRespawnCountDialog when the player has a respawn count
   or g_playerRespawnDialog otherwise. */




void Playerai_ResetPlayerAfterDeath(SharedPlayer *player, PlayerRespawnBodyView *body) {
    SharedPlayer *other;
    SharedPlayer *leader;
    s32 i;
    s32 active;
    s32 out;

    body->motion[0] = 0;
    body->motion[1] = 0;
    body->motion[2] = 0;
    Player_ReleaseObjectHandles(player);
    if (g_gameSettings.local != 0) {
        if (player->views1450.view1450_2.infinite == 0) {
            switch (player->views1C.view5D4_46.slot) {
            case 0:
                Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, g_playerDeathDialogs[0], player, player->views5E8.view698_36.controller, 0);
                break;
            case 1:
                Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, g_playerDeathDialogs[1], player, player->views5E8.view698_36.controller, 0);
                break;
            case 2:
                Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, g_playerDeathDialogs[2], player, player->views5E8.view698_36.controller, 0);
                break;
            case 3:
                Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, g_playerDeathDialogs[3], player, player->views5E8.view698_36.controller, 0);
                break;
            }
        }
        if (g_gameSettings.counters.enabled != 0 && player->views5D8.view5D8_2.controls->team == 0 && player->views5D8.view5D8_2.controls->active != 0) {
            active = 0;
            out = 0;
            leader = 0;
            for (i = 0; i < 8; i++) {
                other = Playerai_GetPlayerByIndex(&g_playerViewRenderContext, i);
                if (other != 0) {
                    if (other->views5D8.view5D8_2.controls->active != 0) {
                        active++;
                        if (other->views5E4.view5E4_3.alive == 0) {
                            out++;
                        }
                    }
                    if (other->views5D8.view5D8_2.controls->mode == 14) {
                        leader = other;
                    }
                }
            }
            if (out == active) {
                if (g_gameSettings.counters.m_nTalsetLives == 2 && leader->views5E4.view5E4_3.alive == 0) {
                    for (i = 0; i < 8; i++) {
                        other = Playerai_GetPlayerByIndex(&g_playerViewRenderContext, i);
                        if (other != 0 && other->views5D8.view5D8_2.controls->active != 0) {
                            Player_PlacePlayerForRound(other);
                        }
                    }
                }
                if (g_gameSettings.counters.m_nTalsetLives < 3) {
                    Player_PlacePlayerForRound(leader);
                }
            }
        }
    } else if (player->views5DC.view5DC_2.view != 0) {
        if (player->views5E8.view5EA_3.respawns != 0) {
            Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, &g_playerRespawnCountDialog_de, player, player->views5E8.view698_36.controller, 0);
        } else {
            Menu_OpenDialog(player->views5DC.view5DC_2.view->menu, &g_playerRespawnDialog, player, player->views5E8.view698_36.controller, 0);
        }
    }
}



void Playerai_TryStartPlayerSequence(PlayerSequenceActorView *playerActor, void *bodyActor, s32 sequenceType)
{
    s32 enabled;
    u32 resource_flags;
    void *resource;
    s32 i;

    enabled = 1;
    resource_flags = 0;

    if (playerActor->modelRecordIndexPointer != 0) {
        resource = Scene_GetModelRecordByIndexPointer(&g_world, playerActor->modelRecordIndexPointer);
        if (resource != 0) {
            resource_flags = ((PlayerSequenceResourceView *)(resource))->resourceFlagBits;
        }
    }

    if (g_world.visibilityEnabled != 0) {
        enabled = 0;
    }
    if (playerActor->stateFlags & 0x8000) {
        enabled = 0;
    }
    if (g_world.visibilityEnabled != 0) {
        enabled = 0;
    }
    if (g_playerCount >= 2) {
        enabled = 0;
    }
    if (sequenceType == 12) {
        enabled = 0;
    }
    if (playerActor->stateFlags & 0x8000) {
        enabled = 0;
    }
    if (resource_flags & 0x1000000) {
        enabled = 0;
    }
    if ((resource_flags & 0x80000) &&
        (sequenceType != 20) && (sequenceType != 40) && (sequenceType != 30)) {
        enabled = 0;
    }

    playerActor->sequenceEnabled = enabled;
    if (enabled != 0) {
        if (sequenceType == 50) {
            void *data;

            data = playerActor->view;
            g_playerSequenceCompletionPending = 1;
            if (data != 0) {
                for (i = 0; i < 4; i++) {
                    g_playerSequenceSavedViewBytes[i] = ((struct PlayerViewSavedBytes *) (((u8 *) playerActor->view) + i))->savedByte;
                }
            }
        }
        g_playerSequenceWindowEnabled = 0;
        g_playerSequenceActor = (Player *)playerActor;
        CCinema_RequestTrackWithCallbacks(sequenceType, 0, (VoidCallback)&g_playerSequenceCallbacks);
    }

    resource = Scene_FindActorDefinition(&g_world, -1, 3141);
    if (resource != 0) {
        playerActor->scaleX = ((PlayerSequenceResourceView *)(resource))->scaleX;
        playerActor->scaleY = ((PlayerSequenceResourceView *)(resource))->scaleY;
        playerActor->scaleZ = ((PlayerSequenceResourceView *)(resource))->scaleZ;
    }
}

typedef struct { f32 x, y, z; } Position;
/* A travel waypoint: where the player ends up, the arc height of the trip, and its duration in 15-frame units. */
struct TravelTarget { u8 pad0[0x34]; Position pos; f32 height; u8 pad44[0x1A]; u8 duration; };


void Playerai_UpdateTravelSequence(Player *player, void *body) {
    f32 yaw, targetYaw, distance, otherDistance, alternate, duration, t;
    CVector3 pos;
    Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    if (((struct TravelTarget *)player->effectModel) != 0) {
        player->travelElapsed += g_frameElapsedTime;
        yaw = player->heading;
        targetYaw = player->modelDistance;
        if (targetYaw != yaw) {
            Graphu64_WrapPeriodicValue(&yaw);
            Graphu64_WrapPeriodicValue(&targetYaw);
            if (yaw > targetYaw) {
                alternate = targetYaw + g_playerTravelPositiveYawPeriod;
                if (alternate - yaw < yaw - targetYaw) targetYaw = alternate;
            } else {
                alternate = targetYaw - g_playerTravelNegativeYawPeriod;
                if (yaw - alternate < targetYaw - yaw) targetYaw = alternate;
            }
            if (targetYaw > yaw) {
                yaw += (targetYaw - yaw) * g_playerTravelYawRiseScale;
                if (targetYaw < yaw) yaw = targetYaw;
            } else {
                yaw -= (yaw - targetYaw) * g_playerTravelYawFallScale;
                if (yaw < targetYaw) yaw = targetYaw;
            }
            Graphu64_WrapPeriodicValue(&yaw);
        }
        player->actorParts[1].yaw = yaw;
        player->heading = yaw;
        duration = (f32)(((struct TravelTarget *)player->effectModel)->duration * 15);
        if (player->travelElapsed < duration) {
            t = player->travelElapsed / duration;
            pos.x = player->effectPosition.x + (((struct TravelTarget *)player->effectModel)->pos.x - player->effectPosition.x) * t;
            pos.z = player->effectPosition.z + (((struct TravelTarget *)player->effectModel)->pos.z - player->effectPosition.z) * t;
            pos.y = player->effectPosition.y + (((struct TravelTarget *)player->effectModel)->pos.y - player->effectPosition.y) * t + ((struct TravelTarget *)player->effectModel)->height * ((t - t * t) * g_playerTravelArcHeightScale);
            player->previousPosition = pos;
            return;
        }
    }
    Player_SetPlayerState(player, body, 2);
}

void Playerai_UpdateMountedMovement(SharedPlayer *player, PlayerBodyPositionYawView *body) {
    Matrix rotation;
    struct Mount *mount;
    CVector3 *offset;
    SharedMovement *movement;
    f32 wave, yaw, unit, forward, side, bump, result, force, absolute, sway, rawForward, rawSide, time;
    mount = player->views5E8.view80C_108.mount;
    wave = Math_Cosf(player->views5E8.view838_114.rideTime*g_playerRideWaveFrequency);
    wave = (((wave+g_playerRideWaveInputOffset)*g_playerRideWaveInputScale+g_playerRideWaveOutputOffset)*g_playerRideWaveOutputScale);
    time = player->views5E8.view838_114.rideTime;
    sway = player->views5E8.view69C_40.stick; sway *= wave;
    time += g_frameElapsedTime;player->views5E8.view838_114.rideTime = time;
    unit = g_playerRideYawScale;
    yaw = body->yaw;
    sway *= unit;force = yaw+sway;
    Graphu64_EaseValueToward(&body->yaw, force, 0.9f);
    yaw = ((yaw-body->yaw)+player->views5E8.view69C_40.stick*g_playerRideSteeringScale)*unit;
    Graphu64_EaseValueToward(&player->views5E8.view72C_76.kickRoll, yaw, 0.1f);
    Player_UpdateViewAngles(player, body, &g_playerRideViewAngleParameters);
    offset = 0;
    if (player->views5E8.view6B8_50.input&8) {
        Actor_RequestActorState(mount, &mount->animation, 46);
        player->views5E8.view704_68.lift = g_playerRideDefaultLift;
        player->views5E8.view6C0_51.movementSpeed = g_playerRideInitialSpeedHalf+g_playerRideInitialSpeedHalf;
    }
    absolute = player->views5E8.view6C0_51.movementSpeed;
    bump = player->views5E8.view83C_116.bump;
    if (absolute<0.0f)absolute = -absolute;
    side = 2.0f*player->views5E8.view6C4_54.sideSpeed;
    if (side<0.0f ? -side<absolute : side<absolute) {
        rawForward = player->views5E8.view6C0_51.movementSpeed;
        if (rawForward<0.0f)result = bump-rawForward;
        else result = bump+rawForward;
    } else {
        rawSide = 2.0f*player->views5E8.view6C4_54.sideSpeed;
        if (rawSide<0.0f)result = bump-rawSide;
        else result = bump+rawSide;
    }
    player->views5E8.view83C_116.bump = result;
    if (g_playerRideBumpThreshold<result) {
        player->views5E8.view83C_116.bump = result-g_playerRideBumpThreshold;
        if (mount->animationId != 46) {
            player->views5E8.view6C0_51.movementSpeed *= g_playerRideSpeedDamping;
            player->views5E8.view6C4_54.sideSpeed *= g_playerRideSpeedDamping;
        }
        forward = player->views5E8.view6C0_51.movementSpeed;
        if (forward<0.0f)force = -forward*g_playerRideReverseShakeScale;
        else force = forward*g_playerRideForwardShakeScale;
        if (g_playerRideShakeMaximum<force)force = g_playerRideShakeMaximum;
        if (player->views5DC.view5DC_6.storage)Gsky_StartScaledShake(player->views5DC.view5DC_6.storage, 0.0f, force, 0.0f, g_playerRideShakeDuration, 1,
            body->position);
    }
    if (0.0f<player->views5E8.view6C0_51.movementSpeed)Player_UpdateGroundThrustAndBoost(player, body, ((struct SharedMovement *)&g_playerRideMovementParameters));
    else Player_UpdateGroundThrustAndBoost(player, body, ((struct SharedMovement *)&g_playerRideMovementParameters + 1));
    forward = player->views5E8.view6C0_51.movementSpeed;
    if (forward<0.0f ? g_playerRideReverseLiftThreshold < -forward : g_playerRideForwardLiftThreshold < forward)player->views5E8.view704_68.lift =
        g_playerRideRaisedLift;
    if (player->views5E8.view810_110.kind == 310) {
        offset = &g_playerRideOffset;
        __builtin_memcpy(&player->views5E8.view814_112.offset, &g_playerRideBaseOffset, sizeof(g_playerRideBaseOffset));
    }
    if (offset) {
        BuildYawMatrix(&rotation, body->yaw);
        Graphu64_TransformPoint(&rotation, offset, &player->views5E8.view73C_82.weapon);
        Graphu64_ScaleVector(&player->views5E8.view73C_82.weapon, &player->views5E8.view73C_82.weapon, 10.24f);
    }
}

/* Runs a player's hold on a carried object: while the player has a view, one frame in five
   on average it tints the view through Gsky_StartFade_PlayeraiInitializeplayerhealth with a random alpha below 7.5 and plays effect
   g_frontendScreenStatus at the view's position; the hold time counts down by the frame time g_frameElapsedTime,
   and once it runs out or the hold flag is clear the player drops flag 0x800000, is released
   through Player_SetPlayerState, and lets go of the object through Barrel_FillDamagePacket_PlayeraiInitializeplayerhealth (flags 0x30200 when
   the object is a carried actor with option 0x200, 0x4600 otherwise) before forgetting it and applying
   the result through Playerai_ApplyDamagePacket. */




void Playerai_UpdateHazardDamage(SharedPlayer *player) {
    Slot hit;
    FadeEmitterView *view;
    Held *owner;
    f32 alpha;
    s32 level;

    if (player->views5DC.view5DC_2.view != 0 && 80.0f < Graphu64_RandomFloat(100.0f)) {
        view = player->views5DC.view5DC_2.view;
        alpha = Graphu64_RandomFloat(7.5f);
        level = (u32) alpha;
        Gsky_StartFade(view, 0xFF, 0xFF, 0, 0, (u8) level, 3, 7);
        Gsky_StartEmitter(&g_frontendScreenStatus, 0.0f, 204.79999f, 0.0f, 512.0f, 0, *(CVector3 *)&view->position);
    }
    player->views1C.view1D4_21.holdTime -= g_frameElapsedTime;
    if (player->views1C.view1D4_21.holdTime <= 0.0f || player->views5E4.view5E4_4.holding == 0) {
        owner = 0;
        if (player->views13D8.view13D8_1.held->type == 1 && (player->views13D8.view13D8_1.held->flags & 0x300000)) {
            owner = player->views13D8.view13D8_1.held;
        }
        player->views1C.view100_9.flags &= ~0x800000;
        Player_SetPlayerState(player, player, 2);
        if (owner->options & 0x200) {
            Barrel_FillDamagePacket(&hit, player->views13D8.view13D8_1.held, 0x30200, 25.599998f, 128, 0);
        } else {
            Barrel_FillDamagePacket(&hit, player->views13D8.view13D8_1.held, 17920, 25.599998f, 128, 0);
        }
        player->views13D8.view13D8_1.held = 0;
        Playerai_ApplyDamagePacket(player, player->views1C.view170_16.body, &hit);
    }
}




void Playerai_UpdateTargetFacing(void *player, void *body) {
    CQuatern aimRotation;
    Shared_Quad aimWords;
    CVector3 toTarget;
    void *aimTarget;
    f32 targetAngle;
    f32 *position;
    f32 comparisonAngle;

    Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    if (((Player *)player)->overlay != 0) {
        aimRotation = Playerai_ComputeAimRotation(player, &aimTarget, (CVector3 *)&aimWords);
        if (aimTarget != 0) {
            position = &((Player *)player)->pos.x;
            if (!(((f32 *)&g_playerTargetFacingDistanceLimits)[1] < Graphu64_GetPointDistance(position, &((LevelActor *)aimTarget)->position0.x))) {
                if (CCollision_SweepPoint(player, ((Player *)player)->pos,
                                     ((LevelActor *)aimTarget)->position0,
                                     &g_particleCollisionProbeResult) == 0 ||
                    g_collisionCurrentActor->instance0 == aimTarget) {
                    Graphu64_SubtractVectors(&toTarget, &((LevelActor *)aimTarget)->position0, (CVector3 *)position);
                    targetAngle = Graphu64_GetHorizontalAngle(&toTarget);
                    Graphu64_WrapPeriodicValue(&targetAngle);
                    Graphu64_WrapPeriodicValue(&((LevelActor *)body)->yaw);
                    comparisonAngle = ((LevelActor *)body)->yaw;
                    if (g_playerTargetFacingPositiveWrapThreshold < comparisonAngle) {
                        if (targetAngle < g_playerTargetFacingNegativeWrapThreshold) {
                            targetAngle += g_playerTargetFacingYawPeriod;
                        } else {
                            goto positive;
                        }
                    } else {
positive:
                        comparisonAngle = targetAngle;
                        if (g_playerTargetFacingTurnThreshold < comparisonAngle &&
                            ((LevelActor *)body)->yaw < g_playerTargetFacingBodyYawThreshold) {
                            ((LevelActor *)body)->yaw =
                                ((LevelActor *)body)->yaw + g_playerTargetFacingBodyYawPeriod;
                        }
                    }
                    Graphu64_EaseValueToward(&((LevelActor *)body)->yaw, targetAngle, g_playerTargetFacingEaseRate);
                }
            }
        }
    }
}


/* Spawn definition of a player model: starting health and spawn position. */
typedef struct PlayerModelDefinition {
    u8 header[0x18];
    s32 startHealth;
    u8 body[0xE0];
    CVector3 spawnPosition;
} PlayerModelDefinition;

static inline PlayerModelDefinition *findModel(s32 kind, s32 id) {
    return (PlayerModelDefinition *)Scene_FindActorDefinition(&g_world, kind, id);
}
static inline s32 startHealth(Player *player) {
    s32 health;
    s8 kind;
    if (g_gameSettings.counters.enabled && player->profile->enabled != 0) {
        kind = player->profile->character;
        if (kind == 11) health = 0x19000;
        else if (kind == 12) health = 0x19000;
        else if (kind == 14) health = 76800;
        else if (kind == 13) health = 76800;
        else health = ((PlayerModelDefinition *)player->definition)->startHealth << 8;
    } else {
        health = ((PlayerModelDefinition *)player->definition)->startHealth << 8;
    }
    if (g_gameSettings.controllerMode == 1 && player->computer == 0) health += g_characterHealthBonuses[player->slot].value;
    return health;
}
void Playerai_InitializePlayerHealth(Player *player) {
    PlayerModelDefinition *model;
    s32 id;
    id = player->state;
    if (g_gameSettings.counters.m_bFragTagOn && player->profile->bonus == 1) id = 19;
    model = findModel(11, id);
    if (model == 0) {
        model = findModel(11, -1);
        if (model == 0) model = findModel(-1, -1);
    }
    player->definition = model;
    player->scale = model->spawnPosition;
    if (g_gameSettings.counters.m_bFragTagOn && player->profile->bonus != 0) {
        player->health = 2560;
        player->actorHealth = 2560;
        return;
    }
    player->health = startHealth(player);
    player->actorHealth = startHealth(player);
    player->playerId = 0xFF;
}

/** Allocate and clear the player array and its per-player state blocks, linking each player to its block. */

void Player_AllocPlayerList(PlayerList *list, int count) {
    int playerSize = count * sizeof(SharedPlayer);
    int stateSize = count * sizeof(Brain);
    char *states;
    void **handle;
    int i;

    handle = Cache_AllocateResource(0, playerSize + stateSize, 35, s_playersText);
    list->handle = handle;
    list->count = count;
    list->players = *handle;
    states = (char *)list->players + playerSize;
    XPlus_FillMemory(list->players, 0, playerSize);
    XPlus_FillMemory(states, 0, stateSize);
    for (i = 0; i < count; i++) {
        list->players[i].views1454.view1454_0.aiController = (struct AiController *)(states + i * sizeof(Brain));
    }
}

/* Updates every player in a world for one frame unless the game state g_gameplayRoundState is 8 or 11: turns
   the world's spin by 5 degrees, then for each player in the list runs its body
   through ContPad_BuildControllerState (restoring the frame time g_frameElapsedTime it may change), its team logic through
   Playerai_BuildEyeMarkerTransform when either team rule is set, its controls through Player_UpdateBodyMovementAndActions unless input is
   frozen by g_simpleObjectPauseState, and its camera through Player_UpdatePlayerCamera_PlayerBuildplayerviewtransform; a second pass opens the pause menu
   through Cinema_RequestSequenceFade for a paused player or one whose controller asks while a menu is
   possible, or otherwise starts the in-game menu for a live player with a view not already showing
   one (unless the match forbids it), before the match end check Playerai_UpdateRoundLimits and the world updates
   Player_UpdateFragTagSelection and Player_ReleaseWaitingPlayer run and the frame time is restored. */



void Player_UpdateWorldPlayers(struct WorldWeaponsUpdateWorldPlayers *world) {
    f32 frameTime;
    SharedPlayer *player;
    Rules *rules;

    if (g_gameplayRoundState.state != 11 && g_gameplayRoundState.state != 8) {
        frameTime = g_frameElapsedTime;
        world->spin += 5;
        if (world->spin >= 360) {
            world->spin = 0;
        }
        rules = &g_gameplayRoundState.rules;
        for (player = world->players; player != 0; player = player->views16E0.view16E0_2.next) {
            ContPad_BuildControllerState((struct ControllerInput *)player->views5E8.view688_33.body, (Player *)player);
            g_frameElapsedTime = frameTime;
            if (rules->teams != 0 || rules->teamRule != 0) {
                Playerai_BuildEyeMarkerTransform(player);
            }
            if (g_gameSession.clockPaused == 0) {
                Player_UpdateBodyMovementAndActions(player);
            }
            Player_UpdatePlayerCamera(player, player);
        }
        for (player = world->players; player != 0; player = player->views16E0.view16E0_2.next) {
            if (Cinema_IsSequenceActive() != 0 && (player->views5E8.view6B0_48.state & 0x8000)) {
                Cinema_RequestSequenceFade();
            } else if (Control_IsStartPressed(player->views5E8.view698_36.controller) != 0) {
                if (Cinema_IsSequenceActive() != 0 || Cinema_HasSequenceResource() != 0) {
                    Cinema_RequestSequenceFade();
                } else if (Tsmos_IsFrontendActive() == 0 && Menu_CountLiveNodes(&g_matchEndingTeamWheelClose) == 0 && player->views5E4.view5E4_3.alive != 0
                           && player->views5DC.view5DC_2.view != 0 && player->views5DC.view5DC_2.view->shieldActive == 0
                           && ((&((MenuWeaponsUpdateWorldPlayers *)&g_matchEndingTeamWheelClose)->rules)->locked == 0 || ((MenuWeaponsUpdateWorldPlayers *)&g_matchEndingTeamWheelClose)->allowed == 0)) {
                    ((MenuWeaponsUpdateWorldPlayers *)&g_matchEndingTeamWheelClose)->open = 1;
                    SoundElement_EnableMusicGainOverride();
                    SoundElement_DisablePeriodicSound();
                    TeamSelect_EmptyWeaponWheelHook();
                    player->views5E8.viewF54_132.selection = -1;
                    player->views5E8.viewF90_134.choice = -1;
                    Frontend_OpenGameplayFrontend();
                }
            }
        }
        Playerai_UpdateRoundLimits(world);
        Player_UpdateFragTagSelection(world);
        Player_ReleaseWaitingPlayer(world);
        g_frameElapsedTime = frameTime;
    }
}


void Player_BuildPlayerOrientation(Player *player, CQuatern *output)
{
    CQuatern pitchRotation;
    CQuatern yawRotation;
    CQuatern rollRotation;
    CQuatern orientation;
    CQuatern pitchYaw;
    CQuatern oriented;
    f32 pitch, yaw, roll, scale, heading;
    f32 rollAngle, pitchAngle, yawAngle;
    pitch = player->pitchOffset + player->sway[0] - player->pitchBias;
    yaw = player->kickYaw + player->sway[1];
    roll = player->lean + player->sway[2];
    heading = player->heading;
    scale = 0.5f;
    rollAngle = roll * scale;
    orientation = player->orientation;
    g_turretAimSine = Gu_Sinf(rollAngle);
    rollRotation.x = 0.0f;
    rollRotation.y = 0.0f;
    rollRotation.z = g_turretAimSine;
    rollRotation.w = Math_Cosf(rollAngle);
    pitchAngle = pitch * scale;
    g_turretAimSine = Gu_Sinf(pitchAngle);
    pitchRotation.x = g_turretAimSine;
    pitchRotation.y = 0.0f;
    pitchRotation.z = 0.0f;
    pitchRotation.w = Math_Cosf(pitchAngle);
    yawAngle = (heading + yaw) * scale;
    g_turretAimSine = Gu_Sinf(yawAngle);
    yawRotation.x = 0.0f;
    yawRotation.y = g_turretAimSine;
    yawRotation.z = 0.0f;
    yawRotation.w = Math_Cosf(yawAngle);
    MultiplyQuaternions(&pitchYaw, &pitchRotation, &yawRotation);
    MultiplyQuaternions(&oriented, &pitchYaw, &orientation);
    MultiplyQuaternions(output, &rollRotation, &oriented);
}


/* Builds a player view matrix: the eye height (base height plus camera offset less the crouch depth,
   at least 40.96) and the view pitch, yaw and roll (each with its kick and sway, the pitch less the
   head bob) become one half-angle quaternion per axis, combined roll * (pitch * yaw), then the
   matrix is rotation * eye-height lift * body orientation * translation to the player position plus
   its side and forward weapon offsets. */
void Player_BuildPlayerViewTransform(Player *player, f32 out[4][4])
{
    CQuatern pitchRotation;
    CQuatern yawRotation;
    CQuatern rollRotation;
    CQuatern orientation;
    CQuatern pitchYaw;
    CQuatern rotation;
    f32 viewRotation[4][4];
    f32 lift[4][4];
    f32 bodyRotation[4][4];
    f32 placement[4][4];
    f32 lifted[4][4];
    f32 oriented[4][4];
    f32 eyeHeight, height, pitch, yaw, roll, x, y, z, scale, heading;
    f32 rollAngle, pitchAngle, yawAngle;
    eyeHeight = player->baseHeight + player->cameraOffset - player->crouchDepth;
    pitch = player->pitchOffset + player->sway[0] - player->pitchBias;
    yaw = player->kickYaw + player->sway[1];
    roll = player->lean + player->sway[2];
    x = player->pos.x + player->sideOffset;
    z = player->pos.z + player->forwardOffset;
    heading = player->heading;
    y = player->pos.y;
    height = (eyeHeight < 40.96f) ? 40.96f : eyeHeight;
    scale = 0.5f;
    rollAngle = roll * scale;
    orientation = player->orientation;
    g_turretAimSine = Gu_Sinf(rollAngle);
    rollRotation.x = 0.0f;
    rollRotation.y = 0.0f;
    rollRotation.z = g_turretAimSine;
    rollRotation.w = Math_Cosf(rollAngle);
    pitchAngle = pitch * scale;
    g_turretAimSine = Gu_Sinf(pitchAngle);
    pitchRotation.x = g_turretAimSine;
    pitchRotation.y = 0.0f;
    pitchRotation.z = 0.0f;
    pitchRotation.w = Math_Cosf(pitchAngle);
    yawAngle = (heading + yaw) * scale;
    g_turretAimSine = Gu_Sinf(yawAngle);
    yawRotation.x = 0.0f;
    yawRotation.y = g_turretAimSine;
    yawRotation.z = 0.0f;
    yawRotation.w = Math_Cosf(yawAngle);
    MultiplyQuaternions(&pitchYaw, &pitchRotation, &yawRotation);
    MultiplyQuaternions(&rotation, &rollRotation, &pitchYaw);
    MatrixFromQuaternion(&rotation, viewRotation);
    Graphu64_BuildTranslationMatrix(lift, 0.0f, height, 0.0f);
    MatrixFromQuaternion(&orientation, bodyRotation);
    Graphu64_MultiplyAffineMatrices(lifted, viewRotation, lift);
    Graphu64_MultiplyAffineMatrices(oriented, lifted, bodyRotation);
    Graphu64_BuildTranslationMatrix(placement, x, y, z);
    Graphu64_MultiplyAffineMatrices(out, oriented, placement);
}

/* g_matchRoundCounters is g_gameSettings.counters in every region. */



void Playerai_ApplyStun(SharedPlayer *player, f32 amount) {
    f32 stun;

    if (amount != 0.0f && !(75.0f <= player->views5E8.view11D8_149.stun) && !(player->views5E8.view670_31.shield > 0.0f)
        && !(g_matchRoundCounters.enabled != 0
#if defined(VERSION_DE) || defined(VERSION_EU_X)
            && player->views5D8.view5D8_2.controls->team != 0
#endif
            && player->views5D8.view5D8_2.controls->mode == 11 && g_matchRoundCounters.m_nBastilleShield > 0)
        && !(player->views122C.view122C_2.options & 0x8000)) {
        stun = player->views5E8.view11D8_149.stun + amount * 15.0f;
        if (75.0f < stun) {
            stun = 75.0f;
        }
        player->views5E8.view11D8_149.stun = stun;
        Actor_RequestActorState(player->views1C.view2E8_28.weapon, player->views1C.view458_30.ammo, 2);
        if (player->views5E8.view1210_153.marker != 0) {
            if (player->views5E4.view5E4_4.holding != 0) {
                Player_SetPlayerState(player, player, 2);
            }
            player->views5E8.view1210_153.marker = 0;
            player->views5E8.view1214_156.markerShown = 0;
        }
        player->views1C.view100_9.flags &= ~0x01000000;
        if (player->views5DC.view5DC_2.view != 0) {
            if (((PlayerFlashView *)player->views5DC.view5DC_2.view)->flash == 0) {
                Gsky_StartFade((PlayerFlashView *)player->views5DC.view5DC_2.view, 128, 0, 0, 250, (u8) (u32) Graphu64_RandomFloat(7.5f), 0,
                              (u8) (u32) ((player->views5E8.view11D8_149.stun * 0.06666667f - 1.5f) * 15.0f));
            } else {
                ((PlayerFlashView *)player->views5DC.view5DC_2.view)->flash = 3;
                ((PlayerFlashView *)player->views5DC.view5DC_2.view)->level = (u32) player->views5E8.view11D8_149.stun;
            }
        }
    }
}

/* Draws the marker over a player that is alive: loads the player's matrix from its table at
   0x1640 (the first entry while Tsmos_IsFrontendActive reports a shared view, otherwise the entry for the current
   view g_lightingBufferIndex), sets the render and geometry modes, fills the five vertices of a green pyramid in
   g_playerAimMarkerVertices and emits them with its four triangles. Adapted from Player_DrawRedMarkerPrism with the pyramid, the
   colour and the matrix selection changed. */




/* Scales damage by ownership and player state and suppresses friendly damage when configured. */




/* Returns the leading team: for each player in the list it adds the player's kills of the
   seven other players (the shorts of its stats) to the total of its team byte at
   0x92, returning 0 at once for a player without a team (0xFF), then returns the first team 0 to 4
   with the highest total. */
s32 Playerai_FindHighestScoringPlayerIndex(struct CPlayerPool_t *game) {
    s32 total0;
    s32 total1;
    s32 total2;
    s32 total3;
    s32 total4;
    char *player;
    char *stats;
    s32 self;
    s32 other;
    s32 best;
    s32 leader;

    total4 = 0;
    total3 = 0;
    total2 = 0;
    total1 = 0;
    total0 = 0;
    for (player = game->m_ActiveList.head; player != 0; player = (char *)((struct Player *)(player))->next) {
        self = (u32) (player - game->m_Players) / 5864;
        for (other = 0; other < 8; other++) {
            if (other == self) {
                continue;
            }
            stats = (char *)((struct Player *)(player))->profile;
            switch (((struct Record *)(stats))->team) {
            case 0xFF:
                return 0;
            case 0:
                total0 += ((Stats *) stats)->kills[other];
                break;
            case 1:
                total1 += ((Stats *) stats)->kills[other];
                break;
            case 2:
                total2 += ((Stats *) stats)->kills[other];
                break;
            case 3:
                total3 += ((Stats *) stats)->kills[other];
                break;
            case 4:
                total4 += ((Stats *) stats)->kills[other];
                break;
            }
        }
    }
    do {
        best = leader = -1;
    } while (0);
    if (best < total0) {
        best = total0;
        leader = 0;
    }
    if (best < total1) {
        best = total1;
        leader = 1;
    }
    if (best < total2) {
        best = total2;
        leader = 2;
    }
    if (best < total3) {
        best = total3;
        leader = 3;
    }
    if (best < total4) {
        best = total4;
        leader = 4;
    }
    return leader;
}

/** Return the animation-table offset selected by the actor state. */
s32 Playerai_SelectCharacterSound(struct Player *player, s32 baseSoundId) {
    s32 *types = &g_fragTagModelId;
    u16 type = player->objectId;
    char *state;
    s32 offset;

    if (type == types[0]) {
        switch (g_gameSettings.counters.m_nFragTagSkin) {
        case 0:
            offset = 1300;
            break;
        case 1:
            offset = 1500;
            break;
        case 2:
            offset = 1400;
            break;
        default:
            g_gameSettings.counters.m_nFragTagSkin = 0;
            offset = 1300;
            break;
        }
    } else if (type == types[-2]) {
        offset = 400;
    } else if (type == types[-1]) {
        offset = 1000;
    } else {
        state = (char *)player->profile;
        switch (((struct AiProfile *)(state))->character) {
        default:
            ((struct AiProfile *)(state))->character = 0;
        case 0:
            offset = 0;
            break;
        case 1:
            offset = 1100;
            break;
        case 2:
            offset = 200;
            break;
        case 3:
            offset = 300;
            break;
        case 4:
            offset = 1200;
            break;
        case 5:
            offset = 100;
            break;
        case 6:
            offset = 600;
            break;
        case 7:
            offset = 900;
            break;
        case 8:
            offset = 800;
            break;
        case 9:
        case 15:
            offset = 700;
            break;
        case 10:
            offset = 500;
            break;
        case 11:
            offset = 1600;
            break;
        case 12:
            offset = 1700;
            break;
        case 13:
        case 16:
            offset = 1800;
            break;
        case 14:
            offset = 1900;
            break;
        }
    }
    return baseSoundId + offset;
}

void Playerai_DrawAimMarker(Player16C0 *player) {
    s32 green;
    s32 alpha;

    if (player->alive != 0) {
        if (Tsmos_IsFrontendActive() != 0) {
            gSPMatrix(g_displayListCursor++, (uintptr_t) &player->markers[0], G_MTX_LOAD);
        } else {
            gSPMatrix(g_displayListCursor++, (uintptr_t) &player->markers[g_lightingBufferIndex], G_MTX_LOAD);
        }
        gDPPipeSync(g_displayListCursor++);
        Geometry_InvalidateMaterialKeys();
        Geometry_SetModePreset(14);
        Geometry_SetCombineMode(28);
        green = 200;
        alpha = 150;
        gSPGeometryMode(g_displayListCursor++, G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | 0x80, 0);
        gSPGeometryMode(g_displayListCursor++, 0, G_SHADE | G_SHADING_SMOOTH);
        g_playerAimMarkerVertices[0].x = 0;
        g_playerAimMarkerVertices[0].y = 0;
        g_playerAimMarkerVertices[0].z = 0;
        g_playerAimMarkerVertices[0].flag = 0;
        g_playerAimMarkerVertices[0].s = 0;
        g_playerAimMarkerVertices[0].t = 0;
        g_playerAimMarkerVertices[0].r = 0;
        g_playerAimMarkerVertices[0].g = green;
        g_playerAimMarkerVertices[0].b = 0;
        g_playerAimMarkerVertices[0].a = alpha;
        g_playerAimMarkerVertices[1].x = 20;
        g_playerAimMarkerVertices[1].y = 40;
        g_playerAimMarkerVertices[1].z = 20;
        g_playerAimMarkerVertices[1].flag = 0;
        g_playerAimMarkerVertices[1].s = 0;
        g_playerAimMarkerVertices[1].t = 0;
        g_playerAimMarkerVertices[1].r = 0;
        g_playerAimMarkerVertices[1].g = green;
        g_playerAimMarkerVertices[1].b = 0;
        g_playerAimMarkerVertices[1].a = alpha;
        g_playerAimMarkerVertices[2].x = -20;
        g_playerAimMarkerVertices[2].y = 40;
        g_playerAimMarkerVertices[2].z = 20;
        g_playerAimMarkerVertices[2].flag = 0;
        g_playerAimMarkerVertices[2].s = 0;
        g_playerAimMarkerVertices[2].t = 0;
        g_playerAimMarkerVertices[2].r = 0;
        g_playerAimMarkerVertices[2].g = green;
        g_playerAimMarkerVertices[2].b = 0;
        g_playerAimMarkerVertices[2].a = alpha;
        g_playerAimMarkerVertices[3].x = -20;
        g_playerAimMarkerVertices[3].y = 40;
        g_playerAimMarkerVertices[3].z = -20;
        g_playerAimMarkerVertices[3].flag = 0;
        g_playerAimMarkerVertices[3].s = 0;
        g_playerAimMarkerVertices[3].t = 0;
        g_playerAimMarkerVertices[3].r = 0;
        g_playerAimMarkerVertices[3].g = green;
        g_playerAimMarkerVertices[3].b = 0;
        g_playerAimMarkerVertices[3].a = alpha;
        g_playerAimMarkerVertices[4].x = 20;
        g_playerAimMarkerVertices[4].y = 40;
        g_playerAimMarkerVertices[4].z = -20;
        g_playerAimMarkerVertices[4].flag = 0;
        g_playerAimMarkerVertices[4].s = 0;
        g_playerAimMarkerVertices[4].t = 0;
        g_playerAimMarkerVertices[4].r = 0;
        g_playerAimMarkerVertices[4].g = green;
        g_playerAimMarkerVertices[4].b = 0;
        g_playerAimMarkerVertices[4].a = alpha;
        gSPVertex(g_displayListCursor++, (u32) g_playerAimMarkerVertices, 5, 0);
        gSP1Triangle(g_displayListCursor++, 0, 1, 2, 0);
        gSP1Triangle(g_displayListCursor++, 0, 1, 4, 0);
        gSP1Triangle(g_displayListCursor++, 0, 2, 3, 0);
        gSP1Triangle(g_displayListCursor++, 0, 3, 4, 0);
    }
}

void Playerai_CreditDamageSource(TransientDamagePlayerView *damagedPlayer, TransientPlayerDamagePacket *damagePacket) {
    f32 damageScale;
    f32 scaledDamage;
    u8 sourceKind;
    u8 difficulty;
    TransientDamagePlayerView *damageSource;
    TransientDamagePlayerView *projectileOwner;
    TransientDamagePlayerView *creditedPlayer;

    damageSource = damagePacket->source;
    creditedPlayer = 0;
    if (damageSource != 0) {
        sourceKind = damageSource->actorKind;
        if (sourceKind != 1) {
            if (sourceKind == 2) {
                projectileOwner = damageSource->projectileOwner;
                if ((projectileOwner != 0) && (projectileOwner->actorKind == 1)) {
                    if (projectileOwner->flags & 0x300000) {
                        creditedPlayer = projectileOwner;
                        if (creditedPlayer == damagedPlayer) {
                            damagePacket->amount =
                                (s32) ((f32) damagePacket->amount * g_playerDamageFixedPointScale * g_playerDamageBaseScale * g_playerDamageDifficultyScale);
                        }
                    } else if (projectileOwner->objectId == 1036) {
                        creditedPlayer = projectileOwner->player;
                    }
                }
            }
        } else if (damageSource->flags & 0x300000) {
            creditedPlayer = damageSource->player;
        }
    } else {
        creditedPlayer = damagedPlayer;
    }
    if (creditedPlayer != 0) {
        if (creditedPlayer->computerControlled != 0) {
            difficulty = creditedPlayer->profile->difficulty;
            switch (difficulty) { /* irregular */
            case 2:
                break;
            default:
                creditedPlayer->profile->difficulty = 0U;
                /* fallthrough */
            case 0:
                scaledDamage = (f32) damagePacket->amount * g_playerDamagePrimaryFixedPointScale;
                scaledDamage *= g_playerDamagePrimaryModeScale;
                damagePacket->amount = (s32) (scaledDamage * g_playerDamageAndDistanceConstants);
                break;
            case 1:
                scaledDamage = (f32) damagePacket->amount * g_playerDamageSecondaryFixedPointScale;
                scaledDamage *= g_playerDamageSecondaryModeScale;
                damagePacket->amount = (s32) (scaledDamage * g_playerDamageAndDistanceConstants);
                break;
            }
        }
        { CGameStatus *state = (&g_gameSettings.counters);
        if ((state->teams != 0)
                && (g_gameSettings.multiplayerRuleBytes[0] == 0)
                && ((creditedPlayer->computerControlled == 0) || (damagedPlayer->computerControlled == 0))
                && (damagedPlayer->profile->reservedByte == creditedPlayer->profile->reservedByte)) {
            damagePacket->amount = 0;
        }}
    }
}

void Playerai_RotatePlayerPoseBuffers(struct CPlayerPool_t *playerPool) {
    void *node;

    if (*(void **)playerPool != 0) {
        Cache_MarkResourceInUse(0, *(void **)playerPool);
    }

    node = playerPool->m_ActiveList.head;
    if (node != 0) {
        do {
            Gobjinst_RotatePoseMatrixBuffers(node);
            Gobjinst_RotatePoseMatrixBuffers(&((struct Player *)(node))->actorParts[1]);
            Playerai_DrawCachedModelAndShadow(node, 0);
            if (g_gameSettings.local != 0) {
                Gobjinst_BuildAnimatedPose(node, 1);
            }
            node = ((struct Player *)(node))->next;
        } while (node != 0);
    }
}

void Playerai_UpdatePlayerRenderResources(struct CPlayerPool_t *playerPool, void *world) {
    void *node;
    int scale;
    s32 count1;
    s32 count2;
    char *entry;

    node = playerPool->m_ActiveList.head;
    if (node != 0) {
        do {
            ((TransientPlayerResetView *)(node))->floorClearance = 0;
            ((TransientPlayerResetView *)(node))->scanClearedWord = 0;
            if (InstHdr_CanActorReceiveInteraction(node) != 0) {
                if (node) {
                    count1 = ((TransientPlayerWorldCounts *)(world))->itemCount1;
                } else {
                    count1 = ((TransientPlayerWorldCounts *)(world))->itemCount1;
                }
                if (count1 != 512) {
                    scale = 4;
                    ((TransientWorldPlayerSlotView *)(((s32)world + count1 * scale)))->itemSlots = node;
                    ((TransientPlayerWorldCounts *)(world))->itemCount1 = count1 + 1;
                }
                count1 = 2888;
                count2 = ((IntegerStateB4C *)world)->itemCount2;
                if (count2 != 128) {
                    ((struct TransientWorldItemSlotView *) (entry = (char *) (((s32) world) + (count2 * 4))))->secondItemSlots = node;
                    ((IntegerStateB4C *)world)->itemCount2 = count2 + 1;
                }
            }
            node = ((TransientPlayerResetView *)(node))->nextPlayer;
        } while (node != 0);
    }
}

void Playerai_DrawPlayersForView(void *world, void *view) {
    Shared_MenuData *object;
    PlayerViewModeView *argument;
    PlayerViewListNode *cur;

    Geometry_BeginModelBatch();
    object = world;
    cur = object->transientPlayers;
    if (cur != 0) {
        do {
            argument = view;
            if (cur->view != view ||
                argument->viewMode == 1 ||
                Cinema_IsSequenceFlagTwoSet() != 0) {
                Player_DrawPlayerModel(cur, view);
            }
            cur = cur->next;
        } while (cur != 0);
    }
    Geometry_FlushModelBatch();
}

/* Removes entity from list if owned by specific owner, with version-specific check. */
void Playerai_DrawViewPlayer(void *world, void *view) {
    Shared_MenuData *object;
    PlayerViewModeView *argument;
    PlayerViewRenderListNode *viewPlayer;

#if defined(VERSION_US_REV1)
    if (g_playerViewRenderingEnabled != 0) {
        object = world;
        object = world;
    viewPlayer = object->transientPlayers;
        if (viewPlayer != 0) {
            do {
                argument = view;
                if (viewPlayer->view == view &&
                    argument->viewMode == 0 &&
                    viewPlayer->modelKind != g_fragTagModelId) {
                    Player_DrawHeldWeapon(viewPlayer, view);
                }
                viewPlayer = viewPlayer->next;
            } while (viewPlayer != 0);
        }
    }
#else
    object = world;
    viewPlayer = object->transientPlayers;
    if (viewPlayer != 0) {
        do {
            argument = view;
            if (viewPlayer->view == view &&
                argument->viewMode == 0 &&
                viewPlayer->modelKind != g_fragTagModelId) {
                Player_DrawHeldWeapon(viewPlayer, view);
            }
            viewPlayer = viewPlayer->next;
        } while (viewPlayer != 0);
    }
#endif
}

/* Notifies the entity list associated with roundContext about entity and calls a handler for each owner. */
void Playerai_UpdateViewPlayerProjection(void *roundContext, void *entity) {
    Round *round = roundContext;
    Player *viewPlayer;

#if defined(VERSION_US_REV1)
    if (g_playerViewRenderingEnabled != 0) {
#endif
        Gsky_LoadProjectionMatrix(entity);
        viewPlayer = round->players;
        if (viewPlayer != 0) {
            do {
                if (viewPlayer->camera == entity) {
                    Player_DrawHeadsUpDisplay(viewPlayer, entity);
                }
                viewPlayer = viewPlayer->next;
            } while (viewPlayer != 0);
        }
#if defined(VERSION_US_REV1)
    }
#endif
}

void Playerai_DrawViewMatchCountdown(void *roundContext, void *viewState) { Player_DrawMatchCountdown(roundContext, viewState); }

int Playerai_GetFirstPlayer(void *world) {
    Context *context = world;
    return (int)context->head;
}

void *Playerai_FindTransientPlayer(struct Context *context) {
    CGameStatus *base = (&g_gameSettings.counters);
    Player *record;

    if (base->m_bFragTagOn != 0 && base->m_FragTagFlipTimer != 0) {
        return 0;
    }
    record = (void *)context->head;
    if (record != 0) {
        do {
            if (record->profile->bonus == 1) {
                return record;
            }
            record = record->next;
        } while (record != 0);
    }
    return 0;
}

/** Start the round-end sequence once no menu or transition is active and any player is flagged. */




/** Return the capacity for an item slot: the player's own value, or in mode 1 the base value plus the character's bonus. */


void *Playerai_FindNearestPlayer(void *world, CVector3 point) {
    f32 nearestDistanceSquared;
    PlayerPositionListNode *candidatePlayer;
    void *result;
    f32 dx, dy, dz, distSq;

    Shared_MenuData *object;

    nearestDistanceSquared = (&g_playerDamageAndDistanceConstants)[1];
    object = world;
    candidatePlayer = object->transientPlayers;
    result = 0;
    if (candidatePlayer != 0) {
        do {
            dx = candidatePlayer->positionX - point.x;
            dx = dx * dx;
            dy = candidatePlayer->positionY - point.y;
            dy = dy * dy;
            dz = candidatePlayer->positionZ - point.z;
            dz = dz * dz;
            distSq = (dx + dy) + dz;
            if (distSq < nearestDistanceSquared) {
                nearestDistanceSquared = distSq;
                result = candidatePlayer;
            }
            candidatePlayer = candidatePlayer->next;
        } while (candidatePlayer != 0);
    }
    return result;
}

void *Playerai_FindNearestLivePlayer(struct Context *context, CVector3 position, void *excludedPlayer) {
    f32 nearestDistanceSquared;
    Player *actor;
    void *nearestPlayer;
    f32 dx, dy, dz, distSq;

    nearestDistanceSquared = g_playerNearestLiveDistanceLimit;
    actor = (void *)context->head;
    nearestPlayer = 0;
    if (actor != 0) {
        do {
            if (actor->health != 0 && actor != excludedPlayer) {
                dx = ((LevelActor *)actor)->position0.x - position.x;
                dx = dx * dx;
                dy = ((LevelActor *)actor)->position0.y - position.y;
                dy = dy * dy;
                dz = ((LevelActor *)actor)->position0.z - position.z;
                dz = dz * dz;
                distSq = (dx + dy) + dz;
                if (distSq < nearestDistanceSquared) {
                    nearestDistanceSquared = distSq;
                    nearestPlayer = actor;
                }
            }
            actor = actor->next;
        } while (actor != 0);
    }
    return nearestPlayer;
}

s32 Player_GetPlayerIndex(void *world, unsigned int playerAddress)
{
    ResourceKeyView *playerArrayRecord = world;
  return (playerAddress - (playerArrayRecord->key)) / 5864;
}

void *Playerai_FindPlayerByController(char *object, s32 controllerAddress) {
    Round *round = (Round *)object;
    Player *record = (Player *)round->players;
    if (record != 0) {
        do {
            if ((s32)record->weaponAnimation == controllerAddress) {
                return record;
            }
            record = record->next;
        } while (record != 0);
    }
    return 0;
}

void *Playerai_GetPlayerByIndex(void *world, u32 playerIndex) {
    Player *actor;
    s32 currentPlayerIndex;

    actor = 0;
    currentPlayerIndex = 0;
    if (playerIndex < 8U) {
        actor = ((struct Context *)world)->head;
        if (actor != 0) {
            do {
                if (currentPlayerIndex == (s32)playerIndex) {
                    return actor;
                }
                actor = actor->next;
                currentPlayerIndex += 1;
            } while (actor != 0);
        }
    }
    return actor;
}

void *Playerai_GetPlayerByViewIndex(struct Context *context, u32 viewPlayerIndex) {
    void *result;
    void *playerView;
    s32 currentViewIndex;

    result = 0;
    currentViewIndex = 0;
    if (viewPlayerIndex < 8U) {
        result = context->head;
        if (result != 0) {
            do {
                playerView = ((Player *)result)->camera;
                if (playerView != 0 && ((GameplayCamera *)playerView)->messageList.flag == 0) {
                    if (currentViewIndex == (s32) viewPlayerIndex) {
                        return result;
                    }
                    currentViewIndex += 1;
                }
                result = ((Player *)result)->next;
            } while (result != 0);
        }
    }
    return result;
}

int Playerai_BeginRoundEnd(char *forcePlayerList) {
    Player *p;
    int count;
    CGameStatus *roundCounters;
    CGameStatus *t;

    if (Cinema_IsSequenceInWindow() != 0 || Cinema_IsSequenceActive() != 0 || g_world.frozen != 0) {
        return 0;
    }
    t = &g_gameSettings.counters;
    if (t->state != 0 || t->elapsed == 0) {
        return 0;
    }
    count = 0;
    for (p = (Player *)((ForcePlayerList *)forcePlayerList)->head; p != 0; p = p->next) {
        if (p->profile->roundFlags[1] == 1) {
            count++;
        }
    }
    if (count <= 0) {
        return 0;
    }
    roundCounters = &g_gameSettings.counters;
    roundCounters->state = 1;
    roundCounters->elapsed = 0;
    return 1;
}

void Playerai_EndRound(void *roundContext) {
    CGameStatus *state;
    Round *round = roundContext;
    Node_Weapons_EndRound *node;

    state = &g_gameSettings.counters;
    if ((state->elapsed != 0) || (state->state != 0)) {
        return;
    }

    Control_SetControllerMode(0);
    if (state->teams != 0) {
        if (state->round == 0) {
            state->round = 1;
            node = (Node_Weapons_EndRound *)round->players;
            while (node != 0) {
                Player_SetPlayerState(node, node, 21);
                node = node->next;
            }
        }
    } else {
        state->elapsed = 1;
        node = (Node_Weapons_EndRound *)round->players;
        while (node != 0) {
            Player_SetPlayerState(node, node, 21);
            node = node->next;
        }
    }

    g_playerRoundEndSignal.value = 1;
    node = (Node_Weapons_EndRound *)round->players;
    while (node != 0) {
        node->roundEndTimer = 0;
        ((AiProfile *)node->state)->roundFlags[1] = 1;
        node = node->next;
    }
}

/** Find the first linked record whose nested flags include either type marker. */
void *Playerai_FindPlayerWithMarker(char *object) {
    Player *record = (void *)((struct Context *)object)->head;
    while (record != 0) {
        AiProfile *nested = record->profile;
        if (nested->bonus == 1 ||
            (u8)nested->state90 == 1) {
            return record;
        }
        record = record->next;
    }
    return record;
}

void Playerai_ResetPlayerControllers(struct Context *object) {
    Player *record = (void *)object->head;
    if (record != 0) {
        do {
            Rumble_FreeAllPoolNodes(&((ControllerProfile *)record->weaponAnimation)->effectPool);
            ((struct IntegerStateD4 *)record->weaponAnimation)->clearedWord = 0;
            record = record->next;
        } while (record != 0);
    }
}

void Playerai_SetAllPlayerTimeScales(char *object, f32 timeScale) {
    Shared_MenuData *object_record = (void *)object;
    PlayerTimeScaleListNode *record = object_record->transientPlayers;
    if (record != 0) {
        do {
            record->timeScale = timeScale;
            record = record->next;
        } while (record != 0);
    }
}

s32 Playerai_CountLocalActivePlayers(struct Context *context) {
    Player *record = (void *)context->head;
    s32 count = 0;
    if (record != 0) {
        do {
            if (record->ammo[5] != 0 && record->computer == 0) {
                count += 1;
            }
            record = record->next;
        } while (record != 0);
    }
    return count;
}

void Playerai_SetTrackedRecordValue(TrackedRecordValueView *record, int newValue) {
    if (record->value == newValue) {
        record->repeatedValue = 1;
    }
    record->value = newValue;
}

void Playerai_StopActiveEffect(Shared_Effect *effect) {
    s32 effectState = effect->state;
    if (effectState != 0 && effectState != 3) {
        effect->state = 3;
    }
}

void Playerai_UpdateHeldWeaponPose(void *player) {
    LevelActor *base;
    s32 old_value;
    s32 new_value;
    f32 saved_value;

    base = &((Player *)player)->actorParts[1];
    old_value = ((Player *)player)->animation;
    saved_value = g_frameElapsedTime;
    base->renderFlags = 0x10;
    base->flags &= 0xFFFDFFFF;
    Gobjinst_UpdateActorController(base);
    if (((Player *)player)->cooldown <= 0.0f) {
        Gobjinst_UpdateActorRootDisplacement(base);
    }
    new_value = ((Player *)player)->animation;
    g_frameElapsedTime = saved_value;
    if (old_value != new_value) {
        ((LevelActor *)player)->animationPending = 0;
    }
    ((Player *)player)->actorParts[1].position0 = ((LevelActor *)player)->position0;
    ((Player *)player)->actorParts[1].yaw = ((LevelActor *)player)->yaw;
    ((Player *)player)->actorParts[1].model = ((LevelActor *)player)->model;
    ((Player *)player)->actorParts[1].rotation = ((LevelActor *)player)->rotation;
}

f32 Playerai_GetSequenceFade(PlayerSequenceFadeView *rampState) {
    f32 value;
    f32 scaled;
    f32 initial;
    initial = rampState->value - 285.0f;
    if (rampState->override != 0) {
        value = 1.0f;
    } else {
        scaled = initial * 0.06666667f;
        if (scaled > 1.0f) {
            value = 1.0f;
        } else {
            value = scaled;
        }
    }
    return 1.0f - value;
}

s32 Playerai_GetWeaponFireMode(AimPlayer *aimPlayer, s32 weaponId) {
    void *weaponInfo = g_weaponInfoByType[weaponId];
    if (aimPlayer->weaponActionMode == 1) {
        return ((GlobalState *)weaponInfo)->primaryFireMode;
    }
    return ((GlobalState *)weaponInfo)->alternateFireMode;
}

s16 Playerai_GetWeaponClassId(Player *player, s32 weaponId) {
    s16 *selectedClassEntry;
    WeaponInfo *weaponDefinition;

    weaponDefinition = g_weaponInfoByType[weaponId];
    if (player->gear == 1) {
        selectedClassEntry = weaponDefinition->weaponClass;
    } else {
        selectedClassEntry = weaponDefinition->alternateClass;
    }
    if (selectedClassEntry != 0) {
        return *selectedClassEntry;
    }
    return -1;
}

s16 Playerai_GetWeaponAmmo(void *actor, s32 weaponId) {
    s16 *selectedClassEntry;
    s32 ammoSlot;
    WeaponInfo *weapon;

    if ((weaponId == 1) && (((Player *)actor)->weaponSlots[1].owned != 0)) {
        return -1;
    }
    weapon = g_weaponInfoByType[weaponId];
    if (((Player *)actor)->gear == 1) {
        selectedClassEntry = weapon->weaponClass;
    } else {
        selectedClassEntry = weapon->alternateClass;
    }
    if (selectedClassEntry != 0) {
        ammoSlot = *selectedClassEntry;
    } else {
        ammoSlot = -1;
    }
    if (ammoSlot != -1) {
        return ((Player *)actor)->ammo[ammoSlot];
    }
    return -1;
}

s32 Playerai_GetSelectedAmmoIcon(void *player) {
    s16 *selectedClassEntry;
    s32 ammoClassId;
    WeaponInfo *weapon;

    weapon = g_weaponInfoByType[((Player *)player)->selectedAction];
    if (((Player *)player)->gear == 1) {
        selectedClassEntry = weapon->weaponClass;
    } else {
        selectedClassEntry = weapon->alternateClass;
    }
    if (selectedClassEntry != 0) {
        ammoClassId = *selectedClassEntry;
    } else {
        ammoClassId = -1;
    }
    if (ammoClassId != -1) {
        return g_ammoClassIconIds[ammoClassId];
    }
    return -1;
}

s32 Player_GetMaxHealth(void *player) {
    char *healthPlayer = (char *)player;
    s32 value;
    s8 type;

    if (g_gameSettings.counters.enabled != 0 && ((struct PlayerProfileStatusView *) ((PlayerHealthDefinitionView *) healthPlayer)->options)->display != 0) {
        type = ((struct PlayerProfileStatusView *) ((PlayerHealthDefinitionView *) healthPlayer)->options)->kind;
        if (type == 11) {
            value = 0x19000;
        } else if (type == 12) {
            value = 0x19000;
        } else if (type == 14) {
            value = 76800;
        } else if (type == 13) {
            value = 76800;
        } else {
            value = ((ActorHealthDefinition *)((PlayerHealthDefinitionView *)healthPlayer)->definition)->health << 8;
        }
    } else {
        value = ((ActorHealthDefinition *)((PlayerHealthDefinitionView *)healthPlayer)->definition)->health << 8;
    }
    if (g_gameSettings.controllerMode == 1 && ((PlayerHealthDefinitionView *)(healthPlayer))->computerControlled == 0) {
        value += g_characterHealthBonuses[((PlayerHealthDefinitionView *)(healthPlayer))->playerIndex].value;
    }
    return value;
}

int Player_GetAmmoCapacity(PlayerWeaponsGetAmmoCapacity *player, int slot) {
    int value;

    if (slot == -1) {
        return 0;
    }
    if (g_gameSettings.controllerMode != 1) {
        value = player->loadout->capacity[slot];
    } else {
        value = g_baseAmmoCapacities[slot];
        if (player->isBot == 0) {
            if (slot == 0) {
                value += g_localPlayerProfiles[player->character].bonus0;
            } else if (slot == 1) {
                value += g_localPlayerProfiles[player->character].bonus1;
            } else if (slot == 2) {
                value += g_localPlayerProfiles[player->character].bonus2;
            }
        }
    }
    return value;
}

/** Report whether the signed word is below 0x6400. */
int Playerai_IsHealthBelowThreshold(struct SharedPlayer *object, s32 choiceId) {
    return object->views5E4.view5E4_0.health < 25600;
}

f32 Playerai_GetObjectOwnerHeight(void *actorObject) {
    struct EffectOwnerObject *object = actorObject;
    struct ModelBlend *owner;

    owner = object->owner;
    if (owner != 0) {
        return owner->height * g_playerOwnerHeightScale;
    }
    return g_playerDefaultOwnerHeight;
}

f32 Playerai_GetDefinedActorHeight(LevelActor *actor) {
    if (actor->definition != 0) {
        return Gobjinst_GetActorHeight(actor);
    } else {
        return g_playerUndefinedActorHeight;
    }
}

int Playerai_SetPositionAndFloor(void *player, void *newPosition) {
    int flag;
    CVector3 *src;
    src = newPosition;
    flag = ((int (*)(void *))Scene_FindFloorPolygon)(&g_world);
    ((LevelActor *)player)->position0 = *src;
    ((LevelActor *)player)->model = flag;
    ((Player *)player)->actorParts[1].position0 = *src;
    ((Player *)player)->actorParts[1].model = flag;
    return flag != 0;
}

void Playerai_StartPrimaryAttachedSound(Player *actor, s32 soundId) {
    s32 viewAddress;
    void *soundPosition;

    viewAddress = (s32) actor->camera;
    if (viewAddress != 0) {
        soundPosition = (void *)((char *)&((GameplayCamera *)viewAddress)->position);
    } else {
        soundPosition = &actor->pos;
    }
    if (g_world.frozen == 0 && g_gameSession.clockPaused == 0) {
        SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), (void *)actor->firstHandle);
        actor->firstHandle = (void *)SoundVoicePool_PlaySpatialSound((void *)SoundVoicePool_GetGlobalState(), soundId, soundPosition, soundPosition, (s32)actor);
    }
}

void Playerai_StopPrimaryAttachedSound(void *player) {
    SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), (void *)(((struct PlayerLoopingSoundHandleView *) player)->primarySoundHandle));
    (((struct PlayerLoopingSoundHandleView *) player)->primarySoundHandle) = 0;
}

void Playerai_StartSecondaryAttachedSound(Player *actor, s32 soundId) {
    s32 viewAddress;
    void *soundPosition;

    if (g_world.frozen == 0 && g_gameSession.clockPaused == 0) {
        viewAddress = (s32) actor->camera;
        if (viewAddress != 0) {
            soundPosition = (void *)((char *)&((GameplayCamera *)viewAddress)->position);
        } else {
            soundPosition = &actor->pos;
        }
        SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), (void *)actor->secondHandle);
        actor->secondHandle = (void *)SoundVoicePool_PlaySpatialSound((void *)SoundVoicePool_GetGlobalState(), soundId, soundPosition, soundPosition, (s32)actor);
    }
}

void Playerai_StopSecondaryAttachedSound(void *player) {
    SoundVoicePool_StopNode(SoundVoicePool_GetGlobalState(), (void *)(((struct PlayerStartupSoundView *) player)->startupSoundNode));
    (((struct PlayerStartupSoundView *) player)->startupSoundNode) = 0;
}

void Playerai_StartTransitionState(void *player, s32 transitionParameter) {
    (((struct PlayerWeaponTransitionParameterView *) player)->transitionParameter) = transitionParameter;
    Player_SetPlayerState(player, player, 16);
}

void Player_SetPlayerResetPosition(void *actorObject, CVector3 *newResetPosition)
{
  Player *player = actorObject;
  void *positionRecord;
  player->resetPosition = *newResetPosition;
  positionRecord = actorObject;
  Player_SetPlayerState(positionRecord, positionRecord, 17);
}


void Player_TransformPointByViewOrOwnerMatrix(void *player, CVector3 *point) {
    CVector3 input;
    MatrixF matrix;
    CVector3 *input_ptr;
    MatrixF *matrix_ptr;

    PlayerForceMarkerOwnerView *object = player;
    PlayerForceMarkerMatrixView *owner;

    input = *point;
    input_ptr = &input;
    matrix_ptr = object->transformOwner;

    if (matrix_ptr != 0) {
        owner = (void *)matrix_ptr;
        matrix_ptr = &owner->viewMatrix;
    } else {
        Player_BuildPlayerViewTransform(player, &matrix);
        matrix_ptr = &matrix;
    }
    Graphu64_TransformPoint(matrix_ptr, input_ptr, point);
}

void Playerai_AddCappedEventCounter(void *player, s32 increment) {
    u16 wrappedSum;
    u16 cappedCounter;
    wrappedSum = (((struct PlayerForceMarkerCounterView *) player)->eventCounter) + increment;
    cappedCounter = wrappedSum;
    (((struct PlayerForceMarkerCounterView *) player)->eventCounter) = wrappedSum;
    if ((u32) (cappedCounter & 0xFFFF) >= 101U) {
        cappedCounter = 100;
    }
    (((struct PlayerForceMarkerCounterView *) player)->eventCounter) = cappedCounter;
}

void Player_GetPlayerViewTranslation(void *player, f32 *origin) {
    MatrixF viewTransform;
    Player_BuildPlayerViewTransform(player, &viewTransform);
    Graphu64_GetMatrixTranslation((char *)&viewTransform, origin);
}

/** Report whether the word is zero. */
int Playerai_IsPlayerInactive(struct SharedPlayer *player) {
    return player->views5E4.view5E4_0.health == 0;
}

/** Return the word0. */
int Playerai_IsAlternateFireHeld(struct SharedPlayer *object) {
    return object->views5E8.view1210_152.marker;
}

void Player_ReleasePlayerParticleEmitters(s32 actor) {
    Particle_ReleaseOwnerEmitters(&g_actorParticleEffectSystem[0], actor);
}

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))


/* Copy of Playerai_BuildForceMarkerTransform: orients the marker matrix along the aim normal, moves it to the marker origin
 * pushed 5.12 units off the surface and packs it into the player's marker transform. */
static inline void buildForceMarkerTransform(Player *player, s32 attract, CVector3 *normal) {
    Matrix matrix;
    CVector3 offset;
    BuildDirectionMatrix(&matrix, normal);
    Graphu64_ScaleVector(&offset, normal, 5.12f);
    Graphu64_AddVec3(&offset, &offset, &player->aimPosition);
    TranslateMatrix(&matrix, offset.x, offset.y, offset.z);
    SwapMatrixUpForward(&matrix);
    Graphu64_ConvertMatrixToFixed(&matrix, player->transform1600);
}
/* Toggles the player's attract/repulse marker while the aim ray hits something: a live marker is removed
 * ("ATTRACT REMOVED"); otherwise a new one is placed at the aim point for 150 frames, pulling when
 * attract is set ("ATTRACT MARKED") and pushing otherwise ("REPULSE MARKED"). */
void Playerai_ToggleForceMarker(Player *player, s32 attract) {
    void *screen;
    u8 *text;
    if (player->aimTarget != 0) {
        if (player->zoom > 0.0f) {
            player->zoom = 0;
            SoundElement_PlayFlatSound(1400);
            screen = player->camera;
            if (screen == 0) return;
            text = g_forceMarkerRemovedText;
        } else {
            player->aimPosition = player->aimPoint;
            player->zoomMode = attract;
            player->zoom = 150.0f;
            buildForceMarkerTransform(player, attract, &player->aimNormal);
            SoundElement_PlayFlatSound(1400);
            screen = player->camera;
            if (screen == 0) return;
            if (attract != 0) text = g_forceMarkerAttractText;
            else text = g_forceMarkerRepulseText;
        }
        Camera_PostScreenMessage((void *)&g_frontendScreenStatus, screen, text);
    }
}
#endif

void *Playerai_FindNearestForceMarker(ForcePlayerList *forcePlayerList, void *position) {
    CVector3 markerDelta;
    Player *node;
    void *bestNode;
    f32 bestDist;
    f32 distSq;

    node = (Player *)forcePlayerList->head;
    bestDist = 0.0f;
    bestNode = 0;
    if (node != 0) {
        do {
            if (node->actorState != 0 &&
                node->zoom != 0.0f) {
                Graphu64_SubtractVectors(&markerDelta, position, &node->aimPosition);
                distSq = markerDelta.x * markerDelta.x + markerDelta.y * markerDelta.y + markerDelta.z * markerDelta.z;
                if (bestNode == 0 || distSq < bestDist) {
                    bestNode = node;
                    bestDist = distSq;
                }
            }
            node = node->next;
        } while (node != 0);
    }
    return bestNode;
}

void Playerai_BuildForceMarkerTransform(char *actorView, s32 markerContext, CVector3 *direction) {
    Player *actor = (Player *)actorView;
    Matrix matrix;
    CVector3 offset;

    BuildDirectionMatrix(&matrix, direction);
    Graphu64_ScaleVector(&offset, direction, 5.12f);
    Graphu64_AddVec3(&offset, &offset, &actor->aimPosition);
    TranslateMatrix(&matrix, offset.x, offset.y, offset.z);
    SwapMatrixUpForward(&matrix);
    Graphu64_ConvertMatrixToFixed(&matrix, actor->transform1600);
}

/** Report whether the floating fieldC is positive. */
int Playerai_HasForceMarker(char *object) {
    Player *actor = (void *)object;
    return actor->zoom > 0.0f;
}

void Playerai_DrawForceMarker(char *player) {
    PlayerForceMarkerHandleView *object = player;
    s32 index;

    if (object->forceMarkerModelSelector != 0) {
        index = Scene_FindModelIdIndex(&g_world, 3204);
    } else {
        index = Scene_FindModelIdIndex(&g_world, 3205);
    }
    if (index != -1) {
        Geometry_QueueDirectModel(Scene_GetIndexedModelResource(&g_world, index),
                      (s32)((Player *)player)->transform1600, (intptr_t)&g_defaultParticleLighting, 0, -1);
    }
}

void Playerai_ClearDamageTimers(s32 player) {
    s32 effectIndex;
    void *effectBase;
    effectIndex = 4;
    effectBase = player + 96;
    do {
        (((struct PlayerForceMarkerStateView *) effectBase)->remainingTime) = 0;
        effectIndex -= 1;
        effectBase -= sizeof(Timer);
    } while (effectIndex >= 0);
}

void Playerai_ResetDamageTimers(s32 playerAddress) {
    s32 effectIndex;
    void *effectBase;
    effectIndex = 4;
    effectBase = playerAddress + 4 * sizeof(Timer);
    do {
        (((struct PlayerForceMarkerStateView *) effectBase)->remainingTime) = 0;
        effectIndex -= 1;
        effectBase -= sizeof(Timer);
    } while (effectIndex >= 0);
}

/* Starts a timer in the first of the object's five 24-byte slots whose remaining time is not
   positive: records the kind, target, a zero elapsed value and the tag, sets the duration to rate
   times g_playerDamageTimerDurationScale and the step to target over duration. */


void Playerai_StartDamageTimer(PlayerEffectTimerSet *obj, float target, float rate, int kind, int tag) {
    int i;

    for (i = 0; i < 5; i++) {
        Timer *t = &obj->timers[i];
        if (t->m_FramesRemaining <= 0.0f) {
            t->kind = kind;
            t->m_TotalDamage = target;
            t->m_DamageIssued = 0.0f;
            t->m_bIsInflator = tag;
            t->m_FramesRemaining = rate * g_playerDamageTimerDurationScale;
            do {
                t->m_DamagePerFrame = target / t->m_FramesRemaining;
                return;
            } while (0);
        }
    }
}

void Playerai_UpdateReactionReserve(void *player) {
    if ((((struct PlayerTintBlendStateView *) player)->health) != 0) {
        (((struct PlayerTintBlendStateView *) player)->reactionReserve) =
            Graphu64_ApproachValue((((struct PlayerTintBlendStateView *) player)->reactionReserve),
            g_playerReactionReserveTarget, g_playerReactionReserveApproachRate);
    }
}


void Playerai_AddReactionReserve(void *actorObject, f32 amount, void *source) {
    Shared_ReactionPlayer *actor = actorObject;
    Shared_ReactionInteraction packet;
    f32 value;
    f32 limited;
    value = actor->reserve + amount;
    limited = gReactionReserveMaximum;
    if (!(limited <= value)) {
        limited = value;
    }
    actor->reserve = limited;
    if (gReactionReserveMaximum <= limited) {
        Barrel_FillDamagePacket(&packet, (s32)source, 0x40000, 25.599998f, 128, 0);
        Playerai_ApplyDamagePacket((Shared_ReactionActor *)actor, &actor->damageState, &packet);
    }
}

/** Start the actor effect and attach optional source-specific resources; the European cartridges pick
    each resource from a per-language table. */

void Player_StartSourceEffect(void *actor, void *effectSource) {
    Player *state = actor;
    Player *source = effectSource;
    void *owner;
    void *payload;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    MenuMatchGlobals *game;
    MenuSettings *settings;
#endif

    if (state->pending != 0.0f) {
        return;
    }

    SoundElement_PlayFlatSound(2885);
    state->pending = g_playerSourceEffectDuration;
    state->effectSource = source;
    owner = state->camera;
    if (owner == 0) {
        return;
    }

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    game = &g_frontendScreenStatus;
    settings = &game->settings;
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Camera_PostScreenMessage((ScreenMessageOwner *)game, owner, g_playerSourceEffectStartMessage[settings->language]);
#else
    Camera_PostScreenMessage((ScreenMessageOwner *)&g_frontendScreenStatus, owner, g_playerSourceEffectStartMessage);
#endif
    if (source == 0) {
        return;
    }
    if (((LevelActor *)source)->kind != 1) {
        return;
    }
    if ((((LevelActor *)source)->flags & 0x300000) == 0) {
        return;
    }

    payload = state->effectPayload;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Libc_FormatString(payload, g_playerSourceEffectOwnerFormatEuropean[settings->language],
#else
    Libc_FormatString(payload, g_playerSourceEffectOwnerFormatEuropean,
#endif
#else
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Libc_FormatString(payload, g_playerSourceEffectOwnerFormat[settings->language],
#else
    Libc_FormatString(payload, g_playerSourceEffectOwnerFormat,
#endif
#endif
                  source->profile->name);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Camera_PostScreenMessage((ScreenMessageOwner *)game, state->camera, payload);
#else
    Camera_PostScreenMessage((ScreenMessageOwner *)&g_frontendScreenStatus, state->camera, payload);
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Camera_PostScreenMessage((ScreenMessageOwner *)game, state->camera, g_playerSourceEffectFinalMessageEuropean[settings->language]);
#else
    Camera_PostScreenMessage((ScreenMessageOwner *)&g_frontendScreenStatus, state->camera, g_playerSourceEffectFinalMessageEuropean);
#endif
#else
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    Camera_PostScreenMessage((ScreenMessageOwner *)game, state->camera, g_playerSourceEffectFinalMessage[settings->language]);
#else
    Camera_PostScreenMessage((ScreenMessageOwner *)&g_frontendScreenStatus, state->camera, g_playerSourceEffectFinalMessage);
#endif
#endif
}

#define g_gameSettingsView (*(s32 *)&g_gameSettings)



void Playerai_UpdateDelayedDamage(void *player) {
    Slot damage;
    f32 remainingDelay;
    f32 previousDelay;

    previousDelay = ((PlayerWeaponDelayStateView *)(player))->delayedDamageTimer;
    if (previousDelay > 0.0f) {
        remainingDelay = previousDelay - g_frameElapsedTime;
        ((PlayerWeaponDelayStateView *)(player))->delayedDamageTimer = remainingDelay;
        if ((remainingDelay <= 0.0f) && !(g_gameSettingsView & 1)) {
            Barrel_FillDamagePacket(&damage,
                          ((PlayerWeaponDelayStateView *)(player))->damageSource,
                          ((PlayerWeaponDelayStateView *)(player))->delayedDamage + 6400,
                          25.599998f, 0x4000, 0);
            Playerai_ApplyDamagePacket(player, &((PlayerWeaponDelayStateView *)(player))->damageState, &damage);
        }
    }
}

#undef g_gameSettingsView

/** Report whether the nested pointer's word is nonzero. */
int Playerai_HasActiveView(void *object) {
    Player *object_record = object;
    View *nested = object_record->camera;
    if (nested != 0) {
        return nested->shieldActive != 0;
    }
    return 0;
}

/** Report whether the global state word is nonzero. */
int Player_IsClockPaused(void) {
    return g_gameSession.clockPaused != 0;
}

void Playerai_LoadActorModel(void *actor) {
    s32 modelKind;
    void *result;

    modelKind = ((Player *)actor)->state;
    if (g_gameSettings.counters.m_bFragTagOn != 0 && ((Player *)actor)->profile->bonus == 1) {
        modelKind = 19;
    }
    result = Scene_FindActorDefinition(&g_world, 11, modelKind);
    if (result != 0) {
        ((Player *)actor)->definition = result;
    } else {
        result = Scene_FindActorDefinition(&g_world, 11, -1);
        if (result != 0) {
            ((Player *)actor)->definition = result;
        } else {
            result = Scene_FindActorDefinition(&g_world, -1, -1);
            ((Player *)actor)->definition = result;
        }
    }
    ((LevelActor *)actor)->scale.x = ((PlayerSequenceResourceView *)result)->scaleX;
    ((LevelActor *)actor)->scale.y = ((PlayerSequenceResourceView *)result)->scaleY;
    ((LevelActor *)actor)->scale.z = ((PlayerSequenceResourceView *)result)->scaleZ;
}

void Playerai_UpdateCharacterModel(void *actor) {
    s32 modelKind;
    Shared_Game *base;

    base = &g_gameSettings;
    if (base->local == 0) {
        modelKind = 102;
    } else if (base->fragTagEnabled != 0 && ((Player *)actor)->profile->bonus != 0) {
        modelKind = g_fragTagModelId;
    } else {
        modelKind = g_characterModelIds[((LevelActor *)actor)->definition->character];
        ((Player *)actor)->playerId = ((Player *)actor)->profile->variant;
    }
    ((void (*)(void *, void *, s32, s32))Scene_ChangeInstanceModel)(&g_world, actor, modelKind, ((Player *)actor)->animation);
}

void Playerai_UpdateHeldWeaponModel(Player *actor) {
    s32 modelOffset;

    if (actor->computer != 0) {
        if (g_gameSettings.counters.transitionActive == 0) {
            modelOffset = 23;
            goto after;
        }
    }
    modelOffset = (g_playerWeaponClassMode == 1) ? 0 : 23;
after:
    ((void (*)(void *, void *, s32, s32))Scene_ChangeInstanceModel)(&g_world, &actor->weaponModel,
        ((WeaponInfo *)g_weaponInfoByType[actor->selectedAction])->model + modelOffset,
        actor->weaponAnimationTable->defaultAnimation);
}

void Playerai_DrawCachedModelAndShadow(void *actorIn, s32 shadowMode) {
    CVector3 viewOffset;
    void *animationResource;
    Player *actor;
    GameplayCamera *message;
    ActorAnimationResourceView *object = actorIn;

    if (object->flags & 0x40000) {
        animationResource = Cache_RequestResource(0, object->resource, object->resource, object->resourceFlags, 4, 0, 0, g_playerModelResourceTag, 1);
        if (animationResource != 0) {
            actor = (Player *)object->owner;
            Gobjinst_UpdateModelBounds(actorIn, (s32)SetN64_GetPackSection(*(void **)animationResource, 0));
            if (shadowMode != 0) {
                message = actor->camera;
                if (message != 0) {
                    viewOffset.x = message->position.x - object->position.x;
                    viewOffset.y = 0.0f;
                    viewOffset.z = actor->camera->position.z - object->position.z;
                    GameObject_DrawBlobShadow(actorIn, &viewOffset, shadowMode);
                }
            }
            Cache_UnlockResource(0, animationResource);
        }
    }
}

void Playerai_SetInheritedMotionFlags(void *player, void *source, s32 enabled) {
    PlayerDamageOverTimeView *object = player;
    LevelActor *argument = source;
    s32 flags;
    s32 flag_1000;
    s32 flag_8000;
    s32 periodicHazardFlag;

    if (enabled != 0) {
        flags = argument->motionState;
        flag_1000 = flags & 0x1000;
        flag_8000 = flags & 0x8000;
        periodicHazardFlag = flags & 0x10000;
        if (flag_1000 == 0) {
            object->effectTimer = 0;
        } else {
            Playerai_ApplyDamageOverTime(player, source);
        }
        if (flag_8000) {
            Playerai_NoopDamageSourceCallback_de(player, source);
        }
        if (periodicHazardFlag) {
            Playerai_ApplyPeriodicHazardDamage(player, source);
        }
    }
}

/* Damage over time while the source's effect flag 0x1000 is set (Playerai_SetInheritedMotionFlags): advances the player's
 * effect timer by the frame step; past 300 it marks the player and deals max(1, (150 - health / 256) / 15)
 * points (8.8 fixed) of kind 0x1F, then winds the timer back by 22.5 so the next tick follows sooner.
 * HONEST-FORM-OPEN: the step check stores the same value in both arms. jump2 cross-jumps the arms and
 * deletes the test, but its reads of `previous` and `step` keep both live past the sum, which puts the
 * sum in $f2 as in the ROM (REV1-ONE-65B RESULT.md). */
void Playerai_ApplyDamageOverTime(Player *player, void *source) {
    s32 missing;
    s32 amount;
    f32 elapsed;
    f32 previous;
    f32 step;
    previous = player->recoveryTime;
    step = g_frameElapsedTime;
    elapsed = previous + step;
    if (elapsed - previous != step) {
        player->recoveryTime = elapsed;
    } else {
        player->recoveryTime = elapsed;
    }
    if (300.0f < elapsed) {
        missing = 150 - (player->health >> 8);
        amount = 1;
        if (missing > 0) {
            missing /= 15;
            if (missing > 0) {
                amount = missing;
            }
        }
        player->collisionState = 1;
        Player_ApplyPlayerDamage(player, source, amount << 8, 0, 31);
        player->recoveryTime -= 22.5f;
    }
}

#define g_gameSettingsView (*(s32 *)&g_gameSettings)

/* Drains a player's ammunition over time: unless Cinema_IsSequenceActive reports a pause, Playerai_IsRoundEndState blocks
   the player, g_worldFrozenFlag is set, bit 1 of g_gameSettings is set or the player's state is below 2, it
   advances the tick counter modulo the period (a fifth of it while the controller is enabled), counting
   only kind 0x20 while the value is positive, and on each wrap takes one from each of the
   three slot counts without going below zero. Written from its own assembly with early
   returns and a clamp-at-zero decrement. */



int Playerai_SelectedWeaponUsesAmmo(Player *actor) {
    short index = actor->selectedAction;
    return ((WeaponInfo *)g_weaponInfoByType[index])->capacity > 0;
}

/** Perform the no-op callback. */
void Playerai_NoopDamageSourceCallback_de(void *player, void *damageSource) {
}

void Playerai_ApplyPeriodicDamage(void *player, s32 damageSource, s32 period, s32 kind) {
    s32 tick;
    if (Cinema_IsSequenceActive() != 0) {
        return;
    }
    if (Playerai_IsRoundEndState(player) != 0) {
        return;
    }
    if (g_world.frozen != 0) {
        return;
    }
    if (g_gameSettingsView & 1) {
        return;
    }
    if ((u16)(((SharedPlayer *)(player))->views5E8.view650_15.actionState) < 2) {
        return;
    }
    if (((SharedPlayer *)(player))->views5E8.view80C_107.mount != 0) {
        period /= 5;
    }
    if (((SharedPlayer *)(player))->views5E8.view670_30.shield > 0.0f && kind != 32) {
        return;
    }
    tick = (((SharedPlayer *)(player))->views5E8.view84C_149.periodicTick + 1) % period;
    ((SharedPlayer *)(player))->views5E8.view84C_149.periodicTick = tick;
    if (tick != 0) {
        return;
    }
    ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[0]) =
        ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[0]) - 1 < 0) ? 0 : (((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[0]) - 1);
    ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[1]) =
        ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[1]) - 1 < 0) ? 0 : (((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[1]) - 1);
    ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[2]) =
        ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[2]) - 1 < 0) ? 0 : (((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[2]) - 1);
}

#undef g_gameSettingsView

/** Set up a player's starting lives from the game mode and character, then reset its respawn state. */









static inline void getEye(Player1680 *player, CVector3 *pos) {
    Matrix frame;

    if (player->mount != 0) {
        *pos = player->mount->position;
    } else {
        Player_BuildPlayerViewTransform(player, &frame);
        Graphu64_GetMatrixTranslation(&frame, pos);
    }
}

static inline float getYaw(void) {
    return g_playerEyeMarkerAngle * g_playerEyeMarkerYawAndHeight.first;
}


void Playerai_ApplyPeriodicHazardDamage(s32 player, s32 damageSource) {
    Playerai_ApplyPeriodicDamage(player, damageSource, 5, 27);
}

void Playerai_UpdateModelBlend(void *actorView, void *bodyActor) {
    void *result;
    f32 blendDelta;
    f32 currentBlend;

    result = (void *)InstHdr_FindActorModelEntry(bodyActor);
    if (result != 0) {
        blendDelta = ((ModelBlend *)result)->blend;
        currentBlend = ((Player *)actorView)->cameraOffset;
        blendDelta = blendDelta - currentBlend;
        blendDelta = blendDelta * g_playerModelBlendRate;
        currentBlend = currentBlend + blendDelta;
        ((Player *)actorView)->cameraOffset = currentBlend;
    }
}

void Playerai_UpdateCountdown(void *player) {
    f32 remainingTime;
    f32 previousTime;
    previousTime = (((struct PlayerTimedPowerupView *) player)->countdownSeconds);
    if (previousTime > 0.0f) {
        remainingTime = previousTime - g_frameElapsedTime;
        (((struct PlayerTimedPowerupView *) player)->countdownSeconds) = remainingTime;
        if (remainingTime < 0.0f) {
            (((struct PlayerTimedPowerupView *) player)->countdownSeconds) = 0.0f;
        }
    }
}

void Playerai_InitializeLivesAndRespawn(PlayerFragTagSelectionView *player) {
    short state;

    if (g_gameSettingsView.started != 0) {
        if (g_gameSettingsView.mode == 1 && player->isBot == 0) {
            player->lives = (unsigned char)Player_GetLevelProgress(&g_localPlayerProfiles[player->character], player->info->character) / 2 + 1;
        }
        if (g_gameSettingsView.mode == 4 && player->isBot == 0 && g_currentStagePreset != 0) {
            player->lives = g_currentStagePreset->laps;
        }
        state = 1;
    } else {
        state = 3;
    }
    player->state = state;
    player->timer = 0;
}

void Playerai_DrawHudSprite1FC(char *player, char *view) {
    f32 x, y;
    f32 sx, sy;
    f32 bx, by;
    f32 hudScreenX, hudScreenY;
    f32 w;
    f32 screenX, screenY;

    Onscrn_SetupSpriteMode(g_playerHudSpriteMode);

    x = ((Shared_HudView *)view)->width;
    sx = x / (f32) g_hudReferenceViewportWidth;
    bx = sx * g_playerHudSpriteMetrics[0];

    y = ((Shared_HudView *)view)->height;
    sy = y / (f32) g_hudReferenceViewportHeight;
    by = sy * g_playerHudSpriteMetrics[0];

    hudScreenX = ((Shared_HudView *)view)->x + x;
    hudScreenY = ((Shared_HudView *)view)->y + y;
    w = ((SharedPlayer *)player)->views5E8.view7BC_101.timer;

    screenX = hudScreenX + bx;
    screenY = hudScreenY + by;

    OnScreen_DrawSpriteResource(508, (s32) w, (s16) (s32) screenX, (s16) (s32) screenY, sx, sy, 1);
}

void Playerai_DrawHudSprite1FB(void *unusedPlayer, struct ScreenRectangle *viewport)
{
  f32 x;
  f32 y;
  f32 ax;
  f32 ay;
  f32 sx;
  f32 sy;
  f32 bx;
  f32 by;
  f32 screenX;
  f32 screenY;
  Onscrn_SetupSpriteMode(g_playerHudSpriteMode);
  x = viewport->x;
  ax = x * g_playerHudSpriteMetrics[1];
  y = viewport->y;
  ay = y * g_playerHudSpriteMetrics[1];
  sx = x / ((f32) g_hudReferenceViewportWidth);
  bx = sx * g_playerHudSpriteMetrics[2];
  sy = y / ((f32) g_hudReferenceViewportHeight);
  by = sy * g_playerHudSpriteMetrics[2];
  screenX = ((viewport->width) + ax) - bx;
  screenY = ((viewport->height) + ay) - by;
  OnScreen_DrawSpriteResource(507, 0, (s16) ((s32) (((viewport->width) + ax) - bx)), (s16) ((s32) screenY), sx, sy, 1);
}

void Playerai_DrawHudSprite201(char *player, char *view) {
    f32 x, y;
    f32 sx, sy;
    f32 bx, by, cz;
    f32 hudScreenX, hudScreenY;
    f32 w;
    f32 screenX, screenY;

    Onscrn_SetupSpriteMode(g_playerHudSpriteMode);

    x = ((Shared_HudView *)view)->width;
    sx = x / (f32) g_hudReferenceViewportWidth;
    bx = sx * g_playerHudSpriteMetrics[3];

    y = ((Shared_HudView *)view)->height;
    sy = y / (f32) g_hudReferenceViewportHeight;
    by = sy * g_playerHudSpriteMetrics[3];

    cz = sy * g_playerHudSpriteMetrics[4];

    hudScreenX = ((Shared_HudView *)view)->x + x;
    hudScreenY = ((Shared_HudView *)view)->y + y;
    w = ((SharedPlayer *)player)->views5E8.view7BC_101.timer;

    screenX = hudScreenX + bx;
    screenY = hudScreenY + by;

    OnScreen_DrawSpriteResource(513, (s32) w, (s16) (s32) screenX, (s16) (s32) screenY, sx, cz, 1);
}

void *Playerai_ResetProfileState(void *actorObject) {
    struct Player *player = actorObject;
    AiProfile *profile = player->profile;
    profile->state90 = 0;
    return profile;
}

s32 Playerai_IsRoundEndState(void *actorObject) {
    Player *player = actorObject;
    s16 action;
    action = player->pose;
    if ((action == 21) || (action == 19) || (action == 20)) {
        return 1;
    }
    return 0;
}

void Playerai_BuildEyeMarkerTransform(Player1680 *player) {
    Matrix mtx;
    CVector3 pos;

    getEye(player, &pos);
    Graphu64_IdentityMatrix(&mtx);
    BuildYawMatrix(&mtx, getYaw());
    TranslateMatrix(&mtx, pos.x, pos.y + g_playerEyeMarkerYawAndHeight.second, pos.z);
    Graphu64_ConvertMatrixToFixed(&mtx, &player->views[g_lightingBufferIndex]);
}

void *Playerai_GetEligiblePlayerByIndex(void *playerWorld, u32 eligiblePlayerIndex) {
    struct PlayerWorldActorTables *world = playerWorld;
    Player *actor;
    s32 eligibleOrdinal;

    actor = 0;
    eligibleOrdinal = 0;
    if (eligiblePlayerIndex < 8U) {
        actor = (void *)world->players;
        if (actor != 0) {
            do {
                if ((u8)actor->profile->state90 == 0) {
                    if (eligibleOrdinal == (s32) eligiblePlayerIndex) {
                        return actor;
                    }
                    eligibleOrdinal += 1;
                }
                actor = actor->next;
            } while (actor != 0);
        }
    }
    return actor;
}

void Playerai_ClearPlayerResetFlags(char *object) {
    struct PlayerWorldActorTables *world = (void *)object;
    Player *record = (void *)world->players;
    while (record != 0) {
        AiProfile *nested = record->profile;
        if ((u8)nested->state90 == 1) {
            nested->state90 = 0;
        }
        record = record->next;
    }
}

void Playerai_ResetAllPlayerHealth(void *object) {
    struct PlayerWorldActorTables *world = (void *)object;
    Player *record = (void *)world->players;
    if (record != 0) {
        do {
            record->profile->bonus = 0;
            Playerai_InitializePlayerHealth(record);
            record = record->next;
        } while (record != 0);
    }
}

s32 Playerai_CountEligiblePlayers(char *object) {
    struct PlayerWorldActorTables *world = (void *)object;
    Player *record = (void *)world->players;
    s32 count = 0;
    while (record != 0) {
        AiProfile *nested = record->profile;
        if ((u8)nested->state90 == 0) {
            count += 1;
        }
        record = record->next;
    }
    return count;
}

s32 Playerai_CountActivePlayers(char *object) {
    struct PlayerWorldActorTables *world = (void *)object;
    Player *record = (void *)world->players;
    s32 count = 0;
    while (record != 0) {
        if (record->actorState != 0) {
            count += 1;
        }
        record = record->next;
    }
    return count;
}

/* Resets a player record to its defaults: clears the reserved and state words, sets both keys to -1, and loads
 * the default float pair, the initial vector (the first default used for x and z) and the default scalar from
 * the constant tables. */

void Player_InitRecordDefaults(void *recordMemory) {
    PlayerRecordDefaultsView *record = recordMemory;
    float defaultFirst = k_playerRecordDefaultPair;
    float defaultSecond = (&k_playerRecordDefaultPair)[1];
    float vectorValue = k_playerRecordDefaultVectorValues;
    float vectorSecondValue = (&k_playerRecordDefaultVectorValues)[1];
    float scalarDefault = k_playerRecordDefaultScalar;

    record->reservedStateOne = 0;
    record->resetState = 0;
    record->reservedStateTwo = 0;
    record->secondKey = -1;
    record->firstKey = -1;
    record->reservedState = 0;
    record->vectorState = 0;
    record->scalarState = 0;
    record->defaultFirstFloat = defaultFirst;
    record->defaultSecondFloat = defaultSecond;
    record->initialVectorX = vectorValue;
    record->initialVectorY = vectorSecondValue;
    record->initialVectorZ = vectorValue;
    record->scalarValue = scalarDefault;
}

s32 Playerai_TryEnterMotionFlagState(void *player, void *bodyActor) {
    s16 state = ((Player *)player)->pose;
    s32 blocked;

    if ((state == 21) || (state == 19) || (state == 20)) {
        blocked = 1;
    } else {
        blocked = 0;
    }
    if (blocked == 0) {
        if ((((LevelActor *)bodyActor)->motionState & 0x20000) == 0) {
            return 0;
        }
        if (((Player *)player)->pose == 13) {
            return 0;
        }
        if (((Player *)player)->pose == 14) {
            return 0;
        }
        Player_SetPlayerState(player, bodyActor, 13);
        return 1;
    }
    return 0;
}

s32 Playerai_TryEnterBodyFlagState(void *player, void *bodyActor) {
    s16 state = ((Player *)player)->pose;
    s32 blocked;
    s32 flags;

    if ((state == 21) || (state == 19) || (state == 20)) {
        blocked = 1;
    } else {
        blocked = 0;
    }
    if (blocked == 0) {
        if (((MovementDescriptor *)((LevelActor *)bodyActor)->definition)->body.header.flags & 1) {
            if (((Player *)player)->pose == 38) {
                return 0;
            }
            if (((Player *)player)->sequenceFlags & 0x8000) {
                return 0;
            }
            flags = ((LevelActor *)bodyActor)->motionState;
            if (flags & 0x80) {
                goto fire;
            }
        }
        return 0;
    }
    return 0;
fire:
    ((LevelActor *)bodyActor)->motionState = flags | 0x100;
    Player_SetPlayerState(player, bodyActor, 15);
    return 1;
}

s32 Player_TryStartJump(void *player, LevelActor *actor) {
    f32 jumpDelay;

    if (((Player *)player)->state7E8 == 0) {
        jumpDelay = ((Player *)player)->jumpDelay;
        if (!(g_playerJumpInputDelayLimit < jumpDelay)) {
            if (!(actor->motionState & 0xC0000)) {
                if (((MovementDescriptor *)actor->definition)->body.header.flags & 2) {
                    if ((((Player *)player)->actionFlags & 0x10) && (((Player *)player)->cooldown <= 0.0f)) {
                        Player_SetPlayerState(player, actor, 5);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

/** Return zero. */
int Player_ReturnZeroStub(void *player, void *actor, s32 *stateFlags) {
    return 0;
}

void Player_ZeroBodyVelocity(void *unusedPlayer, LevelActor *actor) {
    actor->position1.x = 0;
    actor->position1.y = 0;
    actor->position1.z = 0;
}

/* Runs a player's grounded movement state: updates it through Player_EaseOwnerHeightEffect_PlayerJumpAndLeapStates, eases the value at
   0x72C to zero by a quarter, applies the movement tables g_playerGroundViewAngleParameters and g_playerGroundMovementParameters, then leaves for
   state 2 when not on the ground (animation 0x5E24 for the g_playerSpecialAnimationTable state table, otherwise 1), or
   picks the animation from the stick: 0xA64 at rest, 0xA67 or 0xA66 when the
   second axis dominates and 0xA65 or 0xA68 otherwise, by the sign of the dominant axis. */





/* Phase1 source candidate; contract holds and immutable inputs in per-function JSON. */


void Player_StartMovingOnStickInput(struct SharedPlayer *player, void *bodyActor) {
    if ((player->views5E8.view6C0_51.movementSpeed != 0.0f) || (player->views5E8.view6C4_54.sideSpeed != 0.0f)) {
        Player_SetPlayerState(player, bodyActor, 3);
    }
}

void Player_EmptyHandlerAfterStartMovingOnStickInput_de(void) {
}

void Player_EmptyHandlerBeforeUpdateGroundMoveState_de(void) {
}

void Player_UpdateGroundMoveState(struct SharedPlayer *player, void *bodyActor) {
    f32 x;
    f32 y;
    f32 zero;

    Player_EaseOwnerHeightEffect(player);
    zero = 0.0f;
    Graphu64_EaseValueToward(&player->views5E8.view72C_75.strideRoll, zero, 0.25f);
    Player_UpdateViewAngles(player, bodyActor, &g_playerGroundViewAngleParameters);
    Player_UpdateGroundThrustAndBoost(player, bodyActor, &g_playerGroundMovementParameters);
    if (!(player->views5E8.view6AC_45.inputFlags & 0x10)) {
        Player_SetPlayerState(player, bodyActor, 2);
        if (player->views13B4.view13B4_3.character == &g_playerSpecialAnimationTable) {
            player->views5E8.view86C_125.animationId = 24100;
        } else {
            player->views5E8.view86C_125.animationId = 1;
        }
    } else {
        x = player->views5E8.view6C0_51.movementSpeed;
        if (x != zero || player->views5E8.view6C4_54.sideSpeed != zero) {
            y = player->views5E8.view6C4_54.sideSpeed;
            if (x < y) {
                if (zero < y) {
                    player->views5E8.view86C_125.animationId = 2663;
                } else {
                    player->views5E8.view86C_125.animationId = 2662;
                }
            } else if (zero < x) {
                player->views5E8.view86C_125.animationId = 2661;
            } else {
                player->views5E8.view86C_125.animationId = 2664;
            }
        } else {
            player->views5E8.view86C_125.animationId = 2660;
        }
    }
}

void Player_BeginJump(Player *player, void *bodyActor) {
    CVector3 vector;
    f32 scale;
    u8 *result;
    u8 state;
    s32 mode;
    CGameStatus *audio;

    scale = g_playerJumpInitialSpeedScale;
    if (g_activeActorKind == 7601) {
        scale = g_playerJumpInitialSpeedScaleSpecial;
    }
    ((LevelActor *)bodyActor)->position1.y =
        scale * ((Resource_u1 *)((LevelActor *)bodyActor)->definition)->value20;
    result = InstHdr_GetEnabledItemValue(bodyActor);
    if (result != 0) {
        InstHdr_GetActorTargetOffset(result, &vector);
        Graphu64_AddVec3(&((LevelActor *)bodyActor)->position1,
                      &((LevelActor *)bodyActor)->position1, &vector);
    }

    state = ((AiProfile *)player->profile)->bonus;
    if (state == 1) {
        audio = &g_gameSettings.counters;
        if (audio->m_bFragTagOn != 0) {
            mode = audio->m_nFragTagSkin;
            switch (mode) {
        case 0:
            SoundElement_PlaySoundAtPosition(6305,
                          player->pos,
                          (intptr_t)&player->pos, -1);
            break;
        case 1:
            SoundElement_PlaySoundAtPosition(6505,
                          player->pos,
                          (intptr_t)&player->pos, -1);
            break;
        case 2:
            SoundElement_PlaySoundAtPosition(6405,
                          player->pos,
                          (intptr_t)&player->pos, -1);
            break;
            }
        }
    }
}

void Player_UpdateJumpAscent(void *player, LevelActor *actor) {
    f32 scale;

    scale = g_playerJumpAscentSpeedScale;
    if (g_activeActorKind == 7601) {
        scale = g_playerJumpAscentSpeedScaleSpecial;
    }
    if (((Player *)player)->computer != 0) {
        f32 current;

        current = ((Player *)player)->poseTimer;
        if (g_playerBotJumpAscentLimit <= current) {
            goto transition;
        }
        goto scale_value;
    }
    if (!(((Player *)player)->inputFlags & 0x10)) {
        goto transition;
    } else {
        f32 current;

        current = ((Player *)player)->poseTimer;
        if (!(g_playerHumanJumpAscentLimit <= current)) {
            goto scale_value;
        }
    }
transition:
    Player_SetPlayerState(player, actor, 6);
    goto finish;
scale_value:
    actor->position1.y =
        scale * ((Resource_u1 *)actor->definition)->value20;
finish:
    Player_UpdateJumpAirMotion(player, actor);
}

void Player_UpdateJumpAirMotion(void *player, void *body) {
    s32 value;

    Graphu64_EaseValueToward(&((Player *)player)->lean, 0.0f, 0.25f);
    Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    if (!(((Player *)player)->flags660 & 0x8000)) {
        Player_UpdateGroundThrustAndBoost(player, body, &g_playerJumpMovementParameters);
    }
    if (((LevelActor *)body)->position1.y <= 0.0f) {
        if (InstHdr_GetActorMotionState(body) != 0) {
            Player_SetPlayerState(player, body, 2);
        }
    }
    if (((LevelActor *)body)->position1.y <= 0.0f) {
        if (InstHdr_GetShadowGroundHeight(body, 0) < 0.0f) {
            if (-InstHdr_GetShadowGroundHeight(body, 0) < g_playerJumpLandingHeightLimits[0]) {
                goto set_value;
            }
        } else if (InstHdr_GetShadowGroundHeight(body, 0) < g_playerJumpLandingHeightLimits[1]) {
set_value:
            if (((Player *)player)->animationTable == &g_playerSpecialAnimationTable) {
                ((Player *)player)->animation = 24110;
            } else {
                ((Player *)player)->animation = 2040;
            }
        }
    }
}

void Player_BeginLateralLeap(void *movementState, void *actorMotion) {
    if ((((Player *)movementState)->strafe) < 0.0f) {
        (((Player *)movementState)->lateralSpeed) = (f32) g_playerLateralLeapNegativeInputSpeed;
    } else {
        (((Player *)movementState)->lateralSpeed) = (f32) g_playerLateralLeapPositiveInputSpeed;
    }
    (((LevelActor *)actorMotion)->position1.y) = (f32) g_playerLateralLeapInitialVerticalSpeed;
}

void Player_UpdateLateralLeap(void *player, LevelActor *actor) {
    f32 currentLateralSpeed;

    currentLateralSpeed = ((Player *)player)->lateralSpeed;
    if ((currentLateralSpeed < 0.0f && ((Player *)player)->strafe >= 0.0f) ||
        (currentLateralSpeed > 0.0f && ((Player *)player)->strafe <= 0.0f) ||
        (((Player *)player)->poseTimer >= g_playerLateralLeapDuration)) {
        Player_SetPlayerState(player, actor, 8);
    } else {
        actor->position1.y = g_playerLateralLeapVerticalSpeed;
    }
    Player_UpdateLeapMotion((s32)player, (s32)actor);
}

void Player_UpdateLeapMotion(s32 player, s32 body) {
    Graphu64_EaseValueToward(player + 1836, 0.0f, 0.25f);
    Player_UpdateViewAngles((void *)player, (void *)body, &g_playerAirViewAngleParameters);
    Player_UpdateGroundThrustAndBoost((void *)player, (void *)body, &g_playerLeapMovementParameters);
    if (((LevelActor *)body)->position1.y <= 0.0f) {
        if (InstHdr_GetActorMotionState((void *) body) != 0) {
            Player_SetPlayerState((void *) player, (void *) body, 2);
        }
    }
}

void Player_ClearGlobalFlagBit(void) {
    int *gameplayFlags = &g_globalGameplayFlags;
    *gameplayFlags &= 0xFFEFFFFF;
}

/* Runs a player's landing state: sets state 0xD when the value is zero or 0xE otherwise,
   applies the movement tables g_playerFloatViewAngleParameters and g_playerFloatMovementParameters, picks animation 0x8A2 for the model
   g_fragTagModelId or, unless animation 0x1144 is still running with the byte clear, 0x8A2, 0x8A7
   or 0x14 by the stick against g_playerFloatForwardAnimationThreshold and g_playerFloatReverseAnimationThreshold, and switches to state 3 once the
   timer passes g_playerFloatPoseMinimumDuration without input bit 0x20000. */




void Player_AbsorbImpact(void *player, LevelActor *actor) {
    f32 value;
    f32 minimum;
    ((Player *)player)->stick *= g_playerImpactHorizontalDamping;
    ((Player *)player)->lateralSpeed *= g_playerImpactHorizontalDamping;

    value = actor->position1.y * g_playerImpactVerticalDamping;
    minimum = g_playerImpactMinimumVerticalSpeed;
    actor->position1.y = value;
    if (value < minimum) {
        actor->position1.y = minimum;
    }

    ((Player *)player)->collisionState = 0;
    Gsky_ResetHeadBob(((Player *)player)->camera);
    TeamSelect_EmptyWeaponWheelHook();

    if (actor->motionState & 0x8000) {
        SoundElement_PlaySoundAtPosition(730, actor->position0, 0, -1);
    } else {
        SoundElement_PlaySoundAtPosition(732, actor->position0, 0, -1);
    }
}

/** Scales the floats of the first object and the float of the second by g_playerMotionDamping. */


void Player_DampMotion(void *actorState, void *levelActor) {
    Player *actor = actorState;
    LevelActor *other = levelActor;
    actor->stick = actor->stick * (g_playerMotionDamping);
    actor->lateralSpeed = actor->lateralSpeed * (g_playerMotionDamping);
    other->position1.y = other->position1.y * (g_playerMotionDamping);
}

void Player_UpdateFloatPose(void *playerState, LevelActor *actor) {
    Player *player;
    s32 busy;
    f32 x;

    player = playerState;
    if (player->landing == 0.0f) {
        player->pose = 13;
    } else {
        player->pose = 14;
    }
    Player_UpdateViewAngles(player, actor, &g_playerFloatViewAngleParameters);
    Player_UpdateFlyingThrustAndBoost(player, actor, &g_playerFloatMovementParameters);
    busy = 0;
    if (player->animation == 4420) {
        busy = player->animationDone == 0;
    }
    if (player->objectId == g_fragTagModelId) {
        player->animation = 2210;
    } else if (!busy) {
        x = player->stick;
        if (g_playerFloatForwardAnimationThreshold <= x) {
            player->animation = 2210;
        } else if (x <= g_playerFloatReverseAnimationThreshold) {
            player->animation = 2215;
        } else {
            player->animation = 20;
        }
    }
    if (!(actor->motionState & 0x20000) && player->poseTimer > g_playerFloatPoseMinimumDuration) {
        Player_SetPlayerState(player, actor, 3);
    }
}

void Player_ResetMovementInput(void *motionPlayerState, LevelActor *actor)
{
  f32 roundEndMovementScale;
  f32 *movementScale;
  s8 *playerStateBytes;
  playerStateBytes = motionPlayerState;
  roundEndMovementScale = g_playerRoundEndWaitConstants[0];
  ((Player *)playerStateBytes)->stick = 0;
  movementScale = &((Player *)motionPlayerState)->movementScale;
  ((Player *)motionPlayerState)->lateralSpeed = 0;
  *movementScale = roundEndMovementScale;
  actor->position1.x = 0;
  actor->position1.y = 0;
  actor->position1.z = 0;
}

void Player_ResetObjectVelocity(void *ownerActor, void *object) {
    LevelActor *actor = object;
    actor->position1.x = 0.0f;
    actor->position1.y = 0.0f;
    actor->position1.z = 0.0f;
}

/** Perform no operation. */
void Player_EmptyHandlerAfterResetObjectVelocity_de(void) {
}

/** Perform no operation. */
void Player_EmptyHandlerBeforeAimPreviousPositionAtReset_de(void) {
}

void Player_AimPreviousPositionAtReset(void *aimPlayerState) {
    CVector3 vector;
    CVector3 *weaponAimPositionPtr;

    weaponAimPositionPtr = &((Player *)aimPlayerState)->actorParts[1].aimPosition;
    Graphu64_SubtractVectors(&vector, &((Player *)aimPlayerState)->resetPosition, weaponAimPositionPtr);
    Graphu64_NormalizeVec3(&vector);
    Graphu64_ScaleVector(&vector, &vector, 30.0f);
    Graphu64_AddVec3(&((Player *)aimPlayerState)->previousPosition, weaponAimPositionPtr, &vector);
}

void Player_EmptyHandlerAfterAimPreviousPositionAtReset_de(void) {
}

void Player_ResetStunAndReleaseHandles(void *widget) {
    LevelActor *actor = widget;
    Player *player = widget;
    actor->flags &= 0xFF7FFFFF;
    player->cooldown = 0;
    player->zoom = 0.0f;
    actor->flags |= 0x01000000;
    Player_ReleaseObjectHandles((s32) widget);
}

void Player_EmptyHandlerAfterResetStunAndReleaseHandles_de(void) {
}

/** Reset two object fields and replace the control word's mode bit. */
void Player_ResetStunFlags(void *actorState) {
    Player *actor = actorState;
    actor->weaponFlags &= 0xFF7FFFFF;
    actor->cooldown = 0;
    actor->idleAnimationState = 0;
    actor->weaponFlags |= 0x01000000;
}

/** Perform the no-op callback. */
void Player_EmptyHandlerAfterResetStunFlags_de(void) {
}

/* Resets an actor's motion state, advances its wait timer, and fires action 0x13 or 0x14 once the timer passes its limit or the game mode allows it. */




void Playerai_BeginRoundEndWait(Player *widget) {
    s32 clearedActorFlags;

    widget->roundEndWait = 0;
    Player_ReleaseObjectHandles((s32) widget);
    clearedActorFlags = widget->weaponFlags & 0xFF7FFFFF;
    widget->weaponFlags = clearedActorFlags;
    widget->actorMotionWords[0] = 0;
    widget->actorMotionWords[1] = 0;
    widget->actorMotionWords[2] = 0;
    widget->cooldown = 0.0f;
    widget->weaponFlags = clearedActorFlags | 0x01000000;
    widget->idleAnimationState = 0;
    widget->weaponFlags = clearedActorFlags | 0x01000000;
    if (widget->animationTable == &g_playerSpecialAnimationTable) {
        widget->animation = 24100;
    } else {
        widget->animation = 1;
    }
}

void Playerai_UpdateRoundEndWait(Player *player) {
    f32 wait;
    f32 waitLimit;
    CGameStatus *mode;

    player->weaponFlags &= 0xFF7FFFFF;
    player->actorMotionWords[0] = 0;
    player->actorMotionWords[1] = 0;
    player->actorMotionWords[2] = 0;
    player->cooldown = 0.0f;
    player->idleAnimationState = 0;
    player->weaponFlags |= 0x01000000;
    if (player->animationTable == &g_playerSpecialAnimationTable) {
        player->animation = 24100;
    } else {
        player->animation = 1;
    }
    waitLimit = g_playerRoundEndWaitConstants[1];
    wait = player->roundEndWait + g_frameElapsedTime;
    player->roundEndWait = wait;
    if (wait > waitLimit) {
        goto fire;
    }
    if ((mode = &g_gameSettings.counters)->round != 0 && mode->elapsed != 0) {
        fire:
        if ((mode = &g_gameSettings.counters)->round != 0 && 0 == mode->elapsed) {
            Player_SetPlayerState(player, player, 20);
        } else {
            Player_SetPlayerState(player, player, 19);
        }

    }
}

void Playerai_NoopRoundEndWaitFirst_de(void) {
}

void Playerai_NoopRoundEndWaitSecond_de(void) {
}

void Playerai_UpdateRoundEndViewAngles(s32 player, s32 body) {
    Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
}

/** Perform no operation. */
void Playerai_NoopRoundEndViewAngles_de(void) {
}

void Playerai_UpdateShortSequenceWait(void *player) {
    Player *actor = player;
    if (actor->shortSequenceState == 0) {
        if ((actor->sequenceFlags & 0x8000) == 0) {
            Graphu64_EaseValueToward(&actor->lean, 1.308997f, 0.25f);
        }
        if (actor->poseTimer > g_playerShortSequenceWaitLimit) {
            Player_UpdateRunEndPlayer(player);
        }
    }
}

void Playerai_NoopBastilleSquatStart(void) {
}

void Playerai_NoopBastilleSquatUpdate(void) {
}

/** Set bit 0x20 in the wordC. */
void Playerai_SetRunEndFlag(struct SharedPlayer *player) {
    player->views122C.view122C_0.flags |= 0x20;
}

void Playerai_UpdateRunEndTransition(void *runEndPlayer)
{
  f32 elapsedTime;
  elapsedTime = ((PlayerSequenceRunEndActorView *)(runEndPlayer))->poseTimer;
  if (g_playerRunEndTransitionDelay < elapsedTime)
  {
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->overkill = 1;
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->tintMode = -1;
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->tintTime = 0;
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->reactionFlags = (((PlayerSequenceRunEndActorView *)(runEndPlayer))->reactionFlags) & (~0x20);
    Player_UpdateRunEndPlayer(runEndPlayer);
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->scaleX = g_playerRunEndModelScale;
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->scaleY = g_playerRunEndModelScale;
    ((PlayerSequenceRunEndActorView *)(runEndPlayer))->scaleZ = g_playerRunEndModelScale;
    return;
  }
  ContPad_ClearControllerInput(((Player *)runEndPlayer)->tuning);
  ((struct PlayerSequenceRunEndStateView *) ((char *) ((PlayerSequenceRunEndActorView *) runEndPlayer)->controller))->burstRequest = 0;
  ((struct PlayerSequenceRunEndStateView *) ((char *) ((PlayerSequenceRunEndActorView *) runEndPlayer)->controller))->actionFlagFrames = 0;
}

void Playerai_RequestLifeRegenerationTrack(s32 requestValue) {
    g_lifeRegenerationTrackRequest = requestValue;
    CCinema_RequestTrackWithCallbacks(80, 0, addrLow_Playerai_UpdateStoredRunEndPlayer);
}

void Playerai_UpdateSequenceWait(void *player) {
    Player *actor = player;
    f32 value;

    if (actor->shortSequenceState != 0) {
        return;
    }
    if ((actor->sequenceFlags & 0x8000) == 0) {
        Graphu64_EaseValueToward(&actor->lean, 1.308997f, 0.25f);
    }
    value = actor->poseTimer;
    if (g_playerSequenceWaitLimit < value) {
        Player_UpdateRunEndPlayer(player);
    }
}

void Playerai_StartGroundDeathSequence(void *player, void *body) { Playerai_TryStartPlayerSequence(player, body, 10); }

struct CollisionInfo;


void Playerai_ApplyLinkedProjectileStatus(void *linkedActor, s32 statusArg, s32 projectileEvent) {
    Playerai_ApplyProjectileStatus((s32) ((LevelActor *) linkedActor)->controller, linkedActor, statusArg, projectileEvent);
}

void Playerai_ResetControllerMotion(void *player) {
    Player *object = player;
    void *attributes;
    void *state = object->tuning;
    f32 zero;

    if (object->computer != 0) {
        attributes = g_botControllerProfile;
    } else {
        s32 index = object->slot;
        attributes = (void *)(index << 4);
        attributes = (char *)attributes + index;
        attributes = (void *)((s32)attributes << 3);
        attributes = (char *)attributes + index;
        attributes = (void *)((s32)attributes << 2);
        attributes = (char *)g_controllerProfiles + (s32)attributes;
    }
    ContPad_InitControllerInput(state, attributes);

    object->stick = 0;
    object->lateralSpeed = 0;
    object->landing = 0;
    object->landingLateral = 0;
    object->active = 1;
    object->activeElapsed = 0;
    object->activeBlend = 0;
    object->activeResidual = 0;
    object->jumpDelay = 0;
    object->state758 = 0;
    object->state75C = 0;
    object->locked = 0;
    object->lockState = 0;
    object->pitchBias = 0;
    object->pitchBlendStart = 0;
    object->pitchBlendTarget = 0;
    object->pitchBlendProgress = 0;
    object->pitchOffset = 0;
    object->kickYaw = 0;
    object->lean = 0;
    object->sway[0] = 0;
    object->sway[1] = 0;
    object->sway[2] = 0;
    object->sideOffset = 0;
    object->baseHeight = Playerai_GetObjectOwnerHeight(object);
    object->forwardOffset = 0;
    zero = object->forwardOffset;
    (&object->velocity)->x = (&object->velocity)->y = (&object->velocity)->z = zero;
    object->velocityScale = g_playerMotionResetAndProbeScales;
    object->cameraOffset = zero;
    object->cameraScale = g_playerMotionResetAndProbeScales;
    object->previousPosition = object->pos;
    object->previousTarget = object->pos;
}

s32 Playerai_HasWeaponClassType(Player *player, s32 weaponId, s32 classType) {
    s16 **entry;
    s16 **scan;
    WeaponInfo *resource;
    s16 *item;
    s32 i;

    resource = g_weaponInfoByType[weaponId];
    if (player->computer != 0) {
        entry = resource->computerClasses;
        goto scan_setup;
    }
    if (g_playerWeaponClassMode != 1) {
        entry = resource->computerClasses;
        goto scan_setup;
    }
    entry = &resource->weaponClass;

scan_setup:
    i = 0;
    scan = entry;
loop:
    item = *scan;
    if (item == 0) {
        goto null_item;
    }
    if (item[2] != classType) {
        goto mismatch;
    }
    return 1;
null_item:
    return 0;
mismatch:
    i += 1;
    if (i < 3) {
        scan += 1;
        goto loop;
    }
    return 0;
}

s32 Playerai_ProbeCollisionAdjustedPosition(LevelActor *actor, CVector3 *position) {
    /* The movement probe changes only the 0x50-byte actor prefix. */
    u8 saved[0x50];
    s32 moved;

    __builtin_memcpy(saved, actor, sizeof(saved));
    ((struct LevelActor *)actor)->position0.y += Gobjinst_GetActorHeight(actor) * (&g_playerMotionResetAndProbeScales)[1];
    ((struct LevelActor *)actor)->position0.y += ((struct LevelActor *)actor)->eyeHeight;
    Unicol_MoveActorWithCollision(actor, position->x, position->y, position->z, &g_defaultProbeMotionSettings);

    moved = (position->x != ((struct LevelActor *)actor)->position0.x) ||
            (position->y != ((struct LevelActor *)actor)->position0.y) ||
            (position->z != ((struct LevelActor *)actor)->position0.z);
    *position = ((struct LevelActor *)actor)->position0;
    __builtin_memcpy(actor, saved, sizeof(saved));

    return moved;
}

f32 Playerai_SumActivePlayerDistances(void *roundContext, f32 *position) {
    f32 result;
    Round *round = roundContext;
    Player *actorView;

    actorView = round->players;
    result = 0.0f;
    if (actorView != 0) {
        do {
            if (actorView->camera != 0) {
                result += Graphu64_GetPointDistance(position, &actorView->pos.x);
            }
            actorView = (Player *)actorView->next;
        } while (actorView != 0);
    }
    return result;
}

/* Returns whether a record in state 3 carries type 0x5E2A or 0x5E5A, or a type in the range 0x7DF to 0x7E3. */

s32 Playerai_IsStateThreeUpperAnimationGroup(struct SharedPlayer *player) {
    s32 type;

    if (player->views5E8.view650_15.actionState == 3) {
        type = player->views5E8.view86C_125.animationId;
        if (type == 24106 || type == 24154) {
            return 1;
        }
    }
    return player->views5E8.view650_15.actionState == 3 && player->views5E8.view86C_125.animationId >= 2015 && player->views5E8.view86C_125.animationId < 2020;
}

/* Returns whether a record in state 3 carries type 0x5E29 or 0x5E59, or a type in the range 0x7DA to 0x7DE.
 * Adapted from Playerai_IsStateThreeUpperAnimationGroup with the type constants changed. */

s32 Playerai_IsStateThreeLowerAnimationGroup(struct SharedPlayer *player) {
    s32 type;

    if (player->views5E8.view650_15.actionState == 3) {
        type = player->views5E8.view86C_125.animationId;
        if (type == 24105 || type == 24153) {
            return 1;
        }
    }
    return player->views5E8.view650_15.actionState == 3 && player->views5E8.view86C_125.animationId >= 2010 && player->views5E8.view86C_125.animationId < 2015;
}

int Playerai_IsStateFifteen(struct SharedPlayer *player) {
    return player->views5E8.view650_15.actionState == 15;
}

void Playerai_RecoverOutOfBoundsActor(Player *player, LevelActor *actor) {
    void *actorModelEntryResult;

    actorModelEntryResult = InstHdr_FindActorModelEntry(actor);
    if ((actorModelEntryResult != 0) && (((Shared_Surface *)actorModelEntryResult)->flags & 0x4000)) {
        actor->position1.y = 0;
    } else if (actor->position0.y < (g_sceneMinimumActorHeight - g_playerOutOfBoundsAndMarkerHeightConstants)) {
        Player_PlacePlayerAtSpawnPoint(player, player->model, 0, 0);
    }
    if (InstHdr_GetActorMotionState(actor) != 0) {
        player->previousTarget = actor->position0;
    }
}

/* Places a marker in front of an actor: takes the node in *slot or allocates one from pool
   g_dynamicLightPool, turns the offset (0, 0, distance) into world space by the actor's facing through
   Gobjinst_TransformVectorByActorAim, adds the actor's position and stores it as short coordinates, the height raised by
   the actor's size scaled by (&g_playerOutOfBoundsAndMarkerHeightConstants)[1], with scale g_playerOffsetMarkerScale and the node marked active. */






/* Returns whether the entity registered under an id in g_weaponInfoByType has flag 1 (mode 0) or flag 2
   (mode 1) set in its word; other modes give 0. The interval also holds the empty function
   Playerai_EmptyImpactSoundHook that follows. */




u8 Playerai_GetImpactSoundEnabled(s32 soundContext, s32 soundId) {
    if (soundId == 730) {
        if (g_gameSettings.local != 0) {
            return g_gameSettings.bonusIcon;
        }
    }
    return 1;
}

void Playerai_UpdateOffsetMarker(Player *actor, CDLight **slot, s32 kind, f32 distance) {
    CDLight *marker;
    CVector3 offset;
    CVector3 pos;

    marker = *slot;
    if (marker == 0) {
        marker = Gdynlight_AllocateLightNode(&g_dynamicLightPool, kind);
        if (marker == 0) {
            return;
        }
    }
    *slot = marker;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = distance;
    Gobjinst_TransformVectorByActorAim(&pos, actor, offset);
    Graphu64_AddVec3(&pos, &pos, &actor->pos);
    marker->m_bEnabled = 1;
    marker->x = pos.x;
    marker->y = pos.y + Gobjinst_GetActorHeight(actor) * (&g_playerOutOfBoundsAndMarkerHeightConstants)[1];
    marker->z = pos.z;
    marker->m_ColorFade = g_playerOffsetMarkerScale;
}

void Playerai_ReleaseMarkerSlot(void *ownerActor, s32 *markerSlot) {
    s32 lightHandle;

    lightHandle = *markerSlot;
    if (lightHandle != 0) {
        Gdynlight_ReleaseLight(&g_dynamicLightPool, lightHandle);
        *markerSlot = 0;
    }
}

int Playerai_HasWeaponModeFlag(short id, int mode) {
    switch (mode) {
    case 0:
        if (!(((WeaponInfo *)g_weaponInfoByType[id])->flags & 1)) {
            break;
        }
        return 1;
    case 1:
        if (((WeaponInfo *)g_weaponInfoByType[id])->flags & 2) {
            return 1;
        }
        break;
    }
    return 0;
}

void Playerai_EmptyImpactSoundHook(void) {
}

void Playerai_ToggleActionFlagMode(Player *player) {

    if (g_frontendScreenStatus.settings.local != 0) {
        return;
    }
    if (g_frontendScreenStatus.suppressFlaggedActions != 0) {
        if (player->inputFlags & 0x20) {
            return;
        }
    }
    if (!(player->actionFlags & 0x800)) {
        return;
    }
    if (player->toggle != 0) {
        player->toggle = 0;
        return;
    }
    player->toggle = 1;
}

void Playerai_SelectAlternateWeapon(Player *player) {
    WeaponInfo *weaponDefinition;
    s16 alternate;
    u16 alternateWeaponBits;

    if (g_frontendScreenStatus.settings.local != 0) {
        return;
    }
    if (player->weaponLocked != 0) {
        if (player->weaponBusy != 0) {
            return;
        }
    }
    if (g_frontendScreenStatus.suppressFlaggedActions != 0) {
        if (player->inputFlags & 0x20) {
            return;
        }
    }
    if (!(player->actionFlags & 0x200)) {
        return;
    }
    weaponDefinition = g_weaponInfoByType[player->weapon];
    alternate = weaponDefinition->alternate;
    alternateWeaponBits = (u16)weaponDefinition->alternate;
    if (alternate == -1) {
        return;
    }
    if (player->actions[alternate][0] != 0) {
        player->weapon = (s16)alternateWeaponBits;
    }
}

void Playerai_UpdateSurfaceHeightEffect(void *surface, CVector3 *position) {
    f32 first;
    f32 amount;

    if (surface != 0 && position != 0 &&
        (((Shared_CollisionSurface *)surface)->flags & 0x40)) {
        first = Graphu64_GetTrianglePlaneHeight(surface,
            position->x, position->z);
        amount = (f32)(s32)(first - Region_GetPolygonHeight(surface,
            position->x, position->z));
        if (amount < g_playerSurfaceAudioHeightThreshold) {
            SoundElement_SetClampedAudioLevel(g_playerSurfaceAudioBaseLevel - (amount * g_playerSurfaceAudioHeightScale));
            return;
        }
    }
    SoundElement_SetClampedAudioLevel(0.0f);
}

/** Perform no work for callers. */
void Playerai_EmptySurfaceHeightEffectHook(void) {
}

/** Test whether an actor satisfies the condition selected by an entry type. */
s32 Playerai_PlayerHasAmmoForWeapon(void *player, s32 requestedWeaponType) {
    void *entry;
    s16 *condition;
    char *indexed;
    s32 offset;

    entry = g_weaponInfoByType[requestedWeaponType];
    {
        s32 sw_arg1_value = requestedWeaponType;
        if ((unsigned int)sw_arg1_value > 21) {
            goto sw_arg1_default;
        }
        switch (sw_arg1_value) {
        case 0: goto sw_arg1_0;
        case 1: goto sw_arg1_1;
        case 2: goto sw_arg1_1;
        case 3: goto sw_arg1_3;
        case 4: goto sw_arg1_4;
        case 5: goto sw_arg1_1;
        case 6: goto sw_arg1_1;
        case 7: goto sw_arg1_1;
        case 8: goto sw_arg1_1;
        case 9: goto sw_arg1_1;
        case 10: goto sw_arg1_1;
        case 11: goto sw_arg1_1;
        case 12: goto sw_arg1_12;
        case 13: goto sw_arg1_1;
        case 14: goto sw_arg1_1;
        case 15: goto sw_arg1_1;
        case 16: goto sw_arg1_default;
        case 17: goto sw_arg1_default;
        case 18: goto sw_arg1_0;
        case 19: goto sw_arg1_0;
        case 20: goto sw_arg1_0;
        case 21: goto sw_arg1_0;
        }
    }
    do {
    sw_arg1_1:
    sw_arg1_2:
    sw_arg1_5:
    sw_arg1_6:
    sw_arg1_7:
    sw_arg1_8:
    sw_arg1_9:
    sw_arg1_10:
    sw_arg1_11:
    sw_arg1_13:
    sw_arg1_14:
    sw_arg1_15:
        condition = ((WeaponInfo *)(entry))->weaponClass;
        offset = condition[0] * 2;
        indexed = player;
        indexed += offset;
        return ((Player *)player)->ammo[condition[0]] >= condition[3];
    sw_arg1_3:
        return ((Player *)player)->ammo[0] >= 3;
    sw_arg1_4:
        return ((Player *)player)->ammo[0] >= 5;
    sw_arg1_12:
        if (((Player *)player)->ammo[2] == 0) {
            goto check_external;
        }
    sw_arg1_0:
    sw_arg1_18:
    sw_arg1_19:
    sw_arg1_20:
    sw_arg1_21:
        return 1;
    check_external:
        return Particle_CountOwnerListOneEffects(&g_actorParticleEffectSystem[0], (s32)player);
    sw_arg1_default:
        return 0;

    } while (0);
}

int Playerai_ReturnZero(void) {
    char unusedStackPadding[0x10]; /* reserves the original stack frame size */
    return 0;
}

s32 Playerai_TryEnterLandedState(void *player, LevelActor *actor) {
    if (actor->position1.y <= 0.0f && InstHdr_GetActorMotionState(actor) != 0) {
        Player_SetPlayerState(player, actor, 2);
        return 1;
    }
    return 0;
}

/** Update the object's state code from identity, mode, and height bounds. */


void Playerai_SelectMovementAnimation(Player *object) {
    int suppress = 0;
    float value;

    if (object->animation == 4420) {
        suppress = object->animationDone == 0;
    }
    if (object->objectId == g_fragTagModelId) {
        object->animation = 2210;
        return;
    }
    if (!suppress) {
        value = object->stick;
        if (g_playerMovementForwardAnimationThreshold <= value) {
            object->animation = 2210;
            return;
        }
        if (value <= g_playerMovementReverseAnimationThreshold) {
            object->animation = 2215;
            return;
        }
        object->animation = 20;
    }
}

/** Empty adjacent entry point included in Playerai_SelectMovementAnimation's Splat span. */
void Playerai_EmptyMovementAnimationHook(void) {
}

void Playerai_AdvanceCurrentRunEndState(void) {
    if (g_playerSequenceActor->respawnHealth == 1) {
        Player_UpdateRunEndPlayer((s32)g_playerSequenceActor);
    } else {
        Player_SetPlayerState(g_playerSequenceActor, g_playerSequenceActor, 34);
    }
    g_playerSequenceWindowEnabled = 1;
    g_playerSequenceCompletionPending = 0;
}

void Playerai_UpdateStoredRunEndPlayer(void) {
    Player_UpdateRunEndPlayer(g_lifeRegenerationTrackRequest);
}

void Playerai_ResetMotionAndSelectIdleAnimation(Player *player)
{
  s32 clearedActorFlags;
  clearedActorFlags = player->weaponFlags & 0xFF7FFFFF;
  player->weaponFlags = clearedActorFlags;
  player->actorMotionWords[0] = 0;
  player->actorMotionWords[1] = 0;
  player->actorMotionWords[2] = 0;
  player->cooldown = 0.0f;
  player->weaponFlags = clearedActorFlags | 0x01000000;
  player->idleAnimationState = 0;
  player->weaponFlags = clearedActorFlags | 0x01000000;
  if (player->animationTable == (&g_playerSpecialAnimationTable))
  {
    player->animation = 24100;
    return;
  }
  player->animation = 1;
}

void Playerai_ReleasePlayerResource(ResourceLoadState *resourceLoadState) {
    s32 handle;

    Control_SetControllerMode(0);
    Cache_DrainAndCompactResources(0);
    handle = resourceLoadState->handle;
    if (handle != 0) {
        Cache_ReleaseResource(0, handle);
        resourceLoadState->handle = 0;
        resourceLoadState->state4 = 0;
        resourceLoadState->state8 = 0;
    }
}

/** Preserve the empty hook. */
void Playerai_EmptyPlayerResourceHook(void) {
}

void Playerai_RespawnFragTagPlayer(void *player) {
    s32 mode;

    ((Player *)player)->profile->bonus = 1;
    mode = g_gameSettings.counters.m_nFragTagSkin;
    switch (mode) {
    case 0:
        SoundElement_PlaySoundAtPosition(6305,
                      ((Player *)player)->pos,
                      (s32)((char *)player + 8), -1);
        break;
    case 1:
        SoundElement_PlaySoundAtPosition(6505,
                      ((Player *)player)->pos,
                      (s32)((char *)player + 8), -1);
        break;
    case 2:
        SoundElement_PlaySoundAtPosition(6405,
                      ((Player *)player)->pos,
                      (s32)((char *)player + 8), -1);
        break;
    }
    TeamSelect_EmptyWeaponWheelHook();
    ((Player *)player)->locked = 0;
    Actor_RequestActorState(&((Player *)player)->actorParts[1], &((Player *)player)->actorParts[1].behaviorFlags, 1);
    Player_PlacePlayerAtSpawnPoint(player, ((Player *)player)->model, 0, 1);
    Playerai_InitializePlayerHealth(player);
}

s32 Playerai_CountTrailingSpaces(s32 textAddress, s32 length) {
    s32 characterIndex;
    s32 result;
    s32 space;

    result = 0;
    space = 32;
    characterIndex = length;
loop_1:
    characterIndex -= 1;
    if (*((u8 *)textAddress + characterIndex) == space) {
        result += 1;
        if (characterIndex > 0) {
            goto loop_1;
        }
    }
    return result;
}



#if defined(VERSION_EU_X)
extern char s_PlayeraiSelectmovementanimationElsIndeText[8];
#endif

#if defined(VERSION_EU)
extern unsigned int k_playeraiSelectMovementAnimationInstructionWords[2];
#endif

#if defined(VERSION_US)
extern float k_SceneLoadlevelresourcesData[6];
#endif
#if defined(VERSION_EU)
struct {
    unsigned int words0[11];
    float floats1[1];
    unsigned int words2[23];
    char text3[4];
    unsigned int words4[5];
    char text5[4];
    unsigned int words6[620];
} g_playerMovementStateWordsDe = {
    {
        0x3FDD2F1C, 0x4030F27C, 0x41A5E354, 0x3F84B5DE, 0x00000000, 0x00000000, 0x00000000, 0x403851EC,
        0x41ACCCCC, 0x3F8A3D71, 0x3FDD2F1C, 0x414F5C2A, 0x3F25E355, 0x00000000, 0x00000000, 0x00000000,
    },
    { 12.960001f },
    {
        0x3F25E355, 0x00000000, 0x00000000, 0x00000000, 0x4123D70A, 0x41F5C28F, 0x41570A3D, 0x4123D70A,
        0x420F5C29, 0x41570A3D, 0x00000000, 0x00000000, 0x00000000, 0x40A3D70A, 0x4175C28F, 0x4075C28F,
        0x40A3D70A, 0x418F5C29, 0x4075C28F, 0x00000000, 0x00000000, 0x00000000, 0x3E800000, 0x3F666666,
    },
    "\?fff",
    {
        0x3F19999A, 0x3E99999A, 0xBFC90FDC, 0x3FC90FDC, 0x3E800000, 0x3F666666, 0x3F19999A, 0x3E99999A,
    },
    "\?fff",
    {
        0x3F19999A, 0x3E99999A, 0xBF490FDC, 0x3FC90FDC, 0x00000000, 0x00000000, 0x3F000000, 0x3E800000,
        0xBD8EFA36, 0x3FC90FDC, 0x40F5C28F, 0x41B851EB, 0x40B851EB, 0x40F5C28F, 0x41D70A3E, 0x40B851EB,
        0x4123D70A, 0x3F449BA6, 0x00000001, 0x4003126F, 0x4175C28F, 0x3F83126F, 0x41A3D70A, 0x3FC49BA6,
        0x41A3D70A, 0x43199999, 0x42CCCCCC, 0x00000001, 0x3ECCCCCD, 0x3F000000, 0x3F800000, 0x3E800000,
        0xBFC90FDC, 0x3FC90FDC, 0x3E4CCCCD, 0x3E800000, 0x3F000000, 0x3E000000, 0xBFC90FDC, 0x3FC90FDC,
        0x3F83126F, 0x40F5C28F, 0x3F03126F, 0x4123D70A, 0x3F449BA6, 0x4123D70A, 0x42999999, 0x424CCCCC,
        0x00000000, (unsigned int)Player_ZeroBodyVelocity, (unsigned int)Player_UpdateFlyMode,
            (unsigned int)&g_secondaryCollisionContext[6].info, 0x00000000, 0x00000001, 0x00020000, 0x00000000,
        (unsigned int)Player_UpdateFlyMode, (unsigned int)&g_secondaryCollisionContext[6].info, 0x00000000, 0x00000001, 0x00020000,
            (unsigned int)Player_StartMovingOnStickInput, (unsigned int)Player_UpdateStandingState,
            (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x00000001, 0x00020000, (unsigned int)Playerai_StartWalkingMovement_eu_AddressWord,
            (unsigned int)Playerai_UpdateWalkingMovement, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x000007DA,
        0x00030000, (unsigned int)Player_StartGroundMoveState_eu_AddressWord, (unsigned int)Player_UpdateGroundMoveState,
            (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00000A64, 0x00030000, (unsigned int)Player_BeginJump,
        (unsigned int)Player_UpdateJumpAscent, (unsigned int)&g_collisionSurfaceExcludedFromTraceJumpEntry, 0x00000800, 0x000007EE,
            0x00020000, 0x00000000, (unsigned int)Player_UpdateJumpAirMotion,
            (unsigned int)&g_collisionSurfaceExcludedFromTraceJumpEntry,
        0x00000800, 0x000007EE, 0x00020000, (unsigned int)Player_BeginLateralLeap, (unsigned int)Player_UpdateLateralLeap,
            (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x000007EE,
        0x00020000, 0x00000000, (unsigned int)Player_UpdateLeapMotion, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x000007EE, 0x00020000, (unsigned int)g_Player_DampMotionCallbackAddressDe,
        (unsigned int)Player_UpdateWadingState, (unsigned int)g_globalGameplayFlags, 0x00000080, 0x000008A2, 0x00020000,
            (unsigned int)g_Player_DampMotionCallbackAddressDe, (unsigned int)Player_UpdateWadingState,
            (unsigned int)g_globalGameplayFlags,
        0x00000080, 0x000008A2, 0x00030000, (unsigned int)Player_AbsorbImpact, (unsigned int)Player_UpdateFloatingState,
            (unsigned int)&g_pagerPageCounters[8], 0x00000040, 0x000008A2,
        0x00020000, (unsigned int)Player_AbsorbImpact, (unsigned int)Player_UpdateFloatingState,
            (unsigned int)&g_pagerPageCounters[8], 0x00000040, 0x000008A2, 0x00030000, (unsigned int)Player_DampMotion,
        (unsigned int)g_Player_ResetMovementInputCallbackAddressUs, (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry,
            0x00000000, 0x000007DA, 0x00020000, (unsigned int)Player_DampMotion,
            (unsigned int)g_Player_ResetMovementInputCallbackAddressUs, (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry,
        0x00000000, 0x000007DA, 0x00020000, (unsigned int)&g_playerStateNoOperationCallbackWords[0x265],
            (unsigned int)Player_UpdateSwimmingState, (unsigned int)&g_supportingPlatformCollisionQuery[1].info, 0x00000100,
            0x00000A3C,
        0x00020000, (unsigned int)Playerai_BeginRoundEndWait, (unsigned int)g_PlayerResetStunAndMotionCallbackAddressDe,
            (unsigned int)&g_secondaryCollisionContext[1].info, 0x00080000, 0x00000001, 0x00020000,
            (unsigned int)Player_StartAimPreviousPositionAtReset_eu_AddressWord,
        (unsigned int)Player_AimPreviousPositionAtReset, (unsigned int)&g_secondaryCollisionContext[6].info, 0x00100000, 0x00000001,
            0x00020000, (unsigned int)Playerai_ResetPlayerAfterDeath,
            (unsigned int)Playerai_UpdateAfterResetPlayerAfterDeath_eu_AddressWord, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00000000, 0x00010000, (unsigned int)Player_ResetStunAndReleaseHandles, 0x00000000,
            (unsigned int)g_defaultActorCollisionInfo, 0x00000000, 0x00000000,
        0x00010000, (unsigned int)Player_ResetStunFlags, (unsigned int)Player_ResetStunFlags,
            (unsigned int)&g_defaultActorCollisionInfo, 0x00000000, 0x00000000, 0x00010000,
            (unsigned int)Playerai_BeginRoundEndWait,
        (unsigned int)Playerai_UpdateRoundEndWait, (unsigned int)&g_defaultActorCollisionInfo, 0x00000000, 0x00000000, 0x00010000,
            (unsigned int)Playerai_StartGroundDeathSequence, (unsigned int)Playerai_UpdateGroundDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001B58, 0x00010000, (unsigned int)Playerai_StartQuicksandDeathSequence, (unsigned int)Playerai_UpdateQuicksandDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001BBC,
        0x00010000, (unsigned int)Playerai_StartPrimagenDeathSequence, (unsigned int)Playerai_UpdatePrimagenDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001BBD, 0x00010000,
            (unsigned int)Playerai_StartExplosiveDeathSequence,
        (unsigned int)Playerai_UpdateExplosiveDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001C20,
            0x00010000, (unsigned int)Playerai_StartImpalementDeathSequence, (unsigned int)Playerai_UpdateImpalementDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001C21, 0x00010000, (unsigned int)Playerai_StartLavaDeathSequence, (unsigned int)Playerai_UpdateLavaDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001CE8,
        0x00010000, (unsigned int)Playerai_StartDisabledCrawlDeathSequence, (unsigned int)Playerai_UpdateCrawlDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001B5D, 0x00010000,
            (unsigned int)Playerai_StartRunningDeathSequence,
        (unsigned int)Playerai_UpdateRunningDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001D4C,
            0x00010000, (unsigned int)Playerai_StartBackwardMovingDeathSequence, (unsigned int)Playerai_UpdateBackwardMovingDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001D51, 0x00010000, (unsigned int)Playerai_StartViewSavingDrowningDeathSequence, (unsigned int)Playerai_UpdateDrowningDeathSequenceWait,
            (unsigned int)&g_supportingPlatformCollisionQuery[4].info, 0x00000000, 0x00001B6C,
        0x00010000, (unsigned int)Playerai_StartFallingDeathSequence, (unsigned int)Playerai_UpdateFallingDeathSequenceWait,
            (unsigned int)&g_supportingPlatformCollisionQuery[4].info, 0x00000000, 0x00001B62, 0x00010000,
            (unsigned int)Playerai_StartClimbingDeathSequence,
        (unsigned int)Playerai_UpdateClimbingDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001B5C,
            0x00010000, (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[0], 0x00000000,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00000000, 0x00010000, (unsigned int)Playerai_InitializeActorModelEffect,
            (unsigned int)Playerai_UpdateTravelSequence, (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry, 0x00000000,
            0x000007EE,
        0x00010000, (unsigned int)Playerai_ClearPlayerWeaponLock,
            (unsigned int)Playerai_StartMovingSequenceState_eu_x_AddressWord, (unsigned int)&g_portalDefaultCollisionQueryTail,
            0x00008000, 0x000007DA, 0x00020000, (unsigned int)Playerai_ResetPlayerWeaponLock,
        (unsigned int)Playerai_StartStoppedSequenceState_eu_x_AddressWord, (unsigned int)&g_portalDefaultCollisionQueryTail,
            0x00008000, 0x000007DA, 0x00030000, (unsigned int)Playerai_OffsetActorForForceMarker,
            (unsigned int)Playerai_UpdateHazardDamage, (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x000023F0, 0x00020000, (unsigned int)Playerai_StartTargetFacingEntryVariant1_eu_AddressWord,
            (unsigned int)Playerai_UpdateTargetFacing, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00000001,
        0x00020000, (unsigned int)Playerai_StartRoundEndViewAngles_eu_AddressWord,
            (unsigned int)Playerai_UpdateRoundEndViewAngles, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x00000001, 0x00020000, (unsigned int)Playerai_StartChestbursterDeathSequence,
        (unsigned int)Playerai_UpdateChestbursterDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001B83,
            0x00010000, (unsigned int)Playerai_StartSwimmingChestbursterDeathSequence, (unsigned int)Playerai_UpdateSwimmingChestbursterDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001B84, 0x00010000, (unsigned int)Playerai_StartRaptorChestbursterDeathSequence,
            (unsigned int)Playerai_UpdateRaptorChestbursterDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000,
            0x00001B85,
        0x00010000, (unsigned int)g_Playerai_EnterMovingSequenceStateCallbackAddressDe,
            (unsigned int)Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000,
            0x00001B86, 0x00010000, (unsigned int)Playerai_StartEntry5B04_eu_AddressWord,
        (unsigned int)Playerai_UpdateEntry5B04_eu_AddressWord, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x00005B04, 0x00020000, (unsigned int)Playerai_SetRunEndFlag, (unsigned int)Playerai_UpdateRunEndTransition,
            (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x00005B05, 0x00020000, (unsigned int)Player_ZeroBodyVelocity, (unsigned int)Player_UpdateFlyMode,
            (unsigned int)&g_secondaryCollisionContext[6].info, 0x00000000, 0x00000001,
        0x00020000, 0x00000000, (unsigned int)Player_UpdateFlyMode, (unsigned int)&g_secondaryCollisionContext[6].info, 0x00000000,
            0x00000001, 0x00020000, (unsigned int)Player_StartMovingOnStickInput,
        (unsigned int)Player_UpdateStandingState, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00005E24,
            0x00020000, (unsigned int)Playerai_StartWalkingMovement_eu_AddressWord, (unsigned int)Playerai_UpdateWalkingMovement,
            (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x00005E29, 0x00030000, (unsigned int)Player_StartGroundMoveState_eu_AddressWord,
            (unsigned int)Player_UpdateGroundMoveState, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00000A64,
        0x00030000, (unsigned int)Player_BeginJump, (unsigned int)Player_UpdateJumpAscent,
            (unsigned int)&g_collisionSurfaceExcludedFromTraceJumpEntry, 0x00000800, 0x00005E2D, 0x00020000, 0x00000000,
        (unsigned int)Player_UpdateJumpAirMotion, (unsigned int)&g_collisionSurfaceExcludedFromTraceJumpEntry, 0x00000800, 0x00005E2D,
            0x00020000, (unsigned int)Player_BeginLateralLeap, (unsigned int)Player_UpdateLateralLeap,
            (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x00005E2D, 0x00020000, 0x00000000, (unsigned int)Player_UpdateLeapMotion,
            (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00005E2D,
        0x00020000, (unsigned int)g_Player_DampMotionCallbackAddressDe, (unsigned int)Player_UpdateWadingState,
            (unsigned int)g_globalGameplayFlags, 0x00000080, 0x000008A2, 0x00020000,
            (unsigned int)g_Player_DampMotionCallbackAddressDe,
        (unsigned int)Player_UpdateWadingState, (unsigned int)g_globalGameplayFlags, 0x00000080, 0x000008A2, 0x00030000,
            (unsigned int)Player_AbsorbImpact, (unsigned int)Player_UpdateFloatingState, (unsigned int)&g_pagerPageCounters[8],
        0x00000040, 0x000008A2, 0x00020000, (unsigned int)Player_AbsorbImpact, (unsigned int)Player_UpdateFloatingState,
            (unsigned int)&g_pagerPageCounters[8], 0x00000040, 0x000008A2,
        0x00030000, (unsigned int)Player_DampMotion, (unsigned int)g_Player_ResetMovementInputCallbackAddressUs,
            (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry, 0x00000000, 0x00005E29, 0x00020000,
            (unsigned int)Player_DampMotion,
        (unsigned int)g_Player_ResetMovementInputCallbackAddressUs, (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry,
            0x00000000, 0x00005E29, 0x00020000, (unsigned int)&g_playerStateNoOperationCallbackWords[0x265],
            (unsigned int)Player_UpdateSwimmingState, (unsigned int)&g_supportingPlatformCollisionQuery[1].info,
        0x00000100, 0x00005E28, 0x00020000, (unsigned int)Playerai_BeginRoundEndWait,
            (unsigned int)g_PlayerResetStunAndMotionCallbackAddressDe, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00080000,
            0x00005E24,
        0x00020000, (unsigned int)Player_StartAimPreviousPositionAtReset_eu_AddressWord,
            (unsigned int)Player_AimPreviousPositionAtReset, (unsigned int)&g_secondaryCollisionContext[6].info, 0x00100000,
            0x00005E24, 0x00020000, (unsigned int)Playerai_ResetPlayerAfterDeath,
        (unsigned int)Playerai_UpdateAfterResetPlayerAfterDeath_eu_AddressWord, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00000000, 0x00010000, (unsigned int)Player_ResetStunAndReleaseHandles, 0x00000000,
            (unsigned int)&g_defaultActorCollisionInfo,
        0x00000000, 0x00000000, 0x00010000, (unsigned int)Player_ResetStunFlags, (unsigned int)Player_ResetStunFlags,
            (unsigned int)g_defaultActorCollisionInfo, 0x00000000, 0x00000000,
        0x00010000, (unsigned int)Playerai_BeginRoundEndWait, (unsigned int)Playerai_UpdateRoundEndWait,
            (unsigned int)&g_defaultActorCollisionInfo, 0x00000000, 0x00000000, 0x00010000,
            (unsigned int)Playerai_StartGroundDeathSequence,
        (unsigned int)Playerai_UpdateGroundDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001B58,
            0x00010000, (unsigned int)Playerai_StartQuicksandDeathSequence, (unsigned int)Playerai_UpdateQuicksandDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001BBC, 0x00010000, (unsigned int)Playerai_StartPrimagenDeathSequence, (unsigned int)Playerai_UpdatePrimagenDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001BBD,
        0x00010000, (unsigned int)Playerai_StartExplosiveDeathSequence, (unsigned int)Playerai_UpdateExplosiveDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001C20, 0x00010000,
            (unsigned int)Playerai_StartImpalementDeathSequence,
        (unsigned int)Playerai_UpdateImpalementDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001C21,
            0x00010000, (unsigned int)Playerai_StartLavaDeathSequence, (unsigned int)Playerai_UpdateLavaDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001CE8, 0x00010000, (unsigned int)Playerai_StartDisabledCrawlDeathSequence, (unsigned int)Playerai_UpdateCrawlDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001B5D,
        0x00010000, (unsigned int)Playerai_StartRunningDeathSequence, (unsigned int)Playerai_UpdateRunningDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001D4C, 0x00010000,
            (unsigned int)Playerai_StartBackwardMovingDeathSequence,
        (unsigned int)Playerai_UpdateBackwardMovingDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001D51,
            0x00010000, (unsigned int)Playerai_StartViewSavingDrowningDeathSequence, (unsigned int)Playerai_UpdateDrowningDeathSequenceWait,
            (unsigned int)&g_supportingPlatformCollisionQuery[4].info,
        0x00000000, 0x00001B6C, 0x00010000, (unsigned int)Playerai_StartFallingDeathSequence, (unsigned int)Playerai_UpdateFallingDeathSequenceWait,
            (unsigned int)&g_supportingPlatformCollisionQuery[4].info, 0x00000000, 0x00001B62,
        0x00010000, (unsigned int)Playerai_StartClimbingDeathSequence, (unsigned int)Playerai_UpdateClimbingDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001B63, 0x00010000,
            (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[0],
        0x00000000, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00000000, 0x00010000,
            (unsigned int)Playerai_InitializeActorModelEffect, (unsigned int)Playerai_UpdateTravelSequence,
            (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry,
        0x00000000, 0x00005E2D, 0x00010000, (unsigned int)Playerai_ClearPlayerWeaponLock,
            (unsigned int)Playerai_StartMovingSequenceState_eu_x_AddressWord, (unsigned int)&g_portalDefaultCollisionQueryTail,
            0x00008000, 0x00005E29,
        0x00020000, (unsigned int)Playerai_ResetPlayerWeaponLock,
            (unsigned int)Playerai_StartStoppedSequenceState_eu_x_AddressWord, (unsigned int)&g_portalDefaultCollisionQueryTail,
            0x00008000, 0x00005E29, 0x00030000, (unsigned int)Playerai_OffsetActorForForceMarker,
        (unsigned int)Playerai_UpdateHazardDamage, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x000023F0,
            0x00020000, (unsigned int)Playerai_StartTargetFacingEntryVariant1_eu_AddressWord,
            (unsigned int)Playerai_UpdateTargetFacing, (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x00005E24, 0x00020000, (unsigned int)Playerai_StartRoundEndViewAngles_eu_AddressWord,
            (unsigned int)Playerai_UpdateRoundEndViewAngles, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x00005E24,
        0x00020000, (unsigned int)Playerai_StartRequestCinemaTrack_eu_x_AddressWord,
            (unsigned int)g_PlayerRequestCinemaTrackCallbackAddressUs, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x00001B83, 0x00020000, (unsigned int)Playerai_StartSwimmingChestbursterDeathSequence,
        (unsigned int)Playerai_UpdateSwimmingChestbursterDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001B84,
            0x00010000, (unsigned int)Playerai_StartRaptorChestbursterDeathSequence, (unsigned int)Playerai_UpdateRaptorChestbursterDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001B85, 0x00010000, (unsigned int)g_Playerai_EnterMovingSequenceStateCallbackAddressDe,
            (unsigned int)Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000,
            0x00001B86,
        0x00010000, (unsigned int)Playerai_StartEntry5B04_eu_AddressWord, (unsigned int)Playerai_UpdateEntry5B04_eu_AddressWord,
            (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00005B04, 0x00020000,
            (unsigned int)Playerai_SetRunEndFlag,
        (unsigned int)Playerai_UpdateRunEndTransition, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00005B05,
            0x00020000, 0x0000012B, 0x012B012B, 0x012B012B,
        0x012B012B, 0x012B012B, 0x012B0000, 0xBE800000,
    },
};
#endif

#if defined(VERSION_EU)
extern float k_overlayLinkRecordOffsetPairs[6];
#endif

#if defined(VERSION_EU_X)
struct {
    unsigned int words0[11];
    float floats1[1];
    unsigned int words2[23];
    char text3[4];
    unsigned int words4[5];
    char text5[4];
    unsigned int words6[620];
} g_playerMovementStateWordsUs = {
    {
        0x3FDD2F1C, 0x4030F27C, 0x41A5E354, 0x3F84B5DE, 0x00000000, 0x00000000, 0x00000000, 0x403851EC,
        0x41ACCCCC, 0x3F8A3D71, 0x3FDD2F1C, 0x414F5C2A, 0x3F25E355, 0x00000000, 0x00000000, 0x00000000,
    },
    { 12.960001f },
    {
        0x3F25E355, 0x00000000, 0x00000000, 0x00000000, 0x4123D70A, 0x41F5C28F, 0x41570A3D, 0x4123D70A,
        0x420F5C29, 0x41570A3D, 0x00000000, 0x00000000, 0x00000000, 0x40A3D70A, 0x4175C28F, 0x4075C28F,
        0x40A3D70A, 0x418F5C29, 0x4075C28F, 0x00000000, 0x00000000, 0x00000000, 0x3E800000, 0x3F666666,
    },
    "\?fff",
    {
        0x3F19999A, 0x3E99999A, 0xBFC90FDC, 0x3FC90FDC, 0x3E800000, 0x3F666666, 0x3F19999A, 0x3E99999A,
    },
    "\?fff",
    {
        0x3F19999A, 0x3E99999A, 0xBF490FDC, 0x3FC90FDC, 0x00000000, 0x00000000, 0x3F000000, 0x3E800000,
        0xBD8EFA36, 0x3FC90FDC, 0x40F5C28F, 0x41B851EB, 0x40B851EB, 0x40F5C28F, 0x41D70A3E, 0x40B851EB,
        0x4123D70A, 0x3F449BA6, 0x00000001, 0x4003126F, 0x4175C28F, 0x3F83126F, 0x41A3D70A, 0x3FC49BA6,
        0x41A3D70A, 0x43199999, 0x42CCCCCC, 0x00000001, 0x3ECCCCCD, 0x3F000000, 0x3F800000, 0x3E800000,
        0xBFC90FDC, 0x3FC90FDC, 0x3E4CCCCD, 0x3E800000, 0x3F000000, 0x3E000000, 0xBFC90FDC, 0x3FC90FDC,
        0x3F83126F, 0x40F5C28F, 0x3F03126F, 0x4123D70A, 0x3F449BA6, 0x4123D70A, 0x42999999, 0x424CCCCC,
        0x00000000, (unsigned int)Player_ZeroBodyVelocity, (unsigned int)Player_UpdateFlyMode,
            (unsigned int)&g_secondaryCollisionContext[6].info, 0x00000000, 0x00000001, 0x00020000, 0x00000000,
        (unsigned int)Player_UpdateFlyMode, (unsigned int)&g_secondaryCollisionContext[6].info, 0x00000000, 0x00000001, 0x00020000,
            (unsigned int)Player_StartMovingOnStickInput, (unsigned int)Player_UpdateStandingState,
            (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x00000001, 0x00020000, (unsigned int)Playerai_StartWalkingMovement_eu_x_AddressWord,
            (unsigned int)Playerai_UpdateWalkingMovement, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x000007DA,
        0x00030000, (unsigned int)Player_StartGroundMoveState_eu_x_AddressWord, (unsigned int)Player_UpdateGroundMoveState,
            (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00000A64, 0x00030000, (unsigned int)Player_BeginJump,
        (unsigned int)Player_UpdateJumpAscent, (unsigned int)&g_collisionSurfaceExcludedFromTraceJumpEntry, 0x00000800, 0x000007EE,
            0x00020000, 0x00000000, (unsigned int)Player_UpdateJumpAirMotion,
            (unsigned int)&g_collisionSurfaceExcludedFromTraceJumpEntry,
        0x00000800, 0x000007EE, 0x00020000, (unsigned int)Player_BeginLateralLeap, (unsigned int)Player_UpdateLateralLeap,
            (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x000007EE,
        0x00020000, 0x00000000, (unsigned int)Player_UpdateLeapMotion, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x000007EE, 0x00020000, (unsigned int)Player_ClearGlobalFlagBit,
        (unsigned int)Player_UpdateWadingState, (unsigned int)g_globalGameplayFlags, 0x00000080, 0x000008A2, 0x00020000,
            (unsigned int)Player_ClearGlobalFlagBit, (unsigned int)Player_UpdateWadingState, (unsigned int)g_globalGameplayFlags,
        0x00000080, 0x000008A2, 0x00030000, (unsigned int)Player_AbsorbImpact, (unsigned int)Player_UpdateFloatingState,
            (unsigned int)&g_pagerPageCounters[8], 0x00000040, 0x000008A2,
        0x00020000, (unsigned int)Player_AbsorbImpact, (unsigned int)Player_UpdateFloatingState,
            (unsigned int)&g_pagerPageCounters[8], 0x00000040, 0x000008A2, 0x00030000, (unsigned int)Player_DampMotion,
        (unsigned int)g_Player_ResetMovementInputCallbackAddressDe, (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry,
            0x00000000, 0x000007DA, 0x00020000, (unsigned int)Player_DampMotion,
            (unsigned int)g_Player_ResetMovementInputCallbackAddressDe, (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry,
        0x00000000, 0x000007DA, 0x00020000, (unsigned int)g_Player_ResetMovementInputAddress,
            (unsigned int)Player_UpdateSwimmingState, (unsigned int)&g_supportingPlatformCollisionQuery[1].info, 0x00000100,
            0x00000A3C,
        0x00020000, (unsigned int)Player_ResetObjectVelocity,
            (unsigned int)Player_UpdateAfterResetObjectVelocity_eu_x_AddressWord, (unsigned int)&g_secondaryCollisionContext[1].info,
            0x00080000, 0x00000001, 0x00020000, (unsigned int)Player_StartAimPreviousPositionAtReset_eu_x_AddressWord,
        (unsigned int)Player_AimPreviousPositionAtReset, (unsigned int)&g_secondaryCollisionContext[6].info, 0x00100000, 0x00000001,
            0x00020000, (unsigned int)Playerai_ResetPlayerAfterDeath,
            (unsigned int)Playerai_UpdateAfterResetPlayerAfterDeath_eu_x_AddressWord,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00000000, 0x00010000, (unsigned int)Player_ResetStunAndReleaseHandles, 0x00000000,
            (unsigned int)g_defaultActorCollisionInfo, 0x00000000, 0x00000000,
        0x00010000, (unsigned int)Player_ResetStunFlags, (unsigned int)Player_UpdateAfterResetStunFlags_eu_x_AddressWord,
            (unsigned int)&g_defaultActorCollisionInfo, 0x00000000, 0x00000000, 0x00010000,
            (unsigned int)Playerai_BeginRoundEndWait,
        (unsigned int)Playerai_UpdateRoundEndWait, (unsigned int)&g_defaultActorCollisionInfo, 0x00000000, 0x00000000, 0x00010000,
            (unsigned int)addrLow_Playerai_StartRunningDeathSequence_us,
            (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[5], (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001B58, 0x00010000, (unsigned int)addrLow_Playerai_StartClimbingDeathSequence_us,
            (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[7], (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001BBC,
        0x00010000, (unsigned int)g_Playerai_InitializeActorModelEffectCallbackAddressUs,
            (unsigned int)Playerai_InitializeActorModelEffect, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000,
            0x00001BBD, 0x00010000, (unsigned int)addrLow_Playerai_StartPrimagenDeathSequence_us,
        (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[9], (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001C20, 0x00010000, (unsigned int)Playerai_StartImpalementDeathSequence,
            (unsigned int)Playerai_UpdateImpalementDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001C21, 0x00010000, (unsigned int)addrLow_Playerai_StartFallingDeathSequence_us,
            (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[8], (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001CE8,
        0x00010000, (unsigned int)addrLow_Playerai_StartImpalementDeathSequence_us,
            (unsigned int)addrLow_Playerai_UpdateImpalementDeathSequenceWait_us, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001B5D, 0x00010000, (unsigned int)addrLow_Playerai_StartChestbursterDeathSequence_us,
        (unsigned int)addrLow_Playerai_UpdateChestbursterDeathSequenceWait_us, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001D4C, 0x00010000, (unsigned int)addrLow_Playerai_StartSwimmingChestbursterDeathSequence_us,
            (unsigned int)addrLow_Playerai_UpdateSwimmingChestbursterDeathSequenceWait_us, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001D51, 0x00010000, (unsigned int)addrLow_Playerai_StartBackwardMovingDeathSequence_us,
            (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[6],
            (unsigned int)&g_supportingPlatformCollisionQuery[4].info, 0x00000000, 0x00001B6C,
        0x00010000, (unsigned int)addrLow_Playerai_StartSwimmingRaptorChestbursterDeathSequence_us,
            (unsigned int)addrLow_Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait_us,
            (unsigned int)&g_supportingPlatformCollisionQuery[4].info, 0x00000000, 0x00001B62, 0x00010000,
            (unsigned int)addrLow_Playerai_StartRaptorChestbursterDeathSequence_us,
        (unsigned int)addrLow_Playerai_UpdateRaptorChestbursterDeathSequenceWait_us, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001B5C, 0x00010000, (unsigned int)Playerai_RequestLifeRegenerationTrack, 0x00000000,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00000000, 0x00010000, (unsigned int)Playerai_InitializeActorModelEffect,
            (unsigned int)Playerai_UpdateTravelSequence, (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry, 0x00000000,
            0x000007EE,
        0x00010000, (unsigned int)Playerai_StartMovingSequenceState_eu_x_AddressWord,
            (unsigned int)Playerai_EnterMovingSequenceState, (unsigned int)&g_portalDefaultCollisionQueryTail, 0x00008000,
            0x000007DA, 0x00020000, (unsigned int)Playerai_StartStoppedSequenceState_eu_x_AddressWord,
        (unsigned int)Playerai_EnterStoppedSequenceState, (unsigned int)&g_portalDefaultCollisionQueryTail, 0x00008000, 0x000007DA,
            0x00030000, (unsigned int)Playerai_OffsetActorForForceMarker, (unsigned int)Playerai_UpdateHazardDamage,
            (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x000023F0, 0x00020000, (unsigned int)Playerai_StartTargetFacing_eu_x_AddressWord,
            (unsigned int)Playerai_UpdateTargetFacing, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00000001,
        0x00020000, (unsigned int)Playerai_StartRequestCinemaTrack_eu_x_AddressWord,
            (unsigned int)g_PlayerRequestCinemaTrackCallbackAddressUs, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x00000001, 0x00020000, (unsigned int)Playerai_StartChestbursterDeathSequence,
        (unsigned int)Playerai_UpdateChestbursterDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001B83,
            0x00010000, (unsigned int)Playerai_StartSwimmingChestbursterDeathSequence, (unsigned int)Playerai_UpdateSwimmingChestbursterDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001B84, 0x00010000, (unsigned int)Playerai_StartRaptorChestbursterDeathSequence,
            (unsigned int)Playerai_UpdateRaptorChestbursterDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000,
            0x00001B85,
        0x00010000, (unsigned int)Playerai_StartSwimmingRaptorChestbursterDeathSequence, (unsigned int)Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001B86, 0x00010000,
            (unsigned int)Playerai_StartEntry5B04_eu_x_AddressWord,
        (unsigned int)Playerai_UpdateEntry5B04_eu_x_AddressWord, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x00005B04, 0x00020000, (unsigned int)Playerai_SetRunEndFlag,
            (unsigned int)addrLow_Playerai_UpdateGroundDeathSequenceWait_us, (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x00005B05, 0x00020000, (unsigned int)Player_ZeroBodyVelocity, (unsigned int)Player_UpdateFlyMode,
            (unsigned int)&g_secondaryCollisionContext[6].info, 0x00000000, 0x00000001,
        0x00020000, 0x00000000, (unsigned int)Player_UpdateFlyMode, (unsigned int)&g_secondaryCollisionContext[6].info, 0x00000000,
            0x00000001, 0x00020000, (unsigned int)Player_StartMovingOnStickInput,
        (unsigned int)Player_UpdateStandingState, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00005E24,
            0x00020000, (unsigned int)Playerai_StartWalkingMovement_eu_x_AddressWord,
            (unsigned int)Playerai_UpdateWalkingMovement, (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x00005E29, 0x00030000, (unsigned int)Player_StartGroundMoveState_eu_x_AddressWord,
            (unsigned int)Player_UpdateGroundMoveState, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00000A64,
        0x00030000, (unsigned int)Player_BeginJump, (unsigned int)Player_UpdateJumpAscent,
            (unsigned int)&g_collisionSurfaceExcludedFromTraceJumpEntry, 0x00000800, 0x00005E2D, 0x00020000, 0x00000000,
        (unsigned int)Player_UpdateJumpAirMotion, (unsigned int)&g_collisionSurfaceExcludedFromTraceJumpEntry, 0x00000800, 0x00005E2D,
            0x00020000, (unsigned int)Player_BeginLateralLeap, (unsigned int)Player_UpdateLateralLeap,
            (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x00005E2D, 0x00020000, 0x00000000, (unsigned int)Player_UpdateLeapMotion,
            (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x00005E2D,
        0x00020000, (unsigned int)Player_ClearGlobalFlagBit, (unsigned int)Player_UpdateWadingState,
            (unsigned int)g_globalGameplayFlags, 0x00000080, 0x000008A2, 0x00020000, (unsigned int)Player_ClearGlobalFlagBit,
        (unsigned int)Player_UpdateWadingState, (unsigned int)g_globalGameplayFlags, 0x00000080, 0x000008A2, 0x00030000,
            (unsigned int)Player_AbsorbImpact, (unsigned int)Player_UpdateFloatingState, (unsigned int)&g_pagerPageCounters[8],
        0x00000040, 0x000008A2, 0x00020000, (unsigned int)Player_AbsorbImpact, (unsigned int)Player_UpdateFloatingState,
            (unsigned int)&g_pagerPageCounters[8], 0x00000040, 0x000008A2,
        0x00030000, (unsigned int)Player_DampMotion, (unsigned int)g_Player_ResetMovementInputCallbackAddressDe,
            (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry, 0x00000000, 0x00005E29, 0x00020000,
            (unsigned int)Player_DampMotion,
        (unsigned int)g_Player_ResetMovementInputCallbackAddressDe, (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry,
            0x00000000, 0x00005E29, 0x00020000, (unsigned int)g_Player_ResetMovementInputAddress,
            (unsigned int)Player_UpdateSwimmingState, (unsigned int)&g_supportingPlatformCollisionQuery[1].info,
        0x00000100, 0x00005E28, 0x00020000, (unsigned int)Player_ResetObjectVelocity,
            (unsigned int)Player_UpdateAfterResetObjectVelocity_eu_x_AddressWord, (unsigned int)&g_secondaryCollisionContext[1].info,
            0x00080000, 0x00005E24,
        0x00020000, (unsigned int)Player_StartAimPreviousPositionAtReset_eu_x_AddressWord,
            (unsigned int)Player_AimPreviousPositionAtReset, (unsigned int)&g_secondaryCollisionContext[6].info, 0x00100000,
            0x00005E24, 0x00020000, (unsigned int)Playerai_ResetPlayerAfterDeath,
        (unsigned int)Playerai_UpdateAfterResetPlayerAfterDeath_eu_x_AddressWord, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00000000, 0x00010000, (unsigned int)Player_ResetStunAndReleaseHandles, 0x00000000,
            (unsigned int)&g_defaultActorCollisionInfo,
        0x00000000, 0x00000000, 0x00010000, (unsigned int)Player_ResetStunFlags,
            (unsigned int)Player_UpdateAfterResetStunFlags_eu_x_AddressWord, (unsigned int)&g_defaultActorCollisionInfo,
            0x00000000, 0x00000000,
        0x00010000, (unsigned int)Playerai_BeginRoundEndWait, (unsigned int)Playerai_UpdateRoundEndWait,
            (unsigned int)&g_defaultActorCollisionInfo, 0x00000000, 0x00000000, 0x00010000,
            (unsigned int)addrLow_Playerai_StartRunningDeathSequence_us,
        (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[5], (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001B58, 0x00010000, (unsigned int)addrLow_Playerai_StartClimbingDeathSequence_us,
            (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[7], (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001BBC, 0x00010000, (unsigned int)g_Playerai_InitializeActorModelEffectCallbackAddressUs,
            (unsigned int)Playerai_InitializeActorModelEffect, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000,
            0x00001BBD,
        0x00010000, (unsigned int)addrLow_Playerai_StartPrimagenDeathSequence_us,
            (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[9], (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001C20, 0x00010000, (unsigned int)Playerai_StartImpalementDeathSequence,
        (unsigned int)Playerai_UpdateImpalementDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001C21,
            0x00010000, (unsigned int)addrLow_Playerai_StartFallingDeathSequence_us,
            (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[8], (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001CE8, 0x00010000, (unsigned int)addrLow_Playerai_StartImpalementDeathSequence_us,
            (unsigned int)addrLow_Playerai_UpdateImpalementDeathSequenceWait_us, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001B5D,
        0x00010000, (unsigned int)addrLow_Playerai_StartChestbursterDeathSequence_us,
            (unsigned int)addrLow_Playerai_UpdateChestbursterDeathSequenceWait_us, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001D4C, 0x00010000, (unsigned int)addrLow_Playerai_StartSwimmingChestbursterDeathSequence_us,
        (unsigned int)addrLow_Playerai_UpdateSwimmingChestbursterDeathSequenceWait_us, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001D51, 0x00010000, (unsigned int)addrLow_Playerai_StartBackwardMovingDeathSequence_us,
            (unsigned int)g_playerSequenceRunEndUpdateCallbackRecords[6],
            (unsigned int)&g_supportingPlatformCollisionQuery[4].info,
        0x00000000, 0x00001B6C, 0x00010000, (unsigned int)addrLow_Playerai_StartSwimmingRaptorChestbursterDeathSequence_us,
            (unsigned int)addrLow_Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait_us,
            (unsigned int)&g_supportingPlatformCollisionQuery[4].info, 0x00000000, 0x00001B62,
        0x00010000, (unsigned int)addrLow_Playerai_StartRaptorChestbursterDeathSequence_us,
            (unsigned int)addrLow_Playerai_UpdateRaptorChestbursterDeathSequenceWait_us, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
            0x00000000, 0x00001B63, 0x00010000, (unsigned int)Playerai_RequestLifeRegenerationTrack,
        0x00000000, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00000000, 0x00010000,
            (unsigned int)Playerai_InitializeActorModelEffect, (unsigned int)Playerai_UpdateTravelSequence,
            (unsigned int)&g_collisionSurfaceExcludedFromTraceTravelEntry,
        0x00000000, 0x00005E2D, 0x00010000, (unsigned int)Playerai_StartMovingSequenceState_eu_x_AddressWord,
            (unsigned int)Playerai_EnterMovingSequenceState, (unsigned int)&g_portalDefaultCollisionQueryTail, 0x00008000,
            0x00005E29,
        0x00020000, (unsigned int)Playerai_StartStoppedSequenceState_eu_x_AddressWord,
            (unsigned int)Playerai_EnterStoppedSequenceState, (unsigned int)&g_portalDefaultCollisionQueryTail, 0x00008000,
            0x00005E29, 0x00030000, (unsigned int)Playerai_OffsetActorForForceMarker,
        (unsigned int)Playerai_UpdateHazardDamage, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000, 0x000023F0,
            0x00020000, (unsigned int)Playerai_StartTargetFacing_eu_x_AddressWord, (unsigned int)Playerai_UpdateTargetFacing,
            (unsigned int)&g_secondaryCollisionContext[1].info,
        0x00000000, 0x00005E24, 0x00020000, (unsigned int)Playerai_StartRequestCinemaTrack_eu_x_AddressWord,
            (unsigned int)g_PlayerRequestCinemaTrackCallbackAddressUs, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x00005E24,
        0x00020000, (unsigned int)Playerai_StartRequestCinemaTrackDe_eu_x_AddressWord,
            (unsigned int)g_PlayerRequestCinemaTrackCallbackAddressDe, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x00001B83, 0x00020000, (unsigned int)Playerai_StartSwimmingChestbursterDeathSequence,
        (unsigned int)Playerai_UpdateSwimmingChestbursterDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000, 0x00001B84,
            0x00010000, (unsigned int)Playerai_StartRaptorChestbursterDeathSequence, (unsigned int)Playerai_UpdateRaptorChestbursterDeathSequenceWait,
            (unsigned int)((char *)&g_particleOwnerEffectFlags + 8),
        0x00000000, 0x00001B85, 0x00010000, (unsigned int)Playerai_StartSwimmingRaptorChestbursterDeathSequence,
            (unsigned int)Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait, (unsigned int)((char *)&g_particleOwnerEffectFlags + 8), 0x00000000,
            0x00001B86,
        0x00010000, (unsigned int)Playerai_StartEntry5B04_eu_x_AddressWord,
            (unsigned int)Playerai_UpdateEntry5B04_eu_x_AddressWord, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x00005B04, 0x00020000, (unsigned int)Playerai_SetRunEndFlag,
        (unsigned int)addrLow_Playerai_UpdateGroundDeathSequenceWait_us, (unsigned int)&g_secondaryCollisionContext[1].info, 0x00000000,
            0x00005B05, 0x00020000, 0x0000012B, 0x012B012B, 0x012B012B,
        0x012B012B, 0x012B012B, 0x012B0000, 0xBE800000,
    },
};
#endif

#if defined(VERSION_US)
extern float k_DecodeData[16];
#endif

#if defined(VERSION_US)

#endif

/* Retained data for this translation unit. */

const float k_PlayeraiSelectmovementanimationData[2] = {
    1.024f, -1.024f,
};
#if defined(VERSION_EU_X)
char s_PlayeraiSelectmovementanimationElsIndeText[8] =
    "els inde";
#endif
#if defined(VERSION_EU)
unsigned int k_playeraiSelectMovementAnimationInstructionWords[2] = {
    0x2694FFFF, 0x8EA20024,
};
#endif
#if defined(VERSION_EU)
float k_overlayLinkRecordOffsetPairs[6] = {
    -132.0f, 64.0f, 64.0f, 24.0f,
    -12.0f, -48.0f,
};
#endif
