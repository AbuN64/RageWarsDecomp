#include "COMMON/WIDGETRECAT1A.H"
#include "TYPES.H"

/* Links a new node into a tree just before a given node, making it the parent's first child when the given node was, and otherwise attaching it after the predecessor that Node_FindWidgetPredecessor's search finds from the parent by the given node's id. Adapted from Node_FindWidgetPredecessor with the search body kept as a static inline helper and called after the new node's parent, next and child links are set. */



extern struct Tree *Node_FindWidgetPredecessor(struct Tree *node, s32 id);

static inline struct Tree *findPredecessor(struct Tree *node, s32 id) {
    s32 childId;
    struct Tree *found = 0;

    childId = id;
    while (node != 0 && found == 0) {
        if (node->next != 0 && node->next->id == (u16)id) {
            found = node;
        }
        if (found == 0 && node->child != 0) {
            found = Node_FindWidgetPredecessor(node->child, (u16)childId);
        }
        node = node->next;
    }
    return found;
}

void Node_InsertWidgetBefore(struct Tree *node, struct Tree *added) {
    struct Tree *parent;

    added->next = node;
    added->parent = node->parent;
    added->child = 0;
    parent = node->parent;
    if (parent->child == node) {
        parent->child = added;
    } else {
        findPredecessor(parent, (u16)node->id)->next = added;
    }
}
