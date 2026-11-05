#ifndef FRONTEND_NODE_FINDWIDGETBYRESOURCEID_H
#define FRONTEND_NODE_FINDWIDGETBYRESOURCEID_H
#include "Frontend/frontend.h"
#include "types.h"
struct MenuWidget;
extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);
#endif
