#include "Lists/externs.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/listheader.h"
#include "types.h"
#include "Common/self.h"
#include "Engine/lists.h"

/* LISTS.CPP */

/* Initializes an empty linked-list header by clearing its two links and count. */
void Lists_ClearHeader(ListHeader *list) {
    list->head = 0;
    list->tail = 0;
    list->count = 0;
}
/** Push a node onto the front of a doubly-linked list. */
void Lists_PrependNode(void *listHeader, void *node) {
    ListHeader *list = listHeader;
    if (list->count == 0) {
        list->head = node;
        list->tail = node;
        *(s32 *)node = 0;
        ((ResourceKeyView *)node)->key = 0;
    } else {
        ((ListNodeNextView *)node)->value = list->head;
        *(s32 *)node = 0;
        ((ListPreviousLinkView *)list->head)->previous = node;
        list->head = node;
    }
    list->count = list->count + 1;
}

/** Push a node onto the tail of a doubly-linked list; returns new count. */
s32 Lists_Append(ListLinkHeader *listHeader, ListLink *newNode) {
    ListLinkHeader *list = listHeader;
    s32 count;
    if ((((struct ListHeader *) ((s8 *) listHeader))->count) == 0) {
        (((struct ListHeader *) ((s8 *) listHeader))->head) = newNode;
        (((struct ListHeader *) ((s8 *) listHeader))->tail) = newNode;
        (((struct ListLink *) ((s8 *) newNode))->next) = 0;
        (((struct ListLink *) ((s8 *) newNode))->prev) = 0;
    } else {
        (((struct ListPreviousLinkView *) ((s8 *) newNode))->previous) = (((struct ListHeader *) ((s8 *) listHeader))->tail);
        (((struct ListLink *) ((s8 *) newNode))->prev) = 0;
        (((struct ListNodeNextView *) ((s8 *) ((struct ListHeader *) ((s8 *) listHeader))->tail))->value) = newNode;
        (((struct ListHeader *) ((s8 *) listHeader))->tail) = newNode;
    }
    list->count = list->count + 1;
    return list->count;
}
int Lists_Remove(ListLinkHeader *listHeader, ListLink *listLink) {
    if (listLink->prev != 0) {
        listLink->prev->next = listLink->next;
    }
    if (listLink->next != 0) {
        listLink->next->prev = listLink->prev;
    }
    if (listHeader->head == listLink) {
        listHeader->head = listLink->prev;
    }
    if (listHeader->tail == listLink) {
        listHeader->tail = listLink->next;
    }
    listHeader->count -= 1;
    return listHeader->count;
}
/* Reset a pool list header. */
static inline void clear_list(ListHeader *list) {
    list->head = 0;
    list->tail = 0;
    list->count = 0;
}
/* Append a free node and return the new list length. */
static inline s32 append(ListHeader *list, ListLink *node) {
    s32 count;
    if (list->count == 0) {
        list->head = node;
        list->tail = node;
        node->next = 0;
        node->prev = 0;
    } else {
        node->next = list->tail;
        node->prev = 0;
        ((ListLink *)list->tail)->prev = node;
        list->tail = node;
    }
    count = list->count + 1;
    list->count = count;
    return count;
}
/* Reset the free and active headers and link every fixed-size pool node. */
void Lists_InitFromPool(ListHeader *lists, void *pool, s32 stride, s32 count) {
    s32 remaining;
    clear_list(lists);
    clear_list(lists + 1);
    for (remaining = count - 1; remaining != -1; remaining--) {
        append(lists, (ListLink *)pool);
        pool = (char *)pool + stride;
    }
}
ListLink *Lists_MoveHeadToInactiveList(Lists18 *lists) {
    ListLink *node;
    ListLink *tail;
    ListLinkHeader *inactive;
    node = lists->active.head;
    if (node != 0) {
        if (node->prev != 0) {
            node->prev->next = node->next;
        }
        if (node->next != 0) {
            node->next->prev = node->prev;
        }
        if (lists->active.head == node) {
            lists->active.head = node->prev;
        }
        if (lists->active.tail == node) {
            lists->active.tail = node->next;
        }
        lists->active.count -= 1;
        inactive = &lists->inactive;
        if (inactive->count == 0) {
            inactive->head = node;
            inactive->tail = node;
            node->next = 0;
            node->prev = 0;
        } else {
            tail = inactive->tail;
            node->prev = 0;
            node->next = tail;
            inactive->tail->prev = node;
            inactive->tail = node;
        }
        inactive->count += 1;
    }
    return node;
}
void Lists_MoveNodeToActiveList(Lists18 *lists, ListLink *node) {
    ListLinkHeader *inactive;
    ListLink *tail;
    inactive = &lists->inactive;
    if (node->prev != 0) {
        node->prev->next = node->next;
    }
    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (inactive->head == node) {
        inactive->head = node->prev;
    }
    if (inactive->tail == node) {
        inactive->tail = node->next;
    }
    inactive->count -= 1;
    if (lists->active.count == 0) {
        lists->active.head = node;
        lists->active.tail = node;
        node->next = 0;
        node->prev = 0;
    } else {
        tail = lists->active.tail;
        node->prev = 0;
        node->next = tail;
        lists->active.tail->prev = node;
        lists->active.tail = node;
    }
    lists->active.count += 1;
}
s16 Lists_ChooseWeightedEntry(s16 *weightedEntries) {
    s16 *entry;
    s16 *start;
    s32 random;
    s32 total;
    s32 value;
    entry = weightedEntries;
    total = 0;
    start = entry;
    if (*entry != -1) {
        do {
            total += entry[1];
            entry += 2;
        } while (*entry != -1);
    }
    random = Graphu64_NextRandom();
    entry = start;
    value = random % total;
    total = 0;
    while (*entry != -1) {
        total += entry[1];
        if (total >= value) {
            break;
        }
        entry += 2;
    }
    return *entry;
}
/** Clear the leading halfword of the supplied object. */
void Lists_ClearWeightedTable(WeightedTable *object) {
    object->count = 0;
}
s32 Lists_AppendWeightedEntry(WeightedTable *table, s16 value, s16 weight)
{
  s16 entryIndex;
  entryIndex = table->count;
  if (entryIndex == 24)
  {
    return 0;
  }
  table->entries[entryIndex][0] = value;
  table->entries[table->count][1] = weight;
  table->count = ((u16) table->count) + 1;
  return 1;
}
s16 Lists_ChooseWeightedTableEntry(WeightedTable *weightedTable) {
    s16 *entry;
    s16 *start;
    s32 random;
    s32 total;
    s32 value;
    if (weightedTable->count == 0) {
        return -1;
    }
    weightedTable->entries[weightedTable->count][0] = -1;
    entry = &weightedTable->entries[0][0];
    total = 0;
    start = entry;
    if (*entry != -1) {
        do {
            total += entry[1];
            entry += 2;
        } while (*entry != -1);
    }
    random = Graphu64_NextRandom();
    entry = start;
    value = random % total;
    total = 0;
    while (*entry != -1) {
        total += entry[1];
        if (total >= value) {
            break;
        }
        entry += 2;
    }
    return *entry;
}
