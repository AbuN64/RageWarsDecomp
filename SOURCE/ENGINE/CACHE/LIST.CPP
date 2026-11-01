#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "ENGINE/CACHE/LIST.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "COMMON/VECTOR4F.H"

/* LIST.CPP */
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
        *(char **)((char *)node + owner->nextOffset) = head;
        *(void **)((char *)owner->head + owner->prevOffset) = node;
    } else {
        *(void **)((char *)node + owner->nextOffset) = 0;
        owner->tail = node;
    }
    *(void **)((char *)node + owner->prevOffset) = 0;
    owner->head = node;
    owner->count = owner->count + 1;
}

s32 List_AppendIntrusive(IntrusiveList *list, void *node) {
    void **prevLink;
    void **tailLink;
    void **nextLink;
    void *tail;
    s32 count;

    tail = list->tail;
    if (tail != 0) {
        prevLink = node + list->prevOffset;
        *prevLink = tail;
        tailLink = list->tail + list->nextOffset;
        *tailLink = node;
    } else {
        prevLink = node + list->prevOffset;
        *prevLink = 0;
        list->head = node;
    }
    nextLink = node + list->nextOffset;
    *nextLink = 0;
    list->tail = node;
    count = list->count + 1;
    list->count = count;
    return count;
}

void List_InsertBeforeIntrusive(void *list, s32 anchorNode, s32 insertedNode) {
    char *o = (char *) list;
    s32 next = *(s32 *) (anchorNode + ((IntrusiveList *)o)->prevOffset);
    s32 v0;

    if (next != 0) {
        s32 off8;
        *(s32 *) (next + ((IntrusiveList *)o)->nextOffset) = insertedNode;
        off8 = ((IntrusiveList *)o)->prevOffset;
        *(s32 *) (insertedNode + off8) = *(s32 *) (anchorNode + off8);
        *(s32 *) (anchorNode + ((IntrusiveList *)o)->prevOffset) = insertedNode;
        *(s32 *) (insertedNode + ((IntrusiveList *)o)->nextOffset) = anchorNode;
        v0 = ((IntrusiveList *)o)->count + 1;
    } else {
        s32 tail = ((IntrusiveList *)o)->head;
        if (tail != 0) {
            *(s32 *) (insertedNode + ((IntrusiveList *)o)->nextOffset) = tail;
            *(s32 *) (((IntrusiveList *)o)->head + ((IntrusiveList *)o)->prevOffset) = insertedNode;
        } else {
            *(s32 *) (insertedNode + ((IntrusiveList *)o)->nextOffset) = 0;
            ((IntrusiveList *)o)->tail = insertedNode;
        }
        *(s32 *) (insertedNode + ((IntrusiveList *)o)->prevOffset) = 0;
        ((IntrusiveList *)o)->head = insertedNode;
        v0 = ((IntrusiveList *)o)->count + 1;
    }
    ((IntrusiveList *)o)->count = v0;
}

void List_InsertAfterIntrusive(void *list, s32 anchorNode, s32 insertedNode) {
    char *o = (char *) list;
    s32 next = *(s32 *) (anchorNode + ((IntrusiveList *)o)->nextOffset);
    s32 v0;

    if (next != 0) {
        s32 offC;
        *(s32 *) (next + ((IntrusiveList *)o)->prevOffset) = insertedNode;
        offC = ((IntrusiveList *)o)->nextOffset;
        *(s32 *) (insertedNode + offC) = *(s32 *) (anchorNode + offC);
        *(s32 *) (anchorNode + ((IntrusiveList *)o)->nextOffset) = insertedNode;
        *(s32 *) (insertedNode + ((IntrusiveList *)o)->prevOffset) = anchorNode;
        v0 = ((IntrusiveList *)o)->count + 1;
    } else {
        s32 head = ((IntrusiveList *)o)->tail;
        if (head != 0) {
            *(s32 *) (insertedNode + ((IntrusiveList *)o)->prevOffset) = head;
            *(s32 *) (((IntrusiveList *)o)->tail + ((IntrusiveList *)o)->nextOffset) = insertedNode;
        } else {
            *(s32 *) (insertedNode + ((IntrusiveList *)o)->prevOffset) = 0;
            ((IntrusiveList *)o)->head = insertedNode;
        }
        *(s32 *) (insertedNode + ((IntrusiveList *)o)->nextOffset) = 0;
        ((IntrusiveList *)o)->tail = insertedNode;
        v0 = ((IntrusiveList *)o)->count + 1;
    }
    ((IntrusiveList *)o)->count = v0;
}

void List_RemoveIntrusive(void *list, void *node) {
    IntrusiveList *owner = list;
    char *next;
    char *prev;
    next = *(char **)((char *)node + owner->prevOffset);
    if (next != 0) {
        s32 off = owner->nextOffset;
        *(char **)(next + off) = *(char **)((char *)node + off);
    }
    prev = *(char **)((char *)node + owner->nextOffset);
    if (prev != 0) {
        s32 off = owner->prevOffset;
        *(char **)(prev + off) = *(char **)((char *)node + off);
    }
    if (owner->head == node) {
        owner->head = *(void **)((char *)node + owner->nextOffset);
    }
    if (owner->tail == node) {
        owner->tail = *(void **)((char *)node + owner->prevOffset);
    }
    owner->count = owner->count - 1;
}

/** Advance the cursor by its stride and decrement its remaining count. */
void List_DropIntrusiveHead(IntrusiveList *list) {
    char *cursor = list->head;
    int stride = list->nextOffset;
    int value = *(int *)(cursor + stride);
    int count = list->count - 1;
    list->count = count;
    list->head = value;
}

/** Advance the cursor by its stride and decrement its remaining count. */
void List_DropIntrusiveTail(IntrusiveList *list) {
    char *cursor = list->tail;
    int stride = list->prevOffset;
    int value = *(int *)(cursor + stride);
    int count = list->count - 1;
    list->count = count;
    list->tail = value;
}

void List_MoveIntrusiveToHead(void *list, s32 nodeToMove) {
    char *o = (char *)list;
    s32 next;
    s32 prev;
    s32 head;

    next = *(s32 *)(nodeToMove + ((IntrusiveList *)o)->prevOffset);
    if (next != 0) {
        s32 off = ((IntrusiveList *)o)->nextOffset;
        *(s32 *)(next + off) = *(s32 *)(nodeToMove + off);
    }
    prev = *(s32 *)(nodeToMove + ((IntrusiveList *)o)->nextOffset);
    if (prev != 0) {
        s32 off = ((IntrusiveList *)o)->prevOffset;
        *(s32 *)(prev + off) = *(s32 *)(nodeToMove + off);
    }
    if (((IntrusiveList *)o)->head == nodeToMove) {
        ((IntrusiveList *)o)->head = *(s32 *)(nodeToMove + ((IntrusiveList *)o)->nextOffset);
    }
    if (((IntrusiveList *)o)->tail == nodeToMove) {
        ((IntrusiveList *)o)->tail = *(s32 *)(nodeToMove + ((IntrusiveList *)o)->prevOffset);
    }
    ((IntrusiveList *)o)->count = ((IntrusiveList *)o)->count - 1;

    head = ((IntrusiveList *)o)->head;
    if (head != 0) {
        *(s32 *)(nodeToMove + ((IntrusiveList *)o)->nextOffset) = head;
        *(s32 *)(((IntrusiveList *)o)->head + ((IntrusiveList *)o)->prevOffset) = nodeToMove;
    } else {
        *(s32 *)(nodeToMove + ((IntrusiveList *)o)->nextOffset) = 0;
        ((IntrusiveList *)o)->tail = nodeToMove;
    }
    *(s32 *)(nodeToMove + ((IntrusiveList *)o)->prevOffset) = 0;
    ((IntrusiveList *)o)->head = nodeToMove;
    ((IntrusiveList *)o)->count = ((IntrusiveList *)o)->count + 1;
}

void List_MoveIntrusiveToTail(void *list, s32 nodeToMove) {
    char *o = (char *)list;
    s32 next;
    s32 prev;
    s32 tail;

    next = *(s32 *)(nodeToMove + ((IntrusiveList *)o)->prevOffset);
    if (next != 0) {
        s32 off = ((IntrusiveList *)o)->nextOffset;
        *(s32 *)(next + off) = *(s32 *)(nodeToMove + off);
    }
    prev = *(s32 *)(nodeToMove + ((IntrusiveList *)o)->nextOffset);
    if (prev != 0) {
        s32 off = ((IntrusiveList *)o)->prevOffset;
        *(s32 *)(prev + off) = *(s32 *)(nodeToMove + off);
    }
    if (((IntrusiveList *)o)->head == nodeToMove) {
        ((IntrusiveList *)o)->head = *(s32 *)(nodeToMove + ((IntrusiveList *)o)->nextOffset);
    }
    if (((IntrusiveList *)o)->tail == nodeToMove) {
        ((IntrusiveList *)o)->tail = *(s32 *)(nodeToMove + ((IntrusiveList *)o)->prevOffset);
    }
    ((IntrusiveList *)o)->count = ((IntrusiveList *)o)->count - 1;

    tail = ((IntrusiveList *)o)->tail;
    if (tail != 0) {
        *(s32 *)(nodeToMove + ((IntrusiveList *)o)->prevOffset) = tail;
        *(s32 *)(((IntrusiveList *)o)->tail + ((IntrusiveList *)o)->nextOffset) = nodeToMove;
    } else {
        *(s32 *)(nodeToMove + ((IntrusiveList *)o)->prevOffset) = 0;
        ((IntrusiveList *)o)->head = nodeToMove;
    }
    *(s32 *)(nodeToMove + ((IntrusiveList *)o)->nextOffset) = 0;
    ((IntrusiveList *)o)->tail = nodeToMove;
    ((IntrusiveList *)o)->count = ((IntrusiveList *)o)->count + 1;
}

void *List_CountIntrusiveNodes(void *intrusiveList) {
    s32 index;
    s32 offset;
    void *node;

    node = ((IntrusiveList *)intrusiveList)->head;
    if (node == 0) {
        return 0;
    }
    index = Graphu64_NextRandom() % (u32)((IntrusiveList *)intrusiveList)->count;
    index--;
    if (index != -1) {
        offset = ((IntrusiveList *)intrusiveList)->nextOffset;
        do {
            { u8 *cursor = (u8 *)node; cursor += offset; node = *(void **)cursor; }
            index--;
        } while (index != -1);
    }
    return node;
}

void List_TraverseIntrusiveNodes(IntrusiveList *list) {
    s32 node = list->head;
    if (node != 0) {
        s32 offset = list->nextOffset;
        node = *(s32 *)(node + offset);
        while (node != 0) {
            node = *(s32 *)(node + offset);
        }
    }
}

int List_ContainsIntrusiveNode(IntrusiveList *list, int wantedNode) {
    int node = list->head;
    if (node != 0) {
        do {
            if (node == wantedNode) {
                return 1;
            }
            node = *(int *)(node + list->nextOffset);
        } while (node != 0);
    }
    return 0;
}
