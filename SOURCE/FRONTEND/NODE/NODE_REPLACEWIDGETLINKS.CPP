#include "COMMON/NODERECAT2A8.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/WIDGETRECAT1A.H"
#include <ultra64.h>
#include "TYPES.H"

MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier) {
    MenuWidget *node = root;
    u16 id = identifier;
    MenuWidget *found = 0;

    while (node != 0 && found == 0) {
        if (node->resource == id) {
            found = node;
        }
        if (found == 0 && node->child != 0) {
            found = Node_FindWidgetByResourceId(node->child, id);
        }
        node = node->sibling;
    }
    return found;
}

/* Searches the sibling list starting at node, descending depth first into each node's child list, for the first node whose next sibling carries the given id, and returns that predecessor or null. Adapted from Node_FindWidgetByResourceId with the id test moved from the node to its next sibling and the id taken as an int narrowed to unsigned short at each use, the recursive call reading a copy of it taken after the result is cleared. */



struct Tree *Node_FindWidgetPredecessor(struct Tree *node, s32 id) {
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

/* Recursively replaces a node reference throughout a linked hierarchy and copies the old node links into its replacement. */
void Node_ReplaceWidgetLinks(NodeFrontendReplaceWidgetLinks *node, NodeFrontendReplaceWidgetLinks *parent, NodeFrontendReplaceWidgetLinks *oldWidget, NodeFrontendReplaceWidgetLinks *newWidget) {
    NodeFrontendReplaceWidgetLinks *nextSibling;
    NodeFrontendReplaceWidgetLinks *firstChild;
    if (node != NULL) {
        nextSibling = node->nextSibling;
        if (nextSibling != NULL) {
            Node_ReplaceWidgetLinks(nextSibling,parent,oldWidget,newWidget);
        }
        firstChild = node->firstChild;
        if (firstChild != NULL) {
            Node_ReplaceWidgetLinks(firstChild, node, oldWidget, newWidget);
        }
        if (node->parent == oldWidget) {
            node->parent = newWidget;
        }
        if (node->nextSibling == oldWidget) {
            node->nextSibling = newWidget;
        }
        if (node->firstChild == oldWidget) {
            node->firstChild = newWidget;
        }
        if (node == oldWidget) {
            newWidget->parent = (NodeFrontendReplaceWidgetLinks *) node->parent;
            newWidget->nextSibling = (NodeFrontendReplaceWidgetLinks *) node->nextSibling;
            newWidget->firstChild = (NodeFrontendReplaceWidgetLinks *) node->firstChild;
        }
    }
}
