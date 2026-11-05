#include "Common/ai_behaviour_types.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/integerstate2c.h"
#include "Common/player_sequence_state.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Ai/Nav/portal_loadcollisiontable.h"
#include "Render/setn64_getpacksection.h"
#include "Ai/Nav/portal_dispatchactorbehavior_data.h"
#include "Particle/particle_releaseownerlistoneeffects.h"
#include "Portal/portal__player.h"
#include "Render/particle_spawninterpolatedtrail.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Ai/Cbarrel/barrel_getsignedangletopoint.h"
#include "Ai/ai_shared_symbols.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Engine/Instance/insthdr.h"
#include "Engine/Instance/gobjinst.h"
#include "Engine/Unicol/unicol.h"
#include "Common/approachlocation.h"
#include "Ai/ai_functions.h"
#include "include_asm.h"
#include "Common/navigation_graph.h"
#include "Common/world.h"
#include "Ai/Nav/portal_linknavigationobjects.h"
#include "Common/listheader.h"
#include "Common/navigation_node_and_route_views.h"
#include "Ai/Player/scaled_updatetargetpitch.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Engine/scene_findtrackedactors.h"
#include "Common/triple.h"
#include "Ai/nav_symbols.h"
#include <platform_sdk.h>
#include "Ai/Nav/nav_setpickupgoalweights.h"
#include "Ai/Nav/portal.h"
#include "Ai/Nav/Route/route.h"
#include "Common/self.h"
#include "Ai/Nav/portal_initsearchnode.h"
#include "Common/pooled_floats.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Ai/cbarrel.h"
#include "Ai/Nav/farthest.h"

/* Runs a computer player's engagement timer: while the countdown is positive it rerolls the
   wait as the config's base at 8 plus a random share (scale g_timedActionWaitRandomScale) of its spread
   and counts down; at zero it counts the opponents in range through Particle_CountOwnerListOneEffects (three counting as
   the whole wait) and either sets the waiting flag while fewer than the wait or starts pursuit with
   the countdown at -1 and a wait from the config's alternating wait base and spread (scale g_alternatingActionWaitRandomScale); during pursuit
   the wait runs down, ends early once the player is within g_alternatingActionTargetRange of its target on the target's
   height, and when it reaches zero sets the pursuit-ended flag and acts through Portal_InitializeRandomActionSettings. Written in the style of
   Portal_UpdateMeterGatedActionBurst with the random scale loaded into a local first. */




struct EffectSystem;


struct LevelActor;


void Portal_DispatchActorBehavior(void *controller)
{
    /* Dispatch the current actor mode through its per-type behavior table. */
    void *state;
    s32 mode;
    s32 type;
    Player *actor;

    state = controller;
    if (state == 0) {
        return;
    }
    actor = *(Player **)state;
    if (0.0f < actor->cooldown) {
        return;
    }

    mode = actor->actorParts[1].gear;
    type = actor->selectedAction;
    mode -= 1;
    {
        u32 dispatch = *(&g_actorBehaviorDispatchModes[0] + mode + type * 2);
        if (dispatch >= 9) {
            return;
        }
        switch (dispatch) {
        case 0: goto case_0;
        case 1: goto case_0;
        case 2: goto case_0;
        case 3: goto case_0;
        case 4: goto case_1;
        case 5: goto case_3;
        case 6: goto case_5;
        case 7: goto case_4;
        case 8: goto case_2;
        }
    }
case_0:
        Portal_UpdateTimedActionBurst(state, (char *)&((AiConfig *)&g_actorBehaviorActionConfigs)[type] + mode * ((char *)&((AiConfig *)0)->alternateDelayBase - (char *)0));
        goto dispatched;
case_1:
        Portal_UpdateHeldActionBurst(state, (char *)&((AiConfig *)&g_actorBehaviorActionConfigs)[type] + mode * ((char *)&((AiConfig *)0)->alternateDelayBase - (char *)0));
        goto dispatched;
case_2:
        ((CountedEffectActionState *)state)->actionFlagFrames = 1;
        goto dispatched;
case_3:
        Portal_UpdateAlternatingActionBursts(state, &((AiConfig *)&g_actorBehaviorActionConfigs)[type]);
        goto dispatched;
case_4:
        Portal_UpdateCountedEffectAction(state, &((AiConfig *)&g_actorBehaviorActionConfigs)[type]);
        goto dispatched;
case_5:
        Portal_UpdateMeterGatedActionBurst(state, &((AiConfig *)&g_actorBehaviorActionConfigs)[type]);
case_6:
case_7:
case_8:
dispatched:

    if (((CountedEffectActionState *)state)->actionFlagFrames > 0) {
        ((Player *)(*(void **)state))->actionFlags |= 0x4000;
        ((Player *)(*(void **)state))->inputFlags |= 0x4000;
        ((CountedEffectActionState *)state)->actionFlagFrames -= 1;
    }
}

void Portal_UpdateAlternatingActionBursts(AiController *controller, AiConfig *aiConfig)
{
    s32 remainingTicks;
    f32 randomRangeOrAngleLimit;
    f32 scaledActionDuration;
    f32 randomBurstScale;
    s32 nextActionDelay;

    remainingTicks = controller->alternateCountdown;
    if (remainingTicks > 0) {
        remainingTicks = remainingTicks - 1;
        controller->alternateCountdown = remainingTicks;
        if (remainingTicks == 0) {
            randomRangeOrAngleLimit = g_actionBurstRandomRange;
            if (Graphu64_RandomFloat(randomRangeOrAngleLimit) < g_actionBurstAlternateChance) {
                controller->alternateCountdown = -1;
                controller->actionDelay = aiConfig->alternateDelayBase;
                controller->actionDelay = (s32) ((f32) controller->actionDelay
                    + (Graphu64_RandomFloat(randomRangeOrAngleLimit) * (f32) aiConfig->alternateDelaySpread));
                controller->actionDuration = aiConfig->alternateDurationBase;
                controller->actionDuration = (s32) ((f32) controller->actionDuration
                    + (Graphu64_RandomFloat(randomRangeOrAngleLimit) * (f32) aiConfig->alternateDurationSpread));
            } else {
                controller->alternateCountdown = aiConfig->alternateCountdownBase;
                controller->alternateCountdown = (s32) ((f32) controller->alternateCountdown
                    + (Graphu64_RandomFloat(randomRangeOrAngleLimit) * (f32) aiConfig->alternateCountdownSpread));
            }
        }
    }
    if (controller->alternateCountdown == -1) {
        remainingTicks = controller->actionDuration - 1;
        controller->actionDuration = remainingTicks;
        if (remainingTicks == 0) {
            randomRangeOrAngleLimit = g_actionBurstRestartRandomRange;
            controller->alternateCountdown = aiConfig->alternateCountdownBase;
            controller->alternateCountdown = (s32) ((f32) controller->alternateCountdown
                + (Graphu64_RandomFloat(randomRangeOrAngleLimit) * (f32) aiConfig->alternateCountdownSpread));
            controller->actionDelay = aiConfig->primaryDelayBase;
            controller->actionDelay = (s32) ((f32) controller->actionDelay
                + (Graphu64_RandomFloat(randomRangeOrAngleLimit) * (f32) aiConfig->primaryDelaySpread));
            controller->actionDuration = aiConfig->primaryDurationBase;
            scaledActionDuration = (f32) controller->actionDuration
                + (Graphu64_RandomFloat(randomRangeOrAngleLimit) * (f32) aiConfig->primaryDurationSpread);
            controller->actionFlagFrames = 0;
            controller->actionDuration = (s32) scaledActionDuration;
        } else {
            controller->actionFlagFrames = 1;
        }
    }
    remainingTicks = controller->actionDelay;
    if (remainingTicks > 0) {
        controller->actionDelay = remainingTicks - 1;
        return;
    }
    if (controller->actionFlagFrames > 0) {
        nextActionDelay = aiConfig->alternateDelayBase;
        randomBurstScale = Graphu64_RandomFloat(g_actionBurstAlternateDelayRandomRange);
        if (1) {
            randomRangeOrAngleLimit = g_actionBurstAlternateAngleLimit;
            nextActionDelay = (s32) ((f32) nextActionDelay + (randomBurstScale * (f32) aiConfig->alternateDelaySpread));
        }
    } else {
        nextActionDelay = aiConfig->primaryDelayBase;
        nextActionDelay = (s32) ((f32) nextActionDelay + (Graphu64_RandomFloat(g_actionBurstPrimaryDelayRandomRange) * (f32) aiConfig->primaryDelaySpread));
        randomRangeOrAngleLimit = g_actionBurstPrimaryAngleLimit;
    }
    {
        AiTarget *aiTarget = controller->target;
        Player *targetPlayer = aiTarget->player;
        if (!(randomRangeOrAngleLimit < Barrel_GetSignedAngleToPoint(controller->player,
                                    targetPlayer->pos))) {
            controller->fireRequested = 1;
            controller->actionDelay = nextActionDelay;
        }
    }
}

void Portal_UpdateCountedEffectAction(CountedEffectActionState *controller, CountedEffectActionConfig *config) {
    s32 count;
    char *target;
    CVector3 pos;
    f32 range;
    f32 scale;

    if (controller->phaseCountdown > 0) {
        scale = g_timedActionWaitRandomScale;
        controller->waitTimer = config->firstWaitBase;
        controller->waitTimer =
            (f32) controller->waitTimer
            + Graphu64_RandomFloat(scale) * (f32) config->firstWaitSpread;
        controller->phaseCountdown -= 1;
        return;
    }
    if (controller->phaseCountdown == 0) {
        count = Particle_CountOwnerListOneEffects(&g_actorParticleEffectSystem[0], *(void **) controller);
        if (count == 3) {
            controller->waitTimer = count;
        }
        if (count < controller->waitTimer) {
            controller->effectCountShortfallFlag = 1;
            return;
        }
        controller->phaseCountdown = -1;
        scale = g_alternatingActionWaitRandomScale;
        controller->waitTimer = config->secondWaitBase;
        controller->waitTimer =
            (f32) controller->waitTimer
            + Graphu64_RandomFloat(scale) * (f32) config->secondWaitSpread;
        return;
    }
    controller->waitTimer -= 1;
    target = ((LevelActor *)controller->targetView)->controller;
    Particle_AverageOwnerEffectPositions(&g_actorParticleEffectSystem[0], *(void **) controller, &pos);
    range = g_alternatingActionTargetRange;
    pos.y = ((Player *)target)->pos.y;
    if (Graphu64_GetSquaredDistance(&pos, &((Player *)(target))->pos) < range) {
        controller->waitTimer = 0;
    }
    if (controller->waitTimer == 0) {
        controller->actionFlagFrames = 1;
        Portal_InitializeRandomActionSettings(controller, config);
    }
}

void Portal_UpdateMeterGatedActionBurst(void *object, void *settings) {
    AiController *controller = object;
    AiConfig *aiConfig = settings;
    s32 timer;
    s32 minus_one;
    Player *record;
    f32 distance;

    if (controller == 0) {
        return;
    }

    timer = controller->alternateCountdown;
    if (timer == 0) {
        f32 value;

        Particle_FindNearestForeignEffectDistance(&g_actorParticleEffectSystem[0], controller->player, &value);
        if (value < g_meterActionEffectDistanceLimit) {
            f32 chanceBase = g_meterActionChanceBase;
            f32 threshold = Graphu64_RandomFloat(g_meterActionChanceRandomRange) + chanceBase;

            if ((f32) aiConfig->meterThreshold < threshold) {
                s32 base = aiConfig->alternateDurationBase;
                controller->actionFlagFrames =
                    (s32) ((f32) base + Graphu64_RandomFloat(chanceBase) * (f32) aiConfig->alternateDurationSpread);
            }
            controller->alternateCountdown = aiConfig->meterCooldownBase;
            controller->alternateCountdown =
                (s32) ((f32) controller->alternateCountdown +
                       Graphu64_RandomFloat(chanceBase) * (f32) aiConfig->meterCooldownSpread);
            controller->alternateCountdown += controller->actionFlagFrames;
        }
    } else {
        controller->alternateCountdown = timer - 1;
    }

    timer = controller->actionDelay;
    if (timer > 0) {
        controller->actionDelay = timer - 1;
        return;
    }
    minus_one = -1;
    if (timer == minus_one) {
        controller->fireRequested = 1;
        controller->actionDuration += minus_one;
    } else {
        record = controller->target->player;
        distance = Barrel_GetSignedAngleToPoint(controller->player,
                                 record->pos);
        if (Portal_GetEngagementDistance(controller) < distance) {
            return;
        }
        controller->fireRequested = 1;
        controller->actionDelay = minus_one;
    }
    if (controller->actionDuration == 0) {
        controller->fireRequested = 0;
        Portal_InitializeRandomActionSettings(controller, aiConfig);
    }
}

void Portal_LoadCollisionTable(void *resourcePack) {
    s32 queryInPair;
    s32 destinationOffset;
    s32 pairIndex;
    s32 pairByteOffset;
    s32 firstSectionOfPair;
    char *configTable;
    CollisionQuery *sourceQuery;
    char *destination;

    pairIndex = 0;
    configTable = &g_actorBehaviorActionConfigs;
    pairByteOffset = 0;
    do {
        queryInPair = 0;
        firstSectionOfPair = pairIndex * 2;
        destinationOffset = pairByteOffset;
        do {
            sourceQuery = SetN64_GetPackSection(resourcePack, firstSectionOfPair + queryInPair);
            destination = (char *)(destinationOffset + (s32)configTable);
            *(CollisionQuery *)destination = *sourceQuery;
            queryInPair += 1;
            destinationOffset += 28;
        } while (queryInPair < 2);
        pairIndex += 1;
        pairByteOffset += 56;
    } while (pairIndex < 22);
}

void Portal_UpdateTimedActionBurst(void *controller, void *settings) {
    s32 timer;
    s32 minus_one;
    Player *record;
    f32 distance;

    if (controller == 0) {
        return;
    }
    Portal_UpdateRandomActionPulse(controller, settings);
    timer = ((AiController *)controller)->actionDelay;
    if (timer > 0) {
        ((AiController *)controller)->actionDelay = timer - 1;
        return;
    }
    minus_one = -1;
    if (timer == minus_one) {
        ((AiController *)controller)->fireRequested = 1;
        ((AiController *)controller)->actionDuration += minus_one;
    } else {
        record = ((AiController *)controller)->target->player;
        distance = Barrel_GetSignedAngleToPoint(((AiController *)controller)->player, record->pos);
        if (Portal_GetEngagementDistance(controller) < distance) {
            return;
        }
        ((AiController *)controller)->fireRequested = 1;
        ((AiController *)controller)->actionDelay = minus_one;
    }
    if (((AiController *)controller)->actionDuration == 0) {
        ((AiController *)controller)->fireRequested = 0;
        Portal_InitializeRandomActionSettings(controller, settings);
    }
}

void Portal_UpdateHeldActionBurst(void *controller, void *settings) {
    AiController *brain = controller;
    s32 timer;
    Player *record;
    f32 distance;

    if (controller == 0) {
        return;
    }
    Portal_UpdateRandomActionPulse(controller, settings);
    timer = brain->actionDelay;
    if (timer > 0) {
        brain->actionDelay = timer - 1;
        return;
    }
    if (timer == 0) {
        brain->fireRequested = 1;
        brain->actionDuration -= 1;
    }
    if (brain->actionDuration != 0) {
        return;
    }
    brain->actionDelay = -1;
    record = brain->target->player;
    distance = Barrel_GetSignedAngleToPoint(brain->player, record->pos);
    if (Portal_GetEngagementDistance(controller) < distance) {
        brain->fireRequested = 1;
        return;
    }
    brain->fireRequested = 0;
    Portal_InitializeRandomActionSettings(controller, settings);
}

void Portal_UpdateRandomActionPulse(void *controller, void *settings) {
    AiController *randomPulseController = controller;
    AiConfig *pulseSettings = settings;
    s32 timer = randomPulseController->alternateCountdown;

    if (timer == 0) {
        if (randomPulseController->fireRequested == 0 && randomPulseController->actionFlagFrames <= 0) {
            f32 chanceBase = g_actionPulseChanceBase;
            f32 threshold = Graphu64_RandomFloat(g_actionPulseChanceRandomRange) + chanceBase;

            if ((f32) pulseSettings->pulseChancePercent < threshold) {
                randomPulseController->actionFlagFrames = 1;
                Portal_InitializeRandomActionSettings(controller, settings);
            }
            randomPulseController->alternateCountdown = pulseSettings->alternateCountdownBase;
            randomPulseController->alternateCountdown =
                (s32) ((f32) randomPulseController->alternateCountdown +
                       Graphu64_RandomFloat(chanceBase) * (f32) pulseSettings->alternateCountdownSpread);
        }
    } else {
        randomPulseController->alternateCountdown = timer - 1;
    }
}

void Portal_InitializeRandomActionSettings(void *object, void *settings) {
    AiController *controller = object;
    AiConfig *aiConfig = settings;
    f32 randomRange = g_actionSettingsRandomRange;

    controller->actionDelay = aiConfig->primaryDelayBase;
    controller->actionDelay = (s32) ((f32) controller->actionDelay + (Graphu64_RandomFloat(randomRange) * (f32) aiConfig->primaryDelaySpread));
    controller->actionDuration = aiConfig->primaryDurationBase;
    controller->actionDuration = (s32) ((f32) controller->actionDuration + (Graphu64_RandomFloat(randomRange) * (f32) aiConfig->primaryDurationSpread));
    if (aiConfig->pulseChancePercent == 100) {
        controller->actionFlagFrames = 1;
    }
}

/* Returns the difference between the constant after g_actionSettingsRandomRange and Scaled_GetDifficultyEngagementAdjustment's result, scaled by
   g_portalEngagementScale. */



/* Find the nearest world object matching each active target ID, clearing its active flag when no object is close enough. */


f32 Portal_GetEngagementDistance(AiController *controller) {
    return (g_portalEngagementBase - Scaled_GetDifficultyEngagementAdjustment(controller)) * g_portalEngagementScale;
}


/* Give every platform-flagged search node the nearest moving platform and the
 * nearest point on it: a route platform (mode 4) offers each of its route points, any other platform
 * its base and its top (base + height, pushed out by radius along heading when radial). A node with
 * no platform loses its 0x200 flag. */


/* Collisions the actor would meet moving to a point (61.44 above it), without committing the move: the actor's header is saved and
 * restored around the trial move. */
/* Collects the points one portal away from a point, with the portal joining each; returns how many. */
/* Picks the controller's next point: follows a queued point when the actor may take it, otherwise the nearest reachable neighbour
 * (special portals and drops first while within the starting height). */

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif





#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif







/* Returns the difference between the constant after g_actionSettingsRandomRange and Scaled_GetDifficultyEngagementAdjustment's result, scaled by
   g_portalEngagementScale. */



/* Find the nearest world object matching each active target ID, clearing its active flag when no object is close enough. */


void Portal_LinkNavigationObjects(Shared_Arg0 *graph)
{
  f32 candidateDistance;
  f32 nearestDistance;
  f32 emptyDistance;
  s32 *pointStorage;
  s32 actorByteOffset;
  s32 actorIndex;
  u32 candidateObjectId;
  u32 compare_id;
  Shared_WeaponSlot *candidateActor;
  NavigationPoint *navigationPoint;
  Shared_Node *searchNode;
  Shared_WeaponSlot *nearestActor;
  Shared_World *ww;
  searchNode = graph->searchNodes;
  ww = &g_world;
  if (searchNode != 0)
  {
    emptyDistance = g_navigationObjectLinkDistanceLimits[0];
    do
    {
      pointStorage = graph->pointStorage;
      navigationPoint = (NavigationPoint *) (&((NavigationRawByteStorage *) pointStorage)->bytes[(searchNode->nodeKey * (*pointStorage)) + 8]);
      if (navigation_point_flags(navigationPoint) & 1)
      {
        nearestDistance = g_navigationObjectLinkDistanceLimits[1];
        nearestActor = 0;
        if (navigation_point_object_id(navigationPoint) != 1619)
        {
          actorIndex = 0;
          if (actorIndex < ww->actorCapacity)
          {
            actorByteOffset = 0;
            do
            {
              candidateActor = (Shared_WeaponSlot *) (&((NavigationRawByteStorage *) ww->actors)->bytes[actorByteOffset]);
              compare_id = navigation_point_object_id(navigationPoint);
              if (compare_id == 1614)
              {
                candidateObjectId = candidateActor->objectId;
                goto compare;
              }
              if (((u32) (candidateActor->objectId - 1603)) >= 2U)
              {
                goto advance;
              }
              candidateObjectId = Scene_GetModelIdAtIndex(ww, candidateActor->model->modelIndex);
              compare_id = navigation_point_object_id(navigationPoint);
              compare:
              if (candidateObjectId == compare_id)
              {
                candidateDistance = Graphu64_GetPointDistance(navigationPoint, &candidateActor->positionBytes);
                if ((candidateDistance < nearestDistance) || (nearestDistance == emptyDistance))
                {
                  if (navigationPoint)
                  {
                    nearestDistance = candidateDistance;
                    nearestActor = candidateActor;
                  }
                  else
                  {
                    nearestDistance = candidateDistance;
                    nearestActor = candidateActor;
                  }
                }
              }

              advance:
              actorByteOffset += 744;

            }
            while ((++actorIndex) < ww->actorCapacity);
          }
          if (nearestActor != 0)
          {
            if (nearestDistance < g_navigationObjectLinkDistanceLimits[2])
            {
              searchNode->linkedActor = nearestActor;
              goto next_node;
            }
          }
          searchNode->linkedActor = 0;
          navigation_point_clear_flags(navigationPoint, 1);
        }
      }
      next_node:
      searchNode = searchNode->next;

    }
    while (searchNode != 0);
  }
}

/* Give every platform-flagged search node the nearest moving platform and the
 * nearest point on it: a route platform (mode 4) offers each of its route points, any other platform
 * its base and its top (base + height, pushed out by radius along heading when radial). A node with
 * no platform loses its 0x200 flag. */
void Portal_AssignPlatformEndpoints(CNavData *graph) {
    NavigationPlatform *platforms[30];
    CVector3 chosenPosition, start, end;
    NavigationSearchNode *node;
    NavigationPoint *point;
    NavigationPlatform **slot;
    NavigationPlatform *candidate, *actor, *chosen;
    ActorMotionState *motion;
    ActorMotionDefinition *definition;
    PlatformRoute *route;
    CVector3 *position;
    f32 distance, best;
    s32 count, i, j, k, n;

    for (k = 29; k >= 0; k--) {
        platforms[k] = 0;
    }
    count = 0;
    for (n = 0; n < g_navigationPlatformActorCount; n++) {
        candidate = &g_navigationPlatformActors[n];
        if (candidate->objectId == 1602) {
            slot = &platforms[count];
            *slot = candidate;
            count++;
        }
    }
    for (node = graph->searchNodes.head; node != 0; node = node->next) {
        point = navigationRecord(graph->points, node->key);
        if (navigation_point_flags(point) & 0x200) {
            chosen = 0;
            best = -1.0f;
            for (i = 0; i < count; i++) {
                actor = platforms[i];
                motion = &actor->motion;
                definition = &actor->resource->motion;
                if (motion->mode == 4) {
                    route = Scene_GetPlatformRoute(&g_world, motion->route);
                    if (route != 0) {
                        for (j = 0; j < route->count; j++) {
                            position = Scene_GetPlatformRoutePoint(&g_world, motion->route, j);
                            distance = Graphu64_GetPointDistance(point, position);
                            if (distance < best || best == -1.0f) {
                                chosen = platforms[i];
                                best = distance;
                                chosenPosition = *position;
                            }
                        }
                    }
                } else {
                    start = motion->base;
                    end = motion->base;
                    end.y += definition->height;
                    if (definition->radial != 0) {
                        end.x += definition->radius * Gu_Sinf(definition->heading);
                        end.z += definition->radius * Math_Cosf(definition->heading);
                    }
                    distance = Graphu64_GetPointDistance(point, &start);
                    if (distance < best || best == -1.0f) {
                        chosen = platforms[i];
                        best = distance;
                        chosenPosition = start;
                    }
                    distance = Graphu64_GetPointDistance(point, &end);
                    if (distance < best || best == -1.0f) {
                        chosen = platforms[i];
                        best = distance;
                        chosenPosition = end;
                    }
                }
            }
            if (chosen != 0) {
                node->platform = chosen;
                node->endpoint = chosenPosition;
            } else {
                node->platform = 0;
                navigation_point_clear_flags(point, 0x200);
            }
        }
    }
}

s32 Insthdr_IsInactiveOrCollisionOption4(void *actor);

/* Collisions the actor would meet moving to a point (61.44 above it), without committing the move: the actor's header is saved and
 * restored around the trial move. */
static __inline__ s32 navigationBlocked(Player *actor, CNavData *graph, s32 index) {
    CVector3 position;
    CollisionQuery query;
    u8 saved[80];
    s32 mode, result;
    position = ((NavigationPoint *)navigationRecord(graph->points, index))->position;
    position.y += 61.44f;
    if (actor->kind == 1 && (actor->weaponFlags & 0x300000)) {
        query = g_portalAlternateCollisionQuery;
    } else {
        mode = Insthdr_GetModelCollisionFlag1(actor);
        if (Insthdr_IsInactiveOrCollisionOption4(actor) == 0) {
            if (mode != 0) query = g_portalModeCollisionQuery;
            else query = g_portalAlternateCollisionQuery;
        } else if (Insthdr_GetModelCollisionFlag8(actor) == 0) query = g_portalNoModelFlagCollisionQuery;
        else query = g_portalDefaultCollisionQuery;
    }
    query.w[0] = 0x4000;
    __builtin_memcpy(saved, actor, sizeof(saved));
    result = Unicol_MoveActorWithCollision(actor, position.x, position.y, position.z, &query);
    __builtin_memcpy(actor, saved, sizeof(saved));
    return result;
}
/* Collects the points one portal away from a point, with the portal joining each; returns how many. */
static __inline__ s32 navigationNeighbours(CNavData *graph, s32 current, s32 *targets, s32 *portals) {
    NavigationPortal *portal;
    s32 count = 0;
    s32 i;
    for (i = 0; i < graph->m_nNavLinks; i++) {
        portal = navigationRecord(graph->m_pusNavLinks, i);
        if (portal->first == current) {
            targets[count] = portal->second;
            portals[count] = i;
            count++;
        }
        if (portal->second == current) {
            targets[count] = portal->first;
            portals[count] = i;
            count++;
        }
    }
    return count;
}
/* Picks the controller's next point: follows a queued point when the actor may take it, otherwise the nearest reachable neighbour
 * (special portals and drops first while within the starting height). */
void Portal_UpdateActorCurrentNode(CNavData *graph, Player *actor) {
    s32 targets[64];
    s32 portalIds[64];
    CVector3 delta;
    NavigationPoint *point;
    NavigationPortal *portal;
    s32 climbing, swimming;
    s32 best, target;
    s32 count, found;
    s32 busy, hanging, release;
    s32 i;
    f32 dist, bestDist, height, dy;

    for (i = 0; i < 64; i++) {
        targets[i] = -1;
        portalIds[i] = -1;
    }
    found = 0;
    climbing = actor->movementFlags & 0x2000;
    swimming = actor->movementFlags & 0x1000;
    Graphu64_SubtractVectors(&delta, navigationRecord(graph->points, actor->controller->current), &actor->pos);
    if (climbing || swimming) {
        dist = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
    } else {
        dist = delta.x * delta.x + delta.z * delta.z;
    }
    height = delta.y;
    bestDist = dist;
    if (height < 0.0f) {
        height = -height;
    }
    best = actor->controller->current;
    if (actor->computer != 0 && actor->controller->queue[0] != -1) {
        busy = InstHdr_GetActorMotionState(actor);
        hanging = actor->pose == 15;
        release = busy && !actor->active;
        if (busy || hanging || climbing) {
            if (!release) {
                target = actor->controller->queue[0];
                if (target == -1) {
                    target = actor->controller->mode;
                }
                point = navigationRecord(graph->points, target);
                Graphu64_SubtractVectors(&delta, &point->position, &actor->pos);
                if (climbing || swimming || (navigation_point_flags(point) & 0x200)) {
                    dist = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
                } else {
                    dist = delta.x * delta.x + delta.z * delta.z;
                }
                if (dist < bestDist) {
                    /* within five steps (5 x 61.44) up or down */
                    if (delta.y < 0.0f ? -delta.y < 5 * 61.44f : delta.y < 5 * 61.44f) {
                        actor->controller->previous = actor->controller->current;
                        actor->controller->current = target;
                    }
                }
                return;
            }
            actor->controller->queue[0] = -1;
        }
    }
    count = navigationNeighbours(graph, actor->controller->current, targets, portalIds);
    for (i = 0; i < count; i++) {
        target = targets[i];
        point = navigationRecord(graph->points, target);
        portal = navigationRecord(graph->m_pusNavLinks, portalIds[i]);
        if (!(navigation_attributes(point) & 0x300000) || swimming || climbing) {
            Graphu64_SubtractVectors(&delta, &point->position, &actor->pos);
            if (climbing || swimming) {
                dist = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
            } else {
                dist = delta.x * delta.x + delta.z * delta.z;
            }
            dy = delta.y;
            if (dy < 0.0f) {
                dy = -dy;
            }
            if (portal->kind == 3 || portal->kind == 10 || portal->kind == 5 || (!swimming && (navigation_point_flags(point) & 0x20))) {
                if (dy < height) {
                    if (!found) {
                        bestDist = -1.0f;
                        found = 1;
                    }
                    if (dist < bestDist || bestDist == -1.0f) {
                        if (!navigationBlocked(actor, graph, target)) {
                            bestDist = dist;
                            best = target;
                        }
                    }
                }
            } else if (dist < bestDist) {
                if (!navigationBlocked(actor, graph, target)) {
                    bestDist = dist;
                    best = target;
                }
            }
        }
    }
    if (actor->controller->current != best) {
        actor->controller->previous = actor->controller->current;
    }
    actor->controller->current = best;
}

f32 Graphu64_GetSquaredDistance(f32 *a, f32 *b);



struct CNavData_t;

extern void Portal_SearchPath(CNavData *, NavigationSearchNode *);

s32 Portal_CollectDirectedNeighbors(CNavData *graph, s32 nodeKey, s32 preferredNodeKey, s32 *neighborsOut, s32 reverseDirection) {
    NavigationPoint *point;
    NavigationBuffer *points;
    NavigationBuffer *m_pusNavLinksValue;
    s32 *neighborCursor;
    s32 i;
    s32 neighborCount;
    s32 j;
    s32 linkIndex;
    s32 reverseIsBidirectional;
    s32 forwardIsBidirectional;
    s32 kind;
    s32 reverseKind;
    NavigationPortal *portal;

    if (preferredNodeKey != -1) {
        points = graph->points;
        point = navigationRecord(points, preferredNodeKey);
    } else {
        point = NULL;
    }
    linkIndex = 0;
    neighborCount = 0;
    if (graph->m_nNavLinks > 0) {
        s32 reversibleKind4 = 4;
        s32 reversibleKind1 = 1;
        s32 reversibleKind7 = 7;
        s32 noRoom = -1;
        s32 forwardExcludedKind = 6;
        neighborCursor = neighborsOut;
        do {
            m_pusNavLinksValue = graph->m_pusNavLinks;
            portal = navigationRecord(m_pusNavLinksValue, linkIndex);
            if (reverseDirection != 0) {
                if (portal->second == nodeKey) {
                    neighborCount += 1;
                    *neighborCursor = (s32) portal->first;
                    neighborCursor += 1;
                }
                if (portal->first == nodeKey) {
                    kind = portal->kind;
                    if (kind != reversibleKind4) {
                        if ((s32) kind < 5) {
                            reverseIsBidirectional = 0;
                            if (kind != reversibleKind1) {

                            } else {
                                goto block_14;
                            }
                        } else {
                            reverseIsBidirectional = 0;
                            if (kind == reversibleKind7) {
                                goto block_14;
                            }
                        }
                    } else {
block_14:
                        reverseIsBidirectional = 1;
                    }
                    if (reverseIsBidirectional != 0) {
                        neighborCount += 1;
                        *neighborCursor = (s32) portal->second;
                        neighborCursor += 1;
                    }
                }
                if ((preferredNodeKey != noRoom) && (portal->first == nodeKey) && (portal->second == preferredNodeKey)
                        && (point != NULL) && (navigation_point_flags(point) & 2)) {
                    *neighborCursor = preferredNodeKey;
                    neighborCursor += 1;
                    neighborCount += 1;
                }
            } else {
                if ((portal->first == nodeKey) && (portal->kind != forwardExcludedKind)) {
                    neighborCount += 1;
                    *neighborCursor = (s32) portal->second;
                    neighborCursor += 1;
                }
                if (portal->second == nodeKey) {
                    reverseKind = portal->kind;
                    if (reverseKind != reversibleKind4) {
                        if ((s32) reverseKind < 5) {
                            forwardIsBidirectional = 0;
                            if (reverseKind != reversibleKind1) {

                            } else {
                                goto block_32;
                            }
                        } else {
                            forwardIsBidirectional = 0;
                            if (reverseKind == reversibleKind7) {
                                goto block_32;
                            }
                        }
                    } else {
block_32:
                        forwardIsBidirectional = 1;
                    }
                    if (forwardIsBidirectional != 0) {
                        neighborCount += 1;
                        *neighborCursor = (s32) portal->first;
                        neighborCursor += 1;
                    }
                }
            }
            linkIndex += 1;
        } while (linkIndex < graph->m_nNavLinks);
    }
    if (preferredNodeKey == -1) return neighborCount;
    if (point != 0) {
            for (j = 0; j < neighborCount - 1; j++) {
                for (i = j + 1; i < neighborCount; i++) {
                    NavigationBuffer *table = graph->points;
                    s32 firstIndex = neighborsOut[j] * table->stride;
                    s32 secondIndex = neighborsOut[i] * table->stride;
                    void *first = table->data + firstIndex;
                    void *other = table->data + secondIndex;
                    f32 distance = Graphu64_GetSquaredDistance(&point->position.x, first);
                    if (Graphu64_GetSquaredDistance(&point->position.x, other) < distance) {
                        s32 saved = neighborsOut[j];
                        neighborsOut[j] = neighborsOut[i];
                        neighborsOut[i] = saved;
                    }
                }
            }
    }
    return neighborCount;
}

s32 Portal_SearchRelatedGoalPath(CNavData *obj, s32 key, s32 requested, void *owner) {
    NavigationSearchNode *node;
    s32 found;

    {
        NavigationSearchNode *reset;

        reset = obj->searchNodes.head;
        while (reset != 0) {
            reset->value = g_portalResetSearchValue;
            reset->state = -1;
            reset->extra = 0;
            reset->cost = 0;
            reset->estimate = 0;
            reset->total = 0;
            reset->open = 0;
            reset->goal = 0;
            reset->parent = 0;
            reset = reset->next;
        }
    }

    obj->selected = -1;
    obj->value = g_portalRelatedGoalDefaultValue;
    Route_ClearGoalList(obj);
    found = 0;
    Nav_SetPickupGoalWeights(owner);
    Nav_AddGoalNode((CNavData *)obj, requested);

    {
        s32 i;
        s32 count;
        u32 mask;

        i = found;
        count = obj->m_nNavNodes;
        if (count > 0) {
            mask = 0x04300000;
            do {
            char *record;
            s32 product;

            product = i * count;
            if (i != requested) {
                if (*((product + requested) * obj->links->stride + obj->links->data) != 0) {
                    record = (char *)obj->points +
                             (i * obj->points->stride + 8);
                    if (record != 0 && (((NavigationNodeFlagsView *)(record))->flags.v0 & mask) == 0) {
                        Nav_AddGoalNode((CNavData *)obj, i);
                        found++;
                    }
                }
            }
                i++;
                count = obj->m_nNavNodes;
            } while (i < count);
        }

        if (found == 0) {
            for (i = 0; i < obj->m_nNavNodes; i++) {
                char *record;
                s32 product;

                product = i * obj->m_nNavNodes;
                if (i != requested) {
                    if (*((product + requested) * obj->links->stride + obj->links->data) != 0) {
                        record = (char *)obj->points +
                                 (i * obj->points->stride + 8);
                        if (record != 0 && (((NavigationNodeFlagsView *)(record))->flags.v1 & 0x400) == 0) {
                            Nav_AddGoalNode((CNavData *)obj, i);
                        }
                    }
                }
            }
        }
    }

    node = obj->searchNodes.head;
    if (node == 0) {
        goto not_found;
    }
    do {
        if (node->key == key) {
            goto search_done;
        }
        node = node->next;
    } while (node != 0);
not_found:
    node = 0;
search_done:
    Portal_SearchPath(obj, node);
    return obj->selected = obj->result;
}

s32 Portal_SearchPortalRoute(CNavData *, s32, s32, u8, s32, f32 *, f32);
/* Collects the nodes linked to key, with the link index of each, into out/edges; returns how many. */
static __inline__ s32 navigationNeighbors(CNavData *graph, s32 key, s32 *out, s32 *edges) {
    s32 i;
    s32 count = 0;
    for (i = 0; i < graph->m_nNavLinks; i++) {
        NavigationPortal *portal = navigationRecord(graph->m_pusNavLinks, i);
        if (portal->first == key) {
            out[count] = portal->second;
            edges[count] = i;
            count++;
        }
        if (portal->second == key) {
            out[count] = portal->first;
            edges[count] = i;
            count++;
        }
    }
    return count;
}
/* Returns startNode when one of its own links has portalKind, else the portal node the nearest
 * neighbor route reaches within maxDepth links (-1 when none). */
s32 Portal_FindPortalRoute(CNavData *graph, s32 startNode, u8 portalKind, s32 maxDepth) {
    s32 neighborNodes[64];
    s32 neighborLinks[64];
    f32 distance;
    f32 *origin;
    f32 bestDistance;
    s32 foundNode;
    s32 result;
    s32 index;
    s32 neighborCount;
    NavigationPortal *portal;

    result = -1;
    bestDistance = g_portalSearchInitialBestDistance;
    for (index = 0; index < graph->m_nNavLinks; index++) {
        portal = navigationRecord(graph->m_pusNavLinks, index);
        if (portal->first == startNode && portal->kind == portalKind) return startNode;
    }
    origin = navigationRecord(graph->points, startNode);
    neighborCount = navigationNeighbors(graph, startNode, neighborNodes, neighborLinks);
    for (index = 0; index < neighborCount; index++) {
        distance = Graphu64_GetSquaredDistance(origin, navigationRecord(graph->points, neighborNodes[index]));
        foundNode = Portal_SearchPortalRoute(graph, startNode, neighborNodes[index], portalKind, maxDepth - 1, &distance, bestDistance);
        if (foundNode != -1) {
            bestDistance = distance;
            result = foundNode;
        }
    }
    return result;
}

/* Depth-limited search from currentNode (entered from previousNode): returns currentNode when one of its links
 * has portalKind, else the portal node of the shortest route under distanceLimit (-1 when none); stores that
 * route's length in *routeDistance. */
s32 Portal_SearchPortalRoute(CNavData *graph, s32 previousNode, s32 currentNode, u8 portalKind, s32 remainingDepth, f32 *routeDistance, f32 distanceLimit) {
    s32 neighborNodes[64];
    s32 neighborLinks[64];
    f32 candidateDistance;
    f32 *previousPosition;
    f32 bestDistance;
    s32 result;
    s32 index;
    s32 neighborCount;
    s32 portalNode;
    NavigationPortal *portal;

    bestDistance = g_portalRelatedGoalEmptyDistance;
    result = -1;
    for (index = 0; index < graph->m_nNavLinks; index++) {
        portal = navigationRecord(graph->m_pusNavLinks, index);
        if (portal->first == currentNode && portal->kind == portalKind) return currentNode;
    }
    if (remainingDepth == 0) return -1;
    previousPosition = navigationRecord(graph->points, previousNode);
    neighborCount = navigationNeighbors(graph, previousNode, neighborNodes, neighborLinks);
    for (index = 0; index < neighborCount; index++) {
        f32 *point = navigationRecord(graph->points, neighborNodes[index]);
        if (point != previousPosition) {
            candidateDistance = *routeDistance + Graphu64_GetSquaredDistance(previousPosition, point);
            if (candidateDistance < distanceLimit) {
                portalNode = Portal_SearchPortalRoute(graph, currentNode, neighborNodes[index], portalKind, remainingDepth - 1,
                    &candidateDistance, distanceLimit);
            } else {
                portalNode = -1;
            }
            if (portalNode != -1 && candidateDistance < bestDistance) {
                bestDistance = candidateDistance;
                result = portalNode;
            }
        }
    }
    if (bestDistance < distanceLimit) {
        *routeDistance = bestDistance;
    }
    return result;
}


f32 Portal_EstimateGoalDistance(CNavData *graph, NavigationSearchNode *node)
{
    s32 neighbors[64];
    s32 portalIds[64];
    NavigationBuffer *portalTable;
    NavigationBuffer *exitPoints;
    NavigationBuffer *goalPoints;
    NavigationBuffer *exitGoalPoints;
    f32 empty;
    f32 distance;
    f32 exitDistance;
    f32 best;
    s32 goal;
    s32 exitGoal;
    s32 goalIndex;
    s32 neighborIndex;
    s32 neighborCount;
    NavigationPortal *portal;
    NavigationPoint *origin;
    NavigationPoint *exitPoint;
    best = g_portalEstimateEmptyDistance;
    empty = best;
    origin = navigationRecord(graph->points, node->key);
    for (goalIndex = 0; goalIndex < 64; goalIndex++)
    {
        goal = graph->m_nGoalList[goalIndex];
        if (goal == -1)
        {
            continue;
        }
        goalPoints = graph->points;
        distance = Graphu64_GetPointDistance(&origin->position.x, navigationRecord(goalPoints, goal));
        if ((distance < best) || (best == empty))
        {
            best = distance;
        }
    }

    for (goalIndex = 0; goalIndex < 64; goalIndex++)
    {
        neighbors[goalIndex] = -1;
        portalIds[goalIndex] = -1;
    }

    {
        s32 key = node->key;
        s32 *neighborBase = neighbors;
        s32 *portalBase = portalIds;
        s32 portalIndex = 0;
        s32 count = 0;
        s32 *neighborOut;
        s32 *portalOut;
        NavigationBuffer *links;
        NavigationPortal *link;
        if (graph->m_nNavLinks > portalIndex)
        {
            portalOut = portalBase;
            neighborOut = neighborBase;
            do
            {
                links = graph->m_pusNavLinks;
                link = navigationRecord(links, portalIndex);
                if (link->first == key)
                {
                    count += 1;
                    *neighborOut = link->second;
                    *portalOut = portalIndex;
                    portalOut++;
                    neighborOut++;
                }
                if (link->second == key)
                {
                    count += 1;
                    *neighborOut = link->first;
                    *portalOut = portalIndex;
                    portalOut++;
                    neighborOut++;
                }
                portalIndex += 1;
            }
            while (portalIndex < graph->m_nNavLinks);
        }
        neighborCount = count;
    }
    {
        for (neighborIndex = 0; neighborIndex < neighborCount; neighborIndex++)
        {
            portalTable = graph->m_pusNavLinks;
            portal = navigationRecord(portalTable, portalIds[neighborIndex]);
            if ((portal->kind == 9) && (portal->first == node->key))
            {
                exitPoints = graph->points;
                exitPoint = navigationRecord(exitPoints, portal->second);
                for (goalIndex = 0; goalIndex < 64; goalIndex++)
                {
                    exitGoal = graph->m_nGoalList[goalIndex];
                    if (exitGoal == -1)
                    {
                        continue;
                    }
                    exitGoalPoints = graph->points;
                    exitDistance = Graphu64_GetPointDistance(&exitPoint->position.x, navigationRecord(exitGoalPoints, exitGoal));
                    if ((exitDistance < best) || (best == g_portalExitEstimateEmptyDistance))
                    {
                        best = exitDistance;
                    }
                }

            }
        }

    }
    return best;
}


static inline s32 navHasOpenNode(CNavData *graph, s32 status) {
    NavigationSearchNode *node = graph->searchNodes.head;
    while (node) {
        if (node->open == status) return 1;
        node = node->next;
    }
    return 0;
}
static inline NavigationSearchNode *navFindNode(CNavData *graph, s32 key) {
    NavigationSearchNode *node = graph->searchNodes.head;
    while (node) {
        if (node->key == key) return node;
        node = node->next;
    }
    return 0;
}
/* A* search from start over the link graph: repeatedly closes the open node with the lowest total, stores its
 * key in graph->result once it is a goal, otherwise relaxes the cost of every node it links to. */
void Portal_SearchPath(CNavData *graph, NavigationSearchNode *start) {
    s32 neighbors[64];
    s32 portals[64];
    NavigationPoint *origin;
    NavigationPoint *destination;
    f32 initialEstimate;
    f32 estimate;
    f32 cost;
    f32 distance;
    f32 edgeCost;
    s32 neighborKey;
    s32 state;
    s32 index;
    s32 count;
    const s32 open = 1;
    s32 reversible;
    u8 edgeKind;
    NavigationPortal *portal;
    NavigationSearchNode *current;
    NavigationSearchNode *node;
    NavigationSearchNode *best;
    f32 minimum;
    NavigationSearchNode *next;

    start->cost = 0.0f;
    initialEstimate = Portal_EstimateGoalDistance(graph, start);
    start->estimate = initialEstimate;
    start->parent = 0;
    start->open = open;
    start->total = start->cost + initialEstimate;
    while (navHasOpenNode(graph, open)) {
        node = graph->searchNodes.head;
        best = 0;
        minimum = g_portalSearchInitialMinimum;
        while (node) {
            if (node->open == open) {
                if (node->total < minimum) {
                    best = node;
                    minimum = node->total;
                } else if (minimum == g_portalSearchEmptyTotal) {
                    best = node;
                    minimum = node->total;
                }
            }
            node = node->next;
        }
        if (best) best->open = 0;
        current = best;
        origin = navigationRecord(graph->points, current->key);
        if (current->goal != 0) {
            graph->result = current->key;
            return;
        }
        for (index = 0; index < 64; index++) {
            neighbors[index] = -1;
            portals[index] = -1;
        }
        count = navigationNeighbors(graph, current->key, neighbors, portals);
        for (index = 0; index < count; index++) {
            f32 minimumCost = 0.0f;
            neighborKey = neighbors[index];
            destination = navigationRecord(graph->points, neighborKey);
            next = navFindNode(graph, neighborKey);
            portal = navigationRecord(graph->m_pusNavLinks, portals[index]);
            switch (portal->kind) {
                case 1:
                case 4:
                case 7:
                    reversible = 1;
                    break;
                default:
                    reversible = 0;
                    break;
            }
            if (reversible == 0 && portal->first != current->key) continue;
            edgeKind = portal->kind;
            if (edgeKind == 10) continue;
            if (edgeKind == 11) continue;
            if (edgeKind == 9) {
                distance = 0.0f;
            } else {
                distance = Graphu64_GetPointDistance(&destination->position.x, &origin->position.x);
            }
            edgeCost = distance + next->extra;
            if (navigation_point_flags(destination) & 0x400) {
                edgeCost += g_portalFlaggedNodeCost;
            }
            if (edgeCost < minimumCost) {
                edgeCost = minimumCost;
            }
            state = next->open;
            cost = current->cost + edgeCost;
            if (((state ^ 2) == 0) || ((state ^ 1) == 0)) {
                if (!(next->cost <= cost)) {
                    goto update_neighbor;
                }
            } else {
update_neighbor:
                next->parent = current;
                next->cost = cost;
                estimate = Portal_EstimateGoalDistance(graph, next);
                next->estimate = estimate;
                next->total = next->cost + estimate;
                if ((next->open ^ 2) == 0) {
                    next->open = 0;
                }
                if ((next->open ^ open) != 0) {
                    next->open = open;
                }
            }
        }
        current->open = 2;
    }
}

extern CNavData g_navigationGraph;


/** Return the index of the link joining two nodes, accepting reversed links of two-way types, or -1. */


static inline int isTwoWay(Link *link) {
    switch (link->type) {
    case 1:
    case 4:
    case 7:
        return 1;
    }
    return 0;
}



/* Point storage is a record table: its first word is the record stride in bytes,
 * the records follow after an eight-byte header. */
static inline void *Portal_PointRecordAt(s32 *table, s32 index) {
  return (u8 *)table + (index * table[0] + 8);
}


/** Return an indexed record from the table referenced by the input. */
void *Portal_GetGraphPoint(void *table, int index) {
    return Portal_PointRecordAt(*(s32 **)table, index);
}

/** Return an indexed record from the table at object offset 0x8. */
void *Portal_GetStridedTableEntry(struct CNavData_t *object, int index) {
    char *base = (char *)object->m_pusNavLinks;
    int stride = *(int *)base;
    return base + (index * stride + 8);
}

s32 Portal_IsReversibleLink(Link *link) {
    u8 linkTypeByte;
    s32 linkType;

    linkTypeByte = link->type;
    linkType = linkTypeByte;
    if (linkType == 4) {
        goto ret1;
    }
    if (linkType >= 5) {
        goto ge_5;
    }
    if (linkType == 1) {
        goto ret1;
    }
    goto ret0;
ge_5:
    if (linkType != 7) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

void Portal_InitSearchNode(void *searchNode, s32 nodeKey)
{
  NavigationPoint *entry;
  NavigationSearchNode *node = searchNode;
  u16 flags;
  s32 *base;
  char *nodeStorage;
  node->value = g_portalNodeInitialValue;
  node->key = nodeKey;
  node->state = -1;
  node->previous = 0;
  node->next = 0;
  base = (s32 *)g_navigationGraph.points;
  nodeStorage = (char *)base + ((nodeKey * (*base)) + 8);
  entry = (NavigationPoint *)nodeStorage;
  flags = navigation_point_flags(entry);
  if (flags & 2)
  {
    node->wait = g_portalNodeWaitAndHeightOffset;
  }
  node->object = 0;
  node->ticks = 0;
  node->delay = 0;
  node->platform = 0;
  node->endpoint.x = 0;
  node->endpoint.y = 0;
  node->endpoint.z = 0;
  flags = navigation_point_flags(entry);
  if (flags & 0x40)
  {
    node->ticks = (Graphu64_NextRandom() % 5) + 5;
  }
  flags = navigation_point_flags(entry);
  if (flags & 0x80)
  {
    node->delay = (Graphu64_NextRandom() % 5) + 5;
  }
}

s32 Portal_FindNearestPointIndex(struct CNavData_t *pointSet, void *point) {
    CVector3 offset;
    f32 distanceSq;
    f32 bestDistanceSq;
    void *items;
    s32 index;
    s32 bestIndex;
    s32 stride;

    bestIndex = -1;
    bestDistanceSq = 0.0f;
    index = 0;
    if (pointSet->m_nNavNodes > 0) {
        do {
            items = pointSet->points;
            stride = *(s32 *)items;
            Graphu64_SubtractVectors(&offset, point, (char *)items + (index * stride + 8));
            distanceSq = (offset.x * offset.x) + (offset.y * offset.y) + (offset.z * offset.z);
            if ((bestIndex < 0) || (distanceSq < bestDistanceSq)) {
                bestIndex = index;
                bestDistanceSq = distanceSq;
            }
            index += 1;
        } while (index < pointSet->m_nNavNodes);
    }
    return bestIndex;
}

int Portal_FindLinkIndex(CNavData *graph, int from, int to) {
    int i;
    Link *link;

    for (i = 0; i < graph->m_nNavLinks; i++) {
        link = (Link *)((char *)graph->m_pusNavLinks->data + i * graph->m_pusNavLinks->stride);
        if (link->from == from && link->to == to) {
            return i;
        }
        if (link->to == from && link->from == to && isTwoWay(link)) {
            return i;
        }
        if (link->to == from && link->from == to && link->type == 6) {
            return i;
        }
    }
    return -1;
}

s32 Portal_CollectIncidentLinks(CNavData *list, s32 value, s32 *partners, s32 *indices) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    if (list->m_nNavLinks > 0) {
        do {
            s32 product = i * list->m_pusNavLinks->stride;
            s32 offset = product + 8;
            u16 *entry;
            u16 *other_entry;

            entry = (u16 *)((char *)list->m_pusNavLinks + offset);
            other_entry = entry;

            if (entry[0] == value) {
                found++;
                *partners = entry[1];
                *indices = i;
                indices++;
                partners++;
            }
            if (other_entry[1] == value) {
                found++;
                *partners = other_entry[0];
                *indices = i;
                indices++;
                partners++;
            }
            i++;
        } while (i < list->m_nNavLinks);
    }
    return found;
}

s32 Portal_IsNodeMovementBlocked(s32 **nodeStorage, void *instance, s32 nodeKey) {
    CVector3 position;
    CollisionQuery collision;
    struct ActorInstanceHeader saved;
    s32 first_test;
    s32 result;
    s32 *table;
    void *entry;

    table = *nodeStorage;
    entry = Portal_PointRecordAt(table, nodeKey);
    position = *(CVector3 *)entry;
    position.y += *(&g_portalNodeWaitAndHeightOffset + 1);

    if ((((LevelActor *)instance)->kind == 1) && (((LevelActor *)instance)->flags & 0x300000)) {
        collision = g_portalAlternateCollisionQuery;
    } else {
        first_test = Insthdr_GetModelCollisionFlag1(instance);
        if (Insthdr_IsInactiveOrCollisionOption4(instance) == 0) {
            if (first_test != 0) {
                collision = g_portalModeCollisionQuery;
            } else {
                collision = g_portalAlternateCollisionQuery;
            }
        } else if (Insthdr_GetModelCollisionFlag8(instance) == 0) {
            collision = g_portalNoModelFlagCollisionQuery;
        } else {
            collision = g_portalDefaultCollisionQuery;
        }
    }
    collision.w[0] = 0x4000;
    saved = *(struct ActorInstanceHeader *)instance;
    result = Unicol_MoveActorWithCollision(instance, position.x, position.y, position.z, &collision);
    *(struct ActorInstanceHeader *)instance = saved;
    return result == 0;
}

void *Portal_FindSearchNode(char *object, s32 current) {
    CNavData *graph = (CNavData *)object;
    NavigationSearchNode *record = graph->searchNodes.head;
    if (record != 0) {
        do {
            if (record->key == current) {
                return record;
            }
            record = record->next;
        } while (record != 0);
    }
    return 0;
}

void Portal_ResetSearchState(struct CNavData_t *graph) {
    struct NavigationSearchNode *node;
    f32 blockedNodeValue;

    node = graph->searchNodes.head;
    if (node != 0) {
        blockedNodeValue = (-1.0f);
        do {
            node->value = blockedNodeValue;
            node->state = -1;
            node->extra = 0;
            node->cost = 0;
            node->estimate = 0;
            node->total = 0;
            node->open = 0;
            node->goal = 0;
            node->parent = 0;
            node = node->next;
        } while (node != 0);
    }
    graph->value = (-1.0f);
    graph->selected = -1;
}













#if defined(VERSION_US)
unsigned int k_PortalEngagementAndSearchLiteralData[1] = {
    0x5F446973,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_portalEngagementSearchOffset[1] = {
    0xC2480000,
};
#endif

#if defined(VERSION_EU)
unsigned int k_portalEngagementLoadUpperInstruction[1] = {
    0x3C04800E,
};
#endif

#if defined(VERSION_DE)
unsigned int k_portalEngagementNegativeUnit[1] = {
    0xBF800000,
};
#endif

#if defined(VERSION_US_REV1)
unsigned int g_PortalEngagementAndSearchLiteralData[1] = {
    0x3FC00000,
};
#endif

const float g_navigationObjectLinkDistanceLimits[3] = {
    -1.0f, -1.0f, 512.0f,
};

/* Retained data for this translation unit. */
#if !(defined(VERSION_US_REV1))
const float g_Portal_SearchRelatedGoalPathConstantWords_de_eu_eu_x_us[2] = {
    -1.0f, -1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Portal_SearchRelatedGoalPathConstantWords_us_rev1[2] = {
    -1.0f, -1.0f,
};
#endif

const float g_Portal_FindPortalRouteConstantWords[1] = {
    1000000000.0f,
};

const float g_Portal_SearchPortalRouteConstantWords[1] = {
    1e+07f,
};
#if !(defined(VERSION_US_REV1))
const float g_Portal_EstimateGoalDistanceConstantWords_de_eu_eu_x_us[2] = {
    -1.0f, -1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Portal_EstimateGoalDistanceConstantWords_us_rev1[2] = {
    -1.0f, -1.0f,
};
#endif

const float g_Portal_SearchPathConstantWords[3] = {
    -1.0f, -1.0f, 5.12e+04f,
};

const float g_Portal_InitSearchNodeConstantWords[2] = {
    -1.0f, 15.0f,
};

const float g_Portal_IsNodeMovementBlockedConstantWords[1] = {
    61.44f,
};

const float g_Portal_UpdateAlternatingActionBurstsConstantWords[7] = {
    1.0f, 0.3f, 1.0f, 1.0f,
    0.26179942f, 1.0f, 0.52359885f,
};

const float g_Portal_UpdateCountedEffectActionConstantWords[3] = {
    1.0f, 1.0f, 94371.83f,
};

const float g_Portal_UpdateMeterGatedActionBurstConstantWords[3] = {
    41943.035f, 98.0f, 1.0f,
};

const float g_Portal_UpdateRandomActionPulseConstantWords[2] = {
    98.0f, 1.0f,
};

const float g_Portal_InitializeRandomActionSettingsConstantWords[1] = {
    1.0f,
};

const float g_Portal_GetEngagementDistanceConstantWords[2] = {
    1.0f, 0.52359885f,
};
