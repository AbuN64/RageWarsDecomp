#include "COMMON/NAVIGATION_ACTOR_SEARCH_VIEWS.H"
#include "AI/SHARED_PICKUPGOALNODE.H"
#include "AI/NAV/NAV_SELECTPICKUPGOAL.H"
#include "AI/NAV/NAV_SELECTPICKUPGOALEU.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include "include_asm.h"
#include "COMMON/MEASURED_STORAGE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/ROUTE_CHASE_RECORDS.H"
#include "COMMON/REC.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/SELF.H"
#include "AI/NAV/PICKUPTARGET.H"

/* PICKUPSELECT.CPP */
/* 8020EAE0_4.CPP */
#if !defined(VERSION_EU)
s32 Nav_SelectPickupGoal(PickupGoalControllerView *controller) {
    s32 buffer[30];
    s32 count;
    Shared_PickupGoalNode *record;
    PickupGoalNodeList *base;
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
            Portal_ResetSearchState(base);
            Route_ClearGoalList(base);

            key = &controller->searchKey;
            if (Nav_AddPickupGoalsByObjectIds(buffer) == 0) {
                controller->goal = 0;
                controller->goalSet = -1U;
                return 1;
            }

            base->selected = -1U;
            Route_SearchPathByKey(base, *key);

            sel = base->selected;
            if (sel != -1U) {
                record = Portal_FindSearchNode(base, sel);
                controller->selectedNode = base->selected;
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

/* 8020EAE0_5.CPP */
#if defined(VERSION_EU)
int Nav_SelectPickupGoalEu(void *self) {
    PickupGoalControllerView *controller = self;
    s32 buffer[30];
    s32 count;
    Shared_PickupGoalNode *record;
    PickupGoalNodeList *base;
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
            Portal_ResetSearchState(base);
            Route_ClearGoalList(base);

            key = &controller->searchKey;
            if (Nav_AddPickupGoalsByObjectIds(buffer) == 0) {
                controller->goal = 0;
                controller->goalSet = -1U;
                return 1;
            }

            base->selected = -1U;
            Route_SearchPathByKey(base, *key);

            sel = base->selected;
            if (sel != -1U) {
                record = Portal_FindSearchNode(base, sel);
                controller->selectedNode = base->selected;
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

/* PICKUPTARGET.CPP */
/* Selects the nodes of g_navigationGraph's list whose flagged record matches one of thirty ids: every match
   whose owner at 0x34 is active at 0x294 is selected through Nav_AddGoalNode, and when none was, every
   matching node is selected regardless of owner. Returns the number of selections. Written from its
   own assembly in the style of Nav_AddPickupCategoryCosts. */

extern void *Portal_GetGraphPoint(void *, s32);
struct ObjNavAddGoalNode;
extern void Nav_AddGoalNode(struct ObjNavAddGoalNode *, int);

s32 Nav_AddPickupGoalsByObjectIds(s32 *ids) {
    s32 *base;
    NavigationSearchNodeView *node;
    void *record;
    s32 count;
    s32 i;

    base = (s32 *)&g_navigationGraph;
    count = 0;
    for (node = (NavigationSearchNodeView *)((NavigationSearchGraphView *)base)->nodes; node != 0; node = node->next) {
        record = Portal_GetGraphPoint(base, node->key);
        if (navigation_point_flags((NavigationPoint *)record) & 1) {
            for (i = 0; i < 30; i++) {
                if (navigation_point_object_id((NavigationPoint *)record) == ids[i] && node->owner != 0
                    && ((NavigationNodeOwnerView *)node->owner)->active != 0) {
                    Nav_AddGoalNode(base, node->key);
                    count++;
                }
            }
        }
    }
    if (count == 0) {
        for (node = (NavigationSearchNodeView *)((NavigationSearchGraphView *)base)->nodes; node != 0; node = node->next) {
            record = Portal_GetGraphPoint(base, node->key);
            if (navigation_point_flags((NavigationPoint *)record) & 1) {
                for (i = 0; i < 30; i++) {
                    if (navigation_point_object_id((NavigationPoint *)record) == ids[i]) {
                        Nav_AddGoalNode(base, node->key);
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

extern s32 Playerai_GetWeaponClassId(Player *, s32);

s32 Nav_SelectCloseAttackPickupGoal(CloseAttackBrain *closeAttackBrain) {
    s32 data[30];
    s32 *cursor;
    s32 count;
    CNavData *global;
    s32 value;
    s32 current;
    NavigationSearchNode *entry;

    global = (CNavData *)&g_navigationGraph;
    Portal_ResetSearchState(global);
    Route_ClearGoalList((s32)global);
    count = 29;
    cursor = &data[29];
    do {
        *cursor = 0;
        count--;
        cursor--;
    } while (count >= 0);
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
        entry = (NavigationSearchNode *)Portal_FindSearchNode((PickupGoalNodeList *)global, current);
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
    s32 *cursor;
    s32 count;
    char *global;
    s32 value;
    s32 current;

    global = (char *)&g_navigationGraph;
    Portal_ResetSearchState(global);
    Route_ClearGoalList((s32)global);
    count = 29;
    cursor = &data[29];
    do {
        *cursor = 0;
        count--;
        cursor--;
    } while (count >= 0);
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
    Portal_ResetSearchState(global);
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

/** Return the empty result used by callers at VRAM 0x8020F59C. */
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
    node = ((CNavData *)base)->nodes;
    count = 0;
    if (node != 0) {
        do {
            result = Portal_GetGraphPoint(base, node->key);
            if ((navigation_point_flags((NavigationPoint *)result) & 1) &&
                navigation_point_object_id((NavigationPoint *)result) == 1614 &&
                (s8)((LevelActor *)node->object)->aiMode == 0) {
                Nav_AddGoalNode(base, node->key);
                count += 1;
            }
            node = node->next;
        } while (node != 0);
    }
    return count;
}
