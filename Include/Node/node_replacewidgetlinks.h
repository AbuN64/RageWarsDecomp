#ifndef NODE_NODE_REPLACEWIDGETLINKS_H
#define NODE_NODE_REPLACEWIDGETLINKS_H
#include "Frontend/frontend.h"
#include "types.h"
#include "Common/widget_tree.h"
struct MenuWidget;
extern struct Tree *Node_FindWidgetPredecessor(struct Tree *node, s32 id);
extern void Node_ReplaceWidgetLinks(s32 node, s32 parent, struct MenuWidget *oldWidget, struct MenuWidget *newWidget);
struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);
#endif
