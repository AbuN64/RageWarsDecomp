#include "Common/runtime_declarations.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Common/heap_arena_entry.h"
#include "types.h"
#include "Engine/Cache/list.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Common/vector4f.h"

/* LIST.CPP */

/* The link slot a list node keeps at the given byte offset; the offset is chosen per list at run time. */
#define LinkAt(node, offset) (*(void **)((char *)(node) + (offset)))

/** Initialize a five-word record. */
void List_InitializeIntrusive(IntrusiveList *list, s32 prevOffset, s32 nextOffset) {
    list->prevOffset = prevOffset;
    list->nextOffset = nextOffset;
    list->tail = 0;
    list->head = 0;
    list->count = 0;
}

void List_PrependIntrusive(void *list, void *node) {
    IntrusiveList *owner = list;
    char *head;
    head = owner->head;
    if (head != 0) {
        LinkAt(node, owner->nextOffset) = head;
        LinkAt(owner->head, owner->prevOffset) = node;
    } else {
        LinkAt(node, owner->nextOffset) = 0;
        owner->tail = node;
    }
    LinkAt(node, owner->prevOffset) = 0;
    owner->head = node;
    owner->count = owner->count + 1;
}

/* Links node after the current tail and returns the new element count. */
s32 List_AppendIntrusive(IntrusiveList *list, void *node) {
    void *tail = list->tail;

    if (tail != 0) {
        LinkAt(node, list->prevOffset) = tail;
        LinkAt(list->tail, list->nextOffset) = node;
    } else {
        LinkAt(node, list->prevOffset) = 0;
        list->head = node;
    }
    LinkAt(node, list->nextOffset) = 0;
    list->tail = node;
    list->count = list->count + 1;
    return list->count;
}

/* Links insertedNode into the list directly before anchorNode, or at the head when the anchor has no predecessor. */
void List_InsertBeforeIntrusive(void *list, s32 anchorNode, s32 insertedNode) {
    IntrusiveList *owner = (IntrusiveList *)list;
    void *anchor = (void *)anchorNode;
    void *inserted = (void *)insertedNode;
    void *previous = LinkAt(anchor, owner->prevOffset);

    if (previous != 0) {
        LinkAt(previous, owner->nextOffset) = inserted;
        LinkAt(inserted, owner->prevOffset) = LinkAt(anchor, owner->prevOffset);
        LinkAt(anchor, owner->prevOffset) = inserted;
        LinkAt(inserted, owner->nextOffset) = anchor;
    } else {
        void *oldHead = owner->head;
        if (oldHead != 0) {
            LinkAt(inserted, owner->nextOffset) = oldHead;
            LinkAt(owner->head, owner->prevOffset) = inserted;
        } else {
            LinkAt(inserted, owner->nextOffset) = 0;
            owner->tail = inserted;
        }
        LinkAt(inserted, owner->prevOffset) = 0;
        owner->head = inserted;
    }
    owner->count = owner->count + 1;
}

/* Links insertedNode into the list directly after anchorNode, or at the tail when the anchor has no successor. */
void List_InsertAfterIntrusive(void *list, s32 anchorNode, s32 insertedNode) {
    IntrusiveList *owner = (IntrusiveList *)list;
    void *anchor = (void *)anchorNode;
    void *inserted = (void *)insertedNode;
    void *following = LinkAt(anchor, owner->nextOffset);

    if (following != 0) {
        LinkAt(following, owner->prevOffset) = inserted;
        LinkAt(inserted, owner->nextOffset) = LinkAt(anchor, owner->nextOffset);
        LinkAt(anchor, owner->nextOffset) = inserted;
        LinkAt(inserted, owner->prevOffset) = anchor;
    } else {
        void *oldTail = owner->tail;
        if (oldTail != 0) {
            LinkAt(inserted, owner->prevOffset) = oldTail;
            LinkAt(owner->tail, owner->nextOffset) = inserted;
        } else {
            LinkAt(inserted, owner->prevOffset) = 0;
            owner->head = inserted;
        }
        LinkAt(inserted, owner->nextOffset) = 0;
        owner->tail = inserted;
    }
    owner->count = owner->count + 1;
}

void List_RemoveIntrusive(void *list, void *node) {
    IntrusiveList *owner = list;
    char *next;
    char *prev;
    next = (char *)LinkAt(node, owner->prevOffset);
    if (next != 0) {
        s32 off = owner->nextOffset;
        LinkAt(next, off) = LinkAt(node, off);
    }
    prev = (char *)LinkAt(node, owner->nextOffset);
    if (prev != 0) {
        s32 off = owner->prevOffset;
        LinkAt(prev, off) = LinkAt(node, off);
    }
    if (owner->head == node) {
        owner->head = LinkAt(node, owner->nextOffset);
    }
    if (owner->tail == node) {
        owner->tail = LinkAt(node, owner->prevOffset);
    }
    owner->count = owner->count - 1;
}

/** Drops the head node: its successor becomes the head and the count falls by one. */
void List_DropIntrusiveHead(IntrusiveList *list) {
    list->head = LinkAt(list->head, list->nextOffset);
    list->count = list->count - 1;
}

/** Drops the tail node: its predecessor becomes the tail and the count falls by one. */
void List_DropIntrusiveTail(IntrusiveList *list) {
    list->tail = LinkAt(list->tail, list->prevOffset);
    list->count = list->count - 1;
}

/* Detaches node from its neighbours and from the list's head and tail, and decrements the count. */
static void List_UnlinkIntrusiveNode(IntrusiveList *owner, void *node) {
    void *previous = LinkAt(node, owner->prevOffset);
    void *following;

    if (previous != 0) {
        LinkAt(previous, owner->nextOffset) = LinkAt(node, owner->nextOffset);
    }
    following = LinkAt(node, owner->nextOffset);
    if (following != 0) {
        LinkAt(following, owner->prevOffset) = LinkAt(node, owner->prevOffset);
    }
    if (owner->head == node) {
        owner->head = LinkAt(node, owner->nextOffset);
    }
    if (owner->tail == node) {
        owner->tail = LinkAt(node, owner->prevOffset);
    }
    owner->count = owner->count - 1;
}

/* Moves a node already in the list to the head. */
void List_MoveIntrusiveToHead(void *list, s32 nodeToMove) {
    IntrusiveList *owner = (IntrusiveList *)list;
    void *node = (void *)nodeToMove;
    void *oldHead;

    List_UnlinkIntrusiveNode(owner, node);
    oldHead = owner->head;
    if (oldHead != 0) {
        LinkAt(node, owner->nextOffset) = oldHead;
        LinkAt(owner->head, owner->prevOffset) = node;
    } else {
        LinkAt(node, owner->nextOffset) = 0;
        owner->tail = node;
    }
    LinkAt(node, owner->prevOffset) = 0;
    owner->head = node;
    owner->count = owner->count + 1;
}

/* Moves a node already in the list to the tail. */
void List_MoveIntrusiveToTail(void *list, s32 nodeToMove) {
    IntrusiveList *owner = (IntrusiveList *)list;
    void *node = (void *)nodeToMove;
    void *oldTail;

    List_UnlinkIntrusiveNode(owner, node);
    oldTail = owner->tail;
    if (oldTail != 0) {
        LinkAt(node, owner->prevOffset) = oldTail;
        LinkAt(owner->tail, owner->nextOffset) = node;
    } else {
        LinkAt(node, owner->prevOffset) = 0;
        owner->head = node;
    }
    LinkAt(node, owner->nextOffset) = 0;
    owner->tail = node;
    owner->count = owner->count + 1;
}

/* Returns a pseudo-randomly chosen node of the list, or null when the list is empty
 * (the name is historical: it does not count anything). */
void *List_CountIntrusiveNodes(void *intrusiveList) {
    IntrusiveList *list = (IntrusiveList *)intrusiveList;
    void *node = list->head;
    s32 stepsRemaining;

    if (node == 0) {
        return 0;
    }
    stepsRemaining = Graphu64_NextRandom() % (u32)list->count;
    while (stepsRemaining-- != 0) {
        node = LinkAt(node, list->nextOffset);
    }
    return node;
}

/* Walks the list from head to tail without acting on any node. */
void List_TraverseIntrusiveNodes(IntrusiveList *list) {
    void *node = list->head;

    while (node != 0) {
        node = LinkAt(node, list->nextOffset);
    }
}

/* Returns 1 when wantedNode is linked into the list, else 0. */
int List_ContainsIntrusiveNode(IntrusiveList *list, int wantedNode) {
    void *node = list->head;

    while (node != 0) {
        if ((int)node == wantedNode) {
            return 1;
        }
        node = LinkAt(node, list->nextOffset);
    }
    return 0;
}
