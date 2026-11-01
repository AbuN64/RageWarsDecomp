#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include "TYPES.H"
#include "AI/NAV/SEARCH_NODE_STATE.H"
#include "include_asm.h"
#include "COMMON/NAVIGATION_ACTOR_SEARCH_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/AIPROFILE.H"
#include "AI/NAV/PICKUPTARGET.H"

/* SEARCHNODE.CPP */
/* Stores an id in the first free (-1) of the object's 64 id slots at 0x38 and flags the node with that
   id in the object's list at 0x24 as active. */

static inline Node *find_node(ObjNavAddGoalNode *obj, int id) {
    Node *node;

    for (node = obj->list; node != 0; node = node->next) {
        if (node->id == id) {
            return node;
        }
    }
    return 0;
}

void Nav_AddGoalNode(ObjNavAddGoalNode *obj, int id) {
    int i;

    for (i = 0; i < 64; i++) {
        if (obj->ids[i] == -1) {
            obj->ids[i] = id;
            find_node(obj, id)->active = 1;
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

    node = graph->nodes;
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

/** Set the word at byte offset 0x28 to the state value two. */
void Nav_CloseSearchNode(void *object) {
    NavigationSearchNode *node = object;
    node->open = 2;
}

int Nav_IsSearchNodeOpen(void *navigationSearchNode) {
    NavigationSearchNode *node = navigationSearchNode;
    return node->open == 1;
}

/** Report whether the word at object offset 0x28 equals two. */
int Nav_IsSearchNodeClosed(void *navigationSearchNode) {
    NavigationSearchNode *node = navigationSearchNode;
    return node->open == 2;
}

s32 Nav_HasOpenSearchNodes(CNavData *cNavData) {
    CNavData *graph = cNavData;
    NavigationSearchNode *record = graph->nodes;
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

/** Clear the word at offset 0x28. */
void Nav_ClearSearchNodeStatus(void *controller) {
    ObjRecAt28V2 *record = controller;
    record->state = 0;
}

/* ROUTECOST__SEARCHNODE.CPP */
extern s32 Route_GetRouteRelation(void *relationTable, s32 sourceNode, s32 destinationNode);

struct NavigationSearchGraphView; extern s32 Portal_SearchRelatedGoalPath(struct NavigationSearchGraphView *obj, s32 key, s32 requested, void *owner);

/** Reset the float field of each occupied player slot's table entry to the default value. */

extern char *Portal_FindSearchNode(CNavData *, int);
extern CNavData g_navigationGraph;

extern void *Portal_GetGraphPoint(void *, s32);


#if defined(VERSION_US)
#endif

/* FIND.CPP */
/* 80208000_25.CPP */
/* 80208000_25.CPP */
#if defined(VERSION_US)
char s_FindOshEdgeTCSText[12] =
    "oshEdge_t\013CS";
#endif

/* 80208000_27.CPP */
#if defined(VERSION_EU)
unsigned int k_FindEncodedWordsBlock1[3] = {
    0x00000000, 0x0007000D, 0x2401FFFF,
};
#endif

/* 80208000_26.CPP */
#if defined(VERSION_DE)
unsigned int k_FindEncodedWords[3] = {
    0x3F800000, 0x3F800000, 0x0C0AC91C,
};
#endif

/* 800C6E94.CPP */
#if defined(VERSION_US_REV1)
float g_FindEncodedWords[3] = {
    1.024f, -1.024f, 2.0f,
};
#endif

/* K_NAVCHECKCLOSEATTACKROUTEWORDSUS__SEARCHNODE.CPP */
/* 800C1E68_2.CPP */
#if defined(VERSION_US)
#endif
/* 800C2298.CPP */
#if defined(VERSION_EU)
/* ROM-grounded data for eu; supplied-list member has no us-rev1 placement. */
#endif

/* 80208000_28.CPP */
#if defined(VERSION_EU_X)
float k_NavCheckcloseattackrouteEncodedWordsBlock2[3] = {
    0.5f, 1.024f, -1.024f,
};
#endif
