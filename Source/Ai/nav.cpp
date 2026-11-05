#include "Ai/Weapon/weapon.h"
#include "Engine/events.h"
#include "Common/output.h"
#include "frontend_symbols.h"
#include "Common/ai_behaviour_types.h"
#include "Common/navigation_graph.h"
#include "Common/navigation_node_and_route_views.h"
#include "types.h"
#include "Ai/Nav/search_node_state.h"
#include "include_asm.h"
#include "Common/navigation_actor_search_views.h"
#include "Common/vector4f.h"
#include "Common/aiprofile.h"
#include "Ai/Nav/pickuptarget.h"
#include "Ai/portal_searchpath.h"
#include "Ai/portal_isnodemovementblocked.h"
#include "Ai/Nav/Route/route.h"
#include "Ai/shared_pickupgoalnode.h"
#include "Ai/nav_symbols.h"
#include "Common/actorrec.h"
#include "Common/runtime_declarations.h"
#include "Common/sharedplayer.h"
#include "Fx/normalize_vector.h"
#include "pickup.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Ai/ai_functions.h"
#if defined(VERSION_DE)
#include "Data/Actor_state_callbacks/actor_state_callback_labels.h"
#endif
#include "Common/output.h"
#include "Common/Lone/particle_collision_probe_result.h"
#include "Common/ppdecom_unpackresource.h"
#include "Engine/defs.h"
#include "Render/setn64_getpacksection.h"
#include "Math/doublebits.h"
#include "Libsn/nav_isballisticarcobstructed_data.h"
#include "Engine/Unicol/unicol.h"
#include "Common/shared_optionsscreen.h"
#include "Common/gameplay_reaction_rules.h"
#include "Common/gameplay_transition.h"
#include "Common/triple.h"
#include "Common/shared_gameslot.h"
#include "Ai/Nav/nav_evaluatecaptureflagmarkersearch.h"
#include "Ai/Nav/teammarker.h"
#include "Ai/Player/scaled_updatetargetpitch.h"
#include "Ai/ai_shared_symbols.h"
#if defined(VERSION_DE)
#include "Data/Ovl1_c/navigation_callback_address.h"
#endif
#include "Common/level_actor.h"
#include "Ai/Nav/nav_setpickupgoalweights.h"
#include "Ai/Nav/searchnode.h"
#include "Ai/Nav/nav_selectpickupgoal.h"
#include "Ai/Nav/nav_selectpickupgoaleu.h"
#include "Common/measured_storage.h"
#include "Common/route_chase_records.h"
#include "Common/rec.h"
#include "Common/self.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Fx/target.h"
#include <platform_sdk.h>
#include "Common/ballisticparams.h"
#include "Common/weapon_select_brain.h"
#include "Game/weaponselect.h"
#include "Data/rest_source_records.h"
#include "Particle/particle_releaseownerlistoneeffects.h"
#include "World/playerai_respawnfragtagplayer.h"
#include "Common/resourceloadstate.h"
#include "Common/brain.h"
#include "Attack/attack.h"
#include "Common/vector.h"
#include "Ai/Nav/nav_updaterangedcombat.h"
#include "Ai/Nav/nav_updateclosecombat.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Ai/Nav/nav_updatevisiblepursuit.h"
#include "Ai/Nav/nav_initpursuitstrafe.h"
#include "Ai/Nav/combatinit.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Ai/Nav/wheel.h"
#include "Ai/Nav/Portal/portal_updatealternatingactionbursts.h"
#include "Behaviour/behaviour.h"
#include "Frontend/player.h"
#include "Ai/route_relation_grid.h"
#include "Common/shared_worldfunc.h"
#include "Ai/Nav/farthest.h"
#include "Ai/source.h"
#include "Ai/Nav/carrier.h"
#include "Common/format.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"
#include "Ai/Nav/nav_resetobjectarrivalchase.h"
#include "Ai/objectchase.h"
#include "Common/player_sequence_state.h"
#include "Ai/Nav/jumproute.h"
#include "Ai/Nav/roam.h"

/* Stores an id in the first free (-1) of the object's 64 id slots and flags the node with that
   id in the object's list as active. */

static inline NavigationSearchNode *find_node(CNavData *obj, int id) {
    NavigationSearchNode *node;

    for (node = obj->searchNodes.head; node != 0; node = node->next) {
        if (node->key == id) {
            return node;
        }
    }
    return 0;
}

void Nav_AddGoalNode(CNavData *obj, int id) {
    int i;

    for (i = 0; i < 64; i++) {
        if (obj->m_nGoalList[i] == -1) {
            obj->m_nGoalList[i] = id;
            find_node(obj, id)->goal = 1;
            return;
        }
    }
}

int Nav_OpenSearchNode(void *navigationSearchNode) {
    NavigationSearchNode *node = navigationSearchNode;
    node->open = 1;
    return 1;
}

void *Nav_TakeLowestCostOpenNode(void *cNavData) {
    CNavData *graph = cNavData;
    NavigationSearchNode *node;
    NavigationSearchNode *best;
    f32 best_value;

    node = graph->searchNodes.head;
    best_value = (-1.0f);
    best = 0;
    if (node != 0) {
        do {
            if (node->open == 1) {
                f32 value = node->total;
                if (value < best_value || best_value == (-1.0f)) {
                    best = node;
                    best_value = value;
                }
            }
            node = node->next;
        } while (node != 0);
    }
    if (best != 0) {
        best->open = 0;
    }
    return best;
}

/** Set the word to the state value two. */
void Nav_CloseSearchNode(void *object) {
    NavigationSearchNode *node = object;
    node->open = 2;
}

int Nav_IsSearchNodeOpen(void *navigationSearchNode) {
    NavigationSearchNode *node = navigationSearchNode;
    return node->open == 1;
}

/** Report whether the word equals two. */
int Nav_IsSearchNodeClosed(void *navigationSearchNode) {
    NavigationSearchNode *node = navigationSearchNode;
    return node->open == 2;
}

s32 Nav_HasOpenSearchNodes(CNavData *cNavData) {
    CNavData *graph = cNavData;
    NavigationSearchNode *record = graph->searchNodes.head;
    if (record != 0) {
        do {
            if (record->open == 1) {
                return 1;
            }
            record = record->next;
        } while (record != 0);
    }
    return 0;
}

/** Clear the word. */
void Nav_ClearSearchNodeStatus(void *controller) {
    ObjRecAt28V2 *record = controller;
    record->state = 0;
}


struct CNavData_t; extern s32 Portal_SearchRelatedGoalPath(struct CNavData_t *obj, s32 key, s32 requested, void *owner);

/** Reset the float field of each occupied player slot's table entry to the default value. */



#if defined(VERSION_US)

#endif

#if defined(VERSION_EU)

#endif

#if defined(VERSION_DE)

#endif

#if defined(VERSION_US_REV1)
extern float g_FindData[3];
#endif


#if defined(VERSION_EU_X)
extern float k_navCheckcloseattackrouteFragment[3];
#endif

/* Advances a committed selection's stage against the node list g_navigationGraph: finishes through
   Nav_FindSpecialLinkedCandidate when there are no stages, counts once into 0x1C8 the list's kind-6 nodes whose
   id matches the selection id, then runs Nav_AppendDirectionalRouteStage while the stage is within that count,
   Nav_InsertPickupRouteNode on the stage right after it and Nav_ComputeScaledPointCentroid on the one after that. */
/* Navigation selection/list/node canonical ownership remains unresolved. */

extern void *Portal_GetStridedTableEntry(struct CNavData_t *object, int index);

s32 Nav_AdvancePickupRouteSelection(Selection *sel)
{
    CNavData *list = (CNavData *)&g_navigationGraph;
    PickupGoalAvailabilityNode *node;
    s32 i;

    if (list == 0) {
        return 1;
    }
    if (sel->stage == 0) {
        return Nav_FindSpecialLinkedCandidate(sel);
    }
    if (sel->selection != -1 && sel->matches == 0) {
        for (i = 0; i < list->m_nNavLinks; i++) {
            node = (PickupGoalAvailabilityNode *)Portal_GetStridedTableEntry((CNavData *)list, i);
            if (node->id == sel->selection && node->kind == 6) {
                sel->matches++;
            }
        }
    }
    if (sel->stage > 0 && sel->stage < sel->matches + 1) {
        return Nav_AppendDirectionalRouteStage((SelectionNavAppendDirectionalRouteStage *)sel);
    }
    if (sel->stage == sel->matches + 1) {
        return Nav_InsertPickupRouteNode((SelectionNavAppendDirectionalRouteStage *)sel);
    }
    if (sel->stage == sel->matches + 2) {
        return Nav_ComputeScaledPointCentroid(sel);
    }
    return 1;
}

/* Records the next stage of a selection: finds the kind-6 link from the selection's node in the route
 * g_navigationGraph (stopping at the stage number), stores its two node ids in that stage's entry, measures the
 * distance from the selection's own node through Nav_MeasureNodeDistance_de and Graphu64_GetSquaredDistance,
 * multiplies the unit directions from each attached object to the stage's node (Graphu64_NormalizeVector_de)
 * into a facing term, and stores the distance scaled by that term (made positive for a single object) before
 * advancing the stage count. Returns zero. */

extern f32 Graphu64_GetSquaredDistance(f32 *a, f32 *b);

s32 Nav_AppendDirectionalRouteStage(SelectionNavAppendDirectionalRouteStage *sel) {
    CVector3 facing;
    CVector3 *node;
    s32 i;
    s32 stage;
    Link *link;
    f32 distance;
    f32 term;
    CNavData *route;

    node = 0;
    i = 0;
    stage = 0;
    route = &g_navigationGraph;
    for (; i < route->m_nNavLinks; i++) {
        link = Portal_GetStridedTableEntry((CNavData *)route, i);
        if (link->from == sel->id && link->type == 6) {
            node = Portal_GetGraphPoint(route, link->to);
            sel->stages[stage].from = link->from;
            sel->stages[stage].to = link->to;
            if (stage + 1 == sel->stageCount) {
                break;
            }
            stage++;
        }
    }
    distance = Graphu64_GetSquaredDistance(node, Portal_GetGraphPoint(route, sel->node));
    facing.x = facing.y = facing.z = 1.0f;
    for (i = 0; i < sel->objectCount; i++) {
        if (sel->objects[i] == 0) {
            break;
        }
        sel->dirs[stage].x = node->x - sel->objects[i]->pos.x;
        sel->dirs[stage].y = node->y - sel->objects[i]->pos.y;
        sel->dirs[stage].z = node->z - sel->objects[i]->pos.z;
        Graphu64_NormalizeVec3(&sel->dirs[stage]);
        facing.x *= sel->dirs[stage].x;
        facing.y *= sel->dirs[stage].y;
        facing.z *= sel->dirs[stage].z;
    }
    term = facing.x + facing.y + facing.z;
    if (sel->objectCount == 1 && term < 0.0f) {
        term = -term;
    }
    sel->stages[stage].distance = term * distance;
    sel->stageCount++;
    return 0;
}

struct CNavData_t; extern int Portal_FindLinkIndex(struct CNavData_t *graph, int from, int to);
s32 Nav_InsertPickupRouteNode(SelectionNavAppendDirectionalRouteStage *sel) {
    CVector3 avg;
    Shared_PickupGoalNode *info;
    CVector3 *node;
    CNavData *list;
    s32 next;
    s32 best;
    s32 i;
    s32 count;
    f32 inv;

    next = -1;
    count = 0;
    best = sel->objectCount;
    list = &g_navigationGraph;
    for (i = 0; i < sel->objectCount; i++) {
        if (sel->stages[i].distance > count) {
            best = i;
        }
    }
    count = sel->objectCount;
    if (best == count) {
        sel->failed = 0;
        sel->stageCount += 20;
        return 1;
    }
    if (sel->stages[best].to < 0) {
        sel->failed = 0;
        sel->stageCount += 20;
        return 1;
    }
    for (i = 0; i < 3; i++) {
        if (sel->ids[i] == sel->id) {
            next = sel->ids[i + 1];
            break;
        }
    }
    if (next == -1 || Portal_FindLinkIndex((CNavData *)list, sel->id, sel->stages[best].to) == -1 ||
        Portal_FindLinkIndex((CNavData *)list, next, sel->stages[best].to) == -1) {
        sel->failed = 0;
        sel->stageCount += 20;
        return 1;
    }
    for (i = 3; i > 0; i--) {
        if (sel->ids[i - 1] == sel->id) {
            sel->ids[i] = sel->stages[best].to;
            break;
        }
        sel->ids[i] = sel->ids[i - 1];
    }
    avg.x = avg.y = avg.z = 0.0f;
    for (i = 0; i < sel->objectCount; i++) {
        avg.x += sel->dirs[i].x;
        avg.y += sel->dirs[i].y;
        avg.z += sel->dirs[i].z;
    }
    count = sel->objectCount;
    inv = 1.0f / (f32)count;
    avg.x = avg.x * inv;
    avg.y = avg.y * inv;
    avg.z = avg.z * inv;
    info = Portal_FindSearchNode(list, sel->stages[best].to);
    avg.x = avg.x * info->radius;
    avg.y = avg.y * info->radius;
    avg.z = avg.z * info->radius;
    node = Portal_GetGraphPoint(list, sel->stages[best].to);
    sel->result.x = node->x + avg.x;
    sel->result.y = node->y + avg.y;
    sel->result.z = node->z + avg.z;
    sel->lastNode = sel->stages[best].to;
    sel->stageCount++;
    return 0;
}

/** Find the first of an object's four nodes that starts a type-6 link, record it and return 0; return 1 when none does. */

s32 Nav_ComputeScaledPointCentroid(ObjNavComputeScaledPointCentroid *request) {
    CVector3 sum;
    s32 i;
    f32 scale;
    Info *info;
    CVector3 *base;
    void *global;

    sum.x = sum.y = sum.z = 0.0f;
    global = &g_navigationGraph;
    for (i = 0; i < request->count; i++) {
        sum.x += request->points[i].x;
        sum.y += request->points[i].y;
        sum.z += request->points[i].z;
    }
    if (request->count == 0)
        return 1;

    scale = g_pointCentroidUnitScale / (f32)request->count;
    sum.x *= scale;
    sum.y *= scale;
    sum.z *= scale;
    info = (Info *)Portal_FindSearchNode((CNavData *)global, request->infoIndex);
    sum.x *= info->scale;
    sum.y *= info->scale;
    sum.z *= info->scale;
    base = Portal_GetGraphPoint(global, request->infoIndex);
    request->result.x = base->x + sum.x;
    request->result.y = base->y + sum.y;
    request->result.z = base->z + sum.z;
    return 1;
}

int Nav_FindSpecialLinkedCandidate(ObjNavFindSpecialLinkedCandidate *request) {
    int j;
    int i;
    Link *link;
    CNavData *graph = (CNavData *)&g_navigationGraph;

    request->node = -1;
    request->pending = 0;
    for (j = 0; j < 4; j++) {
        for (i = 0; i < graph->m_nNavLinks; i++) {
            link = Portal_GetStridedTableEntry(graph, i);
            if (link->from == request->nodes[j] && link->type == 6) {
                request->hits++;
                request->node = request->nodes[j];
                return 0;
            }
        }
    }
    return 1;
}

#if !(defined(VERSION_US_REV1))
extern const float g_pointCentroidUnitScale;
#endif

#if defined(VERSION_DE)
void *const k_NavComputescaledpointcentroidData[1] = {
    (void *)&Nav_RefineBallisticAim_label336,
};
#endif

#if defined(VERSION_US_REV1)


#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
const char g_navPickupRouteFloatLiteral[4] __attribute__((aligned(4))) = "Bp\000\000";
#endif
#endif



s32 Nav_IsBallisticArcObstructed(ActorRec *actor, f32 scale, f32 lateral);

/* Refine a launch angle by testing a ballistic arc against the destination.
 * State 0 initializes the bounds; later calls bisect the chosen quadrant. */
s32 Nav_RefineBallisticAim(ActorRec *actor) {
    CVector3 current;
    CVector3 delta;
    s32 first, last;
    s32 keyCount;
    BallisticInstance *instance;
    BallisticInstance *activeInstance;
    f32 angleCosineSquared;
    f32 horizontalDistance;
    f32 heightDelta;
    f32 scale;
    f32 deltaX;
    f32 lateral;
    f32 angleCosine;
    f32 deltaZ;
    f32 trajectoryHeight;
    f32 initialHeightDelta;
    f32 currentDeltaZ;
    f32 fallbackPitch;
    f32 initialDeltaX;
    f32 currentDeltaY;
    f32 secondaryPitch;
    s32 trajectoryMode;
    s32 *ballisticResource;
    s32 obstructedQuadrant;
    s32 iterationState;
    s32 nextIteration;
    s32 initialQuadrant;
    s32 secondaryQuadrant;
    s32 fallbackQuadrant;
    BallisticResourceKeys *resourceKeys;
    u32 resourceKey;
    Shared_ParticleDesc *parameterRecord;
    EffectMotion *speedParameters;
    EffectMotion *gravityParameters;

    trajectoryMode = actor->instance->trajectoryMode;
    resourceKey = 0;
    if (trajectoryMode != actor->trajectoryMode) {
        actor->trajectoryInitialized = 0;
        actor->trajectoryMode = (s32) trajectoryMode;
    }
    if (actor != 0) {
        iterationState = actor->trajectoryInitialized;
        if (iterationState == 0) {
            instance = actor->instance;
            current = instance->header.spatial.position;
            delta = actor->destination;
            initialDeltaX = delta.x - current.x;
            initialHeightDelta = delta.y - current.y;
            deltaZ = delta.z - current.z;
            delta.x = initialDeltaX;
            delta.y = initialHeightDelta;
            delta.z = deltaZ;
            actor->trajectoryDistance = Gu_Sqrtf((initialDeltaX * initialDeltaX) + (initialHeightDelta * initialHeightDelta) + (deltaZ * deltaZ));
            heightDelta = delta.y;
            delta.y = 0;
            horizontalDistance = Gu_Sqrtf((delta.x * delta.x) + (delta.z * delta.z));
            {
                switch (trajectoryMode) {
                case 10:
                case 12:
                    actor->trajectoryInitialized = 1;
                    actor->trajectoryPending = 1;
                    actor->trajectoryComplete = 0;
                    break;
                case 6:
                case 8:
                    actor->trajectoryInitialized = 11;
                    actor->trajectoryPending = 0;
                    actor->trajectoryComplete = 1;
                    break;
                case 9:
                    actor->trajectoryInitialized = 1;
                    actor->trajectoryPending = 1;
                    actor->trajectoryComplete = 1;
                    break;
                default:
                case 7:
                case 11:
                if (horizontalDistance == 0.0f) {
                    if (heightDelta < 0.0f) {
                        actor->initialPitch = (f32) -90.0f;
                    } else {
                        actor->initialPitch = (f32) 90.0f;
                    }
                } else {
                    actor->initialPitch = (f32) (XMath_EvaluateArcTangentTwo(heightDelta, horizontalDistance) * 57.2957764f);
                }
                actor->trajectoryPending = 0;
                actor->trajectoryComplete = 0;
                actor->previousPitch = actor->initialPitch;
                actor->previousPitchDelta = actor->pitchDelta = 0.0f;
                return 1;
                }
                    if (horizontalDistance == 0.0f) {
                        if (heightDelta < 0.0f) {
                            actor->targetPitch = -90.0f;
                        } else {
                            actor->targetPitch = 90.0f;
                        }
                    } else {
                        actor->targetPitch = XMath_EvaluateArcTangentTwo(heightDelta, horizontalDistance) * 57.2957764f;
                    }
                    actor->previousPitch = actor->targetPitch;
                    if (45.0f < actor->targetPitch) {
                        actor->pitchSearchStep = 0;
                    } else {
                        initialQuadrant = 1;
                        if (!(actor->targetPitch > 0.0f)) {
                            initialQuadrant = 2;
                            if (!(-45.0f < actor->targetPitch)) {
                                initialQuadrant = 3;
                            }
                        }
                        actor->pitchSearchStep = initialQuadrant;
                    }
                    actor->upperPitchBound = 90.0f - ((f32) actor->pitchSearchStep * 45.0f);
                    actor->lowerPitchBound = actor->targetPitch;
                    actor->targetPitch = (actor->upperPitchBound + actor->lowerPitchBound) * 0.5f;
                    if (actor->trajectoryPending != 0) {
                        actor->previousPitch = actor->targetPitch;
                    }
                    return 0;
            }
        } else {
            if (iterationState < 11) {
                switch (trajectoryMode) {
                case 2: resourceKey = 302; break;
                case 9: resourceKey = 302; break;
                case 10: resourceKey = 302; break;
                case 12: resourceKey = 302; break;
                }
            } else if (iterationState < 21) {
                actor->trajectoryPending = 0;
                switch (trajectoryMode) {
                case 6: resourceKey = 302; break;
                case 8: resourceKey = 302; break;
                case 9: resourceKey = 302; break;
                }
            } else {
                goto block_88;
            }
            {
block_43:
                if (actor->trajectoryInitialized < 21) {
                    ballisticResource = g_ballisticParameterResource;
                    resourceKeys = (void *)SetN64_GetPackSection(ballisticResource, 1);
                    keyCount = resourceKeys->count;
                    if (Defs_FindSortedGroupRange(resourceKeys->keys, keyCount, resourceKey, &first, &last) == 0) {
                        actor->trajectoryPending = 0;
                        actor->trajectoryComplete = 0;
                        actor->trajectoryInitialized = 0;
                        return 1;
                    }
                    {
                        BallisticResourceRecords *records = (void *)SetN64_GetPackSection(ballisticResource, 2);
                        parameterRecord = records->records;
                        parameterRecord += first;
                    }
                    speedParameters = parameterRecord->motion;
                    scale = Rumble_SamplePackedFloatRange((speedParameters->speedHi << 16) | speedParameters->speedLo);
                    gravityParameters = parameterRecord->motion;
                    lateral = Rumble_SamplePackedFloatRange((gravityParameters->gravityHi << 16) | gravityParameters->gravityLo);
                    activeInstance = actor->instance;
                    current = activeInstance->header.spatial.position;
                    delta = actor->destination;
                    deltaX = delta.x - current.x;
                    currentDeltaY = delta.y - current.y;
                    currentDeltaZ = delta.z - current.z;
                    delta.x = deltaX;
                    delta.y = currentDeltaY;
                    delta.z = currentDeltaZ;
                    actor->trajectoryDistance = Gu_Sqrtf((deltaX * deltaX) + (currentDeltaY * currentDeltaY) + (currentDeltaZ * currentDeltaZ));
                    heightDelta = delta.y;
                    delta.y = 0;
                    horizontalDistance = Gu_Sqrtf((delta.x * delta.x) + (delta.z * delta.z));
                    angleCosine = Math_Cosf(actor->targetPitch * 0.0174532942f);
                    angleCosineSquared = angleCosine * angleCosine;
                    trajectoryHeight = (XMath_EvaluateTangent(actor->targetPitch * 0.0174532942f) * horizontalDistance)
                        + ((lateral * (horizontalDistance * horizontalDistance)) / (2.0f * (scale * scale) * angleCosineSquared));
                    if (((heightDelta - 1.0f) <= trajectoryHeight) && (trajectoryHeight <= (heightDelta + 1.0f))) {
                        if (Nav_IsBallisticArcObstructed(actor, scale, lateral) != 0) {
                            obstructedQuadrant = actor->pitchSearchStep;
                            if (obstructedQuadrant > 0) {
                                actor->pitchSearchStep--;
                                actor->upperPitchBound = (f32) (90.0f - ((f32) actor->pitchSearchStep * 45.0f));
                                actor->lowerPitchBound = (f32) (45.0f - ((f32) actor->pitchSearchStep * 45.0f));
                                if (actor->trajectoryPending != 0) {
                                    actor->trajectoryInitialized = 1;
                                } else {
                                    actor->trajectoryInitialized = 11;
                                }
block_54:
                                return 0;
                            }
                        }
                        if ((actor->trajectoryPending != 0) && (actor->trajectoryComplete != 0)) {
                            actor->trajectoryInitialized = 11;
                            actor->trajectoryPending = 0;
                            actor->pitchDelta = (f32) (actor->targetPitch - actor->initialPitch);
                            secondaryPitch = actor->previousPitch;
                            if (45.0f < secondaryPitch) {
                                actor->pitchSearchStep = 0;
                            } else {
                                secondaryQuadrant = 1;
                                if (!(secondaryPitch > 0.0f)) {
                                    secondaryQuadrant = 2;
                                    if (!(-45.0f < secondaryPitch)) {
                                        secondaryQuadrant = 3;
                                    }
                                }
                                actor->pitchSearchStep = secondaryQuadrant;
                            }
                            actor->upperPitchBound = (f32) (90.0f - ((f32) actor->pitchSearchStep * 45.0f));
                            actor->lowerPitchBound = (f32) (45.0f - ((f32) actor->pitchSearchStep * 45.0f));
                            return 0;
                        }
                        actor->trajectoryPending = 0;
                        actor->trajectoryComplete = 0;
                        actor->trajectoryInitialized = (s32) (actor->trajectoryInitialized + 1);
                        actor->pitchDelta = (f32) (actor->targetPitch - actor->initialPitch);
                        return 1;
                    }
                    nextIteration = actor->trajectoryInitialized + 1;
                    if (nextIteration == 11) {
                        fallbackPitch = actor->previousPitch;
                        actor->trajectoryPending = 0;
                        actor->trajectoryInitialized = (s32) (actor->trajectoryInitialized + 1);
                        actor->pitchDelta = (f32) (actor->targetPitch - actor->initialPitch);
                        if (45.0f < fallbackPitch) {
                            actor->pitchSearchStep = 0;
                        } else {
                            fallbackQuadrant = 1;
                            if (!(fallbackPitch > 0.0f)) {
                                fallbackQuadrant = 2;
                                if (!(-45.0f < fallbackPitch)) {
                                    fallbackQuadrant = 3;
                                }
                            }
                            actor->pitchSearchStep = fallbackQuadrant;
                        }
                        actor->upperPitchBound = (f32) (90.0f - ((f32) actor->pitchSearchStep * 45.0f));
                        actor->lowerPitchBound = (f32) (45.0f - ((f32) actor->pitchSearchStep * 45.0f));
                        if (actor->trajectoryComplete == 0) {
                            actor->trajectoryInitialized = 0;
                        }
                        return actor->trajectoryComplete == 0;
                    }
                    if (nextIteration >= 21) {
                        actor->trajectoryPending = 0;
                        actor->trajectoryComplete = 0;
                        actor->trajectoryInitialized = (s32) (actor->trajectoryInitialized + 1);
                        actor->previousPitchDelta = (f32) (actor->targetPitch - actor->previousPitch);
                        return 1;
                    }
                    if (trajectoryHeight < (heightDelta - 1.0f)) {
                        switch (actor->pitchSearchStep) {
                        case 0: actor->upperPitchBound = actor->targetPitch; break;
                        case 1: case 2: case 3: actor->lowerPitchBound = actor->targetPitch; break;
                        }
                    } else {
                        switch (actor->pitchSearchStep) {
                        case 0: actor->lowerPitchBound = actor->targetPitch; break;
                        case 1: case 2: case 3: actor->upperPitchBound = actor->targetPitch; break;
                        }
                    }
                    actor->trajectoryInitialized = (s32) (actor->trajectoryInitialized + 1);
                    actor->targetPitch = (actor->upperPitchBound + actor->lowerPitchBound) * 0.5f;
                    return 0;
                }
                goto block_88;
            }
block_88:
            actor->trajectoryInitialized = 0;
            actor->trajectoryPending = 0;
            actor->trajectoryComplete = 0;
            /* Duplicate return node #89. Try simplifying control flow for better match */
            return 1;
        }
    } else {
        return 1;
    }
}

s32 Nav_IsBallisticArcObstructed(ActorRec *actor, f32 scale, f32 lateral) {
    CVector3 current;
    CVector3 desired;
    CVector3 delta;
    CVector3 acceleration;
    f32 invDuration;
    f32 total;
    f32 segment;
    f32 elapsed;
    f32 accelScale;
    f32 accelX;
    f32 accelY;
    f32 accelZ;
    s32 count;
    s32 i;

    if (actor == 0 || actor->trajectoryDistance == 0.0f) {
        return 0;
    }

    invDuration = g_ballisticInverseDistanceScale / actor->trajectoryDistance;
    delta.x = (actor->destinationX - actor->instance->header.spatial.position.x) * invDuration;
    delta.x *= scale * Math_Cosf(actor->targetPitch);
    delta.z = (actor->destinationZ - actor->instance->header.spatial.position.z) * invDuration;
    delta.z *= scale * Math_Cosf(actor->targetPitch);
    delta.y = scale * Gu_Sinf(actor->targetPitch);

    acceleration.x = 0.0f;
    acceleration.y = lateral;
    acceleration.z = 0.0f;

    total = (scale * Math_Cosf(actor->targetPitch)) / actor->trajectoryDistance;
    if (total == 0.0f) {
        return 0;
    }
    count = (s32)(total * g_ballisticArcSampleRate);
    if (count == 0) {
        return 0;
    }

    segment = total / (f32)count;
    current = actor->instance->header.spatial.position;
    accelScale = segment * segment * g_ballisticAccelerationScale;
    accelX = acceleration.x * accelScale;
    accelY = acceleration.y * accelScale;
    accelZ = acceleration.z * accelScale;

    desired.x = current.x + delta.x * segment + accelX;
    desired.y = current.y + delta.y * segment + accelY;
    desired.z = current.z + delta.z * segment + accelZ;

    elapsed = segment;

    if (CCollision_SweepPoint(&actor->instance->header, current, desired, &g_particleCollisionProbeResult) != 0 &&
        (unsigned)(g_collisionCurrentActor->typeFC - 7) >= 2) {
        return 1;
    }

    i = 0;
    delta.x += acceleration.x * elapsed;
    delta.y += acceleration.x * elapsed;
    delta.z += acceleration.x * elapsed;
    elapsed += segment;

    while (i < count) {
        current = desired;
        desired.x = current.x + delta.x * elapsed + accelX;
        desired.y = current.y + delta.y * elapsed + accelY;
        desired.z = current.z + delta.z * elapsed + accelZ;

        if (CCollision_SweepPoint(&actor->instance->header, current, desired, &g_particleCollisionProbeResult) != 0 &&
            (unsigned)(g_collisionCurrentActor->typeFC - 7) >= 2) {
            return 1;
        }

        delta.x += acceleration.x * elapsed;
        delta.y += acceleration.x * elapsed;
        delta.z += acceleration.x * elapsed;
        elapsed += segment;
        i++;
    }
    return 0;
}

#if defined(VERSION_US)
extern const unsigned int k_navIsballisticarcobstructedFragment[1];
#endif

#if defined(VERSION_DE)
extern const unsigned int k_navIsballisticarcobstructedFragment[1];
#endif

#if defined(VERSION_US_REV1)
void *const g_navBallisticArcCodePointer[1] = {
    (void *)&Playerai_ApplyLinkedProjectileStatus_label2276,
};
#endif



s32 Nav_ShouldSeekUnclaimedTeamMarker(void **controller) {
    char *base;
    f32 seekThreshold;

    base = (char *)&g_matchRoundCounters;
    if (((Shared_MatchRules *)base)->squads == 0) {
        return 0;
    }
    if (((Player *)*controller)->profile->bonus != 0) {
        return 0;
    }
    if (Playerai_FindPlayerWithMarker((char *)&g_playerViewRenderContext) != 0) {
        return 0;
    }
    seekThreshold = Scaled_GetScaledAggression(controller) * g_teamMarkerAggressionScale + g_teamMarkerSeekBaseThreshold;
    if (seekThreshold < Graphu64_RandomBetween(0.0f, g_teamMarkerSeekRandomRange)) {
        return 1;
    }
    return 0;
}

s32 Nav_EvaluateCaptureFlagMarkerSearch(void **controller) {
    if (g_gameSettings.counters.m_bCTFOn != 0) {
        Nav_ShouldSeekUnclaimedTeamMarker(controller);
    }
    return 1;
}



#if defined(VERSION_US)

#endif

#if defined(VERSION_EU_X)
void *const k_playeraiApplyLinkedProjectileStatusCaseAddress[1] = {
    (void *)&Playerai_ApplyLinkedProjectileStatus_label2276,
};
#endif

#if defined(VERSION_DE)
void *const k_navRebuildRequestedGoalRouteCaseAddress[1] = {
    (void *)&Nav_RebuildRequestedGoalRoute_label544,
};
#endif

#if defined(VERSION_US_REV1)
void *const g_navTeamMarkerCodePointer[1] = {
    (void *)&Playerai_ApplyLinkedProjectileStatus_label2276,
};
#endif

/* Commits a pending selection to the controller g_navigationGraph: returns at once when nothing is
   requested, the request is already active, or it continues the committed request
   through valid links that are already current or that Portal_FindLinkIndex joins;
   otherwise it resets the controller, runs the pending release passes for the two flagged
   sides, rebuilds through Nav_SetPickupGoalWeights, loads the request, clears the controller's link word,
   reselects the active entry, copies the four link words and records the request as
   committed. Always returns 1. Written from its own assembly with early returns. */

extern CNavData g_navigationGraph;
extern void Portal_ResetSearchState(struct CNavData_t *graph);
extern void Route_ClearGoalList(s32 cNavData);

extern void Route_SearchPathByKey(void *graph, s32 key);
extern void Route_ReconstructSearchPath(char *owner, s32 *output, s32 count);

s32 Nav_RebuildRequestedGoalRoute(void *controller) {
    s32 *base;
    s32 requested;
    s32 current;
    s32 link;

    base = &g_navigationGraph;
    if (base == 0) {
        return 1;
    }
    requested = ((NavigationRouteControllerView *)controller)->requestedGoalNode;
    if (requested == -1) {
        return 1;
    }
    current = ((NavigationRouteControllerView *)controller)->currentNode;
    if (current == requested) {
        return 1;
    }
    if (((NavigationRouteControllerView *)controller)->committed == requested) {
        link = ((NavigationRouteControllerView *)controller)->links[0];
        if (link != -1 && ((NavigationRouteControllerView *)controller)->links[1] != -1) {
            if (current == link) {
                return 1;
            }
            if (Portal_FindLinkIndex(base, current, link) != -1) {
                return 1;
            }
        }
    }
    Portal_ResetSearchState((CNavData *)base);
    if (((NavigationRouteControllerView *)controller)->releaseFlags[0] != 0) {
        Nav_SetLinkedActorNodeCosts(controller);
    }
    if (((NavigationRouteControllerView *)controller)->releaseFlags[1] != 0) {
        Nav_AccumulateNodeTickCosts(controller);
    }
    if (((NavigationRouteControllerView *)controller)->releaseFlags[2] != 0) {
        Nav_AddPickupCategoryCosts(controller);
    }
    Nav_SetPickupGoalWeights(controller);
    Route_ClearGoalList(base);
    Nav_AddGoalNode(base, ((NavigationRouteControllerView *)controller)->requestedGoalNode);
    base[6] = -1;
    Route_SearchPathByKey(base, ((NavigationRouteControllerView *)controller)->currentNode);
    Route_ReconstructSearchPath(base, &((NavigationRouteControllerView *)controller)->links[0], 4);
    ((NavigationRouteControllerView *)controller)->linkState = 0;
    ((NavigationRouteControllerView *)controller)->selection = -1;
    ((NavigationRouteControllerView *)controller)->committed = ((NavigationRouteControllerView *)controller)->requestedGoalNode;
    return 1;
}

extern char g_actorParticleEffectSystem[];
struct CNavData_t; extern s32 Portal_FindNearestPointIndex(struct CNavData_t *pointSet, void *point);
/* Finds the nav node of obj and stores weight as its goal weight (+0x18). */
#define navigationNodeOf(graph, obj, out) do { (out) = Portal_FindSearchNode((CNavData *)(graph), Portal_FindNearestPointIndex((CNavData *)(graph), (obj))); } while (0)
#define navigationSetGoalWeight(graph, obj, weight) do { u8 *node_; navigationNodeOf(graph, obj, node_); ((NavigationSearchNode *)node_)->extra = (weight); } while (0)
void Nav_SetPickupGoalWeights(void *arg) {
    s32 *ctrl = &g_navigationGraph;
    u8 *node;
    u8 *link;
    s32 i;
    struct EffectSystem *effects = (struct EffectSystem *)g_actorParticleEffectSystem;
    if (g_navigationGraph.points == 0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        for (node = (u8 *)effects->lists[i].head; node != 0; node = (u8 *)((struct Shared_Particle *)node)->next) {
            switch (*(u16 *)(node + 4)) {
            case 1054:
                link = (u8 *)((struct Shared_Particle *)node)->owner;
                if (link == 0 || *link != 1 || !(((LevelActor *)link)->flags & 0x300000) || link == (u8 *)*(s32 **)arg) {
                    break;
                }
            case 1026:
            case 1028:
            case 1035:
            case 1039:
                navigationSetGoalWeight(&g_navigationGraph, (u8 *)&((struct Shared_Particle *)node)->inst.pos, 51200.0f);
                break;
            default:
                break;
            }
        }
    }
}

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_EU_X)
void *const k_PickupgoalData[2] = {
    (void *)&Weapon_FireStateEnterCallbackEntry_label1120, (void *)&Weapon_FireStateEnterCallbackEntry_label948,
};
#endif

#if defined(VERSION_US_REV1)





#endif


struct CNavData_t; extern s32 Portal_SearchRelatedGoalPath(struct CNavData_t *obj, s32 key, s32 requested, void *owner);

/** Reset the float field of each occupied player slot's table entry to the default value. */


s32 Nav_UpdateRouteIntermediateGoal(NavigationRouteControllerView *owner) {
    s32 *base;

    base = &g_navigationGraph;
    if (base != 0) {
        if (owner->destinationNode == -1) {
            return 1;
        }
        if (owner->currentNode == owner->destinationNode) {
            return 1;
        }
        if (Route_GetRouteRelation(base, owner->currentNode, owner->destinationNode) == 0) {
            owner->requestedGoalNode = Portal_SearchRelatedGoalPath((CNavData *)base, owner->currentNode, owner->destinationNode, owner);
        }
    }
    return 1;
}

void Nav_SetLinkedActorNodeCosts(char *actor) {
    CNavData *table = &g_navigationGraph;
    int i;
    float value;

    if (table != 0) {
        value = g_linkedActorNodeDefaultCost;
        for (i = 0; i < 10; i++) {
            Actor1DC *a = ((struct NavigationActorListEntryView *) (actor + (i * 4)))->actor;
            if (a != 0) {
                ((struct NavigationNodeCostView *) Portal_FindSearchNode(table,
                    ((struct ResourceKeyView *) ((NavigationActorSearchStateView *) a->info)->resourceKeyRecord)->key))->cost = value;
            }
        }
    }
}

void Nav_AccumulateNodeTickCosts(void) {
    NavigationSearchNode *node;
    f32 nodeTickCostScale;

    node = g_pickupNavigationGoalList;
    if (node != 0) {
        nodeTickCostScale = g_navigationNodeTickCostScale;
        do {
            node->extra =
                node->extra +
                (f32) (node->ticks * 30) * nodeTickCostScale;
            node = node->next;
        } while (node != 0);
    }
}

void Nav_AddPickupCategoryCosts(void) {
    CNavData *base;
    NavigationSearchNode *node;
    NavigationPoint *result;
    f32 addVal;
    u16 objectId;

    base = &g_navigationGraph;
    node = base->searchNodes.head;
    if (node != 0) {
        addVal = g_pickupCategoryNodeCost;
        do {
            result = Portal_GetGraphPoint(base, node->key);
            if (navigation_point_flags(result) & 1) {
                objectId = navigation_point_object_id(result);
                if (Nav_IsPickupObjectInPairCategory(objectId) != 0 || Nav_IsPickupObjectInSixEntryCategory(navigation_point_object_id(result)) != 0) {
                    node->extra = node->extra + addVal;
                }
            }
            node = node->next;
        } while (node != 0);
    }
}

#if defined(VERSION_US)

#endif

#if defined(VERSION_DE)
void *const k_navFragment[2] = {
    (void *)&Nav_SelectPickupGoal_label188, (void *)&Nav_SelectPickupGoal_label200,
};
#endif

#if defined(VERSION_US_REV1)

#endif

#undef navigationNodeOf
#undef navigationSetGoalWeight

#if !defined(VERSION_EU)
s32 Nav_SelectPickupGoal(PickupGoalControllerView *controller) {
    s32 buffer[30];
    s32 count;
    Shared_PickupGoalNode *record;
    CNavData *base;
    u32 sel;
    s32 *key;

    if (controller->goal == 0) {
        base = &g_navigationGraph;
        for (count = 29; count >= 0; count--) {
            buffer[count] = 0;
        }

        switch (controller->goalSet) {
        case 0:
            buffer[0] = 3014;
            buffer[1] = 3015;
            buffer[2] = 3012;
            buffer[3] = 3013;
            buffer[4] = 3016;
            buffer[5] = 3017;
            buffer[6] = 1722;
            buffer[7] = 1723;
            break;
        case 1:
            buffer[0] = 1722;
            buffer[1] = 1723;
            break;
        case 2:
            buffer[0] = 1722;
            break;
        case 3:
            buffer[0] = 1723;
            break;
        case 4:
            buffer[0] = 3014;
            buffer[1] = 3015;
            buffer[2] = 3012;
            buffer[3] = 3013;
            buffer[4] = 3016;
            buffer[5] = 3017;
            break;
        case 5:
            buffer[0] = 3014;
            buffer[1] = 3015;
            break;
        case 6:
            buffer[0] = 3012;
            buffer[1] = 3013;
            break;
        case 7:
            buffer[0] = 3016;
            buffer[1] = 3017;
            break;
        }

        if (buffer[0] != 0) {
            Portal_ResetSearchState((CNavData *)base);
            Route_ClearGoalList(base);

            key = &controller->searchKey;
            if (Nav_AddPickupGoalsByObjectIds(buffer) == 0) {
                controller->goal = 0;
                controller->goalSet = -1U;
                return 1;
            }

            base->result = -1U;
            Route_SearchPathByKey(base, *key);

            sel = base->result;
            if (sel != -1U) {
                record = Portal_FindSearchNode(base, sel);
                controller->selectedNode = base->result;
                controller->goal = record->goal;
                Route_ReconstructSearchPath(base, controller->history, 4);
                return 1;
            }
            controller->goal = 0;
            controller->goalSet = sel;
        } else {
            controller->goal = 0;
            controller->goalSet = -1U;
        }
    }

    return 1;
}
#endif

#if defined(VERSION_EU)
int Nav_SelectPickupGoalEu(void *self) {
    PickupGoalControllerView *controller = self;
    s32 buffer[30];
    s32 count;
    Shared_PickupGoalNode *record;
    CNavData *base;
    u32 sel;
    s32 *key;

    if (controller->goal == 0) {
        base = &g_navigationGraph;
        for (count = 29; count >= 0; count--) {
            buffer[count] = 0;
        }

        switch (controller->goalSet) {
        case 0:
            buffer[0] = 3014;
            buffer[1] = 3015;
            buffer[2] = 3012;
            buffer[3] = 3013;
            buffer[4] = 3016;
            buffer[5] = 3017;
            buffer[6] = 1722;
            buffer[7] = 1723;
            break;
        case 1:
            buffer[0] = 1722;
            buffer[1] = 1723;
            break;
        case 2:
            buffer[0] = 1722;
            break;
        case 3:
            buffer[0] = 1723;
            break;
        case 4:
            buffer[0] = 3014;
            buffer[1] = 3015;
            buffer[2] = 3012;
            buffer[3] = 3013;
            buffer[4] = 3016;
            buffer[5] = 3017;
            break;
        case 5:
            buffer[0] = 3014;
            buffer[1] = 3015;
            break;
        case 6:
            buffer[0] = 3012;
            buffer[1] = 3013;
            break;
        case 7:
            buffer[0] = 3016;
            buffer[1] = 3017;
            break;
        }

        if (buffer[0] != 0) {
            Portal_ResetSearchState((CNavData *)base);
            Route_ClearGoalList(base);

            key = &controller->searchKey;
            if (Nav_AddPickupGoalsByObjectIds(buffer) == 0) {
                controller->goal = 0;
                controller->goalSet = -1U;
                return 1;
            }

            base->result = -1U;
            Route_SearchPathByKey(base, *key);

            sel = base->result;
            if (sel != -1U) {
                record = Portal_FindSearchNode(base, sel);
                controller->selectedNode = base->result;
                controller->goal = record->goal;
                Route_ReconstructSearchPath(base, controller->history, 4);
                return 1;
            }
            controller->goal = 0;
            controller->goalSet = sel;
        } else {
            controller->goal = 0;
            controller->goalSet = -1U;
        }
    }

    return 1;
}
#endif

/* Selects the nodes of g_navigationGraph's list whose flagged record matches one of thirty ids: every match
   whose owner is active is selected through Nav_AddGoalNode, and when none was, every
   matching node is selected regardless of owner. Returns the number of selections. Written from its
   own assembly in the style of Nav_AddPickupCategoryCosts. */

extern void *Portal_GetGraphPoint(void *, s32);
struct CNavData_t;


s32 Nav_AddPickupGoalsByObjectIds(s32 *ids) {
    s32 *base;
    NavigationSearchNode *node;
    void *record;
    s32 count;
    s32 i;

    base = (s32 *)&g_navigationGraph;
    count = 0;
    for (node = (NavigationSearchNode *)((CNavData *)base)->searchNodes.head; node != 0; node = node->next) {
        record = Portal_GetGraphPoint(base, node->key);
        if (navigation_point_flags((NavigationPoint *)record) & 1) {
            for (i = 0; i < 30; i++) {
                if (navigation_point_object_id((NavigationPoint *)record) == ids[i] && node->object != 0
                    && ((NavigationNodeOwnerView *)node->object)->active != 0) {
                    Nav_AddGoalNode((CNavData *)base, node->key);
                    count++;
                }
            }
        }
    }
    if (count == 0) {
        for (node = (NavigationSearchNode *)((CNavData *)base)->searchNodes.head; node != 0; node = node->next) {
            record = Portal_GetGraphPoint(base, node->key);
            if (navigation_point_flags((NavigationPoint *)record) & 1) {
                for (i = 0; i < 30; i++) {
                    if (navigation_point_object_id((NavigationPoint *)record) == ids[i]) {
                        Nav_AddGoalNode((CNavData *)base, node->key);
                        count++;
                    }
                }
            }
        }
    }
    return count;
}


s32 Nav_SelectCloseAttackPickupGoal(CloseAttackBrain *closeAttackBrain) {
    s32 data[30];
    s32 count;
    CNavData *global;
    s32 value;
    s32 current;
    NavigationSearchNode *entry;

    global = (CNavData *)&g_navigationGraph;
    Portal_ResetSearchState((CNavData *)global);
    Route_ClearGoalList((s32)global);
    for (count = 29; count >= 0; count--) {
        data[count] = 0;
    }
    data[0] = 3031;
    if (Nav_AddPickupGoalsByObjectIds(data) == 0) {
        closeAttackBrain->routeObject = 0;
        closeAttackBrain->routeState = -1;
        return 1;
    }
    value = -1;
    global->result = value;
    Route_SearchPathByKey(global, closeAttackBrain->route);
    current = global->result;
    if (current != value) {
        entry = (NavigationSearchNode *)Portal_FindSearchNode((CNavData *)global, current);
        closeAttackBrain->destination = global->result;
        closeAttackBrain->routeObject = entry->object;
        Route_ReconstructSearchPath(global, &closeAttackBrain->routeNodes[0], 4);
    } else {
        closeAttackBrain->routeObject = 0;
        closeAttackBrain->routeState = current;
    }
    return 1;
}

s32 Nav_SelectChaseObjectGoal(void *controller) {
    s32 data[30];
    s32 count;
    char *global;
    s32 value;
    s32 current;

    global = (char *)&g_navigationGraph;
    Portal_ResetSearchState((CNavData *)global);
    Route_ClearGoalList((s32)global);
    for (count = 29; count >= 0; count--) {
        data[count] = 0;
    }
    data[0] = 1619;
    if (Nav_AddPickupGoalsByObjectIds(data) == 0) {
        ((RouteChaseBot *)controller)->target = 0;
        ((RouteChaseBot *)controller)->targetId = -1;
        return 1;
    }
    value = -1;
    ((CNavData *)global)->result = value;
    Route_SearchPathByKey(global, ((RouteChaseBot *)controller)->node);
    current = ((CNavData *)global)->result;
    if (current != value) {
        ((RouteChaseBot *)controller)->goal = current;
        Route_ReconstructSearchPath(global, &((AiController *)controller)->queue[0], 4);
    }
    return 1;
}

s32 Nav_SelectStationaryObjectGoal(AiController *controller) {
    CNavData *global;
    CNavData *scanbase;
    NavigationSearchNode *node;
    NavigationPoint *result;
    s32 count;
    s32 type;
    s32 value;
    s32 current;

    global = (CNavData *)&g_navigationGraph;
    Portal_ResetSearchState((CNavData *)global);
    Route_ClearGoalList((s32)global);
    count = 0;
    node = g_pickupNavigationGoalList;
    scanbase = global;
    if (node != 0) {
        type = 1614;
        do {
            result = Portal_GetGraphPoint(scanbase, node->key);
            if ((navigation_point_flags(result) & 1) &&
                navigation_point_object_id(result) == type &&
                ((ActorMotionState *)node->object->motion)->mode == 0) {
                Nav_AddGoalNode(scanbase, node->key);
                count += 1;
            }
            node = node->next;
        } while (node != 0);
    }
    if (count == 0) {
        controller->routeObject = 0;
        controller->routeState = -1;
        return 1;
    }
    value = -1;
    global->result = value;
    Route_SearchPathByKey(global, controller->current);
    current = global->result;
    if (current != value) {
        controller->mode = current;
        Route_ReconstructSearchPath(global, &controller->queue, 4);
    }
    return 1;
}

/** Return whether objectId is within the range [0x6BA, 0x6BC). */
s32 Nav_IsPickupObjectInPairCategory(s32 objectId) {
    if (objectId < 1724) {
        if (objectId >= 1722) {
            return 1;
        }
    }
    return 0;
}

/** Return whether objectId is within the range [0xBC4, 0xBCA). */
s32 Nav_IsPickupObjectInSixEntryCategory(s32 objectId) {
    if (objectId < 3018) {
        if (objectId >= 3012) {
            return 1;
        }
    }
    return 0;
}

/** Return the empty result used by callers. */
int Nav_PickupGoalReturnZero(void) {
    return 0;
}

s32 Nav_GetWeaponPickupGoalClass(void **pickupHandle) {
    s32 weaponClassIdResult;
    void *pickupObject;

    pickupObject = *pickupHandle;
    weaponClassIdResult = Playerai_GetWeaponClassId(pickupObject, (s32) ((struct PlayerWeaponClassView *)(pickupObject))->value);
    switch (weaponClassIdResult) {
        case 0:
            return 5;
        case 1:
            return 6;
        case 2:
            return 7;
        default:
            return 4;
    }
}

s32 Nav_AddInactiveObjectGoals(void) {
    s32 *base;
    NavigationSearchNode *node;
    void *result;
    s32 count;

    base = (s32 *)&g_navigationGraph;
    node = ((CNavData *)base)->searchNodes.head;
    count = 0;
    if (node != 0) {
        do {
            result = Portal_GetGraphPoint(base, node->key);
            if ((navigation_point_flags((NavigationPoint *)result) & 1) &&
                navigation_point_object_id((NavigationPoint *)result) == 1614 &&
                (s8)((LevelActor *)node->object)->aiMode == 0) {
                Nav_AddGoalNode((CNavData *)base, node->key);
                count += 1;
            }
            node = node->next;
        } while (node != 0);
    }
    return count;
}

static inline AiTarget *setSelectedTarget(AiController *controller, AiTarget *target) {
    controller->target = target;
    return target;
}

/* Drops the current target when its player is dead, stunned or (in team play) on our team, then picks the
   preferred candidate, the nearest candidate or keeps the current one, and copies its position. */
s32 Target_UpdateTargetSelection(void *object) {
    AiController *controller = object;
    CVector3 *position;
    Player *linked;
    Player *alternate;
    f32 linkedDistance;
    f32 alternateDistance;
    s32 index;
    AiTarget *target;

    position = Scaled_GetControllerPosition(controller);
    if (controller->target != NULL) {
        linked = controller->target->player;
        if (linked->health == 0) {
            controller->target = NULL;
        }
        if (linked->reactionFlags & 0x20) {
            controller->target = NULL;
        }
        if (g_gameSettings.counters.teams != 0) {
            if (controller->player->profile->team == linked->profile->team) {
                controller->target = NULL;
            }
        }
        if (controller->target != NULL) {
            linked = controller->target->player;
            linkedDistance = Graphu64_GetPointDistance(&position->x, &linked->pos.x);
        } else {
            linked = NULL;
            linkedDistance = 0.0f;
        }
    } else {
        linked = NULL;
        linkedDistance = 0.0f;
    }
    if (controller->preferred != NULL && (controller->preferred->flags & 0x300000)) {
        alternate = controller->preferred->player;
        alternateDistance = Graphu64_GetPointDistance(&position->x, &alternate->pos.x);
    } else {
        alternate = NULL;
        alternateDistance = 0.0f;
    }
    if (Scaled_MatchesBehaviorStateFilter(controller) == 0 || linked == NULL) {
        if (Target_CountAcceptedTargets(controller) == 0) {
            controller->target = NULL;
            return 1;
        }
        if (alternate != NULL && Target_IsPreferredTargetAccepted(controller) != 0) {
            controller->target = (AiTarget *)alternate;
            controller->targetPosition.x = alternate->pos.x;
            target = (AiTarget *)alternate;
        } else {
            index = Target_FindNearestFlaggedTarget(controller);
            target = setSelectedTarget(controller, controller->candidates[index]);
            controller->targetPosition.x = target->position.x;
        }
    } else if (alternate != NULL && alternateDistance <= linkedDistance) {
        controller->target = (AiTarget *)alternate;
        controller->targetPosition.x = alternate->pos.x;
        target = (AiTarget *)alternate;
    } else {
        index = Target_FindNearestFlaggedTarget(controller);
        if (index != -1 && (f32)controller->candidateDistances[index] < linkedDistance) {
            target = setSelectedTarget(controller, controller->candidates[index]);
            controller->targetPosition.x = target->position.x;
        } else if (controller->state == 1 && 3072.0f < linkedDistance) {
            controller->target = NULL;
            return 1;
        } else {
            target = controller->target;
            controller->targetPosition.x = target->position.x;
        }
    }
    controller->targetPosition.y = target->position.y;
    controller->targetPosition.z = target->position.z;
    return 1;
}

/* Returns 1 when the preferred target is one of the accepted candidates. */
s32 Target_IsPreferredTargetAccepted(AiController *controller) {
    s32 i;

    if (controller->preferred == NULL) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (controller->candidates[i] == controller->preferred && controller->candidateAccepted[i] != 0) {
            return 1;
        }
    }
    return 0;
}

/* Counts the candidate slots that hold a target and are accepted. */
s32 Target_CountAcceptedTargets(AiController *controller) {
    s32 count;
    s32 i;

    count = 0;
    if (controller->candidateCount == 0) {
        return 0;
    }
    i = 0;
    do {
        if (controller->candidates[i] != NULL && controller->candidateAccepted[i] != 0) {
            count += 1;
        }
        i += 1;
    } while (i < 10);
    return count;
}

/* Returns the index of the nearest accepted candidate whose flags allow targeting, or -1. */
s32 Target_FindNearestFlaggedTarget(AiController *controller) {
    f32 distance;
    f32 unset;
    f32 nearest;
    s32 count;
    s32 mask;
    s32 found;
    s32 i;

    found = -1;
    nearest = -1.0f;
    i = 0;
    if (controller->candidateCount > 0) {
        mask = 0x300000;
        unset = nearest;
        count = controller->candidateCount;
        do {
            if ((controller->candidates[i]->flags & mask) &&
                ((distance = (f32)controller->candidateDistances[i], distance < nearest) || (nearest == unset)) &&
                (controller->candidateAccepted[i] != 0)) {
                nearest = distance;
                found = i;
            }
            i += 1;
        } while (i < count);
    }
    return found;
}

#if defined(VERSION_US)

#endif

#if defined(VERSION_EU_X)

#endif

#if defined(VERSION_EU)

#endif

#if defined(VERSION_DE)

#endif


#if defined(VERSION_US_REV1)

#endif

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
    if (Scaled_IsSeekingPickup(controller) == 0 && healthPercent < (f32)healthThreshold) {
        controller->routeState = 1;
        nextState = 8;
        Scaled_SetBehaviourState(controller, nextState);
        return 1;
    }
    if (Scaled_IsSeekingPickup(controller) == 0 && ammoPercent < 10.0f) {
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
    } else if (Scaled_IsSeekingPickup(controller) != 0 && (f32)healthThreshold < healthPercent && 10.0f < ammoPercent) {
        nextState = 2;
        Scaled_SetBehaviourState(controller, nextState);
        return 1;
    } else if (Scaled_MatchesBehaviorStateFilter(controller) == 0 && Scaled_IsSeekingPickup(controller) == 0 && controller->target != 0) {
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

/* Picks a computer player's next weapon: in state 14 defers to Nav_RequestRandomArmedWeapon; otherwise gathers
 * the loaded weapons it carries (slot kinds, with ammunition and allowed by Nav_IsWeaponAllowed_de),
 * filtering the specials by the record's weapon mode (mode 0 or an unknown mode, reset to 0, skips class-1
 * weapons and treats kind 6 as 5; modes 0 and 1 skip class-2 weapons; mode 2 allows all), and unless it already
 * holds one of them and should keep it (holding kind 4 in gear 2, Particle_CountOwnerListOneEffects reporting a
 * threat, or a 79 percent roll through Nav_RollRandom_de) chooses one at random into 0x770, clearing the brain's
 * switch timer when it changes. */




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
            if (*((WeaponInfo *)g_weaponInfoByType[weapon])->weaponClass == 1) {
                continue;
            }
            if (weapon == 6) {
                weapon = 5;
            }
        second:
            if (*((WeaponInfo *)g_weaponInfoByType[weapon])->weaponClass == 2) {
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
    WeaponSelectionDefinition *definition = (WeaponSelectionDefinition *)brain->player->views18.view18_1.track;
    Nav_SelectAvailableWeapon(brain, definition->ammoGroups[0]);
    return 1;
}

int Nav_SelectWeaponFromSecondAmmoGroup(void *controller) {
    WeaponSelectBrain *brain = controller;
    WeaponSelectionDefinition *definition = (WeaponSelectionDefinition *)brain->player->views18.view18_1.track;
    Nav_SelectAvailableWeapon(brain, definition->ammoGroups[1]);
    return 1;
}

int Nav_SelectWeaponFromThirdAmmoGroup(void *controller) {
    WeaponSelectBrain *brain = controller;
    WeaponSelectionDefinition *definition = (WeaponSelectionDefinition *)brain->player->views18.view18_1.track;
    Nav_SelectAvailableWeapon(brain, definition->ammoGroups[2]);
    return 1;
}

int Nav_SelectSecondAmmoGroupVariantOne(void *controller) {
    WeaponSelectBrain *brain = controller;
    WeaponSelectionDefinition *definition = (WeaponSelectionDefinition *)brain->player->views18.view18_1.track;
    Nav_SelectAvailableWeapon(brain, definition->ammoGroups[1]);
    return 1;
}

int Nav_SelectSecondAmmoGroupVariantTwo(void *controller) {
    WeaponSelectBrain *brain = controller;
    WeaponSelectionDefinition *definition = (WeaponSelectionDefinition *)brain->player->views18.view18_1.track;
    Nav_SelectAvailableWeapon(brain, definition->ammoGroups[1]);
    return 1;
}

void Nav_RequestRandomArmedWeapon(void *brain) {
    AiController *controller = brain;
    s32 chosenWeapon;

    if ((Graphu64_NextRandom() % 100) < 21) {
        do {
            chosenWeapon = Weapon_PickRandomArmedWeapon(controller->player);
        } while (chosenWeapon >= 16);
        ((Player *)controller->player)->weapon = chosenWeapon;
        if (chosenWeapon != ((Player *)controller->player)->selectedAction) {
            controller->actionDelay = 0;
        }
    }
}


#if defined(VERSION_EU_X)

#endif

#if defined(VERSION_EU)

#endif

#if defined(VERSION_US_REV1)

#endif


#if defined(VERSION_US)

#endif

/* Route-following check for a computer driver's brain: when it has a target, it calls UpdateCloseAttack if
 * Nav_CheckTarget_de reports the target reached, and again when its route node (unless -1) lies closer than 100
 * to the position Scaled_GetControllerPosition gives; always returns one. */


struct Player;


s32 Nav_CheckCloseAttackRoute(Brain *brain) {
    void *pos;

    if (brain->target == 0) {
        return 1;
    }
    if (Scaled_HasLineOfSight(brain, brain->target) != 0) {
        UpdateCloseAttack(brain);
    }
    if (brain->destination == -1) {
        return 1;
    }
    pos = Scaled_GetControllerPosition(brain);
    if (Graphu64_GetPointDistance(pos, Portal_GetGraphPoint(&g_navigationGraph, brain->destination)) < 100.0f) {
        UpdateCloseAttack(brain);
    }
    return 1;
}


#if defined(VERSION_EU)
extern const unsigned int k_navFragment[3];
#endif

#if defined(VERSION_DE)
float g_Nav_EvaluateAttackTargetConstants[3] = {
    921.6f, 512.0f, 0.78539824f,
};
#endif

#if defined(VERSION_US)

#endif


#if defined(VERSION_US_REV1)

#endif

/* Runs a computer rider's close attack state: refreshes its view, re-checks line of sight every fourth frame, backs off
   when its target is out of its layer or too close, re-rolls its strafe pattern and steers toward the target. */

struct Brain;




void Nav_UpdatePursuitStrafe(Player *actor) {
    s32 ownStatusBits, targetHasStatus, probeSector, route;
    Player *player;
    Player *target;
    Brain *brain;
    f32 speed;
    s32 pattern;

    brain = ((Brain *)((Player *)actor->actorParts[0].controller)->controller);
    Nav_RunBehaviorHandler(brain);
    player = brain->target;
    if (player != 0) {
        if (!(brain->frames & 3)) {
            brain->visible = Scaled_HasLineOfSight(brain, player);
        }
        brain->frames += 1;
        target = (Player *)((LevelActor *)brain->target)->controller;
        ownStatusBits = ((Player *)brain->player)->movementFlags & 0x3000;
        targetHasStatus = (target->movementFlags & 0x3000) != 0;
        if (ownStatusBits && !targetHasStatus) {
            Scaled_SetBehaviourState(brain, 12);
            return;
        }
        route = ((Brain *)target->controller)->start;
        if (brain->visible != 0) {
            if (Graphu64_GetSquaredDistance(&target->pos, &((Player *)brain->player)->pos) < 360000.0f) {
                brain->combat = 3;
                Scaled_SetBehaviourState(brain, 7);
                return;
            }
            speed = Scaled_ScaleCharacterSettingByDifficulty(brain) * 0.4f;
            if (--brain->timer <= 0) {
                brain->timer = Graphu64_NextRandom() % 4 + 12;
                brain->pattern = Graphu64_NextRandom() % 2;
                if (Graphu64_NextRandom() % 2 == 1) {
                    brain->pattern = 2;
                }
            }
            Nav_SteerTowardPoint(brain, &target->pos, 2.0f, Scaled_UpdateDifficultyAimJitter(brain));
            pattern = brain->pattern;
            if (pattern == 0) {
                probeSector = Wheel_GetDirectionSector((((Player *)brain->player)->heading - 3.1415927f) - 1.5707964f);
                player = ((Player *)brain->player);
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, probeSector);
                }
                if (!(brain->clearance[probeSector] < 100.0f)) {
                    ((Player *)brain->player)->strafe = -speed;
                } else {
                    goto halt;
                }
            } else if (pattern == 1) {
                probeSector = Wheel_GetDirectionSector((((Player *)brain->player)->heading - 3.1415927f) + 1.5707964f);
                player = ((Player *)brain->player);
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, probeSector);
                }
                if (brain->clearance[probeSector] < 100.0f) {
halt:
                    ((Player *)brain->player)->strafe = 0.0f;
                    brain->pattern = 2;
                } else {
                    ((Player *)brain->player)->strafe = speed;
                }
            } else {
                ((Player *)brain->player)->strafe = 0.0f;
            }
            brain->recentNodes[0] = -1;
            Portal_DispatchActorBehavior(brain);
        } else {
            brain->destination = route;
            Nav_SteerAlongRoute(brain);
            Nav_UpdatePlayerSteering(brain);
        }
        if (route != brain->node) {
            brain->node = route;
            if (Route_GetRouteRelation(&g_navigationGraph, brain->start, route) == 0) {
                Scaled_SetBehaviourState(brain, 1);
            }
        }
    }
}

struct Player; struct AiController; struct AiController; struct PlayerAimBrainView; struct CVector3_t; struct Player;
/* Drives combat pursuit, retreat and strafing while refreshing target visibility, routes and fire timing. */


void Nav_UpdateRangedCombat(CloseAttackActor *actor) {
 char *routes;int ownStatusBits, targetHasStatus, probeSector; CloseAttackActor *player;
    CloseAttackActor *target;
    CloseAttackActor *targetActor;
    CloseAttackActor *playerValue;
    CloseAttackBrain *brain;
    CVector3 *targetPosition;
    f32 squaredDistance;
    f32 approachThreshold;
    f32 retreatThreshold;
    f32 strafeSpeed;
    f32 difficultySetting;
    f32 distance;
    f32 desiredSquaredDistance;
    s32 route;
    s32 movementTimer;
    s32 fireTimer;
    s32 unusedValue;
    s32 pattern;
    s32 unusedValue1;
    s32 unusedValue2;
    s32 unusedValue3;
    s32 unusedValue4;
    s32 unusedValue5;
    s32 unusedValue6;

    brain = actor->self->brain;
    Nav_RunBehaviorHandler(brain);
    target = brain->target;routes = (char *)&g_navigationGraph;
    if (target != 0) {
        if (!(brain->frames & 3)) {
            brain->visible = Scaled_HasLineOfSight(brain, target);
        }
        brain->frames += 1;
        targetActor = brain->target->self;
        ownStatusBits = brain->player->flags&0x3000;targetHasStatus = (targetActor->flags&0x3000)!=0;
        if (ownStatusBits && !targetHasStatus) {
            Scaled_SetBehaviourState(brain, 12);return;
        }
        route = targetActor->brain->route;
        if (((NavigationPoint *)Portal_GetGraphPoint(routes, route))->flags & 0x400) {
            brain->target = 0;
            Nav_SelectPlayerState(brain);
            return;
        }
        if (brain->visible != 0) {
            difficultySetting = Scaled_ScaleCharacterSettingByDifficulty(brain);
            movementTimer = brain->timer - 1;
            strafeSpeed = difficultySetting * 0.6f;
            brain->timer = movementTimer;
            if (movementTimer <= 0) {
                brain->timer = Graphu64_NextRandom()%4+12;
                brain->pattern = Graphu64_NextRandom() % 2;
                brain->distance = (Graphu64_NextRandom() % 250000) + 360000;
            }
            targetPosition = &targetActor->pos;
            Nav_SteerTowardPoint(brain, targetPosition, 2.0f, Scaled_UpdateDifficultyAimJitter(brain));
            squaredDistance = Graphu64_GetSquaredDistance(targetPosition, &brain->player->pos);
            approachThreshold = squaredDistance + 10000.0f;
            distance = (f32) brain->distance;
            if (approachThreshold < 0.0f) {
                if (distance < -approachThreshold) {
                    goto block_19;
                }
                goto block_23;
            }
            if (distance < approachThreshold) {
block_19:
                probeSector = Wheel_GetDirectionSector(brain->player->yaw - 3.1415927f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, probeSector);
                }
                if (!(brain->clearance[probeSector] < 100.0f)) {
                    brain->player->forward = 1.0f;
                } else {
                    goto block_31;
                }
            } else {
block_23:
                retreatThreshold = squaredDistance - 10000.0f;
                desiredSquaredDistance = (f32) brain->distance;
                if (retreatThreshold < 0.0f) {
                    if (-retreatThreshold < desiredSquaredDistance) {
                        goto block_27;
                    }
                    goto block_31;
                }
                if (retreatThreshold < desiredSquaredDistance) {
block_27:
                    probeSector = Wheel_GetDirectionSector(brain->player->yaw);
                    player = brain->player;
                    if ((player->slot % 2) == g_lightingBufferIndex) {
                        Wheel_MeasureWheelClearance(player, probeSector);
                    }
                    if (!(brain->clearance[probeSector] < 100.0f)) {
                        brain->player->forward = -1.0f;
                    } else {
                        goto block_31;
                    }
                } else {
block_31:
                    brain->player->forward = 0.0f;
                }
            }
            pattern = brain->pattern;
            if (pattern == 0) {
                probeSector = Wheel_GetDirectionSector((brain->player->yaw - 3.1415927f) - 1.5707964f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, probeSector);
                }
                if (!(brain->clearance[probeSector] < 100.0f)) {
                    brain->player->strafe = -strafeSpeed;
                } else {
                    goto block_41;
                }
            } else if (pattern == 1) {
                probeSector = Wheel_GetDirectionSector((brain->player->yaw - 3.1415927f) + 1.5707964f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, probeSector);
                }
                if (brain->clearance[probeSector] < 100.0f) {
block_41:
                    brain->player->strafe = 0.0f;
                    brain->pattern = 2;
                } else {
                    brain->player->strafe = strafeSpeed;
                }
            } else {
                brain->player->strafe = 0.0f;
            }
            brain->routeNodes[0] = -1;
            fireTimer = brain->fireTimer - 1;
            brain->fireTimer = fireTimer;
            if ((fireTimer == 0) && ((Graphu64_NextRandom() % 100) < (s32) difficultySetting)) {
                playerValue = brain->player;
                playerValue->buttons |= 0x10;
            }
            if (brain->fireTimer < 0) {
                brain->fireTimer = ((Graphu64_NextRandom() % 2) + 2) * 15;
            }
            Portal_DispatchActorBehavior(brain);
        } else {
            brain->destination = route;
            Nav_SteerAlongRoute(brain);
            Nav_UpdatePlayerSteering(brain);
        }
        if (route != brain->node) {
            brain->node = route;
            if (Route_GetRouteRelation(routes, brain->route, route) == 0) {
                Scaled_SetBehaviourState(brain, 1);
            }
        }
    }
}

/* Drives close-range combat: pursuit, retreat and strafing around a target, bailing out when it gets too far away. */

void Nav_UpdateCloseCombat(CloseAttackActor *actor) {
    char *routes;
    s32 ownStatusBits, targetHasStatus, probeSector, route;
    CloseAttackActor *player;
    CloseAttackActor *target;
    CloseAttackBrain *brain;
    CVector3 *pos;
    f32 dist, near, far, range, speed, strafe;
    s32 pattern;

    brain = actor->self->brain;
    Nav_RunBehaviorHandler(brain);
    player = brain->target;
    routes = (char *)&g_navigationGraph;
    if (player != 0) {
        if (!(brain->frames & 3)) {
            brain->visible = Scaled_HasLineOfSight(brain, player);
        }
        brain->frames += 1;
        target = brain->target->self;
        ownStatusBits = brain->player->flags & 0x3000;
        targetHasStatus = (target->flags & 0x3000) != 0;
        if (ownStatusBits && !targetHasStatus) {
            Scaled_SetBehaviourState(brain, 12);
            return;
        }
        route = target->brain->route;
        if (((NavigationPoint *)Portal_GetGraphPoint(routes, route))->flags & 0x400) {
            brain->target = 0;
            Nav_SelectPlayerState(brain);
            return;
        }
        if (brain->visible != 0) {
            speed = Scaled_ScaleCharacterSettingByDifficulty(brain);
            strafe = speed;
            if (--brain->timer <= 0) {
                brain->timer = Graphu64_NextRandom() % 4 + 2;
                brain->pattern = Graphu64_NextRandom() % 2;
                brain->distance = Graphu64_NextRandom() % 32400 + 10000;
            }
            pos = &target->pos;
            Nav_SteerTowardPoint(brain, pos, 2.0f, Scaled_UpdateDifficultyAimJitter(brain));
            dist = Graphu64_GetSquaredDistance(pos, &brain->player->pos);
            if (dist > 377487.3f) {
                brain->combat = 5;
                Scaled_SetBehaviourState(brain, 6);
                return;
            }
            near = dist + 10000.0f;
            range = (f32)brain->distance;
            if (near < 0.0f) {
                if (range < -near) {
                    goto fwd;
                }
                goto back_test;
            }
            if (range < near) {
fwd:
                probeSector = Wheel_GetDirectionSector(brain->player->yaw - 3.1415927f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, probeSector);
                }
                if (!(brain->clearance[probeSector] < 100.0f)) {
                    brain->player->forward = 1.0f;
                } else {
                    goto stop;
                }
            } else {
back_test:
                far = dist - 10000.0f;
                range = (f32)brain->distance;
                if (far < 0.0f) {
                    if (-far < range) {
                        goto back;
                    }
                    goto stop;
                }
                if (far < range) {
back:
                    probeSector = Wheel_GetDirectionSector(brain->player->yaw);
                    player = brain->player;
                    if ((player->slot % 2) == g_lightingBufferIndex) {
                        Wheel_MeasureWheelClearance(player, probeSector);
                    }
                    if (!(brain->clearance[probeSector] < 100.0f)) {
                        brain->player->forward = -1.0f;
                    } else {
                        goto stop;
                    }
                } else {
stop:
                    brain->player->forward = 0.0f;
                }
            }
            pattern = brain->pattern;
            if (pattern == 0) {
                probeSector = Wheel_GetDirectionSector((brain->player->yaw - 3.1415927f) - 1.5707964f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, probeSector);
                }
                if (!(brain->clearance[probeSector] < 100.0f)) {
                    brain->player->strafe = -strafe;
                } else {
                    goto halt;
                }
            } else if (pattern == 1) {
                probeSector = Wheel_GetDirectionSector((brain->player->yaw - 3.1415927f) + 1.5707964f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, probeSector);
                }
                if (brain->clearance[probeSector] < 100.0f) {
halt:
                    brain->player->strafe = 0.0f;
                    brain->pattern = 2;
                } else {
                    brain->player->strafe = strafe;
                }
            } else {
                brain->player->strafe = 0.0f;
            }
            brain->routeNodes[0] = -1;
            if (--brain->fireTimer == 0 && (Graphu64_NextRandom() % 100) < (s32)speed) {
                brain->player->buttons |= 0x10;
            }
            if (brain->fireTimer < 0) {
                brain->fireTimer = ((Graphu64_NextRandom() % 1) + 2) * 15;
            }
            Portal_DispatchActorBehavior(brain);
        } else {
            brain->destination = route;
            Nav_SteerAlongRoute(brain);
            Nav_UpdatePlayerSteering(brain);
        }
        if (route != brain->node) {
            brain->node = route;
            if (Route_GetRouteRelation(routes, brain->route, route) == 0) {
                Scaled_SetBehaviourState(brain, 1);
            }
        }
    }
}

/* Runs a computer player's chase state: refreshes its view through Nav_RunBehaviorHandler and, without a target,
 * returns to roaming (state 2); otherwise re-checks the target's visibility every fourth frame through
 * Nav_CheckTarget_de, backs off (state 12) when only it is on the upper layer, switches to close combat (state
 * 7, sub-state 13) within 600 units, re-rolls its strafe pattern through Nav_RollRandom_de when its timer runs
 * out, steers at the target through Nav_SteerAtTarget_de and strafes left or right at 0.4 of its speed while
 * Wheel_MeasureWheelClearance reports room to walk, stopping otherwise, then drives through
 * Portal_DispatchActorBehavior; losing sight of the target or failing to re-route to the target's new node
 * through Route_GetRouteRelation also returns it to roaming. */

void Nav_UpdateVisiblePursuit(Self *actor) {
    BrainNavUpdateVisiblePursuit *brain;
    s32 ownStatusBits;
    Self *target;
    s32 node;
    f32 speed;
    s32 probeSector;
    s32 roll;
    s32 targetHasStatus;

    brain = actor->self->brain;
    Nav_RunBehaviorHandler(brain);
    if (brain->target == 0) {
        brain->target = 0;
        Scaled_SetBehaviourState(brain, 2);
        return;
    }
    if (!(brain->frames & 3)) {
        brain->visible = Scaled_HasLineOfSight(brain, brain->target);
    }
    brain->frames++;
    target = brain->target->self;
    ownStatusBits = brain->player->flags & 0x3000;
    targetHasStatus = (target->flags & 0x3000) != 0;
    if (ownStatusBits && !targetHasStatus) {
        Scaled_SetBehaviourState(brain, 12);
        return;
    }
    node = target->brain->route;
    if (brain->visible != 0) {
        if (Graphu64_GetSquaredDistance(&target->pos, &brain->player->pos) < 360000.0f) {
            brain->combat = 13;
            Scaled_SetBehaviourState(brain, 7);
            return;
        }
        speed = Scaled_ScaleCharacterSettingByDifficulty(brain) * 0.4f;
        if (--brain->timer <= 0) {
            brain->timer = Graphu64_NextRandom() % 4 + 12;
            brain->pattern = Graphu64_NextRandom() % 2;
            roll = Graphu64_NextRandom();
            if (roll / 2 * 2 == roll - 1) {
                brain->pattern = 2;
            }
        }
        Nav_SteerTowardPoint(brain, &target->pos, 2.0f, Scaled_UpdateDifficultyAimJitter(brain));
        if (brain->pattern == 0) {
            probeSector = Wheel_GetDirectionSector(brain->player->yaw - 3.1415927f - 1.5707964f);
            if (brain->player->slot % 2 == g_lightingBufferIndex) {
                Wheel_MeasureWheelClearance(brain->player, probeSector);
            }
            if (brain->clearance[probeSector] < 100.0f) {
                goto stop;
            }
            brain->player->strafe = -speed;
        } else if (brain->pattern == 1) {
            probeSector = Wheel_GetDirectionSector(brain->player->yaw - 3.1415927f + 1.5707964f);
            if (brain->player->slot % 2 == g_lightingBufferIndex) {
                Wheel_MeasureWheelClearance(brain->player, probeSector);
            }
            if (brain->clearance[probeSector] < 100.0f) {
            stop:
                brain->player->strafe = 0.0f;
                brain->pattern = 2;
            } else {
                brain->player->strafe = speed;
            }
        } else {
            brain->player->strafe = 0.0f;
        }
        brain->routeNodes[0] = -1;
        Portal_DispatchActorBehavior(brain);
    } else {
        brain->target = 0;
        Scaled_SetBehaviourState(brain, 2);
    }
    if (node != brain->node) {
        brain->node = node;
        if (Route_GetRouteRelation(&g_navigationGraph, brain->route, node) == 0) {
            brain->target = 0;
            Scaled_SetBehaviourState(brain, 2);
        }
    }
}

#if !(defined(VERSION_DE))
void Nav_InitPursuitStrafe(void *closeAttackActor) {
    CloseAttackActor *actor = closeAttackActor;
    CloseAttackActor *level1 = actor->self;
    CloseAttackBrain *inner = level1->brain;
    s32 r1, r2;

    inner->state = 0;
    Scaled_ResetBehaviorState(inner);

    r1 = Graphu64_NextRandom();
    inner->timer = r1 % 4 + 12;

    r2 = Graphu64_NextRandom();
    inner->pattern = r2 % 2;
}
#endif

#if !(defined(VERSION_DE))
void Nav_InitRangedCombat(CloseAttackActor *actor) {
    CloseAttackActor *level1 = actor->self;
    CloseAttackBrain *inner = level1->brain;
    s32 r1, r2, r3;

    inner->state = 0;
    Scaled_ResetBehaviorState(inner);

    r1 = Graphu64_NextRandom();
    inner->timer = r1 % 4 + 12;

    r2 = Graphu64_NextRandom();
    inner->pattern = r2 % 2;

    r3 = Graphu64_NextRandom();
    inner->fireTimer = -1;
    inner->frames = 0;
    inner->visible = 0;
    inner->distance = r3 % 250000 + 360000;
}

void Nav_InitCloseCombat(CloseAttackActor *actor) {
    CloseAttackActor *level1 = actor->self;
    CloseAttackBrain *inner = level1->brain;
    s32 r1, r2, r3;

    inner->state = 0;

    r1 = Graphu64_NextRandom();
    inner->timer = r1 % 4 + 2;

    r2 = Graphu64_NextRandom();
    inner->pattern = r2 % 2;

    r3 = Graphu64_NextRandom();
    inner->distance = r3 % 32400 + 10000;

    Scaled_ResetBehaviorState(inner);

    inner->frames = 0;
    inner->visible = 0;
    inner->fireTimer = -1;
}

void Nav_InitVisiblePursuit(CloseAttackActor *actor) {
    CloseAttackActor *level1 = actor->self;
    CloseAttackBrain *inner = level1->brain;
    s32 r1, r2;

    inner->state = 0;
    Scaled_ResetBehaviorState(inner);

    r1 = Graphu64_NextRandom();
    inner->timer = r1 % 4 + 12;

    r2 = Graphu64_NextRandom();
    inner->pattern = r2 % 2;
}
#endif

#if defined(VERSION_US)
/* Zero word ending the COMBAT init object; no instruction reads it. */
unsigned int g_combatInitZeroTail[1] = {
    0x00000000,
};
#endif

#if defined(VERSION_DE)

#endif

/* FARTHEST.CPP */
/* 802106E0_17.CPP */
void *Portal_GetStridedTableEntry(struct CNavData_t *object, int index);
extern void *Portal_GetGraphPoint(void *, s32);
extern f32 Graphu64_GetSquaredDistance(f32 *, f32 *);

/* Choose the farthest reachable neighbor linked by kinds 1, 2 or 7
 * from the actor that this state is following. */
void Nav_SelectFarthestReachableNeighbor(AiController *object)
{
    s32 neighbors[64];
    s32 links[64];
    s32 *linkCursor;
    CVector3 position;
    Player *actor;
    f32 *point;
    f32 distance;
    f32 farthest;
    s32 actor_node;
    register s32 best;
    s32 count;
    s32 i;
    Link *link;
    void *graph = &g_navigationGraph;

    actor = object->target->player;
    actor_node = actor->controller->current;
    position = actor->pos;
    for (i = 0; i < 64; i++) {
        neighbors[i] = -1;
        links[i] = -1;
    }
    linkCursor = links;
    farthest = g_navigationFarthestDistanceAndArrivalLimits[0];
    count = Portal_CollectIncidentLinks(graph, object->current, neighbors, linkCursor);
    best = -1;
    for (i = 0; i < count; i++) {
        link = Portal_GetStridedTableEntry(graph, links[i]);
        if ((link->type >= 1 && link->type <= 2) || link->type == 7) {
            point = Portal_GetGraphPoint(graph, neighbors[i]);
            if (Route_GetRouteRelation(graph, actor_node, neighbors[i])) {
                distance = Graphu64_GetSquaredDistance(&position.x, point);
                if (farthest < distance) {
                    farthest = distance;
                    best = i;
                }
            }
        }
    }
    object->mode = best;
}





struct AiController;

struct AiController;

struct CNavData_t;

struct AiController; extern void Nav_UpdatePlayerSteering(struct AiController *controller);

struct AiController; extern s32 Nav_SelectPlayerState(struct AiController *controller);



void Nav_InitCombatTargetApproach(void *actor) {
    void *brain;
    brain = (((struct Player *) ((s8 *) ((struct LevelActor *) ((s8 *) actor))->controller))->controller);
    (((struct AiController *) ((s8 *) brain))->handlerIndex) = 0;
    Scaled_ResetBehaviorState(brain);
    (((struct AiController *) ((s8 *) brain))->behaviorResetFlag) = 0;
}

void Nav_ApproachCombatTargetAlongRoute(CloseAttackActor *actor)
{
    CloseAttackBrain *state;
    CloseAttackActor *peer;
    CloseAttackActor *peer_actor;
    CloseAttackBrain *peer_state;
    s32 value;

    state = actor->self->brain;
    peer = state->target;
    if (peer == 0) {
        Nav_RunBehaviorHandler(state);
        return;
    }

    peer_actor = peer->self;
    peer_state = peer_actor->brain;
    value = peer_state->route;
    state->destination = value;
    if (value != state->node) {
        state->node = value;
        if (!Route_GetRouteRelation(&g_navigationGraph, state->route, value)) {
            Scaled_SetBehaviourState(state, 1);
            return;
        }
    }

    Nav_RunBehaviorHandler(state);
    Nav_SteerAlongRoute(state);
    Nav_UpdateTargetSteering(state);
    if (Graphu64_GetSquaredDistance(&peer_actor->pos.x,
                       &state->player->pos.x) < g_navigationFarthestDistanceAndArrivalLimits[1] ||
        state->route == state->destination) {
        Scaled_SetBehaviourState(state, state->combat);
    }
}

/** Reset the inner record via Scaled_ResetBehaviorState, then override two of its fields. */
void Nav_InitRetreatMovement(LevelActor *actor) {
    Player *level1 = actor->controller;
    CloseAttackBrain *inner = level1->controller;
    inner->state = 0;
    Scaled_ResetBehaviorState(inner);
    inner->reset2FC = 0;
    inner->destination = -1;
}

void Nav_UpdateRetreatMovement(void *actorObject)
{
    CloseAttackBrain *brain;
    CloseAttackActor *actor = actorObject;
    s32 previousDestination;

    brain = actor->self->brain;
    if (brain->target == 0) {
        Nav_RunBehaviorHandler(brain);
        return;
    }

    previousDestination = brain->destination;
    if (previousDestination == -1) {
        Nav_SelectFarthestReachableNeighbor((AiController *)brain);
        if (brain->destination == previousDestination ||
            brain->destination == brain->route) {
            Scaled_SetBehaviourState(brain, 4);
            return;
        }
    }

    if (g_navigationRetreatDistanceLimit < Graphu64_GetSquaredDistance(
            &brain->target->self->pos.x,
            &brain->player->pos.x)) {
        Scaled_SetBehaviourState(brain, brain->combat);
        return;
    }

    Nav_RunBehaviorHandler(brain);
    Nav_SteerAlongRoute(brain);
    Nav_UpdateTargetSteering(brain);
    if (brain->route == brain->destination) {
        brain->destination = -1;
    }
}

/** Reset the inner record's flag fields, then clear its state via Scaled_ResetBehaviorState. */
void Nav_InitNearbyUnrestrictedGoal(LevelActor *actor) {
    Player *level1 = actor->controller;
    CloseAttackBrain *inner = level1->controller;
    inner->state = 0;
    inner->destination = -1;
    Scaled_ResetBehaviorState(inner);
    inner->reset2FC = 0;
}

void Nav_SeekNearbyUnrestrictedGoal(Shared_Actor *actor)
{
    AiController *state;
    CNavData *table;
    NavigationPoint *entry;
    f32 threshold;
    s32 index;
    s32 value;
    u32 flags;

    state = ((Player *)actor->entity)->controller;
    table = &g_navigationGraph;
    if (state->mode == -1) {
        Portal_ResetSearchState(table);
        Route_ClearGoalList(table);
        threshold = g_navigationNearbyGoalDistanceLimit;
        index = 0;
        if (table->m_nNavNodes > 0) {
            do {
                entry = Portal_GetGraphPoint(table, index);
                if (Graphu64_GetSquaredDistance(&state->player->pos.x, entry) < threshold &&
                    !(navigation_attributes(entry) & 0x04300000)) {
                    Nav_AddGoalNode(table, index);
                }
                index++;
            } while (index < table->m_nNavNodes);
        }
        Route_SearchPathByKey(table, state->current);
        Route_ReconstructSearchPath(table, &state->queue, 4);
        value = table->result;
        state->mode = value;
        state->routeGoal = value;
    }
    Nav_RunBehaviorHandler(state);
    Nav_SteerAlongRoute(state);
    Nav_UpdatePlayerSteering(state);
    flags = (state->player->movementFlags & 0x3000) != 0;
    if (state->current == state->mode &&
        !flags) {
        Nav_SelectPlayerState(state);
    }
}

void Nav_InitUnclaimedMarkerSearch(void *actor) {
    void *brain;
    brain = (((struct Player *) ((s8 *) ((struct LevelActor *) ((s8 *) actor))->controller))->controller);
    (((struct AiController *) ((s8 *) brain))->handlerIndex) = 0;
    Scaled_ResetBehaviorState(brain);
    (((struct AiController *) ((s8 *) brain))->behaviorResetFlag) = 0;
}

void Nav_SeekUnclaimedMarker(void *actorStorage) {
    s32 *behaviorWords;
    void *markerHolder;

    LevelActor *object = actorStorage;
    Player *actor = object->controller;

    behaviorWords = (s32 *)actor->controller;
    markerHolder = Playerai_FindPlayerWithMarker((char *)&g_playerViewRenderContext);
    if (markerHolder == (void *) *behaviorWords) {
        Scaled_SetBehaviourState(behaviorWords, 10);
        return;
    }
    if (markerHolder != 0) {
        Scaled_SetBehaviourState(behaviorWords, 2);
        return;
    }
    Nav_RunBehaviorHandler(behaviorWords);
    Scaled_DistanceToNode(behaviorWords, behaviorWords[3]);
    Nav_SteerAlongRoute(behaviorWords);
    Nav_UpdateTargetSteering(behaviorWords);
}

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)







#endif

void Nav_InitCarrierRoute(AiTarget *aiTarget) {
    AiController *controller;
    controller = aiTarget->player->controller;
    ((CloseAttackBrain *)controller)->state = 0;
    Scaled_ResetBehaviorState(controller);
    controller->behaviorResetFlag = 0;
}

void Nav_FollowMarkerCarrierRoute(AiTarget *aiTarget) {
    AiController *controller;
    void *markerHolder;

    controller = aiTarget->player->controller;
    markerHolder = Playerai_FindPlayerWithMarker((char *)&g_playerViewRenderContext);
    if (markerHolder == 0 || markerHolder != (void *)controller->player) {
        Scaled_SetBehaviourState(controller, 2);
        return;
    }
    controller = aiTarget->player->controller;
    Nav_RunBehaviorHandler(controller);
    Scaled_DistanceToNode(controller, controller->mode);
    Nav_SteerAlongRoute(controller);
    Nav_UpdateTargetSteering(controller);
}

#if defined(VERSION_US)
#if defined(VERSION_US)
const struct {
    f32 g_patrolGoalArrivalDistance;
    u8 retainedArrivalWords[12];
    f32 g_objectChaseRouteDistanceLimit;
    f32 g_objectChaseArrivalDistance;
    u8 retainedEffectTagText[8];
    f32 g_timedJumpRouteArrivalDistance;
    u8 retainedJumpWords[12];
} g_navPatrolRouteDistanceLimits __attribute__((aligned(4))) = {
    102.399994f,
    { 0x52, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa, 0x0, 0x8, 0x0, 0x1c },
    102.399994f,
    51.1999969f,
    { 0x65, 0x72, 0x46, 0x78, 0x5f, 0x74, 0x54, 0x0 },
    102.399994f,
    { 0x0, 0x8, 0x0, 0x8, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7 }
};
typedef char g_navPatrolRouteDistanceLimitsSizeCheck[(sizeof(g_navPatrolRouteDistanceLimits) == 48) ? 1 : -1];
#endif
#endif

#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    u8 retainedRecordWords[8];
} k_navUpdateobjectarrivalchaseFragment __attribute__((aligned(4))) = {
    { 0x00, 0x0B, 0x58, 0x42, 0x01, 0x64, 0x60, 0x24 }
};
#endif
#endif

#if defined(VERSION_EU_X)
float k_navUpdateobjectarrivalchaseFragment[2] = {
    48.0f, 255.0f,
};
#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
f32 g_navUpdateobjectarrivalchaseDataFloatConstants[2] = {
    30.0f, 0.0f
};
#endif
#endif

#if defined(VERSION_DE)

#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#if defined(VERSION_EU)
const f32 k_navUpdateobjectarrivalchaseDataFloatConstants[2] = {
    102.399994f, 51.1999969f
};
#endif
#if defined(VERSION_EU_X)
const f32 k_navUpdateobjectarrivalchaseDataFloatConstants[2] = {
    102.399994f, 51.1999969f
};
#endif
#if defined(VERSION_US_REV1)
const f32 k_navUpdateobjectarrivalchaseDataFloatConstants[2] = {
    102.399994f, 51.1999969f
};
#endif
#endif

#if defined(VERSION_DE)
extern const float g_Nav_ResetPatrolRouteSelectionConstants[2];
#endif

#if defined(VERSION_DE)
/* Fuzzy draft: the other versions' body, not diffed against this version's asm. */
/* Runs a computer player's chase step toward the object: without a target id it
   switches to mode 2 and without an object it only updates; farther than g_objectChaseRouteDistanceLimit from its goal
   node it heads there through Nav_SteerAlongRoute, otherwise it takes mode 8 once arrived or copies the
   object's position to 0x2C; then, within g_objectChaseArrivalDistance of the object and not yet arrived, it marks
   arrival and plans a new route through Portal_CollectDirectedNeighbors to pick the next goal node. */

extern CNavData g_navigationGraph;
extern const f32 g_Nav_ResetPatrolRouteSelectionConstantWords[2];

struct CNavData_t;


void Nav_UpdateObjectArrivalChase(RouteChaseActor *actor)
{
    s32 path[64];
    RouteChaseBot *bot = actor->player->bot;
    CNavData *graph = &g_navigationGraph;
    f32 dist;
    s32 i;
    s32 pathLength;
    s32 start;
    s32 none;

    if (bot->targetId == -1) {
        Scaled_SetBehaviourState(bot, 2);
        return;
    }
    if (bot->target == 0) {
        Nav_RunBehaviorHandler(bot);
        return;
    }
    dist = Scaled_DistanceToNode(bot, bot->goal);
    if (bot->node != bot->goal && g_Nav_ResetPatrolRouteSelectionConstants[0] < dist) {
        Nav_SteerAlongRoute(bot);
    } else if (bot->arrived != 0) {
        Scaled_SetBehaviourState(bot, 8);
    } else {
        bot->dest = bot->target->pos;
    }
    Nav_RunBehaviorHandler(bot);
    if (bot->target != 0) {
        Nav_UpdateTargetSteering(bot);
        if (Graphu64_GetPointDistance(&bot->self->pos, &bot->target->pos) < g_Nav_ResetPatrolRouteSelectionConstants[1] && bot->arrived == 0) {
            bot->arrived = 1;
            none = -1;
            for (i = 63; i >= 0; i--) {
                path[i] = none;
            }
            Portal_CollectDirectedNeighbors(graph, bot->goal, bot->goal, path, 0);
            start = path[0];
            none = -1;
            for (i = 63; i >= 0; i--) {
                path[i] = none;
            }
            pathLength = Portal_CollectDirectedNeighbors(graph, start, bot->goal, path, 0);
            Scaled_ClearNodeQueue(bot);
            bot->goal = path[pathLength - 1];
        }
    }
}
#endif

#if !defined(VERSION_DE)
/* Fuzzy draft: the other versions' body, not diffed against this version's asm. */
/* Runs a computer player's chase step toward the object: without a target id it
   switches to mode 2 and without an object it only updates; farther than g_objectChaseRouteDistanceLimit from its goal
   node it heads there through Nav_SteerAlongRoute, otherwise it takes mode 8 once arrived or copies the
   object's position to 0x2C; then, within g_objectChaseArrivalDistance of the object and not yet arrived, it marks
   arrival and plans a new route through Portal_CollectDirectedNeighbors to pick the next goal node. */

extern CNavData g_navigationGraph;

struct AiController; extern s32 Scaled_SetBehaviourState(struct AiController *controller, s32 behaviourId);
extern void Nav_RunBehaviorHandler(void *aiController);

struct AiController; extern void Nav_SteerAlongRoute(struct AiController *controller);

struct CNavData_t;


void Nav_UpdateObjectArrivalChase(RouteChaseActor *actor)
{
    s32 path[64];
    RouteChaseBot *bot = actor->player->bot;
    CNavData *graph = &g_navigationGraph;
    f32 dist;
    s32 i;
    s32 pathLength;
    s32 start;
    s32 none;

    if (bot->targetId == -1) {
        Scaled_SetBehaviourState(bot, 2);
        return;
    }
    if (bot->target == 0) {
        Nav_RunBehaviorHandler(bot);
        return;
    }
    dist = Scaled_DistanceToNode(bot, bot->goal);
    if (bot->node != bot->goal && g_objectChaseRouteDistanceLimit < dist) {
        Nav_SteerAlongRoute(bot);
    } else if (bot->arrived != 0) {
        Scaled_SetBehaviourState(bot, 8);
    } else {
        bot->dest = bot->target->pos;
    }
    Nav_RunBehaviorHandler(bot);
    if (bot->target != 0) {
        Nav_UpdateTargetSteering(bot);
        if (Graphu64_GetPointDistance(&bot->self->pos, &bot->target->pos) < g_objectChaseArrivalDistance && bot->arrived == 0) {
            bot->arrived = 1;
            none = -1;
            for (i = 63; i >= 0; i--) {
                path[i] = none;
            }
            Portal_CollectDirectedNeighbors(graph, bot->goal, bot->goal, path, 0);
            start = path[0];
            none = -1;
            for (i = 63; i >= 0; i--) {
                path[i] = none;
            }
            pathLength = Portal_CollectDirectedNeighbors(graph, start, bot->goal, path, 0);
            Scaled_ClearNodeQueue(bot);
            bot->goal = path[pathLength - 1];
        }
    }
}
#endif

void Nav_ResetObjectArrivalChase(void *actor) {
    void *brain;
    brain = (((struct Player *) ((s8 *) ((struct LevelActor *) ((s8 *) actor))->controller))->controller);
    (((struct NavigationChaseResetView *) ((s8 *) brain))->target) = 0;
    (((struct NavigationChaseResetView *) ((s8 *) brain))->arrived) = 0;
    (((struct NavigationChaseResetView *) ((s8 *) brain))->closeAttackState) = 0;
    Scaled_ResetBehaviorState(brain);
}

/* JUMPROUTE.CPP */
/* 80212C90_10.CPP */
void Nav_InitTimedJumpRoute(LevelActor *actor) {
    AiController *inner;

    inner = (AiController *)((Player *)actor->controller)->controller;
    inner->handlerIndex = 0;
    Scaled_ResetBehaviorState(inner);
    inner->jumpTimer = -1;
    inner->behaviorResetFlag = 0;
}

struct AiController;

void Nav_UpdateTransientJumpRoute(LevelActor *actor)
{
    void *state;
    s32 random;
    s32 actor_state;
    u32 flags;

    state = ((Player *)actor->controller)->controller;
    if (((AiController *)state)->player->profile->bonus == 0) {
        Scaled_SetBehaviourState(state, 2);
        return;
    }

    Nav_RunBehaviorHandler(state);
    if (--((AiController *)state)->jumpTimer == 0) {
        actor_state = ((AiController *)state)->player->pose;
        flags = ((AiController *)state)->player->movementFlags;
        actor_state ^= 15;
        flags = (flags & 0x3000) != 0;
        if (actor_state != 0 && !flags) {
            ((AiController *)state)->player->actionFlags |= 0x10;
        }
    }

    if (((AiController *)state)->jumpTimer < 0) {
        random = Graphu64_NextRandom();
        ((AiController *)state)->jumpTimer = ((random % 5) + 3) * 15;
    }

    if (Scaled_DistanceToNode(state, ((AiController *)state)->mode) < g_timedJumpRouteArrivalDistance) {
        ((AiController *)state)->player->actionFlags |= 0x10;
    }
    Nav_SteerAlongRoute(state);
    Nav_UpdatePlayerSteering(state);
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)

#endif

#if defined(VERSION_EU_X)
extern const unsigned int k_jumprouteFragment[3];
#endif

#if defined(VERSION_EU)
extern const unsigned int k_jumprouteFragment[3];
#endif

#if defined(VERSION_DE)

#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)

#endif
#endif

void Nav_SelectFlaggedRoamingGoal(void *controller)
{
    s32 choices[32];
    s32 count;
    s32 result;
    s32 fill;

    result = 0;
    count = result;
    fill = -1;
    {
        s32 index = 31;
        do {
            choices[index] = fill;
            index--;
        } while (index >= 0);

        {
            s32 *table = &g_navigationGraph;
        index = 0;
        if (table[1] > 0) {
            do {
                if (navigation_point_flags((NavigationPoint *)Portal_GetGraphPoint(table, index)) & 0x800) {
                    choices[count] = index;
                    count++;
                }
                index++;
            } while (index < table[1]);
        }
        }
    }

    if (count == 0) {
        s32 global_count = g_navigationNodeCount;
        s32 *table = &g_navigationGraph;
        s32 tries = 0;
        s32 candidate;
        if (global_count >= 2) {
            candidate = ((AiController *)controller)->roamingGoal;
loop:
            if (tries < 10) {
                candidate = Graphu64_NextRandom() % table[1];
                if (navigation_point_flags((NavigationPoint *)Portal_GetGraphPoint(table, candidate)) & 0x400) {
                    candidate = ((AiController *)controller)->roamingGoal;
                }
                tries++;
                if (candidate != ((AiController *)controller)->roamingGoal) {
                    goto store_both;
                }
                goto loop;
            } else {
                ((AiController *)controller)->roamingGoal = candidate;
                goto store_c;
            }
        } else {
            candidate = 1;
        }
store_both:
        ((AiController *)controller)->roamingGoal = candidate;
store_c:
        ((AiController *)controller)->mode = candidate;
    } else {
        result = choices[Graphu64_NextRandom() % count];
    }

    ((AiController *)controller)->roamingGoal = result;
    ((AiController *)controller)->mode = result;
}

/* Runs a computer player's think step: when it has reached its goal node or the goal is past
   the node count g_navigationNodeCount, it picks a new goal as Nav_InitRoamingWithJumps does (Nav_SelectFlaggedRoamingGoal for a player
   flagged in mode 12, otherwise up to ten random nodes of g_navigationGraph not flagged 0x400); then
   it counts down the jump timer and on expiry makes its player jump (bit 0x10)
   unless the player is in state 0xF, holds input bits 0x3000 or the bot is busy, rerolls an
   expired timer to 15 times 3 to 9 frames, and runs Nav_RunBehaviorHandler, Nav_SteerAlongRoute and Nav_UpdatePlayerSteering. */

struct AiController;

void Nav_UpdateRoamingWithJumps(Shared_Actor *actorContext) {
    void *actor = ((Player *)(actorContext->entity))->controller;
    void *player;
    s32 busy;
    s32 held;
    s32 state;

    if (((AiController *)(actor))->current == ((AiController *)(actor))->roamingGoal
        || !(((AiController *)(actor))->roamingGoal < g_navigationNodeCount)) {
        void *data = ((Player *)(*(void **) actor))->profile;
        if (((PlayerProfileStatusView *)(data))->display && ((PlayerProfileStatusView *)(data))->kind == 12) {
            Nav_SelectFlaggedRoamingGoal(actor);
        } else {
            s32 global_count = g_navigationNodeCount;
            s32 *table = &g_navigationGraph;
            s32 tries = 0;
            s32 candidate;

            if (global_count >= 2) {
                candidate = ((AiController *)(actor))->roamingGoal;
loop:
                if (tries < 10) {
                    candidate = Graphu64_NextRandom() % table[1];
                    if (navigation_point_flags((NavigationPoint *)(Portal_GetGraphPoint(table, candidate))) & 0x400) {
                        candidate = ((AiController *)(actor))->roamingGoal;
                    }
                    tries++;
                    if (candidate != ((AiController *)(actor))->roamingGoal) {
                        goto store_both;
                    }
                    goto loop;
                } else {
                    ((AiController *)(actor))->roamingGoal = candidate;
                    goto store_c;
                }
            } else {
                candidate = 1;
            }
store_both:
            ((AiController *)(actor))->roamingGoal = candidate;
store_c:
            ((AiController *)(actor))->mode = candidate;
        }
    }
    if (--((AiController *)(actor))->jumpTimer == 0) {
        player = *(void **) actor;
        state = ((Player *)(player))->pose != 15;
        busy = ((AiController *)(actor))->linkTraversalPhase != 0;
        held = (((Player *)(player))->movementFlags & 0x3000) != 0;
        if (state && !held && !busy) {
            ((Player *)(player))->actionFlags |= 0x10;
        }
    }
    if (((AiController *)(actor))->jumpTimer < 0) {
        ((AiController *)(actor))->jumpTimer = (Graphu64_NextRandom() % 7 + 3) * 15;
    }
    Nav_RunBehaviorHandler(actor);
    Nav_SteerAlongRoute(actor);
    Nav_UpdatePlayerSteering(actor);
}

void Nav_InitRoamingWithJumps(Shared_Actor *actorStorage)
{
    void *actor = ((Player *)(actorStorage->entity))->controller;

    ((AiController *)(actor))->handlerIndex = 0;
    {
        void *data = ((Player *)(*(void **)actor))->profile;
        if (((PlayerProfileStatusView *)(data))->display && ((PlayerProfileStatusView *)(data))->kind == 12) {
            Nav_SelectFlaggedRoamingGoal(actor);
        } else {
            s32 global_count = g_navigationNodeCount;
            s32 *table = &g_navigationGraph;
            s32 tries = 0;
            s32 candidate;

            if (global_count >= 2) {
                candidate = ((AiController *)(actor))->roamingGoal;
loop:
                if (tries < 10) {
                    candidate = Graphu64_NextRandom() % table[1];
                    if (navigation_point_flags((NavigationPoint *)(Portal_GetGraphPoint(table, candidate))) & 0x400) {
                        candidate = ((AiController *)(actor))->roamingGoal;
                    }
                    tries++;
                    if (candidate != ((AiController *)(actor))->roamingGoal) {
                        goto store_both;
                    }
                    goto loop;
                } else {
                    ((AiController *)(actor))->roamingGoal = candidate;
                    goto store_c;
                }
            } else {
                candidate = 1;
            }
store_both:
            ((AiController *)(actor))->roamingGoal = candidate;
store_c:
            ((AiController *)(actor))->mode = candidate;
        }
    }
    Scaled_ResetBehaviorState(actor);
    ((AiController *)(actor))->jumpTimer = -1;
}

void Nav_ChooseNewRoamingGoal(void *controller)
{
    s32 *table = &g_navigationGraph;
    s32 tries = 0;
    s32 candidate;

    if (table[1] >= 2) {
        candidate = ((AiController *)(controller))->roamingGoal;
loop:
        if (tries < 10) {
            candidate = Graphu64_NextRandom() % table[1];
            if (navigation_point_flags((NavigationPoint *)(Portal_GetGraphPoint(table, candidate))) & 0x400) {
                candidate = ((AiController *)(controller))->roamingGoal;
            }
            tries++;
            if (candidate != ((AiController *)(controller))->roamingGoal) {
                goto store_both;
            }
            goto loop;
        } else {
            ((AiController *)(controller))->roamingGoal = candidate;
            goto store_c;
        }
    } else {
        candidate = 1;
    }
store_both:
    ((AiController *)(controller))->roamingGoal = candidate;
store_c:
    ((AiController *)(controller))->mode = candidate;
}

/* Retained data for this translation unit. */
#if defined(VERSION_US)
const char s_FindOshEdgeTCSText[12] =
    "oshEdge_t\013CS";
#endif
#if defined(VERSION_EU)
const unsigned int k_findFragment[3] = {
    0x00000000, 0x0007000D, 0x2401FFFF,
};
#endif
#if defined(VERSION_DE)
const unsigned int k_FindData[3] = {
    0x3F800000, 0x3F800000, 0x0C0AC91C,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Nav_ComputeScaledPointCentroidConstantWords[1] = {
    1.0f,
};
#endif

const float k_NavIsballisticarcobstructedData[3] = {
    1.0f, 1.3333334f, 0.5f,
};

const float g_Nav_ShouldSeekUnclaimedTeamMarkerConstantWords[3] = {
    0.6f, 0.2f, 1.0f,
};
#if defined(VERSION_US)
const unsigned int k_TeammarkerData[1] = {
    0x4353776F,
};
#endif
#if !(defined(VERSION_US_REV1))
const float g_Nav_SetLinkedActorNodeCostsConstantWords_de_eu_eu_x_us[3] = {
    51200.0f, 10.24f, -614.39996f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Nav_SetLinkedActorNodeCostsConstantWords_us_rev1[1] = {
    51200.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Nav_AccumulateNodeTickCostsConstantWords[1] = {
    10.24f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Nav_AddPickupCategoryCostsConstantWords[1] = {
    -614.39996f,
};
#endif
#if defined(VERSION_US)
const unsigned int k_RoutecostData[2] = {
    0x14000000, 0x00000E43,
};
#endif
#if defined(VERSION_US_REV1)
const unsigned int g_navRouteCostUnitWeights[2] = {
    0x3F800000, 0x3F800000,
};
#endif
#if defined(VERSION_US)
const unsigned int k_SetselectedtargetData[2] = {
    0x08000000, 0x00001043,
};
#endif
#if defined(VERSION_EU_X)
const unsigned int k_setSelectedTargetScalePair[2] = {
    0x3FE52EDF, 0x3FE52EDF,
};
#endif
#if defined(VERSION_EU)
const unsigned int k_setSelectedTargetLoadByteInstructionWords[2] = {
    0x00000000, 0x90420000,
};
#endif
#if defined(VERSION_DE)
const unsigned int k_setSelectedTargetUnitAndRangeFloats[2] = {
    0x3F800000, 0x42A00000,
};
#endif
#if defined(VERSION_US_REV1)
const unsigned int g_Target_FindNearestFlaggedTargetConstants[2] = {
    0x3DCCCCCD, 0x3C8EFA36,
};
#endif
#if defined(VERSION_EU_X)
const unsigned int k_actionMixedConstantFragments[2] = {
    0x3C5F0B72, 0x3FE52EDF,
};
#endif
#if defined(VERSION_EU)
const unsigned int k_ActionMixedConstantFragmentsData[2] = {
    0x01014824, 0x40896000,
};
#endif
#if defined(VERSION_US_REV1)
const unsigned int g_NavSelectplayerstateData[2] = {
    0x3F800000, 0x3FE52EDF,
};
#endif
#if defined(VERSION_US)
const char s_OvldatELoaderRText[8] =
    "eLoaderR";
#endif
#if defined(VERSION_US)
const unsigned int k_NavCheckCloseAttackRouteWordsUs[3] = {
    0x00000800, 0x11000000, 0x0000086D,
};
#endif
#if defined(VERSION_US_REV1)
const float g_navCloseAttackRouteDistanceFloats[3] = {
    1.0f, 1.0f, 25.0f,
};
#endif
#if !(defined(VERSION_US_REV1))
const float g_Nav_SelectFarthestReachableNeighborConstantWords_de_eu_eu_x_us[4] = {
    -1.0f, 212336.62f, 849346.5f, 1048576.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Nav_SelectFarthestReachableNeighborConstantWords_us_rev1[1] = {
    -1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Nav_ApproachCombatTargetAlongRouteConstantWords[1] = {
    212336.62f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Nav_UpdateRetreatMovementConstantWords[1] = {
    849346.5f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Nav_SeekNearbyUnrestrictedGoalConstantWords[1] = {
    1048576.0f,
};
#endif
#if defined(VERSION_DE)
const unsigned int k_NavUpdateobjectarrivalchaseData[2] = {
    0x24040001, 0xAFBF0028,
};
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
const float g_Nav_UpdateTransientJumpRouteConstantWords[1] = {
    102.399994f,
};
#endif
#if defined(VERSION_DE)
const unsigned int k_JumprouteData[3] = {
    0x43000000, 0x41F00000, 0x00000000,
};
#endif
#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
const f32 g_navJumpRouteOffsetFloats[3] = {
    0.0f, 30.0f, 0.0f
};
#endif
#endif
#if !(defined(VERSION_US_REV1))
const float g_pointCentroidUnitScale = 1.0f;
#endif
#if defined(VERSION_US)
const unsigned int k_navIsballisticarcobstructedFragment[1] = {
    0x52000000,
};
#endif
#if defined(VERSION_DE)
const unsigned int k_navIsballisticarcobstructedFragment[1] = {
    0x10400002,
};
#endif
#if defined(VERSION_EU)
const unsigned int k_navFragment[3] = {
    0x00000000, 0x03E00008, 0x00000000,
};
#endif
#if defined(VERSION_DE)
const float g_Nav_ResetPatrolRouteSelectionConstants[2] = {
    102.399994f, 51.199997f,
};
#endif
#if defined(VERSION_EU_X)
const unsigned int k_jumprouteFragment[3] = {
    0x00000000, 0x41F00000, 0x00000000,
};
#endif
#if defined(VERSION_EU)
const unsigned int k_jumprouteFragment[3] = {
    0x216BFFFF, 0x40021000, 0x04010002,
};
#endif
