#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include "TYPES.H"
#include "COMMON/SELF.H"
#include "AI/NAV/PORTAL_INITSEARCHNODE.H"
#include "COMMON/POOLED_FLOATS.H"

extern struct {s32 *pointStorage;} g_navigationGraph;


extern void Graphu64_SubtractVectors(struct CVector3_t *difference, struct CVector3_t *leftVector, struct CVector3_t *rightVector);

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

extern CollisionQuery g_portalDefaultCollisionQuery;

extern CollisionQuery g_portalModeCollisionQuery;

extern CollisionQuery g_portalNoModelFlagCollisionQuery;

extern CollisionQuery g_portalAlternateCollisionQuery;

extern s32 Insthdr_GetModelCollisionFlag1(void *);

extern s32 Insthdr_IsInactiveOrCollisionOption4(void *);

extern s32 Insthdr_GetModelCollisionFlag8(void *);

extern s32 Unicol_MoveActorWithCollision(ActorInstanceHeader *, CVector3, CollisionQuery *);

/** Return an indexed record from the table referenced by the input. */
void *Portal_GetGraphPoint(void *table, int index) {
    char *base = *(char **)table;
    int stride = *(int *)base;
    return base + (index * stride + 8);
}

/** Return an indexed record from the table at object offset 0x8. */
void *Portal_GetStridedTableEntry(struct NavigationLinkListView *object, int index) {
    char *base = (char *)object->table;
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
  char *nodeStorage;
  s32 *base;
  node->value = g_portalNodeInitialValue;
  node->key = nodeKey;
  node->state = -1;
  node->flags = 0;
  node->next = 0;
  base = g_navigationGraph.pointStorage;
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

s32 Portal_FindNearestPointIndex(struct NavigationSearchGraphView *pointSet, void *point) {
    CVector3 offset;
    f32 distanceSq;
    f32 bestDistanceSq;
    void *items;
    s32 stride;
    s32 index;
    s32 bestIndex;

    bestIndex = -1;
    bestDistanceSq = 0.0f;
    index = 0;
    if (pointSet->count > 0) {
        do {
            items = pointSet->records;
            stride = *(s32 *)items;
            Graphu64_SubtractVectors(&offset, point, (char *)items + (index * stride + 8));
            distanceSq = (offset.x * offset.x) + (offset.y * offset.y) + (offset.z * offset.z);
            if ((bestIndex < 0) || (distanceSq < bestDistanceSq)) {
                bestIndex = index;
                bestDistanceSq = distanceSq;
            }
            index += 1;
        } while (index < pointSet->count);
    }
    return bestIndex;
}

int Portal_FindLinkIndex(Graph *graph, int from, int to) {
    int i;
    Link *link;

    for (i = 0; i < graph->count; i++) {
        link = (Link *)((char *)&graph->links->first + i * graph->links->stride);
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

s32 Portal_CollectIncidentLinks(NavigationLinkListView *list, s32 value, s32 *partners, s32 *indices) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    if (list->count > 0) {
        do {
            s32 product = i * list->table->first;
            s32 offset = product + 8;
            u16 *entry;
            u16 *other_entry;

            entry = (u16 *)((char *)list->table + offset);
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
        } while (i < list->count);
    }
    return found;
}

s32 Portal_IsNodeMovementBlocked(s32 **nodeStorage, ActorInstanceHeader *instance, s32 nodeKey) {
    CVector3 position;
    CollisionQuery collision;
    ActorInstanceHeader saved;
    s32 first_test;
    s32 result;
    s32 *table;
    void *entry;

    table = *nodeStorage;
    entry = (u8 *)table + ((nodeKey * table[0]) + 8);
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
    saved = *instance;
    result = Unicol_MoveActorWithCollision(instance, position, &collision);
    *instance = saved;
    return result == 0;
}

void *Portal_FindSearchNode(char *object, s32 current) {
    CNavData *graph = (CNavData *)object;
    NavigationSearchNode *record = graph->nodes;
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

void Portal_ResetSearchState(struct NavigationSearchGraphView *graph) {
    struct NavigationSearchNodeView *node;
    f32 k;

    node = graph->nodes;
    if (node != 0) {
        k = (-1.0f);
        do {
            node->value = k;
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
