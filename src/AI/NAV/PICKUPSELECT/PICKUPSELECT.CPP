#include "COMMON/NAVIGATION_ACTOR_SEARCH_VIEWS.H"
#include "AI/SHARED_PICKUPGOALNODE.H"
#include "AI/NAV/NAV_SELECTPICKUPGOAL.H"
#include "AI/NAV/NAV_SELECTPICKUPGOALEU.H"

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
