#ifndef AI_NAV_SEARCHNODE_H
#define AI_NAV_SEARCHNODE_H
#include "Ai/nav_symbols.h"
#include "types.h"
#include "Common/small_records.h"

struct ObjRecAt28V2;
struct ObjRecAt28V2 {
    char pad0[0x28];
    int state;
};
typedef struct ObjRecAt28V2 ObjRecAt28V2;

#include "types.h"
#include "Common/navigation_node_and_route_views.h"



#endif
