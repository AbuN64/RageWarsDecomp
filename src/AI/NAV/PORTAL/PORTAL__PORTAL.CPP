#include "include_asm.h"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "COMMON/WORLD.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/INTEGERSTATE2C.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "AI/NAV/PORTAL_LINKNAVIGATIONOBJECTS.H"
#include "COMMON/LISTHEADER.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"

/* 800C6E58.CPP */
#if !(defined(VERSION_US_REV1))
const float g_Portal_SearchRelatedGoalPathConstantWords_de_eu_eu_x_us[2] = {
    -1.0f, -1.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Portal_SearchRelatedGoalPathConstantWords_us_rev1_Portal.c */
const float g_Portal_SearchRelatedGoalPathConstantWords_us_rev1[2] = {
    -1.0f, -1.0f,
};
#endif

/* 800C6E60.CPP */
/* ROM-grounded data: src/g_Portal_FindPortalRouteConstantWords_Portal.c */
const float g_Portal_FindPortalRouteConstantWords[1] = {
    1000000000.0f,
};

/* 800C6E64.CPP */
/* ROM-grounded data: src/g_Portal_SearchPortalRouteConstantWords_Portal.c */
const float g_Portal_SearchPortalRouteConstantWords[1] = {
    1e+07f,
};

/* 800C6E68.CPP */
#if !(defined(VERSION_US_REV1))
const float g_Portal_EstimateGoalDistanceConstantWords_de_eu_eu_x_us[2] = {
    -1.0f, -1.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Portal_EstimateGoalDistanceConstantWords_us_rev1_Portal.c */
const float g_Portal_EstimateGoalDistanceConstantWords_us_rev1[2] = {
    -1.0f, -1.0f,
};
#endif

/* 800C6E70.CPP */
/* ROM-grounded data: src/g_Portal_SearchPathConstantWords_Portal.c */
const float g_Portal_SearchPathConstantWords[3] = {
    -1.0f, -1.0f, 5.12e+04f,
};

/* 800C6E7C.CPP */
/* ROM-grounded data: src/g_Portal_InitSearchNodeConstantWords_Portal.c */
const float g_Portal_InitSearchNodeConstantWords[2] = {
    -1.0f, 15.0f,
};

/* 800C6E84_6.CPP */
/* ROM-grounded data: src/g_Portal_IsNodeMovementBlockedConstantWords_Portal.c */
const float g_Portal_IsNodeMovementBlockedConstantWords[1] = {
    61.44f,
};

/* 80208000_6.CPP */
/** Returns the difference between the constant after g_actionSettingsRandomRange and Scaled_GetDifficultyEngagementAdjustment's result, scaled by g_portalEngagementScale. */

extern f32 Scaled_GetDifficultyEngagementAdjustment(AiController *controller);

extern f32 g_portalEngagementBase;

/* Find the nearest world object matching each active target ID, clearing its active flag when no object is close enough. */

f32 Graphu64_GetPointDistance(void *firstPoint, void *secondPoint);

s32 Scene_GetModelIdAtIndex(void *world, s16 modelIndex);

/* Preserve the owning controller passed in a0 by the original MIPS. */

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
          if (actorIndex < ww->actorCount)
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
            while ((++actorIndex) < ww->actorCount);
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

extern PlatformRoute *Scene_GetPlatformRoute(void *, s32);
extern CVector3 *Scene_GetPlatformRoutePoint(void *, s32, s32);
/* Give every platform-flagged (0x200) search node the nearest moving platform (object 0x642) and the
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
    for (node = graph->nodes; node != 0; node = node->next) {
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

typedef struct NavigationCollisionQuery { s32 flags, word4, word8, wordC, word10, word14, word18; } NavigationCollisionQuery;
extern NavigationCollisionQuery g_portalDefaultCollisionQuery, g_portalModeCollisionQuery, g_portalNoModelFlagCollisionQuery, g_portalAlternateCollisionQuery;
s32 InstHdr_GetActorMotionState(Player *);
s32 Insthdr_GetModelCollisionFlag1(Player *);
s32 Insthdr_IsInactiveOrCollisionOption4(Player *);
s32 Insthdr_GetModelCollisionFlag8(Player *);
s32 Unicol_MoveActorWithCollision(Player *, CVector3, NavigationCollisionQuery *);
void Graphu64_SubtractVectors(struct CVector3_t *difference, struct CVector3_t *leftVector, struct CVector3_t *rightVector);

/* Collisions the actor would meet moving to a point (61.44 above it), without committing the move: the actor's 0x50-byte header is saved and
 * restored around the trial move. */
static __inline__ s32 navigationBlocked(Player *actor, CNavData *graph, s32 index) {
    CVector3 position;
    NavigationCollisionQuery query;
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
    query.flags = 0x4000;
    __builtin_memcpy(saved, actor, sizeof(saved));
    result = Unicol_MoveActorWithCollision(actor, position, &query);
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
