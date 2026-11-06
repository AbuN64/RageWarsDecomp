#include "Data/rom_callback_word.h"
#include "Engine/session.h"
#include "Common/self.h"
#include "Ai/ai_functions.h"
#include "Common/level_actor.h"
#include "Common/shared_gameslot.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/model_render.h"
#include <platform_sdk.h>
#include "Common/frag_tag_scores.h"
#include <PR/abi.h>
#include "Common/vector4f.h"
#include "Common/messagesemaphore.h"
#include <PR/gbi.h>
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/resultsoptionsscreen.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Ai/player_drawtintedplayer.h"
#include "Common/playerprofiles.h"
#include "Ai/player_ammo_gift.h"
#include "Ai/player_message_history.h"
#include "Weapon/weapon.h"
#include "Ui/X_files/x_plus.h"
#include "Gobjinst/player_drawtintedplayer_data.h"
#include "Ai/Playerai/playerai_playerai.h"
#include "Cbarrel/barrel_spawnactoreffect.h"
#include "Engine/Geometry/geometry_setupmaterial.h"
#include "Common/sessionhandlerrow.h"
#include "Ai/ai_shared_symbols.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/aiprofile.h"
#include "Common/gameplay_transition.h"
#include "Common/player_score_table.h"
#include "Render/render_types.h"
#include "Common/menu_match_globals.h"
#include "Gsky/sky_postscaledscreenmessage.h"
#include "Render/player_returnone.h"
#include "Weapons/player_movement_interfaces.h"
#include "Render/weapon_initializechargeandstartupcues_data.h"
#include "Ai/player_alternate_fire.h"
#include "Common/player_sequence_state.h"
#include "Sound/externs.h"
#include "Common/player_action_and_pose_views.h"
#include "Sound/playerai_sequence_waits.h"
#include "include_asm.h"
#include "Common/gameplay_movement.h"
#include "Common/world.h"
#include "Common/triple.h"
#include "Common/resourceloadstate.h"
#include "Ai/Player/playerai_entermovingsequencestate_data.h"
#include "Ai/player_team_score.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Ai/playerai_offsetactorforforcemarker_data.h"
#include "Ai/cteamselect.h"
#include "Engine/Unicol/unicol.h"
#include "Engine/Unicol/PLTFMCOL.h"
#include "Common/Lone/collision_current_actor.h"
#include "Weapons/charge_and_linked_actor_handles.h"
#include "Common/gameplay_camera.h"
#include "Common/gameplay_settings.h"
#include "World/playerai_respawnfragtagplayer.h"
#include "World/playerprofile.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Weapons/player_buildweaponhandtransform.h"
#include "Data/Weapon_callbacks/addrlow_weaponai_initializeswitchforsingleround.h"
#include "Data/Weapon_callbacks/g_weapon_resetcontrollerandspinencodedcallback.h"
#include "Data/Weapon_callbacks/addrlow_weapon_release_handles_and_exit_state_label.h"
#include "Data/Weapon_callbacks/player_health_callback_labels.h"
#include "Data/Ovl1_f/weapon_charge_callback_address.h"
#include "Data/Weapon_callbacks/addrlow_weaponai_updatealternatefire.h"
#include "Data/Weapon_callbacks/weapon_update_trigger_release_state_address.h"
#include "Data/Ovl1_d/weapon_charge_and_loop_sound_callback_address.h"
#include "Data/Ovl1_f/weapon_update_held_fire_callback_address.h"
#include "Data/Weapon_callbacks/weapon_state_callback_address.h"
#include "Data/Weapon_callbacks/weapon_startup_cue_address.h"
#include "Data/Weapon_callbacks/addrlow_weapon_advancespinandtriggermode.h"
#include "Data/Weapon_callbacks/weaponai_selectreleasedfirestate_address.h"
#include "Data/Weapon_callbacks/weapon_fire_state_table.h"
#include "Ai/Player/player_buildplayerviewtransform.h"
#include "Game/builddirectionmatrix.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Engine/defs.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Ui/X_files/x_stdio.h"
#include "Ai/playerprofile_symbols.h"
#include "Menu/player_initplayersettingsscreen.h"
#include "Common/selectionscreenstate.h"
#include "Common/format.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"
#include "Data/rest_source_records.h"
#include "Ai/ai_address_labels.h"
#include "Weapons/startup_cues_and_side_yaw.h"
#include "Ai/playerai_updatedelayeddamage__player.h"
#include "X_files/x_plus.h"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const float g_forceMarkerDurationEuropean = 150.0f;
#endif

/* Draws an actor's player model with its status tint: sets the other-mode lighting command and render
   mode 2, gives the model the team colour byte (the match rule g_gameSettings.counters's colour when team
   colours apply to the player, else the model's own), and by the player's tint mode
   sets a colour override (flag g_menuModelFillEnabled, colour g_menuModelFillColor) that fades with the tint time:
   mode 0 draws through Gobjinst_DrawActorPartsWithViewEffects in yellow fading from full alpha and then draws the second pass
   through Geometry_DrawOwnerFilteredPass with 255 less twice that alpha, mode 1 draws only the second pass in fading
   yellow starting at alpha 128, and mode 3 draws through Gobjinst_DrawActorPartsWithViewEffects with an alpha rising with the
   time; the override is switched off afterwards. */

void Player_DrawTintedPlayer(LevelActor *actor, s32 animationContext, struct Draw *draw) {
    PlayerControllerView *player;
    CGameStatus *counters;
    Gfx *gfx;

    if (actor != 0) {
        player = actor->controller;
        if (player != 0) {
            gDPSetRenderMode(g_displayListCursor++, 0xC4404B50, 0);
            Geometry_SetCombineMode(2);
            counters = &g_gameSettings.counters;
            if (counters->m_bFragTagOn != 0 && player->controls->fragTagEnabled != 0) {
                actor->team = (u8)counters->m_nFragTagSkin;
            } else {
                actor->team = (u8)actor->definition->first;
            }
            if (player->tintMode == 0) {
                CQuatern *colour;

                g_menuModelFillEnabled = 1;
                colour = (CQuatern *)g_menuModelFillColor;
                colour->x = ((255.0f - player->tintTime * 17.0f) < 0.0f ? 0.0f : (255.0f - player->tintTime * 17.0f));
                colour->y = ((255.0f - player->tintTime * 17.0f) < 0.0f ? 0.0f : (255.0f - player->tintTime * 17.0f));
                colour->z = 0.0f;
                colour->w = ((255.0f - player->tintTime * 8.533334f) < 0.0f ? 0.0f : (255.0f - player->tintTime * 8.533334f));
                Gobjinst_DrawActorPartsWithViewEffects(actor, player, animationContext, draw);
                colour->w = ((255.0f - colour->w * 2.0f) < 0.0f ? 0.0f : (255.0f - colour->w * 2.0f));
                Geometry_DrawOwnerFilteredPass(draw->model, player, actor->animationMatrices, 1,
                              &actor->lighting[g_lightingBufferIndex], 0, -1);
            } else if (player->tintMode == 1) {
                CQuatern *colour;

                g_menuModelFillEnabled = 1;
                colour = (CQuatern *)g_menuModelFillColor;
                colour->x = ((255.0f - player->tintTime * 17.0f) < 0.0f ? 0.0f : (255.0f - player->tintTime * 17.0f));
                colour->y = ((255.0f - player->tintTime * 17.0f) < 0.0f ? 0.0f : (255.0f - player->tintTime * 17.0f));
                colour->z = 0.0f;
                colour->w = ((128.0f - player->tintTime * 8.533334f) < 0.0f ? 0.0f : (128.0f - player->tintTime * 8.533334f));
                Geometry_DrawOwnerFilteredPass(draw->model, player, actor->animationMatrices, 1,
                              &actor->lighting[g_lightingBufferIndex], 0, -1);
            } else if (player->tintMode == 3) {
                g_menuModelFillEnabled = 1;
                g_menuModelFillColor[3] = ((player->tintTime * 0.425f) < 0.0f ? 0.0f : (player->tintTime * 0.425f));
                Gobjinst_DrawActorPartsWithViewEffects(actor, player, animationContext, draw);
            }
            g_menuModelFillEnabled = 0;
        }
    }
}


void Playerai_UpdateDamageTimers(void *actor) {
    Slot damage;
    f32 scaledTotalDamage;
    f32 damageProgressValue;
    f32 damageUnitScale;
    f32 remainingFrames;
    f32 frameDamage;
    f32 zero;
    s32 damageEffectOffset;
    s32 i;
    void *damageSource;
    void *damageEffect;

    zero = 0.0f;
    damageUnitScale = g_playerDamageTimerConstants[1];
    i = 0;
    damageEffectOffset = 4680;
    do {
        damageEffect = (char *)actor + damageEffectOffset;
        remainingFrames = ((CPlayerDamageOverTime *)(damageEffect))->m_FramesRemaining;
        if (remainingFrames > zero) {
            damageProgressValue = g_frameElapsedTime;
            frameDamage = *(f32 *)damageEffect * damageProgressValue;
            damageProgressValue = remainingFrames - damageProgressValue;
            frameDamage *= damageUnitScale;
            ((CPlayerDamageOverTime *)(damageEffect))->m_FramesRemaining = damageProgressValue;
            damageProgressValue = ((CPlayerDamageOverTime *)(damageEffect))->m_DamageIssued + (f32)(s32)frameDamage;
            ((CPlayerDamageOverTime *)(damageEffect))->m_DamageIssued = damageProgressValue;
            if (((CPlayerDamageOverTime *)(damageEffect))->m_FramesRemaining <= zero) {
                scaledTotalDamage = ((CPlayerDamageOverTime *)(damageEffect))->m_TotalDamage * damageUnitScale;
                if (damageProgressValue < scaledTotalDamage) {
                    frameDamage += scaledTotalDamage - damageProgressValue;
                }
            }
            damageSource = ((CPlayerDamageOverTime *)(damageEffect))->m_pDamageSource;
            if (damageSource != 0 && *(u8 *)damageSource == 1 &&
                (((DamageSourceFlagsView *)(damageSource))->flags & 0x300000) &&
                (((DamageSourceFlagsView *)(damageSource))->statusFlags & 0x200)) {
                frameDamage *= g_playerDamageTimerFrameScale.value;
            }
            if (((CPlayerDamageOverTime *)(damageEffect))->m_bIsInflator != 0) {
                Playerai_AddReactionReserve(actor, 0.0933333337f, ((CPlayerDamageOverTime *)(damageEffect))->m_pDamageSource);
                if ((f32)((PlayerDamageVisualState *)(actor))->health <= frameDamage) {
                    frameDamage = g_playerDamageTimerFrameDefault.value;
                }
            }
            Barrel_FillDamagePacket((void *)&damage, (s32)((CPlayerDamageOverTime *)(damageEffect))->m_pDamageSource,
                          (s32)frameDamage, 25.599998f, 0x100080, 0);
            Playerai_ApplyDamagePacket(actor, &((PlayerDamageVisualState *)(actor))->damageState, (void *)&damage);
        }
        i++;
        damageEffectOffset += 24;
    } while (i < 5);
}

/* Transfers a randomly selected inventory quantity into an empty recipient slot. */


void Player_TransferRandomInventoryItems(Inventory *inventory, Receiver *receiver) {
 s32 amount;
 s32 index;
 s32 value;
 void *scan;
 if (receiver->amount == 0) {
  amount = 15;
  index = Graphu64_NextRandom()%3;
  value = inventory->items[index];
  if (value<16) amount = value;
  if (amount == 0) {
   Graphu64_NextRandom();
   scan = inventory;
   for (index = 0;index<3;index++) {
    s16 item = inventory->items[index];
    if (item>0) { s32 v = item; if (amount<v) v = amount; amount = v; }
   }
   index = 2;
  }
  if (amount != 0) {
   inventory->items[index] -= amount;
   receiver->index = index;
   receiver->amount = amount;
  }
 }
}

/* Gives a player an amount of one ammunition type and announces it: the count of that type
   rises by the amount up to the type's maximum (none for type -1, the character's table in
   multiplayer, otherwise g_baseAmmoCapacities plus the profile's bonus bytes in g_localPlayerProfiles unless ammunition is
   unlimited), and the message "<amount> <type name>" with a plural suffix for more than one
   is built and shown through Playerai_PostMessageHistoryEntry. */


static inline s32 max_ammo(SharedPlayer *player, s32 type) {
    s32 max;

    if (type == -1) {
        return 0;
    }
    if (g_gameSettings.controllerMode != 1) {
        max = player->views18.view18_4.character->caps[type];
    } else {
        max = g_baseAmmoCapacities[type];
        if (player->views1450.view1450_3.unlimited == 0) {
            if (type == 0) {
                max += g_localPlayerProfiles[player->views1C.view5D4_47.profile].bonus0;
            } else if (type == 1) {
                max += g_localPlayerProfiles[player->views1C.view5D4_47.profile].bonus1;
            } else if (type == 2) {
                max += g_localPlayerProfiles[player->views1C.view5D4_47.profile].bonus2;
            }
        }
    }
    return max;
}

void Player_GiveAmmoWithMessage(SharedPlayer *player, s32 type, s32 amount) {
    char number[8];
    char message[32];

    if (amount != 0) {
        player->views5E8.view5F4_12.ammo[type] = ((player->views5E8.view5F4_12.ammo[type] + amount) < (max_ammo(player,
            type)) ? (player->views5E8.view5F4_12.ammo[type] + amount) : (max_ammo(player, type)));
        XPlus_FormatDecimalInteger(amount, number);
        XPlus_CopyString(message, number);
        XPlus_AppendString(message, s_ammoPickupMessageSeparator);
        XPlus_AppendString(message, Weapon_GetIndexedTableValue(type));
        if (amount >= 2) {
            XPlus_AppendString(message, s_ammoPickupPluralSuffix);
        }
        Playerai_PostMessageHistoryEntry(player, message, 1.0f);
    }
}

extern char s_ammoPickupMessageSeparator[4];
extern char s_ammoPickupPluralSuffix[4];

/* Decreases a float field0 by the given amount, clamps it from below at a floor, and when it reaches the floor
 * builds and dispatches an event. Adapted from Playerai_AddReactionReserve, with the add, the clamp direction,
 * the constant, the third argument (a field plus 0x1900), and a duplicated clamp assignment (which keeps the
 * constant reloaded rather than held in a register) changed. */


void Player_DrainReserveAndDamage(void *actor, f32 amount, void *damageSource) {
    Slot damage;
    f32 reserveValue;
    f32 clampedReserve;

    reserveValue = ((Player *)actor)->reserve - amount;
    clampedReserve = g_playerReserveBounds_de[1];
    if (!(reserveValue <= clampedReserve)) {
        if (actor != 0) {
            clampedReserve = reserveValue;
        } else {
            clampedReserve = reserveValue;
        }
    }
    reserveValue = g_playerReserveBounds_de[1];
    ((Player *)actor)->reserve = clampedReserve;
    if (clampedReserve <= reserveValue) {
        Barrel_FillDamagePacket(&damage, damageSource, ((LevelActor *)actor)->active + 6400, 25.599998f, 128, 0);
        Playerai_ApplyDamagePacket(actor, &((LevelActor *)actor)->behaviorFlags, &damage);
    }
}

/** Adds the argument scaled by g_playerImpulseScale to the object's float and sets bit 0x2000 in its word. */

void Player_AddImpulse(void *actorView, f32 amount) {
    ((Player *)actorView)->impulse = ((Player *)actorView)->impulse + amount * g_playerImpulseScale;
    ((Player *)actorView)->reactionFlags = ((Player *)actorView)->reactionFlags | 0x2000;
}


void Playerai_PostMessageHistoryEntry(void *player, u8 *message, f32 size) {
    s32 count;
    s32 messageCameraAddress;

    count = ((Player *)player)->messageIndex + 1;
    ((Player *)player)->messageIndex = count;
    if (count == 5) {
        ((Player *)player)->messageIndex = 0;
    }
    XPlus_CopyString(((Player *)player)->messageHistory[((Player *)player)->messageIndex], message);
    messageCameraAddress = (s32)((Player *)player)->camera;
    if (messageCameraAddress != 0) {
        Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, messageCameraAddress,
                      ((Player *)player)->messageHistory[((Player *)player)->messageIndex],
                      size);
    }
}

int Player_ReturnOne(void) {
    return 1;
}

void Playerai_BeginHeldAlternateFire(struct SharedPlayer *actor) {
    if (actor->views5E8.view1210_152.marker == 0) {
        Player_SetPlayerState(actor, actor, 39);
        actor->views5E8.view1210_152.marker = 1;
        actor->views5E8.view1214_154.markerState = 0;
    }
}

void Playerai_EndHeldAlternateFire(void *actor) {
    if ((((struct PlayerAlternateFireStateView *) actor)->alternateFireMarker) != 0) {
        if ((((struct PlayerAlternateFireStateView *) actor)->health) != 0) {
            Player_SetPlayerState(actor, actor, 2);
        }
        (((struct PlayerAlternateFireStateView *) actor)->alternateFireMarker) = 0;
        (((struct PlayerAlternateFireStateView *) actor)->alternateFireMarkerState) = 0;
    }
}

/** Return the linked record with the greatest eight-slot score excluding itself. */
void *Playerai_FindHighestScoringOtherPlayer(Context *context) {
    ScoredPlayerRecord *node;
    ScoredPlayerRecord *base;
    ScoredPlayerRecord *bestNode = 0;
    int best = -1;

    node = context->head;
    if (node != 0) {
        base = context->base;
        do {
            unsigned int own = (unsigned int)((u8 *)node - (u8 *)base) / sizeof(ScoredPlayerRecord);
            int score = 0;
            int i;
            for (i = 0; i < 8; i++) {
                if (i == own) {
                    continue;
                }
                score += node->scores->value[i];
                if (best < score) {
                    best = score;
                    bestNode = node;
                }
            }
            node = node->next;
        } while (node != 0);
    }
    return bestNode;
}

/** Read the global word. */

int Playerai_GetPlayerCount(void) {
    return g_playerCount;
}

void Playerai_UpdateGroundDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartViewSavingDrowningDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 50); }

void Playerai_UpdateDrowningDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartQuicksandDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 30); }

void Playerai_UpdateQuicksandDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartLavaDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 40); }

void Playerai_UpdateLavaDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartExplosiveDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 11); }

void Playerai_UpdateExplosiveDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartDisabledCrawlDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 12); }

void Playerai_UpdateCrawlDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartRunningDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 13); }

void Playerai_UpdateRunningDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartBackwardMovingDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 14); }

void Playerai_UpdateBackwardMovingDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartClimbingDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 15); }

void Playerai_UpdateClimbingDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartFallingDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 20); }

void Playerai_UpdateFallingDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartPrimagenDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 70); }

void Playerai_UpdatePrimagenDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartImpalementDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 60); }

void Playerai_UpdateImpalementDeathSequenceWait(void *sequencePlayer) { Playerai_UpdateSequenceWait(sequencePlayer); }

void Playerai_StartChestbursterDeathSequence(void *player, void *sequenceActor) { Playerai_TryStartPlayerSequence(player, sequenceActor, 71); }

/** Thin wrapper around Playerai_UpdateSequenceWait. */
void Playerai_UpdateChestbursterDeathSequenceWait(void *sequencePlayer) {
    Playerai_UpdateSequenceWait(sequencePlayer);
}

/** Thin wrapper around Playerai_TryStartPlayerSequence with player fixed third argument. */
void Playerai_StartSwimmingChestbursterDeathSequence(void *player, void *sequenceActor) {
    Playerai_TryStartPlayerSequence(player, sequenceActor, 72);
}

/** Thin wrapper around Playerai_UpdateSequenceWait. */
void Playerai_UpdateSwimmingChestbursterDeathSequenceWait(void *sequencePlayer) {
    Playerai_UpdateSequenceWait(sequencePlayer);
}

/** Thin wrapper around Playerai_TryStartPlayerSequence with player fixed third argument. */
void Playerai_StartRaptorChestbursterDeathSequence(void *player, void *sequenceActor) {
    Playerai_TryStartPlayerSequence(player, sequenceActor, 73);
}

/** Thin wrapper around Playerai_UpdateSequenceWait. */
void Playerai_UpdateRaptorChestbursterDeathSequenceWait(void *sequencePlayer) {
    Playerai_UpdateSequenceWait(sequencePlayer);
}

/** Thin wrapper around Playerai_TryStartPlayerSequence with player fixed third argument. */
void Playerai_StartSwimmingRaptorChestbursterDeathSequence(void *player, void *sequenceActor) {
    Playerai_TryStartPlayerSequence(player, sequenceActor, 74);
}

/** Thin wrapper around Playerai_UpdateSequenceWait. */
void Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait(void *sequencePlayer) {
    Playerai_UpdateSequenceWait(sequencePlayer);
}

void Playerai_InitializeActorModelEffect(void *effectPlayerState, void *sourceActor) {
    char *effectPlayer = (char *)effectPlayerState;
    s32 actorModelEntry;
    CVector3 modelEffectOffset;
    CVector3 effectDisplacement;

    actorModelEntry = InstHdr_FindActorModelEntry(sourceActor);
    ((Player *)effectPlayerState)->effectModel = (void *)actorModelEntry;
    if (actorModelEntry != 0) {
        ((Player *)effectPlayerState)->modelState = 0;
        ((Player *)effectPlayerState)->effectPosition.x = ((LevelActor *)sourceActor)->position0.x;
        ((Player *)effectPlayerState)->effectPosition.y = ((LevelActor *)sourceActor)->position0.y;
        ((Player *)effectPlayerState)->effectPosition.z = ((LevelActor *)sourceActor)->position0.z;
        modelEffectOffset.x = ((ModelBlend *)actorModelEntry)->effectOffset.x;
        modelEffectOffset.y = ((ModelBlend *)actorModelEntry)->effectOffset.y;
        modelEffectOffset.z = ((ModelBlend *)actorModelEntry)->effectOffset.z;
        Graphu64_SubtractVectors(&effectDisplacement, &modelEffectOffset, &((Player *)effectPlayerState)->effectPosition);
        effectDisplacement.y = 0.0f;
        ((Player *)effectPlayerState)->modelDistance = Graphu64_GetHorizontalAngle(&effectDisplacement);
    }
}

void Playerai_ClearPlayerWeaponLock(void *lockedPlayerState) {
    struct Player *player = lockedPlayerState;
    TeamSelect_EmptyWeaponWheelHook(&player->weaponBusy);
    player->locked = 0;
}

void Playerai_EnterMovingSequenceState(void *player, void *body) {
    struct SharedPlayer *sharedPlayer = (struct SharedPlayer *)player;

    Playerai_UpdateMountedMovement(player, body);
    if (sharedPlayer->views5E8.view6C0_51.movementSpeed != 0.0f) {
        Player_SetPlayerState(player, body, 37);
    }
}

void Playerai_ResetPlayerWeaponLock(void *lockedPlayerState) {
    struct Player *player = lockedPlayerState;
    TeamSelect_EmptyWeaponWheelHook(&player->weaponBusy);
    player->locked = 0;
}

void Playerai_EnterStoppedSequenceState(void *player, void *body) {
    struct SharedPlayer *sharedPlayer = (struct SharedPlayer *)player;

    Playerai_UpdateMountedMovement(player, body);
    if (sharedPlayer->views5E8.view6C0_51.movementSpeed == 0.0f) {
        Player_SetPlayerState(player, body, 36);
    }
}

void Playerai_OffsetActorForForceMarker(Actor126 *actor, Object126 *positionedObject) {
    Object126 *object;
    f32 angle;
    f32 object_angle;
    f32 sine;
    f32 cosine;

    actor->flags |= 0x800000;
    actor->value1D4 = k_playeraiForceMarkerActorOffset;
    if (actor->state652 == 15) {
        object = positionedObject;
        object_angle = object->angle;
        angle = g_playerForceMarkerTilt;
        sine = Gu_Sinf(object_angle + angle);
        cosine = Math_Cosf(object->angle + angle);
        sine *= g_playerForceMarkerBasisScale;
        cosine *= g_playerForceMarkerBasisScale;
        object->x += sine;
        object->y += cosine;
        object->angle += actor->offset728;
        actor->offset728 = 0.0f;
    }
}

/* Eases a player's crouch depth: the target is g_playerCrouchDepthAndMinimumFall[0] while input bits 0xC0000 are
   held or crouching is forced (which also enters state 4 unless already in it) and zero
   otherwise; the depth moves a quarter of the way through Graphu64_EaseValueToward, steps smaller than
   g_playerCrouchDepthAndMinimumFall[1] downward or g_playerCrouchMinimumRiseAndBaseClearance[0] upward are dropped, and bit 0x80 of the flags is set while
   g_playerCrouchMinimumRiseAndBaseClearance[1] less the depth lies within g_playerCrouchClearanceMinimum to g_playerCrouchClearanceMaximum,
       cleared otherwise. */


struct CCollisionInfo2_t;


/* Updates a player's charge effect: cancels the charge and moves its effect to state 3 when the
   current weapon's entry in g_weaponInfoByType has no ammunition, the charge is off, or g_resultExitPending is set with
   the player's controller flag; while the button is held and charging it targets
   g_playerWeaponChargeBlendTarget, then runs the effect through Playerai_EmptyWeaponEffectHook, eases the level toward the target by half
   through Graphu64_EaseValueToward and clears a level below g_playerWeaponChargeBlendCutoff once the target is zero. */


/* Returns whether the entry Scene_GetModelRecordByIndexPointer finds in g_world_AchieveUpdateresultsscreen for an object's key exists
   and has bit 6 of its flags set. */


/* Returns the constant after g_playerForceMarkerBasisScale less the cube of its difference from the argument. */

f32 Playerai_EvaluateCubicComplement(f32 curveInput) {
    f32 inputComplement = g_playerCubicComplementUnit - curveInput;
    return g_playerCubicComplementUnit - (inputComplement * inputComplement * inputComplement);
}

void Playerai_InitializeStateBlendTarget(Player *player) {
    float initialBlendValue = player->pitchBias;
    float blendTarget = g_playerStateBlendTarget;
    player->pitchBlendProgress = 0;
    player->pitchBlendStart = initialBlendValue;
    player->pitchBlendTarget = blendTarget;
}

void Playerai_InitializeStateBlendToZero(Player *player) {
    float initialBlendValue = player->pitchBias;
    player->pitchBlendTarget = 0;
    player->pitchBlendProgress = 0;
    player->pitchBlendStart = initialBlendValue;
}

/** Perform the no-op hook. */
void Playerai_EmptyHandlerAfterInitializeStateBlendToZero_de(void) {
}

/* Reports whether the object's float is above the constant after g_playerStateBlendTarget. */

s32 Playerai_IsSpeedAboveThreshold(Player *actor) {
    f32 field = actor->crouchDepth;
    f32 konst = g_playerSpeedThreshold;
    s32 result = 1;
    if (!(konst < field)) {
        result = 0;
    }
    return result;
}

void Playerai_UpdateCrouchClearance(Player *player, LevelActor *actor, s32 eventArg, s32 *flags) {
    s32 held;
    s32 crouch;
    f32 target;
    f32 depth;
    f32 step;
    f32 clearance;
    f32 moved;
    f32 lo;

    held = actor->motionState & 0xC0000;
    crouch = held != 0;
    if (player->forceCrouch != 0) {
        crouch = 1;
        if (player->pose != 4) {
            Player_SetPlayerState(player, actor, 4);
        }
    }
    target = 0.0f;
    if (crouch) {
        target = g_playerCrouchDepthAndMinimumFall[0];
    }
    depth = player->crouchDepth;
    Graphu64_EaseValueToward(&depth, target, 0.25f);
    do {
        step = depth - player->crouchDepth;
        if (step < 0.0f) {
            if (-step < g_playerCrouchDepthAndMinimumFall[1]) {
                goto still;
            }
        } else if (step < g_playerCrouchMinimumRiseAndBaseClearance[0]) {
        still:
            step = 0.0f;
        }
        moved = player->crouchDepth + step;
        clearance = g_playerCrouchMinimumRiseAndBaseClearance[1] - moved;
        lo = g_playerCrouchClearanceMinimum;
    } while (0);
    player->crouchDepth = moved;
    if (lo <= clearance && clearance <= g_playerCrouchClearanceMaximum) {
        *flags |= 0x80;
    } else {
        *flags &= ~0x80;
    }
}

void Playerai_UpdateActionTransitionBlend(Player *actor) {
    f32 easedBlend;
    f32 targetBlend;
    f32 blendStep;

    targetBlend = 0.0f;
    if ((u32)((u16)actor->pose - 9) < 4U) {
        targetBlend = g_playerActionBlendTargetAndMinimumStep[0];
    }
    easedBlend = actor->eyeOffset;
    Graphu64_EaseValueToward(&easedBlend, targetBlend, 0.25f);
    blendStep = easedBlend - actor->eyeOffset;
    if (blendStep < 0.0f) {
        if (-blendStep < g_playerActionBlendTargetAndMinimumStep[1]) {
            goto clamp;
        }
    } else if (blendStep < g_playerActionBlendMinimumRise) {
clamp:
        blendStep = 0.0f;
    }
    actor->eyeOffset = actor->eyeOffset + blendStep;
}

void Playerai_AdjustHeightForCollision(Player *player, LevelActor *actor) {
    CVector3 next;
    f32 actorBaseOffset;
    f32 collisionHeight;
    f32 actorHeight;
    f32 actorRadius;
    f32 actorReach;
    f32 heightAdjustment;

    heightAdjustment = (((((ModelBlend *)(player->definition))->height -
                    player->cameraOffset) -
                   player->crouchDepth) -
                  player->eyeOffset) -
                 player->heightDelta;
    if (heightAdjustment > 0.0f) {
        actorReach = InstHdr_GetActorReach(actor);
        actorRadius = Gobjinst_GetActorRadius(actor);
        actorHeight = Gobjinst_GetActorHeight(actor);
        actorBaseOffset = InstHdr_GetActorBaseOffset(actor);
        next.x = actor->position0.x;
        next.y = actor->position0.y + heightAdjustment;
        next.z = actor->position0.z;
        if (Unicol_SweepActorMotion(actor, actor->position0, next,
                           &g_playerCollisionProbe, actorReach, actorRadius, actorHeight,
                           actorBaseOffset) != 0) {
            collisionHeight = (*(CVector3 *)&g_collisionCurrentActor->vecE4).y - actor->position0.y;
            player->previousPosition.y -= heightAdjustment - collisionHeight;
            heightAdjustment = collisionHeight;
        }
    }
    player->heightDelta += heightAdjustment;
}

void Playerai_UpdateWeaponEffectBlend(void *player) {
    f32 target;
    char *effect;
    s32 state;

    target = 0.0f;
    effect = &((PlayerWeaponChargeEffectView *)(player))->effect;
    if (((struct WeaponChargeAmmunitionView *)(g_weaponInfoByType[((PlayerWeaponChargeEffectView *)(player))->weaponType]))->ammunition <= 0
        || ((PlayerWeaponChargeEffectView *)(player))->chargeEnabled == 0
        || (g_gameSettings.counters.m_bFragTagOn != 0
                && ((struct FragTagProfileFlagView *) ((PlayerWeaponChargeEffectView *) player)->profile)->fragTagEnabled != 0)) {
        do {
            ((PlayerWeaponChargeEffectView *)(player))->chargeEnabled = 0;
            state = ((Shared_Effect *)(effect))->state;
        } while (0);
        if (state != 0 && state != 3) {
            ((Shared_Effect *)(effect))->state = 3;
        }
    }
    if (((PlayerWeaponChargeEffectView *)(player))->chargeRequested != 0 && ((PlayerWeaponChargeEffectView *)(player))->chargeEnabled != 0) {
        target = g_playerWeaponChargeBlendTarget;
        ((PlayerWeaponChargeEffectView *)(player))->chargeEnabled = 1;
    }
    ((PlayerWeaponChargeEffectView *)(player))->chargeBlendTarget = target;
    Playerai_EmptyWeaponEffectHook(&((PlayerWeaponChargeEffectView *)(player))->effect, player);
    Graphu64_EaseValueToward(&((PlayerWeaponChargeEffectView *)(player))->chargeBlend, target, 0.5f);
    if (target == 0.0f && ((PlayerWeaponChargeEffectView *)(player))->chargeBlend < g_playerWeaponChargeBlendCutoff) {
        ((PlayerWeaponChargeEffectView *)(player))->chargeBlend = 0.0f;
    }
}

void Playerai_ApplyRangedPitchToMatrix(void *matrix, void *poseEvent) {
    PlayerRangedPitchLimits *range;
    PlayerRangedPitchStateView *actor;
    s32 value;
    f32 amount;

    PlayerRangedPitchEventView *event = poseEvent;
    LevelActor *object;

    range = event->pitchLimits;
    value = event->eventIndex;
    if (value < range->firstEventIndex) {
        return;
    }
    if (range->lastEventIndex < value) {
        return;
    }

    object = event->actor;
    actor = object->controller;
    amount = -actor->rangedPitch;
    if (actor->action == 15) {
        amount += g_playerBodyFlagStatePitchOffset;
    }
    PitchMatrix(matrix, amount / (f32)range->pitchDivisor);
}

s32 Playerai_HasLinkedWorldFlagSix(struct LinkedWorldFlagsView *object) {
    struct EntryPlayerHasLinkedWorldFlagSix *entry;

    if (object->flags != 0) {
        entry = Scene_GetModelRecordByIndexPointer(&g_world, object->flags);
        if (entry != 0 && (entry->flags & 0x40)) {
            return 1;
        }
    }
    return 0;
}

void Playerai_UpdateTeamScore(TargetSelectionObj *scoringPlayer, TargetSelectionObj *otherPlayer, s32 mode) {
    CGameStatus *counters = &g_gameSettings.counters;
    s32 teamA;
    s32 teamB;
    s32 *win;
    s32 *loss;
    s32 off;
    s32 *wins;
    s32 *losses;

    if (counters->teams != 0) {
        teamA = scoringPlayer->slot->team;
        teamB = otherPlayer->slot->team;
        if (teamA >= 0) {
          if (teamA < 5) {
            off = teamA * 4;
            wins = counters->scores;
            win = &wins[teamA];
            losses = counters->counts;
            loss = &losses[teamA];
            switch (mode) {
            case 0:
                if (counters->m_bCTFOn == 0 && counters->m_bFragTagOn == 0) {
                    *win -= 1;
                }
                break;
            case 1:
                if (teamB != teamA) {
                    *win += 1;
                }
                break;
            case 3:
                *loss += 1;
                break;
            case 2:
                if (teamB != teamA) {
                    *win += 1;
                    break;
                }
                *win -= 1;
                break;
            }
          }
        }
    }
}

void Player_InitializeProfile(void *profileStorage) {
    u8 *object = (u8 *)profileStorage;
    s32 i;
    u8 *cursor;

    XPlus_FillMemory(object, 0, 8);
    ((Profile *)object)->fresh = 0;
    Player_SetProfileValue14(object, 0);
    Player_SetProfileValue15(object, 0);
    Player_SetProfileValue16(object, 0);
    Player_SetProfileProgress(object, 0);
    Player_SetProfileSlotValue(object, 0, 2);
    Player_SetProfileSlotValue(object, 1, 2);
    Player_SetProfileSlotValue(object, 2, 2);
    Player_SetProfileSlotValue(object, 3, 2);
    Player_SetProfileSlotValue(object, 4, 2);
    Player_SetProfileSlotValue(object, 5, 2);
    Player_SetProfileSlotValue(object, 6, 2);
    Player_SetProfileSlotValue(object, 7, 2);
    Player_SetProfileSlotValue(object, 8, 2);
    Player_SetProfileSlotValue(object, 9, 2);
    Player_SetProfileSlotValue(object, 10, 2);
    Player_SetProfileSlotValue(object, 17, 2);
    Player_SetProfileSlotValue(object, 18, 2);
    ((Profile *)object)->count = 0;
    ((Profile *)object)->slot = 0;
    ((Profile *)object)->totals[2] = 0;
    ((Profile *)object)->totals[0] = 0;
    ((Profile *)object)->totals[1] = 0;
    ((Profile *)object)->rank = 0;
    ((Profile *)object)->time = 0;
    ((Profile *)object)->owner = 0;
    ((Profile *)object)->player = -1;
    XPlus_FillMemory(((Profile *)object)->plays, 0, 36);
    XPlus_FillMemory(&((Profile *)object)->groupFlags, 0, 1);
    XPlus_FillMemory(&((Profile *)object)->achievementFlags[7], 0, 3);
    XPlus_FillMemory(((Profile *)object)->slotLevels, 0, 100);
    Player_SetAchievementFlag7((s32)object, 0);
    Player_SetAchievementFlag7((s32)object, 5);
    Player_SetAchievementFlag7((s32)object, 7);
    XPlus_FillMemory(&((Profile *)object)->kindFlags[3], 0, 20);
    XPlus_FillMemory(((Profile *)object)->kindFlags, 0, 3);
    XPlus_FillMemory(((Profile *)object)->achievementFlags, 0, 7);
    XPlus_FillMemory(&((Profile *)object)->resetByte, 0, 1);
    XPlus_FillMemory(&((Profile *)object)->unlockFlags[0], 0, 2);
    Player_SetAchievementFlag2F((s32)object, 0);
    Player_SetAchievementFlag2F((s32)object, 2);
    Player_SetAchievementFlag2F((s32)object, 3);
    Player_SetAchievementFlag2F((s32)object, 4);
    XPlus_FillMemory(&((Profile *)object)->unlockFlags[2], 0, 2);
    XPlus_FillMemory(((Profile *)object)->levelFlags[0], 0, 5);
    XPlus_FillMemory(((Profile *)object)->levelFlags[2], 0, 5);
    XPlus_FillMemory(((Profile *)object)->levelFlags[3], 0, 5);
    XPlus_FillMemory(((Profile *)object)->levelFlags[1], 0, 5);
    i = 35;
    do {
        ((Profile *)object)->times[i] = 0;
        i--;
    } while (i >= 0);
    XPlus_FillMemory(&((Profile *)object)->trackFlags, 0, 1);
    ((Profile *)object)->setting[1] = 1;
    ((Profile *)object)->setting[2] = 134;
    ((Profile *)object)->setting[0] = 0;
    ((Profile *)object)->setting[3] = 132;
    ((Profile *)object)->setting[4] = 0;
}



void Player_InitializeProfileSlot(s32 profileSlot) {
    AiProfile *config;

    Player_InitializeProfile(&g_localPlayerProfiles[profileSlot]);
    g_localPlayerProfiles[profileSlot].time = 0;
    g_localPlayerProfiles[profileSlot].player = profileSlot;
    g_localPlayerProfiles[profileSlot].owner = 0;
    g_localPlayerProfiles[profileSlot].fresh = 1;
    XStdio_FormatBuffer(g_localPlayerProfiles[profileSlot].name, g_profileSlotNameFormat, profileSlot + 1);
    config = (AiProfile *)((u8 *)g_playerSettings + profileSlot * sizeof(Shared_PlayerSettingsRecord));
    g_localPlayerProfiles[profileSlot].setting[0] = config->controlMode;
    g_localPlayerProfiles[profileSlot].setting[1] = config->pitchMode;
    g_localPlayerProfiles[profileSlot].setting[2] = config->yawSensitivity;
    g_localPlayerProfiles[profileSlot].setting[3] = config->sensitivity;
    g_localPlayerProfiles[profileSlot].setting[4] = config->weaponWheelMode;
}

void Player_SetProfileValue14(void *profileStorage, unsigned char value) {
    ((Profile *)profileStorage)->bonus2 = value;
}

/** Advance the byte by ten. */
void Player_AddTenToProfileValue14(void *object) {
    ((Profile *)object)->bonus2 += 10;
}

/** Read the byte. */
unsigned char Player_GetProfileValue14(Profile *profileStorage) {
    return profileStorage->bonus2;
}

/** Store a byte in the object field. */
void Player_SetProfileValue15(void *object, unsigned char value) {
    ((Profile *)object)->bonus0 = value;
}

int Player_AddFiftyToProfileValue15(void *player) {
    int raisedBonus = ((Profile *)player)->bonus0 + 50;
    ((Profile *)player)->bonus0 = (unsigned char)raisedBonus;
    return raisedBonus;
}

unsigned char Player_GetProfileValue15(Profile *profileStorage) {
    return profileStorage->bonus0;
}

/** Store the supplied byte. */
void Player_SetProfileValue16(void *object, unsigned char value) {
    ((Profile *)object)->bonus1 = value;
}

int Player_AddFiftyToProfileValue16(void *player) {
    int raisedBonus = ((Profile *)player)->bonus1 + 50;
    ((Profile *)player)->bonus1 = (unsigned char)raisedBonus;
    return raisedBonus;
}

/** Read the object byte. */
unsigned char Player_GetProfileValue16(Profile *object) {
    return object->bonus1;
}

void Player_SetProfileProgress(void *profileStorage, int progress) {
    ((Profile *)profileStorage)->progress = progress;
}

/** Advance the word by 0x500. */
void Player_AdvanceProfileProgress(void *object) {
    ((Profile *)object)->progress += 1280;
}

/** Return the word stored. */
unsigned int Player_GetProfileProgress(Profile *object) {
    return object->progress;
}

/* Stores a byte into the object's slot table: indices 0 to 10 directly, 17 and 18 into
   slots 11 and 12, and other indices are ignored. */

void Player_SetProfileSlotValue(Profile *profile, int index, char value) {
    if (index == 17) {
        goto is17;
    }
    if (index < 18) {
        goto below18;
    }
    if (index == 18) {
        goto is18;
    }
    return;
below18:
    if (index >= 11) {
        return;
    }
    if (index < 0) {
        return;
    }
    goto store;
is18:
    index = 12;
    goto store;
is17:
    index = 11;
store:
    profile->levelProgress[index] = value;
}

/* Increments the object's byte counter for a slot in the table: indices 0 to 10 directly,
   17 and 18 as slots 11 and 12, and other indices are ignored. */

void Player_IncrementLevelProgress(Profile *profile, int index) {
    if (index == 17) {
        goto is17;
    }
    if (index < 18) {
        goto below18;
    }
    if (index == 18) {
        goto is18;
    }
    return;
below18:
    if (index >= 11) {
        return;
    }
    if (index < 0) {
        return;
    }
    goto store;
is18:
    index = 12;
    goto store;
is17:
    index = 11;
store:
    profile->levelProgress[index]++;
}

s32 Player_GetLevelProgress(Profile *profile, s32 index) {
    if (index == 17) {
        goto slot17;
    }
    if (index < 18) {
        goto lower;
    }
    if (index == 18) {
        goto slot18;
    }
    goto invalid;
lower:
    if (index >= 11) { goto invalid; }
    if (index < 0) { goto invalid; }
    goto load;
slot17:
    index = 11;
    goto load;
slot18:
    index = 12;
    goto load;
invalid:
    return 2;
load:
    return profile->levelProgress[index];
}


void Player_SetAchievementFlag2F(Profile *player, s32 achievementIndex) {
    Defs_SetBitValue(player->unlockFlags, achievementIndex, 1);
}

s32 Player_HasProfileUnlockFlag(u8 *profileBytes, s32 unlockIndex)
{
  if (unlockIndex == 16)
  {
    return 1;
  }
  if (unlockIndex == 17)
  {
    if (unlockIndex || profileBytes)
    {
      return 1;
    }
    else
    {
      return 1;
    }
  }
  return Defs_TestBit(((Profile *)profileBytes)->unlockFlags, unlockIndex);
}

void Player_SetAchievementFlagByIndex(Profile *player, s32 achievementIndex) {
    u8 *achievementBits;
    s32 mappedAchievementIndex = achievementIndex;

    switch (mappedAchievementIndex) {
    case 16:
        achievementBits = &player->resetByte;
        mappedAchievementIndex = 0;
        break;
    case 17:
        achievementBits = &player->resetByte;
        mappedAchievementIndex = 1;
        break;
    default:
        achievementBits = &player->unlockFlags[2];
        break;
    }
    Defs_SetBitValue(achievementBits, mappedAchievementIndex, 1);
}

s32 Player_GetProfileAchievementFlag(Profile *profile, s32 achievementIndex) {
    u8 *achievementBits;
    s32 index = achievementIndex;

    switch (index) {
    case 16:
        achievementBits = &profile->resetByte;
        index = 0;
        break;
    case 17:
        achievementBits = &profile->resetByte;
        index = 1;
        break;
    default:
        achievementBits = &profile->unlockFlags[2];
        break;
    }
    return Defs_TestBit(achievementBits, index);
}

void Player_SetAchievementFlag7(Profile *record, s32 achievementIndex) {
    Defs_SetBitValue(&record->achievementFlags[7], achievementIndex, 1);
}

/** Tests bit index of the profile achievement flags at +7 (the character unlocks). */
s32 Player_TestAchievementFlag7(Profile *record, s32 index) {
    return Defs_TestBit(&record->achievementFlags[7], index);
}

void Player_BuildWeaponHandTransform(char *weaponActor) {
    CVector3 position;
    Matrix worldMatrix;
    CVector3 scaledOffset;
    CVector3 handOffset;
    Matrix offsetMatrix;
    Matrix viewMatrix;
    CQuatern viewOrientation;
    char *object;
    char *orientation;

    object = ((PlayerProfileAttachmentView *)(weaponActor))->owner;
    handOffset = ((struct WeaponHandOffsetView *) g_weaponInfoByType[((PlayerProfileWeaponView *) object)->selectedAction])->handOffset;
    if (g_weaponHandMirrorX != 0) {
        handOffset.x = -handOffset.x;
    }
    if (g_weaponHandMirrorY != 0) {
        handOffset.y = -handOffset.y;
    }
    if (g_weaponHandMirrorZ != 0) {
        handOffset.z = -handOffset.z;
    }
    Graphu64_ScaleVector(&scaledOffset, &((PlayerProfileAttachmentView *)(weaponActor))->scale, 0.1f);
    Graphu64_BuildScaleMatrix(&offsetMatrix, scaledOffset.x, scaledOffset.y, scaledOffset.z);
    Graphu64_ScaleVector(&handOffset, &handOffset, -10.24f);
    if (((PlayerProfileWeaponView *)(object))->camera.v0 != 0) {
        Graphu64_GetMatrixTranslation(&((GameplayCamera *)((PlayerProfileWeaponView *)object)->camera.v1)->viewOrient, &position);
        MatrixFromQuaternion((CQuatern *)(&((GameplayCamera *)((PlayerProfileWeaponView *)object)->camera.v1)->orientation),
                      &worldMatrix);
    } else {
        Player_BuildPlayerViewTransform(object, &viewMatrix);
        Player_BuildPlayerOrientation(object, &viewOrientation);
        Graphu64_GetMatrixTranslation((char *)&viewMatrix, &position);
        MatrixFromQuaternion(&viewOrientation, &worldMatrix);
    }
    orientation = (char *)&((LevelActor *)weaponActor)->transform;
    TranslateMatrix(&offsetMatrix, handOffset.x, handOffset.y, handOffset.z);
    SwapMatrixUpForward(&offsetMatrix);
    Graphu64_MultiplyAffineMatrices((Matrix *)orientation, &offsetMatrix, &worldMatrix);
    TranslateMatrix((Matrix *)orientation, position.x, position.y, position.z);
}

#if defined(VERSION_US_REV1)

/* Rates read by Playerai_UpdateTargetFacing and Playerai_UpdateReactionReserve. */

/* Linker fill between the rate and the next constant: no instruction reads it and the other builds hold other words here. */

/* Mirror flags read by Player_BuildWeaponHandTransform, followed by two unread zero words. */
extern s32 g_weaponHandMirrorX;
extern s32 g_weaponHandMirrorY;
extern s32 g_weaponHandMirrorZ;
/* Unused zero words after the mirror flags; no instruction reads it. */
extern s32 g_weaponHandMirrorZeroTail[2];

extern f32 k_PlayeraiInitializeplayerhealthNegativeOffset;

/* Base state table of the weapon fire state machine (Weapon_InitializeFireStateCallbacks installs it). */

/* Spin weapon states searched before the base table. */

/* Trigger release weapon states searched before the base table. */
#endif


#if defined(VERSION_US_REV1)
const float k_aiStepAndDiagonalFloats[4] = {
    0.05f, 0.3f, -0.7071f, 0.7071f,
};
#endif

#if defined(VERSION_DE)
const float g_playerDamageStunIncrement[4] = {
    0.05f, 0.3f, -0.7071f, 0.7071f,
};
#endif

#if defined(VERSION_US)
const float g_playerDamageStunIncrement[] = {
    0.05f, 0.3f, -0.7071f, 0.7071f,
};
#endif

#if defined(VERSION_EU)
const float g_playerDamageStunIncrement[4] = {
    0.05f, 0.3f, -0.7071f, 0.7071f,
};
#endif


#if defined(VERSION_EU_X)
const float g_playerDamageStunIncrement[4] = {
    0.05f, 0.3f, -0.7071f, 0.7071f,
};
#endif

const Shared_HeightBonuses g_playerDeathHeightOffsets = {
    10.23999977f,
    81.91999817f,
};
const float g_playerDeathMotionCenter = 512.0f;
const float g_playerDeathMovingSpeed = 5.119999886f;


#if defined(VERSION_US) || defined(VERSION_US_REV1)
const float k_PlayerApplyplayerdamageData[3] = {
    0.06666667f, 1.0f, 51.199997f,
};
#endif

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
const float k_playerApplyPlayerDamageConstants[3] = {
    0.06666667f, 1.0f, 51.199997f,
};
#endif

const float k_PlayeraiComputeaimrotationHalfWords[1] = {
    0.5f,
};


#if defined(VERSION_US_REV1)
const float g_playerSwimConstants[34] = {
    2.048f, 0.1f, 0.0625f, 1.0f,
    -1.0f, 0.78539824f, 1e+02f, -9e+01f,
    9e+01f, 0.017453294f, 11.25f, 1.5707965f,
    3.141593f, -1.5707965f, 3.141593f, 6.2831855f,
    384.0f, 1.5707965f, 3.141593f, -1.5707965f,
    3.141593f, 0.06981318f, 6.144f, 20.48f,
    20.48f, 4.096f, 6.144f, 20.48f,
    20.48f, 4.096f, 8.4375f, 0.1f,
    1.5707964f, 1.5f,
};
#endif

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const f32 g_playerClimbMovementConstantsGerman[34] = {
    2.0480001f, 0.100000001f, 0.0625f, 1.0f, -1.0f, 0.785398245f,
    100.0f, -90.0f, 90.0f, 0.0174532942f, 11.25f, 1.57079649f,
    3.14159298f, -1.57079649f, 3.14159298f, 6.28318548f, 384.0f, 1.57079649f,
    3.14159298f, -1.57079649f, 3.14159298f, 0.069813177f, 6.14400005f, 20.4799995f,
    20.4799995f, 4.09600019f, 6.14400005f, 20.4799995f, 20.4799995f, 4.09600019f,
    8.4375f, 0.100000001f, 1.57079637f, 1.5f,
};
#endif


const float g_playerTravelSequenceConstantWordsUsRevision[5] = {
    6.2831855f, 6.2831855f, 0.2f, 0.2f,
    4.0f,
};

const float g_playerRideMovementConstantWordsUsRevision[16] = {
    0.2792527f, 1.0f, 0.01f, 0.06f,
    8e+01f, 0.017453294f, 8.0f, 9e+01f,
    0.5f, 2.5f, 2.5f, 5e+01f,
    1.0f, 10.24f, 10.24f, 15.0f,
};

const float k_PlayeraiFindtransientplayerMaxFiniteFloatWords[1] = {
    3.4028235e+38f,
};

const float k_PlayeraiFindnearestliveplayerMaxFiniteFloatWords[1] = {
    3.4028235e+38f,
};


#if defined(VERSION_DE)
#if defined(VERSION_DE)
const f32 k_hudSpriteLeadHorizontalOffset = -132.0f;
#endif
#endif

#if defined(VERSION_DE)
extern float k_constantsFragment[6];
#endif

#if defined(VERSION_EU)
#if defined(VERSION_EU)
const f32 k_hudSpriteLeadHorizontalOffset = -132.0f;
#endif
#endif

#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
const f32 k_hudSpriteLeadHorizontalOffset = -132.0f;
#endif
#endif

#if defined(VERSION_EU_X)
extern float k_linktablesFragment[6];
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
const f32 k_hudSpriteLeadHorizontalOffset = -132.0f;
#endif
#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
const f32 k_hudSpriteLeadHorizontalOffset = -132.0f;
#endif
#endif


#if !defined(VERSION_US_REV1)
extern float g_aiDistanceBounds[2];
#endif



#if defined(VERSION_US_REV1)

/* Rates read by Playerai_UpdateTargetFacing and Playerai_UpdateReactionReserve. */
extern f32 g_playerTargetFacingEaseRate;
extern f32 g_playerReactionReserveApproachRate;

/* Linker fill between the rate and the next constant: no instruction reads it and the other builds hold other words here. */
extern u32 g_playerReactionReserveApproachRateLinkerFill[2];

extern f32 k_PlayeraiInitializeplayerhealthUnit;

extern struct WeaponAnimationChoice g_weaponAnimationChoicesA[5];

extern struct WeaponAnimationChoice g_weaponAnimationChoicesB[5];

extern struct WeaponAnimationChoice g_weaponAnimationChoicesC[5];

/* Mirror flags read by Player_BuildWeaponHandTransform, followed by two unread zero words. */

/* Base state table of the weapon fire state machine (Weapon_InitializeFireStateCallbacks installs it). */

/* Spin weapon states searched before the base table. */

/* Trigger release weapon states searched before the base table. */
#endif


#if defined(VERSION_DE)
#if defined(VERSION_DE)
extern struct {
    f32 targetFacingEaseRate;
    f32 reactionReserveApproachRate;
    s16 precedingAnimationTriples[6];
    f32 aimScale;
    s16 weaponAnimationDurationPairs[30];
    s32 handMirrorAxesAndFlags[5];
    f32 weaponRestOffset;
    void * nextTable;
    u32 stateTableHeaderReserved[7];
    s32 state0Id;
    RomCallbackWord state0Enter;
    RomCallbackWord state0Update;
    u32 state0Reserved;
    s32 state0Animation;
    f32 state0Rate;
    s32 state0Threshold;
    u32 state0Flags;
    s32 state1Id;
    RomCallbackWord state1Enter;
    RomCallbackWord state1Update;
    u32 state1Reserved;
    s32 state1Animation;
    f32 state1Rate;
    s32 state1Threshold;
    u32 state1Flags;
    s32 state2Id;
    RomCallbackWord state2Enter;
    RomCallbackWord state2Update;
    u32 state2Reserved;
    s32 state2Animation;
    f32 state2Rate;
    s32 state2Threshold;
    u32 state2Flags;
    s32 state3Id;
    RomCallbackWord state3Enter;
    RomCallbackWord state3Update;
    u32 state3Reserved;
    s32 state3Animation;
    f32 state3Rate;
    s32 state3Threshold;
    u32 state3Flags;
    s32 state4Id;
    RomCallbackWord state4Enter;
    RomCallbackWord state4Update;
    u32 state4Reserved;
    void * state4AnimationList;
    f32 state4Rate;
    s32 state4Threshold;
    u32 state4Flags;
    s32 state5Id;
    RomCallbackWord state5Enter;
    RomCallbackWord state5Update;
    u32 state5Reserved;
    void * state5AnimationList;
    f32 state5Rate;
    s32 state5Threshold;
    u32 state5Flags;
    s32 state6Id;
    RomCallbackWord state6Enter;
    RomCallbackWord state6Update;
    u32 state6Reserved;
    s32 state6Animation;
    f32 state6Rate;
    s32 state6Threshold;
    u32 state6Flags;
    s32 state7Id;
    RomCallbackWord state7Enter;
    RomCallbackWord state7Update;
    u32 state7Reserved;
    s32 state7Animation;
    f32 state7Rate;
    s32 state7Threshold;
    u32 state7Flags;
    void * table8Next;
    u32 table8HeaderReserved[7];
    s32 state9Id;
    RomCallbackWord state9Enter;
    RomCallbackWord state9Update;
    u32 state9Reserved;
    s32 state9Animation;
    f32 state9Rate;
    s32 state9Threshold;
    u32 state9Flags;
    s32 state10Id;
    RomCallbackWord state10Enter;
    RomCallbackWord state10Update;
    u32 state10Reserved;
    s32 state10Animation;
    f32 state10Rate;
    s32 state10Threshold;
    u32 state10Flags;
    s32 state11Id;
    RomCallbackWord state11Enter;
    RomCallbackWord state11Update;
    u32 state11Reserved;
    s32 state11Animation;
    f32 state11Rate;
    s32 state11Threshold;
    u32 state11Flags;
    s32 state12Id;
    RomCallbackWord state12Enter;
    RomCallbackWord state12Update;
    u32 state12Reserved;
    s32 state12Animation;
    f32 state12Rate;
    s32 state12Threshold;
    u32 state12Flags;
    void * table13Next;
    u32 table13HeaderReserved[7];
    s32 state14Id;
    RomCallbackWord state14Enter;
    RomCallbackWord state14Update;
    u32 state14Reserved;
    s32 state14Animation;
    f32 state14Rate;
    s32 state14Threshold;
    u32 state14Flags;
    s32 state15Id;
    RomCallbackWord state15Enter;
    RomCallbackWord state15Update;
    u32 state15Reserved;
    s32 state15Animation;
    f32 state15Rate;
    s32 state15Threshold;
    u32 state15Flags;
    s32 state16Id;
    RomCallbackWord state16Enter;
    RomCallbackWord state16Update;
    u32 state16Reserved;
    s32 state16Animation;
    f32 state16Rate;
    s32 state16Threshold;
    u32 state16Flags;
    s32 state17Id;
    RomCallbackWord state17Enter;
    RomCallbackWord state17Update;
    u32 state17Reserved;
    s32 state17Animation;
    f32 state17Rate;
    s32 state17Threshold;
    u32 state17Flags;
    s32 state18Id;
    RomCallbackWord state18Enter;
    RomCallbackWord state18Update;
    u32 state18Reserved;
    s32 state18Animation;
    f32 state18Rate;
    s32 state18Threshold;
    u32 state18Flags;
} g_weaponSwitchStateWordsDe __attribute__((aligned(4)));
typedef char g_weaponSwitchStateWordsDeSizeCheck[(sizeof(g_weaponSwitchStateWordsDe) == 748) ? 1 : -1];
#endif
#endif
